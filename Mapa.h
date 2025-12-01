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
    vector<vector<Celda>> mapa;
    Oleada oleada{};
    int recursosGenerados{};
    int zombiesUtilizados{};
    int ticks{};

    // --------------- CONSTRUCTOR ------------------

    Mapa() {
        mapa.resize(6);
        for (auto &fila: mapa) {
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
        unsigned int filaRand = rd() % mapa.size();

        if (zombie == tipoZombie::Comun) {
            mapa[filaRand][8].zombies.push_back(std::make_unique<ZombieComun>(pair<int, int>(filaRand, 8)));
        } else if (zombie == tipoZombie::Cono) {
            mapa[filaRand][8].zombies.push_back(std::make_unique<ZombieCono>(pair<int, int>(filaRand, 8)));
        } else if (zombie == tipoZombie::Cubo) {
            mapa[filaRand][8].zombies.push_back(std::make_unique<ZombieCubo>(pair<int, int>(filaRand, 8)));
        } else if (zombie == tipoZombie::Atletico) {
            mapa[filaRand][8].zombies.push_back(std::make_unique<ZombieAtletico>(pair<int, int>(filaRand, 8)));
        } else {
            mapa[filaRand][8].zombies.push_back(std::make_unique<ZombieGigante>(pair<int, int>(filaRand, 8)));
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
        for (auto & j : mapa[fila]) {
            if (!j.zombies.empty()) {
                return j.zombies[0].get();
            }
        }
        return nullptr;
    }

    // AÑADIR PLANTA



    // VERIFICAR SI YA SE USARON TODOS LOS ZOMBIES Y YA NO HAY EN EL MAPA

    bool oleadaIncompleta() {
        if (zombiesUtilizados == oleada.cantZombies) {
            for (auto & i : mapa) {
                for (auto & j : i) {
                    if (!j.zombies.empty()) { return true; }
                }
            }
            return false;
        }
        return true;
    }

    //IMPRIMIR UNA CELDA

    void imprimirCelda() {
        
    }

    // ------------------ ENGINE ------------------

    bool runTurno() {

        // ACTIVAR HABILIDADES PASIVAS

        for (auto & i : mapa) {
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

        for (int i = 0; i < mapa.size(); i++) {
            for (int j = 0; j < mapa[i].size(); j++) {
                if (mapa[i][j].planta != nullptr) {
                    if (mapa[i][j].planta->tipo == tipoPlanta::atacante) {
                        if (mapa[i][j].planta->anadirTick()) {
                            Zombie* dum = zombieCercano(i);
                            if (dum != nullptr) {
                                mapa[i][j].planta->accion(*dum);
                            }
                        }
                    }
                }
            }
        }


        // MOVIMIENTO ZOMBIES

        for (int i = 1; i < mapa.size(); i++) {
            for (int j = 0; j < mapa[i].size(); j++) {
                if (!mapa[i][j].zombies.empty()) {
                    for (int z = 0; z < mapa[i][j].zombies.size();) {
                        if (mapa[i][j].zombies[z]->anadirTick()) {
                            if (mapa[i][j].planta != nullptr) {mapa[i][j].zombies[z]->plantaCerca = true;}
                            mapa[i][j].zombies[z]->actuar();
                            int newcol = mapa[i][j].zombies[z]->getPos().second;
                            if (newcol != j) {
                                mapa[i][newcol].zombies.push_back(std::move(mapa[i][j].zombies[z]));
                                mapa[i][j].zombies.erase(mapa[i][j].zombies.begin() + z);
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

        for (int i = 0; i < mapa.size(); i++) {
            for (int j = 0; j < mapa[i].size(); j++) {
                if (!mapa[i][j].zombies.empty()) { // Limpieza de zombies
                    for (int z = 0; z < mapa[i][j].zombies.size();) {
                        if (mapa[i][j].zombies[z]->getVida()== 0) {
                            mapa[i][j].zombies.erase(mapa[i][j].zombies.begin() + z);
                        } else {
                            z++;
                        }
                    }
                }

                if (mapa[i][j].planta != nullptr) {
                    if (!mapa[i][j].zombies.empty()) {
                        int dmg{};
                        for (int z = 0; z < mapa[i][j].zombies.size();z++) {
                            dmg += mapa[i][j].zombies[z]->danio;
                        }
                        *mapa[i][j].planta -= dmg;
                        if (mapa[i][j].planta->getVida() == 0) {
                            mapa[i][j].planta.reset();
                        }
                    }
                }
            }
        }

        // CHEQUEAR SI SE JUGADOR PERDIO
        bool perdioJuego = false;
        for (auto & i : mapa) {
            if (!i[0].zombies.empty()) {
                perdioJuego = true;
                break;
            }
        }
        return perdioJuego;
    }

    void imprimir() {

    }

    // ------------------ MAIN ENGINE ------------------

    bool runOleada() {
        bool completaOleada = true;
        while (oleadaIncompleta()) {
            this_thread::sleep_for(chrono::milliseconds(500));
            tickZombie();

            bool perdioJuego = this->runTurno();
            if (perdioJuego) {
                completaOleada = false;
                break;
            }
        }
        return completaOleada;
    }

};

#endif //MAPA_H
