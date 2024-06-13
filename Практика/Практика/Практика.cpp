// Практика.cpp: главный файл проекта.

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <windows.h>
#include <iostream>

using namespace std;
using namespace System;
using namespace System::IO;

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 75
#define END 77

struct z {
	char name[35];
	char author[20];
	char genre[15];
	long year;
	char office[20];
	long pages;
	long took;
};
struct sp {
	char namee[35];
	char fio[20];
	char genr[15];
	struct sp *pred;
	struct sp *sled;
	long pages;
	long year2;
	long took;
	int k;
};
struct sp* spisok;//сортировка по авторам
struct sp* spisok2;//сортировка по названиям книг
struct sp* spisok3;//сортировка годов*/

int menu(int);
void alfalist(struct z*);
void vstavka(struct z*,char*);
void vod(struct z*);
void two(struct z*,char*);
void god(struct z*);
void go(struct z*,struct z*);
void popular(struct z*);
void best(char *,char *);
void diagram(struct z*);
void povtor(struct z*);
void pot(struct z*,long,char*,char*);

int main(array<System::String ^> ^args)
{
	int i, n;
	int NC;
	char BlankLine[111]="                                                                 ";
	char dan[7][110]={
		"Алфавитный список всех авторов и количество их книг            ",
		"Книги выпущенные в определённый временной промежуток           ",
		"Самая популярная и непопулярная книга                          ",
		"Книги разного жанра,вышедшие в один и тот же год               ",
		"Количество книг определённого жанра                            ",
		"Диаграмма. Процентное соотношение популярности книги           ",
		"Выход                                                          ",
	};
	FILE *in;
	struct z *book;
	setlocale(LC_CTYPE, "Russian");
	Console::CursorVisible::set(false);
	Console::BufferHeight=Console::WindowHeight;
	Console::BufferWidth=Console::WindowWidth;
	if((in=fopen("Список.txt","r"))==NULL){
		printf("\nФайл Список.txt не открыт!");
		getch();exit(1);}
	printf("Список книг:\n");
	printf("\n            Название                Автор                Жанр"
		"            Год  Издательство     Cтраниц Востребованность\n");
	printf("________________________________________________________________"
		"_______________________________________________________");
	fscanf(in,"%d",&NC);
	book=(struct z*)malloc(NC*sizeof(struct z));
	for(i=0;i<NC;i++)
		fscanf(in,"%s%s%s%ld%s%ld%ld",book[i].name, book[i].author, book[i].genre, &book[i].year, book[i].office, &book[i].pages,&book[i].took);
	for(i=0;i<NC;i++)
		printf("\n%-35s %-20s %-15s %ld %-20s %ld %ld", book[i].name, book[i].author, book[i].genre, book[i].year, book[i].office, book[i].pages,book[i].took);
	getch();
	while(1)
	{

		Console::ForegroundColor=ConsoleColor::Cyan;
		Console::BackgroundColor=ConsoleColor::Blue;
		Console::Clear();
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor=ConsoleColor::Cyan;
		Console::CursorLeft=10;
		Console::CursorTop=4;
		printf(BlankLine);
		for(i=0;i<7;i++){
			Console::CursorLeft=10;
			Console::CursorTop=i+5;
			printf(" %s ",dan[i]);
		}
		Console::CursorLeft=10;
		Console::CursorTop=12;
		printf(BlankLine);
		n=menu(7);
		switch(n){
			case 1: alfalist(book); break;
			case 2: god(book); break;
			case 3: popular(book); break;
			case 4: povtor(book); break;
			case 5: vod(book); break;
			case 6: diagram(book); break;
			case 7: exit(0);
		}
	}
return 0;
}
//выбор из меню
int menu(int n)
{
	char dan[7][110]={
		"Алфавитный список всех авторов и количество их книг            ",
		"Книги выпущенные в определённый временной промежуток           ",
		"Самая популярная и непопулярная книга                          ",
		"Книги разного жанра,вышедшие в один и тот же год               ",
		"Количество книг определённого жанра                            ",
		"Диаграмма. Процентное соотношение популярности книги           ",
		"Выход                                                          ",
	};
	int y1=0,y2=n-1;
	char c=1;
	while (c!=ESC)
	{
		switch(c)
		{
			case DOWN: y2=y1; y1++; break;
			case UP: y2=y1; y1--; break;
			case ENTER: return y1+1;
			case HOME: y2=y1; y1=0; break;
			case END: y2=y1; y1=n-1; break;

		}
		if(y1>n-1){y2=n-1;y1=0;}
		if(y1<0) {y2=0;y1=n-1;}
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::Red;
		Console::CursorLeft=11;
		Console::CursorTop=y1+5;
		printf("%s",dan[y1]);
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor=ConsoleColor::Cyan;
		Console::CursorLeft=11;
		Console::CursorTop=y2+5;
		printf("%s",dan[y2]);
		c=getch();
	}
exit(0);
}
//Алфавитный список
void alfalist(struct z* book)
{
	int i;
	int NC;
	FILE *in;
	if((in=fopen("Список.txt","r"))==NULL){
		printf("\nФайл Список.txt не открыт!");
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	struct sp* nt,*z=0;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Yellow;
	Console::Clear();
	if(!spisok)
		for(i=0;i<NC;i++)
			vstavka(book,book[i].author);
	Console::Clear();
	printf("\n Алфавитный список всех авторов");
	printf("\n ===============================\n");
	for(nt=spisok; nt!=0; nt=nt->sled)
		printf("\n %-20s %d",nt->fio,nt->k);
	for(nt=spisok,z=0; nt!=0; z=nt,nt=nt->sled);
	for(nt=z,i=0; nt!=0; nt=nt->pred,i++){
		Console::CursorLeft=35;
		Console::CursorTop=4+i;
		printf(" %-20s %d\n",nt->fio,nt->k);}
	getch();
}
void god(struct z* book)
{
	int i;
	int NC;
	FILE *in;
	if((in=fopen("Список.txt","r"))==NULL){
		printf("\nФайл Список.txt не открыт!");
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	long e,r;
	struct sp* nt;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Yellow;
	Console::Clear();
	if(!spisok3)
		for(i=0;i<NC;i++)
			go(book,&book[i]);
	cout<<"С ";
	cin>>e;
	cout<<"по ";
	cin>>r;
	for(nt=spisok3; nt!=0; nt=nt->sled)
		if(e<=nt->year2 && nt->year2<=r)
			printf("\n%-35s %ld",nt->namee, nt->year2);
	getch();
	return;
}
void go(struct z* book,struct z* item)//сортировка годов
{
	int j;
	int NC;
	FILE *in;
	if((in=fopen("Список.txt","r"))==NULL){
		printf("\nФайл Список.txt не открыт!");
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	struct sp *nov,*nt,*z=0;
	for(nt=spisok3; nt!=0 && nt->year2<item->year; z=nt, nt=nt->sled);
	nov=(struct sp *) malloc(sizeof(struct sp));
	strcpy(nov->namee,item->name);
	strcpy(nov->genr,item->genre);
	nov->year2=item->year;
	nov->sled=nt;
	nov->took=0;
	for(j=0;j<NC;j++){
		if(item->year==book[j].year)
			nov->took+=book[j].took;}
	if(!z) spisok3=nov;
	else z->sled=nov;
	return;
}
//вставка книг в алфавитный список
void vstavka(struct z* book,char* fio)
{
	int i, k = 0;
	int NC;
	FILE *in;
	if((in=fopen("Список.txt","r"))==NULL){
		printf("\nФайл Список.txt не открыт!");
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	struct sp *nov,*nt,*z=0;
	for(nt=spisok; nt!=0 && strcmp(nt->fio,fio)<0; z=nt, nt=nt->sled);
	if(nt && strcmp(nt->fio,fio)==0) return;
	nov=(struct sp *) malloc(sizeof(struct sp));
	strcpy(nov->fio,fio);
	nov->pred=z;
	nov->sled=nt;
	nov->took=0;
	for(i=0;i<NC;i++)
		if(strcmp(book[i].author,fio)==0)
			k+=1;
	nov->k = k;
	if(!z)
		spisok=nov;
	if(z)
		z->sled=nov;
	if(nt)
		nt->pred=nov;
}
void two(struct z* book,char* namee)//сортировка названий книг
{
	int j;
	int NC;
	FILE *in;
	if((in=fopen("Список.txt","r"))==NULL){
		printf("\nФайл Список.txt не открыт!");
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	struct sp *nov,*nt,*z=0;
	for(nt=spisok2; nt!=0 && strcmp(nt->namee,namee)<0; z=nt, nt=nt->sled);
	if(nt && strcmp(nt->namee,namee)==0) return;
	nov=(struct sp *) malloc(sizeof(struct sp));
	strcpy(nov->namee,namee);
	nov->sled=nt;
	nov->took=0;
	for(j=0;j<NC;j++)
		if(strcmp(book[j].name,namee)==0)
			nov->took+=book[j].took;
	if(!z) spisok2=nov;
	else z->sled=nov;
	return;
}
void popular(struct z* book)
{
	int NC;
	FILE *in;
	if((in=fopen("Список.txt","r"))==NULL){
		printf("\nФайл Список.txt не открыт!");
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	int i=0; struct z best;
	int j=0; struct z worst;
	strcpy(best.name,book[0].name);
	best.took=book[0].took;
	for(i=1;i<NC;i++)
		if (book[i].took>best.took)
		{
			strcpy(best.name,book[i].name);
			best.took=book[i].took;
		}
	Console::ForegroundColor=ConsoleColor::Green;
	Console::BackgroundColor=ConsoleColor::Yellow;
	Console::Clear();
	Console::CursorLeft=15;
	Console::CursorTop=5;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Green;
	printf("Самая популярная книга %s",best.name);
	Console::CursorLeft=15;
	Console::CursorTop=6;
	printf("её брали из библиотеки %ld раз",best.took);
	strcpy(worst.name,book[0].name);
	worst.took=book[0].took;
	for(j=1;j<NC;j++)
		if (book[j].took<worst.took)
		{
			strcpy(worst.name,book[j].name);
			worst.took=book[j].took;
		}
	Console::CursorLeft=15;
	Console::CursorTop=9;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Red;
	printf("Самая непопулярная книга %s",worst.name);
	Console::CursorLeft=15;
	Console::CursorTop=10;
	printf("её брали из библиотеки %ld раз",worst.took);
	getch();
}
void vod(struct z* book)//Количество книг определённого жанра
{
	int i;
	int NC;
	FILE *in;
	if((in=fopen("Список.txt","r"))==NULL){
		printf("\nФайл Список.txt не открыт!");
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	char e[15];
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Yellow;
	Console::Clear();
	if(!spisok2)
		for(i=0;i<NC;i++)
			two(book,book[i].name);
	printf("Введите жанр книги: ");
	SetConsoleCP(1251);
	gets(e);
	SetConsoleCP(866);
	for(i=0;i<NC;i++)
		if (strcmp(book[i].genre,e)==0)
			printf("\n%-35s %-20s %ld %s",book[i].name, book[i].author, book[i].year, book[i].genre);
	getch();
	return;
}
void povtor(struct z* book)//Книги разного жанра,вышедшие в один и тот же год
{
	int i,j;
	int NC;
	FILE *in;
	if((in=fopen("Список.txt","r"))==NULL){
		printf("\nФайл Список.txt не открыт!");
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	bool is_exiting = false;
	struct sp* nt1, *nt2;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Yellow;
	Console::Clear();
	if(!spisok3)
		for(i=0;i<NC;i++)
			go(book,&book[i]);
	Console::Clear();
	for(nt1=spisok3; nt1!=0; nt1=nt1->sled){
		for (nt2=nt1->sled; nt2 != 0; nt2=nt2->sled) {
			if(strcmp(nt1->genr,nt2->genr) != 0 && nt1->year2 == nt2->year2){
				Console::ForegroundColor=ConsoleColor::Black;
				Console::BackgroundColor=ConsoleColor::Green;
				printf("Совпадение %ld\n",nt1->year2);
				Console::ForegroundColor=ConsoleColor::Black;
				Console::BackgroundColor=ConsoleColor::Yellow;
				printf("%-15s %-35s\n",nt1->genr,nt1->namee);
				printf("%-15s %-35s\n",nt2->genr,nt2->namee);
				is_exiting = true;
				break;}
		}
		if (is_exiting) break;
	}
	getch();
	return;
}
void diagram(struct z *book)
{
	struct sp *nt;
	int len,i,NColor;
	int NC;
	FILE *in;
	if((in=fopen("Список.txt","r"))==NULL){
		printf("\nФайл Список.txt не открыт!");
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	long tok = 0;
	char str1[35];
	char str2[10];
	System::ConsoleColor Color;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Yellow;
	Console::Clear();
	for(i=0;i<NC;i++)
		tok = tok+book[i].took;
	if(!spisok2)
		for(i=0;i<NC;i++)
			two(book,book[i].name);
	Color=ConsoleColor::Black; NColor=0;
	for(nt=spisok2,i=0; nt!=0; nt=nt->sled,i++){
		sprintf(str1,"%s",nt->namee);
		sprintf(str2,"%3.1f%%",(nt->took*100./tok));
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor= ConsoleColor::Yellow;
		Console::CursorLeft=5; Console::CursorTop=i+1;
		printf(str1);
		Console::CursorLeft=41;
		printf("%s",str2);
		Console::BackgroundColor=++Color;
		NColor++;
		Console::CursorLeft=50;
		for(len=0; len<nt->took*100/tok; len++)
			printf(" ");
		if(NColor==13){
			Color=ConsoleColor::Black;
			NColor=0;}
	}
	getch();
	return;
}