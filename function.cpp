#include "Header.h";
void LoadFileStudents(Students*& stu)
{
	ifstream input;
	input.open(" CSV ");
	if (!input.is_open())
	{
		cout << "Cannot open file " << endl;
	}
	else
	{
		Students* pCur = stu;
		while (!input.eof())
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
			input >> pCur->No >> pCur->ID >> pCur->NameFirst >> pCur->NameLast >>  pCur->Gender >> pCur->Birth >> pCur->socialID >> pCur->username >> pCur->password;
			pCur->pNext = nullptr;
		}
	}
	input.close();
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
        int staffFlag = 1;
        int options;
        do
        {
           
            system("CLS");
            HANDLE  hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            createframe();
            SetConsoleTextAttribute(hConsole, 121);
            gotoxy(20, 4); cout << "1. Profile";
            gotoxy(20, 5); cout << "2. Change password"; // can be added later on
            if (staffFlag == 1) // chừng nào check là staff được thì sẽ sửa.
            {   
                gotoxy(20, 3); cout << "Welcome Staff";
                gotoxy(20, 6); cout << "3. Create SchoolYear";
                gotoxy(20, 7); cout << "0. Logout";
            }
            else
            {
                gotoxy(20, 3); cout << "Welcome Students";
                gotoxy(20, 6); cout << "0. Logout";
            }
            SetConsoleTextAttribute(hConsole, 6);
            gotoxy(0, 11); cout << " >> Please, select your functions: ";
            cin >> options;
        } while (options != 0);
    }
    void createframe()
        {
        
        int x = 60;  // change size of input
        int y = 10;
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 119);
        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                cout << " " ;
            }
            cout << endl;
        }
        SetConsoleTextAttribute(hConsole, 158);
        for (int i = 1; i < x; i++) // tao dong ngang
        {
            gotoxy(i, 0); printf("%c", 205); // dong ngang tren
            gotoxy(i, y); printf("%c", 205);  // dong ngang duoi
        }
        for (int i = 1; i < y; i++)  // dong ke thang dung
        {
            gotoxy(0, i); printf("%c", 186); // dong thang ben trai
            gotoxy(x, i); printf("%c", 186); // dong thang ben phai
        }
        gotoxy(x, 0); printf("%c", 187); // cai moc cau ben phai ben tre^n
        gotoxy(x, y); printf("%c", 188); // cai moc cau ben phai ben duoi
        gotoxy(0, 0); printf("%c", 201); // cai moc cau ben trai tren
        gotoxy(0, y); printf("%c", 200); // moc cau ben trai duoi
        gotoxy(26, 0); cout << "  MENU  ";
        cout << endl;
     }