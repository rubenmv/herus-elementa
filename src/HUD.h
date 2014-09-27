/*
 * File:   HUD.h
 * Author: Ruben
 *
 * Created on 27 May 2013, 12:09
 */

#ifndef HUD_H
#define	HUD_H

#include "SFML/Graphics/Text.hpp"
#include "Entity.h"
#include "Camera.h"
#include "Text.h"
#include "Ayuda.h"

class HUD {
public:
	static HUD* Instance();
	virtual ~HUD();

	void update(game::Camera camara);
	void draw();

	game::Text *textoVidas;
	Entity *heart;
	Ayuda *ayuda;
private:
	HUD();
	HUD(const HUD& orig);
	HUD &operator= (const HUD &);
    static HUD* pinstance;

};

#endif	/* HUD_H */

