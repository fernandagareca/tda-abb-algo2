#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

#define MAX 11
int comparar_cosas(void *c1, void *c2)
{
	char *cosa1 = c1;
	char *cosa2 = c2;
	return (*cosa1) - (*cosa2);
}
typedef struct prueba {
	int vector[11];
	int posicion;
} prueba_t;

void crear_arbol_devuelve_distinto_de_null()
{
	abb_t *arbol = abb_crear(comparar_cosas);
	pa2m_afirmar(arbol != NULL, "crear un arbol devuelve distinto de null");
	abb_destruir(arbol);
}

void pruebas_en_arbol_vacio()
{
	abb_t *arbol = abb_crear(comparar_cosas);
	pa2m_afirmar(abb_vacio(arbol) == true,
		     "un arbol recien creado esta vacio");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "un arbol recien creado tiene cantidad 0");
	abb_destruir(arbol);
}

void pruebas_inserccion()
{
	int elemento = 44;
	int elemento2 = 18;

	abb_t *arbol = abb_crear(comparar_cosas);
	pa2m_afirmar(abb_vacio(arbol) == true,
		     "un arbol recien creado esta vacio");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "un arbol recien creado tiene cantidad 0");
	pa2m_afirmar(abb_insertar(arbol, &elemento) == arbol,
		     "insertar un elemento devuelve el arbol");
	pa2m_afirmar(abb_tamanio(arbol) == 1, "el tamaño es 1");
	pa2m_afirmar(abb_vacio(arbol) == false, "el arbol ya no esta vacio");

	pa2m_afirmar(abb_insertar(arbol, &elemento2) == arbol,
		     "insertar un elemento devuelve el arbol");
	pa2m_afirmar(abb_tamanio(arbol) == 2, "el tamaño es 2");

	abb_destruir(arbol);
}

void pruebas_en_un_arbol_null()
{
	abb_t *arbol = NULL;
	int elemento = 2;
	pa2m_afirmar(abb_vacio(arbol) == true, "un arbol null esta vacio");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "un arbol null tiene cantidad 0");
	pa2m_afirmar(
		abb_insertar(arbol, &elemento) == arbol,
		"insertar un elemento en un arbol inexistente devuelve null");
	pa2m_afirmar(abb_buscar(arbol, &elemento) == NULL,
		     "buscar en un arbol inexiste devuleve null");
	pa2m_afirmar(abb_quitar(arbol, &elemento) == NULL,
		     "quitar en un arbol inexistente devuelve null");
}

void pruebas_de_busqueda()
{
	char *elemento = "hola";
	char *elemento2 = "chau";
	abb_t *arbol = abb_crear(comparar_cosas);
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "un arbol recien creado tiene cantidad 0");

	abb_insertar(arbol, elemento);
	pa2m_afirmar(abb_buscar(arbol, elemento) == elemento,
		     "el elemento insertado se encuentra");
	pa2m_afirmar(abb_buscar(arbol, elemento2) == NULL,
		     "el elemento buscado no se encuentra");
	abb_destruir(arbol);
}

