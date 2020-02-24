#include <SFML/Graphics.hpp>
#include <global_vars.h>
#include <level_renderer.h>
#include <player_manager.h>
#include <sprite_manager.h>
#include <collision_manager.h>
#include <sprites.h>
#include <iostream>
int main()
{
    const unsigned int video_x=sf::VideoMode::getDesktopMode().width, video_y=sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(video_x, video_y), "Return to Silius", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    PlayerManager player;
    sf::RenderTexture game_layer;
    global::jay.setTarget(&game_layer);

    player.init(&game_layer);

    sf::Sprite game_layer_sprite;

    SpriteManager spr_mgr;
    spr_mgr.addSprite(new StageBlock(0, 288, 777, 100));
    spr_mgr.addSprite(new StageBlock(778, 240, 23, 47));

    CollisionManager coll_mgr;
    coll_mgr.init(&player);

    game_layer_sprite.setTexture(game_layer.getTexture());
    const double scale_factor=(float)video_x/(float)global::resolution_x;
    game_layer_sprite.setScale(scale_factor, scale_factor);
    game_layer_sprite.setPosition(sf::Vector2f(0.f, (video_y-game_layer_sprite.getGlobalBounds().height)/2.f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        spr_mgr.hc1();
        coll_mgr.checkCollisions();
        player.halfcycle1();
        coll_mgr.checkCollisions2();
        player.halfcycle2();
        game_layer.display();
        window.draw(game_layer_sprite);
        window.display();
    }

    return 0;
}
