/***********************************************************************************
 * CharactersState.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class CharactersState.
 ************************************************************************************/


#include "include/CharactersState.hpp"
#include <SFML/Graphics/Font.hpp>

CharactersState::CharactersState(StateStack& stateStack, Context context)
    : State(stateStack, context)
    , mWindow(*context.window)
    , mPlayerInfo(*context.playerInfo)
    , mCharacterTextureID{
        TextureID::TRAINER_000,
        TextureID::TRAINER_001,
        TextureID::TRAINER_002,
        TextureID::TRAINER_003,
        TextureID::TRAINER_004,
        TextureID::TRAINER_011,
        TextureID::TRAINER_015,
        TextureID::TRAINER_016,
        TextureID::TRAINER_017,
        TextureID::TRAINER_018,
        TextureID::TRAINER_024,
        TextureID::TRAINER_027,
        TextureID::TRAINER_031,
        TextureID::TRAINER_038,
        TextureID::TRAINER_066
    }
    , mTextures()
    , mRow(0)
    , mCol(0)

{
    mBackgroundSprite.setTexture(context.textures->get(TextureID::SUB_MENU_SCREEN));
    mBackgroundSprite.scale(640.f/512, 480.f/384); //Equal size of window/size of background image

    sf::Font& font = context.fonts->get(FontID::MAIN);

    mTitleText.setString("Choose Character");
    mTitleText.setFont(font);
    mTitleText.setCharacterSize(40);
    mTitleText.setOrigin(mTitleText.getLocalBounds().width/2.f, mTitleText.getLocalBounds().height/2.f);
    mTitleText.setPosition(0.5f*mWindow.getView().getSize().x, 10.f);


    loadTextures();
    buildScene();

    sf::FloatRect bounds = mCharacterSprites[0].getGlobalBounds();
    mSelectShape.setSize(sf::Vector2f(bounds.width, bounds.height));
    mSelectShape.setFillColor(sf::Color(0,0,0,0));
    mSelectShape.setOutlineColor(sf::Color::White);
    mSelectShape.setOutlineThickness(3);
    mSelectShape.setPosition(bounds.left + 5.f, bounds.top + 5.f);


    mSelectedShape.setSize(sf::Vector2f(bounds.width, bounds.height));
    mSelectedShape.setFillColor(sf::Color(0,0,0,0));
    mSelectedShape.setOutlineColor(sf::Color::Red);
    mSelectedShape.setOutlineThickness(3);
    int index = getIndex(mPlayerInfo.textureID);
    int row_index = static_cast<int>(index / COL_NUM);
    int col_index = static_cast<int>(index % COL_NUM);
    mSelectedShape.setPosition(bounds.left + col_index*IMAGE_WIDTH, bounds.top + row_index*IMAGE_HEIGHT);

}

bool CharactersState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;
    if (event.key.code == sf::Keyboard::Up)
    {
        if (mRow > 0)
            mRow--;
        else
            mRow = ROW_NUM - 1;

    }
    else if (event.key.code == sf::Keyboard::Down)
    {
        if (mRow <= ROW_NUM - 2)
            mRow ++;
        else
            mRow = 0;

    }
    else if (event.key.code == sf::Keyboard::Left)
    {
        if (mCol > 0)
            mCol--;
        else
            mCol = COL_NUM - 1;
    }
    else if (event.key.code == sf::Keyboard::Right)
    {
        if (mCol <= COL_NUM - 2)
            mCol ++;
        else
            mCol = 0;

    }
    else if (event.key.code == sf::Keyboard::Return)
    {
        std::size_t index = mRow*COL_NUM + mCol;
        mPlayerInfo.textureID = mCharacterTextureID[index];
        requestStackPop();
    }
    else if (event.key.code == sf::Keyboard::Escape)
    {
        requestStackPop();
    }
    return false;
}

bool CharactersState::update(sf::Time dt)
{
    sf::FloatRect bounds = mCharacterSprites[0].getGlobalBounds();
    mSelectShape.setPosition(bounds.left + mCol*IMAGE_WIDTH, bounds.top + mRow*IMAGE_HEIGHT);
    return false;
}

void CharactersState::draw()
{
    mWindow.setView(mWindow.getDefaultView());

    mWindow.draw(mBackgroundSprite);
    mWindow.draw(mTitleText);

    for (std::size_t i = 0; i < CHARACTERS_NUM; i++)
    {
        mWindow.draw(mCharacterSprites[i]);
    }

    mWindow.draw(mSelectedShape);
    mWindow.draw(mSelectShape);

}

////////////////PRIVATE
void CharactersState::loadTextures()
{
    mTextures.load(TextureID::TRAINER_000, "media/textures/avatars/trainer000.png");
    mTextures.load(TextureID::TRAINER_001, "media/textures/avatars/trainer001.png");
    mTextures.load(TextureID::TRAINER_002, "media/textures/avatars/trainer002.png");
    mTextures.load(TextureID::TRAINER_003, "media/textures/avatars/trainer003.png");
    mTextures.load(TextureID::TRAINER_004, "media/textures/avatars/trainer004.png");
    mTextures.load(TextureID::TRAINER_011, "media/textures/avatars/trainer011.png");
    mTextures.load(TextureID::TRAINER_015, "media/textures/avatars/trainer015.png");
    mTextures.load(TextureID::TRAINER_016, "media/textures/avatars/trainer016.png");
    mTextures.load(TextureID::TRAINER_017, "media/textures/avatars/trainer017.png");
    mTextures.load(TextureID::TRAINER_018, "media/textures/avatars/trainer018.png");
    mTextures.load(TextureID::TRAINER_024, "media/textures/avatars/trainer024.png");
    mTextures.load(TextureID::TRAINER_027, "media/textures/avatars/trainer027.png");
    mTextures.load(TextureID::TRAINER_031, "media/textures/avatars/trainer031.png");
    mTextures.load(TextureID::TRAINER_038, "media/textures/avatars/trainer038.png");
    mTextures.load(TextureID::TRAINER_066, "media/textures/avatars/trainer066.png");


}

void CharactersState::buildScene()
{
    for (std::size_t k = 0; k < ROW_NUM; k++)
    {
        for (std::size_t i = 0; i < COL_NUM; i++)
        {
            std::size_t index = k*COL_NUM + i;
            mCharacterSprites[index].setTexture(mTextures.get(mCharacterTextureID[index]));
            sf::Vector2f scaleFactor(1.f, 1.f);
            mCharacterSprites[index].setScale(scaleFactor.x, scaleFactor.y);
            mCharacterSprites[index].setPosition(0.f + i*scaleFactor.x*IMAGE_WIDTH, 0.f + k*scaleFactor.y*IMAGE_HEIGHT + 60.f);
        }
    }
}

int CharactersState::getIndex(TextureID id)
{
    for (int i = 0; i < CHARACTERS_NUM; i++)
    {
        if (id == mCharacterTextureID[i])
            return i;
    }
    return 0;
}

