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
    pair<int,int> pos{};
    bool plantaEncima = false;
    bool plantaCerca = false;
    bool especial = false;
    int ticks = 0;
    bool congelado = false;
    int ticksParalizado = 0;


    Zombie(int v, int vel, pair<int, int> ij) : vida(v), velocidad(vel), pos(std::move(ij)) {}
    virtual ~Zombie() = default;

    virtual void actuar()  {
        if (!plantaEncima && ticksParalizado == 0) {
            pos.second--;
            if (plantaCerca) {
                plantaEncima = true;
            }
        }

        if (ticksParalizado > 0) ticksParalizado--;

    }

    void setVelocidad(int vel){ velocidad = vel;}

    void setCongelado(bool valor){ congelado = valor;}

    [[nodiscard]] bool getCongelado() const { return congelado; }
    [[nodiscard]] bool getPlantaCerca() const { return plantaEncima; }


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

    void setVida(int v) {vida = v;}

    void setPos(pair<int,int> p) { pos = p; }

    pair<int,int> getPos() const { return pos; }

    int getVida() const { return vida; }

    void setParalizado(int valor){
        ticksParalizado = valor;
    }

    void setPlantaCerca(bool valor){ plantaEncima = valor; }

    bool anadirTick(){
        ticks++;
        return (ticks % velocidad == 0);
    }


};

class ZombieComun : public Zombie {
public:
    explicit ZombieComun(pair<int, int>ij) : Zombie(190, 5,ij) {}
};


class ZombieCubo : public Zombie {
public:
    explicit ZombieCubo(pair<int,int>ij) : Zombie(1290, 5,ij) {}
};


class ZombieCono : public Zombie {
public:
    explicit ZombieCono(pair<int, int> ij) : Zombie(560, 5, ij) {}
};


class ZombieAtletico : public Zombie {
public:
    explicit ZombieAtletico(pair<int, int> ij) : Zombie(335, 3, ij) {
        especial = true;
    }

    void Saltar() {
        cout << "Zombie atletico salto\n";
        velocidad = 5;
        especial = false;
        pos.second--;
    }

    void actuar() override {
        if (!plantaEncima && ticksParalizado == 0) {
            pos.second--;
            if (plantaCerca && especial) {
                Saltar();
                plantaEncima = true;
            }
        };
        if (ticksParalizado > 0) ticksParalizado--;
    }
};


class ZombieGigante : public Zombie {
public:

    explicit ZombieGigante(pair<int, int> ij) : Zombie(3000, 2, ij) {
        danio = 5000;
        especial = true;
    }

    pair<int,int> zombieLanzado;



    void actuar() override {
        if (!plantaEncima && ticksParalizado == 0) {
            pos.second--;
        }

        if (especial && vida <= 1500) {
            zombieLanzado.first = pos.first;
            zombieLanzado.second = pos.second - 4;
            if (zombieLanzado.second < 1) zombieLanzado.second = 1;

            especial = false;
        }


        if (ticksParalizado > 0) {
            ticksParalizado--;
        }
    };
};

class ZombiePeriodico : public Zombie {
public:
    explicit ZombiePeriodico(pair<int, int > ij) : Zombie(340, 5, ij) {
        especial = true;
    }

    void Enojar(){
        velocidad = 2; // se vuelve mas rapido
        danio *= 2; // come mas rapido
        especial = false;
    }

    void actuar() override {
        if (vida <= 190) Enojar();
        if (!plantaEncima && ticksParalizado == 0) {
            pos.second--;
            if (plantaCerca) {
                plantaEncima = true;
            }
        }

        if (ticksParalizado > 0) ticksParalizado--;

    }
};


#endif
