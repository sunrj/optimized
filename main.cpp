#include "graph.h"

int main()
{
	Graph g;
	string file1 = "58228.txt", file2 = "58228_300_10-99.txt", file3 = "58228_300_10-99bing.txt", file4 = "58228_300_10-99jiao.txt";
	for (int i = 0; i < 300; i++) //这个数值是总的属性个数，用不同的数据集要改的
		g.allAttribute.push_back(i);
	g.dataInput(file1, file2, file3, file4);
	double algStartTime = (double)clock() / CLOCKS_PER_SEC;
	vector<int> A = {};
	A = g.optimized(0.1, 20);
	double runtime = (double)clock() / CLOCKS_PER_SEC - algStartTime;
	cout << "Runtime = " << runtime << endl;
	cout << "A.size = " << A.size() << endl;
	vector<int>::iterator o = A.begin();
	for (; o != A.end(); o++)
	{
		cout << *o << " ";
	}
	cout << endl;
	system("pause");

	/*set<int> te = { 57,194,92,330,249,53,204,80,322,101,24,299,346,94,213,187 };
	cout << g.comVerWonV(242, {19,11}, te) << endl;*/


	/*for (int i = 0; i < 20; i++)
		g.Aa.insert(i);
	g.dataInput();
	cout << "test1" << endl;
	g.getEachVi();
	cout << "test2" << endl;
	g.getEachWiCore(1);
	cout << "test3" << endl;

	int a = g.comWcoreOnV(1, { 3,11 }, g.getUnion(g.Vi[3], g.Vi[11])).size();
	cout << a << endl;*/
	return 0;
}