/* 
 * File:   Door.h
 * Author: Ruben
 *
 * Created on 12 May 2013, 20:22
 */

#ifndef DOOR_H
#define	DOOR_H

#include "Entity.h"

class Door: public Entity {
public:
	Door();
	Door(const Door& orig);
	virtual ~Door();
	
	int rel;
	bool activa;
	
	void activar();
	
private:

};

#endif	/* DOOR_H */

