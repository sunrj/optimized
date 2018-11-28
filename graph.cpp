#include "graph.h"

void stringTOnum1(string s, vector<int> &out)//把从属性文件中读取的属性数据存到节点的属性vector中
{
	bool temp = false;//读取一个数据标志位
	int data = 0;//分离的一个数据
	for (int i = 0; i < s.length(); i++)
	{
		while ((s[i] >= '0') && (s[i] <= '9'))//当前字符是数据，并一直读后面的数据，只要遇到不是数字为止
		{
			temp = true;//读数据标志位置位
			data *= 10;
			data += (s[i] - '0');//字符在系统以ASCII码存储，要得到其实际值必须减去‘0’的ASCII值
			i++;
		}
		//刚读取了数据
		if (temp)//判断是否完全读取一个数据
		{
			vector<int>::iterator te;
			te = find(out.begin(), out.end(), data);
			if (te == out.end())
				out.push_back(data);
			data = 0;
			temp = false;//标志位复位
		}
	}
}

void stringTOnum2(string s, unordered_set<int> &out)//把从属性文件中读取的属性数据存到节点的属性vector中
{
	bool temp = false;//读取一个数据标志位
	int data = 0;//分离的一个数据
	for (int i = 0; i < s.length(); i++)
	{
		while ((s[i] >= '0') && (s[i] <= '9'))//当前字符是数据，并一直读后面的数据，只要遇到不是数字为止
		{
			temp = true;//读数据标志位置位
			data *= 10;
			data += (s[i] - '0');//字符在系统以ASCII码存储，要得到其实际值必须减去‘0’的ASCII值
			i++;
		}
		//刚读取了数据
		if (temp)//判断是否完全读取一个数据
		{
			unordered_set<int>::iterator te;
			te = find(out.begin(), out.end(), data);
			if (te == out.end())
				out.insert(data);
			data = 0;
			temp = false;//标志位复位
		}
	}
}

void quickSort(vector<int> &R, int low, int high)//给vector<int> 按照递增的顺序排序
{
	if (low < high) {
		int i = low, j = high, temp = R[low];

		while (i < j) {
			while (i < j && R[j] >= temp) {
				--j;
			}
			if (i < j) {
				R[i++] = R[j];
			}
			while (i < j && R[i] <= temp) {
				++i;
			}
			if (i < j) {
				R[j--] = R[i];
			}
		}
		R[i] = temp;
		quickSort(R, low, i - 1);
		quickSort(R, i + 1, high);
	}
}

int BinarySearch(vector<int> &a, int value, int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (a[mid] == value)
			return 1;
		if (a[mid] > value)
			high = mid - 1;
		if (a[mid] < value)
			low = mid + 1;
	}
	return 0;
}

