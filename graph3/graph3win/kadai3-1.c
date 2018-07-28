#include<stdio.h>
#include<stdlib.h>
#include<float.h>

#define INF DBL_MAX
#define TRUE 1
#define FALSE 0


double dijkstara(int **adjacent, double **dist, int num);

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

	printf("最短距離 : %lf \n", dijkstara(adjacent, dist, N));

	for (i = 0; i<N; i++) {
		free(adjacent[i]);
		free(dist[i]);
	}
	free(adjacent);
	free(dist);

	return 0;
}

double dijkstara(int **adjacent, double **dist, int N) {
	double *far = (double *)malloc(sizeof(double)*N);//道のり
	int *parent = (int *)malloc(sizeof(int)*N);//自分の前
	char *visited = (char *)malloc(sizeof(char)*N);//通過済み
	int i, s, t; 
	int next;
	double min;

	//input
	printf("from : ");
	fscanf(stdin, "%d", &s);
	printf("to : ");
	fscanf(stdin, "%d", &t);
	//init
	for (i = 0; i<N; i++) {
		far[i] = INF;
		parent[i] = -1;
		visited[i] = FALSE;
	}

	

	far[s] = 0;

	while (1) {
		min = INF;
		for (i = 0; i<N; i++) {
			if (visited[i] == FALSE && (min>far[i])) {
				min = far[i];
				next = i;
			}
		}
		
		if (next == t) {
			int node = t;
			int *route = (int *)malloc(sizeof(int)*N);
			int i = 0;
			while (node != s) {
				route[i++] = node;
				node = parent[node];
			} 
			printf("最短経路 : %d", s);
			while (i > 0) {
			
				printf(" => %d", route[--i]);
			}
			printf("\n");

			return far[t];
		}

		
		for (i = 0; i<N; i++) {
			if (far[i] > dist[next][i] + far[next]) {
				far[i] = dist[next][i] + far[next];
				parent[i] = next;
			}
		}
		visited[next] = TRUE;
	
	}


}


