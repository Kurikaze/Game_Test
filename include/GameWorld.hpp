#ifndef GAMEWORLD_HPP_INCLUDED
#define GAMEWORLD_HPP_INCLUDED
#include <array>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include "include/AnimatedSprite.hpp"
#include "include/SceneNode.hpp"
#include "include/SpriteNode.hpp"
#include "include/Object.hpp"
#include "include/Animal.hpp"
#include "include/ResourceIdentifiers.hpp"
#include "include/gameTypes.h"
#include "include/gameConstants.hpp"
#include "include/CommandQueue.hpp"
#include "include/PlayerInfo.hpp"

class GameWorld : private sf::NonCopyable
{
public:
                    GameWorld(sf::RenderWindow& window, PlayerInfo& info);
public:
    void            update(sf::Time dt);
    void            draw();
    CommandQueue&   accessCommandQueue();

    bool            hasAlivePlayer() const;
    int             getDistanceTravelled();
    int             getScore();

private:
    enum Layer{BACKGROUND, FRONT, INFO, LAYER_COUNT};

private:
    //Private functions
    void            loadTextures();
    void            buildScene();
    void            spawnObstacle(unsigned int num);
    void            spawnPickup();
    void            handleCollision();

    sf::FloatRect   getViewBounds() const;
    sf::FloatRect   getRunnerFieldBounds() const;
    void            destroyEntitiesOutsideView();
    void            updateHearts(sf::Time dt);

    //
    sf::RenderWindow&   mWindow;
    sf::FloatRect       mWorldBounds;
    sf::View            mWorldView;

    PlayerInfo&         mPlayerInfo;

    float               mDistance;
    int                 mBackgroundCount;
    int                 mTotalBackgroundCount;

    //Command
    CommandQueue mCommandQueue;

    //Resources
    TextureHolder mTextures;

    //SceneGraph Structures
    SceneNode mSceneRoot; //Root node for the whole graph
    std::array<SceneNode*, LAYER_COUNT> mSceneLayers;   //Root node for each layer


    //Player
    Animal* mPlayer;
    sf::Vector2f mSpawnPosition;
    std::array<Object*, MAX_HP> mHearts;



    //Logic variables
    bool mIsCollision;
    bool mIsObstacleSpawned;
    bool mIsPickupSpawned;
};


#endif // GAMEWORLD_HPP_INCLUDED
