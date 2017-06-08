/***********************************************************************************
 * GameWorld.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class GameWorld.
 ************************************************************************************/

#include "include/GameWorld.hpp"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>

#include <sstream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#define BGR_REAL_WIDTH 3072
#define BGR_REAL_HEIGHT 1536
#define BGR_WIDTH 960
#define BGR_HEIGHT 480
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

GameWorld::GameWorld(sf::RenderWindow& window, PlayerInfo& info)
    : mWindow(window)
    , mWorldBounds(0.f,0.f, BGR_MULTIPLIER*BGR_WIDTH, BGR_HEIGHT)
    , mWorldView(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT))

    , mPlayerInfo(info)
    , mDistance(0.f)
    , mBackgroundCount(0)
    , mTotalBackgroundCount(0)

    , mSpawnPosition(70.f, mWorldView.getSize().y - 130.f)
    , mIsCollision(false)
    , mIsObstacleSpawned(false)
    , mIsPickupSpawned(false)

{
    //Seed the random function
    srand(static_cast<unsigned int>(time(0)));

    loadTextures();
    buildScene();
}

void GameWorld::update(sf::Time dt)
{
    //Update distance
    mDistance += mPlayer->getVelocity().x * dt.asSeconds();
    if (mDistance >= BGR_WIDTH)
    {
        mBackgroundCount++;
        mTotalBackgroundCount++;
        std::cout << "Background Count: " << mBackgroundCount << std::endl;
        mDistance = 0;
        mIsObstacleSpawned = false;
        mIsPickupSpawned = false;
    }

    //Destroy entities outside view
    destroyEntitiesOutsideView();

    //Forward commands
    while (!mCommandQueue.isEmpty())
    {
        mSceneRoot.onCommand(mCommandQueue.pop(), dt);
    }

    //Spawn obstacle every 500 pixels

    if (!mIsObstacleSpawned && mDistance > 500)
    {
        unsigned int i =  1 + rand()%3;
        std::cout << "Obstacles spawned: " << i << std::endl;
        spawnObstacle(i);
        mIsObstacleSpawned = true;
    }

    //Spawn pickup every 1500 pixels

    if (!mIsPickupSpawned && mDistance > 500 && mBackgroundCount > 0 && mBackgroundCount%2 == 0)
    {
        spawnPickup();
        std::cout << "Pickup spawned" << std::endl;
        mIsPickupSpawned = true;
    }


    //Handle collisions
    handleCollision();

    //Infinite background scrolling
    if (mBackgroundCount == (BGR_MULTIPLIER-1))
    {
        mSceneLayers[BACKGROUND]->move(BGR_WIDTH*(BGR_MULTIPLIER-1), 0.f);
        //mObstacle.move(distance, 0.f);
        std::cout << "Back ground scrolled" << std::endl;
        mBackgroundCount = 0;
    }

    //Hit the ground check
    sf::Vector2f position = mPlayer->getWorldPosition();
    if (position.y > mSpawnPosition.y)
    {
        position.y = mSpawnPosition.y;
        mPlayer->setPosition(position);
        mPlayer->setVelocity(mPlayer->getVelocity().x, 0.f);
        mPlayer->setJumping(false);
    }

    //Perform jump
    if (mPlayer->isJumping())
    {
        mPlayer->accelerate(0.f, g);

    }
    else  //Move player along x direction
    {
        mPlayer->accelerate(gx, 0.f);
    }

    //Player's velocity on x must not exceed SCROLL_SPEED
    mPlayer->setVelocity(std::min(mPlayer->getVelocity().x, SCROLL_SPEED), mPlayer->getVelocity().y);



     //Update hearts
    updateHearts(dt);

    //Remove all destroyed entities
    mSceneRoot.removeDeadNodes();
    //Move the view
    mWorldView.move(mPlayer->getVelocity().x * dt.asSeconds(), 0.f);
    //Update all scene nodes
    mSceneRoot.update(dt);
}


void GameWorld::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneRoot);

    //Display distance travelled
    sf::Font font;
    font.loadFromFile("media/fonts/Sansation.ttf");
    sf::Text text;
    int totalDistance = getDistanceTravelled();
    std::stringstream convert;
    convert << totalDistance;
    text.setString("Distance: " + convert.str() + " m");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(mPlayer->getWorldPosition().x + 200.f, 5.f);
    mWindow.draw(text);
    /////////////////////
}

