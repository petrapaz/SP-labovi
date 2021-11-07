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

int UnosPocetak(Pozicija p);
int UnosKraj(Pozicija p);
int IspisiListu(Pozicija P);
Pozicija TraziElement(Pozicija p);
Pozicija TraziPrethodni(Pozicija p);
int IzbrisiElement(Pozicija p);

///3. zad funkcije pocetak
int UnesiIspred(Pozicija p);
int UnesiIza(Pozicija p);
int SortirajPrez(Pozicija p);
int CitajIzDatoteke(Pozicija p);
int UpisiUDatoteku(Pozicija p);


int main() {

	struct osoba Head; //definiranje head elementa koji pokazuje na NULL
	Head.next = NULL;
	struct osoba* q = NULL;
	int izbor = 1, provjera = 0;

	while (izbor != 0)
	{
		printf("\n1.  Unesi novu osobu na pocetak liste");
		printf("\n2.  Unesi novu osobu na kraj liste");
		printf("\n3.  Ispisi sve osobe sa liste");
		printf("\n4.  Izbrisi osobu iz liste");
		printf("\n5.  Trazi osobu po prezimenu");

		printf("\n6.  Unesi element iza odredjenog elementa");
		printf("\n7.  Unesi element ispred odredjenog elementa");
		printf("\n8.  Sortiraj listu abecedno po prezimenima osoba");
		printf("\n9.  Iscitaj listu iz datoteke");
		printf("\n10. Ispisi listu u datoteku");

		printf("\n0.  Izlaz");
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

		case 6:
			provjera = UnesiIspred(&Head);
			if (provjera == -1)
				printf("\nNije pronadjen element ");
			break;

		case 7:
			provjera = UnesiIza(&Head);
			if (provjera == -1) 
				printf("\nNije pronadjen element ");
			break;

		case 8:
			SortirajPrez(&Head);
			printf("\nSortirana lista po prezimenima:\n");
			IspisiListu(Head.next);
			break;

		case 9:
			provjera = CitajIzDatoteke(&Head);
			if (provjera == -1) 
				printf("Problem s otvaranjem datoteke.\n");
			break;

		case 10:
			provjera = UpisiUDatoteku(Head.next);
			if (provjera == -1) 
				printf("Problem s otvaranjem datoteke.\n");
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
	char unos[MAX];

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


///3. zad funkcije pocetak

int UnesiIspred(Pozicija p)
{
	p = TraziElement(p);
	if (p == NULL)
		return -1;
	UnosPocetak(p); //unosimo novi element ispred trazenog elementa starom funkcijom 

	return 0;
}

int UnesiIza(Pozicija p)
{
	p = TraziPrethodni(p);
	if (p == NULL)
		return -1;
	UnosPocetak(p); //unosimo novi element iza trazenog elementa pomocu stare funkcije

	return 0;
}

int SortirajPrez(Pozicija p)
{
	Pozicija prevj = p, j = NULL, end = NULL, temp = NULL;

	while (p->next != end)
	{
		prevj = p;
		j = p->next;
		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{

				temp = j->next;
				prevj->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prevj = j;
			j = j->next;
		}
		end = j;
	}

	return 0;
}

int CitajIzDatoteke(Pozicija p)
{
	Pozicija temp = NULL;
	FILE* dat = NULL;
	char unos[20];

	printf("Upisite ime datoteke iz koje zelite iscitati listu: ");
	scanf(" %s", unos);

	dat = fopen(unos, "r");

	if (dat == NULL) {
		printf("\nNiste dobro unijeli ime datoteke ili datoteka ne postoji.");
		return -1;
	}

	while (!feof(dat))
	{
		temp = (Pozicija)malloc(sizeof(struct osoba));

		if (temp == NULL) {
			printf("\nDatoteka je prazna!");
			return -1;
		}

		fscanf(dat, " %s %s %d", temp->ime, temp->prezime, &temp->godiste);

		temp->next = p->next;
		p->next = temp;
		p = temp;
	}
	fclose(dat);

	return 0;
}

int UpisiUDatoteku(Pozicija p)
{
	FILE* dat;
	char unos[20];

	printf("Upisite ime datoteke u koju zelite unijeti listu: ");
	scanf(" %s", unos);

	dat = fopen(unos, "w");

	if (dat == NULL)
		return -1;

	while (p != NULL)
	{
		fprintf(dat, "%s\t%s\t%d\n", p->ime, p->prezime, p->godiste);
		p = p->next;
	}

	fclose(dat);
	return 0;
}
