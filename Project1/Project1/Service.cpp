#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include "02.TotalSevice.h"
#include<ctime>
#include <stdlib.h>
#include <malloc.h>


FILE * fp;

char path[30] = "employees.txt";
char path2[30] = "employees2.txt"; // файл для хранения журнала посещений
char path3[30] = "employees3.txt";
EMPLOYEE employees;
int count = 0; // количество служащих

			   // структура для получения системного времени
char *settime(struct tm*u)
{
	char s[40];
	char *tmp;
	for (int i = 0; i < 40; i++) s[i] = 0;
	int length = strftime(s, 40, "%d.%m.%Y %H:%M:%S, %A", u);
	tmp = (char *)malloc(sizeof(s));
	strcpy(tmp, s);
	return(tmp);
}

int authorization(char *lastName, int password)
{
	struct tm *u;
	char *f;
	system("chcp 1251");
	system("cls");
	const time_t timer = time(NULL); // 
	u = localtime(&timer);
	f = settime(u);
	//printf("%ld соответствует ", timer);
	//puts(f);
	getchar();

	int flag = 0;

	int index;
	EMPLOYEE * login = (EMPLOYEE*)calloc(1, sizeof(EMPLOYEE));
	LOGIN * loginEmp = (LOGIN*)calloc(1, sizeof(LOGIN));
	if ((fp = fopen(path, "r")) != NULL)
	{
		int i = 0;

		while (fread((login + i), sizeof(EMPLOYEE), 1, fp))
		{
			i++;
			login = (EMPLOYEE*)realloc(login, sizeof(EMPLOYEE)*(i + 1));
		}

		for (int s = 0; s < i; s++)
		{
			if (strcmp((login + s)->lName, lastName) == 0 && (login + s)->eRole == 1 && (login + s)->password == password)
			{
				strcpy(loginEmp->timeLogIn, f);
				strcpy(loginEmp->lNameLog, (login + s)->lName);
				strcpy(loginEmp->fNameLog, (login + s)->fName);
				strcpy(loginEmp->mNameLog, (login + s)->mName);
				strcpy(loginEmp->pstnLog, (login + s)->pos.pstn);
				loginEmp->passwordLog = (login + s)->password;
				index = s;
				flag = 1;
				break;
			}
			else if (strcmp((login + s)->lName, lastName) == 0 && (login + s)->eRole == 0 && (login + s)->password == password)
			{
				strcpy(loginEmp->timeLogIn, f);
				strcpy(loginEmp->lNameLog, (login + s)->lName);
				strcpy(loginEmp->fNameLog, (login + s)->fName);
				strcpy(loginEmp->mNameLog, (login + s)->mName);
				strcpy(loginEmp->pstnLog, (login + s)->pos.pstn);
				loginEmp->passwordLog = (login + s)->password;
				index = s;
				flag = 2;
				break;
			}
		}
		//fclose(fp);
		if ((fp = fopen(path2, "a+")) != NULL)
		{
			fwrite(loginEmp, sizeof(LOGIN), 1, fp);
		}
		else
			printf("Ошибка открытия файла employees2.txt ");

		fclose(fp);

		if (flag == 1)
			return 1;
		else if (flag == 2)
			return 2;
		else
			return 0;
	}
	fclose(fp);
}



void GenerateDate(BIRTHDATE *bdate)
{
	bdate->day = 1 + rand() % 31;
	bdate->month = 1 + rand() % 12;
	bdate->year = 1940 + rand() % 60;
}

void GenerateDate(DATE *date)
{
	date->day = 1 + rand() % 31;
	date->month = 1 + rand() % 12;
	date->year = 1940 + rand() % 60;
}

void GenerateDate(CURRANTDATE *cdate)
{
	//struct tm *u;
	//char *f;
	//system("chcp 1251");
	//system("cls");
	//const time_t timer = time(NULL); // 
	//u = localtime(&timer);
	//f = settime(u);
	////printf("%ld соответствует ", timer);
	////puts(f);
	//getchar();

	cdate->day = 5;
	cdate->month = 5;
	cdate->year = 2018;
}


void GenerateArmyEntryDate(DATE *armyEntryDate, BIRTHDATE *bdate)
{
	armyEntryDate->day = 1 + rand() % 31;
	armyEntryDate->month = 1 + rand() % 12;
	armyEntryDate->year = bdate->year + 18;
}

void GenerateEntryDate(DATE *entryDate, BIRTHDATE *bdate, ARMY *eArmy, int id)
{
	entryDate->day = 1 + rand() % 31;
	entryDate->month = 1 + rand() % 12;

	if (id)
	{
		entryDate->year = eArmy->retire.year;
	}
	else
		entryDate->year = bdate->year + 18 + rand() % 2;
	/*if(!id)
	entryDate->year = bdate->year + 18 + rand()%2;
	else
	entryDate->year = eArmy->retire.year;*/
}

void CreateName(char *name, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		if (i == 0)
			*(name + i) = (char)(65 + rand() % 24);
		else
			*(name + i) = (char)(97 + rand() % 24);
	}
	*(name + len) = '\0';

}

int diffDay(DATE date1, DATE date2)
{
	DATE date3;
	if (date2.day > date1.day)
	{
		date1.month--;
		date1.day += 30;
	}
	date3.day = date1.day - date2.day;

	if (date2.month > date1.month)
	{
		date1.year--;
		date1.month += 12;
	}

	date3.month = date1.month - date2.month;
	date3.year = date1.year - date2.year;

	return date3.year * 365 + date3.month * 12 + date3.day;
}

int diffDay(CURRANTDATE date1, DATE date2)
{
	DATE date3;
	if (date2.day > date1.day)
	{
		date1.month--;
		date1.day += 30;
	}
	date3.day = date1.day - date2.day;

	if (date2.month > date1.month)
	{
		date1.year--;
		date1.month += 12;
	}

	date3.month = date1.month - date2.month;
	date3.year = date1.year - date2.year;

	return date3.year * 365 + date3.month * 12 + date3.day;
}

long long generateIIN(BIRTHDATE*date)
{
	long long yy, mm, dd, aaa, lll;
	long long red;
	yy = date->year % 100;
	mm = date->month;
	dd = date->day;
	aaa = 100 + rand() % 333;
	lll = 100 + rand() % 555;
	red = yy * 10000000000 + mm * 100000000 + dd * 1000000 + aaa * 1000 + lll;
	return red;
}

int generatePassword()
{
	int password = 1000 + rand() % 3333;
	return password;
}



void GenerateRank(ARMY *eRank, int id, BIRTHDATE *bdt)
{
	int num, nRank, disposition;
	//num = 0 + rand() % 2;
	if (id)
	{
		nRank = 1 + rand() % 6;

		switch (nRank)
		{
		case 1:
			strcpy(eRank->rank, "Рядовой");
			break;

		case 2:
			strcpy(eRank->rank, "Старшина");
			break;

		case 3:
			strcpy(eRank->rank, "Лейтенант");
			break;

		case 4:
			strcpy(eRank->rank, "Капитан");
			break;

		case 5:
			strcpy(eRank->rank, "Майор");
			break;

		case 6:
			strcpy(eRank->rank, "Подполковник");
			break;
		}

		eRank->call.day = 1 + rand() % 31;
		eRank->call.month = 1 + rand() % 12;
		eRank->call.year = bdt->year + 18;

		eRank->retire.day = 1 + rand() % 31;
		eRank->retire.month = 1 + rand() % 12;

		eRank->retire.year = eRank->call.year + rand() % 15;
		//eRank->dayOfService = 

		eRank->dayOfService = diffDay(eRank->retire, eRank->call);
		//eRank->dayOfService = (eRank->retire.year - eRank->call.year) * 365;

		disposition = 1 + rand() % 5;
		switch (disposition)
		{
		case 1:
			strcpy(eRank->dispos, "АВОКУ");
			break;

		case 2:
			strcpy(eRank->dispos, "СВО");
			break;

		case 3:
			strcpy(eRank->dispos, "ЗВО");
			break;

		case 4:
			strcpy(eRank->dispos, "ВВО");
			break;

		case 5:
			strcpy(eRank->dispos, "ЮВО");
			break;
		}

	}
	else
	{
		eRank->call.day = 0;
		eRank->call.month = 0;
		eRank->call.year = 0;
		eRank->retire.day = 0;
		eRank->retire.month = 0;
		eRank->retire.year = 0;
		strcpy(eRank->rank, "Невоеннообязанный\n");
		strcpy(eRank->dispos, "Невоеннообязанный\n");
	}
	//eRank->dayOfService = diffDay(eRank->retire, eRank->call);


}

