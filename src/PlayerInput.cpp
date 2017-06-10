/***********************************************************************************
 * PlayerInput.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class PlayerInput.
 ************************************************************************************/


#include "include/PlayerInput.hpp"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include "include/Animal.hpp"
#include "include/CommandQueue.hpp"
#include "include/gameConstants.hpp"

//Utility functions

//Perform jump
void animalJump(SceneNode& node, sf::Time dt)
{
    Animal& animal = static_cast<Animal&>(node); //Need to cast to Animal to apply its functions (setVelocity(), isJumping(),...)
                                                // We need to use static_cast instead of dynamic since there is no null-reference
    if (!animal.isJumping())
    {
        animal.setVelocity(SCROLL_SPEED, -1*JUMP_SPEED);
        std::cout << "JUMP" << std::endl;
        animal.setJumping(true);
    }
    else std::cout <<"NOT JUMP" << std::endl;
}



/////////
void PlayerInput::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space) //If player trigger jump
        {
            Command command;
            command.category = Category::PLAYER_ANIMAL;
            command.action = animalJump;

            commands.push(command);
        }

    }
}

void PlayerInput::handleRealTimeInput(CommandQueue& commands)
{
    //Will develop this in future (hope so)
}
