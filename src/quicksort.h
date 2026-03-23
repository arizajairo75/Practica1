#pragma once
#include <vector>
#include <string>

// Partición Lomuto: elige el último elemento como pivot
// Mueve todo lo menor al pivot a la izquierda, todo lo mayor a la derecha
// Retorna la posición final del pivot
int partition(std::vector<std::string>& arr, int low, int high) {
    std::string pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Función recursiva principal
void quickSort(std::vector<std::string>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);   // ordenar izquierda
        quickSort(arr, pivotIndex + 1, high);  // ordenar derecha
    }
}