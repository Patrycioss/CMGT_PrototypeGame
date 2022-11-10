#pragma once

#include <map>
#include <functional>

#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Tween.hpp"

class TweenManager
{
private:
	
	static unsigned int lastID_;
	static std::vector<std::unique_ptr<Tween>> tweens_;
	static std::vector<std::vector<std::unique_ptr<Tween>>::iterator> tweensToBeRemoved_;
	static std::vector<Tween*> tweensToAdd_;


public:
	static void Update();
	static Tween* AddTween(Tween* tween);
	static void ClearTweens();
};
