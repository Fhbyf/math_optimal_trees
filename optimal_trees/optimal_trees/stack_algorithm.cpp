#pragma once
#include <iostream>
#include <stack>
#include "nodes.h"
#include "stack_algorithm.h"

using namespace std;

void Move2(stack<node*> &st, stack<node*> &qu, node*parents, size_t& parents_i)
{
	st.push(qu.top());
	qu.pop();
	Move1(st, qu, parents, parents_i);
}

bool Move3(stack<node*> &st, stack<node*> &qu, node*parents, size_t& parents_i)
{
	//строим дерево по принципу: два верхних элемента стека st располагаем на соответствующих уровнях
	//помещаем отца на уровень детей - 1, делаем связи между ними, очевидно
	node* top1 = st.top();
	st.pop();
	node* top2 = st.top();
	st.pop();
	parents[parents_i] = makeParent(top2, top1, false);
	st.push(&parents[parents_i]);
	++parents_i;
	if (st.top()->level) return 1;
	return 0;
}

bool Move1(stack<node*> &st, stack<node*> &qu, node*parents, size_t& parents_i)
{
	if (st.size() < 2)
		Move2(st, qu, parents, parents_i);
	else
	{
		node* top1 = st.top();
		st.pop();
		node* top2 = st.top();
		st.push(top1);
		if (top1->level == top2->level)
			return Move3(st, qu, parents, parents_i);
		else
			Move2(st, qu, parents, parents_i);
	}
}

node* buildTree(vector<node>& nodes, node* parents) {
	stack<node*> st;
	stack<node*> qu;
	for (int i = nodes.size() - 1; i >= 0; i--)  //инициализация стека по имени очередь
		qu.push(&nodes[i]);
	size_t parents_i = 0;
	while (Move1(st, qu, parents, parents_i));
	return st.top();
}