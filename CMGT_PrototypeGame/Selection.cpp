#include "Selection.hpp"
#include "CMGT_PrototypeGame.hpp"

//TODO: text input for name :D
//https://en.sfml-dev.org/forums/index.php?topic=19965.0

Selection::Selection(CMGT_PrototypeGame& game) 
	: SFMLPE::Scene("Selection")
	, game_(game)
	, choices_{std::make_unique<SFMLPE::AnimationSprite>(sf::Vector2f {150,170},"characters/illidan.png", 4, 4, 1)
			   ,std::make_unique<SFMLPE::AnimationSprite>(sf::Vector2f {550,100},"characters/arthas.png", 8, 8, 1)
			   ,std::make_unique<SFMLPE::AnimationSprite>(sf::Vector2f {880,150},"characters/kaelthas.png", 4, 4, 1)}
	
	, choiceButtons_{std::make_unique<NewButton>(sf::Vector2f {150,100},sf::Vector2f{370,500})
				,std::make_unique<NewButton>(sf::Vector2f {560,100}, sf::Vector2f{250,270})
				,std::make_unique<NewButton>(sf::Vector2f {850,100}, sf::Vector2f{370,500})} 
{
	background_.setPosition(sf::Vector2f {0,0});
	background_.setFillColor(sf::Color::Yellow);
	background_.setSize(SFMLPE::Game::sizeF());


	choices_[0]->SetCycle(1,4,120);
	choices_[0]->MirrorVert(true);
	choiceButtons_[0]->rectShape().setFillColor(sf::Color::Green);

//	choices_[1]->SetScale(0.5f,0.5f);
	choices_[1]->SetDelay(130);
	choiceButtons_[1]->rectShape().setFillColor(sf::Color::Blue);

	choices_[2]->SetScale(0.6f,0.6f);
	choices_[2]->SetCycle(1,4,120);
	choiceButtons_[2]->rectShape().setFillColor(sf::Color::Red);
	
	for (int i = 0; i < 3; i++)
	{
		AddChild(choiceButtons_[i].get());
		choiceButtons_[i]->AddChild(choices_[i].get());
	}
}

void Selection::Update() {
	
	for (int i = 0; i < 3; i++)
		choices_[i]->Animate();
	
	GameObject::Update();
}

void Selection::Render(sf::RenderWindow& window) {
	window.draw(background_);
	
	SFMLPE::GameObject::Render(window);
}   
