#include"List.h"
#include"List.cpp" //когда класс у нас шаблонизированный, то подключать надо не только .h файл, но и .cpp

void print(int arr[]);

//#define BASE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST
int main()
{
#ifdef BASE_CHECK
	int n;
	cout << "Inpur list size: ";
	cin >> n;
	List list;
	for (int i = 0; i < n; ++i)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index, value;
	cout << "Input index: "; 
	cin >> index;
	cout << "Input value: ";
	cin >> value;
	list.insert(index, value);
	list.print();
#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	List<int> list = { 3, 5, 8, 13, 21 };
	list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	for (List<int>::ConstReverseIterator it = list.crbegin(); it; ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST
	List<double> d_list = { 2.5, 3.14, 5.2, 8.3 };
	for (double i : d_list) 
		cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator it = d_list.rbegin(); it; ++it)
	{
		cout << *it << tab;
	}

	List<std::string> s_list = { "Have", "a" ,"nice", "day" };
	for (std::string i : s_list)
		cout << i << tab;
	cout << endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
		cout << *it << tab;
	cout << endl;
	return 0;
}