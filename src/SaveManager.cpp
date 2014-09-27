/* 
 * File:   SaveManager.cpp
 * Author: Rubén
 * 
 * Created on 24 May 2013, 01:31
 */

#include <iostream>
#include <fstream>
#include "SaveManager.h"

SaveManager* SaveManager::pinstance = 0;

SaveManager* SaveManager::Instance() {
    if(pinstance == 0) {
            pinstance = new SaveManager;
    }
    return pinstance;
}

SaveManager::SaveManager() {
}

SaveManager::SaveManager(const SaveManager& orig) {
}

SaveManager::~SaveManager() {
}

// Guarda en un fichero el numero del nivel alcanzado
void SaveManager::save(int n) {
	std::ofstream fichero ("save");

	if (fichero.is_open()) {
		fichero << n;
		fichero.close();
	}
	else {
		std::cout << "Hubo un problema al guardar partida. No se pudo abrir el fichero";
	}
}

// Carga desde un fichero el numero del nuvel alcanzado
int SaveManager::load() {
	std::ifstream fichero ("save");
	
	int level;
	
	if (fichero.is_open()) {
		fichero >> level;
		fichero.close();
		return level;
	}
	else {
		save(0);
	}
	
	return 0; // Si no existe el fichero el nivel es el de tutorial
}