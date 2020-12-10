#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "testing.h"

// Funcion auxiliar para iterador interno que imprime el contenido del abb.
bool imprimir_datos(const char* clave, void* valor, void* extra){
    printf("Clave: %s | Valor: %s\n", clave, (char*)valor);
    return true;
}

static void prueba_abb_crear_vacio(){
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("Prueba ABB crear vacio", abb);
    print_test("Prueba ABB la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba ABB obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba ABB pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba ABB borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));
    abb_destruir(abb);
}

static void prueba_abb_iterar_vacio(){
    abb_t* abb = abb_crear(strcmp, free);

    abb_in_order(abb, imprimir_datos, NULL);
    print_test("Prueba ABB iter interno vacio", true);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba ABB iter crear iterador abb vacio", iter);
    print_test("Prueba ABB iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba ABB iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba ABB iter ver actual es NULL", !abb_iter_in_ver_actual(iter));
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_insertar(){
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba ABB insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba ABB la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba ABB obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba ABB pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba ABB borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba ABB la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    
    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba ABB insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba ABB la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba ABB obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba ABB pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba ABB insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba ABB la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba ABB obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba ABB pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}

static void prueba_abb_reemplazar(){
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba ABB insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba ABB obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba ABB insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba ABB obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba ABB la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba ABB insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba ABB obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba ABB insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba ABB obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba ABB la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir(){
    abb_t* abb = abb_crear(strcmp, free);
    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (liberando lo que reemplaza) */
    print_test("Prueba ABB insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba ABB obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba ABB insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba ABB obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba ABB la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba ABB insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba ABB obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba ABB insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba ABB obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba ABB la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}

static void prueba_abb_borrar(){
    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba ABB insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba ABB insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba ABB insertar clave3", abb_guardar(abb, clave3, valor3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba ABB pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba ABB borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba ABB borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba ABB pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba ABB obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba ABB la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba ABB pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba ABB borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba ABB borrar clave1, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba ABB pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba ABB obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba ABB la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba ABB pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba ABB borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba ABB borrar clave2, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba ABB pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba ABB obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba ABB la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    
}

static void prueba_abb_clave_vacia(){
    abb_t* abb = abb_crear(strcmp, free);

    char *clave = "", *valor = "";

    print_test("Prueba ABB insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba ABB la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba ABB obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba ABB pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba ABB borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba ABB la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_null(){
    abb_t* abb = abb_crear(strcmp, free);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba ABB insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba ABB la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba ABB obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba ABB pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba ABB borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba ABB la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

// Crea claves aleatorias de un largo de 10.
static void generar_claves(char** claves, size_t n){
    for (size_t i = 0; i < n; i++){
        claves[i] = malloc(sizeof(char)*10);
        sprintf(claves[i], "%ld", rand() % n);
    }
}

static void prueba_abb_volumen(size_t largo){
    abb_t* abb = abb_crear(strcmp, NULL);
    // Se crea un arreglo de claves generadas aleatoriamiente.
    // Asi se mantiene log(n) y es basicamente una lista.
    char** claves = malloc(largo * sizeof(char*));
    generar_claves(claves, largo);
    bool todo_bien = true;
    for(size_t i = 0; i < largo; i++){
        if(!abb_guardar(abb, claves[i], claves[i])){
            todo_bien = false;
        }
    }
    print_test("Prueba ABB se insertaron correctamente", todo_bien);
    todo_bien = true;
    for(size_t i = 0; i < largo; i++){
        if(abb_pertenece(abb, claves[i]) && strcmp(claves[i], abb_borrar(abb, claves[i]))){
            todo_bien = false;
        }
    }
    print_test("Prueba ABB se borraron correctamente", todo_bien);

    free(claves);
    abb_destruir(abb);
}

static void prueba_abb_iter_interno(){
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 3 valores y luego los recorre*/
    abb_guardar(abb, clave1, valor1);
    abb_guardar(abb, clave2, valor2);
    abb_guardar(abb, clave3, valor3);

    print_test("Se insertaron 3 datos", abb_cantidad(abb) == 3);
    abb_in_order(abb, imprimir_datos, NULL);
    print_test("El iter interno recorrio el ABB correctamente", true);
    abb_destruir(abb);
}

static ssize_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0){
            return (ssize_t)i;
        } 
    }
    return -1;
}

static void prueba_abb_iter_externo(){
    abb_t* abb = abb_crear(strcmp, NULL);
    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};
    /* Inserta 3 valores */
    print_test("Prueba ABB insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba ABB insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba ABB insertar clave3", abb_guardar(abb, claves[2], valores[2]));
    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;
    print_test("Prueba ABB iterador esta al final, es false", !abb_iter_in_al_final(iter));
    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba ABB iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba ABB iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba ABB iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba ABB iterador esta al final, es false", !abb_iter_in_al_final(iter));
    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba ABB iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba ABB iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba ABB iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba ABB iterador esta al final, es false", !abb_iter_in_al_final(iter));
    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba ABB iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba ABB iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba ABB iterador esta al final, es true", abb_iter_in_al_final(iter));
    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba ABB iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba ABB iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba ABB iterador esta al final, es true", abb_iter_in_al_final(iter));
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_iter_volumen(size_t largo){
    abb_t* abb = abb_crear(strcmp, free);
    char** claves = malloc(largo * sizeof(char*));
    generar_claves(claves, largo);
    bool todo_bien = true;
    for(size_t i = 0; i < largo; i++){
        if(!abb_guardar(abb, claves[i], claves[i])){
            todo_bien = false;
        }
    }
    print_test("Prueba ABB se insertaron correctamente", todo_bien);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    char* clave;
    char* valor;
    todo_bien = true;
    for(size_t i = 0; i < largo && !abb_iter_in_al_final(iter); i++){
        clave = (char*)abb_iter_in_ver_actual(iter);
        if (!clave){
            todo_bien = false;
            break;
        }
        valor = abb_obtener(abb,clave);
        if (!valor){
            todo_bien = false;
            break;
        }
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba ABB se itero correctamente", todo_bien);
    print_test("Prueba ABB el iterador esta al final", abb_iter_in_al_final(iter));

    free(claves);
    abb_destruir(abb);

}

void pruebas_abb_alumno(){

    printf("-----CREAR ABB VACÍO-----\n");
    prueba_abb_crear_vacio();
    
    printf("\n-----ITERAR EN ABB VACÍO-----\n");
    prueba_abb_iterar_vacio();

    printf("\n-----INSERTAR EN ABB-----\n");
    prueba_abb_insertar();

    printf("\n-----REEMPLAZAR VALORES EN ABB-----\n");
    prueba_abb_reemplazar();

    printf("\n-----REEMPLAZAR VALORES CON DESTRUCCION-----\n");
    prueba_abb_reemplazar_con_destruir();

    printf("\n-----BORRAR VALORES EN ABB-----\n");
    prueba_abb_borrar();

    printf("\n-----INSERTAR CLAVE VACÍA-----\n");
    prueba_abb_clave_vacia();

    printf("\n-----INSERTAR CLAVE VACÍA Y DATO NULO-----\n");
    prueba_abb_valor_null();

    printf("\n-----ITERADOR INTERNO DE ABB-----\n");
    prueba_abb_iter_interno();

    printf("\n-----ITERADOR EXTERNO DE ABB-----\n");
    prueba_abb_iter_externo();

    printf("\n-----PRUEBA DE VOLUMEN----\n");
    prueba_abb_volumen(5000);

    printf("\n-----PRUEBA DE VOLUMEN CON ITERADOR EXTERNO-----\n");
    prueba_abb_iter_volumen(5000);

    printf("\n-----FIN DE PRUEBAS-----\n");
}


int main(){
    pruebas_abb_alumno();
    return 0;
}
// Cualquier similitud con las pruebas de otro tp son mera coincidencia.