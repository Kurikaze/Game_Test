#ifndef GAMETYPES_HPP_INCLUDED
#define GAMETYPES_HPP_INCLUDED

//Used for Commands
namespace Category
{
    enum ID
    {
        NONE            = 0,
        SCENE           = 1 << 0,
        PLAYER_ANIMAL   = 1 << 1,
        ENEMY_ANIMAL    = 1 << 2,
        OBSTACLE        = 1 << 3,
        PICKUP          = 1 << 4,
        ANIMAL = PLAYER_ANIMAL|ENEMY_ANIMAL,
    };
}





//Used in State
enum class StateID
{
    NONE,
    TITLE,
    LOADING,
    MENU,
    GAME,
    PAUSE,
    GAME_OVER,
    COUNT_DOWN,
    CHARACTERS,
    PLAYERS,
    CREATE_PLAYER,
    LEADERBOARD

};


#endif // GAMETYPES_HPP_INCLUDED
