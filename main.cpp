 #include"Header.h"
int main()
{    
    Students* stu = nullptr;
    string filename_input = "STUDENT_DATABASE.csv";
    LoadFileStudents(stu,filename_input);
    cout << stu->password<<"\n";
    display_information_students(stu);
    string filename_export = "STUDENT_DATABASE.csv";
    export_file(stu, filename_export);
    Release_memory(stu);
    //displayUI();
}
    