/***********************************************************************************
 * gameConstants.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Include all the constants of the game.
 ************************************************************************************/

#ifndef GAMECONSTANTS_HPP_INCLUDED
#define GAMECONSTANTS_HPP_INCLUDED

const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);
const float SCROLL_SPEED = 220.f; //In pixels per second
const float JUMP_SPEED = 800.f; //In pixel per second
const float g = 26.f; //Vertical acceleration - In pixel per second square (pixels/s^2)
const float gx = 8.f; //Horizontal acceleration - In pixel per second square (pixels/s^2)
const float ANIMATION_FREQ = 1; //Numbers of animations per frame
const int   BGR_MULTIPLIER = 4; //Background multiplier for game world bounds
const int   MAX_HP = 3; //Maximum player's hitpoint
const int   SCORE_COUNT = 5; //Hold numbers of score allowed in leaderboard

#endif // GAMECONSTANTS_HPP_INCLUDED
