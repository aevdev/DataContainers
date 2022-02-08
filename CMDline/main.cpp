//Solution: DataContainers
//Project:: ForwardList
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	//int argc - (arguments count) - ��� ���������� �������� ���������� ��������� ������
	//char* argv[] - (argument values) - ������ �����, ������� �������� �������� ����������
	//������� ������� ������� argv[] ��� ������ ������ ��� ������������ ����� ��������� (������� ���� � �����).
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