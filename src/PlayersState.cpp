/***********************************************************************************
 * PlayersState.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class PlayersState.
 ************************************************************************************/


#include "include/PlayersState.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <fstream>

#define TEXT_SIZE 30.f
#define TEXT_SPACE 10.f

PlayersState::PlayersState(StateStack& stateStack, Context context)
    : State(stateStack, context)
    , mPlayerCount(0)
    , mOptionIndex(0)
    , mLowerIndex(0)
    , mUpperIndex(9)

{
    mBackgroundSprite.setTexture(context.textures->get(TextureID::SUB_MENU_SCREEN));
    mBackgroundSprite.scale(640.f/512, 480.f/384); //Equal size of window/size of background image

    sf::Font& font = context.fonts->get(FontID::MAIN);

    loadPlayers("data/players.txt");

    mTitleText.setFont(font);
    mTitleText.setString("Choose player");
    mTitleText.setOrigin(mTitleText.getLocalBounds().width/2.f, mTitleText.getLocalBounds().height/2.f);
    mTitleText.setCharacterSize(1.33f*TEXT_SIZE);
    mTitleText.setPosition(context.window->getView().getSize().x/2.f, 10.f);

    for (std::size_t i = 0; i < mPlayerNames.size(); i++)
    {
        sf::Text playerText;
        playerText.setFont(font);
        playerText.setString(mPlayerNames[i]);
        playerText.setCharacterSize(TEXT_SIZE);
        playerText.setOrigin(playerText.getLocalBounds().width/2.f, playerText.getLocalBounds().height/2.f);
        playerText.setPosition(context.window->getView().getSize().x/2.f, 90.f + i*(TEXT_SIZE + TEXT_SPACE));
        mOptions.push_back(playerText);
    }


    updateOptionText();

}

bool PlayersState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;
    if (event.key.code == sf::Keyboard::Up) //Move cursor to previous entry
    {
        if (mOptionIndex > 0)
            mOptionIndex--;


        //If selected text lies outside view, move the list downwards
        if (mOptionIndex < mLowerIndex)
        {
            moveOptionText(0.f, (mLowerIndex - mOptionIndex)*(TEXT_SIZE + TEXT_SPACE));
            mLowerIndex = mOptionIndex;
            mUpperIndex -= 1;
        }

        updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Down) //Move cursor to next entry
    {
        if (mOptionIndex <= mPlayerCount - 2)
            mOptionIndex ++;

        //If selected text lies outside view, move the list upwards
        if (mOptionIndex > mUpperIndex)
        {
            moveOptionText(0.f, (-1.f)*(mOptionIndex - mUpperIndex)*(TEXT_SIZE + TEXT_SPACE));
            mUpperIndex = mOptionIndex;
            mLowerIndex += 1;
        }


        updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Return) //Select current entry
    {
        getContext().playerInfo->name = mPlayerNames[mOptionIndex];
        requestStackPop();
    }
    else if (event.key.code == sf::Keyboard::Escape) //Escape pressed, return to menu.
    {
        requestStackPop();
    }


    return false;
}

bool PlayersState::update(sf::Time dt)
{


    return false;
}

void PlayersState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);

    window.draw(mTitleText);

    for (int i = 0; i < mPlayerCount; i++)
    {
        window.draw(mOptions[i]);
    }

}


///////////////////PRIVATE
void PlayersState::loadPlayers(std::string filename)
{
    //READ PLAYERS FROM FILE
    std::ifstream ifile;
    ifile.open(filename);
    if (!ifile.is_open())
        throw std::runtime_error("Unable to open file: " + filename);
    std::string line;

    while (!ifile.eof())
    {
        getline(ifile, line);
        mPlayerNames.push_back(line);
        mPlayerCount++;
    }
    ifile.close();
}

void PlayersState::updateOptionText()
{
     //White all text

    for (int i = 0; i < mPlayerCount; i++)
    {
        if (i >= mLowerIndex && i <= mUpperIndex) //If text inside view
            mOptions[i].setFillColor(sf::Color::Blue);
        else
            mOptions[i].setFillColor(sf::Color::Transparent);

    }

    //Red selected text
    mOptions[mOptionIndex].setFillColor(sf::Color::Red);



}

void PlayersState::moveOptionText(float dx, float dy)
{
    for (int i = 0; i < mPlayerCount; i++)
    {
        mOptions[i].move(dx, dy);
    }
}

