/***********************************************************************************
 * SceneNode.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Provide interface for interactions between objects in the GameWorld.
 ************************************************************************************/



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
#include "include/gameTypes.hpp"

struct Command; //Forward declaration

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> UniquePtr;
public:
                            SceneNode();
                            ~SceneNode();

    void                    attachChild(UniquePtr child);   //Add new child to mChildren
    UniquePtr               dettachChild(const SceneNode& child);   //Remove and return child from mChildren

    void                    update(sf::Time dt); //Apply update to this node and all of its children

    sf::Transform           getWorldTransform() const;  //Get total transform of this node
    sf::Vector2f            getWorldPosition() const; //Return absolute (global) position of top left corner (in forms of a vector)
    virtual sf::FloatRect   getBoundingRect() const; //Get the smallest rectangle that bounds the object

    void                    setCategory(Category::ID id); //Set category id for this node
                                                          //(Category::ID is defined in gameTypes.hpp)
    unsigned int            getCategory() const; //Get category id for this node

    void                    onCommand(const Command& command, sf::Time dt); //Apply command on this node and all of its children
                                                                            //(if their categories match)

    bool                    checkCollision(SceneNode& node, std::vector<SceneNode*>& colliders) const; //Return true if *this collides with node and node's children (and false otherwise)
                                                                                                        //All the nodes who collide with *this are added to vector colliders

    void                    removeDeadNodes(); //Remove all nodes that are marked for removal
    bool                    isMarkedForRemoval() const; //Return true if node is dead (not alive)
    virtual bool            isAlive() const; //Return true by default (will be overridden in derived class to return true if this node is alive)
    virtual void            destroy(); //Overridden in derived class

private:
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const; //Override the function in sf::Drawable
                                                                                   //states contains transforms from all parents
    virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; //Draw nothing here by default (will be overridden in derived class)
    void            drawChildren(sf::RenderTarget& target, sf::RenderStates states) const; //Apply draw() to all children

    virtual void    updateCurrent(sf::Time dt); //Update nothing here by default (will be overridden in derived class)
    void            updateChildren(sf::Time dt); //Apply update() to all children

private:
    std::vector<UniquePtr>  mChildren; //Contains unique pointers to children (if these pointers are destroyed, the children they point to are also deleted)
    SceneNode*              mParent; //Hold pointer to this node's parents
    Category::ID            mCategory; //Hold category id of this node
};

#endif // SCENENODE_HPP_INCLUDED
