#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;
// Tamaño del bloque utilizado en la multiplicación por bloques
const int BLOCK_SIZE = 32;
// Número de veces que se repite cada método para medir el tiempo
const int NUM_REPETITIONS = 5;

//Función para la multiplicación clásica de matrices
void MultiplyClassic(int n, const vector<vector<double>>& a, const vector<vector<double>>& b, vector<vector<double>>& c) {
     // Recorrer todas las filas de la matriz A
    for (int i = 0; i < n; ++i) {
        // Recorrer todas las columnas de la matriz B
        for (int j = 0; j < n; ++j) {
            // Inicializar la entrada (i, j) de la matriz resultado C
            c[i][j] = 0.0;
            // Realizar la multiplicación y suma para la entrada (i, j)
            for (int k = 0; k < n; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// Función para la multiplicación de matrices por bloques
void MultiplyByBlocks(int n, const vector<vector<double>>& a, const vector<vector<double>>& b, vector<vector<double>>& c) {
    // Dividir la matriz en bloques de tamaño BLOCK_SIZE x BLOCK_SIZE
    for (int i0 = 0; i0 < n; i0 += BLOCK_SIZE) {
        for (int j0 = 0; j0 < n; j0 += BLOCK_SIZE) {
            for (int k0 = 0; k0 < n; k0 += BLOCK_SIZE) {
                for (int i = i0; i < min(i0 + BLOCK_SIZE, n); ++i) {
                    for (int j = j0; j < min(j0 + BLOCK_SIZE, n); ++j) {
                        for (int k = k0; k < min(k0 + BLOCK_SIZE, n); ++k) {
                            c[i][j] += a[i][k] * b[k][j];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Ingrese la dimensión de las matrices (n): ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n, 1.0));
    vector<vector<double>> B(n, vector<double>(n, 2.0));
    vector<vector<double>> C(n, vector<double>(n, 0.0));

    cout << "Multiplicando matrices " << NUM_REPETITIONS << " veces..." << endl;

    // Medir multiplicación clásica
    double elapsedClassic = 0.0;
    for (int i = 0; i < NUM_REPETITIONS; ++i) {
        fill(C.begin(), C.end(), vector<double>(n, 0.0));
        auto start = high_resolution_clock::now();
        MultiplyClassic(n, A, B, C);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start).count() / 1e6;
        elapsedClassic += duration;
        cout << "Tiempo de la repetición " << i+1 << " (Matriz Clásica) = " << duration << " segundos" << endl;
    }

    // Medir multiplicación por bloques
    double elapsedBlocks = 0.0;
    for (int i = 0; i < NUM_REPETITIONS; ++i) {
        fill(C.begin(), C.end(), vector<double>(n, 0.0));
        auto start = high_resolution_clock::now();
        MultiplyByBlocks(n, A, B, C);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start).count() / 1e6;
        elapsedBlocks += duration;
        cout << "Tiempo de la repetición " << i+1 << " (Por Bloques) = " << duration << " segundos" << endl;
    }

    cout << "Tiempo total (Matriz Clásica) = " << elapsedClassic << " segundos" << endl;
    cout << "Tiempo total (Por Bloques) = " << elapsedBlocks << " segundos" << endl;

    return 0;
}
