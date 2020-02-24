#ifndef play
#define play
#include <SFML/Graphics.hpp>
#include <global_vars.h>
#include <level_renderer.h>
#include <iostream>
#include <cmath>

class PlayerManager
{
private:
    sf::RenderTexture* target;
    LevelRenderer render;
    double velocity=0.0;
    double vertical_velocity=0;
    const double speedatframe[9]= {-34.0*4.0, -39.0*4.0, -15.0*4.0, -11.0*4.0, 0.0, 11.0*4.0, 15.0*4.0, 39.0*4.0, 34.0*4.0};
    const double gravity = 1000; //px sec^-2
    const double terminal_velocity=240;//px s-1
    const double air_decel = 200;//px sec^-2
    int constspeed=4;
    int haltframes=0;
    bool airbourne=true;
    bool jumping=false;
    bool z_been_pressed=false;
    bool jumped_off_land=false;
    bool facing_right=true;
    int jumpcounter=0;
    const int jumpmax=15;//frames ascending
public:
    void init(sf::RenderTexture* tex)
    {
        render.init(tex);
        render.LoadLevel("stage1.png");//testing
    }
    void halfcycle1()
    {
        global::jay.backupPos();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            if(!airbourne&&jumpcounter==jumpmax)jumped_off_land=true;
            if(jumped_off_land)
            {
                z_been_pressed=true;
                if(jumpcounter>0)
                {
                    jumping=true;
                    jumpcounter--;
                    vertical_velocity=-terminal_velocity;
                }
            }
        }
        else if(z_been_pressed)jumpcounter=0;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            facing_right=false;
            if(!airbourne)
            {
                if(constspeed>4)
                {
                    constspeed=4;
                    haltframes=4;
                    velocity=0;
                }
                if(constspeed!=0&&!((bool)haltframes))
                {
                    velocity=speedatframe[--constspeed];
                }
                if((bool)haltframes)haltframes--;
            }
            else
            {
                if(!(velocity<speedatframe[0]))velocity-=air_decel/60.0;
            }
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                facing_right=true;
                if(!airbourne)
                {
                    if(constspeed<4)
                    {
                        constspeed=4;
                        haltframes=4;
                        velocity=0;
                    }
                    if(constspeed!=8&&!((bool)haltframes))velocity=speedatframe[++constspeed];
                    if((bool)haltframes)haltframes--;
                }
                else
                {
                    if(!(velocity>speedatframe[8]))velocity+=air_decel/60.0;
                }
            }
            else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if(velocity<0.0)velocity=speedatframe[++constspeed];
                if(velocity>0.0)velocity=speedatframe[--constspeed];
            }
        }
        global::jay.setPos(sf::Vector2f((floor(((global::jay.getBounds().left+velocity/60.0)*2)+0.5)/2), global::jay.getBounds().top));//horizontal
        if(!jumping)if(vertical_velocity<terminal_velocity)vertical_velocity+=gravity/60.0;//calc gravity
        global::jay.setPos(sf::Vector2f(global::jay.getBounds().left, global::jay.getBounds().top+vertical_velocity/60.0));//vertical
        jumping=false;
        global::jay.updateVelocity(velocity, facing_right);
        global::jay.increment();
        return;
    }
    void halfcycle2()
    {
        render.draw();
        sf::Vector2f jaypos_backup;
        jaypos_backup.x=global::jay.getBounds().left;
        jaypos_backup.y=global::jay.getBounds().top;
        global::jay.setPos(sf::Vector2f(global::jay.getBounds().left-global::camera_x, global::jay.getBounds().top));
        global::jay.draw();
        global::jay.setPos(jaypos_backup);
    }
    void northHit()
    {
        vertical_velocity=0.0;
        jumpcounter=jumpmax;
        z_been_pressed=false;
        jumped_off_land=false;
    }
    void westHit()
    {
        //velocity=0.0;
    }
    void floatation(bool floating)
    {
        airbourne=floating;
    }
};

#endif
