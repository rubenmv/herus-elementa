/* 
 * File:   CreditsState.h
 * Author: Ruben
 *
 * Created on 27 May 2013, 22:04
 */

#ifndef CREDITSSTATE_H
#define	CREDITSSTATE_H

#include "GameState.h"
#include "Entity.h"

class CreditsState: public GameState {
public:
    void Init();
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents(GameManager* game);
    void Update(GameManager* game);
    void Draw(GameManager* game);

    static CreditsState* Instance() {
        return &m_CreditsState;
    }
protected:
    CreditsState(){}
private:
	static CreditsState m_CreditsState;
	Entity *fondo;
	bool avanzar;
    bool salir;

};

#endif	/* CREDITSSTATE_H */

