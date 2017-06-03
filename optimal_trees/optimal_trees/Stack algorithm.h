#pragma once
#include "stdafx.h"
#include "nodes.h"
#include <stack>

using namespace std;

bool Move1(stack<node*> &st, stack<node*> &qu, node* parents, size_t& parents_i);