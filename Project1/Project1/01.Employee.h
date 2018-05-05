struct BIRTHDATE
{
	int day;
	int month;
	int year;
	int age;
};

struct DATE
{
	int day;
	int month;
	int year;
};

struct CURRANTDATE
{
	int day;
	int month;
	int year;
};

struct LOGIN
{

	char lNameLog[10];
	char fNameLog[10];
	char mNameLog[10];
	int passwordLog;
	char timeLogIn[30];
	char timeLogOut[30];
	char pstnLog[30];
	//char passwordLog[5];

};

struct ARMY // ДЛЯ ВОЕННООБЯЗАННЫХ
{
	char rank[30]; //ЗВАНИЕ
	DATE call; //ДАТА ПРИЗЫВА
	DATE retire; //ДАТА УВОЛЬНЕНИЯ В ЗАПАС
	char dispos[10]; //ВОИНСКАЯ ЧАСТЬ
	int dayOfService;
};

struct POSITION
{
	char pstn[30];  //ДОЛЖНОСТЬ
	char sal[10];        // ОКЛАД
	DATE entryDate; //ДАТА ПОСТУПЛЕНИЯ НА РАБОТУ
	CURRANTDATE cdate;
	int dayOfWork;
	int yearOfWork;
};

struct EMPLOYEE
{
	int tblNmb; //ТАБЕЛЬНЫЙ НОМЕР
	char lName[10];
	char fName[10];
	char mName[10]; //ФИО СОТРУДНИКА
	long long iin;
	BIRTHDATE btd;

	int sex; // ПОЛ: 1 - МУЖ, 0 - ЖЕН

	POSITION pos; //ДОЛЖНОСТЬ
	int eRankId; // ДЛЯ ВОЕННООБЯЗАННЫХ: да или нет
	ARMY eRank; // ДЛЯ ВОЕННООБЯЗАННЫХ
	int eRole; // РОЛЬ: АДМИН - 1, ПОЛЬЗОВАТЕЛЬ - 0
	long password;
	//char timeLogin[30];
};
