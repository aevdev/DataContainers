//Solution: DataContainers
//Project:: TemplatedForwardList
#include <iostream>
#include <string>

using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
#define DEBUG
//#define POSTFIX_DEBUG

template<typename T>class ForwardList;	//���������� ��������� ������ ����� �������, ������������ ������������� �������, ����� ����������
template<typename T>class Iterator;		//�� ������������� ������ ����� ������������ (��� �� ��� ����� ������� ����� ����������� ���� ��� ����)

template<typename T>
class Element
{
	T Data; //�������� �������� 
	Element<T>* pNext; //����� ���������� ��������
	//Element* - ��������� �� �������
	//Element<T>* - ��������� �� ��������� �������
	static size_t count;
public:
	Element(T Data, Element<T>* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		++count;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		--count;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}

	friend class ForwardList<T>;
	friend class Iterator<T>;
};

template<typename T>
size_t Element<T>::count = 0; //�������������� ���������� �� �������.

template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) : Temp(Temp)
	{
		cout << "It constructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "It destructor:\t" << this << endl;
	}

	Iterator<T>& operator++() //Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator<T> operator++(int) //Postfix increment
	{
		Iterator old = *this;	//��������� ������ �������� ���������
		Temp = Temp->pNext;		//�������� ��������
		return old;				//���������� ������ ��������
	}
	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}

	const T& operator*()const
	{
		return Temp->Data;
	}

	T& operator*()
	{
		return Temp->Data;
	}

	operator bool()const
	{
		return Temp;
	}

#ifdef POSTFIX_DEBUG
	friend std::ostream& operator<<(std::ostream& os, const Iterator& obj);
#endif // POSTFIX_DEBUG

};

#ifdef POSTFIX_DEBUG
std::ostream& operator<<(std::ostream& os, const Iterator& obj)
{
	return os << obj.Temp;
}
#endif // POSTFIX_DEBUG

template<typename T>
class ForwardList //����������� (����������������) ������
{
	Element<T>* Head; //������ ������ - ��������� �� ��������� ������� ������
	size_t size; //������ ������
public:
	Element<T>* getHead()const
	{
		return Head;
	}

	Iterator<T> begin()
	{
		return Head;
	}

	Iterator<T> end()
	{
		return nullptr;
	}

