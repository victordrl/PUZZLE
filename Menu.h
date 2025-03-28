#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Boton.h"
#include "Usuario.h"
#include "Puzle.h"

using namespace sf;
using namespace std;

class Menu {
public:
	vector <Boton> opciones;
	vector <Usuario> logeados;
	int dificult;

	Texture fondoT;
	Sprite fondoS;
	string imagen;

	Menu(string imagen,Vector2f p0, const string& s0, Vector2f p1, const string& s1, Vector2f p2, const string& s2, Vector2f p3, const string& s3, Vector2f p4, const string& s4, Vector2f p5, const string& s5, Vector2f p6, const string& s6, const string& t1, const string& t2, const string& t3, const string& f1, const string& f2);

	bool ventanaOpen();
	void rankin(RenderWindow& v);
	void config(RenderWindow& vm);
	void login(RenderWindow& v, RenderWindow& vm);
	void regis(RenderWindow& v);
	void game(RenderWindow& v, vector <Usuario>& l);
	void multi(RenderWindow& v, vector <Usuario>& l);
	//void ranking();

	void guardarlogeados(Usuario& archivo);
	void salir(RenderWindow& v, RenderWindow& v2);
	void entrar(RenderWindow& v, RenderWindow& v2);
	int op();
	void update(Event imput);
	void draw(RenderTarget& target);

};

