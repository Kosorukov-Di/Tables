#ifndef __TABLE_STRUCT
#define __TABLE_STRUCT

#include "Polinom.h"
#include <string>
#include <vector>
using namespace std;

class TabNode
{
private:

	string name;
	Polinom* onePolinom;

public:

	TabNode();
	TabNode(const TabNode & );
	TabNode(string , Polinom* );
	
	string GetName() const;
	Polinom* GetPolinom() const;
	
	TabNode& operator=(const TabNode &);
	bool operator==(const TabNode &);

};

///////////////////////////////////////////////////////////////////////////////////////////////////////

TabNode::TabNode() {
	name = "";
	onePolinom = new Polinom();
}

TabNode::TabNode(const TabNode& row){
	name = row.GetName();
	Polinom* pol = row.GetPolinom();
	onePolinom = pol;
}

TabNode::TabNode(string _name, Polinom* _data)
{
	name = _name;
	onePolinom = _data;
}

TabNode& TabNode::operator=(const TabNode& row)
{
	if (this == &row) return *this;
	
	name = row.GetName();
	onePolinom = row.GetPolinom();
	return *this;
}

bool TabNode::operator==(const TabNode& row)
{
	return GetName() == row.GetName();
}

std::string TabNode::GetName() const
{
	return name;
}
Polinom* TabNode::GetPolinom() const
{
	return onePolinom;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////


class Table
{
public:	

	virtual int Find(string)=0;
	virtual void Insert(string, Polinom*)=0;
	virtual void Delete(string)=0;
	virtual Polinom* GetPolinom(string)=0;

};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class SortTable: public Table
{
private:
	int Count;
	int MaxSize;
	TabNode* sortTableData;

	void AddOrderly(string,Polinom *);
	int GetInsertIndex(string);
public:
	SortTable();
	
	int GetCount();
	int GetMaxSize();
	
	bool IsFull();
	void AddMem();
	
	int Find(string);
	void Insert(string,Polinom *);
	void Delete(string);
	Polinom* GetPolinom(string);
	
	TabNode GetTabNode(int);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

SortTable::SortTable()
{
	Count = 0;
	MaxSize = 1;
	sortTableData = new TabNode[MaxSize];
}

int SortTable::GetCount()
{
	return Count;
}
int SortTable::GetMaxSize()
{
	return MaxSize;
}

bool SortTable::IsFull()
{
	return Count == MaxSize;
}

void SortTable::AddMem()
{
	TabNode* tmp = new TabNode[MaxSize*2];
	for (int i = 0; i < MaxSize; i++)
		tmp[i] = sortTableData[i];
	
	delete[] sortTableData;
	MaxSize *=2;
	sortTableData = tmp;
}

int SortTable::GetInsertIndex(string key)
{
	
	int left = -1;                    
	int right = Count;
	int mid;
	while (left < right-1)  
	{            
		mid = (left+right)/2;       
		if (sortTableData[mid].GetName() < key)
			left = mid;
		else
			right = mid;
	}
	return right;
}

void SortTable::AddOrderly(string key, Polinom *pol)
{
	if (Count == 0)
	{
		sortTableData[0] = TabNode(key, pol);
	} 
	else
	{
		int index = GetInsertIndex(key);
		for (int i = Count; i > index; i--)
			sortTableData[i] = sortTableData[i-1];
		
		sortTableData[index] = TabNode(key, pol);
	}
	Count++;
}

int SortTable::Find(string key)
{
	
	int index = GetInsertIndex(key);
	if(sortTableData[index].GetName() == key) return index;
	return -1;
}

void SortTable::Insert(string key, Polinom* pol)
{

	if (Count==MaxSize) AddMem();
	AddOrderly(key, pol);
	
}

void SortTable::Delete(string key)
{
	int index = Find(key);
	if(index==-1) return;
	for (int i = index; i < Count-1; i++)
		sortTableData[i] = sortTableData[i+1];
	
	sortTableData[Count-1] = TabNode("",NULL); 
	Count--;
}

Polinom* SortTable::GetPolinom(string key)
{
	
	int index = Find(key);
	if(index==-1) return NULL;
	return sortTableData[index].GetPolinom();
}

TabNode SortTable::GetTabNode(int pos)
{
	return sortTableData[pos];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

class HashTable: public Table
{
private:
	int MaxSize;
	TabNode* hashTableData;
	
	int GetHash(string);
	
public:
	HashTable();
	HashTable(int);
	
	int GetMaxSize();
	
	int Find(string);
	void Insert(string,Polinom *);
	void Delete(string);
	TabNode GetTabNode(int);
	Polinom* GetPolinom(string);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

HashTable::HashTable()
{
	MaxSize = 10;
	hashTableData = new TabNode[MaxSize];
}

HashTable::HashTable(int _maxSize)
{
	MaxSize = _maxSize;
	hashTableData = new TabNode[MaxSize];
}

int HashTable::GetMaxSize()
{
	return MaxSize;
}

int HashTable::GetHash(string s)
{
	int hash = 0;
	for (int i = 0; i < (int)s.size(); i++)
	{
		hash += s[i]; 
	}
	return hash%MaxSize;
}

int HashTable::Find(string key)
{
	return GetHash(key);
}

void HashTable::Insert(string key, Polinom* pol)
{
	hashTableData[GetHash(key)] = TabNode(key, pol);
}

void HashTable::Delete(string key)
{
	hashTableData[GetHash(key)] = TabNode("",NULL);
}

TabNode HashTable::GetTabNode(int pos)
{
	return hashTableData[pos];
}

Polinom* HashTable::GetPolinom(string key)
{
	return hashTableData[GetHash(key)].GetPolinom();
}

#endif