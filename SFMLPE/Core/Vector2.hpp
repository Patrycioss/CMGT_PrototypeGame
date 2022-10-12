#include <iostream>
#include <SFML/System/Vector2.hpp>

struct Vector2
{
	float x;
	float y;

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vector2)
	{
		os << "{ " << vector2.x << ", " << vector2.y << " }";
		return os;
	}

	Vector2(const float& pX, const float& pY)
	{
		x = pX;
		y = pY;
	}

	Vector2(const Vector2& vector2) : Vector2(vector2.x, vector2.y){};
	explicit Vector2(const sf::Vector2f& vector2) : Vector2(vector2.x, vector2.y){};
	explicit Vector2(const sf::Vector2<int>& vector2) : Vector2((float)vector2.x, (float)vector2.y){};


	explicit Vector2(const sf::Vector2u vector2U)
	{
		x = (float) vector2U.x;
		y = (float) vector2U.y;
	};
	
	Vector2& operator=(const Vector2& a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}
	
	Vector2 operator+(const Vector2& a) const
	{
		return Vector2{x + a.x, y + a.y};
	}
	
	Vector2 operator+=(const Vector2& a)
	{
		x += a.x;
		y += a.y;
		return *this;
	}
	
	Vector2 operator -(const Vector2& a) const
	{
		return Vector2{x - a.x, y - a.y};
	}
	
	Vector2 operator -=(const Vector2& a)
	{
		x -= a.x;
		y -= a.y;
		return *this;
	}
};



