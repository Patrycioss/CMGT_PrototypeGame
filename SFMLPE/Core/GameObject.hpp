#pragma once
#include "SFML/Graphics.hpp"
#include "Rectangle.hpp"
#include <map>

namespace SFMLPE {

  class GameObject {
  private:
	  static unsigned int lastID_;
	  unsigned int ID_ = -1;
	  bool visible_;
	  
	  bool verticallyMirrored_ = false;
	  bool horizontallyMirrored_ = false;
	  

	  Rectangle rect_;
	  std::map<const unsigned int, GameObject*> children_;

	  GameObject* parent_ = nullptr;

  public:

	  void SetParent(GameObject* gameObject, const bool& safe = true);
	  void RemoveParent();

	  void AddChild(GameObject* gameObject);
	  void RemoveChild(unsigned int& ID);
	  void RemoveChild(GameObject* gameObject);

	  GameObject(const GameObject& other);
	  explicit GameObject(const sf::Vector2f &position, const bool &visible = true);
	  GameObject(const float &x, const float &y, const bool &visible = true);
	  ~GameObject();

	  Rectangle rect();
	  [[nodiscard]] sf::Vector2f position() const;
	  [[nodiscard]] virtual sf::Vector2f size() const;

	  [[nodiscard]] float parentSpaceX() const;
	  [[nodiscard]] float localY() const;
	  [[nodiscard]] sf::Vector2f localPosition() const;

	  [[nodiscard]] unsigned int ID() const;
	  
	  [[nodiscard]] unsigned int ChildCount() const;

	  virtual GameObject *parent();

	  [[nodiscard]] bool Visible() const;
	  bool Visible(const bool &visible);

	  virtual void SetPosition(const sf::Vector2f &newPosition);
	  virtual void SetPosition(const float &x, const float &y);
	  virtual void Move(const sf::Vector2f &transformation);
	  virtual void Move(const float &x, const float &y);
	  
	  void SetSize(const sf::Vector2f& size);
	  

	  [[nodiscard]] bool vertMirrored() const;
	  [[nodiscard]] bool horMirrored() const;
	  virtual void MirrorVert(const bool& mirror, const bool& stemsFromRecursion = false);
	  virtual void MirrorHor(const bool& mirror);
	  virtual void Mirror(const bool& horizontal, const bool& vertical);
	  
	  

	  
	  virtual void Render(sf::RenderWindow& renderWindow);
	  virtual void Start();
	  virtual void Update();
	  
	  //Special setPosition versions for mirroring
  protected:
	  virtual void SetPositionMirror(const sf::Vector2f &newPosition);
	  virtual void SetPositionMirror(const float &x, const float &y);
  };
}