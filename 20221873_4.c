#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//partition 함수 구현.
int partition(int A[], int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            int temp1 = A[++i];
            A[i] = A[j];
            A[j] = temp1;
        }   
    }
    int temp2 = A[i+1];
    A[i+1] = A[r];
    A[r] = temp2;
    return (i + 1);
}
//알고리즘 5-1 구현하라.
int select(int A[], int p, int r, int i) {
    if (A[p]==A[r]) {
        return A[p];
    } else {
        int q = partition(A, p, r);
        int k = q - p + 1;
        if (i < k) {
            select(A, p, q-1, i);
        }
        else if (i == k)
        {
            return A[q];
        }
        else {
            select(A, q+1, r, i-k);
        }
    }
    
}
//힙정렬 알고리즘을 이용하라.
void heapify(int A[], int k, int n) {
    int left = (2*k);
    int right = (2*k+1);
    int smaller;
    if (right <= n) {
        if (A[left] < A[right])
        {
            smaller = left;
        } else {
            smaller = right;
        }
    } else if (left <= n) {
        smaller = left;
    } else {
        return;
    }
    if (A[smaller] < A[k]) {
        int temp = A[k];
        A[k] = A[smaller];
        A[smaller] = temp;
        heapify(A, smaller, n);
    } 
}

void buildHeap(int A[], int n) {
    for (int i = (n/2); i > 0; i--)
    {
        heapify(A, i, n);
    }
}

void heapSort(int A[], int n) {
    buildHeap(A, n);
    for (int i = n; i > 1; i--) {
        int temp = A[1];
        A[1] = A[i];
        A[i] = temp;
        heapify(A, 1, i-1);
    }
}
//알고리즘 5-2를 구현하라.
int linearSelect(int A[], int p, int r, int i) {
    //알고리즘 1번 : 알고리즘 5-1을 이용하라
    if (r - p < 5) {
        return select(A, p, r, i);
    } else {
        //알고리즘 2번 : 전체 원소를 5개씩 원소를 가진 그룹으로 나눈다.
        int n = r - p + 1;
        int num_medians = (n + 4) / 5;
        int *median_collection = (int *)malloc(sizeof(int) * (num_medians + 1));
        int m_num = 0;
        median_collection[m_num++] = -1;
        for (int id = p; id < r - 4; id += 5) {
            int B[6] = {-1, A[id], A[id + 1], A[id + 2], A[id + 3], A[id + 4]};
            //알고리즘 3번 : 힙정렬 알고리즘으로 정렬한 후 중앙값을 구하라.
            heapSort(B, 5);
            median_collection[m_num++] = B[3];
        }
        if ((r - p) % 5 != 0) {
            int remain = (r - p) % 5;
            int B[6] = {-1};
            for (int j = 0; j < remain; j++) {
                B[j + 1] = A[r - remain + j + 1];
            }
            heapSort(B, remain);
            median_collection[m_num] = B[(remain + 1) / 2];
        }
        //알고리즘 4번 : 중앙값 M을 재귀적으로 구한다.
        int M = linearSelect(median_collection, 1, m_num, (m_num + 1) / 2);
        //알고리즘 5번 : M을 기준원소로 삼아 전체 원소를 분할한다.
        for (int j = 1; j <= n; j++) {
            if (A[j] == M) {
                int temp = A[j];
                A[j] = A[n];
                A[n] = temp;
            }
        }
        int q = partition(A, p, r);
        int k = q - p + 1;
        //알고리즘 6번 : 분할된 두 그룹 중 적합한 쪽을 선택하여 1~6을 재귀적으로 반복한다.
        if (i < k) {
            free(median_collection);
            return linearSelect(A, p, q - 1, i);
        } else if (i == k) {
            free(median_collection);
            return A[q];
        } else {
            free(median_collection);
            return linearSelect(A, q + 1, r, i - k);
        }
    }
}


int main(void)
{
    int A[100000];
    srand((unsigned int)time(NULL));
    int num;
    printf("몇 번 반복 측정할지 적으시오 : ");
    scanf("%d", &num);
    clock_t total_time = 0;
    for (int i = 1; i <= num; i++) {
        A[0] = -1;
        for (int i = 1; i < 100000; i++) {
            A[i] = rand();
        }
        int ok;
        clock_t start, end;
        //1번째부터 50000째로 작은 값을 구한다.
        for (int j = 1; j <= 50000; j++) {
            start = clock();
            ok = linearSelect(A, 1, 99999, j);
            end = clock();
            printf("%d번째 작은값 : %d\n", j, ok);
            total_time += (end - start);
        }
        printf("%d번째 시도 : 시간 - %f 초\n", i, ((double)(end - start)) / CLOCKS_PER_SEC);
        printf("50000번째 작은 값 : %d\n\n", ok);
    }

    printf("최종 %d번 반복 실행 결과: 총 %f 초\n", num, ((double)total_time) / CLOCKS_PER_SEC);

    return 0;
}