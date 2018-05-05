#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include "02.TotalSevice.h"

void main()
{
	setlocale(LC_ALL, "RUS");
	char lastName[30];
	int password;
	int option;

	int finish;
	do
	{
		clear();
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		Stars();
		printf("*****	    	ИНФОРМАЦИОННАЯ СИСТЕМА \"СОТРУДНИКИ\"		   *****\n");
		Stars();
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		printf("В программе предусмотрены администратор и пользователь по умолчанию:\n");
		printf("1) логин: admin, пароль: 1111;\n");
		printf("2) логин: user, пароль: 1111.\n");
		printf("Для авторизации введите фамилию и пароль.\n");
		printf("Для выхода из программы наберите 0.\n");
		Line();
		printf("Продолжить 1 - да, 0 - нет: \n");
		scanf("%d", &finish);

		if (finish)
		{
			Line();
			printf("Введите фамилию: ");
			scanf("%s", lastName);

			printf("Введите пароль:");
			scanf("%d", &password);
			Line();
			option = authorization(lastName, password);

			switch (option)
			{
			case 0:
			{

				printf("Ошибка авторизации.");
				printf("Проверьте правильность заполнения полей ввода.");
				//clear();
			}break;

			case 1:
			{
				adminMenu();

			}break;

			case 2:
			{
				userMenu();
			}break;
			}

		}

	} while (finish != 0);
	system("pause");

}


