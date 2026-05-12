#include <vector>
#include <string> 
#include <iostream>
//codigo modificado de lab 7


struct Libro{ // almacena la informacion del xml sobre los libros
    std::string id;
    std::string titulo;
    std::string isbn;
    int anio_publicacion;
    std::string idioma;
    std::string descripcion;
    float rating_promedio;
    int num_paginas;
};


class Tree {
private:
    struct Node {
        Libro data;
        Node* parent;
        std::vector<Node*> children;

        Node(Libro value, Node* p = nullptr);
    };

    Node* rootNode;
    int treeSize;
    //int k; lo quito porque ahora el arbol no tiene numero fijo de hijos

    void preOrder(Node* node, std::vector<std::string>& result);
    void postOrder(Node* node, std::vector<std::string>& result);
    void deleteSubtree(Node* node); //si se borra un nodo, se borran todos sus hijos y luego ese nodo.

public:
    //Tree(int k); ya no es k hijos
    Tree();

    bool isEmpty();
    int size();

    std::string root();
    std::string parent(std::string id);
    std::vector<std::string> children(std::string id);
    bool insert(std::string parentId, Libro value);
    bool remove(std::string id);
    Node* search(Node* node, std::string id);

    std::vector<std::string> preOrder();
    std::vector<std::string> postOrder();
    std::vector<std::string> inOrder();

    //funciones que pide el enunciado
    void listar();
    void borrar_ratings(float r);
    std::vector<std::string> precursores(std::string id);
};