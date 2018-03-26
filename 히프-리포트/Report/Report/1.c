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

	while ((i != 1) && strcmp(item.key, h->heap[i / 2].key) > 0)	//����ũ�� �񱳸� ��� key���� �� Ŀ����
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
		if (child <= h->heap_size && strcmp(h->heap[child].key, h->heap[child + 1].key) < 0)	//������ ������ �ڽ��� �� ũ�ٸ� �ε����� �ϳ� �÷���
			child++;
		if (strcmp(temp.key, h->heap[child].key) >= 0)	//������ ������ ���� �� Ŀ���� �극��ũ
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

	printf("delete e4�� ���� ����\n");
	e4 = delete_max_heap(&h);
	printf("e4 = {%s, %d}\n", e4.key, e4.id);
	display_heap(&h);

	printf("delete e5�� ���� ����\n");
	e5 = delete_max_heap(&h);
	printf("e5 = {%s, %d}\n", e4.key, e4.id);
	display_heap(&h);

}

/*
�� ����ü�� ����Ͽ�  �� ���� �̻� max heap�� �Է��ϰ� ���� �� ���ÿ�.����� ȭ�鿡 �Ź� �ﵵ�� �Ͻÿ�.
�� ������ ũ�⸦ ���ڿ� key�� �������� �Ͻÿ�.�� ������ ũ�� �񱳸� �̿��Ͽ� ���� ���
e1 = { "egg", 1234 }, e2 = { "structure", 321 }�̸� e1�� e2���� �۴ٰ� �����Ѵ�.
���ڿ��� ������ ũ�⸦ ���ϴ� �Լ� strcmp�� �̿��Ѵ�.
*/