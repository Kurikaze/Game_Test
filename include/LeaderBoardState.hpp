/***********************************************************************************
 * LeaderboardState.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Display top players with their names and scores.
 ************************************************************************************/

#ifndef LEADERBOARDSTATE_HPP_INCLUDED
#define LEADERBOARDSTATE_HPP_INCLUDED

#include <array>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "include/State.hpp"
#include "include/gameConstants.hpp"

class LeaderboardState : public State
{
public:
                        LeaderboardState(StateStack& stateStack, Context context);

    virtual bool        handleEvent(const sf::Event& event);
    virtual bool        update(sf::Time dt);
    virtual void        draw();

private:
    sf::Sprite                           mBackgroundSprite;
    std::array<sf::Text, SCORE_COUNT>    mNames;
    std::array<sf::Text, SCORE_COUNT>    mScores;

};

#endif // LEADERBOARDSTATE_HPP_INCLUDED
