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
    string nombre{};
    Jugador() = default;
    Jugador(Mapa* mp) : m(mp) {}

    //Aca se le va a pedir al usuario que de una planta o elimine una y en que lugar la quiere poner

    void fasePlantas(Oleada& o) {
        int numero=0, fila=0, columna=0, costo=0;
        int plantasPuestas{};
        vector<string> pDisponibles = o.getPlantasDisponibles();
        cout<<"Plantas disponibles: " << endl << endl;
        for (int i = 0; i < pDisponibles.size(); i++) {
            cout<<i+1<<": "<<pDisponibles[i];
            cout<< endl;
            cout << o.plantas[i];
            cout << endl << endl;
        }
        cout<<endl;
        char opcion{};
        while (opcion != 'A') {
            cout << "A. SALIR " << endl;
            cout << "B. PONER PLANTA" << endl;
            cout << "C. ELIMINAR PLANTA" << endl;
            cout<<"Soles disponibles: "<<soles<<endl;
            cout << "Opcion: ";
            cin >> opcion;
            if (opcion == 'B') {
                cout<< endl <<"Numero de la planta: ";
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
                cout << endl;m->imprimir();

                cout<<"Fila y columna para la Planta (fila columna): " ;
                while (fila < 1 || fila > 5 || columna < 1 || columna > 9) {
                    cin>>fila;
                    cin>>columna;
                }
                cout << endl;
                if (!m->aniadirPlanta(pDisponibles[numero-1], fila-1, columna)) {
                    cout<<"Casilla ocupada"<<endl;
                    soles += costo;
                } else {
                    plantasPuestas++;
                }
            } else if (opcion == 'C') {
                if (plantasPuestas== 0) {
                    cout << "No se han puesto plantas aun" << endl << endl;
                    continue;
                }
                cout << endl << endl;
                m->imprimir();
                cout << endl << endl;
                cout<<"Fila y columna para eliminar planta (fila columna): " ;
                while (fila < 1 || fila > 5 || columna < 1 || columna > 9) {
                    cin>>fila;
                    cin>>columna;
                }
                if (m->grilla[fila-1][columna].planta != nullptr) {
                    soles+= m->grilla[fila][columna].planta->costo;
                }
                if (m->eliminarPlanta(fila-1, columna)) {
                    cout << "Planta eliminada exitosamente" << endl;
                } else {
                    cout << "No habia plantas ahi" << endl;
                }

            }
        }
    }
};
#endif //JUGADOR_H
