/* 
 * File:   Entity.cpp
 * Author: Ruben Martinez Vilar
 * 
 * Created on 12 March 2013, 00:01
 */
#include <iostream>
#include "Entity.h"
#include "GameEngine.h"

// Constructor 1: Simplemente crea una instancia
Entity::Entity() {
	isLoaded = false;

	setSpeed(0.f, 0.f);
}

// Constructor 2: recoge la ruta a la imagen y el tam de cada frame (para sheets)
Entity::Entity(const char *texture_path) {
	// Carga el sprite con la textura
	setSprite(texture_path);
	
	// Iniciamos el reloj
	clock.restart();
	frame = 0;

	setSpeed(0.f, 0.f);
}

// Destructor
Entity::~Entity() {
}

// Establece un sprite a partir de la ruta de la imagen
void Entity::setSprite(const char *texture_path) {
	// Carga la imagen y crea el sprite
	if(!textura.loadFromFile(texture_path)) {
		std::cerr << "Error cargando la imagen " << texture_path;
		isLoaded = false;
	}
	else {
		isLoaded = true;
		
		// Dimensiones de los sprites dentro de la textura
		sprite.setTexture(textura);
		// Size de la textura
		// OJO! para sheets hay que establecer el size deseado (del frame) despues de crear una instancia
		setSize(textura.getSize().x, textura.getSize().y);
	}
}

void  Entity::setCentro(float x, float y) {
	if(isLoaded) {
		sprite.setOrigin(x, y);
	}
}

// Posicion el sprite
void Entity::setPosition(float x, float y) {
	if(isLoaded) {
		sprite.setPosition(x, y);
	}
}

// Recupera la posicion [x, y] del sprite
sf::Vector2f Entity::getPosition() {
	if(isLoaded) {
		return sprite.getPosition();
	}
}

// Devuelve el size del sprite/frame
sf::Vector2u Entity::getSize() {
	return size;
}

// Indica el tamanyo del frame en el sprite sheet
void Entity::setSize(unsigned int x, unsigned int y) {
	size.x = x;
	size.y = y;
}

// Dibuja el sprite en la ventana
void Entity::draw() {
	if(isLoaded) {
        GameEngine &gameEngine = * GameEngine::Instance();
        gameEngine.window.draw(sprite);
	}
}

// Mueve el sprite x e y pixeles
void Entity::move(float x, float y) {
    if(isLoaded) {
        sprite.move(x, y);
    }
}

void Entity::setSpeed(float x, float y) {
	speed.x = x;
	speed.y = y;
}

sf::Vector2f Entity::getSpeed() {
	return speed;
}

// Cambia el frame del sheet (fila y columna/frame) y la escala
void Entity::setFrame(int row, int frame, float scaleX, float scaleY) {
	sprite.setTextureRect(sf::IntRect(frame*size.x, row*size.y, size.x, size.y));
	sprite.setScale(scaleX, scaleY);
}

// Devuelve el rectangulo que cubre al sprite
sf::IntRect Entity::getBounds() {
	sf::IntRect r(getPosition().x - getSize().x/2 + 5, getPosition().y - getSize().y/2 + 5, getSize().x - 10, getSize().y - 5);
	return r;
}

void Entity::fade(int seg) {
	
}
