/*n个集装箱装船，船最大载重为C
体积不考虑，设计算法，使得装船集装箱数目最大*/
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
class solution
{
public:
	int maxLoad(vector<double>& w, double c)
	{
		sort(w.begin(), w.end());
		double weight = 0;
		int num = 0;
		for(int i = 0; i < w.size(); i++)
		{
			weight += w[i];
			if(weight > c)
			{
				num = i;
				weight -= w[i];
				break;
			}
		}
		return num;
	}
};

int main()
{
	vector<double> w {2.0, 2.3, 9.0, 3.4, 5.7, 1.0, 6.0};
	double c = 10.0;
	solution s1;
	cout << s1.maxLoad(w,c) << endl;

	return 0;
}
