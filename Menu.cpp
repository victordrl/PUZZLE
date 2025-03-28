#include "Menu.h"
#include <iostream>

#define HEIGHT 500	//HORIZONTAL
#define WIDTH 900	//VERTICAL

Menu::Menu(string imagen, Vector2f p0 , const string& s0, Vector2f p1, const string& s1, Vector2f p2, const string& s2, Vector2f p3, const string& s3, Vector2f p4, const string& s4, Vector2f p5, const string& s5,  Vector2f p6, const string& s6, const string& t1, const string& t2, const string& t3, const string& f1, const string& f2) {
	Boton p(p0, t1, f1, s0, 30,Color::White);
	opciones.push_back(p);
	Boton pu(p1, t1, f1, s1, 30, Color::White);
	opciones.push_back(pu);
	Boton c(p2, t2, f1, s2, 30, Color::White);
	opciones.push_back(c);
	Boton t(p3, t2, f1, s3, 30, Color::White);
	opciones.push_back(t);
	Boton x(p4, t2, f1, s4, 30, Color::White);
	opciones.push_back(x);
	Boton y(p5, t3, f1, s5, 20, Color::White);
	opciones.push_back(y);
	Boton z(p6, t3, f1, s6, 20, Color::White);
	opciones.push_back(z);

	fondoT.loadFromFile("DEFAULT/" + imagen + ".png");
	fondoS.setTexture(fondoT);

	dificult = 3;
}

void Menu::salir(RenderWindow& v, RenderWindow& v2) {
	int v2x = v2.getPosition().x;
	int v2y = v2.getPosition().y;
	v.setPosition(Vector2i(v2x, v2y));
	v.setVisible(true);
	v2.close();
	//cout << " MENU CRRADO ";
}

void Menu::entrar(RenderWindow& v, RenderWindow& v2) {
	int vx = v.getPosition().x;
	int vy = v.getPosition().y;
	v.setVisible(false);
	v2.setPosition(Vector2i(vx, vy));
}

bool Menu::ventanaOpen() {
	for (const Boton& b : opciones) {
		if (b.pres) {
			return true;
		}
	}
	return false;
}

void Menu::guardarlogeados(Usuario& archivo) {
	archivo.usuariosRegistrados = Usuario::loadFileVec("REGISTRO DE JUGADORES.txt");
	for (const Usuario& user : logeados) {
		archivo.usuariosRegistrados.push_back(user);
	}
	archivo.saveFileVec(archivo.usuariosRegistrados, "REGISTRO DE JUGADORES.txt");
	this->logeados.clear();
}

void Menu::login(RenderWindow& v, RenderWindow& vm) {
	RenderWindow v2(VideoMode(WIDTH, HEIGHT), "LOGIN");
	v2.setFramerateLimit(60);
	this->entrar(v, v2);

	Usuario l;
	l.login();
	 
	while (v2.isOpen()) {
		Event input;
		while (v2.pollEvent(input)) {
			if (input.type == Event::Closed) {
				this->guardarlogeados(l); this->logeados.clear();
				v2.close();
			}
			//LEER IMPUTS UPDATE
			l.loginUpdate(input);
			switch (l.op()) {
			case 0: 
				l.loginCase0(v, v2);
				cout << " BOTON 0 ";
				break;

			case 1:
				l.loginCase1(v2, logeados);
				salir(v, v2);
				cout << " BOTON 1 ";
				break;

			}
		}
		//EJECUTAR LOS COMANDOS CMD

		//UACTUALIZA LOS ESTADOS DEL JUEGO

		//REDIBUJADO
		v2.clear();
		l.loginDraw(v2,v2);
		v2.display();
	}
}

