//����ʱ���
//����       1   2   3   4   5   6   7   8   9   10
//��ʼʱ��   8   9   10  11  13  14  15  17  18  26  
//����ʱ��   10  11  15  14  16  17  17  18  20  19
//̰�Ĳ��ԣ��ֲ����Ž⣬ѡ����������
//�������������
#include<iostream>
using namespace std;
struct Meeting{
	int num;//������� 
	float start;//���鿪ʼʱ�� 
	float end;//�������ʱ��
	int flag;//��¼�Ƿ�ѡ�� 
};
void printMeeting(struct Meeting*meet,int n){
	int i=0;
	if(!meet||n<=0){
		return;
	}	
	for(i=0;i<n;i++){
		printf("DATA:%d:\n",meet[i].num);
		printf("\tstart:%f\n",meet[i].start);
		printf("\tend:%f\n",meet[i].end);
		printf("\tflag:%d\n",meet[i].flag);
	}
} 
int main(int argc,char**argv){
	int i=0,j=0;
	//��������洢������Ϣ
	struct Meeting meet[10]={
		{1,8,10,0},
		{2,9,11,0},
		{3,10,15,0},
		{4,11,14,0},
		{5,13,16,0},
		{6,14,17,0},
		{7,15,17,0},
		{8,17,18,0},
		{9,18,20,0},
		{10,16,19,0}
	};
	//��Ϣ���
	printMeeting(meet,10);
	//���Ǽ�ȻҪѡ���������ģ���ô���������end��meet��������,�Ա����
	//�ڴ�Ϊ�ˣ����ڲ������ݽ��٣�������ð������
	//�����ʱ�临�Ӷ�Ҫ���ϸ񣬿ɸĽ������㷨
	for(i=0;i<10;i++){
		for(j=0;j<10-i-1;j++){
			if(meet[j].end>meet[j+1].end){
				struct Meeting temp=meet[j];
				meet[j]=meet[j+1];
				meet[j+1]=temp;
			}
		}
	}
	//��������
	printf("���������\n");
	printMeeting(meet,10);
	//�洢������ʱ�����Ϣ
	int time_start=8,time_end=20;
	//��ʼ����̰��ѡ��
	int now=time_start;//��¼������ʱ��εĿ�ʼʱ��
	for(i=0;i<10;i++){
		if(meet[i].start>=now&&meet[i].end<=time_end){
			meet[i].flag=1;//ѡ��
			now=meet[i].end;//����now 
		}else if(meet[i].end>time_end){
			break;
		} 
	}
	//������鰲������
	printf("��������Ϊ:\n");
	for(i=0;i<10;i++){
		if(meet[i].flag){
			printf("\t%d",meet[i].num);
		}
	} 
	//�ɼ����鰲������ĽⲢ��Ψһ,����������end��ͬ
	//�Ҷ�����ʱ�����Ƕ��䲻ͬѡ�񣬻������ͬ�Ľ��
	//���⻹����Ϊ:1 4 7 8 9 ,ͬ����5������
	//���ǿ��Խ�һЩ�������Ȩ��ֵ����������������� 
	return 0;
} 
