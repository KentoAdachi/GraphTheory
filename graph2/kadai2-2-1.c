/*
グラフ理論 課題2-2-1

オイラーグラフである<->すべての点の次数が偶数


*/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 8
#pragma warning (disable: 4996)

int *subset(unsigned char val, int N);
void visit(int v, int *yet, int N, int **adjacent);
int connect_check(int N, int ** adjacent);
int cutset(int **adjacent, int N, unsigned char val);
int min_dim(int **adjacent, int N);

int main() {
	int i;//ループカウンタ
	int j;//ループカウンタ
	int size;

	printf("test\n");

	FILE *fp = fopen("graph3.txt", "r");
	fscanf(fp, "%d", &size);

	int **adjacent = (int **)malloc(sizeof(int *)*size);//隣接接点情報
	for (i = 0; i < size; i++)
	{
		adjacent[i] = (int *)malloc(sizeof(int)*size);
	}
	//init graph
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++) {
			adjacent[i][j] = 0;
		}
	}

	//read file
	while (fscanf(fp, "%d  %d", &i, &j) != EOF) {
		adjacent[i][j]++;
		adjacent[j][i]++;
		//printf("%d %d\n", i, j);
	}
	//print graph
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++) {
			printf("%d ", adjacent[i][j]);
		}
		printf("\n");
	}


	//すべての点が偶数である
	int flag = 1;
	for ( i = 0; i < size; i++)
	{
		if (dim(adjacent, i, size) % 2 == 1) {
			flag = 0;
		}
	}
	if (flag)
	{
		printf("オイラーグラフです\n");
	}
	else {
		printf("オイラーグラフではありません");
	}

	//


}

//ある点の次数を計算
int dim(int **adjacent,int index,int N) {
	int i;
	int tmp = 0;
	for ( i = 0; i < N; i++)
	{
		tmp += adjacent[index][i];
	}
	return tmp;
}

//グラフの最小時数を計算
int min_dim(int **adjacent, int N) {

	int i;
	int j;
	int tmp;
	int ret = N;
	for (i = 0; i < N; i++)
	{
		tmp = 0;
		for (j = 0; j < N; j++)
		{
			if (adjacent[i][j] > 0)
			{
				tmp++;
			}
		}
		ret = tmp < ret ? tmp : ret;

	}
	return ret;
}

//分離集合を判断
int cutset(int **adjacent, int N, unsigned char val) {
	int i;
	int j;

	int *sub = subset(val, N);
	for (i = 0; i < N; i++)
	{
		if (sub[i] == 1) {
			for (j = 0; j < N; j++)
			{
				adjacent[i][j] = 0;
				adjacent[j][i] = 0;
			}
		}


	}
	return connect_check(N, adjacent);
}

//部分集合を計算
int *subset(unsigned char val, int N) {
	int i;
	int var = 1;
	int *ret = (int *)malloc(sizeof(int) * N);
	for (i = 0; i < N; i++)
	{

		ret[i] = (val % (var * 2)) / var;
		//printf("%d  %d %d\n", i, var, ret[i]);
		var *= 2;
	}
	return ret;
}


void visit(int v, int *yet, int N, int **adjacent)
{
	int w;
	yet[v] = 0;
	for (w = 0; w<N; w++)
		if (adjacent[v][w] == 1 && yet[w] == 1)
			visit(w, yet, N, adjacent);
}


int connect_check(int N, int **adjacent)
{
	int i,
		*YetToVisit,
		count = 0;
	YetToVisit = (int *)malloc(sizeof(int) * N);
	for (i = 0; i<N; i++)
		YetToVisit[i] = 1;
	for (i = 0; i<N; i++)
		if (YetToVisit[i] == 1) {
			count++;
			visit(i, YetToVisit, N, adjacent);
		}
	free(YetToVisit);
	return (count);
}
//int connect_check(int N, int ** adjacent) {
//
//	int i, *YetToVisit, count = 0;
//	YetToVisit = (int *)malloc(sizeof(int)*N);
//
//	for ( i = 0; i < N; i++)
//		YetToVisit[i] = 1;
//
//	for ( i = 0; i < N; i++)
//		if (YetToVisit[i] == 1) {
//			count++;
//			visit(i, YetToVisit, N, adjacent);
//		}
//
//	free(YetToVisit);
//	return(count);
//	
//}