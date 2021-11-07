#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

typedef struct osoba* Pozicija;
struct osoba {
	char ime[MAX];
	char prezime[MAX];
	int godiste;
	Pozicija next;
};


int UnosPocetak(Pozicija p) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct osoba));

	if (q == NULL) return NULL;

	printf("Upisite podatke o osobi koju zelite dodati na pocetak liste \nime prezime godiste: ");
	scanf("%s %s %d", q->ime, q->prezime, &q->godiste);

	q->next = p->next;
	p->next = q;

	return 0;
}


int UnosKraj(Pozicija p) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct osoba));

	if (q == NULL) return NULL;

	else {
		printf("Upisite podatke o osobi koju zelite dodati na kraj liste \nime prezime godiste: ");
		scanf("%s %s %d", q->ime, q->prezime, &q->godiste);
		
		//trazimo zadnji element iza kojeg cemo ubacit novi element
		while (p->next != NULL)
		{
			p = p->next;
		}
		q->next = p->next;
		p->next = q;
	}
	return 0;
}

int IspisiListu(Pozicija P) {
	if (P == NULL)
		printf("Lista je prazna! \n");
	else {

		while (P != NULL) {
			printf("%s %s %d\n", P->ime, P->prezime, P->godiste);
			P = P->next;
		}
	}
	return 0;
}


Pozicija TraziElement(Pozicija p) {
	char unos[MAX] ;

	printf("Unesite prezime osobe koju trazite:");
	scanf(" %s", unos);

	while (p != NULL && strcmp(p->prezime, unos) != 0) {
		p = p->next;
	}
	
	if (p == NULL)
		printf("\nOsoba koju ste unijeli ne postoji u listi.\n");

	return p;
}


Pozicija TraziPrethodni(Pozicija p)
{
	char u[20];

	puts("\nUpisite prezime osobe koju trazite:");
	scanf(" %s", u);

	while (p->next != NULL && strcmp(p->next->prezime, u) != 0)
		p = p->next;
	if (p->next == NULL) return NULL;
	return p;
}


int IzbrisiElement(Pozicija p)
{
	Pozicija prev; //moramo pronaci prethodni element onoga kojeg zelimo obrisati
	prev = TraziPrethodni(p);

	if (prev != NULL) {
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
	if (prev == NULL) {
		printf("\nOsoba koju zelite izbrisati ne postoji u listi.");
	}
	return 0;
}


int main() {

	struct osoba Head; //definiranje head elementa koji pokazuje na NULL
	Head.next = NULL;
	struct osoba* q = NULL; 
	int izbor = 1, provjera = 0;

	while (izbor != 0)
	{
		printf("\n1. Unesi novu osobu na pocetak liste");
		printf("\n2. Unesi novu osobu na kraj liste");
		printf("\n3. Ispisi sve osobe sa liste");
		printf("\n4. Izbrisi osobu iz liste");
		printf("\n5. Trazi osobu po prezimenu");
		printf("\n0. Izlaz");
		printf("\n\nUnesi svoj izbor: ");
		scanf("%d", &izbor);

		switch (izbor)
		{
		case 1:
			UnosPocetak(&Head);
			break;
		
		case 2:
			UnosKraj(&Head);
			break;
		
		case 3:
			printf("\nOsobe unesene u listu su:\n");
			IspisiListu(Head.next);
			break;
		
		case 4:
			IzbrisiElement(&Head); 
			printf("\nIzbrisana je trazena osoba.\nOsobe koje su ostale u listi su:\n");
			IspisiListu(Head.next);
			break;

		case 5:
			q = TraziElement(Head.next);
			if (q == NULL)
				printf("\nTrazena osoba ne postoji u listi.");
			else
				printf("\nTrazena osoba je: %s  %s  %d\n", q->ime, q->prezime, q->godiste);
			break;
		
		
		case 0:
			printf("Izlaz iz programa !\n");
			break;

		default:
			printf("Greska!!");
			break;
		}
	}
	return 0;
}