void GeneratePosition(POSITION *position, BIRTHDATE *bdt, ARMY *eRank, int id)
{
	int num;
	num = 1 + rand() % 7;

	switch (num)
	{
	case 1:
		strcpy(position->pstn, "Разнорабочий");
		strcpy(position->sal, "50000");
		//printf("Оклад: %s", employees.pos.sal);
		break;

	case 2:
		strcpy(position->pstn, "Техник");
		strcpy(position->sal, "70000");
		//printf("Оклад: %s", employees.pos.sal);
		break;

	case 3:
		strcpy(position->pstn, "Слесарь");
		strcpy(position->sal, "100000");
		//printf("Оклад: %s", employees.pos.sal);
		break;

	case 4:
		strcpy(position->pstn, "Кладовщик");
		strcpy(position->sal, "120000");
		//printf("Оклад: %s", &employees.pos.sal);
		break;

	case 5:
		strcpy(position->pstn, "Бухгалтер");
		strcpy(position->sal, "150000");
		//printf("Оклад: %s", employees.pos.sal);
		break;

	case 6:
		strcpy(position->pstn, "Начальник смены");
		strcpy(position->sal, "170000");
		//printf("Оклад: %s", employees.pos.sal);
		break;

	case 7:
		strcpy(position->pstn, "Сотрудник администрации");
		strcpy(position->sal, "1000000");
		//printf("Оклад: %s", employees.pos.sal);
		break;
	}

	//eRank->call.day = 1 + rand() % 31;
	//eRank->call.month = 1 + rand() % 12;
	//eRank->call.year = bdt->year + 18;

	//position->yearOfWork = 2018 - position->entryDate.year;
	//position->dayOfWork = diffDay(position->cdate, position->entryDate);

	//eRank->retire.day = 1 + rand() % 31;
	//eRank->retire.month = 1 + rand() % 12;

	//eRank->retire.year = eRank->call.year + rand() % 15;
	////eRank->dayOfService = 

	//eRank->dayOfService = diffDay(eRank->retire, eRank->call);
	////eRank->dayOfService = (eRank->retire.year - eRank->call.year) * 365;


	position->entryDate.day = 1 + rand() % 31;
	position->entryDate.month = 1 + rand() % 12;

	if (id)
	{
		position->entryDate.year = eRank->retire.year;
	}
	else
		position->entryDate.year = bdt->year + 18 + rand() % 2;
	position->yearOfWork = 2018 - position->entryDate.year;
	position->dayOfWork = diffDay(position->cdate, position->entryDate);

}




void PrintInfoEmpoyee(EMPLOYEE * employees, int len)
{

	for (int i = 0; i < len; i++)
	{
		Line();
		printf("Табельный номер: %d\n ", (employees + i)->tblNmb);
		printf("ФИО: %s %s %s\n",
			(employees + i)->lName,
			(employees + i)->fName,
			(employees + i)->mName);


		if ((employees + i)->sex)
			printf("пол: муж.\n");
		else
			printf("пол: жен.\n");

		printf("Дата рождения: %d.%d.%d\n",
			(employees + i)->btd.day,
			(employees + i)->btd.month,
			(employees + i)->btd.year);

		printf("Возраст: %d\n ", (employees + i)->btd.age);

		printf("ИИН: %lld\n", (employees + i)->iin);

		printf("Дата начала работы: %d.%d.%d\n",
			(employees + i)->pos.entryDate.day,
			(employees + i)->pos.entryDate.month,
			(employees + i)->pos.entryDate.year);

		printf("Должность: %s\n", (employees + i)->pos.pstn);

		printf("Оклад: %s\n", (employees + i)->pos.sal);
		printf("Стаж: %d\n ", (employees + i)->pos.yearOfWork);
		printf("Стаж в днях: %d\n ", (employees + i)->pos.dayOfWork);
		if ((employees + i)->eRankId)
		{
			printf("Военнообязанный.\n");
			printf("Звание: %s, Дата призыва: %d.%d.%d, Дата увольнения в запас: %d.%d.%d, воинская часть: %s\n",
				(employees + i)->eRank.rank,
				(employees + i)->eRank.call.day,
				(employees + i)->eRank.call.month,
				(employees + i)->eRank.call.year,
				(employees + i)->eRank.retire.day,
				(employees + i)->eRank.retire.month,
				(employees + i)->eRank.retire.year,
				(employees + i)->eRank.dispos);
			printf("Количество дней службы: %d\n", (employees + i)->eRank.dayOfService);
			//printf("Количество дней службы: %d\n", diffDay((employees + i)->eRank.retire, (employees + i)->eRank.call));
		}


		if ((employees + i)->eRole == 0)
			printf("роль: пользователь\n");
		else
			printf("роль: администратор\n");

		printf("пароль: %ld\n", (employees + i)->password);
		Line();

	}

}

void PrintInfoEmpoyee2(EMPLOYEE * employees)
{
	if ((fp = fopen(path, "r")) != NULL)
	{
		while (fread(employees, sizeof(EMPLOYEE), 1, fp))
		{

			Line();
			printf("Табельный номер: %d\n ", employees->tblNmb);
			printf("ФИО: %s %s %s\n",
				employees->lName,
				employees->fName,
				employees->mName);

			if (employees->sex)
				printf("пол: муж.\n");
			else
				printf("пол: жен.\n");

			printf("Дата рождения: %d.%d.%d\n",
				employees->btd.day,
				employees->btd.month,
				employees->btd.year);

			printf("Возраст: %d\n ", employees->btd.age);

			printf("ИИН: %lld\n", employees->iin);

			printf("Дата начала работы: %d.%d.%d\n",
				employees->pos.entryDate.day,
				employees->pos.entryDate.month,
				employees->pos.entryDate.year);

			printf("Должность: %s\n", employees->pos.pstn);

			printf("Оклад: %s\n", employees->pos.sal);

			printf("Стаж: %d\n", employees->pos.yearOfWork);
			printf("Стаж в днях: %d\n", employees->pos.dayOfWork);
			if (employees->eRankId)
			{
				printf("Военнообязанный.\n");
				printf("Звание: %s, Дата призыва: %d.%d.%d, Дата увольнения в запас: %d.%d.%d, воинская часть: %s\n",
					employees->eRank.rank,
					employees->eRank.call.day,
					employees->eRank.call.month,
					employees->eRank.call.year,
					employees->eRank.retire.day,
					employees->eRank.retire.month,
					employees->eRank.retire.year,
					employees->eRank.dispos);
				printf("Количество дней службы: %d\n", employees->eRank.dayOfService);
			}

			if (employees->eRole == 0)
				printf("роль: пользователь\n");
			else
				printf("роль: администратор\n");

			printf("пароль: %ld\n", employees->password);
			Line();

		}
	}
	fclose(fp);
}

