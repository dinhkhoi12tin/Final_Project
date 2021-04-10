#include "Header1.h"
void create_new_year() {
    string newyear;
    cout << "type new year:"; cin >> newyear;
}
Class* Find(Class* classhead, string classname) {
    while (classhead) {
        if (classhead->class_name == classname) return classhead;
        classhead = classhead->Next;
    }
}
void add_one_by_one(Class*& classhead) {
    while (1) {
        cout << "Type -1 to finish\n";
        cout << "Name class:";
        string nameclass;
        cin >> nameclass;
        if (nameclass[0] == '-') break;
        Class* pcur = Find(classhead, nameclass);
        Students* newst = new Students;
        cin.ignore();
        newst->classes = nameclass;
        cout << "No:"; getline(cin, newst->No, '\n');
        cout << "ID:"; getline(cin, newst->ID, '\n');
        cout << "NameFirst:"; getline(cin, newst->NameFirst, '\n');
        cout << "NameLast:"; getline(cin, newst->NameLast, '\n');
        cout << "Gender:"; getline(cin, newst->Gender, '\n');
        cout << "Birth:"; getline(cin, newst->Birth, '\n');
        cout << "socialID:"; getline(cin, newst->socialID, '\n');
        newst->pNext = pcur->sthead;
        pcur->sthead = newst;
    }
}
void display(Class* classhead, string classname) {
    Students* sthead = Find(classhead, classname)->sthead;
    display_information_students(sthead);
}
void add_by_file_csv(Class*& classhead) {
    while (1) {
        cout << "-1.exit\n";
        cout << "filename:";
        string filename;
        cin >> filename;
        if (filename[0] == '-') break;
        Students* Newst = 0;
        LoadFileStudents(Newst, filename);
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
    while (1) {
        string classname;
        cout << "Type -1 to finish\n";
        cout << "type name of class:"; cin >> classname;
        if (classname[0] == '-') break;
        Class* newclass = new Class;
        newclass->class_name = classname;
        newclass->Next = classhead;
        classhead = newclass;
    }
}
void Menu_Feature_First_Staff() {
    Class* classhead = 0;
    create_new_year();
    while (1) {
        cout << "1.create class\n";
        cout << "2.add one by one student to class\n";
        cout << "3.add by file csv\n";
        cout << "0.exit\n";
        int option;
        cin >> option;
        if (option == 1) create_class(classhead);
        if (option == 2) add_one_by_one(classhead);
        if (option == 3) add_by_file_csv(classhead);
        if (option == 0) break;
    }
}