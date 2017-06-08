#include "include/SceneNode.hpp"
#include <algorithm>
#include <cassert>
#include "include/gameTypes.h"
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
    std::cout << "SceneNode Destroy" << std::endl;
}


void SceneNode::attachChild(UniquePtr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::UniquePtr SceneNode::dettachChild(const SceneNode& child)
{
    bool found = false;
    std::vector<UniquePtr>::iterator resultItr;
    for (std::vector<UniquePtr>::iterator itr = mChildren.begin(); itr != mChildren.end() && !found; itr++)
    {
        if (itr->get() == &child)
        {
            found = true;
            resultItr = itr;
        }
    }
    UniquePtr result = std::move(*resultItr);
    assert(found && "Could not find child SceneNode to dettach");
    result->mParent = nullptr;
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
    return sf::FloatRect(); //Meant to be implement by derived class
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
    //Command current node, if category match
    if (command.category & mCategory)
    {
        command.action(*this, dt);
    }

    //Command children
    for (const UniquePtr& child : mChildren)
    {
        child->onCommand(command, dt);
    }
}

bool SceneNode::checkCollision(SceneNode& node, std::vector<SceneNode*>& colliders) const
{
    if (this == &node) return false;
    float crashDistance = (getBoundingRect().width + node.getBoundingRect().width)/2.f;
    sf::Vector2f r = getWorldPosition() - node.getWorldPosition();
    if (sqrt(r.x*r.x + r.y*r.y) < crashDistance*0.80f) //0.80 is correction coefficient
    {
        colliders.push_back(&node);
        return true;
    }
    else
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
    // Remove all children which request so
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), [](UniquePtr& child){return child->isMarkedForRemoval();});
	mChildren.erase(wreckfieldBegin, mChildren.end());

	// Call function recursively for all remaining children
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
    //SceneNode is alive by default
    return true;
}

void SceneNode::destroy()
{
    //Do nothing
}


//////////////////////////////////////////////PRIVATE/////////////////////////

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = states.transform * getTransform(); //getTransform is a public member of sf::Transformable
    drawCurrent(target, states);
    drawChildren(target, states);
}

void    SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Draw nothing here
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
    //Update nothing here
}

void SceneNode::updateChildren(sf::Time dt)
{
    for (UniquePtr& child : mChildren)
    {
        child->update(dt);
    }
}
