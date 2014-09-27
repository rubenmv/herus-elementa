/* 
 * File:   IntroState.h
 * Author: Ruben
 *
 * Created on 27 May 2013, 22:28
 */

#ifndef INTROSTATE_H
#define	INTROSTATE_H

#include "GameState.h"
#include "Entity.h"
#include "Text.h"

class IntroState: public GameState {
public:
    void Init();
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents(GameManager* game);
    void Update(GameManager* game);
    void Draw(GameManager* game);

    static IntroState* Instance() {
        return &m_IntroState;
    }
protected:
    IntroState(){}
private:
	static IntroState m_IntroState;
	Entity *fondo;
	bool avanzar;
    bool salir;
	
	game::Text *texto;

};

#endif	/* INTROSTATE_H */