void Menu::regis(RenderWindow& v) {
	RenderWindow v2(VideoMode(WIDTH, HEIGHT), "REGIST");
	v2.setFramerateLimit(60);
	int vx = v.getPosition().x;
	int vy = v.getPosition().y;
	v2.setPosition(Vector2i(vx, vy));
	v.setVisible(false);

	Usuario r;
	Usuario archivo;
	r.regis();

	while (v2.isOpen()) {
		Event input;
		while (v2.pollEvent(input)) {
			if (input.type == Event::Closed) {
				this->guardarlogeados(archivo); this->logeados.clear();
				v2.close();
			}
			//LEER IMPUTS UPDATE
			r.regisUpdate(input);
			switch (r.op()) {
			case 0:
				r.regisCase0(v, v2);
				cout << " BOTON 0 ";
				break;

			case 1:
				r.regisCase1(v2, logeados);
				cout << " BOTON 1 ";
				break;

			}
		}
		//EJECUTAR LOS COMANDOS CMD

		//UACTUALIZA LOS ESTADOS DEL JUEGO

		//REDIBUJADO
		v2.clear();
		r.regisDraw(v2,v2);
		v2.display();
	}
}

void Menu::game(RenderWindow& v ,vector <Usuario>& l) {
	RenderWindow v2(VideoMode(WIDTH, HEIGHT), "GAME");
	v2.setFramerateLimit(60);
	this->entrar(v, v2);

	Puzle p(this->dificult);
	Usuario archivo;

	Clock cicloTime;
	Time segTotal;
	Time cronometroPuzzle;

	while (v2.isOpen()) {
		Event input;
		while (v2.pollEvent(input)) {
			if (input.type == Event::Closed) {
				this->guardarlogeados(archivo); this->logeados.clear();
				p.salir(v, v2);
			}
			//LEER IMPUTS UPDATE
			p.update(input,v2);
		}
		//EJECUTAR LOS COMANDOS CMD

		Time seg = cicloTime.getElapsedTime();
		cicloTime.restart();
		segTotal += seg;

		if (p.star) {
			cronometroPuzzle += seg;
		}
		float cronometro = cronometroPuzzle.asSeconds();
		string cronometroP = to_string(cronometro);

		p.cmd(segTotal);
		cout << segTotal.asSeconds();

		//UACTUALIZA LOS ESTADOS DEL JUEGO
		if (p.endGame()) {
			p.star = false;
			cronometroPuzzle = cicloTime.restart();
			p.ganador = true;
			switch (this->dificult) {
			case 3: if (cronometro < l[0].puntajeF) { l[0].puntajeF = cronometro; } break;
			case 5: if (cronometro < l[0].puntajeN) { l[0].puntajeN = cronometro; } break;
			case 7: if (cronometro < l[0].puntajeD) { l[0].puntajeD = cronometro; } break;
			}
			v2.clear();
			p.draw(v2); 
			p.cmd2(v2);
			v2.display();
			sleep(seconds(5.0f));
			p.salir(v, v2);
			v2.close();

			cout << l[0].puntajeF;
		}
		//REDIBUJADO 
		v2.clear();
		p.draw(v2);
		Boton::textoVentana(v2, "DIGITAL", cronometroP, { 450,25 }, 25, Color::White);
		v2.display();
	}
}

