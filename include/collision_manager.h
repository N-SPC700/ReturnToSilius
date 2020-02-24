#ifndef collmgr
#define collmgr
#include "sprites.h"
#include <cmath>

class CollisionManager
{
private:
    PlayerManager* pm;
    bool floating=true;
    sf::FloatRect HB_a, HB_b;//center, against
    inline bool overlap (float StartA,float EndA, float StartB, float EndB)
    {
        return StartA <= EndB&&EndA >= StartB;
    }

    side checkSide()
    {

        bool Firsttotheleft = false;
        bool Firsttotheright = false;
        bool Firstabove = false;
        bool Firstbelow = false;
        //ToS stands for Top or side. It tells whether the sprite collided with the top/bottom part or the side part. 0 = top/bottom, 1 = sides
        if((HB_a.left - std::fabs(HB_a.left- global::jay.getLastPos().x)) <= (HB_b.left - HB_a.width))
            return W;
        if((HB_a.left+HB_a.width + std::fabs(HB_a.left- global::jay.getLastPos().x)) >= ((HB_b.left+HB_b.width) + HB_a.width))
            return E;
        if((HB_a.top - std::fabs(HB_a.top- global::jay.getLastPos().y)) <= (HB_b.top - HB_a.height))
            return N;
        if((HB_a.top+HB_a.height + std::fabs(HB_a.top- global::jay.getLastPos().y)) >= ((HB_b.top+HB_a.height) + (HB_a.height)))
            return S;

    }
    sf::FloatRect ceilRect(sf::FloatRect f)
    {
        f.left=ceil(f.left);
        f.top=ceil(f.top);
    }
    sf::FloatRect floorRect(sf::FloatRect f)
    {
        f.left=floor(f.left);
        f.top=floor(f.top);
    }
public:
    void init(PlayerManager* p)
    {
        pm=p;
    }
    void handleCollision(side s)
    {
        switch(s)
        {
        case N:
            //std::cout << "lastpos " << global::jay.getLastPos().y << std::endl;
            // std::cout << "pos " << global::jay.getBounds().top << std::endl;
            global::jay.setPos(sf::Vector2f(global::jay.getBounds().left, HB_b.top-global::jay.getBounds().height-.1f));//puts jay a tad bit above the surface in hopes that he collides immediately next frame
            pm->northHit();
            floating=false;
            // std::cout << "COLLISION!" << std::endl;
            break;
        case W:
            global::jay.setPos(sf::Vector2f(HB_b.left-global::jay.getBounds().width-.1f, global::jay.getBounds().top));
            pm->westHit();
            // std::cout << "COLLISION!" << std::endl;
            break;
        }
    }
    void checkCollisions()
    {
        for(int i=0; i<global::StageBuffer.size(); i++)
        {
            HB_a=global::jay.getBounds();
            HB_b=global::StageBuffer[i]->getBounds();
            if(HB_a.intersects(HB_b))
            {
                handleCollision(checkSide());
            }
        }
        pm->floatation(floating);
        floating=true;
    }
    void checkCollisions2()
    {

        for(int i=0; i<global::StageBuffer.size(); i++)
        {
            HB_a=global::jay.getBounds();
            HB_b=global::StageBuffer[i]->getBounds();
            if(HB_a.intersects(HB_b))
            {
                handleCollision(checkSide());
                std::cout << "COLLISION!" << std::endl;
            }
        }
    }
};

#endif

