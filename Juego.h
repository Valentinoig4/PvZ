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
    ifstream archivoEntrada;
    vector<Oleada> oleadas{};
    Mapa mapa{};
    string historial{};
    Jugador jugador = Jugador(&mapa);
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
        oleadas[4].plantas.push_back(make_unique<NuezDoble>());
        oleadas[4].plantas.push_back(make_unique<GirasolDoble>());
        oleadas.emplace_back(Oleada({tipoZombie::Comun, tipoZombie::Cono, tipoZombie::Atletico, tipoZombie::Cubo }, 3, 15, {"Lanzaguisantes", "Girasol", "Lanzaguisantes Doble", "Nuez", "Lanzaguisantes de fuego", "Nuez Doble", "Girasol Doble"}));
        oleadas[5].plantas.push_back(make_unique<LanzaGuisantes>());
        oleadas[5].plantas.push_back(make_unique<Girasol>());
        oleadas[5].plantas.push_back(make_unique<LanzaGuisantesDoble>());
        oleadas[5].plantas.push_back(make_unique<Nuez>());
        oleadas[5].plantas.push_back(make_unique<LanzaGuisantesFuego>());
        oleadas[5].plantas.push_back(make_unique<NuezDoble>());
        oleadas[5].plantas.push_back(make_unique<GirasolDoble>());
        oleadas.emplace_back(Oleada({tipoZombie::Comun, tipoZombie::Cono, tipoZombie::Atletico, tipoZombie::Cubo }, 5, 20, { "Lanzaguisantes", "Girasol", "Lanzaguisantes Doble", "Nuez", "Lanzaguisantes de fuego", "Nuez Doble", "Girasol Doble"}));
        oleadas[6].plantas.push_back(make_unique<LanzaGuisantes>());
        oleadas[6].plantas.push_back(make_unique<Girasol>());
        oleadas[6].plantas.push_back(make_unique<LanzaGuisantesDoble>());
        oleadas[6].plantas.push_back(make_unique<Nuez>());
        oleadas[6].plantas.push_back(make_unique<LanzaGuisantesFuego>());
        oleadas[6].plantas.push_back(make_unique<NuezDoble>());
        oleadas[6].plantas.push_back(make_unique<GirasolDoble>());
        oleadas.emplace_back(Oleada({tipoZombie::Comun, tipoZombie::Gigante, tipoZombie::Cubo, tipoZombie::Periodico }, 5, 30, {"Lanzaguisantes", "Girasol", "Lanzaguisantes Doble", "Nuez", "Lanzaguisantes de fuego", "Nuez Doble", "Girasol Doble", "Lanzaguisantes de Hielo"}));
        oleadas[7].plantas.push_back(make_unique<LanzaGuisantes>());
        oleadas[7].plantas.push_back(make_unique<Girasol>());
        oleadas[7].plantas.push_back(make_unique<LanzaGuisantesDoble>());
        oleadas[7].plantas.push_back(make_unique<Nuez>());
        oleadas[7].plantas.push_back(make_unique<LanzaGuisantesFuego>());
        oleadas[7].plantas.push_back(make_unique<NuezDoble>());
        oleadas[7].plantas.push_back(make_unique<GirasolDoble>());
        oleadas[7].plantas.push_back(make_unique<LanzaGuisantesHielo>());
        oleadas.emplace_back(Oleada({tipoZombie::Comun, tipoZombie::Atletico,  tipoZombie::Gigante, tipoZombie::Cubo, tipoZombie::Periodico }, 5, 35, { "Lanzaguisantes", "Girasol", "Lanzaguisantes Doble", "Nuez", "Lanzaguisantes de fuego", "Nuez Doble", "Girasol Doble", "Lanzaguisantes de Hielo","Lanzamaiz"}));
        oleadas[8].plantas.push_back(make_unique<LanzaGuisantes>());
        oleadas[8].plantas.push_back(make_unique<Girasol>());
        oleadas[8].plantas.push_back(make_unique<LanzaGuisantesDoble>());
        oleadas[8].plantas.push_back(make_unique<Nuez>());
        oleadas[8].plantas.push_back(make_unique<LanzaGuisantesFuego>());
        oleadas[8].plantas.push_back(make_unique<NuezDoble>());
        oleadas[8].plantas.push_back(make_unique<GirasolDoble>());
        oleadas[8].plantas.push_back(make_unique<LanzaGuisantesHielo>());
        oleadas.emplace_back(Oleada({tipoZombie::Comun,  tipoZombie::Gigante, tipoZombie::Cubo, tipoZombie::Periodico }, 3, 25, { "Lanzaguisantes", "Girasol", "Lanzaguisantes Doble", "Nuez", "Lanzaguisantes de fuego", "Nuez Doble", "Girasol Doble", "Lanzaguisantes de Hielo","Lanzamaiz"}));
        oleadas[9].plantas.push_back(make_unique<LanzaGuisantes>());
        oleadas[9].plantas.push_back(make_unique<Girasol>());
        oleadas[9].plantas.push_back(make_unique<LanzaGuisantesDoble>());
        oleadas[9].plantas.push_back(make_unique<Nuez>());
        oleadas[9].plantas.push_back(make_unique<LanzaGuisantesFuego>());
        oleadas[9].plantas.push_back(make_unique<NuezDoble>());
        oleadas[9].plantas.push_back(make_unique<GirasolDoble>());
        oleadas[9].plantas.push_back(make_unique<LanzaGuisantesHielo>());
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

    void solesPorRonda(int ronda) {
        if (ronda == 1) {
            jugador.soles += 700;
        } else if (ronda == 2) {
            jugador.soles += 600;
        } else if (ronda == 3) {
            jugador.soles += 500;
        } else if (ronda == 4) {
            jugador.soles += 400;
        } else if (ronda == 5) {
            jugador.soles += 300;
        } else if (ronda == 6) {
            jugador.soles += 200;
        } else if (ronda == 7) {
            jugador.soles += 100;
        } else if (ronda == 8) {
            jugador.soles += 50;
        } else if (ronda == 9) {
            jugador.soles += 0;
        } else if (ronda == 10) {
            jugador.soles += 0;
        }
    }

    void iniciarJuego() {
        int ronda = 0;
        for ( auto& oleada: oleadas) {
            ronda++;
            cout << "------------------------------ RONDA " << ronda << " ------------------------------"<<  endl << endl;
            cout << "FASE DE LAS PLANTAS:" << endl << endl;
            solesPorRonda(ronda);
            fasePlantas(oleada);
            bool rondaCompleta = faseZombies(oleada);
            solesGenerados += mapa.solesGenerados;
            jugador.soles += mapa.solesGenerados;
            dañoRecibido += mapa.dañoRecibido;
            zombiesElimintados += mapa.zombiesEliminados;
            puntosFinales += zombiesElimintados*3;
            if (rondaCompleta) {oleadasCompletadas++; mapa.reset();}
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
        archivo << endl;
        archivo.close();
        if (ronda == 10) {cout << "Ganaste!!" << endl;}
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
                    int opcion2 = 0;
                    cout << "Ver resultados (1 o 0): ";
                    cin >> opcion2;
                    if (opcion2 == 1) {
                        archivoEntrada.open(historial,ios::in);
                        string linea{};
                        while (getline(archivoEntrada,linea)) {
                            cout << linea << endl;
                        }
                        cout << endl;
                    }
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
                cout << endl;

            }
        }
    }


    // MENU
    // FASES DEL JUEGO
    // HISTORIAL

};

#endif //JUEGO_H
