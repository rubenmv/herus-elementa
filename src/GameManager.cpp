/* 
 * File:   GameManager.cpp
 * Author: DKLawis
 * 
 * Created on 13 de mayo de 2013, 12:21
 */

#include "GameManager.h"
#include "GameState.h"
#include <stdio.h>
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GameEngine.h"

void GameManager::Init(){
	GameEngine &engine = * GameEngine::Instance();

    m_running = true;

}
void GameManager::Cleanup(){// Motor de juego (reloj y ventana)
	GameEngine &engine = * GameEngine::Instance();
		
    // Limpia todos los estados
    while(!states.empty()){
        states.back()->Cleanup();
        states.pop_back();
    }
	engine.window.close();
	

}

void GameManager::ChangeState(GameState* state){
    // Limpia los estados anteriores
    if(!states.empty()){
        states.back()->Cleanup();
        states.pop_back();
    }
    // Almacena e inicializa un nuevo estado
    states.push_back(state);
    states.back()->Init();

}

void GameManager::PushState(GameState* state){
    // Pausa el estado actual
    if ( !states.empty() ) {
        states.back()->Pause();
    }

    // Almacena e inicializa un nuevo estado
    states.push_back(state);
    states.back()->Init();
}

void GameManager::PopState(){
    // Limpia el estado actual
    if ( !states.empty() ) {
        states.back()->Cleanup();
        states.pop_back();
    }

    // Continua con el estado anterior
    if ( !states.empty() ) {
        states.back()->Resume();
    }
}

void GameManager::HandleEvents(){ // Controlador de los eventos de teclado
    // Controla los input del juego
    states.back()->HandleEvents(this);
}

void GameManager::Update(){ // Actualiza el juego
    // Controla el update del juego
    states.back()->Update(this);
}

void GameManager::Draw(){ // Dibuja
	// Motor de juego (reloj y ventana)

	GameEngine &engine = * GameEngine::Instance();
		
    // Controla el render del juego
	engine.window.clear();
	engine.clock.restart();
    states.back()->Draw(this);
    engine.window.display();
}

