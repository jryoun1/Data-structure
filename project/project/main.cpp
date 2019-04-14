#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

void main()
{
	char key[50], c;

	//build_search_engine("doc1.txt");		// 1번째 파일
	//build_search_engine("doc2.txt");		// 2번째 파일
	//build_search_engine("doc3.txt");		// 3번째 파일
	//build_search_engine("doc4.txt");		// 4번째 파일

	//read_record("doc1.txt");
	//read_record("doc2.txt");
	//read_record("doc3.txt");
	//read_record("doc4.txt");

	build_search_engine("document1.txt");
	build_search_engine("document2.txt");

	read_record("document1.txt");//단어의 중복을 제외하지 않고 구조체에 첫번째 txt파일의 단어를 하나씩 넣어준다.
	read_record("document2.txt");//단어의 중복을 제외하지 않고 구조체에 두번째 txt파일의 단어를 하나씩 넣어준다.

	
	

	printf("Total number of documents : %d\n", document - 1);
	printf("Total number of indexed words : %d\n", word);
	printf("Total number of comparison : %d\n\n", num_comparison);

	printf("****************************************\n");
	printf("   검색 : S   끝내기 : Q\n");
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
			printf("\n검색할 단어를 입력해주세요 : ");
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
	FILE *ifp;//파일을 불러오기위한 파일포인터
	char temp[50]; //특수문자를 뺀 단어를 넣어줄 배열을 선언.
	

	ifp = fopen(fname, "r");
	while (fscanf(ifp, "%s", r[wordnumber].item) == 1) //단어를 특수문자 포함해서 한단어씩 읽어옴
	{
		int k = 0;
		for (int i = 0; i<50; i++) //배열 초기화
			temp[i] = NULL;
		for (int j = 0; j < strlen(r[wordnumber].item); j++) //각 단어의 길이만큼 for문을 돌려서 특수문자를 제외해줌.
		{
			if (('a' <= r[wordnumber].item[j] && r[wordnumber].item[j] <= 'z') || ('A' <= r[wordnumber].item[j] && r[wordnumber].item[j] <= 'Z'))  //영문자 대소문자 일경우
				temp[k++] = tolower(r[wordnumber].item[j]); //소문자로 바꿔서 temp에 넣어줌.
			else if(r[wordnumber].item[j] == '-') // -일 경우
				temp[k++] = r[wordnumber].item[j]; // 그대로 temp로 넣어줌
		}
		strcpy(r[wordnumber].only_alpha, temp); //r구조체에 onlyalpha에 특수문자를 제외한 단어를 저장해준다.
		r[wordnumber].docnum = countdocument; //단어가 포함된 문서의 번호를 저장해준다.
		wordnumber++; //단어 갯수 증가
	}


	fclose(ifp);

	countdocument++; //문서 번호 증가
}

void build_search_engine(char *fname)// txt파일에서 단어들을 읽어 해시테이블을 만든다.
{
	char key[100];
	char data[100];
	FILE *ifp; //파일을 불러오기위한 파일포인터

	if ((ifp = fopen(fname, "r")) == NULL) // 파일이 존재하지않을때 파일이 없습니다라는 메시지 출력
	{
		printf("파일이 없습니다. \n");
		exit(1);
	}

	while (fscanf(ifp, "%s ", key) == 1) //한단어씩 스캔한다.
	{
		num_comparison++;
		strcpy(data, key); //data에 읽어온 key를 복사한다.
		strcpy(key, filter(key)); //key에서 영문자와 - 만 걸러내어서 key에 다시 복사해준다.
		hash_insert(key, data); //해쉬테이블에 넣어준다.
	}

	++document; //문서의 갯수 증가

	fclose(ifp);
}

char *filter(char *word) //파일에서 읽어들인 단어에서 영문자와 - 만 골라내는 함수
{
	int j = 0;

	char temp[50]; // 받아온 단어에서 영문자와 - 만 포함한 단어를 다시 넣어줄 배열

	for (int i = 0; i<50; i++) //배열 초기화
		temp[i] = NULL;

	for (int i = 0; i < strlen(word); i++)
	{
		if (('a' <= word[i] && word[i] <= 'z') || ('A' <= word[i] && word[i] <= 'Z'))   //영문자 대소문자 일경우
			temp[j++] = tolower(word[i]);  //소문자로 바꿔서 temp에 넣어줌.
		else if(word[i] == '-') // -일 경우
			temp[j++] = word[i]; // 그대로 temp로 넣어줌
	}
	return temp; //temp를 리턴함
}

void hash_insert(char *key, char *data) //해시테이블에 key와 data를 넣어주는 함수.
{
	int i = hash(key); //key의 아스키코드로 변형값을 i에 넣어줌.
	list_ptr temp, trail, lead; //chaining 방식을 이용하기 위해서 포인터 선언.

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
		if (strcmp(lead->item.key, key) == 0) //만약 중복될경우 
		{
			num_comparison++;
			strcpy(temp->item.key, key);
			strcpy(temp->item.data, data);
			lead->item.count[document] += 1;
			return;
		}
	}

	word++;
	//hash table에 처음 넣는 경우
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

void *hash_search(char *key)// 해시테이블에서 키값이 key인 자료를 검색해서 각 문서에 그 단어가 몇번 들어가고 좌우 3단어씩 출력한다.
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
							for (int a = 0; a < wordnumber; a++) //저장된 단어를 다 한번씩 검색해봄.
							{
								
								if (r[a].docnum == max_index) //단어의 문서 번호가 지금 찾는 문서번호와 같다면
								{
									search_num++; //그 단어가 들어간 문서에서 단어를 찾는 비교횟수를 증가시킨다.
									if (strcmp(r[a].only_alpha, temp->item.key) == 0) //단어가 찾는 것이 맞다면
									{
										for (int b = -3; b < 4; b++) //앞뒤로 단어 3개씩 프린트를 해줌,
										{
											if (r[a+b].docnum == max_index) //만약 문서번호가 맞지 않는단어라면 (즉 앞뒤로 3씩 더하고 뻇을때 다른 문서로 넘어감) 프린트하지않는다.
											{
												if(b==-3 && r[a+b-1].docnum == max_index) //첫번째 프린트 하는 던어가 문서의 끝이 아닐 경우 ...을 프린트해준다
													printf("... ");
												printf("%s ", r[a + b].item);
												if (b == 3 && r[a + b + 1].docnum == max_index) //마지막으로 프린트하는 단어가 문서의 끝이 아닐 경우 ...을 프린트해준다.
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
		else //단어를 찾지 못했을 경우
		{
			printf("No search word\n"); 
			return false;
		}
	}

	else//단어를 찾지 못했을 경우
	{
		printf("No search word\n");
		return false;
	}

	return false;
}

int hash(char *key) // 해시 함수 (folding + division (TABLE_SIZE로 나눈 나머지))
{
	return(transform(key) % TABLE_SIZE);
}

int transform(char *key)
{
	int number = 0;
	while (*key)
	{
		number += *key++;  //*key를 통해서 key의 단어들 각각의 아스키코드를 더해준다.
	}
	return number;
}