	ForwardList()
	{
		Head = nullptr; //���� ������ ��������� �� 0, �� ������ ����.
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(size_t size) : ForwardList()
	{
		//this->Head = nullptr;
		//this->size = 0;
		for (int i = 0; i < size; ++i)
		{
			push_front(T());
			//T() - �������� ��-��������� ��� ���������� ����.
		}
		cout << "LConstructor:\t" << this << endl;
	}

	ForwardList(const initializer_list<T>& il) : ForwardList()
	{
		//il.begin() - ���������� �������� �� ������ ����������
		//il.end() - ���������� �������� �� ����� ����������
		cout << typeid(il.begin()).name() << endl;
		//const int * - ��� ����������� ��������� (�� ���������� �����)
		//int const * - ��� ��������� �� ��������� (�� ���������� �������� �� ������)

		//for (T const* it = il.begin(); it != il.end(); ++it)
		//{
		//	//it - iterator
		//	push_back(*it);
		//}

		for (T const* it = il.end() - 1; it != il.begin() - 1; --it) //<--- ���� ������� ������� � �������������� 
		{
			push_front(*it); 
		}

		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList<T>& other) : ForwardList()
	{
		//for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
		//{
		//	push_back(Temp->Data);
		//}
		for (Iterator<T> it = other.Head; it != nullptr; it++)
			push_back(*it);
		cout << "CopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front(); //������� ���� ������
		for (Iterator<T> it = other.Head; it; ++it) //�������� �� ���� ������ � ���������  �������� ��� ��������� � ���� ������.
			push_back(*it);
		cout << "CopyAssignment:\t" << this << endl;
	}
	const T& operator[](const int index)const //���������� ���������� ������ ������ ���� ��� ����: 1 ��������� �������� ���������� ����� ������, � 2� �� ���������.
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; ++i) Temp = Temp->pNext;
		return Temp->Data;
	}

	T& operator[](const int index)
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; ++i) Temp = Temp->pNext;
		return Temp->Data;
	}
	//			Adding elements:

	void push_front(T Data)
	{
		//Element* New = new Element(Data);//������� ������ ������� � �������� � ���� �������� Data.
		//New->pNext = Head; //����������� ����� ������� � ������ ������
		//Head = New; //��������� ������ �� ����� �������.

		Head = new Element<T>(Data, Head); //���������������� ������ �������� ��������.
		++size;
	}

	void push_back(T Data)
	{
		//0) ���������, �������� �� ������ ������:
		if (Head == nullptr) return push_front(Data); //����������� �� ����� ��� ������, ���� ���������� ������� ���� ���������� void
		//1) ������� ����� �������
		////Element* New = new Element(Data);
		//2) ������� �� ����� ������
		Element<T>* Temp = Head;
		while (Temp->pNext) //����, pNext �������� �������� �� 0
		{
			Temp = Temp->pNext; //��������� �� ��������� �������
		}
		//������ �� ��������� � ��������� ��������, �� ���� Temp->pNext == nullptr
		//3) ������������ ����� ������� � ����������
		////Temp->pNext = New;
		Temp->pNext = new Element<T>(Data); //���������������� ������ ���� ������� ���� � ������� ���������������� (////)
		++size;
	}

	void insert(int index, T Data)
	{
		if (index == 0 || Head == nullptr) return push_front(Data);
		if (index == 0) return push_front(Data);
		if (index > size) return;
		////Element* New = new Element(Data);
		//1) ������� �� ������� ��������:
		Element<T>* Temp = Head;
		for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;
		//2) �������� ����� ������� � ������
		////New->pNext = Temp->pNext;
		////Temp->pNext = New;
		Temp->pNext = new Element<T>(Data, Temp->pNext); //���������������� ������ ���� ������� � ������� ����������������
		++size;
	}
	//			Removing elements:
	void pop_front()
	{
		if (Head == nullptr) return;
		//1) ���������� ����� ���������� ��������
		Element<T>* Erased = Head;
		//2) ��������� ��������� ������� �� ������
		Head = Erased->pNext; //����� ��� Head = Head-pNext;
		//3) ������� ������� �� ������
		delete Erased;
		--size;
	}
	void pop_back()
	{
		if (Head == nullptr) return;
		if (Head->pNext == nullptr) return pop_front();
		//1) ������� �� �������������� ��������
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		//2) ������� ��������� ������� �� ������
		delete Temp->pNext;
		//3) �������� ��������� �������������� (������ ����������) �������� �� nulltpr
		Temp->pNext = nullptr;
		--size;
	}

	void erase(int index)
	{
		if (index > size) return;
		if (index == 0) return pop_front();
		//1) ������� �� ������� ��������
		Element<T>* Temp = Head; //������� �������� � ������� � ������ ����� ������.
		//������ � ��������� ����� ��������� ��������.
		for (int i = 0; i < index - 1; ++i)
			Temp = Temp->pNext;
		//2) ���������� ����� ���������� ��������
		Element<T>* Erased = Temp->pNext;
		//3) ��������� ������� �� ������:
		Temp->pNext = Temp->pNext->pNext; //��� Temp->pNext = Erased->pNext;
		//4) ������� ������� �� ������:
		delete Erased;
		--size;
	}

	//			Methods:
	void print()const
	{
#ifdef OLD_PRINT
		Element* Temp = Head; //Temp - ��� ��������
//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������.
		while (Temp) //���� �������� �������� ��������� �����.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //������� �� ��������� ������� 
		}
#endif //OLD_PRINT

		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		//for (Element* Temp = Head; Temp; ++Temp)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Count of elements in list:\t" << size << endl;
		cout << "Common count of elements:\t" << Head->count << endl;
	}
	
	void print_list(const ForwardList<T>& list)
	{
		for (size_t i = 0; i < list.get_size(); ++i)
		{
			cout << list[i] << tab;
		}
		cout << endl;
	}

	void unique() //��� �� �������� �� �������, ��� ������������, � ������, ��� ����� ���� �� ��� ������� ������� �����.
	{
		size_t temp_s = 0; //������-�� � ��� �� ���� �������� � ���� for � �������� ��� ����� ��������� ����� �������.
		for (Element<T>* Temp = Head; Temp->pNext; Temp = Temp->pNext, ++temp_s)
		{
			size_t temp_s2 = temp_s + 1;
			for (Element<T>* Temp2 = Temp->pNext; Temp2; Temp2 = Temp2->pNext, ++temp_s2)
			{
				if (Temp->Data == Temp2->Data)
				{
					erase(temp_s2);
					return unique(); //��� ����� �� ������.
				}
			}
		}
	}

	void reverse()
	{

	}
};

