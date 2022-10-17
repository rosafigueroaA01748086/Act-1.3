#include "bitacora.hpp"
#include <vector>
#include <fstream> //Biblioteca para lectura y escritura de archivos

int particion(vector<Bitacora *> &log,int inicio, int fin){
    int pivote=log[inicio]->getClave(); //pivote
    int i=(fin+1);
    
    for(int j=fin;j>inicio;j--){
        if(log[j]->getClave()>pivote){
            i--;
            swap(log[i],log[j]);
        }
    }
    i--;
    swap(log[i],log[inicio]);
    return(i);
}

//QuickSort recursiva
void quickSort(vector<Bitacora *> &log, int inicio, int fin){
    //Caso recursivo
    if(inicio<fin){
        //Encontrar la posición final (índice del pivote dentro del arreglo) y además
        //colocar los elementos menores a la izquierda y los mayores a la derecha 
        int pivote = particion(log,inicio,fin);
        //Partición izquierda
        quickSort(log,inicio,pivote-1);
        //Partición derecha
        quickSort(log,pivote+1,fin);
    }
    //Caso Base
}

void busqueda(int inicioBusq,int finalBusq,vector<Bitacora *> log){
    int tam=log.size();
    ofstream archivoBusq("busqueda.txt"); 
    int revisar=0;
    for(int i=0; i<tam;i++){
        if(log[i]->getClave()<=finalBusq && log[i]->getClave()>=inicioBusq){
            revisar=1;
            log[i]->imprimirRegistro();
            archivoBusq<<log[i]->getMes()<<" "<<log[i]->getDia()<<" "<<log[i]->getHora()<<" "<<log[i]->getIpp()<<" "<<log[i]->getFalla()<<"\n";
        }
    }
    archivoBusq.close();
    if (revisar==0){
        cout<<"NO SE ENCONTRARON DATOS EN ESAS FECHAS. INTENTE CON OTRAS."<<endl;
    }
}

int main(){
 
    //Lectura de archivos
    ifstream datos; //Stack
    datos.open("bitacoraPrincipal.txt");
    string entrada;
   
    string mes,dia,hora,ipp,falla;
    vector<Bitacora *> log; //vector con objetos dentro del heap

    while(datos.good()){
        getline(datos,mes,' ');
        getline(datos,dia,' ');
        getline(datos,hora,' ');
        getline(datos,ipp,' ');
        getline(datos,falla);
        log.push_back(new Bitacora(mes,dia,hora,ipp,falla)); //vectores insertados en un arreglo
    }
    datos.close();

    quickSort(log,0,log.size()-1);
   
    int tam= log.size();  
    for(int i=0;i<tam;i++)
        log[i]->imprimirRegistro();


    ofstream archivo("ordenamiento.txt"); 
    for(int i=0;i<tam;i++)
        archivo<<log[i]->getMes()<<" "<<log[i]->getDia()<<" "<<log[i]->getHora()<<" "<<log[i]->getIpp()<<" "<<log[i]->getFalla()<<"\n";
    archivo.close();  

    cout<<"**BUSQUEDA DE INFORMACION**"<<endl;
    int respuesta=1;
    string mesInicio;
    string diaInicio;
    string mesFin;
    string diaFin;
    int inicioBusq;
    int finalBusq;

    while(respuesta == 1){
        cout<<"Primero introduzca los datos del INICIO de su búsqueda en cifras de dos digitos. Por ejemplo: si el mes es enero deberá de escribir 01. Lo mismo sucederá con los días, 02 corresponde al segundo día."<<endl;
        cout<<"Introduzca el mes: "; 
        cin>>mesInicio;
        cout<<"Introduzca el dia: "; 
        cin>>diaInicio;
        inicioBusq = stoi(mesInicio+diaInicio);
        cout<<"Primero los datos del FIN de su búsqueda en cifras de dos digitos. Usando el mismo formato que en INICIO"<<endl;
        cout<<"Introduzca el mes: "; 
        cin>>mesFin;
        cout<<"Introduzca el dia: "; 
        cin>>diaFin;
        finalBusq= stoi(mesFin+diaFin);
        
        busqueda(inicioBusq,finalBusq,log);
        cout<<"¿Desea continuar la busqueda? Ingrese 1. Ingrese cualquier otro número de ser lo contrario: "; 
        cin>>respuesta;

    }

    return 0;

}