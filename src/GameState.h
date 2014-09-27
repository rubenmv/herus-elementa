/* 
 * File:   GameState.h
 * Author: DKLawis
 *
 * Created on 13 de mayo de 2013, 12:56
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameManager.h"

class GameState{
public:
    virtual void Init()=0;
    virtual void Cleanup()=0;

    virtual void Pause()=0;
    virtual void Resume()=0;

    virtual void HandleEvents(GameManager* gameman)=0;
    virtual void Update(GameManager* gameman)=0;
    virtual void Draw(GameManager* gameman)=0;

    void ChangeState(GameManager* gameman, GameState* state){
        gameman->ChangeState(state);
    }

protected:
    GameState(){}
};

#endif