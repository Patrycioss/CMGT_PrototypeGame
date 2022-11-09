#include "Button.hpp"
#include "ResourceManager.hpp"
#include "../Audio/Jukebox.hpp"
#include "Game.hpp"

#include <utility>

Button::Button(const sf::Vector2f& position, const char* filePath, const unsigned int& numFrames, const unsigned int& cols,
               const unsigned int& rows, const bool& visible)
					: GameObject(position, visible)
		, animationSprite_(std::make_unique<AnimationSprite>(position, filePath, numFrames, cols, rows))
		, hovering_(false)

{
	UpdateSize(animationSprite_->size().x, animationSprite_->size().y);
	AddChild(animationSprite_.get());
}

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const bool& visible)
	: GameObject(position)
	, rectangleShape_(size)
{
	rectangleShape_.setPosition(position);
	text_.setPosition(position);
	text_.setStyle(sf::Text::Regular);
	text_.setFont(*ResourceManager::LoadFont(fontPath_));
	text_.setCharacterSize(20);
	UpdateSize(size.x, size.y);
}


void Button::SetClickAction(const std::function<void()>& action) {
	onClick_ = action;
}

void Button::SetPointerEnterAction(const std::function<void()>& action) {
	onPointerEnter_ = action;
}

void Button::SetPointerExitAction(const std::function<void()>& action) {
	onPointerExit_ = action;
}

void Button::SetLockAction(const std::function<void()>& action) {
	onLock_ = action;
}

void Button::SetUnlockAction(const std::function<void()>& action) {
	onUnlock_ = action;
}

const bool& Button::hovering() const {
	return hovering_;
}

void Button::Start()
{
	eventHandler.Subscribe(sf::Event::MouseButtonPressed, [this] (const sf::Event& event)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (locked_) return;
			
			if (hovering_ && onClick_) {
				Jukebox::get().buttonClick.play();
				onClick_();
			}
		}
	});

	GameObject::Start();
}

void Button::Update()
{
	if (locked_) return;
	
	if (PointOver(Game::MousePosition()))
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
	
	GameObject::Update();
}

AnimationSprite& Button::animation() {
	return *animationSprite_;
}

void Button::Render(sf::RenderWindow& window) 
{
	window.draw(rectangleShape_);
	window.draw(text_);
	GameObject::Render(window);
}

sf::RectangleShape& Button::rectShape() {
	return rectangleShape_;
}

sf::Text& Button::text() {
	return text_;
}

Button::~Button() 
{
	ResourceManager::RemoveFont(fontPath_);
}

bool Button::TriggerClickAction() {
	if (onClick_) {
		onClick_();
		return true;
	}
	return false;
}

bool Button::TriggerPointerEnterAction() {
	if (onPointerEnter_) {
		onPointerEnter_();
		return true;
	}
	return false;}

bool Button::TriggerPointerExitAction() {
	if (onPointerExit_) {
		onPointerExit_();
		return true;
	}
	return false;
}

bool Button::TriggerLockAction(){
	if (onLock_) {
		onLock_();
		return true;
	}
	return false;
}

bool Button::TriggerUnlockAction(){
	if (onUnlock_) {
		onUnlock_();
		return true;
	}
	return false;
}

void Button::Lock(const bool& lock) {
	
	if (locked_ && !lock) TriggerUnlockAction();
	else if (!locked_ && lock) TriggerLockAction();
	
	locked_ = lock;
}

const bool& Button::locked() const {
	return locked_;
}

void Button::UpdateScale(const sf::Vector2f& prevScale) {
	GameObject::UpdateScale(prevScale);
	
	rectangleShape_.setScale(scale());
	text_.setScale(scale());
	
}