void Graph::dataInput(string edge_file, string attribute_file, string union_file, string intersec_file)
{
	int n = 0, m = 0;//n存放节点的个数，m存放边的个数
	string s = {};
	ifstream infile1, infile2, infile3, infile4;
	infile1.open(edge_file);
	infile2.open(attribute_file);
	infile3.open(union_file);
	infile4.open(intersec_file);
	infile1 >> n >> m;
	for (int i = 0; i < n; i++)//创建节点并初始化节点的各个属性
	{
		vector<int> id;
		vector<float> w;
		vector<vector<int>> se;
		vector<vector<float>> we;
		id.push_back(i);//先把节点创建出来，把节点的id存到vector<vector<int>>行首
		vertex.push_back(id);//先把节点创建出来
		attributeUnionInt.push_back(id);
		se.push_back(id);
		attributeIntersecSet.push_back(se);
		w.push_back(i);
		we.push_back(w);
		edgeWeightOnEachAtt.push_back(we);
		tempEdgeWeight.push_back(w);
		edgeWeightOnA0.push_back(w);
		countdownInt.push_back(0);
		donotAccessNow.push_back(0);
		dwSum.push_back(0.0);
		exist.push_back(1);//初始化第i个节点的exist属性为1
		mustDelete.push_back(0);//初始化第i个节点的mustDelete属性为0
		explored.push_back(0);
		survived.push_back(1);
		inH.push_back(0);
		inNowWcore.push_back(0);
		inNowSearchRange.push_back(0);
		weight.push_back(0.0);//初始化第i个节点的weight属性为0.0
		upWeight.push_back(0.0);//初始化第i个节点的upWeight属性为0.0

		//srand(time(0));

		/**************************
		下面的代码是在创建节点时随机生成节点的属性
		*************************/
		/*int r1 = 20, r2 = 20;//这个r1是想要随机为节点生成的属性个数的最大值，这个r2是想要随机生成的属性的种类

		int z = (double)rand() / (RAND_MAX + 1) * r1;//这个20是想要随机为节点生成的属性个数的最大值

		for (int k = 0; k <= z; k++)
		{
			int u = (double)rand() / (RAND_MAX + 1) * r2; // RAND_MAX = 32767
			vex.attribute.insert(u);
		}*/


		/**************************
		下面的代码是从infile2中读取每个节点的属性
		*************************/
		vector<int> att;
		getline(infile2, s);
		stringTOnum1(s, att);//获取节点i的属性
		sort(att.begin(), att.end());//把节点的属性按照从小到大排列
		//quickSort(att, 0, att.size() - 1);
		attribute.push_back(att);//把节点i的属性存进去
	}
	infile2.close();
	int id1, id2, unionInt;
	for (int j = 0; j < m; j++)//遍历所有的边，存入各个节点的邻居节点，与对应邻居的属性的UnionInt值，IntersecSet集合。默认是边的数据集里面既有(0,1)也有(1,0)，并且第一个节点按序排列
	{
		infile1 >> id1 >> id2;
		infile3 >> unionInt;

		//unordered_set<int> in = {};
		vector<int> in = {};
		getline(infile4, s);
		stringTOnum1(s, in);

		vertex[id1].push_back(id2);
		tempEdgeWeight[id1].push_back(0.0);
		edgeWeightOnA0[id1].push_back(0.0);
		attributeUnionInt[id1].push_back(unionInt);
		attributeIntersecSet[id1].push_back(in);

		/*vector<int>::iterator te1, te2;

		te1 = find(vertex[id1].begin(), vertex[id1].end(), id2);
		if (te1 == vertex[id1].end())
		{
			float w = 0.0;
			tempEdgeWeight[id1].push_back(w);
			vertex[id1].push_back(id2);
		}

		te2 = find(vertex[id2].begin(), vertex[id2].end(), id1);
		if (te2 == vertex[id2].end())
		{
			float w = 0.0;
			tempEdgeWeight[id2].push_back(w);
			vertex[id2].push_back(id1);
		}*/
	}
	//for (int k = 0; k < allAttribute.size(); k++)
	//{
	//	vector<int> att;
	//	getline(infile5, s);
	//	stringTOnum1(s, att);//获取属性k包含的节点集
	//	Vi.push_back(att);
	//}

	//vector<vector<int>>::iterator vex = vertex.begin();
	//for (; vex != vertex.end(); vex++)
	//{
	//	sort(vex->begin() + 1, vex->end());//把节点的邻居按照从小到大排序
	//	//quickSort(*vex, 1, vex->size() - 1);
	//}
	infile1.close();
	infile3.close();
	infile4.close();
	//infile5.close();
}

vector<int> Graph::getVi(int aId)
{
	vector<int> V = {};
	for (int i = 0; i < attribute.size(); i++)
	{
		if (!mustDelete[i] && BinarySearch(attribute[i], aId, attribute[i].size()))
		{
			V.push_back(i);
		}
	}
	return V;
}

void Graph::getEachVi()
{
	vector<int>::iterator aId;
	for (aId = allAttribute.begin(); aId != allAttribute.end(); aId++)
	{
		cout << "getV" << *aId << endl;
		Vi.push_back(getVi(*aId));
	}

}

