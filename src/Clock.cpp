/* 
 * File:   Clock.cpp
 * Author: Ruben
 * 
 * Created on 07 May 2013, 16:45
 */

#include "Clock.h"

namespace game {

game::Clock::Clock() {
	clock.restart();
}


Clock::~Clock() {
}
	
float Clock::getSeconds() {
	return clock.getElapsedTime().asSeconds();
}
float Clock::getMiliseconds() {
	return clock.getElapsedTime().asMilliseconds();
}
void Clock::restart() {
    elapsedSeconds = clock.restart().asSeconds();
}

}