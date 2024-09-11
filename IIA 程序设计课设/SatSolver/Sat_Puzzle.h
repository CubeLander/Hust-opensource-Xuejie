#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

#define TRUE 1        //�ж�Ϊ�� 
#define FALSE 0       //�ж�Ϊ�� 
#define OK 1          //����ִ�гɹ� 
#define ERROR 0       //����ִ��ʧ�� 
#define INFEASTABLE -1     //�ṹ��δ����洢�ռ� 
#define OVERFLOW -2       //������������䴢��ռ�ʧ�� 

typedef struct lNode {
	int l;          //�洢���� 
	int exist;      //��Ǹ������Ƿ�ɾ������ʼֵΪ1             
	struct lNode* next;
}lNode, * plNode;               //�洢һ�����ֽڵ�

typedef struct cNode {
	int l_num;			  //�洢һ���Ӿ�����ָ���
	int flag;             //��¼���Ӿ���Ϊflag����ɾ������ʼֵΪ0 
	int exist;             //��Ǹ��Ӿ��Ƿ�ɾ�� ����ʼֵΪ1 
	lNode* firstl;        //ָ���һ�����ֽڵ� 
	struct cNode* next;   //ָ����һ���Ӿ� 
}cNode, * pcNode;     //�Ӿ�(ͷ)�ڵ� 

typedef struct iNode {
	cNode* p_cnode;       //�洢ָ�������ͷ����ָ�� 
	struct iNode* next;
}iNode, * piNode;       //��������ڽӵ� 

typedef struct {
	iNode* firstpos;       //�����ֵ������� 
	iNode* firstneg;       //�����ֵ������� 
} index, * pindex;//����������Ķ��� 

typedef struct cnf {
	int vari_num;        //��Ԫ���� 
	int clau_num;        //�Ӿ����
	cNode* firstclau;       //ָ���һ���Ӿ�ڵ�
	index* Index_List;   //������������ 
}cnf, * pcnf;            //һ��cnf��ʽ

typedef struct AnsList {
	int* elem;		//����������ѡ�����֣�
	int length;		//��
}AnsList;     //һ��˳���ṹ���洢�� 

int loadCNF(pcnf* L, char filename[80]);        //����CNFʽ 
int printCNF(pcnf L);     //��ӡCNF��ʽ 
int loadAnswer(pcnf L, AnsList& An);
int deleteclau(pcnf L, int flag);
int restoreclau(pcnf L, int flag);
int EmptyClause(pcnf L);
int Findl(pcnf L, AnsList& An);
int DPLL(pcnf L, AnsList& An, int now_l);
int verify(pcnf L, AnsList& An);
int rule_1(char filename[80]);
int rule_2(char filename[80]);
int rule_3(char filename[80]);
int write(char filename[80]);
int WriteCNF(char filename[80]);
int SaveSolution(int res, double time, AnsList& An, char filename[80]);
int ResWrite_2(int res, double time, AnsList& An, char filename[80]);
