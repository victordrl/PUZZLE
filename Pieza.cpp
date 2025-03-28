#include "Pieza.h"

Pieza::Pieza() {
	piezaTezure.loadFromFile("DEFAULT/DEFAULT.png");
	piezaSprite.setTexture(piezaTezure);

	bandera = true;
	ordenada = false;
}

float Pieza::randomF(float a,  float b) {
	random_device rand;
	mt19937 generator(rand());						//CREA NUMERO ALEATORI

	uniform_real_distribution<float> rago(a, b);    //ENTRE UN RANGO A Y B

	int randomFloat = rago(generator);				//DEVUELVE UN ALEATORIO
	return randomFloat;
}

void Pieza::colicion(int l, int u, int r, int d) {
	int x = piezaSprite.getPosition().x;
	int y = piezaSprite.getPosition().y;
	int xx = piezaSprite.getGlobalBounds().width;
	int yy = piezaSprite.getGlobalBounds().height;

	if (x - (xx / 2) <= l) {
		piezaSprite.setPosition((xx / 2), y);
		animation = false;
	}
	if (y - (yy / 2) <= u) {
		piezaSprite.setPosition(x, (yy / 2));
		animation = false;
	}
	if (x + (xx / 2) >= r) {
		piezaSprite.setPosition(r - (xx / 2), y);
		animation = false;
	}
	if (y + (yy / 2) >= d) {
		piezaSprite.setPosition(x, d - (yy / 2));
		animation = false;
	}

	if (x + (xx / 2) >= r && y + (yy / 2) >= d) {
		piezaSprite.setPosition(r - (xx / 2), d - (yy / 2));
		animation = false;
	}
	if (x - (xx / 2) <= l && y + (yy / 2) >= d) {
		piezaSprite.setPosition((xx / 2), d - (yy / 2));
		animation = false;
	}
	if (x + (xx / 2) >= r && y - (yy / 2) <= 0) {
		piezaSprite.setPosition(r - (xx / 2), (yy / 2));
		animation = false;
	}
	if (x - (xx / 2) <= u && y - (yy / 2) <= 0) {
		piezaSprite.setPosition((xx / 2), (yy / 2));
		animation = false;
	}
}

void Pieza::animate(bool& inicio, Time seg, Time tiempoMovimiento) {
	if (inicio && seg.asSeconds() <= tiempoMovimiento.asSeconds() + 2.5 && animation) {
		if (bandera) {
			speed.x = randomF(-15.5, 15.5);
			speed.y = randomF(-15.5, 15.5);
			bandera = false;
		}
		animation = inicio;
		piezaSprite.move(speed);

		colicion(0, 20, 900, 400);
	}
}

void Pieza::draw(RenderTarget& target, RenderStates states) const {
	target.draw(piezaSprite, states);
}