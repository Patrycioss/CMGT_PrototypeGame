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

  sf::Vector2f GameObject::parentOffset() const {
	  return parentOffset_;
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
	  gameObject->parent_ = this;
	  gameObject->SetParentOffset();
  }

  void GameObject::RemoveChild(unsigned int &ID) {
	  children_[ID]->parent_ = nullptr;
	  children_[ID]->SetParentOffset();
	  children_.erase(ID);
  }

  void GameObject::RemoveChild(GameObject *gameObject) {
	  gameObject->parent_ = nullptr;
	  gameObject->SetParentOffset();

	  if (children_.contains(gameObject->ID_))
		  children_.erase(gameObject->ID());

	  else printf("Failed to delete object with ID: %d", gameObject->ID_);
  }

  void GameObject::RemoveParent() {
	  parent_->RemoveChild(this);
	  parent_ = nullptr;
	  SetParentOffset();
  }

  void GameObject::SetParent(GameObject* gameObject, const bool &safe) {

	  if (parent_ == gameObject) return;
	  parent_->RemoveChild(gameObject);
	  parent_ = gameObject;
	  parent_->AddChild(this);
	  SetParentOffset();
  }

////////////////////////////////////////////////////////////////////////////////////////////

  void GameObject::SetPosition(const sf::Vector2f &newPosition) {
	  sf::Vector2f transformation = newPosition - rect_.position_;
	  rect_.position_ = newPosition;

	  SetParentOffset();

	  for (auto pair: children_)
		  pair.second->SetPosition(pair.second->position() + transformation);
  }

  void GameObject::SetPosition(const float &x, const float &y) {
	  sf::Vector2f transformation = sf::Vector2f{x, y} - rect_.position_;
	  rect_.position_ = sf::Vector2f{x, y};

	  SetParentOffset();
			  
	  for (auto pair: children_)
		  pair.second->SetPosition(pair.second->position() + transformation);
  }

  void GameObject::SetSize(const sf::Vector2f& size) 
  {
	  rect_.size_ = size;
  }


  void GameObject::SetParentOffset() 
  {
	  if (parent_ == nullptr)
	  {
		  parentOffset_ = {0,0};
		  return;
	  }
	  
	  parentOffset_ = position() - parent_->position();
	  
	  if (vertMirrored()) parentOffset_.x *= -1;
	  if (horMirrored()) parentOffset_.y *= -1;
  }

  void GameObject::Move(const sf::Vector2f &transformation) {
	  rect_.Move(transformation);

	  SetParentOffset();

	  for (auto pair: children_)
		  pair.second->Move(transformation);
  }

  void GameObject::Move(const float &x, const float &y) {
	  rect_.Move(x, y);

	  SetParentOffset();


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

  bool GameObject::vertMirrored() const {
	  return verticallyMirrored_;
  }
  
  bool GameObject::horMirrored() const {
	  return horizontallyMirrored_;
  }

  void GameObject::MirrorHor(const bool& mirror) {
	  beingHorMirrored_ = true;

	  sf::Vector2f position = rect_.position_;

	  bool orphan = parent_ == nullptr;
	  
	  if (mirror) {
		  if (!orphan && parent_->beingHorMirrored_)
			  SetOnlyThisPosition(position.x, parent()->position().y - parentOffset_.y);

		  else {
			  SetOnlyThisPosition(position.x, position.y + size().y);
			  printf("ID: %u, height: %f \n", ID_, size().y);
		  }
	  }
	  else {
		  if (!orphan && parent_->beingHorMirrored_) {
			  SetOnlyThisPosition(position.x, parent_->position().y + parentOffset_.y);
//			  printf("ID: %u, with offset from parent: %f, parent has pos: %f, this will have pos: %f \n",ID(), parentOffset_.y,
//			         parent_->position().y, parent_->position().y - parentOffset_.y);		  
		  }
		  else {
			  if (!orphan)
				  SetOnlyThisPosition(position.x, parent_->position().y + ((position.y - size().y) - parent_->position().y));

			  else SetOnlyThisPosition(position.x, position.y - size().y);
		  } 
	  }

	  horizontallyMirrored_ = mirror;

	  for (auto pair : children_)
		  pair.second->MirrorHor(mirror);


	  beingHorMirrored_ = false;
  }

  void GameObject::MirrorVert(const bool& mirror) 
  {
	  beingVertMirrored_ = true;
	  
	  sf::Vector2f position = rect_.position_;

	  bool orphan = parent_ == nullptr;

	  if (mirror) {
		  if (!orphan && parent_->beingVertMirrored_)
			  SetOnlyThisPosition(parent()->position().x - parentOffset_.x, position.y);
		  
		  else SetOnlyThisPosition(position.x + size().x, position.y);
	  }
	  else {
		  if (!orphan && parent_->beingVertMirrored_) {
			  SetOnlyThisPosition(parent_->position().x + parentOffset_.x, position.y);
//			  printf("ID: %u, with offset from parent: %f, parent has pos: %f, this will have pos: %f \n",ID(), parentOffset_.x,
//			         parent_->position().x, parent_->position().x - parentOffset_.x);		  
		  }
		  else  {
			  if (!orphan)
				  SetOnlyThisPosition(parent_->position().x + ((position.x - size().x) - parent_->position().x), position.y);

			  else SetOnlyThisPosition(position.x - size().x, position.y);
		  }
	  }

	  verticallyMirrored_ = mirror;
	  
	  for (auto pair : children_)
		  pair.second->MirrorVert(mirror);


	  beingVertMirrored_ = false;
  }
  
  void GameObject::Mirror(const bool& horizontal, const bool& vertical) {
	  MirrorHor(horizontal);
	  MirrorVert(vertical);
  }

  void GameObject::SetOnlyThisPosition(const sf::Vector2f& position) {
	  rect_.position_ = position;
  }

  void GameObject::SetOnlyThisPosition(const float& x, const float& y) {
	  rect_.position_ = sf::Vector2f{x, y};
  }
}