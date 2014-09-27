/* 
 * File:   Torch.h
 * Author: Rubén
 *
 * Created on 26 May 2013, 13:48
 */

#ifndef TORCH_H
#define	TORCH_H

#include "Entity.h"
#include "Clock.h"
#include "Resources.h"

class Torch: public Entity {
public:
	Torch();
	Torch(const Torch& orig);
	virtual ~Torch();
	
	bool activa;
	int rel;
	
	void activar();
	void update();
	void animate();
	
	game::Clock tempo;
private:

};

#endif	/* TORCH_H */

