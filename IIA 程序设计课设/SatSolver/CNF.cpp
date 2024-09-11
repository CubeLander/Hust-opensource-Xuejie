#include "Sat_Puzzle.h"
int loadCNF(pcnf* L, char filename[80]) {
	pcNode p;    //�Ӿ��� 
	plNode q;    //���ֽڵ�
	piNode r;    //�����ڵ� 
	int i;
	//Ϊcnf�ṹ����L���Ӿ�ͷ���cNode�ṹ����p����洢�ռ�
	*L = (cnf*)malloc(sizeof(struct cnf));
	p = (cNode*)malloc(sizeof(struct cNode));
	p->flag = 0;
	p->exist = 1;
	(*L)->firstclau = p;	//���־�ָ��p
	FILE* fp;
	int num = 0;
	int k = 0;              //��¼ÿ���Ӿ����ָ��� 
	int m = 0;             //��¼�Ӿ�ĸ��� 
	int positive;         //��¼���� 
	char c;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return 0;
	}
	fscanf(fp, "%c", &c);
	while (!feof(fp)) {
		if (c == 'c') {            //cnf�ļ�ע�Ͳ��� 
			while (c != '\n') {
				fscanf(fp, "%c", &c);
			}
			fscanf(fp, "%c", &c);
		}
		else if (c == 'p') {	//cnf�ļ���Ϣͷ
			while (c != '\n') {
				while (c < '0' || c>'9') {
					fscanf(fp, "%c", &c);
				}
				while (c >= '0' && c <= '9') {        //��ȡ��Ԫ�� 
					num = num * 10;			//ǰ������λ+1���ճ��µĸ�λ����ȡ
					num += c - '0';			//��λ
					fscanf(fp, "%c", &c);	//��ȡ���ո�Ϊֹ
				}

				(*L)->vari_num = num;	//�洢��Ԫ��
				(*L)->Index_List = (index*)malloc((num + 1) * sizeof(index));//����������ռ�
				for (i = 0; i <= num; i++) {//������ָ���ʼ��
					(*L)->Index_List[i].firstneg = NULL;
					(*L)->Index_List[i].firstpos = NULL;
				}
				num = 0;
				while (c < '0' || c>'9') {
					fscanf(fp, "%c", &c);
				}
				while (c >= '0' && c <= '9') {        //��ȡ�Ӿ��� 
					num = num * 10;
					num += c - '0';
					fscanf(fp, "%c", &c);
				}
				(*L)->clau_num = num;
				num = 0;
			}
			fscanf(fp, "%c", &c);
		}
		else if ((c >= '0' && c <= '9') || (c == '-')) {//cnf�ļ����Ӿ�
			//�������ֽṹlNode q
			q = (lNode*)malloc(sizeof(struct lNode));	//���ֽ��q
			q->exist = 1;
			p->firstl = q;		//���־�ĵ�һ������Ϊq
			while (c != '\n') {
				while (c != '0') {
					while (c != ' ') {
						positive = 1;	//Ĭ������Ϊ��
						while ((c >= '0' && c <= '9') || (c == '-')) {
							if (c == '-') {
								fscanf(fp, "%c", &c);
								positive = 0;	//����Ϊ��
							}
							num = num * 10;	//��¼���־���ֵ
							num += c - '0';
							fscanf(fp, "%c", &c);
						}
						//���������q��������
						r = (iNode*)malloc(sizeof(struct iNode));//�µ��������
						r->p_cnode = p;	//�����ֱ������Ӿ�p�г���
						if (positive == 0) {                    //Ϊ������� 
							q->l = -num;
							r->next = (*L)->Index_List[num].firstneg;
							(*L)->Index_List[num].firstneg = r;
						}
						else {                    //Ϊ������� 
							q->l = num;
							r->next = (*L)->Index_List[num].firstpos;//�����������
							(*L)->Index_List[num].firstpos = r;
						}
						num = 0;
						k++;	//���Ӿ��Ѿ�������k������
					}
					fscanf(fp, "%c", &c);
					if (c == '0') q->next = NULL;//�Ӿ����
					else {
						q->next = (lNode*)malloc(sizeof(struct lNode));
						q = q->next;
						q->exist = 1;
					}
				}
				fscanf(fp, "%c", &c);
			}
			fscanf(fp, "%c", &c);
			p->l_num = k;		//���Ӿ���k������
			k = 0;
			m++;

			if (m < (*L)->clau_num) {//�����µ��Ӿ�
				p->next = (cNode*)malloc(sizeof(struct cNode));
				p = p->next;
				p->flag = 0;
				p->exist = 1;
			}
			else p->next = NULL;
		}
		else fscanf(fp, "%c", &c);	//��ֹ�ļ���β�ж������ 
	}
	fclose(fp);
	return OK;
}


