#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

void main()
{
	char key[50], c;

	//build_search_engine("doc1.txt");		// 1��° ����
	//build_search_engine("doc2.txt");		// 2��° ����
	//build_search_engine("doc3.txt");		// 3��° ����
	//build_search_engine("doc4.txt");		// 4��° ����

	//read_record("doc1.txt");
	//read_record("doc2.txt");
	//read_record("doc3.txt");
	//read_record("doc4.txt");

	build_search_engine("document1.txt");
	build_search_engine("document2.txt");

	read_record("document1.txt");//�ܾ��� �ߺ��� �������� �ʰ� ����ü�� ù��° txt������ �ܾ �ϳ��� �־��ش�.
	read_record("document2.txt");//�ܾ��� �ߺ��� �������� �ʰ� ����ü�� �ι�° txt������ �ܾ �ϳ��� �־��ش�.

	
	

	printf("Total number of documents : %d\n", document - 1);
	printf("Total number of indexed words : %d\n", word);
	printf("Total number of comparison : %d\n\n", num_comparison);

	printf("****************************************\n");
	printf("   �˻� : S   ������ : Q\n");
	printf("****************************************\n\n");
	

	while (1)
	{
		printf("Command> ");
		c = getch();
		putch(c);
		c = toupper(c);

		switch (c)
		{
		case 'S':
			printf("\n�˻��� �ܾ �Է����ּ��� : ");
			scanf("%s", key);
			strlwr(key);
			hash_search(key);
			printf("\n");
			break;

		case 'Q':
			printf("\n");
			exit(1);

		default: break;
		}
	}
}

void read_record(char *fname)
{
	FILE *ifp;//������ �ҷ��������� ����������
	char temp[50]; //Ư�����ڸ� �� �ܾ �־��� �迭�� ����.
	

	ifp = fopen(fname, "r");
	while (fscanf(ifp, "%s", r[wordnumber].item) == 1) //�ܾ Ư������ �����ؼ� �Ѵܾ �о��
	{
		int k = 0;
		for (int i = 0; i<50; i++) //�迭 �ʱ�ȭ
			temp[i] = NULL;
		for (int j = 0; j < strlen(r[wordnumber].item); j++) //�� �ܾ��� ���̸�ŭ for���� ������ Ư�����ڸ� ��������.
		{
			if (('a' <= r[wordnumber].item[j] && r[wordnumber].item[j] <= 'z') || ('A' <= r[wordnumber].item[j] && r[wordnumber].item[j] <= 'Z'))  //������ ��ҹ��� �ϰ��
				temp[k++] = tolower(r[wordnumber].item[j]); //�ҹ��ڷ� �ٲ㼭 temp�� �־���.
			else if(r[wordnumber].item[j] == '-') // -�� ���
				temp[k++] = r[wordnumber].item[j]; // �״�� temp�� �־���
		}
		strcpy(r[wordnumber].only_alpha, temp); //r����ü�� onlyalpha�� Ư�����ڸ� ������ �ܾ �������ش�.
		r[wordnumber].docnum = countdocument; //�ܾ ���Ե� ������ ��ȣ�� �������ش�.
		wordnumber++; //�ܾ� ���� ����
	}


	fclose(ifp);

	countdocument++; //���� ��ȣ ����
}

void build_search_engine(char *fname)// txt���Ͽ��� �ܾ���� �о� �ؽ����̺��� �����.
{
	char key[100];
	char data[100];
	FILE *ifp; //������ �ҷ��������� ����������

	if ((ifp = fopen(fname, "r")) == NULL) // ������ �������������� ������ �����ϴٶ�� �޽��� ���
	{
		printf("������ �����ϴ�. \n");
		exit(1);
	}

	while (fscanf(ifp, "%s ", key) == 1) //�Ѵܾ ��ĵ�Ѵ�.
	{
		num_comparison++;
		strcpy(data, key); //data�� �о�� key�� �����Ѵ�.
		strcpy(key, filter(key)); //key���� �����ڿ� - �� �ɷ���� key�� �ٽ� �������ش�.
		hash_insert(key, data); //�ؽ����̺� �־��ش�.
	}

	++document; //������ ���� ����

	fclose(ifp);
}

char *filter(char *word) //���Ͽ��� �о���� �ܾ�� �����ڿ� - �� ��󳻴� �Լ�
{
	int j = 0;

	char temp[50]; // �޾ƿ� �ܾ�� �����ڿ� - �� ������ �ܾ �ٽ� �־��� �迭

	for (int i = 0; i<50; i++) //�迭 �ʱ�ȭ
		temp[i] = NULL;

	for (int i = 0; i < strlen(word); i++)
	{
		if (('a' <= word[i] && word[i] <= 'z') || ('A' <= word[i] && word[i] <= 'Z'))   //������ ��ҹ��� �ϰ��
			temp[j++] = tolower(word[i]);  //�ҹ��ڷ� �ٲ㼭 temp�� �־���.
		else if(word[i] == '-') // -�� ���
			temp[j++] = word[i]; // �״�� temp�� �־���
	}
	return temp; //temp�� ������
}

