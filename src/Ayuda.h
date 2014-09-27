
/* 
 * File:   Ayuda.h
 * Author: ASUS
 *
 * Created on 13 de mayo de 2013, 14:30
 */

#ifndef AYUDA_H
#define	AYUDA_H

#include "Entity.h"
#include <iostream>
#include "Clock.h"
#include "Camera.h"


class Ayuda {
public:
    Ayuda();
    Ayuda(const Ayuda& orig);
    virtual ~Ayuda();
    bool getActivo();
    void setActivo(int elec);
    void update(game::Camera camara);
    void draw();
private:
    void elegirMensaje();
    bool activo;
    bool prime;
    float blo;
    float let;
	int mensaje;
    game::Clock tiempo;
    sf::Text texto;
    sf::RectangleShape cuad;
};

#endif	/* AYUDA_H */