#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "Boton.h"
#include "Pieza.h"

using namespace std;
using namespace sf;

class Puzle : public Pieza {
public:
	int preparado;
	bool piezaColocada;
	bool star;
	bool ganador;
	Music audioW;
	Music audioL;

	Puzle(int dificul);

	int random(int a, int b);
	void salir(RenderWindow& v, RenderWindow& v2);
	void printAleatorio();
	void divImag();
	void plano();
	void cmd(Time seg);
	void cmd2(RenderWindow& v2);
	bool endGame();
	void update(Event imput, RenderWindow& ventana);
	void draw(RenderTarget& target);

protected:

	vector <int> indices;
	vector <CircleShape> planoS;
	vector <Pieza> piezaS;
	Texture originalTexture;
	Sprite  originalSprite;

	Texture planoT, marcoT, ggT, fondoT;
	Sprite  marcoS, ggS, fondoS;


	Texture fondoG;
	Sprite fondoSG;

	vector <Boton> opciones;

	int nxn;
	int imagenCodigo;
	bool inicio;
	Time tiempoMovimiento;
	bool arrastrarPieza;
	int indice;
	Vector2f centrado = { 250, 50};
	string direccionFile;
	string direccionWav;
	string codigoFile;
};