int printCNF(pcnf L) {//��ӡ����cnf��ʽ
	if (L->clau_num == 0) {
		printf("cnf��ʽΪ��\n");
		return OK;
	}
	pcNode p = L->firstclau;	//�Ӿ�ָ��
	plNode q = p->firstl;	//����ָ��
	printf("cnf��ʽ��Ԫ����%d  �Ӿ�����%d\n", L->vari_num, L->clau_num);
	int i = 1;
	int j;
	while (p) {
		if (p->exist == 0) p = p->next;
		else {
			printf("��%d����%d������   ", i++, p->l_num);
			q = p->firstl;
			j = 1;
			while (q) {
				if (q->exist == 0)  q = q->next;
				else {
					printf("��%d������Ϊ%d   ", j++, q->l);
					q = q->next;
				}
			}
			printf("\n");
			p = p->next;
		}

	}
	return OK;
}

int loadAnswer(pcnf L, AnsList& An) {//Ϊ�洢�𰸵�˳������洢�ռ� 
	An.elem = (int*)malloc((L->vari_num + 1) * sizeof(int));//����洢�ռ� 
	if (!An.elem) {
		return ERROR;//����洢�ռ�ʧ�� 
	};
	An.length = L->vari_num + 1;//��ʼ�����Ա�ĳ���Ϊ0 
	for (int i = 1; i < An.length; i++) {
		An.elem[i] = 0;                        //��ʾû�о������Ӿ�򻯸�ֵ 
		//printf("%d  ",An.elem[i]);                           �鿴�������н��ȣ�û�б�Ҫ�� 
	}
	return OK;
}
int write(char filename[80]) {   //�����̵ĳ�ʼ����д���ļ�
	int a[20], i = 0;
	printf("д�����̵ĳ�ʼ��������0Ϊ��β\n");
	scanf("%d", &a[0]);
	while (a[i] != 0) {
		i++;
		scanf("%d", &a[i]);
	}
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return ERROR;
	}
	fprintf(fp, "ccccccBinary_Puzzle\n");
	fprintf(fp, "p cnf 36 %d\n", i + 2376);
	i = 0;
	while (a[i] != 0) {
		fprintf(fp, "%d 0\n", a[i]);
		i++;
	}
	fclose(fp);
	return OK;
}

int WriteCNF(char filename[80]) {     //�����̵ĳ�ʼ����������Լ�������cnf��ʽ��д���ļ� 
	if (write(filename) != OK)  return FALSE;
	if (rule_1(filename) != OK) return FALSE;
	if (rule_2(filename) != OK) return FALSE;
	if (rule_3(filename) != OK) return FALSE;
	return OK;
}

int SaveSolution(int res, double time, AnsList& An, char filename[80]) {       //�������д���ļ� 
	int i = 0;
	while (filename[i] != '\0') i++;
	filename[i - 3] = 't';    //ֻ�ı��ļ�����չ�� 
	filename[i - 2] = 'x';
	filename[i - 1] = 't';
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return ERROR;
	}
	fprintf(fp, "s %d\n", res);    //res���������1��ʾ���㣬0��ʾ�����㣬-1δ��
	fprintf(fp, "v \n");
	for (i = 1; i < An.length; i++) {
		if (An.elem[i] == -1)  fprintf(fp, "%5d", -i);
		else fprintf(fp, "%5d", i);
		if (i % 10 == 0)  fprintf(fp, "\n");
	}
	fprintf(fp, "\nt %f ms\n", time);
	fclose(fp);
	return OK;
}

int ResWrite_2(int res, double time, AnsList& An, char filename[80]) {       //�������д���ļ� 
	int i = 0, j;
	while (filename[i] != '\0') i++;
	filename[i - 3] = 't';    //ֻ�ı��ļ�����չ�� 
	filename[i - 2] = 'x';
	filename[i - 1] = 't';
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return ERROR;
	}
	fprintf(fp, "s %d\n", res);    //res���������1��ʾ���㣬0��ʾ�����㣬-1δ��
	fprintf(fp, "v \n");
	for (i = 0; i < 6; i++) {
		fprintf(fp, "----------------------------\n  ");
		for (j = 1; j <= 6; j++) {
			if (An.elem[6 * i + j] == 1) fprintf(fp, "1  ");
			else fprintf(fp, "0  ");
			if (j != 6) fprintf(fp, "   ");
			else fprintf(fp, "\n");
		}
	}
	fprintf(fp, "----------------------------\n");
	fprintf(fp, "\nt %f ms\n", time);
	fclose(fp);
	return OK;
}