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
    int zombiesElimintados{};
    int dañoRecibido{};
    int puntosFinales{};
    int solesGenerados{};

public:
    Juego() {
        oleadas.emplace_back(Oleada({tipoZombie::Comun}, 3, 10, {"Lanzaguisantes", "Girasol"}));
        oleadas[0].plantas.push_back(make_unique<LanzaGuisantes>());
        oleadas[0].plantas.push_back(make_unique<Girasol>());
        oleadas.emplace_back(Oleada({tipoZombie::Comun, tipoZombie::Cono}, 3, 15, {"Lanzaguisantes", "Girasol", "Lanzaguisantes Doble"}));
        oleadas[1].plantas.push_back(make_unique<LanzaGuisantes>());
        oleadas[1].plantas.push_back(make_unique<Girasol>());
        oleadas[1].plantas.push_back(make_unique<LanzaGuisantesDoble>());
        oleadas.emplace_back(Oleada({tipoZombie::Comun, tipoZombie::Cono}, 4, 15, {"Lanzaguisantes", "Girasol", "Lanzaguisantes Doble", "Nuez"}));
        oleadas[2].plantas.push_back(make_unique<LanzaGuisantes>());
        oleadas[2].plantas.push_back(make_unique<Girasol>());
        oleadas[2].plantas.push_back(make_unique<LanzaGuisantesDoble>());
        oleadas[2].plantas.push_back(make_unique<Nuez>());
        oleadas.emplace_back(Oleada({tipoZombie::Comun, tipoZombie::Cono, tipoZombie::Atletico }, 4, 20, {"Lanzaguisantes", "Girasol", "Lanzaguisantes Doble", "Nuez", "Lanzaguisantes de Hielo"}));
        oleadas[3].plantas.push_back(make_unique<LanzaGuisantes>());
        oleadas[3].plantas.push_back(make_unique<Girasol>());
        oleadas[3].plantas.push_back(make_unique<LanzaGuisantesDoble>());
        oleadas[3].plantas.push_back(make_unique<Nuez>());
        oleadas[3].plantas.push_back(make_unique<LanzaGuisantesHielo>());
        oleadas.emplace_back(Oleada({tipoZombie::Comun, tipoZombie::Cono, tipoZombie::Atletico, tipoZombie::Cubo }, 4, 30, {"Lanzaguisantes", "Girasol", "Lanzaguisantes Doble", "Nuez", "Lanzaguisantes de Hielo", "Nuez Doble", "Girasol Doble"}));
        oleadas[4].plantas.push_back(make_unique<LanzaGuisantes>());
        oleadas[4].plantas.push_back(make_unique<Girasol>());
        oleadas[4].plantas.push_back(make_unique<LanzaGuisantesDoble>());
        oleadas[4].plantas.push_back(make_unique<Nuez>());
        oleadas[4].plantas.push_back(make_unique<LanzaGuisantesHielo>());
        oleadas[4].plantas.push_back(make_unique<GirasolDoble>());

    };
    ~Juego()=default;

    void fasePlantas(Oleada& oleada) {
        jugador.fasePlantas(oleada);
    };
    bool faseZombies(Oleada &_oleada) {
        mapa.aniadirOleada(&_oleada);
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
            zombiesElimintados += mapa.zombiesEliminados;
            puntosFinales += zombiesElimintados*3;
            if (rondaCompleta) {oleadasCompletadas++;}
            if (!rondaCompleta) {cout << jugador.nombre << " perdiste";break;}
        }
        auto fecha = chrono::system_clock::now();
        time_t t = chrono::system_clock::to_time_t(fecha);
        tm *tiempoLocal = localtime(&t);
        archivo << "Hora: "<<put_time(tiempoLocal, "%Y-%m-%d %H:%M:%S") << endl;
        archivo<<"Nombre: "<<jugador.nombre<<endl;
        archivo<<"Oleadas completadas: "<<oleadasCompletadas<<endl;
        archivo<<"Zombies eliminados: "<<zombiesElimintados<<endl;
        archivo<<"Soles generados: "<<solesGenerados<<endl;
        archivo<<"Dano recibido: "<<dañoRecibido<<endl;
        archivo<<"Puntos finales: "<<zombiesElimintados*30<<endl;
        archivo.close();
    }

    void iniciar() {
        cout << "---------------- BIENVENIDO A PLANTAS VS ZOMBIES ----------------" << endl;
        cout << "Cual es tu nombre: ";
        cin >> jugador.nombre;
        cout << endl;
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
                    archivo.open(historial,ios::app);
                } else {
                    cout << "Nombre de archivo no valido" << endl << endl;
                }
            }

            if (opcion == 2) {
                if (historial.empty()) {
                    cout << "Se creará un historial con el nombre: HistorialPVZ.txt" << endl;
                    historial = "HistorialPVZ.txt";
                    archivo.open(historial, ios::app);
                }
                cout << "------------------------------ Iniciando el juego ------------------------------" << endl << endl;
                iniciarJuego();
                break;
            }
        }
    }


    // MENU
    // FASES DEL JUEGO
    // HISTORIAL

};

#endif //JUEGO_H
