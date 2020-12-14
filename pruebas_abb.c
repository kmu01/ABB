#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
bool sumar_primeros_elementos (const char* clave , void* dato , void* extra);
bool sumar_elementos (const char* clave , void* dato , void* extra);


static void pruebas_abb_vacio(void){

    printf("\nINICIO DE PRUEBAS CON ARBOL VACIO\n");

    abb_t *arbol = abb_crear(strcmp,NULL);
    const char* clave_falsa = "Prueba";

    /* Inicio de pruebas */
    print_test("Creo un arbol", arbol != NULL);
    print_test("La cantidad es 0", abb_cantidad(arbol)==0);
    print_test ("Obtener dato es NULL" , abb_obtener(arbol,clave_falsa) == NULL);
    print_test ("Borrar clave no existente es NULL" , abb_borrar (arbol , clave_falsa) == NULL);
    print_test ("Pertenece clave no existente es false" , !abb_pertenece (arbol , clave_falsa));
    int extra = 0;
    abb_in_order(arbol , sumar_primeros_elementos , &extra);
    print_test ("Intento recorrer con iter interno" , true);
    /* Destruyo el arbol*/
    abb_destruir(arbol);
    print_test("El arbol fue destruido", true);

}

static void pruebas_abb_con_null(void){

    printf("\nINICIO DE PRUEBAS CON ARBOL Y NULL\n");

    abb_t *arbol = abb_crear(strcmp,NULL);
    /* Defino los valores a utilizar*/
    char *vacio="vacio";
    void *nada = NULL;
    /* Inicio de pruebas */
    print_test("Creo un arbol", arbol != NULL);

    /* Pruebo que esta vacio y que no hay elemento para hacer algo con ellos*/
    print_test("Prueba de que la cantidad es 0", abb_cantidad(arbol)==0);
    /* Introduzco el elemento NULL*/
    print_test("Introduzco el elemento NULL", abb_guardar(arbol,vacio,nada));
    print_test("Confirmo que cambio el largo de 0 a 1", abb_cantidad(arbol)==1);
    print_test ("Confirmo que pertenece el elemento" , abb_pertenece (arbol , vacio));
    print_test("Confirmo que el elemento introducido es NULL",abb_obtener(arbol,vacio)==nada);
    print_test("Elimino el elemento introducido",abb_borrar(arbol,vacio)==nada);
    print_test("Confirmo que cambio el largo de 1 a 0", abb_cantidad(arbol)==0);

    /* Destruyo el arbol*/
    abb_destruir(arbol);
    print_test("El arbol fue destruido", true);

}
static void pruebas_abb_con_algunos_elementos(void){

    printf("\nINICIO DE PRUEBAS CON ARBOL Y ALGUNOS ELEMENTOS\n");

    abb_t *arbol = abb_crear(strcmp,NULL);
    /* Defino los valores a utilizar*/
    char *claves[3]={"papa","pato","padre"};
    char *datos[3]={"1","2","3"};
    /* Inicio de pruebas */
    print_test("Creo un arbol", arbol != NULL);

    /* Pruebo que esta vacio y que no hay elemento para hacer algo con ellos*/
    print_test("Prueba de que la cantidad es 0", abb_cantidad(arbol)==0);
    /* Inicio pruebas */
    print_test("Introduzco el elemento 1", abb_guardar(arbol,claves[0],datos[0]));
    print_test("Confirmo que cambio el largo de 0 a 1", abb_cantidad(arbol)==1);
    print_test("Confirmo que el elemento pertenece" , abb_pertenece (arbol , claves[0]));
    print_test("Confirmo que el elemento introducido es el elemento 1",abb_obtener(arbol,claves[0])==datos[0]);
    print_test("Introduzco el elemento 2", abb_guardar(arbol,claves[1],datos[1]));
    print_test("confirmo que cambio el largo de 1 a 2", abb_cantidad(arbol)==2);
    print_test("Confirmo que el elemento pertenece" , abb_pertenece (arbol , claves[1]));
    print_test("confirmo que el elemento introducido es el elemento 2",abb_obtener(arbol,claves[1])==datos[1]);
    print_test("Introduzco el elemento 3", abb_guardar(arbol,claves[2],datos[2]));
    print_test("confirmo que cambio el largo de 2 a 3", abb_cantidad(arbol)==3);
    print_test("Confirmo que el elemento pertenece" , abb_pertenece (arbol , claves[2]));
    print_test("confirmo que el elemento introducido es el elemento 3",abb_obtener(arbol,claves[2])==datos[2]);
    print_test("Elimino el elemento 2",abb_borrar(arbol,claves[2])==datos[2]);
    print_test("Confirmo que cambio el largo de 3 a 2", abb_cantidad(arbol)==2);
    print_test("Confirmo que obtener con clave 2 es NULL",abb_obtener(arbol,claves[2])==NULL);
    print_test("Confirmo que despues de borrar no pertenece" , !abb_pertenece (arbol , claves[2]));

    /* Destruyo el arbol*/
    abb_destruir(arbol);
    print_test("El arbol fue destruido", true);

}

