#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador) {
		return NULL;
	}
	abb_t *abb = malloc(sizeof(abb_t));
	if (!abb) {
		return NULL;
	}
	abb->comparador = comparador;
	abb->nodo_raiz = NULL;
	abb->tamanio = 0;
	return abb;
}
/*
 *pre: recibe un puntero a un elemento de tipo indeterminado.
 * post: reserva memoria para un nodo nuevo y lo devuelve en caso de error debuelve null.
 */
nodo_abb_t *crear_nodo(void *elemento)
{
	nodo_abb_t *nuevo_nodo = malloc(sizeof(nodo_abb_t));
	if (!nuevo_nodo) {
		return NULL;
	}
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->derecha = NULL;
	nuevo_nodo->izquierda = NULL;
	return nuevo_nodo;
}
/*
 *pre: recibe el nodo raiz ,el elemento a insertar,una funcion comparadora .
 * post: reserva memoria para un nuevo nodo y lo inserta de forma ordenada. 
 */
nodo_abb_t *abb_insertar_rec(nodo_abb_t *nodo, void *elemento,
			     int (*comparador)(void *, void *), bool *problema)
{
	if (!nodo) {
		nodo_abb_t *nuevo_nodo = crear_nodo(elemento);
		if (!nuevo_nodo) {
			*problema = true;
		}

		return nuevo_nodo;
	}
	int valor = comparador(elemento, nodo->elemento);
	if (valor <= 0) {
		nodo->izquierda = abb_insertar_rec(nodo->izquierda, elemento,
						   comparador, problema);
	} else if (valor > 0) {
		nodo->derecha = abb_insertar_rec(nodo->derecha, elemento,
						 comparador, problema);
	}
	return nodo;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}
	bool problema = false;
	arbol->nodo_raiz = abb_insertar_rec(arbol->nodo_raiz, elemento,
					    arbol->comparador, &problema);

	if (problema) {
		return NULL;
	}

	arbol->tamanio++;
	return arbol;
}

/*
 *pre: recibe el nodo raiz y un puntero al elemento buscado.
 * post: elimina el predecesor inorden y se guarda el elemento. 
 */
nodo_abb_t *extraer_predecesor(nodo_abb_t *nodo, void **elemento)
{
	if (nodo->derecha == NULL) {
		*elemento = nodo->elemento;
		nodo_abb_t *aux_izquierda = nodo->izquierda;
		free(nodo);
		return aux_izquierda;
	}

	nodo->derecha = extraer_predecesor(nodo->derecha, elemento);
	return nodo;
}

/*
 *pre: recibe el nodo raiz, elelemento a eliminar otra varible elemento buscado con valor null,una funcion comparador y una variable quitado en false.
 * post:quita el elemneto del arbol  si se encuentra.
 */
nodo_abb_t *quitar_rec(nodo_abb_t *nodo, void *elemento,
		       int (*comparador)(void *, void *),
		       void **elemento_buscado, bool *quitado)
{
	if (!nodo) {
		return NULL;
	}
	int valor = comparador(elemento, nodo->elemento);

	if (valor < 0) {
		nodo->izquierda = quitar_rec(nodo->izquierda, elemento,
					     comparador, elemento_buscado,
					     quitado);

	} else if (valor > 0) {
		nodo->derecha = quitar_rec(nodo->derecha, elemento, comparador,
					   elemento_buscado, quitado);
	} else {
		*quitado = true;
		*elemento_buscado = nodo->elemento;
		if (nodo->izquierda == NULL || nodo->derecha == NULL) {
			nodo_abb_t *hijo_valido = nodo->izquierda;
			if (!hijo_valido) {
				hijo_valido = nodo->derecha;
			}

			free(nodo);
			return hijo_valido;

		} else {
			void *valor = NULL;
			nodo->izquierda =
				extraer_predecesor(nodo->izquierda, &valor);
			nodo->elemento = valor;
			return nodo;
		}
	}
	return nodo;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol || abb_vacio(arbol)) {
		return NULL;
	}

	void *buscado = NULL;
	bool quitado = false;
	arbol->nodo_raiz = quitar_rec(arbol->nodo_raiz, elemento,
				      arbol->comparador, &buscado, &quitado);
	if (quitado) {
		arbol->tamanio--;
	}
	return buscado;
}

