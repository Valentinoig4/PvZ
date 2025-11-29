//
// Created by vale on 11/26/2025.
//

#ifndef CPUZOMBIEOLEADAS_H
#define CPUZOMBIEOLEADAS_H

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
    double velocidad = 4.7;
    int danio = 100;
    pair<int,int> pos;

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
};



class ZombieComun : public Zombie {
public:
    ZombieComun() : Zombie(190, 4.7) {}

    void actuar() override {
        cout << "Zombie normal camina hacia la casa.\n";
    }
};



class ZombieFortificadoCasco : public Zombie {
public:
    ZombieFortificadoCasco() : Zombie(1290, 4.7) {}

    void actuar() override {
        cout << "Zombie con casco avanza .\n";
    }
};



class ZombieFortificadoCono : public Zombie {
public:
    ZombieFortificadoCono() : Zombie(560, 100) {}

    void actuar() override {
        cout << "Zombie cono avanza\n";
    }
};



class ZombieAtletico : public Zombie {
public:
    ZombieAtletico() : Zombie(335, 2.5) {}

    void Saltar() {
        cout << "Zombie atletico salto\n";
        velocidad = 4.7;
    }
    void actuar() override {
        cout << "Zombie atletico avanza rapidamente\n";
    }
};


class Oleadas {
public:
    int numeroOleada;

    Oleadas() : numeroOleada(1) {}

    void siguienteOleada() {
        numeroOleada++;
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




#endif //CPUZOMBIEOLEADAS_H
