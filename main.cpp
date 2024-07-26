#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <iostream>
#include <memory> 
#include "ventana.h"
#include "campodejuego.h"
#include "musica.h"
#include "controles.h"
#include "command.h"
#include "juego.h"
#include "Menu.h"

using namespace sf;
using namespace std;

int veljug = 4;
unique_ptr<vector<vector<bool>>> campo;

int main() {
    srand(time(0));

    // Tamaño de pantalla
    VideoMode pantalla_completa;
    RenderWindow ventana_dlj;
    configurarVentana(pantalla_completa, ventana_dlj);
    int anchop = pantalla_completa.width;
    int altop = pantalla_completa.height;
    inicializarCampo(anchop, altop);

    // Crear el menu
    Menu menu(anchop, altop);

    // Musica de fondo
    try {
        Musica::getInstance().configurarMusica("rude_buster.ogg", true);
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    
    Sound gameover;
    

    // Mostrar menu inicial
    bool mostrar_menu = true;
    while (ventana_dlj.isOpen() && mostrar_menu) {
        menu.mostrar(ventana_dlj);
        mostrar_menu = menu.manejarEventos(ventana_dlj);
    }

    if (!ventana_dlj.isOpen()) {
        return 0;
    }

    // Uso del factory method
    RandomPlayerFactory factory1(Color::Red);
    RandomPlayerFactory factory2(Color::Blue);

    // Uso de unique para factory
    unique_ptr<player> p1 = factory1.createPlayer(anchop, altop);
    unique_ptr<player> p2 = factory2.createPlayer(anchop, altop);

    Sprite sprite;
    RenderTexture t;
    t.create(anchop, altop);
    t.setSmooth(true);
    sprite.setTexture(t.getTexture());
    t.clear();

    // Cargar el fondo de pantalla
    Texture texturas;
    Sprite s;
    cargarFondo(texturas, s, anchop, altop);
    t.draw(s);

    // Textos para ganador y perdedor
    Font fuente;
    fuente.loadFromFile("sansation.ttf");

    Text txt("YOU WIN", fuente, 35);
    txt.setPosition(anchop / 2 - 80, 20);

    Text lostxt("YOU LOSE", fuente, 35);
    lostxt.setPosition(anchop / 2 - 80, altop - 50);

    // Iniciar el juego despuus de salir del menu inicial
    iniciarJuego(ventana_dlj, pantalla_completa, anchop, altop, *p1, *p2, sprite, t, s, fuente, txt, lostxt, Musica::getInstance().getMusica(), gameover);

     

    return 0;
}
