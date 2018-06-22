/*
グラフ理論 課題2-2-2

オイラー閉路を求める

*/

#include<stdio.h>
#include<stdlib.h>

#define ALT  //<=コメントアウトを外す
#ifdef ALT
#define FILENAME "graph3.txt"
#else
#define FILENAME "graph2.txt"
#endif // ALT

#pragma warning (disable: 4996)

int *subset(unsigned char val, int N);
void visit(int v, int *yet, int N, int **adjacent);
int connect_check(int N, int ** adjacent);
int cut(int **adjacent, int N, unsigned char val);
int min_dim(int **adjacent, int N);
int **removeEdge(int **adjacent, int N, int u, int v);
int search(int **adjacent, int N, int position);
int isBridge(int **adjacent, int N, int u, int v);
int isEuler(int **adjacent, int N);
int dim(int **adjacent, int index, int N);

int main() {
	int i;//ループカウンタ
	int j;//ループカウンタ
	int size;
	printf(FILENAME);
	printf("\n");

	FILE *fp = fopen(FILENAME, "r");
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
	//オイラーグラフを判定
	if (!isEuler(adjacent,size))
		exit(1);
	search(adjacent,size,0);
	printf("\n");


}

//探索
int search(int **adjacent,int N,int position) {
	printf("%d", position);

	int i;
	int *yet = (int *)malloc(sizeof(int)*N);

	for ( i = 0; i < N; i++)
	{
		yet[i] = 1;
	}
	
	for ( i = 0; i < N; i++)
	{
		if (adjacent[position][i])
		{
			if (!isBridge(adjacent, N, position, i))
			{
				//printf("橋じゃない\n");
				printf(" -> ");
				search(removeEdge(adjacent, N, position, i), N, i);
				return 0;
			}
		}
	}

	for (i = 0; i < N; i++)
	{
		if (adjacent[position][i])
		{
			//printf("橋を選択\n");
			printf(" -> ");
			search(removeEdge(adjacent, N, position, i), N, i);
			return 0;
		}
	}
	return 0;
}
//uvが橋であることを示す
//count 使いきった点の数
int isBridge(int **adjacent,int N,int u,int v){
	int i, j;
	int c,count;
	count = 1;
	for ( i = 0; i < N; i++)
	{	
		c = 0;
		for ( j = 0; j < N; j++)
		{
			if (adjacent[i][j] != 0)c++;
		}
		if (c == 0)count++;
	}
	
	if (connect_check(N, removeEdge(adjacent, N, u, v)) > count)return 1;
	return 0;
}




//隣接行列を削除
int **removeEdge(int **adjacent,int N, int u, int v) {

	int **ret = (int **)malloc(sizeof(int *)* N);
	int i,j;
	for ( i = 0; i < N; i++)
	{
		ret[i] = (int *)malloc(sizeof(int)*N);
		for ( j	= 0; j < N; j++)
		{
			ret[i][j] = adjacent[i][j];
		}
	}

	
	ret[u][v]--;
	ret[v][u]--;
	return ret;
}


//オイラーグラフを判定
int isEuler(int **adjacent, int N) {
	//すべての点が偶数である
	int i;
	for (i = 0; i < N; i++)
	{
		if (dim(adjacent, i, N) % 2 == 1) {
			printf("オイラーグラフではありません\n");
			return 0;
		}
	}
		printf("オイラーグラフです\n");
		return 1;


}

//ある点の次数を計算
int dim(int **adjacent, int index, int N) {
	int i;
	int tmp = 0;
	for (i = 0; i < N; i++)
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
int cut(int **adjacent, int N, unsigned char val) {
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
	//printf("visited %d\n",v);
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
