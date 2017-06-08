#include "include/GameState.hpp"

GameState::GameState(StateStack& stateStack, Context context)
    : State(stateStack, context)
    , mWorld(*context.window, *context.playerInfo)
{
    //Play Game Theme
    context.musicPlayer->play(MusicID::GAME_THEME);
}



bool GameState::handleEvent(const sf::Event& event)
{
    //Escaped pressed, trigger pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(StateID::PAUSE);

    //Game input handling
    CommandQueue& commands = mWorld.accessCommandQueue();
    mPlayerInput.handleEvent(event, commands);

    return true;

}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);
    if (!mWorld.hasAlivePlayer())
    {
        (getContext().playerInfo)->score = mWorld.getScore();
        requestStackPush(StateID::GAME_OVER);
    }
    return true;
}

void GameState::draw()
{
    mWorld.draw();
}
