#ifndef ENTITY_H
#define ENTITY_H

#include "SFML/Graphics.hpp"
#include "Clock.h"

class Entity {
	public:
		Entity();						
		Entity(const char *texture_path); 
		virtual ~Entity();
                
		bool  isLoaded;
		sf::Sprite  sprite;
		sf::Texture textura;
		void setSprite(const char *path);
		void setSize(unsigned int x, unsigned int y);
		void setPosition(float x, float y);
		void setCentro(float x, float y);
		void setSpeed(float x, float y);
		void setFrame(int row, int frame, float scaleX, float scaleY);
		void animate();
		void update();
		
		sf::Vector2f getPosition();
		sf::Vector2u getSize();
		sf::Vector2f getSpeed();
		sf::IntRect getBounds();
		
		void draw();
		void move(float x, float y);
		void fade(int seg);
		
		// Reloj para animaciones
		game::Clock clock;
		int frame; // Frame actual en la fila de la animacion

	protected:
		sf::Vector2u size;
		sf::Vector2f speed;
};

#endif