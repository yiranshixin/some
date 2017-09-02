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
