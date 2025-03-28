#include "Puzle.h"

Puzle::Puzle(int dificul) {
    imagenCodigo = random(0, 23);                   //CARGA IMAGEN RANDOM
    codigoFile= to_string(imagenCodigo);
    direccionFile = "PUZLE/PUZLE_IMAGEN_" + codigoFile + ".png";

    direccionWav = "Wav/" + codigoFile + " ganar.wav";
    audioW.openFromFile(direccionWav);

    direccionWav = "Wav/" + codigoFile + " perder.wav";
    audioL.openFromFile(direccionWav);

    originalTexture.loadFromFile(direccionFile);
    originalSprite.setTexture(originalTexture);
    //originalSprite.setOrigin(originalTexture.getSize().x /2, originalTexture.getSize().y / 2);
    originalSprite.setPosition(450,35);

    planoT.loadFromFile("DEFAULT/CIR.png");
    marcoT.loadFromFile("DEFAULT/MARCO.png");
    ggT.loadFromFile("DEFAULT/GG.png");
    fondoT.loadFromFile("DEFAULT/FONDO_G.png");

    marcoS.setTexture(marcoT);
    marcoS.setOrigin(0, marcoS.getGlobalBounds().height);
    marcoS.setPosition(90, 430);

    ggS.setTexture(ggT);
    ggS.setOrigin(ggS.getGlobalBounds().width / 2, ggS.getGlobalBounds().height / 2);
    ggS.setPosition(450, 250);

    fondoS.setTexture(fondoT);

    preparado = 0;
    nxn = dificul;
    inicio = false;
    arrastrarPieza = false;
    ganador = false;

    fondoG.loadFromFile("DEFAULT/f.png");
    fondoSG.setTexture(fondoG);

    this->plano();
    this->divImag();
    this->printAleatorio();
}

void Puzle::salir(RenderWindow& v, RenderWindow& v2) {
    int v2x = v2.getPosition().x;
    int v2y = v2.getPosition().y;
    v.setPosition(Vector2i(v2x, v2y));
    v.setVisible(true);
    v2.close();
    cout << " GAME CRRADO ";
}

int Puzle::random(int a, int b) {
    random_device rand;
    mt19937 generator(rand());                  //CREA NUMERO ALEATORI

    uniform_int_distribution<> rago(a, b);      //ENTRE UN RANGO A Y B

    int randomNumber = rago(generator);         //DEVUELVE UN ALEATORIO
    return randomNumber;
}

void Puzle::printAleatorio() {
    do {
        int n = random(0, (nxn * nxn)-1);
        auto it = find(indices.begin(), indices.end(), n);
        if (it == indices.end()) {
            indices.push_back(n);
        }
    } while (indices.size() < nxn * nxn);
}

void Puzle::divImag() {
    int size_x = originalTexture.getSize().x / nxn;
    int size_y = originalTexture.getSize().y / nxn;

    for (int y = 0; y < nxn; y++) {
        for (int x = 0; x < nxn; x++) {
            Pieza aux;
            aux.piezaSprite.setTexture(originalTexture);

            aux.piezaSprite.setScale(1.0f, 1.0f);
            aux.piezaSprite.setTextureRect(IntRect(x * size_x, y * size_y, size_x, size_y));
            aux.piezaSprite.setPosition(centrado.x - 50 + (x * size_x) + aux.piezaSprite.getGlobalBounds().width / 2, centrado.y + (y * size_y) + aux.piezaSprite.getGlobalBounds().height / 2);
            aux.piezaSprite.setOrigin(aux.piezaSprite.getGlobalBounds().width / 2, aux.piezaSprite.getGlobalBounds().height / 2);
            
            piezaS.push_back(aux);
        }
    }

    Boton s({ 450,410 }, "PEQUE_", "ARCADE", "STAR", 30, Color::White);
    Boton l({ 390,410 }, "PEQUE_", "ARCADE", "LISTO", 30, Color::White);
    Boton h({ 90,430 }, "CIRCULAR_", "ARCADE", "HELP", 30, Color::White);
    opciones.push_back(s);
    opciones.push_back(l); 
    opciones.push_back(h);
}

