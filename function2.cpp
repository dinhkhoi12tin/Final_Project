#include"Header1.h"
Year* Find_Year(Year* yearh, string name_year)
{
    while (yearh != nullptr) {
        if (yearh->year_name == name_year) return yearh;
        yearh = yearh->Next;
    }
    return nullptr;
}

Course* Find_Course(Year*& year_cur, Course* courseh, string id_course, int num_sem)
{
    while (year_cur->sem[num_sem - 1].courseh != nullptr)
    {
        if (year_cur->sem[num_sem - 1].courseh->course_id == id_course) return year_cur->sem[num_sem - 1].courseh;
        year_cur->sem[num_sem - 1].courseh = year_cur->sem[num_sem - 1].courseh->Next;
    }
    return nullptr;
}

void Menu_Op()
{
    Year* yearh = nullptr;
    create_new_year(yearh);
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
    // Create Semester
    Year* year_cur = Find_Year(yearh, newyear);
    CreateSem(yearh, year_cur);
}

void CreateSem(Year*& yearh, Year*& year_cur)
{
    int num_sem;
    cout << "Input the sem you want to create: " << endl;
    cin >> num_sem;
    if (num_sem == 1) year_cur->sem[num_sem - 1].sem_name = "Semester 1";
    if (num_sem == 2) year_cur->sem[num_sem - 1].sem_name = "Semester 2";
    if (num_sem == 3) year_cur->sem[num_sem - 1].sem_name = "Semester 3";
    cout << "Input the start of semester " << num_sem << ":";
    cin >> year_cur->sem[num_sem - 1].dateStart;
    cout << "Input the end of semester " << num_sem << ":";
    cin >> year_cur->sem[num_sem - 1].dateEnd;
    //Create Course
    year_cur->sem[num_sem - 1].courseh = nullptr;
    CreateCourse(yearh, year_cur, year_cur->sem[num_sem - 1].courseh, num_sem);
}

void CreateCourse(Year*& yearh, Year*& year_cur, Course*& courseh, int num_sem)
{
    int n;
    cout << "Input the number of courses you want to create: ";
    cin >> n;
    Course* coursecur = nullptr;
    for (int i = 0; i < n; i++)
    {
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
        coursecur->maxnum_stu = 50;
        cout << "Input name of the course: " << endl;
        cin.ignore();
        getline(cin, coursecur->course_name);
        cout << "Input ID of the course: " << endl;
        cin >> coursecur->course_id;
        cout << "Input name of teacher of the course: " << endl;
        cin.ignore();
        getline(cin, coursecur->teacher_name);
        cout << "Input the number of credits of the course: " << endl;
        cin >> coursecur->cre_num;
        cout << "Input the registration start day of the course: " << endl;
        cin >> coursecur->startdate;
        cout << "Input the registration end day of the course: " << endl;
        cin >> coursecur->enddate;
        CreateSes(yearh, coursecur, num_sem);
    }
    /*Create Session
    string course_id;
    for (int i = 0; i < n; i++)
    {
        cout << "Input course ID you want to create sessions: " << endl;
        cin >> course_id;
        Course* course_cur = Find_Course(year_cur, courseh, course_id, num_sem);
        CreateSes(yearh, course_cur, num_sem);
    }*/
}

void CreateSes(Year* yearh, Course*& course_cur, int num_sem)
{
    for(int i = 0; i < 2; i++)
    {
        cout << "Input the course's day in week: " << endl;
        cin >> course_cur->ses[i].date;
        cout << "Input the session: " << endl;
        cout << "S1. 7:30" << endl;
        cout << "S2. 9:30" << endl;
        cout << "S3. 13:30" << endl;
        cout << "S4. 15:30" << endl;
        do
        {
            cin >> course_cur->ses[i].timeofSes;
        } while (course_cur->ses[i].timeofSes != "S1" && course_cur->ses[i].timeofSes != "S2" && course_cur->ses[i].timeofSes != "S3" && course_cur->ses[i].timeofSes != "S4");
    }   
}