void Graph::getEachWiCore(float w)
{
	vector<int>::iterator aId;
	for (aId = allAttribute.begin(); aId != allAttribute.end(); aId++)
	{
		cout << "getW" << *aId << "core ";
		vector<int> reexist = {};
		double algStartTime = (double)clock() / CLOCKS_PER_SEC;
		WiCore.push_back(comWcoreOnV(w, *aId, Vi[*aId], reexist));
		double runtime = (double)clock() / CLOCKS_PER_SEC - algStartTime;
		cout << "runtime = " << runtime << endl;
		existReset(reexist);
	}
}

void Graph::existReset(vector<int> reexist)
{
	for (int i = 0; i < reexist.size(); i++)
	{
		exist[reexist[i]] = 1;
	}
}

vector<int> Graph::getIntersection(vector<int> A, vector<int> B)
{
	vector<int> result = {};
	int i = 0, j = 0;
	while (i < A.size() && j < B.size())
	{
		if (A[i] > B[j])
			j++;
		else if (A[i] < B[j])
			i++;
		else
		{
			result.push_back(A[i]);
			i++;
			j++;
		}
	}
	return result;
}

vector<int> Graph::getUnion(vector<int> A, vector<int> B)
{
	vector<int> result = {};
	int i = 0, j = 0;
	while (i < A.size() && j < B.size())
	{
		if (A[i] > B[j])
		{
			result.push_back(B[j]);
			j++;
		}
		else if (A[i] < B[j])
		{
			result.push_back(A[i]);
			i++;
		}
		else
		{
			result.push_back(A[i]);
			i++;
			j++;
		}
	}
	while (i < A.size())
	{
		result.push_back(A[i]);
		i++;
	}
	while (j < B.size())
	{
		result.push_back(B[j]);
		j++;
	}
	return result;
}

vector<int> Graph::getDifference(vector<int> A, vector<int> B)
{
	vector<int> result = {};
	int i = 0, j = 0;
	while (i < A.size() && j < B.size())
	{
		if (A[i] > B[j])
			j++;
		else if (A[i] < B[j])
		{
			result.push_back(A[i]);
			i++;
		}
		else
		{
			i++;
			j++;
		}
	}
	while (i < A.size())
	{
		result.push_back(A[i]);
		i++;
	}
	return result;
}

float Graph::computeEdgeWeight(int id1, int count, vector<int> A)
{
	float result = 0.0;
	vector<int> temp = {}, molecule = {};
	//unordered_set<int> temp = {};
	//temp = getIntersection(attribute[id1], attribute[id2]);
	temp = attributeIntersecSet[id1][count];
	molecule = getIntersection(temp, A);
	//denominator = getUnion(attribute[id1], attribute[id2]);
	//result = float(molecule.size()) / float(denominator.size());
	result = float(molecule.size()) / float(attributeUnionInt[id1][count]);
	return result;//保留小数点后三位
}

float Graph::comVerWonV(int id, int attributeId, vector<int> V)
{
	int count = 0;
	float result = 0.0;
	vector<int>::iterator nei;
	for (nei = vertex[id].begin() + 1; nei != vertex[id].end(); nei++)
	{
		count++;
		if (BinarySearch(V, *nei, V.size()))//!mustDelete[*nei] && inNowWcore[*nei] || 
		{
			//float temp = computeEdgeWeight(id, *nei, A);
			//float temp = computeEdgeWeight(id, count, A);
			float temp = edgeWeightOnEachAtt[id][count][attributeId];
			tempEdgeWeight[id][count] = temp;
			result = result + temp;
		}
	}
	return result;
}

