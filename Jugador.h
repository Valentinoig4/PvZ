#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include <string>
using namespace std;
#include "Planta.h"

class Jugador {
protected:
    vector<Planta*> plantas;
public:
    int cantidadSoles{};
};


#endif //JUGADOR_H