void PrintInfoEmpoyee3(EMPLOYEE * employees)
{
	if ((fp = fopen(path, "r")) != NULL)
	{
		while (fread(employees, sizeof(EMPLOYEE), 1, fp))
		{

			Line();
			printf("Табельный номер: %d\n ", employees->tblNmb);
			printf("ФИО: %s %s %s\n",
				employees->lName,
				employees->fName,
				employees->mName);

			printf("Возраст: %d\n ", employees->btd.age);

			printf("Стаж в днях: %d\n", employees->pos.dayOfWork);

			printf("пароль: %ld\n", employees->password);
			Line();

		}
	}
	fclose(fp);
}




EMPLOYEE *CreateEmployee(int *count)
{
	EMPLOYEE *employees = (EMPLOYEE*)calloc(*count, sizeof(EMPLOYEE));
	if (employees != NULL)
	{
		for (int i = 0; i < *count - 2; i++)
		{
			GenerateDate(&(employees + i)->pos.cdate);
			(employees + i)->tblNmb = 1000 + rand() % 2000; // табельный номер
			CreateName((employees + i)->lName, 10);
			CreateName((employees + i)->fName, 10);
			CreateName((employees + i)->mName, 10);
			(employees + i)->sex = 0 + rand() % 2; // пол
			GenerateDate(&(employees + i)->btd);  // день рождения
			(employees + i)->btd.age = 2018 - (employees + i)->btd.year; // возраст
																		 //GeneratePosition(&(employees + i)->pos); // должность и оклад
			(employees + i)->eRankId = 0 + rand() % 2;
			GenerateRank(&(employees + i)->eRank, (employees + i)->eRankId, &(employees + i)->btd);
			GenerateEntryDate(&(employees + i)->pos.entryDate, &(employees + i)->btd, &(employees + i)->eRank, (employees + i)->eRankId);
			GeneratePosition(&(employees + i)->pos, &(employees + i)->btd, &(employees + i)->eRank, (employees + i)->eRankId);
			(employees + i)->iin = generateIIN(&(employees + i)->btd);
			(employees + i)->password = generatePassword();
			(employees + i)->eRole = 0;
		}
		GenerateDate(&(employees + *count - 1)->pos.cdate);
		(employees + *count - 1)->tblNmb = 0001; // табельный номер
		strcpy((employees + *count - 1)->lName, "admin");
		strcpy((employees + *count - 1)->fName, "admin");
		strcpy((employees + *count - 1)->mName, "admin");
		(employees + *count - 1)->sex = 1; // пол
		GenerateDate(&(employees + *count - 1)->btd);  // день рождения
		(employees + *count - 1)->btd.age = 2018 - (employees + *count - 1)->btd.year; // возраст
																					   //GeneratePosition(&(employees + *count - 1)->pos); // должность и оклад
		(employees + *count - 1)->eRankId = 0 + rand() % 2;
		GenerateRank(&(employees + *count - 1)->eRank, (employees + *count - 1)->eRankId, &(employees + *count - 1)->btd);
		GenerateEntryDate(&(employees + *count - 1)->pos.entryDate, &(employees + *count - 1)->btd, &(employees + *count - 1)->eRank, (employees + *count - 1)->eRankId);
		GeneratePosition(&(employees + *count - 1)->pos, &(employees + *count - 1)->btd, &(employees + *count - 1)->eRank, (employees + *count - 1)->eRankId); // должность и оклад
		(employees + *count - 1)->iin = generateIIN(&(employees + *count - 1)->btd);
		(employees + *count - 1)->password = 1111;
		(employees + *count - 1)->eRole = 1;

		GenerateDate(&(employees + *count - 2)->pos.cdate);
		(employees + *count - 2)->tblNmb = 0002; // табельный номер
		strcpy((employees + *count - 2)->lName, "user");
		strcpy((employees + *count - 2)->fName, "user");
		strcpy((employees + *count - 2)->mName, "user");
		(employees + *count - 2)->sex = 0; // пол
		GenerateDate(&(employees + *count - 2)->btd);  // день рождения
		(employees + *count - 2)->btd.age = 2018 - (employees + *count - 2)->btd.year; // возраст

		(employees + *count - 2)->eRankId = 0 + rand() % 2;
		GenerateRank(&(employees + *count - 2)->eRank, (employees + *count - 2)->eRankId, &(employees + *count - 2)->btd);
		GenerateEntryDate(&(employees + *count - 2)->pos.entryDate, &(employees + *count - 2)->btd, &(employees + *count - 2)->eRank, (employees + *count - 2)->eRankId);
		GeneratePosition(&(employees + *count - 2)->pos, &(employees + *count - 2)->btd, &(employees + *count - 2)->eRank, (employees + *count - 2)->eRankId); // должность и оклад
		(employees + *count - 2)->iin = generateIIN(&(employees + *count - 2)->btd);
		(employees + *count - 2)->password = 1111;
		(employees + *count - 2)->eRole = 0;
	}
	else
	{
		printf("Ошибка!");
		exit(1);
	}
	return employees;
}

void Line()
{
	printf("------------------------------------------------------------------------\n");
}