void Graph::getcountdownInt(float w)
{
	for (int i = 0; i < countdownInt.size(); i++)
	{
		float temp = 0.0;
		int count = 0;
		if (!mustDelete[i])
		{
			vector<int>::iterator nei;
			for (nei = vertex[i].begin() + 1; nei != vertex[i].end(); nei++)
			{
				count++;
				if (!mustDelete[*nei])
				{
					/*set<int> runion = {};
					runion = Graph::getUnion(vex->attribute, vertex[*nei].attribute);
					temp = temp + 1.0 / float(runion.size());*/
					temp = temp + 1.0 / float(attributeUnionInt[i][count]);
				}
			}
			dwSum[i] = temp;
			countdownInt[i] = w / temp + 1;
		}
	}
}

void Graph::countdown(float w, int ith, vector<float> dwSum, vector<int> &redonotAccessNow)
{
	queue<int> notAccess = {};
	for (int i = 0; i < countdownInt.size(); i++)
	{
		if (countdownInt[i] > 0)
		{
			notAccess.push(i);
			donotAccessNow[i] = 1;
			redonotAccessNow.push_back(i);
		}
	}
	int notAccessId;
	while (!notAccess.empty())
	{
		int count = 0;
		notAccessId = notAccess.front();
		notAccess.pop();
		vector<int>::iterator nei;
		for (nei = vertex[notAccessId].begin() + 1; nei != vertex[notAccessId].end(); nei++)
		{
			count++;
			if (!mustDelete[*nei] && !donotAccessNow[*nei])
			{
				dwSum[*nei] = dwSum[*nei] - 1.0 / float(attributeUnionInt[notAccessId][count]);
				if (w / dwSum[*nei] > ith)
				{
					notAccess.push(*nei);
					donotAccessNow[*nei] = 1;
					redonotAccessNow.push_back(*nei);
				}
			}
		}
	}
}

void Graph::getedgeWeightOnEachAtt()
{
	for (int i = 0; i < edgeWeightOnEachAtt.size(); i++)
	{
		double algStartTime2 = (double)clock() / CLOCKS_PER_SEC;
		int count = 0;
		if (mustDelete[i])
		{
			vector<int>::iterator nei;
			for (nei = vertex[i].begin() + 1; nei != vertex[i].end(); nei++)
			{
				count++;
				vector<float> edgeWeight = {};
				for (int j = 0; j < allAttribute.size(); j++)
				{
					edgeWeight.push_back(0.0);
				}
				edgeWeightOnEachAtt[i].push_back(edgeWeight);
			}
		}
		else
		{
			vector<int>::iterator nei;
			for (nei = vertex[i].begin() + 1; nei != vertex[i].end(); nei++)
			{
				count++;
				if (mustDelete[*nei])
				{
					vector<float> edgeWeight = {};
					for (int j = 0; j < allAttribute.size(); j++)
					{
						edgeWeight.push_back(0.0);
					}
					edgeWeightOnEachAtt[i].push_back(edgeWeight);
				}
				else
				{
					vector<float> edgeWeight = {};
					for (int j = 0; j < allAttribute.size(); j++)
					{
						float weight = 0.0;
						weight = Graph::computeEdgeWeight(i, count, { j });
						edgeWeight.push_back(weight);
					}
					edgeWeightOnEachAtt[i].push_back(edgeWeight);
				}
			}
		}
		double runtime2 = (double)clock() / CLOCKS_PER_SEC - algStartTime2;
		cout << i << "  runtime = " << runtime2 << endl;
	}
}

