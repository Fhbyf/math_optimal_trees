#pragma once
#include "stdafx.h"
#include "nodes.h"
#include <stack>
#include <vector>

using namespace std;

bool Move1(stack<node*>&, stack<node*>&, node*, size_t&);
void Move2(stack<node*>&, stack<node*>&, node*, size_t&);
bool Move3(stack<node*>&, stack<node*>&, node*, size_t&);

node* buildTree(vector<node>&, node*);