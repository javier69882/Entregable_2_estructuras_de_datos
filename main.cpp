#include <iostream>
#include <filesystem>
#include <string>
#include "tree.hpp"
#include "pugixml.hpp"
#include <chrono>

namespace fs = std::filesystem;

void cargarDatosEnArbol(Tree& miArbol, const std::string& rutaCarpeta) {
    //raiz padre total dl arbol
    Tree::Node* nodoRaiz = miArbol.getRoot(); 
    int contador = 0;
    //se itera por los primeros 10000 archivos del xml
    for (const auto& entry : fs::directory_iterator(rutaCarpeta)) {
        if (contador >= 10000) break; // 
        if (fs::is_regular_file(entry.status())) {
            
            pugi::xml_document doc;
            pugi::xml_parse_result result = doc.load_file(entry.path().c_str());

            if (result) {
                pugi::xml_node xmlBook = doc.child("GoodreadsResponse").child("book");
                
                if (xmlBook) {
                    // Creamos el nodo "L" de libro que
                    Tree::Node* bookNode = miArbol.insert(nodoRaiz, "L");

                    // ponemos los atributos del libro bajo el nodo "L"
                    miArbol.insert(bookNode, "Id", xmlBook.child_value("id"));
                    miArbol.insert(bookNode, "Nom", xmlBook.child_value("title"));
                    miArbol.insert(bookNode, "isbn", xmlBook.child_value("isbn"));
                    miArbol.insert(bookNode, "F", xmlBook.child_value("publication_year"));
                    miArbol.insert(bookNode, "language_code", xmlBook.child_value("language_code"));
                    miArbol.insert(bookNode, "description", xmlBook.child_value("description"));
                    miArbol.insert(bookNode, "average_rating", xmlBook.child_value("average_rating"));
                    miArbol.insert(bookNode, "num_pages", xmlBook.child_value("num_pages"));

                    // ponemos el nodo "S" de similares debajo del nodo "L"
                    pugi::xml_node xmlSimilarBooks = xmlBook.child("similar_books");
                    Tree::Node* similaresNode = miArbol.insert(bookNode, "S");

                    //Iteramos por cada libro similar en el XML
                    for (pugi::xml_node simBook = xmlSimilarBooks.child("book"); simBook; simBook = simBook.next_sibling("book")) {
                        
                        // ponemos el nodo "Ls" de libro similar debajo del nodo "S"
                        Tree::Node* simBookNode = miArbol.insert(similaresNode, "Ls");

                        //ponemos los atributos del libro similar denajo del nodo "Ls"
                        miArbol.insert(simBookNode, "Nom", simBook.child_value("title"));
                        miArbol.insert(simBookNode, "Id", simBook.child_value("id"));
                        miArbol.insert(simBookNode, "isbn", simBook.child_value("isbn"));
                        miArbol.insert(simBookNode, "F", simBook.child_value("publication_year"));
                    }
                }
            } else {
                std::cerr << "Error al leer el archivo: " << entry.path().filename() << "\n";
            }
        }
        contador++;
    }
}

int main() {
    // iniciamos el arbol con un nodo raiz "total"
    Tree miArbol("total");
    // ruta del directorio con los archivos xml
    std::string ruta = "./books_xml"; 
    
    std::cout << "Iniciando la carga de los archivos XML en el arbol..." << std::endl;
  //medimos el tiempo de carga de los datos en el arbol, en mi pc dio 26.8263 segundos para los 10000 archivos xml
  // ademas en mi pc se crearon   676969
    auto tiempoInicio = std::chrono::high_resolution_clock::now();
    cargarDatosEnArbol(miArbol, ruta);

    auto tiempoFin = std::chrono::high_resolution_clock::now();

  
    std::chrono::duration<double> duracionSegundos = tiempoFin - tiempoInicio;

    std::cout << "Tiempo total de carga: " << duracionSegundos.count() << " segundos." << std::endl;
    // listamos los id de los libros cargados en el arbol, para verificar que se cargaron correctamente
    std::cout << "Lista de IDs de los libros:" << std::endl;
    miArbol.listar();
    return 0;
}