/* 数组p为某图片各像素点的灰度值，将p分成m段
 * 设第t段有l[t]个像素点（每一段最大不超过255，则用8位二进制数表示）
 * 每个像素点灰度值用b[t]位来表示（b[t] 1~8 用三位二进制数表示）
 * 没段段头记录l[t]与b[t]需要11bit
 * 该图片共计需要b[1]l[1].b[2]l[2]...b[m]l[m]+11m 个bit来存储
 * 使用动态规划 */
#include "compress.h"
#include<iostream>
#include<cmath>

int length(int a)
{
	int k = 1;
	a = a/2;
	while(a>0)
	{
		k++;
		a /= 2;
	}
	return k;
}
void compress(int* p, int n, int* s, int* l, int* b)
{
	int lmax = 256, header = 11;
	int bmax;
	s[0] = 0;

	for(int i = 1; i <= n; i++)
	{
		b[i] = length(p[i-1]);
		bmax = b[i];
		s[i] = s[i-1] + bmax;
		l[i] = 1;

		for(int j = 2; j <= (i < 256 ? i : lmax); j++)
		{
			if(bmax < b[i-j+1])
			  bmax = b[i-j+1];
			if(s[i] > s[i-j] + j*bmax)
			{
				s[i] = s[i-j] + j*bmax;
				l[i] = j;
			}
		}
		s[i] = s[i] + header;
	}
}

int Traceback(int n, int* l, int* c)
{
	int j = 0;
	while(n != 0)
	{
		c[j++] = l[n];
		n = n - l[n];
	}
	return j;
}

void output(int* c, int len_c, int* p)
{
	int k = 0;
	for(int i = len_c-1; i >= 0; i--)
	{
		for(int j = 0; j < c[i]; j++)
		{
			std::cout << p[k++] << " ";
		}  
		std::cout << std::endl;
	}
}
