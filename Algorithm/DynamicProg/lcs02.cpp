/* 动态规划设计最长公共子序列 */
#include<iostream>
#include<string>
#include<algorithm>

using std::string;

string dp_lcs(const string& a,const string& b)
{
	int len_a=a.length();
	int len_b=b.length();
	std::cout << len_a;
	std::cout << " " << len_b <<std::endl; 
	int dp[len_b+1][len_a+1];
	for(int i=0;i<len_b+1;i++)
	  dp[i][0]=0;
	for(int j=1;j<len_a+1;j++)
	  dp[0][j]=0;

	int maxNum=0;
	for(int i=1;i<len_b+1;i++)
	{
		for(int j=1;j<len_a+1;j++)
		{
			if(a[j-1]==b[i-1]) { dp[i][j]=dp[i-1][j-1]+1;}
			else {dp[i][j]=(dp[i-1][j]>dp[i][j-1])? dp[i-1][j]:dp[i][j-1];}

			if(dp[i][j]>maxNum)
			  maxNum=dp[i][j];
		}
	}
    std::cout << maxNum << std::endl;

	for(int i=0;i<len_b+1;i++)
	{
		for(int j=0;j<len_a+1;j++)
		{
			std::cout << dp[i][j]<< " " ;
		}
		std::cout << "\n";
	}
	string substring="";
	int n=len_a,m=len_b;
	while(maxNum>=0)
	{
		if(a[n-1]==b[m-1]) 
		{
			substring+=a[n-1];
			--n;--m;
			--maxNum;
		}
		else
		{
			if(dp[m][n-1]>=dp[m-1][n]) { n--;}
			else {m--;}
		}
	}
	//std::cout << substring.size() << std::endl;
	reverse(substring.begin(),substring.end());
	//std::cout << "Text!";	
//    std::cout << substring << std::endl;

	return substring;
}

int main()
{
	string a{"demost"};
	string b{"demo"};

	string c=dp_lcs(a,b);

	std::cout << c << std::endl;


	return 0;

}

