#ifndef levelrender
#define levelrender

#include <SFML/Graphics.hpp>
#include <global_vars.h>
#include <string>
#define camera_threshold 300
class LevelRenderer
{
private:
    sf::RenderTexture* target;
    sf::Texture level_texture;
    sf::Sprite level_sprite;
public:
    void init(sf::RenderTexture* tex)
    {
        target=tex;
        level_sprite.setPosition(sf::Vector2f(0.f, 0.f));
        target->create(global::resolution_x, global::resolution_y);
    }
    void draw()
    {
        if(global::jay.getBounds().left+global::jay.getBounds().width>global::camera_x+camera_threshold)global::camera_x=global::jay.getBounds().left+global::jay.getBounds().width-camera_threshold;
        level_sprite.setTextureRect(sf::IntRect(global::camera_x, global::camera_y, global::resolution_x,global::resolution_y));
        target->draw(level_sprite);
    }
    void LoadLevel(std::string file)
    {
        level_texture.loadFromFile(file);
        level_sprite.setTexture(level_texture);
    }
};

#endif
