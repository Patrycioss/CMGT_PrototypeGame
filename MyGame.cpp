#include "SFMLPE/Core/Game/MyGame.hpp"

namespace SFMLPE
{
//	class Test
//	{
//	private:
//		Vector2 position_;
//		float speed_;
//		Sprite sprite;
//		EventHandler eventHandler;
//		
//	public:
//		void MoveX(float x)
//		{
//			position_.x += x;
//			sprite.Move(x);
//		}
//		
//		void MoveY(float y)
//		{
//			position_.y += y;
//			sprite.MoveY(y);
//		}
//		
//		void Move(const sf::Vector2f& movement)
//		{
//			position_.x += movement.x;
//			position_.y += movement.y;
//			sprite.Move(movement);
//		}
//		
//		void Move(const float& x, const float& y)
//		{
//			position_.x += x;
//			position_.y += y;
//			sprite.Move(x,y);
//		}
//		
//		explicit Test(const sf::Vector2f& position, const float& speed)
//			: sprite("test.png", position, true)
//			, position_(position), speed_(speed)
//		{
//			eventHandler.Subscribe(sf::Event::EventType::KeyPressed, [&](sf::Event event)
//			{
//				sf::Keyboard::Key& key = event.key.code;
//
//				if (key == sf::Keyboard::W) MoveY(-speed_);
//				if (key == sf::Keyboard::S) MoveY(speed_);
//				if (key == sf::Keyboard::A) MoveX(-speed_);
//				if (key == sf::Keyboard::D) MoveX(speed_);
//			});
//		};
//  };



  //Code in here runs right after the window's creation before the main loop
  void MyGame::Start()
  {
//		Test* test = new Test(sf::Vector2f{0,0}, 5);
  }

//Code in here runs every cycle
  void MyGame::Update()
  {

  }
}