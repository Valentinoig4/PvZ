#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include "Oleada.h"
#include "CPU.h"
#include "Mapa.h"
#include <iostream>
#include <string>


class Juego {

private:
    vector<Oleada> oleadas{};
    Jugador jugador{};
    Mapa mapa{};
    CPU cpu = CPU(&mapa);
    string historial{};

public:
    Juego() {
        oleadas.emplace_back(Oleada({tipoZombie::Comun}, 4));
        oleadas.emplace_back(Oleada({tipoZombie::Comun}, 2));
        oleadas.emplace_back(Oleada({tipoZombie::Comun, tipoZombie::Fortificado}, 3));
        oleadas.emplace_back(Oleada({tipoZombie::Comun, tipoZombie::Fortificado}, 2));
        oleadas.emplace_back(Oleada({tipoZombie::Comun}, 2));
        oleadas.emplace_back(Oleada({tipoZombie::Comun}, 2));
        oleadas.emplace_back(Oleada({tipoZombie::Comun}, 2));
        oleadas.emplace_back(Oleada({tipoZombie::Comun}, 2));
        oleadas.emplace_back(Oleada({tipoZombie::Comun}, 2));
        oleadas.emplace_back(Oleada({tipoZombie::Comun}, 2));
    };
    ~Juego()=default;

    void fasePlantas();
    void faseZombies();

    void iniciarJuego() {

    }

    void iniciar() {
        int opcion{2};
        while (abs(opcion-3)) {
            cout <<"SELECCIONAR UNA OPCION:" << endl;
            cout << "1. Cargar Historial" << endl;
            cout << "2. Jugar" << endl;
            cout << "3. Salir" << endl;
            cout << "Opcion: ";
            cin >> opcion;
            cout << endl;

            if (opcion == 1) {
                string s;
                cout << "Ingresa el archivo: ";
                cin >> s;
                if (s.size() >= 5  && s.substr(s.size()-4, 7) == ".txt") {
                    historial = s;
                    cout << "se guardó: " << historial << endl << endl;;
                } else {
                    cout << "Nombre de archivo no valido" << endl << endl;
                }
            }

            if (opcion == 2) {
                if (historial.empty()) {
                    cout << "Se creará un historial con el nombre: HistorialPVZ.txt" << endl;
                    historial = "HistorialPVZ.txt";
                }
            }
        }
    }


    // MENU
    // FASES DEL JUEGO
    // HISTORIAL

};

#endif //JUEGO_H
