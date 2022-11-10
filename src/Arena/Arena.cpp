#include "Arena.hpp"
#include "../CMGT_PrototypeGame.hpp"
#include "../Utility/Timers/TimerManager.hpp"
#include "ConstantManager.hpp"
#include "../Audio/Jukebox.hpp"
#include "../Engine/ResourceManager.hpp"
#include "../Utility/Tweening/TweenManager.hpp"
#include "../Utility/Tweening/SpritePosTween.hpp"
#include "../Utility/Tweening/RectangleShapeSizeTween.hpp"


const sf::Vector2f Arena::FULL_WELLNESS_BAR_SIZE = sf::Vector2f{200,25};


Arena::Arena(CMGT_PrototypeGame& game) 
	: Scene("Arena")
	, game_(game)
	, enemiesSlain_(0)
	, difficulty_(Difficulty::Normal)
	, outputLog_(sf::Vector2f{175,460})
	, playerTurn_(true)
	, defeated(false)
	, gameOverScreen_(nullptr)
{
}

void Arena::Continue(const SaveInformation& saveInformation)
{
	difficulty_ = saveInformation.difficulty;
	player_ = saveInformation.player;
	opponent_ = saveInformation.opponent;
	
	player_.OverrideDamageDone(saveInformation.damageDone);
	enemiesSlain_ = saveInformation.enemiesSlain;
	
	GenericStuff();
	MakeOpponentAvatar();
	
	playerTurn_ = saveInformation.playerTurn;
	
	if (!saveInformation.playerTurn)
	{
		for (std::unique_ptr<Button>& button : moveButtons_)
			button->Lock(true);
		
		TimerManager::AddTimer(Timer(sf::seconds(1), [this] ()
		{
			GenerateOpponentTurn();
		}));
	}

	UpdateWellnessBars();
}

void Arena::Begin(const sf::String& name, const Avatar& avatar, Attributes& attributes, const Difficulty& difficulty) 
{
	difficulty_ = difficulty;
	
	attributes.FillRemainingPoints();
	player_.Init(name,avatar,attributes);

	GenerateNewOpponent();
	GenericStuff();
	
	
}

void Arena::GenericStuff() {
	eventHandler.Subscribe(sf::Event::KeyPressed, [this] (const sf::Event& event)
	{
		if (event.key.code == sf::Keyboard::G)
			player_.Damage(10);
	});
	
	
	Jukebox::Play(Mode::Battle);
	
	player_.SetOutputLog(outputLog_);
	opponent_.SetOutputLog(outputLog_);
	AddChild(&outputLog_);

	CreateArena();

	magicSound_.setBuffer(*ResourceManager::LoadSoundBuffer("sounds/magic.wav"));
	magicSound_.setVolume(50);
	attackSound_.setBuffer(*ResourceManager::LoadSoundBuffer("sounds/attack.wav"));
	attackSound_.setVolume(70);
	prepAndRecoverSound_.setBuffer(*ResourceManager::LoadSoundBuffer("sounds/recover.wav"));
	prepAndRecoverSound_.setVolume(50);
	trembleSound_.setBuffer(*ResourceManager::LoadSoundBuffer("sounds/tremble.wav"));
	victorySound_.setBuffer(*ResourceManager::LoadSoundBuffer("sounds/victory.wav"));
	victorySound_.setVolume(30);
	defeatSound_.setBuffer(*ResourceManager::LoadSoundBuffer("sounds/defeat.wav"));
	
	restorationEffect_ = std::make_unique<AnimationSprite>(sf::Vector2f{}, "abilities/restoration.png", 3, 3, 1);
	restorationEffect_->SetDelay(50);
	restorationEffect_->SetScale(2.5f, 1.4f);

	preparationEffect_ = std::make_unique<AnimationSprite>(sf::Vector2f{}, "abilities/preparation.png", 3, 3, 1);
	preparationEffect_->SetDelay(50);
	preparationEffect_->SetScale(2.5f, 1.4f);

	magicEffect_ = std::make_unique<AnimationSprite>(sf::Vector2f{}, "abilities/magic.png", 3, 3, 1);
	magicEffect_->SetDelay(50);
	magicEffect_->SetScale(0.7f, 0.7f);


	opponent_.SetOnDeathAction([this] ()
	{
		sf::Vector2f pos = ConstantManager::Get(opponent_.avatar(), Orientation::Right);
		pos.y -= 500;
		TweenManager::AddTween(new SpritePosTween(opponentAvatar_.get(), pos, sf::milliseconds(300)))
		->SetEndAction([this]()
		{
			RemoveChild(opponentAvatar_.get());
			
			TimerManager::AddTimer(Timer(sf::seconds(2), [this] ()
			{
				GenerateNewOpponent();
				UpdateInformationDisplay();
				outputLog_.Push(opponent_.name() + " joins the fray!");
				
				TimerManager::AddTimer(Timer(sf::seconds(1), [this] ()
				{
					DecideTurn();
				}));
			}));
		});
	});
}

