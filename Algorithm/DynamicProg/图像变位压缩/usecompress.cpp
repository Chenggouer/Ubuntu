#include "compress.h"
#include<iostream>

int main()
{
	int p[] {10,12,15,255,1,2,1,1,2,2,1,1};
	int s[13] = {0};
	int l[13] = {0};
	int b[13] = {0};
	int c[13] = {0};
	int len;

	int n = sizeof(p)/sizeof(p[0]);
	compress(p,n,s,l,b);
	std::cout << s[n] << std::endl;
	len = Traceback(n,l,c);
	output(c, len, p);
	
	int g = length(2);
	std::cout << g << std::endl;

	return 0;
}
