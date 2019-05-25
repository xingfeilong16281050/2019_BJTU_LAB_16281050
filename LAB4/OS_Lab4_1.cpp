// OS_Lab4_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>
#include<time.h>
#include<windows.h>
#include<cstdlib>
#include<ctime>

using namespace std;
void maincontrol();//主控函数 初始化工作集（缓冲区）并且装入初始值（访问序列的前n个）
void create_visilist(int size);
void maincontrol();//主控函数 初始化工作集（缓冲区）并且装入初始值（访问序列的前n个）
void beat_value(int wl, int vl, int index);
void best_change(int wl, int vl);
void print_worklist(int wl);
void first_in_outchangge(int now, int wl);
void FIFO(int wl, int vl);
void LRU_value(int  now, int wl,double *con);
void LRU(int wl, int vl);
int PBA_changew2(int now, int wl);
int PBA_changew1(int now, int wl);
void PBA(int wl, int vl);
void Sclock();//改进的clock算法
void print_cwork(int wl);
void ischange(int index);//随机修改函数
int isexit1(int wl);
int isexit2(int wl);

struct STU
{
	int yenumber;
	int isexit;
	int ischange;
	int blocknumber;
};

int** worklist=NULL;//工作集
int** worklist2 = NULL;
int* visitlist = NULL;//访问序列
int** cwork = NULL;
clock_t start1, end1;

//主控函数 初始化工作集（缓冲区）并且装入初始值（访问序列的前n个）
void maincontrol() 
{
	cout << endl << "请输入工作集大小：";
	int temp = 0;
	cin >> temp;
	worklist = new int * [temp];
	for (int i = 0; i < temp; i++) {
		worklist[i] = new int[2];
		worklist[i][0] = 0;
		worklist[i][1] = 214748364;
	}
		

	cout << endl << "请输入访问序列大小：";
	int temp2 = 0;
	cin >> temp2;
	create_visilist(temp2);
	cout << endl << "工作集初始化结果："<<endl;
	for (int i = 0; i < temp; i++)
	{
		worklist[i][0] = visitlist[i];
		cout << worklist[i][0]<<"  "<<endl;
	}
	
	start1 = clock();
	best_change(temp, temp2);
	//FIFO(temp, temp2);
	//LRU(temp, temp2);
	//PBA(temp, temp2);
	end1 = clock();
	double endtime = (double)(end1 - start1) / CLOCKS_PER_SEC;
	cout << "Total time:" << endtime*1000<<"ms" << endl;
	return ;
}

//改进的clock算法
void Sclock()
{
	double right_count =0;
	cout << endl << "请输入改进clock工作集大小：";
	int wl = 0;
	cin >> wl;
	worklist = new int* [wl];
	for (int i = 0; i < wl; i++) {
		worklist[i] = new int[3];
		worklist[i][0] = 0;
		worklist[i][1] = 0;
		worklist[i][2] = 0;
	}


	cout << endl << "请输入访问序列大小：";
	int vl = 0;
	cin >> vl;
	create_visilist(vl);
	cout << endl << "工作集初始化结果：" << endl;
	for (int i = 0; i < wl; i++)
	{
		worklist[i][0] = visitlist[i];
	}
	print_cwork(wl);
	start1 = clock();
	for (int i = 0; i < vl; i++)
	{
		cout <<endl<<"*************************************"<< endl;
		cout << endl << "访问元素：" << visitlist[i];
		print_cwork(wl);
		int temp = 0;
		for (int j = 0; j < wl; j++)
		{
			if (visitlist[i] == worklist[j][0])
			{
				temp = 1;
				ischange(j);
				break;
			}
		}
		if (temp == 1)
		{
			right_count++;
			continue;
		}
		else
		{
			int index1 = 0;
			if (((index1 = isexit1(wl)))== -1) {
				if ( (index1 = isexit2(wl)) == -1) {
					if ( (index1 = isexit1(wl)) == -1) {
						(index1 = isexit2(wl));
						worklist[index1][0] = visitlist[i];
						worklist[index1][1] = 1;
						ischange(index1);
						cout << endl << "置换位置：" << index1 + 1;
					}
					else
					{
						worklist[index1][0] = visitlist[i];
						worklist[index1][1] = 1;
						ischange(index1);
						cout << endl << "置换位置：" << index1 + 1;
					}
				}
				else {
					worklist[index1][0] = visitlist[i];
					worklist[index1][1] = 1;
					ischange(index1);
					cout << endl << "置换位置：" << index1 + 1;
				}
			}
			else
			{
				worklist[index1][0] = visitlist[i];
				worklist[index1][1] = 1;
				ischange(index1);
				cout << endl << "置换位置：" << index1 + 1;
			}

			continue;
		}
		
	}
	cout << endl << "页面置换次数：" << vl - right_count;
	cout << endl << "缺页率" << 1 - double(right_count / vl) << endl;
	end1 = clock();
	double endtime = (double)(end1 - start1) / CLOCKS_PER_SEC;
	cout << "Total time:" << endtime * 1000 << "ms" << endl;
	return;
}

