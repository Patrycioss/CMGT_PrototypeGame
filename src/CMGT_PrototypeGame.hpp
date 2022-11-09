#pragma once
#include "MainMenu/MainMenu.hpp"
#include "Arena/Arena.hpp"
#include "CharacterSelect/Selection.hpp"
#include "Engine/Game.hpp"

enum class Scenes
{
	None,
	MainMenu,
	Selection,
	Arena
};

class CMGT_PrototypeGame : public Game // NOLINT(cppcoreguidelines-pro-type-member-init)
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
	Scene* SwapScene(const Scenes& scene);
};