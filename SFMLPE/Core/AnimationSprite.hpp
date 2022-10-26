#pragma once
#include "Sprite.hpp"




namespace SFMLPE
{
  ///All frame indexing starts from 0, so if an animation has 11 frames it will go from frame 0 to frame 10
  
  class AnimationSprite : public Sprite
  {
  private:
	  sf::Clock clock;
	  
	  unsigned int frameWidth_;
	  unsigned int frameHeight_;
	  
	  unsigned int rows_;
	  unsigned int columns_;
	  
	  unsigned int startFrame_ = 0;
	  unsigned int currentFrame_ = 0;
	  
	  unsigned int frameCount_;
	  unsigned int cycleFrameCount_;
	  
	  //Frame delay in milliseconds
	  unsigned int animationDelay_ = 100;
	  
	  

	  
  public:

	  //Frames index from 0
	  void SetFrame(const unsigned int& frame);

	  void SetCycle(const unsigned int& startFrame, const unsigned int& numFrames,
	                const unsigned int& animationDelay = 1, const bool& setFrame = true);
	  
	  AnimationSprite();
	  
	  AnimationSprite(const sf::Vector2f& position, 
					  const char* path, const unsigned int& numFrames,
					  const unsigned int& rows, const unsigned int& columns,
					  const bool& visible = true);

	  AnimationSprite(const sf::Vector2f& position, 
					  sf::Texture* texture, const unsigned int& numFrames, 
					  const unsigned int& rows, const unsigned int& columns,
					  const bool& visible = true);
	  
//	  AnimationSprite(const sf::Vector2f& position, const sf::Vector2f& size);
	  
	  void Animate();
	  
	  void UpdateSize() override;
  };
}



