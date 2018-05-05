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

struct ARMY // дкъ бнеммннаъгюммшу
{
	char rank[30]; //гбюмхе
	DATE call; //дюрю опхгшбю
	DATE retire; //дюрю сбнкэмемхъ б гюоюя
	char dispos[10]; //бнхмяйюъ вюярэ
	int dayOfService;
};

struct POSITION
{
	char pstn[30];  //днкфмнярэ
	char sal[10];        // нйкюд
	DATE entryDate; //дюрю онярсокемхъ мю пюанрс
	CURRANTDATE cdate;
	int dayOfWork;
	int yearOfWork;
};

struct EMPLOYEE
{
	int tblNmb; //рюаекэмши мнлеп
	char lName[10];
	char fName[10];
	char mName[10]; //тхн янрпсдмхйю
	long long iin;
	BIRTHDATE btd;

	int sex; // онк: 1 - лсф, 0 - фем

	POSITION pos; //днкфмнярэ
	int eRankId; // дкъ бнеммннаъгюммшу: ДЮ ХКХ МЕР
	ARMY eRank; // дкъ бнеммннаъгюммшу
	int eRole; // пнкэ: юдлхм - 1, онкэгнбюрекэ - 0
	long password;
	//char timeLogin[30];
};
