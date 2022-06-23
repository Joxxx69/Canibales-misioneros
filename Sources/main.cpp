#include <iostream>
#include "../Headers/cabecera.h"

void almacenarVisitado(Estado *);
bool fueVisitado(Estado );
int anchuraBFS(Nodo *);
Estado *arregloEstados, *estadoVisitado;    
int nodosVisitado = 0;
 
int main(){
    Nodo nodo,*punteroNodo=NULL;    
    punteroNodo=nodo.autoApuntador();
    anchuraBFS(punteroNodo);
    return 0;
};

//int anchuraBFS(Nodo *punteroNodo){
int anchuraBFS(Nodo *punteroNodo){
    int nivel=0;
    cout<<"-----------------  BUSQUEDA EN BFS  -----------------"<<endl;

    //CREACIÓN DE LA FRONTERA Y UN APUNTADOR A LA FRONTERA
    //Frontera elementoF,*frontera=NULL;
    //frontera=elementoF.autoApuntadorF();
    //frontera->addElemento(punteroNodo);
    Frontera elementoF,frontera;
    frontera=*elementoF.autoApuntadorF();
    frontera.addElemento(punteroNodo);

    //CREACIÓN DEL ARRAY DE ESTADOS VISITADOS Y UN PUNTERO AL ARRAY
    Explorado expl;
    Explorado *explorad;
    explorad=expl.autoApuntExpl();

    //CREACION DE UN PUNTERO DE TIPO ESTADO
    Estado *punterobmc;

    //CICLO PARA QUE EXPLORE EL NODO ACORDE A LOS ELEMENTOS DE LA FRONTERA
    do{
        cout<<"-----------------------------------------------------"<<endl;
        cout<<"\n\t\tNIVEL DEL ARBOL: "<<nivel++<<endl;
        //int nodosTotalesFrontera=frontera->nodosTotalesF;
        int nodosTotalesFrontera=frontera.nodosTotalesF;
        cout<<"NUMERO DE ELEMENTOS EN FRONTERA: "<<nodosTotalesFrontera<<endl;
        for(int i = 0; i<nodosTotalesFrontera;i++){                                      //PARA CADA ELEMENTO DE LA FRONTERA
            cout<<"EXTRAYENDO EL PRIMER NODO DE LA FRONTERA"<<endl;
            punteroNodo=frontera.f[0];                                                   // EXTRAER EL PRIMER ELEMENTO DE LA FRONTERA
            punteroNodo->e.print();
            if((punteroNodo->e.estadoObjetivo())){                                 //TEST OBJETIVO DEL ESTADO DEL NODO ESTRAIDO
                    cout<<"EXISTE UNA SOLUCION: \nSE DESCRIBE LOS PASOS A REALIZAR EN ORDEN INVERSO: "<<endl;
                    punteroNodo->hallarRaiz(punteroNodo);                                          //SI HALLA LA SOLUCION IMPRIME
                    frontera.~Frontera();                                       //DESTRUYE LOS OBJETOS DE TIPO FRONTERA
                    return 1;                                                    //RETORNA 1 SI HALLA LA SOLUCIÓN
            }else{                                                      //SI EL ESTADO NO ES EL OBJETIVO HACER ...
                punterobmc=punteroNodo->e.apuntadorEstado();                         //CREAMOS UN PUNTERO AL ESTADO DEL NODO EXTRAIDO DE LA FRONTERA
                cout<<"puntero bmc: "<<endl;
                //punterobmc->print();
                explorad->addEstadoVisitado(punterobmc);                    //AÑADIMOS EL ESTADO EXTRAIDO A LA LISTA DE ESTADOS VISITADOS
                int num_Hijos_Creados=punteroNodo->funcionSucesor();                                       //CREAMOS LOS HIJOS DEL NODO EXTRAIDO DE LA FRONTERA
                //punteroNodo->e.print();
                cout<<"EL NUMERO DE HIJOS POSIBLES QUE TIENE ES: "<<num_Hijos_Creados<<endl;
                //cout<<"HIJOS DEL NODO "<<i<<" EN FRONTERA: "<<punteroNodo->fR<<endl;

                for(int j=0; j<punteroNodo->fR;j++){                                 //PARA CADA HIJO DEL NODO EXTRAIDO HACER
                    //if(explorad->fueVisitado(punteroNodo->punteroHijos[j]->e.apuntadorEstado())==false){  //VERIFICAMOS QUE EL ESTADO NO HAYA SIDO VISITADO
                    if(explorad->fueVisitado(punteroNodo->punteroHijos[j]->e.apuntadorEstado())==false){  //VERIFICAMOS QUE EL ESTADO NO HAYA SIDO VISITADO
                        frontera.addElemento(punteroNodo->punteroHijos[j]);           //SI EL ESTADO DEL NODO HIJO NO HA SIDO VISITADO, SE LO AÑADE A LA FRONTERA
                        //punteroNodo->punteroHijos[j]->e.print();
                    }
                }
                frontera.eliminarElemento(punteroNodo);             //COMO EL NODO FUE EXTRAIDO DE LA FRONTERA, LO ELIMINAMOS
            }
            //cout<<"INGRESARON EN FRONTERA"<<endl;
        }
        //break;
    }while(frontera.fronteraVacia()==false);
    return 0;
};

 

void almacenarVisitado (Estado *estado){
    arregloEstados = new Estado [nodosVisitado + 1]; // Asigno dinamicamente nodosTotalesF+1 elementos en ATPN (uno mas de lo que hay en f)
    for (int i = 0; i < nodosVisitado; i++){
            arregloEstados[i] = estadoVisitado[i]; // ATPN igual a frontera APN (Arreglo de punteros a nodo)
    }
    arregloEstados[nodosVisitado]=*estado;                 //Ingreso el nuevo elemento al final de la frontera
    estadoVisitado=arregloEstados;                      //f toma lo que se tiene en auxx
    nodosVisitado++;                      //Aumento e numero de elementos de frontera
};

bool fueVisitado(Estado estado){
    bool resultado = false;
    for(int i=0;i<nodosVisitado;i++){
        if((estado.bmc[0]==estadoVisitado[i].bmc[0]) && (estado.bmc[1]==estadoVisitado[i].bmc[1]) && (estado.bmc[2]==estadoVisitado[i].bmc[2])){
            resultado=true;
            estado.print();
            cout<<"YA FUE VISITADO"<<endl;
            return resultado;
        }
    }
    estado.print();
    cout<<"NO FUE VISITADO"<<endl;
    return resultado;
};


