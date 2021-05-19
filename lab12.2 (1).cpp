#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h> 

#define MAX_LEN 1000

typedef struct link
{
	struct link* next;
	double value;
} link_t;

// створення пустого єлемента списка
static link_t* create_link()
{
	link_t* l = (link_t*)malloc(sizeof(link_t));
	l->next = NULL;
	l->value = 0;

	return l;
}

// видалення списка
static void delete_list(link_t** l)
{
	if (l && *l)
	{
		delete_list(&((*l)->next));
		free(*l);
		*l = NULL;
	}
}

// створення списка з файла
static void create_list_from_file(link_t** l, FILE* file)
{
	double c;
	fscanf(file, "%lf", &c);

	if (!feof(file))
	{
		(*l) = create_link();
		(*l)->value = c;

		create_list_from_file(&((*l)->next), file);
	}
}

// печать списка
static void print_list(link_t* l)
{
	link_t* current = l;

	while (current)
	{
		printf("%lf ", current->value);
		current = current->next;
	}

	printf("\n");
}

// провірка на вміст
static bool contains(link_t* l, link_t* w)
{
	// пусті списки
	if (l == NULL || w == NULL)
		return false;

	link_t * currentl = l, *currentw = w;

	// зрівнюємо 2 слова
	while (currentw && currentl)
	{
		if (currentl->value != currentw->value)
			break;

		currentl = currentl->next;
		currentw = currentw->next;
	}

	return !l ? false : currentw ? contains(l->next, w) : true;
}

static bool readList(link_t * *l)
{
	char fileName[255];


	printf("Введите имя файла: \n");
	scanf("%s", fileName);

	FILE* file = fopen(fileName, "r");
	if (!file)
	{
		printf("Не удалось открыть файл %s\n", fileName);
		return false;
	}

	// створюємо список з файлу
	create_list_from_file(l, file);
	fclose(file);

	return true;
}

int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	// пусті списки l1, l2
	link_t* l1 = NULL, * l2 = NULL;

	if (!readList(&l1))
		return EXIT_FAILURE;
	if (!readList(&l2))
		return EXIT_FAILURE;

	
	printf("L1: \n");
	print_list(l1);

	printf("L2: \n");
	print_list(l2);

	if (contains(l1, l2))
		printf("Первый список содержит второй\n");
	else if (contains(l2, l1))
		printf("Второй список содержит первый\n");
	else
		printf("Ни один из списков не содерит друг друга\n");

	delete_list(&l1);
	delete_list(&l2);

	_getch();
	return EXIT_SUCCESS;

}