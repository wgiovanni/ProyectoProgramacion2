/* Wilkel Giovanni CI:2242883
 * Geraldine Herrera CI:20981655
 */
#ifndef NODON_H
#define NODON_H
#include <iostream>
#include <ostream>

using namespace std;

template <class T>
class NodoN
{
        //atributos
        private:
                T dato;
                NodoN *hizq,*hder;

        //Metodos
        public:
               	//constructores
                NodoN():dato(T()),hizq(NULL),hder(NULL){} //Constructor
				NodoN(T e){ dato=e; hizq=NULL; hder=NULL;} //Constructor
                NodoN(const NodoN &n):dato(n.dato), hizq(n.hizq), hder(n.hder){}
				NodoN(T e, NodoN<T>* hijo, NodoN<T>* hermano):hizq(hijo),hder(hermano),dato(e){}//Con parametro
                //observadoras
                T get_dato() const {return dato;};
                NodoN* get_hizq() const {return hizq;};
                NodoN* get_hder() const {return hder;};
                //modificadoras
                void set_dato(const T &d) { dato=d; }//Modificador dato
                void set_hizq(NodoN* h_izquierdo) {this->hizq = h_izquierdo;} //Modificador de hijo izquierdo
                void set_hder(NodoN* h_derecho) {this->hder = h_derecho;} //Modificador de hermano derecho

           
};
#endif
