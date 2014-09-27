/*
 * File:   Level.cpp
 * Author: Ruben Martinez Vilar
 *
 * Created on 12 March 2013, 00:01
 */
#include <vector>
#include "Level.h"

namespace game {

// Constructor normal
Level::Level() {
}

// Destructor
Level::~Level() {
    // Borramos los punteros de la matriz de tiles
    for ( std::vector< std::vector< Tile* > >::iterator it = tiles.begin(); it != tiles.end(); it++ ) {
            for ( std::vector<Tile*>::iterator jt = it->begin() ; jt != it->end(); jt++ ) {
                    delete *jt;
            }
    }
    tiles.clear();
    // Terreno y zonas de muerte
    colisionMap.clear();
    deathMap.clear();
	
	// Borramos los enemigos
    for ( std::vector<Enemy*>::iterator obj = enemigos.begin(); obj != enemigos.end(); obj++ ) {
            delete *obj;
    }
    enemigos.clear();
    // Borramos las llaves
    for ( std::vector<Key*>::iterator obj = llaves.begin(); obj != llaves.end(); obj++ ) {
            delete *obj;
    }
    llaves.clear();
    // Borramos las puertas
    for ( std::vector<Door*>::iterator obj = puertas.begin(); obj != puertas.end(); obj++ ) {
            delete *obj;
    }
    puertas.clear();
    // Borramos las Palancas
    for ( std::vector<Palanca*>::iterator obj = palancas.begin(); obj != palancas.end(); obj++ ) {
            delete *obj;
    }
	palancas.clear();
	// Borramos las Antorchas
    for ( std::vector<Torch*>::iterator obj = antorchas.begin(); obj != antorchas.end(); obj++ ) {
            delete *obj;
    }
	antorchas.clear();
	// Borramos las cajas
    for ( std::vector<Box*>::iterator obj = cajas.begin(); obj != cajas.end(); obj++ ) {
            delete *obj;
    }
    cajas.clear();
    // Borramos las Plataformas
    for ( std::vector<Plataforma*>::iterator obj = plataformas.begin(); obj != plataformas.end(); obj++ ) {
            delete *obj;
    }
    plataformas.clear();
	
    delete poder;
}


}