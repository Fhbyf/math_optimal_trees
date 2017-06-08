#pragma once
#include "stdafx.h"
#include <vector>
#include "nodes.h"

using namespace std;

vector<node*> makePointersVector(vector<node>& nodes) {
	vector<node*> r;
	for (size_t i = 0; i < nodes.size(); i++)
	{
		r.push_back(&nodes[i]);
	}
	return r;
}

size_t min_node(vector<node*> all, bool orEqual) {
	size_t min = 0;
	for (size_t i = 1; i < all.size(); i++)
	{
		if (orEqual) {
			if (all[i]->weight <= all[min]->weight) min = i;
		}
		else {
			if (all[i]->weight < all[min]->weight) min = i;
		}
	}
	return all[min]->id;
}

void erase(vector<node*>& n, size_t id) {
	n.erase(n.begin() + id);
	for (size_t i = id; i < n.size(); i++)
		--n[i]->id;
}

void incrementLevel(node* a) {
	++(a->level);
	if (a->left) {
		incrementLevel(a->left);
		incrementLevel(a->right);
	}
}

node makeParent(node* a, node* b, bool increment = true) {
	if (increment) {
		incrementLevel(a);
		incrementLevel(b);
	}

	return{ a->id, '\0', (a->weight + b->weight), (a->level - 1), a, b };
}

vector<node*> findAllCompatibles(vector<node*>& arr, size_t curr)
{
	vector<node*> all_compatible;
	for (size_t i = 0; i < arr.size(); i++)
		if (i != curr && isCompatible(arr, curr, i))
		{
			all_compatible.push_back(arr[i]);
		}
	return all_compatible;
}



bool isCompatible(vector<node*> &arr, size_t a, size_t b) {
	if ((a == (b + 1)) || (a == (b - 1)))
		return true;
	if (a > b) swap(a, b);
	for (size_t i = a + 1; i < b; i++)
	{
		if (arr[i]->left == nullptr) return false;
	}
	return true;
}