#pragma clang diagnostic push

#include <cmath>
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
	  return rect_.position;
  }

  const sf::Vector2f& GameObject::size() const 
  {
	  return rect_.size;
  }
  
  const sf::Vector2f& GameObject::originalSize() const 
  {
	  return originalSize_;
  }

  const sf::Vector2f& GameObject::scale() const 
  {
	  return scale_;
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
	  sf::Vector2f transformation = newPosition - rect_.position;
	  rect_.position = newPosition;

	  this->CalcParentOffset();

	  for (auto pair: children_)
		  pair.second->SetPosition(pair.second->position() + transformation);
  }

  void GameObject::SetPosition(const float &x, const float &y) 
  {
	  sf::Vector2f transformation = sf::Vector2f{x, y} - rect_.position;
	  rect_.position = sf::Vector2f{x, y};

	  this->CalcParentOffset();

	  for (auto pair: children_)
		  pair.second->SetPosition(pair.second->position() + transformation);
  }

  void GameObject::Move(const sf::Vector2f &transformation)  // NOLINT(misc-no-recursion)
  {
	  rect_.Move(transformation);

	  this->CalcParentOffset();

	  for (auto pair: children_)
		  pair.second->Move(transformation);
  }

  void GameObject::Move(const float &x, const float &y)  // NOLINT(misc-no-recursion)
  {
	  rect_.Move(x, y);

	  this->CalcParentOffset();
	  
	  for (auto pair: children_)
		  pair.second->Move(x, y);
  }

  void GameObject::MirrorVert(const bool& mirror) // NOLINT(misc-no-recursion)
  {
	  beingVertMirrored_ = true;
	  
	  bool orphan = parent_ == nullptr;

	  if (mirror) {
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


  void GameObject::MirrorHor(const bool& mirror)  // NOLINT(misc-no-recursion)
  {
	  beingHorMirrored_ = true;
	  
	  printf("ID: %u with offset: %f \n", ID_, parentOffset_.y);
	  
	  
	  if (mirror) {
		  if (parent_ != nullptr && parent_->beingHorMirrored())
			  SetOnlyThisPosition(
					    this->position().x
					  , parent_->position().y 
					  - parentOffset_.y);
		  
		  else SetOnlyThisPosition(
				        this->position().x
					  , this->position().y 
					  + this->size().y);
	  }
	  else {
		  if (parent_ != nullptr && parent_->beingHorMirrored()) 
			  SetOnlyThisPosition(
					    this->position().x
					  , parent_->position().y 
					  + parentOffset_.y);
		  
		  else SetOnlyThisPosition(
					    this->position().x
					  , this->position().y 
					  - this->size().y);
	  }

	  horizontallyMirrored_ = mirror;

	  for (auto pair : children_)
		  pair.second->MirrorHor(mirror);

	  beingHorMirrored_ = false;
  }
  
  void GameObject::Mirror(const bool& horizontal, const bool& vertical) 
  {
	  this->MirrorHor(horizontal);
	  this->MirrorVert(vertical);
  }

  //Calculates the distance between this object and its parent
  void GameObject::CalcParentOffset()
  {
	  if (parent_ == nullptr)
	  {
		  parentOffset_ = {0,0};
		  return;
	  }
	  
	  if (verticallyMirrored_) parentOffset_.x = parent_->position().x - this->position().x;
	  else parentOffset_.x = this->position().x - parent_->position().x;	  
	 
	  if (horizontallyMirrored_) parentOffset_.y = parent_->position().y - this->position().y;
	  else parentOffset_.y = this->position().y - parent_->position().y;
  }
  
  void GameObject::SetWidth(const float& x)
  {
	  sf::Vector2f prevScale = scale_;

	  rect_.size.x = std::fabs(x);
	  scale_.x = rect_.size.x / originalSize_.x;
	  this->UpdateScale(prevScale);
  }
  
  void GameObject::SetHeight(const float& y) 
  {
	  sf::Vector2f prevScale = scale_;

	  rect_.size.y = std::fabs(y);
	  scale_.y = rect_.size.y / originalSize_.y;
	  this->UpdateScale(prevScale);
  }
  
  void GameObject::SetSize(const sf::Vector2f& size) 
  {
	  sf::Vector2f prevScale = scale_;

	  rect_.size = {std::fabs(size.x), std::fabs(size.y)};
	  scale_.x = rect_.size.x / originalSize_.x;
	  scale_.y = rect_.size.y / originalSize_.y;
	  this->UpdateScale(prevScale);
  }
  
  void GameObject::SetSize(const float& x, const float& y) 
  {
	  sf::Vector2f prevScale = scale_;

	  rect_.size = {std::fabs(x),std::fabs(y)};
	  scale_.x = rect_.size.x / originalSize_.x;
	  scale_.y = rect_.size.y / originalSize_.y;
	  this->UpdateScale(prevScale);
  }
  
  void GameObject::SetScaleX(const float& x) 
  {
	  sf::Vector2f prevScale = scale_;

	  scale_.x = std::fabs(x);
	  rect_.size.x = originalSize_.x * scale_.x;
	  this->UpdateScale(prevScale);
  }
  
  void GameObject::SetScaleY(const float& y) 
  {
	  sf::Vector2f prevScale = scale_;
	  
	  scale_.y = std::fabs(y);
	  rect_.size.y = originalSize_.y * scale_.y;
	  
	  this->UpdateScale(prevScale);
  }
  
  void GameObject::SetScale(const sf::Vector2f& scale) 
  {
	  sf::Vector2f prevScale = scale_;

	  scale_ = {std::fabs(scale.x), std::fabs(scale.y)};
	  
	  rect_.size.x = originalSize_.x * scale_.x;
	  rect_.size.y = originalSize_.y * scale_.y;
	  
	  this->UpdateScale(prevScale);
  }
  
  void GameObject::SetScale(const float& x, const float& y) 
  {
	  sf::Vector2f prevScale = scale_;
	  
	  scale_ = {std::fabs(x), std::fabs(y)};
	  
	  rect_.size.x = originalSize_.x * scale_.x;
	  rect_.size.y = originalSize_.y * scale_.y;
	  
	  this->UpdateScale(prevScale);
  }

  void GameObject::UpdateScale(const sf::Vector2f& prevScale)
  {
	  if (parent_ != nullptr)
	  {
		 
		  
		  sf::Vector2f newOffset = {std::fabs(parentOffset_.x) / prevScale.x, std::fabs(parentOffset_.y) / prevScale.y};
		  newOffset.x *= scale_.x;
		  newOffset.y *= scale_.y;

		  if (parent_->horizontallyMirrored_) newOffset.y *= -1;
		  if (parent_->verticallyMirrored_) newOffset.x *= -1;
		  
		  
		  printf("ID: %u, offsetY: %f, scaled down offsetY: %f, offsetX: %f, scaled down offsetX: %f \n",
		         ID_, parentOffset_.y, parentOffset_.y * scale_.y, parentOffset_.x, parentOffset_.x * scale_.x);
		  printf("Scale: %f, prevScale: %f, posX: %f, posY: %f \n", scale_.y, prevScale.y, position().x, position().y);
		  printf("PPosX: %f, PPosY: %f newOffsetX: %f, newOffsetY: %f \n"
				 , parent_->position().x, parent_->position().y, newOffset.x, newOffset.y);
		  
		  
		  SetOnlyThisPosition(parent_->position() + newOffset);
	  }
	  
	  for (auto pair : children_)
	  {
		  pair.second->SetScale(scale_);
	  }
  }

  //Only updates the original size, use SetSize() to change the size
  void GameObject::UpdateSize(const float& x, const float& y)
  {
	  rect_.size.x = x;
	  rect_.size.y = y;
	  
	  
	  originalSize_ = rect_.size;
	  
	  sf::Vector2f prevScale = scale_;
	  
	  scale_.x = 1;
	  scale_.y = 1;
	  
	  this->UpdateScale(prevScale);
  }

  //Doesn't update children
  void GameObject::SetOnlyThisPosition(const sf::Vector2f& position) 
  {
	  rect_.position = position;
  }

  //Doesn't update children
  void GameObject::SetOnlyThisPosition(const float& x, const float& y) 
  {
	  rect_.position = sf::Vector2f{x, y};
  }
  
  
////////////////////////////////////////////////////////////////////////////////////////////

//HitChecking

////////////////////////////////////////////////////////////////////////////////////////////

  bool GameObject::PointOver(const sf::Vector2f& point) const
  {
	  return     (point.x >= position().x
	              && point.x <= position().x + size().x
	              && point.y >= position().y
	              && point.y <= position().y + size().y);
  }

  bool GameObject::PointOver(const float& x, const float& y) const 
  {
	  return  (x >= position().x
	           && x <= position().x + size().x
	           && y >= position().y
	           && y <= position().y + size().y);
  }


////////////////////////////////////////////////////////////////////////////////////////////

//Hierarchy Information

////////////////////////////////////////////////////////////////////////////////////////////

  const unsigned int& GameObject::ID() const 
  {
	  return ID_;
  }

  unsigned int GameObject::ChildCount() const 
  {
	  return children_.size();
  }

  const bool& GameObject::Visible() const 
  {
	  return visible_;
  }

  const bool& GameObject::Visible(const bool &visible) 
  {
	  return visible_ = visible;
  }
  
  const GameObject* GameObject::parent() const
  {
	  return parent_;
  }

  const sf::Vector2f& GameObject::parentOffset() const 
  {
	  return parentOffset_;
  }
  

////////////////////////////////////////////////////////////////////////////////////////////

//Hierarchy Manipulation

////////////////////////////////////////////////////////////////////////////////////////////

  void GameObject::SetParent(GameObject* gameObject) 
  {
	  if (parent_ == gameObject) return;
	  
	  
	  parent_->RemoveChild(gameObject);
	  
	  parent_ = gameObject;

	  this->CalcParentOffset();
	  
	  if (gameObject != nullptr) parent_->AddChild(this);
  }

  void GameObject::RemoveParent() 
  {
	  parent_->RemoveChild(this);
	  parent_ = nullptr;
	  this->CalcParentOffset();
  }

  void GameObject::AddChild(GameObject* gameObject) 
  {
	  children_[gameObject->ID_] = gameObject;
	  gameObject->parent_ = this;
	  gameObject->CalcParentOffset();
  }

  void GameObject::RemoveChild(unsigned int &ID) 
  {
	  children_[ID]->parent_ = nullptr;
	  children_[ID]->CalcParentOffset();
	  children_.erase(ID);
  }

  void GameObject::RemoveChild(GameObject *gameObject) 
  {
	  gameObject->SetParent(nullptr);
	  gameObject->CalcParentOffset();

	  if (!children_.erase(gameObject->ID()))
	    printf("Failed to delete object with ID: %d", gameObject->ID());
  }
  

////////////////////////////////////////////////////////////////////////////////////////////

//Call chain methods

////////////////////////////////////////////////////////////////////////////////////////////

  void GameObject::Render(sf::RenderWindow& window)
  {
	  for (auto pair : children_) 
	  {
		  if (pair.second->visible_)
			  pair.second->Render(window);
	  }
  }

  void GameObject::Start(){
	  for (auto pair : children_)
		  pair.second->Start();
  }
  
  void GameObject::Update()
  {
	  for (auto pair : children_)
		  pair.second->Update();
  }
}