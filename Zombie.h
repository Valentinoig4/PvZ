//
// Created by vale on 11/26/2025.
//

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include <utility>
using namespace std;

class Zombie {
protected:
    int vida;
    double velocidad = 4.7;
    int danio = 100;
    pair<int,int> pos;
    bool paralizado = false;
    int ticks = 0;
    bool PlantaCerca = false;


public:
    Zombie(int v, double vel) : vida(v), velocidad(vel) {}
    virtual ~Zombie() {}

    virtual void actuar() = 0;

    void recibirDanio(int d) {
        vida -= d;
        if (vida < 0) vida = 0;
    }

    bool estaVivo() { return vida > 0; }

    void setPos(pair<int,int> p) { pos = p; }
    pair<int,int> getPos() const { return pos; }

    int getVida() const { return vida; }

    void setParalizado(bool valor){
        paralizado = valor;

    
};

class ZombieComun : public Zombie {
public:
    ZombieComun() : Zombie(190, 4.7) {}

    void actuar() override {
        cout << "Zombie normal camina hacia la casa.\n";
    }
};


class ZombieFortificadoCono : public Zombie {
public:
    ZombieFortificadoCono() : Zombie(560, 4.7) {}

    void actuar() override {
        cout << "Zombie cono avanza\n";
    }
};


class ZombieAtletico : public Zombie {
public:
    ZombieAtletico() : Zombie(335, 2.5) {}

    bool saltar = true;

    void Saltar() {
        cout << "Zombie atletico salto\n";
        velocidad = 4.7;
        saltar = false;
        pos.first++;
    }

    void actuar() override {
        cout << "Zombie atletico avanza rapidamente\n";
    }
};

#endif


#endif



