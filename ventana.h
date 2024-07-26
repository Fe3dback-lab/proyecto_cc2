#ifndef VENTANA_H
#define VENTANA_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

void configurarVentana(VideoMode &pantalla_completa, RenderWindow &ventana_dlj) {
    pantalla_completa = VideoMode::getDesktopMode();
    ventana_dlj.create(pantalla_completa, "", Style::Fullscreen);
    ventana_dlj.setFramerateLimit(60);
}

void cargarFondo(Texture &texturas, Sprite &s, int anchop, int altop) {
    texturas.loadFromFile("fondo.jpeg");
    s.setTexture(texturas);
    s.setScale(
        static_cast<float>(anchop) / texturas.getSize().x,
        static_cast<float>(altop) / texturas.getSize().y
    );
}

#endif // VENTANA_H
 