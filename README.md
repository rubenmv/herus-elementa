herus-elementa
==============

Mi primer juego de plataformas que hice en C++ y utilizando la librería multimedia SFML.

Este proyecto se realizó para la asignatura "Fundamentos de los videojuegos" del Grado en Ingeniería Multimedia de la Universida de Alicante.

El proyecto consistió en realizar un videojuegos entres 4 personas desde el diseño inicial de este hasta su implementación final, dividiendo el proceso en 3 entregas. Todo esto plasmado en un Game Design Document (GDD).

El proyecto se realizó por el grupo **4TheLulZ** compuesto por:
* Rubén Martínez Vilar
* Begoña Morillas Guijarro
* Alexis Martín Santacruz
* Jose Luís Contreras Martínez

La documentación del proyecto se puede encontrar en la carpeta "doc" como "GDD.pdf".

Capturas
--------
![screenshot 1](/doc/screenshots/screenshot-1.jpg)
![screenshot 1](/doc/screenshots/screenshot-2.png)
![screenshot 1](/doc/screenshots/screenshot-3.jpg)

Instalación
-----------
Se incluye un instalador (herus-elementa-setup.exe) que ha sido testeado en Windows 7.

El respositorio incluye el proyecto completo listo para abrirlo con Code::Blocks 13.12 (la versión que incluye MinGW 4.7). Se incluyen todas las librerías necesarias para simplemente abrirlo y compilar.

Bugs
----
Este juego contiene muchos errores y bugs de novatos, pero en general es jugable de principio a fin.

* Si el juego se rompe al terminar un nivel simplemente volver a abrirlo y entrar en continuar y escoger el siguiente nivel (el último que sea seleccionable).
* A veces algunos enemigos no se muestran.
* A veces algunos textos no se muestran.
* Las colisiones estan medios rotas, son pequeños errores que puede que arregle algún día que me apetezca retomar este proyecto.

Software
--------
Este juego se programó utilizando el IDE Code::Blocks bajo C++ y la librería SFML.
Los mapas y la colocación de items y enemigos se realizaron mediante el editor de mapas Tiled (http://www.mapeditor.org/).

Licencia
--------
SFML se basa en la licencia zlib/png.
http://sfml-dev.org/license.php

El resto del código lo comparto bajo la GNU GPLv2
The rest of the code is licensed under the GNU GPL v3 (http://www.gnu.org/licenses/gpl-2.0.txt)

Los assets se comparten bajo la Creative Commons Attribute Share-Alike 4.0 International (http://creativecommons.org/licenses/by-sa/4.0/)
