#include "Sat_Puzzle.h"
int deleteclau(pcnf L, int flag) {            //һ���ҳ�һ����Ԫ����ɾ�� 
	pcNode p;    //�Ӿ�ͷ��� 
	plNode q;    //���ֽڵ�
	piNode r;    //������ڵ�
	if (flag > 0) {//������
		r = L->Index_List[flag].firstpos;		// ��ɾȥ�Ӿ� 
		while (r) {
			if (r->p_cnode->exist == 0)   r = r->next;//�Ѿ�ɾ��������ȥ
			else {
				r->p_cnode->exist = 0;
				r->p_cnode->flag = flag;//�þ���Ϊ����flag����ؼ����ֱ�ɾ��
				L->clau_num--;
				r = r->next;
			}
		}
		r = L->Index_List[flag].firstneg;		//ɾ������-flag
		while (r) {
			if (r->p_cnode->exist == 0)  r = r->next;
			else {
				q = r->p_cnode->firstl;
				while (q) {
					if (q->exist == 0)  q = q->next;
					else {
						if (q->l == -flag) {
							q->exist = 0;
							r->p_cnode->l_num--;
							break;
						}
						q = q->next;
					}
				}
				r = r->next;
			}
		}
	}
	else {//������
		r = L->Index_List[-flag].firstneg;////// ��ɾȥ�Ӿ� 
		while (r) {
			if (r->p_cnode->exist == 0)   r = r->next;
			else {
				r->p_cnode->exist = 0;
				r->p_cnode->flag = flag;
				L->clau_num--;
				r = r->next;
			}
		}
		r = L->Index_List[-flag].firstpos; //ɾ������
		while (r) {
			if (r->p_cnode->exist == 0)  r = r->next;
			else {
				q = r->p_cnode->firstl;
				while (q) {
					if (q->exist == 0)  q = q->next;
					else {
						if (q->l == -flag) {
							q->exist = 0;
							r->p_cnode->l_num--;
							break;
						}
						q = q->next;
					}
				}
				r = r->next;
			}
		}
	}


	L->vari_num--;
	return OK;
}

int restoreclau(pcnf L, int flag) {       //�ָ�ǰ����Ϊflag��ɾ����Ԫ�� 
	pcNode p;    //�Ӿ�ͷ��� 
	plNode q;    //���ֽڵ�
	piNode r;    //������ڵ� 
	if (flag > 0) {
		r = L->Index_List[flag].firstpos;          //����Ӿ�
		while (r) {
			if (r->p_cnode->exist == 1)  r = r->next;
			else {
				if (r->p_cnode->flag == flag) {
					r->p_cnode->exist = 1;
					r->p_cnode->flag = 0;
					L->clau_num++;
				}
				r = r->next;
			}
		}
		r = L->Index_List[flag].firstneg;      //�������-flag
		while (r) {
			q = r->p_cnode->firstl;
			while (q) {
				if (q->exist == 0 && q->l == -flag) {
					q->exist = 1;
					r->p_cnode->l_num++;
					break;
				}
				q = q->next;
			}
			r = r->next;
		}
	}
	else {
		r = L->Index_List[-flag].firstneg;          //����Ӿ�
		while (r) {
			if (r->p_cnode->exist == 1)  r = r->next;
			else {
				if (r->p_cnode->flag == flag) {
					r->p_cnode->exist = 1;
					r->p_cnode->flag = 0;
					L->clau_num++;
				}
				r = r->next;
			}
		}
		r = L->Index_List[-flag].firstpos;      //�������
		while (r) {
			q = r->p_cnode->firstl;
			while (q) {
				if (q->exist == 0 && q->l == -flag) {
					q->exist = 1;
					r->p_cnode->l_num++;
					break;
				}
				q = q->next;
			}
			r = r->next;
		}
	}
	L->vari_num++;             //��Ԫ��Ŀ��һ 
	return OK;
}

int EmptyClause(pcnf L) {        //�鿴�Ƿ��пվ� 
	pcNode p = L->firstclau;
	while (p) {
		if (p->l_num == 0 && p->exist == 1) return OK;
		p = p->next;
	}
	return FALSE;
}

