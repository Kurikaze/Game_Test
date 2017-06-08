#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED
#include <functional>
#include <SFML/System/Time.hpp>
#include "include/gameTypes.h"

class SceneNode;

struct Command
{
    typedef std::function<void(SceneNode&, sf::Time)> Action;

    unsigned int category;
    Action action;
};


#endif // COMMAND_HPP_INCLUDED
