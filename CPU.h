#ifndef CPU_H
#define CPU_H

#include <iostream>
#include "Mapa.h"
#include "Oleadas.h"
#include "ZombieComun.h"
#include "ZombieFortificadoCasco.h"
#include "ZombieFortificadoCono.h"
#include "ZombieAtletico.h"

using namespace std;

class CPU {
public:
    Oleadas oleadas;
    Mapa* mapa;

    CPU(Mapa* m) : mapa(m) {}

    Zombie* generarZombieRandom() {
        int tipo = rand() % 4;

        if (tipo == 0) {
            cout << "CPU hizo Zombie normal\n";
            return new ZombieComun();
        }
        if (tipo == 1) {
            cout << "CPU hizo zombie de casco\n";
            return new ZombieFortificadoCasco();
        }
        if (tipo == 2) {
            cout << "CPU hizo zombie de cono\n";
            return new ZombieFortificadoCono();
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

#endif
