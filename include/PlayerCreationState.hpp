/***********************************************************************************
 * PlayerCreationState.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Allow user to create new player name.
 ************************************************************************************/

#ifndef PLAYERCREATIONSTATE_HPP_INCLUDED
#define PLAYERCREATIONSTATE_HPP_INCLUDED

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "include/State.hpp"

class PlayerCreationState : public State
{
public:
                        PlayerCreationState(StateStack& stateStack, Context context);
                        ~PlayerCreationState();

    virtual bool        handleEvent(const sf::Event& event);
    virtual bool        update(sf::Time dt);
    virtual void        draw();

private:
    bool                checkValidName(int& errorCode);
    void                updateDataFile(std::string filename);

    sf::Sprite          mBackgroundSprite;
    std::string         mPlayerName;
    sf::Text            mText;
    sf::Text            mErrorText;
};

#endif // PLAYERCREATIONSTATE_HPP_INCLUDED
