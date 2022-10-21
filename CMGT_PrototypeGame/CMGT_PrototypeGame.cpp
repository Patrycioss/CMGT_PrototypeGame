#include "CMGT_PrototypeGame.hpp"
#include "Utility/InputHelper.hpp"

void CMGT_PrototypeGame::Start()
{
	
	AddScene(scene.name(), &scene);
	
}

void CMGT_PrototypeGame::Update() 
{

}

void CMGT_PrototypeGame::End() 
{
	
}

//eventHandler.Subscribe(sf::Event::KeyPressed, [=](sf::Event event)
//{
//if (event.key.code == sf::Keyboard::V)
//{
//animationTest->Visible(!animationTest->Visible());
//}
//else if (event.key.code == sf::Keyboard::M)
//{
//animationTest->MirrorVert(!animationTest->vertMirrored());
//}
//else if (event.key.code == sf::Keyboard::C)
//{
//testSprite->MirrorHor(!testSprite->horMirrored());
//}
//else if (event.key.code == sf::Keyboard::F)
//{
//testSprite->MirrorVert(!testSprite->vertMirrored());
//}
//else if (event.key.code == sf::Keyboard::B)
//{
//main_menu.MirrorHor(!main_menu.horMirrored());
//}
//else if (event.key.code == sf::Keyboard::G)
//{
//main_menu.Mirror(!main_menu.horMirrored(),!main_menu.vertMirrored());
//}
//else if (event.key.code == sf::Keyboard::Add)
//{
//testSprite->SetScale(0.5f,0.5f);
//}
//else if (event.key.code == sf::Keyboard::Subtract)
//{
//testSprite->SetScale(1,1);
//}
//
//});




