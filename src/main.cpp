/*
 * File:   main.cpp
 * Author: Ruben Martinez
 *
 * Created on 18 April 2013, 00:05
 */

#include <iostream>
#include "GameEngine.h"
#include "GameManager.h"
#include "InLevelState.h"
#include "IntroState.h"

int main() {
    GameManager* gameman = new GameManager();
	// Motor de juego (reloj y ventana)

	GameEngine &engine = * GameEngine::Instance();
	
    // initialize the engine
    gameman->Init();

    // load the intro
    gameman->ChangeState(IntroState::Instance());
	
    // main loop
    while(gameman->Running()){
        gameman->HandleEvents();
        gameman->Update();
        gameman->Draw();
    }
	
    // cleanup the engine
    gameman->Cleanup();
    return 0;
}

