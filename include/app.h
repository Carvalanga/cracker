#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//--------------------------------------------------------------------
const char* BTN_FONT_PATH   = "../fonts/Dogurtlen DEMO.ttf";
const char* BG_TEXTURE_PATH = "../textures/bg_sprite_sheet.png";
const char* MUSIC_PATH 		= "../music/music.mp3";
const float button_size_x = 100.f;
const float button_size_y = 50.f;
//--------------------------------------------------------------------

const int img_size = 320;
const int sheet_cnt = 32;

const double time_offset = 0.04f;

int run_app();
bool create_button(sf::RectangleShape &button, sf::Text &text, const char *font_path, const char *string);

#endif