//判断工作空间是否存在一类页面，若有，返回坐标，若不存在返回-1
int isexit1(int wl) {
	for (int j = 0; j < wl; j++)
	{
		if (worklist[j][1] == 0 && worklist[j][2] == 0)
		{
			return j;
			break;
		}
	}
	return -1;
}

//判断工作空间是否存在二类页面，若有，返回坐标，若不存在返回-1
int isexit2(int wl) {

	for (int j = 0; j < wl; j++)
	{
		if (worklist[j][1] == 0 && worklist[j][2] == 1)
		{
			return j;
			break;
		}
		worklist[j][1] = 0;
	}
	return -1;
}

//打印改进clock算法的工作集
void print_cwork(int wl) {
	cout << endl << "改进clock工作集：" << endl;
	for (int i = 0; i < wl; i++)
	{
		cout << worklist[i][0] << "  " << worklist[i][1] << "  " << worklist[i][2] << endl;
	}
}

//随机修改函数
void ischange(int index){
	int a = rand() % 10;
	if ( a<5 )
	{
		cout <<index+1<< "号页面被修改" << endl;
		worklist[index][2] = 1;
	}
	return;
}

//工作集打印函数
void print_worklist(int wl) {

	cout << endl << "工作集：" << endl;
	for (int i = 0; i < wl; i++)
	{
		cout << worklist[i][0] << "  "<<worklist[i][1]<<endl;
	}
}

//最佳置换算法
void best_change(int wl, int vl) {

	double right_count = 0;
	for (int i = 0; i < vl; i++)
	{
		cout << endl << "*************************************";
		cout<<endl << "访问元素：" << visitlist[i];
		print_worklist(wl);
		int temp = 0;
		for (int j = 0; j < wl; j++)
		{
			if (visitlist[i]==worklist[j][0])
			{
				temp = 1;
				break;
			}
		}
		if (temp==1)
		{
			right_count++;
			beat_value(wl, vl, i + 1);
			continue;
		}
		else
		{
			int max_index = 0;
			int max_value = worklist[0][1];
			for (int k = 0; k < wl; k++)
			{
				if (worklist[k][1]>max_value)
				{
					max_index = k;
				}
			}
			worklist[max_index][0] = visitlist[i];
			beat_value(wl, vl, i+1);
			cout<<endl << "置换位置：" << max_index+1;
		}
	}
	cout << endl << "页面置换次数：" << vl - right_count;
	cout<<endl << "缺页率" << 1-double(right_count / vl) << endl;
}

//最佳置换算法工作集中每个元素最近访问位置计算
void beat_value(int wl, int vl, int index) {
	for (int j = 0; j < wl; j++) {
		for (int i = index; i < vl; i++)
		{
			if (worklist[j][0] == visitlist[i]) {
				worklist[j][1] = i - index;
				break;
			}
			worklist[j][1] = 214748364;
		}
	}


}

//先进先出置换算法
void FIFO(int wl, int vl) {
	for (int k = 0; k < wl; k++)
	{
		worklist[k][1] = 0;
	}
	double right_count = 0;
	for (int i = 0; i < vl; i++)
	{
		cout << endl << "*************************************";
		cout << endl << "访问元素：" << visitlist[i];
		print_worklist(wl);
		int temp = 0;
		for (int j = 0; j < wl; j++)
		{
			if (visitlist[i] == worklist[j][0])
			{
				temp = 1;
				break;
			}
		}
		if (temp == 1)
		{
			for (int k = 0; k < wl; k++)
			{
				worklist[k][1]++;
			}
			right_count++;
			continue;
		}
		else
		{
			first_in_outchangge(visitlist[i], wl);
			
		}
	}
	cout << endl << "页面置换次数：" << vl - right_count;
	cout << endl << "缺页率" << 1 - double(right_count / vl) << endl;
}

//先进先出元素替换函数··
void first_in_outchangge(int now,int wl) {
	int max_index = 0;
	int max_value = worklist[0][1];
	for (int k = 0; k < wl; k++)
	{
		if (worklist[k][1] > max_value)
		{
			max_index = k;
		}
	}
	worklist[max_index][0] = now;
	worklist[max_index][1] = 0;
	cout << endl << "置换位置：" << max_index+1 << endl;
	for (int k = 0; k < wl; k++)
	{
		worklist[k][1]++;
	}
}

//LRU置换算法
void LRU(int wl, int vl) {
	for (int k = 0; k < wl; k++)
	{
		worklist[k][1] = 0;
	}
	double right_count = 0;
	
	for (int i = 0; i < vl; i++)
	{
		cout << endl << "*************************************";
		cout << endl << "访问元素：" << visitlist[i];
		print_worklist(wl);
		LRU_value(visitlist[i], wl,&right_count);
	}
	cout << endl << "页面置换次数：" << vl - right_count;
	cout << endl << "缺页率" << 1 - double(right_count / vl) << endl;
}