/* меню для администратора */
void adminMenu()
{
	int p;
	do
	{
		Line();
		printf("\t\t\tМЕНЮ АДМИНИСТРАТОРА\n");
		Line();

		printf("1. Ввод данных новых сотрудников.\n");
		printf("2. Вывод информации о сотрудниках.\n");
		printf("3. Редактирование данных сотрудника.\n");
		printf("4. Удаление сотрудника.\n");
		printf("5. Поиск сотрудника по фамилии.\n");
		printf("6. Поиск сотрудников по возрасту.\n");
		printf("7. Поиск сотрудников по начальной букве.\n");
		printf("8. Список пользователей входивших в систему.\n");
		printf("9. Отчет о военнообязанных с указанием срока службы в днях.\n");
		printf("10. Отчеты по военнообязанным по заданному периоду.\n");
		Line();

		printf("Выберите пункт меню: ");
		scanf("%d", &p);

		switch (p)
		{
			/* перезапись сотрудников */
		case 12:
		{
			count = 5; // ЗАДАЕМ КОЛИЧЕСТВО СОТРУДНИКОВ
			EMPLOYEE *employees;
			Line();
			printf("Записываем данные в файл emloyees.txt\n");
			employees = CreateEmployee(&count);
			PrintInfoEmpoyee(employees, count);
			Line();

			if ((fp = fopen(path, "w")) != NULL)
			{
				fwrite(employees, count * sizeof(EMPLOYEE), 1, fp);
			}
			else
			{
				printf("Ошибка!");
				exit(1);
			}
			fclose(fp);

		}break;

		/* 1. Ввод данных новых сотрудников.*/
		case 1:
		{
			count++; // увеличиваем количесво сотрудников
			EMPLOYEE *employees2 = (EMPLOYEE*)calloc(1, sizeof(EMPLOYEE));
			clear();
			Line();
			printf("\t\t\t1. Ввод данных новых сотрудников.\n\n");
			Line();

			if ((fp = fopen(path, "a")) != NULL)
			{
				//rewind(fp);
				fread(employees2, 1 * sizeof(EMPLOYEE), 1, fp);
				(employees2)->tblNmb = 1000 + rand() % 2000;

				printf("Введите фамилию: ");
				scanf("%s", (employees2)->lName);

				printf("Введите имя: ");
				scanf("%s", (employees2)->fName);

				printf("Введите отчество: ");
				scanf("%s", employees2->mName);

				printf("Введите пол: 0 - жен., 1 - муж.");
				scanf("%d", &employees2->sex);

				printf("Введите дату рождения в формате (дд.мм.гггг): ");
				scanf("%d.%d.%d",
					&employees2->btd.day,
					&employees2->btd.month,
					&employees2->btd.year);

				employees2->btd.age = 2018 - employees2->btd.year;
				printf("Возраст: %d\n", employees2->btd.age);


				printf("Введите должность: \n");
				printf("1. Разнорабочий.\n");
				printf("2. Техник.\n");
				printf("3. Слесарь.\n");
				printf("4. Кладовщик.\n");
				printf("5. Бухгалтер.\n");
				printf("6. Начальник смены.\n");
				printf("7. Сотрудник администрации.\n");
				int position;
				scanf("%d", &position);
				switch (position)
				{
				case 1:
					strcpy(employees2->pos.pstn, "Разнорабочий");
					strcpy(employees2->pos.sal, "50000");
					printf("Должность: %s\n", &employees2->pos.pstn);
					printf("Оклад: %s\n", &employees2->pos.sal);
					break;

				case 2:
					strcpy(employees2->pos.pstn, "Техник");
					strcpy(employees2->pos.sal, "70000");
					printf("Должность: %s\n", &employees2->pos.pstn);
					printf("Оклад: %s\n", &employees2->pos.sal);
					break;

				case 3:
					strcpy(employees2->pos.pstn, "Слесарь");
					strcpy(employees2->pos.sal, "100000");
					printf("Должность: %s\n", &employees2->pos.pstn);
					printf("Оклад: %s\n", &employees2->pos.sal);
					break;

				case 4:
					strcpy(employees2->pos.pstn, "Кладовщик");
					strcpy(employees2->pos.sal, "120000");
					printf("Должность: %s\n", &employees2->pos.pstn);
					printf("Оклад: %s\n", &employees2->pos.sal);
					break;

				case 5:
					strcpy(employees2->pos.pstn, "Бухгалтер");
					strcpy(employees2->pos.sal, "150000");
					printf("Должность: %s\n", &employees2->pos.pstn);
					printf("Оклад: %s\n", &employees2->pos.sal);
					break;

				case 6:
					strcpy(employees2->pos.pstn, "Начальник смены");
					strcpy(employees2->pos.sal, "170000");
					printf("Должность: %s\n", &employees2->pos.pstn);
					printf("Оклад: %s\n", &employees2->pos.sal);
					break;

				case 7:
					strcpy(employees2->pos.pstn, "Сотрудник администрации");
					strcpy(employees2->pos.sal, "1000000");
					printf("Должность: %s\n", &employees2->pos.pstn);
					printf("Оклад: %s\n", &employees2->pos.sal);
					break;
				}

				printf("Введите дату поступления на работу в формате (дд.мм.гггг): ");
				scanf("%d.%d.%d",
					&employees2->pos.entryDate.day,
					&employees2->pos.entryDate.month,
					&employees2->pos.entryDate.year);

				employees2->pos.yearOfWork = 2018 - employees2->pos.entryDate.year;
				printf("Стаж: %d\n ", employees2->pos.yearOfWork);

				GenerateDate(&employees2->pos.cdate);
				employees2->pos.dayOfWork = diffDay(employees2->pos.cdate, employees2->pos.entryDate);
				printf("Стаж в днях: %d\n ", employees2->pos.dayOfWork);

				printf("Военнообязанность: 1 -да, 0 - нет: ");
				scanf("%d", &employees2->eRankId);

				if (employees2->eRankId)
				{
					printf("Введите звание: ");
					printf("1. Рядовой.\n");
					printf("2. Старшина.\n");
					printf("3. Лейтенант.\n");
					printf("4. Капитан.\n");
					printf("5. Майор.\n");
					printf("6. Подполковник.\n");

					int rank;
					scanf("%d", &rank);

					switch (rank)
					{
					case 1:
						strcpy(employees2->eRank.rank, "Рядовой");
						break;

					case 2:
						strcpy(employees2->eRank.rank, "Старшина");
						break;

					case 3:
						strcpy(employees2->eRank.rank, "Лейтенант");
						break;

					case 4:
						strcpy(employees2->eRank.rank, "Капитан");
						break;

					case 5:
						strcpy(employees2->eRank.rank, "Майор");
						break;

					case 6:
						strcpy(employees2->eRank.rank, "Подполковник");
						break;
					}

					printf("Введите дату призыва (дд.мм.гггг): ");
					scanf("%d.%d.%d",
						&employees2->eRank.call.day,
						&employees2->eRank.call.month,
						&employees2->eRank.call.year);

					printf("Введите дату увольнения в запас (дд.мм.гггг): ");
					scanf("%d.%d.%d",
						&employees2->eRank.retire.day,
						&employees2->eRank.retire.month,
						&employees2->eRank.retire.year);

					employees2->eRank.dayOfService = diffDay(employees2->eRank.retire, employees2->eRank.call);
					printf("Количество дней службы: %d\n", employees2->eRank.dayOfService);

					printf("Введите воинскую часть: \n");
					printf("1. АВОКУ.\n");
					printf("2. СВО.\n");
					printf("3. ЗВО.\n");
					printf("4. ВВО.\n");
					printf("5. ЮВО.\n");

					int disposition;
					scanf("%d", &disposition);

					switch (disposition)
					{
					case 1:
						strcpy(employees2->eRank.dispos, "АВОКУ");
						break;

					case 2:
						strcpy(employees2->eRank.dispos, "СВО");
						break;

					case 3:
						strcpy(employees2->eRank.dispos, "ЗВО");
						break;

					case 4:
						strcpy(employees2->eRank.dispos, "ВВО");
						break;

					case 5:
						strcpy(employees2->eRank.dispos, "ЮВО");
						break;
					}

				}
				else
				{
					employees2->eRank.call.day = 0;
					employees2->eRank.call.month = 0;
					employees2->eRank.call.year = 0;
					employees2->eRank.retire.day = 0;
					employees2->eRank.retire.month = 0;
					employees2->eRank.retire.year = 0;
					strcpy(employees2->eRank.rank, "Невоеннообязанный\n");
					strcpy(employees2->eRank.dispos, "Невоеннообязанный\n");
				}

				employees2->password = generatePassword();
				printf("пароль: %ld\n", employees2->password);

				employees2->iin = generateIIN(&employees2->btd);
				printf("ИИН: %lld\n", employees2->iin);

				printf("Роль: 1 - админ, 0 - пользователь.\n");
				scanf("%d", &employees2->eRole);

				fwrite(employees2, sizeof(EMPLOYEE), 1, fp);

				clear();
				printf("Данные успешно сохранены.\n");
			}
			else
				printf("Ошибка!\n");

			Line();
			fclose(fp);
			clear();
		}break;

		/* 2.Инормация о сотрудниках */
		case 2:
		{
			clear();
			Line();
			printf("\t\t\t2.Инормация о сотрудниках.\n");
			Line();

			if ((fp = fopen(path, "r")) != NULL)
			{
				while (fread(&employees, sizeof(EMPLOYEE), 1, fp))
				{
					PrintInfoEmpoyee2(&employees);
				}
			}
			fclose(fp);
		}break;

		/* 3. Редактирование данных сотрудника. */
		case 3:
		{
			clear();
			Line();
			printf("\t\t\t3. Редактирование данных сотрудника.\n");
			Line();
			char lastName[30];
			char tempChar[30];
			int tempInt;
			printf("Введите фамилию сотрудника: ");
			scanf("%s", lastName);
			Line();

			EMPLOYEE * redactedItemd = (EMPLOYEE*)calloc(1, sizeof(EMPLOYEE));
			int j = 0;
			if ((fp = fopen(path, "r")) != NULL)
			{
				int i = 0;

				while (fread((redactedItemd + i), sizeof(EMPLOYEE), 1, fp))
				{
					i++;
					redactedItemd = (EMPLOYEE*)realloc(redactedItemd, sizeof(EMPLOYEE)*(i + 1));
				}

				int ind;
				int flag = 0;
				for (int s = 0; s < i; s++)
				{
					if (strcmp((redactedItemd + s)->lName, lastName) == 0)
					{
						ind = s;
						flag = 1;
						PrintInfoEmpoyee((redactedItemd + s), 1);
						int n;
						do
						{
							Line();
							printf("Выберите поле для редактирования:\n");
							printf("1. Фамилия\n");
							printf("2. Имя\n");
							printf("3. Отчество\n");
							printf("4. Дата рождения\n");
							printf("5. Дата начала работы\n");
							printf("6. Должность и оклад\n");
							printf("7. Звание\n");
							printf("8. Дата призыва\n");
							printf("9. Дата увольнения в запас\n");
							printf("10. Воинская часть\n");
							printf("11. Роль\n");
							printf("12. Пароль\n");

							scanf("%d", &n);
							Line();
							switch (n)
							{
								/* 1. Фамилия */
							case 1:
							{
								Line();
								printf("Текущая фамилия: %s\n",
									(redactedItemd + s)->lName);

								printf("Введите фамилию: ");
								scanf("%s", tempChar);
								strcpy((redactedItemd + s)->lName, tempChar);
								printf("%s\n", (redactedItemd + s)->lName);
								Line();
							}break;

							/* 2. Имя */
							case 2:
							{
								Line();
								printf("Текущее имя: %s\n",
									(redactedItemd + s)->fName);

								printf("Введите имя: ");
								scanf("%s", tempChar);
								strcpy((redactedItemd + s)->fName, tempChar);
								printf("%s\n", (redactedItemd + s)->fName);
								Line();
							}break;

							/* 3. Отчество */
							case 3:
							{
								Line();
								printf("Текущее отчество: %s\n",
									(redactedItemd + s)->mName);

								printf("Введите отчество: ");
								scanf("%s", tempChar);
								strcpy((redactedItemd + s)->mName, tempChar);
								printf("%s\n", (redactedItemd + s)->mName);
								Line();
							}break;

							/* 4. Дата рождения */
							case 4:
							{
								Line();
								printf("Текущая дата рождения: %d.%d.%d\n",
									(redactedItemd + s)->btd.day,
									(redactedItemd + s)->btd.month,
									(redactedItemd + s)->btd.year);
								printf("Введите дату рождения в формате (дд.мм.гггг): ");
								scanf("%d.%d.%d",
									&(redactedItemd + s)->btd.day,
									&(redactedItemd + s)->btd.month,
									&(redactedItemd + s)->btd.year);
								printf("Дата рождения: %d.%d.%d\n",
									(redactedItemd + s)->btd.day,
									(redactedItemd + s)->btd.month,
									(redactedItemd + s)->btd.year);
								Line();
							}break;

							/* 5. Дата начала работы */
							case 5:
							{
								Line();
								printf("Текущая дата поступления на работу: %d.%d.%d\n",
									(redactedItemd + s)->pos.entryDate.day,
									(redactedItemd + s)->pos.entryDate.month,
									(redactedItemd + s)->pos.entryDate.year);

								printf("Введите дату поступления на работу в формате (дд.мм.гггг): ");
								scanf("%d.%d.%d",
									&(redactedItemd + s)->pos.entryDate.day,
									&(redactedItemd + s)->pos.entryDate.month,
									&(redactedItemd + s)->pos.entryDate.year);
								printf("Дата поступления на работу: %d.%d.%d\n",
									(redactedItemd + s)->pos.entryDate.day,
									(redactedItemd + s)->pos.entryDate.month,
									(redactedItemd + s)->pos.entryDate.year);

								Line();
							}break;

							/* 6. Должность и оклад */
							case 6:
							{
								Line();
								printf("Текущая должность: %s\n", (redactedItemd + s)->pos.pstn);
								printf("Текущий оклад: %s\n", &(redactedItemd + s)->pos.sal);
								printf("Введите должность: \n");
								printf("1. Разнорабочий.\n");
								printf("2. Техник.\n");
								printf("3. Слесарь.\n");
								printf("4. Кладовщик.\n");
								printf("5. Бухгалтер.\n");
								printf("6. Начальник смены.\n");
								printf("7. Сотрудник администрации.\n");
								int position;
								scanf("%d", &position);
								switch (position)
								{
								case 1:
									strcpy((redactedItemd + s)->pos.pstn, "Разнорабочий");
									strcpy((redactedItemd + s)->pos.sal, "50000");
									printf("Должность: %s\n", &(redactedItemd + s)->pos.pstn);
									printf("Оклад: %s\n", &(redactedItemd + s)->pos.sal);
									break;

								case 2:
									strcpy((redactedItemd + s)->pos.pstn, "Техник");
									strcpy((redactedItemd + s)->pos.sal, "70000");
									printf("Должность: %s\n", &(redactedItemd + s)->pos.pstn);
									printf("Оклад: %s\n", &(redactedItemd + s)->pos.sal);
									break;

								case 3:
									strcpy((redactedItemd + s)->pos.pstn, "Слесарь");
									strcpy((redactedItemd + s)->pos.sal, "100000");
									printf("Должность: %s\n", &(redactedItemd + s)->pos.pstn);
									printf("Оклад: %s\n", &(redactedItemd + s)->pos.sal);
									break;

								case 4:
									strcpy((redactedItemd + s)->pos.pstn, "Кладовщик");
									strcpy((redactedItemd + s)->pos.sal, "120000");
									printf("Должность: %s\n", &(redactedItemd + s)->pos.pstn);
									printf("Оклад: %s\n", &(redactedItemd + s)->pos.sal);
									break;

								case 5:
									strcpy((redactedItemd + s)->pos.pstn, "Бухгалтер");
									strcpy((redactedItemd + s)->pos.sal, "150000");
									printf("Должность: %s\n", &(redactedItemd + s)->pos.pstn);
									printf("Оклад: %s\n", &(redactedItemd + s)->pos.sal);
									break;

								case 6:
									strcpy((redactedItemd + s)->pos.pstn, "Начальник смены");
									strcpy((redactedItemd + s)->pos.sal, "170000");
									printf("Должность: %s\n", &(redactedItemd + s)->pos.pstn);
									printf("Оклад: %s\n", &(redactedItemd + s)->pos.sal);
									break;

								case 7:
									strcpy((redactedItemd + s)->pos.pstn, "Сотрудник администрации");
									strcpy((redactedItemd + s)->pos.sal, "1000000");
									printf("Должность: %s\n", &(redactedItemd + s)->pos.pstn);
									printf("Оклад: %s\n", &(redactedItemd + s)->pos.sal);
									break;
								}
								Line();
							}break;

							/* 7. Звание */
							case 7:
							{
								Line();
								printf("Текущее звание: %s\n", &(redactedItemd + s)->eRank.rank);

								printf("Введите звание: \n");
								printf("1. Рядовой.\n");
								printf("2. Старшина.\n");
								printf("3. Лейтенант.\n");
								printf("4. Капитан.\n");
								printf("5. Майор.\n");
								printf("6. Подполковник.\n");

								int rank;
								scanf("%d", &rank);
								if (rank)
								{
									(redactedItemd + s)->eRankId = 1;
								}
								switch (rank)
								{

								case 1:
									strcpy((redactedItemd + s)->eRank.rank, "Рядовой");
									printf("Звание: %s\n", &(redactedItemd + s)->eRank.rank);
									break;

								case 2:
									strcpy((redactedItemd + s)->eRank.rank, "Старшина");
									printf("Звание: %s\n", &(redactedItemd + s)->eRank.rank);
									break;

								case 3:
									strcpy((redactedItemd + s)->eRank.rank, "Лейтенант");
									printf("Звание: %s\n", &(redactedItemd + s)->eRank.rank);
									break;

								case 4:
									strcpy((redactedItemd + s)->eRank.rank, "Капитан");
									printf("Звание: %s\n", &(redactedItemd + s)->eRank.rank);
									break;

								case 5:
									strcpy((redactedItemd + s)->eRank.rank, "Майор");
									printf("Звание: %s\n", &(redactedItemd + s)->eRank.rank);
									break;

								case 6:
									strcpy((redactedItemd + s)->eRank.rank, "Подполковник");
									printf("Звание: %s\n", &(redactedItemd + s)->eRank.rank);
									break;
								}
								Line();
							}break;

							/* 8. Дата призыва */
							case 8:
							{
								Line();
								printf("Текущая дата призыва: %d.%d.%d\n",
									(redactedItemd + s)->eRank.call.day,
									(redactedItemd + s)->eRank.call.month,
									(redactedItemd + s)->eRank.call.year);

								printf("Введите дату призыва (дд.мм.гггг): ");
								scanf("%d.%d.%d",
									&(redactedItemd + s)->eRank.call.day,
									&(redactedItemd + s)->eRank.call.month,
									&(redactedItemd + s)->eRank.call.year);

								if (&(redactedItemd + s)->eRank.call.day != 0)
								{
									(redactedItemd + s)->eRankId = 1;
								}

								printf("Дата призыва: %d.%d.%d\n",
									(redactedItemd + s)->eRank.call.day,
									(redactedItemd + s)->eRank.call.month,
									(redactedItemd + s)->eRank.call.year);
								Line();

							}break;

							/* 9. Дата увольнения в запас */
							case 9:
							{
								Line();
								printf("Текущая дата увольнения в запас: %d.%d.%d\n",
									(redactedItemd + s)->eRank.retire.day,
									(redactedItemd + s)->eRank.retire.month,
									(redactedItemd + s)->eRank.retire.year);
								printf("Введите дату увольнения в запас (дд.мм.гггг): ");
								scanf("%d.%d.%d",
									&(redactedItemd + s)->eRank.retire.day,
									&(redactedItemd + s)->eRank.retire.month,
									&(redactedItemd + s)->eRank.retire.year);

								if (&(redactedItemd + s)->eRank.call.day != 0)
								{
									(redactedItemd + s)->eRankId = 1;
								}
								printf("Дата увольнения в запас: %d.%d.%d\n",
									(redactedItemd + s)->eRank.retire.day,
									(redactedItemd + s)->eRank.retire.month,
									(redactedItemd + s)->eRank.retire.year);
								Line();
							}break;

							/* 10. Воинская часть */
							case 10:
							{
								Line();
								printf("Текущая воинская часть: %s\n", &(redactedItemd + s)->eRank.dispos);
								printf("Введите воинскую часть: \n");
								printf("1. АВОКУ.\n");
								printf("2. СВО.\n");
								printf("3. ЗВО.\n");
								printf("4. ВВО.\n");
								printf("5. ЮВО.\n");

								int disposition;
								scanf("%d", &disposition);

								switch (disposition)
								{
									if (&(redactedItemd + s)->eRank.call.day != 0)
									{
										(redactedItemd + s)->eRankId = 1;
									}
								case 1:
									strcpy((redactedItemd + s)->eRank.dispos, "АВОКУ");
									printf("Воинская часть: %s\n", &(redactedItemd + s)->eRank.dispos);
									break;

								case 2:
									strcpy((redactedItemd + s)->eRank.dispos, "СВО");
									printf("Воинская часть: %s\n", &(redactedItemd + s)->eRank.dispos);
									break;

								case 3:
									strcpy((redactedItemd + s)->eRank.dispos, "ЗВО");
									printf("Воинская часть: %s\n", &(redactedItemd + s)->eRank.dispos);
									break;

								case 4:
									strcpy((redactedItemd + s)->eRank.dispos, "ВВО");
									printf("Воинская часть: %s\n", &(redactedItemd + s)->eRank.dispos);
									break;

								case 5:
									strcpy((redactedItemd + s)->eRank.dispos, "ЮВО");
									printf("Воинская часть: %s\n", &(redactedItemd + s)->eRank.dispos);
									break;
								}
								Line();
							}break;

							/* 11. Роль */
							case 11:
							{
								Line();
								if ((redactedItemd + s)->eRole == 0)
									printf("Текущая роль: %s\n", "пользователь.");
								else
									printf("Текущая роль: %s\n", "админ.");

								printf("Введите роль: \n");
								scanf("%d", &(redactedItemd + s)->eRole);

								if ((redactedItemd + s)->eRole == 0)
									printf("Роль: %s\n", "пользователь.");
								else
									printf("Роль: %s\n", "админ.");
								Line();

							}break;

							/* 12. Пароль */
							case 12:
							{
								Line();
								printf("Текущий пароль: %ld\n", (redactedItemd + s)->password);
								(redactedItemd + s)->password = generatePassword();
								printf("Сгенерированный пароль: %ld\n", (redactedItemd + s)->password);
								Line();

							}break;

							default:
							{
								Line();
								printf("Такого поля нет.\n");
								printf("Выберите поле еще раз.\n");
								Line();
							}break;

							}
							(redactedItemd + s)->eRank.dayOfService = diffDay((redactedItemd + s)->eRank.retire, (redactedItemd + s)->eRank.call);
						} while (n != 0);

					}

				}

				count = i;

				if (!flag)
				{
					printf("По Вашему запросу ничего не найдено.\n");
				}
				else
					PrintInfoEmpoyee((redactedItemd + ind), 1);
			}
			fclose(fp);

			if ((fp = fopen(path, "w")) != NULL)
			{
				fwrite(redactedItemd, sizeof(EMPLOYEE)*count, 1, fp);
			}
			fclose(fp);

		}break;

		/* 4. Удаление сотрудника. */
		//case 4:
		//{
		//	clear();
		//	char lastName[30];
		//	Stars();
		//	printf("\t\t\t4. Удаление сотрудника.\n");
		//	Line();
		//	printf("Введите фамилию сотрудника: ");
		//	scanf("%s", lastName);
		//	Line();

		//	EMPLOYEE * eLastName1 = (EMPLOYEE*)calloc(count, sizeof(EMPLOYEE));

		//	int index;
		//	int p = 0;
		//	if ((fp = fopen(path, "r")) != NULL)
		//	{

		//		while (fread((eLastName1 + p), sizeof(EMPLOYEE), 1, fp))
		//		{
		//			p++;
		//			eLastName1 = (EMPLOYEE*)realloc(eLastName1, sizeof(EMPLOYEE)*(p + 1));
		//		}

		//		for (int s = 0; s < p; s++)
		//		{
		//			if (strcmp((eLastName1 + s)->lName, lastName) == 0)
		//			{
		//				PrintInfoEmpoyee((eLastName1 + s), 1);
		//				index = s;
		//			}
		//		}

		//		//count--;

		//	}
		//	fclose(fp);

		//	EMPLOYEE * eLastName2 = (EMPLOYEE*)calloc(p - 1, sizeof(EMPLOYEE));
		//
		//	for (int i = 0; i < p - 1; i++)
		//	{
		//		if (i<index)
		//		{
		//			(eLastName2 + i)->tblNmb = (eLastName1 + i)->tblNmb; // табельный номер

		//			strcpy((eLastName2 + i)->lName, (eLastName1 + i)->lName);
		//			strcpy((eLastName2 + i)->fName, (eLastName1 + i)->fName);
		//			strcpy((eLastName2 + i)->mName, (eLastName1 + i)->mName);
		//	
		//			(eLastName2 + i)->sex = (eLastName1 + i)->sex;

		//			(eLastName2 + i)->btd.day = (eLastName1 + i)->btd.day;
		//			(eLastName2 + i)->btd.month = (eLastName1 + i)->btd.month;
		//			(eLastName2 + i)->btd.year = (eLastName1 + i)->btd.year;

		//			(eLastName2 + i)->btd.age = (eLastName1 + i)->btd.age;

		//			(eLastName2 + i)->iin = (eLastName1 + i)->iin;

		//			(eLastName2 + i)->pos.entryDate.day = (eLastName1 + i)->pos.entryDate.day;
		//			(eLastName2 + i)->pos.entryDate.month = (eLastName1 + i)->pos.entryDate.month;
		//			(eLastName2 + i)->pos.entryDate.year = (eLastName1 + i)->pos.entryDate.year;

		//			(eLastName2 + i)->pos.dayOfWork = (eLastName1 + i)->pos.dayOfWork;
		//			(eLastName2 + i)->pos.yearOfWork = (eLastName1 + i)->pos.yearOfWork;

		//			strcpy((eLastName2 + i)->pos.pstn, (eLastName1 + i)->pos.pstn);
		//			strcpy((eLastName2 + i)->pos.sal, (eLastName1 + i)->pos.sal);


		//			(eLastName2 + i)->eRankId = (eLastName1 + i)->eRankId;
		//			strcpy((eLastName2 + i)->eRank.rank, (eLastName1 + i)->eRank.rank);
		//			(eLastName2 + i)->eRank.call.day = (eLastName1 + i)->eRank.call.day;
		//			(eLastName2 + i)->eRank.call.month = (eLastName1 + i)->eRank.call.month;
		//			(eLastName2 + i)->eRank.call.year = (eLastName1 + i)->eRank.call.year;
		//			(eLastName2 + i)->eRank.retire.day = (eLastName1 + i)->eRank.retire.day;
		//			(eLastName2 + i)->eRank.retire.month = (eLastName1 + i)->eRank.retire.month;
		//			(eLastName2 + i)->eRank.retire.year = (eLastName1 + i)->eRank.retire.year;
		//			strcpy((eLastName2 + i)->eRank.dispos, (eLastName1 + i)->eRank.dispos);
		//			(eLastName2 + i)->eRank.dayOfService = (eLastName1 + i)->eRank.dayOfService;

		//			(eLastName2 + i)->eRole = (eLastName1 + i)->eRole;

		//			(eLastName2 + i)->password = (eLastName1 + i)->password;

		//		}
		//		else if (i>= index)
		//		{
		//			(eLastName2 + i)->tblNmb = (eLastName1 + i+1)->tblNmb; // табельный номер

		//			strcpy((eLastName2 + i)->lName, (eLastName1 + i+1)->lName);
		//			strcpy((eLastName2 + i)->fName, (eLastName1 + i+1)->fName);
		//			strcpy((eLastName2 + i)->mName, (eLastName1 + i+1)->mName);

		//			(eLastName2 + i)->sex = (eLastName1 + i+1)->sex;

		//			(eLastName2 + i)->btd.day = (eLastName1 + i+1)->btd.day;
		//			(eLastName2 + i)->btd.month = (eLastName1 + i+1)->btd.month;
		//			(eLastName2 + i)->btd.year = (eLastName1 + i+1)->btd.year;

		//			(eLastName2 + i)->btd.age = (eLastName1 + i+1)->btd.age;

		//			(eLastName2 + i)->iin = (eLastName1 + i+1)->iin;

		//			(eLastName2 + i)->pos.entryDate.day = (eLastName1 + i+1)->pos.entryDate.day;
		//			(eLastName2 + i)->pos.entryDate.month = (eLastName1 + i+1)->pos.entryDate.month;
		//			(eLastName2 + i)->pos.entryDate.year = (eLastName1 + i+1)->pos.entryDate.year;

		//			(eLastName2 + i)->pos.dayOfWork = (eLastName1 + i + 1)->pos.dayOfWork;
		//			(eLastName2 + i)->pos.yearOfWork = (eLastName1 + i + 1)->pos.yearOfWork;

		//			strcpy((eLastName2 + i)->pos.pstn, (eLastName1 + i+1)->pos.pstn);
		//			strcpy((eLastName2 + i)->pos.sal, (eLastName1 + i+1)->pos.sal);


		//			(eLastName2 + i)->eRankId = (eLastName1 + i+1)->eRankId;
		//			strcpy((eLastName2 + i)->eRank.rank, (eLastName1 + i+1)->eRank.rank);
		//			(eLastName2 + i)->eRank.call.day = (eLastName1 + i+1)->eRank.call.day;
		//			(eLastName2 + i)->eRank.call.month = (eLastName1 + i+1)->eRank.call.month;
		//			(eLastName2 + i)->eRank.call.year = (eLastName1 + i+1)->eRank.call.year;
		//			(eLastName2 + i)->eRank.retire.day = (eLastName1 + i+1)->eRank.retire.day;
		//			(eLastName2 + i)->eRank.retire.month = (eLastName1 + i+1)->eRank.retire.month;
		//			(eLastName2 + i)->eRank.retire.year = (eLastName1 + i+1)->eRank.retire.year;
		//			strcpy((eLastName2 + i)->eRank.dispos, (eLastName1 + i+1)->eRank.dispos);
		//			(eLastName2 + i)->eRank.dayOfService = (eLastName1 + i+1)->eRank.dayOfService;

		//			(eLastName2 + i)->eRole = (eLastName1 + i+1)->eRole;

		//			(eLastName2 + i)->password = (eLastName1 + i+1)->password;
		//		}				
		//	}

		//	if ((fp = fopen(path, "w")) != NULL)
		//	{
		//		fwrite(eLastName2, sizeof(EMPLOYEE)*count, 1, fp);
		//	}
		//	fclose(fp);

		//}break;

		/* 5. Поиск сотрудника по фамилии.*/
		case 5:
		{
			clear();
			char lastName[30];
			Stars();
			printf("\t\t\t5. Поиск сотрудника по фамилии.\n");
			Line();
			printf("Введите фамилию сотрудника: ");
			scanf("%s", lastName);
			Line();

			if ((fp = fopen(path, "r")) != NULL)
			{
				EMPLOYEE * eLastName;
				eLastName = (EMPLOYEE*)calloc(1, sizeof(EMPLOYEE));
				int i = 0;

				while (fread((eLastName + i), sizeof(EMPLOYEE), 1, fp))
				{
					//PrintInfo((eLastName + i));
					i++;
					eLastName = (EMPLOYEE*)realloc(eLastName, sizeof(EMPLOYEE)*(i + 1));
				}

				EMPLOYEE * f = eLastName;
				int ind;
				for (int s = 0; s < i; s++)
				{
					if (strcmp((eLastName + s)->lName, lastName) == 0)
					{
						PrintInfoEmpoyee((eLastName + s), 1);
					}

				}

			}

			fclose(fp);

		}break;

		/* 6. Поиск сотрудников по возрасту.*/
		case 6:
		{
			clear();
			int eAge;
			Stars();
			printf("\t\t\t6. Поиск сотрудников по возрасту.\n");
			Line();
			printf("Введите возраст сотрудника: ");
			scanf("%d", &eAge);
			Line();

			if ((fp = fopen(path, "r")) != NULL)
			{
				EMPLOYEE * eLastName;
				eLastName = (EMPLOYEE*)calloc(1, sizeof(EMPLOYEE));
				int i = 0;

				while (fread((eLastName + i), sizeof(EMPLOYEE), 1, fp))
				{
					//PrintInfo((eLastName + i));
					i++;
					eLastName = (EMPLOYEE*)realloc(eLastName, sizeof(EMPLOYEE)*(i + 1));
				}

				EMPLOYEE * f = eLastName;
				int ind;
				for (int s = 0; s < i; s++)
				{
					if ((eLastName + s)->btd.age == eAge)
					{
						PrintInfoEmpoyee((eLastName + s), 1);
					}

				}

			}

			fclose(fp);
		}break;

		/*7. Поиск сотрудников по начальной букве.*/
		case 7:
		{
			clear();
			char eLetter[1];

			Stars();
			printf("\t\t\t7. Поиск сотрудников по начальной букве.\n");
			Line();
			printf("Введите начальную букву сотрудника: ");
			scanf("%s", eLetter);
			Line();

			if ((fp = fopen(path, "r")) != NULL)
			{
				EMPLOYEE * eLastName;
				eLastName = (EMPLOYEE*)calloc(1, sizeof(EMPLOYEE));
				int i = 0;

				while (fread((eLastName + i), sizeof(EMPLOYEE), 1, fp))
				{
					//PrintInfo((eLastName + i));
					i++;
					eLastName = (EMPLOYEE*)realloc(eLastName, sizeof(EMPLOYEE)*(i + 1));
				}

				for (int s = 0; s < i; s++)
				{
					if (eLastName[s].lName[0] == eLetter[0])
					{
						PrintInfoEmpoyee((eLastName + s), 1);

					}

				}

			}

			fclose(fp);
		}break;

		/* 8. Список пользователей входивших в систему.*/
		case 8:
		{
			Stars();
			printf("\t\t\t8. Список пользователей входивших в систему.\n");
			Line();

			if ((fp = fopen(path2, "r")) != NULL)
			{
				LOGIN *logins = (LOGIN*)calloc(1, sizeof(LOGIN));

				while (fread(logins, sizeof(LOGIN), 1, fp))
				{

					printf("-------------------------------\n");
					printf("Фамилия: %s\n", logins->lNameLog);
					printf("Имя: %s\n", logins->fNameLog);
					printf("Отчество: %s\n", logins->mNameLog);
					printf("Должность: %s\n", logins->pstnLog);
					printf("Пароль: %d\n", logins->passwordLog);

					printf("Время: %s\n", logins->timeLogIn);
					printf("-------------------------------\n");
				}

			}
			fclose(fp);
		}break;

		/*9. Отчет о военнообязанных с указанием срока службы в днях.*/
		case 9:
		{
			clear();
			Stars();
			printf("\t\t\t9. Отчет о военнообязанных с указанием срока службы в днях.\n");
			Stars();
			Line();

			if ((fp = fopen(path, "r")) != NULL)
			{
				EMPLOYEE * eLastName;
				eLastName = (EMPLOYEE*)calloc(1, sizeof(EMPLOYEE));
				int i = 0;

				while (fread((eLastName + i), sizeof(EMPLOYEE), 1, fp))
				{
					//PrintInfo((eLastName + i));
					i++;
					eLastName = (EMPLOYEE*)realloc(eLastName, sizeof(EMPLOYEE)*(i + 1));
				}

				EMPLOYEE * f = eLastName;
				int day3;
				int month3;
				int year3;
				for (int s = 0; s < i; s++)
				{
					if ((eLastName + s)->eRankId != 0)
					{
						PrintInfoEmpoyee((eLastName + s), 1);
					}
				}
			}
			fclose(fp);

		}break;

		/*10. Отчеты по военнообязанным по заданному периоду.*/
		case 10:
		{
			clear();
			Stars();

			int day1, day2, month1, month2, year1, year2;

			printf("Введите начальную дату (дд.мм.гггг): ");
			scanf("%d.%d.%d", &day1, &month1, &year1);

			printf("Введите конечную дату (дд.мм.гггг): ");
			scanf("%d.%d.%d", &day2, &month2, &year2);

			Line();

			if ((fp = fopen(path, "r")) != NULL)
			{
				EMPLOYEE * eRank;
				eRank = (EMPLOYEE*)calloc(1, sizeof(EMPLOYEE));
				int i = 0;

				while (fread((eRank + i), sizeof(EMPLOYEE), 1, fp))
				{
					i++;
					eRank = (EMPLOYEE*)realloc(eRank, sizeof(EMPLOYEE)*(i + 1));
				}

				for (int s = 0; s < i; s++)
				{
					if ((eRank + s)->eRankId != 0 &&
						(eRank + s)->eRank.call.year >= year1 && (eRank + s)->eRank.retire.year <= year2)// &&
																										 //(eRank + s)->eRank.call.month >= month1 && (eRank + s)->eRank.retire.month <= month2 &&
																										 //(eRank + s)->eRank.call.day >= day1 && (eRank + s)->eRank.retire.day <= day2)

						PrintInfoEmpoyee((eRank + s), 1);

				}

			}

			fclose(fp);

		}break;
		}
	} while (p != 0);
}

