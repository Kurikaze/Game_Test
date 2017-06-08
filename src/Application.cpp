/***********************************************************************************
 * Application.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class Application.
 ************************************************************************************/


#include "include/Application.hpp"
#include "include/gameConstants.hpp"
#include <string>
#include <sstream>
#include <fstream>

#include "include/TitleState.hpp"
#include "include/MenuState.hpp"
#include "include/GameState.hpp"
#include "include/PauseState.hpp"
#include "include/GameOverState.hpp"
#include "include/CountDownState.hpp"
#include "include/CharactersState.hpp"
#include "include/PlayersState.hpp"
#include "include/PlayerCreationState.hpp"
#include "include/LeaderBoardState.hpp"

Application::Application()
    : mWindow(sf::VideoMode(640, 480), "APP")
    , mTextures()
    , mFonts()
    , mMusicPlayer()
    , mPlayerInfo(getNewestPlayerName("data/players.txt"), TextureID::TRAINER_000, 0)    // Get newest player name
                                                                                        // Choose default texture for player
                                                                                        // and initialize score to 0
    , mStateStack(State::Context(mWindow, mTextures, mFonts, mMusicPlayer, mPlayerInfo))
    , mStatisticsNumFrames(0)

{
    //Load textures
    mTextures.load(TextureID::TITLE_SCREEN, "media/textures/backgrounds/credits1.png");
	mTextures.load(TextureID::MENU_SCREEN, "media/textures/backgrounds/credits2.png");
	mTextures.load(TextureID::SUB_MENU_SCREEN, "media/textures/backgrounds/credits3.png");

	//Load fonts
	mFonts.load(FontID::MAIN, "media/fonts/DOSVGA.ttf");
	mFonts.load(FontID::TITLE, "media/fonts/Pokemon_Solid.ttf");

	//Load music
	mMusicPlayer.addMusic(MusicID::GAME_THEME, "media/music/021-Field04.ogg");
    mMusicPlayer.addMusic(MusicID::MENU_THEME, "media/music/Airship.ogg");
    mMusicPlayer.addMusic(MusicID::GAME_OVER_THEME, "media/music/013-Gag02.ogg");

    //Register all necessary states
	registerStates();

	//Push first state to the stack
	mStateStack.pushState(StateID::TITLE);

	//Initialize statistic text
	mStatisticsText.setFont(mFonts.get(FontID::MAIN));
	mStatisticsText.setPosition(560 - 5.f, 5.f);
	mStatisticsText.setCharacterSize(15);
}

void Application::run()
{
    sf::Clock clock;
    static sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) //MAIN LOOP OF THE GAME
    {
        sf::Time dt = clock.restart(); //dt equal elapsed time from the last frame/iteration up to this point
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TIME_PER_FRAME) //Need to call update(sf::Time t) for fixed t to avoid lags
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            processInput();
            update(TIME_PER_FRAME);

            // Check inside this loop, because stack might be empty
			if (mStateStack.isEmpty())
				mWindow.close();
        }

        updateStatistics(dt);

        render();   //Only render when all is updated
    }
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(StateID::TITLE);
    mStateStack.registerState<MenuState>(StateID::MENU);
    mStateStack.registerState<GameState>(StateID::GAME);
    mStateStack.registerState<PauseState>(StateID::PAUSE);
    mStateStack.registerState<GameOverState>(StateID::GAME_OVER);
    mStateStack.registerState<CountDownState>(StateID::COUNT_DOWN);
    mStateStack.registerState<CharactersState>(StateID::CHARACTERS);
    mStateStack.registerState<PlayersState>(StateID::PLAYERS);
    mStateStack.registerState<PlayerCreationState>(StateID::CREATE_PLAYER);
    mStateStack.registerState<LeaderboardState>(StateID::LEADERBOARD);
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();
        else
            mStateStack.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear();
    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);

    mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        //Convert mStaticsNumFrames to string
        std::stringstream convert;
        convert << mStatisticsNumFrames;
        std::string frames = convert.str();

        mStatisticsText.setString("FPS " + frames);
        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

//////////////////////////PRIVATE
std::string Application::getNewestPlayerName(std::string filename)
{
    //READ PLAYERS FROM FILE
    std::ifstream ifile;
    ifile.open(filename);

    //Check if ifile is opened
    if (!ifile.is_open())
    {
        std::ofstream ofile("data/players.txt");
        ofile << "Player";
        ofile.close();
        return "Player";
        //throw std::runtime_error("Unable to open file: " + filename);
    }
    else
    {
        std::string line;

        while (!ifile.eof())
        {
            getline(ifile, line);

        }
        //line now contains last line in the file
        ifile.close();
        return line;
    }

}

