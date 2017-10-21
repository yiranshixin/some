void bubble_sort(int a[], int len) 
{
	int tmp = 0;
	for(int i = 0;i<len - 1; i++)
	{
		for (int j = 0; j < len-i-1; j++)
		{
			if (a[j] > a[j + 1]) 
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}

void select_sort(int a[], int len)
{
	int i, j, min,tmp;

	for (i = 0; i < len - 1; i++)
	{
		min = i;
		for (j = i + 1; j < len; j++)
		{
			if (a[j] < a[min])
			{
				min = j;
			}
		}

		tmp = a[i];
		a[i] = a[min];
		a[min] = tmp;
	}
}


void insert_sort(int a[], const int len)
{
	int i, j, k;
	for (i = 1; i < len; ++i)
	{
		k = a[i];
		j = i - 1;
		while ((j >= 0) && (k < a[j]))
		{
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = k;
	}
}

void binary_sort(int a[], int l, int r)
{
	int ll = l, rr = r;
	if(l < r)
	{
		int x = a[ll];
		while (ll < rr)
		{

			while (rr > ll || a[rr] > x)
			{
				rr--;
			}

			if (ll < rr)
			{
				a[ll] = a[rr];
			}

			while (ll < rr && a[ll] < x)
			{
				ll++;
			}

			if (ll < rr)
			{
				a[rr] = a[ll];
			}
		}

		a[ll] = x;
		binary_sort(a, l, rr - 1);
		binary_sort(a, ll + 1, r);
	}
}




void findNumAppearOnce(int data[], int length, int *num)
{
	int i = 1;
	int r = data[0];
	while (i < length)
	{
		r ^= data[i++];
	}

	*num = r;
}

void findNumsAppearOnce2(int data[], int length, int *num1, int *num2) 
{
	int i = 1;
	int r = data[0];

	int k = 0;

	while (i < length)
	{
		r ^= data[i++];
	}

	int r1 = r, r2 = r;
	while (!(r & 1 << k)) 
	{
		k++;
	}

	i = 0;
	while (i< length)
	{
		if (data[i] & 1 << k) 
		{
			r1 ^= data[i];
		}
		else 
		{
			r2 ^= data[i];
		}
	}

	*num1 = r1;
	*num2 = r2;
}

#include <vector>
void findNumsAppearOnce3(int data[], int length, int *num1, int *num2, int *num3)
{
	int r1 = 0;
	findNumAppearOnce(data, length, &r1);
	int k = 0;
	while (!(r1 & 1 << k))
	{
		k++;
	}
	
	vector<int> d1;
	vector<int> d2;
	int i = 0;
	while (i < length)
	{
		if (data[i] & 1 << k) 
		{
			d1.push_back(data[i]);
		}
		else
		{
			d2.push_back(d2[i]);
		}
	}

	if (d1.size()%2 == 0)
	{//两个不一样
		findNumsAppearOnce2(&d1[0], d1.size(), num1, num2);
		findNumAppearOnce(&d2[0], d2.size(), num3);
	}
	else
	{//一个不一样
		findNumsAppearOnce2(&d2[0], d2.size(), num1, num2);
		findNumAppearOnce(&d1[0], d1.size(), num3);
	}
}

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void AllRange(char *pszStr, int k, int m)
{
	if (k == m)
	{
		static int s_i = 1;
		printf("  第%3d个排列\t%s\n", s_i++, pszStr);
	}
	else
	{
		for (int i = k; i <= m; i++)
		{
			swap(pszStr + k, pszStr + i);
			AllRange(pszStr, k + 1, m);
			swap(pszStr + k, pszStr + i);
		}
	}
}
