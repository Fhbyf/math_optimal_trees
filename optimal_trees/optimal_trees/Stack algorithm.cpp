#pragma once
#include "stdafx.h"
#include <iostream>
#include <stack>
#include "nodes.h"
#include "Stack algorithm.h"

using namespace std;

void Move2(stack<node*> &st, stack<node*> &qu, node*parents, size_t& parents_i, size_t max_level)
{
	st.push(qu.top());
	qu.pop();
	Move1(st, qu, parents, parents_i, max_level);
}

bool Move3(stack<node*> &st, stack<node*> &qu, node*parents, size_t& parents_i, size_t max_level)
{
	//строим дерево по принципу: два верхних элемента стека st располагаем на соответствующих уровнях
	//делаем что-то похожее на //комбинируем л.м.с.п., первый член ...
	//помещаем отца на уровень детей - 1, делаем связи между ними, очевидно
	
	//{
		node* top1 = st.top();
		st.pop();
		node* top2 = st.top();
		st.pop();
		//что с символом делать
		parents[parents_i] = makeParent(top2, top1, false);
		st.push(&parents[parents_i]);
		++parents_i;
		if (st.top()->level) return 1;
	//}
	return 0;
}

bool Move1(stack<node*> &st, stack<node*> &qu, node*parents, size_t& parents_i, size_t max_level)
{
	if (st.size() < 2)
		Move2(st, qu, parents, parents_i, max_level);
	else
	{
		node* top1 = st.top();
		st.pop();
		node* top2 = st.top();
		st.push(top1);
		if (top1->level == top2->level)
			return Move3(st, qu, parents, parents_i, max_level);
		else
			Move2(st, qu, parents, parents_i, max_level);
	}
}

node* buildTree(vector<node>& nodes, node* parents) {
	stack<node*> st;
	stack<node*> qu;
	size_t max_level = 0;
	for (int i = nodes.size() - 1; i >= 0; i--)  //инициализация стека по имени очередь
	{
		if (nodes[i].level > max_level)
			max_level = nodes[i].level;
		qu.push(&nodes[i]);
	}
	size_t parents_i = 0;
	while (Move1(st, qu, parents, parents_i, max_level));
	return st.top();
}