void Graph::vertexDeletion(float w, int b)
{
	queue<int> delVertexId = {};
	for (int i = 0; i < upWeight.size(); i++)//先遍历所有的节点，查看是否有节点的weight upbound小于w，有的话就放入队列中，并把节点的mustDelete属性设置为true
	{
		float w_v = 0.0;
		int count = 0;
		vector<int>::iterator nei;
		for (nei = vertex[i].begin() + 1; nei != vertex[i].end(); nei++)
		{
			count++;
			vector<int> rintersec = {};
			int runion;
			//rintersec = getIntersection(attribute[i], attribute[*nei]);
			//runion = getUnion(attribute[i], attribute[*nei]); 
			rintersec = attributeIntersecSet[i][count];
			runion = attributeUnionInt[i][count];
			if (rintersec.size() < b)
			{
				tempEdgeWeight[i][count]= float(rintersec.size()) / float(runion);
				w_v = w_v + float(rintersec.size()) / float(runion);
			}
			else
			{
				tempEdgeWeight[i][count] = float(b) / float(runion);
				w_v = w_v + float(b) / float(runion);
			}
		}
		upWeight[i] = w_v;
		if (w_v < w)
		{
			mustDelete[i] = 1;
			exist[i] = 0;
			delVertexId.push(i);
		}
	}
	int delId;
	while (!delVertexId.empty())//把在对列中的节点出队并更新其所有mustDelete属性为false的邻居节点的weight upbound，如果其邻居节点的weight upbound更新之后小于w，则入队并把节点的mustDelete属性设置为true
	{
		int count = 0;
		delId = delVertexId.front();
		delVertexId.pop();
		vector<int>::iterator nei;
		for (nei = vertex[delId].begin() + 1; nei != vertex[delId].end(); nei++)
		{
			count++;
			if (!mustDelete[*nei])
			{
				/*vector<int> rintersec = {}, runion = {};
				rintersec = getIntersection(attribute[delId], attribute[*nei]);
				runion = getUnion(attribute[delId], attribute[*nei]);
				if (rintersec.size() < b)
				{
					upWeight[*nei] = upWeight[*nei] - float(rintersec.size()) / float(runion.size());
				}
				else
				{
					upWeight[*nei] = upWeight[*nei] - float(b) / float(runion.size());
				}*/
				upWeight[*nei] = upWeight[*nei] - tempEdgeWeight[delId][count];
				if (upWeight[*nei] < w)
				{
					mustDelete[*nei] = 1;
					exist[*nei] = 0;
					delVertexId.push(*nei);
				}
			}
		}
	}
}

vector<int> Graph::comWcoreOnV(float w, int attributeId, vector<int> V, vector<int> &reexist)
{
	vector<int> result = {};
	queue<int> delVertexId = {};//用队列存储所有不满足条件的节点的id
	for (int i = 0; i < weight.size(); i++)
	{
		if (!mustDelete[i])
		{
			weight[i] = comVerWonV(i, attributeId, V);//计算了节点集V中的所有存在节点在V集范围内的weight
			if (weight[i] < w)
			{
				exist[i] = 0;
				delVertexId.push(i);
			}
		}
	}
	int delId;
	while (!delVertexId.empty())
	{
		int count = 0;
		delId = delVertexId.front();
		delVertexId.pop();
		vector<int>::iterator nei;
		for (nei = vertex[delId].begin() + 1; nei != vertex[delId].end(); nei++)
		{
			count++;
			if (exist[*nei] && BinarySearch(V, *nei, V.size()))//!mustDelete[*nei] && 
			{
				//weight[*nei] = weight[*nei] - computeEdgeWeight(delId, *nei, A);
				weight[*nei] = weight[*nei] - tempEdgeWeight[delId][count];
				if (weight[*nei] < w)
				{
					exist[*nei] = 0;
					delVertexId.push(*nei);
				}
			}
		}
	}
	for (int i = 0; i < exist.size(); i++)//计算剩下的依然存在的节点的个数就是在节点集V中满足attribute weighted core条件的节点集
	{
		if (!mustDelete[i])
		{
			if (exist[i])
			{
				result.push_back(i);
			}
			else
				reexist.push_back(i);
		}
	}
	return result;
}

