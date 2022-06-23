#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED
#include <iostream>
#include <time.h>
using namespace std;

class Estado {
public:
    int bmc[3];  //arreglo con estados de bote-misionero-canibal

    Estado() { 
        bmc[0]=1; //lado del vote    1 -> izquierda  y    0 -> derecha
        bmc[1]=3; //numero de misioneros
        bmc[2]=3; //numero de canibales
    };

    Estado * apuntadorEstado(){  //auto apuntador a la misma instancia de la clase
        return this;
    };

    void operator=(Estado e) { //tomo lo que está en e y lo copio
        for (int i=0; i<3; i++) {
            bmc[i]=e.bmc[i];
        }
    };

    void operator= (int e) { //tomo lo que está en e y lo copio
        for(int i=0; i<3; i++) {
            bmc[i]=e;
        }
    };

    bool operator==(Estado e) { //Sobrecarga del operador (==)
        bool flag=true;
        for(int i=0; i<3; i++) {
            if(bmc[i]==e.bmc[i]) {
                flag=false;
            }
        }
        return flag;
    };

    bool operator!=(Estado e) { //Sobrecarga del operador (!=)
        bool flag=false;
        for(int i=0; i<3; i++) {
            if(bmc[i]==e.bmc[i]) {
                flag=true;
            }
        }
        return flag;
    };

    bool estadoObjetivo() {   //metodo que inidica si se alcanzo el estado objetivo
        return (bmc[0] == 0 && bmc[1]==0 && bmc[2]==0 ); //Retorno false o true, dependiendo si llego al estado objetivo
    };

    void print() {    //Imprimir el estado
        cout<<"- - - - - - - - -  \t \t- - - - - - - - -"<<endl;
        for(int i =0; i<3; i++) {
            cout<<bmc[i]<<"\t";
        }
        cout<<"\t";
        for(int i=0;i<3;i++){
            (i > 0) ? cout << 3 - bmc[i] << "\t" : cout << 1 - bmc[i] << "\t";
        }
        cout<<endl<<"- - - - - - - - - \t \t- - - - - - - - -"<<endl;
    };
};

class Nodo {
public:
    Nodo * punteroPadre;    //Puntero a padre
    Nodo **punteroHijos;   //Puntero a hijos
    int  fR;    //Factor de ramificación (numero de hijos en cada nodo)
    int n;      //Profundidad del arbol (nivel)--> cantidad de nodos en el camino mas largo de la raiz a una hoja
    Estado e;   //Estado almacena el estado

    Nodo() {
        punteroPadre=NULL;
        punteroHijos=NULL;
        fR=0;
        n=0;  
    };

    Nodo* autoApuntador() { //retorna un puntero a su posicion
        return this;
    };

    int funcionSucesor() { //retorna el numero de hijos para cada nodo --> maximo 5 
        int cantidadHijos=5, fact;
        int accion[3][5];
        int aux[3];
        /*  
         *  1   1   1    1   1  
         *  1   2   0    1   0
         *  1   0   2    0   1
         */
        //Accion 0: MBC
        accion[0][0]=1; //b
        accion[1][0]=1; //m
        accion[2][0]=1; //c
        //Accion 1: BMM
        accion[0][1]=1; //b
        accion[1][1]=2; //m m
        accion[2][1]=0;
        //Accion 2: BCC
        accion[0][2]=1; //b
        accion[1][2]=0;
        accion[2][2]=2; //c c
        //Accion 3: BM
        accion[0][3]=1; //b
        accion[1][3]=1; //m
        accion[2][3]=0;
        //Accion 4: BC
        accion[0][4]=1;  //b
        accion[1][4]=0;
        accion[2][4]=1;  //c

        int accionValida[5] = {1, 1, 1, 1, 1}; // 0 --> accion posible; 1 -> accion invalida;

        //obtiene los posibles estados a partir del padre
        for(int j=0; j<5; j++) {
            fact = (e.bmc[0] == 1) ? -1 : 1; //  1 -> der a izq; -1 -> de izq a der;
            for(int i =0; i<3;i++) {  // genera hijos al padre --> maximo 5
                aux[i]=e.bmc[i]+fact*accion[i][j];
            }
                //validacion parte izquierda        //validacion parte derecha                //validacion 0< c,m <4 
            if(((aux[1]<aux[2])&&(aux[1]>0)) || ((3-aux[1]<3-aux[2])&&(3-aux[1]>0))|| aux[1]>3 ||aux[1]<0 || aux[2]>3||aux[2]<0) { 
                accionValida[j]=0;
                cantidadHijos--;
            }

        }
        expansion(cantidadHijos); //genera hijos de acuerdo al padre

        int cont=0;
        for(int j=0;j<5;j++){ // definicion de estado del hijo de acuerdo a la accion permitida
            if(accionValida[j]==1){
               for(int i=0;i<3;i++){
                    // el hijo tiene el mismo estado del padre y se le suma el el factor por la accion
                    punteroHijos[cont]-> e.bmc[i]=punteroHijos[cont]->e.bmc[i]+(fact*accion[i][j]);
               }
               cont++;
            }
        }
        return cantidadHijos;
    };

