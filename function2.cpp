#include"Header.h"
Year* Find_Year(Year* yearh, string name_year)
{
    while (yearh != nullptr) {
        if (yearh->year_name == name_year) return yearh;
        yearh = yearh->Next;
    }
    return nullptr;
}

Course* Find_Course(Year* yearh, string id_course, int num_sem)
{
    Course* Cur = yearh->sem[num_sem - 1].courseh;
    while (Cur)
    {
        if (Cur->course_id == id_course) return Cur;
        Cur = Cur->Next;
    }
    return nullptr;
}

void create_new_year(Year*& yearh, Year*& year_cur, int& n) {
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
void Remove_All_Course(Students*& stu, int num_sem) {
    Students* stu_cur = stu;
    while (stu_cur != nullptr) // run until no students left
    {
        for (int i = stu_cur->num_Cour; i >= 0; i--)
            stu_cur->Cour[i] = stu_cur->Cour[i + 1];
        stu_cur->num_Cour = 0;
        stu_cur = stu_cur->pNext;
    }
}
void CreateSem(Year*& year_cur, int& n, int& num_sem, Students*& stu)
{
    int offset = 30;
    createframe();
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    gotoxy(8 + offset, 3);
    Remove_All_Course(stu, num_sem);
    cout << "Input the Semester(1/2/3): ";
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
    gotoxy(8 + offset, 4);  cin >> year_cur->sem[num_sem - 1].regStart;
    gotoxy(8 + offset, 5);
    cout << "Input the registration end day of the course: ";
    gotoxy(8 + offset, 6); cin >> year_cur->sem[num_sem - 1].regEnd;
    //Create Course
    year_cur->sem[num_sem - 1].courseh = nullptr;
    gotoxy(8 + offset, 7);
    /*cout << "Input the number of courses you want to create: ";
    cin >> n;*/
    //CreateCourse(year_cur->sem[num_sem - 1].courseh, num_sem, n);
    ifstream input;
    CreateCourseByFile(year_cur->sem[num_sem - 1].courseh, num_sem, n, input);
}

void CreateCourseByFile(Course*& courseh, int num_sem, int& n, ifstream& input)
{
    n = 0;
    int offset = 30;
    string filename;
    gotoxy(8 + offset, 7);
    cout << "Input name of file you want to add: " << endl;
    gotoxy(8 + offset, 8);
    cin >> filename;
    //filename = "Semester-1.csv"
    input.open(filename);
    if (!input.is_open())
    {
        gotoxy(8 + offset, 9);
        cout << "Cannot open file " << endl;
    }
    else
    {
        Course* coursecur = nullptr;
        while (input.good())
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
            getline(input, coursecur->course_name, ',');
            getline(input, coursecur->course_id, ',');
            getline(input, coursecur->teacher_name, ',');
            getline(input, coursecur->cre_num, ',');
            for (int i = 0; i < 2; i++)
            {
                getline(input, coursecur->ses[i].date, ',');
                if (i == 0) getline(input, coursecur->ses[0].timeofSes, ',');
                if (i == 1) getline(input, coursecur->ses[1].timeofSes, '\n');
            }
            n++;
            coursecur->Next = nullptr;
        }
    }
    input.close();
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
        cout << "Input the No. " << i + 1 << " course's day: ";
        gotoxy(8 + offset, 4); cout << "Mon       /       Tue";
        gotoxy(8 + offset, 5); cout << "Wed       /       Thu";
        gotoxy(8 + offset, 6); cout << "Fri       /       Sat";
        do
        {
            gotoxy(69, 3); cout << "         ";
            gotoxy(69, 3);
            cin >> course_cur->ses[i].date;
        } while (course_cur->ses[i].date != "Mon" && course_cur->ses[i].date != "Tue" && course_cur->ses[i].date != "Wed" && course_cur->ses[i].date != "Thu" && course_cur->ses[i].date != "Sat" && course_cur->ses[i].date != "Fri");
        createframe();
        SetConsoleTextAttribute(hConsole, 121);
        gotoxy(8 + offset, 3);
        cout << "Input the No. " << i + 1 << " session: ";
        gotoxy(8 + offset, 4);
        cout << "S1. 7:30";
        gotoxy(8 + offset, 5);
        cout << "S2  9:30";
        gotoxy(8 + offset, 6);
        cout << "S3. 13:30";
        gotoxy(8 + offset, 7);
        cout << "S4. 15:30";
        do
        {
            gotoxy(57, 4); cout << "         ";
            gotoxy(57, 4);
            cin >> course_cur->ses[i].timeofSes;
        } while (course_cur->ses[i].timeofSes != "S1" && course_cur->ses[i].timeofSes != "S2" && course_cur->ses[i].timeofSes != "S3" && course_cur->ses[i].timeofSes != "S4");
    }
}

