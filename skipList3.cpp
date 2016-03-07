#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

class node
{
public:
	node* up;
	node* front;
	node* down;
	node* back;

	int value;
	int level;
	int maxLevel;

	node(int value, int level, int maxLevel, node* back = NULL, node* front = NULL, node* down = NULL, node* up = NULL)
	{
		this->value = value;
		this->level = level;
		this->maxLevel = maxLevel;

		this->up = up;
		this->front = front;
		this->down = down;
		this->back = back;
	}
	node() {}

};

class jumpList :public node
{
public:
	node* root;
	int maxLvlOfList;
	jumpList()
	{
	}
	jumpList(int maxLvlOfList)
	{
		this->maxLvlOfList = maxLvlOfList;
		root = new node(0, 1, maxLvlOfList);
	}

	bool isEmpty()
	{
		if (root->front == NULL) return true;
		return false;
	}

	int randomLevel(int maxLvl)
	{
		int random = 1;
		int flag = false;
		while (((rand() % 2)==1) && flag != true)
		{
			if (random == maxLvl-1)
				flag = 1;
			random++;
		}
		return random;
	}

	void add(int value)
	{
		if (isEmpty())
		{
 			int temp = randomLevel(maxLvlOfList);
			
			root->front = new node(value, 1, temp);
			node* ptr = root->front;
			for (int i = 1; i < temp; i++)
			{
				ptr->up = new node(value, i, temp);
				ptr->up->down = ptr;
				ptr = ptr->up;
			}
		}
		else
		{
			node* ptr = searchWhereToAdd(value, root);
			if (ptr->front != NULL)
			{
				int temp = randomLevel(maxLvlOfList);
				while (ptr->down != NULL)
				{
					ptr = ptr->down;
				}
				for (int i = 1; i <= temp; i++)
				{
					if (i > 1)
					{
						node* ptr2 = ptr;
						node* ptr3 = ptr;
						if (ptr->up == NULL)
						{
							node* ptrBackup = ptr;
							while (ptr!= NULL && ptr->maxLevel < i)
							{
								ptr = ptr->back;
							}
							if(ptr != NULL)
								ptr = ptr->up;
							while (ptr2->value != value)
							{
								ptr2 = ptr2->front;
							}
							while (ptr2->level < i-1)
								ptr2 = ptr2->up;
							node* ptr3Backup = ptr3;
							while (ptr3 != NULL && (ptr3->maxLevel < i && ptr3->value != value))
							{
								ptr3 = ptr3->front;
							}
							if (ptr3 != NULL)
								ptr3 = ptr3->up;
							ptr2->up = new node(value, i, temp, ptr, ptr3, ptr2);
							if (ptr != NULL && ptr3 != NULL)
							{
								ptr->front = ptr2->up;
								ptr3->back = ptr2->up;
							}
							else
								if (ptr != NULL && ptr3 == NULL)
								{
									ptr->front = ptr2->up;
									ptr3 = ptr3Backup;
								}
								else
									if (ptr == NULL && ptr3 != NULL)
									{
										ptr3->back = ptr2->up;
										ptr = ptrBackup;
									}
									else
									{
										ptr = ptrBackup;
										ptr3 = ptr3Backup;
									}
						}
						else
						{
							ptr = ptr->up;
							while (ptr2->value != value)
							{
								ptr2 = ptr2->front;
							}
							while (ptr2->level < i - 1)
								ptr2 = ptr2->up;
							node* ptr3Backup = ptr3;
							while (ptr3 != NULL && ptr3->maxLevel < i)
							{
								ptr3 = ptr3->front;
							}
							if(ptr3 != NULL)
								ptr3 = ptr3->up;
							ptr2->up = new node(value, i, temp, ptr, ptr3, ptr2);
							ptr->front = ptr2->up;
							if (ptr3 == NULL)
								ptr3 = ptr3Backup;
							else
								ptr3->back = ptr2->up;
						}
					}
					else
					{
						ptr->front->back = new node(value, i, temp, ptr, ptr->front);
						ptr->front = ptr->front->back;
					}
				}
			}
			else
			{
				int temp = randomLevel(maxLvlOfList);
				while (ptr->down != NULL)
				{
					ptr = ptr->down;
				}
				for (int i = 1; i <= temp; i++)
				{
					if (i > 1)
					{
						node* ptr2 = ptr;
						if (ptr->up == NULL)
						{
							node* ptrBackup = ptr;
							while (ptr != NULL && ptr->maxLevel < i)
							{
								ptr = ptr->back;
							}
							if(ptr != NULL)
								ptr = ptr->up;
							while (ptr2->value != value)
							{
								ptr2 = ptr2->front;
							}
							while (ptr2->level < i - 1)
								ptr2 = ptr2->up;
							ptr2->up = new node(value, i, temp, ptr, NULL, ptr2);
							if (ptr != NULL)
							{
								ptr->front = ptr2->up;
							}
							else ptr = ptrBackup;
						}
						else
						{
							ptr = ptr->up;
							while (ptr2->value != value)
							{
								ptr2 = ptr2->front;
							}
							while (ptr2->level < i - 1)
								ptr2 = ptr2->up;
							ptr2->up = new node(value, i, temp, ptr, NULL, ptr2);
							ptr->front = ptr2->up;
						}
					}
					else
					{
						ptr->front = new node(value, i, temp, ptr);
					}
				}
			}
					
		}
	}

	node* searchWhereToAdd(int value, node* temp, bool flag = false) // recursif
	{
		node* ptr = temp;
		if (flag != true)
		{
			while (ptr->up != NULL)
			{
				ptr = ptr->up;
			}
		}
		if (ptr->front != NULL && ptr->front->value < value)
		{
			searchWhereToAdd(value, ptr->front, true);
		}
		else
		{
			if (ptr->down != NULL)
				searchWhereToAdd(value, ptr->down, true);
		return ptr;
		}
	}
	bool search(int value, node* temp, bool flag = false) // recursif
	{
		node* ptr = temp;
		while (ptr->up != NULL || flag != true)
		{
			ptr = ptr->up;

		}
		if (ptr->value == value)
			return true;
		else
		{

			if ((ptr->down != NULL) || (ptr->value < ptr->front->value))
				search(value, ptr->down, true);
			else
			{
				if ((ptr->front != NULL) || (ptr->value > ptr->front->value))
					search(value, ptr->front);
			}
			return false;
		}

	}

	void print(node* ptr)
	{
		node* ptr2 = ptr;
		for (int i = maxLvlOfList; i > 0; i--)
		{
			while (ptr != NULL)
			{
				node* ptr3;
				while (ptr != NULL && ptr->maxLevel < i)
				{
					ptr = ptr->front;
					cout << "\t";
				}
				if (ptr!=NULL && ptr->front != NULL)
				{
					  ptr3 = ptr->front;
				}
				else ptr3 = NULL;
				
				if (ptr != NULL)
				{
					for (int j = i; j > 1; j--)
					{
						ptr = ptr->up;
					}
					cout << ptr->value << "\t";
				}
				ptr = ptr3;
			}
			cout << endl;
			ptr = ptr2;
		}
	}

};

int main()
{
	int val;
	srand(time(NULL));
	jumpList a(3);
	fstream file; 
	file.open("input.txt");
	while (file >> val)
	{
		a.add(val);
	}
	a.print(a.root->front);

	return 0;
}
