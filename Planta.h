#ifndef PLANTA_H
#define PLANTA_H

#include "Zombie.h"

enum class tipoPlanta {
    atacante,productor, soporte
};

class Planta {
protected:
    int vida{}, costo{}, nivel{}, ticks{}, demora{};
public:
    tipoPlanta tipo;
    Planta() = default;
    Planta(tipoPlanta t, int v, float d, int c, int n) : vida(v), costo(c), nivel(n), demora(d), tipo(t) {}
    bool anadirTick() {
        ticks++;
        if (tipo != tipoPlanta::soporte && demora > 0)
            return ticks % demora == 0;
        return false;
    }
    void recibir_dano(int dano) {
        vida -= dano;
        vida < 0 ? vida = 0 : vida;
    }
};

class Atacante : public Planta {
protected:
    int ataque{};
public:
    Atacante() { tipo = tipoPlanta::atacante; }
    Atacante(int v, int a, int d, int c, int n) : Planta(tipoPlanta::atacante, v, d, c, n), ataque(a) {}
    virtual void accion(Zombie& z) = 0;
};

class Productor : public Planta {
protected:
    int soles{};
public:
    Productor() { tipo = tipoPlanta::productor; }
    Productor(int v, int s, int c, int n, int d) : Planta(tipoPlanta::productor, v, d, c, n), soles(s) {}
    virtual void accion() = 0;
};

class Soporte : public Planta {
public:
    Soporte() { tipo = tipoPlanta::soporte; };
    Soporte(int v, int c, int n, int d) : Planta(tipoPlanta::soporte, v, d, c, n) {}
};

class LanzaGuisantes : public Atacante {
public:
    LanzaGuisantes() : Atacante(300, 20, 3, 100, 1) {}
    void accion (Zombie& z) override {
        z.recibirDanio(ataque);
    }
};

class LanzaGuisantesDoble : public Atacante {
public:
    LanzaGuisantesDoble() : Atacante(200, 20, 3, 100, 1) {}
};

#endif //PLANTA_H
