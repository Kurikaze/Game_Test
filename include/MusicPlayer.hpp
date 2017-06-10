/***********************************************************************************
 * MusicPlayer.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Hold and manage game music.
 ************************************************************************************/
#ifndef MUSICPLAYER_HPP_INCLUDED
#define MUSICPLAYER_HPP_INCLUDED

#include <map>
#include <string>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>
#include "include/ResourceIdentifiers.hpp"


class MusicPlayer : private sf::NonCopyable
{
public:
                MusicPlayer();

    void        addMusic(MusicID theme, std::string filename);
    void        play(MusicID theme);
    void        stop();

    void        setPaused(bool paused);
    void        setVolume(float volume);
private:
    std::string        getFilename(MusicID theme);

    sf::Music                           mMusic;
    std::map<MusicID, std::string>      mFilenames; //Store filename correspond to their id
    float                               mVolume;
};

#endif // MUSICPLAYER_HPP_INCLUDED
