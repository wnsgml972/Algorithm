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
{ // number�� key�� ���� element�� �����Ѵ�. ���� �Ŀ� max heap�� �����Ǿ�� �Ѵ�}
	
	element *e;
	int cnt = 0, k = -1, i;
	int element_size, temp_heap_size;

	//������ ���ϴ� ����� ���� ��
	for (i = 1; i <= h->heap_size;i++)
		if (h->heap[i].key == number)
			cnt++;
	
	element_size = h->heap_size - cnt;	//��ü���� ������ ���ϴ� ���� �� ���ο� ������
	temp_heap_size = h->heap_size;	//�ؿ��� heap ����� delete�� �����ϸ� �ٲ�Ƿ� �װ��� ����� ���� ����

	e = (element*)malloc(sizeof(element)*element_size);	//������ �� ���ܸ� ���� element �迭

	for (i = 1; i <= temp_heap_size;i++)	//���ǹ��� ���
	{
		if (h->heap[1].key == number)	//������ ���ϴ� ���� ���⸸ ��, ������ �� ���� ���� ���Ƿ� ���� ���� ���� ���ϴ� ������ ��� ã��
			delete_max_heap(h);
		else
			e[++k] = delete_max_heap(h); //������ ���ϴ� �� ���� ���ο� �迭�� ����
	}

	for (i = 0; i < element_size; i++) //������ �Ϸ��� element�� ���ο� max_heap ����
		insert_max_heap(h, e[i]);
}



void main()
{
	element e[9] = { { 10 },{ 40 },{ 30 },{ 5 },{ 12 },{ 6 },{ 15 },{ 9 },{ 60 } };
	HeapType heap1;
	int i;
	int num = 40;	//40�� ������ max heap
	element a;

	init(&heap1);
	for (i = 0;i < 9;i++)
		insert_max_heap(&heap1, e[i]);
	print_heap(&heap1);

	printf("40�� ������ ����\n");
	delete_element(&heap1, num);
	print_heap(&heap1);

	//max heap���� üũ�ϴ� ����   ���� ū ������� ��µǾ�� �Ѵ�
	printf("���� ���� ����\n");
	for (i = 0;i < 8;i++)
	{
		a = delete_max_heap(&heap1);
		printf("%d ", a.key);
	}
}

//(3) max heap���� ������ ���Ҹ� �����ϴ� �Լ��� ������ ���� �ۼ��Ͻÿ�.(å ��������22)