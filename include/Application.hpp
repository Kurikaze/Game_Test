/***********************************************************************************
 * Application.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Connect all the parts of the game together in an application.
 ************************************************************************************/


#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <string>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "include/ResourceIdentifiers.hpp"
#include "include/gameTypes.hpp"
#include "include/State.hpp"
#include "include/StateStack.hpp"
#include "include/PlayerInfo.hpp"




class Application
{
public:
    Application();
    void run();
private:
    void registerStates();

    void processInput();
    void update(sf::Time dt);
    void render();

    void updateStatistics(sf::Time dt);
private:
    std::string         getNewestPlayerName(std::string filename); //Return name of newest player created

    sf::RenderWindow    mWindow;

    //See ResourceHolder.hpp, ResourceHolder.inl and ResourceIdentifiers.hpp for these resources
    TextureHolder       mTextures;
    FontHolder          mFonts;

    //See MusicPlayer.hpp and MusicPlayer.cpp
    MusicPlayer         mMusicPlayer;

    PlayerInfo          mPlayerInfo; //Contain player info (name, TextureID, score) (see in PlayerInfo.hpp)

    StateStack          mStateStack;

    //Contain statistic information (FPS)
    sf::Text            mStatisticsText;
    sf::Time            mStatisticsUpdateTime;
    int                 mStatisticsNumFrames;

};

#endif // APPLICATION_HPP_INCLUDED
