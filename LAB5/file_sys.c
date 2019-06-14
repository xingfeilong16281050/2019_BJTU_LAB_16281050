// file_system.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdlib.h>
using namespace std;

int isexit(string name);
void init_filesys();//文件系统初始化
int find_suoyin();//文件索分配函数
int find_kblock(int num, int index);//空闲块的寻找和分配
void create();//新建文件
void destroy();//文件删除
int open();//文件打开
int isexit(string name);//判断文件是否存在
void lseek(int index);//改变文件的读写指针的位置
void write(int index);//写文件
void close(int index);//
string read(int index);
void option();
void edit(int index);

int ldisk[10][1][10] = {0};

int block_graph[100] = {1,1,0};//位图占用第一块


//文件结构体
typedef struct file {
	int isopen;//打开标志位
	int index;//索引位置
	string filename;//文件名
	int filelenth;//文件长度
	string filecontent;//文件内容
	int point;//编辑指针
};

file my_file[40];

//文件描述符结构体
typedef struct File_discription {

	int index;//文件索引位置

	int lenth;//文件大小B

	int position[3];//文件所占块数

};

File_discription file_dis[40];

//初始化
void init_filesys(){
	for (int i = 0; i < 40; i++)
	{
		my_file[i].index = -1;
		my_file[i].filelenth = -1;
		my_file[i].filecontent = "";
		my_file[i].filename = "";
		my_file[i].point = 0;
	}
	for (int i = 0; i < 40; i++)
	{
		file_dis[i].index = -1;
		file_dis[i].lenth = -1;
		file_dis[i].position[0] = -1;
		file_dis[i].position[1] = -1;
		file_dis[i].position[2] = -1;
	}
	block_graph[0] = 1;
	block_graph[1] = 1;
	
}

//寻找空闲索引位置
int find_suoyin() {
	for (int i = 0; i < 40; i++)
	{
		if (my_file[i].index == -1)
			return i;
	}
	return -1;
}

//寻找空闲块并写入
int find_kblock(int num,int index) {
	if (num == 1)
	{
		for (int i = 0; i < 100; i++)
		{
			if (block_graph[i] == 0) {
				block_graph[i] = 1;
				file_dis[index].position[0] = i;
				file_dis[index].position[1] = -1;
				file_dis[index].position[2] = -1;
				return i;
			}
		}
	}
	else if (num == 2) {
		for (int i = 0; i < 99; i++)
		{
			if (block_graph[i] == 0 && block_graph[i + 1] == 0)
			{
				block_graph[i] = 1;
				block_graph[i + 1] = 1;
				file_dis[index].position[0] = i;
				file_dis[index].position[1] = i + 1;
				file_dis[index].position[2] = -1;
				return i;
			}
		}
	}
	else
	{
		for (int i = 0; i < 98; i++)
		{
			if (block_graph[i] == 0 && block_graph[i + 1] == 0 && block_graph[i + 2] == 0)
			{
				block_graph[i] = 1;
				block_graph[i + 1] = 1;
				block_graph[i + 2] = 1;
				file_dis[index].position[0] = i;
				file_dis[index].position[1] = i + 1;
				file_dis[index].position[2] = i + 2;

				return i;
			}
		}
	}
	return -1;
}

//新建文件
void create() {
	cout <<endl<< "请输入文件名：";
	string name;
	cin >> name;
	if (isexit(name)!=-1)
	{
		cout << "文件名已存在！" << endl;
	}
	else
	{
		cout << endl << "请输入文件大小：";
		int lenth;
		cin >> lenth;
		int num = lenth / 512 + 1;
		int index = find_suoyin();
		if (find_kblock(num,index) != -1) {
			my_file[index].filename = name;
			my_file[index].filelenth = lenth;
			my_file[index].index = index;
			my_file[index].point = 0;
			file_dis[index].index = index;
			file_dis[index].lenth = lenth;
			cout << endl << "创建成功";
		}
		else
		{
			cout << endl << "创建失败，空闲空间不足";
		}
	}
}

//删除文件
void destroy() {
	string name;
	cout << endl << "请输入要删除的文件名：";
	cin >> name;
	if (isexit(name) == -1)
	{
		cout << "文件不存在！" << endl;
	}
	else
	{
		int temp_index = isexit(name);
		my_file[temp_index].filelenth = -1;
		my_file[temp_index].index = -1;
		my_file[temp_index].filecontent = "";
		my_file[temp_index].filename = "";
		my_file[temp_index].point = 0;
		file_dis[temp_index].index = -1;
		file_dis[temp_index].lenth = -1;
		for (int i = 0; i < 3; i++)
		{
			if (file_dis[temp_index].position[i] != -1) {
				block_graph[file_dis[temp_index].position[i]] = 0;
			}
		}
		cout << "文件已删除！" << endl;
	}
}

