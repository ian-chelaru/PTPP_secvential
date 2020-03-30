#include <stdio.h>
#include <stdlib.h>
#include <chrono>

using namespace std;


int main()
{
	FILE *f = fopen("matrices/A10.txt", "r");
	FILE *g = fopen("matrices/B10.txt", "r");
	int n, m;
	fscanf(f, "%d", &n);
	fscanf(g, "%d", &m);

	if (n != m)
	{
		printf("The matrices should have the same size");
		return 0;
	}

	int *matA = (int*)malloc(n * n * sizeof(int));
	int *matB = (int*)malloc(n * n * sizeof(int));
	int *matC = (int*)malloc(n * n * sizeof(int));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fscanf(f, "%d", &matA[i * n + j]);
			fscanf(g, "%d", &matB[i * n + j]);
		}
	}

	fclose(f);
	fclose(g);

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int pos = i * n + j;
			matC[pos] = 0;
			for (int k = 0; k < n; k++)
			{
				matC[pos] += matA[i * n + k] * matB[k * n + j];
			}
		}
	}

	auto end = chrono::high_resolution_clock::now();

	double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-6;
	printf("Execution time: %lf miliseconds", time_taken);

	FILE *h = fopen("matrices/C10.txt", "w");

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fprintf(h, "%d ", matC[i * n + j]);
		}
		fprintf(h, "\n");
	}
	
	fclose(h);

	getchar();
	return 0;
}