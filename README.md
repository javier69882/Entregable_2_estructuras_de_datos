# Entregable 2 — Estructuras de Datos

Repositorio con un árbol general que carga archivos XML usando `pugixml`.

## Descripción

El proyecto parsea los archivos XML ubicados en `books_xml/` y construye un árbol general donde:
- La raíz `total` contiene nodos `L` (libros).
- Cada `L` tiene atributos como `Id`, `Nom`, `F` (año), `average_rating`, etc.
- Cada `L` contiene un hijo `S` que agrupa nodos `Ls` con libros similares (cada `Ls` tiene su propio `Id`, `F`, ...).

El objetivo es practicar recorridos y operaciones sobre estructuras de datos (inserción, búsqueda, borrado en cascada, filtrado).

## Archivos principales

- `main.cpp` — carga los XML, construye el árbol y llama métodos de verificación.
- `tree.hpp` / `tree.cpp` — implementación del ADT árbol general y métodos requeridos.
- `pugixml.cpp` / `pugixml.hpp` — parser XML integrado.
- `books_xml/` — carpeta con los archivos XML de entrada.
- `estructura arbol.png/` — diagrama inicial para el modelamiento del árbol. Se acaba optando por la opción de la derecha.

## Funcionalidad implementada

- `Tree::print(int n)`: imprime los primeros `n` libros con estructura anidada.
- `Tree::listar()`: imprime en consola los `Id` de los libros que cuelgan directamente de la raíz, en formato `[id1, id2, ...]`.
- `Tree::borrar_ratings(float r)`: elimina (en cascada) los libros cuyo `average_rating` ≤ `r`.
- `Tree::precursores()`: imprime los `Id` de los libros cuya condición sobre libros similares se cumple (todos los similares son posteriores en año).

## Uso

Compilar con C++17 (ejemplo):

```powershell
g++ -std=c++17 main.cpp tree.cpp pugixml.cpp -o tarea
```

## Notas y rendimiento

- La carga de los XML se limita a los primeros 10,000 archivos por diseño del `main` para acotar tiempo y memoria.
- En pruebas locales la carga completa tomó varios segundos y creó cientos de miles de nodos (depende del dataset).
- Se usan conversiones `std::stoi` / `std::stof` con `try/catch` para tolerar campos vacíos o malformados en el XML.

## Autores

- Javier Argomedo
- Victor Galaz