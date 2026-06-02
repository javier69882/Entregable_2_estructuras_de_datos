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

/*
Lista por consola los id de todos los libros en el arbol
La funcion recorre el arbol en preorder para obtener todos los nodos,
filtra los nodos para encontrar los que cuelgan directamente de la raiz total y tienen etiqueta "L" (libro),
luego busca el nodo hijo con etiqueta id y extrae su valor.
Imprime los ids en formato [id1, id2, id3]


*/
void Tree::listar() { // lista los id de los libros que cuelgan directamente de la raiz total, en formato [id1, id2, id3]
    if (!rootNode) return;
    std::vector<Node*> nodos = preOrder(); // se recorre el arbol en preorder para obtener todos los nodos en un vector
    std::vector<std::string> ids;

    for (Node* nodo : nodos) { // se itera por todos los nodos del arbol
        if (nodo == rootNode) continue;

        // solo interesan los libros que cuelgan directamente de la raiz.
        if (nodo->parent == rootNode && nodo->etiqueta == "L") {
            for (Node* hijo : nodo->children) {
                if (hijo->etiqueta == "Id" && !hijo->valor.empty()) {
                    ids.push_back(hijo->valor);
                    break;
                }
            }
        }
    }

    // imprimir en el formato mencionado
    std::cout << "[";
    for (size_t i = 0; i < ids.size(); ++i) {
        std::cout << ids[i];
        if (i + 1 < ids.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}


/*
Elimina del arbol todos los libros cuyo rating promedio es menor o igual a r
La funcion recorre los hijos de la raiz total para encontar los nodos de libros, luego busca
en sus hijo el nodo con etiqueta average_rating, convierte su valor a float.
Si el rating es menor o igual a r, se añade el nodo del libro a un vector de nodos a borrar
Luego se itera por el vector de nodos a borrar y se llama a remove para eliminar cada nodo del arbol, lo que borra el nodo y todo su subarbol de atributos

*/
void Tree::borrar_ratings(float r) {
    if(!rootNode) return;
    //vector para amacenar los nodos a borrar
    std::vector<Node*> libros_a_borrar;
    // recorre hijos de la raiz padre total
    for(Node* libro : rootNode->children){
        // busca el nodo average_rating dentro de los hijos del nodo L
        for(Node* atributo : libro->children){
            if (atributo->etiqueta == "average_rating"){

                //convierte el string a float
                float rating = std::stof(atributo->valor);
                // si el rating es menor se añade al vector
                if(rating <= r){
                    libros_a_borrar.push_back(libro);
                }
                break;
            }
        }
    }
    //borra los nodso en el vector
    for (Node* libro : libros_a_borrar){
        remove(libro);
    }
    }
/*  
Identifica y lista los id de los libros que son mas antiguos que sus libros similares
Analiza cada libro que cuelga directo de la raiz total y extrae su año de publicacion nodo F
Luego revisa los similares de ese libro en nodo S  Y LS, compara los años de publicacion
Imprime todos los libros que cumplen la condicion

*/
void Tree::precursores() { // lista los id de los libros cuyos libros similares son todos posteriores a ellos
    std::vector<std::string> ids;
    if (!rootNode) {
        std::cout << "[]" << std::endl;
        return;
    }

    for (Node* libro : rootNode->children) { // iteramos por los hijos de la raiz total
        if (libro->etiqueta != "L") continue;

        int año_original = -1; // si no se encuentra el año de publicacion, se considera invalido y se ignora ese libro
        Node* similares = nullptr;

        for (Node* atributo : libro->children) { // iteramos por los atributos del libro para encontrar el año de publicacion y el nodo de libros similares
            if (atributo->etiqueta == "F") {
                try {
                    año_original = std::stoi(atributo->valor);
                } catch (...) {
                    año_original = -1;
                }
            } else if (atributo->etiqueta == "S") {
                similares = atributo;
            }
        }

        if (año_original == -1) continue; // si no se encontró un año de publicación válido, se ignora este libro
        bool todos_posteriores = true; // asumimos que todos los similares son posteriores hasta que se demuestre lo contrario

        if (similares) { // si el libro tiene similares, verificamos sus años de publicación
            for (Node* libro_similar : similares->children) {
                if (libro_similar->etiqueta != "Ls") continue;

                for (Node* atributo_similar : libro_similar->children) { // iteramos por los atributos del libro similar para encontrar su año de publicación
                    if (atributo_similar->etiqueta == "F") {
                        try { // intentamos convertir el año de publicación del libro similar a entero
                            int año_similar = std::stoi(atributo_similar->valor);
                            if (año_similar <= año_original) {
                                todos_posteriores = false;
                            }
                        } catch (...) { // si no se pudo convertir el año de publicación del libro similar a entero, se considera inválido y se ignora ese libro similar
                            todos_posteriores = false;
                        }
                        break;
                    }
                }

                if (!todos_posteriores) break;
            }
        }

        if (todos_posteriores) { // si todos los libros similares son posteriores, se añade el id del libro original a la lista de ids a imprimir
            for (Node* atributo : libro->children) {
                if (atributo->etiqueta == "Id" && !atributo->valor.empty()) {
                    ids.push_back(atributo->valor);
                    break;
                }
            }
        }
    }

    std::cout << "["; // finalmente, se imprime la lista de ids con los libros cuyos similares son posteriores
    for (size_t i = 0; i < ids.size(); ++i) {
        std::cout << ids[i];
        if (i + 1 < ids.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}



// Función privada recursiva
void Tree::print(Node* node, int depth) {
    if (!node) return;

    
    for (int i = 0; i < depth; ++i) {
        std::cout << "    "; 
    }

    // Imprimimos la etiqueta del nodo
    std::cout << "|-- " << node->etiqueta;

    // Si el nodo tiene un valor de texto, lo mostramos al lado
    if (!node->valor.empty()) {
        std::cout << ": " << node->valor;
    }
    std::cout << std::endl;

    // Llamada recursiva para todos los hijos directos
    for (auto child : node->children) {
        print(child, depth + 1);
    }
}

// Función publica contenedora
void Tree::print(int limiteLibros) {
    if (!rootNode) {
        std::cout << "El árbol está vacío." << std::endl;
        return;
    }

    // Imprimimos la raíz total
    std::cout << "|-- " << rootNode->etiqueta << std::endl;

    int librosImpresos = 0;
    // Recorremos los hijos de la raíz 
    for (auto libro : rootNode->children) {
        if (librosImpresos >= limiteLibros) {
            std::cout << "    |-- ... (y " << (rootNode->children.size() - limiteLibros) 
                      << " libros mas)" << std::endl;
            break;
        }
        
        // Llamamos al asistente recursivo para que imprima este libro con todos sus atributos
        print(libro, 1);
        librosImpresos++;
    }
}