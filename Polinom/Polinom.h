#ifndef __POLINOM_STRUCT
#define __POLINOM_STRUCT

#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

struct monom{
	monom *next;// ��������� �� ��������� �����
	int coeff;	// ����������
	int st;		// ������� xyz
	
	monom(int _coeff=0, int _st=0, monom* next_=0)
	{
		coeff=_coeff;
		st=_st;
		next=next_;
	} 
	
	monom(monom *b)
	{
		coeff=b->coeff;
		st=b->st;
		next = 0;
	}
};

class Polinom {
private:
	monom *head;// ��������� �� ������ �����

public:
	
	Polinom();								// �����������
	Polinom(const Polinom &b);				// ����������� �����������
	~Polinom();								// ����������

	bool empty();							// ������? ���� ��?
	void Del();								// �������
	void const Print();							// �����
	
	monom* getHead() {return head; }
	
	void AddMonom(int _coeff, int _st);		// �������� �����

	int Exe();								// ��������� � ������
	int Exe(int x,int y,int z);				// ���������

	Polinom &operator=(const Polinom &b); 		// �����
	Polinom const operator+(const Polinom &b);		// ����
	Polinom const operator-(const Polinom &b);		// �����
	Polinom operator+=(const Polinom &b);		// ���������
	Polinom operator-=(const Polinom &b);		// ����������
	Polinom const operator*(const monom *m);	// �������� ������� �� �����
	Polinom const operator*(Polinom &b);	// (����������) �������� ������� �� �������
};

Polinom::Polinom()
{
	head = new monom();
	if(!head) throw "���������� ����� ��������!";
}

Polinom::Polinom(const Polinom &b)
{
	head = new monom(); // ������� ������
	head->coeff = b.head->coeff; // ����������� ����������� ����� ������ (��������� ����) ���������� ���������
	monom *tempThis = head;
	monom *temp = b.head->next;
	while(temp) // ���� �������� �� ��������� ������ ��� �������
	{
		tempThis->next = new monom(temp->coeff,temp->st,0);
		tempThis = tempThis->next;
		temp = temp->next;
	}
}

