#include"Header.h"
Year* Find_Year(Year* yearh, string name_year)
{
    while (yearh != nullptr) {
        if (yearh->year_name == name_year) return yearh;
        yearh = yearh->Next;
    }
    return nullptr;
}

Course* Find_Course(Year* yearh, string id_course)
{
    while (yearh)
    {
        for (int num_sem = 0; num_sem < 3; ++num_sem) {
            if (yearh->sem[num_sem].courseh->course_id == id_course)
                return yearh->sem[num_sem].courseh;
        }
        yearh = yearh->Next;
    }
    return nullptr;
}

void Menu_Op(Year*& yearh)
{
    Year* year_cur = nullptr;
    int num_sem = 0;
    int n;
    create_new_year(yearh, year_cur);
    CreateSem(year_cur, n, num_sem);
    //Delete_Course(year_cur, n, num_sem);
    Update_Course(year_cur, num_sem);
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
    gotoxy(8 + offset, 3);
    cout << "Type name of new year: ";
    cin >> newyear;
    Year* yearcur = new Year;
    yearcur->year_name = newyear;
    yearcur->Next = yearh;
    yearh = yearcur;
    year_cur = Find_Year(yearh, newyear);
}

void CreateSem(Year*& year_cur, int& n, int& num_sem)
{
    int offset = 30;
    createframe();
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    gotoxy(8 + offset, 3);
    cout << "Input the sem you want to create: ";
    cin >> num_sem;
    if (num_sem == 1) year_cur->sem[num_sem - 1].sem_name = "Semester 1";
    if (num_sem == 2) year_cur->sem[num_sem - 1].sem_name = "Semester 2";
    if (num_sem == 3) year_cur->sem[num_sem - 1].sem_name = "Semester 3";
    gotoxy(8 + offset, 4);
    cout << "Input the start of semester " << num_sem << ": ";
    cin >> year_cur->sem[num_sem - 1].dateStart;
    gotoxy(8 + offset, 5);
    cout << "Input the end of semester " << num_sem << ": ";
    cin >> year_cur->sem[num_sem - 1].dateEnd;
    createframe();
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    gotoxy(8 + offset, 3);
    cout << "Input the registration start day of the course: ";
    cin >> year_cur->sem[num_sem - 1].regStart;
    gotoxy(8 + offset, 4);
    cout << "Input the registration end day of the course: ";
    cin >> year_cur->sem[num_sem - 1].regEnd;
    //Create Course
    year_cur->sem[num_sem - 1].courseh = nullptr;
    gotoxy(8 + offset, 5);
    cout << "Input the number of courses you want to create: ";
    cin >> n;
    CreateCourse(year_cur->sem[num_sem - 1].courseh, num_sem, n);
}

void CreateCourse(Course*& courseh, int num_sem, int n)
{
    Course* coursecur = nullptr;
    int offset = 30;
    createframe();
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
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
        gotoxy(8 + offset, 3);
        cout << "Input name of the course: ";
        cin.ignore();
        getline(cin, coursecur->course_name);
        gotoxy(8 + offset, 4);
        cout << "Input ID of the course: ";
        cin >> coursecur->course_id;
        gotoxy(8 + offset, 5);
        cout << "Input name of teacher of the course: ";
        cin.ignore();
        getline(cin, coursecur->teacher_name);
        gotoxy(8 + offset, 6);
        cout << "Input the number of credits of the course: ";
        cin >> coursecur->cre_num;
        CreateSes(coursecur, num_sem);
        coursecur->Next = nullptr;
    }
}

