//�Ͽ�˹�����·���㷨����Դ���·����
#include<iostream>
using namespace std;
//�������
const int CITY = 5;
//��������
const int INF = 1000;
//ʹ�ö�ά����洢�ڽӾ���
//�ڴ�����ֱ����Դ�����������ڽӾ�����Ϣ
//Ϊ����Ū���������̶���ʵ������
int map[CITY][CITY]={
{INF,2,5,INF,INF},
{INF,INF,2,6,INF},
{INF,INF,INF,7,1},
{INF,INF,2,INF,4},
{INF,INF,INF,INF,INF}
};
//dist������pǰ������
int dist[CITY]={0};
int p[CITY]={0}; 
//��־����(��ʾ�����Ƿ������Sս��)
int Flag[CITY]={0}; 

//���·�� 
void FindRoad(int last,int origin){
	if(dist[last]==INF){
		printf("Error not find Road\n");
	}
	if(last==origin){
		printf(" %d ",last);
		return;
	}
	FindRoad(p[last],origin);
	printf(" %d ",last);
}

//������ 
int main(int argc,char**argv){
	int i,j;
	//����ڽӾ��� 
	printf("map:\n");
	for(i=0;i<CITY;i++){
		for(j=0;j<CITY;j++){
			if(map[i][j]==INF)
				printf(" INF ");
			else
				printf(" %d ",map[i][j]);
		}
		printf("\n");
	}
	//ѡ��Դ��,ѡ��0ΪԴ��
	int origin=0;
	//��Դ����Sս��
	Flag[origin]=1; 
	//��ʼ��dist������ǰ������
	for(i=0;i<CITY;i++){ 
		if(i==origin){//dist����
			dist[i]=0;
			p[i]=-1;
		}else{
			dist[i]=map[origin][i];
			if(map[origin][i]==INF){
				p[i]=-1;
			}else{
				p[i]=origin;
			}
		}
	}
	//���dist������ǰ������
	printf("dist:\n");
	for(i=0;i<CITY;i++){
		printf(" %d ",dist[i]);
	}
	printf("\np:\n");
	for(i=0;i<CITY;i++){
		printf(" %d ",p[i]);
	}	
	printf("\n");
	//����Ҫѡ��n����Сdist
	for(i=0;i<CITY;i++){
		//�ڼ���v-s����dist��С��
		int temp = INF,t=origin;//tΪ�ҵ��Ľ��
		for(j=0;j<CITY;j++){
			if(Flag[j]==0&&dist[j]<temp){
				temp=dist[j];
				t=j;
			}
		} 
		if(t==origin){//v-sΪ�� 
			break;
		}
		//����Sս��
		Flag[t]=1;
		//����dist������ǰ������,���趫��
		for(j=0;j<CITY;j++){
			if(Flag[j]==0&&map[t][j]<INF){
				if(dist[j]>dist[t]+map[t][j]){
					dist[j]=dist[t]+map[t][j];
					p[j]=t;
				}
			}
		} 
	} 		
	//���ǰ������
	printf("���·��ǰ������Ϊ\n");
	for(i=0;i<CITY;i++){
		printf(" %d ",p[i]);
	} 
	printf("\n");
	
	//�����·�����ǿ��Բ��õݹ��������ջ�ķ���
	//FindRoad(4,origin);//��һ������Ϊ�յ㣬�ڶ�������ΪԴ�� 
	for(i=0;i<CITY;i++){
		FindRoad(i,origin);
		printf("\n");
	} 
	return 0;
} 
