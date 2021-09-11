// Program2.cpp: определяет точку входа для приложения.
//

#include "Program2.h"

using namespace std;

fstream FileTemp;

string path = "../../Shared/Temp.txt";


int main()
{
	string str;

	do
	{
		this_thread::sleep_for(chrono::milliseconds(3000));
		FileTemp.open(path);
		if (FileTemp.is_open())
		{
			FileTemp >> str;
			cout << str << '\n';
			if (str == "")
			{
				cout << "Data not found\n";
			}
		}
		else
		{
			cout << "File open error\n";
		}
		FileTemp.close();

	} while (str == "");


	int count = size(str);
	int num = stoi(str);
	if (count > 2 && num % 32 == 0)
	{
		cout << "Data received\n";
	}
	else
		cout << "Error\n";

	FileTemp.open(path, FileTemp.out);
	FileTemp.close();

	main();
}