static void prueba_abb_insertar_elementos (void){
    
    printf ("\nINICIO DE PRUEBA INSERTAR ELEMENTOS\n");

    /* Defino recursos a utilizar */
    abb_t* arbol = abb_crear (strcmp , NULL);
    char* claves [6] = {"Clave 1" , "Clave 2" , "Clave 3" , "Clave 4" , "Clave 5" , "Clave 6"};
    char* datos [6] = {"Dato 1" , "Dato 2" , "Dato 3" , "Dato 4" , "Dato 5" , "Dato 6"};

    /* Inicio de pruebas */
    print_test ("Creo abb" , arbol != NULL);
    print_test ("Inserto elemento 3" , abb_guardar (arbol , claves[2] , datos[2]));
    print_test ("Inserto elemento 1" , abb_guardar (arbol , claves[0] , datos[0]));
    print_test ("Inserto elemento 4" , abb_guardar (arbol , claves[3] , datos[3]));
    print_test ("Inserto elemento 2" , abb_guardar (arbol , claves[1] , datos[1]));
    print_test ("Inserto elemento 6" , abb_guardar (arbol , claves[5] , datos[5]));
    print_test ("Inserto elemento 5" , abb_guardar (arbol , claves[4] , datos[4]));

    print_test ("Verifico que pertenece elemento 1" , abb_pertenece (arbol , claves[0]));
    print_test ("Verifico que pertenece elemento 2" , abb_pertenece (arbol , claves[1]));
    print_test ("Verifico que pertenece elemento 3" , abb_pertenece (arbol , claves[2]));
    print_test ("Verifico que pertenece elemento 4" , abb_pertenece (arbol , claves[3]));
    print_test ("Verifico que pertenece elemento 5" , abb_pertenece (arbol , claves[4]));
    print_test ("Verifico que pertenece elemento 6" , abb_pertenece (arbol , claves[5]));

    print_test ("Verifico obtener elemento 1" , abb_obtener(arbol , claves[0]) == datos[0]);
    print_test ("Verifico obtener elemento 2" , abb_obtener(arbol , claves[1]) == datos[1]);
    print_test ("Verifico obtener elemento 3" , abb_obtener(arbol , claves[2]) == datos[2]);
    print_test ("Verifico obtener elemento 4" , abb_obtener(arbol , claves[3]) == datos[3]);
    print_test ("Verifico obtener elemento 5" , abb_obtener(arbol , claves[4]) == datos[4]);
    print_test ("Verifico obtener elemento 6" , abb_obtener(arbol , claves[5]) == datos[5]);

    abb_destruir (arbol);
    print_test ("El arbol fue destruido" , true);
}

