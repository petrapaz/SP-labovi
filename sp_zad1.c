#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 100

typedef struct {
	char ime[MAX];
	char prezime[MAX];
	int bodovi;
}Student;

// broji broj redaka u datoteci odnosno broj studenata u navedenoj datoteci
int IzbrojiStudente(FILE* nazivDat) {
	int n = 0;

	while (!feof(nazivDat)) {
		if (fgetc(nazivDat) == '\n') //sporo	
			n++;
	}

	//fclose(nazivDat); //NE RADI s ovim ??
	rewind(nazivDat);		
	return n;
}

void Upis(Student* s, int n, FILE* dat) {		
	int i;
	for (i = 0; i < n; i++)
	{
		fscanf(dat, " %s %s %d \n", s[i].ime, s[i].prezime, &s[i].bodovi); 
	}
	fclose(dat); 
	return;
}

void Ispis(Student* s, int n, double max) {		
	int i;
	double relativno = 0;

	printf("\nIME\t\tPREZIME\t\tBODOVI\t\tRELATIVNI BODOVI\n");
	for (i = 0; i < n; i++)
	{
		relativno = (double)s[i].bodovi / max * 100;		//relativni broj bodova
		printf("%s\t\t%s\t\t%d\t\t%lf\n", s[i].ime, s[i].prezime, s[i].bodovi, relativno);
	}
	return;
}

int main() {
	Student* s;
	double max = 0;
	char unos[MAX];
	int BrSt;

	printf("Upisite ime datoteke: ");
	scanf(" %s", unos);

	FILE* dat = fopen(unos, "r");
	if (dat == NULL) printf("\nGreska pri otvaranju datoteke!");

	BrSt = IzbrojiStudente(dat);
	printf("\nBroj studenata je: %d \n", BrSt);

	//alociranje prostora za studente
	s = (Student*)malloc(BrSt * sizeof(Student));

	printf("\nUnesite maximalan broj bodova:");
	scanf("%lf", &max);

	Upis(s, BrSt, dat);
	Ispis(s, BrSt, max);
	
	fclose(dat);
	return 0;
}