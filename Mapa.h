//
// Created by Rafael Chamayo on 29/11/25.
//

#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include "Planta.h"
#include "Zombie.h"
#include <utility>
#include "Oleada.h"
#include <memory>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;

class Celda {
public:
    unique_ptr<Planta> planta{};
    vector<unique_ptr<Zombie>> zombies{};
    Celda() = default;
};

// PODADORAS
// ZOMBIE MAS CERCANO
// DETERMINAR SI EL JUEGO ESTA PERDIDO SI CPU SE QUEDA SIN ZOMBIES Y TODOS PIERDEN O SI  EL JUGADOR PIERDE
//

class Mapa {
public:
    vector<vector<Celda>> grilla;
    Oleada oleada{};
    int recursosGenerados{};
    int zombiesUtilizados{};
    int ticks{};

    // --------------- CONSTRUCTOR ------------------

    Mapa() {
        grilla.resize(6);
        for (auto &fila: grilla) {
            fila.resize(9);
        }

    }

    // --------------- METODOS RELEVANTES---------------------

    // AÑADIR OLEADA

    void aniadirOleada(const Oleada &_oleada) {
        oleada = _oleada;
    };

    // AÑADIR UN ZOMBIE ALEATORIAMENTE
    void randZombie() {
        random_device rd;
        unsigned int numZombie = rd() % oleada.zombies.size();
        tipoZombie zombie = oleada.zombies[numZombie];
        unsigned int filaRand = rd() % grilla.size();

        if (zombie == tipoZombie::Comun) {
            grilla[filaRand][8].zombies.push_back(std::make_unique<ZombieComun>(pair<int, int>(filaRand, 8)));
        } else if (zombie == tipoZombie::Cono) {
            grilla[filaRand][8].zombies.push_back(std::make_unique<ZombieCono>(pair<int, int>(filaRand, 8)));
        } else if (zombie == tipoZombie::Cubo) {
            grilla[filaRand][8].zombies.push_back(std::make_unique<ZombieCubo>(pair<int, int>(filaRand, 8)));
        } else if (zombie == tipoZombie::Atletico) {
            grilla[filaRand][8].zombies.push_back(std::make_unique<ZombieAtletico>(pair<int, int>(filaRand, 8)));
        } else {
            grilla[filaRand][8].zombies.push_back(std::make_unique<ZombieGigante>(pair<int, int>(filaRand, 8)));
        }
        zombiesUtilizados++;
    }

    // AÑADIR UN ZOMBIE DE ACUERDO A LA VELOCIDAD DE SPAWNEO

    void tickZombie() {
        ticks++;
        if (ticks%oleada.velocidadDeSpawneo == 0) {
            random_device rd;
            unsigned int numZombie = rd() % 3 +1;
            for (unsigned int i = 0; i < numZombie; i++) {
                randZombie();
            }
        }
    }

    // ENCONTRAR AL ZOMBIE MAS CERCANO

    Zombie* zombieCercano(int fila) {
        for (auto & j : grilla[fila]) {
            if (!j.zombies.empty()) {
                return j.zombies[0].get();
            }
        }
        return nullptr;
    }

    // AÑADIR PLANTA

    bool aniadirPlanta(string tipoPlanta, int fila, int col) {
        if (grilla[fila][col].planta != nullptr) {
            return false;
        } else {
            if (tipoPlanta == "Lanzaguisantes") grilla[fila][col].planta = std::make_unique<LanzaGuisantes>();
            else if (tipoPlanta == "Lanzaguisantes Doble") grilla[fila][col].planta = std::make_unique<LanzaGuisantesDoble>();
            else if (tipoPlanta == "Lanzaguisantes de Hielo") grilla[fila][col].planta = std::make_unique<LanzaGuisantesHielo>();
            else if (tipoPlanta == "Lanzaguisantes de fuego") grilla[fila][col].planta = std::make_unique<LanzaGuisantesFuego>();
            else if (tipoPlanta == "Lanzamaiz") grilla[fila][col].planta = std::make_unique<LanzaMaiz>();
            else if (tipoPlanta == "Girasol") grilla[fila][col].planta = std::make_unique<Girasol>();
            else if (tipoPlanta == "Girasol Doble") grilla[fila][col].planta = std::make_unique<GirasolDoble>();
            else if (tipoPlanta == "Nuez") grilla[fila][col].planta = std::make_unique<Nuez>();
            else if (tipoPlanta == "Nuez Doble") grilla[fila][col].planta = std::make_unique<NuezDoble>();
            return true;
        }

    }

    // VERIFICAR SI YA SE USARON TODOS LOS ZOMBIES Y YA NO HAY EN EL MAPA

