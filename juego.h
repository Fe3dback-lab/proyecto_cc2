#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "jugadores.h"
#include "ventana.h"
#include "campodejuego.h"
#include "musica.h"
#include "controles.h"
#include "command.h"

using namespace sf;
using namespace std;

struct Estela {
    CircleShape forma;
    Color color;
};
 
// Funcion para mover un sprite con las teclas del jugador
void moverSprite(Sprite& sprite, float velocidad, player& jugador, int anchop, int altop) {
    // Obtener la direccion actual del jugador
    int dir = jugador.dir;
    // Mover el sprite segun la direccion del jugador
    if (dir == 0) { // Abajo
        sprite.move(0, velocidad);
        if (sprite.getPosition().y > altop)
            sprite.setPosition(sprite.getPosition().x, 0);
    }
    else if (dir == 1) { // Izquierda
        sprite.move(-velocidad, 0);
        if (sprite.getPosition().x < 0)
            sprite.setPosition(anchop, sprite.getPosition().y);
    }
    else if (dir == 2) { // Derecha
        sprite.move(velocidad, 0);
        if (sprite.getPosition().x > anchop)
            sprite.setPosition(0, sprite.getPosition().y);
    }
    else if (dir == 3) { // Arriba
        sprite.move(0, -velocidad);
        if (sprite.getPosition().y < 0)
            sprite.setPosition(sprite.getPosition().x, altop);
    }
}

// Funci�n para ajustar el origen del sprite
void ajustarOrigen(Sprite& sprite, int direccion) {
    if (direccion == 0) { // Abajo
        sprite.setOrigin(sprite.getTextureRect().width / 2, 0); // Parte superior central
    }
    else if (direccion == 1) { // Izquierda
        sprite.setOrigin(sprite.getTextureRect().width, sprite.getTextureRect().height / 2); // Parte derecha central
    }
    else if (direccion == 2) { // Derecha
        sprite.setOrigin(0, sprite.getTextureRect().height / 2); // Parte izquierda central
    }
    else if (direccion == 3) { // Arriba
        sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height); // Parte inferior central
    }
}

