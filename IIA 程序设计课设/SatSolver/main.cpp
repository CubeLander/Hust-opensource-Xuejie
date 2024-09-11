#include "Sat_Puzzle.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	pcnf L = NULL;			//��cnf�ļ�
	AnsList Ans;				//�洢��
	clock_t start, end;              //��¼ʱ��
	double duration;
	char filename[80];
	//��������ѡ�� 
	int op = 1;
	int op_1 = 1;
	int op_2 = 1;
	int tag = -1;
	while (op) {//����ģ��sat��puzzle 
		system("cls");	printf("\n\n");
		//printf("      Menu for Linear Table On Sequence Structure \n");
		printf("		��ӭʹ��DPLL-SAT����� \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. SAT�������       2. ����������\n");
		printf("          0. �˳�                   \n");
		printf("------------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~2]:");
		scanf("%d", &op);
		switch (op) {  //��ʾϵͳ�Ĺ���ѡ�� 
		case 1:
			op_1 = 1;
			while (op_1) {//sat����ϵͳ 
				system("cls");	printf("\n\n");
				//printf("     Menu for Linear Table On Sequence Structure    \n");
				printf("					�����ȶ���CNF�ļ�    \n");
				printf("----------------------------------------------------\n");
				printf("       1. ����CNF�ļ�         2. ��ӡCNF��ʽ               \n");
				printf("       3. DPLL�㷨���        4. ��֤���                  \n");
				printf("       5. ��ӡ��	             6. ����⵽�ļ�            \n");
				printf("       0. �˳�                                      \n");
				printf("----------------------------------------------------\n");
				printf("     ��ѡ����Ĳ���[0~6]:\n");
				scanf("%d", &op_1);
				switch (op_1) {
				case 1:
					//printf("\n--------creatCNF���ܴ�ʵ�֣�\n");
					printf("������ѡ����ļ���\n");
					scanf("%s", filename);
					if (loadCNF(&L, filename) == OK) printf("cnf��ʽ�����ɹ�\n");
					else {
						printf("cnf��ʽ����ʧ��\n");
						getchar(); getchar();
						break;
					}
					if (loadAnswer(L, Ans) == OK) printf("�������洢�ռ�ɹ�\n");
					else {
						printf("�������洢�ռ�ʧ��\n");
						getchar(); getchar();
						break;
					}
					getchar(); getchar();
					break;
				case 2:
					//printf("\n--------printCNF���ܴ�ʵ�֣�\n");
					if (printCNF(L) == OK) printf("cnf��ʽ��ӡ�ɹ�\n");
					else printf("��ӡʧ��\n");
					getchar(); getchar();
					break;
				case 3:
					//printf("\n--------DPLL���ܴ�ʵ�֣�\n");
					start = clock();
					if (DPLL(L, Ans, 1) == OK) {
						tag = 1;
						printf("���ɹ�\n");
					}
					else {
						tag = 0;
						printf("���ʧ��\n");
					}
					end = clock();
					duration = ((double)(end - start)) / CLK_TCK * 1000;
					printf("����ʱ��Ϊ��%f����\n", duration);
					getchar(); getchar();
					break;
				case 4:
					//printf("\n--------verify���ܴ�ʵ�֣�\n");
					if (verify(L, Ans) == TRUE) printf("------------�𰸺���\n");
					else printf("---------�𰸲�����\n");
					getchar(); getchar();
					break;
				case 5:
					//printf("\n--------prfAnswer���ܴ�ʵ�֣�\n");
					for (int i = 1; i < Ans.length; i++) {
						if (Ans.elem[i] == -1)  printf("%5d", -i);
						else printf("%5d", i);
						if (i % 10 == 0)  printf("\n");
					}
					getchar(); getchar();
					break;
				case 6:
					//printf("\n------ResWrite���ܴ�ʵ��\n");
					if (SaveSolution(tag, duration, Ans, filename) == OK) printf("���д��ɹ�\n");
					else printf("���д��ʧ��\n");
					getchar(); getchar();
					break;
				case 0:
					break;
				}
			}
			//getchar();getchar();
			break;
		case 2:
			op_2 = 1;
			while (op_2) {//puzzle����ϵͳ 
				system("cls");	printf("\n\n");
				printf("     Menu for Linear Table On Sequence Structure    \n");
				printf("----------------------------------------------------\n");
				printf("       1. WriteCNF         2. loadCNF             \n");
				printf("       3. DPLL             4. verify                  \n");
				printf("       5. prfAnswer        6. ResWrite              \n");
				printf("       0. Exit                                      \n");
				printf("----------------------------------------------------\n");
				printf("     ��ѡ����Ĳ���[0~6]:\n");
				scanf("%d", &op_2);
				switch (op_2) {
				case 1:
					printf("\n--------WriteFile���ܴ�ʵ�֣�\n");
					printf("������ѡ����ļ���\n");
					scanf("%s", filename);
					if (WriteCNF(filename) == OK)  printf("����ļ�д��ɹ�\n");
					else printf("����ļ�д��ʧ��\n");
					getchar(); getchar();
					break;
				case 2:
					printf("\n--------loadCNF���ܴ�ʵ�֣�\n");
					if (loadCNF(&L, filename) == OK) printf("cnf��ʽ�����ɹ�\n");
					else {
						printf("cnf��ʽ����ʧ��\n");
						getchar(); getchar();
						break;
					}
					if (loadAnswer(L, Ans) == OK) printf("�������洢�ռ�ɹ�\n");
					else {
						printf("�������洢�ռ�ʧ��\n");
						getchar(); getchar();
						break;
					}
					getchar(); getchar();
					break;
				case 3:
					printf("\n--------DPLL���ܴ�ʵ�֣�\n");
					start = clock();
					if (DPLL(L, Ans, 1) == OK) {
						tag = 1;
						printf("���ɹ�\n");
					}
					else {
						tag = 0;
						printf("���ʧ��\n");
					}
					end = clock();
					duration = ((double)(end - start)) / CLK_TCK * 1000;
					printf("����ʱ��Ϊ��%f����\n", duration);
					getchar(); getchar();
					break;
				case 4:
					printf("\n--------verify���ܴ�ʵ�֣�\n");
					if (verify(L, Ans) == TRUE) printf("------------�𰸺���\n");
					else printf("----------�𰸲�����\n");
					getchar(); getchar();
					break;
				case 5:
					printf("\n--------prfAnswer���ܴ�ʵ�֣�\n");
					for (int i = 1; i < Ans.length; i++) {
						if (Ans.elem[i] == -1)  printf("0 ");
						else printf("1 ");
						if (i % 6 == 0)  printf("\n");
					}
					getchar(); getchar();
					break;
				case 6:
					printf("\n------ResWrite���ܴ�ʵ��\n");
					if (ResWrite_2(tag, duration, Ans, filename) == OK) printf("���д��ɹ�\n");
					else printf("���д��ʧ��\n");
					getchar(); getchar();
					break;
				case 0:
					break;
				}
			}
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}
