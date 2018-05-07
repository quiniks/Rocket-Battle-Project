#include "..\include\Menu.h"

Menu::Menu(sf::RenderWindow& p_Window)
{
	//Reference: https://www.dafont.com/pixeled.font
	m_PixelFont.loadFromFile(".\\Assets\\Fonts\\Pixeled.ttf");
	m_Title.setFont(m_PixelFont);
	m_Title.setString("Rocket Battle");
	m_Title.setCharacterSize(30);
	m_Title.setFillColor(sf::Color::White);
	m_Title.setPosition(sf::Vector2f(p_Window.getSize().x / 2.0f, 100.0f));
	m_Title.setOrigin(m_Title.getLocalBounds().width / 2.0f, m_Title.getLocalBounds().height / 2.0f);

	m_StartButton = new TextButton(m_PixelFont, "Start", 25, sf::Color::White, sf::Color(100, 100, 100));
	m_StartButton->setPosition(sf::Vector2f(p_Window.getSize().x / 2.0f, 200.0f));

	m_Rocket.setTexture(*TextureLoader::instance()->getTexture("WhiteRocket.png"));
	float l_ImagePosX = (p_Window.getSize().x / 2.0f) + (m_Title.getLocalBounds().width / 2.0f) + 20.0f;
	m_Rocket.setPosition(sf::Vector2f(l_ImagePosX, 93.0f));
	m_Rocket.setOrigin(m_Rocket.getLocalBounds().width / 2.0f, m_Rocket.getLocalBounds().height / 2.0f);
}

Menu::~Menu()
{

}

void Menu::handleKeyboardInput(int key)
{
}

void Menu::handleMouseInput(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) {
		if (m_StartButton->isMouseOver((sf::Vector2f)m_MousePixelPos)) {
			m_SceneFinished = true;
			m_NextScene = new Game();
		}
	}
}

void Menu::handleMouseMove(const sf::RenderWindow & p_Window)
{
	m_MousePixelPos = sf::Mouse::getPosition(p_Window);
}

void Menu::update(float p_TimeStep)
{
	m_StartButton->update((sf::Vector2f)m_MousePixelPos);
}


void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Title);
	target.draw(m_Rocket);
	target.draw(*m_StartButton);
}
