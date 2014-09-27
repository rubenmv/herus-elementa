/* 
 * File:   SFaseState.cpp
 * Author: DKLawis
 * 
 * Created on 27 de mayo de 2013, 12:26
 */
#include "GameManager.h"
#include "GameState.h"
#include "SFaseState.h"
#include "InLevelState.h"
#include "MenuState.h"
#include "Entity.h"
#include "SaveManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "LevelManager.h"
#include <iostream>
using namespace game;
using namespace std;
SFaseState SFaseState::m_SFaseState;
void SFaseState::Init(){ // Inicializa el estado
    game::LevelManager &levelManager = * game::LevelManager::Instance();
    SaveManager &saveMan = * SaveManager::Instance();
    niveles=saveMan.load()+1;
    levelManager.nivelActual = 0;

    ////////VARIABLES///////
    salir=false;
    avanzar=false;
    cambio=false;
    volver=false;
    posicionant=0;
    posicion=1;
    ////////FONDO//////////
    m_bg=new Entity("resources/graphics/pantallas/pantalla_niveles.jpg");
    ////////BOTONES///////
    boton_luna=new Entity("resources/graphics/pantallas/iconos_castillos.png");
    boton_luna->setSize(100,100);
    boton_luna->setFrame(0,0,1,1);
    boton_luna->setCentro(boton_luna->getSize().x/2,boton_luna->getSize().y/2);
    boton_luna->setPosition(m_bg->getSize().x-700,m_bg->getSize().y-500);
    
    boton_aire=new Entity("resources/graphics/pantallas/iconos_castillos.png");
    boton_aire->setSize(100,100);
    boton_aire->setFrame(1,1,1,1);
    boton_aire->setCentro(boton_aire->getSize().x/2,boton_aire->getSize().y/2);
    boton_aire->setPosition(m_bg->getSize().x-630,m_bg->getSize().y-380);
    
    boton_tierra=new Entity("resources/graphics/pantallas/iconos_castillos.png");
    boton_tierra->setSize(100,100);
    boton_tierra->setFrame(1,2,1,1);
    boton_tierra->setCentro(boton_tierra->getSize().x/2,boton_tierra->getSize().y/2);
    boton_tierra->setPosition(m_bg->getSize().x-700,m_bg->getSize().y-100);
    
    boton_agua=new Entity("resources/graphics/pantallas/iconos_castillos.png");
    boton_agua->setSize(100,100);
    boton_agua->setFrame(1,3,1,1);
    boton_agua->setCentro(boton_agua->getSize().x/2,boton_agua->getSize().y/2);
    boton_agua->setPosition(m_bg->getSize().x/2+30,m_bg->getSize().y-100);
    
    boton_fuego=new Entity("resources/graphics/pantallas/iconos_castillos.png");
    boton_fuego->setSize(100,100);
    boton_fuego->setFrame(1,4,1,1);
    boton_fuego->setCentro(boton_fuego->getSize().x/2,boton_fuego->getSize().y/2);
    boton_fuego->setPosition(m_bg->getSize().x/2+60,m_bg->getSize().y-400);
    ////////CAMARA/////////
    
    ////////RELOJES////////
    clock= new game::Clock();
    

}

void SFaseState::Cleanup(){ // Vacia el estado
    //////DELETES///////
    m_bg->~Entity();
    boton_luna->~Entity();
    boton_aire->~Entity();
    boton_tierra->~Entity();
    boton_agua->~Entity();
    boton_fuego->~Entity();

}

void SFaseState::Pause(){ // Pausa el estado

}

void SFaseState::Resume(){ // Continua el estado

}

void SFaseState::HandleEvents(GameManager* game){ // Controla los eventos de Input
    GameEngine &engine = * GameEngine::Instance();
    //Bucle de obtención de eventos
    sf::Event event;
    if(engine.window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed: // Si se cierra la ventana
                game->Quit();
                break;
            case sf::Event::KeyPressed: // Si se pulsa una tecla
                switch(event.key.code){
                    case sf::Keyboard::Return:
                        if(!avanzar) {
                            avanzar = true;
                            clock->restart();
                        }
                        break;
                    case sf::Keyboard::Left:
                        if(posicion!=1 && !avanzar) {
                            posicionant=posicion;
                            posicion--;
                            cambio = true;
                            clock->restart();
                        }
                        break;
                    case sf::Keyboard::Right:
                        if(posicion<niveles && !avanzar) {
                            posicionant=posicion;
                            posicion++;
                            cambio = true;
                            clock->restart();
                        }
                        break;
                    case sf::Keyboard::Escape:
                        volver=true;
                        break;
                }
                break;         
        }
    }
}

