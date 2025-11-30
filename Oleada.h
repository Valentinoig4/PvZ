
#ifndef OLEADA_H
#define OLEADA_H
#include <utility>
#include "Zombie.h"

enum class tipoZombie {
    Comun,
    Fortificado,
    Especial
};

class Oleada {
public:
    vector<tipoZombie> zombies{};
    int velocidadDeSpawneo{};

    Oleada(const vector<tipoZombie>& _zombies, int _velocidadDeSpawneo) : zombies(_zombies), velocidadDeSpawneo(_velocidadDeSpawneo) {};


};

#endif //OLEADA_H
