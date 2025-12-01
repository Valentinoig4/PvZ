//
// Created by fvale on 11/30/2025.
//

#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <iostream>
#include <utility>
using namespace std;

// CREAMOS LA CLASE BASE ZOMBIE

class Zombie {
public:

// Atributos importantes
    int vida;
    int velocidad = 5;
    int danio = 100;
    pair<int,int> pos;
    bool plantaCerca = false;
    bool especial = false;
    int ticks = 0;
    bool congelado = false;
    int ticksParalizado = 0;
    bool gigante = false;

    char ID = 'z';
    

    Zombie(int v, int vel) : vida(v), velocidad(vel) {}
    virtual ~Zombie() {}

    virtual void actuar() = 0;
//Setters
    void setVelocidad(int vel){ velocidad = vel;}
    void setCongelado(bool valor){ congelado = valor;}
    void setVida(int v) {vida = v;}
    void setPos(pair<int,int> p) { pos = p; }
    void setParalizado(int valor){ ticksParalizado = valor; }
    void setPlantaCerca(bool valor){ plantaCerca = valor; }
//Getters
    bool getCongelado() const { return congelado; }
    bool getPlantaCerca() const { return plantaCerca; }
    pair<int,int> getPos() const { return pos; }
    int getVida() const { return vida; }



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


    bool anadirTick(int demora){
        if (demora <= 0) return false;
        ticks++;
        return (ticks % demora == 0);

    }

    
};

class ZombieComun : public Zombie {
public:
    ZombieComun() : Zombie(190, 5) {
        ID = 'Z';
    }

    void actuar() override {
        if (anadirTick(velocidad) && ticksParalizado == 0) {
            pos.second--;
        }
        if (ticksParalizado > 0) ticksParalizado--;
    }
};


class ZombieCubo : public Zombie {
public:
    ZombieCubo() : Zombie(1290, 5) {
        ID = 'M';
    }

    void actuar() override {
        if (anadirTick(velocidad) && ticksParalizado == 0) {
            pos.second--;
        }    
        if (ticksParalizado > 0) ticksParalizado--;
    }
};


class ZombieCono : public Zombie {
public:
    ZombieCono() : Zombie(560, 5) {
        ID = 'O';
    }

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
        ID = 'A';
    }

    void Saltar() {
        cout << "Zombie atletico salto\n";
        velocidad = 5;  // aumentan los segundos por casilla
        especial = false; // no tiene habilidad
        pos.second--; // avanza una casilla instantaneamente
    }

    void actuar() override {
        if (plantaCerca && ticksParalizado == 0) Saltar();
        else if (anadirTick(velocidad) && ticksParalizado == 0) pos.second--;
        if (ticksParalizado > 0) ticksParalizado--;
    }
};


class ZombieGigante : public Zombie {
public:

    ZombieGigante() : Zombie(3000, 2) {
        danio = 5000;
        especial = true;
        gigante = true;
        ID = 'G';
    }

    pair<int,int> zombieLanzado; // Ubicacion del nuevo zombie


    void actuar() override {
        if (ticksParalizado == 0 && anadirTick(velocidad)) {
            pos.second--;
        }

        if (especial && vida <= 1500) {
            zombieLanzado.first = pos.first;
            zombieLanzado.second = pos.second - 4;
            if (zombieLanzado.second < 0) zombieLanzado.second = 0;
            
            especial = false;
        }

        

        if (ticksParalizado > 0) {
            ticksParalizado--;
        }
    }
};

class ZombiePeriodico : public Zombie {
public:
    ZombiePeriodico() : Zombie(340, 5) {
        especial = true;
    }

    void Enojar(){
        velocidad = 2; // se vuelve mas rapido
        especial = false;
    }

    void actuar() override {
        if (vida <= 190) Enojar();
        if (anadirTick(velocidad) && ticksParalizado == 0) pos.second--;
        if (ticksParalizado > 0) ticksParalizado--;

    }
};

#endif
