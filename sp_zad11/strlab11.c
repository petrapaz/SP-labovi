/*11. Prepraviti zadatak 10 na način da se formira hash tablica država. Tablica ima 11 mjesta, a
funkcija za preslikavanje ključ računa da se zbraja ASCII vrijednost prvih pet slova države zatim
računa ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice. Države s istim ključem se
pohranjuju u vezanu listu sortiranu po nazivu države. Svaki čvor vezane liste sadrži stablo
gradova sortirano po broju stanovnika, zatim po nazivu grada*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define N 11
#define MAX_SIZE 30
#pragma warning(disable : 4996)

struct cities;
typedef struct cities* position_city;
struct cities
{
    char city_name[MAX_SIZE];
    int population;
    position_city right;
    position_city left;
};

struct countries;
typedef struct countries* position_country;
struct countries
{
    char country_name[20];
    position_city city;
    position_country next;
};

int functionCountry(position_country, char*, char*);
int functionCity(position_city, char*);
position_city addCity(position_city, char*, int);
int printCountries(position_country);
int printCities(position_city);
position_country searchCountry(position_country, char*);
int searchCity(position_city, int);
int countryKey(char*);

int main(void)
{
    struct countries head = { .country_name = "", .city = NULL, .next = NULL };
    struct countries hash[N];

    FILE* f = NULL;
    char enter_country[20];
    char file_city[20];
    int enter_population = 0;
    position_country p = NULL;
    position_city h = NULL;

    int key = 0;
    int i = 0;

    for (i = 0; i < N; i++)
    {
        hash[i].city = NULL;
        hash[i].next = NULL;
        strcpy(hash[i].country_name, "");
    }

    f = fopen("countries.txt", "r");
    if (f == NULL)
    {
        printf("\nERROR: Couldn't open file!");
        return -1;
    }
    while (!feof(f))
    {
        fscanf(f, "%s %s", enter_country, file_city);
        key = countryKey(enter_country);
        functionCountry(&hash[key], enter_country, file_city);
    }
    fclose(f);

    printf("Countries and cities:\n");
    for (i = 0; i < N; i++)
    {
        printf("Hash[%d]:\n", i);
        printCountries(hash[i].next);
    }
    printf("\n\n");

    printf("\nEnter name of country to see its cities: ");
    scanf("%s", enter_country);
    key = countryKey(enter_country);
    p = searchCountry(&hash[key], enter_country);
    if (p == NULL)
    {
        printf("\nERROR: Couldn't find entered country.");
        return 0;
    }
    printf("\nEnter minimum population of city: ");
    scanf("%d", &enter_population);
    printf("\nCities in %s with more than %d population:\n", p->country_name, enter_population);
    searchCity(p->city, enter_population);


    return 0;
}

int functionCountry(position_country p, char* name, char* file)
{
    position_country q = NULL;
    position_country prev = NULL;
    position_city h = NULL;
    q = (position_country)malloc(sizeof(struct countries));
    if (q == NULL)
    {
        printf("\nError while allocating memory!");
        return -1;
    }
    strcpy(q->country_name, name);
    q->city = h;

    h = (position_city)malloc(sizeof(struct cities));
    if (h == NULL)
    {
        printf("\nError while allocating memory!");
        return -1;
    }
    strcpy(h->city_name, "");
    h->population = 0;
    h->right = NULL;
    h->left = NULL;
    q->city = h;
    functionCity(q->city, file);

    prev = p;
    while (p != NULL)
    {
        if (p->next == NULL)
        {
            p->next = q;
            q->next = NULL;
            break;
        }
        if (strcmp(q->country_name, prev->next->country_name) < 0)
        {
            q->next = prev->next;
            prev->next = q;
            break;
        }
        prev = p;
        p = p->next;
    }
    return 0;
}

int functionCity(position_city p, char* file)
{
    FILE* f = NULL;
    char ime[20];
    int stan = 0;

    f = fopen(file, "r");
    if (f == NULL)
    {
        printf("\nERROR: Couldn't open file!");
        return -1;
    }

    while (!feof(f))
    {
        fscanf(f, "%s %d", ime, &stan);
        p = addCity(p, ime, stan);
    }
    fclose(f);
    return 0;
}

position_city addCity(position_city p, char* name, int num_people)
{
    position_city q = NULL;
    if (p == NULL)
    {
        q = (position_city)malloc(sizeof(struct cities));
        if (q == NULL)
        {
            printf("\nError while allocating memory!");
            return NULL;
        }
        strcpy(q->city_name, name);
        q->population = num_people;
        q->left = NULL;
        q->right = NULL;
        return q;
    }
    if (num_people > p->population)
        p->right = addCity(p->right, name, num_people);
    if (num_people < p->population)
        p->left = addCity(p->left, name, num_people);
    if (num_people == p->population)
    {
        if (strcmp(name, p->city_name) >= 0)
            p->right = addCity(p->right, name, num_people);
        else
            p->left = addCity(p->left, name, num_people);
    }

    return p;
}

int printCountries(position_country p)
{
    while (p != NULL)
    {
        printf("%s\n", p->country_name);
        printCities(p->city->right);
        p = p->next;
        printf("\n");
    }
    return 0;
}

int printCities(position_city p)
{
    if (p == NULL)
        return 0;
    printCities(p->left);
    printf("- %s\n", p->city_name);
    printCities(p->right);
    return 0;
}

position_country searchCountry(position_country p, char* name)
{
    while (p != NULL)
    {
        if (strcmp(p->country_name, name) == 0)
            return p;
        p = p->next;
    }
    return p;
}

int searchCity(position_city p, int num)
{
    if (p == NULL)
        return 0;
    searchCity(p->left, num);
    if (p->population >= num)
        printf("- %s : %d\n", p->city_name, p->population);
    searchCity(p->right, num);
    return 0;
}

int countryKey(char* countryName)
{
    int key = 0;
    int i = 0;

    for (i = 0; i < 5; i++)
        key += (int)countryName[i];

    return key % N;
}