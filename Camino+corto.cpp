/* Objetivo: Comparar algoritmos para recorrer un grafo ponderado y encontar el camino mas corto.     
Autores: Jose Angel Armadillo, Jorge Andres Diaz, Mario Alberto Gonzalez.
Ingenieria en Computacion Inteligente (ICI)
Estructuras Computacionales Avanzadas
Semestre 3.
Fecha: 18 octubre 2025.
*/
#include <iostream>

const int MAX_NODOS = 50;
const int INFINITO = INT_MAX;

// Funcion para obtener el indice numurico de cada nodo
int index(char nodo, const char conj[], int nodos) {
    for (int i = 0; i < nodos; i++) {
        if (conj[i] == nodo) {
            return i;
        }
    }
    return -1; // No se encontro el nodo
}

// Funcion para encontrar el nodo con la distancia minima
int min_distancia(const int dist[], const bool visitado[], int nodos) {
    int min = INFINITO, min_index;
    for (int v = 0; v < nodos; v++) {
        if (!visitado[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Implementacion del algoritmo de Dijkstra
void dijkstra(const int matriz[MAX_NODOS][MAX_NODOS], int origen_idx, int nodos, const char conj[]) {
    int dist[MAX_NODOS];
    bool visitado[MAX_NODOS];
    
    for (int i = 0; i < nodos; i++) {
        dist[i] = INFINITO;
        visitado[i] = false;
    }
    
    dist[origen_idx] = 0;

    for (int i = 0; i < nodos - 1; i++) {
        int u = min_distancia(dist, visitado, nodos);
        visitado[u] = true;

        for (int v = 0; v < nodos; v++) {
            if (!visitado[v] && matriz[u][v] != INFINITO && dist[u] != INFINITO && dist[u] + matriz[u][v] < dist[v]) {
                dist[v] = dist[u] + matriz[u][v];
            }
        }
    }

    cout << "Distancias mas cortas desde el nodo " << conj[origen_idx] << ":" << endl;
    for (int i = 0; i < nodos; i++) {
        cout << " -> " << conj[i] << ": ";
        if (dist[i] == INFINITO) {
            cout << "No hay camino" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }
}

int main() {
    int nodos, aristas;

    cout << "Ingrese la cantidad de nodos del grafo: ";
    cin >> nodos;
    if (nodos > MAX_NODOS) {
        cout << "Error: La cantidad de nodos excede el maximo permitido (" << MAX_NODOS << ")." << endl;
        return 1;
    }

    int matriz[MAX_NODOS][MAX_NODOS];
    char conj[MAX_NODOS];

    // Inicializar la matriz con INFINITO
    for(int i = 0; i < nodos; i++) {
        for(int j = 0; j < nodos; j++) {
            matriz[i][j] = INFINITO;
            if (i == j) matriz[i][j] = 0; // Distancia de un nodo a si mismo es 0
        }
    }
    
    cout << "Ingrese la identificacion de cada nodo (ej. A B C): ";
	for (int i = 0; i < nodos; i++) {
        cin >> conj[i];
    }

    cout << "Ingrese la cantidad de aristas: ";
    cin >> aristas;
    
    cout << "El nodo sera dirigido (SI (S) o NO (N))" << endl;
    char tipo;
    cin >> tipo;
    
    cout << "Ingrese los pares de nodos que forman cada arista y su peso (origen destino peso):" << endl;
    for (int i = 0; i < aristas; i++) {
        char origen_char, destino_char;
        int peso;
        cin >> origen_char >> destino_char >> peso;

        int origen_idx = index(origen_char, conj, nodos);
        int destino_idx = index(destino_char, conj, nodos);
        
        if (tipo == 'S' || tipo == 's') {
        	if (origen_idx != -1 && destino_idx != -1) {
            matriz[origen_idx][destino_idx] = peso;
		} else {
            cout << "Error: Nodos invalidos ingresados. Intente de nuevo." << endl;
            i--; // Para que el bucle repita la iteraci�n
        }
	}
	
	    if (tipo == 'N' || tipo == 'n') {
        if (origen_idx != -1 && destino_idx != -1) {
            matriz[origen_idx][destino_idx] = peso;
            matriz[destino_idx][origen_idx] = peso; // arista en ambas direcciones (no dirigido)
        } else {
            cout << "Error: Nodos invalidos ingresados. Intente de nuevo." << endl;
            i--;
        }
    }
    }

    char inicio_char;
    cout << "Ingrese el nodo de inicio para el algoritmo de Dijkstra: ";
    cin >> inicio_char;
    int inicio_idx = index(inicio_char, conj, nodos);

    if (inicio_idx != -1) {
        dijkstra(matriz, inicio_idx, nodos, conj);
    } else {
        cout << "Nodo de inicio invalido." << endl;
    }

    return 0;
}
