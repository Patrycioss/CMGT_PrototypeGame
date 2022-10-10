#include "SFMLPE/Core/Game/MyGame.hpp"

namespace SFMLPE
{
	class Test
	{
	private:
		Vector2 position_;
		float speed_;
		Sprite sprite;
		EventHandler eventHandler;
		
	public:
		void MoveX(float x)
		{
			position_.x += x;
			sprite.
		}
		
		void MoveY(float y)
		{
			position_.y += y;
		}
		
		explicit Test(const Vector2& position, const float& speed)
			: sprite("test.png", position, true), position_(position), speed_(speed)
		{
			eventHandler.Subscribe(sf::Event::EventType::KeyPressed, [&](sf::Event event)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::W:
						MoveY(-speed_);
						break;
					
					case sf::Keyboard::S:
						MoveY(speed_);
						break;
					
					case sf::Keyboard::A:
						MoveX(-speed_);
						break;
					
					case sf::Keyboard::D:
						MoveY(speed_);
						break;
						
					default:
						printf("jawel \n");
						break;
				}
			});
			
			
		};
		
	};
	
	
	
	//Code in here runs right after the window's creation before the main loop
	void MyGame::Start()
	{
		Test* test = new Test(Vector2{0,0}, 5);
	}

//Code in here runs every cycle
	void MyGame::Update()
	{
		
	}
}