vector<int> Graph::getCounter(vector<int> V, vector<int> VanchorSet, float w, int x)//vector<int> A
{
	vector<int> result = {};
	queue<int> H = {};
	vector<int>::iterator Van;
	for (Van = VanchorSet.begin(); Van != VanchorSet.end(); Van++)//把锚点集的所有在搜索范围内且不属于Wcore的邻居放入队列H中
	{
		vector<int>::iterator nei;
		for (nei = vertex[*Van].begin() + 1; nei != vertex[*Van].end(); nei++)
		{
			if (!inNowWcore[*nei] && !inH[*nei] && inNowSearchRange[*nei])//可能是这个范围不对的影响********* !mustDelete[*nei] && 
			{
				H.push(*nei);
				inH[*nei] = 1;
			}
		}
	}
	while (!H.empty())
	{
		int u = H.front();
		H.pop();
		explored[u] = 1;
		upWeight[u] = Graph::computeUpWeight(u, x);
		if (upWeight[u] >= w)
		{
			survived[u] = 1;
			vector<int>::iterator nei;
			for (nei = vertex[u].begin() + 1; nei != vertex[u].end(); nei++)
			{
				if (!inNowWcore[*nei] && !inH[*nei] && inNowSearchRange[*nei] && !explored[*nei])//!mustDelete[*nei] && 
				{
					H.push(*nei);
					inH[*nei] = 1;
				}
			}
		}
		else
		{
			survived[u] = 0;
			Graph::Shrink(u, w);
		}
	}
	vector<int>::iterator v = V.begin();
	for (; v != V.end(); v++)
	{
		if (inNowWcore[*v] || (explored[*v] && survived[*v]))//后面一个条件应该可以用不加 && !mustDelete[*v]
			result.push_back(*v);
	}
	return result;
}

vector<int> Graph::forU(vector<int> V, vector<int> unexploredV, float w, int x, vector<int> &reexist)
{
	vector<int> result = {};
	queue<int> H = {};
	vector<int>::iterator unv = unexploredV.begin();
	for (; unv != unexploredV.end(); unv++)
	{
		H.push(*unv);
		inH[*unv] = 1;
	}
	while (!H.empty())
	{
		int u = H.front();
		H.pop();
		explored[u] = 1;
		upWeight[u] = Graph::computeUpWeight(u, x);
		if (upWeight[u] >= w)
		{
			survived[u] = 1;
			vector<int>::iterator nei;
			for (nei = vertex[u].begin() + 1; nei != vertex[u].end(); nei++)
			{
				if (!inNowWcore[*nei] && !inH[*nei] && inNowSearchRange[*nei] && !explored[*nei])//!mustDelete[*nei] && 
				{
					H.push(*nei);
					inH[*nei] = 1;
				}
			}
		}
		else
		{
			survived[u] = 0;
			Graph::Shrink(u, w);
		}
	}
	vector<int>::iterator v = V.begin();
	for (; v != V.end(); v++)
	{
		reexist.push_back(*v);
		if (inNowWcore[*v] || (explored[*v] && survived[*v]))//后面一个条件应该可以用不加 && !mustDelete[*v]
			result.push_back(*v);
	}
	return result;
}

void Graph::Shrink(int id, float w)
{
	int count = 0;
	vector<int> delId = {};//存储更改节点权重后不满足权重条件的节点id
	vector<int>::iterator nei;
	for (nei = vertex[id].begin() + 1; nei != vertex[id].end(); nei++)
	{
		count++;
		if (explored[*nei] && survived[*nei])//后面两个条件应该可以用不加 && inNowSearchRange[*nei] && !inNowWcore[*nei] !mustDelete[*nei] && 
		{
			//upWeight[*nei] = upWeight[*nei] - Graph::computeEdgeWeight(id, *nei, A);
			upWeight[*nei] = upWeight[*nei] - tempEdgeWeight[id][count];
			if (upWeight[*nei] < w)
			{
				survived[*nei] = 0;
				delId.push_back(*nei);
			}
		}
	}
	vector<int>::iterator de = delId.begin();
	for (; de != delId.end(); de++)
	{
		Graph::Shrink(*de, w);
	}
}