void Arena::CreateArena()
{
	background_.setSize(Game::sizeF());
	background_.setFillColor(sf::Color(213,194,165));
	
	textBox_.setSize(sf::Vector2f{950,170});
	textBox_.setPosition(175,460);
	textBox_.setOutlineColor(sf::Color::Black);
	textBox_.setOutlineThickness(3);

	CreateWellnessBars();
	CreateExitButton();
	CreateMoveButtons();
	MakePlayerAvatar();
	MakeDispAttributes();
	UpdateInformationDisplay();
	MakeNameTags();
}

void Arena::CreateExitButton() {
	exitButton_ = std::make_unique<Button>(sf::Vector2f{1240,740}, sf::Vector2f{50,50});

	exitButton_->rectShape().setFillColor(sf::Color::Red);
	exitButton_->rectShape().setOutlineColor(sf::Color{139,0,0});
	exitButton_->rectShape().setOutlineThickness(5);

	exitButton_->text().setCharacterSize(90);
	exitButton_->text().setString("x");
	exitButton_->text().setPosition(sf::Vector2f{1243,697});

	exitButton_->SetPointerEnterAction([this]()
	{
		exitButton_->rectShape().setOutlineThickness(7);
		exitButton_->rectShape().setOutlineColor(sf::Color::Black);
		exitButton_->text().setOutlineThickness(2);
	});

	exitButton_->SetPointerExitAction([this]()
	{
		exitButton_->rectShape().setOutlineThickness(5);
		exitButton_->rectShape().setOutlineColor(sf::Color{139,0,0});
		exitButton_->text().setOutlineThickness(0);
	});

	exitButton_->SetClickAction([this]()
	{
		if (player_.wellness().health > 0 && player_.wellness().sanity > 0)
			Save();
		
		game_.SwapScene(Scenes::MainMenu);
		Jukebox::get().exit.play();
	});

	AddChild(exitButton_.get());
}

void Arena::CreateWellnessBars() 
{
	wellnessBars_[0].setPosition(15,280);
	wellnessBars_[0].setFillColor(sf::Color::Red);
	
	wellnessBars_[2].setPosition(15,320);
	wellnessBars_[2].setFillColor(sf::Color::Blue);
	wellnessBars_[4].setPosition(1085,280);
	wellnessBars_[4].setFillColor(sf::Color::Red);
	wellnessBars_[6].setPosition(1085,320);
	wellnessBars_[6].setFillColor(sf::Color::Blue);
	
	
	for (int i = 0; i < 8; i++)
	{
		wellnessBars_[i].setSize(FULL_WELLNESS_BAR_SIZE);
		
		if (i % 2 != 0)
		{
			wellnessBars_[i].setOutlineThickness(4);
			wellnessBars_[i].setOutlineColor(sf::Color::Yellow);
			wellnessBars_[i].setFillColor(sf::Color::Transparent);
			wellnessBars_[i].setPosition(wellnessBars_[i-1].getPosition());
		}
	}
}

