#ifndef SCENENODE_HPP_INCLUDED
#define SCENENODE_HPP_INCLUDED
#include <vector>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "include/gameTypes.h"

struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> UniquePtr;
public:
                            SceneNode();
                            ~SceneNode();

    void                    attachChild(UniquePtr child);
    UniquePtr               dettachChild(const SceneNode& child);

    void                    update(sf::Time dt);

    sf::Transform           getWorldTransform() const;
    sf::Vector2f            getWorldPosition() const; //Return absolute position of top left corner
    virtual sf::FloatRect   getBoundingRect() const;

    void                    setCategory(Category::ID id);
    unsigned int            getCategory() const;

    void                    onCommand(const Command& command, sf::Time dt);

    bool                    checkCollision(SceneNode& node, std::vector<SceneNode*>& colliders) const;
    void                    removeDeadNodes();
    bool                    isMarkedForRemoval() const;
    virtual bool            isAlive() const;
    virtual void            destroy(); //Overridden in Entity

private:
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const; //Override function in sf::Drawable
                                                                                   //states contains transforms from all parents
    virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; //Draw nothing here
    void            drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void    updateCurrent(sf::Time dt); //Update nothing here
    void            updateChildren(sf::Time dt);

private:
    std::vector<UniquePtr>  mChildren;
    SceneNode*              mParent;
    Category::ID            mCategory;
};

#endif // SCENENODE_HPP_INCLUDED
