#define _CRT_SECURE_NO_WARNINGS
#define MAX_HEAP_SIZE 200
#include <stdio.h>

typedef struct
{
	int key;
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
		printf("h[%d] -> %d   \n", i, h->heap[i].key);
	printf("\n");
}

void insert_min_heap(HeapType *h, element item)
{
	int i = ++h->heap_size;

	while ((i != 1) && (item.key < h->heap[i / 2].key))	//min heap 이므로 부호가 반대!
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType *h)
{
	element item, temp;
	int parent, child;

	parent = 1;
	child = 2;

	item = h->heap[1];
	temp = h->heap[h->heap_size--];

	while (child <= h->heap_size)
	{
		if (child < h->heap_size && (h->heap[child].key > h->heap[child + 1].key))	//더 작은 자식을 찾음
			child++;
		if (temp.key <= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];

		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void min_heap_sort(element a[], int n)
{
	int i;
	HeapType h;
	int k = -1;

	init(&h);
	for (i = 0; i < n; i++)
		insert_min_heap(&h, a[i]);
	for (i = n - 1; i >= 0; i--)
		a[++k] = delete_min_heap(&h);

	for (i = 0; i < n; i++)
		printf("%d  ", a[i].key);
	printf("\n");
}

int main()
{
	element e[7] = { 4 ,2,1,1,5, 9, 3};
	int i;
	HeapType h;
	
	init(&h);

	for (i = 0; i < 7; i++)
		insert_min_heap(&h, e[i]);
	display_heap(&h);

	printf("min heap 오름차순 정렬\n");
	min_heap_sort(e, 7);
}

//(2) 홈페이지 8장 프로그램에 있는 sort를 min heap을 사용하여 오름차순으로 정렬하도록 변경하시오.