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
    while (yearh)
    {
        if (yearh->sem[num_sem - 1].courseh->course_id == id_course) return yearh->sem[num_sem- 1].courseh;
        yearh->sem[num_sem - 1].courseh = yearh->sem[num_sem -1].courseh->Next;
    }
    return nullptr;
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

void create_new_year(Year*& yearh, Year*& year_cur,int &n) {
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

/*void CreateCourse(Course*& courseh, int num_sem, int n)
{
    Course* coursecur = nullptr;
    int offset = 30;
    for (int i = 0; i < n; i++)
    {
        createframe();
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 121);
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
        cout << "Input the No. " << i + 1 << " course's name: ";
        cin.ignore();
        getline(cin, coursecur->course_name);               
        gotoxy(8 + offset, 4);
        cout << "Input the No. " << i + 1 << " course's ID: ";
        cin >> coursecur->course_id;
        gotoxy(8 + offset, 5);
        cout << "Input the No. " << i + 1 << " course's teacher's name: ";
        cin.ignore();
        getline(cin, coursecur->teacher_name);
        gotoxy(8 + offset, 6);
        cout << "Input the No. " << i + 1 << " course's credits: ";
        cin >> coursecur->cre_num;
        CreateSes(coursecur, num_sem);
        coursecur->Next = nullptr;
    }
}*/                                                                                                                                                                         

void CreateCourseByFile(Course*& courseh, int num_sem, int& n, ifstream& input)
{
    input.open("Semester-1.csv");
    if (!input.is_open())
    {
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

void View_List_Course(Year* year_cur, int n)
{
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    int choice;
    gotoxy(8 + offset, 3);
    cout << "Input the semester you want to view";
    cout << " (1 2 3): "; // choose semester
    cin >> choice;
    if (year_cur->sem[choice - 1].courseh == nullptr) {
        createframe();
        gotoxy(8 + offset, 3);
        cout << "Semester does not exist";
    }
    else
    {
        Course* coursecur = year_cur->sem[choice - 1].courseh;
        createframe();
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 121);
        for (int i = 0; i < n; i++)
        {
            gotoxy(38, i + 3);
            cout << i << ". " << coursecur->course_name;
            coursecur = coursecur->Next;
            cout << endl;
        }
        int choice2;
        gotoxy(8 + offset, 2);
        cout << "Input the course you want to view: ";
        cin >> choice2;
        coursecur = year_cur->sem[choice - 1].courseh;
        for (int i = 0; i < choice2; i++)
        {
            coursecur = coursecur->Next;
        }

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
            gotoxy(58, 5);
            cout << coursecur->ses[i].date << " ";
            gotoxy(58, 6);
            cout << coursecur->ses[i].timeofSes;
            cout << endl;
        }
    }
}

void Delete_Course(Year*& year_cur, int& n, int num_sem)
{
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    string tempID;
    gotoxy(8 + offset, 3);
    cout << "Input the ID of course you want to delete: " <<endl;
    gotoxy(51 + offset, 3);
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
    createframe();
    gotoxy(8 + offset, 4);
    cout << "Delete complete." << endl;
}

void Update_Course(Year*& year_cur, int num_sem)
{
    int offset = 30;
    createframe();
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    string tempID;
    gotoxy(8 + offset, 3);
    cout << "Input the ID of course you want to change: " << endl;
    gotoxy(51 + offset, 3);
    cin >> tempID;
    Course* coursecur = Find_Course(year_cur, tempID, num_sem);
    int choice;
    createframe();
    gotoxy(8 + offset, 3);
    cout << "1. Change the name of the course: " << endl;
    gotoxy(8 + offset, 4);
    cout << "2. Change the ID of the course: " << endl;
    gotoxy(8 + offset, 5);
    cout << "3. Change the name of the teacher of the course: " << endl;
    gotoxy(8 + offset, 6);
    cout << "4. Change the number of credits of the course: " << endl;
    gotoxy(8 + offset, 7);
    cout << "5. Change the sessions of the course: " << endl;
    gotoxy(8 + offset, 3);
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
    gotoxy(8 + offset, 3);
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
    gotoxy(8 + offset, 3);
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
        cout << sthead->ID << " " << sthead->NameFirst << " " << sthead->NameLast << " " << sthead->Gender << endl;
    }
}
void View_List_Of_Students_Course(Year* year_cur, int num_sem)
{
    string tempID;
    cout << "Input the ID of the course: ";
    cin >> tempID;
    Course* course_cur = Find_Course(year_cur, tempID, num_sem);
    int n = course_cur->num_stu;
    for (int i = 0; i < n; i++)
    {
        cout << i << ". " << course_cur->Stu[i].ID << " " << course_cur->Stu[i].NameFirst << " " << course_cur->Stu[i].NameLast << " " << course_cur->Stu[i].Gender;
        cout << endl;
    }
}
void GetCurrentDate(int &Year, int &Month, int &Day) {
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    Year = 1900 + newtime.tm_year;
    Month = 1 + newtime.tm_mon;
    Day = newtime.tm_mday;
    
}
void Convert_Date(string s, int &dd, int &mm, int &yyyy)
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
    Convert_Date(year_cur->sem[num_sem - 1].regStart , dd1, mm1, yyyy1);
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
    string tempID;
    cout << "Input the ID of the course: ";
    cin >> tempID;
    ofstream output;
    output.open("Stu_in_course.csv");
    Course* course_cur = Find_Course(year_cur, tempID, num_sem);
    int n = course_cur->num_stu;
    for (int i = 0; i < n; i++)
    {
        output << course_cur->Stu[i].ID << "," << course_cur->Stu[i].Fullname << "," << course_cur->Stu[i].Gender;
        output << endl;
    }
}
void Import_Scoreboard(Year* year_cur, int num_sem)
{
    ifstream input;
    string tempID;;
    input.open("Scoreboard.csv");
    cout << "Input the course you want to add scoreboard: " << endl;
    cin >> tempID;
    Course* course_cur = Find_Course(year_cur, tempID, num_sem);
    if (!input.is_open())
    {
        cout << "Cannot open file " << endl;
    }
    else
    {
        int i = 0;
        while (input.good())
        {
            getline(input, course_cur->Stu[i].No, ',');
            getline(input, course_cur->Stu[i].NameFirst, ',');
            getline(input, course_cur->Stu[i].NameLast, ',');
            input >> course_cur->Stu[i].score.Midterm >> course_cur->Stu[i].score.Other >> course_cur->Stu[i].score.Final >> course_cur->Stu[i].score.Total;
            i++;
        }
    }
    input.close();
}
void View_Scoreboard_Course(Year* year_cur, int num_sem)
{
    string tempID;
    int count;
    cout << "Input the course you want to add scoreboard: " << endl;
    cin >> tempID;
    Course* course_cur = Find_Course(year_cur, tempID, num_sem);
    count = course_cur->num_stu;
    for (int i = 0; i < count; i++)
    {
        cout << course_cur->Stu[i].No << " " << course_cur->Stu[i].ID << " " << course_cur->Stu[i].Fullname << " " << course_cur->Stu[i].score.Midterm << " " << course_cur->Stu[i].score.Other << " " << course_cur->Stu[i].score.Final << " " << course_cur->Stu[i].score.Total;
        cout << endl;
    }
}
void Edit_Score(Year*& year_cur, int num_sem)
{
    string tempID, tempIDStu;
    cout << "Input the course you want to add scoreboard: " << endl;
    cin >> tempID;
    Course* course_cur = Find_Course(year_cur, tempID, num_sem);
    int count = course_cur->num_stu;
    Students1 TempStu;
    cout << "Input the ID of student you want to edit: " << endl;
    cin >> tempIDStu;
    for (int i = 0; i < count; i++)
    {
        if (course_cur->Stu[i].ID == tempIDStu)
        {
            TempStu = course_cur->Stu[i];
        }
    }
    int option;
    cout << "Input the score you want to edit: ";
    cout << "1. Midterm Score" << endl;
    cout << "2. Other Score" << endl;
    cout << "3. Final Score" << endl;
    cout << "4. Total" << endl;
    cin >> option;
    if (option == 1)
    {
        cout << "Input Midterm Score" << endl;
        cin >> TempStu.score.Midterm;
    }
    if (option == 2)
    {
        cout << "Input Other Score" << endl;
        cin >> TempStu.score.Other;
    }
    if (option == 3)
    {
        cout << "Input Final Score" << endl;
        cin >> TempStu.score.Final;
    }
    if (option == 4)
    {
        cout << "Input Final Score" << endl;
        cin >> TempStu.score.Total;
    }
}