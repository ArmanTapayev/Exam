#include "01.Employee.h"

void GenerateDate(DATE *date);
void GenerateDate(BIRTHDATE *bdate);
void GenerateDate(CURRANTDATE *cdate);
void CreateName(char *name, int len);
void GeneratePosition(POSITION *position, BIRTHDATE *bdt, ARMY *eRank, int id);
//void GenerateEntryDate(DATE *entryDate);
void GenerateEntryDate(DATE *entryDate, BIRTHDATE *bdate, ARMY *eArmy, int id);
void GenerateArmyEntryDate(DATE *armyEntryDate, BIRTHDATE *bdate);
void GenerateRank(ARMY *eRank, int id, BIRTHDATE *bdt);
int diffDay(DATE date1, DATE date2);
int diffDay(CURRANTDATE date1, DATE date2);
void PrintInfoEmpoyee3(EMPLOYEE * employees);
long long generateIIN(BIRTHDATE*date);
int generatePassword();
void PrintInfoEmpoyee(EMPLOYEE * employees, int len);
EMPLOYEE *CreateEmployee(int *count);
void Line();
void Stars();
void clear();
void PrintInfoEmpoyee2(EMPLOYEE * employees);

int authorization(char *lastName, int password);
void adminMenu();
void userMenu();
//int Time();
//void PrintInfo(EMPLOYEE * employees);
//void PrintInfo2(EMPLOYEE *employees);
//void Line();
//void Stars();
//void clear();

