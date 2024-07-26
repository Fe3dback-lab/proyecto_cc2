#ifndef CAMPODEJUEGO_H
#define CAMPODEJUEGO_H

#include <SFML/Graphics.hpp>
#include <memory> 
#include <vector> 

using namespace sf;
using namespace std;

extern unique_ptr<vector<vector<bool>>> campo;
extern int veljug;

// Funciun para inicializar el campo 
void inicializarCampo(int anchop, int altop) {
    campo = make_unique<vector<vector<bool>>>(anchop, vector<bool>(altop, false));
}

// Funcion para liberar el campo de juego
void liberarCampo() {
    
    campo.reset();
}

#endif // CAMPODEJUEGO_H  
