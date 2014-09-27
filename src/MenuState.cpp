/*
 * File:   MenuState.cpp
 * Author: DKLawis
 *
 * Created on 14 de mayo de 2013, 11:46
 */
#include "GameManager.h"
#include "GameState.h"
#include "MenuState.h"
#include "InLevelState.h"
#include "SFaseState.h"
#include "Entity.h"
#include "SaveManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "LevelManager.h"
#include <iostream>
using namespace game;
using namespace std;
MenuState MenuState::m_MenuState;

void MenuState::Init(){ // Inicializa el estado
    game::LevelManager &levelManager = * game::LevelManager::Instance();
    levelManager.nivelActual = 0;
    ////////VARIABLES///////
    salir=false;
    avanzar=false;
    cambio=false;
    posicionant=0;
    posicion=1;
    ////////FONDO//////////
    m_bg=new Entity("resources/graphics/pantallas/Pantalla_intro.jpg");

    ////////BOTONES///////
    boton1=new Entity("resources/graphics/pantallas/Botones.png");
    boton1->setSize(310,122);
    boton1->setFrame(0,0,1,1);
    boton1->setCentro(boton1->getSize().x/2,boton1->getSize().y/2);
    boton1->setPosition(m_bg->getSize().x/2-150,m_bg->getSize().y-400);

    boton2=new Entity("resources/graphics/pantallas/Botones.png");
    boton2->setSize(310,122);
    boton2->setFrame(1,1,1,1);
    boton2->setCentro(boton2->getSize().x/2,boton2->getSize().y/2);
    boton2->setPosition(m_bg->getSize().x/2-150,m_bg->getSize().y-250);

    boton3=new Entity("resources/graphics/pantallas/Botones.png");
    boton3->setSize(310,122);
    boton3->setFrame(2,1,1,1);
    boton3->setCentro(boton3->getSize().x/2,boton3->getSize().y/2);
    boton3->setPosition(m_bg->getSize().x/2-150,m_bg->getSize().y-100);

    ////////CAMARA/////////

    ////////RELOJES////////
    clock= new game::Clock();


}

void MenuState::Cleanup(){ // Vacia el estado
    //////DELETES///////
    m_bg->~Entity();
    boton1->~Entity();
    boton2->~Entity();
    boton3->~Entity();

}

void MenuState::Pause(){ // Pausa el estado

}

void MenuState::Resume(){ // Continua el estado

}

void MenuState::HandleEvents(GameManager* gameman){ // Controla los eventos de Input
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
                            clock->restart();
                        }
                        break;
                    case sf::Keyboard::Up:
                        if(posicion!=1 && !avanzar) {
                            posicionant=posicion;
                            posicion--;
                            cambio = true;
                            clock->restart();
                        }
                        break;
                    case sf::Keyboard::Down:
                        if(posicion!=3 && !avanzar) {
                            posicionant=posicion;
                            posicion++;
                            cambio = true;
                            clock->restart();
                        }
                        break;
                    case sf::Keyboard::Escape:
                        salir = true;
                        break;
                }

                // PODERES
                game::LevelManager &levelManager = * game::LevelManager::Instance();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
                        levelManager.nivelActual = 0;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        levelManager.nivelActual = 1;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                        levelManager.nivelActual = 2;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                        levelManager.nivelActual = 3;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                        levelManager.nivelActual = 4;
                }
                break;
        }
    }
}

void MenuState::Update(GameManager* gameman) { // Actualiza el estado del juego
    if(avanzar){
        if(clock->getMiliseconds()>=300){

            avanzar = false;
            // Antes de cambiar al mapa indicamos el nivel a cargar al level manager
            game::LevelManager &levelManager = * game::LevelManager::Instance();
            if(posicion==1){

                levelManager.nivelActual = 0;

				SaveManager &saveMan = * SaveManager::Instance();
				saveMan.save(0);

                gameman->ChangeState(InLevelState::Instance());
            }
            if(posicion==2){
                gameman->ChangeState(SFaseState::Instance());
            }
            if(posicion==3){
                gameman->Quit();
            }
        }
        else if (clock->getMiliseconds()<=100) {

            if(posicion==1) boton1->sprite.scale(0.99,0.99);
            if(posicion==2) boton2->sprite.scale(0.99,0.99);
            if(posicion==3) boton3->sprite.scale(0.99,0.99);
        }
        else if (clock->getMiliseconds()>100 && clock->getMiliseconds()<200){

            if(posicion==1) boton1->sprite.scale(1.01,1.01);
            if(posicion==2) boton2->sprite.scale(1.01,1.01);
            if(posicion==3) boton3->sprite.scale(1.01,1.01);
        }
    }
    // Cuando no se realiza ninguna accion
    switch(posicion){
        case 1:
            // boton1 grande
            if(cambio && clock->getMiliseconds()<200){
                boton1->setFrame(0,0,1,1);
                if(posicionant==2){
                    boton2->setFrame(1,1,1,1);
                }
                cambio=false;
            }
            break;
        case 2:
            // boton2 grande
            if(cambio && clock->getMiliseconds()<200){
                boton2->setFrame(1,0,1,1);
                cambio=false;
            }
            if(posicionant==1){
                boton1->setFrame(0,1,1,1);
            }
            if(posicionant==3){
                boton3->setFrame(2,1,1,1);
            }
            break;
        case 3:
            // boton3 grande
            if(cambio && clock->getMiliseconds()<200){
                boton3->setFrame(2,0,1,1);
                if(posicionant==2){
                    boton2->setFrame(1,1,1,1);
                }
                cambio=false;
            }
            break;
    }
    if(cambio && clock->getMiliseconds()>200){
        cambio=false;
        clock->restart();
    }
    if(salir){
        salir=false;
        gameman->Quit();
    }
}

void MenuState::Draw(GameManager* game) { // Realiza los draws correspondientes en game->screen
    ///////DRAW/////////
    m_bg->draw();
    boton1->draw();
    boton2->draw();
    boton3->draw();
}
