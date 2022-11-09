#include "Selection.hpp"
#include "../CMGT_PrototypeGame.hpp"
#include "effolkronium/random.hpp"
#include "../Audio/Jukebox.hpp"
#include "../Engine/ResourceManager.hpp"

Selection::Selection(CMGT_PrototypeGame& game) 
	: Scene("Selection")
	, game_(game)
	, choices_{std::make_unique<AnimationSprite>(sf::Vector2f {130,170}, "characters/illidan.png", 4, 4, 1)
			   ,std::make_unique<AnimationSprite>(sf::Vector2f {550,100}, "characters/arthas.png", 8, 8, 1)
			   ,std::make_unique<AnimationSprite>(sf::Vector2f {900,150}, "characters/kaelthas.png", 4, 4, 1)}
	
	, choiceButtons_{std::make_unique<Button>(sf::Vector2f {130,100}, sf::Vector2f{370,500})
				,std::make_unique<Button>(sf::Vector2f {560,100}, sf::Vector2f{250,270})
				,std::make_unique<Button>(sf::Vector2f {870,100}, sf::Vector2f{370,500})} 
{
	background_.setPosition(sf::Vector2f {0,0});
	background_.setFillColor(sf::Color::Yellow);
	background_.setSize(Game::sizeF());
	
	
//	eventHandler.Subscribe(sf::Event::KeyPressed, [this] (const sf::Event& event)
//	{
//		if (event.key.code == sf::Keyboard::G) 
//			choiceButtons_[0]->SetScale(0.5f,0.5f);
//		
//		else if (event.key.code == sf::Keyboard::N)
//			choiceButtons_[0]->SetScale(1,1);
//	});
//	
	MakeAvatarSelection();
	MakeNameCreation();
	MakePointDistributionStuff();
	MakeDifficultySelection();
	MakeStartButton();
	CreateExitButton();
}

void Selection::MakeStartButton() {
	startButton_ = std::make_unique<Button>(sf::Vector2f{587,660}, sf::Vector2f{200,100});
	startButton_->rectShape().setFillColor(sf::Color::Cyan);
	startButton_->rectShape().setOutlineThickness(4);
	startButton_->rectShape().setOutlineColor(sf::Color::Black);
	
	startButton_->text().setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
	startButton_->text().setOutlineThickness(4);
	startButton_->text().setOutlineColor(sf::Color::Black);
	startButton_->text().setCharacterSize(40);
	startButton_->text().setPosition(sf::Vector2f{635, 690});
	
	startButton_->text().setString("Start");
	
	startButton_->SetPointerEnterAction([this]()
	{
		startButton_->rectShape().setFillColor(sf::Color::Magenta);
		startButton_->text().setFillColor(sf::Color::Yellow);
	});
	
	startButton_->SetPointerExitAction([this]()
	{
		startButton_->rectShape().setFillColor(sf::Color::Cyan);
		startButton_->text().setFillColor(sf::Color::White);
	});
	
	startButton_->SetClickAction([this]()
	{
		StartGame();
	});

	AddChild(startButton_.get());
}

