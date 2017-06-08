#include "include/PlayerInput.hpp"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include "include/Animal.hpp"
#include "include/CommandQueue.hpp"
#include "include/gameConstants.hpp"

//Utility functions
void animalJump(SceneNode& node, sf::Time dt)
{
    Animal& animal = static_cast<Animal&>(node);
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
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space)
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

}
