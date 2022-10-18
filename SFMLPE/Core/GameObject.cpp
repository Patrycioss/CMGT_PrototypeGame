#pragma clang diagnostic push
#include "GameObject.hpp"

namespace SFMLPE {

  unsigned int GameObject::lastID_;

  GameObject::GameObject(const GameObject &other)
		  : visible_(other.visible_), rect_(other.rect_), parent_(other.parent_) {
	  ID_ = lastID_;
  }

  GameObject::GameObject(const sf::Vector2f &position, const bool &visible)
		  : visible_(visible), rect_(Rectangle{position}) {
	  ID_ = lastID_++;
//	  printf("ID: %d, with x: %d \n", ID_, (int)rect_.position_.x);

  }

  GameObject::GameObject(const float &x, const float &y, const bool &visible)
		  : visible_(visible), rect_(Rectangle{x, y}) {
	  ID_ = lastID_++;
//	  printf("ID: %d, with x: %d \n", ID_, (int)rect_.position_.x);

  }

  GameObject::~GameObject() {
  }

////////////////////////////////////////////////////////////////////////////////////////////

  unsigned int GameObject::ID() const {
	  return ID_;
  }

//Returns a copy of the object's rectangle
  Rectangle GameObject::rect() {
	  return rect_;
  }

  GameObject *GameObject::parent() {
	  return parent_;
  }

  sf::Vector2f GameObject::position() const {
	  return rect_.position_;
  }

  sf::Vector2f GameObject::size() const {
	  return rect_.size_;
  }

  bool GameObject::Visible() const {
	  return visible_;
  }

  bool GameObject::Visible(const bool &visible) {
	  return visible_ = visible;
  }

  unsigned int GameObject::ChildCount() const {
	  return children_.size();
  }
////////////////////////////////////////////////////////////////////////////////////////////

  void GameObject::AddChild(GameObject* gameObject) {
	  children_[gameObject->ID_] = gameObject;
	  gameObject->parent_ = gameObject;
  }

  void GameObject::RemoveChild(unsigned int &ID) {
	  children_[ID]->parent_ = nullptr;
	  children_.erase(ID);
  }

  void GameObject::RemoveChild(GameObject *gameObject) {
	  gameObject->parent_ = nullptr;

	  if (children_.contains(gameObject->ID_))
		  children_.erase(gameObject->ID());

	  else printf("Failed to delete object with ID: %d", gameObject->ID_);
  }

  void GameObject::RemoveParent() {
	  parent_->RemoveChild(this);
	  parent_ = nullptr;
  }

  void GameObject::SetParent(GameObject* gameObject, const bool &safe) {

	  if (parent_ == gameObject) return;
	  parent_->RemoveChild(gameObject);
	  parent_ = gameObject;
	  parent_->AddChild(this);
  }

////////////////////////////////////////////////////////////////////////////////////////////

  void GameObject::SetPosition(const sf::Vector2f &newPosition) {
	  sf::Vector2f transformation = newPosition - rect_.position_;
	  rect_.position_ = newPosition;

	  for (auto pair: children_)
		  pair.second->SetPosition(pair.second->position() + transformation);
  }

  void GameObject::SetPosition(const float &x, const float &y) {
	  sf::Vector2f transformation = sf::Vector2f{x, y} - rect_.position_;
	  rect_.position_ = sf::Vector2f{x, y};

	  for (auto pair: children_)
		  pair.second->SetPosition(pair.second->position() + transformation);
  }

  void GameObject::Move(const sf::Vector2f &transformation) {
	  rect_.Move(transformation);

	  for (auto pair: children_)
		  pair.second->Move(transformation);
  }

  void GameObject::Move(const float &x, const float &y) {
	  rect_.Move(x, y);

	  for (auto pair: children_)
		  pair.second->Move(x, y);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////

  void GameObject::Start(){
	  for (auto pair : children_)
		  pair.second->Start();
  }
  void GameObject::Update()
  {
	  for (auto pair : children_)
		  pair.second->Update();
  }

  void GameObject::Render(sf::RenderWindow& window)
  {
	  for (auto pair : children_) {
		  if (pair.second->visible_)
			  pair.second->Render(window);
	  }
  }
}