#pragma clang diagnostic push
#include "GameObject.hpp"

namespace SFMLPE {

////////////////////////////////////////////////////////////////////////////////////////////

//Constructors

////////////////////////////////////////////////////////////////////////////////////////////  
 
  unsigned int GameObject::lastID_;

  GameObject::GameObject(const GameObject &other)
		  : visible_(other.visible_), rect_(other.rect_), parent_(other.parent_) 
  {
	  ID_ = lastID_;
  }

  GameObject::GameObject(const sf::Vector2f &position, const bool &visible)
		  : visible_(visible), rect_(Rectangle{position}) 
  {
	  ID_ = lastID_++;
  }

  GameObject::GameObject(const float &x, const float &y, const bool &visible)
		  : visible_(visible), rect_(Rectangle{x, y}) 
  {
	  ID_ = lastID_++;
  }

  
////////////////////////////////////////////////////////////////////////////////////////////

//Geometric Information

////////////////////////////////////////////////////////////////////////////////////////////

  const Rectangle& GameObject::rect() const 
  {
	  return rect_;
  }

  const sf::Vector2f& GameObject::position() const 
  {
	  return rect_.position_;
  }

  const sf::Vector2f& GameObject::size() const 
  {
	  return rect_.size_;
  }

  const bool& GameObject::vertMirrored() const 
  {
	  return verticallyMirrored_;
  }

  const bool& GameObject::horMirrored() const 
  {
	  return horizontallyMirrored_;
  }
  
  const bool& GameObject::beingVertMirrored() const 
  {
	  return beingHorMirrored_;
  }
  
  const bool& GameObject::beingHorMirrored() const 
  {
	  return beingHorMirrored_;
  }

  
////////////////////////////////////////////////////////////////////////////////////////////

//Geometric Manipulation

////////////////////////////////////////////////////////////////////////////////////////////

  void GameObject::SetPosition(const sf::Vector2f &newPosition)  // NOLINT(misc-no-recursion)
  {
	  sf::Vector2f transformation = newPosition - rect_.position_;
	  rect_.position_ = newPosition;

	  CalcParentOffset();

	  for (auto pair: children_)
		  pair.second->SetPosition(pair.second->position() + transformation);
  }

  void GameObject::SetPosition(const float &x, const float &y) 
  {
	  sf::Vector2f transformation = sf::Vector2f{x, y} - rect_.position_;
	  rect_.position_ = sf::Vector2f{x, y};

	  CalcParentOffset();

	  for (auto pair: children_)
		  pair.second->SetPosition(pair.second->position() + transformation);
  }

  void GameObject::Move(const sf::Vector2f &transformation)  // NOLINT(misc-no-recursion)
  {
	  rect_.Move(transformation);

	  CalcParentOffset();

	  for (auto pair: children_)
		  pair.second->Move(transformation);
  }

  void GameObject::Move(const float &x, const float &y)  // NOLINT(misc-no-recursion)
  {
	  rect_.Move(x, y);

	  CalcParentOffset();


	  for (auto pair: children_)
		  pair.second->Move(x, y);
  }

  void GameObject::MirrorVert(const bool& mirror)
  {
	  beingVertMirrored_ = true;
	  
	  bool orphan = parent_ == nullptr;

	  if (mirror) {
		  //If parent is part of the mirror chain we can set our
		  //x to the x of the parent + our width
		  // as the parent is already mirrored
		  if (!orphan && parent_->beingVertMirrored_)
			  SetOnlyThisPosition(
					    parent()->position().x 
					  - parentOffset_.x
					  , this->position().y);

		  else SetOnlyThisPosition(
				        this->position().x 
					  + this->size().x
					  , this->position().y);
	  }
	  else {
		  if (!orphan && parent_->beingVertMirrored_)
			  SetOnlyThisPosition(
					    parent_->position().x 
					  + parentOffset_.x
					  , this->position().y);
		  else 
		  {
			  SetOnlyThisPosition(
					    this->position().x 
					  - this->size().x
					  , this->position().y);
		  }
	  }

	  verticallyMirrored_ = mirror;

	  for (auto pair : children_)
		  pair.second->MirrorVert(mirror);


	  beingVertMirrored_ = false;
  }


