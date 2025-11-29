//
// Created by Rafael Chamayo on 29/11/25.
//

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

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


#endif //ZOMBIE_H