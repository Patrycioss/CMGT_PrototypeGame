#pragma once
#include "../SFMLPE/Core/AnimationSprite.hpp"

class NewButton : public SFMLPE::GameObject
{
	
private:
	std::unique_ptr<SFMLPE::AnimationSprite> animationSprite_;

	std::function<void()> onClick_;
	std::function<void()> onPointerEnter_;
	std::function<void()> onPointerExit_;
	
	sf::Text text_;
	sf::RectangleShape rectangleShape_;
	
	
	bool hovering_ = false;
	
	void OnClick();
	

public:
	NewButton(const sf::Vector2f& position,
	          const char* filePath,
	          const unsigned int& numFrames,
	          const unsigned int& cols,
	          const unsigned int& rows,
	          const bool& visible = true);

	NewButton(const sf::Vector2f& position,
			  const sf::Vector2f& size,
	          const bool& visible = true);
	
	void SetClickAction(std::function<void()> action);
	void SetPointerEnterAction(const std::function<void()>& action);
	void SetPointerExitAction(const std::function<void()>& action);
	
	[[nodiscard]] const bool& hovering() const;

	SFMLPE::AnimationSprite& animation();

	sf::RectangleShape& rectShape();
	sf::Text& text();

	void Start() override;
	void Update() override;
	void Render(sf::RenderWindow& window) override;
};
