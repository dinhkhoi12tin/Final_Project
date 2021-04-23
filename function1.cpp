#include "Header.h"
void create_new_year() {
    int offset = 30;
    createframe();
    string newyear;
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 121);
    gotoxy(20 + offset, 3); cout << "type new year:"; cin >> newyear;
}
Class* Find(Class* classhead, string classname) {
    while (classhead) {
        if (classhead->class_name == classname) return classhead;
        classhead = classhead->Next;
    }
    return 0;
}
void add_one_by_one(Class*& classhead) {
    int offset = 30;
    while (1) {
        createframe();
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 121);
        gotoxy(20 + offset, 3); cout << "Type -1 to finish\n";
        gotoxy(20 + offset, 4); cout << "Name class:";
        string nameclass;
        cin >> nameclass;
        if (nameclass[0] == '-') break;
        createframe();
        SetConsoleTextAttribute(hConsole, 121);
        Class* pcur = Find(classhead, nameclass);
        Students* newst = new Students;
        cin.ignore();
        newst->classes = nameclass;
        gotoxy(20 + offset, 2); cout << "No:"; getline(cin, newst->No, '\n');
        gotoxy(20 + offset, 3); cout << "ID:"; getline(cin, newst->ID, '\n');
        gotoxy(20 + offset, 4); cout << "NameFirst:"; getline(cin, newst->NameFirst, '\n');
        gotoxy(20 + offset, 5); cout << "NameLast:"; getline(cin, newst->NameLast, '\n');
        gotoxy(20 + offset, 6); cout << "Gender:"; getline(cin, newst->Gender, '\n');
        gotoxy(20 + offset, 7); cout << "Birth:"; getline(cin, newst->Birth, '\n');
        gotoxy(20 + offset, 8); cout << "socialID:"; getline(cin, newst->socialID, '\n');
        newst->username = newst->password = newst->ID;
        newst->pNext = pcur->sthead;
        pcur->sthead = newst;
    }
}
void display(Class* classhead) {
    while (classhead) {
        Students* sthead = classhead->sthead;
        display_information_students(sthead);
        classhead = classhead->Next;
    }
}
void Export_new(Class* classhead, Students* stu) {
    Students* stu_cur = stu;
    while (stu->pNext && stu->pNext->No != "") stu = stu->pNext;
    while (classhead) {
        Students* sthead = classhead->sthead;
        while (sthead) {
            stu->pNext = sthead;

            stu = stu->pNext;
            sthead = sthead->pNext;
        }
        //display_information_students(sthead);
        classhead = classhead->Next;
    }
    string filename = "STUDENT_DATABASE.csv";
    export_file(stu_cur, filename);
    //display_information_students(stu_cur);
}
void LoadFileNewStudents(Students*& stu, string filename)
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
            if (pCur != stu)pCur->username = pCur->password = pCur->ID;
            getline(input, pCur->classes, '\n');
            pCur->pNext = nullptr;
        }
    }
    input.close();
}
void add_by_file_csv(Class*& classhead) {
    int offset = 30;
    while (1) {
        createframe();
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 121);
        gotoxy(20 + offset, 3); cout << "-1.exit\n";
        gotoxy(20 + offset, 4); cout << "filename:";
        string filename;
        cin >> filename;
        if (filename[0] == '-') break;
        Students* Newst = 0;
        LoadFileNewStudents(Newst, filename);
        Newst = Newst->pNext;
        while (Newst) {
            Class* Cur = Find(classhead, Newst->classes);
            Students* ptemp = Newst;
            Newst = Newst->pNext;
            ptemp->pNext = Cur->sthead;
            Cur->sthead = ptemp;
        }
    }
}
void create_class(Class*& classhead) {
    int offset = 30;
    while (1) {
        createframe();
        string classname;
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 121);
        gotoxy(20 + offset, 3); cout << "Type -1 to finish\n";
        gotoxy(20 + offset, 4); cout << "type name of class:"; cin >> classname;
        if (classname[0] == '-') break;
        Class* newclass = new Class;
        newclass->class_name = classname;
        newclass->Next = classhead;
        classhead = newclass;
    }
}
void Menu_Feature_First_Staff(Students* stu) {
    int offset = 30;
    Class* classhead = 0;
    create_new_year();
    while (1) {
        createframe();
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 121);
        gotoxy(20 + offset, 3); cout << "1.create class\n";
        gotoxy(20 + offset, 4); cout << "2.add one by one student to class\n";
        gotoxy(20 + offset, 5); cout << "3.add by file csv\n";
        gotoxy(20 + offset, 6); cout << "0.exit\n";
        int option;
        SetConsoleTextAttribute(hConsole, 6);
        gotoxy(0 + offset, 11); cout << " >> Please, select your functions: "; gotoxy(35 + offset, 11); cout << "   ";
        gotoxy(35 + offset, 11);  cin >> option;
        if (option == 1) create_class(classhead);
        if (option == 2) add_one_by_one(classhead);
        if (option == 3) add_by_file_csv(classhead);
        if (option == 0) break;
    }
    Export_new(classhead, stu);
}
