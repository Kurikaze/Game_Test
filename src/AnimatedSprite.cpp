#include "include/AnimatedSprite.hpp"
AnimatedSprite::AnimatedSprite()
    : Sprite()
{

}

AnimatedSprite::AnimatedSprite(const sf::Texture& texture)
    : Sprite(texture)
{

}

AnimatedSprite::AnimatedSprite(const sf::Texture& texture, const sf::IntRect& spriteRect, const int row, const int col, const float freq)
    : Sprite(texture, spriteRect)
    , mInitialPoint(sf::Vector2f(spriteRect.left, spriteRect.top))
    , mSpriteRectSize(sf::Vector2f(spriteRect.width, spriteRect.height))
    , mFrequency(freq)
    , mSpritesPerRow(row)
    , mSpritesPerCol(col)


{
    initSpriteRects();
}

void AnimatedSprite::initAnimation(const sf::IntRect& spriteRect, const int row, const int col, const float freq)
{
    setTextureRect(spriteRect);
    mInitialPoint = sf::Vector2f(spriteRect.left, spriteRect.top);
    mSpriteRectSize = sf::Vector2f(spriteRect.width, spriteRect.height);
    mSpritesPerRow = row;
    mSpritesPerCol = col;
    mFrequency = freq;
    initSpriteRects();

}

void AnimatedSprite::setFrequency(const float freq)
{
    mFrequency = freq;
}

void AnimatedSprite::addSpriteRect(const sf::IntRect& rect)
{
    mSpriteRects.push_back(rect);
}



void AnimatedSprite::performAnimation()
{
    static float currentIndex = 0;
    int total = mSpritesPerRow * mSpritesPerCol;
    if (static_cast<int>(currentIndex) >= total) currentIndex = 0;
    setTextureRect(mSpriteRects[currentIndex]);
    currentIndex += mFrequency;
}

void AnimatedSprite::initSpriteRects()
{
    static int r = 0;
    static int c = 0;
    for (r = 0; r < mSpritesPerCol; r++)
    {
        for (c = 0; c < mSpritesPerRow; c++)
        {
            int left = c*mSpriteRectSize.x + mInitialPoint.x;
            int top = r*mSpriteRectSize.y + mInitialPoint.y;
            mSpriteRects.push_back(sf::IntRect(left, top, mSpriteRectSize.x, mSpriteRectSize.y));
        }
    }
}
