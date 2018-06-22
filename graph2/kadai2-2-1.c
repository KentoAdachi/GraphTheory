/*
�O���t���_ �ۑ�2-2-1

�I�C���[�O���t�ł���<->���ׂĂ̓_�̎���������


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
	int i;//���[�v�J�E���^
	int j;//���[�v�J�E���^
	int size;

	FILE *fp = fopen("graph2.txt", "r");
	fscanf(fp, "%d", &size);

	int **adjacent = (int **)malloc(sizeof(int *)*size);//�אڐړ_���
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

	isEuler(adjacent, size);


	//


}

//�I�C���[�O���t�𔻒�
int isEuler(int **adjacent, int N) {
	//���ׂĂ̓_�������ł���
	int flag = 1;
	int i;
	for (i = 0; i < N; i++)
	{
		if (dim(adjacent, i, N) % 2 == 1) {
			flag = 0;
		}
	}
	if (flag)
	{
		printf("�I�C���[�O���t�ł�\n");
		return 1;
	}
	else {
		printf("�I�C���[�O���t�ł͂���܂���\n");
		return 0;
	}

}

//����_�̎������v�Z
int dim(int **adjacent, int index, int N) {
	int i;
	int tmp = 0;
	for (i = 0; i < N; i++)
	{
		tmp += adjacent[index][i];
	}
	return tmp;
}

