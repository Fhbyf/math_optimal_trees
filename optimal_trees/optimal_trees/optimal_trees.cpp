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

bool isCompatible(array<node, 11>, size_t, size_t);  //поиск всех своместимых для i-того элемента
array<node, 11> findAllCompatibles(array<node, 11>, size_t, size_t);

int main()
{
	array<node, 11> arr = { {
		{ 'a',8,0,0,0 },
		{ 'b',6,0,0,0 },
		{ 'c',2,0,0,0 },
		{ 'd',3,0,0,0 },
		{ 'e',4,0,0,0 },
		{ 'f',7,0,0,0 },
		{ 'g',11,0,0,0 },
		{ 'h',9,0,0,0 },
		{ 'j',8,0,0,0 },
		{ 'k',1,0,0,0 },
		{ 'l',3,0,0,0 }
	} };

	
	array<node, 11>  curr_arr = arr; //бля, че он не ругается

	size_t curr_size = curr_arr.size(); //кажется так надо, но это неточно 
									  //(если можно корректно для curr_arr.size уменьшить длину массива, то не надо)
	///////////ШАГ 1/////////////
	// ищем локально минимальную совместимую пару (A, B)
	size_t A = 0, B = 0;
	while (curr_arr.size())
	{

		for (size_t i = A; i < curr_size; i++) //перебор первого члена пары
		{
			array<node, 11> all_compatible;
			size_t k = 0;
			for (size_t j = 0; j < curr_size; j++) //перевод второго члена пары
			{
				if (i == j) continue;
				all_compatible = findAllCompatibles(curr_arr, i, curr_size);  //первая часть первого условия л.м.с.п.
				for (k = 0; k < all_compatible.size(); k++)  //вторая часть первого условия л.м.с.п.
					if (!(all_compatible[k].weight > curr_arr[j].weight))
						break;
				if (k == all_compatible.size())
				{
					all_compatible = { 0 };  //хз как обнулит
					all_compatible = findAllCompatibles(curr_arr, j, curr_size);  //первая часть второго условия л.м.с.п.
					for (k = 0; k < all_compatible.size(); k++)   //вторая часть второго условия л.м.с.п.
						if (!(all_compatible[k].weight >= curr_arr[i].weight))
							break;
					if (k == all_compatible.size())   //все условия выполнены, пара найдена
					{
						B = j;
						break;
					}
				}
				/*if (isCompatible(arr, i, j)) {
					all_compatible[k] = arr[j];
					++k;
				}*/
			}
			if (k == all_compatible.size()) //возможно как-то можно прервать два цикла сразу
			{
				A = i;
				break;
			}
		}


		//комбинируем л.м.с.п., первый член заменятся отцом, второй идёт нахуй
		curr_arr[A].weight += curr_arr[B].weight; //что при этом делать с символами
		curr_arr[A].level = max(curr_arr[A].level, curr_arr[B].level) + 1;
		//тут надо изменить уровень у соответствующих элементов из arr
		for (size_t i = B; i < curr_size - 1; i++)
			swap(curr_arr[i], curr_arr[i + 1]);
		curr_size--;

	}
	//ну и весь шаг надо зациклить пока в curr_arr не останется один элемент

	////////////ШАГ 2///////////////////
	// стековый алгоритм
	stack<node> st;  //обнулить наверное
	stack<node> qu;
	for (int i = 10; i < 0; i--)  //инициализация стека по имени очередь
		qu.push(arr[i]);
	
	while (Move1(st, qu));   //трабл с передачей по указателю
		
    return 0;
}

array<node, 11> findAllCompatibles(array<node,11> arr, size_t curr, size_t size)
{   
	array<node, 11> all_compatible;
	size_t k = 0;
	for (size_t i = 0; i < size; i++)
		if (i != curr && isCompatible(arr, curr, i))
		{
			all_compatible[k] = arr[i];
			k++;
		}
	return all_compatible;  //хз как правильно передать
}



bool isCompatible(array<node, 11> arr, size_t a, size_t b) {
	if ((a == (b + 1)) || (a == (b - 1)))
		return true;
	if (a > b) swap(a, b);
	for (size_t i = a + 1; i < b; i++)
	{
		if (!arr[i].level) return false;
	}
	return true;
}

