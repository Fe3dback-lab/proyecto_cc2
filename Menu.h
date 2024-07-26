#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <future> 
#include <iostream> 
using namespace std;

class Menu {
public:
    Menu(int width, int height);

    void mostrar(sf::RenderWindow& ventana);
    bool manejarEventos(sf::RenderWindow& ventana);
    bool recursosCargados() const { return recursosCargados_; }

private:
    sf::Texture textura_menu;
    sf::Sprite sprite_menu;
    sf::Font fuente;
    sf::Text texto_jugar;
    sf::Text texto_salir;

    sf::RectangleShape boton_jugar;
    sf::RectangleShape boton_salir;

    std::future<void> cargarRecursosAsync;

    bool recursosCargados_ = false;

    void configurarBotones(int width, int height);
    void cargarRecursos(int width, int height);
};

// Implementacion de async

Menu::Menu(int width, int height) {
    cargarRecursosAsync = async(std::launch::async, [this, width, height]() {
        cargarRecursos(width, height);
        });
}

void Menu::cargarRecursos(int width, int height) {
    bool cargaExitosa = true;

    if (!textura_menu.loadFromFile("fondomenuN.jpeg")) {
        cout << "No se pudo cargar el archivo de textura de men�." << endl;
        cargaExitosa = false;
    }
    else {
        sprite_menu.setTexture(textura_menu);
        sprite_menu.setScale(
            static_cast<float>(width) / textura_menu.getSize().x,
            static_cast<float>(height) / textura_menu.getSize().y
        );
    }

    if (!fuente.loadFromFile("sansation.ttf")) {
        std::cout << "No se pudo cargar el archivo de fuente." << std::endl;
        cargaExitosa = false;
    }

    if (cargaExitosa) {
        configurarBotones(width, height);
        recursosCargados_ = true;
    }
}

void Menu::configurarBotones(int width, int height) {
    // Configurar el boton de jugar
    boton_jugar.setSize(sf::Vector2f(200, 50));
    boton_jugar.setFillColor(sf::Color::Green);
    boton_jugar.setPosition(width / 2 - 100, height / 2 - 60);

    texto_jugar.setFont(fuente);
    texto_jugar.setString("Jugar");
    texto_jugar.setCharacterSize(24);
    texto_jugar.setFillColor(sf::Color::Black);
    texto_jugar.setPosition(
        boton_jugar.getPosition().x + (boton_jugar.getSize().x - texto_jugar.getGlobalBounds().width) / 2,
        boton_jugar.getPosition().y + (boton_jugar.getSize().y - texto_jugar.getGlobalBounds().height) / 2
    );

    // Configurar el boton de salir
    boton_salir.setSize(sf::Vector2f(200, 50));
    boton_salir.setFillColor(sf::Color::Red);
    boton_salir.setPosition(width / 2 - 100, height / 2 + 20);

    texto_salir.setFont(fuente);
    texto_salir.setString("Salir");
    texto_salir.setCharacterSize(24);
    texto_salir.setFillColor(sf::Color::Black);
    texto_salir.setPosition(
        boton_salir.getPosition().x + (boton_salir.getSize().x - texto_salir.getGlobalBounds().width) / 2,
        boton_salir.getPosition().y + (boton_salir.getSize().y - texto_salir.getGlobalBounds().height) / 2
    );
}

void Menu::mostrar(sf::RenderWindow& ventana) {
    if (!recursosCargados_) {
        cout << "Recursos no cargados correctamente." << endl;
        return;
    }

    ventana.clear();
    ventana.draw(sprite_menu);
    ventana.draw(boton_jugar);
    ventana.draw(texto_jugar);
    ventana.draw(boton_salir);
    ventana.draw(texto_salir);
    ventana.display();
}

bool Menu::manejarEventos(sf::RenderWindow& ventana) {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            ventana.close();
            return false;
        }
        if (evento.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i posicion_mouse = sf::Mouse::getPosition(ventana);
            sf::FloatRect rect_jugar = boton_jugar.getGlobalBounds();
            sf::FloatRect rect_salir = boton_salir.getGlobalBounds();

            if (rect_jugar.contains(static_cast<float>(posicion_mouse.x), static_cast<float>(posicion_mouse.y))) {
                return false; // Comienza el juego
            }
            if (rect_salir.contains(static_cast<float>(posicion_mouse.x), static_cast<float>(posicion_mouse.y))) {
                ventana.close();
                return false; // Sale del juego
            }
        }
    }
    return true;
}

#endif // MENU_H 
