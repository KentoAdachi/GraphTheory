//
//  main.c
//  graph3
//
//  Created by 足立賢人 on 2018/07/18.
//  Copyright © 2018年 足立賢人. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define filename "./network1.txt"

int **adjacent;
double **dist;
int n_ = 0;

int init_graph(void);

int main(int argc, const char * argv[]) {

    //グラフの初期化
    init_graph();
    //キーボードから値を入力する
    int s,t;
    printf("s t:\n");
    scanf("%d %d",&s,&t);
    printf("%d %d\n",s,t);
    
    //最短経路を出力する

    
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
int init_graph(){
    int i;
    int j;
    //ファイルを読み込み
    printf(filename);
    printf("\n");
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    
    //要素数の取得
    fscanf(fp,"%d",&n_);
    printf("要素数 = %d\n",n_);
    //行列の初期化
    adjacent = (int **)malloc(n_ * sizeof(int *));
    for (i = 0; i < n_; i++)
        adjacent[i] = (int *)malloc(sizeof(int)*n_);
    
    dist = (double **)malloc(n_ * sizeof(double*));
    for (i = 0; i < n_; i++)
        dist[i] = (double *)malloc(sizeof(double)*n_);
    
    int a,b;
    double d;//floatだと丸め誤差的なことが起きた
    while (fscanf(fp, "%d %d %lf",&a,&b,&d) != EOF) {
        printf("%d %d %lf\n",a,b,d);
        adjacent[a][b] = 1;
        adjacent[b][a] = 1;
        dist[a][b] = d;
        dist[b][a] = d;
    }
    
    
    for (i = 0; i < n_; i++) {
        for (j = 0; j < n_; j++) {
            printf("%3d ",adjacent[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < n_; i++) {
        for (j = 0; j < n_; j++) {
            printf("%3lf ",dist[i][j]);
        }
        printf("\n");
    }
    
    
    
    fclose(fp);
    return 0;
}


