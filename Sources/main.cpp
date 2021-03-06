#include <iostream>
//#include <bits/stdc++.h>
#include "../Headers/cabecera.h"
using namespace std;

void anchuraBFS(Nodo *punteroNodo){
    cout<<"-------------------------------------------------"<<endl;
    cout<<"----------  Busqueda en Anchura (BFS)  ----------"<<endl;
    Frontera elementoF, frontera, estadoVisitado;
    frontera=*elementoF.autoApuntadorF();  // creacion y auto apuntado a los nodos de la frontera
    estadoVisitado = frontera;             // creacion y auto-apuntado a los estados en la frontera
    frontera.addElemento(punteroNodo);    // agregar un puntero a la frontera --> auto-Apuntado 

    int nivelArbol=0;
    while(!frontera.fronteraVacia()){
        cout<<"-------------------------------------------------"<<endl;
        cout<<endl<<"Nivel: "<<nivelArbol<<endl;
        int nodosFrontera=frontera.nodosTotalesF;
        cout<<"Nodos en Frontera: "<<nodosFrontera<<endl;
        for(int i = 0; i<nodosFrontera;i++){                       
            punteroNodo=frontera.f[0];    //primer nodo de la frontera
            (punteroNodo->e.estadoObjetivo())? 
            cout << "\t   Estado Objetivo Alcanzado" << endl:
            cout<<endl<<"\t   Nodo Frotera - Nodo Padre ["<<i+1<<"]"<<endl;
            if((punteroNodo->e.estadoObjetivo())){ // true --> estado objetivo alcanzado; false --> estado objetivo no alcanzado
                punteroNodo->e.impresion();
                cout<<"-------------------------------------------------"<<endl;
                cout <<endl<<"\t\t   Hallar Raiz" << endl;
                punteroNodo->hallarRaiz(punteroNodo); // imprime los pasos hasta llegar al padre
                frontera.~Frontera();                 // elimina la frontera
                break;
            }
            punteroNodo->e.impresion();
            estadoVisitado.almacenarVisitado(punteroNodo->e.apuntadorEstado()); // almacenar el estado auto-apuntado de la frontera             
            int cantidadHijos=punteroNodo->funcionSucesor();   // retorno de cantidad de hijos y su respectiva creacion
            cout<<"Hijos totales: "<<cantidadHijos<<endl;
            for(int j=0; j<punteroNodo->hijosporNodo;j++){                                 
                if(!estadoVisitado.estadoshijos(punteroNodo->punteroHijos[j]->e.apuntadorEstado())){  // true --> estado usado; false--> estado nuevo
                    frontera.addElemento(punteroNodo->punteroHijos[j]);           //agrega estados no repetidos a la frontera
                }
            }
            frontera.eliminarElemento(punteroNodo); // se elimina el primer nodo
        }
        nivelArbol++;
    };
};


int main(){
    Nodo nodo;   
    anchuraBFS(nodo.autoApuntador()); // argumento --> punteronodo --> auto-apuntado
    return 0;
};

