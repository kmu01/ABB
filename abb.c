#include "abb.h"
#include "pila.h"
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
    pila_t* nodos;
};


/*    DECLARACIONES DE AUXILIARES    */

//Crea un nodo de ABB.
static nodo_abb_t* nodo_abb_crear(char* clave, void* dato);

//Destruye un nodo de ABB.
static void nodo_abb_destruir(nodo_abb_t* nodo);

//Destruye el arbol.
static void _abbd(abb_t* arbol, nodo_abb_t* act);

//Busca un nodo dentro del arbol utilizando su clave.
static nodo_abb_t* nodo_buscar(abb_t* arbol,nodo_abb_t* act,nodo_abb_t* ant,char* clave);

//Guarda elementos en el arbol.
static bool _ag(abb_t* arbol,nodo_abb_t* act,nodo_abb_t* nuevo);

//Wrapper del iterador intero.
static void _abbinorder(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra,nodo_abb_t* act,bool iterar);

//Apila el nodo pasado por parámetro junto con su rama izquierda.
static void iter_apilar_elementos(pila_t* pila,nodo_abb_t* nodo);

//Reorganiza el arbol al borrar un elemento con un hijo.
static void* borrar_un_hijo(nodo_abb_t* padre,nodo_abb_t* abuelo);

//Reorganiza el arbol al borrar un elemento con 2 hijos.
static void* borrar_dos_hijos(abb_t* arbol,nodo_abb_t* padre,nodo_abb_t* abuelo);

//Busca un reemplazo para el nodo a borrar.
static nodo_abb_t* buscar_reemplazo(abb_t* arbol,nodo_abb_t* nodo);

//Reorganiza los hijos del nodo de reemplazo.
static void acomodar_hijos(nodo_abb_t* reemp,nodo_abb_t* padre);

/*   PRIMITIVAS   */

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* a = malloc(sizeof(abb_t));
    if(!a) return NULL;
    a->raiz = NULL;
    a->cant = 0;
    a->cmp = cmp;
    a->destruir_dato = destruir_dato;
    return a;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    if(!arbol->cant){
        nodo_abb_t* n = nodo_abb_crear(clave,dato);
        arbol->raiz = n;
        arbol->cant++;
        return true;
    }
    nodo_abb_t* n = nodo_buscar(arbol,arbol->raiz,NULL,NULL,clave);
    if(n){
        if(arbol->destruir_dato){
            arbol->destruir_dato(n->dato);
        }
        n->dato = dato;
        return true;
    }
    n = nodo_abb_crear(clave,dato);
    if(!n) return false;
    return _ag(arbol,arbol->raiz,n);
}

void *abb_borrar(abb_t *arbol, const char *clave){
    nodo_abb_t* ant = NULL;
    nodo_abb_t* n = nodo_buscar(arbol,arbol->raiz,ant,clave);
    if(!n) return NULL;
    if(!n->der && !n->izq){ //Caso sin hijos.
        void* dato = n->dato;
        if(ant && arbol->cmp(clave,ant->clave) < 0){
            ant->izq = NULL;
        }
        else if(ant && arbol->cmp(clave,ant->clave) > 0){
            ant->der = NULL;
        }
        else if(n == arbol->raiz){
            arbol->raiz == NULL;
        }
        nodo_abb_destruir(n);
        arbol->cant--;
        return dato;
    }
    if((!n->izq && n->der) || (n->izq && !n->der)){ //Caso un hijo.
        return borrar_un_hijo(n,ant);
    }
    return borrar_dos_hijos(arbol,n);
}

void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_abb_t* n = nodo_buscar(arbol,arbol->raiz,NULL,clave);
    if(!n) return NULL;
    return n->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    return nodo_buscar(arbol,arbol->raiz,NULL,clave) == NULL;
}

size_t abb_cantidad(abb_t *arbol){
    return arbol->cant;
}

void abb_destruir(abb_t *arbol){
    return _abbd(arbol,arbol->raiz);
    free(arbol);
}

/*   ITERADOR INTERNO     */

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){    
    bool iterar = true;
    return _abbinorder(arbol,visitar,extra,arbol->raiz,iterar);
}

