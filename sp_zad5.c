/*LAB 5: Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct element;
typedef struct element* position;
typedef struct element {
	int x;
	position next;
}el;

int CitajPostfix(position);
int Push(position, int);  //stavljanje elementa na stog
int Pop(position);		  //micanje elementa sa stoga
int IzracunajPostfix(int, int, char*);
int Ispis(position);
int Brojac(position);

int main(void)
{
	el head;
	head.next = NULL;

	printf("\tLABORATORIJSKA VJEZBA 5: POSTFIX IZRAZ I STOG\n\n");

	if (CitajPostfix(&head) != 0)
		printf("Greska!!\n");

	return 0;
}

int CitajPostfix(position p)
{
	FILE* dat = NULL;
	char* filename = NULL;
	char* temp = NULL;
	int x1 = 0, x2 = 0, rez = 0;

	filename = (char*)malloc(20 * sizeof(char));
	if (filename == NULL)
		printf("Greska!!\n");

	temp = (char*)malloc(20 * sizeof(char));
	if (temp == NULL)
		printf("Greska!!\n");

	printf("Unesite ime datoteke : \n");
	scanf("%s", filename);
	//strcat(filename, ".txt");

	dat = fopen(filename, "r");
	if (dat == NULL)
		printf("Greska!!\n");

	while (!feof(dat))
	{
		fscanf(dat, "%s ", temp);

		if (isdigit(*temp))   //provjeri je li ucitani znak znamenka ili ne
		{
			if (Push(p, atoi(temp)) != 0)   //atoi() funkcija pretvara string znakova u int vrijednost
				printf("Greska!!\n");

			printf("Ucitavanje novog elementa na stog :\n");
			if (Ispis(p) != 0)
				printf("Greska!!\n");
		}
		else
		{
			x1 = Pop(p);
			x2 = Pop(p);
			if (x2 == -1)
			{
				printf("Krivo napisan postfix izraz!\n");
				return 0;
			}


			rez = IzracunajPostfix(x1, x2, temp);
			if (Push(p, rez) != 0)
				printf("Greska!!\n");
			if (rez == -1) {
				printf("Greska!!\n");
				return 0;
			}

			printf("Nakon nailaska na operator \"%s\": \n", temp);
			if (Ispis(p) != 0)
				printf("Greska!!\n");
		}
	}

	if (Brojac(p) != 1)
		printf("Krivo napisan postfix izraz!!\n");

	return 0;
}

int Push(position p, int a)
{
	position novo = NULL;

	novo = (position)malloc(sizeof(el));
	if (novo == NULL)
		printf("Greska!!\n");

	novo->x = a;

	novo->next = p->next;
	p->next = novo;

	return 0;
}

int Brojac(position p)
{
	int br = 0;

	while (p->next != NULL)
	{
		br++;
		p = p->next;
	}

	return br;
}

int Ispis(position p)
{
	while (p->next != NULL)
	{
		printf("%d\n", p->next->x);
		p = p->next;
	}

	return 0;
}

int IzracunajPostfix(int a, int b, char* c)
{
	switch (*c)
	{
	case '+':
		return b + a;
		break;
	case '*':
		return b * a;
		break;
	case '-':
		return b - a;
		break;
	case '/':
		if (a == 0)
		{
			printf("Dijeljenje s nulom nije dozvoljeno!\n");
			return -1;
		}
		return b / a;
		break;
	}
}

int Pop(position p)
{
	position temp = NULL;
	int a = 0;

	if (p->next != NULL)
	{
		temp = p->next;
		p->next = p->next->next;
		a = temp->x;
		free(temp);

		return a;
	}
	else
		return -1;

}