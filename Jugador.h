#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include "Oleada.h"
#include "Mapa.h"

class Jugador {
protected:
    Mapa* m;
public:
    int soles{};
    string nombre{};
    Jugador() = default;
    Jugador(Mapa* mp, int s) : m(mp), soles(s) {}

    //Aca se le va a pedir al usuario que de una planta o elimine una y en que lugar la quiere poner

    void fasePlantas(Oleada& o) {
        int numero=0, fila=0, columna=0, costo=0;
        vector<string> pDisponibles = o.getPlantasDisponibles();
        cout<<"Plantas disponibles: " << endl;
        for (int i = 0; i < pDisponibles.size(); i++) {
            cout<<i+1<<" ("<<pDisponibles[i]<<") ";
        }
        cout<<endl << endl;
        while (true) {
            cout<<"Soles disponibles: "<<soles<<endl;
            cout<<"Numero de la planta (-1 para finalizar): ";
            numero = 0, fila = 0, columna = 0, costo = 0;
            while (numero < 1 || numero > pDisponibles.size()) {
                cin>>numero;
                if (numero == -1) return;
            }
            if (pDisponibles[numero-1] == "Lanzaguisantes") costo = 100;
            else if (pDisponibles[numero-1] == "Lanzaguisantes Doble") costo = 150;
            else if (pDisponibles[numero-1] == "Lanzaguisantes de Hielo") costo = 175;
            else if (pDisponibles[numero-1] == "Lanzaguisantes de fuego") costo = 150;
            else if (pDisponibles[numero-1] == "Lanzamaiz") costo = 100;
            else if (pDisponibles[numero-1] == "Girasol") costo = 50;
            else if (pDisponibles[numero-1] == "Girasol Doble") costo = 100;
            else if (pDisponibles[numero-1] == "Nuez") costo = 50;
            else if (pDisponibles[numero-1] == "Nuez Doble") costo = 125;
            if (soles - costo < 0) {
                cout<<"Soles insuficientes"<<endl;
                continue;
            }
            soles -= costo;
            cout << endl;m->imprimir(); cout << endl;
            cout<<"Fila y columna para la Planta (fila columna): " ;
            while (fila < 1 || fila > 5 || columna < 1 || columna > 9) {
                cin>>fila;
                cin>>columna;
            }
            cout << endl;
            if (!m->aniadirPlanta(pDisponibles[numero-1], fila-1, columna)) {
                cout<<"Casilla ocupada"<<endl;
                soles += costo;
            }
        }
    }
};
#endif //JUGADOR_H
