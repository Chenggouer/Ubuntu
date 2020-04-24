#include<iostream>
#include<string>

class Solution
{
public:
	bool isSubstr(std::string& t, std::string& s) //is s a substring of t?
	{
		int si = 0;
		int tj = 0;
		int cnt = 0;
		bool flag = false;

		while(si < s.size() && tj < t.size())
		{
			if(s[si] == t[tj])
			{
				cnt++;
				si++;
				tj++;
			}
			else
			{
				tj++;
			}
		}
		if(cnt == s.size()) 
		  flag = true;
		
		return flag;
	}
};
int main()
{
	std::string s = "thinks";
	std::string t = "ivthkinkgdknhsq";
	Solution s1;

	std::cout << s1.isSubstr(t, s) << std::endl;

	return 0;
}
