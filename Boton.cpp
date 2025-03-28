#include "Boton.h"
#include <iostream>

Boton::Boton(Vector2f p, const string& imag, const string& f, const string& s, int t, const Color& c) {
	for (int i = 0; i < 3; i++) {
		string cod = to_string(i);
		dirreccion = "BOTON/BOTON_" + imag + cod + ".png";
		
		textrueExtra.loadFromFile(dirreccion);

		botonTexture.push_back(textrueExtra);
	}
	posicion = p;
	botonSprite.setTexture(botonTexture.at(0));

	Vector2u dimencionTexture = textrueExtra.getSize();
	botonSprite.setOrigin(dimencionTexture.x / 2, dimencionTexture.y / 2);;
	botonSprite.setPosition(posicion);

	textoString = s;
	textoTamano = t;
	textoFont = f;


	over = false;
	pres = false;
}

void Boton::update(Event imput) {

	if (imput.type == Event::MouseButtonPressed) {
		if (botonSprite.getGlobalBounds().contains(imput.mouseButton.x, imput.mouseButton.y)) {
			over = true;
			botonSprite.setTexture(botonTexture.at(2));
		}
	}
	else if (imput.type == Event::MouseButtonReleased) {
		if (botonSprite.getGlobalBounds().contains(imput.mouseButton.x, imput.mouseButton.y)) {
			over = false; pres = true;
			botonSprite.setTexture(botonTexture.at(1));
		}
	}
	else if (imput.type == Event::MouseMoved) {
		if (botonSprite.getGlobalBounds().contains(imput.mouseMove.x, imput.mouseMove.y)) {
			botonSprite.setTexture(botonTexture.at(1));
		}
		else {
			botonSprite.setTexture(botonTexture.at(0));
		}
	}

	if (over) {
		botonSprite.setPosition(posicion.x, posicion.y + 5);
		botonSprite.setTexture(botonTexture.at(2));
	}
	else {
		botonSprite.setPosition(posicion);
		over = false;
	}
}

// "ARCADE.ttf", "SINGLEP-PLAYER",30,Color::White
//void Boton::mostrarTextoBoton(RenderTarget& target, RenderStates states, const string& f, const string& s, const Vector2f& p, int t, const Color& c) {
//	
//	font.loadFromFile("FUENTE/FONT_" + f);
//	mensaje.setFont(font);
//	mensaje.setString(s);
//	mensaje.setCharacterSize(t);
//	mensaje.setOrigin(mensaje.getGlobalBounds().width / 2, mensaje.getGlobalBounds().height / 2);
//	mensaje.setFillColor(c);
//	mensaje.setPosition(p);
//}

void Boton::draw(RenderTarget& target, RenderStates states) const {
	target.draw(botonSprite, states);
	Boton::textoTarget(target,states, textoFont, textoString, posicion, textoTamano, Color::White);
}
