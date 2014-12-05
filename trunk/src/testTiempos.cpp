#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <ctime>
#include "pagerank.cpp"
#include "hits.cpp"
#include "indeg.cpp"
#include "readFile.cpp"
#include <algorithm>
#include <ctime>
#include <time.h>
using namespace std;

int main() {
	clock_t start;
	double timedif;
	double timedifAnt = -1;
	for( int i = 10; i < 11000; i=i+200){
		vector<vector<int> > links(i);
		for( int j = 0; j < i; j++){
			srand(time(NULL));
			int cantSalidas = rand()% (i-4)+4;
			vector<int>  salidas(cantSalidas);
			for( int k = 0; k < cantSalidas; k++){
				srand(time(NULL));
				int nodo = rand()%i;
				salidas[k] = nodo;
			}
			links[j] = salidas;
		}
		start = clock();  
        Hits h(links);
		h.hubsYautoridades(0.001);
		timedif = ((double)clock() - start) / CLOCKS_PER_SEC;
		cout.precision(15);
		
			cout << i << " " << timedif << " ";

			timedifAnt = timedif;
			start = clock(); 
			PageRank pr(0.15, 0.001 , links.size(), links);
          		pr.ranking(1000);
			timedif = ((double)clock() - start) / CLOCKS_PER_SEC;
			cout << timedif << " ";

			start = clock();
			Indeg indeg (links);
			timedif = ((double)clock() - start) / CLOCKS_PER_SEC;
			cout << timedif << "\n";	
		
	}	
    return 0;
}