CommandQueue& GameWorld::accessCommandQueue()
{
    return mCommandQueue;
}

bool GameWorld::hasAlivePlayer() const
{
    return (mPlayer->getHitpoints()) > 0;
}

int GameWorld::getDistanceTravelled()
{
    return mTotalBackgroundCount*BGR_WIDTH + mDistance;
}

int GameWorld::getScore()
{
    return getDistanceTravelled();
}

/////////////////////PRIVATE//////////////////
void GameWorld::loadTextures()
{
    mTextures.load(TextureID::BLANK, "media/textures/Blank.png");
    mTextures.load(TextureID::BACKGROUND, "media/textures/backgrounds/Fence_bgr.png");

    mTextures.load(TextureID::TRAINER_000, "media/textures/characters/Trainer_000.png");
    mTextures.load(TextureID::TRAINER_001, "media/textures/characters/Trainer_001.png");
    mTextures.load(TextureID::TRAINER_002, "media/textures/characters/Trainer_002.png");
    mTextures.load(TextureID::TRAINER_003, "media/textures/characters/Trainer_003.png");
    mTextures.load(TextureID::TRAINER_004, "media/textures/characters/Trainer_004.png");
    mTextures.load(TextureID::TRAINER_011, "media/textures/characters/Trainer_011.png");
    mTextures.load(TextureID::TRAINER_015, "media/textures/characters/Trainer_015.png");
    mTextures.load(TextureID::TRAINER_016, "media/textures/characters/Trainer_016.png");
    mTextures.load(TextureID::TRAINER_017, "media/textures/characters/Trainer_017.png");
    mTextures.load(TextureID::TRAINER_018, "media/textures/characters/Trainer_018.png");
    mTextures.load(TextureID::TRAINER_024, "media/textures/characters/Trainer_024.png");
    mTextures.load(TextureID::TRAINER_027, "media/textures/characters/Trainer_027.png");
    mTextures.load(TextureID::TRAINER_031, "media/textures/characters/Trainer_031.png");
    mTextures.load(TextureID::TRAINER_038, "media/textures/characters/Trainer_038.png");
    mTextures.load(TextureID::TRAINER_066, "media/textures/characters/Trainer_066.png");

    mTextures.load(TextureID::CACTUS, "media/textures/Cactus.png");
    mTextures.load(TextureID::HEART, "media/textures/Heart.png");
}

void GameWorld::buildScene()
{
    //Create root nodes for each layer
    for (std::size_t i = 0; i < LAYER_COUNT; i++)
    {
        std::unique_ptr<SceneNode> layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneRoot.attachChild(std::move(layer));
    }

    //Create background
    sf::Texture& bgrTexture = mTextures.get(TextureID::BACKGROUND);
    sf::IntRect bgrRect(sf::IntRect(0, 0, static_cast<float>((BGR_MULTIPLIER+1)*BGR_REAL_WIDTH),
                                    static_cast<float>((BGR_MULTIPLIER+1)*BGR_REAL_HEIGHT)));
    bgrTexture.setRepeated(true);

    std::unique_ptr<SpriteNode> background(new SpriteNode(bgrTexture, bgrRect));
    background->scale(0.3125f, 0.3125f);
    background->setPosition(mWorldBounds.left - BGR_WIDTH, mWorldBounds.top);
    mSceneLayers[BACKGROUND]->attachChild(std::move(background));

    //Create player
    std::unique_ptr<Animal> player(new Animal(mPlayerInfo.textureID, mTextures));
    player->setCategory(Category::PLAYER_ANIMAL);
    player->setAnimation(sf::IntRect(0,0,48,72), 2, 2, ANIMATION_FREQ/5.f);
    player->setHitpoints(MAX_HP);
    player->setVelocity(SCROLL_SPEED, 0.f);
    player->setPosition(mSpawnPosition);
    mPlayer = player.get();
    mSceneLayers[FRONT]->attachChild(std::move(player));


    //Create information items (hearts)
    std::unique_ptr<Object> heart_0(new Object(mTextures.get(TextureID::HEART)));
    heart_0->setCategory(Category::NONE);
    heart_0->setPosition(10.f, 10.f);
    heart_0->setVelocity(SCROLL_SPEED, 0.f);
    mHearts[0] = heart_0.get();
    for (int i = 1; i < MAX_HP; i++)
    {
        std::unique_ptr<Object> heart(new Object(mTextures.get(TextureID::HEART)));
        heart->setCategory(Category::NONE);
        heart->setPosition(30.f*i, 0.f);
        mHearts[i] = heart.get();
        heart_0->attachChild(std::move(heart));
    }
    mSceneLayers[INFO]->attachChild(std::move(heart_0));

}


