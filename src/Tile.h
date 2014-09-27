#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"

class Tile {
	public:
		Tile();
		virtual ~Tile();		         
		
		int getGid();
		sf::Vector2i position;
		sf::Vector2i getFrame();
		
		sf::Vector2i getPosition();

		void setGid(int gid);
		void setFrame(int x, int y);
		void setPosition(int x, int y);
		
	private:
		int gid;
		// Frame de la textura asociado
		sf::Vector2i frame;
		
};

#endif