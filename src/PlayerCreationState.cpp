/***********************************************************************************
 * PlayerCreationState.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class PlayerCreationState.
 ************************************************************************************/



#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include "include/PlayerCreationState.hpp"

#define MAX_NAME_LENGTH 10
#define EMPTY_NAME 0
#define NAME_TOO_LONG 1
#define FIRST_CHAR_IS_NUM 2
#define DUPLICATE_NAME 3

PlayerCreationState::PlayerCreationState(StateStack& stateStack, Context context)
    : State(stateStack, context)
{
    mBackgroundSprite.setTexture(context.textures->get(TextureID::SUB_MENU_SCREEN));
    mBackgroundSprite.scale(640.f/512, 480.f/384); //Equal size of window/size of background image

    sf::Vector2f viewSize(context.window->getView().getSize());

    mText.setString("");
    mText.setFont(context.fonts->get(FontID::MAIN));
    mText.setCharacterSize(30);
    mText.setPosition(10.f, viewSize.y/2.f - 60);

    mErrorText.setString("");
    mErrorText.setFont(context.fonts->get(FontID::MAIN));
    mErrorText.setFillColor(sf::Color::Transparent);
    mErrorText.setCharacterSize(20);
    mErrorText.setPosition(10.f, viewSize.y/2.f + 30.f);
}

PlayerCreationState::~PlayerCreationState()
{


}



bool PlayerCreationState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode == 27) //Escape pressed, return to menu.
        {
            requestStackPop();
        }
        else if (event.text.unicode == 8 || event.text.unicode == 127) //Backspace is pressed, delete previous character.
        {
            if (mPlayerName.length() > 0)
                mPlayerName.pop_back();

        }

        else if (event.text.unicode < 128 && event.text.unicode >= 33) //Normal character
        {
            char c = static_cast<char>(event.text.unicode);
            std::cout << "ASCII character typed: " << c << std::endl;
            mPlayerName.push_back(c);

        }

    }
    else if (event.type == sf::Event::KeyPressed) //Name entered
    {
        if (event.key.code == sf::Keyboard::Return)
        {
            int errorCode;
            if (!checkValidName(errorCode))
            {
                switch (errorCode)
                {
                case EMPTY_NAME:
                    mErrorText.setString("Invalid name!");
                    break;
                case NAME_TOO_LONG:
                    mErrorText.setString("Name is too long!");
                    break;
                case FIRST_CHAR_IS_NUM:
                    mErrorText.setString("The first character must not be a number!");
                    break;
                case DUPLICATE_NAME:
                    mErrorText.setString("This username already exists!");
                    break;
                }
                std::cout << "Invalid name" << std::endl;
                mErrorText.setFillColor(sf::Color::Red);
            }
            else //If no errors
            {
                std::cout << "Name is: " << mPlayerName << std::endl;

                getContext().playerInfo->name = mPlayerName;
                updateDataFile("data/players.txt");

                requestStackPop();
            }

        }


    }

    return false;
}

bool PlayerCreationState::update(sf::Time dt)
{
    mText.setString("Enter name: " + mPlayerName + "\n(Less than 10 characters/numbers \nand contain no space)");
    return false;
}

void PlayerCreationState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mText);
    window.draw(mErrorText);
}

///////////////////PRIVATE
bool PlayerCreationState::checkValidName(int& errorCode)
{
    //CHECK VALIDITY
    if (mPlayerName.empty())
    {
        errorCode = EMPTY_NAME;
        return false;
    }
    else if (mPlayerName.length() > MAX_NAME_LENGTH)
    {
        errorCode = NAME_TOO_LONG;
        return false;
    }
    else if (isdigit(mPlayerName.at(0)))
    {
        errorCode = FIRST_CHAR_IS_NUM;
        return false;
    }

    //CHECK DUPLICATE
    std::ifstream ifile;
    ifile.open("data/players.txt");
    if (!ifile.is_open())
        throw std::runtime_error("Unable to open file: data/players.txt");
    std::string line;
    std::string name;

    while (!ifile.eof())
    {
        //Get names from file
        getline(ifile, line);

        std::stringstream convert(line);
        convert >> name;

        if (name == mPlayerName)
        {
            errorCode = DUPLICATE_NAME;
            return false;
        }

        name = "";
    }
    ifile.close();
    return true;
}


void PlayerCreationState::updateDataFile(std::string filename)
{
    if (!mPlayerName.empty())
    {
        std::ofstream ofile;
        ofile.open(filename, std::ios::out | std::ios::app);
        if (!ofile.is_open())
            throw std::runtime_error("Unable to open file: " + filename);

        ofile << "\n" << mPlayerName;

        ofile.close();
    }

}
