/* 小朋友对饼干的渴望度由g来表示
 * 饼干大小由S标记。给定饼干数，及其大小
 * 设计算法，满足最多小盆友对饼干的渴望 */
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
class solution
{
public:
	int findContentChild(vector<int>& g, vector<int>& s)
	{
		sort(s.begin(), s.end(), greater<int>());
		sort(g.begin(), g.end(), greater<int>());

		int i = 0, j = 0, cnt = 0;
		while(j < g.size() && i < s.size())
		{
			if(s[i] >= g[j])
			{
				cnt++;
				i++;
				j++;
			}
			else {j++;}
		}
		return cnt;
	}
};

int main()
{
	vector<int> s = {1,3,2,6,8,4};
	vector<int> g = {1,4,2,3,5,6,7};
    solution s1;
	int num =s1. findContentChild(g, s);
	cout << "content child number is :" << num << endl;

	return 0;
}
