#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

struct polinom;
typedef struct polinom* Polinom;
struct polinom {
	int koeficijent;
	int potencija;
	Polinom next;
};

Polinom NoviPolinom();
int CitajDatoteku(Polinom);
int IspisiPolinom(Polinom);
int ZbrojiPolinome(Polinom, Polinom, Polinom);
int PomnoziPolinome(Polinom, Polinom, Polinom);

int main()
{
	struct polinom p1, p2, suma, produkt;     //suma i produkt ce biti dva nova podatka tipa polinom
	p1.next = p2.next = suma.next = produkt.next = NULL;
	int n;

	printf("\t\tLaboratorijska vjezba 4: POLINOMI\n");
	printf("\nUpisite datoteke iz kojih zelite iscitati polinome:\n");
	n = CitajDatoteku(&p1);
	if (n == -1) 
		printf("Greska! \n");
	
	n = CitajDatoteku(&p2);
	if (n == -1)
		printf("Greska! \n");

	printf("\nPolinom 1:\t ");
	IspisiPolinom(p1.next);
	
	printf("\nPolinom 2:\t ");
	IspisiPolinom(p2.next);

	//zbrajanje
	n = ZbrojiPolinome(p1.next, p2.next, &suma);
	if (n == -1) 
		printf("Greska! \n");
	printf("\n\nSuma:\t");
	IspisiPolinom(suma.next);

	//umnozak
	n = PomnoziPolinome(p1.next, p2.next, &produkt);
	if (n == -1)
		printf("Greska! \n");
	printf("\n\nProdukt:\t ");
	IspisiPolinom(produkt.next);

	printf("\n");

	return 0;
}

Polinom NoviPolinom()
{
	Polinom q = NULL;
	q = (Polinom)malloc(sizeof(struct polinom));
	if (q == NULL) return q;
	q->next = NULL;

	return q;
}

int CitajDatoteku(Polinom P)
{
	FILE* dat = NULL;
	Polinom q = NULL, prev = NULL, temp = NULL;
	char ime[MAX];

	printf("Upisi ime datoteke: ");
	scanf(" %s", ime);

	dat = fopen(ime, "r");
	if (dat == NULL)
		return -1;

	while (!feof(dat))
	{
		q = NoviPolinom();
		if (q == NULL) 
			return -1;
		fscanf(dat, "%d %d", &q->koeficijent, &q->potencija);  //citanje clanova polinoma iz datoteke koji NISU nuzno sortirani
															   //zbog brzine programa bitno ih je odmah sortitirati
		prev = P;
		temp = P->next;

		while (temp != NULL && temp->potencija > q->potencija)  //provjeravanje velicine potencija --> sortiranje !!
		{
			prev = temp;
			temp = temp->next;
		}
		q->next = temp;
		prev->next = q;
	}
	fclose(dat);
	return 0;
}

int IspisiPolinom(Polinom P)
{
	while (P != NULL)
	{
		printf("%d*x^%d  ", P->koeficijent, P->potencija);
		P = P->next;
	}
	return 0;
}

int ZbrojiPolinome(Polinom P1, Polinom P2, Polinom S)
{
	Polinom q, temp;
	q = temp = NULL;

	while (P1 != NULL && P2 != NULL)
	{
		q = NoviPolinom();
		if (q == NULL) return -1;

		if (P1->potencija > P2->potencija)
		{
			q->koeficijent = P1->koeficijent;
			q->potencija = P1->potencija;

			P1 = P1->next;
		}
		else if (P1->potencija < P2->potencija)
		{
			q->koeficijent = P2->koeficijent;
			q->potencija = P2->potencija;

			P2 = P2->next;
		}
		else		//jednake pot
		{
			q->koeficijent = P1->koeficijent + P2->koeficijent;
			q->potencija = P1->potencija;

			P1 = P1->next;
			P2 = P2->next;
		}
		q->next = S->next;
		S->next = q;
		S = q;
	}

	if (P1 != NULL)
		temp = P1;
	else
		temp = P2;

	while (temp != NULL)
	{
		q = NoviPolinom();
		if (q == NULL) return -1;

		q->koeficijent = temp->koeficijent;
		q->potencija = temp->potencija;

		S->next = q;
		S = q;

		temp = temp->next;
	}
	return 0;
}

int PomnoziPolinome(Polinom P1, Polinom P2, Polinom P)
{
	Polinom q = NULL, Pocetak1 = P1, Pocetak2 = P2, temp = P->next, prev = P;
	int ZbrPot;

	while (P1 != NULL)
	{
		P2 = Pocetak2;

		while (P2 != NULL)
		{
			prev = P;
			temp = P->next;

			ZbrPot = P1->potencija + P2->potencija;

			while (temp != NULL && temp->potencija > ZbrPot)
			{
				temp = temp->next;
				prev = prev->next;
			}

			if (temp != NULL && temp->potencija == ZbrPot)
			{
				temp->koeficijent += (P1->koeficijent * P2->koeficijent);
			}
			else
			{
				q = NoviPolinom();
				if (q == NULL) return -1;

				q->koeficijent = P1->koeficijent * P2->koeficijent;
				q->potencija = ZbrPot;

				prev->next = q;
				q->next = temp;
			}
			P2 = P2->next;
		}
		P1 = P1->next;
	}
	return 0;
}