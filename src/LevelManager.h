/* 
 * File:   LevelFactory.h
 * Author: Ruben
 *
 * Created on 12 May 2013, 13:29
 */

#ifndef LEVELMANAGER_H
#define	LEVELMANAGER_H

#include "Level.h"
#include "tinyxml2.h"

namespace game {
	
class LevelManager {
public:
	static LevelManager* Instance();
	
	virtual ~LevelManager();

	Level *inlevel;
	int nivelActual;
	
	void loadMap();
	// Carga los objetos, enemigos y otros
	void loadObjects();
	// Dibuja el mapa
	void draw(sf::RenderWindow &window, game::Camera *camara);
	void drawFront(sf::RenderWindow &window, game::Camera *camara);
	// Recarga el mapa
	void reload();
	// Actualiza las posiciones de los objetos/entidades del nivel
	void updateObjects();
	// Eliminar objetos/enemigos inactivos
	void objCleaner();

private:
	LevelManager();
	LevelManager(const LevelManager &);
	LevelManager &operator= (const LevelManager &);
	static LevelManager* pinstance;
};

}
#endif	/* LevelFactory_H */
