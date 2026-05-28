#ifndef TREE_HPP
#define TREE_HPP
#include <vector>
#include <string> 
#include <iostream>
//codigo modificado de lab 7
/*
struct Libro_similar{
    std::string titulo;
    std::string isbn;
    int anio_publicacion;
};
struct Libro{ // almacena la informacion del xml sobre los libros
    std::string id;
    std::string titulo;
    std::string isbn;
    int anio_publicacion;
    std::string idioma;
    std::string descripcion;
    float rating_promedio;
    int num_paginas;

    //vector de libros similares
    std::vector<Libro_similar> libros_similares;
};
*/

class Tree {
public:
    struct Node {
        std::string etiqueta; //libro, id, nombre, etc
        std::string valor;    //valor para el tag, titulo, numero, etc
        Node* parent;
        
        //vector para almacenr los hijos de forma dinamica
        // porque podrian ser 10000, 7, 2 , 0 etc
        std::vector<Node*> children; 

        Node(std::string tag, std::string val, Node* p = nullptr);
    };
private:
void print(Node* node, int depth);
    Node* rootNode;
    int treeSize;
    //int k; lo quito porque ahora el arbol no tiene numero fijo de hijos

    void preOrder(Node* node, std::vector<Node*>& result);
    void postOrder(Node* node, std::vector<Node*>& result);
    void deleteSubtree(Node* node); //si se borra un nodo, se borran todos sus hijos y luego ese nodo.

public:
    //EL arbol inica con un nodo raiz
     void print(int limiteLibros = 3);
    Tree(std::string rootTag, std::string rootVal = "");
    ~Tree();
    bool isEmpty();
    int size();
    Node* getRoot();
    // insert recibe nodo padra, etiqueta y valor, y devuelve el nodo insertado
    Node* insert(Node* parentNode, std::string etiqueta, std::string valor = "");
    bool remove(Node* node);
    Node* search(Node* node, std::string etiqueta_buscada, std::string valor_buscado = "");
    std::vector<Node*> preOrder();
    std::vector<Node*> postOrder();

    //funciones que pide el enunciado
    void listar();
    void borrar_ratings(float r);
    void listar_similares_posteriores();
    void precursores();
};
#endif