/***********************************************************************************
 * StateStack.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Stack structure to hold and manage all the states of the game.
 ************************************************************************************/




#ifndef STATESTACK_HPP_INCLUDED
#define STATESTACK_HPP_INCLUDED
#include <functional>
#include <map>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include "include/State.hpp"
#include "include/gameTypes.hpp"

class StateStack
{
public:
    enum Action{PUSH, POP, CLEAR}; //Used in struct PendingChange (see below)
public:
    explicit         StateStack(State::Context context);

    void             handleEvent(const sf::Event& event); //Call member function handleEvent() for each state in mStack as long as it returns true
    void             update(sf::Time dt); //Call member function update() for each state in mStack as long as it returns true
    void             draw(); //Call member function update() for each state in mStack


    template <typename T>
    void             registerState(StateID id); //Register functor in mFactories to create State later

    void             pushState(StateID id); //Push struct PendingChange containing action PUSH to mPendingList
    void             popState(); //Push struct PendingChange containing action POP to mPendingList
    void             clearStates(); //Push struct PendingChange containing action CLEAR to mPendingList

    bool             isEmpty() const;   //Return true if mStack is empty

private:

    State::UniquePtr createState(StateID id); //Used in function applyPendingChanges()
    void             applyPendingChanges(); //Apply all changes in mPendingList

private:
    struct PendingChange
    {
        explicit PendingChange(Action action, StateID id = StateID::NONE);
        Action action; //See Action enum type above
        StateID stateID;    //StateID to apply changes on
    };


    std::vector<State::UniquePtr>                           mStack;     //Hold unique pointers to allocated State objects (after pushed to the stack)
    State::Context                                          mContext;   //Value is struct Context (containing pointers to window, textures, fonts...) (see in State.hpp)

    std::map<StateID, std::function<State::UniquePtr()>>    mFactories; //Hold pairs of stateID and functor to create allocated State objects
    std::vector<PendingChange>                              mPendingList; //Hold list of pending commands for stack (in form of struct PendingChange)
};


template <typename T>
void StateStack::registerState(StateID id)
{
    mFactories[id] = [this]() //This is the lambda expression (serving as function that return State::UniquePtr)
    {
        return State::UniquePtr(new T(*this, mContext));
    };
}

#endif // STATESTACK_HPP_INCLUDED
