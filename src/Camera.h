/* 
 * File:   Camera.h
 *
 * Created on 23 de abril de 2013, 10:00
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include "SFML/Graphics.hpp"

namespace game {
class Camera {
	public:
		Camera();
		Camera(sf::FloatRect);
		virtual ~Camera();

		sf::View view;
		void setCenter(float x, float y);
		void restoreCenter();
		void setSize(float x, float y);
		void display();
        void update();

		sf::Vector2f getCenter();
		sf::Vector2f getSize();

		void  move(float x, float y);

	private:
		sf::Vector2f centro;
		sf::Vector2f size;
};
}
#endif	/* Camera_H */

