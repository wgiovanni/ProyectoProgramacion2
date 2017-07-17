/* Wilkel Giovanni CI:2242883
 * Geraldine Herrera CI:20981655
 */
#include <iostream>
#include "ArbolN.h"

using namespace std;
//======================================================================
string Validacion(string cadena) //valida que el primer caracter sea en mayuscula
{
	char c;
	c = cadena[0];
	if(c >= 'a' && c <= 'z')
	{
		c -= 32;
		cadena[0] = c; 
	}
	return cadena;
}
//======================================================================
int main()
{
	string father,child,person;
	int n,i=1,j;
	list<string> Lchild,aux;
	ArbolN<string> A;
	list<PadreHijos<string> > R;
	
	
	cin >> father;
	father = Validacion(father);
	while(cin)
	{
		while(father != "***")
		{
			cin >> n;
			for (int i = 1; i <= n; i++)
			{
				cin >> child;
				child = Validacion(child);
				Lchild.push_back(child);
			}
			A.Insertar(father,Lchild);
			Lchild.clear();
			cin >> father;
			father = Validacion(father);
		}
		cin >> person;
		person = Validacion(person);
		R = A.primos(person);
		cout << "Caso #" << i << endl;
		if(!R.empty())
		{
			cout << "Los primos de " << person << " son:" << endl;
			while(!R.empty())
			{
				aux = R.front().get_hijos();
				j = aux.size();
				if(j == 1)
				{
					
					if(!aux.empty())
					{
						while(!aux.empty())
						{
							cout << aux.front() << " ";
							aux.pop_front();
						}
						cout << "(hijo(a) de " << R.front().get_padre() << ")." << endl;
					}
				}
				else
				{
					if(!aux.empty())
					{
						for (int k = 0; k < j-2; k++)
						{
							cout << aux.front() << ", ";
							aux.pop_front();
						}
						cout << aux.front() << " ";
						aux.pop_front();
						cout << "y " << aux.front() << " ";
						cout << "(hijos(as) de " << R.front().get_padre() << ")." << endl;
					}
				}
				R.pop_front();
			}
		}
		else
		{
			cout << person << " no tiene primos." << endl;
		}
		A.vaciar();
		Lchild.clear();
		cout << endl;
		cin >> father;
		i++;
	}
    return 0;
}
