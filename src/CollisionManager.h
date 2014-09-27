#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "SFML/Graphics.hpp"
#include <string>

namespace game {
	
class CollisionManager {
	public:
		static CollisionManager* Instance();
		virtual ~CollisionManager();
		
		
		bool checkCollision(sf::IntRect r1, sf::IntRect r2);
		// Maneja todas las colisiones del nivel actual
		void handleCollisions();
		// Si true, la colision es por la izquierda, false por la derecha
		bool left;
		bool right;
		// Si true, la colision es por arriba, false por abajo
		bool top;
		bool bottom;

	private:
		CollisionManager();
		CollisionManager(const CollisionManager &);
		CollisionManager &operator= (const CollisionManager &);
		static CollisionManager* pinstance;
};

}
#endif