/*
 * File:   GameManager.h
 * Author: DKLawis
 *
 * Created on 13 de mayo de 2013, 12:21
 */

#ifndef GAMEMANAGER_H
#define	GAMEMANAGER_H

#include <vector>
#include "GameEngine.h"

#include "SFML/Graphics/RenderWindow.hpp"
using namespace std;

class GameState;

class GameManager {
    public:
        void Init();
        void Cleanup();

        void ChangeState(GameState* state);
        void PushState(GameState* state);
        void PopState();

        void HandleEvents(); // Controlador de los eventos de teclado
        void Update(); // Actualiza el juego
        void Draw(); // Dibuja

        bool Running(){
            return m_running;
        }
        void Quit(){
            m_running=false;
        }



    private:
        // Pila de estados
        vector<GameState*> states;

        bool m_running;

};

#endif	/* GAMEMANAGER_H */

