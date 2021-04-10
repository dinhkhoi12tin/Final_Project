#include"Header.h"
struct Class {
    string class_name = "";
    Students* sthead = 0;
    Class* Next = 0;
};
void create_new_year();
Class* Find(Class* classhead, string classname);
void add_one_by_one(Class*& classhead);
void display(Class* classhead, string classname);
void add_by_file_csv(Class*& classhead);
void create_class(Class*& classhead);
void Menu_Feature_First_Staff();