/* меню пользователя */
void userMenu()
{
	int p;
	do
	{
		Line();
		printf("1. Вывод информации о сотрудниках.\n");
		printf("2. Поиск сотрудника по фамилии.\n");
		printf("3. Отчет о возрасте каждого сотрудника и количестве отработанных дней.\n");
		printf("4. Отчет о сотрудниках предпенсионного возраста со стажем более 30 лет .\n");
		Line();

		printf("Выберите пункт меню: ");
		scanf("%d", &p);

		switch (p)
		{
			/* 1. Инормация о сотрудниках. */
		case 1:
		{
			clear();
			Line();
			printf("\t\t\t1.Инормация о сотрудниках.\n");
			Line();

			if ((fp = fopen(path, "r")) != NULL)
			{
				while (fread(&employees, sizeof(EMPLOYEE), 1, fp))
				{
					PrintInfoEmpoyee2(&employees);
				}
			}

			fclose(fp);

		}break;

		/* 2. Поиск сотрудника по фамилии. */
		case 2:
		{
			clear();
			char lastName[30];
			Stars();
			printf("\t\t\t2. Поиск сотрудника по фамилии.\n");
			Line();
			printf("Введите фамилию сотрудника: ");
			scanf("%s", lastName);
			Line();

			if ((fp = fopen(path, "r")) != NULL)
			{
				EMPLOYEE * eLastName;
				eLastName = (EMPLOYEE*)calloc(1, sizeof(EMPLOYEE));

				int i = 0;

				while (fread((eLastName + i), sizeof(EMPLOYEE), 1, fp))
				{
					i++;
					eLastName = (EMPLOYEE*)realloc(eLastName, sizeof(EMPLOYEE)*(i + 1));
				}

				for (int s = 0; s < i; s++)
				{
					if (strcmp((eLastName + s)->lName, lastName) == 0)
					{
						PrintInfoEmpoyee((eLastName + s), 1);
					}

				}

			}

			fclose(fp);

		}break;

		/* 3. Отчет о возрасте каждого сотрудника и количестве отработанных дней. */
		case 3:
		{
			clear();
			Line();
			printf("\t\t\t3. Отчет о возрасте каждого сотрудника и количестве отработанных дней.\n");
			Line();

			if ((fp = fopen(path, "r")) != NULL)
			{
				while (fread(&employees, sizeof(EMPLOYEE), 1, fp))
				{
					PrintInfoEmpoyee3(&employees);
				}
			}

			fclose(fp);

		}break;

		/* 4. Отчет о сотрудниках предпенсионного возраста со стажем более 30 лет. */
		case 4:
		{
			/* Организовать просмотр информации о сотрудниках пенсионного возраста
			(мужчины – до 60 лет, женщины – до 55 лет), проработавших на предприятии более 30 лет.*/
			clear();
			Stars();

			int day1, day2, month1, month2, year1, year2;

			printf("\t\t\t4. Отчет о сотрудниках предпенсионного возраста со стажем более 30 лет.\n");


			Line();

			if ((fp = fopen(path, "r")) != NULL)
			{
				EMPLOYEE * eRank;
				eRank = (EMPLOYEE*)calloc(1, sizeof(EMPLOYEE));
				int i = 0;

				while (fread((eRank + i), sizeof(EMPLOYEE), 1, fp))
				{
					i++;
					eRank = (EMPLOYEE*)realloc(eRank, sizeof(EMPLOYEE)*(i + 1));
				}

				for (int s = 0; s < i; s++)
				{
					if ((((eRank + s)->sex == 0 && (eRank + s)->btd.age <= 55) ||
						((eRank + s)->sex == 1 && (eRank + s)->btd.age <= 60)) &&
						(eRank + s)->pos.yearOfWork>30)

						PrintInfoEmpoyee((eRank + s), 1);

				}

			}

			fclose(fp);

		}break;

		}
	} while (p != 0);
}

void Stars()
{
	printf("************************************************************************\n");
}

void clear()
{
	system("cls");
}



