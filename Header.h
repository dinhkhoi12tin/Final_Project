#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct Students
{
	string No;
	string ID;
	string NameFirst, NameLast;
	string Gender;
	string Birth;
	string socialID;
	string username;
	string password;
	Students* pNext;
};

void LoadFileStudents(Students*& stu);