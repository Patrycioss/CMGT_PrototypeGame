#pragma once
#include "effolkronium/random.hpp"


struct Attributes
{
	static const unsigned int POINTS = 8;
	static const unsigned int MANDATORY_STRENGTH_POINTS = 1;
	static const unsigned int MANDATORY_WITS_POINTS = 1;
	static const unsigned int MANDATORY_AGILITY_POINTS = 0;
	
	Attributes(const Attributes& attributes) = default;
	
	Attributes() 
		: agility(MANDATORY_AGILITY_POINTS), strength(MANDATORY_STRENGTH_POINTS), wits(MANDATORY_WITS_POINTS){};
	
	explicit Attributes(const unsigned int& points)
		: agility(0), strength(0), wits(0)
	{
		RandomizePoints(points);
	};

	unsigned int agility;   //1
	unsigned int wits;      //2
	unsigned int strength;  //3

	//Returns selected attribute based on index.
	//1 - Agility
	//2 - Wits
	//3 - Strength
	unsigned int& attribute(const unsigned int& index)
	{
		switch (index)
		{
			case 1:
				return agility;
				break;
			
			case 2:
				return wits;
				break;
			
			case 3:
				return strength;
				break;  
			
			default:
				throw std::invalid_argument("Attribute has to have the number 1, 2 or 3");
				break;
		}
	}
	
	//Checks if all points have been spent
	[[nodiscard]] bool IsFull() const {
		return (strength + agility + wits == POINTS);
	};
	
	[[nodiscard]] unsigned int Remaining() const {
		return POINTS - strength - agility - wits;
	}
	
	//Resets all attributes to their minimum points
	void Reset()
	{
		strength = MANDATORY_STRENGTH_POINTS;
		agility = MANDATORY_AGILITY_POINTS;
		wits = MANDATORY_WITS_POINTS;
	};
	
	//Number in the range of 0-8, if less than mandatory points they will still be assigned
	void RandomizePoints(unsigned int points)
	{
		if (agility < MANDATORY_AGILITY_POINTS)
		{
			agility++;
			points--;
		}

		if (wits < MANDATORY_WITS_POINTS)
		{
			wits++;
			points--;
		}

		if (strength < MANDATORY_STRENGTH_POINTS)
		{
			strength++;
			points--;
		}
		
		if (points <= 0) return;
		
		for (int i = 0; i < points; i++) AddToRandomAttribute();
	};

	//Resets all points and randomizes them
	void Randomize()
	{
		Reset();
		RandomizePoints(POINTS - MANDATORY_AGILITY_POINTS + MANDATORY_STRENGTH_POINTS + MANDATORY_WITS_POINTS);
	};
	
	//Fills the attributes with random points keeping the already assigned ones
	void FillRemainingPoints() {
		RandomizePoints(Remaining());
	};
	
private:
	void AddToRandomAttribute() {
		attribute(effolkronium::random_static::get(1,3))++;
	};
};
