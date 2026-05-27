#include "tree.hpp"
#include <algorithm>
#include <functional>

// constructor del nodo
Tree::Node::Node(std::string tag, std::string val, Node* p) {
    etiqueta = tag;
    valor = val;
    parent = p;
}

//Constructor del arbol
Tree::Tree(std::string rootTag, std::string rootVal) {
    rootNode = new Node(rootTag, rootVal);
    treeSize = 1;
}

// Destructor
Tree::~Tree() {
    deleteSubtree(rootNode);
}

bool Tree::isEmpty() {
    return treeSize == 0;
}

int Tree::size() {
    return treeSize;
}

Tree::Node* Tree::getRoot() {
    return rootNode;
}

//busqueda por etiqueta y valor
Tree::Node* Tree::search(Node* node, std::string etiqueta_buscada, std::string valor_buscado) {
    if (!node) return nullptr;
    
    // Verificamos si coincide la etiqueta, y si se pasa un valor a buscar, tambien se verifica
    if (node->etiqueta == etiqueta_buscada && (valor_buscado == "" || node->valor == valor_buscado)) {
        return node;
    }

    //si no es el actual, busca recursivamente en los hijos
    for (auto child : node->children) {
        Node* found = search(child, etiqueta_buscada, valor_buscado);
        if (found) return found;
    }
    return nullptr;
}

// inserta nuevo nodo con etiqueta y valor debajo del nodo padre dado
Tree::Node* Tree::insert(Node* parentNode, std::string etiqueta, std::string valor) {
    if (!parentNode) return nullptr;

    Node* newNode = new Node(etiqueta, valor, parentNode);
    parentNode->children.push_back(newNode);
    treeSize++;
    return newNode;
}

   


void Tree::deleteSubtree(Node* node) {
    if (!node) return;
    for (auto child : node->children) {
        deleteSubtree(child);
    }
    delete node;
}

// Borrado directo por puntero
bool Tree::remove(Node* node) {
    if (!node) return false;

    //evito borrar la raiz padre total
    if (node == rootNode) {
        deleteSubtree(rootNode);
        rootNode = nullptr;
        treeSize = 0;
        return true;
    }

    Node* parent = node->parent;
    auto& siblings = parent->children;

    //se borra el puntero en el vecto del padre
    siblings.erase(
        std::remove(siblings.begin(), siblings.end(), node),
        siblings.end()
    );

    //se libera la memoria del subarbol
    deleteSubtree(node);
    treeSize--;
    return true;
}


//recorre en preodrder y guarda los nodos en un vector
void Tree::preOrder(Node* node, std::vector<Node*>& result) {
    if (!node) return;
    result.push_back(node);
    for (auto child : node->children) {
        preOrder(child, result);
    }
}

std::vector<Tree::Node*> Tree::preOrder() {
    std::vector<Node*> result;
    preOrder(rootNode, result);
    return result;
}

//recorre en postorder y guarda los nodos en un vector
void Tree::postOrder(Node* node, std::vector<Node*>& result) {
    if (!node) return;
    for (auto child : node->children) {
        postOrder(child, result);
    }
    result.push_back(node);
}

std::vector<Tree::Node*> Tree::postOrder() {
    std::vector<Node*> result;
    postOrder(rootNode, result);
    return result;
}
/*
std::vector<std::string> Tree::inOrder() {
    std::vector<std::string> result;

    std::function<void(Node*)> inorder = [&](Node* node) {
        if (!node) return;

        int half = node->children.size() / 2;

        for (int i = 0; i < half; i++)
            inorder(node->children[i]);

        result.push_back(node->data.id);

        for (size_t i = half; i < node->children.size(); i++)
            inorder(node->children[i]);
    };

    inorder(rootNode);
    return result;
}
    */

//funciones que pide el enunciado
void Tree::listar() {
 
}

void Tree::borrar_ratings(float r) {

    }

std::vector<std::string> Tree::precursores(std::string id) {
    std::vector<std::string> resultado;
    return resultado;
}