float Graph::computeUpWeight(int id, int x)//vector<int> A
{
	int count = 0;
	float result = 0.0;
	vector<int>::iterator nei;
	for (nei = vertex[id].begin() + 1; nei != vertex[id].end(); nei++)
	{
		count++;
		if (inNowSearchRange[*nei])//!mustDelete[*nei] && 
		{
			if (inNowWcore[*nei] || !explored[*nei] || survived[*nei])
			{
				//float temp = Graph::computeEdgeWeight(id, count, A);
				float temp = edgeWeightOnA0[id][count] + edgeWeightOnEachAtt[id][count][x];
				tempEdgeWeight[id][count] = temp;
				result = result + temp;
			}
		}
	}
	return result;
}

void Graph::vertexReset(vector<int> reexist)
{
	for (int i = 0; i < reexist.size(); i++)
	{
		exist[reexist[i]] = 1;
		explored[reexist[i]] = 0;
		survived[reexist[i]] = 1;
		inH[reexist[i]] = 0;
		inNowWcore[reexist[i]] = 0;
		inNowSearchRange[reexist[i]] = 0;
		upWeight[reexist[i]] = 0.0;
		weight[reexist[i]] = 0.0;
	}
}

void Graph::donotAccessNowReset(vector<int> redonotAccessNow)
{
	for (int i = 0; i < redonotAccessNow.size(); i++)
	{
		donotAccessNow[redonotAccessNow[i]] = 0;
	}
}

void put_out(vector<int> &p) {
	vector<int>::iterator it = p.begin();
	while (it != p.end()) {
		cout << *it << " ";
		it++;
	}
}

