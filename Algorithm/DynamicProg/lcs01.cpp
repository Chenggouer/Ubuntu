/* 递归法设计最长公共子序列 */
#include<iostream>
#include<string>
using std::string;

int max1(int a,int b)
{
	return (a>b)? a:b;
}
string max2(string a,string b)
{
	return (a.length()>b.length())? a:b;
}
int lcs(const string& a,const string& b,int n,int m)
{
	if(n==0 || m==0)
	{
		return 0;
	}
	if(a[n]==b[m])
	{
		return lcs(a,b,n-1,m-1)+1;
	}
	if(a[n]!=b[m])
	{
		return max1(lcs(a,b,n-1,m),lcs(a,b,n,m-1));
	}
}

string lcs2(string& a,string& b,int n,int m)
{
	if(n==-1 || m==-1)
	{
		return "";
	}
	if(a[n]==b[m])
	{
		return lcs2(a,b,n-1,m-1)+a[n];
	}
	if(a[n]!=b[m])
	{
		return max2(lcs2(a,b,n-1,m),lcs2(a,b,n,m-1));
	}
}

int main()
{
	string a{"demstrate"};
	string b{"demo"};
	int n=lcs(a,b,a.length(),b.length());
	std::cout << "length of sub:" << n << std::endl;
	string c=lcs2(a,b,a.length(),b.length());
	std::cout << c << std::endl;
	return 0;
}
