//
// Created by vale on 11/26/2025.
//

#ifndef SEMANA15_CPUZOMBIEOLEADAS_H
#define SEMANA15_CPUZOMBIEOLEADAS_H

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Mapa {
public:
    int filas, columnas;

    Mapa(int f = 5, int c = 9) : filas(f), columnas(c) {}

    pair<int,int> posAleatoria() {
        return { rand() % filas, 1 };
    }
};


class Zombie {
protected:
    int vida;
    int velocidad;
    pair<int,int> pos;

public:
    Zombie(int v, int vel) : vida(v), velocidad(vel) {}

    virtual ~Zombie() {}

    virtual void actuar() = 0;

    virtual void recibirDanio(int d) {
        vida -= d;
        if (vida < 0) vida = 0;
    }

    bool estaVivo() { return vida > 0; }

    void setPos(pair<int,int> p) { pos = p; }

    pair<int,int> getPos() const { return pos; }

    int getVida() const { return vida; }
};



class ZombieComun : public Zombie {
public:
    ZombieComun() : Zombie(50, 1) {}

    void actuar() override {
        cout << "Zombie normal camina hacia la casa.\n";
    }
};



class ZombieFortificadoCasco : public Zombie {
public:
    ZombieFortificadoCasco() : Zombie(150, 1) {}

    void actuar() override {
        cout << "Zombie con casco avanza .\n";
    }

    void recibirDanio(int d) override {
        vida -= d;
        if (vida < 0) vida = 0;
    }
};



class ZombieFortificadoCono : public Zombie {
public:
    ZombieFortificadoCono() : Zombie(100, 1) {}

    void actuar() override {
        cout << "Zombie cono avanza\n";
    }

    void recibirDanio(int d) override {
        vida -= d;
        if (vida < 0) vida = 0;
    }
};



class ZombieAtletico : public Zombie {
public:
    ZombieAtletico() : Zombie(80, 3) {}

    void actuar() override {
        cout << "zombie corredor corre  rápido y salta la primera planta\n";
    }
};


class Oleadas {
public:
    int numeroOleada;
    vector<Zombie*> zombies;

    Oleadas() : numeroOleada(1) {}

    void siguienteOleada() {
        numeroOleada++;
        zombies.clear();
    }
};



class CPU {
public:
    Oleadas oleadas;
    Mapa* mapa;

    CPU(Mapa* m) : mapa(m) {}

    Zombie* generarZombieRandom() {
        int tipo = rand() % 4;

        if (tipo == 0) {
            cout << "CPU hizo Zombie normal\n";
            return new ZombieComun();
        }
        if (tipo == 1) {
            cout << "CPU hizo zombie de casco\n";
            return new ZombieFortificadoCasco();
        }
        if (tipo == 2) {
            cout << "CPU hizo zombie de cono\n";
            return new ZombieFortificadoCono();
        }
        cout << "CPU hizo Zombie atletico\n";
        return new ZombieAtletico();
    }

    void colocarZombie() {
        Zombie* z = generarZombieRandom();
        pair<int,int> pos = mapa->posAleatoria();
        z->setPos(pos);
    }
};




#endif //SEMANA15_CPUZOMBIEOLEADAS_H