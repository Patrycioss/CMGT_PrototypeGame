#pragma once
#include "SFML/Graphics.hpp"
#include "Rectangle.hpp"
#include <map>


namespace SFMLPE {

  class GameObject {
	  
  private:

	  //Hierarchy information
  
      std::map<const unsigned int, GameObject*> children_;
	  GameObject* parent_ = nullptr;
	  static unsigned int lastID_;
	  unsigned int ID_ = -1;
	  bool visible_;
	  
	  sf::Vector2f parentOffset_;
	  
  //Geometric information  

	  Rectangle rect_;
	  sf::Vector2f originalSize_;
	  sf::Vector2f scale_{1,1};
	  
	  //Mirroring stuff
	  
	  bool verticallyMirrored_ = false;
	  bool horizontallyMirrored_ = false;
	  bool beingVertMirrored_ = false;
	  bool beingHorMirrored_ = false;
	  
	  
  public:
  //Constructors
  
	  GameObject(const GameObject& other);
	  explicit GameObject(const sf::Vector2f &position, const bool &visible = true);
	  GameObject(const float &x, const float &y, const bool &visible = true);

	  
  //Geometric information
  
	  [[nodiscard]] const Rectangle& rect() const;
	  [[nodiscard]] const sf::Vector2f& position() const;
	  [[nodiscard]] const sf::Vector2f& size() const;
	  [[nodiscard]] const sf::Vector2f& originalSize() const;
	  [[nodiscard]] const sf::Vector2f& scale() const;

	  sf::Vector2f mousePosition;

	  [[nodiscard]] const bool& vertMirrored() const;
	  [[nodiscard]] const bool& horMirrored() const;
	  [[nodiscard]] const bool& beingVertMirrored() const;
	  [[nodiscard]] const bool& beingHorMirrored() const;

	  
  //Geometric manipulation

	  virtual void SetPosition(const sf::Vector2f &newPosition);
	  virtual void SetPosition(const float &x, const float &y);
	  virtual void Move(const sf::Vector2f &transformation);
	  virtual void Move(const float &x, const float &y);

	  virtual void MirrorVert(const bool& mirror);
	  virtual void MirrorHor(const bool& mirror);
	  virtual void Mirror(const bool& horizontal, const bool& vertical);

	  void CalcParentOffset();

	  void SetWidth(const float& x);
	  void SetHeight(const float& y);
	  void SetSize(const float& width, const float& height);
	  void SetSize(const sf::Vector2f& size);
	  
	  void SetScaleX(const float& x);
	  void SetScaleY(const float& y);
	  void SetScale(const sf::Vector2f& scale);
	  void SetScale(const float& x, const float& y);
	  virtual void UpdateScale(const sf::Vector2f& prevScale);

  protected:
	  virtual void UpdateSize(const float& x, const float& y);
	  virtual void SetOnlyThisPosition(const sf::Vector2f &position);
	  virtual void SetOnlyThisPosition(const float &x, const float &y);
	  
  public:
	  //HitChecking
  
	  [[nodiscard]] bool PointOver(const sf::Vector2f& point) const;
	  [[nodiscard]] bool PointOver(const float& x, const float& y) const;
	  
	  
  //Hierarchy information
  
	  [[nodiscard]] const unsigned int& ID() const;
	  [[nodiscard]] unsigned int ChildCount() const;
	  [[nodiscard]] const bool& Visible() const;
	  const bool& Visible(const bool &visible);

	  [[nodiscard]] const GameObject* parent() const;
	  [[nodiscard]] const sf::Vector2f& parentOffset() const;
	  
  //Hierarchy manipulation
  
	  void SetParent(GameObject* gameObject);
	  void RemoveParent();

	  void AddChild(GameObject* gameObject);
	  void RemoveChild(unsigned int& ID);
	  void RemoveChild(GameObject* gameObject);
	  
	  
  //Call chain methods
  
  public:
	  virtual void Render(sf::RenderWindow& renderWindow);
	  virtual void Start();
	  virtual void Update();
  };
}