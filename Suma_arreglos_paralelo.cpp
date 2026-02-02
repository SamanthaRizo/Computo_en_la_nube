#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

#define chunk 100
#define mostrar 10

void imprimeArreglo(float* d, int n, bool completo);

int main()
{
    std::cout << "=============================================\n";
    std::cout << " Suma de Arreglos en Paralelo con OpenMP\n";
    std::cout << "=============================================\n";

    int N, opcion, verTodo;

    // Solicitar tamaño
    std::cout << "\nIngrese el tamano de los arreglos: ";
    std::cin >> N;

    // Reservar memoria
    float* a = new float[N];
    float* b = new float[N];
    float* c = new float[N];

    // Seleccionar método de llenado
    std::cout << "\nSeleccione como desea llenar los arreglos:\n";
    std::cout << "1. Ingresar valores manualmente\n";
    std::cout << "2. Generar valores aleatorios\n";
    std::cout << "Opcion: ";
    std::cin >> opcion;

    if (opcion == 1)
    {
        std::cout << "\nIngrese los valores del arreglo A separados por espacios:\n";
        for (int i = 0; i < N; i++)
            std::cin >> a[i];

        std::cout << "\nIngrese los valores del arreglo B separados por espacios:\n";
        for (int i = 0; i < N; i++)
            std::cin >> b[i];
    }
    else
    {
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

    // Mostrar primeros valores
    std::cout << "\nPrimeros valores del arreglo A:\n";
    imprimeArreglo(a, N, false);

    std::cout << "\nPrimeros valores del arreglo B:\n";
    imprimeArreglo(b, N, false);

    std::cout << "\nPrimeros valores del arreglo C (A + B):\n";
    imprimeArreglo(c, N, false);

    // Preguntar si desea ver arreglos completos
    std::cout << "\n¿Desea ver los arreglos completos?\n";
    std::cout << "1. Si\n";
    std::cout << "2. No\n";
    std::cout << "Opcion: ";
    std::cin >> verTodo;

    if (verTodo == 1)
    {
        std::cout << "\nArreglo A completo:\n";
        imprimeArreglo(a, N, true);

        std::cout << "\nArreglo B completo:\n";
        imprimeArreglo(b, N, true);

        std::cout << "\nArreglo C completo (A + B):\n";
        imprimeArreglo(c, N, true);
    }

    // Liberar memoria
    delete[] a;
    delete[] b;
    delete[] c;

    std::cout << "\nProceso finalizado correctamente.\n";
    return 0;
}

// Función para imprimir arreglos
void imprimeArreglo(float* d, int n, bool completo)
{
    int limite = completo ? n : (n < mostrar ? n : mostrar);

    for (int i = 0; i < limite; i++)
        std::cout << d[i] << "  ";

    std::cout << std::endl;
}
