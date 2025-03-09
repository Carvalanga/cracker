#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "app.h"
#include "cracker.h"

static const bool is_Started = 0;

int run_app()
{

    sf::Texture bg_texture;
    if(!bg_texture.loadFromFile(BG_TEXTURE_PATH))
        return 0;

    sf::Music music;
    if(!music.openFromFile(MUSIC_PATH))
        return 0;

    sf::Font btn_font;
    if(!btn_font.loadFromFile(BTN_FONT_PATH))
        return 0;

    sf::IntRect bg_rect(0, 0, img_size, img_size);
    sf::Sprite bg(bg_texture, bg_rect);

    sf::RectangleShape hack_button(sf::Vector2(button_size_x, button_size_y));
    hack_button.setFillColor(sf::Color(41,49,51));
    hack_button.setPosition({110, 248});

    sf::RectangleShape progressBar({290, 15});
    progressBar.setFillColor(sf::Color(0, 128, 0));
    progressBar.setPosition({15, 248 + button_size_y / 2 - 7});

    sf::Text hack_text;
    hack_text.setFont(btn_font);
    hack_text.setFillColor(sf::Color::White);
    hack_text.setString("HACK!");
    hack_text.setPosition({130, 250});

    sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(img_size, img_size), "Cracker");
    sf::Event event;
    music.play();

    CRACK_ERRORS err_code = NOTHING;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2 mouse_pos = sf::Mouse::getPosition(window);
                if (hack_button.getGlobalBounds().contains({mouse_pos.x, mouse_pos.y}) && !is_Started)
                    err_code = crack();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        if(clock.getElapsedTime().asSeconds() > time_offset)
        {
            if(bg_rect.left == (sheet_cnt - 1) * img_size)
                bg_rect.left = 0;
            else
                bg_rect.left += img_size;

            bg.setTextureRect(bg_rect);
            clock.restart();
        }

        window.clear();

        window.draw(bg);
        window.draw(progressBar);
        window.draw(hack_button);

        switch (err_code)
        {
        case NOTHING:
            window.draw(hack_text);
            break;

        case NO_ERROR:
            printf("WIN!");
            break;

        default:
            break;
        }


        window.display();
    }

    return 0;
}