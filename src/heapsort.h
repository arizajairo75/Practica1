#pragma once
#include <vector>
#include <string>

// Heapify: mantiene la propiedad de Max-Heap en el subárbol con raíz en i
// n = tamaño del heap, i = índice de la raíz del subárbol
void heapify(std::vector<std::string>& arr, int n, int i) {
    int largest = i;        // asumimos que la raíz es el mayor
    int left    = 2*i + 1;
    int right   = 2*i + 2;

    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest); // seguir bajando
    }
}

void heapSort(std::vector<std::string>& arr) {
    int n = arr.size();

    // Fase 1: construir el Max-Heap (de abajo hacia arriba)
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Fase 2: extraer el mayor uno por uno y ponerlo al final
    for (int i = n-1; i > 0; i--) {
        std::swap(arr[0], arr[i]); // el mayor va al final
        heapify(arr, i, 0);        // restaurar heap en el resto
    }
}