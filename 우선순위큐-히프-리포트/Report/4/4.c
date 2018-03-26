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
{//	k-max-heap(�ڽ��� k���� ���� k-nary tree�� �̿��� heap))�� �ǵ��� �ڷḦ �Է�
	int i = ++h->heap_size;

	while (i != 1 && (item.key > h->heap[(i+k-2)/k].key))	//K�� Ʈ���� �θ� �ε����� ���� ����
	{
		h->heap[i] = h->heap[(i+k-2)/k];
		i = (i + k - 2) / k;
	}
	h->heap[i] = item;
}

int get_max_index(HeapType *h, int start, int number)
{//	heap�� start���� number �� ��ŭ�� ���� �� ���� key�� ū ������ index�� ��ȯ�ϴ�.
	int i, k;
	int max = h->heap[start].key;
	int max_index = start;	//���� �ؿ� �������� �Ȱ�ġ�� ���� ���� ���� ū �ε���

	for (i = start, k = 0; k < number; i++, k++)	//number��ŭ ������ ��
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
{//	k-max-heap���� ���� key�� ū ���Ҹ� ��ȯ�Ѵ�. ��ȯ �� k-max-heap�� �����Ѵ�. ���� max�Լ��� �̿�
	element item, temp;
	int child, parent;

	item = h->heap[1];
	temp = h->heap[h->heap_size--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size)	//�ڽ��� ���� ū ���� �ε����� ã�� ���� max�Լ� �̿�
	{
		if (child < h->heap_size)
			child = get_max_index(h, parent*k-(k-2), k);	//k�����ϱ� number�� k��ŭ ã��
		if (temp.key >= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child = child*k - (k - 2);	//k�� Ʈ���� ���� �ڽ� ����
	}
	
	h->heap[parent] = temp;
	return item;
}

void heap_sort(element a[], int n, int k)
{ //k-max-heap�� �̿��Ͽ� �����Ѵ�.
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

	printf("3�� Ʈ�� \n");
	for (i = 0; i < 10; i++)
		insert_max_heap(&h, e[i], 3);
	print_heap(&h);	
	printf("3�� Ʈ�� ����\n");
	heap_sort(e, 10, 3);

	printf("\n4�� Ʈ�� \n");
	for (i = 0; i < 10; i++)
		insert_max_heap(&h2, e[i], 4);
	print_heap(&h2);
	printf("4�� Ʈ�� ����\n");
	heap_sort(e, 10, 4);

	printf("\n5�� Ʈ�� \n");
	for (i = 0; i < 10; i++)
		insert_max_heap(&h3, e2[i], 5);
	print_heap(&h3);
	printf("5�� Ʈ�� ����\n");
	heap_sort(e2, 10, 5);

	//������ 10�̻��� ���� ���� ���� ������ �迭�� ���� heap_sort�� �̿��Ͽ� 
	//�����Ͻÿ�. k���� ���� ���� ���� �ؼ� test�� ���ÿ�.
}

//(4) k - nary tree(k�� Ʈ��)�� �̿��Ͽ� max heap�� ����� �̸� �̿��Ͽ� ������ �����Ͻÿ�.������ ���� �����Ͻÿ�.