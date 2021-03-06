/***********************************************************************************
 * PlayerInfo.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Hold info of player (name, texture id and score)
 ************************************************************************************/


#ifndef PLAYERINFO_HPP_INCLUDED
#define PLAYERINFO_HPP_INCLUDED
#include "include/ResourceIdentifiers.hpp"

struct PlayerInfo
{

    PlayerInfo(std::string name, TextureID id, int scoreVal)
        : name(name)
        , textureID(id)
        , score(scoreVal)
    {
    };

    std::string name;
    TextureID textureID;
    int score;
};


#endif // PLAYERINFO_HPP_INCLUDED
