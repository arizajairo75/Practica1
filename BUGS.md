# Bugs conocidos y limitaciones

## Bug 1 — QuickSort: desbordamiento de pila con datos ordenados
**Descripción:** Con 100.000 palabras ya ordenadas, QuickSort hace
100.000 llamadas recursivas anidadas en vez de ~17. Esto puede causar
stack overflow en sistemas con límite de pila pequeño.

**Causa:** La partición Lomuto con pivot en el último elemento siempre
produce una partición de tamaño n-1 y otra de tamaño 0 con datos ordenados.

**Estado:** Conocido. Se documenta como demostración del peor caso O(n²).

**Solución posible:** Usar pivot aleatorio o mediana de tres elementos.

---

## Bug 2 — Palabras duplicadas ignoradas en AVL
**Descripción:** Si el dataset contiene palabras repetidas, el AVL
las ignora silenciosamente — no las inserta ni lanza error.

**Causa:** La función insert tiene esta condición:
```cpp
else return node; // duplicado, ignorar
```

**Estado:** Comportamiento intencional para este dataset.
**Impacto:** Ninguno — el dataset no tiene duplicados.

---

## Limitación 1 — Ruta del dataset hardcodeada
**Descripción:** El programa asume que el dataset está en `data/dataset.txt`
relativo al directorio de ejecución. Si se corre desde otra ubicación falla.

**Solución posible:** Recibir la ruta como argumento de línea de comandos.

---

## Limitación 2 — Memoria del AVL no recuperable parcialmente
**Descripción:** Si el programa se interrumpe antes de llamar `deleteTree()`,
toda la memoria de los nodos AVL queda sin liberar.

**Solución posible:** Usar smart pointers (`std::unique_ptr`).
