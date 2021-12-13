/*7. Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Točnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 30

struct Stablo;
struct stog;
typedef struct Stablo* Direktorij;
typedef struct stog* Pozicija;

struct Stablo {
	char name[MAX];
	Direktorij sibling;
	Direktorij child;
};

struct stog {
	Direktorij data;
	Pozicija next;
};

Direktorij createNew(); 
Pozicija AllocateMemory();    //alokacija memorije za svako stvaranje direktorija itd
int makeDirectory(Direktorij S, char ime[]);    //stvara novi direktorij
int printDirectory(Direktorij S);		  //ispise children direktorije od parent-a
int Push(Direktorij S, Pozicija P);		//stavlja na stog
Direktorij Pop(Pozicija P);		//mice sa stoga
Direktorij changeDirectory(Direktorij S, Pozicija P, char ime[]);   //promijeni trenutni direktorij

int main()
{
	Direktorij root;
	Direktorij current;
	root = createNew();
	current = createNew();
	current = root;
	int x = 9;
	char input[20];
	Pozicija head;
	head = AllocateMemory();
	strcpy(root->name, "root");

	printf("LABORATORIJSKA VJEZBA 7:\n\n");

	while (x != 0)
	{
		printf("1 - md : make new directory\n"); 
		printf("2 - cd dir : change current directory\n");
		printf("3 - cd.. : leave current directory to parent directory\n");
		printf("4 - dir : print all files from current directory\n");
		printf("0 - exit\n");
		printf("\nChoice number:\n");
		scanf(" %d", &x);

		switch (x)
		{
		case 1:
			printf("Enter name of directory you want to make:\n");
			scanf(" %s", input);
			makeDirectory(current, input);
			break;
		case 2:
			printf("Enter name of a directory you want to enter:\n");
			scanf(" %s", input);
			current = changeDirectory(current, head, input);
			break;
		case 3:
			current = Pop(head);
			break;
		case 4:
			printDirectory(current);
			break;
		case 0:
			printf("Exit.\n");
			break;
		default:
			printf("Something went wrong! Try again!\n");
			break;
		}
		printf("\n");
	}

	return 0;
}

Direktorij createNew()
{
	Direktorij temp = NULL;
	temp = (Direktorij)malloc(sizeof(struct Stablo));
	temp->child = NULL;
	temp->sibling = NULL;
	strcpy(temp->name, " ");

	if (!temp)
	{
		printf("\nSomething went wrong while allocating memory!\n");
		return temp;
	}

	return temp;
}

Pozicija AllocateMemory()
{
	Pozicija temp = NULL;
	temp = (Pozicija)malloc(sizeof(struct stog));
	temp->next = NULL;
	temp->data = NULL;

	if (!temp)
	{
		printf("\nSomething went wrong while allocating memory!\n");
		return temp;
	}

	return temp;
}

int makeDirectory(Direktorij S, char ime[])
{
	Direktorij newDir = createNew();
	strcpy(newDir->name, ime);
	if (S->child == NULL)
		S->child = newDir;
	else
	{
		S = S->child;
		if (S->sibling == NULL)
		{
			S->sibling = newDir;
		}
		else
		{
			while (S->sibling != NULL)
			{
				S = S->sibling;
			}
			S->sibling = newDir;
		}
	}
	return 0;
}

int printDirectory(Direktorij S)
{
	if (S->child == NULL)
	{
		printf("Empty directory!\n");
	}
	else
	{
		if (S->child->sibling == NULL)
		{
			printf("%s\n", S->child->name);
		}
		else
		{
			S = S->child;
			while (S->sibling != NULL)
			{
				printf("%s\n", S->name);
				S = S->sibling;
			}
			printf("%s\n", S->name);
		}
	}
	return 0;
}

int Push(Direktorij S, Pozicija P)
{
	Pozicija newDir = NULL;
	newDir = AllocateMemory();
	if (P->next == NULL)
	{
		newDir = AllocateMemory();
		newDir->data = S;
		P->next = newDir;
	}
	else
	{
		while (P->next != NULL)
		{
			P = P->next;
		}

		newDir = AllocateMemory();
		newDir->data = S;
		P->next = newDir;
	}
	return 0;
}

Direktorij Pop(Pozicija P)
{
	Direktorij x;
	Pozicija temp;

	while (P->next->next != NULL)
	{
		P = P->next;
	}
	x = P->next->data;
	temp = P->next;
	P->next = temp->next;
	free(temp);

	return x;
}

Direktorij changeDirectory(Direktorij S, Pozicija P, char ime[])
{
	Push(S, P);
	Direktorij mainDir = S;

	if (S->child == NULL)
	{
		printf("Empty directory!\n");
	}
	else
	{
		S = S->child;
		while (S->sibling != NULL)
		{
			if (!(strcmp(S->name, ime)))
			{
				return S;
			}
			S = S->sibling;
		}

		if (!(strcmp(S->name, ime)))
		{
			printf("You are currently in directory: %s\n", ime);
			return S;
		}
		else
		{
			printf("Directory from your input does not exist.\n");
			return mainDir;
		}
	}
}
