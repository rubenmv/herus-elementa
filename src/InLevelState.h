/* 
 * File:   InLevelState.h
 * Author: Rubén
 *
 * Created on 24 May 2013, 23:17
 */

#include "GameState.h"
#include "Camera.h"
#include "HUD.h"

#ifndef LEVELSTATE_H
#define	LEVELSTATE_H

class InLevelState: public GameState {
	public:
		void Init();
		void Cleanup();

		void Pause();
		void Resume();

		void HandleEvents(GameManager* game);
		void Update(GameManager* game);
		void Draw(GameManager* game);

		static InLevelState* Instance() {
			return &m_InLevelState;
		}
		
		virtual ~InLevelState();	
	protected:
		InLevelState();
		InLevelState(const InLevelState& orig);
	private:
		static InLevelState m_InLevelState;
		bool salir;
		bool volver;
		bool avanzar;
		
		game::Camera *camara;
};

#endif	/* LEVELSTATE_H */