void Menu::multi(RenderWindow& v, vector <Usuario>& l) {
	//RenderWindow v2(VideoMode(WIDTH, HEIGHT), "GAME");
	//RenderWindow v3(VideoMode(WIDTH, HEIGHT), "GAME2");
	//v2.setFramerateLimit(60);
	//int vx = v.getPosition().x;
	//int vy = v.getPosition().y;
	//v2.setPosition(Vector2i(vx, vy));
	//v3.setPosition(Vector2i(vx+900, vy));
	//v.setVisible(false);

	//Puzle p(this->dificult);
	//Puzle p2(this->dificult); 
	//Usuario archivo;

	//Clock cicloTime;
	//Time segTotal;
	//Time cronometroPuzzle1, cronometroPuzzle2;

	//bool turno = true;

	//while (v2.isOpen()) {
	//	Event input;
	//	if (turno) {
	//		while (v2.pollEvent(input)) {
	//			if (input.type == Event::Closed) {
	//				this->guardarlogeados(archivo); this->logeados.clear();
	//				p.salir(v, v2);
	//			}
	//			//LEER IMPUTS UPDATE
	//			p.update(input, v2);
	//			if (p.piezaColocada) {
	//				turno = false;
	//				p.piezaColocada = false;
	//			}
	//		}
	//	}
	//	else {
	//		while (v3.pollEvent(input)) {
	//			if (input.type == Event::Closed) {
	//				this->guardarlogeados(archivo); this->logeados.clear();
	//				p2.salir(v, v3);
	//			}
	//			//LEER IMPUTS UPDATE
	//			p2.update(input, v3);
	//			if (p2.piezaColocada) {
	//				turno = true;
	//				p2.piezaColocada = false;
	//			}
	//		}
	//	}
	//	//EJECUTAR LOS COMANDOS CMD

	//	Time seg = cicloTime.getElapsedTime();
	//	cicloTime.restart();
	//	segTotal += seg;

	//	if (p.star && turno) {
	//		cronometroPuzzle1 += seg;
	//	}
	//	float cronometro1 = cronometroPuzzle1.asSeconds();
	//	string cronometroP1 = to_string(cronometro1);


	//	if (p2.star && !turno) {
	//		cronometroPuzzle2 += seg;
	//	}
	//	float cronometro2 = cronometroPuzzle2.asSeconds();
	//	string cronometroP2 = to_string(cronometro2);

	//	p.cmd(segTotal);
	//	p2.cmd(segTotal);


	//	//UACTUALIZA LOS ESTADOS DEL JUEGO
	//	if (p.endGame() || p2.endGame()) {
	//		p.star = false; p2.star = false;
	//		cronometroPuzzle1 = cicloTime.restart();
	//		cronometroPuzzle2 = cicloTime.restart();
	//		p.salir(v, v2); p2.salir(v, v3);
	//		v2.close(); v3.close();
	//		switch (this->dificult) {
	//		case 3: if (cronometro1 < l[0].puntajeF) { l[0].puntajeF = cronometro1; } if (cronometro2 < l[1].puntajeF) { l[1].puntajeF = cronometro2; } break;
	//		case 5: if (cronometro1 < l[0].puntajeN) { l[0].puntajeN = cronometro1; } if (cronometro2 < l[1].puntajeF) { l[1].puntajeF = cronometro2; } break;
	//		case 7: if (cronometro1 < l[0].puntajeD) { l[0].puntajeD = cronometro1; } if (cronometro2 < l[1].puntajeF) { l[1].puntajeF = cronometro2; } break;
	//		}

	//		v2.clear(); v3.clear();
	//		p.draw(v2); p2.draw(v3);
	//		p.cmd2(v2); p2.cmd2(v3);
	//		sleep(seconds(10.0f));
	//		v2.display(); v3.display();
	//	}

	//	//REDIBUJADO 
	//	v2.clear(); v3.clear();
	//	p.draw(v2); p2.draw(v3);
	//	Boton::textoVentana(v2, "DIGITAL", cronometroP1, { 450,25 }, 35, Color::White);
	//	Boton::textoVentana(v3, "DIGITAL", cronometroP2, { 450,25 }, 35, Color::White);
	//	v2.display(); v3.display();
	//	v2.close(); v3.close();
	//}

RenderWindow v2(VideoMode(WIDTH, HEIGHT), "GAME");
RenderWindow v3(VideoMode(WIDTH, HEIGHT), "GAME2");
v2.setFramerateLimit(60);
int vx = v.getPosition().x;
int vy = v.getPosition().y;
v2.setPosition(Vector2i(vx, vy));
v3.setPosition(Vector2i(vx + v.getSize().x, vy + v.getSize().y));
v.setVisible(false);

Puzle p(this->dificult);
Puzle p2(this->dificult);
Usuario archivo;

Clock cicloTime;
Time segTotal;
Time cronometroPuzzle1, cronometroPuzzle2;

bool turno = true;

while (v2.isOpen()) {
	Event input;

	if (turno) {
		while (v2.pollEvent(input)) {
			if (input.type == Event::Closed) {
				this->guardarlogeados(archivo); this->logeados.clear();
				p.salir(v, v2);
			}
			//LEER IMPUTS UPDATE
			p.update(input, v2);
			if (p.piezaColocada) {
				turno = false;
				p.piezaColocada = false;
			}
		}
	}
	else {
		while (v3.pollEvent(input)) {
			if (input.type == Event::Closed) {
				this->guardarlogeados(archivo); this->logeados.clear();
				p2.salir(v, v3);
			}
			//LEER IMPUTS UPDATE
			p2.update(input, v3);
			if (p2.piezaColocada) {
				turno = true;
				p2.piezaColocada = false;
			}
		}
	}
	//EJECUTAR LOS COMANDOS CMD

	Time seg = cicloTime.getElapsedTime();
	cicloTime.restart();
	segTotal += seg;

	if (p.star && turno) {
		cronometroPuzzle1 += seg;
	}
	float cronometro1 = cronometroPuzzle1.asSeconds();
	string cronometroP1 = to_string(cronometro1);


	if (p2.star && !turno) {
		cronometroPuzzle2 += seg;
	}
	float cronometro2 = cronometroPuzzle2.asSeconds();
	string cronometroP2 = to_string(cronometro2);

	p.cmd(segTotal);
	p2.cmd(segTotal);

	//UACTUALIZA LOS ESTADOS DEL JUEGO
	if (p.endGame() || p2.endGame()) {
		p.star = false; p2.star = false;
		cronometroPuzzle1 = cicloTime.restart();
		if (p.endGame()) {
			p.ganador = true; cout << "GANO 1";
		}
		else {
			p2.ganador = true;  cout << "GANO 2";
		}
		v2.clear(); v3.clear();
		p.cmd2(v2); p2.cmd2(v3);
		p.draw(v2); p2.draw(v3);
		sleep(seconds(6.f)); p2.salir(v, v3);
		switch (this->dificult) {
		case 3: if (cronometro1 < l[0].puntajeF) { l[0].puntajeF = cronometro1; } if (cronometro2 < l[1].puntajeF) { l[1].puntajeF = cronometro2; } break;
		case 5: if (cronometro1 < l[0].puntajeN) { l[0].puntajeN = cronometro1; } if (cronometro2 < l[1].puntajeF) { l[1].puntajeF = cronometro2; } break;
		case 7: if (cronometro1 < l[0].puntajeD) { l[0].puntajeD = cronometro1; } if (cronometro2 < l[1].puntajeF) { l[1].puntajeF = cronometro2; } break;
		}
		sleep(seconds(6.f));
		p.salir(v, v2);
		v2.close(); v3.close();
	}
	//REDIBUJADO 
	v2.clear(); v3.clear();
	p.draw(v2); p2.draw(v3);
	Boton::textoVentana(v2, "DIGITAL", cronometroP1, { 450,25 }, 40, Color::White);
	Boton::textoVentana(v3, "DIGITAL", cronometroP2, { 450,25 }, 40, Color::White);
	v2.display(); v3.display();

}
}

