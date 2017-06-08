#ifndef RESOURCEIDENTIFIERS_HPP_INCLUDED
#define RESOURCEIDENTIFIERS_HPP_INCLUDED

#include "include/ResourceHolder.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

enum class TextureID
{
    BLANK,

    TITLE_SCREEN,
    MENU_SCREEN,
    SUB_MENU_SCREEN,

    BACKGROUND,

    TRAINER_000,
    TRAINER_001,
    TRAINER_002,
    TRAINER_003,
    TRAINER_004,
    TRAINER_011,
    TRAINER_015,
    TRAINER_016,
    TRAINER_017,
    TRAINER_018,
    TRAINER_024,
    TRAINER_027,
    TRAINER_031,
    TRAINER_038,
    TRAINER_066,

    PIKACHU,
    JOLTEON,
    FENNEKIN,
    GREEN,
    STEGOSAURUS,
    CACTUS,

    HEART
};

enum class FontID
{
    TITLE,
    MAIN
};

enum class MusicID
{
    TITLE_THEM,
    MENU_THEME,
    GAME_THEME,
    GAME_OVER_THEME

};

typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;
typedef ResourceHolder<sf::Font, FontID> FontHolder;


#endif // RESOURCEIDENTIFIERS_HPP_INCLUDED
