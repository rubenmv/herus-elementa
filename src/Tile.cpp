/* 
 * File:   Tile.cpp
 * Author: Ruben Martinez Vilar
 * 
 * Created on 12 March 2013, 00:01
 */
#include "Tile.h"

Tile::Tile() {

}

Tile::~Tile() {}

// Devuelve la posicion en fila y columna dentro de la matriz de tiles
sf::Vector2i Tile::getFrame() {
	return frame;
}
// Establece el gid que identifica la posicion sobre el tileset
void Tile::setGid(int id) {
	gid = id;
}
// Devuelve el gid que indica la posicion sobre el tileset
int Tile::getGid() {
	return gid;
}
// Establece la posicion en fila y columna dentro de la matriz de tiles
void Tile::setFrame(int x, int y) {
	frame.x = x;
	frame.y = y;
}

void Tile::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

sf::Vector2i Tile::getPosition() {
	return position;
}


