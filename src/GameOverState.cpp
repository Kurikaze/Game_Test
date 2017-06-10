/***********************************************************************************
 * GameOverState.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class GameOverState.
 ************************************************************************************/

#include "include/GameOverState.hpp"
#include "include/gameConstants.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

GameOverState::GameOverState(StateStack& stateStack, Context context)
    : State(stateStack, context)
    , mWindow(*context.window)
    , mGameOverText()
    , mElapsedTime(sf::Time::Zero)
    , mScore(context.playerInfo->score)
{
    //Load font
    sf::Font& font = context.fonts->get(FontID::MAIN);

    //Set GameOver Text
    mGameOverText.setString("Game Over!");
    mGameOverText.setFont(font);
    mGameOverText.setCharacterSize(60);
    mGameOverText.setOrigin(mGameOverText.getLocalBounds().width/2.f, mGameOverText.getLocalBounds().height/2.f);
    mGameOverText.setPosition(0.5f*mWindow.getView().getSize().x, 0.35f*mWindow.getView().getSize().y);


    //
    processScore();

    //Set score text
    mScoreText.setFont(font);
    mScoreText.setCharacterSize(30);
    mScoreText.setOrigin(mScoreText.getLocalBounds().width/2.f, mScoreText.getLocalBounds().height/2.f);
    mScoreText.setPosition(mGameOverText.getPosition() + sf::Vector2f(0.f, 100.f));

    //Play GameOver Theme
    context.musicPlayer->play(MusicID::GAME_OVER_THEME);
}

bool GameOverState::handleEvent(const sf::Event& event)
{
    return false;
}

bool GameOverState::update(sf::Time dt)
{
    // Show this state for 5 seconds, after that return to menu
	mElapsedTime += dt;
	if (mElapsedTime > sf::seconds(5))
	{
		requestStackClear();
		requestStackPush(StateID::MENU);
	}
	return false;
}

void GameOverState::draw()
{
    mWindow.setView(mWindow.getDefaultView());
    sf::RectangleShape backgroundShape(sf::Vector2f(getContext().window->getSize()));
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));

    mWindow.draw(backgroundShape);
    mWindow.draw(mGameOverText);
    mWindow.draw(mScoreText);

}

/////////////PRIVATE

void GameOverState::processScore()
{
    std::string name_arr[SCORE_COUNT]; //Store name of top players
    int score_arr[SCORE_COUNT]; //Store their scores

    //READ SCORES
    std::cout << "READING FILE" << std::endl;
    std::ifstream ifile;
    ifile.open("data/highscore.txt");

    if (!ifile.is_open()) //Check if file is opened
        throw std::runtime_error("Unable to open file: data/highscore.txt" );
    std::string line;

    int index = 0;
    while (!ifile.eof())
    {
        getline(ifile, line);
        std::cout << line << std::endl;
        //Convert line to string and int
        std::stringstream convert(line);
        convert >> name_arr[index] >> score_arr[index];
        index++;
    }
    ifile.close();

    //Display current score on game screen
    std::stringstream convertStr;
    convertStr << mScore;
    mScoreText.setString("Score: " + convertStr.str());

    //COMPARE SCORES AND UPDATE SCORE TEXT
    for (int i = 0; i < SCORE_COUNT; i++)
    {
        if (mScore > score_arr[i]) //If mScore larger than a score in leaderboard
        {

            //Move all lower entries down by one position
            for (int j = SCORE_COUNT - 1; j > i; j--)
            {
                name_arr[j] = name_arr[j-1];
                score_arr[j] = score_arr[j-1];
            }

            //Replace leaderboard entry by player name and score
            name_arr[i] = getContext().playerInfo->name;
            score_arr[i] = mScore;

            //Display new high score
            mScoreText.setString("New High Score: " + convertStr.str());

            break;
        }
    }



    //OUTPUT SCORES
    std::cout << "OUTPUTING FILE SCORE" << std::endl;
    std::ofstream ofile;
    ofile.open("data/highscore.txt");
    if (!ofile.is_open())
        throw std::runtime_error("Unable to open file: data/highscore.txt");
    for (int i = 0; i < SCORE_COUNT; i++)
    {
        ofile << name_arr[i] << " " << score_arr[i];
        if (i < SCORE_COUNT-1)
            ofile << "\n";
    }
    ofile.close();
}