void Selection::MakeDifficultySelection() 
{
	difficultyButtons_[0] = std::make_unique<Button>(sf::Vector2f{850,650}, sf::Vector2f{200,75});
	difficultyButtons_[0]->text().setString("Normal");
	difficultyButtons_[0]->text().setPosition(sf::Vector2f{887, 662});
	
	difficultyButtons_[0]->rectShape().setFillColor(sf::Color::Magenta);
	
	difficultyButtons_[0]->SetPointerEnterAction([this]
	{
		difficultyButtons_[0]->rectShape().setOutlineColor(sf::Color::Blue);
		difficultyButtons_[0]->text().setOutlineColor(sf::Color::Blue);
	});

	difficultyButtons_[0]->SetPointerExitAction([this]
	{
		difficultyButtons_[0]->rectShape().setOutlineColor(sf::Color::Black);
		difficultyButtons_[0]->text().setOutlineColor(sf::Color::Transparent);
	});

	difficultyButtons_[0]->SetClickAction([this]()
	{
		difficultyButtons_[1]->rectShape().setOutlineThickness(3);
		difficultyButtons_[0]->rectShape().setOutlineThickness(5);
		difficulty_ = Difficulty::Normal;
	});
	
	
	difficultyButtons_[1] = std::make_unique<Button>(sf::Vector2f{1060,650}, sf::Vector2f{200,75});
	difficultyButtons_[1]->text().setString("Hard");
	difficultyButtons_[1]->text().setPosition(sf::Vector2f{1113,662});

	difficultyButtons_[1]->rectShape().setFillColor(sf::Color::Red);

	difficultyButtons_[1]->SetPointerEnterAction([this]
	{
		difficultyButtons_[1]->rectShape().setOutlineColor(sf::Color::Blue);
		difficultyButtons_[1]->text().setOutlineColor(sf::Color::Blue);
	});

	difficultyButtons_[1]->SetPointerExitAction([this]
	{
		difficultyButtons_[1]->rectShape().setOutlineColor(sf::Color::Black);
		difficultyButtons_[1]->text().setOutlineColor(sf::Color::Transparent);
	});

	difficultyButtons_[1]->SetClickAction([this]()
	{
		difficultyButtons_[0]->rectShape().setOutlineThickness(3);
		difficultyButtons_[1]->rectShape().setOutlineThickness(5);
		difficulty_ = Difficulty::Hard;
	});

	for (std::unique_ptr<Button>& button : difficultyButtons_)
	{
		button->text().setOutlineThickness(4);
		button->text().setOutlineColor(sf::Color::Transparent);
		button->text().setFillColor(sf::Color::White);
		button->text().setCharacterSize(40);
		button->text().setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
		
		button->rectShape().setOutlineThickness(3);
		button->rectShape().setOutlineColor(sf::Color::Black);
		
		AddChild(button.get());
	}

	difficultyButtons_[0]->rectShape().setOutlineThickness(5);
	difficultyButtons_[0]->rectShape().setOutlineColor(sf::Color::Black);
}

void Selection::UpdatePoints() {
	stats_[1].setString(std::to_string(chosenAttributes_.agility));
	stats_[3].setString(std::to_string(chosenAttributes_.wits));
	stats_[5].setString(std::to_string(chosenAttributes_.strength));

	pointsToSpend_ = 8 - chosenAttributes_.agility - chosenAttributes_.wits - chosenAttributes_.strength;
	pointsToSpendText_[1].setString(std::to_string(pointsToSpend_));

	if (pointsToSpend_ == 0) pointsToSpendText_[1].setFillColor(sf::Color::Red);
	else pointsToSpendText_[1].setFillColor(sf::Color::Green);
	
}