static void prueba_abb_borrar_elementos (void){
    
    printf ("\nINICIO DE PRUEBA BORRAR ELEMENTOS\n");

    /* Defino recursos a utilizar */
    abb_t* arbol = abb_crear (strcmp , NULL);
    char* claves [6] = {"Clave 1" , "Clave 2" , "Clave 3" , "Clave 4" , "Clave 5" , "Clave 6"};
    char* datos [6] = {"Dato 1" , "Dato 2" , "Dato 3" , "Dato 4" , "Dato 5" , "Dato 6"};

    /* Inicio de pruebas */
    print_test ("Creo abb" , arbol != NULL);
    print_test ("Inserto elemento 3" , abb_guardar (arbol , claves[2] , datos[2]));
    print_test ("Inserto elemento 1" , abb_guardar (arbol , claves[0] , datos[0]));
    print_test ("Inserto elemento 4" , abb_guardar (arbol , claves[3] , datos[3]));
    print_test ("Inserto elemento 2" , abb_guardar (arbol , claves[1] , datos[1]));
    print_test ("Inserto elemento 6" , abb_guardar (arbol , claves[5] , datos[5]));
    print_test ("Inserto elemento 5" , abb_guardar (arbol , claves[4] , datos[4]));

    print_test ("Borrar elemento 3 (raiz)" , abb_borrar (arbol , claves[2]) == datos[2]);
    print_test ("Borrar elemento 6" , abb_borrar (arbol , claves[5]) == datos[5]);
    print_test ("Borrar elemento 1" , abb_borrar (arbol , claves[0]) == datos[0]);
    print_test ("Borrar elemento 5" , abb_borrar (arbol , claves[4]) == datos[4]);
    print_test ("Borrar elemento 2" , abb_borrar (arbol , claves[1]) == datos[1]);
    print_test ("Borrar elemento 4" , abb_borrar (arbol , claves[3]) == datos[3]);

    abb_destruir (arbol);
    print_test ("El arbol fue destruido" , true);
}

static void prueba_abb_borrar_elementos_destruir(){

    printf ("\nINICIO DE PRUEBAS PARA DESTRUIR ELEMENTOS\n");

    /* Defino recursos a utilizar */
    abb_t* arbol = abb_crear (strcmp , free);
    char* claves [3] = {"Clave 1" , "Clave 2" , "Clave 3"};
    char* dato1 = malloc (5*sizeof (char));
    dato1[0]='H'; dato1[1]='O'; dato1[2]='L'; dato1[3]='A'; dato1[4]='\0';
    char* dato2 = malloc (5*sizeof (char));
    dato2[0]='C'; dato2[1]='A'; dato2[2]='S'; dato2[3]='A'; dato2[4]='\0';
    char* dato3 = malloc (5*sizeof (char));
    dato3[0]='A'; dato3[1]='L'; dato3[2]='G'; dato3[3]='O'; dato3[4]='\0';
    char* dato4 = malloc (5*sizeof (char));
    dato4[0]='M'; dato4[1]='A'; dato4[2]='T'; dato4[3]='E'; dato4[4]='\0';

    /* Inicio pruebas */
    print_test ("Creo un arbol" , arbol != NULL);
    print_test ("Insertar elemento" , abb_guardar(arbol,claves[1],dato2));
    print_test ("Insertar elemento" , abb_guardar(arbol,claves[0],dato1));
    print_test ("Insertar elemento" , abb_guardar(arbol,claves[2],dato3));

    print_test ("Reemplazo elemento" , abb_guardar(arbol,claves[0],dato4));

    abb_destruir(arbol);
    print_test("El arbol fue destruido",true);

}

