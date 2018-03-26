#define SORT_H
#ifdef SORT_H

#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t) )


int n;			//정렬할 정수의 갯수
int cending;	//오름차순? 내림차순?
typedef struct
{
	int id;
	char name[20];
}element;

element temp;
element list[100];//최대 100개까지만

				  //선택정렬
void selection_sort(element list[], int n, int(*compare)(int, int))
{
	int i, j, least;

	for (i = 0; i < n - 1; i++)
	{
		least = i;
		for (j = i + 1; j < n; j++)
		{
			if (!compare(list[j].id, list[least].id))
				least = j;
		}
		if (i != least)
			SWAP(list[i], list[least], temp);
	}
}

//삽입정렬
void insertion_sort(element list[], int n, int(*compare)(int, int))
{
	int i, j;
	element key;

	for (i = 1; i < n; i++)
	{
		key = list[i];
		for (j = i - 1; j >= 0 && compare(list[j].id, key.id); j--)
			list[j + 1] = list[j];
		list[j + 1] = key;
	}
}

//버블정렬
void bubble_sort(element list[], int n, int(*compare)(int, int))
{
	int i, j;

	for (i = n - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (compare(list[j].id, list[j + 1].id))
				SWAP(list[j], list[j + 1], temp);
		}
	}
}

//셸정렬
void inc_insertion_sort(element list[], int first, int last, int gap, int(*compare)(int, int))
{
	int i, j;
	element key;

	for (i = first + gap; i <= last; i += gap)
	{
		key = list[i];
		for (j = i - gap; j >= first && compare(list[j].id, key.id); j -= gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}
void shell_sort(element list[], int n, int(*compare)(int, int))
{
	int i, gap;

	for (gap = n / 2; gap > 0; gap /= 2)
	{
		if (gap % 2 == 0)
			gap++;
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap, compare);
	}
}

element sorted[100];
//합병정렬
void merge(element list[], int left, int mid, int right, int(*compare)(int, int))
{
	int i, j, k, l;

	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right)
	{
		if (!compare(list[i].id, list[j].id))
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	if (i > mid)
		for (l = j;l <= right;l++)
			sorted[k++] = list[l];
	else
		for (l = i;l <= mid; l++)
			sorted[k++] = list[l];

	for (l = left;l <= right;l++)
		list[l] = sorted[l];
}
void merge_sort(element list[], int left, int right, int(*compare)(int, int))
{
	int mid;

	if (left < right)
	{
		mid = (left + right) / 2;

		merge_sort(list, left, mid, compare);
		merge_sort(list, mid + 1, right, compare);
		merge(list, left, mid, right, compare);
	}
}

//퀵정렬
int partition(element list[], int left, int right, int(*compare)(int, int))
{
	element pivot;
	int low, high;

	//do while문 생각하면서 짜기
	low = left;
	high = right + 1;
	pivot = list[left];

	do
	{
		do
		{
			low++;
		} while (low <= high && !compare(list[low].id, pivot.id));
		do
		{
			high--;
		} while (high <= right && compare(list[high].id, pivot.id));

		if (low < high)
			SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);

	return high;
}
void quick_sort(element list[], int left, int right, int(*compare)(int, int))
{
	if (left < right)
	{
		int q = partition(list, left, right, compare);
		quick_sort(list, left, q - 1, compare);
		quick_sort(list, q + 1, right, compare);
	}
}

#endif SORT_H