#pragma once
#include "../SFMLPE/SFMLPE.hpp"
#include "../test_example/TestSprite.hpp"
#include "Screens/MainMenu.hpp"
#include "Fighting/Arena.hpp"
#include "Selection.hpp"



enum class Scenes
{
	None,
	MainMenu,
	Selection,
	Arena
};

class CMGT_PrototypeGame : public SFMLPE::Game // NOLINT(cppcoreguidelines-pro-type-member-init)
{
private:
	
	Scenes activeScene_;
	
	std::unique_ptr<MainMenu> mainMenu_;
	std::unique_ptr<Arena> arena_;
	std::unique_ptr<Selection> selection_;
	
	void DeactivateScene(const Scenes& scene);
	void DeleteScene(const Scenes& scene);
	
	Scenes sceneToBeRemoved = Scenes::None;


protected:
	void Start() override;
	void Update() override;
	void End() override;
	
public:
	void SwapScene(const Scenes& scene);
};