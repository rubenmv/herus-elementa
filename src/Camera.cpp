/* 
 * File:   Camera.cpp
 * 
 * Created on 23 de abril de 2013, 10:01
 */

#include "Camera.h"
#include "GameEngine.h"
#include "Player.h"
#include "LevelManager.h"

namespace game {
    
Camera::Camera() {
}
// Constructor
Camera::Camera(sf::FloatRect rect) {
	setCenter(rect.left, rect.top);
    setSize(rect.width, rect.height);
}
//Destructor
Camera::~Camera() {
}

void Camera::setCenter(float x, float y) {
	centro.x = x;
	centro.y = y;
    view.setCenter(x, y);
}
// Restaura la camara al inicio de la pantalla
void Camera::restoreCenter() {
	GameEngine *ge1 = GameEngine::Instance();
	GameEngine *ge2 = ge1->Instance();
	GameEngine &engine = * GameEngine::Instance();
	this->setCenter(engine.windowWidth / 2, engine.windowHeight / 2);
}
void Camera::setSize(float x, float y){
	size.x = x;
	size.y = y;
	view.setSize(x, y);
}
sf::Vector2f Camera::getSize(){
	size = view.getSize();
	return size;
}
sf::Vector2f Camera::getCenter() {
	centro = view.getCenter();
	return centro;
}
void Camera::move(float x, float y){
	view.move(x, y);
}
void Camera::display() {
    GameEngine *ge1 = GameEngine::Instance();
    GameEngine *ge2 = ge1->Instance();
    GameEngine &engine = * GameEngine::Instance();
    
    engine.window.setView(view);
}

void Camera::update() {
    GameEngine *ge1 = GameEngine::Instance();
    GameEngine *ge2 = ge1->Instance();
    GameEngine &engine = * GameEngine::Instance();
    game::Player *p1 = game::Player::Instance();
    game::Player *p2 = p1->Instance();
    game::Player &player = * game::Player::Instance();
    game::LevelManager *lf1 = game::LevelManager::Instance();
    game::LevelManager *lf2 = lf1->Instance();
    game::LevelManager &levelManager = * game::LevelManager::Instance();

    // Solo se mueve si el jugador esta a cierta distancia el inicio y el final
    if(player.vivo && player.getPosition().x - (engine.windowWidth/2) > 0  &&
       ((player.getPosition().x + (engine.windowWidth/2)) < (levelManager.inlevel->mapSize.x * 32)))
    {
		if(player.oldPos.x != player.getPosition().x) {
				move(player.getSpeed().x*engine.clock.elapsedSeconds, 0.f);
		}
    }
}

}