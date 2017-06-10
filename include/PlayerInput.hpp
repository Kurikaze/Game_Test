/***********************************************************************************
 * PlayerInput.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Handle player input.
 ************************************************************************************/

#ifndef PLAYERINPUT_HPP_INCLUDED
#define PLAYERINPUT_HPP_INCLUDED
#include <SFML/Window/Event.hpp>

class CommandQueue;
struct Command;

class PlayerInput
{
public:
    void handleEvent(const sf::Event& event, CommandQueue& commands); //Push command to the queue based on event
    void handleRealTimeInput(CommandQueue& commands);
};


#endif // PLAYERINPUT_HPP_INCLUDED
