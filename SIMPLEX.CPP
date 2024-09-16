#include <iostream>
using namespace std;
#include <math.h>
#include <vector>
#include <algorithm>

void validarEntero(int *x){
    double v, intpart;
    cin>>v;
    while(cin.fail()||modf(v, &intpart)!=0){
        cin.clear();
        cin.ignore(123, '\n');
        cout<<"Ha ingresado un entero incorrecto, vuelva a ingresar un numero: ";
        cin>>v;
    }
    *x=(int)v;
}

void validarDecimal(double *x){
    cin>>*x;
    while(cin.fail()){
        cin.clear();
        cin.ignore(123, '\n');
        cout<<"Ha ingresado un numero incorrecto, vuelva a ingresar un entero: ";
        cin>>*x;
    }
}

vector<vector<double>> simplexMin(vector<vector<double>> matriz, int numRestric){
    bool enProceso = true;
    //indicecol e indicefil hacen referencia al indice de la columna y fila pivote, dando asi el elemento pivote
    int indiceCol, indiceFil, indiceDiv;
    double max, temp, min, elemPivot, divisor, dividendo, t1, t2;
    vector<double> divisiones, columnap, filap, solucion, respuestas;
    while(enProceso){
        //se encuentra el mayor valor de la fila z
        max = *max_element(matriz.at(0).begin(), matriz.at(0).end());
        auto it = find(matriz.at(0).begin(), matriz.at(0).end(), max);
        //se encuentra el indice del mayor valor de la fila z 
        indiceCol = it - matriz.at(0).begin();
        //se recolectan los valores de la division entre la columna r y la columna pivote
        divisiones.clear(); //por si no es la primera iteracion.
        for (int i = 1; i < numRestric+1; i++)
        {
            indiceDiv = matriz[i].size()-1;
            divisor = matriz[i][indiceCol];
            dividendo = matriz[i][indiceDiv];
            temp = (dividendo)/(divisor);
            divisiones.push_back(temp);
        }
        //se encuentra el menor valor dentro de las divisiones
        min = *min_element(divisiones.begin(), divisiones.end());
        auto it1 = find(divisiones.begin(), divisiones.end(), min);
        //se obtiene el indice de fila de la menor division
        indiceFil = (it1 - divisiones.begin())+1;
        //se asigna el valor del elemento pivote
        elemPivot = matriz[indiceFil][indiceCol];
        //se divide toda la columna entre el valor del elemento pivote
        for (int i = 0; i < matriz[indiceFil].size(); i++)
        {
            matriz[indiceFil][i] /= elemPivot;
        }
        //se obtiene el vector que contiene la columna pivote:
        columnap.clear();
        for (int i = 0; i < numRestric+1; i++)
        {
            columnap.push_back(matriz[i][indiceCol]);
        }
        
        //se obtiene el vector que contiene la fila pivote:
        filap.clear();
        filap = matriz[indiceFil];
        //se hace la operacion del renglon actual - valor de la columna pivote * renglon pivote

        for (int i = 0; i < matriz.size(); i++)
        {
            for (int j = 0; j < matriz[i].size(); j++)
            {
                if(i!=indiceFil){
                    t1 = columnap[i];
                    t2 = filap[j];
                    matriz[i][j] -= (t1*t2) ;
                }
            }   
        }
        //log 
        for (int i = 0; i < numRestric+1; i++)
        {
            solucion.push_back(0);
        }
        solucion.at(indiceFil)=(double)indiceCol+1;
        //verificacion
        bool offender = false;
        for (int i = 0; i < matriz[0].size(); i++)
        {
            if(matriz[0][i]>0){
                offender = true;
                break;
            }
        }
        
        if(offender){
            enProceso=true;
        }
        else{
            enProceso=false;
        }
        for (int i = 0; i < matriz.size(); i++) 
        {
            for (int j = 0; j < matriz[i].size(); j++)
            {
                cout << matriz[i][j] << " ";
            }    
            cout << endl;
        }
        cout<<"--------------------------------------------------"<<endl;
    }
    int contadorR=0;
    for (int i = 0; i < solucion.size(); i++)
    {
        if(solucion[i]!=0){
            contadorR++;
        }
    }
    for (int i = 0; i < contadorR+1; i++)
    {
        respuestas.push_back(0);
    }
    for (int i = 0; i < solucion.size(); i++)
    {
        if(solucion[i]!=0){
            respuestas[solucion[i]-1]=matriz[i][matriz[i].size()-1];
        }
    }
    
    cout<<"Z: "<<matriz[0][matriz[0].size()-1]<<endl;
    for (int i = 0; i < respuestas.size(); i++)
    {
        if(respuestas[i]!=0){
            cout<<"X"<<i+1<<": "<<respuestas[i]<<endl;
        }
        
    }
    
    return matriz;
};

