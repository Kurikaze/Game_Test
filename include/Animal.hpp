/***********************************************************************************
 * Animal.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Animal object. Hold AnimatedSprite for animation.
 ************************************************************************************/


#ifndef ANIMAL_HPP_INCLUDED
#define ANIMAL_HPP_INCLUDED
#include <SFML/Graphics/Rect.hpp>
#include "include/Entity.hpp"
#include "include/AnimatedSprite.hpp"
#include "include/gameTypes.hpp"
#include "include/ResourceIdentifiers.hpp"

class Animal : public Entity
{
public:
                    Animal();
                    Animal(TextureID id, const TextureHolder& textures);

    void            initialize(TextureID id, const TextureHolder& textures);
    void            setAnimation(const sf::IntRect& spriteRect, const int row, const int col, const float freq = 1);

    virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual sf::FloatRect   getBoundingRect() const;
    virtual void            drawBound(sf::RenderTarget& target, sf::RenderStates states) const;


    bool                    isJumping() const;
    void                    setJumping(bool jump);
private:
    virtual void    updateCurrent(sf::Time dt);
    AnimatedSprite  mSprite;

    bool mIsJumping;
};


#endif // ANIMAL_HPP_INCLUDED
