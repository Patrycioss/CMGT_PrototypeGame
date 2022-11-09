#pragma once
#include "SFML/Graphics.hpp"
#include "Rectangle.hpp"
#include "GameObject.hpp"

class Sprite : public GameObject
{
private:


protected:
	sf::Texture* texture_;
	sf::Sprite sprite_;
	const char* texturePath_;


public:
	Sprite();
	Sprite(const char* texturePath, const sf::Vector2f& position, const bool& visible = true);

	void SetPosition(const sf::Vector2f& newPosition) override;
	void SetPosition(const float& x, const float& y) override;
	void Move(const float& x, const float& y) override;
	void Move(const sf::Vector2f& transformation) override;

	void MirrorVert(const bool& mirrored) override;
	void MirrorHor(const bool& mirrored) override;

	void UpdateScale(const sf::Vector2f& prevScale) override;
	virtual void UpdateSize();

public:


	const sf::Sprite& GetSFMLSprite() const;

	void Render(sf::RenderWindow& window) override;

	~Sprite();

protected:

	void SetOnlyThisPosition(const sf::Vector2f &newPosition) override;
	void SetOnlyThisPosition(const float &x, const float &y) override;
};