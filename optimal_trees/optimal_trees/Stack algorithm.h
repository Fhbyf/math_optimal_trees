#pragma once

using namespace std;

struct node {
	char sign;
	int weight, level;
	node *left, *right;
};

node *T;

bool Move1(stack<node> &st, stack<node> &qu);