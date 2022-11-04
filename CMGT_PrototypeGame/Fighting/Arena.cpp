#include "Arena.hpp"
#include "../CMGT_PrototypeGame.hpp"
#include "../Tweening/TweenManager.hpp"
#include "../Tweening/RectPosTween.hpp"


Arena::Arena(CMGT_PrototypeGame& game) 
	: SFP::Scene("Arena")
	, game_(game)
	, enemiesSlain_(0)
	, damageDone_(0)
	, difficulty_(Difficulty::Normal)
{
}

void Arena::Begin(const sf::String& name, const Avatar& avatar, const Attributes& attributes, const Difficulty& difficulty) 
{
	difficulty_ = difficulty;
	player_.Init(name,avatar,attributes);

	GenerateNewOpponent();
	CreateArena();
}

void Arena::CreateArena()
{
	background_.setSize(SFP::Game::sizeF());
	background_.setFillColor(sf::Color(213,194,165));
	
	textBox_.setSize(sf::Vector2f{700,170});
	textBox_.setPosition(300,460);
	textBox_.setOutlineColor(sf::Color::Black);
	textBox_.setOutlineThickness(3);

	CreateWellnessBars();
	CreateExitButton();
	CreateMoveButtons();
	MakePlayerAvatar();
	MakeDispAttributes();
	UpdateAttribDisplay();
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
		Save();
		game_.SwapScene(Scenes::MainMenu);
	});

	AddChild(exitButton_.get());
}

void Arena::CreateWellnessBars() 
{
	wellnessBars_[0].setPosition(50,500);
	wellnessBars_[0].setFillColor(sf::Color::Red);
	
	wellnessBars_[2].setPosition(50,540);
	wellnessBars_[2].setFillColor(sf::Color::Blue);
	wellnessBars_[4].setPosition(1050,500);
	wellnessBars_[4].setFillColor(sf::Color::Red);
	wellnessBars_[6].setPosition(1050,540);
	wellnessBars_[6].setFillColor(sf::Color::Blue);
	
	
	for (int i = 0; i < 8; i++)
	{
		wellnessBars_[i].setSize(sf::Vector2f{200,25});
		
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
		});

		AddChild(moveButtons_[i].get());
	}
	
	//Attack
	moveButtons_[0]->text().setString("Attack");
	moveButtons_[0]->text().setPosition(227,680);
	moveButtons_[0]->rectShape().setFillColor(sf::Color::Red);

	moveButtons_[0]->SetUnlockAction([this]()
	{
		moveButtons_[0]->rectShape().setFillColor(sf::Color::Red);
	});
	
	
	//Prepare
	moveButtons_[1]->text().setString("Prepare");
	moveButtons_[1]->text().setPosition(465,680);
	moveButtons_[1]->rectShape().setFillColor(sf::Color::Blue);

	//Recover
	moveButtons_[2]->text().setString("Recover");
	moveButtons_[2]->text().setPosition(715,680);
	moveButtons_[2]->rectShape().setFillColor(sf::Color::Green);

	//CastMagic
	moveButtons_[3]->text().setString("Cast Magic");
	moveButtons_[3]->text().setPosition(950,680);
	moveButtons_[3]->rectShape().setFillColor(sf::Color::Magenta);
}

void Arena::Render(sf::RenderWindow& window)
{
	window.draw(background_);
	window.draw(textBox_);
	
	for (sf::RectangleShape& wellnessBar : wellnessBars_)window.draw(wellnessBar);
	for (sf::RectangleShape& rect : attribRects_) window.draw(rect);
	for (sf::Text& playerAttrib : dispAttributes_)window.draw(playerAttrib);
	
	SFP::GameObject::Render(window);
}

void Arena::EndTurn() {
	for (auto & moveButton : moveButtons_)
		moveButton->Lock(playerTurn_);

	playerTurn_ = !playerTurn_;
}

void Arena::Save() {

}

void Arena::MakePlayerAvatar() 
{
	switch (player_.avatar())
	{
		default:
			throw std::invalid_argument("Player avatar has to be something!");
			break;
			
		case Avatar::Illidan:
			playerAvatar_ = std::make_unique<SFP::AnimationSprite>(sf::Vector2f{220,70},"characters/illidan.png", 4, 4, 1);
			playerAvatar_->MirrorVert(true);
			break;
			
		case Avatar::Arthas:
			playerAvatar_ = std::make_unique<SFP::AnimationSprite>(sf::Vector2f{300,180},"characters/arthas.png", 8, 8, 1);
			playerAvatar_->MirrorVert(true);
			break;
			
		case Avatar::Kaelthas:
			playerAvatar_ = std::make_unique<SFP::AnimationSprite>(sf::Vector2f{270,20},"characters/kaelthas.png", 4, 4, 1);
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
			opponentAvatar_ = std::make_unique<SFP::AnimationSprite>(sf::Vector2f{695,70},"characters/illidan.png", 4, 4, 1);
			break;

		case Avatar::Arthas:
			opponentAvatar_ = std::make_unique<SFP::AnimationSprite>(sf::Vector2f{740,180},"characters/arthas.png", 8, 8, 1);
			break;

		case Avatar::Kaelthas:
			opponentAvatar_ = std::make_unique<SFP::AnimationSprite>(sf::Vector2f{730,20},"characters/kaelthas.png", 4, 4, 1);
			opponentAvatar_->SetScale(0.6f,0.6f);
			break;
	}
	AddChild(opponentAvatar_.get());
}

void Arena::GenerateNewOpponent() 
{
	opponent_.Init("", Avatar(2), Attributes(difficulty_ == Difficulty::Normal? 6 : 7));
	
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
		text.setFont(*SFP::ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
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

void Arena::UpdateAttribDisplay()
{
	dispAttributes_[1].setString(std::to_string(player_.attributes().agility));
	dispAttributes_[3].setString(std::to_string(opponent_.attributes().agility));
	dispAttributes_[5].setString(std::to_string(player_.attributes().wits));
	dispAttributes_[7].setString(std::to_string(opponent_.attributes().wits));
	dispAttributes_[9].setString(std::to_string(player_.attributes().strength));
	dispAttributes_[11].setString(std::to_string(opponent_.attributes().strength));
}








