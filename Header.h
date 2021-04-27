#include<stdlib.h>
#include<windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<conio.h>
using namespace std;
struct Session {
    string date;
    string timeofSes;
};
struct Students1
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
};
struct Course {
    string course_id, course_name, teacher_name, cre_num;
    int maxnum_stu = 50;
    int num_stu = 0; // So luong hoc sinh da dang ki
    Session* ses = new Session[2];
    Students1* Stu = new Students1[51];
    Course* Next;
    string startdate, enddate;
};
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
    Course* Cour = new Course[7];
};
struct Class {
    string class_name = "";
    Students* sthead = 0;
    Class* Next = 0;
};
struct Semester {
    string sem_name;
    string dateStart;
    string dateEnd;
    Course* courseh;
    string regStart;
    string regEnd;
};

struct Year {
    string year_name;
    Semester* sem = new Semester[3];
    string dateStart;
    string dateEnd;
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

void InputMaskedPassword(string& password);
Students* Find_User_By_ID(Students* stu, string ID);
void Option_After_Login(Students*& stu, Students*& sta, Students*& stu_cur, string filename, Year*& yearh);
void Menu();

void Enroll_Course(Students*& stu_cur, Year*& yearh);
void View_Course(Students* stu_cur);
void Remove_Course(Students*& stu_cur, Year*& yearh);
Class* Find(Class* classhead, string classname);
void add_one_by_one(Class*& classhead);
void display(Class* classhead);
void add_by_file_csv(Class*& classhead);
void create_class(Class*& classhead);

void Menu_Feature_First_Staff(Students* stu, Year*& yearh);

void Export_new(Class* classhead, Students* stu);

void create_new_year(Year*& yearh, Year*& year_cur);

void CreateSem(Year*& year_cur, int& n, int& num_sem);
void CreateCourse(Course*& courseh, int num_sem, int n);

void CreateSes(Course*& course_cur, int num_sem);

void Menu_Op(Year*& yearh);


void View_List_Course(Year* year_cur, int n);
void Delete_Course(Year*& year_cur, int& n, int num_sem);
void Update_Course(Year*& year_cur, int num_sem);
void Convert_Date(string s);
void View_List_Of_Classes(Class* classhead);
void View_Classes_Students(Students* sthead);
void View_List_Of_Students_Course(Year* year_cur, int num_sem);