void View_List_Course(Year* year_cur, int n, int& choice2, string& ID)
{
    while (1)
    {
        int offset = 30;
        createframe();
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 121);
        int choice;
        gotoxy(8 + offset, 3);
        cout << "Input the semester you want to view";
        cout << " (1/2/3): "; // choose semester
        cin >> choice;
        if (year_cur->sem[choice - 1].courseh == nullptr) {
            createframe();
            gotoxy(8 + offset, 3);
            cout << "Semester does not exist";
            string wait;
            SetConsoleTextAttribute(hConsole, 6);
            gotoxy(0 + offset, 11); cout << " >> Press any to stop.  "; gotoxy(24 + offset, 11); cout << "                               ";
            gotoxy(25 + offset, 11);  cin >> wait;
        }
        else
        {
            Course* coursecur = year_cur->sem[choice - 1].courseh;
            createframe();
            HANDLE  hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 121);

            gotoxy(8 + offset, 8);
            for (int i = 1; i < n; i++)
            {
                if (coursecur != nullptr)
                {
                    gotoxy(38, i + 2);
                    cout << i << ". " << coursecur->course_name;
                    coursecur = coursecur->Next;
                }
            }
            gotoxy(8 + offset, n + 2); cout << "0. Exit";
            coursecur = year_cur->sem[choice - 1].courseh;
            //while (coursecur != nullptr) {}
            gotoxy(38, 9);
            cout << "Input the course you want to view: "; // can add danh sach

            cin >> choice2;
            coursecur = year_cur->sem[choice - 1].courseh;
            if (choice2 == 0) break;
            for (int i = 0; i < choice2 - 1; i++)
            {
                coursecur = coursecur->Next;
            }
            ID = coursecur->course_id;
            createframe();
            SetConsoleTextAttribute(hConsole, 121);
            gotoxy(8 + offset, 1);
            cout << "Course ID: " << coursecur->course_id << endl;
            gotoxy(8 + offset, 2);
            cout << "Course Name: " << coursecur->course_name << endl;
            gotoxy(8 + offset, 3);
            cout << "Course Credit: " << coursecur->cre_num << endl;
            gotoxy(8 + offset, 4);
            cout << "Course's teacher's name: " << coursecur->teacher_name << endl;
            gotoxy(8 + offset, 5);
            cout << "Course's Session: ";
            for (int i = 0; i < 2; i++)
            {
                gotoxy(58, i + 5);
                cout << coursecur->ses[i].date << "  -";
                gotoxy(65, i + 5);
                cout << coursecur->ses[i].timeofSes;
                cout << endl;
            }
            break;
        }
    }
}
void Delete_Course(Year*& year_cur, int& n, int num_sem, string ID)
{
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    Course* coursecur = year_cur->sem[num_sem - 1].courseh;
    if (year_cur->sem[num_sem - 1].courseh->course_id == ID)
    {
        year_cur->sem[num_sem - 1].courseh = year_cur->sem[num_sem - 1].courseh->Next;
        delete coursecur;
        n--;
    }
    else
    {
        while (coursecur->Next != nullptr)
        {
            if (coursecur->Next->course_id == ID) //crashing
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
    createframe();
    gotoxy(8 + offset, 4);
    cout << "Delete complete." << endl;
}
void Update_Course(Year*& year_cur, int num_sem, string ID)
{
    int offset = 30;
    string tempID;
    tempID = ID;
    Course* coursecur = Find_Course(year_cur, tempID, num_sem);
    int choice;
    createframe();
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    gotoxy(8 + offset, 3);
    cout << "1. Change the name of the course " << endl;
    gotoxy(8 + offset, 4);
    cout << "2. Change the ID of the course " << endl;
    gotoxy(8 + offset, 5);
    cout << "3. Change the name of the teacher of the course " << endl;
    gotoxy(8 + offset, 6);
    cout << "4. Change the number of credits of the course " << endl;
    gotoxy(8 + offset, 7);
    cout << "5. Change the sessions of the course " << endl;
    gotoxy(8 + offset, 3);
    SetConsoleTextAttribute(hConsole, 6);
    gotoxy(0 + offset, 11); cout << " >> Please, select your functions: "; gotoxy(35 + offset, 11); cout << "                    ";
    gotoxy(36 + offset, 11);  cin >> choice;
    createframe();
    SetConsoleTextAttribute(hConsole, 121);
    gotoxy(8 + offset, 3);
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

        for (int i = 0; i < 2; i++)
        {
            cout << "Input No. " << i + 1 << " Session: ";
            cout << "Input course's new date: ";
            cin >> coursecur->ses[i].date;
            gotoxy(8 + offset, 5);
            cout << "Input new session: ";
            cin >> coursecur->ses[i].timeofSes;
        }
    }

}
bool check(Students* stu_cur, Course* Cour) {
    if (Cour->num_stu == 50 || stu_cur->num_Cour == 5) return 0;
    for (int i = 1; i <= stu_cur->num_Cour; ++i) {
        if (stu_cur->Cour[i].ses[1].date == Cour->ses[1].date
            && stu_cur->Cour[i].ses[1].timeofSes == Cour->ses[1].timeofSes) return 0;

        if (stu_cur->Cour[i].ses[0].date == Cour->ses[0].date
            && stu_cur->Cour[i].ses[0].timeofSes == Cour->ses[0].timeofSes) return 0;
    }
    return 1;
}
void Enroll_Course(Students*& stu_cur, Year*& yearh, int num_sem) {
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    string ID;
    gotoxy(8 + offset, 3);
    cout << "Input Id course: ";
    cin >> ID;
    Course* Cour = Find_Course(yearh, ID, num_sem);
    if (check(stu_cur, Cour)) {
        Cour->Stu[++Cour->num_stu] =
        { stu_cur->No,stu_cur->ID,stu_cur->NameFirst,stu_cur->NameLast,stu_cur->Gender,
            stu_cur->Birth,stu_cur->socialID,stu_cur->username,stu_cur->password,stu_cur->classes };
        stu_cur->Cour[++stu_cur->num_Cour] = *Cour;
    }
    else {
        gotoxy(8 + offset, 4); cout << "Unable to register\n";
    }
}
void View_Course(Students* stu_cur) {
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    for (int i = 1; i <= stu_cur->num_Cour; ++i) {

        gotoxy(20 + offset, i + 2); cout << stu_cur->Cour[i].course_name << " ";
    }
}
void Remove_Course(Students*& stu_cur, Year*& yearh, int num_sem) {
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    string ID;
    gotoxy(8 + offset, 3);
    cout << "type ID course to remove: ";
    cin >> ID;
    for (int i = 1; i <= stu_cur->num_Cour; ++i)
        if (stu_cur->Cour[i].course_id == ID) {
            for (int j = i; j < stu_cur->num_Cour; ++j)
                stu_cur->Cour[j] = stu_cur->Cour[j + 1];
            break;
        }
    stu_cur->num_Cour--;
    Course* Cou = Find_Course(yearh, ID, num_sem);
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
    int offset = 30;
    Class* classcur = classhead;
    int yformat = 0;
    while (classcur != nullptr)
    {
        yformat++;
        classcur = classcur->Next;
    }
    createframe();
    if (yformat >= 10)
    {
        extendframe(yformat);
    }
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    int i = 2;
    while (classhead != nullptr)
    {
        i++;
        gotoxy(8 + offset, i);
        cout << classhead->class_name;
        classhead = classhead->Next;
    }
    //int wait;
    //SetConsoleTextAttribute(hConsole, 6);
    //gotoxy(0 + offset, 11); cout << " >> Press any to continue.  "; gotoxy(24 + offset, 11); cout << "                               ";
    //gotoxy(25 + offset, 11);  cin >> wait;
}
void View_Classes_Students(Students* sthead)
{
    int offset = 30;
    createframe();
    int class_size = 0;
    Students* sttemp = sthead;
    while (sttemp != nullptr)
    {
        class_size++;
        sttemp = sttemp->pNext;
    }
    int pressY = 11;
    if (class_size >= 8)
    {
        pressY = class_size + 3;
        extendframe(class_size + 1);
    }
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    int i = 1;
    while (sthead != nullptr)
    {
        i++;
        gotoxy(8 + offset, i);
        cout << i - 1 << ". " << sthead->ID << " - " << sthead->NameFirst << " " << sthead->NameLast << " - " << sthead->Gender << endl;
        sthead = sthead->pNext;
    }
    string wait;
    SetConsoleTextAttribute(hConsole, 6);
    gotoxy(0 + offset, pressY); cout << " >> Press any to return.  "; gotoxy(24 + offset, pressY); cout << "                               ";
    gotoxy(25 + offset, pressY);  cin >> wait;
    system("CLS");
}
void View_List_Of_Students_Course(Year* year_cur, int num_sem, string ID)
{
    string tempID = ID;
    Course* course_cur = Find_Course(year_cur, tempID, num_sem);
    int n = course_cur->num_stu;
    int offset = 30;
    createframe();
    int pressY = 11;
    if (n >= 7) {
        pressY = (n + 5);
        extendframe(n + 1);
    }
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    for (int i = 1; i <= n; i++)
    {
        gotoxy(8 + offset, i+3);
        cout << i << ". " << course_cur->Stu[i].ID << " - " << course_cur->Stu[i].NameFirst << " " << course_cur->Stu[i].NameLast << " - " << course_cur->Stu[i].Gender;
    }
    string wait;
    SetConsoleTextAttribute(hConsole, 6);
    gotoxy(0 + offset, pressY); cout << " >> Press any to return.  "; gotoxy(24 + offset, pressY); cout << "                               ";
    gotoxy(25 + offset, pressY);  cin >> wait;
    system("CLS");
}
void GetCurrentDate(int& Year, int& Month, int& Day) {
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    Year = 1900 + newtime.tm_year;
    Month = 1 + newtime.tm_mon;
    Day = newtime.tm_mday;

}
void Convert_Date(string s, int& dd, int& mm, int& yyyy)
{
    dd = ((int)s[0] - 48) * 10 + ((int)s[1] - 48);
    mm = ((int)s[3] - 48) * 10 + ((int)s[4] - 48);
    yyyy = ((int)s[6] - 48) * 1000 + ((int)s[7] - 48) * 100 + ((int)s[8] - 48) * 10 + ((int)s[9] - 48);
}
bool CheckRegistrationDate(Year* year_cur, int num_sem)
{
    int CheckY, CheckM, CheckD;
    GetCurrentDate(CheckY, CheckM, CheckD);
    int dd1, mm1, yyyy1, dd2, mm2, yyyy2;
    Convert_Date(year_cur->sem[num_sem - 1].regStart, dd1, mm1, yyyy1);
    Convert_Date(year_cur->sem[num_sem - 1].regEnd, dd2, mm2, yyyy2);
    int CD = (CheckY * 10000) + (CheckM * 100) + CheckD;
    int SD = (yyyy1 * 10000) + (mm1 * 100) + dd1;
    int ED = (yyyy2 * 10000) + (mm2 * 100) + dd2;
    if (CD >= SD && CD <= ED) {
        return 1;
    }
    else {
        return 0;
    }
}
void Export_List_Stu_In_Course(Year* year_cur, int num_sem)
{
    int offset = 30;
    string filename;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    string tempID;
    gotoxy(8 + offset, 3);
    cout << "Input the ID of the course: ";
    cin >> tempID;
    cout << "Input the name of the file you want to export list of students in course: ";
    cin >> filename;
    ofstream output;
    //filename = Stu_in_course.csv
    output.open(filename);
    Course* course_cur = Find_Course(year_cur, tempID, num_sem);
    int n = course_cur->num_stu;
    for (int i = 1; i <= n; i++)
    {
        gotoxy(58, 3);
        output << course_cur->Stu[i].ID << "," << course_cur->Stu[i].Fullname << "," << course_cur->Stu[i].Gender;
        output << endl;
    }
}

void Import_Scoreboard(Year*& year_cur, int num_sem)
{
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    ifstream input;
    string tempID;
    string filename;
    gotoxy(8 + offset, 3);
    cout << "Input name of file you want to add: " << endl;
    gotoxy(8 + offset, 4);
    cin >> filename;
    //filename = "Scoreboard.csv"
    input.open(filename);
    createframe();
    SetConsoleTextAttribute(hConsole, 121);
    gotoxy(8 + offset, 3);
    cout << "Input the course you want to add scoreboard: " << endl;
    gotoxy(8 + offset, 4);
    cin >> tempID;
    Course* course_cur = Find_Course(year_cur, tempID, num_sem);
    if (!input.is_open())
    {
        cout << "Cannot open file " << endl;
    }
    else
    {
        string s;
        getline(input, s);
        int i = 1;
        while (input.good())
        {
            getline(input, course_cur->Stu[i].No, ',');
            getline(input, course_cur->Stu[i].ID, ',');
            getline(input, course_cur->Stu[i].NameFirst, ',');
            getline(input, course_cur->Stu[i].NameLast, ',');
            char trash;
            input >> course_cur->Stu[i].score.Midterm >> trash >> course_cur->Stu[i].score.Other >> trash >> course_cur->Stu[i].score.Final >> trash >> course_cur->Stu[i].score.Total;
            getline(input, s);
            i++;
        }
    }
    input.close();
}
void View_Scoreboard_Course(Year* year_cur, int num_sem)
{
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    string tempID;
    int count;
    gotoxy(8 + offset, 3);
    cout << "Input the course you want to add scoreboard: " << endl;
    gotoxy(46 + offset, 3);
    cin >> tempID;
    Course* course_cur = Find_Course(year_cur, tempID, num_sem);
    count = course_cur->num_stu;
    for (int i = 1; i <= count; i++)
    {
        gotoxy(8 + offset, 3);
        cout << course_cur->Stu[i].No << " " << course_cur->Stu[i].ID << " " << course_cur->Stu[i].Fullname << " " << course_cur->Stu[i].score.Midterm << " " << course_cur->Stu[i].score.Other << " " << course_cur->Stu[i].score.Final << " " << course_cur->Stu[i].score.Total;
        cout << endl;
    }
}
void Edit_Score(Year*& year_cur, int num_sem)
{
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    string tempID, tempIDStu;
    gotoxy(8 + offset, 3);
    cout << "Input the course you want to add scoreboard: " << endl;
    gotoxy(46 + offset, 3);
    cin >> tempID;
    Course* course_cur = Find_Course(year_cur, tempID, num_sem);
    int count = course_cur->num_stu;
    gotoxy(8 + offset, 4);
    cout << "Input the ID of student you want to edit: " << endl;
    gotoxy(43 + offset, 4);
    cin >> tempIDStu;
    int temp;
    for (int i = 1; i <= count; i++)
    {
        if (course_cur->Stu[i].ID == tempIDStu)
        {
            temp = i;
            break;
        }
    }
    int option;
    createframe();
    gotoxy(8 + offset, 3);
    cout << "Input the score you want to edit: ";
    gotoxy(8 + offset, 4);
    cout << "1. Midterm Score" << endl;
    gotoxy(8 + offset, 5);
    cout << "2. Other Score" << endl;
    gotoxy(8 + offset, 6);
    cout << "3. Final Score" << endl;
    gotoxy(8 + offset, 7);
    cout << "4. Total" << endl;
    gotoxy(36 + offset, 3);
    cin >> option;
    if (option == 1)
    {
        cout << "Input Midterm Score" << endl;
        cin >> course_cur->Stu[temp].score.Midterm;
    }
    if (option == 2)
    {
        cout << "Input Other Score" << endl;
        cin >> course_cur->Stu[temp].score.Other;
    }
    if (option == 3)
    {
        cout << "Input Final Score" << endl;
        cin >> course_cur->Stu[temp].score.Final;
    }
    if (option == 4)
    {
        cout << "Input Total Score" << endl;
        cin >> course_cur->Stu[temp].score.Total;
    }
    Export_Edit_Score(year_cur, num_sem, tempID, course_cur, count);
}
void Export_Edit_Score(Year*& year_cur, int num_sem, string tempID, Course* course_cur, int count)
{
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    ofstream output;
    output.open("Scoreboard.csv");
    //No, ID, FirstName, LastName, Midterm, Other, Final, Total
    gotoxy(8 + offset, 3);
    output << "No, ID, FirsName, LastName, Midterm, Other, Final, Total" << endl;
    for (int i = 1; i <= count; i++)
    {
        gotoxy(8 + offset, 4);
        output << course_cur->Stu[i].No << "," << course_cur->Stu[i].ID << "," << course_cur->Stu[i].NameFirst << "," << course_cur->Stu[i].NameLast << "," << course_cur->Stu[i].score.Midterm << "," << course_cur->Stu[i].score.Other << "," << course_cur->Stu[i].score.Final << "," << course_cur->Stu[i].score.Total;
        output << endl;
    }
}

float GPA(int score) {
    if (score >= 9) return 4;
    if (score >= 8) return 3.5;
    if (score >= 7) return 3;
    if (score >= 6) return 2.5;
    if (score >= 5) return 2;
    if (score >= 4) return 1.5;
    if (score >= 3) return 1;
    if (score >= 2) return 0.5;
    return 0;
}
float* Overal_Count_GPA(Students1* stu, int num_stu, int& t) {
    float* ans = new float[1000];
    int  num = 0;
    float s = 0;
    for (int i = 1; i <= num_stu; ++i) {
        if (i == 1 || stu[i].Fullname == stu[i - 1].Fullname) {
            s += GPA(stu[i].score.Total);
            num++;
        }
        else {
            ans[++t] = (float)s / num;
            num = 1;
            s = GPA(stu[i].score.Total);
        }
    }
    ans[++t] = (float)s / num;
    return ans;
}
void Get_all_students(Year* yearh, string classname, Students1*& stu, int num_sem, int& num_stu) {
    Course* Co = yearh->sem[num_sem - 1].courseh;
    while (Co) {
        // cout << Co->course_name << " " << Co->num_stu << endl;
        for (int i = 1; i <= Co->num_stu; ++i)
            if (Co->Stu[i].classes == classname) {
                stu[++num_stu] = Co->Stu[i];
                stu[num_stu].course_name = Co->course_name;
            }
        Co = Co->Next;
    }
}
void sort(Students1*& stu, int num_stu) {
    for (int i = 1; i < num_stu; ++i)
        for (int j = i + 1; j <= num_stu; ++j)
            if (stu[i].ID > stu[j].ID) swap(stu[i], stu[j]);
}


float* Total_Gpa(Year* yearh, string classname, int Sem) {
    float* ans = new float[1000];
    for (int i = 0; i < 1000; ++i)
        ans[i] = 0;
    int n = 0;
    for (int num_sem = 1; num_sem <= Sem; ++num_sem) {
        Students1* stu = new Students1[1000];
        int num_stu = 0;
        Get_all_students(yearh, classname, stu, num_sem, num_stu);
        sort(stu, num_stu);
        int t = 0;
        float* Total_Gpa = Overal_Count_GPA(stu, num_stu, t);
        if (n != 0) n = t;
        for (int i = 1; i <= t; ++i)
            ans[i] += Total_Gpa[i];
    }
    for (int i = 1; i <= n; ++i)
        ans[i] = (float)ans[i] / Sem;
    return ans;
}
void View_Score_Class(Year* yearh, int num_sem) {
    int offset = 30;
    createframe();

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    string classname;
    gotoxy(8 + offset, 3);
    cout << "Input The Classname:"; cin >> classname;
    Students1* stu = new Students1[1000];
    int num_stu = 0;
    Get_all_students(yearh, classname, stu, num_sem, num_stu);
    sort(stu, num_stu);
    int t = 0;
    float* Overal_GPA = Overal_Count_GPA(stu, num_stu, t);
    float* Total_GPA = Total_Gpa(yearh, classname, num_sem);
    int k = 0;
    int yformat = 0;
    int increment = 0;
    for (int i = 1; i <= num_stu; ++i) {
        yformat += increment;
        if (i == 1 || stu[i].Fullname != stu[i - 1].Fullname) {
            increment = yformat;
        }
        else {
            increment++;
        }
    }
    if (yformat >= 10)
    {
        createframe();
        extendframe(yformat);
        SetConsoleTextAttribute(hConsole, 121);
    }
    yformat = 0;
    increment = 0;
    for (int i = 1; i <= num_stu; ++i) {
        yformat += increment;
        if (i == 1 || stu[i].Fullname != stu[i - 1].Fullname) {
            gotoxy(7 + offset, yformat + 2);
            cout << stu[i].Fullname << " - Semester Gpa: " << Overal_GPA[++k] << " - Overall GPA: " << Total_GPA[k];
            increment = yformat;
        }
        else {
            gotoxy(14 + offset, increment + 3);
            cout << stu[i].course_name << " - Final Score: " << stu[i].score.Final;
            increment++;
        }
    }
    if (yformat < 10)
    {
        yformat = 10;
    }
    string wait;
    SetConsoleTextAttribute(hConsole, 6);
    gotoxy(0 + offset, (yformat) + 1); cout << " >> Press any to stop.  "; gotoxy(24 + offset, (yformat) + 1); cout << "                               ";
    gotoxy(25 + offset, (yformat) + 1);  cin >> wait;
    system("CLS");
}
void View_Stu_Score(Year* year_cur, int num_sem, Students* stu_cur)
{

    int offset = 30;
    createframe();

    int count = stu_cur->num_Cour;
    extendframe((count + 2) * 5);
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    float OverallGPA = 0;
    int yformat = 0;
    stu_cur->score.GPASem[num_sem - 1] = 0;
    for (int i = 1; i <= count; i++)
    {
        int count_temp = stu_cur->Cour[i].num_stu;
        for (int j = 1; j <= count_temp; j++)
        {
            if (stu_cur->ID == stu_cur->Cour[i].Stu[j].ID)
            {

                gotoxy(8 + offset, yformat + 2);
                cout << "Midterm Score of " << stu_cur->Cour[i].course_name << ": " << stu_cur->Cour[i].Stu[j].score.Midterm << endl;
                gotoxy(8 + offset, yformat + 3);
                cout << "Other Score of " << stu_cur->Cour[i].course_name << ": " << stu_cur->Cour[i].Stu[j].score.Other << endl;
                gotoxy(8 + offset, yformat + 4);
                cout << "Final Score of " << stu_cur->Cour[i].course_name << ": " << stu_cur->Cour[i].Stu[j].score.Final << endl;
                gotoxy(8 + offset, yformat + 5);
                cout << "Total Score of " << stu_cur->Cour[i].course_name << ": " << stu_cur->Cour[i].Stu[j].score.Total << endl;
                stu_cur->Cour[i].Stu[j].score.GPA = GPA(stu_cur->Cour[i].Stu[j].score.Total);
                stu_cur->score.GPASem[num_sem - 1] += stu_cur->Cour[i].Stu[j].score.GPA;

                gotoxy(8 + offset, yformat + 6);
                cout << "GPA of " << stu_cur->Cour[i].course_name << ": " << stu_cur->Cour[i].Stu[j].score.GPA;
                yformat += 6;
                break;
            }
        }
    }
    stu_cur->score.GPASem[num_sem - 1] /= count;
    gotoxy(8 + offset, ((count + 1) * 5));
    cout << "Semester GPA: " << setprecision(1) << stu_cur->score.GPASem[num_sem - 1];
    for (int k = 0; k < num_sem; k++)
    {
        OverallGPA += stu_cur->score.GPASem[k];
    }
    gotoxy(8 + offset, ((count + 1) * 5 + 2));
    cout << "Overall GPA: " << setprecision(1) << OverallGPA << endl;
    string wait;
    SetConsoleTextAttribute(hConsole, 6);
    gotoxy(0 + offset, (count + 2) * 5 + 1); cout << " >> Press any to stop.  "; gotoxy(24 + offset, (count + 2) * 5 + 1); cout << "                               ";
    gotoxy(25 + offset, (count + 2) * 5 + 1);  cin >> wait;
    system("CLS");
}

void Release_memory(Students*& stu, Students*& sta, Year*& yearh, Year*& year_cur, Class*& classhead)
{
    while (stu != nullptr)
    {
        Students* ptemp_stu = stu;
        delete[]ptemp_stu->Cour;
        stu = stu->pNext;
        delete ptemp_stu;
    }
    while (sta != nullptr)
    {
        Students* ptemp_sta = sta;
        sta = sta->pNext;
        delete ptemp_sta;
    }
    for (int i = 0; i < 3; i++)
    {
        while (year_cur->sem[i].courseh != nullptr)
        {
            delete[] year_cur->sem[i].courseh->Stu;
            year_cur->sem[i].courseh = year_cur->sem[i].courseh->Next;
        }
        while (year_cur->sem[i].courseh != nullptr)
        {
            delete[] year_cur->sem[i].courseh->ses;
            year_cur->sem[i].courseh = year_cur->sem[i].courseh->Next;
        }
        while (year_cur->sem[i].courseh != nullptr)
        {
            Course* ptemp_course = year_cur->sem[i].courseh;
            year_cur->sem[i].courseh = year_cur->sem[i].courseh->Next;
            delete ptemp_course;
        }
    }
    while (yearh != nullptr)
    {
        year_cur = yearh;
        delete[]year_cur->sem;
        yearh = yearh->Next;
        delete year_cur;
    }
    while (classhead != nullptr)
    {
        Class* ptemp_class = classhead;
        classhead = classhead->Next;
        delete ptemp_class;
    }
}