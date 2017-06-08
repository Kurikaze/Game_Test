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

    void initAnimation(const sf::IntRect& spriteRect, const int row, const int col, const float freq = 1);
    void setFrequency(const float freq);

    void addSpriteRect(const sf::IntRect& rect);
    void performAnimation();

private:
    void initSpriteRects();

    sf::Vector2f mInitialPoint;
    sf::Vector2f mSpriteRectSize;
    float mFrequency;
    int mSpritesPerRow;
    int mSpritesPerCol;

    std::vector<sf::IntRect> mSpriteRects;
};


#endif // ANIMATEDSPRITE_HPP_INCLUDED
