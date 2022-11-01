#include "Button.hpp"

Button::Button(const sf::Vector2f& position, 
			   const char* filePath, 
			   const unsigned int& numFrames, 
			   const unsigned int& cols, 
			   const unsigned int& rows,
			   const bool& visible)
			   : SFP::GameObject(position, visible)
			   , animationSprite_(std::make_unique<SFP::AnimationSprite>(position, filePath, numFrames, cols, rows))
{
	UpdateSize(animationSprite_->size().x, animationSprite_->size().y);
	AddChild(animationSprite_.get());
}
			
void Button::Start() 
{
	eventHandler.Subscribe(sf::Event::MouseButtonPressed, [&] (const sf::Event& event)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (hovering_) OnClick();

		}
	});
	
	GameObject::Start();
}

void Button::Update() 
{
	if (PointOver(SFP::Game::MousePosition()))
	{
		if (!hovering_)
		{
			OnPointerEnter();
			hovering_ = true;
		}

		WhenHovering();
	}
	else if (hovering_)
	{
		OnPointerExit();
		hovering_ = false;
	}

	animationSprite_->Animate();
	
	SFP::GameObject::Update();
}

SFP::AnimationSprite& Button::animation() {
	return *animationSprite_;
}

const bool& Button::hovering() const {
	return hovering_;
}

void Button::OnClick(){}
void Button::WhenHovering(){}
void Button::OnPointerEnter(){}
void Button::OnPointerExit(){}


