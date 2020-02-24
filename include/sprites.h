#ifndef spr
#define spr
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

enum SpriteType {PLAYER, SOLID, ENEMY, P_BULLET, SOLID_SPRT};
enum PlayerCollisionType {GHOST, COL_SOLID};
enum side {N=42,S,E,W};

class SpriteBase
{
protected:
    sf::Sprite Sprite;
    sf::RenderTexture* target;
    sf::Vector2f last_pos;
    std::vector<sf::Texture> Textures;//loading of textures and animation cycling should occur in each sprite's constructor
    bool lifetime_over=false;//signals to be removed from sprite buffer
public:
    SpriteType _SpriteType;
    PlayerCollisionType _PlayerCollisionType;
    unsigned int ID=0;

    virtual sf::FloatRect getBounds()
    {
        return Sprite.getGlobalBounds();
    }
    virtual void setPos(sf::Vector2f pos)
    {
        Sprite.setPosition(pos);
    }
    virtual backupPos()
    {
        last_pos.x=getBounds().left;
        last_pos.y=getBounds().top;
    }
    virtual void increment() {}
    virtual void draw()
    {
        sf::Vector2f temp;
        temp.x=Sprite.getGlobalBounds().left;
        temp.y=Sprite.getGlobalBounds().top;
        Sprite.setPosition(round(temp.x), round(temp.y));
        target->draw(Sprite);
        Sprite.setPosition(temp);
    }
    virtual void setTarget(sf::RenderTexture* tex)
    {
        target=tex;
    }
    virtual void damage(int dmg) {}
    virtual sf::Vector2f getLastPos()
    {
        return last_pos;
    }
};
class StageBlock : public SpriteBase
{
private:
    sf::FloatRect Sol; //collision data
public:
    StageBlock(float x, float y, float w, float h)
    {
        _SpriteType=SOLID;
        _PlayerCollisionType=COL_SOLID;
        Sol.left=x;
        Sol.top=y;
        Sol.width=w;
        Sol.height=h;
    }
    sf::FloatRect getBounds() override
    {
        return Sol;
    }
    void setPos(sf::Vector2f pos) override
    {
        Sol.left=pos.x;
        Sol.top=pos.y;
    }

};

class Player : public SpriteBase
{
private:
    double phase_inc=0.0;
    double phase=0.0;
    bool facing_right=true;
    std::vector<sf::Texture> Textures_flp;
    std::vector<sf::Texture> Textures_idle;
public:
    Player(sf::Vector2f pos)
    {
        _SpriteType=PLAYER;
        _PlayerCollisionType=GHOST;
        Textures.resize(14);
        Textures_flp.resize(14);
        Textures_idle.resize(2);
        for(int i=0; i<Textures.size(); i++)Textures[i].loadFromFile("jaysprites/std/" + std::to_string(i)+".gif");
        for(int i=0; i<Textures_flp.size(); i++)Textures_flp[i].loadFromFile("jaysprites/flp/" + std::to_string(i)+".gif");
        Textures_idle[1].loadFromFile("jaysprites/idle/left.gif");
        Textures_idle[0].loadFromFile("jaysprites/idle/right.gif");
        Sprite.setTexture(Textures[0]);
        Sprite.setPosition(pos);
    }
    void increment() override
    {
        phase+=phase_inc;
        phase=std::fmod(phase, 1.0);
        if(facing_right)
        {
            std::cout << lrint(phase*13.0)<< std::endl;
            if(phase_inc!=0.0)Sprite.setTexture(Textures[lrint(phase*13.0)]);//dependent on anim frames of jay
            else
            {
                Sprite.setTexture(Textures_idle[0]);
                phase=0;
            }
        }
        else
        {
            std::cout << lrint(phase*13.0)<< std::endl;
            if(phase_inc!=0.0)Sprite.setTexture(Textures_flp[lrint(phase*13.0)]);//dependent on anim frames of jay
            else
            {
                Sprite.setTexture(Textures_idle[1]);
                phase=0;
            }
        }

    }
    void updateVelocity(double vel, bool direction) //true is right
    {
        phase_inc=(std::abs (vel)/ (34.0*4.0))*(1.0/((60.0/(1000.0/14.0))*60.0));//DEPENDENT ON SPEEDATFRAME AND JAYS ANIM FRAMERATE
        facing_right=direction;
    }
    sf::FloatRect getBounds() override
    {
        sf::FloatRect temp=Sprite.getGlobalBounds();
        temp.height-=1.f;
        return temp;
    }
};
#endif
