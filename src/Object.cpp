/***********************************************************************************
 * Object.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class Object.
 ************************************************************************************/


#include "include/Object.hpp"

Object::Object()
    : Entity(1) //All object has 1 hitpoint by default
{

}

Object::Object(const sf::Texture& texture)
    : Entity(1)
    , mSprite(texture)
{

}

Object::Object(const sf::Texture& texture, const sf::IntRect& textureRect)
    : Entity(1)
    , mSprite(texture, textureRect)
{

}

void Object::initialize(const sf::Texture& texture, const sf::IntRect& textureRect)
{
    mSprite.setTexture(texture);
    mSprite.setTextureRect(textureRect);
}

void Object::setTexture(const sf::Texture& texture)
{
    mSprite.setTexture(texture);
}

void Object::setTexture(const sf::Texture& texture, const sf::IntRect& textureRect)
{
    mSprite.setTexture(texture);
    mSprite.setTextureRect(textureRect);
}


void Object::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Uncomment the next line to draw the boundary of the object (used for debugging collision)
    //drawBound(target, states);

    target.draw(mSprite, states);
}

sf::FloatRect Object::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Object::drawBound(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::CircleShape circle(getBoundingRect().width/2.f);
    //circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(this->getWorldPosition());
    circle.setFillColor(sf::Color::Black);
    target.draw(circle);
}

void Object::updateCurrent(sf::Time dt)
{
    Entity::updateCurrent(dt);
}
