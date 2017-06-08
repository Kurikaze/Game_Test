#include "include/PauseState.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

#define TEXT_SIZE 30.f
#define TEXT_SPACE 10.f

PauseState::PauseState(StateStack& stateStack, Context context)
    : State(stateStack, context)
    , mWindow(*context.window)
    , mOptions()
    , mOptionText{"Resume", "Quit to Main Menu"}
    , mOptionIndex(0)
{

    //Load Font
    sf::Font& font = context.fonts->get(FontID::MAIN);

    sf::Vector2f viewSize = context.window->getView().getSize();

    //Create Pause Text
    mPauseText.setString("Game Paused");
    mPauseText.setFont(font);
    mPauseText.setCharacterSize(1.5f*TEXT_SIZE);
    mPauseText.setOrigin(mPauseText.getLocalBounds().width/2.f, mPauseText.getLocalBounds().height/2.f);
    mPauseText.setPosition(viewSize.x/2.f, 60.f);

    //Create all Option text
    for (std::size_t i = 0; i < OPTION_COUNT; i++)
    {
        if (i == 0) mOptions[i].setFillColor(sf::Color::Red);
        else mOptions[i].setFillColor(sf::Color::White);

        mOptions[i].setFont(font);
        mOptions[i].setString(mOptionText[i]);
        mOptions[i].setCharacterSize(TEXT_SIZE);
        mOptions[i].setOrigin(mOptions[i].getLocalBounds().width/2.f, mOptions[i].getLocalBounds().height/2.f);
        sf::Vector2f textPos = context.window->getView().getSize()/2.f;
        textPos.y = textPos.y - 0.5f*((TEXT_SIZE*OPTION_COUNT) + TEXT_SPACE*(OPTION_COUNT-1)) + i*(TEXT_SPACE + TEXT_SIZE);
        mOptions[i].setPosition(textPos);
    }


    context.musicPlayer->setPaused(true);
}

PauseState::~PauseState()
{
    getContext().musicPlayer->setPaused(false);
}


bool PauseState::handleEvent(const sf::Event& event)
{

    if (event.type != sf::Event::KeyPressed)
        return false;
    if (event.key.code == sf::Keyboard::Up)
    {
        if (mOptionIndex > 0)
            mOptionIndex--;
        else
            mOptionIndex = OPTION_COUNT - 1;

        updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
        if (mOptionIndex <= OPTION_COUNT - 2)
            mOptionIndex ++;
        else
            mOptionIndex = 0;

        updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == RESUME)
        {
            requestStackPop();
            requestStackPush(StateID::COUNT_DOWN);
        }
        else if (mOptionIndex == QUIT_TO_MAIN_MENU)
        {
            requestStackClear();
            requestStackPush(StateID::MENU);
        }


    }
    return false;
}

bool PauseState::update(sf::Time dt)
{
    return false;
}

void PauseState::draw()
{
    mWindow.setView(mWindow.getDefaultView());
    sf::RectangleShape backgroundShape(sf::Vector2f(getContext().window->getSize()));
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));

    mWindow.draw(backgroundShape);
    mWindow.draw(mPauseText);

    for (std::size_t i = 0; i < OPTION_COUNT; i++)
    {
        mWindow.draw(mOptions[i]);
    }
}

//////////////////PRIVATE

void PauseState::updateOptionText()
{
    //White all text
    for (std::size_t i = 0; i < OPTION_COUNT; i++)
    {
        mOptions[i].setFillColor(sf::Color::White);
    }

    //Red selected text
    mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

