#include<iostream>
#include<fstream>
#include<cmath>
#include<time.h>
using namespace std;
int data[10][10];//9x9 九宫格
bool nums[2][10][10];//每行每列可以取的数
bool sub[4][4][10];//小九宫格可以取的数
ifstream in("..\\Debug\\in.txt");
ofstream out("..\\Debug\\out.txt");
/*
	9x9的二维数组中第n个位置的坐标是: (ceil(n/9), (n-1)%9+1)
*/
void PrintResult(int m[10][10]){
	for(int i=1;i<10;i++){
		for(int j=1;j<10;j++){
			out<<m[i][j]<<"\t";
		}
		out<<endl;
	}
}
void Find(int level){
	bool yes=0;
		if(level>81){
			out<<"*******************************"<<endl;
			PrintResult(data);
			out<<"*******************************"<<endl;
			yes=1;
		}
		if(yes==1)
			return;
		
	//	cout<<"---------"<<level<<endl;
		bool canSel=false;	
		int x=ceil((double)level/9),y=(level-1)%9+1;
		if(data[x][y]!=0) Find(level+1);
		else{
			int sx=ceil((double)x/3),sy=ceil((double)y/3);
			for(int j=1;j<=9;j++){
				if(nums[0][x][j]==true&&nums[1][y][j]==true&&sub[sx][sy][j]==true){//如果行和列都可选则选中
					canSel=true;
					nums[0][x][j]=false;
					nums[1][y][j]=false;
					sub[sx][sy][j]=false;
					data[x][y]=j;
					Find(level+1);
					nums[0][x][j]=true;
					nums[1][y][j]=true;
					sub[sx][sy][j]=true;
					data[x][y]=0;
				}
			}
			if(!canSel){//中途停止，搜索失败,结束当前分支
				return;
			}
		}
}


void Init(){//初始化数据
	int i,j,k;
	i=j=k=0;
	for(i=0;i<3;i++){
		for(j=1;j<=10;j++){
			for(k=1;k<=10;k++){
				nums[i][j][k]=true;
			}
		}
	}
	for(i=1;i<4;i++){
		for(j=1;j<4;j++){
			for(k=1;k<10;k++){
				sub[i][j][k]=true;
			}
		}
	}
	for(i=1;i<10;i++){
		for(j=1;j<10;j++){
			in>>data[i][j];
			if(data[i][j]!=0){
				nums[0][i][data[i][j]]=false;//在第i行可选数字中去掉data[i][j]
				nums[1][j][data[i][j]]=false;//在第j列可选数字中去掉data[i][j]
				sub[(int)ceil((double)i/3)][(int)ceil((double)j/3)][data[i][j]]=false;
			}
		}
	}
	//PrintResult(data);
	//in.close();
}

int main(){
	clock_t start_time=clock();
	int n;
	in>>n;
	for(int i=1;i<=n;i++){
		Init();
		Find(i);
	}
	clock_t end_time=clock();
	cout<< "Running time is: "<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间
	in.close();
	system("pause");
	return 0;
}
