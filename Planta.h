#ifndef PLANTA_H
#define PLANTA_H

#include <random>
#include "Zombie.h"

enum class tipoPlanta {
    atacante,productor, soporte
};

enum class nombrePlanta {
    lanzaGuisantes, lanzaGuisantesDoble, lanzaGuisantesHielo,
    lanzaGuisantesFuego, lanzaMaiz, girasol, girasolDoble,
    nuez, nuezDoble, n
};

class Planta {
protected:
    int vida{}, costo{}, nivel{}, ticks{}, demora{};
public:
    tipoPlanta tipo;
    nombrePlanta nombre{};
    Planta() = default;
    Planta(tipoPlanta t, nombrePlanta p, int v, float d, int c, int n) : vida(v), costo(c), nivel(n), demora(d), tipo(t) {}
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
};

class Atacante : public Planta {
protected:
    int ataque{};
public:
    Atacante() { tipo = tipoPlanta::atacante; }
    Atacante(nombrePlanta p, int v, int a, int d, int c, int n) : Planta(tipoPlanta::atacante, p, v, d, c, n), ataque(a) {}
    virtual void accion(Zombie& z) {
        z -= ataque;
    }
};

class Productor : public Planta {
protected:
    int soles{};
public:
    Productor() { tipo = tipoPlanta::productor; }
    Productor(nombrePlanta p, int v, int s, int d, int c, int n) : Planta(tipoPlanta::productor, p, v, d, c, n), soles(s) {}
    int habilidadPasiva() {return soles;}
};

class Soporte : public Planta {
public:
    Soporte() { tipo = tipoPlanta::soporte; };
    Soporte(nombrePlanta p, int v, int c, int n, int d) : Planta(tipoPlanta::soporte, p, v, d, c, n) {}
};

class LanzaGuisantes : public Atacante {
public:
    LanzaGuisantes() : Atacante(nombrePlanta::lanzaGuisantes, 300, 20, 3, 100, 1) {}
};

class LanzaGuisantesDoble : public Atacante {
public:
    LanzaGuisantesDoble() : Atacante(nombrePlanta::lanzaGuisantesDoble, 300, 40, 3, 150, 1) {}
};

class LanzaGuisantesHielo : public Atacante {
public:
    LanzaGuisantesHielo() : Atacante(nombrePlanta::lanzaGuisantesHielo, 300, 20, 3, 175, 1) {}
    void accion(Zombie& z) override {
        z -= ataque;
        !z.congelado ? z.velocidad += 2 : z.velocidad;
        z.congelado = true;
    }
};

class LanzaGuisantesFuego : public Atacante {
public:
    LanzaGuisantesFuego() : Atacante(nombrePlanta::lanzaGuisantesFuego, 300, 30, 3, 150, 1) {}
};

class LanzaMaiz : public Atacante {
public:
    LanzaMaiz() : Atacante(nombrePlanta::lanzaMaiz, 300, 20, 3, 100, 1) {}
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
    Girasol() : Productor(nombrePlanta::girasol, 300, 50, 49, 50, 1) {}
};

class GirasolDoble : public Productor {
public:
    GirasolDoble() : Productor(nombrePlanta::girasolDoble, 300, 100, 49, 50, 1) {}
};

class Nuez : public Soporte {
public:
    Nuez() : Soporte(nombrePlanta::nuez, 4000, 50, 1, 0) {}
};

class NuezDoble : public Soporte {
public:
    NuezDoble() : Soporte(nombrePlanta::nuezDoble, 8000, 125, 1, 0) {}
};

#endif //PLANTA_H