static void prueba_abb_obtener_pertenece (void){

    printf ("\nINICIO DE PRUEBAS OBTENER Y PERTENECE\n");

    /* Defino recursos a utilizar */
    abb_t* arbol = abb_crear (strcmp , NULL);
    char* claves [5] = {"0" , "1" , "2" , "3" , "4"};
    int numeroo0 = 3; int* numero0 = &numeroo0;
    int numeroo1 = 4; int* numero1 = &numeroo1;
    int numeroo2 = 1; int* numero2 = &numeroo2;
    int numeroo3 = 10; int* numero3 = &numeroo3;
    int numeroo4 = 12; int* numero4 = &numeroo4;

    /* Inicio pruebas */
    print_test ("Inserto elemento 3" , abb_guardar (arbol , claves[2] , numero2));
    print_test ("Inserto elemento 1" , abb_guardar (arbol , claves[0] , numero0));
    print_test ("Inserto elemento 5" , abb_guardar (arbol , claves[4] , numero4));
    print_test ("Inserto elemento 1" , abb_guardar (arbol , claves[1] , numero1));
    print_test ("Inserto elemento 4" , abb_guardar (arbol , claves[3] , numero3));

    print_test ("Verifico cantidad 5" , abb_cantidad(arbol)==5);

    print_test ("Verifico que pertenece elemento 1" , abb_pertenece(arbol,claves[0]));
    print_test ("Verifico que pertenece elemento 2" , abb_pertenece(arbol,claves[1]));
    print_test ("Verifico que pertenece elemento 3" , abb_pertenece(arbol,claves[2]));
    print_test ("Verifico que pertenece elemento 4" , abb_pertenece(arbol,claves[3]));
    print_test ("Verifico que pertenece elemento 5" , abb_pertenece(arbol,claves[4]));

    print_test ("Verifico que coincide con el elemento1" , abb_obtener (arbol , claves[0])==numero0);
    print_test ("Verifico que coincide con el elemento2" , abb_obtener (arbol , claves[1])==numero1);
    print_test ("Verifico que coincide con el elemento3" , abb_obtener (arbol , claves[2])==numero2);
    print_test ("Verifico que coincide con el elemento4" , abb_obtener (arbol , claves[3])==numero3);
    print_test ("Verifico que coincide con el elemento5" , abb_obtener (arbol , claves[4])==numero4);

    abb_destruir (arbol);
    print_test ("El arbol fue destruido" , true);
}

static void prueba_abb_insertar_borrar_varios (){
    
    printf ("\nINICIO DE PRUEBAS CON VARIOS ELEMENTOS\n");

    /* Defino recursos a utilizar */
    abb_t* arbol = abb_crear (strcmp , NULL);
    char* claves [6] = {"0" , "4" , "7" , "13" , "34" , "52"};
    int numeroo0 = 3; int* numero0 = &numeroo0;
    int numeroo1 = 4; int* numero1 = &numeroo1;
    int numeroo2 = 1; int* numero2 = &numeroo2;
    int numeroo3 = 10; int* numero3 = &numeroo3;
    int numeroo4 = 12; int* numero4 = &numeroo4;
    int numeroo5 = 42; int* numero5 = &numeroo5;

    /* Inicio pruebas */
    print_test ("Insertar raiz" , abb_guardar (arbol , claves[3] , numero3));
    print_test ("Borro raiz" , abb_borrar(arbol , claves[3])==numero3);
    print_test ("Insertar nueva raiz" , abb_guardar (arbol , claves[2] , numero2));
    print_test ("Insertar elemento" , abb_guardar (arbol , claves[4] , numero4));
    print_test ("Insertar elemento" , abb_guardar(arbol , claves[3] , numero3));
    print_test ("Insertar elemento" , abb_guardar (arbol , claves[0] , numero0));
    print_test ("Insertar elemento" , abb_guardar (arbol , claves[1] , numero1));
    print_test ("Borrar elemento" , abb_borrar(arbol , claves[4])== numero4);
    print_test ("Insertar elemento" , abb_guardar(arbol , claves[5] , numero5));
    print_test ("Borrar elemento" , abb_borrar(arbol,claves[0])==numero0);
    print_test ("Verifico cantidad" , abb_cantidad(arbol)==4);

    abb_destruir (arbol);
    print_test ("El arbol fue destruido" , true);
}

