/***********************************************************************************
 * Entity.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class Entity.
 ************************************************************************************/



#include "include/Entity.hpp"
Entity::Entity(int hitpoints)
    : mVelocity(sf::Vector2f(0.f, 0.f))
    , mHitpoints(hitpoints)
{

}


void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

void Entity::accelerate(sf::Vector2f a)
{
    mVelocity += a;
}

void Entity::accelerate(float ax, float ay)
{
    mVelocity.x += ax;
    mVelocity.y += ay;
}

void Entity::setHitpoints(int hp)
{
    mHitpoints = hp;
}

int Entity::getHitpoints() const
{
    return mHitpoints;
}

void Entity::heal(int hp)
{
    mHitpoints += hp;
}


void Entity::damage(int hp)
{
    mHitpoints -= hp;
}

void Entity::destroy()
{
    mHitpoints = -1;
}


bool Entity::isAlive() const
{
    return mHitpoints >= 0;
}


/////////////////PROTECTED
void Entity::updateCurrent(sf::Time dt)
{
    this->move(mVelocity * dt.asSeconds()); //move is a function of sf::Transformable
}
