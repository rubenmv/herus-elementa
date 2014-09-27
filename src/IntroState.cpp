/* 
 * File:   IntroState.cpp
 * Author: Ruben
 * 
 * Created on 27 May 2013, 22:28
 */

#include "IntroState.h"
#include "GameManager.h"
#include "MenuState.h"
#include "Resources.h"

IntroState IntroState::m_IntroState;

void IntroState::Init(){ // Inicializa el estado
	avanzar=false;
	salir = false;
	
	fondo = new Entity("resources/graphics/pantallas/pantalla_intro.jpg");
	fondo->setPosition(0, 0);
	
	texto = new game::Text();
	texto->setFont(RUTA_FONT_GABRIOLA);
	texto->setCharacterSize(48);
	texto->setColor(sf::Color(0, 0, 0));
	texto->setString("Has sido escogido para\ndominar los cuatro\nelementos de la vida.\nPulsar Enter para comenzar\ntu aventura.");
	texto->setPosition(50, 170);
}

void IntroState::Cleanup(){ // Vacia el estado
	delete fondo;
	delete texto;
}


void IntroState::Pause() { // Pausa el estado

}

void IntroState::Resume() { // Continua el estado

}

void IntroState::HandleEvents(GameManager* gameman){ // Controla los eventos de Input
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

void IntroState::Update(GameManager* gameman) { // Actualiza el estado del juego
    if(avanzar){
		gameman->ChangeState(MenuState::Instance());
	}
}

void IntroState::Draw(GameManager* gameman) { // Realiza los draws correspondientes en game->screen
	fondo->draw();
	texto->draw();
}