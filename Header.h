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

void createframe(); // Truong Gia Huy function
void gotoxy(int x, int y);
void displayUI();
void LoadFileStudents(Students*& stu, string filename);
void export_file(Students * stu,string filename);
void Release_memory(Students *& stu);
void display_information_students(Students* stu);
<<<<<<< Updated upstream
void Change_Password(Students* stu, string ID, string New_Password, string filename);
void View_profile(Students* stu, Students* stu_cur);
=======
<<<<<<< HEAD
bool CheckUser(Students*& stu, string user, string pass);
void Login(Students*& stu);
=======
void Change_Password(Students* stu, string ID, string New_Password, string filename);
void View_profile(Students* stu, Students* stu_cur);
>>>>>>> 7047496c390092f7c13b93e1ad6edc911ceba7ff
>>>>>>> Stashed changes
