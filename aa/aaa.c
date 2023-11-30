#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 노드의 구조체
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 연결 리스트의 구조체
typedef struct LinkedList {
    Node* head;
    Node* tail;
} LinkedList;

// 빈 연결 리스트 생성
LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        printf("메모리 할당 오류");
        exit(1);
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// 노드를 연결 리스트의 끝에 추가
void appendNode(LinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("메모리 할당 오류");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;

    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// 연결 리스트를 출력
void printList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 주어진 자릿수에 해당하는 숫자 추출
int getDigit(int number, int digit) {
    for (int i = 0; i < digit; i++) {
        number /= 10;
    }
    return number % 10;
}
void radixSort(LinkedList* randomList, int n) {
    LinkedList* buckets[10]; // 0부터 9까지의 버킷 배열 생성

    for (int digit = 0; digit < 4; digit++) {
        // 각 자릿수에 따라 버킷 초기화
        for (int i = 0; i < 10; i++) {
            buckets[i] = createLinkedList();
        }

        // 연결 리스트에 있는 숫자를 해당 자릿수의 버킷에 넣음
        Node* current = randomList->head;
        while (current != NULL) {
            int number = current->data;
            int digitValue = getDigit(number, digit);
            appendNode(buckets[digitValue], number);
            current = current->next;
        }

        // 버킷에서 숫자를 다시 연결 리스트로 이동
        LinkedList* result = createLinkedList();
        for (int i = 0; i < 10; i++) {
            Node* current = buckets[i]->head;
            while (current != NULL) {
                appendNode(result, current->data);
                Node* temp = current;
                current = current->next;
                free(temp);
            }
            free(buckets[i]);
        }
        printList(result);

        // 결과를 원래 리스트로 복사
        Node* resultNode = result->head;
        Node* originalNode = randomList->head;
        while (resultNode != NULL) {
            originalNode->data = resultNode->data;
            resultNode = resultNode->next;
            originalNode = originalNode->next;
        }
        printList(randomList);
        free(result);
        
    }
}

int main() {
    srand(time(NULL));

    int n, m;
    printf("정렬할 정수의 개수 n을 입력하세요: ");
    scanf("%d", &n);
    printf("실행 횟수 m을 입력하세요: ");
    scanf("%d", &m);

    LinkedList* randomList = createLinkedList();

    for (int i = 0; i < m; i++) {
        // 무작위 숫자 생성 및 연결 리스트에 추가
        for (int j = 0; j < n; j++) {
            int randomNumber = rand() % 10000;
            appendNode(randomList, randomNumber);
        }

        printf("랜덤 숫자 리스트: ");
        printList(randomList);

        // 기수 정렬 수행
        radixSort(randomList, n);

        printf("기수 정렬 결과: ");
        printList(randomList);

        // 연결 리스트 비우기
        Node* current = randomList->head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        randomList->head = NULL;
        randomList->tail = NULL;
    }

    free(randomList);

    return 0;
}