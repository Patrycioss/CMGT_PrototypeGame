#include "CMGT_PrototypeGame.hpp"
#include "Utility/InputHelper.hpp"

void CMGT_PrototypeGame::Start()
{
	
	testSprite = new TestSprite(sf::Vector2f(0,0));
	
	animationTest = new AnimationTest(sf::Vector2f(0,0));



	main_menu.AddChild(testSprite);
	
	
	testSprite->AddChild(animationTest);

	AddScene(main_menu.name(),&main_menu);


//	testSprite->MirrorVert(true);

//	
//	printf("%f", testSprite->size().x);
//	printf("\n%f", testSprite->position().x);
//	printf("\n%f", testSprite->GetSFMLSprite().getScale().x);
//	
//	printf("\n%f", testSprite->GetSFMLSprite().getScale().x);


	
	
	eventHandler.Subscribe(sf::Event::KeyPressed, [=](sf::Event event)
	{
		if (event.key.code == sf::Keyboard::V)
		{
			animationTest->Visible(!animationTest->Visible());
		}
		else if (event.key.code == sf::Keyboard::M)
		{
			animationTest->MirrorVert(!animationTest->vertMirrored());
		}
		else if (event.key.code == sf::Keyboard::C)
		{
			testSprite->MirrorVert(!testSprite->vertMirrored());
		}
		
	});
	
	printf("SceneLocal = %f, SpriteLocal = %f, AnimationLocal = %f \n",main_menu.parentSpaceX(), testSprite->parentSpaceX(), animationTest->parentSpaceX());
}

void CMGT_PrototypeGame::Update() 
{
//	printf("Animationtest is at x: %f \n", animationTest->position().x);
//	printf("Main has ID: %u, Animation has ID: %u, Sprite has ID: %u \n", main_menu.ID(), testSprite->ID(), animationTest->ID() );

//	printf("SceneLocal = %f, SpriteLocal = %f, AnimationLocal = %f \n",main_menu.localX(), testSprite->localX(), animationTest->localX());


	animationTest->Animate();
	testSprite->Move(InputHelper::get_arrowKeys_direction());
	animationTest->Move(InputHelper::get_wasd_direction());
}

void CMGT_PrototypeGame::End() 
{
	delete testSprite;
	delete animationTest;
}   




