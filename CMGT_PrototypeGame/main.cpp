#include <iostream>
#include <random>
#include "../SFMLPE/SFMLPE.hpp"
#include "CMGT_PrototypeGame.hpp"
#include <string.h>
#include "effolkronium/random.hpp"

using Random = effolkronium::random_static;

struct WindowNamePicker
{
	static const int amount = 5;
	
	const char* names[amount]{
		"Brought to you by ÉHâ─ ]├ÉUHëσHâ∞ Hï♣±%☻",
		"Brought to you by Chthonic Metal Games Tribe Company!",
		"Brought to you by three hamsters in a trenchcoat!",
		"AAAAAAHHHHHHH",
		":)     :|      :(      :'("
	};
	
	
	const char* GetName(const unsigned int& index = -1)
	{
		if (index == -1) {

			int i = Random::get<uint8_t>(0, amount-1);

			return names[i];
		}
		else if (index < amount) return names[index];
		
		return "nope :(";
	};
};

int main(int argc, char** argv)
{
	int width = 1300;
	int height = 800;
	char* resourcePath;
	
	const char* possibleArguments = "Possible argument formats are: \n"
									"   [resourcePath] \n"
									"   [width] [height] \n"
									"   [resourcePath] [width] [height] \n"
									"   [width] [height][resourcePath] \n \n";


	if (argc == 2)
	{
		if (strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-h") == 0)
			printf("%s", possibleArguments);

		resourcePath = argv[1];
		printf("Set resource path to {%s} \n", resourcePath);
	}
	else if (argc == 3)
	{
		int newWidth = std::strtol(argv[1], nullptr, 10);

		if (newWidth != 0L)
		{
			int newHeight = std::strtol(argv[2], nullptr, 10);

			if (newHeight != 0L) {
				
				width = newWidth;
				printf("Set window width to: {%d} \n", width);

				height = newHeight;
				printf("Set window height to: {%d} \n", width);
			}
			else
			{
				printf("Arguments {%s} {%s} are invalid,\n%s \n",
				            argv[1], argv[2], possibleArguments);
			}
			
		}
		else printf("Arguments {%s} {%s} are invalid,\n%s \n",
		            argv[1], argv[2], possibleArguments);
	}
	else if (argc == 4)
	{
		int newWidth = std::strtol(argv[1], nullptr, 10);
		
		if (newWidth == 0L)
		{
			newWidth = std::strtol(argv[2], nullptr, 10);
			
			if (newWidth != 0L)
			{
				int newHeight = std::strtol(argv[3], nullptr, 10);
				
				if (newHeight == 0L)
					printf("Arguments {%s} {%s} {%s} are invalid,\n%s \n",
					       argv[1], argv[2], argv[3], possibleArguments);
				
				else
				{					
					resourcePath = argv[1];
					printf("Set resource path to {%s} \n", resourcePath);

					width = newWidth;
					printf("Set window width to: {%d} \n", width);

					height = newHeight;
					printf("Set window height to: {%d} \n", width);
				}
			}
			else printf("Arguments {%s} {%s} {%s} are invalid,\n%s \n",
			            argv[1], argv[2], argv[3], possibleArguments);
			
		}
		else
		{
			int newHeight = std::strtol(argv[2], nullptr, 10);
			
			if (newHeight != 0L)
			{
				width = newWidth;
				printf("Set window width to: {%d} \n", width);

				height = newHeight;
				printf("Set window height to: {%d} \n", width);

				resourcePath = argv[3];
				printf("Set resource path to {%s} \n", resourcePath);
			}
			else printf("Arguments {%s} {%s} {%s} are invalid,\n%s \n",
			            argv[1], argv[2], argv[3], possibleArguments);
		}
	}
	
	
	CMGT_PrototypeGame game;
	game.Run(width,height,WindowNamePicker().GetName(), "CMGT_PrototypeGame/Resources", "fonts/minecraftFont.ttf");
	return 0;
}