/*   PRIMITIVAS ITERADOR EXTERNO    */

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(!iter) return NULL;
    iter->nodos = pila_crear();
    if(!iter->nodos) return NULL;

    /*Se apilan los elementos de la izquierda así, al avanzar por el arbol con
        con el iterador, se podra hacer un recorrido in-order. */
    iter_apilar_elementos(iter->nodos,arbol->raiz);
    iter->arbol = arbol;
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return false;
    //Desapilo el tope y apilo su elemento derecho.
    iter_apilar_elementos(iter->nodos,(nodo_abb_t*)pila_desapilar(iter->nodos)->der);
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    if(pila_esta_vacia(iter->nodos)) return NULL;
    return (nodo_abb_t*)pila_ver_tope(iter->nodos)->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_ver_tope(iter->nodos) == NULL;
}

void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->nodos);
    free(iter);
}

/*    AUXILIARES    */

static nodo_abb_t* nodo_abb_crear(char* clave, void* dato){
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

static void nodo_abb_destruir(nodo_abb_t* nodo){
free(nodo->clave);
free(nodo);
}

static void _abbd(abb_t* arbol, nodo_abb_t* act){
    if(act->izq){
        return _abbd(arbol,act->izq);
    }
    if(act->der){
        return _abbd(arbol,act->der);
    }
    if(arbol->destruir_dato){
        arbol->destruir_dato(act->dato);
    }
    nodo_abb_destruir(act);
    return;
}

static nodo_abb_t* nodo_buscar(abb_t* arbol,nodo_abb_t* act,nodo_abb_t* ant,char* clave){
    if(!act) return NULL; //Caso base, no se encuentra el nodo.
    size_t comparacion = arbol->cmp(clave,act->clave);
    if(comparacion == 0) return act; //Si la comparación da 0, encontré el nodo.
    if(comparacion < 0){
        ant = act;
        act = act->izq;
        return nodo_buscar(arbol,act,ant,clave);
    }
    ant = act;
    act = act->der;
    return nodo_buscar(arbol,act,ant,clave);   
}
static bool _ag(abb_t* arbol,nodo_abb_t* act,nodo_abb_t* nuevo){
    size_t comp = arbol->cmp(n->clave,act->clave);
    if(comp < 0){
        if(!act->izq){
            act->izq = nuevo;
            arbol->cant++;
            return true;
        }
        return _ag(arbol,act->izq,nuevo)
    }
    if(!act->der){
        act->der = nuevo;
        arbol->cant++;
        return true;
    }
    return _ag(arbol,act->der,nuevo);
}


/*
 La iteración in-order lee elementos a la izquierda, luego el padre o "centro" 
 y finalmente la derecha.  
*/
static void _abbinorder(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra,nodo_abb_t* act,bool iterar){
    if(!act || !iterar) return;

    /* Llamo a _abbinorder con el hijo izquierdo del actual 
        antes de llamar a visitar para cumplir con el recorrido in-order.
    */

    _abbinorder(abb_t* arbol,visitar,extra,act->izq,iterar);
    if(!act || !visitar(act->clave,act->dato,extra)){
        iterar = false;
    }
    _abbinorder(abb_t* arbol,visitar,extra,act->der,iterar);
}

static void iter_apilar_elementos(pila_t* pila,nodo_abb_t* nodo){
    if(!nodo || !pila_apilar(pila,nodo))return;
    return iter_apilar_elementos(pila,nodo->izq);
}

static void* borrar_un_hijo(nodo_abb_t* padre,nodo_abb_t* abuelo){
    nodo_abb_t* hijo;
    if(!padre->izq){
        hijo = padre->der;
    }else{
        hijo = padre->izq;
    }
    if(abuelo->izq == padre){
        abuelo->izq = hijo;
    }else{
        abuelo->der = hijo;
    }
    void* dato = padre->dato;
    nodo_abb_destruir(padre);
    return dato;
}

static void* borrar_dos_hijos(abb_t* arbol,nodo_abb_t* padre){
    nodo_abb_t* reemp = buscar_reemplazo(arbol,padre);
    void* dato = padre->dato;
    free(padre->clave);
    padre->clave = reemp->clave;
    padre->dato = reemp->dato;
    if(reemp->der){
        acomodar_hijos(reemp,padre);
    }
    nodo_abb_destruir(reemp);
    return dato;
}

static nodo_abb_t* buscar_reemplazo(abb_t* arbol,nodo_abb_t* nodo){
    nodo_abb_t* reemp = nodo->der;
    while(reemp->izq){
        reemp = reemp->izq;
    }
    return reemp;
}

static void acomodar_hijos(nodo_abb_t* reemp,nodo_abb_t* padre){
    nodo_abb_t* hijo = reemp->der;
    while(hijo->der){
        hijo = hijo->der;
    }
    hijo->der = padre->der;
    padre->der = hijo;
}