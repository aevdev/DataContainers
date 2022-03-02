#include <iostream>
//#include<string> - это необ€зательно в 19й студии и далее, поскольку string подт€гиваетс€ как-то через iostream
#define tab '\t'
using namespace std;
using std::cin;
using std::cout;
using std::endl;

template<typename T>
class List
{
	class Element
	{
		T Data; //значение элемента
		Element* pNext; //адрес следующего элемента.
		Element* pPrev; //адрес предыдущего элемента.
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, *Tail;//вместо этого можно было еще написать
	/*
	Element* Head;
	Element* Tail;
	*/
	size_t size;

	class BaseIterator
	{
	protected: //открываем пр€мой доступ к переменной Temp из дочерних классов
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr);
		~BaseIterator();
		virtual BaseIterator& operator++() = 0;
		//virtual BaseIterator operator++(int) = 0;
		virtual BaseIterator& operator--() = 0;
		//virtual BaseIterator operator--(int) = 0;

		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;
		const T& operator*()const;
		operator bool()const;
	};

public: //alt + стрелка вверх/вниз позвол€ет перемещать строку.
	class ConstIterator :public BaseIterator 
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator : public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : ConstIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		T& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};

	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();
		T& operator*();
	};

	//Shift + стрелка дл€ выделени€ построчно
	ConstIterator cbegin()const;
	ConstIterator cend()const; 
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;

	Iterator begin();
	Iterator end();

	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const initializer_list<T>& il);
	~List();

	//Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(int index, T Data);

	//				Removing elements:
	void pop_front();

	void pop_back();

	//			Methods:
	void print()const;

	void reverse_print()const;
};

template<typename T>
List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) : Data(Data), pNext(pNext), pPrev(pPrev)
{
	cout << "EConstructor:\t" << this << endl;
}
template<typename T>
List<T>::Element::~Element()
{
	cout << "EDestructor:\t" << this << endl;
}

template<typename T>
List<T>::BaseIterator::BaseIterator(Element* Temp) : Temp(Temp)
{
#ifdef DEBUG
	cout << "BItConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>
List<T>::BaseIterator::~BaseIterator()
{
#ifdef DEBUG
	cout << "BItDestructor:\t" << this << endl;
#endif // DEBUG

}

template<typename T>
bool List<T>::BaseIterator::operator==(const List<T>::BaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>
bool List<T>::BaseIterator::operator!=(const BaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>
const T& List<T>::BaseIterator::operator*()const
{
	return Temp->Data;
}
template<typename T>
List<T>::BaseIterator::operator bool()const
{
	return Temp;
}

template<typename T>
List<T>::ConstIterator::ConstIterator(Element* Temp) : BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "CItConstrutor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>
List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "CItDestructor:\t" << this << endl;
#endif // DEBUG

}

template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}
template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}
template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}

template<typename T>
List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) : BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RCItConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>
List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RCItDestructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>
typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>
typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}
template<typename T>
typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}
template<typename T>
typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}

template<typename T>
List<T>::ReverseIterator::ReverseIterator(Element* Temp) : ConstReverseIterator(Temp) //элементы по-умолчанию могут быть заданы только в прототипе функции Element* Temp = nullptr
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>
List<T>::ReverseIterator::~ReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>
T& List<T>::ReverseIterator::operator*()
{
	return BaseIterator::Temp->Data;
}

template<typename T>
typename List<T>::ConstIterator List<T>::cbegin()const //const begin //typename - таким образом мы показываем, что это тип данных, а не им€ метода
{
	return Head;
}
template<typename T>
typename List<T>::ConstIterator List<T>::cend()const //const end
{
	return nullptr;
}
template<typename T>
typename List<T>::ConstReverseIterator List<T>::crbegin()const //const reverse begin
{
	return Tail;
}
template<typename T>
typename List<T>::ConstReverseIterator List<T>::crend()const //const reverse end
{
	return nullptr;
}
template<typename T>
typename List<T>::Iterator List<T>::begin() //const begin
{
	return Head;
}
template<typename T>
typename List<T>::Iterator List<T>::end() //const end
{
	return nullptr;
}
template<typename T>
typename List<T>::ReverseIterator List<T>::rbegin() //const reverse begin
{
	return Tail;
}
template<typename T>
typename List<T>::ReverseIterator List<T>::rend() //const reverse end
{
	return nullptr;
}

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}

template<typename T>List<T>::List(const initializer_list<T>& il) : List()
{
	//const int* p; - константный указатель
	//int const* p; - указатель на конастанту
	// const int const* p; - константный указатель на константу
	//it - iterator
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}
}

template<typename T>List<T>::~List()
{
	//while(Head) pop_front();
	while (Head) pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//Adding elements:
template<typename T>
void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		++size;
		return;
	}
	/*
	Element* New = new Element(Data);
	New->pNext = Head;
	Head->pPrev = New;
	Head = New;
	*/
	Head = Head->pPrev = new Element(Data, Head);
	++size;
}

template<typename T>
void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		++size;
		return;
	}
	/*
	Element* New = new Element(Data);
	New->pPrev = Tail;
	Tail->pNext = New;
	Tail = New;
	*/
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	++size;
}

template<typename T>
void List<T>::insert(int index, T Data)
{
	if (index > size) return;
	if (index == 0) return push_front(Data);
	if (index == size) return push_back(Data);
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; ++i)
			Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - index - 1; ++i)
			Temp = Temp->pPrev;
	}
	//Ќеважно, с какой стороны мы добрались до нужного элемента,
	//процедура добавлени€ нового элемента будет идентичной.
	/*
	Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;
	*/
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	++size;
}

//				Removing elements:
template<typename T>
void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)
		return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		--size;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	--size;
}

template<typename T>
void List<T>::pop_back()
{
	if (Head == nullptr && Tail == nullptr)
		return;
	if (Head == Tail)
		return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	--size;
}

//			Methods:
template<typename T>
void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Count of elements in list: " << size << endl;
}

template<typename T>
void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Count of elements in list: " << size << endl;
}

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