void Arena::CreateMoveButtons()
{
	for (int i = 0; i < 4; i++) {
		moveButtons_[i] = std::make_unique<Button>(sf::Vector2f{(float)(i * 250) + 175, 650}, sf::Vector2f{200, 100});
		
		moveButtons_[i]->rectShape().setOutlineThickness(4);
		moveButtons_[i]->rectShape().setOutlineColor(sf::Color::Black);
		
		moveButtons_[i]->text().setCharacterSize(30);
		moveButtons_[i]->text().setOutlineThickness(3);
		moveButtons_[i]->text().setOutlineColor(sf::Color::Black);
		
		moveButtons_[i]->SetPointerEnterAction([this, i]()
		{
			moveButtons_[i]->rectShape().setOutlineThickness(6);
			moveButtons_[i]->text().setFillColor(sf::Color::Yellow);
		});

		moveButtons_[i]->SetPointerExitAction([this, i]()
		{
			moveButtons_[i]->rectShape().setOutlineThickness(4);
			moveButtons_[i]->text().setFillColor(sf::Color::White);
		});
		
		moveButtons_[i]->SetLockAction([this, i]()
		{
			moveButtons_[i]->rectShape().setFillColor(sf::Color(123,123,123));
			moveButtons_[i]->rectShape().setOutlineThickness(4);
			moveButtons_[i]->text().setFillColor(sf::Color::White);
		});
		
		AddChild(moveButtons_[i].get());
	}
	
	//Attack
	moveButtons_[0]->text().setString("Attack");
	moveButtons_[0]->text().setPosition(227,680);
	moveButtons_[0]->rectShape().setFillColor(sf::Color::Red);

	moveButtons_[0]->SetUnlockAction([this]() {
		moveButtons_[0]->rectShape().setFillColor(sf::Color::Red);
	});
	
	moveButtons_[0]->SetClickAction([this]()
	{
		LockMoveButtons(true);
		attackSound_.play();
		
		TweenManager::AddTween(
			new SpritePosTween(playerAvatar_.get(), ConstantManager::Get(player_.avatar(), Orientation::Left_Attack)
							   , ConstantManager::Get(player_.avatar(), TypeDuration::Attack)))
		->SetEndAction([this] ()
		{
			TweenManager::AddTween(new SpritePosTween(playerAvatar_.get(), ConstantManager::Get(player_.avatar(), Orientation::Left_Mirrored)
								, ConstantManager::Get(player_.avatar(), TypeDuration::Attack)))
			->SetEndAction([this]()
			{
				player_.Attack(opponent_);
				EndPlayerTurn();
			});
		});
	});


	//Prepare
	moveButtons_[1]->text().setString("Prepare");
	moveButtons_[1]->text().setPosition(465,680);
	moveButtons_[1]->rectShape().setFillColor(sf::Color::Blue);

	moveButtons_[1]->SetUnlockAction([this]() {
		moveButtons_[1]->rectShape().setFillColor(sf::Color::Blue);
	});

	moveButtons_[1]->SetClickAction([this](){
		LockMoveButtons(true);

		prepAndRecoverSound_.play();

		preparationEffect_->SetPosition(ConstantManager::Get(Avatar::Illidan, Orientation::Left));
		AddChild(preparationEffect_.get());
		player_.Prepare();

		TimerManager::AddTimer(Timer(sf::seconds(3), [this](){
			RemoveChild(preparationEffect_.get());
			EndPlayerTurn();
		}));
	});

	//Recover
	moveButtons_[2]->text().setString("Recover");
	moveButtons_[2]->text().setPosition(715,680);
	moveButtons_[2]->rectShape().setFillColor(sf::Color::Green);

	moveButtons_[2]->SetUnlockAction([this]() {
		moveButtons_[2]->rectShape().setFillColor(sf::Color::Green);
	});
	
	moveButtons_[2]->SetClickAction([this](){
		LockMoveButtons(true);

		prepAndRecoverSound_.play();
		restorationEffect_->SetPosition(ConstantManager::Get(Avatar::Illidan, Orientation::Left));
		AddChild(restorationEffect_.get());
		
		TimerManager::AddTimer(Timer(sf::seconds(3), [this](){
			RemoveChild(restorationEffect_.get());
			player_.Recover();
			EndPlayerTurn();
		}));
	});

	//CastMagic
	moveButtons_[3]->text().setString("Cast Magic");
	moveButtons_[3]->text().setPosition(950,680);
	moveButtons_[3]->rectShape().setFillColor(sf::Color::Magenta);

	moveButtons_[3]->SetUnlockAction([this]() {
		moveButtons_[3]->rectShape().setFillColor(sf::Color::Magenta);
	});

	moveButtons_[3]->SetClickAction([this](){
		LockMoveButtons(true);

		sf::Vector2f pos = ConstantManager::Get(Avatar::Arthas, Orientation::Right);
		pos.y -= 80;
		pos.x -= 50;
		magicEffect_->SetPosition(pos);
		opponentAvatar_->AddChild(magicEffect_.get());
		
		magicSound_.play();

		TimerManager::AddTimer(Timer(sf::seconds(1), [this](){
			opponentAvatar_->RemoveChild(magicEffect_.get());
			player_.CastMagic(opponent_);
			EndPlayerTurn();
		}));
	});
	
	if (opponent_.attributes().agility > player_.attributes().agility) {
		playerTurn_ = false;
		for (std::unique_ptr<Button>& button: moveButtons_)
			button->Lock(true);

		TimerManager::AddTimer(Timer(sf::seconds(2), [this]()
		{
			GenerateOpponentTurn();
		}));
	}
	else playerTurn_ = true;
}