void iniciarJuego(RenderWindow& ventana_dlj, VideoMode& pantalla_completa, int& anchop, int& altop, player& p1, player& p2,
    Sprite& sprite, RenderTexture& t, Sprite& s, Font& font, Text& txt, Text& lostxt, Sound& musicaf, Sound& gameover) {

    // Cargar las texturas
    Texture texture1_up, texture1_down, texture1_left, texture1_right; // Texturas para el jugador 1
    Texture texture2_up, texture2_down, texture2_left, texture2_right; // Texturas para el jugador 2

    if (!texture1_up.loadFromFile("player2_up.png")) {
        cout << "Nose cargo la imagen p2_up" << endl;
    }
    if (!texture1_down.loadFromFile("player2_down.png")) {
        cout << "Nose cargo la imagen p2_down" << endl;
    }
    if (!texture1_left.loadFromFile("player2_left.png")) {
        cout << "Nose cargo la imagen p2_left" << endl;
    }
    if (!texture1_right.loadFromFile("player2_right.png")) {
        cout << "Nose cargo la imagen p2_left" << endl;
    }
    if (!texture2_up.loadFromFile("player1_up.png")) {
        cout << "Nose cargo la imagen p1_up" << endl;
    }
    if (!texture2_down.loadFromFile("player1_down.png")) {
        cout << "Nose cargo la imagen p1_down" << endl;
    }
    if (!texture2_left.loadFromFile("player1_left.png")) {
        cout << "Nose cargo la imagen p2_left" << endl;
    }
    if (!texture2_right.loadFromFile("player1_right.png")) {
        cout << "Nose cargo la imagen p1_right" << endl;
    }

    Sprite sprite1(texture1_up); // Sprite para el jugador 1
    Sprite sprite2(texture2_up); // Sprite para el jugador 2

    sprite1.setPosition(p1.x, p1.y); // Posicionar el sprite en la posicion inicial del jugador 1
    sprite2.setPosition(p2.x, p2.y); // Posicionar el sprite en la posicion inicial del jugador 2

    Controlador_Teclas Teclas(p1, p2);
    bool Game = true;

    // Crear una lista para almacenar las estelas
    vector<Estela> estelas;

    // Aqu� se manejan los eventos de la ventana
    while (ventana_dlj.isOpen()) {
        Event e;
        while (ventana_dlj.pollEvent(e)) {
            if (e.type == Event::Closed) {
                ventana_dlj.close();
            }
        }

        Teclas.Entradas();

        // Dibuja los textos de ganador y perdedor
        if (!Game) {
            ventana_dlj.draw(txt);
            ventana_dlj.draw(lostxt);
            ventana_dlj.display();
            continue;
        }

        // Actualiza la posicion de los jugadores si salen de un lado de la ventana aparecen en el otro
        for (int i = 0; i < veljug; i++) {
            p1.cambio(anchop, altop);
            p2.cambio(anchop, altop);

            // Se verifican las colisiones y se pone la musica
            if ((*campo)[p1.x][p1.y]) {
                Game = false;
                txt.setFillColor(p2.color);
                lostxt.setFillColor(p1.color);
                musicaf.stop();
                gameover.play();
            }
            if ((*campo)[p2.x][p2.y]) {
                Game = false;
                txt.setFillColor(p1.color);
                lostxt.setFillColor(p2.color);
                musicaf.stop();
                gameover.play();
            }

            (*campo)[p1.x][p1.y] = true;
            (*campo)[p2.x][p2.y] = true;

            // Cambiar la textura del sprite del jugador 1 segun la direccion
            switch (p1.dir) {
            case 0:
                sprite1.setTexture(texture1_down);
                sprite1.setTextureRect(IntRect(0, 0, 25, 74));
                ajustarOrigen(sprite1, 0);
                break;
            case 1:
                sprite1.setTexture(texture1_left);
                sprite1.setTextureRect(IntRect(0, 0, 74, 25));
                ajustarOrigen(sprite1, 1);
                break;
            case 2:
                sprite1.setTexture(texture1_right);
                sprite1.setTextureRect(IntRect(0, 0, 74, 25));
                ajustarOrigen(sprite1, 2);
                break;
            case 3:
                sprite1.setTexture(texture1_up);
                sprite1.setTextureRect(IntRect(0, 0, 25, 74));
                ajustarOrigen(sprite1, 3);
                break;
            }

            // Cambiar la textura del sprite del jugador 2 segun la direccion
            switch (p2.dir) {
            case 0:
                sprite2.setTexture(texture2_down);
                sprite2.setTextureRect(IntRect(0, 0, 25, 74));
                ajustarOrigen(sprite2, 0);
                break;
            case 1:
                sprite2.setTexture(texture2_left);
                sprite2.setTextureRect(IntRect(0, 0, 74, 25));
                ajustarOrigen(sprite2, 1);
                break;
            case 2:
                sprite2.setTexture(texture2_right);
                sprite2.setTextureRect(IntRect(0, 0, 74, 25));
                ajustarOrigen(sprite2, 2);
                break;
            case 3:
                sprite2.setTexture(texture2_up);
                sprite2.setTextureRect(IntRect(0, 0, 25, 74));
                ajustarOrigen(sprite2, 3);
                break;
            }

            // Mover el jugador 1 y el sprite
            moverSprite(sprite1, 1.0f, p1, anchop, altop);

            // Mover el jugador 2 y el sprite
            moverSprite(sprite2, 1.0f, p2, anchop, altop);

            // Generar estelas
            Estela estela1;
            estela1.forma.setRadius(2);
            estela1.forma.setFillColor(Color::Red);
            estela1.forma.setPosition(sprite1.getPosition().x, sprite1.getPosition().y);
            estela1.color = Color::Red;

            Estela estela2;
            estela2.forma.setRadius(2);
            estela2.forma.setFillColor(Color::Blue);
            estela2.forma.setPosition(sprite2.getPosition().x, sprite2.getPosition().y);
            estela2.color = Color::Blue;

            estelas.push_back(estela1);
            estelas.push_back(estela2);

            // Verificar colisiones con estelas
            for (const auto& estela : estelas) {
                FloatRect sprite1Bounds = sprite1.getGlobalBounds();
                FloatRect sprite2Bounds = sprite2.getGlobalBounds();
                FloatRect estelaBounds = estela.forma.getGlobalBounds();

                if (estela.color == Color::Red && sprite2Bounds.intersects(estelaBounds)) {
                    Game = false;
                    txt.setFillColor(p1.color);
                    lostxt.setFillColor(p2.color);
                    musicaf.stop();
                    gameover.play();
                }
                if (estela.color == Color::Blue && sprite1Bounds.intersects(estelaBounds)) {
                    Game = false;
                    txt.setFillColor(p2.color);
                    lostxt.setFillColor(p1.color);
                    musicaf.stop();
                    gameover.play();
                }
            }
            // Dibujar la estela del jugador 1
            CircleShape puntoEstela1(2); // Tamaño del punto de la estela del jugador 1
            puntoEstela1.setFillColor(Color::Red); // Color de la estela del jugador 1
            puntoEstela1.setPosition(sprite1.getPosition().x, sprite1.getPosition().y);
            t.draw(puntoEstela1);

            // Dibujar la estela del jugador 2
            CircleShape puntoEstela2(2); // Tamaño del punto de la estela del jugador 2
            puntoEstela2.setFillColor(Color::Blue); // Color de la estela del jugador 2
            puntoEstela2.setPosition(sprite2.getPosition().x, sprite2.getPosition().y);
            t.draw(puntoEstela2);

            t.display();
        }

        ventana_dlj.clear();
        ventana_dlj.draw(sprite);
        ventana_dlj.draw(sprite1); // Dibujar el sprite del jugador 1
        ventana_dlj.draw(sprite2); // Dibujar el sprite del jugador 2
        ventana_dlj.display();
    }

    // Detener la musica
    musicaf.stop();
    gameover.stop();

    liberarCampo();
}
#endif // JUEGO_H
