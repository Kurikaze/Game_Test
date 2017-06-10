/***********************************************************************************
 * Entity.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Contains information of the object (hitpoints, velocity etc)
 ************************************************************************************/

#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "include/SceneNode.hpp"

class Entity : public SceneNode
{
public:
                    Entity(int hitpoints);

    void            setVelocity(sf::Vector2f velocity);
    void            setVelocity(float vx, float vy);

    sf::Vector2f    getVelocity() const;

    void            accelerate(sf::Vector2f a);
    void            accelerate(float ax, float ay);

    void            setHitpoints(int hp);
    int             getHitpoints() const;

    void            heal(int hp);
    void            damage(int hp);

    void            destroy(); //Set hitpoint negative

    virtual bool    isAlive() const; //Override the function in class SceneNode. Return true if hitpoint >= 0

protected:
    virtual void    updateCurrent(sf::Time dt);
private:
    sf::Vector2f    mVelocity;
    int             mHitpoints;


};


#endif // ENTITY_HPP_INCLUDED