void Arena::Render(sf::RenderWindow& window)
{
	window.draw(background_);
	window.draw(textBox_);
	
	for (sf::RectangleShape& wellnessBar : wellnessBars_)window.draw(wellnessBar);
	for (sf::RectangleShape& rect : attribRects_) window.draw(rect);
	for (sf::Text& playerAttrib : dispAttributes_)window.draw(playerAttrib);
	for (sf::RectangleShape& rect : nameBoxes_) window.draw(rect);
	for (sf::Text& name : nameTexts_) window.draw(name);
	
	GameObject::Render(window);
}

void Arena::EndOpponentTurn()
{
	playerTurn_ = true;
	UpdateWellnessBars([this]()
	{
		if (player_.wellness().health <= 0 || player_.wellness().sanity <= 0)
		{
			Defeat();			
		}
		else LockMoveButtons(false);
	});
}

void Arena::Defeat()
{
	defeatSound_.play();
	LockMoveButtons(true);
	
	Score score {player_.name(), (int) player_.damageDone(), (int) enemiesSlain_};
	
	ScoreLoader::StoreScore(player_.name(), score);
	ScoreLoader::SaveScores();
	
	TimerManager::AddTimer(Timer(sf::seconds(1), [this, score] ()
	{
		gameOverScreen_ = std::make_unique<GameOverScreen>(score);
		AddChild(gameOverScreen_.get());
	}));
}

void Arena::LockMoveButtons(const bool& lock)
{
	for (auto & moveButton : moveButtons_)
		moveButton->Lock(lock);
}


void Arena::EndPlayerTurn() {
	playerTurn_ = false;
	
	UpdateWellnessBars([this] () {
		if (opponent_.wellness().health <= 0 || opponent_.wellness().sanity <= 0)
		{
			opponent_.Kill();
			victorySound_.play();
			enemiesSlain_++;
		}
		else GenerateOpponentTurn();
	});
}

void Arena::Save() {
	SaveLoader::Save(player_, opponent_, difficulty_, enemiesSlain_, playerTurn_);
}

void Arena::MakePlayerAvatar() 
{
	switch (player_.avatar())
	{
		default:
			throw std::invalid_argument("Player avatar has to be something!");
			break;
			
		case Avatar::Illidan:
			playerAvatar_ = std::make_unique<AnimationSprite>(sf::Vector2f{220,70},"characters/illidan.png", 4, 4, 1);
			playerAvatar_->MirrorVert(true);
			break;
			
		case Avatar::Arthas:
			playerAvatar_ = std::make_unique<AnimationSprite>(sf::Vector2f{300,180},"characters/arthas.png", 8, 8, 1);
			playerAvatar_->MirrorVert(true);
			break;
			
		case Avatar::Kaelthas:
			playerAvatar_ = std::make_unique<AnimationSprite>(sf::Vector2f{270,20},"characters/kaelthas.png", 4, 4, 1);
			playerAvatar_->SetScale(0.6f,0.6f);
			playerAvatar_->MirrorVert(true);
			break;
	}
	AddChild(playerAvatar_.get());
}