//LRU元素置换函数
void LRU_value( int  now,int wl,double *con) {
	int temp = 0;
	for (int j = 0; j < wl; j++)
	{
		if (now == worklist[j][0])
		{
			temp = 1;
			worklist[j][1]=0;
			break;
		}
	}
	if (temp == 1)
	{
		cout << "命中" << endl;
		*con = *con+1;
		for (int k = 0; k < wl; k++)
		{
			worklist[k][1]++;
		}
	}
	else
	{
		cout << "未命中" ;
		first_in_outchangge(now, wl);
	}

}

//PBA工作集页面修改函数
int PBA_changew1(int now, int wl) {
	int max_index = 0;
	int max_value = worklist[0][1];
	int return_vale;
	for (int k = 0; k < wl; k++)
	{
		if (worklist[k][1] > max_value)
		{
			max_index = k;
		}
	}
	return_vale = worklist[max_index][0];
	worklist[max_index][0] = now;
	worklist[max_index][1] = 0;
	cout << endl << "置换位置：" << max_index + 1;

	for (int k = 0; k < wl; k++)
	{
		worklist[k][1]++;
	}
	return return_vale;
}

//缓冲空间页面修改函数
int PBA_changew2(int now, int wl2) {
	int max_index = 0;
	int max_value = worklist2[0][1];
	int return_vale;
	for (int k = 0; k < wl2; k++)
	{
		if (worklist2[k][1] > max_value)
		{
			max_index = k;
		}
	}
	return_vale = worklist2[max_index][0];
	worklist2[max_index][0] = now;
	worklist2[max_index][1] = 0;

	for (int k = 0; k < wl2; k++)
	{
		worklist2[k][1]++;
	}
	return return_vale;
}

//PBA置换算法
void PBA(int wl, int vl) {
	cout << endl << "请输入二级缓存队列大小：";
	int tempw2 = 0;
	cin >> tempw2;
	worklist2 = new int* [tempw2];
	for (int i = 0; i < tempw2; i++) {
		worklist2[i] = new int[2];
		worklist2[i][0] = 0;
		worklist2[i][1] = 0;
	}

	for (int k = 0; k < wl; k++)
	{
		worklist2[k][1] = 214748364;
	}
	double right_count = 0;


	for (int i = 0; i < vl; i++)
	{
		cout << endl << "*************************************";
		cout << endl << "访问元素：" << visitlist[i];
		print_worklist(wl);
		int temp = 0;
		for (int j = 0; j < wl; j++)
		{
			if (visitlist[i] == worklist[j][0])
			{
				temp = 1;
				break;
			}
		}
		if (temp == 1)
		{
			cout << endl << "命中！" << endl;
			right_count++;
			for (int k = 0; k < wl; k++)
			{
				worklist[k][1]++;
			}
			continue;
		}
		else
		{
			int temp2 = 0;
			int tempvalue =0;
			for (int j = 0; j < tempw2; j++)
			{
				if (visitlist[i] == worklist2[j][0])
				{
					temp2 = 1;
					break;
				}
			}
			if (temp2==1)
			{
				right_count++;
				cout << "未命中但二级队列中存在！" << endl;
				tempvalue = PBA_changew1(visitlist[i], wl);
				PBA_changew2(tempvalue, tempw2);
			}
			else
			{
				cout << "未命中且二级队列中不存在！" << endl;
				tempvalue = PBA_changew1(visitlist[i], wl);
				PBA_changew2(tempvalue, tempw2);
			}

		}
	}
	cout << endl << "页面置换次数：" << vl - right_count;
	cout << endl << "缺页率" << 1 - double(right_count / vl) << endl;
}

//随机访问序列生成函数
void create_visilist(int size) 
{
	int N = 20;
	int p = 0;
	int m = 6;
	double t = 0.7;
	int choose = 0;
	cout<<endl <<"是否要改变访问序列生成时的其他参数[0(否)/1(是)]：";
	cin >> choose;
	if (choose == 1)
	{
		cout << endl << "请输入虚拟内存尺寸N：";
		cin >> N;
		cout << endl << "请输入起始位置p：";
		cin >> p;
		cout << endl << "请输入工作集移动率m：";
		cin >> m;
		cout << endl << "请输入访问调变率t：";
		cin >> t;
	}

	visitlist = new int[size];
	int temp = 0;
	visitlist[0] = 0;
	for (int  i = 1; i < size; i++)
	{
		temp++;
		if (temp%m == 0)
		{
			p = p + 1;
		}
		int temp = rand() % 6 + p;
		double r = rand() % 100 / 100.0;
		if (r<t)
		{
			visitlist[i] = temp;
		}

		else
		{
			visitlist[i] = (visitlist[i - 1] + 1) % N;
		}
	}
	cout << "随机访问序列为：" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << visitlist[i]<<" ";
	}

}


int main()
{
	srand((unsigned)time(NULL)); //令每次生成的随机数不同
	//maincontrol();
	Sclock();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
