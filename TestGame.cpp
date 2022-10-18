#include "TestGame.hpp"
#include "TestSprite.hpp"

void TestGame::Start() {
	auto* testSprite = new TestSprite(sf::Vector2f(5,5));
	auto* test2 = new SFMLPE::Sprite("head.png", sf::Vector2f(0,0));
	
	testSprite->AddChild(test2);
	
	AddScene("test").AddChild(testSprite);
	
	eventHandler.Subscribe(sf::Event::EventType::KeyPressed, [=](sf::Event event) {
		{
			sf::Vector2f testSpriteMovement{0, 0};

			if (event.key.code == sf::Keyboard::A) {
				testSpriteMovement.x = -speed;
			} else if (event.key.code == sf::Keyboard::D) {
				testSpriteMovement.x = speed;
			} else if (event.key.code == sf::Keyboard::W) {
				testSpriteMovement.y = -speed;
			} else if (event.key.code == sf::Keyboard::S) {
				testSpriteMovement.y = speed;
			}

			testSprite->Move(testSpriteMovement);
		}

		{
			sf::Vector2f test2Movement{0,0};

			if (event.key.code == sf::Keyboard::Left){
				test2Movement.x = -speed;
			}
			else if (event.key.code == sf::Keyboard::Right){
				test2Movement.x = speed;
			}
			else if (event.key.code == sf::Keyboard::Up){
				test2Movement.y = -speed;
			}
			else if (event.key.code == sf::Keyboard::Down){
				test2Movement.y = speed;
			}
			
			test2->Move(test2Movement);
		}
		
		
		if (event.key.code == sf::Keyboard::V)
		{
			testSprite->Visible(!testSprite->Visible());
		}
		else if (event.key.code == sf::Keyboard::B)
		{
			test2 -> Visible(!test2->Visible());
		}
	});
	
	
	testSprite->SetPosition(100,0);

}


void TestGame::Update() {
}

