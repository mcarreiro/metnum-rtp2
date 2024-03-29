#include "pagerank.h"
#include <utility>      // std::pair
#include <iostream>     // std::cout
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;
//links: en la pos "i" tiene un vector con sus links "j" de salida
PageRank::PageRank(double c, double tolerancia, int dim, vector<vector<int> >& links) : c(c), tolerancia(tolerancia){

	v = * new vector<double>(dim);

	for(int i = 0; i < dim; i++){
		v.at(i) = 1.00/(double)dim;
	}


	matriz = * new DOK(dim);
	desconectados = * new vector<int>();
	for(unsigned int i = 0; i < links.size(); i++){

		vector<int> salidas = links[i];
		int cantSalidas = salidas.size();

		if(cantSalidas != 0){
			for(int j = 0; j < cantSalidas; j++){
				int s = salidas[j];

				matriz.definir(s, i, 1.00/cantSalidas ); // En la columna i se define a los s que sale.
			}			
		}else{
			desconectados.push_back(i);
		}
	}

}

double PageRank::manhattan(vector<double>& x, vector<double>&y){
	double res = 0, parcial = 0;
	for(unsigned int i = 0; i < x.size(); i++){
		parcial = abs(x[i] - y[i]);
		if(parcial < 0.00000000000000001) parcial = 0;
		res += parcial;
	}
	return res;
}

void PageRank::ranking(int max){

	//M = (1-c)*A + c * B con B = 1/n * matriz de unos
	//Mv = (1-c) * Av + c*Bv 

	//P1 = P + d
	//P2 = cP1 + (1-c)E
	//P2v = c(P+D)v + (1-c)Ev
	//P2v = cPv + cDv + (1-c)Ev
    int tam = v.size();
    int it = 0;
    double norma;
	while(it == 0 || (norma > tolerancia && it < max)  ){


        vector<double> w = v;
        
        double sumaDesconectados = 0;
        int nodoDesc;
        for (int i = 0; i < desconectados.size(); i++){
        	nodoDesc = desconectados[i];
           	sumaDesconectados+= v[nodoDesc]/tam;
		}
        v = *matriz.porVector(v);
        
        for (int i = 0; i < tam; i++){
            v[i] = c*(v[i]+sumaDesconectados)+((1-c)/(double)tam)  ;
			//cout << v[i] << ";";
		}
		norma = this->manhattan(v,w);
		//cout << it << " "<< norma << "\n";
		it++;
	}
}
