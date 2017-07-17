/* Wilkel Giovanni CI:2242883
 * Geraldine Herrera CI:20981655
 */
#ifndef ArbolN_h
#define ArbolN_h
#include "NodoN.h"
#include <cmath>
#include <string>
#include <cctype>
#include <list>
#include <queue>

template <class T>
class PadreHijos
{
	private:
		T padre;
		list<T> hijos;
	public:
		PadreHijos(): padre(T()){}
		T get_padre(){return padre;}
		list<T> get_hijos(){return hijos;}
		void mod_padre(T p){ padre = p;}
		void mod_hijos(list<T> L){ hijos = L;}
};
//======================================================================
template <class T>
class ArbolN
{	
		//atributos:
		private:
			NodoN<T> *nodoRaiz;
		//metodos:
		private:
			//Recorridos:
			void PostOrden(NodoN<T>* arbn);
			void PreOrden(NodoN<T>* arbn);
			void InOrden(NodoN<T>* arbn);
			void c_preorden(NodoN<T>* arbn, list<T> &l);
			void c_postorden(NodoN<T>* arbn, list<T> &l);
			void c_inorden(NodoN<T>* p, list<T> &l);
			//Metodos de Modificacion:
			void vaciar(NodoN<T> *p);
			NodoN<T>* copiar(NodoN<T> *p);
			//Metodos de Inspeccion:
			void ObtPeso(NodoN<T> *p, int &peso);
			void Altura(NodoN<T> *p, int &alt);
			void Encontrar_padre(NodoN<T> *p, T e, list<T> l);			//busca el padre e inserta los hijos
			void buscarPrimos(NodoN<T>* padre, list<PadreHijos<T> > &L);//busca los primos que estan a la derecha de el
			void buscar(NodoN<T> *p, NodoN<T> *padre, list<PadreHijos<T> > &L); //busca los primos que estan a la izquierda
			void primos(NodoN<T> *p, NodoN<T> *padre, T e, list<PadreHijos<T> > &L);
			
