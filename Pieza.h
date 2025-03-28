#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

using namespace std;
using namespace sf;

class Pieza : public Drawable {
public:
	Texture piezaTezure;
	Sprite piezaSprite;

	Pieza();

	float randomF(float a, float b);
	void animate(bool& inicio, Time seg, Time tiempoMovimiento);
	void colicion(int l, int u, int r, int d);
	void draw(RenderTarget& target, RenderStates states) const;

	bool bandera;
	bool animation;
	bool ordenada;
	Vector2f speed;
};