vector<int> Graph::optimized(float w, int b)
{
	
	vector<int> A = {}, Adiff = {}, VCA = {}, CWc = {};//VCA存放的是当前最优解覆盖的点集，CWc存放当前最优属性集下的wrighted core

	cout << "vertexdeletion_begin" << endl;
	double algStartTime1 = (double)clock() / CLOCKS_PER_SEC;
	Graph::vertexDeletion(w, b);
	double runtime1 = (double)clock() / CLOCKS_PER_SEC - algStartTime1;
	cout << "vertexdeletion_end " << "runtime = " << runtime1 << endl;

	cout << "getedgeWeightOnEachAtt_begin" << endl;
	double algStartTime2 = (double)clock() / CLOCKS_PER_SEC;
	Graph::getedgeWeightOnEachAtt();
	double runtime2 = (double)clock() / CLOCKS_PER_SEC - algStartTime2;
	cout << "getedgeWeightOnEachAtt_end " << "runtime = " << runtime2 << endl;

	Graph::getEachVi();
	Graph::getEachWiCore(w);
	Graph::getcountdownInt(w);
	for (int i = 0; i < b; i++)
	{

		for (int j = 0; j < countdownInt.size(); j++)
			countdownInt[j]--;

		vector<int> redonoAccessNow = {};

		Graph::countdown(w, i, dwSum, redonoAccessNow);

		int x = 0, count = 0;//x存放当前最好的属性，count表示当前最好的属性集所生成的attribute wrighted core的size
		vector<int> cBestWcore = {};//cBestWcore存放当前最好的wrighted core
		//Adiff = Graph::getDifference(allAttribute, A);//Adiff存放candidate属性
		//vector<PAIR> sCan = Graph::sortCandidateAttribute(Adiff, VCA);

		//map<int, int> sCan = Graph::test(Adiff, VCA);
		//map<int, int>::iterator sc;

		vector<int>::iterator sc;

		for (sc = allAttribute.begin(); sc != allAttribute.end(); sc++)
		{
			//if (sc->second < count)//如果当前属性的查找范围小于当前最优的attribute wrighted core的size就可以不用再去访问以后的所有属性
				//break;
			if (*sc == -1)
				continue;
			double algStartTime = (double)clock() / CLOCKS_PER_SEC;
			vector<int> nV = Graph::getUnion(VCA, Vi[*sc]);
			vector<int>::iterator temp1 = nV.begin();
			for (; temp1 != nV.end(); temp1++)//把在当前查找范围内的节点inNowSearchRange属性值设为true
			{
				if (!mustDelete[*temp1] && !donotAccessNow[*temp1])
					inNowSearchRange[*temp1] = 1;
			}

			vector<int> nVcore = {};
			nVcore = Graph::getUnion(CWc, WiCore[*sc]);
			vector<int>::iterator temp2 = nVcore.begin();
			for (; temp2 != nVcore.end(); temp2++)//把在当前查找范围内必定存在于Wcore的节点inNowWcore属性值设为true  explored[*temp2] = 1;survived[*temp2] = 1;
			{
				inNowWcore[*temp2] = 1;
			}

			vector<int> te = Graph::getIntersection(VCA, Vi[*sc]);
			vector<int> VanchorSet1 = Graph::getIntersection(nVcore, te);//VanchorSet1是当前的锚点集
			vector<int> out1 = {};
			out1 = Graph::getCounter(nV, VanchorSet1, w, *sc);

			//这一步是要在剩余的未访问的节点里面计算一下core，然后用这些core来当作锚点，再重复上面的步骤

			//vector<int> temp3 = Graph::getDifference(te, nVcore);
			vector<int> unexploredV = {};
			vector<int>::iterator temp4 = te.begin();
			for (; temp4 != te.end(); temp4++)
			{
				if (!mustDelete[*temp4] && !donotAccessNow[*temp4] && !explored[*temp4])
					unexploredV.push_back(*temp4);
			}
			vector<int> reexist = {}, out2 = {};
			out2 = Graph::forU(nV, unexploredV, w, *sc, reexist);
			Graph::vertexReset(reexist);//重置节点的explored survived inH inNowWcore inNowSearchRange upWeight属性值
			//put_out(out2);
			//cout << endl;
			double runtime = (double)clock() / CLOCKS_PER_SEC - algStartTime;
			cout << "i = " << i << "  xi = " << *sc << "  size = " << out2.size() << "  runtime = " << runtime << endl;

			if (out2.size() > count)
			{
				count = out2.size();
				cBestWcore = out2;
				x = *sc;
			}
		}

		for (int k = 0; k < vertex.size(); k++)
		{
			int count = 0;
			vector<int>::iterator nei;
			for (nei = vertex[k].begin() + 1; nei != vertex[k].end(); nei++)
			{
				count++;
				edgeWeightOnA0[k][count] = edgeWeightOnA0[k][count] + edgeWeightOnEachAtt[k][count][x];
			}
		}

		cout << "nowbest: " << x << endl;
		CWc = cBestWcore;
		A = Graph::getUnion(A, { x });
		VCA = Graph::getUnion(VCA, Vi[x]);
		allAttribute[x] = -1;
		Graph::donotAccessNowReset(redonoAccessNow);
	}
	return A;
}

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
	return lhs.second > rhs.second;
}

vector<PAIR> Graph::sortCandidateAttribute(vector<int> Adiff, vector<int> VCA)//按照map的value属性的递减排列map里面的元素。意思就是按照节点集交集的大小递减排列map
{
	map<int, int> temp;
	vector<int>::iterator ca;
	for (ca = Adiff.begin(); ca != Adiff.end(); ca++)//先把所有的候选属性xi以及其对应的|Vxi并上V当前最优属性覆盖集|
	{
		temp.insert(pair<int, int>(*ca, Graph::getUnion(Vi[*ca], VCA).size()));
	}
	vector<PAIR> result(temp.begin(), temp.end());
	sort(result.begin(), result.end(), cmp_by_value);
	return result;
}

map<int, int> Graph::test(vector<int> Adiff, vector<int> VCA)
{
	map<int, int> temp;
	vector<int>::iterator ca;
	for (ca = Adiff.begin(); ca != Adiff.end(); ca++)//先把所有的候选属性xi以及其对应的|Vxi并上V当前最优属性覆盖集|
	{
		temp.insert(pair<int, int>(*ca, Graph::getUnion(Vi[*ca], VCA).size()));
	}
	return temp;
}