#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include "Planta.h"
#include "Zombie.h"
using namespace std;

class Celda {

};

class Mapa {
public:
    int filas{5}, columnas{9};

    Mapa() = default;

    [[nodiscard]] pair<int,int> posAleatoria() const {
        random_device rd;
        return { rd() % filas, columnas-1 };
    }
};

#endif //MAPA_H
