#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENT 200

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int key;
}element;

typedef struct
{
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void init(HeapType *h)
{
	h->heap_size = 0;
}

//left_child of i=i*k-(k-2)
//parent index of l = (l + k - 2) /k

void insert_max_heap(HeapType *h, element item, int k)
{//	k-max-heap(자식이 k개인 완전 k-nary tree를 이용한 heap))이 되도록 자료를 입력
	int i = ++h->heap_size;

	while (i != 1 && (item.key > h->heap[(i+k-2)/k].key))	//K진 트리의 부모 인덱스의 식을 대입
	{
		h->heap[i] = h->heap[(i+k-2)/k];
		i = (i + k - 2) / k;
	}
	h->heap[i] = item;
}

int get_max_index(HeapType *h, int start, int number)
{//	heap의 start에서 number 개 만큼의 원소 중 가장 key가 큰 원소의 index를 반환하다.
	int i, k;
	int max = h->heap[start].key;
	int max_index = start;	//만약 밑에 이프문을 안거치면 최초 값이 가장 큰 인덱스

	for (i = start, k = 0; k < number; i++, k++)	//number만큼 포문을 돔
	{
		if (h->heap[i].key > max)
		{
			max = h->heap[i].key;
			max_index = i;
		}
	}

	return max_index;
}


//left_child of i=i*k-(k-2)
//parent index of l = (l + k - 2) /k

element delete_max_heap(HeapType *h, int k)
{//	k-max-heap에서 가장 key가 큰 원소를 반환한다. 반환 후 k-max-heap을 유지한다. 위의 max함수를 이용
	element item, temp;
	int child, parent;

	item = h->heap[1];
	temp = h->heap[h->heap_size--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size)	//자식중 가장 큰 값의 인덱스를 찾음 위에 max함수 이용
	{
		if (child < h->heap_size)
			child = get_max_index(h, parent*k-(k-2), k);	//k진수니까 number는 k만큼 찾음
		if (temp.key >= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child = child*k - (k - 2);	//k진 트리의 왼쪽 자식 공식
	}
	
	h->heap[parent] = temp;
	return item;
}

void heap_sort(element a[], int n, int k)
{ //k-max-heap을 이용하여 정렬한다.
	int i;
	HeapType h;
	init(&h);

	for (i = 0;i<n;i++) 
		insert_max_heap(&h, a[i], k);

	for (i = n - 1;i >= 0;i--) 
		a[i] = delete_max_heap(&h, k);

	for (i = 0;i < n;i++)
		printf("%d ", a[i].key);
	printf("\n");
}


void print_heap(HeapType *h)
{
	int i;

	for (i = 1; i <= h->heap_size; i++)
		printf("h[%d] -> %d   \n", i, h->heap[i].key);
	printf("\n");
}

void main()
{
	HeapType h, h2 ,h3;
	element e[10] = { 1, 4, 3, 2, 8, 7 ,6 ,9, 10 , 5};
	element e2[15] = { 1,5,4,7,13,2,5,3,6,2,1,3,9,8,10};
	int i;
	
	init(&h);
	init(&h2);
	init(&h3);

	printf("3진 트리 \n");
	for (i = 0; i < 10; i++)
		insert_max_heap(&h, e[i], 3);
	print_heap(&h);	
	printf("3진 트리 정렬\n");
	heap_sort(e, 10, 3);

	printf("\n4진 트리 \n");
	for (i = 0; i < 10; i++)
		insert_max_heap(&h2, e[i], 4);
	print_heap(&h2);
	printf("4진 트리 정렬\n");
	heap_sort(e, 10, 4);

	printf("\n5진 트리 \n");
	for (i = 0; i < 10; i++)
		insert_max_heap(&h3, e2[i], 5);
	print_heap(&h3);
	printf("5진 트리 정렬\n");
	heap_sort(e2, 10, 5);

	//사이즈 10이상인 정렬 되지 않은 정수형 배열을 위의 heap_sort를 이용하여 
	//정렬하시오. k값을 여러 가지 경우로 해서 test해 보시오.
}

//(4) k - nary tree(k진 트리)를 이용하여 max heap을 만들고 이를 이용하여 정수를 정렬하시오.다음과 같이 시작하시오.