#ifndef LEVEL_H
#define LEVEL_H

#include "SFML/Graphics.hpp"
#include "Tile.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Palanca.h"
#include "Plataforma.h"
#include "Camera.h"
#include "Poder.h"
#include "Box.h"
#include "Rejilla.h"
#include "Torch.h"

namespace game {
	

class Level {
	
public:
	Level();						 

	virtual ~Level();		         

	// Fichero del mapa
	const char *rutamapa;
	sf::Vector2i mapSize;
	sf::Vector2i tileSize;

	sf::Texture tileset;
	std::vector< sf::Sprite > capas;
	std::vector< std::vector< Tile* > > tiles;
	// Rectangulos solidos de terreno
	std::vector< sf::IntRect > colisionMap;
	// Rectangulos para pinchos y otras zonas de muerte
	std::vector< sf::IntRect > deathMap;
	// Enemigos en el nivel
	std::vector< Enemy* > enemigos;
	// Llaves en el nivel
	std::vector< Key* > llaves;
	// Puertas en el nivel
	std::vector< Door* > puertas;
	// Palancas en el nivel
	std::vector< Palanca* > palancas;
	// Antorchas en el nivel
	std::vector< Torch* > antorchas;
	// Cajas en el nivel
	std::vector< Box* > cajas;
	// Plataformas en el nivel
	std::vector< Plataforma* > plataformas;
	// Rejillas en el nivel
	std::vector< Rejilla* > rejillas;
	// Sprite para el poder del nivel
	Poder *poder;

	sf::Vector2f spawnPoint;
	bool finish;
	
};

}


#endif