# Práctica I - Sorting Large Dataset (C++)

**ST0245 - Estructuras de Datos y Algoritmos**  
Universidad EAFIT - Escuela de Ciencias Aplicadas e Ingeniería  
Docente: Alexander Narvaez Berrio  
Marzo 2026

---

## Descripción

Programa en C++ que ordena un dataset de 100.000 palabras en inglés usando tres estrategias algorítmicas distintas, cada una basada en una estructura de datos diferente:

- **QuickSort** sobre un arreglo dinámico (`std::vector<string>`)
- **HeapSort** usando un Binary Heap in-place
- **AVL Tree** con inserción y recorrido inorder

Se evalúan tres escenarios: datos aleatorios, datos ya ordenados y datos en orden inverso.

---

## Estructura del proyecto
```
Practica1-Sorting/
├── src/
│   ├── main.cpp        ← programa principal y reporte
│   ├── quicksort.h     ← implementación QuickSort
│   ├── heapsort.h      ← implementación HeapSort
│   ├── avl.h           ← implementación AVL Tree
│   └── timer.h         ← medición de tiempo con std::chrono
├── CMakeLists.txt
└── Practica1_Informe.docx
```

---

## Requisitos

- Compilador g++ con soporte C++17
- Dataset `data/dataset.txt` provisto por el docente (100.000 palabras)

---

## Compilación y ejecución
```bash
g++ -std=c++17 -O2 -o sorting.exe src/main.cpp
./sorting.exe
```

---

## Resultados obtenidos

| Algoritmo | Datos aleatorios | Datos ordenados | Datos inversos |
|-----------|-----------------|-----------------|----------------|
| QuickSort | ~66 ms          | ~85,319 ms ⚠️   | ~40,283 ms ⚠️  |
| HeapSort  | ~88 ms          | ~75 ms          | ~72 ms         |
| AVL Tree  | ~68 ms          | ~40 ms          | ~36 ms         |

⚠️ QuickSort activa su peor caso O(n²) con datos ordenados.

---

## Conclusiones

- **QuickSort** es el más rápido en datos aleatorios por su localidad de caché, pero degrada a O(n²) con datos ordenados.
- **HeapSort** garantiza O(n log n) en todos los casos con memoria mínima.
- **AVL Tree** es la única estructura que permite búsqueda e inserción O(log n) posterior al ordenamiento.
