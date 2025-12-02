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
    vector<string> plantasDisponibles{};
    vector<Planta*> plantas{};
    int velocidadDeSpawneo{};
    int cantZombies{};
    Oleada() = default;
    Oleada(const vector<tipoZombie>& _zombies, int _velocidadDeSpawneo, int _cantZombies, vector<string> pd) : zombies(_zombies),
    velocidadDeSpawneo(_velocidadDeSpawneo), cantZombies(_cantZombies), plantasDisponibles(pd) {};
    vector<string> getPlantasDisponibles() { return plantasDisponibles; }
    ~Oleada() {
        for (auto c : plantas) {
            delete c;
        }
    };
};

#endif //OLEADA_H
