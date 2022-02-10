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

template<typename T>class ForwardList;	//необходимо объявлять классы перед классом, использующим дружественные функции, чтобы избавиться
template<typename T>class Iterator;		//от множественных ошибок после шаблонизации (так же это нужно сделать перед прототипами если они есть)

template<typename T>
class Element
{
	T Data; //значение элемента 
	Element<T>* pNext; //Адрес следующего элемента
	//Element* - указатель на элемент
	//Element<T>* - указатель на шаблонный элемент
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
size_t Element<T>::count = 0; //инициализируем переменную за классом.

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
		Iterator old = *this;	//Сохраняем старое значение итератора
		Temp = Temp->pNext;		//Изменяем итератор
		return old;				//Возвращаем старое значение
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
class ForwardList //Односвязный (однонаправленный) список
{
	Element<T>* Head; //Голова списка - указывает на начальный элемент списка
	size_t size; //Размер списка
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
		Head = nullptr; //Если голова указывает на 0, то список пуст.
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
			//T() - значение по-умолчанию для шаблонного типа.
		}
		cout << "LConstructor:\t" << this << endl;
	}

	ForwardList(const initializer_list<T>& il) : ForwardList()
	{
		//il.begin() - возвращает итератор на начало контейнера
		//il.end() - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		//const int * - это константный указатель (НЕ изменяется адрес)
		//int const * - это указатель на константу (НЕ изменяется значение по адресу)

		//for (T const* it = il.begin(); it != il.end(); ++it)
		//{
		//	//it - iterator
		//	push_back(*it);
		//}

		for (T const* it = il.end() - 1; it != il.begin() - 1; --it) //<--- Этот вариант быстрее и функциональнее 
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
		while (Head) pop_front(); //Очищаем этот список
		for (Iterator<T> it = other.Head; it; ++it) //проходим по тому списку и вставляем  значения его элементов в этот список.
			push_back(*it);
		cout << "CopyAssignment:\t" << this << endl;
	}
	const T& operator[](const int index)const //операторов квадратные скобки должно быть два вида: 1 позволяет изменять переменные члены класса, а 2й не позволяет.
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
		//Element* New = new Element(Data);//Создаем новфый элемент и помещаем в него значение Data.
		//New->pNext = Head; //Привязываем новый элемент к началу списка
		//Head = New; //Переводим Голову на новый элемент.

		Head = new Element<T>(Data, Head); //оптимизированная версия верхнего варианта.
		++size;
	}

	void push_back(T Data)
	{
		//0) Проверяем, является ли список пустым:
		if (Head == nullptr) return push_front(Data); //оказывается мы можем так писать, если вызываемая функция тоже возвращает void
		//1) Создаем новый элемент
		////Element* New = new Element(Data);
		//2) Доходим до конца списка
		Element<T>* Temp = Head;
		while (Temp->pNext) //Пока, pNext текущего элемента НЕ 0
		{
			Temp = Temp->pNext; //Переходим на следующий элемент
		}
		//Теперь мы находимся в последнем элементе, то есть Temp->pNext == nullptr
		//3) Присоединяем новый элемент к последнему
		////Temp->pNext = New;
		Temp->pNext = new Element<T>(Data); //оптимизированная версия двух строчек кода с двойным комментированием (////)
		++size;
	}

	void insert(int index, T Data)
	{
		if (index == 0 || Head == nullptr) return push_front(Data);
		if (index == 0) return push_front(Data);
		if (index > size) return;
		////Element* New = new Element(Data);
		//1) Доходим до нужного элемента:
		Element<T>* Temp = Head;
		for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;
		//2) Включаем новый элемент в список
		////New->pNext = Temp->pNext;
		////Temp->pNext = New;
		Temp->pNext = new Element<T>(Data, Temp->pNext); //оптимизированная версия трех строчек с двойным комментированием
		++size;
	}
	//			Removing elements:
	void pop_front()
	{
		if (Head == nullptr) return;
		//1) Запоминаем адрес удаляемого элемента
		Element<T>* Erased = Head;
		//2) Исключаем удаляемый элемент из списка
		Head = Erased->pNext; //можно еще Head = Head-pNext;
		//3) Удаляем элемент из памяти
		delete Erased;
		--size;
	}
	void pop_back()
	{
		if (Head == nullptr) return;
		if (Head->pNext == nullptr) return pop_front();
		//1) Доходим до ПРЕДпоследнего элемента
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		//2) Удаляем последний элемент из памяти
		delete Temp->pNext;
		//3) Затираем указатель предпоследнего (теперь последнего) элемента на nulltpr
		Temp->pNext = nullptr;
		--size;
	}

	void erase(int index)
	{
		if (index > size) return;
		if (index == 0) return pop_front();
		//1) Доходим до нужного элемента
		Element<T>* Temp = Head; //Создаем итератор и заходим в список через голову.
		//Теперь в Итераторе адрес головного элемента.
		for (int i = 0; i < index - 1; ++i)
			Temp = Temp->pNext;
		//2) Запоминаем адрес удаляемого элемента
		Element<T>* Erased = Temp->pNext;
		//3) Исключаем элемент из списка:
		Temp->pNext = Temp->pNext->pNext; //или Temp->pNext = Erased->pNext;
		//4) Удаляем элемент из памяти:
		delete Erased;
		--size;
	}

	//			Methods:
	void print()const
	{
#ifdef OLD_PRINT
		Element* Temp = Head; //Temp - это итератор
//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		while (Temp) //Пока итератор содержит ненулевой адрес.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //Переход на следующий элемент 
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

	void unique() //мне не нравится моё решение, оно тяжеловесное, я уверен, что можно было бы это сделать гораздо легче.
	{
		size_t temp_s = 0; //почему-то я его не могу объявить в теле for в качестве еще одной перменной через запятую.
		for (Element<T>* Temp = Head; Temp->pNext; Temp = Temp->pNext, ++temp_s)
		{
			size_t temp_s2 = temp_s + 1;
			for (Element<T>* Temp2 = Temp->pNext; Temp2; Temp2 = Temp2->pNext, ++temp_s2)
			{
				if (Temp->Data == Temp2->Data)
				{
					erase(temp_s2);
					return unique(); //без этого он падает.
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
	//range-based for (for для диапозона)
	for (int i : arr)
	{
		cout << i << tab;
	}
	//Под диапазоном понимается контейнер (массив, список и т.д.)
	//в других языках программирования это называют foreach (для каждого)  
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
	 value последовательно принимает значения всех элементов контейнера
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

//Синтаксис создания объекта:
/*
	Шаблонным называется класс, тип полей которого определяется при создании объекта.
	То есть переменные члены класса могут быть абсолютно любого типа.
	Но при создании объекта обязательно нужно указывать тип его полей.

	Для того, чтобы сделать класс шаблонным перед ним нужно просто создать шаблон
------------------------------------------------------------
	Class object;		// создание объекта обычного класса
	Class<type> object; // создаение объекта шаблонного класса 

	template<typename T>	//После этого любая переменная в классе может быть шаблонного типа.
							//А все методы реализованные внутри класса автоматически становятся шаблонными
------------------------------------------------------------
*/