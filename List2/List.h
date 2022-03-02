#pragma once
#include <iostream>
//#include<string> - ��� ������������� � 19� ������ � �����, ��������� string ������������� ���-�� ����� iostream
#define tab '\t'
using namespace std;
using std::cin;
using std::cout;
using std::endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////					���������� ������ - CLASSS DECLARATION			   //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class List
{
	class Element
	{
		T Data; //�������� ��������
		Element* pNext; //����� ���������� ��������.
		Element* pPrev; //����� ����������� ��������.
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail;//������ ����� ����� ���� ��� ��������
	/*
	Element* Head;
	Element* Tail;
	*/
	size_t size;

	class BaseIterator
	{
	protected: //��������� ������ ������ � ���������� Temp �� �������� �������
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

public: //alt + ������� �����/���� ��������� ���������� ������.
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

	//Shift + ������� ��� ��������� ���������
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