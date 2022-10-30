#include "Button.hpp"

class EraseButton : public Button
{
public:
	explicit EraseButton(const sf::Vector2f& position);
	void OnPointerExit() override;
	void OnPointerEnter() override;
	void OnClick() override;

};
