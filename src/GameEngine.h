/*
 * File:   GameEngine.h
 * Author: Rubén
 *
 * Created on 22 May 2013, 00:44
 */

#ifndef GAMEENGINE_H
#define	GAMEENGINE_H

#include "Clock.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Camera.h"

class GameEngine {
public:
    static GameEngine* Instance();
    virtual ~GameEngine();

    sf::RenderWindow window;
    int windowWidth;
    int windowHeight;

	game::Clock clock;

private:
    GameEngine();
    GameEngine(const GameEngine& orig);
    GameEngine &operator= (const GameEngine &);
    static GameEngine* pinstance;



};

#endif	/* GAMEENGINE_H */

