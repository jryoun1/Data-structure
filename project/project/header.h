#pragma once

#define TABLE_SIZE 8001
#define	boolean	unsigned char
#define	true	1
#define	false	0

// Hash table
typedef struct {
	char 	key[100];
	char	data[100];
	int		count[10];
} element;
typedef struct list *list_ptr;
typedef struct list {
	element item;
	list_ptr link;
}list;


typedef struct {
	char item[100]; //Ư������ ���� �ܾ� ����
	char only_alpha[100]; //Ư������ ���� �ܾ� ����
	int docnum; //���� ��ȣ ����
}wordstruct;

wordstruct r[TABLE_SIZE];

list_ptr hash_table[TABLE_SIZE];


int num_comparison = 0;		// �񱳸� ���� ����
int word = 0;				// �ܾ� ������ �������� ����
int document = 1;			// ���� ������ �������� ����
int countdocument = 1; //��� �������� �����ϱ� ���ؼ� ������ ����
int wordnumber = 0; //�ߺ��� �������� �ʰ� �� �ܾ��� ����.

void build_search_engine(char *fname); // ���Ͽ��� �ܾ���� �о� �ؽ����̺� ����
char *filter(char *p);// ���Ͽ��� �о���� �ܾ �ƽ�Ű�ڵ�� ���� �� �߶� �Ѱ����� ���ڷ� ��Ÿ���� �Լ� ���� -�� �ϳ��� �ܾ�� �ν�
void hash_insert(char *key, char *data);// �ؽ����̺� (key, data) �ڷ� ����
void * hash_search(char *key);// �ؽ����̺��� Ű���� key�� �ڷḦ �˻�, data�� ��ȯ
int hash(char *key);// �ؽ� �Լ� (folding + division (TABLE_SIZE�� ���� ������))
int transform(char *key);// folding (key�� �� character ���� ����)
void read_record(char *fname); //�ߺ��� �������� �ʰ� �ܾ �����ϴ� �Լ