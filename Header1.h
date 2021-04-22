#include"Header.h"
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
    int num_stu; // So luong hoc sinh da dang ki
    Session* ses = new Session[2];
    Course* Next;
};

struct Semester {
    string sem_name;
    int dateStart;
    int dateEnd;
    Course* courseh;
    int regStart;
    int regEnd;
};

struct Year {
    string year_name;
    Semester* sem = new Semester[3];
    int dateStart, dateEnd;
    Year* Next;
};

Class* Find(Class* classhead, string classname);
void add_one_by_one(Class*& classhead);
void display(Class* classhead);
void add_by_file_csv(Class*& classhead);
void create_class(Class*& classhead);
void Menu_Feature_First_Staff(Students * stu);
void Export_new(Class* classhead, Students* stu);
void create_new_year(Year*& yearh, Year*& year_cur);
void CreateSem(Year*& year_cur, int& n);
void CreateCourse(Course*& courseh, int num_sem, int n);
void CreateSes(Course*& course_cur, int num_sem);
void View_List_Course(Year* year_cur, int n);
//void PrintSem(Year* yearh, Year*& year_cur);
void Menu_Op();
