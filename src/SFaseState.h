/* 
 * File:   SFaseState.h
 * Author: DKLawis
 *
 * Created on 27 de mayo de 2013, 12:26
 */

#ifndef SFASESTATE_H
#define	SFASESTATE_H
#include "GameState.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include "Clock.h"

class SFaseState: public GameState {
public:
    void Init();
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents(GameManager* game);
    void Update(GameManager* game);
    void Draw(GameManager* game);

    static SFaseState* Instance() {
        return &m_SFaseState;
    }
protected:
    SFaseState(){}    
private:
    static SFaseState m_SFaseState;
    Entity* m_bg;
    Entity* boton_luna;
    Entity* boton_aire;
    Entity* boton_tierra;
    Entity* boton_agua;
    Entity* boton_fuego;
    int posicion;
    int posicionant;
    int niveles;
    bool avanzar;
    bool cambio;
    bool volver;
    bool salir;
    game::Clock* clock;
};

#endif	/* SFASESTATE_H */

