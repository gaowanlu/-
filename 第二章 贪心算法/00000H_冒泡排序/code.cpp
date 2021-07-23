#include<iostream>
using namespace std;
/*ð��������һ��̰���㷨����
ÿ���ܴ�������ѡ��һ���ֲ����Ž�
Ȼ�������ģ��һ����С
���������ķ�������һ�ν�����ⷽ����һ����
*/ 
void function(int*list,int n){
	int i=0,j=0;
	bool flag=0;
	for(i=0;i<n;++i){
		flag=0;
		for(int j=0;j<n-i-1;j++){
			if(list[j]>list[j+1]){
				flag=1;
				int temp=list[j];
				list[j]=list[j+1];
				list[j+1]=temp;
			}
		}
		if(!flag){//flag==0是即数列已经有序了 中间没有出现迭代交换的情况 故直接停止排序即可 排序完成
			break;
		}
	} 
}
int main(int argc,char**argv){
	int list[10]={2,4,6,5,3,1,9,7,8,0};
	//��list����ð������ 
	function(list,10);
	int i=0;
	cout<<"list:\n";
	for(i;i<10;++i){
		cout<<"\t"<<list[i]<<endl;
	}
	return 0;
}