static void prueba_abb_iterador_interno_con_corte (void){

    printf ("\nINICIO DE PRUEBAS ITERADOR INTERNO CON CORTE\n");

    /* Defino recursos a utilizar */
    abb_t* arbol = abb_crear (strcmp , NULL);
    char* claves[8] = {"M" , "S" , "G" , "B" , "L" , "A" , "D" , "T"};
    int numeroo0 = 3; int* numero0 = &numeroo0;
    int numeroo1 = 15; int* numero1 = &numeroo1;
    int numeroo2 = 7; int* numero2 = &numeroo2;
    int numeroo3 = 0; int* numero3 = &numeroo3;
    int numeroo4 = 16; int* numero4 = &numeroo4;
    int numeroo5 = 30; int* numero5 = &numeroo5;
    int numeroo6 = 2; int* numero6 = &numeroo6;
    int numeroo7 = 8; int* numero7 = &numeroo7;

    /* Inicio pruebas */
    print_test ("Inserto elemento 1" , abb_guardar (arbol , claves[0] , numero0));
    print_test ("Inserto elemento 2" , abb_guardar (arbol , claves[1] , numero1));
    print_test ("Inserto elemento 3" , abb_guardar (arbol , claves[2] , numero2));
    print_test ("Inserto elemento 4" , abb_guardar (arbol , claves[3] , numero3));
    print_test ("Inserto elemento 5" , abb_guardar (arbol , claves[4] , numero4));
    print_test ("Inserto elemento 6" , abb_guardar (arbol , claves[5] , numero5));
    print_test ("Inserto elemento 7" , abb_guardar (arbol , claves[6] , numero6));
    print_test ("Inserto elemento 8" , abb_guardar (arbol , claves[7] , numero7));

    int extra = 0;
    abb_in_order (arbol , sumar_primeros_elementos , &extra);
    print_test ("Verifico resultado iteracion" , extra == 55);

    abb_destruir (arbol);
    print_test ("El arbol fue destruido" , true);  
}

static void prueba_abb_iterador_interno_sin_corte(void){

    printf ("\nINICIO DE PRUEBAS ITERADOR INTERNO SIN CORTE\n");

    /* Defino recursos a utilizar */
    abb_t* arbol = abb_crear (strcmp , NULL);
    char* claves[8] = {"M" , "S" , "G" , "B" , "L" , "A" , "D" , "T"};
    int numeroo0 = 3; int* numero0 = &numeroo0;
    int numeroo1 = 15; int* numero1 = &numeroo1;
    int numeroo2 = 7; int* numero2 = &numeroo2;
    int numeroo3 = 0; int* numero3 = &numeroo3;
    int numeroo4 = 16; int* numero4 = &numeroo4;
    int numeroo5 = 30; int* numero5 = &numeroo5;
    int numeroo6 = 2; int* numero6 = &numeroo6;
    int numeroo7 = 8; int* numero7 = &numeroo7;

    /* Inicio pruebas */
    print_test ("Inserto elemento 1" , abb_guardar (arbol , claves[0] , numero0));
    print_test ("Inserto elemento 2" , abb_guardar (arbol , claves[1] , numero1));
    print_test ("Inserto elemento 3" , abb_guardar (arbol , claves[2] , numero2));
    print_test ("Inserto elemento 4" , abb_guardar (arbol , claves[3] , numero3));
    print_test ("Inserto elemento 5" , abb_guardar (arbol , claves[4] , numero4));
    print_test ("Inserto elemento 6" , abb_guardar (arbol , claves[5] , numero5));
    print_test ("Inserto elemento 7" , abb_guardar (arbol , claves[6] , numero6));
    print_test ("Inserto elemento 8" , abb_guardar (arbol , claves[7] , numero7));

    int extra = 0;
    abb_in_order (arbol , sumar_elementos , &extra);
    print_test ("Verifico resultado iteracion" , extra == 81);

    abb_destruir (arbol);
    print_test ("El arbol fue destruido" , true);  

}

