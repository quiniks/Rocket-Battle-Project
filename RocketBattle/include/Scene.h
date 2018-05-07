/*!
@file Scene.h
*/

#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

/* \class Scene
\brief A class that provides late binding methods for an interactable screen e.g. a game or a menu
*/

class Scene : public sf::Drawable {
protected:
	bool m_Debug = false;  //!< Debug boolean
	sf::View m_View; //!< The view
	Scene* m_NextScene = nullptr; //!< Pointer to next scene
	sf::Vector2u m_WindowSize; //!< A copy of the initial window size
	sf::Vector2f m_MouseWorldPos; //!< The current mouse pos
public:
	Scene(); //!< Default constructor
	~Scene(); //!< Destructor
	/*!
	* Handle keyboard input events
	* @param[in] p_Key The Key that was pressed
	*/
	virtual void handleKeyboardInput(int p_Key) = 0;
	/*!
	* Handle mouse input events
	* @param[in] p_Button The button that was pressed
	*/
	virtual void handleMouseInput(sf::Mouse::Button p_Button) = 0;
	/*!
	* Handle mouse mouse movement
	* @param[in] p_Window Used to calculate mouse pos relative to the window
	*/
	void handleMouseMove(const sf::RenderWindow& p_Window);
	/*!
	* Update the scene
	* @param[in] p_TimeStep the change in time since the last frame
	*/
	virtual void update(float p_TimeStep) = 0;
	/*!
	* Draw
	* @param[in, out] target Render target to draw to
	* @param[in] states Render state
	*/
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
	Scene* getNextScene(); //!< Returns a pointer to the heap for the next scene
	bool isSceneFinished(); //!< Returns true if m_NextScene isnt a nullptr
	bool getDebug(); //!<Returns the debug state
};