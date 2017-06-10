/***********************************************************************************
 * AnimatedSprite.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Hold Sprite and perform animations.
 ************************************************************************************/

#ifndef ANIMATEDSPRITE_HPP_INCLUDED
#define ANIMATEDSPRITE_HPP_INCLUDED
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class AnimatedSprite : public sf::Sprite
{
public:
            AnimatedSprite();
            AnimatedSprite(const sf::Texture & texture);
            AnimatedSprite(const sf::Texture & texture, const sf::IntRect& spriteRect, const int row, const int col, const float freq = 1);
    //row and col are numbers of sprites per row and per column in spritesheet (passed as texture)
    //spriteRect is a rectangle of the first sprite (length = (length of spritesheet) / (row); width = (width of spritesheet) / (col)))
    //freq is the numbers of animation per frame

    void    initAnimation(const sf::IntRect& spriteRect, const int row, const int col, const float freq = 1); //Call this function if these arguments have not been passed in constructor

    void    setFrequency(const float freq);

    //Add additional sprite rectangle
    void    addSpriteRect(const sf::IntRect& rect);

    //Call this function everyframe to proceed to next sprite rectangle (perform the next animation)
    void    performAnimation();

private:
    void    initSpriteRects();  //Initialize all the sprite rectangle based the first sprite rectangle
                                //and the number of sprites per row and per column in spritesheet

    sf::Vector2f mInitialPoint; //Vector to top left corner of the first sprite rectangle
    sf::Vector2f mSpriteRectSize; //Size of each sprite rectangle

    float mFrequency; //Animation frequency

    int mSpritesPerRow;
    int mSpritesPerCol;

    std::vector<sf::IntRect> mSpriteRects; //Contains all the sprite rectangles
};


#endif // ANIMATEDSPRITE_HPP_INCLUDED