void Selection::MakePointDistributionStuff() 
{
	for (sf::Text& text : stats_)
	{
		text.setStyle(sf::Text::Style::Italic);
		text.setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
		text.setCharacterSize(30);
	}
	
	stats_[0].setString("Agility:");
	stats_[0].setFillColor(sf::Color::Green);
	stats_[0].setPosition(100,650);
	
	stats_[1].setString("0");
	stats_[1].setFillColor(sf::Color::Green);
	stats_[1].setPosition(200,650);

	stats_[2].setString("Wits:");
	stats_[2].setFillColor(sf::Color::Blue);
	stats_[2].setPosition(260,650);

	stats_[3].setString("1");
	stats_[3].setFillColor(sf::Color::Blue);
	stats_[3].setPosition(325,650);

	stats_[4].setString("Strength:");
	stats_[4].setFillColor(sf::Color::Red);
	stats_[4].setPosition(370,650);

	stats_[5].setString("1");
	stats_[5].setFillColor(sf::Color::Red);
	stats_[5].setPosition(510,650);

	//Agility
	pointButtons_[0] = std::make_unique<Button>(sf::Vector2f{125,700}, sf::Vector2f{20,20});
	pointButtons_[0]->SetClickAction([this]()
	{
		if (pointsToSpend_ == 0) return;
		pointsToSpend_--;
		chosenAttributes_.agility++;
		UpdatePoints();
	});
	
	pointButtons_[1] = std::make_unique<Button>(sf::Vector2f{175,700}, sf::Vector2f{20,20});
	pointButtons_[1]->SetClickAction([this]()
	{
		if (chosenAttributes_.agility == 0) return;
		pointsToSpend_++;
		chosenAttributes_.agility--;
		UpdatePoints();
	});
	
	//Wits
	pointButtons_[2] = std::make_unique<Button>(sf::Vector2f{260,700}, sf::Vector2f{20,20});
	pointButtons_[2]->SetClickAction([this]()
	{
		if (pointsToSpend_ == 0) return;
		pointsToSpend_--;
		chosenAttributes_.wits++;
		UpdatePoints();
	});

	pointButtons_[3] = std::make_unique<Button>(sf::Vector2f{310,700}, sf::Vector2f{20,20});
	pointButtons_[3]->SetClickAction([this]()
	{
		if (chosenAttributes_.wits == 1) return;
		pointsToSpend_++;
		chosenAttributes_.wits--;
		UpdatePoints();
	});

	//Strength
	pointButtons_[4] = std::make_unique<Button>(sf::Vector2f{400,700}, sf::Vector2f{20,20});
	pointButtons_[4]->SetClickAction([this]()
	{
		if (pointsToSpend_ == 0) return;
		pointsToSpend_--;
		chosenAttributes_.strength++;
		UpdatePoints();
	});
	
	pointButtons_[5] = std::make_unique<Button>(sf::Vector2f{450,700}, sf::Vector2f{20,20});
	pointButtons_[5]->SetClickAction([this]()
	{
		if (chosenAttributes_.strength == 1) return;
		pointsToSpend_++;
		chosenAttributes_.strength--;
		UpdatePoints();
	});


	for (int i = 0; i < 6; i++)
	{
		if (i != 0 && i % 2 != 0){
			pointButtons_[i]->rectShape().setFillColor(sf::Color::Red);
			pointButtons_[i]->text().setString("-");
		}
		else {
			pointButtons_[i]->rectShape().setFillColor(sf::Color::Green);
			pointButtons_[i]->text().setString("+");
		}

		sf::Vector2f pos = pointButtons_[i]->text().getPosition();
		pos.x += 5;
		pos.y -= 3;
		pointButtons_[i]->text().setPosition(pos);
		
		AddChild(pointButtons_[i].get());
	}
	
	for (sf::Text& text : pointsToSpendText_)
	{
		text.setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
		text.setCharacterSize(30);
	}
	
	pointsToSpendText_[0].setString("Points left:");
	pointsToSpendText_[0].setFillColor(sf::Color::Magenta);
	pointsToSpendText_[0].setPosition(200,750);
	
	pointsToSpendText_[1].setString("6");
	pointsToSpendText_[1].setFillColor(sf::Color::Green);
	pointsToSpendText_[1].setPosition(375,750);
	
	randomizer_ = std::make_unique<Button>(sf::Vector2f{0,700}, "dice.png", 5, 5, 1);
	randomizer_->SetScale(0.5f,0.5f);

	randomizer_->animation().SetCycle(1,1,150);
	
	randomizer_->SetPointerEnterAction([this]()
	{
		randomizer_->animation().SetCycle(1,5);
	});

	randomizer_->SetPointerExitAction([this]()
	{
		randomizer_->animation().SetCycle(1,1);
	});
	
	randomizer_->SetClickAction([this]()
	{
		chosenAttributes_ = Character::GetRandomAttributes(chosenAttributes_);
		UpdatePoints();
	});

	AddChild(randomizer_.get());
}

void Selection::Update() {
	
	for (int i = 0; i < 3; i++)
		choices_[i]->Animate();

	if (maxCharactersReached_ && maxCharacterFadeClock_.getElapsedTime().asSeconds() > 1)
		maxCharactersReached_ = false;
	
	GameObject::Update();
}

void Selection::Render(sf::RenderWindow& window) {
	window.draw(background_);
	
	if (maxCharactersReached_) window.draw(maxCharactersWarning_);
	
	window.draw(chooseYourName_);

	for (const sf::Text& text: chooseYourAvatar_) window.draw(text);
	for (const sf::Text& text : stats_) window.draw(text);
	for (const sf::Text& text : pointsToSpendText_) window.draw(text);
	
	GameObject::Render(window);
}

void Selection::SelectAvatar(Button* button, const Avatar& avatar) 
{
	if (selectedAvatarButton_ != nullptr)
	{
		selectedAvatarButton_->rectShape().setOutlineThickness(5);
	}
	
	selectedAvatarButton_ = button;
	button->rectShape().setOutlineThickness(20);
	
	selectedAvatar_ = avatar;
}

