/***********************************************************************************
 * StateStack.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for StateStack.hpp
 ************************************************************************************/

#include "include/StateStack.hpp"
#include <cassert>


StateStack::StateStack(State::Context context)
    : mStack()
    , mContext(context)
    , mFactories()
    , mPendingList()
{

}

void StateStack::handleEvent(const sf::Event& event)
{
    //Iterate from top to bottom, stop as soon as handleEvent() returns false
    for (auto i = mStack.rbegin(); i != mStack.rend(); i++)
    {
        if (!(*i)->handleEvent(event))
            break;
    }
    applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
    //Iterate from top to bottom, stop as soon as update() returns false
    for (auto i = mStack.rbegin(); i != mStack.rend(); i++)
    {
        if (!(*i)->update(dt))
            break;
    }
    applyPendingChanges();
}

void StateStack::draw()
{
    //Iterate from bottom to top and call draw() for each state
    for (auto i = mStack.begin(); i != mStack.end(); i++)
    {
        (*i)->draw();
    }
}



void StateStack::pushState(StateID id)
{
    mPendingList.push_back(PendingChange(PUSH, id));
}

void StateStack::popState()
{
    mPendingList.push_back(PendingChange(POP));
}

void StateStack::clearStates()
{
    mPendingList.push_back(PendingChange(CLEAR));
}

bool StateStack::isEmpty() const
{
    //Return true if stack is empty
    return mStack.empty();
}

State::UniquePtr StateStack::createState(StateID id)
{
    //Find the pair in mFactories whose index (of type StateID) matches the value of id
    auto found = mFactories.find(id);

    //Check if the pair could be found (only for debugging - not included in release version)
    assert(found != mFactories.end() && "StateID cannot be found");

    //If found, return second component of the pair, which of type std::function<State::UniquePtr()>
    //This functor must be created first by calling registerState< -example- MenuState->(StateID) at the beginning of the game
    return (found->second());

}

void StateStack::applyPendingChanges()
{
    //Iterate mPendingList from bottom to top (apply oldest commands first)
    for (auto i = mPendingList.begin(); i != mPendingList.end(); i++)
    {
        switch (i->action)
        {
        case PUSH:
            mStack.push_back(createState(i->stateID)); //Get the function to create state for the StateID from createState(StateID)
                                                        //Receive State::UniquePtr from the function and push to mStack
            break;
        case POP:
            mStack.pop_back();  //Pop the latest state off mStack (deleting the memory by destroying the State::UniquePtr)
            break;
        case CLEAR:
            mStack.clear(); //Clear/Pop all states off mStack
            break;
        default:
            break;
        }
    }

    mPendingList.clear();
}


///Constructor for struct PendingChange
StateStack::PendingChange::PendingChange(Action action, StateID id)
    : action(action)
    , stateID(id)
{

}
