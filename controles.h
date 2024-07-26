#ifndef CONTROLES_H
#define CONTROLES_H

#include <SFML/Graphics.hpp>
#include "jugadores.h"
#include "command.h"
 
using namespace sf;
using namespace std;
class Izquierda : public Command {
public:
    Izquierda(player &p) : _player(p) {}
    void mover() override {
        if (_player.dir != 2) _player.dir = 1;
    }
private:
    player &_player;
};

class Derecha : public Command {
public:
    Derecha(player &p) : _player(p) {}
    void mover() override {
        if (_player.dir != 1) _player.dir = 2;
    }
private:
    player &_player;
};

class Arriba : public Command {
public:
    Arriba(player &p) : _player(p) {}
    void mover() override {
        if (_player.dir != 0) _player.dir = 3;
    }
private:
    player &_player;
};

class Abajo : public Command {
public:
    Abajo(player &p) : _player(p) {}
    void mover() override {
        if (_player.dir != 3) _player.dir = 0;
    }
private:
    player &_player;
};

class Controlador_Teclas {
public:
    Controlador_Teclas(player &p1, player &p2) : p1Left(p1), p1Right(p1), p1Up(p1), p1Down(p1),
    p2Left(p2), p2Right(p2), p2Up(p2), p2Down(p2) {}
    //Entradas del teclado
    void Entradas() {
        if (Keyboard::isKeyPressed(Keyboard::Left)) p1Left.mover();
        if (Keyboard::isKeyPressed(Keyboard::Right)) p1Right.mover();
        if (Keyboard::isKeyPressed(Keyboard::Up)) p1Up.mover();
        if (Keyboard::isKeyPressed(Keyboard::Down)) p1Down.mover();

        if (Keyboard::isKeyPressed(Keyboard::A)) p2Left.mover();
        if (Keyboard::isKeyPressed(Keyboard::D)) p2Right.mover();
        if (Keyboard::isKeyPressed(Keyboard::W)) p2Up.mover();
        if (Keyboard::isKeyPressed(Keyboard::S)) p2Down.mover();
    }

private:
    Izquierda p1Left;
    Derecha p1Right;
    Arriba p1Up;
    Abajo p1Down;
    Izquierda p2Left;
    Derecha p2Right;
    Arriba p2Up;
    Abajo p2Down;
};

#endif // CONTROLES_H 
