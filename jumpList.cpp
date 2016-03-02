#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

class node
{
public:
	node* son;
	node* bro;
	node* dad;
	int value;
	int level;
	int maxLevel;

	node(int value, int level, node* son = NULL, node* bro = NULL, node* dad = NULL)
	{
		this->value = value;
		this->level = level;
		this->son = son;
		this->bro = bro;
	}
	node(){}

};

class jumpList:public node
{
	node* root;
	int maxLvlOfList;
	jumpList()
	{
	}
	jumpList(int maxLvlOfList)
	{
		this->maxLvlOfList = maxLvlOfList;
		root = NULL;
	}

	bool isEmpty()
	{
		if(root == NULL) return true;
		return false;
	}

	void add(int value)
	{
		if(isEmpty())
		{
			root = new node(value, maxLvlOfList);
		}
		else
		{

		}
	}

	bool search(int value, node* temp)
	{
		node* ptr = temp;
		while(ptr->son != NULL)
		{
			ptr = ptr->son;
			
		}
	}

};

int main()
{

	return 0;
}
