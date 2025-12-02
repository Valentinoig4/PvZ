//
// Created by Rafael Chamayo on 28/11/25.
//

#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include "Oleada.h"
#include "Mapa.h"
#include <iostream>
#include <string>
#include <fstream>

class Juego {

private:
    ofstream archivo;
    vector<Oleada> oleadas{};
    Mapa mapa{};
    string historial{};
    Jugador jugador = Jugador(&mapa, 300);
    int oleadasCompletadas{};
    int zombiesEliminados{};
    int dañoRecibido{};
    int puntosFinales{};
    int solesGenerados{};

public:
    Juego() {
        oleadas.emplace_back(Oleada({tipoZombie::Comun}, 3, 10, {"Lanzaguisantes"}));
        oleadas[0].plantas.push_back(new LanzaGuisantes);
    };
    ~Juego()=default;

    void fasePlantas(Oleada& oleada) {
        jugador.fasePlantas(oleada);
    };
    bool faseZombies(Oleada _oleada) {
        mapa.aniadirOleada(_oleada);
        bool rondaCompleta = mapa.runOleada();
        return rondaCompleta;
    };

    void iniciarJuego() {
        int ronda = 0;
        for ( auto& oleada: oleadas) {
            ronda++;
            cout << "------------------------------ RONDA " << ronda << " ------------------------------"<<  endl << endl;
            cout << "FASE DE LAS PLANTAS:" << endl << endl;
            fasePlantas(oleada);
            bool rondaCompleta = faseZombies(oleada);
            solesGenerados += mapa.solesGenerados;
            dañoRecibido += mapa.dañoRecibido;
            zombiesEliminados += mapa.zombiesEliminados;
            puntosFinales += zombiesEliminados*3;
            if (rondaCompleta) {oleadasCompletadas++;}
            if (!rondaCompleta) {cout << jugador.nombre << " perdiste";break;}
            archivo<<"Nombre: "<<jugador.nombre<<endl;
            archivo<<"Oleadas completadas: "<<oleadasCompletadas<<endl;
            archivo<<"Zombies eliminados: "<<zombiesEliminados<<endl;
            archivo<<"Soles generados: "<<solesGenerados<<endl;
            archivo<<"Dano recibido: "<<dañoRecibido<<endl;
            archivo<<"Puntos finales: "<<zombiesEliminados*30<<endl;
            archivo.close();
        }
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
                    archivo.open(historial, ios::app);
                    auto fecha = chrono::system_clock::now();
                    time_t t = chrono::system_clock::to_time_t(fecha);
                    tm *tiempoLocal = localtime(&t);
                    archivo << put_time(tiempoLocal, "%Y-%m-%d %H:%M:%S") << endl;
                }
                cout << "------------------------------ Iniciando el juego ------------------------------" << endl << endl;
                iniciarJuego();
            }
        }
    }


    // MENU
    // FASES DEL JUEGO
    // HISTORIAL

};

#endif //JUEGO_H
