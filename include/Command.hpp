/***********************************************************************************
 * Command.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Hold information of a command (which categories and actions to apply)
 ************************************************************************************/

#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED
#include <functional>
#include <SFML/System/Time.hpp>
#include "include/gameTypes.hpp"

class SceneNode;

struct Command
{
    typedef std::function<void(SceneNode&, sf::Time)> Action;

    unsigned int category;
    Action action;
};


#endif // COMMAND_HPP_INCLUDED