		public:								
			//Constructores:
			ArbolN<T>():nodoRaiz(NULL){}
			ArbolN(const ArbolN<T> &a);	
			ArbolN(T e);
			ArbolN(T e, list< ArbolN<T> > &A);
			ArbolN(T e, list<T> l);
			//Metodos de Inspeccion:
			bool esNulo(){return(nodoRaiz == NULL);}
			T raiz(){return(nodoRaiz -> get_dato());}
			NodoN<T>* obt_Raiz() const{return nodoRaiz;}
			list< ArbolN<T> > hijos();
			bool esHoja(){return(nodoRaiz -> get_hder() == NULL && nodoRaiz -> get_hizq()==NULL);}
			int Obt_Peso();
			int Altura();
			//Recorridos:
			void PostOrden(){PostOrden(nodoRaiz);}
			void PreOrden(){PreOrden(nodoRaiz);}
			void InOrden(){InOrden(nodoRaiz);}
			void Niveles();
			list<T> r_preorden();
			list<T> r_inorden();
			list<T> r_postorden();
			list<T> Cargar_Niveles();
			//Metodos de Modificacion:
			void copiar(ArbolN &A){nodoRaiz = copiar(A.nodoRaiz);}
			void insertar(ArbolN<T> &A);
			void Insertar(T e, list<T> Child);							//Inserta los hijos del padre
			void eliminar(int pos);
			list<PadreHijos<T> > primos(T e);																			
			void vaciar();
			//Sobrecarga de operadores:
			void operator=(const ArbolN<T> &a);
			//Destructor: 
			~ArbolN();
};
/******************************************/
/********Constructores de la Clase:*******/
/*****************************************/
template <class T>
ArbolN<T>::ArbolN(const ArbolN<T> &a)
{		
	*this = a;
}
//======================================================================
template <class T>
ArbolN<T>::ArbolN(T e)
{
	nodoRaiz = new NodoN<T>(e,NULL,NULL);
}
//======================================================================
template <class T>
ArbolN<T>::ArbolN(T e, list< ArbolN<T> > &l)
{
	NodoN<T> *aux;
	nodoRaiz = new NodoN<T>(e,NULL,NULL);
	if(!l.empty())
	{
			nodoRaiz -> set_hizq(copiar(l.front().nodoRaiz));
			l.pop_front();
			aux = nodoRaiz -> get_hizq();
			while(!l.empty())
			{
					aux -> set_hder(copiar(l.front().nodoRaiz));
					l.pop_front();
					aux = aux -> get_hder();
			}
	}
	
}
//======================================================================
template <class T>
ArbolN<T>::ArbolN(T e, list<T> l)
{
	NodoN<T> *aux;

    nodoRaiz = new NodoN<T>(e);
    if(!l.empty())
	{
		aux = new NodoN<T>(l.front());
        nodoRaiz -> set_hizq(aux);
        l.pop_front();
        while(!l.empty())
        {
			aux -> set_hder(new NodoN<T>(l.front()));
			l.pop_front();
			aux = aux -> get_hder();
        }
    }
}
/*****************************/
/**********Recorridos:********/ 
/*****************************/
template <class T>
void ArbolN<T>::PostOrden(NodoN<T>* arbn)
{
		if(arbn != NULL)
		{
			PostOrden(arbn -> get_hizq());
			PostOrden(arbn -> get_hder());
			cout << arbn -> get_dato()<< " ";
		}
}
//======================================================================
template <class T>
void ArbolN<T>::c_postorden(NodoN<T>* arbn, list<T> &l)
{
		if(arbn != NULL)
		{
			c_postorden(arbn -> get_hizq(),l);
			c_postorden(arbn -> get_hder(),l);
			l.push_back(arbn -> get_dato());
		}
}
//======================================================================
template <class T>
list<T> ArbolN<T>::r_postorden()
{
		list<T> l;
		c_postorden(nodoRaiz,l);
		return(l);
}
//======================================================================
template <class T>
void ArbolN<T>::PreOrden(NodoN<T>* arbn)
{
		if(arbn != NULL)
		{
			cout << arbn -> get_dato()<< " ";
			PreOrden(arbn -> get_hizq());
			PreOrden(arbn -> get_hder());
		}
}
//======================================================================
template <class T>
void ArbolN<T>::c_preorden(NodoN<T>* arbn, list<T> &l)
{
		if(arbn != NULL)
		{
			l.push_back(arbn -> get_dato());
			c_preorden(arbn -> get_hizq(),l);
			c_preorden(arbn -> get_hder(),l);
		}
}
//======================================================================
template <class T>
list<T> ArbolN<T>::r_preorden()
{
		list<T> l;
		c_preorden(nodoRaiz,l);
		return(l);
}
//======================================================================
template <class T>
void ArbolN<T>::InOrden(NodoN<T>* p)
{
	NodoN<T> *aux;
	if(p!=NULL)
	{
		InOrden(p -> get_hizq());
		cout << p -> get_dato() << " ";
	  if(p -> get_hizq() != NULL)
	  {
		aux = p -> get_hizq() -> get_hder();
		while(aux != NULL)
		{
		    InOrden(aux);
			aux = aux -> get_hder();
		}
	  }	
	}
}
//======================================================================
template <class T>
void ArbolN<T>::c_inorden(NodoN<T>* p, list<T> &l)
{
	NodoN<T> *aux;
	if(p!=NULL)
	{
		c_inorden(p -> get_hizq(),l);
		l.push_back(p -> get_dato());
	  if(p -> get_hizq() != NULL)
	  {
		aux = p -> get_hizq() -> get_hder();
		while(aux != NULL)
		{
		    c_inorden(aux,l);
			aux = aux -> get_hder();
		}
	  }	
	}
}
//======================================================================
template <class T>
list<T> ArbolN<T>::r_inorden()
{
		list<T> l;
		c_inorden(nodoRaiz,l);
		return(l);
}
//======================================================================
template <class T>
list<T> ArbolN<T>::Cargar_Niveles()
{
		NodoN<T> *p,*x;
		queue< NodoN<T>* > C;
		list<T> procesar;
		list< NodoN<T>* > h;
		
		if(nodoRaiz != NULL)
		{
			p = nodoRaiz;
			procesar.push_back(p -> get_dato());
			if(p -> get_hizq()!=NULL)
			{
				x = p -> get_hizq();	
				h.push_back(x);
			}
			while(x != NULL)
			{
			  if(x -> get_hder() != NULL)	
				h.push_back(x -> get_hder());
			  x = x -> get_hder();
			}
			
			while(!h.empty())
			{
				C.push(h.front());
				p = h.front();
				if(p -> get_hizq() != NULL)
				{
					x = p -> get_hizq();	
					h.push_back(x);
				}
				while(x!=NULL)
				{
				   if(x -> get_hder() != NULL)		
					h.push_back(x -> get_hder());
				   x = x -> get_hder();
				}
				h.pop_front();		
			}
				
			while(!C.empty())
			{	
				procesar.push_back(C.front() -> get_dato());
				C.pop();
			}	
		}
		return(procesar);		
}
//======================================================================
template <class T>
void ArbolN<T>::Niveles()
{
	list<T> p;
	p = Cargar_Niveles();
	 while(!p.empty())
		{
			cout << p.front() << " ";
			p.pop_front();	
		}
		cout<<endl;
}		
/*****************************/
/***Métodos de Inspección:****/
/*****************************/
template <class T>
list< ArbolN<T> > ArbolN<T>::hijos()
{
	NodoN<T> *aux;
	ArbolN<T> A;
	list< ArbolN<T> > l;

	aux = nodoRaiz -> get_hizq();
	
	while(aux != NULL)
	{
		A.nodoRaiz = copiar(aux);
		l.push_back(A);
		aux = aux -> get_hder();
	}
	return(l);
}
//======================================================================
template <class T>
void ArbolN<T>::ObtPeso(NodoN<T> *p, int &peso)
{
		if(p != NULL)
		{
			peso++;
			ObtPeso(p -> get_hizq(),peso);
			ObtPeso(p -> get_hder(),peso);	
		}
}
//======================================================================
template <class T>
int ArbolN<T>::Obt_Peso()
{
	int peso=0;
	ObtPeso(nodoRaiz,peso);
	return(peso);	
}
//======================================================================
template <class T>
void ArbolN<T>::Altura(NodoN<T> *p, int &alt)
{
	int ai=0,ad=0;
	if(p == NULL)
	{
		alt=-1;
	}
	else
	{
		if(p -> get_hizq() == NULL && p -> get_hder() == NULL)
		{
			alt=0;	
		}
		else
		{
			Altura(p -> get_hizq(),ai);
			while(p != NULL)
			{
				if(p -> get_hder() != NULL)
					Altura(p -> get_hder(),ad);
				p = p -> get_hder();	
			}	
			alt = max(ai,ad)+1;
		}	
	}
}
//======================================================================
template <class T>
int ArbolN<T>::Altura()
{
    int alt;
    NodoN<T> *p;
    p=nodoRaiz;
    if(p == NULL)
    {
	  alt=-1;
	}
	else
	{
		if(p -> get_hizq() == NULL && p -> get_hder() == NULL)
		{
			alt=0;	
		}
		else
		{
		   Altura(p -> get_hizq(),alt);
		   alt++;
		}	
	}
	return(alt);
}
/*****************************/
/****Métodos Modificadores:***/
/*****************************/
template <class T>
void ArbolN<T>::vaciar()
{
	vaciar(nodoRaiz);
	nodoRaiz = NULL;
}
//======================================================================
template <class T>
void ArbolN<T>::vaciar(NodoN<T> *p)
{
	  if(p != NULL)
	  {
			vaciar(p -> get_hizq());
			vaciar(p -> get_hder());
			p = NULL;
	  }	
}
//======================================================================
template <class T>
void ArbolN<T>::insertar(ArbolN<T> &A)
{
	NodoN<T> *nuevo;
	//Caso 1 
	if(nodoRaiz -> get_hizq()==NULL)
	{
		nodoRaiz -> set_hizq((copiar(A.nodoRaiz)));
	}
	else
	{
		//Caso 2
		nuevo = nodoRaiz -> get_hizq();
		while(nuevo -> get_hder()!=NULL)
		{
				nuevo = nuevo -> get_hder();
		}
		nuevo -> set_hder((copiar(A.nodoRaiz)));
	}
}
//======================================================================
template <class T>
void ArbolN<T>::Encontrar_padre(NodoN<T> *p, T e, list<T> l)
{
	NodoN<T> *aux;
	if(p != NULL)
	{
		if(p -> get_dato() == e)
		{
			if(!l.empty())
			{
				aux = new NodoN<T>(l.front());
				p -> set_hizq(aux);
				l.pop_front();
				while(!l.empty())
				{
					aux -> set_hder(new NodoN<T>(l.front()));
					l.pop_front();
					aux = aux -> get_hder();
				}
			}
		}
		else
		{
			Encontrar_padre(p -> get_hizq(),e,l);
			Encontrar_padre(p -> get_hder(),e,l);
		}
	}
}
//======================================================================
template <class T>
void ArbolN<T>::Insertar(T e, list<T> Child)
{
	NodoN<T> *aux;
	if(nodoRaiz == NULL)
	{
		nodoRaiz = new NodoN<T>(e);
		if(!Child.empty())
		{
			nodoRaiz -> set_hizq(new NodoN<T>(Child.front()));
			Child.pop_front();
			aux = nodoRaiz -> get_hizq();
			while(!Child.empty())
			{
				aux -> set_hder(new NodoN<T>(Child.front()));
				Child.pop_front();
				aux = aux -> get_hder();
			}
		}
	}
	else
	{
		Encontrar_padre(nodoRaiz,e,Child);
	}
}
//======================================================================
template<class T>
void ArbolN<T>::eliminar(int pos)
{
	NodoN<T> *aux,*aux2;
	int i;
	
	if(nodoRaiz != NULL && pos != 0)
	{
		if(pos == 1)
		{
			aux = nodoRaiz -> get_hizq();
			nodoRaiz -> set_hizq(aux -> get_hder());
			aux -> set_hder(NULL);
			vaciar(aux);
		}
		else
		{
			aux = nodoRaiz -> get_hizq();
			for(i = 2; i <= pos; i++)
			{
				aux2 = aux;
				aux = aux -> get_hder();	
			}
		  if(aux != NULL)
		  {	
			aux2 -> set_hder(aux -> set_hder());
			aux -> set_hder(NULL);
			vaciar(aux);
		  }
		  else
		  {
				cerr << "Se intento eliminar un SubArbol Inexistente" << endl;
		  }
		}
	 }
	 else
	 {
		 cerr << "Se intento eliminar un SubArbol Inexistente o el Arbol esta vacio" << endl;
	 }	
}
//======================================================================
template <class T>
void ArbolN<T>::buscarPrimos(NodoN<T>* padre, list<PadreHijos<T> > &L)
{
	PadreHijos<T> P;
	list<T> h;
	NodoN<T> *aux;
	
	if(padre != NULL)
	{
		padre = padre -> get_hder();
		while(padre != NULL)
		{
			aux = padre -> get_hizq();
			while(aux != NULL)
			{
				h.push_back(aux -> get_dato());
				aux = aux -> get_hder();
			}
			if(!h.empty())
			{
				P.mod_padre(padre -> get_dato());
				P.mod_hijos(h);
				L.push_back(P);
				h.clear();
			}
			padre = padre -> get_hder();
		}
	}
}
//======================================================================
template <class T>
void ArbolN<T>::buscar(NodoN<T> *p, NodoN<T> *padre, list<PadreHijos<T> > &L)
{
	ArbolN<T> A,B;
	list<ArbolN<T> > H,aux; 
	list<T> child;
	PadreHijos<T> P;
	NodoN<T> *aux1;
	int i=0;
	bool band = false;
	if(p != NULL)
	{

		A.nodoRaiz = p;
		H = A.hijos();
		aux = H;
		while(!aux.empty() && !band)
		{
			if(aux.front().raiz() == padre -> get_dato())
			{
				band = true;;
			}
			aux.pop_front();
			i++;
		}
		if(band)
		{
			for (int j = 0; j < i-1; j++)
			{
				B = H.front();
				aux1 = B.nodoRaiz-> get_hizq();
				while(aux1 != NULL)
				{
					child.push_back(aux1 -> get_dato());
					aux1 = aux1 -> get_hder();
				}
				if(!child.empty())
				{
					P.mod_padre(H.front().raiz());
					P.mod_hijos(child);
					L.push_back(P);
					child.clear();
					H.pop_front();
				}
			}
		}
		else
		{
			buscar(p -> get_hizq(),padre,L);
			buscar(p -> get_hder(),padre,L);
		}
	}
}
//======================================================================
template <class T>
void ArbolN<T>::primos(NodoN<T> *p,NodoN<T> *padre, T e, list<PadreHijos<T> > &L)
{
	if(p != NULL)
	{
		if(p -> get_dato() == e)
		{
			buscarPrimos(padre,L);

			if(L.empty())
			{
				buscar(nodoRaiz,padre,L);
			}
		}
		else
		{
			primos(p -> get_hizq(),p ,e,L);
			primos(p -> get_hder(),padre,e,L);
		}
	}
}
//======================================================================
template <class T>
list<PadreHijos<T> > ArbolN<T>::primos(T e)
{
	list<PadreHijos<T> > L;
	NodoN<T> *padre;
	if(nodoRaiz != NULL && nodoRaiz -> get_hizq() != NULL)
	{
		padre = nodoRaiz;
		primos(nodoRaiz -> get_hizq(),padre,e,L);
	}
	return L;
}
//======================================================================
template<class T>
NodoN<T>* ArbolN<T>::copiar(NodoN<T> *p)
{
	NodoN<T> *nuevo;
	if(p != NULL)
	{
			nuevo = new NodoN<T>(p -> get_dato());
			nuevo -> set_hizq(copiar(p -> get_hizq()));
			nuevo -> set_hder(copiar(p -> get_hder()));
			return(nuevo);
	}
	else
	{
			return(NULL);
	}
}
/*****************************/
/**Sobrecarga de Operadores:**/
/*****************************/
template <class T>
void ArbolN<T>::operator=(const ArbolN<T> &a)
{	
	if(this != &a)
	{
		nodoRaiz = this -> copiar(a.nodoRaiz);
	}	
}
/*********************************/
/**Único Destructor de la Clase:**/
/*********************************/		
template <class T>
ArbolN<T>::~ArbolN()
{
	vaciar();
}
#endif
