#include <iostream>
// Ejecución: g++ "P51.cpp" -o p5.exe

using namespace std;
int c[20][20];// Distancia de la ciudad
int d[20][100];// Resultado de la tabla TSP
int col;// El nÃºmero de columnas en la tabla TSP
int sub[100];//Subconjunto

// Encuentra un subconjunto, mira arriba para una explicación detallada
int subGather(int n,int num)
{
    int i,length;
    length=0;
    for(i=1;i<num;i++)
    {
        if(n&1==1)
            sub[length++]=i;
        n=n>>1;
    }
    sub[length]=-1;
    return length;
}
// Verifica si el elemento existe en el subconjunto
int subContain(int n)
{
    int i=0;
    while(sub[i]!=-1)
    {
        if(sub[i]==n) return 1;
        i++;
    }
    return 0;
}
// Crear matriz de espaciado de ciudades
void setDistance(int num)
{
    int i,j;
    cout<<"Coloca la distancia:\n";
    for(i=0;i<num;i++)
    {
        for(j=0;j<num;j++)
        {
            if(i==j)
                c[i][j]=-1;
            else
            {
                cout<<"Coloca la distancia entre la ciudad \t"<<i<<" y la ciudad \t"<<j<<":";
                cin>>c[i][j];
            }
        }
    }
    cout << "Listo!" << endl;
}
// Ver arriba para una explicación detallada
int deSub(int k,int j)
{
    int temp=1;
    temp=temp<<(k-1);
    return j-temp;
}
//TSP
int doTSP(int num)
{
    int i,j;
    // Calcula el número de columnas de la matriz d [] []
    for(i=0,col=1;i<num-1;i++,col*=2);
    // Inicializa la primera columna de la matriz d [] []
    for(i=1;i<num;i++)
        d[i][0]=c[i][0];
    // Complete el contenido de las columnas 2 a col-1
    int length;
    int aaa=1;
    while(aaa<num-1)// Complete el formulario en orden creciente de elementos en el subconjunto
    {
        for(j=1;j<col;j++)
        {
            length=subGather(j,num);
            if(length==aaa)
            {
                for(i=1;i<num;i++)
                {
                    if(subContain(i)==0)// El elemento no existe en el subconjunto
                    {
                        int md=10000;//MÃ­nimo
                        int temp;
                        int k;
                        for(k=0;k<length;k++)
                        {
                            temp=c[i][sub[k]]+d[sub[k]][deSub(sub[k],j)];
                            if(temp<md)
                                md=temp;
                        }
                        d[i][j]=md;
                    }
                }
            }
        }
        aaa++;
    }
    // Completa la última columna
    int md=10000;//MÃ­nimo
    int temp;
    int k;
    length=subGather(col-1,num);
    for(k=0;k<length;k++)
    {
        temp=c[0][sub[k]]+d[sub[k]][deSub(sub[k],col-1)];
        if(temp<md)
            md=temp;
    }
    d[0][col-1]=md;
    return d[0][col-1];
}
// Resultado de salida
void showResult(int num)
{
    int i,j;
    for(i=0;i<num;i++)
    {
        for(j=0;j<col;j++)
            cout<<d[i][j]<<"\t";
        cout<<endl;
    }
}
int main()
{
    int num;// Número de ciudades
    int p_length;// La longitud de la ruta más corta
    cout<<"Coloca el numero de ciudades:";
    cin>>num;
    setDistance(num);
    p_length=doTSP(num);
    cout<<"La longitud del camino mas corto es "<<p_length<<endl;
    cout<<"TSP tabla:\n";
    showResult(num);
    return 0;
}
