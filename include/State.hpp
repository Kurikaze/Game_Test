/***********************************************************************************
 * State.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Base abstract class for different states of the game (CharacterState, PauseState
 * GameOverState, GameState, MenuState..., these are all derived from this class).
 ************************************************************************************/


#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED
#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "include/ResourceIdentifiers.hpp"
#include "include/gameTypes.hpp"
#include "include/PlayerInfo.hpp"
#include "include/MusicPlayer.hpp"


class StateStack;


///This class is an abstract class
class State
{
public:
    typedef std::unique_ptr<State> UniquePtr;

    struct Context //Hold pointer to window, player info and resources so that every states could access them
    {
        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, MusicPlayer& music, PlayerInfo& info);
        sf::RenderWindow*   window;
        TextureHolder*      textures;
        FontHolder*         fonts;
        MusicPlayer*        musicPlayer;
        PlayerInfo*         playerInfo;

    };


public:
                    State(StateStack& stateStack, Context context);
    virtual         ~State();

    virtual bool    handleEvent(const sf::Event& event) = 0; //Return true to let lower states in the stack call handleEvent()
    virtual bool    update(sf::Time dt) = 0; //Return true to let updates through lower state in the stack
    virtual void    draw() = 0; //Does not return boolean value since every states need to be drawn

protected:

    void            requestStackPush(StateID id); //Push state corresponding to id on the state stack
    void            requestStackPop();  //Pop the top state from state stack
    void            requestStackClear(); //Clear all states on stack

    Context         getContext() const;

private:
    StateStack*     mStack;
    Context         mContext;


};


#endif // STATE_HPP_INCLUDED
