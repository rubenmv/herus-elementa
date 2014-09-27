/* 
 * File:   InLevelState.cpp
 * Author: Ruben Martinez Vilar
 * 
 * Created on 24 May 2013, 23:17
 */

#include "InLevelState.h"
#include "MenuState.h"
#include "SFaseState.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "GameEngine.h"
#include "LevelManager.h"
#include "Player.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SaveManager.h"
#include "Resources.h"
#include "CreditsState.h"

InLevelState InLevelState::m_InLevelState;

InLevelState::InLevelState() {}

InLevelState::InLevelState(const InLevelState& orig) {
}

InLevelState::~InLevelState() {
}

void InLevelState::Init() { // Inicializa el estado
	avanzar = false;
    salir = false;
	volver = false;
	

	GameEngine &engine = * GameEngine::Instance();
	// Recoge/crea una instancia de nivel
	game::LevelManager &levelManager = * game::LevelManager::Instance();
	// Jugador
	game::Player &player = * game::Player::Instance();
		
	// Cargamos el primer jefe
	levelManager.loadMap();
	levelManager.loadObjects();

	player.setSpawn(levelManager.inlevel->spawnPoint.x, levelManager.inlevel->spawnPoint.y);
	player.init();
	
	if(levelManager.nivelActual >= 1) {
		player.powers[0] = 0;
	}
	if(levelManager.nivelActual >= 2) {
		player.powers[1] = 0;
	}
	if(levelManager.nivelActual >= 3) {
		player.powers[2] = 0;
	}
	if(levelManager.nivelActual >= 4) {
		player.powers[3] = 0;
	}
	
	// Creamos la view
	camara = new game::Camera(sf::FloatRect(engine.windowWidth / 2, engine.windowHeight / 2, engine.windowWidth, engine.windowHeight));
	
	HUD &hud = * HUD::Instance();
	// Primer mensaje de ayuda
	if(levelManager.nivelActual == 0) {
		hud.ayuda->setActivo(0);
	}
}

void InLevelState::Cleanup() { // Vacia el estado

	delete camara;
}

void InLevelState::Pause() { // Pausa el estado

}

void InLevelState::Resume() { // Continua el estado

}

void InLevelState::HandleEvents(GameManager* gameman) { // Controla los eventos de Input
	GameEngine &engine = * GameEngine::Instance();
	game::LevelManager &levelManager = * game::LevelManager::Instance();
	game::Input &input = * game::Input::Instance();
	game::Player &player = * game::Player::Instance();
	HUD &hud = * HUD::Instance();
		
    //Bucle de obtención de eventos
    sf::Event event;
    if(engine.window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed: // Si se cierra la ventana
                gameman->Quit();
                break;
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					volver = true;
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
					levelManager.reload();
					player.setSpawn(200.f, 200.f);
					player.init();
					camara->setCenter(engine.windowWidth / 2, engine.windowHeight / 2);
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
					levelManager.reload();
					player.setSpawn(3200.f, 200.f);
					player.init();
					camara->setCenter(2900.f, engine.windowHeight / 2);
				}
				// PODERES
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					player.togglePower(0);
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					player.togglePower(1);
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
					player.togglePower(2);
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
					player.togglePower(3);
				}
				// AYUDA
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                    hud.ayuda->setActivo(-1);
                }
			break;     
        }
    }
	
	// Recogemos otras teclas para movimiento de jugador
	input.getInput();
}

void InLevelState::Update(GameManager* gameman) { // Actualiza el estado del juego
	
	// Comprobamos si se ha llegado al final del nivel
	game::LevelManager &levelManager = * game::LevelManager::Instance();
	if(levelManager.inlevel->finish) {
		SaveManager &saveMan = * SaveManager::Instance();
		int nivel = levelManager.nivelActual + 1;
		saveMan.save(nivel); // Guarda el numero del siguiente nivel

		camara->restoreCenter();
		camara->display();
		levelManager.inlevel->~Level();
		
		// Creditos del final
		if(levelManager.nivelActual == 4) {
			gameman->ChangeState(CreditsState::Instance());
		}
		// Devuelve a pantalla de seleccion de fase
		else {
			gameman->ChangeState(SFaseState::Instance());
		}
        
	}
	
	if(volver) {
		camara->restoreCenter();
		camara->display();
		volver = false;
		levelManager.inlevel->~Level();
		gameman->ChangeState(SFaseState::Instance());
	}
	else if(salir) {
        salir = false;
        gameman->Quit();
    }
	else {
		GameEngine &engine = * GameEngine::Instance();
		
		game::CollisionManager &collision = * game::CollisionManager::Instance();
		game::Player &player = * game::Player::Instance();
		
		player.update();
		// Una vida menos, contamos hasta reinicio
		if(!player.vivo && player.getVidas() > 0) {
			player.setSpeed(0, player.getSpeed().y);

			if(player.clock.getSeconds() > 1.5f) {
				levelManager.reload(); // Recarga el nivel actual
				player.respawn();
				if(player.getPosition().x >= engine.windowWidth/2) {
					camara->setCenter(player.getPosition().x, engine.windowHeight / 2);
				}
				else {
					camara->setCenter(engine.windowWidth/2, engine.windowHeight / 2);
				}
			}
		}
		// No quedan vidas, GAME OVER
		else if(!player.vivo) {
			player.setSpeed(0, player.getSpeed().y);
			for(int i = 0; i < 4; i++) {
				player.powers[i] = -1;
			}
			
			camara->restoreCenter();
			camara->display();
			levelManager.inlevel->~Level();
            gameman->ChangeState(SFaseState::Instance());
		}
		// Actualizamos las posiciones de algunas entidades del nivel
		levelManager.updateObjects();
		/* COLISIONES */
		collision.handleCollisions();
		// Borramos las entidades inactivas
		levelManager.objCleaner();  
		// Animacion jugador
		player.animate();
		/* CAMARA */
        camara->update();
		
		HUD &hud = * HUD::Instance();
		hud.update(*camara);
	}
}

void InLevelState::Draw(GameManager* gameman) { // Realiza los draws correspondientes en game->screen
	GameEngine &engine = * GameEngine::Instance();
	game::LevelManager &levelManager = * game::LevelManager::Instance();
	game::Player &player = * game::Player::Instance();
	HUD &hud = * HUD::Instance();
	
    camara->display();
	// Dibujado del nivel junto sus objetos
	levelManager.draw(engine.window, camara);
	// Jugador y jefe
	player.draw();
	hud.draw();
	 // Los tiles que van por delante de todo lo demás, aunque no haya ninguno
	levelManager.drawFront(engine.window, camara);

}