void Puzle::plano() {
    int size_x = originalTexture.getSize().x / nxn;
    int size_y = originalTexture.getSize().y / nxn;

    for (int y = 0; y < nxn; y++) {
        for (int x = 0; x < nxn; x++) {

            CircleShape aux(size_y/3);
            aux.setFillColor(Color(100, 100, 100));
            aux.setTexture(&planoT);

            aux.setOrigin(aux.getRadius(), aux.getRadius());
            aux.setPosition((x * size_x) + 250, (y * size_y) + 50);
            aux.setPosition(centrado.x + (x * size_x) + aux.getGlobalBounds().width / 2, centrado.y + 15 + (y * size_y) + aux.getGlobalBounds().height / 2);

            planoS.push_back(aux);
        }
    }
}

void Puzle::cmd(Time seg) {
    if (opciones[0].pres) {
        preparado += 1;
        inicio = true;
        tiempoMovimiento = seg;
    }

    for (int i = 0; i < nxn * nxn; i++) {
        piezaS[i].animate(inicio, seg, tiempoMovimiento);
    }
    if (opciones[0].pres ) {
        inicio = false;
        star = true;
    }
    else {
        opciones[0].pres = false;
    }
    if (opciones[2].over) {
        originalSprite.setScale(0.3f, 0.3f);
        originalSprite.setPosition(90, 270);
    }
}

void Puzle::cmd2(RenderWindow& v2) {
    if (ganador) {
        Boton::textoVentana(v2, "ARCADE", "WINER", { 450,250 }, 60, Color::White);
        audioW.play(); while (audioW.getStatus() == Music::Playing){} 
    }
    else {
        Boton::textoVentana(v2, "ARCADE", "LOSER", { 450,250 }, 60, Color::White);
        audioL.play(); while (audioL.getStatus() == Music::Playing) {}
    }
}

bool Puzle::endGame() {

    for (const Pieza& p : piezaS) {
        if (!p.ordenada) {
            inicio = false;
            return false;
        }
    }
    return true;
}

void Puzle::update(Event imput, RenderWindow& ventana) {

    opciones[0].update(imput);
    opciones[1].update(imput);
    opciones[2].update(imput);

    if (star) {
        for (int i = 0; i < nxn * nxn; i++) {
            //piezaS[i].update(imput, ventana);
            if (imput.type == Event::MouseButtonPressed) {
                if (imput.mouseButton.button == Mouse::Left) {
                    if (!arrastrarPieza && piezaS[i].piezaSprite.getGlobalBounds().contains(Mouse::getPosition(ventana).x, Mouse::getPosition(ventana).y)) {
                        arrastrarPieza = true;
                        indice = i;
                        if (piezaS[indice].ordenada) {
                            piezaS[indice].ordenada = false;
                        }
                    }
                }
            }
            if (imput.type == Event::MouseButtonReleased) {
                if (imput.mouseButton.button == Mouse::Left) {
                    if (arrastrarPieza) {
                        arrastrarPieza = false;
                        for (int j = 0; j < planoS.size(); j++) {
                            const CircleShape& c = planoS[j];
                            if (c.getGlobalBounds().contains(Mouse::getPosition(ventana).x, Mouse::getPosition(ventana).y)) {
                                piezaS[indice].piezaSprite.setPosition(c.getPosition().x, c.getPosition().y);
                                if (indice == j) {
                                    piezaS[indice].ordenada = true;
                                }
                                piezaColocada = true;
                            }
                        }
                    }
                }
            }
            if (arrastrarPieza) {
                piezaS[indice].piezaSprite.setPosition(Mouse::getPosition(ventana).x, Mouse::getPosition(ventana).y);
                piezaS[indice].colicion(0, 0, 900, 500);
            }
        }
    }
}

void Puzle::draw(RenderTarget& target) {
    target.draw(fondoS);
    for (const CircleShape& c : planoS) {
        target.draw(c);
    }
    for (int i = 0; i < piezaS.size(); i++) {
        target.draw(piezaS[indices[i]]);
    }
   //for (const Boton b : opciones) {
    //    target.draw(b);
    //}
    target.draw(opciones[0]);
    target.draw(opciones[2]);
    if (opciones[2].over) {
        target.draw(originalSprite);
        target.draw(marcoS);
    }
    if (ganador) {
      target.draw(ggS);
    }

}