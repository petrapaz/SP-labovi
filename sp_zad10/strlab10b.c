/*
10. Napisati program koji čita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država. Uz
ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
države. Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
broj_stanovnika.
a) Potrebno je formirati sortiranu vezanu listu država po nazivu. Svaki čvor vezane liste
sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
b) Potrebno je formirati stablo država sortirano po nazivu. Svaki čvor stabla sadrži vezanu
listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
Nakon formiranja podataka potrebno je ispisati države i gradove te omogućiti korisniku putem
tastature pretragu gradova određene države koji imaju broj stanovnika veći od unosa na
tastaturi.
*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define MAX_SIZE 30
#pragma warning(disable : 4996)

struct cities;
typedef struct cities* position_city;
struct cities
{
    char city_name[20];
    int population;
    position_city next;
};

struct drzave;
typedef struct drzave* poz;
struct drzave
{
    char country_name[20];
    position_city city;
    poz right;
    poz left;
};

poz functionCountry(poz, char*, char*);
int functionCity(position_city, char*);
int printCountriesInorder(poz);
int printCities(position_city);
int cmpCities(position_city, position_city);
int search(poz, char*, int);
poz searchCountry(poz, char*);

int main(void)
{
    printf("\tLABORATORIJSKA VJEZBA 10.b)\n");
    poz root = NULL;
    FILE* fp = NULL;
    char enter_country[MAX_SIZE];
    char file_city[MAX_SIZE];
    int enter_population = 0;

    fp = fopen("countries.txt", "r");
    if (fp == NULL)
    {
        printf("ERROR: Couldn't open file!\n");
        return 0;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%s %s", enter_country, file_city);
        root = functionCountry(root, enter_country, file_city);
    }
    fclose(fp);
    printCountriesInorder(root);

    printf("\nEnter name of country to see its cities: ");
    scanf("%s", enter_country);
    printf("\nEnter minimum population of city: ");
    scanf("%d", &enter_population);
    search(root, enter_country, enter_population);

    return 0;
}

int printCountriesInorder(poz p)
{
    if (p == NULL)
        return 0;
    printCountriesInorder(p->left);
    printf("%s\n", p->country_name);
    printCities(p->city->next);
    printf("\n");
    printCountriesInorder(p->right);
    return 0;
}

int printCities(position_city p)
{
    while (p != NULL)
    {
        printf("- %s : %d\n", p->city_name, p->population);
        p = p->next;
    }
    return 0;
}

poz functionCountry(poz p, char* country_name, char* filecity)
{
    poz q = NULL;
    position_city h = NULL;
    if (p == NULL)
    {
        q = (poz)malloc(sizeof(struct drzave));
        if (q == NULL)
        {
            printf("\nError while allocating memory!");
            return NULL;
        }
        strcpy(q->country_name, country_name);

        h = (position_city)malloc(sizeof(struct cities));
        if (q == NULL)
        {
            printf("\nError while allocating memory!");
            return NULL;
        }
        strcpy(h->city_name, "");
        h->population = 0;
        h->next = NULL;
        q->city = h;

        functionCity(q->city, filecity);
        q->left = NULL;
        q->right = NULL;

        return q;
    }
    else if (strcmp(p->country_name, country_name) > 0)
        p->left = functionCountry(p->left, country_name, filecity);
    else if (strcmp(p->country_name, country_name) < 0)
        p->right = functionCountry(p->right, country_name, filecity);
    return p;
}

int functionCity(position_city p, char* datGrad)
{
    position_city q = NULL;
    FILE* f = NULL;
    char name[MAX_SIZE];
    int num_people = 0;
    position_city prev = p;
    position_city s = p;

    f = fopen(datGrad, "r");
    if (f == NULL)
    {
        printf("\nERROR: Couldn't open file!!");
        return -1;
    }

    while (!feof(f))
    {
        prev = s;
        p = s;
        fscanf(f, "%s %d", name, &num_people);
        q = (position_city)malloc(sizeof(struct cities));
        if (q == NULL)
        {
            printf("\nError while allocating memory!");
            return -1;
        }
        strcpy(q->city_name, name);
        q->population = num_people;
        while (p != NULL)
        {
            if (p->next == NULL)
            {
                q->next = p->next;
                p->next = q;
                break;
            }
            if (cmpCities(q, prev->next) == 1)
            {
                q->next = prev->next;
                prev->next = q;
                break;
            }
            prev = p;
            p = p->next;
        }
    }
    fclose(f);
    return 0;
}

int cmpCities(position_city p, position_city q)
{
    if (p->population > q->population)
        return 1;
    else if (p->population < q->population)
        return -1;
    else
    {
        if (strcmp(p->city_name, q->city_name) > 0)
            return 1;
        else if (strcmp(p->city_name, q->city_name) < 0)
            return -1;
    }
    return 0;
}

int search(poz p, char* countryName, int num_people)
{
    poz drzava = NULL;
    position_city h = NULL;
    int x = 0;

    drzava = searchCountry(p, countryName);
    if (drzava == NULL)
    {
        printf("\nERROR: No such country in the file!");
        return 0;
    }
    h = drzava->city;

    if (h == NULL)
    {
        printf("\nERROR: No cities in %s ...", countryName);
        return 0;
    }
    h = h->next;
    while (h != NULL)
    {
        if (h->population >= num_people)
        {
            printf("- %s\n", h->city_name);
            x = 1;
        }
        else
            break;
        h = h->next;
    }
    if (x == 0)
        printf("\nERROR: No city in %s that meets the conditions...");

    return 0;
}

poz searchCountry(poz p, char* imeDrzave)
{
    if (p == NULL)
        return NULL;
    if (strcmp(imeDrzave, p->country_name) == 0)
        return p;
    if (strcmp(imeDrzave, p->country_name) < 0)
        return searchCountry(p->left, imeDrzave);
    if (strcmp(imeDrzave, p->country_name) > 0)
        return searchCountry(p->right, imeDrzave);
}