/*
 *pre: recibe el nodo raiz ,el elemento a buscar,y una funcion comparadora.
 *post: busca el elemento recibido como parametro y lo devuelve ,en caso de no encontrarlo devuelve null.
 */
void *buscar_rec(nodo_abb_t *nodo, void *elemento,
		 int (*comparador)(void *, void *))
{
	if (!nodo) {
		return NULL;
	}
	int valor = comparador(elemento, nodo->elemento);

	if (valor < 0) {
		return buscar_rec(nodo->izquierda, elemento, comparador);
	} else if (valor > 0) {
		return buscar_rec(nodo->derecha, elemento, comparador);
	}
	return nodo->elemento;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}

	return buscar_rec(arbol->nodo_raiz, elemento, arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
	if (!arbol || abb_tamanio(arbol) == 0) {
		return true;
	}

	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol) {
		return 0;
	}
	return arbol->tamanio;
}

/*
 *pre: recibe el nodo raiz.
 *post: libera todos los nodos.
 */
void abb_destruir_rec(nodo_abb_t *nodo)
{
	if (!nodo) {
		return;
	}
	abb_destruir_rec(nodo->izquierda);
	abb_destruir_rec(nodo->derecha);
	free(nodo);
}
void abb_destruir(abb_t *arbol)
{
	if (!arbol) {
		return;
	}

	abb_destruir_rec(arbol->nodo_raiz);
	free(arbol);
}

/*
 *pre: recibe el nodo raiz y una funcion destructora.
 *post: le aplica la funcion destructora cada elemento y libera los nodos.
 */
void abb_destruir_todo_rec(nodo_abb_t *nodo, void (*destructor)(void *))
{
	if (!nodo) {
		return;
	}

	abb_destruir_todo_rec(nodo->izquierda, destructor);
	abb_destruir_todo_rec(nodo->derecha, destructor);
	destructor(nodo->elemento);
	free(nodo);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol) {
		return;
	}
	if (!destructor) {
		abb_destruir(arbol);
		return;
	}
	abb_destruir_todo_rec(arbol->nodo_raiz, destructor);
	free(arbol);
}

/*
 *pre: recibe el nodo raiz ,una funcion ,un contador con valor 0.
 * post: itera todos los elementos de manera inorder , va aplicando la funcion a cada elemento mientras la funcion de true  y cuenta cuantos elementos pudo iterar.
 */
bool iterrar_inorder(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
		     void *aux, int *contador)
{
	if (!nodo)
		return true;

	if (iterrar_inorder(nodo->izquierda, funcion, aux, contador) == false) {
		return false;
	}
	(*contador)++;
	if (funcion(nodo->elemento, aux) == false) {
		return false;
	}
	return iterrar_inorder(nodo->derecha, funcion, aux, contador);
}
/*
 *pre: recibe el nodo raiz ,una funcion ,un contador con valor 0.
 * post: itera todos los elementos de manera postorder,va aplicando la funcion a cada elemento mientras la funcion de true y cuenta cuantos elementos pudo iterar.
 */
bool iterrar_postorder(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
		       void *aux, int *contador)
{
	if (!nodo)
		return true;

	if (iterrar_postorder(nodo->izquierda, funcion, aux, contador) ==
	    false) {
		return false;
	}

	if (iterrar_postorder(nodo->derecha, funcion, aux, contador) == false) {
		return false;
	}

	(*contador)++;
	if (funcion(nodo->elemento, aux) == false) {
		return false;
	}
	return true;
}

/*
 *pre: recibe el nodo raiz ,una funcion ,un contador con valor 0.
 * post: itera todos los elementos de manera preorder,va aplicando la funcion a cada elemento mientras la funcion de true y cuenta cuantos elementos pudo iterar.
 */
