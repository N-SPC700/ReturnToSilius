#ifndef sprmgr
#define sprmgr
#include "sprites.h"
#include <memory>
#include <vector>
#include <global_vars.h>

class SpriteManager
{
private:
    std::vector<std::shared_ptr<SpriteBase>> StageSolids;//contains all solids, but not active
    unsigned int last_ID=0;
public:
    void addSprite(SpriteBase* sprt)
    {
        std::shared_ptr<SpriteBase> temp (sprt);
        temp->ID=last_ID++;
        switch(temp->_SpriteType)
        {
        case SOLID:
            StageSolids.push_back(temp);
            return;
        default:
            global::SpriteBuffer.push_back(temp);
        }
    }
    void hc1()
    {
        global::StageBuffer.clear();
        for(int i=0; i<StageSolids.size(); i++) //will eventually optimise for relevant sprites
        {
            global::StageBuffer.push_back(StageSolids[i]);
        }
    }
};


#endif