void pruebas_de_eliminar()
{
	abb_t *arbol = abb_crear(comparar_cosas);
	char *elemento = "hola";

	int elemento1 = 61;
	int elemento2 = 33;
	int elemento3 = 87;
	int elemento4 = 40;
	int elemento5 = 30;

	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "un arbol recien creado tiene cantidad 0");

	abb_insertar(arbol, elemento);
	pa2m_afirmar(abb_tamanio(arbol) == 1, "un arbol tiene cantidad 1");
	pa2m_afirmar(abb_quitar(arbol, elemento) == elemento,
		     "se quito el elemento raiz");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "un arbol tiene cantidad 0");
	int *valor = 0;

	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_insertar(arbol, &elemento5);
	pa2m_afirmar(abb_tamanio(arbol) == 5, "la cantidad del arbol el 5");
	valor = abb_quitar(arbol, &elemento1);
	pa2m_afirmar(*valor == elemento1,
		     "se quito el elemento de la raiz devuelve el elemento");
	valor = arbol->nodo_raiz->elemento;
	pa2m_afirmar(*valor == elemento4, "la nueva raiz es correcta");
	pa2m_afirmar(abb_buscar(arbol, &elemento1) == NULL,
		     "no se encuentra el elemento eliminado devuelve null");
	pa2m_afirmar(abb_tamanio(arbol) == 4, "el tamaño es 4");
	valor = abb_quitar(arbol, &elemento2);
	pa2m_afirmar(*valor == elemento2,
		     "se elimina un elemento devuelve el elemento");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "el tamaño es 3");
	valor = arbol->nodo_raiz->derecha->elemento;
	pa2m_afirmar(*valor == elemento3,
		     "el elemento derecho de la raiz es correcto");
	valor = abb_quitar(arbol, &elemento4);
	pa2m_afirmar(*valor == elemento4, "se elimina la raiz");
	valor = arbol->nodo_raiz->elemento;
	pa2m_afirmar(*valor == elemento5, "la nueva raiz es correcta");
	pa2m_afirmar(abb_tamanio(arbol) == 2, "el tamano es 2");
	valor = abb_quitar(arbol, &elemento3);
	pa2m_afirmar(*valor == elemento3,
		     "se elimina un elemento devuelve el elemento");
	pa2m_afirmar(abb_tamanio(arbol) == 1, "el tamaño es 1");
	valor = abb_quitar(arbol, &elemento5);
	pa2m_afirmar(*valor == elemento5,
		     "se elimina la raiz devuelve la raiz");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "el tamaño es 0");
	pa2m_afirmar(abb_vacio(arbol) == true, "el arbol esta vacio");

	abb_destruir(arbol);
}

void insertar_y_eliminar()
{
	int elemento1 = 61;
	int elemento2 = 100;
	int *valor;

	abb_t *arbol = abb_crear(comparar_cosas);

	abb_insertar(arbol, &elemento1);
	pa2m_afirmar(abb_vacio(arbol) == false, "el arbol no esta vacio");
	valor = abb_quitar(arbol, &elemento1);
	pa2m_afirmar(*valor == elemento1, "se quito el elemento");
	pa2m_afirmar(abb_vacio(arbol) == true, "el arbol esta vacio");

	abb_insertar(arbol, &elemento1);
	pa2m_afirmar(abb_vacio(arbol) == false, "el arbol no esta vacio");
	valor = abb_quitar(arbol, &elemento1);
	pa2m_afirmar(*valor == elemento1, "se quito el elemento");
	pa2m_afirmar(abb_vacio(arbol) == true, "el arbol esta vacio");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "el arbol esta vacio");
	pa2m_afirmar(abb_quitar(arbol, &elemento1) == NULL,
		     "intentar eliminar en una rbol vacio devuelve null");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "el arbol esta vacio");
	pa2m_afirmar(abb_insertar(arbol, &elemento1) == arbol,
		     "se inseto un elemento");
	pa2m_afirmar(abb_vacio(arbol) == false, "el arbol no esta vacio");
	pa2m_afirmar(
		abb_quitar(arbol, &elemento2) == NULL,
		"intentar quitar un elemento que no se encuntra devuleve null");
	pa2m_afirmar(abb_tamanio(arbol) == 1,
		     "el arbol continua con un elemento");
	valor = abb_buscar(arbol, &elemento1);
	pa2m_afirmar(*valor == elemento1, "no se borro el elemento almacenado");
	abb_destruir(arbol);
}

bool funcion(void *v1, void *v2)
{
	int *valor = v1;
	prueba_t *prueba = v2;
	pa2m_afirmar(*valor == prueba->vector[prueba->posicion],
		     "se itero el elemento correcto");
	prueba->posicion++;

	return true;
}

