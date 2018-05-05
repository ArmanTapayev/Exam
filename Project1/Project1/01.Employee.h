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

struct ARMY // ��� ���������������
{
	char rank[30]; //������
	DATE call; //���� �������
	DATE retire; //���� ���������� � �����
	char dispos[10]; //�������� �����
	int dayOfService;
};

struct POSITION
{
	char pstn[30];  //���������
	char sal[10];        // �����
	DATE entryDate; //���� ����������� �� ������
	CURRANTDATE cdate;
	int dayOfWork;
	int yearOfWork;
};

struct EMPLOYEE
{
	int tblNmb; //��������� �����
	char lName[10];
	char fName[10];
	char mName[10]; //��� ����������
	long long iin;
	BIRTHDATE btd;

	int sex; // ���: 1 - ���, 0 - ���

	POSITION pos; //���������
	int eRankId; // ��� ���������������: �� ��� ���
	ARMY eRank; // ��� ���������������
	int eRole; // ����: ����� - 1, ������������ - 0
	long password;
	//char timeLogin[30];
};
