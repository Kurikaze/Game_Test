/***********************************************************************************
 * Animal.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class Animal.
 ************************************************************************************/


#include "include/Animal.hpp"

Animal::Animal()
    : Entity(1)
{

}

Animal::Animal(TextureID id, const TextureHolder& textures)
    : Entity(1)
{
    initialize(id, textures);
}



void Animal::initialize(TextureID id, const TextureHolder& textures)
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    mIsJumping = false;
    mSprite.setTexture(textures.get(id));

}


void Animal::setAnimation(const sf::IntRect& spriteRect, const int row, const int col, const float freq)
{
    mSprite.initAnimation(spriteRect, row, col, freq);
}




void Animal::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Uncomment the next line to draw the boundary (used for debugging)
    //drawBound(target, states);
    target.draw(mSprite, states);

}

sf::FloatRect Animal::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());

}


void Animal::drawBound(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::CircleShape circle(getBoundingRect().width/2.f);
    //circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(this->getWorldPosition());
    circle.setFillColor(sf::Color::Black);
    target.draw(circle);
}



bool Animal::isJumping() const
{
    return mIsJumping;
}

void Animal::setJumping(bool jump)
{
    mIsJumping = jump;
}


void Animal::updateCurrent(sf::Time dt)
{
    mSprite.performAnimation();
    Entity::updateCurrent(dt);
}