vector<vector<double>> simplexMax(vector<vector<double>> matriz, int numRestric){
    bool enProceso = true;
    //indicecol e indicefil hacen referencia al indice de la columna y fila pivote, dando asi el elemento pivote
    int indiceCol, indiceFil, indiceDiv;
    double minz, temp, min, elemPivot, divisor, dividendo, t1, t2;
    vector<double> divisiones, columnap, filap, solucion, respuestas;
    while(enProceso){
        //se encuentra el mayor valor de la fila z
        minz = *min_element(matriz.at(0).begin(), matriz.at(0).end());
        auto it = find(matriz.at(0).begin(), matriz.at(0).end(), minz);
        //se encuentra el indice del mayor valor de la fila z 
        indiceCol = it - matriz.at(0).begin();
        //se recolectan los valores de la division entre la columna r y la columna pivote
        divisiones.clear(); //por si no es la primera iteracion.
        for (int i = 1; i < numRestric+1; i++)
        {
            indiceDiv = matriz[i].size()-1;
            divisor = matriz[i][indiceCol];
            dividendo = matriz[i][indiceDiv];
            temp = (dividendo)/(divisor);
            divisiones.push_back(temp);
        }
        //se encuentra el menor valor dentro de las divisiones
        min = *min_element(divisiones.begin(), divisiones.end());
        auto it1 = find(divisiones.begin(), divisiones.end(), min);
        //se obtiene el indice de fila de la menor division
        indiceFil = (it1 - divisiones.begin())+1;
        //se asigna el valor del elemento pivote
        elemPivot = matriz[indiceFil][indiceCol];
        //se divide toda la columna entre el valor del elemento pivote
        for (int i = 0; i < matriz[indiceFil].size(); i++)
        {
            matriz[indiceFil][i] /= elemPivot;
        }
        //se obtiene el vector que contiene la columna pivote:
        columnap.clear();
        for (int i = 0; i < numRestric+1; i++)
        {
            columnap.push_back(matriz[i][indiceCol]);
        }
        
        //se obtiene el vector que contiene la fila pivote:
        filap.clear();
        filap = matriz[indiceFil];
        //se hace la operacion del renglon actual - valor de la columna pivote * renglon pivote

        for (int i = 0; i < matriz.size(); i++)
        {
            for (int j = 0; j < matriz[i].size(); j++)
            {
                if(i!=indiceFil){
                    t1 = columnap[i];
                    t2 = filap[j];
                    matriz[i][j] -= (t1*t2) ;
                }
            }   
        }
        //log 
        for (int i = 0; i < numRestric+1; i++)
        {
            solucion.push_back(0);
        }
        solucion.at(indiceFil)=(double)indiceCol+1;
        //verificacion
        bool offender = false;
        for (int i = 0; i < matriz[0].size(); i++)
        {
            if(matriz[0][i]<0){
                offender = true;
                break;
            }
        }
        
        if(offender){
            enProceso=true;
        }
        else{
            enProceso=false;
        }
        for (int i = 0; i < matriz.size(); i++) 
        {
            for (int j = 0; j < matriz[i].size(); j++)
            {
                cout << matriz[i][j] << " ";
            }    
            cout << endl;
        }
        cout<<"--------------------------------------------------"<<endl;
    }
    int contadorR=0;
    for (int i = 0; i < solucion.size(); i++)
    {
        if(solucion[i]!=0){
            contadorR++;
        }
    }
    for (int i = 0; i < contadorR+1; i++)
    {
        respuestas.push_back(0);
    }
    for (int i = 0; i < solucion.size(); i++)
    {
        if(solucion[i]!=0){
            respuestas[solucion[i]-1]=matriz[i][matriz[i].size()-1];
        }
    }
    
    cout<<"Z: "<<matriz[0][matriz[0].size()-1]<<endl;
    for (int i = 0; i < respuestas.size(); i++)
    {
        if(respuestas[i]!=0){
            cout<<"X"<<i+1<<": "<<respuestas[i]<<endl;
        }
        
    }
    
    return matriz;
};

int main(int argc, char const *argv[])
{
    system("cls");
    cout<<"Ingrese 1 para min, 2 para max: ";
    int m;
    validarEntero(&m);
    while(m>2||m<1){
        cout<<"Ha ingresado un valor incorrecto, por favor vuelva a ingresar 1 para min o 2 para max:"<<endl;
        validarEntero(&m);
    }
    system("cls");
    cout<<endl<<"Ingrese el numero de variables en la funcion objetivo: ";
    int numVariables;
    validarEntero(&numVariables);
    while(numVariables<0){
        cout<<"Ha ingresado un valor incorrecto, por favor vuelva a ingresar el numero de variables:"<<endl;
        validarEntero(&numVariables);
    }
    system("cls");
    vector<double> coeficientesObjetivo;
    double temp;
    for (int i = 0; i < numVariables; i++)
    {
        cout<<endl<<"Ingrese el coeficiente de x"<<i+1<<": ";
        validarDecimal(&temp);
        temp=temp*-1;
        coeficientesObjetivo.push_back(temp);
    }
    system("cls");
    
    vector<vector<double>> matriz;
    matriz.push_back(coeficientesObjetivo);

    cout<<endl<<"Ingrese el numero de restricciones del problema: ";
    int numRestric;
    validarEntero(&numRestric);
    while(numRestric<0){
        cout<<"Ha ingresado un valor incorrecto, por favor vuelva a ingresar el numero de restricciones:"<<endl;
        validarEntero(&numRestric);
    }
    for (int i = 0; i < numRestric+1; i++)
    {
        matriz.at(0).push_back(0);
    }
    int posicion;
    double r;
    vector<double> temporal;
    for (int i = 0; i < numRestric; i++)
    {
        temporal.clear();
        for (int a = 0; a < numVariables+1; a++)
        {
            if(a!=numVariables){
                cout<<endl<<"Ingrese el coeficiente de x"<<a+1<<" en la restriccion "<<i+1<<": ";
                validarDecimal(&temp);
                temporal.push_back(temp);
            }
            else{
                cout<<endl<<"Ingrese el valor de R en la restriccion "<<i+1<<": ";
                validarDecimal(&r);
            }
        }
        for (int b = 1; b <= numRestric; b++)
        {
            temporal.push_back(0);
        }
        posicion = i+numVariables;
        temporal.at(posicion)=1;
        temporal.push_back(r);
        matriz.push_back(temporal);
    }
    
    switch(m){
        case 1:
            matriz = simplexMin(matriz, numRestric);
        break;
        case 2:
            matriz = simplexMax(matriz, numRestric);
        break;
        default:
            cout<<"Ha ingresado un valor incorrecto."<<endl;
        break;
    }
    system("pause");
    return 0;
}
