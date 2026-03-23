#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "timer.h"
#include "quicksort.h"
#include "heapsort.h"
#include "avl.h"

std::vector<std::string> loadWords(const std::string& filepath) {
    std::ifstream file(filepath);
    std::vector<std::string> words;
    std::string word;
    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir " << filepath << std::endl;
        return words;
    }
    while (std::getline(file, word)) {
        if (!word.empty()) words.push_back(word);
    }
    return words;
}

void printMemoryAnalysis(int n) {
    size_t avgWordSize = 32 + 8;
    size_t vectorMem   = n * avgWordSize;
    size_t avlNodeSize = sizeof(std::string) + 2*sizeof(AVLNode*) + sizeof(int);
    size_t avlMem      = n * avlNodeSize;

    std::cout << "\n== Memoria estimada ==" << std::endl;
    std::cout << "QuickSort (vector): " << vectorMem / 1024.0 / 1024.0 << " MB" << std::endl;
    std::cout << "HeapSort  (vector): " << vectorMem / 1024.0 / 1024.0 << " MB" << std::endl;
    std::cout << "AVL Tree  (nodos):  " << avlMem    / 1024.0 / 1024.0 << " MB" << std::endl;
}

void runAll(const std::string& scenarioName, std::vector<std::string> words) {
    std::cout << "\n\n==========================================" << std::endl;
    std::cout << "ESCENARIO: " << scenarioName << std::endl;
    std::cout << "==========================================" << std::endl;

    // QuickSort
    std::vector<std::string> qs = words;
    auto t1 = startTimer();
    quickSort(qs, 0, qs.size() - 1);
    double timeQS = stopTimer(t1);

    // HeapSort
    std::vector<std::string> hs = words;
    auto t2 = startTimer();
    heapSort(hs);
    double timeHS = stopTimer(t2);

    // AVL Tree
    AVLNode* root = nullptr;
    auto t3 = startTimer();
    for (const auto& w : words)
        root = insert(root, w);
    std::vector<std::string> avlResult;
    avlResult.reserve(words.size());
    inorder(root, avlResult);
    double timeAVL = stopTimer(t3);
    deleteTree(root);

    // Tabla de resultados
    std::cout << "\nAlgoritmo        | Tiempo        | Complejidad" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "QuickSort        | " << timeQS  << " ms\t | O(n log n) avg" << std::endl;
    std::cout << "HeapSort         | " << timeHS  << " ms\t | O(n log n)    " << std::endl;
    std::cout << "AVL Tree         | " << timeAVL << " ms\t | O(n log n)    " << std::endl;

    bool equal = (qs == hs && hs == avlResult);
    std::cout << "\nVerificacion: "
              << (equal ? "OK - los 3 producen el mismo orden" : "ERROR") << std::endl;
}

void printReport() {
    std::cout << "\n\n==========================================" << std::endl;
    std::cout << "              REPORTE FINAL               " << std::endl;
    std::cout << "==========================================" << std::endl;

    std::cout << "\n-- Enfoque de implementacion --" << std::endl;
    std::cout << "QuickSort: particion Lomuto con pivot en el ultimo elemento." << std::endl;
    std::cout << "HeapSort:  construccion de Max-Heap in-place + extraccion ordenada." << std::endl;
    std::cout << "AVL Tree:  insercion con rebalanceo por rotaciones + recorrido inorder." << std::endl;

    std::cout << "\n-- Comparacion de algoritmos --" << std::endl;
    std::cout << "Todos son O(n log n) pero QuickSort es mas rapido en datos aleatorios" << std::endl;
    std::cout << "por su mejor localidad de cache. HeapSort y AVL garantizan O(n log n)" << std::endl;
    std::cout << "en todos los casos. QuickSort degenera a O(n^2) con datos ordenados." << std::endl;

    std::cout << "\n-- Conclusion --" << std::endl;
    std::cout << "Para datos aleatorios:  QuickSort es la mejor opcion (mas rapido)." << std::endl;
    std::cout << "Para datos ordenados:   AVL Tree es superior (no tiene peor caso)." << std::endl;
    std::cout << "Para uso dinamico:      AVL Tree permite busqueda e insercion O(log n)." << std::endl;
    std::cout << "Para garantia absoluta: HeapSort garantiza O(n log n) en todo caso." << std::endl;
}

int main() {
    std::vector<std::string> words = loadWords("data/dataset.txt");
    if (words.empty()) return 1;
    std::cout << "Palabras cargadas: " << words.size() << std::endl;

    // Escenario 1: datos aleatorios
    runAll("Datos aleatorios", words);

    // Escenario 2: datos ya ordenados (usando nuestro QuickSort, no std::sort)
    std::vector<std::string> sorted = words;
    quickSort(sorted, 0, sorted.size() - 1);
    runAll("Datos ya ordenados", sorted);

    // Escenario 3: datos en orden inverso (std::reverse no es ordenamiento)
    std::vector<std::string> reversed = sorted;
    std::reverse(reversed.begin(), reversed.end());
    runAll("Datos en orden inverso", reversed);

    // Memoria
    printMemoryAnalysis(words.size());

    // Reporte final
    printReport();

    return 0;
}