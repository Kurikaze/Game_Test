#include "include/TitleState.hpp"

#define TEXT_SIZE 30.f
#define TEXT_SPACE 10.f

TitleState::TitleState(StateStack& stateStack, Context context)
    : State(stateStack, context)
    , mTextEffectTime(sf::Time::Zero)
    , mShowText(false)
{
    mBackgroundSprite.setTexture(context.textures->get(TextureID::TITLE_SCREEN));
    mBackgroundSprite.scale(640.f/512, 480.f/384);


    sf::Font& font = context.fonts->get(FontID::TITLE);

    mTitleText.setFont(font);
    mTitleText.setString("A Certain \nSide Scrolling Game");
    mTitleText.setFillColor(sf::Color::White);
    mTitleText.setOutlineColor(sf::Color::Red);
    mTitleText.setOutlineThickness(2);
    mTitleText.setCharacterSize(2.f*TEXT_SIZE);
    mTitleText.setOrigin(mTitleText.getLocalBounds().width/2.f, mTitleText.getLocalBounds().height/2.f);
    mTitleText.setPosition(context.window->getView().getSize().x/2.f, 100.f);


    mFlashingText.setFont(font);
    mFlashingText.setString("Press any key to continue");
    mFlashingText.setFillColor(sf::Color::Yellow);
    mFlashingText.setCharacterSize(TEXT_SIZE*0.7);
    mFlashingText.setOrigin(mFlashingText.getLocalBounds().width/2.f, mFlashingText.getLocalBounds().height/2.f);
    mFlashingText.setPosition(context.window->getView().getSize().x/2.f, 400.f);




}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(StateID::MENU);
    }
    return true;
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;
    if (mTextEffectTime >= sf::seconds(0.5f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }
    return true;
}

void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mTitleText);

    if (mShowText)
        window.draw(mFlashingText);

}
