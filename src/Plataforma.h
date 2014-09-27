/* 
 * File:   Plataforma.h
 * Author: Ruben
 *
 * Created on 13 May 2013, 16:08
 */

#ifndef PLATAFORMA_H
#define	PLATAFORMA_H

#include "Entity.h"

class Plataforma: public Entity {
public:
	Plataforma();
	Plataforma(const Plataforma& orig);
	virtual ~Plataforma();
	
	int rel;
	float distancia;
	bool activa;
	
	void activar();
	
private:

};

#endif	/* PLATAFORMA_H */

