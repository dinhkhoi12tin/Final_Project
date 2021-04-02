#include<stdlib.h>
#include<windows.h>
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

void createframe(); // Truong Gia Huy function
void gotoxy(int x, int y);
void displayUI();
void LoadFileStudents(Students*& stu);