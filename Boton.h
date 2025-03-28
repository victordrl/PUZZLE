#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class Boton : public Drawable{
public:
	bool pres;
	bool over;
	vector <Texture> botonTexture;
	Sprite  botonSprite;
	Texture textrueExtra;

	Vector2f posicion;
	string imagen;
	string fotogtrama;
	string dirreccion;

	Boton(Vector2f p,const string& imag, const string& f, const string& s, int t, const Color& c);
	void update(Event event);
	void draw(RenderTarget& target, RenderStates states) const;

	//TEXTO
	Font font;
	Text mensaje;

	string textoString;
	string textoFont;
	int textoTamano;

	//void mostrarTextoBoton(RenderTarget& target, RenderStates states, const string& f, const string& s, const Vector2f& p, int t, const Color& c);

	static void textoVentana(RenderWindow& v, const string& f, const string& s, const Vector2f& p, int t, const Color& c) {
		Font font;
		font.loadFromFile("FUENTE/FONT_" + f + ".ttf");
		Text mensaje;
		mensaje.setFont(font);
		mensaje.setString(s);
		mensaje.setCharacterSize(t);
		mensaje.setOrigin(mensaje.getGlobalBounds().width / 2, (mensaje.getGlobalBounds().height / 2) + (t / 3));
		mensaje.setFillColor(c);
		mensaje.setPosition(p);

		v.draw(mensaje);
	}

	static void textoTarget(RenderTarget& target, RenderStates states, const string& f, const string& s, const Vector2f& p, int t, const Color& c) {
		Font font;
		font.loadFromFile("FUENTE/FONT_" + f + ".ttf");
		Text mensaje;
		mensaje.setFont(font);
		mensaje.setString(s);
		mensaje.setCharacterSize(t);
		mensaje.setOrigin(mensaje.getGlobalBounds().width / 2, (mensaje.getGlobalBounds().height / 2) + (t / 3));
		mensaje.setFillColor(c);
		mensaje.setPosition(p);

		target.draw(mensaje, states);
		//v.draw(mensaje);
	}
	//Text texVisual(Vector2f p, string f, string s, float t, Color c);
	
};




