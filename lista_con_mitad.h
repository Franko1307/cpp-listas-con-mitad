#pragma once
#include <iostream>

enum DONDE { VACIO,INICIO,MITAD,FINAL };
template <typename _InputIter> struct caja {
  _InputIter var;
  caja<_InputIter> *siguiente;
  caja<_InputIter> *anterior;
};
template <typename _InputIter> class lista_con_mitad {
private:
  DONDE donde;
  bool encontrado;
  bool mayor;
  size_t menores;
  size_t mayores;
  caja<_InputIter> *principio;
  caja<_InputIter> *anterior;
  caja<_InputIter> *mitad;
  caja<_InputIter> *final;
  void buscar(_InputIter);
public:
  lista_con_mitad(): donde(INICIO),encontrado(false),mayor(false),menores(0),mayores(0)
                     ,principio(NULL),anterior(NULL),mitad(NULL),final(NULL){};
  ~lista_con_mitad();
  bool agregar(_InputIter);
  bool quitar(_InputIter);
  void pintar_1();
  void pintar_2();
};
template <typename _InputIter> lista_con_mitad<_InputIter>::~lista_con_mitad() {
  caja<_InputIter> *iterador;
  while (principio) {
    iterador = principio;
    principio = iterador->siguiente;
    delete iterador;
  }
  donde = VACIO;
  encontrado = false;
  mayor = false;
  menores = 0;
  mayores = 0;
  principio = NULL;
  anterior = NULL;
  mitad = NULL;
  final = NULL;
}
template <typename _InputIter> void lista_con_mitad<_InputIter>::buscar(_InputIter var) {
  if (!principio) {
    encontrado = false;
    donde = VACIO;
    anterior = NULL;
    mitad = NULL;
    return;
  }

  caja<_InputIter> *iterador;

  if (var < mitad->var) iterador = principio;
  else iterador = mitad;

  anterior = iterador->anterior;
  while (iterador) {
    if (iterador->var < var) {
      anterior = iterador;
      iterador = iterador->siguiente;
    } else if (iterador->var == var) {
      encontrado = true;
      return;
    } else {
      encontrado = false;
      if (principio == iterador) donde = INICIO;
      else donde = MITAD;
      return;
    }
  }
  encontrado = false;
  donde = FINAL;
}
template <typename _InputIter> bool lista_con_mitad<_InputIter>::agregar(_InputIter var) {

  buscar(var);

  if (encontrado) return false;

  caja<_InputIter> *iterador = new caja<_InputIter>;
  iterador->var = var;

  if (donde == MITAD) {
    iterador->siguiente = anterior->siguiente;
    iterador->anterior = anterior;
    anterior->siguiente = iterador;
    iterador->siguiente->anterior = iterador;
  } else if (donde == FINAL) {
    iterador->siguiente = NULL;
    iterador->anterior = final;
    final->siguiente = iterador;
    final = iterador;
  } else if (donde == INICIO){
    iterador->anterior = NULL;
    iterador->siguiente = principio;
    principio->anterior = iterador;
    principio = iterador;
  } else {
    iterador->siguiente = NULL;
    iterador->anterior = NULL;
    principio = iterador;
    final = iterador;
    mitad = iterador;
  }

  if (iterador->var >= mitad->var) mayores++;
  else menores++;
  if (menores+2 <= mayores) {
    mitad = mitad->siguiente;
    menores++;
    mayores--;
  } else if (menores>mayores) {
    mitad = mitad->anterior;
    menores--;
    mayores++;
  }
  
  return true;
}
template <typename _InputIter> void lista_con_mitad<_InputIter>::pintar_1() {
  caja<_InputIter> *iterador = principio;
  std::cout << "[ ";
  while (iterador) {
    std::cout << iterador->var << ",";
    iterador = iterador->siguiente;
  }
  std::cout << "\b ]";
}
template <typename _InputIter> void lista_con_mitad<_InputIter>::pintar_2() {
  caja<_InputIter> *iterador = final;
  std::cout << "[ ";
  while (iterador) {
    std::cout << iterador->var << ",";
    iterador = iterador->anterior;
  }
  std::cout << "\b ]";
}
