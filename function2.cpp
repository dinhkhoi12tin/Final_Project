#include"Header1.h"
Year* Find_Year(Year* yearh, string name_year)
{
    while (yearh != nullptr) {
        if (yearh->year_name == name_year) return yearh;
        yearh = yearh->Next;
    }
    return nullptr;
}

Course* Find_Course(Year*& year_cur, Course* courseh, string name_course, int num_sem)
{
    while (year_cur->sem[num_sem - 1].courseh != nullptr)
    {
        if (year_cur->sem[num_sem - 1].courseh->course_name == name_course) return year_cur->sem[num_sem - 1].courseh;
        year_cur->sem[num_sem - 1].courseh = year_cur->sem[num_sem - 1].courseh->Next;
    }
    return nullptr;
}
void Menu_Op()
{
    Year* yearh = nullptr;
    Year* year_cur = nullptr;
    Course* courseh = nullptr; 
    create_new_year(yearh);
    CreateSem(yearh, year_cur);
    //PrintSem(yearh, year_cur);
}


/*void PrintSem(Year* yearh, Year*& year_cur)
{
    int num_sem;
    string name_year;
    cout << "Input name of year: " << endl;
    cin >> name_year;
    year_cur = Find_Year(yearh, name_year);
    cout << "The sem you want to check: " << endl;
    cin >> num_sem;
    cout << "Semester " << num_sem << "in year" << year_cur->year_name << endl;
    cout << "The start of semester " << num_sem << ":" << year_cur->sem[num_sem - 1].dateStart << endl;
    cout << "The end of semester " << num_sem << ":" << year_cur->sem[num_sem - 1].dateEnd << endl;
}
*/

void create_new_year(Year*& yearh) {
    string newyear;
    Year* yearcur = nullptr;
    int offset = 30;
    createframe();
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    gotoxy(20 + offset, 3);
    cout << "Type name of new year:";
    cin >> newyear;
    Year* yearcur = new Year;
    yearcur->year_name = newyear;
    yearcur->Next = yearh;
    yearh = yearcur;
}

void CreateSem(Year*& yearh, Year*& year_cur)
{
    int num_sem;
    string name_year;
    cout << "Input name of year: " << endl;
    cin >> name_year;
    year_cur = Find_Year(yearh, name_year);
    cout << "Input the sem you want to create: " << endl;
    cin >> num_sem;
    if (num_sem == 1) year_cur->sem[num_sem - 1].sem_name = "Semester 1";
    if (num_sem == 2) year_cur->sem[num_sem - 1].sem_name = "Semester 2";
    if (num_sem == 3) year_cur->sem[num_sem - 1].sem_name = "Semester 3";
    cout << "Input the start of semester " << num_sem << ":";
    cin >> year_cur->sem[num_sem - 1].dateStart;
    cout << "Input the end of semester " << num_sem << ":";
    cin >> year_cur->sem[num_sem - 1].dateEnd;
}

void CreateCourse(Year*& yearh, Year*& year_cur, Course*& courseh)
{
    int num_sem;
    string name_year;
    cout << "Input name of year: " << endl;
    cin >> name_year;
    year_cur = Find_Year(yearh, name_year);
    cout << "Input the sem you want to choose: " << endl;
    cin >> num_sem;
    Course* coursecur;
    if (courseh == nullptr)
    {
        courseh = new Course;
        coursecur = courseh;
    }
    else
    {
        coursecur->Next = new Course;
        coursecur = coursecur->Next;
    }
    year_cur->sem[num_sem - 1].courseh->maxnum_stu = 50;
    cout << "Input name of the course: " << endl;
    cin >> year_cur->sem[num_sem - 1].courseh->course_name;
    cout << "Input ID of the course: " << endl;
    cin >> year_cur->sem[num_sem - 1].courseh->course_id;
    cout << "Input name of teacher of the course: " << endl;
    cin >> year_cur->sem[num_sem - 1].courseh->teacher_name;
    cout << "Input the number of credits of the course: " << endl;
    cin >> year_cur->sem[num_sem - 1].courseh->cre_num;
    cout << "Input the day of the course: " << endl;
    cin >> year_cur->sem[num_sem - 1].courseh->dateofWeek;
    cout << "Input the registration start day of the course: " << endl;
    cin >> year_cur->sem[num_sem - 1].courseh->startdate;
    cout << "Input the registration end day of the course: " << endl;
    cin >> year_cur->sem[num_sem - 1].courseh->enddate;
}

void CreateSes(Year* yearh, Year* year_cur, Course*& courseh, Course* course_cur, int num_sem)
{
    for(int i = 0; i < 2; i++)
    {
        cout << "Input the course's day: " << endl;
        cin >> year_cur->sem[num_sem - 1].courseh->ses[i].date;
        cout << "Input the session: " << endl;
        cout << "S1. 7:30" << endl;
        cout << "S2. 9:30" << endl;
        cout << "S3. 13:30" << endl;
        cout << "S4. 15:30" << endl;
        do
        {
            cin >> year_cur->sem[num_sem - 1].courseh->ses[i].timeofSes;
        } while (year_cur->sem[num_sem - 1].courseh->ses[i].timeofSes != "S1" && year_cur->sem[num_sem - 1].courseh->ses[i].timeofSes != "S2" && year_cur->sem[num_sem - 1].courseh->ses[i].timeofSes != "S3" && year_cur->sem[num_sem - 1].courseh->ses[i].timeofSes != "S4");
    }   
}

