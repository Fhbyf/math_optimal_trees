#pragma once
#include "stdafx.h"
#include <stack>

using namespace std;

struct node {
	char sign;
	int weight, level;
	node *left, *right;
};


bool Move1(stack<node> &st, stack<node> &qu);