#include "..\include\GameOver.h"

GameOver::GameOver(sf::Vector2u p_WindowSize, std::string p_Winner, sf::Color p_Color)
{
	m_WindowSize = p_WindowSize;
	m_View.setCenter(p_WindowSize.x / 2, p_WindowSize.y / 2);
	m_View.setSize(p_WindowSize.x, p_WindowSize.y);
	m_View.zoom(1);
	//Reference: https://www.dafont.com/pixeled.font
	m_PixelFont.loadFromFile(".\\Assets\\Fonts\\Pixeled.ttf");
	m_Title.setFont(m_PixelFont);
	m_Title.setString(p_Winner);
	m_Title.setCharacterSize(30);
	m_Title.setFillColor(p_Color);
	m_Title.setPosition(sf::Vector2f(p_WindowSize.x / 2.0f, 100.0f));
	m_Title.setOrigin(m_Title.getLocalBounds().width / 2.0f, m_Title.getLocalBounds().height / 2.0f);

	m_MenuButton = new TextButton(m_PixelFont, "Menu", 25, sf::Color::White, sf::Color(100, 100, 100));
	m_MenuButton->setPosition(sf::Vector2f(p_WindowSize.x / 2.0f, 200.0f));
}

GameOver::~GameOver()
{
	delete m_MenuButton;
	m_MenuButton = nullptr;
}

void GameOver::handleKeyboardInput(int key)
{
}

void GameOver::handleMouseInput(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) {
		if (m_MenuButton->isMouseOver(m_MouseWorldPos)) {
			m_NextScene = new Menu(m_WindowSize);
		}
	}
}

void GameOver::update(float p_TimeStep)
{
	m_MenuButton->update(m_MouseWorldPos);
}

void GameOver::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.setView(m_View);
	target.draw(m_Title);
	target.draw(*m_MenuButton);
}
