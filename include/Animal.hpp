#ifndef ANIMAL_HPP_INCLUDED
#define ANIMAL_HPP_INCLUDED
#include <SFML/Graphics/Rect.hpp>
#include "include/Entity.hpp"
#include "include/AnimatedSprite.hpp"
#include "include/gameTypes.h"
#include "include/ResourceIdentifiers.hpp"

class Animal : public Entity
{
public:
                    Animal();
                    Animal(TextureID id, const TextureHolder& textures);
    void            initialize(TextureID id, const TextureHolder& textures);
    void            setAnimation(const sf::IntRect& spriteRect, const int row, const int col, const float freq = 1);

    virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; // Is not declared as const
                                                                                    // since it modifies mSprite.setTextureRect()
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
