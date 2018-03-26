#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENT 100

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void init(HeapType *h)
{
	h->heap_size = 0;
}

void insert_max_heap(HeapType *h, element item)
{
	int i = ++h->heap_size;

	while (i != 1 && (item.key > h->heap[i/2].key))
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

	parent = 1;
	child = 2;

	item = h->heap[1];
	temp = h->heap[h->heap_size--];

	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child+1].key))
			child++;
		if (temp.key >= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void print_heap(HeapType *h)
{
	int i;

	for (i = 1; i <= h->heap_size; i++)
		printf("h[%d] -> %d   \n", i, h->heap[i].key);
	printf("\n");
}


void delete_element(HeapType *h, int number)
{ // number를 key로 갖는 element를 삭제한다. 삭제 후에 max heap이 유지되어야 한다}
	
	element *e;
	int cnt = 0, k = -1, i;
	int element_size, temp_heap_size;

	//삭제를 원하는 요소의 수를 셈
	for (i = 1; i <= h->heap_size;i++)
		if (h->heap[i].key == number)
			cnt++;
	
	element_size = h->heap_size - cnt;	//전체에서 삭제를 원하는 수를 뺀 새로운 사이즈
	temp_heap_size = h->heap_size;	//밑에서 heap 사이즈가 delete를 수행하며 바뀌므로 그것을 대신할 값을 대입

	e = (element*)malloc(sizeof(element)*element_size);	//삭제한 것 제외를 받을 element 배열

	for (i = 1; i <= temp_heap_size;i++)	//조건문에 사용
	{
		if (h->heap[1].key == number)	//삭제를 원하는 값은 빼기만 함, 어차피 맨 위에 값만 빼므로 제일 위에 값이 원하는 값인지 계속 찾음
			delete_max_heap(h);
		else
			e[++k] = delete_max_heap(h); //삭제를 원하는 값 제외 새로운 배열을 만듬
	}

	for (i = 0; i < element_size; i++) //삭제를 완료한 element로 새로운 max_heap 생성
		insert_max_heap(h, e[i]);
}



void main()
{
	element e[9] = { { 10 },{ 40 },{ 30 },{ 5 },{ 12 },{ 6 },{ 15 },{ 9 },{ 60 } };
	HeapType heap1;
	int i;
	int num = 40;	//40을 제거한 max heap
	element a;

	init(&heap1);
	for (i = 0;i < 9;i++)
		insert_max_heap(&heap1, e[i]);
	print_heap(&heap1);

	printf("40을 제거한 다음\n");
	delete_element(&heap1, num);
	print_heap(&heap1);

	//max heap인지 체크하는 과정   값이 큰 순서대로 출력되어야 한다
	printf("내림 차순 정렬\n");
	for (i = 0;i < 8;i++)
	{
		a = delete_max_heap(&heap1);
		printf("%d ", a.key);
	}
}

//(3) max heap에서 임의의 원소를 삭제하는 함수를 다음과 같이 작성하시오.(책 연습문제22)