/***********************************************************************************
 * SceneNode.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class SceneNode.
 ************************************************************************************/


#include "include/SceneNode.hpp"
#include <algorithm>
#include <cassert>
#include "include/gameTypes.hpp"
#include "include/Command.hpp"

#include <iostream>

SceneNode::SceneNode()
    : mChildren()
    , mParent(nullptr)
    , mCategory(Category::SCENE)
{

}

SceneNode::~SceneNode()
{
    std::cout << "SceneNode Destroy" << std::endl; //Used for debugging
}


void SceneNode::attachChild(UniquePtr child)
{
    //Add this node as the child's parent
    child->mParent = this;

    //Add child to mChildren vector
    mChildren.push_back(std::move(child));
}

SceneNode::UniquePtr SceneNode::dettachChild(const SceneNode& child)
{
    bool found = false;
    std::vector<UniquePtr>::iterator resultItr; //Hold index to founded child

    //Search in mChildren for matching child until found
    for (std::vector<UniquePtr>::iterator itr = mChildren.begin(); itr != mChildren.end() && !found; itr++)
    {
        if (itr->get() == &child)
        {
            found = true;
            resultItr = itr;
        }
    }
    UniquePtr result = std::move(*resultItr);

    //Check if child could be found
    assert(found && "Could not find child SceneNode to dettach");

    //Set parent of that child to null pointer
    result->mParent = nullptr;

    //Removed child from mChildren
    mChildren.erase(resultItr);

    return result;
}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform totalTransform = sf::Transform::Identity;
    //Get transformations from this node's parent, grandparent, greatgrandparent...
    //The results are multiplied to get total transformation
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		totalTransform = node->getTransform() * totalTransform;

	return totalTransform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::FloatRect SceneNode::getBoundingRect() const
{
    return sf::FloatRect(); //Need to be implemented by derived class
}

void SceneNode::setCategory(Category::ID id)
{
    mCategory = id;
}

unsigned int SceneNode::getCategory() const
{
    return mCategory;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
    //Apply command current node, if category match
    if (command.category & mCategory)
    {
        command.action(*this, dt);
    }

    //Apply command on children
    for (const UniquePtr& child : mChildren)
    {
        child->onCommand(command, dt);
    }
}

bool SceneNode::checkCollision(SceneNode& node, std::vector<SceneNode*>& colliders) const
{
    if (this == &node) return false; //Nodes cannot collide with themselves

    float crashDistance = (getBoundingRect().width + node.getBoundingRect().width)/2.f; //Smallest allowed distance

    sf::Vector2f r = getWorldPosition() - node.getWorldPosition(); //Vector from *this to node

    if (sqrt(r.x*r.x + r.y*r.y) < crashDistance*0.80f) //If distance between to nodes is smaller than allowed distance
                                                        //(0.80 is correction coefficient to reduce hitbox)
    {
        colliders.push_back(&node); //Add node to colliders
        return true;
    }
    else    //Only check children if their parents are not collided
    {
        for (UniquePtr& child : node.mChildren)
        {
            if (checkCollision(*child, colliders)) return true;
        }
    }
    return false;

}

void SceneNode::removeDeadNodes()
{
    // Remove all children who are marked for removal
    //std::remove_if(...) shifts all children that are marked for removal to the end of vector
    //removeIndex equals the index of the first element needed to be removed (in the new range)
	auto removeIndex = std::remove_if(mChildren.begin(), mChildren.end(), [](UniquePtr& child){return child->isMarkedForRemoval();});

	//Remove these children from vector
	mChildren.erase(removeIndex, mChildren.end());

	// Call function recursively for all remaining children (who are not removed)
	for (std::vector<UniquePtr>::iterator itr = mChildren.begin(); itr != mChildren.end() ; itr++)
    {
        (*itr)->removeDeadNodes();
    }
}

bool SceneNode::isMarkedForRemoval() const
{
    return !isAlive();
}


bool SceneNode::isAlive() const
{
    //SceneNode is alive by default (will be overridden in derived class)
    return true;
}

void SceneNode::destroy()
{
    //Do nothing by default (will be overridden in derived class)
}


//////////////////////////////////////////////PRIVATE/////////////////////////

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = states.transform * getTransform(); //getTransform() is a public member of sf::Transformable
                                                          //We don't call getWorldTransform() because the transforms
                                                          //of parents, grandparents... are already included in states.transform
    drawCurrent(target, states);
    drawChildren(target, states);
}

void    SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Draw nothing here by default (will be overridden in derived class)
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const UniquePtr& child : mChildren)
    {
        child->draw(target, states);
    }
}


void    SceneNode::updateCurrent(sf::Time dt)
{
    //Update nothing here by default (will be overridden in derived class)
}

void SceneNode::updateChildren(sf::Time dt)
{
    for (UniquePtr& child : mChildren)
    {
        child->update(dt);
    }
}
