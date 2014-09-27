/* 
 * File:   Key.h
 * Author: Ruben
 *
 * Created on 09 May 2013, 19:47
 */

#ifndef KEY_H
#define	KEY_H

#include "Entity.h"
	
class Key: public Entity {
public:
	Key();
	Key(const Key& orig);
	virtual ~Key();
	
	int rel;
	int active; // -1 = inactiva, 0 = parada, 1 = animacion
private:

};


#endif	/* KEY_H */

