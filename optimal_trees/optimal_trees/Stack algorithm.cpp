#pragma once
#include "stdafx.h"
#include <iostream>
#include <stack>
#include "Stack algorithm.h"

using namespace std;

node *T;

//комбинируем два элемента в дереве
int add_father(node *&T, size_t w1, size_t w2, int lev, int curr_lev, int max_lev)
{
	if (T->left && !T->right && curr_lev != lev - 1)
		add_father(T->right, w1, w2, lev, curr_lev + 1, max_lev);
	if (T->left && !T->right && curr_lev == lev - 1)
	{
		T = new node;
		T->right = new node;
		T->right->weight = w2;
		T->right->left = NULL;
		T->right->right = NULL;
		T->weight = w1 + w2;
		return T->weight;
	}
	if (T->left && T->right && T->left->weight == w1 && T->right->weight == w2)
	{
		T = new node;
		T->weight = w1 + w2;
		//наверное надо учесть, что w2 может быть не отцом и обнулить его хвост
		return T->weight;
	}
		if (!T->left && curr_lev != lev - 1)
		add_father(T->left, w1, w2, lev, curr_lev + 1, max_lev);
	if (!T && curr_lev == lev - 1)
	{
		T = new node;
		T->left = new node;
		T->left->weight = w1;
		T->left->left = NULL;
		T->left->right = NULL;
		T->right->weight = w2;
		T->right->left = NULL;
		T->right->right = NULL;
		T->weight = w1 + w2;
		return T->weight;
	}
}

void Move2(stack<node> st, stack<node> qu)
{
	st.push(qu.top());
	qu.pop();
	Move1(st, qu);
}

bool Move3(stack<node> &st, stack<node> &qu)
{
	//строим дерево по принципу: два верхних элемента стека st располагаем на соответствующих уровнях
	//делаем что-то похожее на //комбинируем л.м.с.п., первый член ...
	//помещаем отца на уровень детей - 1, делаем связи между ними, очевидно
	int max_lev = 4;
	if (!qu.empty())
	{
		node top1 = st.top();
		st.pop();
		node top2 = st.top();
		st.pop();
		//что с символом делать
		top1.weight = add_father(T, top1.weight, top2.weight, top1.level, 0, max_lev);  //определить max_lev
		top1.level--;
		st.push(top1);
		return 1;
	}
	return 0;
}

bool Move1(stack<node> &st, stack<node> &qu)   //передача по указателю
{
	if (st.size() < 2)
		Move2(st, qu);
	else
	{
		node top1 = st.top();
		st.pop();
		node top2 = st.top();
		if (top1.weight == top2.weight)
			return Move3(st, qu);
		else
		{
			st.push(top1);
			Move2(st, qu);
		}
	}
}