void CreateSes(Course*& course_cur, int num_sem)
{
    int offset = 30;
    for (int i = 0; i < 2; i++)
    {
        createframe();
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 121);
        gotoxy(8 + offset, 3);
        cout << "Input the course's day in week: ";
        cin >> course_cur->ses[i].date;
        gotoxy(8 + offset, 4);
        cout << "Input the session: ";
        gotoxy(8 + offset, 5);
        cout << "S1. 7:30";
        gotoxy(8 + offset, 6);
        cout << "S2  9:30";
        gotoxy(8 + offset, 7);
        cout << "S3. 13:30";
        gotoxy(8 + offset, 8);
        cout << "S4. 15:30";
        do
        {
            gotoxy(57, 4); cout << "         ";
            gotoxy(57, 4);
            cin >> course_cur->ses[i].timeofSes;
        } while (course_cur->ses[i].timeofSes != "S1" && course_cur->ses[i].timeofSes != "S2" && course_cur->ses[i].timeofSes != "S3" && course_cur->ses[i].timeofSes != "S4");
    }
}

void View_List_Course(Year* year_cur, int n)
{
    int choice;
    cout << "1 2 3"; // choose semester
    cin >> choice;
    if (year_cur->sem[choice - 1].courseh == nullptr) cout << "Nothing";
    else
    {
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
        cout << "Course ID: " << coursecur->course_id << endl;
        cout << "Course Name: " << coursecur->course_name << endl;
        cout << "Course Credit: " << coursecur->cre_num << endl;
        cout << "Course's teacher's name: " << coursecur->teacher_name << endl;
        cout << "Course Session: ";
        for (int i = 0; i < 2; i++)
        {
            cout << coursecur->ses[i].date << " ";
            cout << coursecur->ses[i].timeofSes;
            cout << endl;
        }
    }
}

void Delete_Course(Year*& year_cur, int& n, int num_sem)
{
    string tempID;
    cout << "Input the ID of course you want to delete: " << endl;
    cin >> tempID;
    Course* coursecur = year_cur->sem[num_sem - 1].courseh;
    if (year_cur->sem[num_sem - 1].courseh->course_id == tempID)
    {
        year_cur->sem[num_sem - 1].courseh = year_cur->sem[num_sem - 1].courseh->Next;
        delete coursecur;
        n--;
    }
    while (coursecur->Next != nullptr)
    {
        if (coursecur->Next->course_id == tempID)
        {
            Course* pDel = coursecur->Next;
            coursecur->Next = coursecur->Next->Next;
            delete pDel;
            n--;
            break;
        }
        else coursecur = coursecur->Next;
    }
}

void Update_Course(Year*& year_cur, int num_sem)
{
    string tempID;
    cout << "Input the ID of course you want to change: " << endl;
    cin >> tempID;
    Course* coursecur = Find_Course(year_cur, tempID);
    int choice;
    cout << "1. Change the name of the course: " << endl;
    cout << "2. Change the ID of the course: " << endl;
    cout << "3. Change the name of the teacher of the course: " << endl;
    cout << "4. Change the number of credits of the course: " << endl;
    cout << "5. Change the sessions of the course: " << endl;
    cin >> choice;
    if (choice == 1)
    {
        cout << "Input new name of the course: ";
        cin.ignore();
        getline(cin, coursecur->course_name);
    }
    if (choice == 2)
    {
        cout << "Input new ID of the course: ";
        cin.ignore();
        getline(cin, coursecur->course_id);
    }
    if (choice == 3)
    {
        cout << "Input new name of the teacher of the course: ";
        cin.ignore();
        getline(cin, coursecur->teacher_name);
    }
    if (choice == 4)
    {
        cout << "Input new number of credits of the course: ";
        cin >> coursecur->cre_num;
    }
    if (choice == 5)
    {
        cout << "Input new sessions of the course: ";
        for (int i = 0; i < 2; i++)
        {
            cout << "Input new day of course: " << endl;
            cin >> coursecur->ses[i].date;
            cout << "Input new session: " << endl;
            cin >> coursecur->ses[i].timeofSes;
        }
    }

}

