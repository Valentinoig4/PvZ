#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include "Planta.h"
#include "Oleada.h"
#include "Mapa.h"

class Jugador {
protected:
    Mapa* m;
public:
    int soles{};
    Jugador() = default;
    Jugador(Mapa* mp, int s) : m(mp), soles(s) {}
    //Aca se le va a pedir al usuario que de una planta y en que lugar la quiere poner
    void pedirPlantas(Oleada* o) {
        int numero=0, fila=0, columna=0, costo=0;
        vector<string> pDisponibles = o->getPlantasDisponibles();
        cout<<"ELIJA SUS PLANTAS:"<<endl;
        cout<<"Plantas disponibles:"<<endl;
        for (int i = 0; i < pDisponibles.size(); i++) {
            cout<<i+1<<": "<<pDisponibles[i]<<" ";
        }
        cout<<endl;
        while (true) {
            cout<<"Soles disponibles: "<<soles<<endl;
            cout<<"Ingrese el numero de la planta (para finalizar ingrese -1): ";
            while (numero < 1 || numero > pDisponibles.size()) {
                cin>>numero;
                if (numero == -1) return;
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
                    numero = 0;
                }
            }
            soles -= costo;
            cout<<"Ingrese la fila y columna donde poner la planta (fila columna)";
            while (fila < 1 || fila > 5 || columna < 1 || columna > 9) {
                cin>>fila;
                cin>>columna;
            }
            if (!m.ponerPlanta(pDisponibles[numero-1], fila-1, columna)) {
                cout<<"Casilla ocupada"<<endl;
                soles += costo;
            }
        }
    }
};
#endif //JUGADOR_H