bool iterrar_preorder(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
		      void *aux, int *contador)
{
	if (!nodo)
		return true;

	(*contador)++;
	if (funcion(nodo->elemento, aux) == false) {
		return false;
	}
	if (iterrar_preorder(nodo->izquierda, funcion, aux, contador) ==
	    false) {
		return false;
	}
	return iterrar_preorder(nodo->derecha, funcion, aux, contador);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || !funcion) {
		return 0;
	}
	int contador = 0;
	if (recorrido == INORDEN) {
		iterrar_inorder(arbol->nodo_raiz, funcion, aux, &contador);

	} else if (recorrido == POSTORDEN) {
		iterrar_postorder(arbol->nodo_raiz, funcion, aux, &contador);
	} else if (recorrido == PREORDEN) {
		iterrar_preorder(arbol->nodo_raiz, funcion, aux, &contador);
	}
	return (size_t)contador;
}

/*
 *pre: recibe el nodo raiz,el tamanio del vector y una variable tamañio con valor 0.
 *post:recorre todos los elementos de manera inorder mientras tamanio < al tamañio del vector y va cargando el vector.
 */
void recorrer_inorder(nodo_abb_t *nodo, void **array, size_t *tamanio,
		      size_t tamanio_array)
{
	if (!nodo)
		return;

	if (nodo->izquierda) {
		recorrer_inorder(nodo->izquierda, array, tamanio,
				 tamanio_array);
	}
	if ((*tamanio) >= tamanio_array)
		return;

	array[(*tamanio)] = nodo->elemento;
	(*tamanio)++;

	if (nodo->derecha) {
		recorrer_inorder(nodo->derecha, array, tamanio, tamanio_array);
	}
	return;
}

/*
 *pre: recibe el nodo raiz,el tamanio del vector y una variable tamañio con valor 0.
 *post:recorre todos los elementos de manera postorder mientras tamanio < al tamañio del vector y va cargando el vector.
 */
void recorrer_postorden(nodo_abb_t *nodo, void **array, size_t *tamanio,
			size_t tamanio_array)
{
	if (!nodo) {
		return;
	}
	if (nodo->izquierda) {
		recorrer_postorden(nodo->izquierda, array, tamanio,
				   tamanio_array);
	}
	if (nodo->derecha) {
		recorrer_postorden(nodo->derecha, array, tamanio,
				   tamanio_array);
	}
	if ((*tamanio) >= tamanio_array)
		return;

	array[(*tamanio)] = nodo->elemento;
	(*tamanio)++;
	return;
}

/*
 *pre: recibe el nodo raiz,el tamanio del vector y una variable tamañio con valor 0.
 *post:recorre todos los elementos de manera preorder mientras tamanio < al tamañio del vector y va cargando el vector.
 */
void recorrer_preorder(nodo_abb_t *nodo, void **array, size_t *tamanio,
		       size_t tamanio_array)
{
	if (!nodo) {
		return;
	}
	if ((*tamanio) >= tamanio_array)
		return;

	array[(*tamanio)] = nodo->elemento;
	(*tamanio)++;

	if (nodo->izquierda) {
		recorrer_preorder(nodo->izquierda, array, tamanio,
				  tamanio_array);
	}
	if (nodo->derecha) {
		recorrer_preorder(nodo->derecha, array, tamanio, tamanio_array);
	}
	return;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol) {
		return 0;
	}
	size_t cantidad = 0;
	if (recorrido == INORDEN) {
		recorrer_inorder(arbol->nodo_raiz, array, &cantidad,
				 tamanio_array);
	} else if (recorrido == POSTORDEN) {
		recorrer_postorden(arbol->nodo_raiz, array, &cantidad,
				   tamanio_array);
	} else if (recorrido == PREORDEN) {
		recorrer_preorder(arbol->nodo_raiz, array, &cantidad,
				  tamanio_array);
	}
	return cantidad;
}