void Convert_Date(string s)
{
    int dd, mm, yyyy;
    dd = ((int)s[0] - 48) * 10 + ((int)s[1] - 48);
    cout << dd;
    mm = ((int)s[3] - 48) * 10 + ((int)s[4] - 48);
    cout << mm;
    yyyy = ((int)s[6] - 48) * 1000 + ((int)s[7] - 48) * 100 + ((int)s[8] - 48) * 10 + ((int)s[9] - 48);
    cout << yyyy;
}

bool check(Students* stu_cur, Course* Cour) {
    if (Cour->num_stu == 50 || stu_cur->num_Cour == 5) return 0;
    while (stu_cur->Cour) {
        for (int i = 1; i <= stu_cur->num_Cour; ++i) {
            if (stu_cur->Cour[i].ses[1].date == Cour->ses[1].date
                && stu_cur->Cour[i].ses[1].timeofSes == Cour->ses[1].timeofSes) return 0;

            if (stu_cur->Cour[i].ses[0].date == Cour->ses[0].date
                && stu_cur->Cour[i].ses[0].timeofSes == Cour->ses[0].timeofSes) return 0;
        }
        stu_cur->Cour = stu_cur->Cour->Next;
    }
    return 1;
}

void Enroll_Course(Students*& stu_cur, Year*& yearh) {
    string ID;
    cout << "type Id course: "; cin >> ID;
    Course* Cour = Find_Course(yearh, ID);
    if (check(stu_cur, Cour)) {
        Cour->Stu[++Cour->num_stu] =
        { stu_cur->No,stu_cur->ID,stu_cur->NameFirst,stu_cur->NameLast,stu_cur->Gender,
            stu_cur->Birth,stu_cur->socialID,stu_cur->username,stu_cur->password,stu_cur->classes };
        stu_cur->Cour[++stu_cur->num_Cour] = *Cour;
    }
    else {
        cout << "khong the dang ki\n";
    }
}

void View_Course(Students* stu_cur) {
    for (int i = 1; i <= stu_cur->num_Cour; ++i) {
        cout << stu_cur->Cour[i].course_name << " ";
    }
}

void Remove_Course(Students*& stu_cur, Year*& yearh) {
    string ID;
    cout << "type ID course to remove: "; cin >> ID;
    for (int i = 1; i <= stu_cur->num_Cour; ++i)
        if (stu_cur->Cour[i].course_id == ID) {
            for (int j = i; j < stu_cur->num_Cour; ++j)
                stu_cur->Cour[j] = stu_cur->Cour[j + 1];
            break;
        }
    stu_cur->num_Cour--;
    Course* Cou = Find_Course(yearh, ID);
    for (int i = 1; i <= Cou->num_stu; ++i) {
        if (Cou->Stu[i].ID == stu_cur->ID) {
            for (int j = i; j < Cou->num_stu; ++j)
                Cou->Stu[j] = Cou->Stu[j + 1];
            break;
        }
    }
    Cou->num_stu--;
}

void View_List_Of_Classes(Class* classhead)
{
    if (classhead != nullptr)
    {
        View_List_Of_Classes(classhead->Next);
        cout << classhead->class_name << endl;
    }
}

void View_Classes_Students(Students* sthead)
{
    if (sthead != nullptr)
    {
        View_Classes_Students(sthead->pNext);
        cout << sthead->ID << " " << sthead->NameFirst << " " << sthead->NameLast << " " << sthead->Gender <<endl;
    }
}

void View_List_Of_Students_Course(Year * year_cur, int num_sem)
{
    string tempID;
    cout << "Input the ID of the course: ";
    cin >> tempID;
    Course* course_cur = Find_Course(year_cur, tempID);
    int n = course_cur->num_stu;
    for (int i = 0; i < n; i++)
    {
        cout << i << ". " << course_cur->Stu[i].ID << " " << course_cur->Stu[i].NameFirst << " " << course_cur->Stu[i].NameLast << " " << course_cur->Stu[i].Gender;
        cout << endl;
    }
}   