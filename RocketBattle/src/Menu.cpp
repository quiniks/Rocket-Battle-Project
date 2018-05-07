#include "..\include\Menu.h"

Menu::Menu(sf::Vector2u p_WindowSize)
{
	m_WindowSize = p_WindowSize;
	m_View.setCenter(p_WindowSize.x / 2, p_WindowSize.y / 2);
	m_View.setSize(p_WindowSize.x, p_WindowSize.y);
	m_View.zoom(1);
	//Reference: https://www.dafont.com/pixeled.font
	m_PixelFont.loadFromFile(".\\Assets\\Fonts\\Pixeled.ttf");
	m_Title.setFont(m_PixelFont);
	m_Title.setString("Rocket Battle");
	m_Title.setCharacterSize(30);
	m_Title.setFillColor(sf::Color::White);
	m_Title.setPosition(sf::Vector2f(p_WindowSize.x / 2.0f, 100.0f));
	m_Title.setOrigin(m_Title.getLocalBounds().width / 2.0f, m_Title.getLocalBounds().height / 2.0f);

	m_StartButton = new TextButton(m_PixelFont, "Start", 25, sf::Color::White, sf::Color(100, 100, 100));
	m_StartButton->setPosition(sf::Vector2f(p_WindowSize.x / 2.0f, 200.0f));

	m_Hint.setTexture(*TextureLoader::instance()->getTexture("Hint.png"));
	m_Hint.setPosition(sf::Vector2f(p_WindowSize.x/2.0f, 400.0f));
	m_Hint.setOrigin(m_Hint.getLocalBounds().width / 2.0f, m_Hint.getLocalBounds().height / 2.0f);
}

Menu::~Menu()
{
	delete m_StartButton;
	m_StartButton = nullptr;
}

void Menu::handleKeyboardInput(int key)
{
}

void Menu::handleMouseInput(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) {
		if (m_StartButton->isMouseOver((sf::Vector2f)m_MousePixelPos)) {
			m_NextScene = new Game(m_WindowSize);
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
	target.setView(m_View);
	target.draw(m_Title);
	target.draw(*m_StartButton);
	target.draw(m_Hint);
}
