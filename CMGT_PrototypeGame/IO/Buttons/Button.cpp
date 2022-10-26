#include "Button.hpp"

Button::Button(const sf::Vector2f& position, 
			   const char* filePath, 
			   const unsigned int& numFrames, 
			   const unsigned int& cols, 
			   const unsigned int& rows,
			   const bool& visible)
			   : SFMLPE::GameObject(position, visible)
			   , animationSprite_(new SFMLPE::AnimationSprite(position, filePath, numFrames, cols, rows))
{
	UpdateSize(animationSprite_->size().x, animationSprite_->size().y);
	AddChild(animationSprite_);
}

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const bool& visible)
				: SFMLPE::GameObject(position, visible)
				, animationSprite_()
{
	SetSize(size);
}
				
void Button::Start() 
{
	eventHandler.Subscribe(sf::Event::MouseButtonPressed, [&] (const sf::Event& event)
	{
		
		if (event.mouseButton.button == sf::Mouse::Left)
				if (hovering_) OnClick();
	});
	
	
	GameObject::Start();
}

void Button::Update() 
{
	if (PointOver(SFMLPE::Game::MousePosition()))
	{
		if (!hovering_)
		{
			OnPointerEnter();
			hovering_ = true;
			
			if (hasAnimation_) animationSprite_->SetCycle(3, 3, 400);
		}

		WhenHovering();
	}
	else if (hovering_)
	{
		OnPointerExit();
		if (hasAnimation_) animationSprite_->SetCycle(0,3,400);
		hovering_ = false;
	}

	if (hasAnimation_) animationSprite_->Animate();
	
	SFMLPE::GameObject::Update();
}

SFMLPE::AnimationSprite* Button::GetAnimation() {
	return animationSprite_;
}

[[maybe_unused]] const bool& Button::hovering() const {
	return hovering_;
}

void Button::OnClick(){}
void Button::WhenHovering(){}
void Button::OnPointerEnter(){}
void Button::OnPointerExit(){}


