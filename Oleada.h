#ifndef OLEADA_H
#define OLEADA_H
#include <utility>
#include "Zombie.h"

enum class tipoZombie {
    Comun,
    Cono,
    Cubo,
    Atletico,
    Gigante
};

class Oleada {
public:
    vector<tipoZombie> zombies{};
    int velocidadDeSpawneo{};
    int cantZombies{};
    Oleada() = default;
    Oleada(const vector<tipoZombie>& _zombies, int _velocidadDeSpawneo, int _cantZombies) : zombies(_zombies), velocidadDeSpawneo(_velocidadDeSpawneo), cantZombies(_cantZombies) {};


};

#endif //OLEADA_H
