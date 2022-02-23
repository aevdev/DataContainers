#include <iostream>
//#include<string> - это необязательно в 19й студии и далее, поскольку string подтягивается как-то через iostream
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
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List<T>;
	}*Head, *Tail;//вместо этого можно было еще написать
	/*
	Element* Head;
	Element* Tail;
	*/
	size_t size;

	class BaseIterator
	{
	protected: //открываем прямой доступ к переменной Temp из дочерних классов
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr) : Temp(Temp)
		{
#ifdef DEBUG
			cout << "BItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~BaseIterator()
		{
#ifdef DEBUG
			cout << "BItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		virtual BaseIterator& operator++() = 0;
		//virtual BaseIterator operator++(int) = 0;
		virtual BaseIterator& operator--() = 0;
		//virtual BaseIterator operator--(int) = 0;

		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const T& operator*()const
		{
			return Temp->Data;
		}
		operator bool()const
		{
			return Temp;
		}
	};

public: //alt + стрелка вверх/вниз позволяет перемещать строку.
	class ConstIterator :public BaseIterator 
	{
	public:
		ConstIterator(Element* Temp = nullptr) : BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CItConstrutor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "CItDestructor:\t" << this << endl;
#endif // DEBUG

		}

		ConstIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		} 
		ConstIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator : public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) : BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RCItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "RCItDestructor:\t" << this << endl;
#endif // DEBUG

 		}
		ConstReverseIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}
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
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		T& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};

	ConstIterator cbegin()const //const begin
	{
		return Head;
	}
	ConstIterator cend()const //const end
	{
		return nullptr;
	}
	ConstReverseIterator crbegin()const //const reverse begin
	{
		return Tail;
	}
	ConstReverseIterator crend()const //const reverse end
	{
		return nullptr;
	}
	Iterator begin() //const begin
	{
		return Head;
	}
	Iterator end() //const end
	{
		return nullptr;
	}
	ReverseIterator rbegin() //const reverse begin
	{
		return Tail;
	}
	ReverseIterator rend() //const reverse end
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const initializer_list<T>& il) : List()
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
	~List()
	{
		//while(Head) pop_front();
		while(Head) pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//Adding elements:
	void push_front(T Data)
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

	void push_back(T Data)
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

	void insert(int index, T Data)
	{
		if (index > size) return;
		if (index == 0) return push_front(Data);
		if (index ==  size) return push_back(Data);
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
		//Неважно, с какой стороны мы добрались до нужного элемента,
		//процедура добавления нового элемента будет идентичной.
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
	void pop_front()
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

	void pop_back()
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
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Count of elements in list: " << size << endl;
	}

	void reverse_print()const
	{
		for(Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Count of elements in list: " << size << endl;
	}			
};


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