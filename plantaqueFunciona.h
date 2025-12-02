#ifndef PLANTA_H
#define PLANTA_H

#include <random>
#include "Zombie.h"

enum class tipoPlanta {
    atacante,productor, soporte
};

class Planta {
public:
    int vida{}, costo{}, nivel{}, ticks{}, demora{};
    int ataque{};
    char ID{};

    virtual ~Planta() = default;

    tipoPlanta tipo{};
    Planta() = default;
    Planta(tipoPlanta t, int v, int d, int c, int n, char id) : vida(v), costo(c), nivel(n), demora(d), tipo(t), ID(id) {}
    Planta(tipoPlanta t, int v, int d, int c, int n, int a, char id) : vida(v), costo(c), nivel(n), demora(d), tipo(t), ataque(a), ID(id) {}
    bool anadirTick() {
        ticks++;
        if (tipo != tipoPlanta::soporte && demora > 0)
            return ticks % demora == 0;
        return false;
    }
    void operator -=(int dano) {
        vida -= dano;
        vida < 0 ? vida = 0 : vida;
    }
    virtual void accion(Zombie& z) {
        z -= ataque;
    }
    [[nodiscard]] virtual int habilidadPasiva() const {return 0;}

    [[nodiscard]] int getVida() const {return vida;}
};

    class Atacante : public Planta {
public:
    Atacante() { tipo = tipoPlanta::atacante; }
    Atacante(int v, int a, int d, int c, int n, char id) : Planta(tipoPlanta::atacante, v, d, c, n, a, id) {}
};

class Productor : public Planta {
protected:
    int soles{};
public:
    Productor() { tipo = tipoPlanta::productor; }
    Productor(int v, int s, int d, int c, int n, char id) : Planta(tipoPlanta::productor, v, d, c, n, id), soles(s) {}
    [[nodiscard]] int habilidadPasiva() const override {
        return soles;
    };
};

class Soporte : public Planta {
public:
    Soporte() { tipo = tipoPlanta::soporte; };
    Soporte(int v, int c, int n, int d, char id) : Planta(tipoPlanta::soporte, v, d, c, n, id) {}
};

class LanzaGuisantes : public Atacante {
public:
    LanzaGuisantes() : Atacante(300, 20, 3, 100, 1, 'L') {}
};

class LanzaGuisantesDoble : public Atacante {
public:
    LanzaGuisantesDoble() : Atacante(300, 40, 3, 150, 1, 'D') {}
};

class LanzaGuisantesHielo : public Atacante {
public:
    LanzaGuisantesHielo() : Atacante(300, 20, 3, 175, 1, 'H') {}
    void accion(Zombie& z) override {
        z -= ataque;
        !z.congelado ? z.velocidad += 2 : z.velocidad;
        z.congelado = true;
    }
};

class LanzaGuisantesFuego : public Atacante {
public:
    LanzaGuisantesFuego() : Atacante(300, 30, 3, 150, 1, 'F') {}
};

class LanzaMaiz : public Atacante {
public:
    LanzaMaiz() : Atacante(300, 20, 3, 100, 1, 'M') {}
    void accion(Zombie& z) override {
        random_device rd;
        if (rd() % 100 < 30) {
            z -= ataque*2;
            z.ticksParalizado = 4;
        } else {
            z -= ataque;
        }
    }
};

class Girasol : public Productor {
public:
    Girasol() : Productor(300, 50, 49, 50, 1, 'G') {}
};

class GirasolDoble : public Productor {
public:
    GirasolDoble() : Productor(300, 100, 49, 50, 1, 'G') {}
};

class Nuez : public Soporte {
public:
    Nuez() : Soporte(4000, 50, 1, 0, 'N') {}
};

class NuezDoble : public Soporte {
public:
    NuezDoble() : Soporte(8000, 125, 1, 0, 'N') {}
};

inline ostream& operator<<(ostream& os, Planta* planta) {
    os << "Vida: " <<  planta->getVida() << "\nCosto: " << planta->costo << "\nVelocidad de Ataque: " << planta->demora;
    return os;
}

#endif //PLANTA_H
