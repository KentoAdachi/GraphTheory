/*
グラフ理論 課題２－１



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
		printf("%d %d\n", i, j);
	}
	//print graph
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++) {
			printf("%d ", adjacent[i][j]);
		}
		printf("\n");
	}


	//アルゴリズム
	//グラフの最小時数を計算する
	int delta = min_dim(adjacent, size);
	printf("min dim = %d\n", delta);
	//変数xを定義しx = 1とする
	int x = 1;
	//要素数がxとなる点の部分集合をすべて生成する
	while (1) {
		unsigned char box[255];
		int index = 0;
		for (i = 0; i < 255; i++) {
			int *sub = subset(i, size);
			int youso = 0;
			for (j = 0; j < size; j++)
			{
				youso += sub[j];
			}
			if (youso == x)
			{
				box[index] = i;
				index++;
			}
		}
		//一つでも分離集合ならxを表示して終了
		//何かがおかしい
		for (; index >= 0; index--)
		{
			if (cutset(adjacent, size, box[index]) > 1)
			{
				printf("x = %d\nそれを与える部分集合 = %d\n", x,box[index]);
				return 0;
			}

		}

		//そうでないならxをインクリメントする
		x++;

		//x = deltaなら点連結度はdeltaとなり終了そうでなければ繰り返す
		if (x == delta) {
			printf("x = %d\n最大点連結度です\n", x);
			return 0;
		}

	}
}
//グラフの最小時数を計算
int min_dim(int **adjacent, int N) {
	
	int i;
	int j;
	int tmp;
	int ret = N;
	for ( i = 0; i < N; i++)
	{
		tmp = 0;
		for ( j = 0; j < N; j++)
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
int cutset(int **adjacent, int N,unsigned char val) {
	int i;
	int j;

	int *sub = subset(val,N);
	for ( i = 0; i < N; i++)
	{
		if (sub[i] == 1) {
			for ( j = 0; j < N; j++)
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
	for ( i = 0; i < N; i++)
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