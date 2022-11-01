#pragma once
#include "../SFMLPE/SFMLPE.hpp"

class NewButton : public SFP::GameObject
{
	
private:
	std::unique_ptr<SFP::AnimationSprite> animationSprite_;

	std::function<void()> onClick_;
	std::function<void()> onPointerEnter_;
	std::function<void()> onPointerExit_;
	
	const char* fontPath_ = "fonts/minecraftFont.ttf";
	sf::Text text_;
	sf::RectangleShape rectangleShape_;
	
	
	bool hovering_ = false;
	

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
	
	void SetClickAction(const std::function<void()>& action);
	void SetPointerEnterAction(const std::function<void()>& action);
	void SetPointerExitAction(const std::function<void()>& action);
	
	void TriggerClickAction();
	void TriggerPointerEnterAction();
	void TriggerPointerExitAction();
	
	[[nodiscard]] const bool& hovering() const;

	SFP::AnimationSprite& animation();

	sf::RectangleShape& rectShape();
	sf::Text& text();

	void Start() override;
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	
	~NewButton();
};
