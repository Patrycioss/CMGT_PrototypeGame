#include "../Character/Character.hpp"

//Illidan
	#define ILLIDAN_LEFT sf::Vector2f{220,70}
	#define ILLIDAN_LEFT_MIRRORED sf::Vector2f{604,70}
	#define ILLIDAN_LEFT_ATTACK sf::Vector2f{850,70}

	#define ILLIDAN_RIGHT sf::Vector2f{695,70}
	#define ILLIDAN_RIGHT_ATTACK sf::Vector2f{449, 70};

//Kaelthas
	#define KAELTHAS_LEFT sf::Vector2f{232,20}
	#define KAELTHAS_LEFT_MIRRORED sf::Vector2f{604,20}
	#define KAELTHAS_LEFT_ATTACK sf::Vector2f{850,20}
	
	#define KAELTHAS_RIGHT sf::Vector2f{730,20}
	#define KAELTHAS_RIGHT_ATTACK sf::Vector2f{484,20}

//Arthas
	#define ARTHAS_LEFT sf::Vector2f{300,180}
	#define ARTHAS_LEFT_MIRRORED sf::Vector2f{556,180}
	#define ARTHAS_LEFT_ATTACK sf::Vector2f{802,180}

	#define ARTHAS_RIGHT sf::Vector2f{740,180}
	#define ARTHAS_RIGHT_ATTACK sf::Vector2f{494, 180}


//Timings
#define ARTHAS_ATTACK_DURATION sf::milliseconds(300);
#define ILLIDAN_ATTACK_DURATION sf::milliseconds(300);
#define KAELTHAS_ATTACK_DURATION sf::milliseconds(300);

enum class Orientation
{
	Left,
	Left_Mirrored,
	Left_Attack,
	Right,
	Right_Attack
};

enum class TypeDuration
{
	Attack
};

class ConstantManager
{

public:
	
	static sf::Vector2f Get(const Avatar& avatar, const Orientation& orientation)
	{
		
		switch (avatar)
		{
			case Avatar::Kaelthas:
				switch (orientation) 
				{
					case Orientation::Left: return KAELTHAS_LEFT;
					case Orientation::Left_Mirrored: return KAELTHAS_LEFT_MIRRORED;
					case Orientation::Right: return KAELTHAS_RIGHT;
					case Orientation::Left_Attack: return KAELTHAS_LEFT_ATTACK;
					case Orientation::Right_Attack: return KAELTHAS_RIGHT_ATTACK;
				}
				break;
			
			case Avatar::Arthas:
				switch (orientation)
				{
					case Orientation::Left: return ARTHAS_LEFT;
					case Orientation::Left_Mirrored: return ARTHAS_LEFT_MIRRORED;
					case Orientation::Right: return ARTHAS_RIGHT;
					case Orientation::Left_Attack: return ARTHAS_LEFT_ATTACK;
					case Orientation::Right_Attack: return ARTHAS_RIGHT_ATTACK;
				}
				break;
			
			case Avatar::Illidan:
				switch (orientation)
				{
					case Orientation::Left: return ILLIDAN_LEFT;
					case Orientation::Left_Mirrored: return ILLIDAN_LEFT_MIRRORED;
					case Orientation::Right: return ILLIDAN_RIGHT;
					case Orientation::Left_Attack: return ILLIDAN_LEFT_ATTACK;
					case Orientation::Right_Attack: return ILLIDAN_RIGHT_ATTACK;
				}
				break;

			case Avatar::None: throw std::invalid_argument("Can't get the orientation of Avatar::None");
		}
		
		return {};
	};
	
	static sf::Time Get(const Avatar& avatar, const TypeDuration& timing)
	{
		switch (avatar) {
			case Avatar::Illidan:
				switch (timing) {
					case TypeDuration::Attack:
						return ILLIDAN_ATTACK_DURATION;
				}
				break;
			case Avatar::Arthas:
				switch (timing) {
					case TypeDuration::Attack:
						return ARTHAS_ATTACK_DURATION;
				}
				break;
			case Avatar::Kaelthas:
				switch (timing) {
					case TypeDuration::Attack:
						return KAELTHAS_ATTACK_DURATION;
				}
				break;
			case Avatar::None:
				throw std::invalid_argument("Can't get the timing of Avatar::None");
		};
		
		return {};
	};
};