void Arena::MakeOpponentAvatar() 
{
	switch (opponent_.avatar())
	{
		default:
			throw std::invalid_argument("Opponent avatar has to be something!");
			break;

		case Avatar::Illidan:
			opponentAvatar_ = std::make_unique<AnimationSprite>(sf::Vector2f{695,70},"characters/illidan.png", 4, 4, 1);
			break;

		case Avatar::Arthas:
			opponentAvatar_ = std::make_unique<AnimationSprite>(sf::Vector2f{740,180},"characters/arthas.png", 8, 8, 1);
			break;

		case Avatar::Kaelthas:
			opponentAvatar_ = std::make_unique<AnimationSprite>(sf::Vector2f{730,20},"characters/kaelthas.png", 4, 4, 1);
			opponentAvatar_->SetScale(0.6f,0.6f);
			break;
	}
	AddChild(opponentAvatar_.get());
}

void Arena::GenerateNewOpponent() 
{
	std::string name;
	
	while (name == player_.name()) name = Character::GetRandomName();
	
	opponent_.Init(name, Avatar(2), Attributes(difficulty_ == Difficulty::Normal? 6 : 7));
	
	MakeOpponentAvatar();
}

void Arena::MakeDispAttributes() {
	
	for (int i = 0; i < 2; i++)
	{
		attribRects_[i].setPosition( (float) ((1070 * i) + 5), 100);
		attribRects_[i].setOutlineThickness(2);
		attribRects_[i].setOutlineColor(sf::Color::Black);
		attribRects_[i].setFillColor(sf::Color::White);
		attribRects_[i].setSize({220,150});
	}
	
	
	for (sf::Text& text : dispAttributes_)
	{
		text.setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
		text.setCharacterSize(30);
	}
	
	for (int i = 0; i < 4; i++) dispAttributes_[i].setFillColor(sf::Color::Green);
	for (int i = 4; i < 8; i++) dispAttributes_[i].setFillColor(sf::Color::Blue);
	for (int i = 8; i < 12; i++) dispAttributes_[i].setFillColor(sf::Color::Red);
	
	
	//Agility P
	dispAttributes_[0].setString("Agility:");
	dispAttributes_[0].setPosition({10,100});
	dispAttributes_[1].setPosition({200,100});
	
	//Agility O
	dispAttributes_[2].setString("Agility:");
	dispAttributes_[2].setPosition({1100,100});
	dispAttributes_[3].setPosition({1270,100});

	//Wits P
	dispAttributes_[4].setString("Wits:");
	dispAttributes_[4].setPosition({10,150});
	dispAttributes_[5].setPosition({200,150});

	//Wits O
	dispAttributes_[6].setString("Wits:");
	dispAttributes_[6].setPosition({1100,150});
	dispAttributes_[7].setPosition({1270,150});


	//Strength P
	dispAttributes_[8].setString("Strength:");
	dispAttributes_[8].setPosition({10,200});
	dispAttributes_[9].setPosition({200,200});


	//Strength O
	dispAttributes_[10].setString("Strength:");
	dispAttributes_[10].setPosition({1100,200});
	dispAttributes_[11].setPosition({1270,200});
}

void Arena::UpdateInformationDisplay()
{
	dispAttributes_[1].setString(std::to_string(player_.attributes().agility));
	dispAttributes_[3].setString(std::to_string(opponent_.attributes().agility));
	dispAttributes_[5].setString(std::to_string(player_.attributes().wits));
	dispAttributes_[7].setString(std::to_string(opponent_.attributes().wits));
	dispAttributes_[9].setString(std::to_string(player_.attributes().strength));
	dispAttributes_[11].setString(std::to_string(opponent_.attributes().strength));
	
	nameTexts_[1].setString(opponent_.name());
	wellnessBars_[4].setSize(FULL_WELLNESS_BAR_SIZE); 
	wellnessBars_[6].setSize(FULL_WELLNESS_BAR_SIZE); 
}