int Findl(pcnf L, AnsList& An) {
	pcNode p;
	plNode q;
	int i;
	int flag = 0;
	p = L->firstclau;
	while (p) {
		if (p->exist == 1 && p->l_num == 1) {      //Ѱ�ҵ��Ӿ� 
			q = p->firstl;
			while (q) {
				if (q->exist == 1) {
					if (q->l > 0) 	An.elem[q->l] = 1;
					else    An.elem[-(q->l)] = -1;
					return q->l;
				}
				else q = q->next;
			}
		}
		else p = p->next;
	}
	//���Ӿ䲻���ڣ���Ѱ�ҳ��ִ��������Ǹ���Ԫ
	int* a = (int*)malloc((2 * An.length - 1) * sizeof(int));     //��������a���洢����Ԫ���ֵĴ���
	for (i = 0; i < 2 * An.length - 1; i++) {
		a[i] = 0;
	}
	p = L->firstclau;
	while (p) {                //��¼����Ԫ���ֵĴ��� 
		if (p->exist == 0) p = p->next;	//���Ӿ䱻ɾ��������
		else {
			q = p->firstl;
			while (q) {
				if (q->exist == 0) q = q->next;
				else {
					if (q->l > 0) a[2 * (q->l) - 1]++;//�������ְ��Ŵ����
					else if (q->l < 0)    a[2 * (-(q->l))]++;
					q = q->next;
				}
			}
			p = p->next;
		}
	}
	for (i = 1; i < 2 * An.length - 1; i++) {    //�ҳ����ִ��������ֵ 
		if (a[i] > flag)  flag = a[i];
	}
	for (i = 1; i < 2 * An.length - 1; i++) {  //�ҵ���Ԫ 
		if (a[i] == flag)  break;
	}
	free(a);
	if (i % 2) {//i������
		An.elem[(i + 1) / 2] = 1;
		return ((i + 1) / 2);
	}
	else {
		An.elem[i / 2] = -1;
		return (-(i / 2));
	}
}


int DPLL(pcnf L, AnsList& Ans, int pre_l) {
	int next_l;
	if (L->clau_num == 0) return OK;       //cnf��ʽΪ�գ�����ɹ� 
	else {
		if (EmptyClause(L) == OK) {       //�п��Ӿ� 
			if (restoreclau(L, pre_l) != OK)  printf("�ָ�ʧ��\n");
			if (pre_l > 0) Ans.elem[pre_l] = 0;
			else Ans.elem[-pre_l] = 0;
			return FALSE;
		}
		else {
			next_l = Findl(L, Ans);
			//printf("1"); 
			if (next_l == 0) return FALSE;//���Ĺؼ���Ϊ0���򲻿�����

			if (deleteclau(L, next_l) != OK)  printf("ɾ��ʧ��\n");

			if (DPLL(L, Ans, next_l) == OK)  return OK;
			else {
				if (restoreclau(L, next_l) != OK) printf("�ָ�ʧ��\n");
				if (deleteclau(L, -next_l) != OK) printf("ɾ��ʧ��\n");
				if (DPLL(L, Ans, -next_l) == OK) {
					if (next_l > 0) Ans.elem[next_l] = -1;//���´�
					else  Ans.elem[-next_l] = 1;
					return OK;
				}
				else {
					if (restoreclau(L, -next_l) != OK) printf("�ָ�ʧ��\n");
					if (next_l > 0) Ans.elem[next_l] = 0;
					else Ans.elem[-next_l] = 0;
					return FALSE;
				}
			}
		}
	}
}

int verify(pcnf L, AnsList& An) {       //������Ƿ���ȷ 
	int flag;
	pcNode p;
	plNode q;
	p = L->firstclau;
	while (p) {
		flag = 0;
		q = p->firstl;
		while (q) {
			//����һ������Ϊ��
			if (((q->l > 0) && (An.elem[q->l] == 1)) || ((q->l < 0) && (An.elem[-(q->l)] == -1))) {
				flag = 1;
				break;
			}
			else q = q->next;
		}
		if (flag == 0) break;//��������Ϊ��
		p = p->next;
	}
	if (flag == 0)  return FALSE;
	else return TRUE;
}
