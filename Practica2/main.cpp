/*
 * File:   main.cpp
 * Author: Alvaro & Pablo Dubikin
 *
 * PRACTICA 2 · DEVOLUCIÓN DEL CAMBIO DE MONEDAS
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

void calculoNumeroMonedas(int cantidad, vector<int> monedas, vector<vector<int> > &tablaNum, vector<vector<bool> > &tablaBool);
vector<int> calculoMonedas(int cantidad, vector<int> monedas, vector<vector<int> > &tablaNum, vector<vector<bool> > &tablaBool);
void imprimirListaProgramacionDinamica(vector<int> monedas, int cantidad, vector<vector<int> > tablaNum, vector<vector<bool> > tablaBool);
void programacion_dinamica(vector<int> monedas, int dinero);

void elige_sistema_monetario(vector<int> &monedas);
void sistema_monetario_euro(vector<int> &monedas);
void sistema_monetario_personalizado(vector<int> &monedas);
void muestra_monedas(vector<int> &monedas);
void devuelve_cambio(vector<int> &monedas, int &dinero_insertado);
void ingresa_dinero(int &dinero_insertado);
void voraz(vector<int> &monedas, int &dinero_insertado);
void despedida();
void progr();

int main(int argc, char** argv) {
    
    progr();
    return 0;
}

void progr(){
    vector<int> monedas;
    int dinero_insertado;
    
    elige_sistema_monetario(monedas);
    ingresa_dinero(dinero_insertado);
    devuelve_cambio(monedas, dinero_insertado);
    despedida();
}


// Método que introduce al usuario la elección del sistema monetario a ser utilizado para devolver el cambio
void elige_sistema_monetario(vector<int> &monedas){
    
    int op;
    
    cout << "Seleccione el sistema monetario para realizar la devolución:" << endl;
    cout << "1 · Sistema monetario del EURO" << endl;
    cout << "2 · Sistema monetario personalizado" << endl;
    
    cin >> op;
    
    switch(op){
        case 1:
            sistema_monetario_euro(monedas);
            muestra_monedas(monedas);
            break;
            
        case 2:
            sistema_monetario_personalizado(monedas);
            muestra_monedas(monedas);
            break;
            
        default:
            break;
    }
    while(op != 1 && op != 2){
        cout << "Dicha opción no se encuentra en el menu";
        cin >> op;
    }
    
}

// Método que genera el sistema monetario del EURO
void sistema_monetario_euro(vector<int> &monedas){
    
    monedas.push_back(200);
    monedas.push_back(100);
    monedas.push_back(50);
    monedas.push_back(20);
    monedas.push_back(10);
    monedas.push_back(5);
    monedas.push_back(2);
    monedas.push_back(1);
    
}

// Método para generar un sistema monetario personalizado por el usuario
void sistema_monetario_personalizado(vector<int> &monedas){
    
    int auxiliar;
    float moneda;
    
    cout << "Introduzca sus valores para el nuevo sistema monetario personalizado." << endl;
    cout << "Para finalizar el sistema monetario, introduzca el valor 0." << endl;
    
    while (moneda != 0 && moneda > 0)
    {
        cout << "Nuevo valor de moneda: ";
        cin >> moneda;
        if(moneda > 0)
        {
            auxiliar = moneda * 100;
            monedas.push_back(auxiliar);
        }
    }
    
}

// Recorre el vector de las monedas para mostrarlo por pantalla
void muestra_monedas(vector<int> &monedas){
    
    cout << "| ";
    
    for(int i=0; i<monedas.size(); i++){
        cout << monedas[i]/100. ;
        cout << " | ";
    }
    
    cout << "\n" << endl;
    
}

// Solicita el dinero al usuario
void ingresa_dinero(int &dinero_insertado){
    
    float din;
    cout << "Introduce tu cantidad de dinero a cambiar: \n";
    cin >> din;
    dinero_insertado = din*100;
    
}

// Método que incluye los distintos medios para devolver el cambio
void devuelve_cambio(vector<int> &monedas, int &dinero_insertado){
    
    char devolucion;
    
    cout << "Seleccione el medio mediante el cual quiere recibir su cambio \n" << endl;
    cout << "V -> Devolución mediante el Algoritmo Voraz" << endl;
    cout << "D -> Devolución mediante el Algoritmo de Programación Dinámica" << endl;
    cin >> devolucion;
    cout << "\n";
    
    switch(devolucion){
        case 'V':
        case 'v':
            voraz(monedas,dinero_insertado);
            break;
            
        case 'D':
        case 'd':
            // Invierto el array porque para la programación dinámica lo necesitamos al revés.
            if(monedas.size()> 1 &&
                    monedas[0]>monedas[1])std::reverse(monedas.begin(), monedas.end());
            programacion_dinamica(monedas, dinero_insertado);
            break;
        default:
            cout << "Dicha opción no se encuentra en el menu";
            break;
            
    }
}

void programacion_dinamica(vector<int> monedas, int dinero){
    
    vector<vector<int> > tablaNum(monedas.size(),vector<int>(dinero+1));
    vector<vector<bool> > tablaBool(monedas.size(),vector<bool>(dinero+1));
    
    calculoNumeroMonedas(dinero, monedas, tablaNum, tablaBool);
    
    vector<int> sol = calculoMonedas(dinero, monedas, tablaNum, tablaBool);
    
    cout << "Solución por programación dinámica: " << endl;
    for(int i=0; i<sol.size(); i++){
        cout << "monedas de " << monedas[i]/100. << " = " << sol[i] << endl;
    }
    
    char imprimirLista;
    cout << "\n ¿Quiere imprimir las tablas de la devolución del cambio? \n" << endl;
    cout << "S" << endl;
    cout << "N" << endl;
    cin >> imprimirLista;
    cout << "\n";
    
    switch(imprimirLista){
        case 'S':
        case 's':
            imprimirListaProgramacionDinamica(monedas, dinero, tablaNum, tablaBool);
            break;
            
        case 'N':
        case 'n':
            cout << "Vale!" << endl;
            break;
        default:
            cout << "Dicha opción no se encuentra en el menu";
            break;
            
    }
}

// Calcula la devolución del cambio mediante el Algoritmo Voraz
void voraz(vector<int> &monedas, int &dinero_insertado){
    
    int cuenta_cambio=0; // Almacena el número de monedas que irán al cambio
    vector<int> cambio; // Vector para almacenar cada tipo de moneda del cambio
    int i=0;
    
    // Antes de nada se ordena el sistema monetario de mayor a menor
    sort(monedas.begin(), monedas.end(), greater<int>());
    
    cout << "· Operaciones realizadas durante el cambio: \n" << endl;
    
    // Comprueba si hay monedas aun en el vector y si el dinero insertado es mayor que 0
    while (i < monedas.size() && dinero_insertado > 0.00){
        
        int tipo_moneda = 0; // Almacena la cuenta del número de monedas utilizadas de cada tipo
        
        // Comprueba si la moneda es mayor o igual que el dinero insertado
        while(monedas[i] <= dinero_insertado){
            
            // Resta la vuelta al dinero insertado y muestra la operación por pantalla
            cout << dinero_insertado /100. << "€ - " << monedas[i] /100. << "€ = ";
            dinero_insertado = dinero_insertado - monedas[i];
            cout << dinero_insertado /100. << "€ " << endl;
            
            cuenta_cambio++; // Incrementa la cantidad de monedas del cambio
            tipo_moneda++; // Incrementa la cantidad de monedas de este tipo
        }
        i++;
        cambio.push_back(tipo_moneda); // Añade al vector del cambio la moneda del tipo en concreto
        
    }
    
    cout << "\n· Monedas totales añadidas al cambio: " << cuenta_cambio << endl;
    cout << "· Tipos de cada moneda añadidas al cambio: \n" << endl;
    
    // Termina el algoritmo comprobando qué monedas se han utilizado de cada tipo a través del vector del cambio
    for(i=0; i<cambio.size(); i++){
        if(cambio[i]!=0){
            cout << cambio[i] << " monedas de " << monedas[i]/100. << "€" << endl;
        }
    }
    
}

void despedida(){
    
    char despedida;
    vector<int> monedas;
    int dinero_insertado;
    
    cout << "\n ¿Quiere reiniciar la máquina de la devolución del cambio? \n" << endl;
    cout << "S" << endl;
    cout << "N" << endl;
    cin >> despedida;
    cout << "\n";
    
    switch(despedida){
        case 'S':
        case 's':
            progr();
            break;
            
        case 'N':
        case 'n':
            cout << "Hasta otra!!!!" << endl;
            break;
        default:
            cout << "Dicha opción no se encuentra en el menu";
            break;
            
    }
    
}

// Calcula qué monedas se van a devolver finalmente a partir de los datos provistos
vector<int> calculoMonedas(int cantidad, vector<int> monedas, vector<vector<int> > &tablaNum, vector<vector<bool> > &tablaBool){
    
    // Vector para guardar el numero de monedas de cada tipo del vector de monedas
    vector<int> solucion(monedas.size());
    int i, j;
    
    i = monedas.size() -1 ;
    j = cantidad;
    
    while(i!=0 && j!=0){
        
        if(tablaBool[i][j] == false){
            i = i-1;
        } else {
            solucion[i] = solucion[i] +1 ;
            j -= monedas[i];
        }
    }
    
    return solucion;
}

// Calcula las monedas necesarias para ir devolviendo los datos, y rellena la tabla con estos
void calculoNumeroMonedas(int cantidad, vector<int> monedas, vector<vector<int> > &tablaNum, vector<vector<bool> > &tablaBool){
    
    int i, j;
    
    int n = monedas.size();
    
    for(i=0; i<n; i++){
        for(j=0; j<= cantidad;j++){
            
            if(i==0 && j<monedas[i]){
                tablaNum[i][j] = 0;
                tablaBool[i][j] = false;
            } else {
                if(i==0){
                    tablaNum[i][j] = 1 + tablaNum[i][j-monedas[0]];
                    tablaBool[i][j] = true;
                } else {
                    if(j<monedas[i]){
                        tablaNum[i][j] = tablaNum[i-1][j]; // Copiamos la celda superior
                        tablaBool[i][j] = false;
                    } else {
                        
                        // Elegimos la opción con menor num de monedas
                        tablaNum[i][j] = tablaNum[i-1][j] < 1 + tablaNum[i][j-monedas[i]] ? tablaNum[i-1][j] : 1 + tablaNum[i][j-monedas[i]];
                        tablaBool[i][j] = tablaNum[i][j] != tablaNum[i-1][j] ? true : false ;
                    }
                }
            }
        }
    }
}

// Imprime la tabla de numeros de moneda para cada resultado y de booleanos correspondiente
void imprimirListaProgramacionDinamica(vector<int> monedas, int cantidad, vector<vector<int> > tablaNum, vector<vector<bool> > tablaBool){
    
    int i, j;
    
    cout << endl << endl << endl;
    
    for(i=0; i<monedas.size(); i++){
        cout << "valor[" << monedas[i] << "] - " ;
        for(j=0; j<cantidad+1;j++){
            cout << tablaNum[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << endl;cout << endl;
    
    for(i=0; i<monedas.size(); i++){
        cout << "valor[" << monedas[i] << "] - " ;
        for(j=0; j<cantidad+1;j++){
            cout << tablaBool[i][j] << " ";
        }
        cout << endl;
    }
}