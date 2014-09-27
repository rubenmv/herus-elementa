/* 
 * File:   Poder.h
 * Author: Ruben
 *
 * Created on 14 May 2013, 16:12
 */

#ifndef PODER_H
#define	PODER_H

#include "Entity.h"

class Poder: public Entity {
public:
	Poder(const int t);
	Poder(const Poder& orig);
	virtual ~Poder();
	
	int tipo; // 1 = viento, 2 = tierra...
	int active; // -1 = inactiva, 0 = parada, 1 = animacion
	
	void animate();
private:

};

#endif	/* PODER_H */

