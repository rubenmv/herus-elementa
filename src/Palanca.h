/* 
 * File:   Palanca.h
 * Author: Ruben
 *
 * Created on 13 May 2013, 16:08
 */

#ifndef PALANCA_H
#define	PALANCA_H

#include "Entity.h"

class Palanca: public Entity {
public:
	Palanca();
	Palanca(const Palanca& orig);
	virtual ~Palanca();
	
	bool activa;
	int rel;
	
	void activar();
	
private:

};

#endif	/* PALANCA_H */

