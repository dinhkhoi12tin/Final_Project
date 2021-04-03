 #include"Header.h"
int main()
{    
    Students* stu = nullptr;
    string filename_input = "STUDENT_DATABASE.csv";
    LoadFileStudents(stu,filename_input);
    display_information_students(stu);
    //Change_Password(stu, "20127001", "dinhkhoi123", "STUDENT-CSV-DATABASE.csv");
    //displayUI();
    Release_memory(stu);
    
}
    