# Entregable_2_estructuras_de_datos
El arbol esta cargado, utilizando el parser pugi con todos los archivos xml en orden.
Se utilizo como base el adt de arbol binario de la ayudantia, pero claramente lo tuvimos que modificar, porque estamos usando un arbol general
Se utilizo la estructura de la imagen que cargamos, la que dice idea victor.
Se implemento como extra el metodo print, el cual imprime los primeros n libros del arbol con la estructura indicada en la imagen idea de Victor, en el main se usa miArbol.print(n); 
El metodo listar, recorre el arbol en preorder revisando los tags id de los nodos , solo se añaden a un vector los libros que cuelgan del nodo raiz total, luego se imprime por pantalla en el formato pedido, se utiliza en el main como miArbol.listar();
El metodo borrar_ratings, al igual que listar, recorre hijos del padre total, viendo en el tag de average_rating, el cual transformamos de string a float, si es menor al rating dado, se elimina en cascada con el metodo remove del adt, el cual elimina en cascada y libera la memoria, en el main se utiliza miArbol.borrar_ratings(f), donde f es un decimal entre 0 y 5.
El metodo precursores, recorre el arbol y compara los publication_year del libro, con los libros similares, los que se reportan se añaden a un vector y luego se imprimen por pantalla, y en el caso de no poder acceder a un año, por el hecho de que este en blanco o mal formato, se usa try y catch, donde si no encuentra el año de publicacion prueba con ellibro siguiente.

Javier Argomedo
Victor Galaz
