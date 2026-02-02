#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

#define chunk 100
#define mostrar 10

void imprimeArreglo(float* d, int n);

int main()
{
    std::cout << "=============================================\n";
    std::cout << " Suma de Arreglos en Paralelo con OpenMP\n";
    std::cout << "=============================================\n";

    int opcion, N;
    float* a;
    float* b;
    float* c;

    std::cout << "\nSeleccione como desea llenar los arreglos:\n";
    std::cout << "1. Ingresar valores manualmente\n";
    std::cout << "2. Generar valores aleatorios\n";
    std::cout << "Opcion: ";
    std::cin >> opcion;

    if (opcion == 1)
    {
        std::cout << "\nIngrese el tamano de los arreglos: ";
        std::cin >> N;

        a = new float[N];
        b = new float[N];
        c = new float[N];

        std::cout << "\nIngrese los valores del arreglo A separados por espacios:\n";
        for (int i = 0; i < N; i++)
            std::cin >> a[i];

        std::cout << "\nIngrese los valores del arreglo B separados por espacios:\n";
        for (int i = 0; i < N; i++)
            std::cin >> b[i];
    }
    else
    {
        N = 1000;  // tamaño por defecto

        a = new float[N];
        b = new float[N];
        c = new float[N];

        srand((unsigned)time(NULL));
        for (int i = 0; i < N; i++)
        {
            a[i] = rand() % 100;
            b[i] = rand() % 100;
        }
    }

    // FOR paralelo
#pragma omp parallel for shared(a, b, c) schedule(static, chunk)
    for (int i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    // Resultados
    std::cout << "\nPrimeros valores del arreglo A:\n";
    imprimeArreglo(a, N);

    std::cout << "\nPrimeros valores del arreglo B:\n";
    imprimeArreglo(b, N);

    std::cout << "\nPrimeros valores del arreglo C (A + B):\n";
    imprimeArreglo(c, N);

    // para liberar memoria
    delete[] a;
    delete[] b;
    delete[] c;

    std::cout << "\nProceso finalizado correctamente.\n";
    return 0;
}

void imprimeArreglo(float* d, int n)
{
    int limite = (n < mostrar) ? n : mostrar;
    for (int i = 0; i < limite; i++)
        std::cout << d[i] << "  ";
    std::cout << std::endl;
}
