/***********************************************************************************
 * PauseState.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Pause the game. Triggered when press a specific key while the game is running.
 ************************************************************************************/

#ifndef PAUSESTATE_HPP_INCLUDED
#define PAUSESTATE_HPP_INCLUDED

#include <array>
#include "include/State.hpp"
#include <SFML/Graphics/Text.hpp>



class PauseState : public State
{
public:
    enum Option{RESUME = 0, QUIT_TO_MAIN_MENU, OPTION_COUNT};
public:
    PauseState(StateStack& stateStack, Context context);
    ~PauseState();

    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    update(sf::Time dt);
    virtual void    draw();

private:
    void                updateOptionText();

    sf::RenderWindow&                           mWindow;

    sf::Text                                    mPauseText;

    std::array<sf::Text, OPTION_COUNT>          mOptions;
    std::array<std::string, OPTION_COUNT>       mOptionText;
    std::size_t                                 mOptionIndex;
};

#endif // PAUSESTATE_HPP_INCLUDED
