//Solution: DataContainers
//Project:: ForwardList
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	//int argc - (arguments count) - это количество принятых аргументов командной строки
	//char* argv[] - (argument values) - массив строк, который содержит значения аргументов
	//Нулевой элемент массива argv[] это всегда полное имя исполняемого файла программы (включая путь к файлу).
	for (int i = 0; i < argc; ++i)
	{
		cout << "argv[" << i << "]\t" << argv[i] << endl;
	}

	if (argc > 5)
	{
		cerr << "Incorrect syntax" << endl;
		return -1;
	}

	return 0;
}