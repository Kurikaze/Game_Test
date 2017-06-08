#include "include/LeaderBoardState.hpp"

#include <string>
#include <fstream>
#include <sstream>

#define TEXT_SIZE 30.f
#define TEXT_SPACE 10.f

LeaderboardState::LeaderboardState(StateStack& stateStack, Context context)
    : State(stateStack, context)
{

    mBackgroundSprite.setTexture(context.textures->get(TextureID::SUB_MENU_SCREEN));
    mBackgroundSprite.scale(640.f/512, 480.f/384); //Equal size of window/size of background image


    //READ SCORES
    std::ifstream ifile;
    ifile.open("data/highscore.txt");
    if (!ifile.is_open())
        throw std::runtime_error("Unable to open file: data/highscore.txt");
    std::string line;
    std::string name;
    int score;
    int index = 0;

    while (!ifile.eof())
    {
        //Get name and score from file
        getline(ifile, line);

        std::stringstream convert(line);
        convert >> name >> score;

        //Convert these info to string
        convert.str("");
        convert.clear();
        convert << (index + 1) << ". " << name;
        mNames[index].setString(convert.str());
        mNames[index].setFont(getContext().fonts->get(FontID::MAIN));
        mNames[index].setCharacterSize(TEXT_SIZE);
        mNames[index].setPosition(10.f, 50.f + index*(TEXT_SIZE + TEXT_SPACE));

        convert.str("");
        convert.clear();
        convert << score;

        mScores[index].setString(convert.str());
        mScores[index].setFont(getContext().fonts->get(FontID::MAIN));
        mScores[index].setCharacterSize(TEXT_SIZE);
        mScores[index].setPosition(300.f, 50.f + index*(TEXT_SIZE + TEXT_SPACE));

        index ++;
    }
    ifile.close();
}

bool LeaderboardState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
        requestStackPop();

    return false;
}

bool LeaderboardState::update(sf::Time dt)
{
    return false;
}

void LeaderboardState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    for (int i = 0; i < SCORE_COUNT; i++)
    {
        window.draw(mNames[i]);
        window.draw(mScores[i]);

    }
}
