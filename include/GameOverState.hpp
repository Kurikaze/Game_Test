/***********************************************************************************
 * GameOverState.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Triggered when player dies.
 ************************************************************************************/

#ifndef GAMEOVERSTATE_HPP_INCLUDED
#define GAMEOVERSTATE_HPP_INCLUDED
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include "include/State.hpp"

class GameOverState : public State
{
public:
                    GameOverState(StateStack& stateStack, Context context);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    update(sf::Time dt);
    virtual void    draw();
private:
    void            processScore(); //Analyze the score (if it is high enough, put it in leaderboard)

    sf::RenderWindow&   mWindow;
    sf::Text            mGameOverText;
    sf::Text            mScoreText;
    sf::Time            mElapsedTime;
    int                 mScore;

};


#endif // GAMEOVERSTATE_HPP_INCLUDED
