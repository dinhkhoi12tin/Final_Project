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
    Year* year_cur = nullptr;
    int n;
    create_new_year(yearh, year_cur);
    CreateSem(year_cur, n);
    View_List_Course(year_cur, n);
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

void create_new_year(Year*& yearh, Year*& year_cur) {
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
    year_cur = Find_Year(yearh, newyear);
}

void CreateSem(Year*& year_cur, int& n)
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
    cout << "Input the registration start day of the course: " << endl;
    cin >> year_cur->sem[num_sem - 1].regStart;
    cout << "Input the registration end day of the course: " << endl;
    cin >> year_cur->sem[num_sem - 1].regEnd;
    //Create Course
    year_cur->sem[num_sem - 1].courseh = nullptr;
    cout << "Input the number of courses you want to create: ";
    cin >> n;
    CreateCourse(year_cur->sem[num_sem - 1].courseh, num_sem, n);
}

void CreateCourse(Course*& courseh, int num_sem, int n)
{
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
        CreateSes(coursecur, num_sem);
        coursecur->Next = nullptr;
    }
}

void CreateSes(Course*& course_cur, int num_sem)
{
    for(int i = 0; i < 2; i++)
    {
        cout << "Input the course's day in week: " << endl;
        cin >> course_cur->ses[i].date;
        cout << "Input the session: " << endl;
        cout << "S1. 7:30" << endl;
        cout << "S2  9:30" << endl;
        cout << "S3. 13:30" << endl;
        cout << "S4. 15:30" << endl;
        do
        {
            cin >> course_cur->ses[i].timeofSes;
        } while (course_cur->ses[i].timeofSes != "S1" && course_cur->ses[i].timeofSes != "S2" && course_cur->ses[i].timeofSes != "S3" && course_cur->ses[i].timeofSes != "S4");
    }   
}

void View_List_Course(Year* year_cur, int n)
{
    int choice;
    cout << "1 2 3";
    cin >> choice;
    Course* coursecur = year_cur->sem[choice - 1].courseh;
    for (int i = 0; i < n; i++)
    {
        cout << i << ". " << coursecur->course_name;
        coursecur = coursecur->Next;
        cout << endl;
    }
    int choice2;
    cout << "Input the course you want to view: ";
    cin >> choice2;
    coursecur = year_cur->sem[choice - 1].courseh;
    for (int i = 0; i < choice2; i++)
    {
        coursecur = coursecur->Next;
    }
    cout << "Course ID: "  << coursecur->course_id << endl;
    cout << "Course Name: " << coursecur->course_name << endl;
    cout << "Course Credit: " << coursecur->cre_num << endl;
    cout << "Course's teacher's name: " << coursecur->teacher_name << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << coursecur->ses[i].date << " ";
        cout << coursecur->ses[i].timeofSes;
        cout << endl;
    }
}

/*void Delete_Course(Course*& courseh, int num_sem)
{
    string tempID;
    cout << "Input the ID of course: " << endl;
    cin >> tempID;
    Course* coursecur = courseh;
    if (courseh->course_id == tempID)
    {
        courseh = courseh->Next;
        delete coursecur;
    }
    while (coursecur->Next != nullptr )
    {
        if (coursecur->Next->course_id == tempID)
        {
            Course* pDel = coursecur->Next;
            coursecur->Next = coursecur->Next->Next;
            delete pDel;
            break;
        }
        else coursecur = coursecur->Next;
    }
}
*/
