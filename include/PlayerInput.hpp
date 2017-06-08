#ifndef PLAYERINPUT_HPP_INCLUDED
#define PLAYERINPUT_HPP_INCLUDED
#include <SFML/Window/Event.hpp>

class CommandQueue;
struct Command;

class PlayerInput
{
public:
    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealTimeInput(CommandQueue& commands);
};


#endif // PLAYERINPUT_HPP_INCLUDED
