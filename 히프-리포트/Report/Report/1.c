#define _CRT_SECURE_NO_WARNINGS
#define MAX_HEAP_SIZE 200

#include <stdio.h>
#include <string.h>

typedef struct
{
	char key[20];
	int id;
}element;
typedef struct
{
	element heap[MAX_HEAP_SIZE];
	int heap_size;
}HeapType;

void init(HeapType *h)
{
	h->heap_size = 0;
}

void display_heap(HeapType *h)
{
	int i;

	for (i = 1; i <= h->heap_size; i++)
		printf("h[%d] -> {%s, %d}   \n",i , h->heap[i].key, h->heap[i].id);
	printf("\n");
}

void insert_max_heap(HeapType *h, element item)
{
	int i = ++h->heap_size;

	while ((i != 1) && strcmp(item.key, h->heap[i / 2].key) > 0)	//사전크기 비교를 사용 key값이 더 커야함
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_max_heap(HeapType *h)
{
	element item, temp;
	int parent, child;

	item = h->heap[1];
	temp = h->heap[h->heap_size--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size)
	{
		if (child <= h->heap_size && strcmp(h->heap[child].key, h->heap[child + 1].key) < 0)	//사전비교 오른쪽 자식이 더 크다면 인덱스를 하나 늘려줌
			child++;
		if (strcmp(temp.key, h->heap[child].key) >= 0)	//사전비교 템프에 값이 더 커지면 브레이크
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;

	return item;
}

int main()
{
	HeapType h;
	element e1 = { "egg", 1234 };
	element	e2 = { "structure", 321 };
	element e3 = { "apple", 333 };

	element e4, e5;

	init(&h);

	printf("insert e1\n");
	insert_max_heap(&h, e1);
	display_heap(&h);

	printf("insert e2\n");
	insert_max_heap(&h, e2);
	display_heap(&h);

	printf("insert e3\n");
	insert_max_heap(&h, e3);
	display_heap(&h);

	printf("delete e4에 값을 받음\n");
	e4 = delete_max_heap(&h);
	printf("e4 = {%s, %d}\n", e4.key, e4.id);
	display_heap(&h);

	printf("delete e5에 값을 받음\n");
	e5 = delete_max_heap(&h);
	printf("e5 = {%s, %d}\n", e4.key, e4.id);
	display_heap(&h);

}

/*
위 구조체를 사용하여  세 원소 이상 max heap에 입력하고 삭제 해 보시오.결과를 화면에 매번 찍도록 하시오.
두 원소의 크기를 문자열 key에 따르도록 하시오.즉 사전적 크기 비교를 이용하여 예를 들면
e1 = { "egg", 1234 }, e2 = { "structure", 321 }이면 e1가 e2보다 작다고 생각한다.
문자열의 사전적 크기를 비교하는 함수 strcmp를 이용한다.
*/