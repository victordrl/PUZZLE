//ROMPECABEZAS

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <algorithm>
#include "Menu.h"
#include "Puzle.h"
#include "Boton.h"
#include <iostream>

using namespace std;
using namespace sf;

#define HEIGHT 500	//HORIZONTAL
#define WIDTH 900	//VERTICAL

int main() {

	//CREA VENTANA
	RenderWindow ventana(VideoMode(WIDTH, HEIGHT), "PUZZLE");
	ventana.setFramerateLimit(60);

	Menu m("FONDO", { 350, 330 }, "SNGLE", {550,330}, "MULTI", {90,430}, "CONFIG", {810,430}, "RANKING", {-110,-110}, "", {-110,-110}, "", {-110,-110}, "", "TRON_", "CIRCULAR_", "CUADRO_", "ARCADE", "ARCADE");
	Usuario archivo;

	//GAME LOOP DEL JUEGO
	while (ventana.isOpen()) {
		Event event;
		while (ventana.pollEvent(event)) {
			if (event.type == Event::Closed) {
				m.guardarlogeados(archivo); m.logeados.clear();
				ventana.close();
			}
			//LEER IMPUTS UPDATE
			if (!m.ventanaOpen()) {
				//cout<< endl << " EVENTO MENU "<<endl ;
				m.update(event);
			}
			switch (m.op()) {
			case 0: if (m.logeados.size() == 1) { m.game(ventana, m.logeados); } m.opciones[0].pres = false; cout << " BOTON 0"; break;
			case 1: if (m.logeados.size() == 2) { m.multi(ventana, m.logeados); } m.opciones[1].pres = false; cout << " BOTON 1"; break;
			case 2: m.config(ventana); m.opciones[2].pres = false; cout << " BOTON 2"; break;
			case 3: m.rankin(ventana); m.opciones[3].pres = false; cout << " BOTON 3"; break;
			}
		}
		//EJECUTAR LOS COMANDOS CMD

		//UACTUALIZA LOS ESTADOS DEL JUEGO

		//REDIBUJADO
		if (!m.ventanaOpen()) {
			ventana.clear();
			m.draw(ventana);
			Boton::textoVentana(ventana, "LEGADO", "PUZZLE", { 450, 210 }, 80, Color::White);
			ventana.display();
			//cout << " MENU DRAW ";
		}
	}
	return 0;
}
