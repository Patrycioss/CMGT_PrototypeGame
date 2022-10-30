#include "NewButton.hpp"

#include <utility>
#include "../SFMLPE/Core/Game.hpp"

NewButton::NewButton(const sf::Vector2f& position, const char* filePath, const unsigned int& numFrames, const unsigned int& cols,
                     const unsigned int& rows, const bool& visible)
					: SFMLPE::GameObject(position, visible)
		, animationSprite_(std::make_unique<SFMLPE::AnimationSprite>(position, filePath, numFrames, cols, rows))
		, hovering_(false)

{
	UpdateSize(animationSprite_->size().x, animationSprite_->size().y);
	AddChild(animationSprite_.get());
}

NewButton::NewButton(const sf::Vector2f& position, const sf::Vector2f& size, const bool& visible)
	: SFMLPE::GameObject(position)
	, rectangleShape_(size)
{
	rectangleShape_.setPosition(position);
	text_.setPosition(position);
	text_.setStyle(sf::Text::Regular);
	text_.setFont(SFMLPE::Game::mainFont());
	text_.setCharacterSize(20);
	UpdateSize(size.x, size.y);
}


void NewButton::SetClickAction(std::function<void()> action) {
	onClick_ = action;
}

void NewButton::SetPointerEnterAction(const std::function<void()>& action) {
	onPointerEnter_ = action;
}

void NewButton::SetPointerExitAction(const std::function<void()>& action) {
	onPointerExit_ = action;
}

const bool& NewButton::hovering() const {
	return hovering_;
}

void NewButton::Start()
{
	eventHandler.Subscribe(sf::Event::MouseButtonPressed, [&] (const sf::Event& event)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (hovering_ && onClick_) OnClick();
		}
	});

	GameObject::Start();
}

void NewButton::Update()
{
	if (PointOver(SFMLPE::Game::MousePosition()))
	{
		if (!hovering_)
		{
			if (onPointerEnter_) onPointerEnter_();
			hovering_ = true;
		}
	}
	else if (hovering_)
	{
		if (onPointerExit_) onPointerExit_();
		hovering_ = false;
	}

	if (animationSprite_ != nullptr) animationSprite_->Animate();

	SFMLPE::GameObject::Update();
}

SFMLPE::AnimationSprite& NewButton::animation() {
	return *animationSprite_;
}

void NewButton::Render(sf::RenderWindow& window) 
{
	window.draw(rectangleShape_);
	window.draw(text_);
	SFMLPE::GameObject::Render(window);
}

sf::RectangleShape& NewButton::rectShape() {
	return rectangleShape_;
}

sf::Text& NewButton::text() {
	return text_;
}

void NewButton::OnClick() {
	this->onClick_();
}