//打开文件
int open() {
	string name;
	cout << endl << "请输入要打开的文件名：";
	cin >> name;
	if (isexit(name) == -1)
	{
		cout << "文件不存在！" << endl;
		return -1;
	}
	else
	{
		int temp_index = isexit(name);
		if (my_file[temp_index].isopen == 1)
		{
			cout << endl << "文件已打开"<<endl;
		}
		else {
			my_file[temp_index].isopen = 1;
			cout <<endl<< "文件打开成功"<<endl;
		}
		return temp_index;
	}
}

//判断文件是否存在
int isexit(string name) {

	for (int i = 0; i < 40; i++)
	{
		if (name == my_file[i].filename)
		{
			return i;
		}
	}
	return -1;
}

//文件读写指针移动
void lseek(int index) {
	int pos;
	cout << endl << "请输读写指针位置；";
	cin >> pos;
	my_file[index].point = pos;
	if (my_file[index].point < 0)
		my_file[index].point = 0;
	return;
}

//文件写函数
void write(int index) {
	cout<<endl << "请输入写入内容";
	string temp;
	cin >> temp;
	my_file[index].filecontent = my_file[index].filecontent.insert(my_file[index].point,temp);
	my_file[index].point += temp.length();
}

//文件关闭函数
void close(int index) {
	if (my_file[index].isopen==1)
	{
		my_file[index].isopen == 1;
		cout << endl << "文件关闭成功"<<endl;
	}
	else {
		cout << endl << "文件未打开"<<endl;
	}
}

//文件读取函数
string read(int index) {
	cout << endl << "请输入读取长度";
	int count;
	cin >> count;
	string temp = my_file[index].filecontent;
	if (my_file[index].point+count>=temp.length())
	{
		cout <<endl<< "文件长度不足";
		return "";
	}
	else
	{
		string temp2 = temp.substr(my_file[index].point, count);
		my_file[index].point += count;
		return temp2;
	}
}

//文件打印
void directory() {
	cout << endl << "-------------------文件列表-------------------" << endl;
	cout << "文件名" << "\t" << "文件长度"<<"\t"<<"文件所占块";
	for (int i = 0; i < 40; i++)
	{
		if (my_file[i].index != -1) {
			cout << endl << my_file[i].filename << "\t" << my_file[i].filelenth <<"B"<< "\t";
			cout << "\t";
			for (int j = 0; j < 3; j++)
			{
				if (file_dis[i].position[j] != -1) {
					cout << file_dis[i].position[j]<<" ";
				}
			}
			
		}
	}
	cout << endl << "----------------------------------------------" << endl;
}

//位图打印函数
void print_block() {
	cout << endl << "---------------------位图---------------------" << endl;
	for (int i = 0; i < 100; i++)
	{
		cout<<block_graph[i]<<"  ";
		if ((i+1)%10 ==0)
		{
			cout << "\n";
		}
	}
	cout << endl << "----------------------------------------------" << endl;
}

//操作菜单
void option(){
	int index;
	cout << endl << "***********************操作菜单***********************" << endl;
	cout << "1:打印位图" << endl;
	cout << "2:打印文件列表" << endl;
	cout << "3:创建文件" << endl;
	cout << "4:编辑文件" << endl;
	cout << "5:删除文件" << endl;
	cout << "0:退出";
	cout << endl << "******************************************************" << endl;
	cout << "选择你的操作：";
	int temp = 0;
	cin >> temp;
	switch (temp)
	{
	case 1:
		print_block();
		option();
		break;
	case 2:
		directory();
		option();
		break;
	case 3:
		create();
		option();
		break;
	case 4:
		index = open();
		edit(index);
		option();
		break;
	case 5:
		destroy();
		option();
		break;
	case 0:
		exit(0);
		break;
	default:
		cout << endl << "选项无效" << endl;
		option();
		break;
	}
}

//编辑菜单
void edit(int index) {
	cout << endl << "***********************文件编辑***********************" << endl;
	cout << "1:查看文件内容" << endl;
	cout << "2:移动读写指针" << endl;
	cout << "3:读文件" << endl;
	cout << "4:写文件" << endl;
	cout << "5:查看文件详情" << endl;
	cout << "0:返回上级菜单";
	cout << endl << "******************************************************" << endl;
	cout << "选择你的操作：";
	int tempx = 0;
	cin >> tempx;
	string temp_str;
	switch (tempx)
	{
	case 1:
		cout << endl << "文件内容为：" << my_file[index].filecontent;
		edit(index);
		break;
	case 2:
		lseek(index);
		edit(index);
		break;
	case 3:
		temp_str = read(index);
		cout << "读取内容:" << temp_str << endl;
		edit(index);
		break;
	case 4:
		write(index);
		edit(index);
		break;
	case 5:
		edit(index);
		break;
	case 0:
		option();
		break;
	default:
		cout << endl << "选项无效" << endl;
		edit(index);
		break;
	}

}


int main()
{
	init_filesys();
	option();
	return 0;
}
