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
		printf("*****	    	�������������� ������� \"����������\"		   *****\n");
		Stars();
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		printf("� ��������� ������������� ������������� � ������������ �� ���������:\n");
		printf("1) �����: admin, ������: 1111;\n");
		printf("2) �����: user, ������: 1111.\n");
		printf("��� ����������� ������� ������� � ������.\n");
		printf("��� ������ �� ��������� �������� 0.\n");
		Line();
		printf("���������� 1 - ��, 0 - ���: \n");
		scanf("%d", &finish);

		if (finish)
		{
			Line();
			printf("������� �������: ");
			scanf("%s", lastName);

			printf("������� ������:");
			scanf("%d", &password);
			Line();
			option = authorization(lastName, password);

			switch (option)
			{
			case 0:
			{

				printf("������ �����������.");
				printf("��������� ������������ ���������� ����� �����.");
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


