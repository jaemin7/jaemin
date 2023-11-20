#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//노드의 구조체
typedef struct Node{
	int data;
	struct Node* next;
}Node;

//연결 리스트의 구조체
typedef struct Linkedlist{
	Node* head;
	Node* tail;
} Linkedlist;

//빈 연결리스트 생성
Linkedlist* create_empty_list() {
	Linkedlist* list = (Linkedlist*)malloc(sizeof(Linkedlist));
	if (list == NULL) {
		printf("메모리 할당 오류");
		exit(1);
	}
	list->head = NULL;
	list->tail = NULL;
	return list;
}

//연결리스트 마지막에 노드 추가
void addNode_list(Linkedlist* list, int value) {
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

//연결리스트 안에 있는 데이터들 순서대로 출력
void print_list(Linkedlist* list) {
	Node* curr = list->head;
	while(curr != NULL) {
		printf("%d ", curr->data);
		curr = curr->next;
	}
	printf("\n");
}	

// 주어진 자릿수에 해당하는 숫자 추출
int get_dight(int num, int digit) {
	for (int i = 0; i < digit; i++) {
		num /= 10;
	}
	return num % 10;
}

int main(void)
{
	srand(time(NULL));
	int n;
	int m;
	printf("정렬할 정수의 개수 n개를 입력해주세요.");
	scanf("%d", &n);
	printf("실행 횟수 m을 입력하세요.");
	scanf("%d", &m);
	
	//빈 연결리스트 생성
	Linkedlist* random_num_list = create_empty_list();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			//4자리 정수를 rand() 함수를 통해 생성
			int random_num = rand() % 10000;
			//n개의 정수를 저장하는 연결리스트 생성
			addNode_list(random_num_list, random_num);
		}
		printf("랜덤 숫자 리스트: ");
		print_list(random_num_list);

		for (int digit = 0; digit < 4; digit++) {
			//0부터 9까지의 자릿수에 해당하는 10개의 연결리스트를 동적 메모리 할당으로 생성
			Linkedlist* zero_digit_list = create_empty_list();
			Linkedlist* one_digit_list = create_empty_list();
			Linkedlist* two_digit_list = create_empty_list();
			Linkedlist* three_digit_list = create_empty_list();
			Linkedlist* four_digit_list = create_empty_list();
			Linkedlist* five_digit_list = create_empty_list();
			Linkedlist* six_digit_list = create_empty_list();
			Linkedlist* seven_digit_list = create_empty_list();
			Linkedlist* eight_digit_list = create_empty_list();
			Linkedlist* nine_digit_list = create_empty_list();

			//헤드를 저장하는 크기가 10인 포인터 배열 생성
			Node* headarr[10];
			//테일을 저장하는 크기가 10인 포인터 배열 생성
			Node* tailarr[10];
			// 연결 리스트에 있는 숫자를 해당 자릿수의 연결 리스트에 넣음
			Node* curr = random_num_list->head;
			while (curr != NULL) {
				int num = curr->data;
				int digit_num = get_dight(num, digit);
				switch (digit_num) {
					case 0:
						addNode_list(zero_digit_list, num);
						break;	
					case 1:
						addNode_list(one_digit_list, num);
						break;	
					case 2:
						addNode_list(two_digit_list, num);
						break;
					case 3:
						addNode_list(three_digit_list, num);
						break;
					case 4:
						addNode_list(four_digit_list, num);
						break;
					case 5:
						addNode_list(five_digit_list, num);
						break;
					case 6:
						addNode_list(six_digit_list, num);
						break;
					case 7:
						addNode_list(seven_digit_list, num);
						break;
					case 8:
						addNode_list(eight_digit_list, num);
						break;
					case 9:
						addNode_list(nine_digit_list, num);
						break;
					default:
						printf("으악");
						break;
				}
				curr = curr->next;
			}
			headarr[0] = zero_digit_list->head;
			tailarr[0] = zero_digit_list->tail;
			headarr[1] = one_digit_list->head;
			tailarr[1] = one_digit_list->tail;
			headarr[2] = two_digit_list->head;
			tailarr[2] = two_digit_list->tail;
			headarr[3] = three_digit_list->head;
			tailarr[3] = three_digit_list->tail;
			headarr[4] = four_digit_list->head;
			tailarr[4] = four_digit_list->tail;
			headarr[5] = five_digit_list->head;
			tailarr[5] = five_digit_list->tail;
			headarr[6] = six_digit_list->head;
			tailarr[6] = six_digit_list->tail;
			headarr[7] = seven_digit_list->head;
			tailarr[7] = seven_digit_list->tail;
			headarr[8] = eight_digit_list->head;
			tailarr[8] = eight_digit_list->tail;
			headarr[9] = nine_digit_list->head;
			tailarr[9] = nine_digit_list->tail;

			// 버킷에서 숫자를 다시 연결 리스트로 이동
        	Linkedlist* result = create_empty_list();
			for (int i = 0; i < 10; i++) {
				Node* current = headarr[i];
				while (current != NULL) {
                	addNode_list(result, current->data);
                	Node* temp = current;
                	current = current->next;
                	free(temp);
           	 	}
			}

        	// 결과를 원래 리스트로 복사
        	Node* resultNode = result->head;
       		Node* originalNode = random_num_list->head;
        	while (resultNode != NULL) {
            	originalNode->data = resultNode->data;
            	resultNode = resultNode->next;
            	originalNode = originalNode->next;
        	}
        	free(result);
		}	
		printf("기수 정렬 결과: ");
        print_list(random_num_list);
		// 연결 리스트 비우기
        Node* current = random_num_list->head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        random_num_list->head = NULL;
        random_num_list->tail = NULL;
	}	
	free(random_num_list);
	return 0;
} 