void Menu::config(RenderWindow& vm) {
	RenderWindow v2(VideoMode(WIDTH, HEIGHT), "CONGIGURATION");
	v2.setFramerateLimit(60);

	Menu c("FONDO", { 350, 330 }, "LOGIN", {550,330}, "REGIST", {350,70}, "3X3", {450,70}, "5X5", {550,70}, "7X7", {90, 430}, "CLOSE LOGIN", {810, 430}, "MENU", "TRON_", "PEQUE_", "CIRCULAR_", "ARCADE", "ARCADE");
	c.entrar(vm,v2);
	Usuario archivo;
	c.logeados = this->logeados;

	while (v2.isOpen()) {
		Event event;
		while (v2.pollEvent(event)) {
			if (event.type == Event::Closed) {
				c.guardarlogeados(archivo); this->logeados.clear();
				v2.close();
			}
			//LEER IMPUTS UPDATE
			if (!c.ventanaOpen()) {
				//cout<< endl << " EVENTO MENU "<<endl ;
				c.update(event);
			}
			switch (c.op()) {
			case 0: c.login(v2, vm); c.opciones[0].pres = false; cout << " BOTON 0"; break;
			case 1: c.regis(v2); c.opciones[1].pres = false; cout << " BOTON 1"; break;
			case 2: this->dificult = 3; c.opciones[2].pres = false; cout << " BOTON 2"; break;
			case 3: this->dificult = 5; c.opciones[3].pres = false; cout << " BOTON 3"; break;
			case 4: this->dificult = 7; c.opciones[4].pres = false; cout << " BOTON 4"; break;
			case 5: c.guardarlogeados(archivo); this->logeados.clear(); c.opciones[5].pres = false; cout << " BOTON 5"; break;
			case 6: c.salir(vm,v2); c.opciones[6].pres = false; cout << " BOTON 6"; break;
			}
		}
		//EJECUTAR LOS COMANDOS CMD
		
		//UACTUALIZA LOS ESTADOS DEL JUEGO

		//REDIBUJADO
		if (!c.ventanaOpen()) {
			//cout << " CONFIG DRAW ";
			v2.clear();
			c.draw(v2);
			switch (this->dificult) {
			case 3: Boton::textoVentana(v2, "ARCADE", "9 PIEZAS", { 450,120 }, 25, Color::White); break;
			case 5: Boton::textoVentana(v2, "ARCADE", "25 PIEZAS", { 450,120 }, 25, Color::White); break;
			case 7: Boton::textoVentana(v2, "ARCADE", "49 PIEZAS", { 450,120 }, 25, Color::White); break;
			}
			for (int i = 0; i < this->logeados.size(); i++) {
				float x = i;
				Boton::textoVentana(v2, "LEGADO", this->logeados[i].nick, {350 + (x * 200),430}, 30, Color::White);
			}
			Boton::textoVentana(v2, "LEGADO", "CONFIG", {450 , 210}, 80, Color::White);
			v2.display();
		}
		this->logeados = c.logeados;
	}
}

