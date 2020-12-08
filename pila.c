#include "pila.h"
#include <stdlib.h>

#define TAM_DEFAULT 10
#define REDIMENSION 2

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

//FUNCIONES AUXILIARES

bool pila_redimensionar(pila_t *pila, size_t cap_nueva){

	void **datos_nuevo = realloc(pila->datos, cap_nueva * sizeof(void*));

    if (datos_nuevo == NULL) {
        return false;
    }

    pila->datos = datos_nuevo;
    pila->capacidad = cap_nueva;
    return true;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(void){

	pila_t *pila = malloc(sizeof(pila_t));

    if (pila == NULL){
        return NULL;
    }
    
    pila->datos = malloc(TAM_DEFAULT * sizeof(void*));
    pila->cantidad = 0;
    pila->capacidad = TAM_DEFAULT;
    
    if (!pila->datos){
    	free(pila);
    	return NULL;
    }
    return pila;

}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}


bool pila_esta_vacia(const pila_t *pila){
	if (!pila){
		return true;
	}
	return (pila->cantidad==0);
}

bool pila_apilar(pila_t *pila, void *valor){

	if (!pila){
		return false;
	}
	if (pila->cantidad == pila->capacidad){
		if (!pila_redimensionar(pila, pila->capacidad * REDIMENSION)){
			return false;
		}
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}

void *pila_ver_tope(const pila_t *pila){
	if (pila_esta_vacia(pila)){
		return NULL;
	}
	return(pila->datos[pila->cantidad-1]);
}

void *pila_desapilar(pila_t *pila){
	
	if (pila_esta_vacia(pila)){
		return NULL;
	}

	pila->cantidad -= 1;

	if ((pila->cantidad*4 <= pila->capacidad) && (pila->capacidad > TAM_DEFAULT)){
		if ((pila->capacidad / REDIMENSION) > TAM_DEFAULT){
			pila_redimensionar(pila, pila->capacidad / REDIMENSION);
		}
		else{
			pila_redimensionar(pila, TAM_DEFAULT);
		}
	}

	return pila->datos[pila->cantidad];
}


