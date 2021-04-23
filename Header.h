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
    int num_Cour = 0;
	Course *Cour=new Course[6];
};
struct Class {
    string class_name = "";
    Students* sthead = 0;
    Class* Next = 0;
};

struct Session {
    string date;
    string timeofSes;
};

struct Course {
    string course_id, course_name, teacher_name, cre_num;
    int maxnum_stu = 50;
    int num_stu=0; // So luong hoc sinh da dang ki
    Session* ses = new Session[2];
    Students* Stu = new Students[51];
    Course* Next;
    int startdate, enddate;
};

struct Semester {
    string sem_name;
    int dateStart;
    int dateEnd;
    Course* courseh;
};

struct Year {
    string year_name;
    Semester* sem = new Semester[3];
    int dateStart, dateEnd;
    Year* Next;
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
void Login(Students* stu, Students* sta, Students*& stu_cur, Year*& yearh);
Students* Find_User_By_ID(Students* stu, string ID);
void Option_After_Login(Students*& stu, Students*& sta, Students*& stu_cur, string filename, Year*& yearh);
void Menu();



void Enroll_Course(Students*& stu_cur, Year*& yearh);
Class* Find(Class* classhead, string classname);
void add_one_by_one(Class*& classhead);
void display(Class* classhead);
void add_by_file_csv(Class*& classhead);
void create_class(Class*& classhead);
void Menu_Feature_First_Staff(Students* stu);
void Export_new(Class* classhead, Students* stu);
void create_new_year(Year*& yearh);
void CreateSem(Year*& yearh, Year*& year_cur);
void CreateCourse(Year*& yearh, Year*& year_cur, Course*& courseh, int num_sem);
void CreateSes(Year* yearh, Course*& course_cur, int num_sem);
//void PrintSem(Year* yearh, Year*& year_cur);
void Menu_Op();
