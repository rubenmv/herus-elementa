/* 
 * File:   LevelFactory.cpp
 * Author: Ruben Martinez Vilar
 * 
 * Created on 12 May 2013, 13:29
 */
#include <iostream>
#include "LevelManager.h"
#include "Resources.h"
#include "GameEngine.h"

#define kGravity 20

namespace game {
	
LevelManager* LevelManager::pinstance = 0;

LevelManager* LevelManager::Instance() {
	if(pinstance == 0) {
		pinstance = new LevelManager;
	}
	return pinstance;
}

LevelManager::LevelManager() {
}

LevelManager::~LevelManager() {
	delete inlevel; // Destruimos el nivel actual
}

void LevelManager::loadMap() {
	// Carga fichero tmx/xml
	tinyxml2::XMLDocument doc;
	inlevel = new game::Level();
	
	// Eleccion del mapa a cargar
	inlevel->finish = false;
	if(this->nivelActual == 0) {
		inlevel->rutamapa = RUTA_MAPA1;
		inlevel->spawnPoint.x = 200.f;
		inlevel->spawnPoint.y = 200.f;
	}
	else if(this->nivelActual == 1) {
		inlevel->rutamapa = RUTA_MAPA2;
		inlevel->spawnPoint.x = 150.f;
		inlevel->spawnPoint.y = 200.f;
	}
	else if(this->nivelActual == 2) {
		inlevel->rutamapa = RUTA_MAPA3;
		inlevel->spawnPoint.x = 150.f;
		inlevel->spawnPoint.y = 200.f;
		
	}
	else if(this->nivelActual == 3) {
		inlevel->rutamapa = RUTA_MAPA4;
		inlevel->spawnPoint.x = 150.f;
		inlevel->spawnPoint.y = 200.f;
	}
	else if(this->nivelActual == 4) {
		inlevel->rutamapa = RUTA_MAPA5;
		inlevel->spawnPoint.x = 150.f;
		inlevel->spawnPoint.y = 200.f;
	}

	doc.LoadFile(inlevel->rutamapa);
	
	// Propiedades del mapa
	tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
	// Dimensiones del mapa
	inlevel->mapSize.x  = atoi(mapElement->Attribute("width"));
	inlevel->mapSize.y  = atoi(mapElement->Attribute("height"));

	inlevel->tileSize.x = inlevel->tileSize.y = 32;

	// Tileset
	tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
	tinyxml2::XMLElement* imageElement = tilesetElement->FirstChildElement("image");
	const char *imageSource = imageElement->Attribute("source");
	
	inlevel->tileset.loadFromFile(imageSource);
        
	// GUARDAR LOS GIDS DE LOS TILES
	// Recorremos las capas
	tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
	std::vector< Tile* > tempTiles;
	
	Tile *tile;
	
	// Guarda en una matriz de columnas (capas) de Tiles los tiles
	while(layerElement) {
		// Primer tile dentro de la capa
		tinyxml2::XMLElement* tileElement = layerElement->FirstChildElement("data")->FirstChildElement("tile");
		// Para el mapa de colisiones
		int x = 0, y = 0;

		// Si es el mapa de solidos
		if(std::strcmp(layerElement->Attribute("name"), "solid") == 0) {
			// Mientras encuentre tiles
			while(tileElement) {
				int gid = atoi(tileElement->Attribute("gid"));

				// Creamos su rectangulo teniendo en cuenta su posicion (en px) dentro el nivel
				if(gid != 0) {
					sf::IntRect r(x*inlevel->tileSize.x, y*inlevel->tileSize.y, inlevel->tileSize.x, inlevel->tileSize.y);
					
					// Tile de muerte
					if(gid == 78) {
						inlevel->deathMap.push_back(r);
					}
					// Tile de terreno
					else {
						inlevel->colisionMap.push_back(r);
					}
				}
				x++;
				// Si llegamos al final del ancho bajamos una fila
				if(x >= this->inlevel->mapSize.x) {
					x = 0;
					y++;
				}
				// Nos movemos al siguiente tile
				tileElement = tileElement->NextSiblingElement("tile");
			}
		}
		// Tiles normales
		else {
			while(tileElement) {
				int gid = atoi(tileElement->Attribute("gid"));
				sf::Sprite nuevaCapa;
				nuevaCapa.setTexture(inlevel->tileset);
				inlevel->capas.push_back(nuevaCapa);

				tile = new Tile();
				tile->setGid(gid);
				// Calculamos el frame(fila, columna) de la textura asociado
				int col = gid / (inlevel->tileset.getSize().x / inlevel->tileSize.x);
				int fil = gid % (inlevel->tileset.getSize().x / inlevel->tileSize.y) - 1;
				tile->setFrame(col, fil);

				tempTiles.push_back(tile);
				
				// Nos movemos al siguiente tile
				tileElement = tileElement->NextSiblingElement("tile");
			}
			
			// Copiamos los tiles a la matriz mapa
			inlevel->tiles.push_back(tempTiles);
			tempTiles.clear();

		}
		
		// Nos movemos a la siguiente capa
		layerElement = layerElement->NextSiblingElement("layer");
	}
        
        
}

// Carga objetos y enemigos sobre el mapa
void LevelManager::loadObjects() {
	// Carga fichero tmx/xml
	tinyxml2::XMLDocument doc;
       
	doc.LoadFile(inlevel->rutamapa);
        
	// Inicializamos el poder
	inlevel->poder = new Poder(-1);

	// Nos movemos directamente al primer objetos
	tinyxml2::XMLElement* objectElement = doc.FirstChildElement("map")->FirstChildElement("objectgroup")->FirstChildElement("object");
         
	while(objectElement) {
            
		const char *t = objectElement->Attribute("type");
		
		if(std::strcmp(t, "gobo") == 0) {
			Enemy *enemigo = new Enemy(1);
			enemigo->setPosition(atof(objectElement->Attribute("x")), atof(objectElement->Attribute("y")) - enemigo->getSize().y);
			inlevel->enemigos.push_back(enemigo);
		}
		if(std::strcmp(t, "kompa") == 0) {
			Enemy *enemigo = new Enemy(2);
			enemigo->setPosition(atof(objectElement->Attribute("x")), atof(objectElement->Attribute("y")) - enemigo->getSize().y);
			inlevel->enemigos.push_back(enemigo);
		}
		if(std::strcmp(t, "llave") == 0) {
			Key *llave = new Key();
			llave->setPosition(atof(objectElement->Attribute("x")) + llave->getSize().x/2, atof(objectElement->Attribute("y")) - llave->getSize().y/2);
			llave->rel = atoi(objectElement->Attribute("name"));
			inlevel->llaves.push_back(llave);
		}
		if(std::strcmp(t, "puerta") == 0) {
			Door *puerta = new Door();
			puerta->setPosition(atof(objectElement->Attribute("x")) + puerta->getSize().x/2, atof(objectElement->Attribute("y")) - puerta->getSize().y/2);
			puerta->rel = atoi(objectElement->Attribute("name"));
			inlevel->puertas.push_back(puerta);
		}
		if(std::strcmp(t, "palanca") == 0) {
			Palanca *palanca = new Palanca();
			palanca->setPosition(atof(objectElement->Attribute("x")) + palanca->getSize().x/2, atof(objectElement->Attribute("y")) - palanca->getSize().y/2);
			palanca->rel = atoi(objectElement->Attribute("name"));
			inlevel->palancas.push_back(palanca);
		}
		if(std::strcmp(t, "antorcha") == 0) {
			Torch *antorcha = new Torch();
			antorcha->setPosition(atof(objectElement->Attribute("x")) + antorcha->getSize().x/2, atof(objectElement->Attribute("y")) - antorcha->getSize().y/2);
			antorcha->rel = atoi(objectElement->Attribute("name"));
			inlevel->antorchas.push_back(antorcha);
		}
		if(std::strcmp(t, "caja") == 0) {
			Box *caja = new Box();
			caja->setPosition(atof(objectElement->Attribute("x")) + caja->getSize().x/2, atof(objectElement->Attribute("y")) - caja->getSize().y/2);
			inlevel->cajas.push_back(caja);
		}
		if(std::strcmp(t, "plataforma") == 0) {
			Plataforma *plataforma = new Plataforma();
			plataforma->setPosition(atof(objectElement->Attribute("x")) + plataforma->getSize().x/2, atof(objectElement->Attribute("y")) - plataforma->getSize().y/2);
			plataforma->rel = atoi(objectElement->Attribute("name"));
			inlevel->plataformas.push_back(plataforma);
		}
		if(std::strcmp(t, "rejilla") == 0) {
			Rejilla *rejilla = new Rejilla();
			rejilla->setPosition(atof(objectElement->Attribute("x")) + rejilla->getSize().x/2, atof(objectElement->Attribute("y")) - rejilla->getSize().y/2);
			inlevel->rejillas.push_back(rejilla);
		}
		if(std::strcmp(t, "poder") == 0) {
			inlevel->poder->tipo = atoi(objectElement->Attribute("name"));
			inlevel->poder->active = 0;
			switch (inlevel->poder->tipo) {
				case 1: // Viento
					inlevel->poder->setFrame(1, 1, 1, 1);
					break;
				case 2: // Tierra
					inlevel->poder->setFrame(0, 2, 1, 1);
					break;
				case 3: // Agua
					inlevel->poder->setFrame(1, 2, 1, 1);
					break;
				case 4: // Fuego
					inlevel->poder->setFrame(1, 0, 1, 1);
					break;
			}
			inlevel->poder->setPosition(atof(objectElement->Attribute("x")) + inlevel->poder->getSize().x/2, atof(objectElement->Attribute("y")) - inlevel->poder->getSize().y);
		}
                
		objectElement = objectElement->NextSiblingElement("object");
	}
}

// Actualiza las posiciones de los objetos/entidades del nivel
void LevelManager::updateObjects() {
	game::LevelManager &levelManager = * game::LevelManager::Instance();
	GameEngine &engine = * GameEngine::Instance();
	
	// Movimiento de enemigos
	for ( std::vector<Enemy*>::iterator obj = levelManager.inlevel->enemigos.begin(); obj != levelManager.inlevel->enemigos.end(); obj++ ) {
		// Primero movemos al enemigo
		(*obj)->move(((*obj)->getSpeed().x)*((*obj)->clock.elapsedSeconds), ((*obj)->getSpeed().y)*((*obj)->clock.elapsedSeconds));
		(*obj)->clock.restart();

		if(!(*obj)->vivo) {
			(*obj)->setSpeed(0, (*obj)->getSpeed().y + kGravity);
		}
		else {
			// Si se han recorrido 200px
			if(abs((*obj)->getPosition().x - (*obj)->distance) > 100) {
				// Invertimos direccion y guardamos la posicion de inicio nueva
				(*obj)->setSpeed((*obj)->getSpeed().x*-1, (*obj)->getSpeed().y);
				(*obj)->distance = (*obj)->getPosition().x;
			}			
		}
		// Animacion enemigos
		(*obj)->animate();
	}

	// Movimiento de plataformas activas
	for ( std::vector<Plataforma*>::iterator obj = levelManager.inlevel->plataformas.begin(); obj != levelManager.inlevel->plataformas.end(); obj++ ) {
		if((*obj)->activa) { // Si esta activa la movemos
			(*obj)->move((*obj)->getSpeed().x*engine.clock.elapsedSeconds, (*obj)->getSpeed().y*engine.clock.elapsedSeconds);
			// Restamos la distancia
			(*obj)->distancia += (*obj)->getSpeed().x;

			if((*obj)->distancia <= 0) {
				(*obj)->activa = false;
			}
		}
	}
	
	// Movimento de cajas
	for ( std::vector<Box*>::iterator obj = levelManager.inlevel->cajas.begin(); obj != levelManager.inlevel->cajas.end(); obj++ ) {
		(*obj)->move(((*obj)->getSpeed().x) * (engine.clock.elapsedSeconds), 0);
		// Detenemos la caja para que no siga moviendose indefinidamente
		// en el siguiende tick el jugador la seguira empujando o no
		(*obj)->setSpeed(0, 0);
	}
	
	// Actualizamos el estado y animacion de las antorchas segun el tiempo
	for ( std::vector<Torch*>::iterator obj = levelManager.inlevel->antorchas.begin(); obj != levelManager.inlevel->antorchas.end(); obj++ ) {
		(*obj)->update();
		// Si se ha desactivado, cerramos las puertas asociadas
		if(!(*obj)->activa) {
			for ( std::vector<Door*>::iterator pobj = levelManager.inlevel->puertas.begin(); pobj != levelManager.inlevel->puertas.end(); pobj++ ) {
				if((*obj)->rel == (*pobj)->rel) {
					(*pobj)->activa = false;
					(*pobj)->setFrame(0, 3, 1, 1);
				}
			}
		}
	}
	
}

// Dibuja en pantalla todos los tiles del mapa
void LevelManager::draw(sf::RenderWindow &window, game::Camera *camara) {
	int j = 0; // Tile actual dentro de la capa
        
	for(int i = 0; i < inlevel->tiles.size()-1; i++) {
		j = 0;
		// Recorremos la pantalla
		for(int y = 0; y < inlevel->mapSize.y; y++) {
			for(int x = 0; x < inlevel->mapSize.x; x++) {

				// Si hay tile y estamos dentro de la vision de la camara
				if(inlevel->tiles[i][j]->getGid() > 0) {
                                    
					// Obtenemso la posicion x del tile sobre el nivel, en pixeles
					int posX = x * inlevel->tileSize.x;
					int cX1 = camara->getCenter().x - (camara->getSize().x/2) - inlevel->tileSize.x;
					int cX2 = camara->getCenter().x + (camara->getSize().x/2) + inlevel->tileSize.x;
					
					// Si el tile se encuentra en el campo de vision de la camara
					if(	(posX >= cX1) && (posX <= cX2 ) ) {
						// Nos movemos por la pantalla de 32 en 32 pixeles
						inlevel->capas[i].setPosition(x * inlevel->tileSize.x, y * inlevel->tileSize.y);

						// Creamos el frame a dibujar
						inlevel->capas[i].setTextureRect(sf::IntRect(inlevel->tiles[i][j]->getFrame().y * inlevel->tileSize.x, inlevel->tiles[i][j]->getFrame().x * inlevel->tileSize.y, inlevel->tileSize.x, inlevel->tileSize.y));
						window.draw(inlevel->capas[i]);
					}
				}
				// Siguiente tile
				j++;
			}
		}
	}
	
	// Llaves
	for ( std::vector<Key*>::iterator obj = inlevel->llaves.begin(); obj != inlevel->llaves.end(); obj++ ) {
		(*obj)->draw();
	}
	// Puertas
	for ( std::vector<Door*>::iterator obj = inlevel->puertas.begin(); obj != inlevel->puertas.end(); obj++ ) {
		(*obj)->draw();
	}
	// Palancas
	for ( std::vector<Palanca*>::iterator obj = inlevel->palancas.begin(); obj != inlevel->palancas.end(); obj++ ) {
		(*obj)->draw();
	}
	// Antorchas
	for ( std::vector<Torch*>::iterator obj = inlevel->antorchas.begin(); obj != inlevel->antorchas.end(); obj++ ) {
		//std::cout << "dibujando antorcha" << std::endl;
		(*obj)->draw();
	}	
	// Cajas
	for ( std::vector<Box*>::iterator obj = inlevel->cajas.begin(); obj != inlevel->cajas.end(); obj++ ) {
		(*obj)->draw();
	}
	// Plataformas
	for ( std::vector<Plataforma*>::iterator obj = inlevel->plataformas.begin(); obj != inlevel->plataformas.end(); obj++ ) {
		(*obj)->draw();
	}
	// Rejillas
	for ( std::vector<Rejilla*>::iterator obj = inlevel->rejillas.begin(); obj != inlevel->rejillas.end(); obj++ ) {
		(*obj)->draw();
	}
	// Poder
	if(inlevel->poder->active != -1) {
		inlevel->poder->draw();
	}
	
	// Dibujamos los objetos y enemigos
	for ( std::vector<Enemy*>::iterator obj = inlevel->enemigos.begin(); obj != inlevel->enemigos.end(); obj++ ) {
		(*obj)->draw();
	}
        
}

// Dibuja en pantalla todos los tiles del mapa
void LevelManager::drawFront(sf::RenderWindow &window, game::Camera *camara) {
	int j = 0; // Tile actual dentro de la capa

	int i = inlevel->tiles.size()-1; // Ultima capa de tiles, front
	
	// Recorremos la pantalla
	for(int y = 0; y < inlevel->mapSize.y; y++) {
		for(int x = 0; x < inlevel->mapSize.x; x++) {
			// Si hay tile y estamos dentro de la vision de la camara
			if(inlevel->tiles[i][j]->getGid() > 0) {
				// Obtenemso la posicion x del tile sobre el nivel, en pixeles
				int posX = x * 32;
				int cX1 = camara->getCenter().x - (camara->getSize().x/2) - inlevel->tileSize.x;
				int cX2 = camara->getCenter().x + (camara->getSize().x/2) + inlevel->tileSize.x;

				// Si el tile se encuentra en el campo de vision de la camara
				if(	(posX >= cX1) && (posX <= cX2 ) ) {
					// Nos movemos por la pantalla de 32 en 32 pixeles
					inlevel->capas[i].setPosition(x * 32, y * 32);

					// Creamos el frame a dibujar
					inlevel->capas[i].setTextureRect(sf::IntRect(inlevel->tiles[i][j]->getFrame().y * inlevel->tileSize.x, inlevel->tiles[i][j]->getFrame().x * inlevel->tileSize.y, inlevel->tileSize.x, inlevel->tileSize.y));
					window.draw(inlevel->capas[i]);
				}
			}
			// Siguiente tile
			j++;
		}
	}
}

// Recarga el nivel y sus objetos
void LevelManager::reload() {
	// Borramos los punteros de la matriz de tiles
	for ( std::vector< std::vector< Tile* > >::iterator it = inlevel->tiles.begin(); it != inlevel->tiles.end(); it++ ) {
		for ( std::vector<Tile*>::iterator jt = it->begin() ; jt != it->end(); jt++ ) {
			delete *jt;
		}
		(*it).clear();
    }
    inlevel->tiles.clear();
	// Borramos los enemigos
	for ( std::vector<Enemy*>::iterator obj = inlevel->enemigos.begin(); obj != inlevel->enemigos.end(); obj++ ) {
		delete *obj;
    }
    inlevel->enemigos.clear();
	// Borramos las llaves
	for ( std::vector<Key*>::iterator obj = inlevel->llaves.begin(); obj != inlevel->llaves.end(); obj++ ) {
		delete *obj;
    }
    inlevel->llaves.clear();
	// Borramos las puertas
	for ( std::vector<Door*>::iterator obj = inlevel->puertas.begin(); obj != inlevel->puertas.end(); obj++ ) {
		delete *obj;
    }
    inlevel->puertas.clear();
	// Borramos las Palancas
	for ( std::vector<Palanca*>::iterator obj = inlevel->palancas.begin(); obj != inlevel->palancas.end(); obj++ ) {
		delete *obj;
    }
    inlevel->palancas.clear();
	// Borramos las antorchas
	for ( std::vector<Torch*>::iterator obj = inlevel->antorchas.begin(); obj != inlevel->antorchas.end(); obj++ ) {
		delete *obj;
    }
    inlevel->antorchas.clear();
	// Borramos las cajas
	for ( std::vector<Box*>::iterator obj = inlevel->cajas.begin(); obj != inlevel->cajas.end(); obj++ ) {
		delete *obj;
	}
	inlevel->cajas.clear();
	// Borramos las Plataformas
	for ( std::vector<Plataforma*>::iterator obj = inlevel->plataformas.begin(); obj != inlevel->plataformas.end(); obj++ ) {
		delete *obj;
    }
    inlevel->plataformas.clear();
	// Borramos las rejillas
	for ( std::vector<Rejilla*>::iterator obj = inlevel->rejillas.begin(); obj != inlevel->rejillas.end(); obj++ ) {
		delete *obj;
    }
    inlevel->rejillas.clear();
	
	// Sprite del poder
	delete inlevel->poder;
	
	loadMap();
	loadObjects();
}

// Eliminar objetos/enemigos inactivos
void LevelManager::objCleaner() {
	// Borrado de entidades inactivas
	for ( std::vector<Key*>::iterator obj = inlevel->llaves.begin(); obj != inlevel->llaves.end();) {
		if(!(*obj)->active == -1) {
			delete *obj;
			obj = inlevel->llaves.erase(obj);
		}
		else { obj++; }
	}
	for ( std::vector<Enemy*>::iterator obj = inlevel->enemigos.begin(); obj != inlevel->enemigos.end();) {
		if(!(*obj)->vivo && (*obj)->getPosition().y > 600 + 50) {
			delete *obj;
			obj = inlevel->enemigos.erase(obj);
		}
		else { obj++; }
	}
}

}