void iterrar_todos_los_elementos(int vector[MAX], abb_recorrido recorrido)
{
	abb_t *arbol = abb_crear(comparar_cosas);

	int elemento1 = 20, elemento2 = 15, elemento3 = 25, elemento4 = 10,
	    elemento5 = 17, elemento6 = 30, elemento7 = 5, elemento8 = 13,
	    elemento9 = 19, elemento10 = 27, elemento11 = 35;

	prueba_t prueba;

	for (int i = 0; i < 11; i++) {
		prueba.vector[i] = vector[i];
	}
	prueba.posicion = 0;

	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_insertar(arbol, &elemento5);
	abb_insertar(arbol, &elemento6);
	abb_insertar(arbol, &elemento7);
	abb_insertar(arbol, &elemento8);
	abb_insertar(arbol, &elemento9);
	abb_insertar(arbol, &elemento10);
	abb_insertar(arbol, &elemento11);

	pa2m_afirmar(abb_con_cada_elemento(arbol, recorrido, funcion,
					   &prueba) == abb_tamanio(arbol),
		     "se iteraron todos los elementos");
	abb_destruir(arbol);
}

void pruebas_de_recorrer(int vector[MAX], abb_recorrido recorrido)
{
	abb_t *arbol = abb_crear(comparar_cosas);

	int elemento1 = 20, elemento2 = 15, elemento3 = 25, elemento4 = 10,
	    elemento5 = 17, elemento6 = 30, elemento7 = 5, elemento8 = 13,
	    elemento9 = 19, elemento10 = 27, elemento11 = 35;

	void **array = calloc(11, sizeof(void *));
	size_t tamanio = 11;

	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_insertar(arbol, &elemento5);
	abb_insertar(arbol, &elemento6);
	abb_insertar(arbol, &elemento7);
	abb_insertar(arbol, &elemento8);
	abb_insertar(arbol, &elemento9);
	abb_insertar(arbol, &elemento10);
	abb_insertar(arbol, &elemento11);

	pa2m_afirmar(abb_recorrer(arbol, recorrido, array, tamanio) ==
			     abb_tamanio(arbol),
		     "se recorrieron todos los elementos");
	for (int i = 0; i < tamanio; i++) {
		int *valor = array[i];
		pa2m_afirmar(*valor == vector[i],
			     "el elemento recorrido es correcto");
	}

	abb_destruir(arbol);
	free(array);
}

int main()
{
	int vector_inorder[MAX] = { 5, 10, 13, 15, 17, 19, 20, 25, 27, 30, 35 };
	int vector_postorden[MAX] = {
		5, 13, 10, 19, 17, 15, 27, 35, 30, 25, 20
	};
	int vector_preorder[MAX] = { 20, 15, 10, 5, 13, 17, 19, 25, 30, 27, 35 };

	pa2m_nuevo_grupo("pruebas de arbol inexistente");
	pruebas_en_un_arbol_null();

	pa2m_nuevo_grupo("pruebas de crear arbol");
	crear_arbol_devuelve_distinto_de_null();
	pruebas_en_arbol_vacio();

	pa2m_nuevo_grupo("pruebas de insercion");
	pruebas_inserccion();

	pa2m_nuevo_grupo("pruebas de busqueda");
	pruebas_de_busqueda();

	pa2m_nuevo_grupo("pruebas de eliminacion");
	pruebas_de_eliminar();
	pa2m_nuevo_grupo(" mas pruebas de eliminacion");
	insertar_y_eliminar();

	pa2m_nuevo_grupo("prueba de iterrador inorder");
	iterrar_todos_los_elementos(vector_inorder, 0);
	pa2m_nuevo_grupo("prueba de iterrador postorder");
	iterrar_todos_los_elementos(vector_postorden, 2);
	pa2m_nuevo_grupo("prueba de iterrador preorder");
	iterrar_todos_los_elementos(vector_preorder, 1);

	pa2m_nuevo_grupo("prueba de recorrido inorder");
	pruebas_de_recorrer(vector_inorder, 0);
	pa2m_nuevo_grupo("prueba de recorrido preorder");
	pruebas_de_recorrer(vector_preorder, 1);
	pa2m_nuevo_grupo("prueba de recorrido postorden");
	pruebas_de_recorrer(vector_postorden, 2);

	return pa2m_mostrar_reporte();
}
