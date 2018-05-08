/*!
@file Terrain.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/*! \class Terrain
\brief A class that handles an sf::Image and provides methods for objects to react to its pixels
*/

class Terrain : public sf::Drawable {
private:
	sf::Image m_Image; //!< Image that contains pixel data, getters and setters
	sf::Texture m_Texture; //!< Texture for the foreground sprite
	sf::RenderTexture m_RenderTexture; //!< Render texture for subtracting/adding shapes to/from the image
	sf::Sprite m_Foreground; //!< drawable forground sprite
	sf::Sprite m_Background; //!< drawable background sprite
public:
	Terrain(); //!< default constructor
	~Terrain(); //!< destructor
	/*!
	* Copies a texture to m_Image. Also sets foreground/background sprite's textures
	* @param[in] p_ForegroundTexture Texture to be copied to m_Image and foreground sprite
	* @param[in] p_BackgroundTexture Texture for background sprite
	*/
	void loadTerrain(sf::Texture* p_ForegroundTexture, sf::Texture* p_BackgroundTexture);
	/*!
	* Calculates a unit surface normal from a sqaure of pixels based on transparency
	* @param[in] p_X X value
	* @param[in] p_Y Y value
	* @param[in] p_Radius Search radius
	*/
	sf::Vector2f getNormal(int p_X, int p_Y, int p_Radius);
	/*!
	* Checks if a pixel is empty
	* @param[in] m_Pos Chosen pixel to check
	*/
	bool isPixelEmpty(sf::Vector2i m_Pos);
	/*!
	* Subtract a shape from the image 
	* @param[in] p_Shape Polymorphic shape to subtract
	*/
	void subtractShape(sf::Shape& p_Shape);
	/*!
	* Draw
	* @param[in, out] target Render target to draw to
	* @param[in] states Render state
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};