#ifndef MUSICA_H
#define MUSICA_H

#include <SFML/Audio.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <iostream>

using namespace sf;
using namespace std;

class Musica {
public:
    static Musica& getInstance() {
        static Musica instance; 
        return instance;
    }

    // Eliminar la copia y la asignacion para evitar la creacion de mas instancias
    Musica(const Musica&) = delete;
    Musica& operator=(const Musica&) = delete;

    void configurarMusica(const string& archivo, bool loop = false) {
        if (!buffer.loadFromFile(archivo)) {
            throw runtime_error("No se pudo cargar el archivo de m�sica.");
        }

        musica.setBuffer(buffer);
        musica.setLoop(loop);

        // Iniciar la musica en un hilo separado
        stopRequested = false;
        musicThread = thread(&Musica::playMusic, this);
    }

    // M�todo para detener la m�sica
    void stopMusic() {
        stopRequested = true;
        if (musicThread.joinable()) {
            musicThread.join();
        }
    }

    ~Musica() {
        stopMusic(); // Asegurarse de que el hilo de musica se detenga al destruir la instancia
    }

    Sound& getMusica() { return musica; }

private:
    Musica() {} // Constructor privado

    void playMusic() {
        musica.play();
        while (musica.getStatus() == Sound::Playing && !stopRequested) {
            this_thread::sleep_for(chrono::milliseconds(100)); // Reducir uso de CPU
        }
        musica.stop();
    }

    SoundBuffer buffer;
    Sound musica;
    thread musicThread;
    atomic<bool> stopRequested; // Indica si se debe detener la musica
};

#endif // MUSICA_H 
