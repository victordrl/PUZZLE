#include "Usuario.h"

ostream& operator<<(ostream& os, const Usuario& obj) {
	os << obj.nick << ' ' << obj.puntajeD << ' ' << obj.puntajeN << ' ' << obj.puntajeF << '\n';
	return os;
}

istream& operator>>(istream& is, Usuario& obj) {
	is >> obj.nick >> obj.puntajeD >> obj.puntajeN >> obj.puntajeF;
	return is;
}

Usuario::Usuario() {
	nick = "";
	puntajeD = 999;
	puntajeN = 999;
	puntajeF = 999;
	fondoT.loadFromFile("DEFAULT/FONDO_S.png");
	fondoS.setTexture(fondoT);

}

void Usuario::saveFileVec(const vector<Usuario>& vec, const string& archivo) {
	ofstream ofsArchvio(archivo);
	if (ofsArchvio) {
		for (const auto& obj : vec) {
			ofsArchvio << obj;
		}
	}
}

int Usuario::op() {
	for (int i = 0; i < opciones.size(); i++) {
		if (opciones[i].pres) {
			opciones[i].pres = false;
			return i;
		}
	}
	return -1;
}

void Usuario::mostrar() {
	for (const Usuario& u : usuariosRegistrados) {
		cout << "- " << u.nick << endl;
	}
}

void Usuario::toupperString(string& cadena) {
	for (char& c : cadena) {
		c = toupper(c);
	}
}

void Usuario::login() {
	//INICIALIZAR PANTALLA LOGIN
	usuariosRegistrados = Usuario::loadFileVec("REGISTRO DE JUGADORES.txt");

	Boton a({ 270,400 }, "TRON_", "ARCADE", "ATRAS", 30, Color::White);
	Boton b({ 630,400 }, "TRON_", "ARCADE", "LOGIN", 30, Color::White);
	opciones.push_back(a);
	opciones.push_back(b);

	posTexto = Vector2f(450, 255);

	cout << " LOGIN ENCABEZADO ";
}

void Usuario::loginUpdate(Event input) {
	//ACTUALIZAR INPUTS EN LOGIN
	for (int i = 0; i < opciones.size(); i++) {
		opciones[i].update(input);
	}

	if (input.type == sf::Event::TextEntered) {
		if (input.text.unicode < 128) {
			if (input.text.unicode == '\b' && !texto.empty()) {
				texto.pop_back();
			}
			else if (input.text.unicode != '\b') {
				texto += static_cast<char>(input.text.unicode);
				tleido.setPosition(posTexto.x - (tleido.getGlobalBounds().width / 2), posTexto.y);
			}
		}
	}
	tleido.setString(texto);
	//cout << " EVENTO LOGIN ";
}

bool Usuario::loginConfirmed(string buscar, vector <Usuario>& logeados) {
	tmensaje = "NO EXISTE ";
	for (const Usuario& user : usuariosRegistrados) {
		if (buscar == user.nick && logeados.size() < 2) {
			auto it = find_if(logeados.begin(), logeados.end(), [&](Usuario& u) { return u.nick == buscar; });
			if (it == logeados.end()) {
				logeados.push_back(user);
				usuariosRegistrados.erase(remove_if(usuariosRegistrados.begin(), usuariosRegistrados.end(), [&](const Usuario& u) { return u.nick == buscar; }), usuariosRegistrados.end());
				tmensaje = "LOGEADO ";
				mensaje = true;
				return true;
			}
			else {
				tmensaje = "YA LOGEADO ";
			}
		}
	}
	mensaje = true;
	return false;
}

void Usuario::loginDraw(RenderTarget& target, RenderWindow& v) {
	target.draw(fondoS);
	Boton::textoVentana(v, "ARCADE", texto, posTexto, 40, Color::White);
	if (mensaje) {
		Boton::textoVentana(v, "ARCADE", tmensaje, { 450,470 }, 40, Color::White);
	}

	for (const Boton& o : opciones) {
		target.draw(o);
	}
	Boton::textoVentana(v, "LEGADO", "LOGIN", { 450,145 }, 80, Color::White);
	//cout << " LOGIN DIBUJADO ";
}

void Usuario::loginCase0(RenderWindow& v, RenderWindow& v2) {
	int v2x = v2.getPosition().x;
	int v2y = v2.getPosition().y;
	v.setPosition(Vector2i(v2x, v2y));
	v.setVisible(true);
	v2.close();
	cout << " LOGIN CRRADO ";
}

void Usuario::loginCase1(RenderWindow& v, vector <Usuario>& logeados) {
	toupperString(texto);
	if (loginConfirmed(texto,logeados)) {
		cout << " SE ENCONTRO ";
	}
	else {
		cout << " NO ENCONTRADO ";
	}
	saveFileVec(usuariosRegistrados, "REGISTRO DE JUGADORES.txt");
}


void Usuario::regis() {
	//INICIALIZAR PANTALLA LOGIN

	usuariosRegistrados = Usuario::loadFileVec("REGISTRO DE JUGADORES.txt");

	Boton a({ 270,400 }, "TRON_", "ARCADE", "ATRAS", 30, Color::White);
	Boton b({ 630,400 }, "TRON_", "ARCADE", "REGISTRAR", 30, Color::White);
	opciones.push_back(a);
	opciones.push_back(b);

	posTexto = Vector2f(450, 255);

	cout << " REGIST ENCABEZADO ";
}