void Arena::MakeNameTags() 
{
	for (int i = 0; i < 2; i ++)
	{
		nameBoxes_[i].setPosition({5 + (float)(i * 990), 20});
		nameBoxes_[i].setSize({300,60});
		nameBoxes_[i].setFillColor(sf::Color::White);
		nameBoxes_[i].setOutlineThickness(3);
		nameBoxes_[i].setOutlineColor(sf::Color::Black);
	}
	
	nameTexts_[0].setString(player_.name());
	nameTexts_[1].setString(opponent_.name());
	
	for (int i = 0; i < 2; i ++)
	{
		nameTexts_[i].setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
		nameTexts_[i].setPosition({10 + (float)(i * 990), 25});
		nameTexts_[i].setCharacterSize(35);
		nameTexts_[i].setFillColor(sf::Color::Black);
	}
}


void Arena::GenerateOpponentTurn()
{

	std::function<void()> Attack = [this] ()
	{
		attackSound_.play();
		
		TweenManager::AddTween(new SpritePosTween(opponentAvatar_.get(), ConstantManager::Get(opponent_.avatar(), Orientation::Right_Attack)
								, ConstantManager::Get(opponent_.avatar(), TypeDuration::Attack)))
			->SetEndAction([this] ()
			{
				TweenManager::AddTween(new SpritePosTween(opponentAvatar_.get(),ConstantManager::Get(opponent_.avatar(), Orientation::Right)
								, ConstantManager::Get(opponent_.avatar(), TypeDuration::Attack)))
					->SetEndAction([this]()
					{
						opponent_.Attack(player_);
						EndOpponentTurn();
					});
			});
	};
	
	std::function<void()> Prepare = [this] ()
	{
		prepAndRecoverSound_.play();

		preparationEffect_->SetPosition(ConstantManager::Get(Avatar::Illidan, Orientation::Right));
		AddChild(preparationEffect_.get());
		opponent_.Prepare();

		TimerManager::AddTimer(Timer(sf::seconds(3), [this](){
			RemoveChild(preparationEffect_.get());
			EndOpponentTurn();
		}));
	};
	
	std::function<void()> Recover = [this] ()
	{
		prepAndRecoverSound_.play();
		
		restorationEffect_->SetPosition(ConstantManager::Get(Avatar::Illidan, Orientation::Right));
		AddChild(restorationEffect_.get());

		TimerManager::AddTimer(Timer(sf::seconds(3), [this](){
			RemoveChild(restorationEffect_.get());
			opponent_.Recover();
			EndOpponentTurn();
		}));
	};
	
	std::function<void()> CastMagic = [this] ()
	{
		sf::Vector2f pos = ConstantManager::Get(Avatar::Arthas, Orientation::Left);
		pos.y -= 80;
		pos.x -= 50;
		magicEffect_->SetPosition(pos);
		playerAvatar_->AddChild(magicEffect_.get());

		magicSound_.play();

		TimerManager::AddTimer(Timer(sf::seconds(1), [this](){
			playerAvatar_->RemoveChild(magicEffect_.get());
			opponent_.CastMagic(player_);
			EndOpponentTurn();
		}));
	};

	std::function<void()> Tremble = [this] ()
	{
		trembleSound_.play();
		opponent_.Tremble();
		
		
		TimerManager::AddTimer(Timer(sf::seconds(1), [this] ()
		{
			EndOpponentTurn();
		}));
	};
	
	TimerManager::AddTimer(Timer(sf::seconds(1), [this, Attack, Recover, Prepare, CastMagic, Tremble]()
	{
		int n = effolkronium::random_static::get(1,100);

		switch (difficulty_)
		{
			case Difficulty::Normal:
				if (n <= 35) Attack();
				else if (n <= 60) Prepare();
				else if (n <= 70) Recover();
				else if (n <= 90) CastMagic();
				else if (n <= 100) Tremble();
				break;

			case Difficulty::Hard:
				if (n <= 35) Attack();
				else if (n <= 60) Prepare();
				else if (n <= 74) Recover();
				else if (n <= 97) CastMagic();
				else if (n <= 100) Tremble();
				break;
		}
	}));
}

