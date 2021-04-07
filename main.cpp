 #include"Header.h"
int main()
{    
    Students* stu = nullptr;
    string filename_input = "STUDENT_DATABASE.csv";
    LoadFileStudents(stu, filename_input);
    //display_information_students(stu);
    Login(stu);
    Release_memory(stu);
    displayUI();
}
   
