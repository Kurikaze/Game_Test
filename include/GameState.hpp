#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED
#include "include/State.hpp"
#include "include/GameWorld.hpp"
#include "include/PlayerInput.hpp"

class GameState : public State
{
public:
                    GameState(StateStack& stateStack, Context context);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    update(sf::Time dt);
    virtual void    draw();

private:
    GameWorld mWorld;
    PlayerInput mPlayerInput;
};


#endif // GAMESTATE_HPP_INCLUDED
