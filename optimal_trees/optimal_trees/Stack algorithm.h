#pragma once
#include "stdafx.h"
#include "nodes.h"
#include <stack>
#include <vector>

using namespace std;

bool Move1(stack<node*> &st, stack<node*> &qu, node* parents, size_t& parents_i, size_t max_level);
node* buildTree(vector<node>&, node*);