    bool oleadaIncompleta() {
        if (zombiesUtilizados == oleada.cantZombies) {
            for (auto & i : grilla) {
                for (auto & j : i) {
                    if (!j.zombies.empty()) { return true; }
                }
            }
            return false;
        }
        return true;
    }

    //IMPRIMIR UNA CELDA

    void imprimirCelda(const Celda& celda) {
        string contenido{};
        if (celda.planta != nullptr) {
            contenido+= 'P';
        }
        int contzombies{};
        if (!celda.zombies.empty()) {
            for (int i = 0; i < celda.zombies.size(); i++) {
                contzombies++;
            }
            contenido += " " + to_string(contzombies) + "Z";
        }
        if (contenido.empty()) {
            contenido += '-';
        }
        cout << setw(10) << left << contenido;
    }

    // ------------------ ENGINE ------------------

    bool runTurno() {

        // ACTIVAR HABILIDADES PASIVAS

        for (auto & i : grilla) {
            for (auto & j : i) {
                if (j.planta != nullptr) {
                    if (j.planta->tipo == tipoPlanta::productor) {
                        if (j.planta->anadirTick()) {
                            recursosGenerados+= j.planta->habilidadPasiva();
                        }
                    }
                }
            }
        }

        // ACTIVAS HABILIDADES PLANTAS ACTIVAS

        for (int i = 0; i < grilla.size(); i++) {
            for (int j = 0; j < grilla[i].size(); j++) {
                if (grilla[i][j].planta != nullptr) {
                    if (grilla[i][j].planta->tipo == tipoPlanta::atacante) {
                        if (grilla[i][j].planta->anadirTick()) {
                            Zombie* dum = zombieCercano(i);
                            if (dum != nullptr) {
                                grilla[i][j].planta->accion(*dum);
                            }
                        }
                    }
                }
            }
        }


        // MOVIMIENTO ZOMBIES

        for (int i = 1; i < grilla.size(); i++) {
            for (int j = 0; j < grilla[i].size(); j++) {
                if (!grilla[i][j].zombies.empty()) {
                    for (int z = 0; z < grilla[i][j].zombies.size();) {
                        if (grilla[i][j].zombies[z]->anadirTick()) {
                            if (grilla[i][j].planta != nullptr) {grilla[i][j].zombies[z]->plantaCerca = true;}
                            grilla[i][j].zombies[z]->actuar();
                            int newcol = grilla[i][j].zombies[z]->getPos().second;
                            if (newcol != j) {
                                grilla[i][newcol].zombies.push_back(std::move(grilla[i][j].zombies[z]));
                                grilla[i][j].zombies.erase(grilla[i][j].zombies.begin() + z);
                            } else {
                                z++;
                            }
                        } else {
                            z++;
                        }
                    }
                }
            }
        }

        // COLISION Y VIDA PLANTAS Y ZOMBIES

        for (int i = 0; i < grilla.size(); i++) {
            for (int j = 0; j < grilla[i].size(); j++) {
                if (!grilla[i][j].zombies.empty()) { // Limpieza de zombies
                    for (int z = 0; z < grilla[i][j].zombies.size();) {
                        if (grilla[i][j].zombies[z]->getVida()== 0) {
                            grilla[i][j].zombies.erase(grilla[i][j].zombies.begin() + z);
                        } else {
                            z++;
                        }
                    }
                }

                if (grilla[i][j].planta != nullptr) {
                    if (!grilla[i][j].zombies.empty()) {
                        int dmg{};
                        for (int z = 0; z < grilla[i][j].zombies.size();z++) {
                            dmg += grilla[i][j].zombies[z]->danio;
                        }
                        *grilla[i][j].planta -= dmg;
                        if (grilla[i][j].planta->getVida() == 0) {
                            grilla[i][j].planta.reset();
                        }
                    }
                }
            }
        }

        // CHEQUEAR SI SE JUGADOR PERDIO
        bool perdioJuego = false;
        for (auto & i : grilla) {
            if (!i[0].zombies.empty()) {
                perdioJuego = true;
                break;
            }
        }
        return perdioJuego;
    }

    void imprimir() {
        for (int i = 0; i < grilla.size(); i++) {
            for (int j = 0; j < grilla[i].size(); j++) {
                imprimirCelda(grilla[i][j]);
            }
            cout << endl;
        }
        cout << endl << endl;
    }

    // ------------------ MAIN ENGINE ------------------

    bool runOleada() {
        bool completaOleada = true;
        while (oleadaIncompleta()) {
            this_thread::sleep_for(chrono::milliseconds(1000));
            tickZombie();

            bool perdioJuego = this->runTurno();
            if (perdioJuego) {
                completaOleada = false;
                break;
            }
            imprimir();
        }
        return completaOleada;
    }

};

#endif //MAPA_H
