/***********************************************************************************
 * MenuState.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Main menu. Provide options of the game.
 ************************************************************************************/

#ifndef MENUSTATE_HPP_INCLUDED
#define MENUSTATE_HPP_INCLUDED

#include <array>
#include <vector>
#include <string>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "include/State.hpp"



class MenuState : public State
{
public:
    enum Option{PLAY = 0, CHARACTERS, PLAYERS, CREATE_NEW_PLAYER ,LEADERBOARD, EXIT, OPTION_COUNT};
public:
    MenuState(StateStack& stateStack, Context context);

    virtual bool        handleEvent(const sf::Event& event);
    virtual bool        update(sf::Time dt);
    virtual void        draw();

private:
    void                updateOptionText();


    sf::Sprite                                  mBackgroundSprite;
    std::array<sf::Text, OPTION_COUNT>          mOptions;
    std::array<std::string, OPTION_COUNT>       mOptionText;
    int                                         mOptionIndex;

    sf::Text                                    mPlayerInfoText;

};


#endif // MENUSTATE_HPP_INCLUDED
