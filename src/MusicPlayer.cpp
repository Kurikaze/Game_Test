#include "include/MusicPlayer.hpp"

MusicPlayer::MusicPlayer()
    : mMusic()
    , mFilenames()
    , mVolume(100.f)
{
}

void MusicPlayer::addMusic(MusicID theme, std::string filename)
{
    auto inserted = mFilenames.insert(std::make_pair(theme, filename));
    assert(inserted.second && "Could not insert into map (The ID already inserted)");
}


void MusicPlayer::play(MusicID theme)
{
    std::string filename = getFilename(theme);

    if (!mMusic.openFromFile(filename))
        throw std::runtime_error("Music filename " + filename + " could not be opened.");

    mMusic.setVolume(mVolume);
    mMusic.setLoop(true);
    mMusic.play();
}

void MusicPlayer::stop()
{
    mMusic.stop();
}

void MusicPlayer::setPaused(bool paused)
{
    if (paused)
        mMusic.pause();
    else
        mMusic.play();
}

void MusicPlayer::setVolume(float volume)
{

}


///////////////////PRIVATE
std::string MusicPlayer::getFilename(MusicID theme)
{
    auto found = mFilenames.find(theme);
    //Check if filename could be found
    assert (found != mFilenames.end() && "MusicPayer::play() - Could not find filename for Music");
    //(found is a iterator to a pair in mFilenames, whose second part is a string)
    return (found->second);
}

