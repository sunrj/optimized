#ifndef GRAPH
#define GRAPH
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<unordered_set>
#include<map>
#include<algorithm>
#include<queue>
#include<iterator>
#include<ctime>
#include<fstream>

using namespace std;

typedef pair<int, int> PAIR;

class Graph
{
public:
	vector<vector<int>> vertex;//存储节点以及节点的邻居
	vector<vector<int>> attribute;//存储节点以及节点的属性
	vector<vector<int>> attributeUnionInt;//存储各个边的端点的属性集的并集的大小，与vector<vector<int>> vertex 的结构完全对应
	vector<vector<vector<int>>> attributeIntersecSet;//存储各个边的端点的属性集的交集的set，与vector<vector<int>> vertex 的结构基本对应
	vector<vector<vector<float>>> edgeWeightOnEachAtt;
	vector<vector<float>> tempEdgeWeight;//存储计算的当前属性集下的各边的权重，与vector<vector<int>> vertex 的结构完全对应
	vector<vector<float>> edgeWeightOnA0;//各个边在当前最好的属性集下的权重，与vector<vector<int>> vertex 的结构完全对应
	vector<int> countdownInt;
	vector<int> donotAccessNow;
	vector<float> dwSum;
	vector<int> access;//用来统计每次循环访问的节点的个数
	vector<int> exist;//size为节点个数n，表示节点是否存在与当前属性的判断中。1表示存在，0表示不存在，默认是1
	vector<int> mustDelete;//size为节点个数n，表示那些节点必定不存在与最后的结果中。1表示被删除，0表示未被删除，默认为0
	vector<int> explored;//size为节点个数n，判断节点是否被访问，1表示被访问了，0表示unexplored，初始化为0
	vector<int> survived;//size为节点个数n，判断节点被访问后是否存活下载，1表示访问后存活下来，0表示访问被discarded，初始化为1
	vector<int> inH;//size为节点个数n，主要是为了最优的那个方法而存在的，判断节点是否在队列中。初始化为0
	vector<int> inNowWcore;//size为节点个数n，主要是为了最优的那个方法而存在的，判断节点是否在当前的必定存在的Wcore里面。初始化为0
	vector<int> inNowSearchRange;//size为节点个数n，主要是为了最优的那个方法而存在的，判断节点是否在当前的查找范围里面。初始化为0
	vector<float> weight;//size为节点个数n，存储节点的权重，默认为0.0
	vector<float> upWeight;//size为节点个数n，存储节点的权重上线，默认为0.0
	vector<int> allAttribute;//存储当前图的所有属性
	vector<int> getVi(int aId);//aId表示属性的Id，该方法是找到包含aId这个属性的节点集
	vector<vector<int>> Vi;//存储每个属性所覆盖的节点集
	void getEachVi();//计算Vi
	vector<vector<int>> WiCore;//存储在每一个属性下生成的WiCore
	void getedgeWeightOnEachAtt();
	void getcountdownInt(float w);
	void countdown(float w, int ith, vector<float> dwSum, vector<int> &redonotAccessNow);//ith表示第几次迭代
	void getEachWiCore(float w);//计算WiCore
	void dataInput(string edge_file, string attribute_file, string union_file, string intersec_file);//数据输入，edge_file是节点以及边的数据文件，attribute_file是各个节点的属性文件，, string attributeInVex_fileunion_file存储各个边的端点的属性集的并集的大小，intersec_file存储各个边的端点的属性集的交集的set，attributeInVex_file存储每个属性所覆盖的节点集
	vector<int> getIntersection(vector<int> A, vector<int> B);//获得A与B的交集
	vector<int> getUnion(vector<int> A, vector<int> B);//获得A与B的并集
	vector<int> getDifference(vector<int> A, vector<int> B);//获得A\B，差集
	float computeEdgeWeight(int id1, int id2, vector<int> A);//计算两个节点之间的边在给定的属性集下的权重
	float comVerWonV(int id, int attributeId, vector<int> V);//计算节点在节点集V中和给定的属性集下的权重
	void vertexDeletion(float w, int b);//初始化，把所有一定不会存在与weighted core的节点删除
	vector<int> comWcoreOnV(float w, int attributeId, vector<int> V, vector<int> &reexist);//计算节点集V的范围内attribute weighted core
	void vertexReset(vector<int> reexist);//重置节点的explored survived inH inNowWcore inNowSearchRange upWeight属性值
	void existReset(vector<int> reexist);//把非mustDelete的节点的exist属性重置为true，因需要判断不同的属性集的情况下的结果，所有每次判断时不能遗留上一次的结果
	void donotAccessNowReset(vector<int> reexist);
	vector<int> getCounter(vector<int> V, vector<int> VanchorSet, float w, int x);//想不好怎么描述这个算法了。就是最优算法的关键找follow集的步骤。V是查找范围，VanchorSet就是锚点集，返回在当前属性下的Wcore
	vector<int> forU(vector<int> V, vector<int> unexploredV, float w, int x, vector<int> &reexist);
	void Shrink(int id, float w);//把当前要discarded的节点会造成的影响给更新
	float computeUpWeight(int id, int x);//计算节点权重的upbound
	vector<int> optimized(float w, int b);//使用改进的优化算法来计算最优的b个属性，返回这个属性集
	vector<PAIR> sortCandidateAttribute(vector<int> Adiff, vector<int> VCA);//把候选属性按照属性和最有属性所覆盖的点集大小的递减顺序排列。diff是候选属性集，CA是当前最优属性集覆盖的点集。key值存放的是属性的id，value值存放的是属性覆盖的点集的大小
	map<int, int> test(vector<int> Adiff, vector<int> VCA);
};

#endif // !GRAPH