#ifndef glob
#define glob
#include <vector>
#include "sprites.h"
#include <memory>

namespace global{ //contains global variables
double camera_x=0, camera_y=0;//all coordinates are based on the actual level and are converted to a view friendly value at rendertime
Player jay(sf::Vector2f(0,0));
    unsigned int resolution_x=460*1.5, resolution_y=240*1.5;
std::vector<std::shared_ptr<SpriteBase>> StageBuffer;//only contains active solids
std::vector<std::shared_ptr<SpriteBase>> SpriteBuffer;
std::vector<unsigned int> graveyard;
}

#endif

