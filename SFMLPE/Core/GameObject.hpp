#pragma once
#include "SFML/Graphics.hpp"
#include "Rectangle.hpp"
#include <map>

namespace SFMLPE {

  class GameObject {
  private:
	  static unsigned int lastID_;
	  unsigned int ID_;
	  bool visible_;

	  Rectangle rect_;
	  std::map<const unsigned int, GameObject *> children_;

	  GameObject *parent_ = nullptr;

  protected:
	  void SetParent(GameObject *gameObject, const bool &safe = true);
	  void RemoveParent(const bool &removeFromParent = true);

	  void AddChild(GameObject *gameObject, const bool &setParent = true);
	  void RemoveChild(unsigned int &ID, const bool &fixParent = true);
	  void RemoveChild(GameObject *gameObject, const bool &fixParent = true);
	  void RemoveAllChildren(const bool &safe = true);

  public:
	  GameObject(const GameObject &other);
	  explicit GameObject(const sf::Vector2f &position, const bool &visible = true);
	  GameObject(const float &x, const float &y, const bool &visible = true);
	  ~GameObject();

	  Rectangle rect();
	  [[nodiscard]] sf::Vector2f position() const;
	  [[nodiscard]] sf::Vector2f size() const;

	  [[nodiscard]] unsigned int ID() const;

	  GameObject *parent();

	  [[nodiscard]] bool Visible() const;
	  bool Visible(const bool &visible);

	  virtual void SetPosition(const sf::Vector2f &newPosition);
	  virtual void SetPosition(const float &x, const float &y);
	  virtual void Move(const sf::Vector2f &transformation);
	  virtual void Move(const float &x, const float &y);

	  virtual void Render();
	  virtual void Start();
	  virtual void Update();
  };
}