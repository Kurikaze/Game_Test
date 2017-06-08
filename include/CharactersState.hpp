

#ifndef CHARACTERSSTATE_HPP_INCLUDED
#define CHARACTERSSTATE_HPP_INCLUDED

#include <array>
#include "include/State.hpp"
#include "include/ResourceIdentifiers.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


#define CHARACTERS_NUM 15
#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 128
#define ROW_NUM 3
#define COL_NUM 5

class CharactersState : public State
{
public:
    CharactersState(StateStack& stateStack, Context context);

    virtual bool        handleEvent(const sf::Event& event);
    virtual bool        update(sf::Time dt);
    virtual void        draw();
private:
    void                loadTextures();
    void                buildScene();
    int                 getIndex(TextureID id); //Return index in mCharacterTextureID


    sf::RenderWindow&                           mWindow;
    PlayerInfo&                                 mPlayerInfo;
    std::array<TextureID, CHARACTERS_NUM>       mCharacterTextureID;
    TextureHolder                               mTextures; //This is different from the textures of GameWorld,
                                                          //although using same textureID (Trainer_000 - 066)

    sf::Sprite                                  mBackgroundSprite;
    std::array<sf::Sprite, CHARACTERS_NUM>      mCharacterSprites;
    sf::Text                                    mTitleText;
    sf::RectangleShape                          mSelectShape;
    sf::RectangleShape                          mSelectedShape;

    sf::Time                                    mElapsedTime;

    std::size_t                                 mRow;
    std::size_t                                 mCol;
};


#endif // CHOOSINGSTATE_HPP_INCLUDED