static void prueba_abb_iter_vacio (void){

    printf ("\n INICIO DE PRUEBAS ITER VACIO\n");

    /* Defino recursos a utilizar */
    abb_t* arbol = abb_crear (strcmp , NULL);
    abb_iter_t* iter = abb_iter_in_crear(arbol);

    /* Inicio pruebas */
    print_test ("Creo el iterador" , iter!= NULL);
    print_test ("Verifico que ver actual es NULL",abb_iter_in_ver_actual(iter)==NULL);
    print_test ("Verifico que está al final" , abb_iter_in_al_final(iter));
    print_test ("Verifico avanzar es false" , !abb_iter_in_avanzar(iter));

    /* Destruyo el iterador */
    abb_iter_in_destruir(iter);
    print_test("El iterador fue destruido" , true);
    abb_destruir (arbol);
    print_test ("El arbol fue destruido" , true);
}

static void prueba_abb_iter_avanzar_ver_actual (void){

    printf ("\nINICIO DE PRUEBAS ITER AVANZAR Y VER ACTUAL\n");

    /* Defino recursos a utilizar */
    abb_t* arbol = abb_crear (strcmp , NULL);
    char* claves[8] = {"M" , "S" , "G" , "B" , "L" , "A" , "D" , "T"};
    int numeroo0 = 3; int* numero0 = &numeroo0;
    int numeroo1 = 15; int* numero1 = &numeroo1;
    int numeroo2 = 7; int* numero2 = &numeroo2;
    int numeroo3 = 0; int* numero3 = &numeroo3;
    int numeroo4 = 16; int* numero4 = &numeroo4;
    int numeroo5 = 30; int* numero5 = &numeroo5;
    int numeroo6 = 2; int* numero6 = &numeroo6;
    int numeroo7 = 8; int* numero7 = &numeroo7;

    print_test ("Inserto elemento 1" , abb_guardar (arbol , claves[0] , numero0));
    print_test ("Inserto elemento 2" , abb_guardar (arbol , claves[1] , numero1));
    print_test ("Inserto elemento 3" , abb_guardar (arbol , claves[2] , numero2));
    print_test ("Inserto elemento 4" , abb_guardar (arbol , claves[3] , numero3));
    print_test ("Inserto elemento 5" , abb_guardar (arbol , claves[4] , numero4));
    print_test ("Inserto elemento 6" , abb_guardar (arbol , claves[5] , numero5));
    print_test ("Inserto elemento 7" , abb_guardar (arbol , claves[6] , numero6));
    print_test ("Inserto elemento 8" , abb_guardar (arbol , claves[7] , numero7));

    abb_iter_t* iter = abb_iter_in_crear (arbol);

    /* Inicio de pruebas */
    print_test ("Creo el iter" , iter!=NULL);
    print_test ("Verifico que no está al final" , !abb_iter_in_al_final(iter));
    print_test ("Veo que el actual coincida",(int)strcmp (abb_iter_in_ver_actual(iter),claves[5]) == 0);
    print_test ("Avanzo el iter" , abb_iter_in_avanzar(iter));
    print_test ("Verifico que no está al final" , !abb_iter_in_al_final(iter));
    print_test ("Veo que el actual coincida",(int)strcmp (abb_iter_in_ver_actual(iter),claves[3]) == 0);
    print_test ("Avanzo el iter" , abb_iter_in_avanzar(iter));
    print_test ("Verifico que no está al final" , !abb_iter_in_al_final(iter));
    print_test ("Veo que el actual coincida",(int)strcmp (abb_iter_in_ver_actual(iter),claves[6]) == 0);
    print_test ("Avanzo el iter" , abb_iter_in_avanzar(iter));
    print_test ("Verifico que no está al final" , !abb_iter_in_al_final(iter));
    print_test ("Veo que el actual coincida",(int)strcmp (abb_iter_in_ver_actual(iter),claves[2]) == 0);
    print_test ("Avanzo el iter" , abb_iter_in_avanzar(iter));
    print_test ("Verifico que no está al final" , !abb_iter_in_al_final(iter));
    print_test ("Veo que el actual coincida",(int)strcmp (abb_iter_in_ver_actual(iter),claves[4]) == 0);
    print_test ("Avanzo el iter" , abb_iter_in_avanzar(iter));
    print_test ("Verifico que no está al final" , !abb_iter_in_al_final(iter));
    print_test ("Veo que el actual coincida",(int)strcmp (abb_iter_in_ver_actual(iter),claves[0]) == 0);
    print_test ("Avanzo el iter" , abb_iter_in_avanzar(iter));
    print_test ("Verifico que no está al final" , !abb_iter_in_al_final(iter));
    print_test ("Veo que el actual coincida",(int)strcmp (abb_iter_in_ver_actual(iter),claves[1]) == 0);
    print_test ("Avanzo el iter" , abb_iter_in_avanzar(iter));
    print_test ("Verifico que no está al final" , !abb_iter_in_al_final(iter));
    print_test ("Veo que el actual coincida",(int)strcmp (abb_iter_in_ver_actual(iter),claves[7]) == 0);
    print_test ("Avanzo el iter" , abb_iter_in_avanzar(iter));
    print_test ("Verifico que está al final" , abb_iter_in_al_final(iter));
    print_test ("Veo que el actual es NULL",abb_iter_in_ver_actual(iter)==NULL);

    /* Destruyo el iterador */
    abb_iter_in_destruir(iter);
    print_test("El iterador fue destruido" , true);
    abb_destruir (arbol);
    print_test ("El arbol fue destruido" , true);
}

