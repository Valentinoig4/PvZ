#ifndef CPU_H
#define CPU_H

#include <utility>

#include "Oleada.h"
#include "Mapa.h"
#include "Zombie.h"


class CPU {
public:
    Oleada oleada{};
    Mapa* mapa{};

    explicit CPU(Mapa* mapa) : mapa(mapa){};
    CPU(Oleada _oleada, Mapa* m) : oleada(std::move(_oleada)), mapa(m) {}

    void añadirOleada(Oleada _oleada) {
        this->oleada = std::move(_oleada);
    }

    Zombie* generarZombieRandom() {
        int tipo = rand() % 4;

        if (tipo == 0) {
            cout << "CPU hizo Zombie normal\n";
            return new ZombieComun();
        }
        if (tipo == 1) {
            cout << "CPU hizo zombie de cubo\n";
            return new ZombieCubo();
        }
        if (tipo == 2) {
            cout << "CPU hizo zombie de cono\n";
            return new ZombieCono();
        }
        cout << "CPU hizo Zombie atletico\n";
        return new ZombieAtletico();
    }

    void colocarZombie() {
        Zombie* z = generarZombieRandom();
        pair<int,int> pos = mapa->posAleatoria();
        z->setPos(pos);
    }
};

#endif //CPU_H