void GameWorld::spawnObstacle(unsigned int num)
{
        std::unique_ptr<Object> cactus_0(new Object(mTextures.get(TextureID::CACTUS)));
        cactus_0->setCategory(Category::OBSTACLE);
        cactus_0->setOrigin(cactus_0->getBoundingRect().width/2.f, cactus_0->getBoundingRect().height/2.f);
        //Random position for main obstacle
        int free_var = rand() % 150 + 1;
        cactus_0->setPosition(mPlayer->getWorldPosition().x + 660.f + free_var, mSpawnPosition.y + 20.f);
        //Create sub obstacle to attach to the main one
        for (std::size_t k = 1; k < num; k++)
        {
            std::unique_ptr<Object> cactus(new Object(mTextures.get(TextureID::CACTUS)));
            cactus->setCategory(Category::OBSTACLE);
            float obs_distance = 40.f*(k);
            cactus->setPosition(sf::Vector2f(obs_distance, 0.f));
            cactus_0->attachChild(std::move(cactus));
        }
        mSceneLayers[FRONT]->attachChild(std::move(cactus_0));

}

void GameWorld::spawnPickup()
{
    std::unique_ptr<Object> heart(new Object(mTextures.get(TextureID::HEART)));
    heart->setCategory(Category::PICKUP);
    heart->setOrigin(heart->getBoundingRect().width/2.f, heart->getBoundingRect().height/2.f);
    int free_var = rand() % 40 + 1;
    heart->setPosition(mPlayer->getWorldPosition().x + 600.f + free_var, mSpawnPosition.y + 20.f);
    mSceneLayers[FRONT]->attachChild(std::move(heart));
}


void GameWorld::handleCollision()
{

    std::vector<SceneNode*> colliders;
    if (!(mPlayer->checkCollision(*mSceneLayers[FRONT], colliders)))
        mIsCollision = false;
    while (!colliders.empty())
    {
        SceneNode* collider = colliders.back();
        //PICKUP
        if (collider->getCategory() == Category::PICKUP)
        {
            if (mPlayer->getHitpoints() < MAX_HP)
                mPlayer->heal(1);
            std::cout << "HEAL" << std::endl;
            collider->destroy();
            mIsCollision = false;
        }
        //HIT OBSTACLE
        else if (collider->getCategory() == Category::OBSTACLE)
        {
            if (!mIsCollision)
            {
                mIsCollision = true;
                if (mPlayer->getHitpoints() > 0)
                    mPlayer->damage(1);
                std::cout <<"CRASH!"<<std::endl;

                //Bounce off obstacle
                mPlayer->setVelocity(mPlayer->getVelocity()*(-1.f));


            }
        }
        colliders.pop_back();
    }

}

sf::FloatRect GameWorld::getViewBounds() const
{
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}
sf::FloatRect GameWorld::getRunnerFieldBounds() const
{
    sf::FloatRect bounds = getViewBounds();
	bounds.left -= 100.f;
	bounds.width += 300.f;

	return bounds;
}

void GameWorld::destroyEntitiesOutsideView()
{
    Command command;
    command.category = Category::ENEMY_ANIMAL | Category::OBSTACLE | Category::PICKUP;
    command.action = [this](SceneNode& node, sf::Time dt)
    {
        Entity& e = static_cast<Entity&>(node);
        if (!getRunnerFieldBounds().intersects(e.getBoundingRect()))
        {
            e.destroy();
            std::cout << "OUT VIEW" << std::endl;
        }

    };
    mCommandQueue.push(command);
}

void GameWorld::updateHearts(sf::Time dt)
{
    mHearts[0]->setVelocity(mPlayer->getVelocity().x, 0.f);
    for (int i = 0; i < MAX_HP; i++)
    {
        mHearts[i]->setTexture(mTextures.get(TextureID::BLANK));
    }
    for (int i = 0; i < mPlayer->getHitpoints(); i++)
    {
        mHearts[i]->setTexture(mTextures.get(TextureID::HEART));
    }


}