void Arena::DecideTurn()
{
	if (opponent_.attributes().agility > player_.attributes().agility)
	{
		for (std::unique_ptr<Button>& button: moveButtons_) button->Lock(true);
		playerTurn_ = false;
		GenerateOpponentTurn();
	}
	else {
		for (std::unique_ptr<Button>& button: moveButtons_)
			button->Lock(false);
		
		playerTurn_ = true;
	}
}

void Arena::UpdateWellnessBars(const std::function<void()>& function)
{
	opponentHealthDone_ = true;
	opponentSanityDone_ = true;
	playerHealthDone_ = true;
	playerSanityDone_ = true;
	
	if (!opponent_.wellness().FullHealth())
	{
		int correctWidth = (int)((FULL_WELLNESS_BAR_SIZE.x / (float) opponent_.wellness().maxHealth) * (float) opponent_.wellness().health);

		if ((int) wellnessBars_[4].getSize().x != correctWidth)
		{
			opponentHealthDone_ = false;
			TweenManager::AddTween(
					new RectangleShapeSizeTween(wellnessBars_[4], sf::Vector2f{(float) correctWidth, FULL_WELLNESS_BAR_SIZE.y}, sf::seconds(3)))
					->SetEndAction([this, function]() {
						opponentHealthDone_ = true;
						if (opponentSanityDone_ && playerHealthDone_ && playerSanityDone_) function();
					});
		}			
	}
	
	if (!opponent_.wellness().FullSanity())
	{
		int correctWidth = (int) ((FULL_WELLNESS_BAR_SIZE.x / (float) opponent_.wellness().maxSanity) * (float) opponent_.wellness().sanity);

		if ((int) wellnessBars_[6].getSize().x != correctWidth) {
			opponentSanityDone_ = false;
			TweenManager::AddTween(
					new RectangleShapeSizeTween(wellnessBars_[6], sf::Vector2f{(float) correctWidth, FULL_WELLNESS_BAR_SIZE.y}, sf::seconds(3)))
					->SetEndAction([this, function]()
					{
						opponentSanityDone_ = true;
						if (opponentHealthDone_ && playerHealthDone_ && playerSanityDone_) function();
					});
		}
	}

	if (!player_.wellness().FullHealth())
	{
		int correctWidth = (int)((FULL_WELLNESS_BAR_SIZE.x / (float) player_.wellness().maxHealth) * (float) player_.wellness().health);

		if ((int) wellnessBars_[0].getSize().x != correctWidth)
		{
			playerHealthDone_ = false;
			TweenManager::AddTween(
					new RectangleShapeSizeTween(wellnessBars_[0], sf::Vector2f{(float)correctWidth, FULL_WELLNESS_BAR_SIZE.y}, sf::seconds(3)))
					->SetEndAction([this,function] () {
						playerHealthDone_ = true;
						if (opponentHealthDone_ && opponentSanityDone_ && playerSanityDone_) function();
					});
		}
	}

	if (!player_.wellness().FullSanity())
	{
		int correctWidth = (int) (FULL_WELLNESS_BAR_SIZE.x / (float) player_.wellness().maxSanity * (float) player_.wellness().sanity);

		if ((int) wellnessBars_[2].getSize().x != correctWidth) {
			playerSanityDone_ = false;
			TweenManager::AddTween(
					new RectangleShapeSizeTween(wellnessBars_[2], sf::Vector2f{(float) correctWidth, FULL_WELLNESS_BAR_SIZE.y}, sf::seconds(3)))
					->SetEndAction([this, function]() {
						playerSanityDone_ = true;
						if (opponentHealthDone_ && opponentSanityDone_ && playerHealthDone_) function();
					});
		}
	}

	if (opponentHealthDone_ && opponentSanityDone_ && playerHealthDone_ && playerSanityDone_) function();
}