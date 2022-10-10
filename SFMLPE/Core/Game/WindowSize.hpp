#pragma once

struct WindowSize
{
	float width, height;
	
	void SetDimensions(const int& width_, const int& height_)
	{
		width = (float) width_;
		height = (float) height_;
	};
};