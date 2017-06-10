/***********************************************************************************
 * Object.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Derived from Entity. Used for holding sf::Sprite
 ************************************************************************************/

#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED
#include "include/Entity.hpp"

class Object : public Entity
{
public:
                            Object();
                            Object(const sf::Texture& texture);
                            Object(const sf::Texture& texture, const sf::IntRect& textureRect);

    void                    initialize(const sf::Texture& texture, const sf::IntRect& textureRect);
    void                    setTexture(const sf::Texture& texture);
    void                    setTexture(const sf::Texture& texture, const sf::IntRect& textureRect);

    //Override the corresponding functions in SceneNode
    virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual sf::FloatRect   getBoundingRect() const;
    virtual void            drawBound(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    virtual void            updateCurrent(sf::Time dt);

    sf::Sprite  mSprite;
};

#endif // OBJECT_HPP_INCLUDED
