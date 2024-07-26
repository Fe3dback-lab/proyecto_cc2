#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
using namespace sf;
using namespace std;

class player {
public:
    int x, y, dir;
    Color color;
    player(Color c, int maxX, int maxY);
    void cambio(int maxX, int maxY);
    Vector3f ob_color();
};

// Constructor de jugador
player::player(Color c, int maxX, int maxY) {
    x = rand() % maxX;
    y = rand() % maxY;
    color = c;
    dir = rand() % 4;
}

// Cuando sale de un lado de la pantalla aparece por el otro
void player::cambio(int maxX, int maxY) {
    if (dir == 0) y += 1;
    if (dir == 1) x -= 1;
    if (dir == 2) x += 1;
    if (dir == 3) y -= 1;

    if (x >= maxX) x = 0; if (x < 0) x = maxX - 1;
    if (y >= maxY) y = 0; if (y < 0) y = maxY - 1;
}

Vector3f player::ob_color() {
    return Vector3f(color.r, color.g, color.b);
}

// Factory Method
class PlayerFactory {
public:
    virtual ~PlayerFactory() {}
    virtual unique_ptr<player> createPlayer(int maxX, int maxY) = 0;
};

class RandomPlayerFactory : public PlayerFactory {
public:
    Color color;

    RandomPlayerFactory(Color c) : color(c) {}

    unique_ptr<player> createPlayer(int maxX, int maxY) override;
};

// Implementacion del metodo createPlayer
unique_ptr<player> RandomPlayerFactory::createPlayer(int maxX, int maxY) {
    return make_unique<player>(color, maxX, maxY);
}

#endif  
