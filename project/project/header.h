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
	char item[100]; //특수문자 포함 단어 저장
	char only_alpha[100]; //특수문자 제외 단어 저장
	int docnum; //문서 번호 저장
}wordstruct;

wordstruct r[TABLE_SIZE];

list_ptr hash_table[TABLE_SIZE];


int num_comparison = 0;		// 비교를 위한 변수
int word = 0;				// 단어 갯수를 세기위한 변수
int document = 1;			// 문서 갯수를 세기위한 변수
int countdocument = 1; //몇번 문서인지 저장하기 위해서 선언한 변수
int wordnumber = 0; //중복을 제외하지 않고 센 단어의 갯수.

void build_search_engine(char *fname); // 파일에서 단어들을 읽어 해시테이블 구성
char *filter(char *p);// 파일에서 읽어들인 단어를 아스키코드로 변경 후 잘라서 한가지의 숫자로 나타내는 함수 또한 -도 하나의 단어로 인식
void hash_insert(char *key, char *data);// 해시테이블에 (key, data) 자료 삽입
void * hash_search(char *key);// 해시테이블에서 키값이 key인 자료를 검색, data를 반환
int hash(char *key);// 해시 함수 (folding + division (TABLE_SIZE로 나눈 나머지))
int transform(char *key);// folding (key의 각 character 값을 더함)
void read_record(char *fname); //중복을 제거하지 않고 단어를 저장하는 함수