//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define TO_DO
//#define TO_DO2

//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

int main()
{
	int n;
#ifdef BASE_CHECK
	cout << "Enter list size: ";
	cin >> n;
	ForwardList list;
	list.pop_front();
	list.pop_back();
	for (int i = 0; i < n; ++i)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_front();
	//list.print();
	//list.pop_back();
	//list.print();
	int index;
	int value;
	cout << "\nInput INDEX: ";
	cin >> index;
	cout << "\nInput VALUE: ";
	cin >> value;
	list.insert(index, value);
	list.print();

	cout << "\nInput DELETE INDEX: ";
	cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

	//ForwardList list1;
	//list1.push_back(3);
	//list1.push_back(5);
	//list1.push_back(8);
	//list1.push_back(13);
	//list1.push_back(21);
	//list1.print();


	//ForwardList list2;
	//list2.push_back(34);
	//list2.push_back(55);
	//list2.push_back(89);
	//list2.print();


#ifdef DESTRUCTOR_CHECK
	cout << "Input list size: ";
	cin >> n;
	ForwardList list;
	for (int i = 0; i < n; ++i)
		list.push_front(rand());

	cout << "\nList is filled.\n";
#endif // DESTRUCTOR_CHECK


#ifdef TO_DO
	cout << "Input list size: ";
	cin >> n;
	ForwardList list(n);
	for (int i = 0; i < n; ++i)
		list[i] = rand() % 100;
	for (int i = 0; i < n; ++i)
		cout << list[i] << tab;
#endif // TO_DO

#ifdef TO_DO2

	ForwardList<int> list = { 3, 5, 3, 13, 3 }; //(ForwardList) = (initializer_list)
	//list.print();
	for (Iterator<int> it = list.getHead(); it != nullptr; ++it)
	{
		cout << *it << tab; 
	}
	cout << endl;
	list.unique();
	for (Iterator<int> it = list.getHead(); it != nullptr; ++it)
	{
		cout << *it << tab;
	}

#endif // TO_DO2

#ifdef POSTFIX_DEBUG
	Iterator it = list.getHead();
	Iterator it2 = ++it;
	cout << it << endl;
	cout << it2 << endl;
#endif // POSTFIX_DEBUG

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	//range-based for (for ��� ���������)
	for (int i : arr)
	{
		cout << i << tab;
	}
	//��� ���������� ���������� ��������� (������, ������ � �.�.)
	//� ������ ������ ���������������� ��� �������� foreach (��� �������)  
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList<int> list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	//Range-based for
	/*
	 ------------------------------------------------------------
	 for (value : container)
	 {
		cout << value;
	 }
	 value ��������������� ��������� �������� ���� ��������� ����������
	 ------------------------------------------------------------
	*/

	ForwardList<double> d_list = { 2.5, 3.14, 5.2, 8.3 };
	for (double i : d_list)
		cout << i << tab;

	cout << endl;

	ForwardList<string> s_list = { "Have", "a", "nice",  "day." };
	for (string i : s_list)
		cout << i << tab;
	
	//ForwardList<string> s_list2 = s_list; //CopyConstructor
	ForwardList<string> s_list2;
	s_list2 = s_list; //CopyConstructor
	for (string i : s_list2)
		cout << i << tab;
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

	return 0;
}

//��������� �������� �������:
/*
	��������� ���������� �����, ��� ����� �������� ������������ ��� �������� �������.
	�� ���� ���������� ����� ������ ����� ���� ��������� ������ ����.
	�� ��� �������� ������� ����������� ����� ��������� ��� ��� �����.

	��� ����, ����� ������� ����� ��������� ����� ��� ����� ������ ������� ������
------------------------------------------------------------
	Class object;		// �������� ������� �������� ������
	Class<type> object; // ��������� ������� ���������� ������ 

	template<typename T>	//����� ����� ����� ���������� � ������ ����� ���� ���������� ����.
							//� ��� ������ ������������� ������ ������ ������������� ���������� ����������
------------------------------------------------------------
*/