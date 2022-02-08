//Solution: DataContainers
//Project:: ForwardList
#include <iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
#define DEBUG
//#define POSTFIX_DEBUG

class Element
{
	int Data; //�������� �������� 
	Element* pNext; //����� ���������� ��������
	static size_t count;
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
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

	friend class ForwardList;
	friend class Iterator;
};

size_t Element::count = 0; //�������������� ���������� �� �������.

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
		cout << "It constructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "It destructor:\t" << this << endl;
	}

	Iterator& operator++() //Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int) //Postfix increment
	{
		Iterator old = *this;	//��������� ������ �������� ���������
		Temp = Temp->pNext;		//�������� ��������
		return old;				//���������� ������ ��������
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}

	int& operator*()
	{
		return Temp->Data;
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

class ForwardList //����������� (����������������) ������
{
	Element* Head; //������ ������ - ��������� �� ��������� ������� ������
	size_t size; //������ ������
public:
	Element* getHead()const
	{
		return Head;
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
			push_front(0);
		}
		cout << "LConstructor:\t" << this << endl;
	}

	ForwardList(const initializer_list<int>& il) : ForwardList()
	{
		//il.begin() - ���������� �������� �� ������ ����������
		//il.end() - ���������� �������� �� ����� ����������
		cout << typeid(il.begin()).name() << endl;
		//const int * - ��� ����������� ��������� (�� ���������� �����)
		//int const * - ��� ��������� �� ��������� (�� ���������� �������� �� ������)

		//for (int const* it = il.begin(); it != il.end(); ++it)
		//{
		//	//it - iterator
		//	push_back(*it);
		//}

		for (int const* it = il.end(); it != il.begin() - 1; --it) //<--- ���� ������� ������� � ��������������
		{
			push_front(*it); 
		}

		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Operators:
	const int& operator[](const int index)const //���������� ���������� ������ ������ ���� ��� ����: 1 ��������� �������� ���������� ����� ������, � 2� �� ���������.
	{
		Element* Temp = Head;
		for (int i = 0; i < index; ++i) Temp = Temp->pNext;
		return Temp->Data;
	}

	int& operator[](const int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; ++i) Temp = Temp->pNext;
		return Temp->Data;
	}
	//			Adding elements:

	void push_front(int Data)
	{
		//Element* New = new Element(Data);//������� ������ ������� � �������� � ���� �������� Data.
		//New->pNext = Head; //����������� ����� ������� � ������ ������
		//Head = New; //��������� ������ �� ����� �������.

		Head = new Element(Data, Head); //���������������� ������ �������� ��������.
		++size;
	}

	void push_back(int Data)
	{
		//0) ���������, �������� �� ������ ������:
		if (Head == nullptr) return push_front(Data); //����������� �� ����� ��� ������, ���� ���������� ������� ���� ���������� void
		//1) ������� ����� �������
		////Element* New = new Element(Data);
		//2) ������� �� ����� ������
		Element* Temp = Head;
		while (Temp->pNext) //����, pNext �������� �������� �� 0
		{
			Temp = Temp->pNext; //��������� �� ��������� �������
		}
		//������ �� ��������� � ��������� ��������, �� ���� Temp->pNext == nullptr
		//3) ������������ ����� ������� � ����������
		////Temp->pNext = New;
		Temp->pNext = new Element(Data); //���������������� ������ ���� ������� ���� � ������� ���������������� (////)
		++size;
	}

	void insert(int index, int Data)
	{
		if (index == 0 || Head == nullptr) return push_front(Data);
		if (index == 0) return push_front(Data);
		if (index > size) return;
		////Element* New = new Element(Data);
		//1) ������� �� ������� ��������:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;
		//2) �������� ����� ������� � ������
		////New->pNext = Temp->pNext;
		////Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext); //���������������� ������ ���� ������� � ������� ����������������
		++size;
	}
	//			Removing elements:
	void pop_front()
	{
		if (Head == nullptr) return;
		//1) ���������� ����� ���������� ��������
		Element* Erased = Head;
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
		Element* Temp = Head;
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
		Element* Temp = Head; //������� �������� � ������� � ������ ����� ������.
		//������ � ��������� ����� ��������� ��������.
		for (int i = 0; i < index - 1; ++i)
			Temp = Temp->pNext;
		//2) ���������� ����� ���������� ��������
		Element* Erased = Temp->pNext;
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

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		//for (Element* Temp = Head; Temp; ++Temp)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Count of elements in list:\t" << size << endl;
		cout << "Common count of elements:\t" << Head->count << endl;
	}
};

//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define TO_DO
//#define TO_DO2

#define RANGE_BASED_FOR_ARRAY
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

	ForwardList list = { 3, 5, 8, 13, 21 }; //(ForwardList) = (initializer_list)
	//list.print();
	for (Iterator it = list.getHead(); it != nullptr; ++it)
	{
		cout << *it << tab; 
	}
	cout << endl;

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
	ForwardList list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST


	return 0;
}