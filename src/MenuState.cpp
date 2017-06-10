/***********************************************************************************
 * MenuState.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class MenuState.
 ************************************************************************************/


#include "include/MenuState.hpp"
#include "include/StateStack.hpp"

#define TEXT_SIZE 33.f
#define TEXT_SPACE 10.f


MenuState::MenuState(StateStack& stateStack, Context context)
    : State(stateStack, context)
    , mOptions()
    , mOptionText{"Play", "Characters", "Choose player", "Create new player", "Leaderboard", "Exit"}
    , mOptionIndex(0)

{
    //Load background texture
    sf::Texture& bgrTexture = context.textures->get(TextureID::MENU_SCREEN);
    mBackgroundSprite.setTexture(bgrTexture);
    mBackgroundSprite.scale(640.f/512, 480.f/384); //Scale coefficient =  (size of window)/(size of background image)

    //Create all Option text
    sf::Font& font = context.fonts->get(FontID::MAIN);
    for (int i = 0; i < OPTION_COUNT; i++)
    {

        mOptions[i].setFont(font);
        mOptions[i].setString(mOptionText[i]);
        mOptions[i].setCharacterSize(TEXT_SIZE);
        mOptions[i].setOrigin(mOptions[i].getLocalBounds().width/2.f, mOptions[i].getLocalBounds().height/2.f);
        sf::Vector2f textPos = context.window->getView().getSize()/2.f;
        textPos.y = textPos.y - 0.5f*((TEXT_SIZE + TEXT_SPACE)*(OPTION_COUNT-1)) + i*(TEXT_SIZE + TEXT_SPACE);
        mOptions[i].setPosition(textPos);
    }


    updateOptionText();

    //Create player info text
    mPlayerInfoText.setFont(font);
    mPlayerInfoText.setString("You're logged in as: " + context.playerInfo->name);
    mPlayerInfoText.setPosition(5.f, 5.f);
    mPlayerInfoText.setCharacterSize(15.f);

    //Play Menu Theme
    context.musicPlayer->play(MusicID::MENU_THEME);
}

bool MenuState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;
    if (event.key.code == sf::Keyboard::Up) //Point to previous option. If goes beyond top of the list, return to the bottom
    {
        if (mOptionIndex > 0)
            mOptionIndex--;
        else
            mOptionIndex = OPTION_COUNT - 1;

        updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Down) //Point to next option. If goes beyond bottom of the list, return to the top
    {
        if (mOptionIndex <= OPTION_COUNT - 2)
            mOptionIndex ++;
        else
            mOptionIndex = 0;

        updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Return) //Option chosen. Trigger corresponding state.
    {
        if (mOptionIndex == PLAY)
        {
            requestStackPop();
            requestStackPush(StateID::GAME);
        }
        else if (mOptionIndex == CHARACTERS)
        {
            requestStackPush(StateID::CHARACTERS);
        }
        else if (mOptionIndex == PLAYERS)
        {
            requestStackPush(StateID::PLAYERS);
        }
        else if (mOptionIndex == CREATE_NEW_PLAYER)
        {
            requestStackPush(StateID::CREATE_PLAYER);
        }
        else if (mOptionIndex == LEADERBOARD)
        {
            requestStackPush(StateID::LEADERBOARD);
        }
        else if (mOptionIndex == EXIT)
        {
            requestStackClear();
        }

    }
    return true;
}

bool MenuState::update(sf::Time dt)
{
    mPlayerInfoText.setString("You're logged in as: " + getContext().playerInfo->name);
    return true;
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);

    for (int i = 0; i < OPTION_COUNT; i++)
    {
        window.draw(mOptions[i]);
    }

    window.draw(mPlayerInfoText);
}


//////////////////PRIVATE

void MenuState::updateOptionText()
{
    //White all text
    for (int i = 0; i < OPTION_COUNT; i++)
    {
        mOptions[i].setFillColor(sf::Color::White);
    }

    //Red selected text
    mOptions[mOptionIndex].setFillColor(sf::Color::Red);

}

