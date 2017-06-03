#pragma once
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include "Stack algorithm.h"
#include "nodes.h"

using namespace std;

int main()
{
	
	vector<node> nodes = { {
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
	vector<node*> pointers = { {
			&nodes[0],
			&nodes[1],
			&nodes[2],
			&nodes[3],
			&nodes[4],
			&nodes[5],
			&nodes[6],
			&nodes[7],
			&nodes[8],
			&nodes[9],
			&nodes[10]
		} };
	t_nodes arr = { nodes.size(), pointers };
	size_t max_parents = nodes.size() - 1;
	node * parents = new node[max_parents];
	size_t were = nodes.size();
	///////////ШАГ 1/////////////
	// ищем локально минимальную совместимую пару (A, B)
	size_t  i, j;
	while (arr.size - 1)
	{
		for (i = 0; i < arr.size; i++) //перебор первого члена пары
		{
			// фиксируем i-тый

			// первая часть первого условия л.м.с.п.
			// ищем все совместимые с i-тым
			vector<node*> compatibleWithI = findAllCompatibles(arr, i);
			j = min_node(compatibleWithI,false);
			vector<node*> compatibleWithJ = findAllCompatibles(arr, j);
			size_t minCompatibleWithJ = min_node(compatibleWithJ,true);

			if ((minCompatibleWithJ == i) && (i != j)) 
				goto all_found;
				//break; break;		
		}
		all_found:
		//комбинируем л.м.с.п., первый член заменятся отцом, второй уходит
		//если корень пустой, кладем отца в корень
		//node a = arr.nodes[i];
		//node b = arr.nodes[j];
		
		//arr.nodes.push_back(arr.nodes[i]);
		parents[were - arr.size] = makeParent(arr.nodes[i], arr.nodes[j], true);
		arr.nodes[i] = &parents[were - arr.size];
		erase(arr, j);
		
	}
	//ну и весь шаг надо зациклить пока в arr не останется один элемент

	// дальше хуета

	////////////ШАГ 2///////////////////
	// стековый алгоритм
	stack<node*> st;
	stack<node*> qu;
	for (int i = nodes.size()-1; i >= 0; i--)  //инициализация стека по имени очередь
		qu.push(&nodes[i]);
	size_t parents_i = 0;
	while (Move1(st, qu, parents, parents_i));
    return 0;
}
