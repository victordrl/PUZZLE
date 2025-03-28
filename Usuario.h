#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include "Boton.h"

using namespace std;
using namespace sf;


class Usuario {
public:

	string nick;
	float puntajeD;
	float puntajeN;
	float puntajeF;

	vector <Usuario> usuariosRegistrados;
	vector <Boton> opciones;

	Font fuente;
	Text titulo;
	Texture fondoT;
	Sprite fondoS;

	bool mensaje;
	
	Font f;
	Text tleido;
	Vector2f posTexto;
	string tmensaje;
	string texto;


	Usuario();

	void login();
	void loginUpdate(Event input);
	bool loginConfirmed(string buscar, vector <Usuario>& logeados);
	void loginDraw(RenderTarget& target, RenderWindow& v);
	void loginCase0(RenderWindow& v, RenderWindow& v2);
	void loginCase1(RenderWindow& v, vector <Usuario>& logeados);


	void regis();
	void regisUpdate(Event input);
	bool regisConfirmed(string buscar, vector <Usuario>& logeados);
	void regisDraw(RenderTarget& target, RenderWindow& v);
	void regisCase0(RenderWindow& v, RenderWindow& v2);
	void regisCase1(RenderWindow& v, vector <Usuario>& logeados);

	void rankinFacil();
	void facildraw(RenderWindow& v);
	void rankinNormal();
	void normaldraw(RenderWindow& v);
	void rankinDificl();
	void dificildraw(RenderWindow& v);

	void mostrar();
	void toupperString(string& cadena);
	int op();
	void saveFileVec(const vector<Usuario>& vec, const string& archivo);

	static vector<Usuario> loadFileVec(const string& archivo) {
		vector<Usuario> vec;
		ifstream ifsArchvio(archivo);
		if (ifsArchvio) {
			Usuario obj;
			while (ifsArchvio >> obj) {
				vec.push_back(obj);
			}
		}
		return vec;
	}

	friend std::ostream& operator<<(ostream& os, const Usuario& obj);
	friend std::istream& operator>>(istream& is, Usuario& obj);
};
