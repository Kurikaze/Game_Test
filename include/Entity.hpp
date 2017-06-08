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
    void            destroy();

    virtual bool    isAlive() const;

protected:
    virtual void    updateCurrent(sf::Time dt);
private:
    sf::Vector2f    mVelocity;
    int             mHitpoints;


};


#endif // ENTITY_HPP_INCLUDED