void hash_insert(char *key, char *data) //�ؽ����̺� key�� data�� �־��ִ� �Լ�.
{
	int i = hash(key); //key�� �ƽ�Ű�ڵ�� �������� i�� �־���.
	list_ptr temp, trail, lead; //chaining ����� �̿��ϱ� ���ؼ� ������ ����.

	temp = (list_ptr)malloc(sizeof(list));
	for (int j = 0; j<10; j++)
		temp->item.count[j] = 0;
	temp->item.count[document] = 1;

	trail = NULL;
	lead = NULL;

	num_comparison++;
	for (lead = hash_table[i]; lead; trail = lead, lead = lead->link)
	{
		num_comparison++;
		if (strcmp(lead->item.key, key) == 0) //���� �ߺ��ɰ�� 
		{
			num_comparison++;
			strcpy(temp->item.key, key);
			strcpy(temp->item.data, data);
			lead->item.count[document] += 1;
			return;
		}
	}

	word++;
	//hash table�� ó�� �ִ� ���
	strcpy(temp->item.key, key); 
	strcpy(temp->item.data, data);
	temp->link = NULL;

	if (trail != NULL)
	{
		trail->link = temp;
	}
	else
	{
		hash_table[i] = temp;
	}
}

void *hash_search(char *key)// �ؽ����̺��� Ű���� key�� �ڷḦ �˻��ؼ� �� ������ �� �ܾ ��� ���� �¿� 3�ܾ ����Ѵ�.
{
	int i, hash_value, max_index = 1; 
	int search_num = 0;
	i = hash_value = hash(key);

	list_ptr temp;

	if ((hash_table[i]->item.key) != 0)
	{
		
		if (strlen(hash_table[i]->item.key) != 0)
		{
			for (temp = hash_table[i]; temp; temp = temp->link)
			{
				
				if (strcmp(temp->item.key, key) == 0)
				{
					for (int j = 1; j < 10; j++)
					{
						if (temp->item.count[j] != 0)
						{
							for (int k = 1; k < 10; k++)
							{
								if (temp->item.count[k] > temp->item.count[max_index])
								{
									max_index = k;
								}
							}
							printf("<document%d.txt> %s: %d\n", max_index, temp->item.key, temp->item.count[max_index]);
							for (int a = 0; a < wordnumber; a++) //����� �ܾ �� �ѹ��� �˻��غ�.
							{
								
								if (r[a].docnum == max_index) //�ܾ��� ���� ��ȣ�� ���� ã�� ������ȣ�� ���ٸ�
								{
									search_num++; //�� �ܾ �� �������� �ܾ ã�� ��Ƚ���� ������Ų��.
									if (strcmp(r[a].only_alpha, temp->item.key) == 0) //�ܾ ã�� ���� �´ٸ�
									{
										for (int b = -3; b < 4; b++) //�յڷ� �ܾ� 3���� ����Ʈ�� ����,
										{
											if (r[a+b].docnum == max_index) //���� ������ȣ�� ���� �ʴ´ܾ��� (�� �յڷ� 3�� ���ϰ� �P���� �ٸ� ������ �Ѿ) ����Ʈ�����ʴ´�.
											{
												if(b==-3 && r[a+b-1].docnum == max_index) //ù��° ����Ʈ �ϴ� ��� ������ ���� �ƴ� ��� ...�� ����Ʈ���ش�
													printf("... ");
												printf("%s ", r[a + b].item);
												if (b == 3 && r[a + b + 1].docnum == max_index) //���������� ����Ʈ�ϴ� �ܾ ������ ���� �ƴ� ��� ...�� ����Ʈ���ش�.
													printf("...");
											}
											
										}
										printf("\n");
									}
									
								}
							}
							printf("\n\n");
							temp->item.count[max_index] = -1;
						}
					}
					printf("Total number of comparison: %d\n", search_num);
				}
			}
		}
		else //�ܾ ã�� ������ ���
		{
			printf("No search word\n"); 
			return false;
		}
	}

	else//�ܾ ã�� ������ ���
	{
		printf("No search word\n");
		return false;
	}

	return false;
}

int hash(char *key) // �ؽ� �Լ� (folding + division (TABLE_SIZE�� ���� ������))
{
	return(transform(key) % TABLE_SIZE);
}

int transform(char *key)
{
	int number = 0;
	while (*key)
	{
		number += *key++;  //*key�� ���ؼ� key�� �ܾ�� ������ �ƽ�Ű�ڵ带 �����ش�.
	}
	return number;
}