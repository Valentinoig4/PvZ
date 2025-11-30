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
    bool plantaCerca = false;
    bool especial = false;
    int ticks = 0;
    bool congelado = false;
    int ticksParalizado = 0;
    

    Zombie(int v, int vel) : vida(v), velocidad(vel) {}
    virtual ~Zombie() {}

    virtual void actuar() = 0;

    void setVelocidad(int vel){ velocidad = vel;}

    void setCongelado(bool valor){ congelado = valor;}

    bool getCongelado() const { return congelado; }
    bool getPlantaCerca() const { return plantaCerca; }


    void recibirDanio(int d) {
        vida -= d;
        if (vida < 0) vida = 0;
    }

    void operator-=(int d) {
        vida -= d;
        if (vida < 0) vida = 0;
    }

    bool estaVivo() const {
        return vida > 0; 
    }

    void setPos(pair<int,int> p) { pos = p; }
    
    pair<int,int> getPos() const { return pos; }

    int getVida() const { return vida; }

    void setParalizado(int valor){ 
        ticksParalizado = valor;
    }

    void setPlantaCerca(bool valor){ plantaCerca = valor; }

    bool anadirTick(int demora){
        if (demora <= 0) return false;
        ticks++;
        return (ticks % demora == 0);

    }

    
};

class ZombieComun : public Zombie {
public:
    ZombieComun() : Zombie(190, 5) {}

    void actuar() override {
        if (anadirTick(velocidad) && ticksParalizado == 0) {
            pos.second--;
        }
        if (ticksParalizado > 0) ticksParalizado--;
    }
};


class ZombieCubo : public Zombie {
public:
    ZombieCubo() : Zombie(1290, 5) {}

    void actuar() override {
        if (anadirTick(velocidad) && ticksParalizado == 0) {
            pos.second--;
        }    
        if (ticksParalizado > 0) ticksParalizado--;
    }
};


class ZombieCono : public Zombie {
public:
    ZombieCono() : Zombie(560, 5) {}

    void actuar() override {
        if (anadirTick(velocidad) && ticksParalizado == 0) {
            pos.second--;
        }

        if (ticksParalizado > 0) ticksParalizado--;

    }
};


class ZombieAtletico : public Zombie {
public:
    ZombieAtletico() : Zombie(335, 3) {
        especial = true;
    }

    void Saltar() {
        cout << "Zombie atletico salto\n";
        velocidad = 5;
        especial = false;
        pos.second--;
    }

    void actuar() override {
        if (plantaCerca && ticksParalizado == 0) Saltar();
        else if (anadirTick(velocidad) && ticksParalizado == 0) pos.second--;
        if (ticksParalizado > 0) ticksParalizado--;
        
        }
    }
};




#endif













