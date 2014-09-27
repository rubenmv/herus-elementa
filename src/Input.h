/* 
 * File:   Input.h
 * Author: Ruben
 *
 * Created on 12 May 2013, 20:46
 */

#ifndef INPUT_H
#define	INPUT_H

namespace game {

class Input {
public:
	static Input* Instance();
	virtual ~Input();

	bool left;
	bool right;
	bool up;
	bool down;
	
	void getInput();

private:
	Input();
	Input(const Input &);
	
	Input &operator= (const Input &);
	static Input* pinstance;
};
	
}
#endif	/* INPUT_H */

