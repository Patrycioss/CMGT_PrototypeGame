#pragma once
#include "../../SFMLPE/SFMLPE.hpp"

class Button : public SFMLPE::GameObject
{
private:
	std::unique_ptr<SFMLPE::AnimationSprite> animationSprite_;
	bool hovering_ = false;
	
public:
	Button(const sf::Vector2f& position, const char* filePath, const unsigned int& numFrames, const unsigned int& cols, const unsigned int& rows,
	       const bool& visible = true);
	
	SFMLPE::AnimationSprite& animation();

	[[nodiscard]] const bool& hovering() const;
	
protected:
	virtual void OnClick();
	virtual void OnPointerEnter();
	virtual void OnPointerExit();
	virtual void WhenHovering();

	void Start() override;
	void Update() override;
};


