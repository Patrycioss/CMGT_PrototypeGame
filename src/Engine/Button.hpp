#pragma once
#include "GameObject.hpp"
#include "AnimationSprite.hpp"

class Button : public GameObject
{
	
private:
	std::unique_ptr<AnimationSprite> animationSprite_;
	
	

	std::function<void()> onClick_;
	std::function<void()> onPointerEnter_;
	std::function<void()> onPointerExit_;
	std::function<void()> onLock_;
	std::function<void()> onUnlock_;
	
	const char* fontPath_ = "fonts/minecraftFont.ttf";
	sf::Text text_;
	sf::RectangleShape rectangleShape_;
	
	bool hovering_ = false;
	bool locked_ = false;
	

public:
	Button(const sf::Vector2f& position,
	       const char* filePath,
	       const unsigned int& numFrames,
	       const unsigned int& cols,
	       const unsigned int& rows,
	       const bool& visible = true);

	Button(const sf::Vector2f& position,
	       const sf::Vector2f& size,
	       const bool& visible = true);
	
	void SetClickAction(const std::function<void()>& action);
	void SetPointerEnterAction(const std::function<void()>& action);
	void SetPointerExitAction(const std::function<void()>& action);
	void SetLockAction(const std::function<void()>& action);
	void SetUnlockAction(const std::function<void()>& action);
	
	bool TriggerClickAction();
	bool TriggerPointerEnterAction();
	bool TriggerPointerExitAction();
	bool TriggerLockAction();
	bool TriggerUnlockAction();
	
	[[nodiscard]] const bool& hovering() const;

	AnimationSprite& animation();

	sf::RectangleShape& rectShape();
	sf::Text& text();

	void Start() override;
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	
	void UpdateScale(const sf::Vector2f &prevScale) override;
	
	
	void Lock(const bool& lock);
	const bool& locked() const;
	
	~Button();
};
