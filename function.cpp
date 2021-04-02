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
			input >> stu->No >> stu->NameFirst >> stu->NameLast >>  stu->ID >> stu->Gender >> stu->socialID >> stu->username >> stu->password >> stu->Birth ;
			pCur->pNext = nullptr;
		}
	}
	input.close();
}