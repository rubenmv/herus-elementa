/* 
 * File:   CreditsState.cpp
 * Author: Ruben
 * 
 * Created on 27 May 2013, 22:04
 */

#include "CreditsState.h"
#include "GameManager.h"
#include "MenuState.h"

CreditsState CreditsState::m_CreditsState;

void CreditsState::Init(){ // Inicializa el estado
	avanzar=false;
	salir = false;
	
	fondo = new Entity("resources/graphics/pantallas/pantalla_creditos.jpg");
	fondo->setPosition(0, 0);
}

void CreditsState::Cleanup(){ // Vacia el estado
	delete fondo;
}


void CreditsState::Pause() { // Pausa el estado

}

void CreditsState::Resume() { // Continua el estado

}

void CreditsState::HandleEvents(GameManager* gameman){ // Controla los eventos de Input
    GameEngine &engine = * GameEngine::Instance();
	
    //Bucle de obtención de eventos
    sf::Event event;
    if(engine.window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed: // Si se cierra la ventana
                gameman->Quit();
                break;
            case sf::Event::KeyPressed: // Si se pulsa una tecla
                switch(event.key.code){
                    case sf::Keyboard::Return:
                        if(!avanzar) {
                            avanzar = true;
                        }
                        break;
                    case sf::Keyboard::Escape:
                        salir = true;
                        break;
                }      
        }
    }
}

void CreditsState::Update(GameManager* gameman) { // Actualiza el estado del juego
    if(avanzar){
		gameman->ChangeState(MenuState::Instance());
	}
}

void CreditsState::Draw(GameManager* gameman) { // Realiza los draws correspondientes en game->screen
	fondo->draw();
}