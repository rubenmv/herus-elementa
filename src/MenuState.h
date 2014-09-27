/*
 * File:   MenuState.h
 * Author: DKLawis
 *
 * Created on 14 de mayo de 2013, 11:46
 */

#ifndef MENUSTATE_H
#define	MENUSTATE_H
#include "GameState.h"
#include "Entity.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Clock.h"


class MenuState: public GameState {
public:
    void Init();
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents(GameManager* game);
    void Update(GameManager* game);
    void Draw(GameManager* game);

    static MenuState* Instance() {
        return &m_MenuState;
    }
protected:
    MenuState(){}
private:
    static MenuState m_MenuState;
    Entity* m_bg;
    Entity* boton1;
    Entity* boton2;
    Entity* boton3;
    game::Clock* clock;
    int posicion;
    int posicionant;
    bool cambio;
    bool avanzar;
    bool salir;
};

#endif	/* MENUSTATE_H */

