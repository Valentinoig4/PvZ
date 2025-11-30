#ifndef PLANTA_H
#define PLANTA_H

class Planta {
protected:
    int vida{}, costo{}, nivel{};
    float demora{};
public:
    Planta() = default;
    virtual ~Planta() = default;
    Planta(int v, float d, int c, int n) : vida(v), costo(c), nivel(n), demora(d) {};
    virtual void accion() = 0;
    void recibir_dano(int dano) {
        vida -= dano;
        vida < 0 ? vida = 0 : vida;
    }
};

class Atacante : public Planta {
protected:
    int ataque{};
public:
    Atacante() = default;
    Atacante(int v, int a, float d, int c, int n) : Planta(v, d, c, n), ataque(a) {};
};

class LanzaGuisantes : public Atacante {
public:
    LanzaGuisantes() : Atacante(300, 20, 1.425, 100, 1) {}
    void accion () override {
        //atacar a zombie con ataque
    }
};

#endif //PLANTA_H
