#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define INFINITO 999999999
#define MAXN 10100
using namespace std;

typedef pair<int, int> par;   
//Primm vars globais                        
int n, m;                       
int distancia[MAXN];            
int processado[MAXN];          
vector<par> vizinhos[MAXN];     
//---------------------
//Dijikstra vars globais
int destino, origem, vertices;
int custo, *custos = NULL;
///////////////###############  Primm:  ####################### ////////////////////////

int Prim(){
	
	for(int i = 2;i <= n;i++) distancia[i] = INFINITO; 
	distancia[1] = 0;                                   
	
	priority_queue< par, vector<par>, greater<par> > fila;  
	fila.push( par(distancia[1], 1) );                      
	
	int nodo = 0;
	while(nodo>=0){  
		
		nodo = -1;
		
		// seleciona vértice mais próxima
		while(!fila.empty()){
			
			int atual = fila.top().second;  
			fila.pop();					 
			
			if(!processado[atual]){  
				nodo = atual;
				break;				 
			}
		}
		
		if(nodo == -1) break;  
		
		processado[nodo] = true;  
		
		// atualizar as distâncias
		for(int i = 0;i < (int)vizinhos[nodo].size();i++){
			
			int dist  = vizinhos[nodo][i].first;  
			int atual = vizinhos[nodo][i].second;
 
			// se o vértice atual não foi processado ainda
			if( distancia[atual] > dist && !processado[atual]){   
				distancia[atual] = dist;                          
				fila.push( par(distancia[atual], atual) );        
			}
		}
	}
	
	int custo_arvore = 0;
	for(int i = 1;i <= n;i++) custo_arvore += distancia[i];
	
	return custo_arvore;
}


///////////////###############  Dijikstra:  ####################### ////////////////////////
void dijkstra(int vertices,int origem,int destino,int *custos)
{
    int i,v, cont = 0;
    int *ant, *tmp;
    int *z;      
    double min;
    double dist[vertices];  

    ant = (int *)calloc (vertices, sizeof(int));
    tmp = (int *)calloc (vertices, sizeof(int));
    z = (int *)calloc (vertices, sizeof(int));
  
    for (i = 0; i < vertices; i++)
    {
        if (custos[(origem - 1) * vertices + i] !=- 1)
        {
            ant[i] = origem - 1;
            dist[i] = custos[(origem-1)*vertices+i];
        }
        else
        {
            ant[i]= -1;
            dist[i] = INFINITO;
        }
        z[i]=0;
    }
    z[origem-1] = 1;
    dist[origem-1] = 0;

     
    do
    {
        // Encontra vertice que deve entrar em z
        min = INFINITO;
        for (i=0; i<vertices; i++)
            if (!z[i])
                if (dist[i]>=0 && dist[i]<min)
                {
                    min=dist[i];
                    v=i;
                }

        //Calcula distancias dos novos vizinhos de z
        if (min != INFINITO && v != destino - 1)
        {
            z[v] = 1;
            for (i = 0; i < vertices; i++)
                if (!z[i])
                {
                    if (custos[v*vertices+i] != -1 && dist[v] + custos[v*vertices+i] < dist[i])
                    {
                        dist[i] = dist[v] + custos[v*vertices+i];
                        ant[i] =v;
                    }
                }
        }
    }
    while (v != destino - 1 && min != INFINITO);

    // Resultado da busca 
    cout << "De "<<origem<< "  para "<< destino << ":   ";
    if (min == INFINITO)
    {
        cout << "Nao existe"<<endl;
		cout << "Custo: "<<endl;
    }
    else
    {
        i = destino;
        i = ant[i-1];
        while (i != -1)
        {
            tmp[cont] = i+1;
            cont++;
            i = ant[i];
        }

        for (i = cont; i > 0 ; i--)
        {
            cout << tmp[i-1] << "->" ;
        }
        cout << destino << endl;
        cout << "Custo:" << (int) dist[destino-1] << endl;
    }
}
 

void add(void) //entrar com o grafo
{
    int i, j, s, arestas;  
	vertices = 0;
    while (vertices < 2 )
    {
    	cout << "Digite numero de vertives e arestas: "<<endl;
        cin >> vertices >> arestas;
    }
	int parar = arestas;
    if (!custos)
        free(custos);
    custos = (int *) malloc(sizeof(int)*vertices*vertices);
    for (i = 0; i <= vertices * vertices; i++)
        custos[i] = -1;
    cout << "Digite <Origem Destino Custo>, usando numeros inteiros positivos"<<endl;
	do
    {
        do
        {
            cout << "Origem Destino Custo:"<<endl;
            cin >> origem >> destino >> custo;
            parar--;
            if (parar == 0) break;
        }
       while (origem < 0 || origem > vertices || destino<1 || destino>vertices ||destino == origem || custo<0 );

        if (parar == 0) break;
            	
		if (origem) 
			custos[(origem-1) * vertices + destino - 1] = custo;    
    }
    while (origem);
}
 
int main(int argc, char **argv)
{
    int i, j, op;
    do
    {
        system ("cls");
        cout<< "Digite:" <<endl;
		cout<<"\t 1 - Dijsktra\n"
               "\t 2 - Primm\n"
               "\t 3 - Sair do programa\n\n"<<endl;
       cin >> op;
        if (op == 1)
        {
        	add();
        	if ((vertices>0))
            {
            	cout << "digite nodo origem nodo destino"<<endl;
			    cin >> i >> j;
			    dijkstra(vertices, i,j, custos); 
		        system ("pause");
			}        	
		}
        if ((op == 2))
        {
        	cout << "Digite numero de vertives e arestas"<<endl;
			cin >> n >> m;
			
			for(int i = 1;i <= m;i++){
				
				int x, y, dist;
				cout << "vertice1 vertice2 distancia"<<endl;
				cin >> x >> y >> dist;
				
				vizinhos[x].push_back( par(dist, y) );
				vizinhos[y].push_back( par(dist, x) );
			}
			
			cout << "Custo do caminho  = " << Prim() << endl; 	
	        system ("pause");
		  
		  
		}
        if ((op != 1) && (op != 2) && (op != 3)) 
	    {
	    	cout << "digite uma opcao valida"<<endl;
	    	system ("pause");	
		}	
    }
    while (op != 3);
    return 0;
}
