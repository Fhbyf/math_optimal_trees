#pragma once
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <array>
#include <queue>
#include <stack>
#include "Stack algorithm.h"

//node *T;

using namespace std;

bool isCompatible(vector<node>, size_t, size_t);  //поиск всех своместимых для i-того элемента
vector<node> findAllCompatibles(vector<node>&, size_t);
node makeParent(node*, node*);
size_t min_node(vector<node>,bool);
void erase(vector<node>*, size_t);

int main()
{
	vector<node> arr = { {
		{ 0, 'a', 8, 0, 0, 0 },
		{ 1, 'b', 6, 0, 0, 0 },
		{ 2, 'c', 2, 0, 0, 0 },
		{ 3, 'd', 3, 0, 0, 0 },
		{ 4, 'e', 4, 0, 0, 0 },
		{ 5, 'f', 7, 0, 0, 0 },
		{ 6, 'g', 11, 0, 0, 0 },
		{ 7, 'h', 9, 0, 0, 0 },
		{ 8, 'j', 8, 0, 0, 0 },
		{ 9, 'k', 1, 0, 0, 0 },
		{ 10, 'l', 3 ,0 ,0 ,0 }
	} };

	node * root_first_tree = NULL;
	
	///////////ШАГ 1/////////////
	// ищем локально минимальную совместимую пару (A, B)
	size_t  i, j;
	size_t size = arr.size();
	while (size - 1)
	{
		for (i = 0; i < size; i++) //перебор первого члена пары
		{
			// фиксируем i-тый

			// первая часть первого условия л.м.с.п.
			// ищем все совместимые с i-тым
			vector<node> compatibleWithI = findAllCompatibles(arr, i);
			j = min_node(compatibleWithI,false);
			vector<node> compatibleWithJ = findAllCompatibles(arr, j);
			size_t minCompatibleWithJ = min_node(compatibleWithJ,true);

			if ((minCompatibleWithJ == i) && (i != j)) 
				goto all_found;
				//break; break;		
		}
		all_found:
		//комбинируем л.м.с.п., первый член заменятся отцом, второй уходит
		//если корень пустой, кладем отца в корень
		node a = arr[i];
		node b = arr[j];
		arr[i] = makeParent(&a, &b);
		erase(&arr, j);
		size--;
	}
	//ну и весь шаг надо зациклить пока в arr не останется один элемент

	// дальше хуета

	////////////ШАГ 2///////////////////
	// стековый алгоритм
	stack<node> st;  
	stack<node> qu;
	for (int i = 10; i < 0; i--)  //инициализация стека по имени очередь
		qu.push(arr[i]);
	
	while (Move1(st, qu));   //трабл с передачей по указателю
		
    return 0;
}

size_t min_node(vector<node> all, bool orEqual) {
	size_t min = 0;
	for (size_t i = 1; i < all.size(); i++)
	{
		if (orEqual) {
			if (all[i].weight <= all[min].weight) min = i;
		}
		else {
			if (all[i].weight < all[min].weight) min = i;
		}
	}
	return all[min].id;
}

void erase(vector<node> *nodes, size_t id) {
	/*node rght = *(*nodes)[id - 1].right;   //костылиииииии
	nodes->erase(nodes->begin() + id);
	(*nodes)[id - 1].right = &rght;*/

	for (size_t i = id; i < nodes->size() - 1; i++)
	{
		swap((*nodes)[i], (*nodes)[i + 1]);
		--(*nodes)[i].id;           //что делать с id детей?
	}
}

void incrementLevel(node *a) {
	++(a->level);
	if (a->left) {
		incrementLevel(a->left);
		incrementLevel(a->right);
	}
}

node makeParent(node *a, node *b) {
	incrementLevel(a);
	incrementLevel(b);
	/*node c;
	c.id = a->id;
	c.sign = '\0';
	c.weight = (a->weight + b->weight);
	c.level = 0;
	c.left = a;
	c.right = b;
	node * zh = &c;
	return c;*/
	return { a->id, '\0', (a->weight+b->weight), 0, a, b };
}

vector<node> findAllCompatibles(vector<node> &arr, size_t curr)
{   
	vector<node> all_compatible;
	for (size_t i = 0; i < arr.size(); i++)
		if (i != curr && isCompatible(arr, curr, i))
		{
			all_compatible.push_back(arr[i]);
		}
	return all_compatible;  
}



bool isCompatible(vector<node> arr, size_t a, size_t b) {
	if ((a == (b + 1)) || (a == (b - 1)))
		return true;
	if (a > b) swap(a, b);
	for (size_t i = a + 1; i < b; i++)
	{
		if (arr[i].left==nullptr) return false;
	}
	return true;
}