void SFaseState::Update(GameManager* game) { // Actualiza el estado del juego
    if(avanzar){
        if(clock->getMiliseconds()>=300){

            avanzar = false;

            // Antes de cambiar al mapa indicamos el nivel a cargar al level manager
            game::LevelManager &levelManager = * game::LevelManager::Instance();
            levelManager.nivelActual = posicion-1;
			
            game->ChangeState(InLevelState::Instance());
            
        }
        else if (clock->getMiliseconds()<=100) {
           
            if(posicion==1) boton_luna->sprite.scale(0.99,0.99);
            if(posicion==2) boton_aire->sprite.scale(0.99,0.99);
            if(posicion==3) boton_tierra->sprite.scale(0.99,0.99);
            if(posicion==4) boton_agua->sprite.scale(0.99,0.99);
            if(posicion==5) boton_fuego->sprite.scale(0.99,0.99);
        }
        else if (clock->getMiliseconds()>100 && clock->getMiliseconds()<200){
            
            if(posicion==1) boton_luna->sprite.scale(1.01,1.01);
            if(posicion==2) boton_aire->sprite.scale(1.01,1.01);
            if(posicion==3) boton_tierra->sprite.scale(1.01,1.01);
            if(posicion==4) boton_agua->sprite.scale(1.01,1.01);
            if(posicion==5) boton_fuego->sprite.scale(1.01,1.01);
        }
    }
    // Cuando no se realiza ninguna accion
    switch(posicion){
        case 1:
            // boton1 grande
            if(cambio && clock->getMiliseconds()<200){
                boton_luna->setFrame(0,0,1,1);
                if(posicionant==2){
                    boton_aire->setFrame(1,1,1,1);
                }
                cambio=false;
            }
            break;
        case 2:
            // boton2 grande
            if(cambio && clock->getMiliseconds()<200){
                boton_aire->setFrame(0,1,1,1);
                cambio=false;
            }
            if(posicionant==1){
                boton_luna->setFrame(1,0,1,1);
            }
            if(posicionant==3){
                boton_tierra->setFrame(1,2,1,1);
            }
            break;
        case 3:
            // boton3 grande
            if(cambio && clock->getMiliseconds()<200){
                boton_tierra->setFrame(0,2,1,1);
                if(posicionant==2){
                    boton_aire->setFrame(1,1,1,1);
                }
                if(posicionant==4){
                    boton_agua->setFrame(1,3,1,1);
                }
                cambio=false;
            }
            break;
        case 4:
            // boton3 grande
            if(cambio && clock->getMiliseconds()<200){
                boton_agua->setFrame(0,3,1,1);
                if(posicionant==3){
                    boton_tierra->setFrame(1,2,1,1);
                }
                if(posicionant==5){
                    boton_fuego->setFrame(1,4,1,1);
                }
                cambio=false;
            }
            break;
        case 5:
            // boton3 grande
            if(cambio && clock->getMiliseconds()<200){
                boton_fuego->setFrame(0,4,1,1);
                if(posicionant==4){
                    boton_agua->setFrame(1,3,1,1);
                }
                cambio=false;
            }
            break;
    }
    if(cambio && clock->getMiliseconds()>200){
        cambio==false;
        clock->restart();
    }
    if(volver){
        game->ChangeState(MenuState::Instance());
    }
    if(salir){
        salir=false;
        game->Quit();
    }
}

void SFaseState::Draw(GameManager* game) { // Realiza los draws correspondientes en game->screen
    ///////DRAW/////////
    m_bg->draw();
    boton_luna->draw();
    boton_aire->draw();
    boton_tierra->draw();
    boton_agua->draw();
    boton_fuego->draw();
}