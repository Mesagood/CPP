// Program1.cpp: определяет точку входа для приложения.
//

#include "Program1.h"

using namespace std;


fstream FileBuff;

//Путь к файлу
string path = "../../Shared/Buffer.txt";
string PathTemp = "../../Shared/Temp.txt";

//Очистка файлов
void ClearFile()
{
	FileBuff.open(path, FileBuff.out);
	FileBuff.close();
}

//Вывод информации о строке
void Output(int a, int count)
{
	switch (a)
	{
	case 0:
		cout << "Status:    " << "Good" << "\n";
		break;
	case 1:
		cout << "Status:	" << "Error" << "\n";
		break;
	case 2:
		cout << "Number in line:    " << count << "\n";
		break;
	case 3:
		cout << "Number > 64\n";
		break;
	case 4:
		cout << "Sum of digits: " << '\t' << count;
		cout << '\n' << '\n' << '\n';
		break;
	}
}

//Проверка на качество строки
bool IsNumValid(string& str)
{
	int Err = 0;
	if (str != "")
	{
		for (int i = 0; i < size(str); i++)
		{
			if (str[i] < '0' || str[i] > '9')
			{
				Err++;
				Output(1, Err);
				return false;
			}
		}
		Output(0, Err);
		return true;
	}
	else
	{
		Output(1, Err);
		return false;
	}
}

//Проверка на кол-во символов в строке
bool IsValidCount(string& str)
{
	int count = size(str);
	if (count > 64)
	{
		Output(3, count);
		str = "";
		return false;
	}
	Output(2, count);
	return true;
}

//Вывод сортировки
void OutputSort(string& str)
{
	//Вывод
	cout << "Sort array:" << '\t';
	for (int index = 0; index < size(str); index++)
	{
		//Сортированный массив
		cout << str[index];
	}
	cout << '\n';

	//Замена в массиве
	for (int index = 0; index < size(str); index++)
	{
		//Масив с заменой
		if (str[index] % 2 == 0)
		{
			str[index] = 'K';
		}
	}
}

//Сортировка
void SortReplace(string& str)
{
	//Сортировка (выборка)
	for (int startIndex = 0; startIndex < size(str) - 1; startIndex++)
	{
		int smallestIndex = startIndex;
		for (int currentIndex = startIndex + 1; currentIndex < size(str); currentIndex++)
		{
			if (str[currentIndex] > str[smallestIndex])
				smallestIndex = currentIndex;
		}
		swap(str[startIndex], str[smallestIndex]);
	}
	OutputSort(str);
}

//Сумма цифр
void sum(string& str)
{
	int result = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		result += (str[i] - '0');
	}

	FileBuff.open(PathTemp, ios::out);
	if (FileBuff.is_open())
	{
		FileBuff << result << endl;
	}
	else
	{
		cout << "File open error\n";
	}

	Output(4, result);
}

//Оичстка строки 
void ClearingLine(string str)
{
	char c = 'K';
	for (int i = 0; i < c; ++i)
	{
		str.erase(remove(str.begin(), str.end(), c), str.end());
	}
	sum(str);
}

//Поток 2
void Thread1()
{
	cout << '\n';
	cout << "\tId Thread1: " << this_thread::get_id() << endl;
	cout << '\n';
	string StrThread1;

	FileBuff.open(path, fstream::in);
	if (FileBuff.is_open())
	{
		while (!FileBuff.eof())
		{
			FileBuff >> StrThread1;
			cout << "In Buffer: \t" << StrThread1 << endl;
			break;
		}
	}
	FileBuff.close();

	//костыль для очистки файла
	ClearFile();


	ClearingLine(StrThread1);
}

//Поток 1
int main()
{
	cout << "\n\tId main:" << this_thread::get_id << endl;
	string num;

	cout << "\r\nEnter number: ";
	cin >> num;

	//Проверка на наличие не цифр в строке
	if (IsNumValid(num) == false)
	{
		cout << "Try again!";
		main();
	}

	//Проверка на кол-во символов	
	if (IsValidCount(num) == false)
	{
		cout << "Try again!";
		main();
	}

	//Сортировка/замена
	SortReplace(num);

	cout << "Array after replace:" << '\t' << num << '\n';

	//Костыль для очистки файла
	ClearFile();

	FileBuff.open(path, ios::out);
	if (FileBuff.is_open())
	{
		FileBuff << num << '\n';
	}
	else
	{
		cout << "File open error" << '\n';
	}
	FileBuff.close();

	thread th1(Thread1);
	th1.join();

	main();
}

