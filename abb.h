#include <stdbool.h>

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

//Crea y devuelve un abb, o NULL si algo salió mal.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

//Guarda una clave junto con su dato en el abb.
//Pre: el abb existe.
//Pos: se devuelve true si se pudo guardar o false si no se pudo.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

//Borra la clave del abb y devuelve su dato.
//Pre: el arbol existe.
//Pos: se devolvió el dato o un NULL si la clave no se encuentra.
void *abb_borrar(abb_t *arbol, const char *clave);

//Obtiene en valor de la clave ingresada y lo devuelve.
//Pre: el abb existe.
//Pos: se devolvió el dato o NULL en caso de error.
void *abb_obtener(const abb_t *arbol, const char *clave);

//Devuelve un booleano indicando si la clave está o no en el arbol.
//Pre: el abb existe.
//Pos: devolvió true si la clave esstaba o false si no estaba.
bool abb_pertenece(const abb_t *arbol, const char *clave);

//Devuelve la cantidad de elementos que tiene el arbol.
size_t abb_cantidad(abb_t *arbol);

//Destruye el arbol y aplica la función destruir dato.
void abb_destruir(abb_t *arbol);

//Iterador interno del ABB.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

typedef struct abb_iter abb_iter_t;

//Crea un iterador para el abb
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

//Avanza en el arbol con el ieterador.
//Pre: el iterador existe.
//Pos: se devolvió true si se pudo avanzar o false si no se pudo.
bool abb_iter_in_avanzar(abb_iter_t *iter);

//Devuelve la clave del elemento en donde está parado el iterador.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

//Devuelve un booleano indicando si el iterador está o no al final del arbol.
bool abb_iter_in_al_final(const abb_iter_t *iter);

//Destruye el ieterador del abb.
void abb_iter_in_destruir(abb_iter_t* iter);