#include<stdlib.h>
#include<windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
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
	string classes;
	Students* pNext;
};
void createframe();
void gotoxy(int x, int y);
void displayUI();
void LoadFileStudents(Students*& stu, string filename);
void LoadFileStaff(Students*& sta, string filename);
void export_file(Students* stu, string filename);
void Release_memory(Students*& stu);
void display_information_students(Students* stu);
//void display_information_staffs(Students* stu);
void Change_Password(Students* stu, Students*& stu_cur, string New_Password, string filename);
void View_profile(Students* stu, Students* stu_cur);
bool CheckUser(Students* stu, Students*& stu_cur, string ID, string pass);
void Login(Students* stu, Students* sta, Students*& stu_cur);
Students* Find_User_By_ID(Students* stu, string ID);
void Option_After_Login(Students*& stu, Students*& sta, Students*& stu_cur, string filename);
void Menu();