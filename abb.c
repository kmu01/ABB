#include "abb.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct nodo_abb{
    struct nodo_abb* izq;
    struct nodo_abb* der;
    char* clave;
    void* dato;
} nodo_abb_t;

struct abb{
    nodo_abb_t* raiz;
    size_t cant;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
};

struct abb_iter{
    abb_t* arbol;
    nodo_abb_t* act;
    nodo_abb_t* ant;
};

/*    AUXILIARES    */
nodo_abb_t* nodo_abb_crear(char* clave, void* dato){
    nodo_abb_t* n = malloc(sizeof(nodo_abb_t));
    if(!n) return NULL;
    n->clave = strdup(clave);
    if(!n->clave){
        free(n);
        return NULL;
    }
    n->dato = dato;
    n->izq = NULL;
    n->der = NULL;
    return n;
}

/*   PRIMITIVAS   */

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* a = malloc(sizeof(abb_t));
    if(!a) return NULL;
    a->raiz = NULL;
    a->cmp = cmp;
    a->destruir_dato = destruir_dato;
    return a;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    nodo_abb_t* n = nodo_abb_crear(clave,dato);
    if(!n) return false;
    if(!arbol->cant){
        arbol->raiz = n;
        arbol->cant++;
        return true;
    }
    return guardar_recursivo()

}

void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

bool abb_pertenece(const abb_t *arbol, const char *clave);

size_t abb_cantidad(abb_t *arbol){
    return arbol->cant;
}

void abb_destruir(abb_t *arbol);

/*   ITERADOR INTERNO     */

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/*   PRIMITIVAS ITERADOR EXTERNO    */

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

bool abb_iter_in_avanzar(abb_iter_t *iter);

const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return !iter->act 
}

void abb_iter_in_destruir(abb_iter_t* iter){
    free(iter);
}