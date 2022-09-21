#include <stdio.h>
#include<vector>

using namespace std;

void bobleSort(int arr[], int num);
void selectsSort(int arr[], int num);
void insertSort(int arr[], int num);
void shellSort(int arr[], int num);
void merge_sort(int arr[]);
void merge_sort_recursive(int arr[], int reg[], int start, int end);
void quickSort(int arr[], int len);
void quick(int arr[], int start, int end);
void heap_sort(int arr[], int len);
void max_heapify(int arr[], int start, int end);


int main(void)
{
	int arr[10] = { 2,7,4,9,45,15,2,46,24,15 };
	for (int i = 0; i < 10; i++)
	{
		printf("arr[%d]=%d\n", i, arr[i]);
	}
	//shellSort(arr, 10);
	quickSort(arr,10);

	for (int i = 0; i < 10; i++)
	{
		printf("arr[%d]=%d\n", i, arr[i]);
	}
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void bobleSort(int arr[], int num)
{
	for (int i = 0; i < num - 1; ++i)
	{
		for (int j = i ; j < num - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
		}
	}
}

void selectsSort(int arr[], int num)
{
	for (int i = 0; i < num - 1; i++)
	{
		int minNum = i;
		for (int j = i + 1; j < num ; j++)
		{
			if (arr[j] < arr[minNum])
				minNum = j;
		}		
		swap(arr[i], arr[minNum]);
	}

}

void insertSort(int arr[], int num)
{
	for (int i = 0; i < num - 1; i++)
	{
		int j = i + 1;
		while (j >= 1 && arr[j] < arr[j-1])
		{
			swap(arr[j], arr[j - 1]);
			j--;
		}
	}
}

void shellSort(int arr[], int num)
{
	//首先设置分组，比较分组同位置大小，在缩小分组
	if (arr == NULL || num <= 1)
		return;
	for (int d = num / 2; d > 0; d /= 2)
	{
		for (int i = d; i < num; i++)
		{
			for (int j = i - d; j >= 0; j -= d)
			{
				if (arr[j] > arr[j + d])
					swap(arr[j], arr[j + d]);
			}
		}
	}
}

//递归法 归并排序
void merge_sort_recursive(int arr[], int reg[], int start, int end) {
	if (start >= end)
		return;
	int len = end - start, mid = (len >> 1) + start;
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	merge_sort_recursive(arr, reg, start1, end1);
	merge_sort_recursive(arr, reg, start2, end2);
	int k = start;
	while (start1 <= end1 && start2 <= end2)
		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
	while (start1 <= end1)
		reg[k++] = arr[start1++];
	while (start2 <= end2)
		reg[k++] = arr[start2++];
	for (k = start; k <= end; k++)
		arr[k] = reg[k];
}
void merge_sort(int arr[]) {
	int reg[10];
	merge_sort_recursive(arr, reg, 0, 9);
}
//迭代法 归并排序
int min(int x, int y) {
	return x < y ? x : y;
}
void merge_sort(int arr[], int len) {
	int* a = arr;
	int* b = (int*)malloc(len * sizeof(int));
	int seg, start;
	for (seg = 1; seg < len; seg += seg) {
		for (start = 0; start < len; start += seg * 2) {
			int low = start, mid = min(start + seg, len), high = min(start + seg * 2, len);
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2)
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
			while (start1 < end1)
				b[k++] = a[start1++];
			while (start2 < end2)
				b[k++] = a[start2++];
		}
		int* temp = a;
		a = b;
		b = temp;
	}
	if (a != arr) {
		int i;
		for (i = 0; i < len; i++)
			b[i] = a[i];
		b = a;
	}
	free(b);
}

//快排 当数组中左边的元素都比这个元素小，右边的元素都比这个元素大，该元素的位置就确认
void quick(int arr[], int start, int end) {
	if (start >= end)
		return;
	//设置中间值为数组最后一位
	int mid = arr[end];
	int left = start, right = end - 1;
	while (left < right) {
		while (arr[left] < mid && left < right)
			left++;
		while (arr[right] >= mid && left < right)
			right--;
		swap(arr[left], arr[right]);
	}

	if (arr[left] >= arr[end])
		swap(arr[left], arr[end]);
	else
		left++;
	if (left)
		quick(arr, start, left - 1);
	quick(arr, left + 1, end);
}
void quickSort(int arr[], int len) {
	quick(arr, 0, len - 1);
}

//堆排序
void max_heapify(int arr[], int start, int end) {
	// 建立父節點指標和子節點指標
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { // 若子節點指標在範圍內才做比較
		if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比較兩個子節點大小，選擇最大的
			son++;
		if (arr[dad] > arr[son]) //如果父節點大於子節點代表調整完畢，直接跳出函數
			return;
		else { // 否則交換父子內容再繼續子節點和孫節點比較
			swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}
void heap_sort(int arr[], int len) {
	int i;
	// 初始化，i從最後一個父節點開始調整
	for (i = len / 2 - 1; i >= 0; i--)
		max_heapify(arr, i, len - 1);
	// 先將第一個元素和已排好元素前一位做交換，再重新調整，直到排序完畢
	for (i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		max_heapify(arr, 0, i - 1);
	}
}

//基数排序
void counting_sort(int* ini_arr, int* sorted_arr, int n) {
	int* count_arr = (int*)malloc(sizeof(int) * 100);
	int i, j, k;
	for (k = 0; k < 100; k++)
		count_arr[k] = 0;
	for (i = 0; i < n; i++)
		count_arr[ini_arr[i]]++;
	for (k = 1; k < 100; k++)
		count_arr[k] += count_arr[k - 1];
	for (j = n; j > 0; j--)
		sorted_arr[--count_arr[ini_arr[j - 1]]] = ini_arr[j - 1];
	free(count_arr);
}

//基数排序
int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
	int maxData = data[0];              ///< 最大数
	/// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
	for (int i = 1; i < n; ++i)
	{
		if (maxData < data[i])
			maxData = data[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p)
	{
		//p *= 10; // Maybe overflow
		maxData /= 10;
		++d;
	}
	return d;
	/*    int d = 1; //保存最大的位数
		int p = 10;
		for(int i = 0; i < n; ++i)
		{
			while(data[i] >= p)
			{
				p *= 10;
				++d;
			}
		}
		return d;*/
}
void radixsort(int data[], int n) //基数排序
{
	int d = maxbit(data, n);
	int* tmp = new int[n];
	int* count = new int[10]; //计数器
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		for (j = 0; j < n; j++)
		{
			k = (data[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
		for (j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) //将临时数组的内容复制到data中
			data[j] = tmp[j];
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
}
