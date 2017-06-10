/***********************************************************************************
 * SceneNode.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Display title screen of the game.
 ************************************************************************************/

#ifndef TITLESTATE_HPP_INCLUDED
#define TITLESTATE_HPP_INCLUDED

#include "include/State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>


class TitleState : public State
{

public:
    TitleState(StateStack& stateStack, Context context);


    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    update(sf::Time dt);
    virtual void    draw();

private:
    sf::Sprite  mBackgroundSprite;

    sf::Text    mTitleText;
    sf::Text    mFlashingText;

    sf::Time    mTextEffectTime;
    bool        mShowText;

};
#endif // TITLESTATE_HPP_INCLUDED