void Menu::rankin(RenderWindow& v) {
	RenderWindow v2(VideoMode(WIDTH, HEIGHT), "RANKING");
	v2.setFramerateLimit(60); 

	Menu r("FONDO_T", { -110, -110 }, "X", {-110,-110}, "X", {350,30}, "3X3", {450,30}, "5X5", {550,30}, "7X7", {450, 460}, "MENU", {-110,-110}, "X", "", "PEQUE_", "TRON_", "ARCADE", "ARCADE");
	r.entrar(v, v2);
	
	Usuario rr;
	rr.usuariosRegistrados = Usuario::loadFileVec("REGISTRO DE JUGADORES.txt");
	bool facil = false;
	bool normal = false;
	bool dificil = false;

	while (v2.isOpen()) {

		Event event;
		while (v2.pollEvent(event)) {
			if (event.type == Event::Closed) {
				v2.close();
			}
			//LEER IMPUTS UPDATE
			r.update(event);
			switch (r.op()) {
			case 2: facil = true; normal = false; dificil = false; r.opciones[2].pres = false; cout << " BOTON 0"; break;
			case 3: normal = true; facil = false; dificil = false; r.opciones[3].pres = false; cout << " BOTON 3"; break;
			case 4: dificil = true; normal = false; facil = false; r.opciones[4].pres = false; cout << " BOTON 4"; break;
			case 5: r.salir(v, v2); r.opciones[5].pres = false; cout << " BOTON 5"; break;
			}
		}
		//EJECUTAR LOS COMANDOS CMD
		if (!r.ventanaOpen()) {
			//cout << " CONFIG DRAW ";
		}
		if (facil) {
			rr.rankinFacil();
		}
		if (normal) {
			rr.rankinNormal();
		}
		if (dificil) {
			rr.rankinDificl();
		}

		//UACTUALIZA LOS ESTADOS DEL JUEGO

		//REDIBUJADO
		v2.clear();
		r.draw(v2);
		if (!r.ventanaOpen()) {
		}
		if (facil) {
			rr.facildraw(v2);
		}
		if (normal) {
			rr.normaldraw(v2);
		}
		if (dificil) {
			rr.dificildraw(v2);
		}
		Boton::textoVentana(v2, "LEGADO", "RANKING", { 450, 100 }, 80, Color::White);
		//cout << " CONFIG DRAW ";
		v2.display();
	}
}

int Menu::op() {
	for (int i = 0; i < opciones.size(); i++) {
		if (opciones[i].pres) {
			return i;
		}
	}
}

void Menu::update(Event imput) {
	for (int i = 0; i < opciones.size(); i++) {
		opciones[i].update(imput);
	}
}

void Menu::draw(RenderTarget& target) {
	target.draw(fondoS);
	for (const Boton& b : opciones) {
		target.draw(b);
	}
}
