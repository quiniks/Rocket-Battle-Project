#include "Terrain.h"

Terrain::Terrain()
{

}

Terrain::~Terrain()
{

}

void Terrain::LoadTerrain(sf::Texture* p_Texture)
{
	m_Texture = p_Texture;
	m_Image = p_Texture->copyToImage();
	m_Background.setTexture(*p_Texture);
	m_Foreground.setTexture(*p_Texture);
	m_Foreground.setPosition(1.0f, 1.0f);
	m_RenderTexture.create(p_Texture->getSize().x, p_Texture->getSize().y, false);
}

sf::Vector2f Terrain::GetNormal(unsigned int p_X, unsigned int p_Y, int p_Radius)
{
	sf::Vector2f normal = sf::Vector2f(0.0f, 0.0f);
	for (int i = -p_Radius; i <= p_Radius; i++) {
		for (int j = -p_Radius; j <= p_Radius; j++) {
			if (p_X + i < m_Image.getSize().x && p_Y + j < m_Image.getSize().y) {
				if (m_Image.getPixel(p_X + i, p_Y + j).a != 0) {
					normal -= sf::Vector2f((float)i, (float)j);
				}
			}
		}
	}
	float length = sqrt(normal.x * normal.x + normal.y * normal.y);
	if (length != 0) {
		normal = normal / length;
	}
	std::cout << "normalx" << normal.x << std::endl;
	std::cout << "normaly" << normal.y << std::endl;
	return normal;
}

bool Terrain::isPixelEmpty(sf::Vector2u m_Pos)
{
	if (m_Pos.x < m_Image.getSize().x && m_Pos.y < m_Image.getSize().y) {
		if (m_Image.getPixel(m_Pos.x, m_Pos.y).a == 0) {
			return true;
		}
	}
	return false;
}

void Terrain::SubtractShape(sf::Shape* p_Shape)
{
	m_RenderTexture.clear();
	m_RenderTexture.draw(m_Foreground);
	m_RenderTexture.draw(*p_Shape, sf::BlendMultiply);
	m_RenderTexture.display();

	*m_Texture = m_RenderTexture.getTexture();
	m_Foreground.setTexture(*m_Texture);
	m_Image = m_Texture->copyToImage();
}

void Terrain::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Foreground);
}