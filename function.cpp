#include "Header.h";
void Menu_Feature_First_Staff(Students* stu);
void LoadFileStudents(Students*& stu, string filename)
{
    ifstream input;
    input.open(filename);
    if (!input.is_open())
    {
        cout << "Cannot open file " << endl;
    }
    else
    {
        Students* pCur = stu;
        while (input.good())
        {

            if (stu == nullptr)
            {
                stu = new Students;
                pCur = stu;
            }
            else
            {
                pCur->pNext = new Students;
                pCur = pCur->pNext;
            }
            getline(input, pCur->No, ',');
            getline(input, pCur->ID, ',');
            getline(input, pCur->NameFirst, ',');
            getline(input, pCur->NameLast, ',');
            getline(input, pCur->Gender, ',');
            getline(input, pCur->Birth, ',');
            getline(input, pCur->socialID, ',');
            getline(input, pCur->username, ',');
            getline(input, pCur->password, ',');
            getline(input, pCur->classes, '\n');
            pCur->pNext = nullptr;
        }
    }
    input.close();
}
void LoadFileStaff(Students*& sta, string filename)
{
    ifstream input;
    input.open(filename);
    if (!input.is_open())
    {
        cout << "Cannot open file " << endl;
    }
    else
    {
        Students* pCur = sta;
        while (input.good())
        {

            if (sta == nullptr)
            {
                sta = new Students;
                pCur = sta;
            }
            else
            {
                pCur->pNext = new Students;
                pCur = pCur->pNext;
            }
            getline(input, pCur->No, ',');
            getline(input, pCur->ID, ',');
            getline(input, pCur->NameFirst, ',');
            getline(input, pCur->NameLast, ',');
            getline(input, pCur->Gender, ',');
            getline(input, pCur->Birth, ',');
            getline(input, pCur->socialID, ',');
            getline(input, pCur->username, ',');
            getline(input, pCur->password, '\n');
            pCur->pNext = nullptr;
        }
    }
    input.close();
}
void Release_memory(Students*& stu) {
    while (stu != nullptr) {
        Students* ptemp = stu;
        stu = stu->pNext;
        delete ptemp;
    }
}
void display_information_students(Students* stu) {
    while (stu) {
        int space[] = { 10,10,20,8,12,10,10,15,10 };
        cout << stu->No << setw(space[0]) << stu->ID << setw(space[1]) << stu->NameFirst << setw(space[2]) << stu->NameLast;
        cout << setw(space[3]) << stu->Gender << setw(space[4]) << stu->Birth << setw(space[5]) << stu->socialID;
        cout << setw(space[6]) << stu->username << setw(space[7]) << stu->password << setw(space[8]) << stu->classes;
        cout << "\n";
        stu = stu->pNext;
    }
}
void display_information_staffs(Students* stu) {
    while (stu != nullptr) {
        int space[] = { 10,10,20,8,12,10,10,15,10 };
        cout << stu->No << setw(space[0]) << stu->ID << setw(space[1]) << stu->NameFirst << setw(space[2]) << stu->NameLast;
        cout << setw(space[3]) << stu->Gender << setw(space[4]) << stu->Birth << setw(space[5]) << stu->socialID;
        cout << setw(space[6]) << stu->username << setw(space[7]) << stu->password;
        cout << "\n";
        stu = stu->pNext;
    }
}
void export_file(Students* stu, string filename) {
    ofstream output;
    output.open(filename);
    Students* s = stu->pNext;
    while (stu != nullptr && stu->No != "") {
        output << stu->No << "," << stu->ID << "," << stu->NameFirst << "," << stu->NameLast << "," << stu->Gender
            << "," << stu->Birth << "," << stu->socialID << "," << stu->username << "," << stu->password;
        if (s->ID[0] != '0') output << "," << stu->classes;
        output << "\n";
        stu = stu->pNext;
    }
    output.close();
}
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}
void displayUI()
{
    int offset = 30;
    int staffFlag = 1;
    int options;
    do
    {
        system("CLS");
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        createframe();
        SetConsoleTextAttribute(hConsole, 121);
        gotoxy(20 + offset, 4); cout << "1. Profile";
        gotoxy(20 + offset, 5); cout << "2. Change password"; // can be added later on
        if (staffFlag == 1) // chừng nào check là staff được thì sẽ sửa.
        {
            gotoxy(20 + offset, 3); cout << "Welcome Staff";
            gotoxy(20 + offset, 7); cout << "0. Logout";
        }
        else
        {
            gotoxy(20 + offset, 3); cout << "Welcome Students";
            gotoxy(20 + offset, 6); cout << "0. Logout";
        }
        SetConsoleTextAttribute(hConsole, 6);
        gotoxy(0 + offset, 11); cout << " >> Please, select your functions: ";
        cin >> options;
    } while (options != 0);
}
void createframe()
{
    int offset = 30;
    int x = 60 + offset;  // change size of input
    int y = 10;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 119);
    for (int i = 0; i < y; i++)
    {
        for (int j = 0 + offset; j < x; j++)
        {
            gotoxy(j, i);
            cout << " ";
        }
        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, 158);
    for (int i = 0 + offset; i < x; i++) // tao dong ngang
    {
        gotoxy(i, 0); printf("%c", 205); // dong ngang tren
        gotoxy(i, y); printf("%c", 205);  // dong ngang duoi
    }
    for (int i = 1; i < y; i++)  // dong ke thang dung
    {
        gotoxy(0 + offset, i); printf("%c", 186); // dong thang ben trai
        gotoxy(x, i); printf("%c", 186); // dong thang ben phai
    }
    gotoxy(x, 0); printf("%c", 187); // cai moc cau ben phai ben tre^n
    gotoxy(x, y); printf("%c", 188); // cai moc cau ben phai ben duoi
    gotoxy(0 + offset, 0); printf("%c", 201); // cai moc cau ben trai tren
    gotoxy(0 + offset, y); printf("%c", 200); // moc cau ben trai duoi
    gotoxy(26 + offset, 0); cout << "  MENU  ";
    cout << endl;
}
Students* Find_User_By_ID(Students* stu, string ID)
{
    while (stu != nullptr) {
        if (stu->ID == ID) return stu;
        stu = stu->pNext;
    }
    return nullptr;
}
bool CheckUser(Students* stu, Students*& stu_cur, string ID, string pass)
{
    if (stu == nullptr) return false;
    // stu la dong dau tien Name ,NO LAST NAME...
    stu_cur = Find_User_By_ID(stu->pNext, ID);

    if (stu_cur == nullptr || stu_cur->password != pass) return false;
    return true;
}
void InputMaskedPassword(string& password)
{
    password = "";
    char ch;
    ch = _getch();
    while (ch != 13) {//character 13 is enter

        if (ch == '\b')   //If the 'Backspace' key is pressed
        {
            if (password.size() != 0)  //If the password string contains data, erase last character
            {
                cout << "\b \b";
                password.erase(password.size() - 1, 1);
            }
        }
        else {
            password.push_back(ch);
            cout << '*';
        }
        ch = _getch();
    }
}
void Login(Students* stu, Students* sta, Students*& stu_cur, Year*& yearh)
{
    int offset = 30;
    while (1)
    {
        createframe();
        string user;
        string pass;
        string filenameStu = "STUDENT_DATABASE.csv";
        string filenameSta = "STAFF.csv";
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 121);
        gotoxy(20 + offset, 3); cout << "Username: "; cin >> user;
        if (user[0] == '-') break;
        gotoxy(20 + offset, 4); cout << "Password: ";
        InputMaskedPassword(pass);
        if (user[0] != '0')
        {
            if (CheckUser(stu, stu_cur, user, pass) == false)
            {
                gotoxy(20 + offset, 3); cout << "Username:                     ";
                gotoxy(10 + offset, 6);
                cout << "Wrong username or password " << endl;
                gotoxy(20 + offset, 4); cout << "Password:                     ";
                gotoxy(10 + offset, 7);
                cout << "Please try again " << endl;
                Sleep(1500);
            }
            else {
                Option_After_Login(stu, sta, stu_cur, filenameStu, yearh);
            }
        }
        if (user[0] == '0')
        {
            if (CheckUser(sta, stu_cur, user, pass) == false)
            {
                gotoxy(20 + offset, 3); cout << "Username:                     ";
                gotoxy(10 + offset, 6);
                cout << "Wrong username or password " << endl;
                gotoxy(20 + offset, 4); cout << "Password:                     ";
                gotoxy(10 + offset, 7);
                cout << "Please try again " << endl;
                Sleep(1500);
            }
            else {
                Option_After_Login(stu, sta, stu_cur, filenameSta, yearh);
            }
        }
    }
}
void Change_Password(Students* stu, Students*& stu_cur, string New_Password, string filename) {
    stu_cur->password = New_Password;
    export_file(stu, filename);
}
void View_profile(Students* stu, Students* stu_cur) {
    createframe();
    int offset = 30;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    gotoxy(12 + offset, 1); cout << stu->No << ":  " << stu_cur->No;
    gotoxy(12 + offset, 2); cout << stu->ID << ":  " << stu_cur->ID;
    gotoxy(12 + offset, 3); cout << "Name:  " << stu_cur->NameLast << " " << stu_cur->NameFirst;
    gotoxy(12 + offset, 4); cout << stu->Gender << ":  " << stu_cur->Gender;
    gotoxy(12 + offset, 5); cout << stu->Birth << ":  " << stu_cur->Birth;
    gotoxy(12 + offset, 6); cout << stu->socialID << ":  " << stu_cur->socialID;
    gotoxy(12 + offset, 7); cout << stu->username << ":  " << stu_cur->username;
    gotoxy(12 + offset, 8); cout << stu->password << ":  " << stu_cur->password;
    if (stu_cur->ID[0] != '0')
    {
        gotoxy(12 + offset, 9); cout << stu->classes << ":  " << stu_cur->classes;
    }
    int wait = 0;
    do
    {
        SetConsoleTextAttribute(hConsole, 6);
        gotoxy(0 + offset, 11); cout << " >> Press any to stop.  "; gotoxy(24 + offset, 11); cout << "                               ";
        gotoxy(25 + offset, 11);  cin >> wait;
    } while (wait = 0);
}
void Option_After_Login(Students*& stu, Students*& sta, Students*& stu_cur, string filename, Year*& yearh) {
    int offset = 30;
    while (1) {
        createframe();
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 121);
        gotoxy(20 + offset, 4); cout << "1.View Profile\n";
        gotoxy(20 + offset, 5); cout << "2.Change Password\n";
        gotoxy(20 + offset, 6);
        if (stu_cur->username[0] != '0') {
            cout << "3. Enroll in a course\n";
            gotoxy(20 + offset, 7); cout << "4. View enrolled courses";
            gotoxy(20 + offset, 8); cout << "0.Log out\n";
        }//cout student name of function
        if (stu_cur->username[0] == '0'){ cout << "3.Academic Year Options\n"; // cout staff name of function
        gotoxy(20 + offset, 7); cout << "0.Log out\n";
    }
        int option;
        SetConsoleTextAttribute(hConsole, 6);
        gotoxy(0 + offset, 11); cout << " >> Please, select your functions: "; gotoxy(35 + offset, 11); cout << "   ";
        gotoxy(35 + offset, 11);  cin >> option;
        if (option == 0)  break;
        if (option == 1) View_profile(stu, stu_cur);
        if (option == 2) {
            string pass;
            createframe();
            SetConsoleTextAttribute(hConsole, 121);
            gotoxy(20 + offset, 4);
            cout << "New Password="; cin >> pass;
            if (stu_cur->username[0] != '0')Change_Password(stu, stu_cur, pass, filename);
            if (stu_cur->username[0] == '0')Change_Password(sta, stu_cur, pass, filename);
        }
        if (stu_cur->username[0] != '0' && option == 3) {
            Enroll_Course(stu_cur, yearh);
        } // student function;
        if (stu_cur->username[0] == '0' && option == 3) {
            Menu_Feature_First_Staff(stu, yearh);
        }
        if (stu_cur->username[0] == '0' && option == 4) {
            View_Course(stu_cur);
            //if (time == true)
            //{
                 gotoxy(20 + offset, 8); cout << "1. Remove Enrolled Courses";
                 gotoxy(20 + offset, 9); cout << "0. Exit";
                 cin >> option;
                 if (option == 0) break;
                 if (option == 1) Remove_Course(stu_cur, yearh);
            //}
        }
    }
}
void Menu()
{
    Students* stu = nullptr;
    Students* sta = nullptr;
    Students* stu_cur = nullptr;
    string filenameStu = "STUDENT_DATABASE.csv";
    string filenameSta = "STAFF.csv";
    LoadFileStudents(stu, filenameStu);
    LoadFileStaff(sta, filenameSta);
    Year* yearh = nullptr;
    Login(stu, sta, stu_cur, yearh);
}