  void GameObject::MirrorHor(const bool& mirror) 
  {
	  //Is true as long as the mirroring chain is doing its thing
	  beingHorMirrored_ = true;
	  
	  printf("ID: %u with sizeX: %f and sizeY: %f \n", ID_, size().x, size().y);
	  
	  
	  if (mirror) {
		  //If parent is part of the mirror chain we can set our
		  //y to the y of the parent + our width
		  // as the parent is already mirrored
		  if (parent_ != nullptr && parent_->beingHorMirrored())
			  SetOnlyThisPosition(
					    this->position().x
					  , parent_->position().y 
					  - parentOffset_.y);

		  //Otherwise we move it downwards with its own height
		  else SetOnlyThisPosition(
				        this->position().x
					  , this->position().y 
					  + this->size().y);
	  }
	  else {
		  //If parent is part of the mirror chain we can set the 
		  //y back to the parent's y + the y-offset.
		  if (parent_ != nullptr && parent_->beingHorMirrored()) 
			  SetOnlyThisPosition(
					    this->position().x
					  , parent_->position().y 
					  + parentOffset_.y);
		  
		  //otherwise we move it upwards with its own height
		  else SetOnlyThisPosition(
					    this->position().x
					  , this->position().y 
					  - this->size().y);
	  }

	  horizontallyMirrored_ = mirror;

	  for (auto pair : children_)
		  pair.second->MirrorHor(mirror);

	  //If the complete mirroring chain is done 
	  beingHorMirrored_ = false;
  }
  
  void GameObject::Mirror(const bool& horizontal, const bool& vertical) 
  {
	  this->MirrorHor(horizontal);
	  this->MirrorVert(vertical);
  }

  void GameObject::UpdateSize(const float& x, const float& y)
  {
	  rect_.size_.x = x;
	  rect_.size_.y = y;
  }

////////////////////////////////////////////////////////////////////////////////////////////

//HitChecking

////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////

//Hierarchy Information

////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////

//Hierarchy Manipulation

////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////

//Call chain methods

////////////////////////////////////////////////////////////////////////////////////////////


  unsigned int GameObject::ID() const {
	  return ID_;
  }

  

  GameObject *GameObject::parent() {
	  return parent_;
  }

  

  sf::Vector2f GameObject::parentOffset() const {
	  return parentOffset_;
  }

  

  const bool& GameObject::Visible() const {
	  return visible_;
  }

  const bool& GameObject::Visible(const bool &visible) {
	  return visible_ = visible;
  }

  unsigned int GameObject::ChildCount() const {
	  return children_.size();
  }

  bool GameObject::MouseOver() const{
	  return PointOver((float) sf::Mouse::getPosition().x , (float) sf::Mouse::getPosition().y);
  }

  bool GameObject::PointOver(const sf::Vector2f& point) const{
	  return     (point.x >= position().x
	              && point.x <= position().x + size().x
	              && point.y >= position().y
	              && point.y <= position().y + size().y);
  }

  bool GameObject::PointOver(const float& x, const float& y) const {
	  return  (x >= position().x
	           && x <= position().x + size().x
	           && y >= position().y
	           && y <= position().y + size().y);
  }
////////////////////////////////////////////////////////////////////////////////////////////

  void GameObject::AddChild(GameObject* gameObject) {
	  children_[gameObject->ID_] = gameObject;
	  gameObject->parent_ = this;
	  gameObject->CalcParentOffset();
  }

  void GameObject::RemoveChild(unsigned int &ID) {
	  children_[ID]->parent_ = nullptr;
	  children_[ID]->CalcParentOffset();
	  children_.erase(ID);
  }

  void GameObject::RemoveChild(GameObject *gameObject) {
	  gameObject->parent_ = nullptr;
	  gameObject->CalcParentOffset();

	  if (children_.contains(gameObject->ID_))
		  children_.erase(gameObject->ID());

	  else printf("Failed to delete object with ID: %d", gameObject->ID_);
  }

  void GameObject::RemoveParent() {
	  parent_->RemoveChild(this);
	  parent_ = nullptr;
	  CalcParentOffset();
  }

  void GameObject::SetParent(GameObject* gameObject, const bool &safe) {

	  if (parent_ == gameObject) return;
	  parent_->RemoveChild(gameObject);
	  parent_ = gameObject;
	  parent_->AddChild(this);
	  CalcParentOffset();
  }

////////////////////////////////////////////////////////////////////////////////////////////
  void GameObject::CalcParentOffset() 
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

  

  

  void GameObject::SetOnlyThisPosition(const sf::Vector2f& position) {
	  rect_.position_ = position;
  }

  void GameObject::SetOnlyThisPosition(const float& x, const float& y) {
	  rect_.position_ = sf::Vector2f{x, y};
  }

  
}