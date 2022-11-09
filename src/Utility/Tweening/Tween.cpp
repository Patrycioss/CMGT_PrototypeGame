#include "Tween.hpp"
#include "TweenManager.hpp"

Tween* Tween::operator+=(std::function<void()>& onEnd) {
	onEnd_ = onEnd;
	return this;
}

bool Tween::operator==(const Tween& tween) const {
	return (tween.ID_ == ID_);
}

void Tween::Update() {}

void Tween::Finish() 
{
	if (onEnd_) onEnd_();
	finished_ = true;
}

void Tween::SetEndAction(const std::function<void()>& action) {
	onEnd_ = action;
}

//Finish without calling the onFinish stuff (for quitting during animation)
void Tween::Abort() {
	finished_ = true;
}
