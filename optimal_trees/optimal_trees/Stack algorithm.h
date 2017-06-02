#pragma once
#include "stdafx.h"
#include <stack>
#include <vector>

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

struct t_nodes {
	size_t size;
	vector<node*> nodes;
	//t_nodes() {
	//	size = 0;
	//	*nodes = { {0,0,0,0,0} };
	//}
	//t_nodes(size_t a, vector<node>* b) {
	//	size = a;
	//	nodes = b;
	//}
	//t_nodes(t_nodes & h) {
	//	size = h.size;
	//	nodes = h.nodes;
	//}
};


bool Move1(stack<node> &st, stack<node> &qu);