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
    void            processScore();

    sf::RenderWindow&   mWindow;
    sf::Text            mGameOverText;
    sf::Text            mScoreText;
    sf::Time            mElapsedTime;
    int                 mScore;

};


#endif // GAMEOVERSTATE_HPP_INCLUDED
