/* 
 * File:   Ayuda.cpp
 * Author: ASUS
 * 
 * Created on 13 de mayo de 2013, 14:30
 */

#include "Ayuda.h"
#include "Clock.h"
#include "Camera.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "SFML/System.hpp"
#include "InLevelState.h"

#define anchura 650
#define altura 100

Ayuda::Ayuda() {
    sf::Font font;
    font.loadFromFile(RUTA_FONT_GBB);
 
    sf::Color letra, bloq;
    letra = sf::Color::White;
    letra.a = 0;
    bloq = sf::Color(55,55,55,100);
    activo = false;
    prime = false;
    
    blo = 0;
    let = 0;
    
    sf::Text texto;
    texto.setString("O¿O");
    texto.setCharacterSize(30);
    texto.setFont(font);
    texto.setColor(letra);
    texto.setPosition(400, 400);
    
    cuad.setFillColor(bloq);
    cuad.setSize(sf::Vector2f(500, 100));
    cuad.setOrigin(anchura/2,altura/2);
    cuad.setPosition(400,400);
}

Ayuda::Ayuda(const Ayuda& orig) {
}

Ayuda::~Ayuda() {
}

void Ayuda::update(game::Camera camara){
	if(activo) {
		if(tiempo.getSeconds() > 0 && tiempo.getSeconds() <= 2){
			blo += 1.5;
			let += 2;
		}
		if(tiempo.getSeconds() > 2 && tiempo.getSeconds() < 5){
			blo = 180;
			let = 240;
		}
		if(tiempo.getSeconds() >= 5){ 
			activo = false;
			blo = 0;
			let = 0;
		}

		if(!activo){
			blo = 0;
			let = 0;
		}

		texto.setColor(sf::Color(255, 255, 255, let));
		cuad.setFillColor(sf::Color(55, 55, 55, blo));

		texto.setPosition(camara.getCenter().x - 220, camara.getCenter().y + 190);
		cuad.setPosition(camara.getCenter().x + 80, camara.getCenter().y + 230);
	}
}
void Ayuda::draw(){
	GameEngine &engine = * GameEngine::Instance();
	
    if(activo){
		engine.window.draw(cuad);
		engine.window.draw(texto);
    }
}
void Ayuda::setActivo(int elec){
    activo = true;
	mensaje = elec;

	tiempo.restart();
	
	elegirMensaje();
}
void Ayuda::elegirMensaje(){
	int numMensajes = 5;
	
	if(mensaje == -1) {
		mensaje  = std::rand() % numMensajes;
	}

    switch(mensaje){
		case 0:
			texto.setString("Hola! Soy la ayuda y te ire dando\npistas cuando me llames con la H");
			break;
        case 1:
            texto.setString("Puedes moverte con las teclas\nWASD o las flechas de direccion.");
            break;
        case 2:
            texto.setString("Consigue poderes y activalos\ncon 1, 2, 3 y 4.");
            break;
        case 3:
            texto.setString("Activa interruptores con la S.");
            break;
        case 4:
            texto.setString("Los gobos no tiene cuernos,\npuedes saltar encima de ellos.");
            break;
		// Adquiere el poder por primera vez
		case 10:
			texto.setString("El poder del viento.\nActiva con 1 y prueba a saltar.");
			break;
		case 11:
			texto.setString("El poder de la tierra.\nActiva con 2 y mueve la caja.");
			break;
		case 12:
			texto.setString("El poder del agua.\nActiva con 3 y pasa por rejillas.");
			break;
		case 13:
			texto.setString("El poder del fuego.\nActiva con 4 y enciende antorchas.");
			break;
    }
}
bool Ayuda::getActivo(){
    return activo;
}