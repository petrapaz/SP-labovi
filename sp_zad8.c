/*LAB 8: Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ERROR (-1)
#define SUCCESS (0)

struct Cvor;
typedef struct Cvor _cvor;
typedef struct Cvor* Pozicija;
struct Cvor {
	int element;
	Pozicija right;
	Pozicija left;
};

Pozicija UnesiElement(Pozicija, int);
void inorder(Pozicija);
void preorder(Pozicija);
void postorder(Pozicija);
Pozicija TraziNajmanjiElement(Pozicija);
Pozicija TraziNajveciElement(Pozicija);
Pozicija IzbrisiElement(Pozicija, int);
Pozicija TraziElement(Pozicija, int);
void levelorder(Pozicija);
void PrintLevel(Pozicija, int);
int GetLevelCount(Pozicija);

int main(int argc, char* argv[]) {
	Pozicija root = NULL;
	int izbor = 0;
	int br = 0;
	Pozicija a = NULL;

	//punjenje stabla za lakse testiranje funkcija
	root = UnesiElement(root, 8);
	root = UnesiElement(root, 4);
	root = UnesiElement(root, 6);
	root = UnesiElement(root, 3);
	root = UnesiElement(root, 2);
	root = UnesiElement(root, 7);
	root = UnesiElement(root, 5);
	root = UnesiElement(root, 1);

	printf("\tLABORATORIJSKA VJEZBA 8:");

	while (izbor != 8) {
		printf("\n1 - dodavanje novog elementa");
		printf("\n2 - ispis INORDER");
		printf("\n3 - ispis PREORDER");
		printf("\n4 - ispis POSTORDER");
		printf("\n5 - ispis LEVELORDER");
		printf("\n6 - brisanje odredjenog elementa");
		printf("\n7 - trazenje odredjenog elementa");
		printf("\n8 - izlaz iz programa");
		printf("\n\nUnesite odabir:\t ");
		scanf(" %d", &izbor);

		if (izbor == 1) {
			printf("\nUnesite broj za unosenje u stablo: ");
			scanf(" %d", &br);
			root = UnesiElement(root, br);
		}
		else if (izbor == 2) {
			if (root == NULL) {
				printf("\nStablo je prazno.\n");
				return ERROR;
			}
			else {
				inorder(root);
				printf("\n");
			}
		}
		else if (izbor == 3) {
			if (root == NULL) {
				printf("\nStablo je prazno.\n");
				return ERROR;
			}
			else {
				preorder(root);
				printf("\n");
			}
		}
		else if (izbor == 4) {
			if (root == NULL) {
				printf("\nStablo je prazno.\n");
				return ERROR;
			}
			else {
				postorder(root);
				printf("\n");
			}
		}
		else if (izbor == 5) {
			if (root == NULL) {
				printf("\nStablo je prazno.\n");
				return ERROR;
			}
			else {
				levelorder(root);
				printf("\n");
			}
		}
		else if (izbor == 6) {
			if (root == NULL) {
				printf("\nStablo je prazno\n");
				return ERROR;
			}
			else {
				printf("\nUnesite element za brisanje: ");
				scanf(" %d", &br);

				root = IzbrisiElement(root, br);
			}
		}
		else if (izbor == 7) {
			if (root == NULL) {
				printf("\nStablo je prazno\n");
				return ERROR;
			}
			else {
				printf("\nUnesite element koji zelite pronaci: ");
				scanf(" %d", &br);
				a = TraziElement(root, br);
				if (a != NULL)
					printf("\nElement %d je pronadjen na adresi 0x%xh\n", a->element, (unsigned int)a);
				else printf("\nElement nije pronadjen.\n");
			}
		}
		else if (izbor == 8) {
			printf("\nIzlaz iz programa.\n");
		}
		else printf("\nOdaberite nesto od ponudjenog!\n");
	}
	return SUCCESS;
}

Pozicija UnesiElement(Pozicija P, int br) {
	//alociramo memoriju za novi element i stavljamo ga u stablo
	if (P == NULL) {
		P = (Pozicija)malloc(sizeof(struct Cvor));
		if (P == NULL) {
			printf("\nGreska kod alokacije memorije.\n");
			return P;
		}

		P->element = br;
		P->left = NULL;
		P->right = NULL;
	}
	//ako vec imamo elemente u stablu, provjeravamo je li onaj kojeg unosimo veci ili manji
	//ako je manji postat ce lijevo dijete, a ako je veci desno dijete
	else if (P->element < br)
		P->right = UnesiElement(P->right, br);
	else if (P->element > br)
		P->left = UnesiElement(P->left, br);
	else
		printf("\nElement kojeg zelite unijeti vec postoji u stablu.\n");
	return P;
}
void inorder(Pozicija P) {
	if (P != NULL)
	{
		inorder(P->left);
		printf(" %d", P->element);
		inorder(P->right);
	}
}
void preorder(Pozicija P) {
	if (P != NULL)
	{
		printf(" %d", P->element);
		preorder(P->left);
		preorder(P->right);
	}
}
void postorder(Pozicija P) {
	if (P != NULL)
	{
		postorder(P->left);
		postorder(P->right);
		printf(" %d", P->element);
	}
}
//funkcije za level order ispis
int GetLevelCount(Pozicija p)
{
	if (p == NULL){
		return 0;
	}
	int leftMaxLevel = 1 + GetLevelCount(p->left);
	int rightMaxLevel = 1 + GetLevelCount(p->right);
	if(leftMaxLevel > rightMaxLevel){
		return leftMaxLevel;
	}
	else{
		return rightMaxLevel;
	}
}
void PrintLevel(Pozicija p, int level)
{
	if (p != NULL && level == 0)
	{
		printf(" %d", p->element);
	}
	else if (p != NULL)
	{
		PrintLevel(p->left, level - 1);
		PrintLevel(p->right, level - 1);
	}
}
void levelorder(Pozicija p)
{
	int i;
	int levelCount = GetLevelCount(p);
	for (i = 0; i < levelCount; i++)
	{
		PrintLevel(p, i);
		printf("\n");
	}
}
Pozicija TraziNajmanjiElement(Pozicija P) {
	if (P != NULL && P->left != NULL) {
		return TraziNajmanjiElement(P->left);
	}
	return P;
}
Pozicija IzbrisiElement(Pozicija P, int br) {
	Pozicija temp;
	if (P == NULL) {
		printf("\nElement ne postoji.\n");
	}
	else if (br < P->element)
		P->left = IzbrisiElement(P->left, br);
	else if (br > P->element)
		P->right = IzbrisiElement(P->right, br);
	else {
		if (P->left != NULL && P->right != NULL) {
			// ako je P taj kojeg moramo brisati, umjesto njega mora ici ili najmanji s desnog podstabla ili najveci s lijevog
			temp = TraziNajmanjiElement(P->right);
			P->element = temp->element;
			P->right = IzbrisiElement(P->right, temp->element);
		}
		else {
			//ako P nema djece s lijeve ili desne strane
			temp = P;
			if (P->left == NULL)
				P = P->right;
			else
				P = P->left;
			free(temp);
		}
	}

	return P;
}
Pozicija TraziElement(Pozicija P, int br) {
	if (P == NULL)
		return P;
	//ako je trazeni broj manji od P (poslat cemo root..), trazimo ga s lijeve strane
	if (P->element > br)
		return TraziElement(P->left, br);
	//ako je trazeni broj veci od P, trazimo ga s desne strane
	else if (P->element < br)
		return TraziElement(P->right, br);
	else
		return P;
}
