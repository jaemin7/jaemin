#include <stdio.h>
#include <stdlib.h>
int maxnum(int a, int b) {
    if (a >= b)
    {
        return a;
    } else {
        return b;
    }    
}

int matrixPath(int n, int **arr, int **c) {
    for (int i = 0; i < n+1; i++) {
        c[i][0] = 0;
    }
    for (int j = 0; j < n+1; j++) {
        c[0][j] = 0;
    }
    for (int i = 1; i < n+1; i++) {
        for (int j = 1; j < n+1; j++) {
            c[i][j] = arr[i-1][j-1] + maxnum(c[i-1][j], c[i][j-1]);
        }
    }
    int result = c[n][n];
    return result;
}

void find_print_path(int n, int **c) {
    int **find = (int **)malloc((n+1)*sizeof(int*));
    for (int i = 0; i < n+1; i++) {
        find[i] = (int*)malloc((n+1)*sizeof(int));
    }
    for (int i = 0; i < n+1; i++) {
        for (int j = 0; j < n+1; j++) {
            find[i][j] = 0;
        }
    }
    find[n][n] = 1;
    int x = n;
    int y = n;
    while (x > 0 && y > 0)
    {
        if(c[x][y-1] >= c[x-1][y]) {
            find[x][y-1] = 1;
            y--;
        } else {
            find[x-1][y] = 1;
            x--;
        }
    }
    printf("경로 : ");
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if(find[i][j] == 1) {
                if (i == n && j == n)
                {
                    printf("(%d, %d)", i, j);
                } else {
                    printf("(%d, %d) -> ", i, j);
                }
            } 
        }
    }

    for (int i = 0; i < n+1; i++) {
        free(find[i]);
    }
    free(find);
}

int main(void)
{
    printf("n 값 입력 : ");
    int n;
    scanf("%d", &n);
    int **arr = (int **)malloc((n)*sizeof(int*));
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)malloc((n)*sizeof(int));
    }
        int **c = (int **)malloc((n+1)*sizeof(int*));
    for (int i = 0; i < n+1; i++) {
        c[i] = (int*)malloc((n+1)*sizeof(int));
    }

    for (int i = 0; i < n; i++) {  
        printf("%d행 입력 : ", i+1);
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    printf("\n");

    int max_num = matrixPath(n, arr, c);
    printf("최대값 : %d\n", max_num);
    find_print_path(n, c);

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    for (int i = 0; i < n+1; i++) {
        free(c[i]);
    }
    free(c);


    return 0;
}