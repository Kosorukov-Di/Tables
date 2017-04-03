#include "table.h"

void main()
{
	Polinom P1;

	P1.AddMonom(4,100);
	P1.AddMonom(3,10);
	P1.AddMonom(-2,1);

	Polinom P2;

	P2.AddMonom(2,10);
	P2.AddMonom(-3,4);

	//P.Print();
	//cout<<'='<<P.Exe();

	SortTable st;

	st.Insert("abc", &P1);
	st.Insert("bbb", &P2);

	cout<<st.Find("bbb")<<" pol: ";
	st.GetPolinom("bbb")->Print();

	cout<<'\n';

	HashTable ht;

	ht.Insert("abc", &P1);
	ht.Insert("bbb", &P2);

	cout<<ht.Find("bbb")<<" pol: ";
	ht.GetPolinom("bbb")->Print();
	
	_getch();
}