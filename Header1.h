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
    Session* ses = new Session[2];
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

Class* Find(Class* classhead, string classname);
void add_one_by_one(Class*& classhead);
void display(Class* classhead);
void add_by_file_csv(Class*& classhead);
void create_class(Class*& classhead);
void Menu_Feature_First_Staff(Students * stu);
void Export_new(Class* classhead, Students* stu);
void create_new_year(Year*& yearh);
void CreateSem(Year*& yearh, Year*& year_cur);
void CreateCourse(Year*& yearh, Year*& year_cur, Course*& courseh, int num_sem);
void CreateSes(Year* yearh, Course*& course_cur, int num_sem);
//void PrintSem(Year* yearh, Year*& year_cur);
void Menu_Op();