    void expansion(int cantidadHijos){     //creacion de hijos de acuerdo a su cantidad
        fR=cantidadHijos;
        punteroHijos=new Nodo*[fR];    //creado espacio en memoria para los arreglos
        for(int i=0;i<fR;i++){
            punteroHijos[i]=new Nodo;
            punteroHijos[i]->punteroPadre=this; // se hace un auto apuntado
            punteroHijos[i]->n=n+1;  //el nivel del hijo es igual al del padre + 1
            punteroHijos[i]->e=e;      // el estado del hijo es igual al del padre
        }   
    };

    Nodo* hallarRaiz(Nodo *pnt){    //recupera el nodo padre
        Nodo *Padre;
        if(pnt->punteroPadre!=NULL){
            pnt->e.print();
            Padre=hallarRaiz(pnt->punteroPadre);
        }else{
            pnt->e.print();
        };
        return Padre;
    };
};

// la frontera es un arreglo dinamico
class Frontera{
public:
    Nodo **f;   //Conjunto de elementos en frontera / Arreglo dinámico de punteros a nodo
    Estado *arregloEstados, *estadoVisitado;    
    int nodosTotalesF;    //Número de elementos de frontera

    Frontera(){ //Constructor
        f=NULL; //Puntero inicial apunta a null / nada
        nodosTotalesF=0;  //Inicializo contador de frontera a 0
    };

    Frontera* autoApuntadorF() {return this;};

    ~Frontera(){    //Destructor de la clase
        for(int C=0; C<nodosTotalesF;C++){f[C]=NULL;};
        f=NULL;
        nodosTotalesF=0;
    };

    bool fronteraVacia(){ return (f == NULL); }// true --> frontera vacia; false --> frontera con elementos

    void addElemento (Nodo *n){
        Nodo **aux;                 //Arreglo temporal de punteros a nodos
        aux=new Nodo* [nodosTotalesF+1];      //Asigno dinamicamente nodosTotalesF+1 elementos en ATPN (uno mas de lo que hay en f)
        for(int i=0;i<nodosTotalesF;i++){
            aux[i]=f[i];            //ATPN igual a frontera APN (Arreglo de punteros a nodo)
        }
        aux[nodosTotalesF]=n;                 //Ingreso el nuevo elemento al final de la frontera
        if(nodosTotalesF>0){delete[] f;}           //Borro el espacio de memoria del arreglo de punteros de f
        f=aux;                      //f toma lo que se tiene en auxx
        nodosTotalesF++;                      //Aumento e numero de elementos de frontera
    };

    void almacenarVisitado (Estado *estado){
        arregloEstados = new Estado [nodosTotalesF + 1]; // Asigno dinamicamente nodosTotalesF+1 elementos en ATPN (uno mas de lo que hay en f)
        for (int i = 0; i < nodosTotalesF; i++){
                arregloEstados[i] = estadoVisitado[i]; // ATPN igual a frontera APN (Arreglo de punteros a nodo)
        }
        arregloEstados[nodosTotalesF]=*estado;                 //Ingreso el nuevo elemento al final de la frontera
        estadoVisitado=arregloEstados;                      //f toma lo que se tiene en auxx
        nodosTotalesF++;                      //Aumento e numero de elementos de frontera
    };

    bool fueVisitado(Estado *estado){
        bool resultado = false;
        for(int i=0;i<nodosTotalesF;i++){
            if((estado->bmc[0]==estadoVisitado[i].bmc[0]) && (estado->bmc[1]==estadoVisitado[i].bmc[1]) && (estado->bmc[2]==estadoVisitado[i].bmc[2])){
                resultado=true;
                estado->print();
                cout<<"YA FUE VISITADO"<<endl;
                return resultado;
            }
        }
        estado->print();
        cout<<"NO FUE VISITADO"<<endl;
        return resultado;
    };




    bool eliminarElemento(Nodo *n){
        bool resultado = false;
        Nodo **aux;
        aux= new Nodo*[nodosTotalesF-1];
        int pos=-1;
        for(int i=0;i<nodosTotalesF;i++){
            if(n==f[i]){
                pos=i;
                resultado=true;
                break;
            }
        }
        if(pos!=-1){
            for(int i=0;i<pos;i++){
                aux[i]=f[i];
            }
            f[pos]=NULL;
            for(int i=pos;i<nodosTotalesF-1;i++){
                aux[i]=f[i+1];
                f[i+1]=NULL;
            }
            delete[] f;
            f=aux;
            nodosTotalesF--;
        }else{
            for(int i=0;i<nodosTotalesF-1;i++){
                aux[i]=NULL;
            }
            delete[]aux;
            aux=NULL;
        }
        return resultado;
    };

};


#endif // CABECERA_H_INCLUDED