// Funciones para iterador interno
bool sumar_primeros_elementos (const char* clave , void* dato , void* extra){
    char* clave_tope = "M";
    int comparacion = (int)strcmp (clave , clave_tope);
    if (comparacion<0){
        *(int*)extra += *(int*)dato;
        return true;
    }
    return false;
}

bool sumar_elementos (const char* clave , void* dato , void* extra){
    *(int*)extra += *(int*)dato;
    return true;
}

// Crea claves aleatorias de un largo de 10.
static void generar_claves(char** claves, size_t n){
    for (size_t i = 0; i < n; i++){
        claves[i] = malloc(sizeof(char)*10);
        sprintf(claves[i], "%ld", rand() % n);
    }
}

static void prueba_abb_volumen(size_t largo){
    printf ("\nINICIO DE PRUEBAS DE VOLUMEN\n");
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
            free(claves[i]);
        }
    }
    print_test("Prueba ABB se borraron correctamente", todo_bien);
    for(size_t i = 0; i < largo; i++){
        free(claves[i]);
    }
    free(claves);
    abb_destruir(abb);
}

static void prueba_abb_iter_volumen(size_t largo){
    printf ("\nINICIO DE PRUEBAS DE VOLUMEN CON ITERADOR\n");
    abb_t* abb = abb_crear(strcmp, NULL);
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
    for(size_t i = 0; i < largo; i++){
        free(claves[i]);
    }
    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);

}

void pruebas_abb_estudiante() {
    pruebas_abb_vacio();
    pruebas_abb_con_null();
    pruebas_abb_con_algunos_elementos();
    prueba_abb_insertar_elementos ();
    prueba_abb_borrar_elementos();
    prueba_abb_borrar_elementos_destruir();
    prueba_abb_obtener_pertenece ();
    prueba_abb_insertar_borrar_varios ();
    prueba_abb_iterador_interno_con_corte ();
    prueba_abb_iterador_interno_sin_corte();
    prueba_abb_iter_vacio ();
    prueba_abb_iter_avanzar_ver_actual();
    prueba_abb_volumen(5000);
    prueba_abb_iter_volumen(5000);
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_abb_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
