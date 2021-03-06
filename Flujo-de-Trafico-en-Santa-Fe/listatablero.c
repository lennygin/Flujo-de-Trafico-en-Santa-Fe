/**
 *@listatablero.c
 *Este programa agrega los movimientos a una lista declarada en listatablero.h,
 *guarda la lista en un archivo, lee la lista de archivo, elimina la lista que 
 *se encuentra en memoria y trunca la lista en caso de que el usuario quiera 
 *retomar la lista desde un punto diferente al final.
 *@Mariana
 *@01/05/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include "listatablero.h"




PtrMovimiento raiz=NULL; //Inicializamos la raiz a NULL

/**
 *Esta función agrega el movimiento y la ficha a una lista 
 *Recibe la posición en i,j y el color de la ficha
 *Regresa 0 en caso de éxito
 *Regresa -1 en caso de error
 *@Mariana 
 *@Param int i Posición en tablero
 *@Param int j Posición en tablero
 *@Param char color Color de la ficha(ficha a colocar)
 *@return int
 */
int AgregarMov(int i, int j, char color)
{
  PtrMovimiento elemento, p;
  elemento = (PtrMovimiento)malloc(sizeof(Movimiento));
  if(elemento==NULL)
    {
      return -1;
    }
  elemento->i=i;
  elemento->j=j;
  elemento->color=color;
  elemento->siguiente=NULL;
  if(raiz==NULL)
    {
      elemento->num=1;
      raiz=elemento;
      return 0;
    }
  p=raiz;
  while(p->siguiente!=NULL)
    {
      p=p->siguiente;
    }
  p->siguiente=elemento;
  elemento->num=p->num+1;
  return 0;
}

/**
 *Esta función guarda la lista creada en un archivo 
 *Recibe el nombre del archivo 
 *Regresa 0 en caso de éxito
 *Regresa -1 en caso de error
 *@Mariana 
 *@Param char *NombreArchivo Nombre del archivo el cual da el usuario
 *@return int
 */
int GuardarLista(char *NombreArchivo)
{
  FILE *fd;
  PtrMovimiento p;
  if(raiz==NULL)
    {
      return -1;
    }
  fd=fopen(NombreArchivo, "wt");
  if(fd==NULL)
    {
      return -2;
    }
  p=raiz;
  while(p)
    {
      fprintf(fd, "%d,%d,%d,%c\n", p->num, p->i, p->j, p->color);
      p=p->siguiente;
    }
  fclose(fd);
  return 0;
}

/**
 *Esta función elimina la lista 
 *No recibe ni regresa nada
 *@Mariana 
 */
void EliminarLista()
{
  PtrMovimiento p, q;
  p=raiz;
  while(p)
    {
      q=p->siguiente;
      free(p);
      p=q;
    }
  raiz=NULL;
}

/**
 *Esta función lee la lista de un archivo 
 *Recibe el nombre del archivo que se desea leer 
 *Regresa el total de jugadas leídas en caso de éxito
 *Regresa -1 en caso de error
 *@Mariana 
 *@Param char *NombreArchivo Nombre del archivo el cual da el usuario
 *@return int
 */
int LeerLista(char *NombreArchivo)
{
  FILE *fd;
  int status; //
  int num, i, j;
  char color;
  EliminarLista();
  fd=fopen(NombreArchivo, "rt");
  if(fd==NULL)
    {
      return -1;
    }
  num=0;
  while((status=fscanf(fd, "%d,%d,%d,%c\n", &num, &i, &j, &color))==4)
    {
      AgregarMov(i, j, color);
    }
  fclose(fd);
  return num;
}

/**
 *Esta función trunca la lista, es decir si el usuario lee una jugada pasada, y desea parar en cierto
 *movimiento, sin que se haya terminado la lista, se queda donde el usuario desea y borra el restante
 *de la lista.
 *Recibe el número de jugada en el que se desea parar
 *Y no regresa ningún valor
 *@Mariana 
 *@Param int num Número de jugada a parar
 */
void TruncarLista(int num)
{
  PtrMovimiento p, q;
  p=raiz;
  while(p)
    {
      q=p->siguiente;
      if (q && (q->num >= num))
	p->siguiente=NULL;
      if (p->num >= num)
	{
	  if (p == raiz)
	    raiz = NULL;
	  free(p);
	}
      p=q;
    }
}