void Usuario::regisUpdate(Event input) {
	//ACTUALIZAR INPUTS EN LOGIN
	for (int i = 0; i < opciones.size(); i++) {
		opciones[i].update(input);
	}

	if (input.type == sf::Event::TextEntered) {
		if (input.text.unicode < 128) {
			if (input.text.unicode == '\b' && !texto.empty()) {
				texto.pop_back();
			}
			else if (input.text.unicode != '\b') {
				texto += static_cast<char>(input.text.unicode);
				tleido.setPosition(posTexto.x - (tleido.getGlobalBounds().width / 2), posTexto.y);
			}
		}
	}
	tleido.setString(texto);
	//cout << " EVENTO REGIST ";
}

bool Usuario::regisConfirmed(string buscar, vector <Usuario>& logeados) {
	bool puedoRegistrar = true;
	for (const Usuario& user : usuariosRegistrados) {
		if (buscar == user.nick) {
			puedoRegistrar = false;
			tmensaje = "YA EXIST ";
			mensaje = true;
			return false;
		}
	}
	if (puedoRegistrar) {
		Usuario user;
		user.nick = texto;
		usuariosRegistrados.push_back(user);
	}
	tmensaje = "REGISTRADO ";
	mensaje = true;
	return true;
}

void Usuario::regisDraw(RenderTarget& target, RenderWindow& v) {
	//DIBUJAR PANTALLA REGIST
	v.draw(fondoS);
	Boton::textoVentana(v, "ARCADE", texto, posTexto, 40, Color::White);
	if (mensaje) {
		Boton::textoVentana(v, "ARCADE", tmensaje, { 450,470 }, 40, Color::White);;
	}
	for (const Boton& o : opciones) {
		target.draw(o);
	}
	Boton::textoVentana(v, "LEGADO", "REGISTRO", { 450,145 }, 80, Color::White);
	//cout << " REGIST DIBUJADO ";
}

void Usuario::regisCase0(RenderWindow& v, RenderWindow& v2) {
	int v2x = v2.getPosition().x;
	int v2y = v2.getPosition().y;
	v.setPosition(Vector2i(v2x, v2y));
	v.setVisible(true);
	v2.close();
	//cout << " REGIST CRRADO ";
}

void Usuario::regisCase1(RenderWindow& v, vector <Usuario>& logeados) {
	toupperString(texto);
	if (regisConfirmed(texto, logeados)) {
		loginCase1(v, logeados);
		cout << " NO ENCONTRO ";
	}
	else {
		cout << " SI ENCONTRO ";
	}
	saveFileVec(usuariosRegistrados, "REGISTRO DE JUGADORES.txt");
}

void Usuario::rankinFacil() {
	//usuariosRegistrados = Usuario::loadFileVec("REGISTRO DE JUGADORES.txt");
	for (int i = 0; i < usuariosRegistrados.size(); i++) {
		for (int j = 0; j < usuariosRegistrados.size(); j++) {
			if (usuariosRegistrados[i].puntajeF < usuariosRegistrados[j].puntajeF) {
				swap(usuariosRegistrados[i], usuariosRegistrados[j]);
			}
		}
	}
}
void Usuario::facildraw(RenderWindow& v) {
	string tabla; string puntajeString;
	for (int i = 0; i < usuariosRegistrados.size(); i++) {
		puntajeString = to_string(usuariosRegistrados[i].puntajeF);
		tabla = usuariosRegistrados[i].nick + "  " + puntajeString;
		float pos = i * 25;
		if (usuariosRegistrados[i].puntajeF != 999) {
			Boton::textoVentana(v, "LEGADO", tabla, { 450,160 + pos }, 20, Color::White);
		}
	}
	//cout << " RANKING FACIL ";
}

void Usuario::rankinNormal() {
	//usuariosRegistrados = Usuario::loadFileVec("REGISTRO DE JUGADORES.txt");
	for (int i = 0; i < usuariosRegistrados.size(); i++) {
		for (int j = 0; j < usuariosRegistrados.size(); j++) {
			if (usuariosRegistrados[i].puntajeN < usuariosRegistrados[j].puntajeN) {
				swap(usuariosRegistrados[i], usuariosRegistrados[j]);
			}
		}
	}
}
void Usuario::normaldraw(RenderWindow& v) {
	string tabla; string puntajeString;
	for (int i = 0; i < usuariosRegistrados.size(); i++) {
		puntajeString = to_string(usuariosRegistrados[i].puntajeN);
		tabla = usuariosRegistrados[i].nick + "  " + puntajeString;
		float pos = i * 25;
		if (usuariosRegistrados[i].puntajeN != 999) {
			Boton::textoVentana(v, "LEGADO", tabla, { 450,160 + pos }, 20, Color::White);
		}
	}
	//cout << " RANKING NORMAL ";
}

void Usuario::rankinDificl() {
	//usuariosRegistrados = Usuario::loadFileVec("REGISTRO DE JUGADORES.txt");
	for (int i = 0; i < usuariosRegistrados.size(); i++) {
		for (int j = 0; j < usuariosRegistrados.size(); j++) {
			if (usuariosRegistrados[i].puntajeD < usuariosRegistrados[j].puntajeD) {
				swap(usuariosRegistrados[i], usuariosRegistrados[j]);
			}
		}
	}
}
void Usuario::dificildraw(RenderWindow& v) {
	string tabla; string puntajeString;
	for (int i = 0; i < usuariosRegistrados.size(); i++) {
		puntajeString = to_string(usuariosRegistrados[i].puntajeD);
		tabla = usuariosRegistrados[i].nick + "  " + puntajeString;
		float pos = i * 25;
		if (usuariosRegistrados[i].puntajeD != 999) {
			Boton::textoVentana(v, "LEGADO", tabla, { 450,160 + pos }, 20, Color::White);
		}
	}
	//cout << " RANKING DIFICL ";
}