void Selection::MakeAvatarSelection() 
{
	for (sf::Text& text : chooseYourAvatar_)
	{
		text.setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
		text.setCharacterSize(50);
		text.setStyle(sf::Text::Style::Italic | sf::Text::Style::Bold);
	}
	
	chooseYourAvatar_[0].setString("Choose");
	chooseYourAvatar_[0].setFillColor(sf::Color::Green);
	chooseYourAvatar_[0].setPosition(225, 0);
	
	chooseYourAvatar_[1].setString("Your");
	chooseYourAvatar_[1].setFillColor(sf::Color::Blue);
	chooseYourAvatar_[1].setPosition(625, 0);
	
	chooseYourAvatar_[2].setString("Character");
	chooseYourAvatar_[2].setFillColor(sf::Color::Red);
	chooseYourAvatar_[2].setPosition(925, 0);
	
	
	
	
///////////////////////////////////////////////////////////////////////////
	//Illidan

	choices_[0]->SetCycle(1,4,120);
	choices_[0]->MirrorVert(true);

	choiceButtons_[0]->rectShape().setFillColor(sf::Color::Green);
	choiceButtons_[0]->rectShape().setOutlineColor(sf::Color(0, 100, 0));
	choiceButtons_[0]->rectShape().setOutlineThickness(10);

	choiceButtons_[0]->SetPointerEnterAction([this]()
	{
		choiceButtons_[0]->rectShape().setFillColor(sf::Color{210, 248, 210});
	});

	choiceButtons_[0]->SetPointerExitAction([this]()
	{
		choiceButtons_[0]->rectShape().setFillColor(sf::Color::Green);
	});

	choiceButtons_[0]->SetClickAction([this]()
	{
		SelectAvatar(choiceButtons_[0].get(), Avatar::Illidan);
	});

	///////////////////////////////////////////////////////////////////////////
	//Arthas

	choices_[1]->SetDelay(130);

	choiceButtons_[1]->rectShape().setFillColor(sf::Color::Blue);
	choiceButtons_[1]->rectShape().setOutlineColor(sf::Color(0, 0, 139));
	choiceButtons_[1]->rectShape().setOutlineThickness(10);

	choiceButtons_[1]->SetPointerEnterAction([this]()
	{
		choiceButtons_[1]->rectShape().setFillColor(sf::Color{173, 216, 230});
	});

	choiceButtons_[1]->SetPointerExitAction([this]()
	{
		choiceButtons_[1]->rectShape().setFillColor(sf::Color::Blue);
	});

	choiceButtons_[1]->SetClickAction([this]()
	{
		SelectAvatar(choiceButtons_[1].get(), Avatar::Arthas);
	});

	///////////////////////////////////////////////////////////////////////////
	//Kaelthas

	choices_[2]->SetScale(0.6f,0.6f);
	choices_[2]->SetCycle(1,4,120);

	choiceButtons_[2]->rectShape().setFillColor(sf::Color::Red);
	choiceButtons_[2]->rectShape().setOutlineColor(sf::Color(100, 0, 0));
	choiceButtons_[2]->rectShape().setOutlineThickness(10);

	choiceButtons_[2]->SetPointerEnterAction([this]()
	{
		choiceButtons_[2]->rectShape().setFillColor(sf::Color{255,204,203});
	});

	choiceButtons_[2]->SetPointerExitAction([this]()
	{
		choiceButtons_[2]->rectShape().setFillColor(sf::Color::Red);
	});

	choiceButtons_[2]->SetClickAction([this]()
	{
		SelectAvatar(choiceButtons_[2].get(), Avatar::Kaelthas);
	});

	///////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < 3; i++)
	{
		AddChild(choiceButtons_[i].get());
		choiceButtons_[i]->AddChild(choices_[i].get());
	}
}

void Selection::MakeNameCreation() {
	
	chooseYourName_.setString("Enter your name!");
	chooseYourName_.setStyle(sf::Text::Style::Bold);
	chooseYourName_.setCharacterSize(25);
	chooseYourName_.setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
	chooseYourName_.setPosition(570, 460);
	chooseYourName_.setFillColor(sf::Color::Blue);
	
	
	nameInput_ = std::make_unique<TextInput>(sf::Vector2f{535,505}, sf::Vector2f{300,100});
	nameInput_->text().setPosition(550, 525);
	nameInput_->characterLimit = 9;

	maxCharactersWarning_.setString("No more characters left!");
	maxCharactersWarning_.setFillColor(sf::Color::Red);
	maxCharactersWarning_.setStyle(sf::Text::Style::Bold);
	maxCharactersWarning_.setPosition(550, 610);
	maxCharactersWarning_.setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
	maxCharactersWarning_.setCharacterSize(20);

	nameInput_->SetMaxCharactersAction([this]()
	{
		maxCharactersReached_ = true;
		maxCharacterFadeClock_.restart();
	});

	AddChild(nameInput_.get());
}

void Selection::StartGame() 
{
	dynamic_cast<Arena*>(game_.SwapScene(Scenes::Arena))
			->Begin(nameInput_->text().getString(), selectedAvatar_, chosenAttributes_, difficulty_);
}

void Selection::CreateExitButton() {
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
		Jukebox::get().exit.play();
		game_.SwapScene(Scenes::MainMenu);
	});

	AddChild(exitButton_.get());
}
