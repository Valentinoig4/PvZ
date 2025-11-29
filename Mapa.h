//
// Created by Rafael Chamayo on 29/11/25.
//

#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Mapa {
public:
    int filas{5}, columnas{9};

    Mapa() = default;

    pair<int,int> posAleatoria() {
        return { rand() % filas, columnas-1 };
    }
};

#endif //MAPA_H