Polinom::~Polinom() 
{
	monom* temp;
	while(head) 
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

bool Polinom::empty()
{
	return ((head->coeff==0)&&(head->next==0));
}

void Polinom::Del()
{
	monom* temp;
	while(head) // ������� � ������
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	head = new monom();
}

void const Polinom::Print()
{
	cout<<head->coeff;
	monom *temp = head->next;
	while(temp)
	{
		// ????? ???
		int x = temp->st/100;
		int y = (temp->st/10)%10;
		int z = temp->st%10;
		cout<<'+'<<temp->coeff<<'*'<<"x^"<<x<<"y^"<<y<<"z^"<<z;
		temp = temp->next;
	}
	cout<<'\n';
}

void Polinom::AddMonom(int _coeff, int _st)
{
	if(_coeff) // ����� ���-�� ������ ���� �� ����
	{
		if(_st) // ���� ������� �� 0
		{
			monom *temp = head;
			monom *tempNext = head->next;
			while(tempNext && (tempNext->st < _st)) // ������ ���� ���� ���� � ���� ������� ������ ������ ������� ������, ������� ����� ��������
			{
				temp = tempNext;
				tempNext = tempNext->next;
			}
			
			if(tempNext && (tempNext->st == _st)) // ���� ������� ����� - ����� �������
			{
				tempNext->coeff += _coeff;
				if(tempNext->coeff == 0) // ���� �� ���� ����� - ����������
				{
					temp->next = tempNext->next;
					delete tempNext;
				}
			} else { // �������� ��������� �����
				temp->next = new monom(_coeff, _st, tempNext);
				if(!temp->next) throw "�� ����������!";
			}
			
		} else { // ������ ��������� ���� - ����� ������� � ������
			head->coeff += _coeff;
		}
	}
}

int Polinom::Exe(int x,int y = 0,int z = 0)
{
	monom *temp = head;
	int res = 0;
	while(temp)
	{
		int _x = 1, _y = 1, _z = 1;
		
		// ????? ???
		int st_x = (temp->st)/100;
		int st_y = ((temp->st)/10)%10;
		int st_z = (temp->st)%10;
		
		for(int i=0; i<st_x; i++) _x*=x;
		for(int i=0; i<st_y; i++) _y*=y;
		for(int i=0; i<st_z; i++) _z*=z;
		
		res+=(temp->coeff)*_x*_y*_z;
		temp = temp->next;
	}
	return res;
}

int Polinom::Exe()
{
	int x, y, z;
	cout<<"Enter x="; cin>>x;
	cout<<"Enter y="; cin>>y;
	cout<<"Enter z="; cin>>z;
	return Exe(x,y,z);
}

Polinom &Polinom::operator=(const Polinom &b)
{
	if(this!=&b)
	{
		Del(); // ������� ����
		head->coeff = b.head->coeff; // ����������� ����������� ����� ������ (��������� ����) ���������� ���������
		monom *tempThis = head;
		monom *temp = b.head->next;
		while(temp)  // ���� �������� �� ��������� ������ ��� �������
		{
			tempThis->next = new monom(temp->coeff,temp->st,0);
			tempThis = tempThis->next;
			temp = temp->next;
		}
	}
	return *this;
}

/*
Polinom const Polinom::operator+(const Polinom &b)
{
	Polinom res = *this; // ������� �������������� �������
	monom *temp = b.head; // �������� � ������ ������� ��������
	while(temp) // ���� ������ ������� �� �������� ��������������� ������ � ��������������� ��������
	{
		res.AddMonom(temp->coeff,temp->st);
		temp = temp->next;
	}
	return res; // ���������� ���������
}

Polinom const Polinom::operator-(const Polinom &b)
{
	Polinom res=*this;
	monom *temp = b.head;
	while(temp)
	{
		res.AddMonom(-(temp->coeff),temp->st);
		temp = temp->next;
	}
	return res;
}
*/

Polinom const Polinom::operator+(const Polinom &b)
{
	Polinom res;
	monom *tempr = res.head;
	monom *tempa = head->next;
	monom *tempb = b.head->next;

	res.head->coeff = head->coeff+b.head->coeff;

	while(tempa && tempb) {
		if((tempb->st)>(tempa->st)) {
			tempr->next = new monom(tempa); 
			tempa = tempa->next;
			tempr = tempr->next;
		}
		else {
			if((tempb->st)<(tempa->st)) {
			tempr->next = new monom(tempb);
			tempb = tempb->next;
			tempr = tempr->next;
			} else {
				int c = tempa->coeff+tempb->coeff;
				if(c!=0) {
					tempr->next = new monom(c, tempa->st, 0);
					tempr = tempr->next;
				}
				tempa = tempa->next;
				tempb = tempb->next;
			}
		}
		
	}
	while(tempb) {
		tempr->next = new monom(tempb);
		tempb = tempb->next;
		tempr = tempr->next;
	}
	while(tempa) {
		tempr->next = new monom(tempa);
		tempa = tempa->next;
		tempr = tempr->next;
	}


	return res;
}

Polinom const Polinom::operator-(const Polinom &b)
{
	Polinom res;
	monom *tempr = res.head;
	monom *tempa = head->next;
	monom *tempb = b.head->next;

	res.head->coeff = head->coeff-b.head->coeff;

	while(tempa && tempb) {
		if((tempb->st)>(tempa->st)) {
			tempr->next = new monom(tempa); 
			tempa = tempa->next;
			tempr = tempr->next;
		}
		else {
			if((tempb->st)<(tempa->st)) {
			tempr->next = new monom(-tempb->coeff, tempb->st, 0);
			tempb = tempb->next;
			tempr = tempr->next;
			} else {
				int c = tempa->coeff-tempb->coeff;
				if(c!=0) {
					tempr->next = new monom(c, tempa->st, 0);
					tempr = tempr->next;
				}
				tempa = tempa->next;
				tempb = tempb->next;
			}
		}
		
	}
	while(tempb) {
		tempr->next = new monom(-tempb->coeff, tempb->st, 0);
		tempb = tempb->next;
		tempr = tempr->next;
	}
	while(tempa) {
		tempr->next = new monom(tempa->coeff, tempa->st, 0);
		tempa = tempa->next;
		tempr = tempr->next;
	}

	return res;
}

Polinom Polinom::operator+=(const Polinom &b)
{
	// �� �� ����� ��� � � + ������ ��������� ����
	monom *temp = b.head;
	while(temp)
	{
		AddMonom(temp->coeff,temp->st);
		temp = temp->next;
	}
	return *this;
}

Polinom Polinom::operator-=(const Polinom &b)
{
	monom *temp = b.head;
	while(temp)
	{
		AddMonom(-(temp->coeff),temp->st);
		temp = temp->next;
	}
	return *this;
}

Polinom const Polinom::operator*(const monom *m)
{
	Polinom res = *this; // ������� �������������� �������
	monom *temp = res.head; // �������� � ������ ����������
	while(temp) // ���� ������� �� �������� ����������� ���������� � ������� ������� ������� ������ ������ �� ���������� � ������� ������ m
	{
		temp->coeff *= m->coeff;
		temp->st += m->st;
		temp = temp->next;
	}
	return res; // ���������� ���������
}

Polinom const Polinom::operator*(Polinom &b)
{
	Polinom res; // ������� �������������� �������
	monom *m = head; // �������� �� ����� ������
	while(m) // ���� ������� �� �������� ������ ���� ����� �������� �� ������ ������� � ������� � ����������
	{
		res += b*m;
		m = m->next;
	}
	return res; // ���������� ���������
}

#endif