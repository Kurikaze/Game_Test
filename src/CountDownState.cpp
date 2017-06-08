#include "include/CountDownState.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

CountDownState::CountDownState(StateStack& stateStack, Context context)
    : State(stateStack, context)
    , mWindow(*context.window)
    , mText()
    , mElapsedTime(sf::Time::Zero)
{
    sf::Font& font = context.fonts->get(FontID::MAIN);

    mText.setString("3");
    mText.setFont(font);
    mText.setCharacterSize(60);
    mText.setOrigin(mText.getLocalBounds().width/2.f, mText.getLocalBounds().height/2.f);
    mText.setPosition(0.5f*mWindow.getView().getSize().x, 0.35f*mWindow.getView().getSize().y);


}

bool CountDownState::handleEvent(const sf::Event& event)
{
    return false;
}

bool CountDownState::update(sf::Time dt)
{

	mElapsedTime += dt;
	if (mElapsedTime < sf::seconds(1))
	{
        mText.setString("3");
	}
	else if (mElapsedTime < sf::seconds(2))
	{
        mText.setString("2");
	}
    else if (mElapsedTime < sf::seconds(3))
    {
        mText.setString("1");
    }
    else
    {
        requestStackPop();
    }

    return false;
}

void CountDownState::draw()
{
    mWindow.setView(mWindow.getDefaultView());
    sf::RectangleShape backgroundShape(sf::Vector2f(getContext().window->getSize()));
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));

    mWindow.draw(backgroundShape);
    mWindow.draw(mText);

}
