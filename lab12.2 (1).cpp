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

// ��������� ������� �������� ������
static link_t* create_link()
{
	link_t* l = (link_t*)malloc(sizeof(link_t));
	l->next = NULL;
	l->value = 0;

	return l;
}

// ��������� ������
static void delete_list(link_t** l)
{
	if (l && *l)
	{
		delete_list(&((*l)->next));
		free(*l);
		*l = NULL;
	}
}

// ��������� ������ � �����
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

// ������ ������
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

// ������� �� ����
static bool contains(link_t* l, link_t* w)
{
	// ���� ������
	if (l == NULL || w == NULL)
		return false;

	link_t * currentl = l, *currentw = w;

	// �������� 2 �����
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


	printf("������� ��� �����: \n");
	scanf("%s", fileName);

	FILE* file = fopen(fileName, "r");
	if (!file)
	{
		printf("�� ������� ������� ���� %s\n", fileName);
		return false;
	}

	// ��������� ������ � �����
	create_list_from_file(l, file);
	fclose(file);

	return true;
}

int main()
{
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������
	// ���� ������ l1, l2
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
		printf("������ ������ �������� ������\n");
	else if (contains(l2, l1))
		printf("������ ������ �������� ������\n");
	else
		printf("�� ���� �� ������� �� ������� ���� �����\n");

	delete_list(&l1);
	delete_list(&l2);

	_getch();
	return EXIT_SUCCESS;

}