#include <iostream>
//#include <bits/stdc++.h>
#include "../Headers/cabecera.h"

using namespace std;
int anchuraBFS(Nodo *);
void estadosRepetidos(Nodo *, Frontera, Frontera);

int main(){
    Nodo nodo;   
    anchuraBFS(nodo.autoApuntador()); // argumento --> punteronodo --> auto-apuntado
    return 0;
};

int anchuraBFS(Nodo *punteroNodo){
    cout<<"-----------------  Busqueda en Anchura (BFS)  -----------------"<<endl;
    Frontera elementoF, frontera, estadoVisitado;
    frontera=*elementoF.autoApuntadorF();  // creacion y auto apuntado a los nodos de la frontera
    estadoVisitado = frontera;             // creacion y auto-apuntado a los estados en la frontera
    frontera.addElemento(punteroNodo);    // agregar un puntero a la frontera --> auto-Apuntado 

    Estado *punterobmc; //craecion de un puntero al estado
    Estado estado;

    int nivel=0;
    while(!frontera.fronteraVacia()){
        cout<<"-----------------------------------------------------"<<endl;
        cout<<endl<<"Nivel: "<<nivel<<endl;
        int nodosFrontera=frontera.nodosTotalesF;
        cout<<"Nodos en Frontera: "<<nodosFrontera<<endl;
        for(int i = 0; i<nodosFrontera;i++){                       
            cout<<"Extraccion de Nodo en Frontera"<<endl;
            punteroNodo=frontera.f[0];    //primer nodo de la frontera
            punteroNodo->e.impresion();
            if((punteroNodo->e.estadoObjetivo())){ // true --> estado objetivo alcanzado; false --> estado objetivo no alcanzado
                cout<<"-----------------------------------------------------"<<endl;
                cout << "Hallar Raiz:" << endl;
                punteroNodo->hallarRaiz(punteroNodo); // imprime los pasos hasta llegar al padre
                frontera.~Frontera();                 // elimina la frontera
                return 1;                             
            }else{
                estadoVisitado.almacenarVisitado(punteroNodo->e.apuntadorEstado()); // almacenar el estado auto-apuntado de la frontera             
                int cantidadHijos=punteroNodo->funcionSucesor();   // retorno de cantidad de hijos y su respectiva creacion
                cout<<"Hijos totales: "<<cantidadHijos<<endl;
                for(int j=0; j<punteroNodo->hijosporNodo;j++){                                 //PARA CADA HIJO DEL NODO EXTRAIDO HACER
                    if(estadoVisitado.fueVisitado(punteroNodo->punteroHijos[j]->e.apuntadorEstado())==false){  //VERIFICAMOS QUE EL ESTADO NO HAYA SIDO VISITADO
                        frontera.addElemento(punteroNodo->punteroHijos[j]);           //SI EL ESTADO DEL NODO HIJO NO HA SIDO VISITADO, SE LO AÑADE A LA FRONTERA
                    }
                }
                frontera.eliminarElemento(punteroNodo); 
            }
        }
        nivel++;
    };
    return 0;
};

