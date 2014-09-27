/* 
 * File:   Box.h
 * Author: Rubén
 *
 * Created on 25 May 2013, 20:07
 */

#ifndef BOX_H
#define	BOX_H

#include "Entity.h"

class Box: public Entity {
public:
	Box();
	Box(const Box& orig);
	virtual ~Box();
private:

};

#endif	/* BOX_H */

