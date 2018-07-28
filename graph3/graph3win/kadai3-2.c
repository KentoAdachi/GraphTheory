#include<stdio.h>
#include<stdlib.h>
#include<float.h>

#define INF DBL_MAX
#define TRUE 1
#define FALSE 0

void prim(int **adjacent, double **dist, int num);

int main(int argc, char *args[]) {
	FILE *fp;
	int N;
	int **adjacent;
	double **dist;
	int i, j;  
	double tmp;

	//read file
	if (argc<2) {
		fprintf(stdout, "usage ./a.out filename\n");
		return 0;
	}

	if ((fp = fopen(args[1], "r")) == NULL) {
		fprintf(stderr, "fopen\n");
		exit(EXIT_FAILURE);
	}
	printf("succesfuly opened %s\n", args[1]);
	
	//init graph
	fscanf(fp, "%d", &N);
	adjacent = (int **)malloc(sizeof(int *)*N);
	dist = (double **)malloc(sizeof(double *)*N);
	for (i = 0; i<N; i++) {
		adjacent[i] = (int *)malloc(sizeof(int)*N);
		dist[i] = (double *)malloc(sizeof(double)*N);
		for (j = 0; j<N; j++) {
			adjacent[i][j] = 0;
			dist[i][j] = INF;
		}
	}
	while (fscanf(fp, "%d %d %lf", &i, &j, &tmp) != EOF) {
		adjacent[i][j] = adjacent[j][i] = 1;
		dist[i][j] = dist[j][i] = tmp;
	}

	while (fscanf(fp, "%d %d %lf", &i, &j, &tmp) != EOF) {
		adjacent[i][j] = adjacent[j][i] = 1;
		dist[i][j] = dist[j][i] = tmp;
	}

	prim(adjacent, dist, N);

	for (i = 0; i<N; i++) {
		free(adjacent[i]);
		free(dist[i]);
	}
	free(adjacent);
	free(dist);

	return 0;
}

void prim(int **adjacent, double **dist, int N) {
	char *visited = (char *)malloc(sizeof(char)*N);
	double *far = (double *)malloc(sizeof(double)*N);
	int *parent = (int *)malloc(sizeof(int)*N);
	int i, s, t;
	double min;

	fprintf(stderr, "start -> ");
	fscanf(stdin, "%d", &s);

	//init
	for (i = 0; i<N; i++) {
		far[i] = INF;
		visited[i] = FALSE;
	}

	far[s] = 0;

	while (1) {
		min = INF;
		for (i = 0; i<N; i++) {
			if (visited[i] == FALSE && (min>far[i])) {
				min = far[i];
				t = i;
			}
		}

		int flag = 1;
		for (i = 0; i<N; i++) {
			if (visited[i] == FALSE) flag = 0;
		}

		if (flag) {
			fprintf(stdout, "MST :\n");
			for (i = 0; i<N; i++) {
				if (i != s) fprintf(stdout, "%d - %d\n", parent[i], i);
			}
			return;
		}

		int neighbor;
		for (neighbor = 0; neighbor<N; neighbor++) {
			if (far[neighbor] > dist[t][neighbor] + far[t]) {
				far[neighbor] = dist[t][neighbor] + far[t];
				parent[neighbor] = t;
			}
		}
		visited[t] = TRUE;
	}

}