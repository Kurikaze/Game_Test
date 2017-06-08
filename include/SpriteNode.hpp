#ifndef SPRITENODE_HPP_INCLUDED
#define SPRITENODE_HPP_INCLUDED
#include "include/SceneNode.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Rect.hpp>

class SpriteNode : public SceneNode
{
public:
                    SpriteNode();
                    SpriteNode(const sf::Texture& texture);
                    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
    void            initialize(const sf::Texture& texture, const sf::IntRect& textureRect);
    virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite mSprite;
};

#endif // SPRITENODE_HPP_INCLUDED
