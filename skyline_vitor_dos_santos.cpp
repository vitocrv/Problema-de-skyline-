#include <iostream>
#include <stdio.h>
using namespace std;

struct Predios 
{
	//coordenada 'x1' lado esquerdo
	int x1;

	//altura
	int y;

	//coordenada 'x2' lado direito
	int x2;
};

//Traça a linha no horizonte.
class Linhas 
{
	int x1;
	int y;

public:
	Linhas(int l = 0, int h = 0)
	{
		x1 = l;
		y = h;
	}
	friend class SkyLine;
};

//Classe para representar a saida da matriz
class SkyLine 
{
	Linhas* coordenadas;

	//Variavel da matriz de linhas
	int capacidade;

	//Numero de linhas na matriz
	int z;

public:
	~SkyLine() { delete[] coordenadas; }
	int count() { return z; }

	//Uma funcao para mesclar um horizonte com o outro
	SkyLine* Merge(SkyLine* outro);

	SkyLine(int cap)
	{
		capacidade = cap;
		coordenadas = new Linhas[cap];
		z = 0;
	}

	//Criei uma funcao para adicionar as linhas para matriz
	void acrescentar(Linhas* st)
	{
		
		//If´s para verificar se existem linhas repetidas. 
		if (z > 0 && coordenadas[z - 1].y == st-> y) //Verifica se ha alturas repetidas
			return;
		if (z > 0 && coordenadas[z - 1].x1 == st-> x1) //Verifica se alguma linha a esquerda repetida.
		{
			coordenadas[z - 1].y = max(coordenadas[z - 1].y, st->y);
			return;
		}

		coordenadas[z] = *st;
		z++;
	}

	//Uma funcao 'void' para imprimir as coordenadas do skyline.
	void imprimir()
	{
		for (int i = 0; i < z; i++) 
			printf("(%d, %d)\n", coordenadas[i].x1, coordenadas[i].y); //saida de dados das coordenadas
	}
};


SkyLine* acheskyline(Predios coordenadas[], int l, int h)
{
	if (l == h) {
		SkyLine* res = new SkyLine(2);
		res->acrescentar(
			new Linhas(
				coordenadas[l].x1, coordenadas[l].y));
		res->acrescentar(
			new Linhas(
				coordenadas[l].x2, 0));
		return res;
	}

	int meio = (l + h) / 2;

	//funcao criada para mesclar os resultados de: 'x1' e 'y'.
	SkyLine* sl = acheskyline
	(coordenadas, l, meio);

	SkyLine* sr = acheskyline
	(coordenadas, meio + 1, h);

	SkyLine* res = sl->Merge(sr);

	
	delete sl;
	delete sr;

	return res;
}


SkyLine* SkyLine::Merge(SkyLine* outro)
{
	SkyLine* res = new SkyLine(
		this->z + outro->z);

	//Variaveis para armazenar a altura de dois horizontes = "skylines"
	int h1 = 0, h2 = 0;

	//Indices de linhas nos horizontes
	int i = 0, j = 0;
	while (i < this->z && j < outro->z) 
	{
		//Compara as coordenadas 'x1' e 'y' e imprime o menor resultado
		if (this->coordenadas[i].x1 < outro->coordenadas[j].x1) {
			int x1 = this->coordenadas[i].x1;
			h1 = this->coordenadas[i].y;

			int maxh = max(h1, h2);

			res->acrescentar(new Linhas(x1, maxh));
			i++;
		}
		else 
		{
			int x2 = outro->coordenadas[j].x1;
			h2 = outro->coordenadas[j].y;
			int maxh = max(h1, h2);
			res->acrescentar(new Linhas(x2, maxh));
			j++;
		}
	}

	//Enquando sobrar linhas no horizonte...
	while (i < this->z) 
	{
		res->acrescentar(&coordenadas[i]);
		i++;
	}

	while (j < outro->z) 
	{
		res->acrescentar(&outro->coordenadas[j]);
		j++;
	}
	return res;
}

	
//finalmente a funçao main para leitura de dados.
int main()
{
	int n, x1, x2, y;

	printf("Qtd de predios: "); //Ler a qtd de predios digitada pelo usuario
	scanf("%d", &n);

	Predios coordenadas[n] = {};

	for (int i = 0; i < n; i++) //Leitura das coordenadas dos 'n' predios lidos anteriormente.
	{
		for (int k = 0; i < n; i++)
		{
			printf("\nPredio %d: ", i+1);
			printf("X1: ");
			scanf("%d", &coordenadas[i].x1);

			printf("Y: ");
			scanf("%d", &coordenadas[i].y);

			printf("X2: ");
			scanf("%d", &coordenadas[i].x2);
		}
		
	}

	int z = sizeof(coordenadas) / sizeof(coordenadas[0]);

	SkyLine* ptr = acheskyline(coordenadas, 0, z - 1);
	puts("\nCoordenadas:");
	ptr->imprimir();
}
