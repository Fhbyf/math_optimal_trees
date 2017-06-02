#pragma once
#include "stdafx.h"
#include <stack>

using namespace std;

struct node {
	
	size_t id;
	char sign;
	size_t weight, level;
	node* left; 
	node* right;
	node() {
		id = NULL;
		sign = 0;
		weight = 0;
		level = 0;
		left = nullptr;
		right = nullptr;
	}
	node(char s, size_t w, size_t l, node *lt, node *rt) {
		id = NULL;
		sign = s;
		weight = w;
		level = l;
		left = lt;
		right = rt; 
	}
	node(size_t i, char s, size_t w, size_t l, node *lt, node *rt) {
		id = i;
		sign = s;
		weight = w;
		level = l;
		left = lt;
		right = rt;
	}
	node(const node&Ob) {
		id = Ob.id;
		sign = Ob.sign;
		weight = Ob.weight;
		level = Ob.level;
		left = Ob.left;
		right = Ob.right;
	}
};


bool Move1(stack<node> &st, stack<node> &qu);