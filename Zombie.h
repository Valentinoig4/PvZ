//
// Created by fvale on 11/30/2025.
//

#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <iostream>
#include <utility>
using namespace std;

class Zombie {
public:
    int vida;
    int velocidad = 5;
    int danio = 100;
    pair<int,int> pos;
    bool paralizado = false;
    bool PlantaCerca = false;
    bool especial = false;
    int ticks = 0;
    

    Zombie(int v, double vel) : vida(v), velocidad(vel) {}
    virtual ~Zombie() {}

    virtual void actuar() = 0;

    void recibirDanio(int d) {
        vida -= d;
        if (vida < 0) vida = 0;
    }

    bool estaVivo() {
        return vida > 0; 
    }

    void setPos(pair<int,int> p) { pos = p; }
    
    pair<int,int> getPos() const { return pos; }

    int getVida() const { return vida; }

    void setParalizado(bool valor){ paralizado = valor; }

    void setPlantaCerca(bool valor){ especial = valor; }

    bool anadirTick(int demora){
        if (ticks % demora == 0){
            return true;
        }
    }

    
};

class ZombieComun : public Zombie {
public:
    ZombieComun() : Zombie(190, 5) {}

    void actuar() override {
        if (anadirTick(velocidad) && not paralizado) {
            pos.second--;
        }
    }
};


class ZombieFortificadoCono : public Zombie {
public:
    ZombieFortificadoCono() : Zombie(560, 5) {}

    void actuar() override {
        if (anadirTick(velocidad) && not paralizado) {
            pos.second--;
        }    }
};


class ZombieAtletico : public Zombie {
public:
    ZombieAtletico() : Zombie(335, 3) {}

    bool especial = true;
    void Saltar() {
        cout << "Zombie atletico salto\n";
        velocidad = 5;
        especial = false;
        pos.first--;
    }

    void actuar() override {
        if (PlantaCerca && not paralizado) Saltar();
        else if (anadirTick(velocidad) && not paralizado) {
            pos.first--;
        }
    }
};




#endif
