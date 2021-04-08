 #include"Header.h"
struct Class {
    string class_name="";
    Students *sthead=0;
    Class* Next = 0;
};
void create_new_year(string & newyear) {
    cout << "type new year:"; cin >> newyear;
}
Class* Find(Class*classhead,string classname) {
    while (classhead) {
        if (classhead->class_name == classname) return classhead;
        classhead = classhead->Next;
    }
}
void add_one_by_one(Class*& classhead) {
  
    string nameclass;
    cin.ignore();
    cout << "Name class:"; getline(cin,nameclass,'\n');
    Class* pcur = Find(classhead,nameclass);
    Students* newst = new Students;
    cout << "No:"; getline(cin,newst->No,'\n');
    cout << "ID:"; getline(cin,newst->ID,'\n');
    cout << "NameFirst:"; getline(cin,newst->NameFirst,'\n');
    cout << "NameLast:"; getline(cin,newst->NameLast,'\n');
    cout << "Gender:"; getline(cin,newst->Gender,'\n');
    cout << "Birth:"; getline(cin,newst->Birth,'\n');
    cout << "socialID:"; getline(cin,newst->socialID,'\n');
    newst->pNext = pcur->sthead;
    pcur->sthead = newst;
}
void create_class(Class*& classhead) {
    while (1) {
        cout << "1.create class\n";
        cout << "2.add one by one student to class\n";
        cout << "0.exit\n";
        int option;
        cin >> option;
        if (!option) break;
        else if (option == 2) add_one_by_one(classhead);
        else {
            string classname;
            cout << "type name of class:"; cin >> classname;
            Class* newclass = new Class;
            newclass->class_name = classname;
            newclass->Next = classhead;
            classhead = newclass;
        }
    }
}
void display(Class * classhead,string classname) {
    Students* sthead = Find(classhead, classname)->sthead;
    while (sthead) {
        cout << sthead->No << " " << sthead->ID << " " << sthead->NameFirst << " " << sthead->NameLast << " ";
        cout << sthead->Gender << " " << sthead->Birth << " " << sthead->socialID<<"\n";
        sthead = sthead->pNext;
    }
}
int main()
{
    //Students* stu = nullptr;
    //string filename_input = "STUDENT_DATABASE.csv";
    // LoadFileStudents(stu, filename_input);
    //display_information_students(stu);
    //Login(stu);
    //Release_memory(stu);
    //displayUI();
}