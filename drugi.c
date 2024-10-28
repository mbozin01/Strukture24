/*2. Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
A.dinamièki dodaje novi element na poèetak liste,
B.ispisuje listu,
C.dinamièki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct person* position;

typedef struct person {
	char name[MAX];
	char surname[MAX];
	int birthYear;
	position next;

}Person;

int addToBeg(position head);
int printList(position q);
int addToEnd(position head);
position findByLn(position q);
int deleteEl(position head);
int menu(position head);

int main() {
	Person head = { {0},{0},0,NULL };
	menu(&head);
	
	return 0;
}
int menu(position head) {
	char pick = '\0';
	position resPerson = NULL;

	while (1) {
		printf("\nZa dodati novi element na pocetak liste upisite 1, za ispisati listu upisite 2, za dodati novi element na kraj liste upisite 3, za pronaci odredeni element u listi po prezimenu upisite 4, za izbrisati odredeni element iz liste upisite 5, za ucitati listu iz datoteke upisite x\n");
		scanf("\n%c", &pick);
		switch (pick) {

		case '1':

			addToBeg(head);

			continue;

		case '2':

			printList(head->next);

			continue;

		case '3':

			addToEnd(head);

			continue;

		case '4':
			findByLn(head->next);

			continue;

		case '5':
			deleteEl(head);
			
			continue;

		case 'x':
			loadFromFile(head);
			continue;


		default:
			printf("\nKrivi unos!!\n");

			break;
		}

		break;
	};


	return 0;
}

int addToBeg(position head) {
	position newPerson;
	newPerson = (Person*)malloc(sizeof(Person));

	if (!newPerson) {
		printf("\nNeuspjela alokacija memorije za newPerson");
		exit(-1);
	}
	newPerson->next = NULL;

	printf("\nUnesite ime, prezime i godinu rodenja osobe koju zelite dodati na pocetak:\n");
	scanf("\n%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);

	newPerson->next = head->next;
	head->next = newPerson;

	return 0;
}

int printList(position q) {
	if (q == NULL)
		return 0;
	else {
		while (q != NULL) {
			printf("%s %s %d\n", q->name, q->surname, q->birthYear);
			q = q->next;
		}
	}

	return 0;
}

int addToEnd(position head) {
	position newPerson = NULL;
	position q = head;
	newPerson = (Person*)malloc(sizeof(Person));

	if (!newPerson) {
		printf("\nNeuspjela alokacija memorije za newPerson");
		exit(-1);
	}
	
	while (newPerson->next != NULL) {
		newPerson = newPerson->next;
	}
	q->next = newPerson->next;
	newPerson->next = q;

	return 0;
}

position findByLn(position q) {
	char lastn[MAX];
	printf("Unesite prezime koje zelite pronaci\n");
	scanf("%s", lastn);
	printf("\n");

	if (q == NULL)
		printf("Osoba s prezimenom %s ne postoji u listi!\n", lastn);

	while (q != NULL && strcmp(q->surname, lastn) != 0) {
		q = q->next;
	}

	return q;
}

int deleteEl(position head) {
	Person del = { {0},{0},0,NULL };
	position temp = NULL, q = head;

	printf("Unesite ime, prezime i godinu rodenja osobe koju zelite izbrisati\n");
	scanf("%s %s %d", del.name, del.surname, &del.birthYear);

	while (q->next != NULL && strcmp(q->next->surname, del.surname) != 0 && strcmp(q->next->name, del.name) != 0 && q->next->birthYear != del.birthYear) {

		q = q->next;
	}


	if (q->next == NULL)
		printf("\nTe osoba nema na listi\n");

	else {
		temp = q->next;
		q->next = temp->next;
		printf("\nOsoba %s %s %d je obrisana!\n", del.name, del.surname, del.birthYear);

	}

	free(temp);

	return 0;
}

int loadFromFile(position head) {
	FILE* file = NULL;
	file = fopen("studenti.txt", "r");
	if (!file) {
		printf("Otvaranje datoteke nije uspjelo\n");
		return -1;
	}

	position temp = head;
	while (!feof(file)) {
		position newPerson = (Person*)malloc(sizeof(Person));
		if (!newPerson) {
			printf("Neuspela alokacija memorije!\n");
			fclose(file);
			return -1;
		}
		newPerson->next = NULL;

		// Èitanje iz datoteke
		if (fscanf(file, "%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear) == 3) {
			// Dodavanje na kraj liste
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newPerson;
		}
		else {
			free(newPerson);
		}
	}

	fclose(file);
	return 0;
}
