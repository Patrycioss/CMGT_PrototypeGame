#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "GameObject.hpp"

namespace SFMLPE {

  unsigned int GameObject::lastID_;

  GameObject::GameObject(const GameObject &other)
		  : visible_(other.visible_), rect_(other.rect_), parent_(other.parent_) {
	  ID_ = lastID_++;
  }

  GameObject::GameObject(const sf::Vector2f &position, const bool &visible)
		  : visible_(visible), rect_(Rectangle{position}) {
	  ID_ = lastID_++;
  }

  GameObject::GameObject(const float &x, const float &y, const bool &visible)
		  : visible_(visible), rect_(Rectangle{x, y}) {
	  ID_ = lastID_++;
  }

  GameObject::~GameObject() {
	  RemoveAllChildren();
	  RemoveParent();
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

////////////////////////////////////////////////////////////////////////////////////////////

  void GameObject::AddChild(GameObject *gameObject, const bool &setParent) {
	  children_.emplace(gameObject->ID(), gameObject);

	  if (setParent)
		  gameObject->SetParent(this, false);
  }

  void GameObject::RemoveChild(unsigned int &ID, const bool &fixParent) {
	  if (children_.contains(ID)) {
		  if (fixParent)
			  children_[ID]->RemoveParent(false);

		  children_.erase(ID);
	  }
  }

  void GameObject::RemoveAllChildren(const bool &safe) {

	  for (auto pair: children_) {
		  if (!safe) {
			  delete pair.second;
			  continue;
		  }

		  if (pair.second != nullptr) {
			  if (pair.second->parent_ == this)
				  delete pair.second;
		  }
	  }
  }

  void GameObject::RemoveChild(GameObject *gameObject, const bool &fixParent) {
	  if (children_.contains(gameObject->ID())) {
		  if (fixParent)
			  gameObject->RemoveParent(false);

		  children_.erase(gameObject->ID());
	  }
  }

  void GameObject::RemoveParent(const bool &removeFromParent) {
	  if (parent_ == nullptr) return;

	  if (removeFromParent)
		  parent_->RemoveChild(this, false);

	  parent_ = nullptr;
  }

  void GameObject::SetParent(GameObject *gameObject, const bool &safe) {

	  if (parent_ == gameObject) return;

	  if (safe)
		  parent_->RemoveChild(this, false);

	  parent_ = gameObject;

	  if (safe)
		  parent_->AddChild(this, false);
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
  
  void GameObject::Render()
  {
	  for (auto pair : children_)
		  pair.second->Render();
  }
}





#pragma clang diagnostic pop