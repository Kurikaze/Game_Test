/***********************************************************************************
 * State.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class State.
 ************************************************************************************/



#include "include/State.hpp"
#include "include/StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, MusicPlayer& music, PlayerInfo& info)
    : window(&window) //window is pointer to sf::RenderWindow, so has to put & to give address
    , textures(&textures)
    , fonts(&fonts)
    , musicPlayer(&music)
    , playerInfo(&info)
{

}



State::State(StateStack& stateStack, Context context)
    : mStack(&stateStack)
    , mContext(context)
{

}

State::~State()
{

}


void State::requestStackPush(StateID id)
{
    mStack->pushState(id);
}

void State::requestStackPop()
{
    mStack->popState();
}

void State::requestStackClear()
{
    mStack->clearStates();
}

State::Context State::getContext() const
{
    return mContext;
}

