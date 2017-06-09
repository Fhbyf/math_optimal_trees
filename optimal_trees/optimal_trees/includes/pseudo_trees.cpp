#pragma once
#include "pseudo_trees.h"
#include "nodes.h"
#include <vector>

using namespace std;
node* buildPseudoTree(bool alg, vector<node*>& arr, vector<node>& nodes, node* parents) {
	if (!alg) 
		return buildPseudoTree_HuTucker(arr, nodes, parents);
	else 
		return buildPseudoTree_GarsiaWachs(arr, nodes, parents);
}
node* buildPseudoTree_HuTucker(vector<node*>& arr, vector<node>& nodes, node* parents) {
	size_t were = nodes.size();
	size_t  i, j;
	while (arr.size() - 1)
	{
		for (i = 0; i < arr.size(); i++) //перебор первого члена пары
		{
			vector<node*> compatibleWithI = findAllCompatibles(arr, i);
			j = min_node(compatibleWithI, false);
			vector<node*> compatibleWithJ = findAllCompatibles(arr, j);
			size_t minCompatibleWithJ = min_node(compatibleWithJ, true);

			if ((minCompatibleWithJ == i) && (i != j))
				break;
		}
		parents[were - arr.size()] = makeParent(arr[i], arr[j], true);
		arr[i] = &parents[were - arr.size()];
		erase(arr, j);
	}
	return arr[0];
}

node* buildPseudoTree_GarsiaWachs(vector<node*>& arr, vector<node>& nodes, node* parents) {
	size_t were = nodes.size();
	size_t  i, j;
	while (arr.size() - 1)
	{
		for (i = 0; i < arr.size()-1; i++) //перебор первого члена пары
		{
			vector<node*> compatibleWithI;
			if (i == 0)
				compatibleWithI.push_back(arr[i + 1]);
			else {
				compatibleWithI.push_back(arr[i - 1]);
				compatibleWithI.push_back(arr[i + 1]);
			}
			j = min_node(compatibleWithI, false);
			vector<node*> compatibleWithJ;
			if (j == 0)
				compatibleWithJ.push_back(arr[j + 1]);
			if (j == arr.size() - 1)
				compatibleWithJ.push_back(arr[j - 1]);
			if (j > 0 && j < arr.size() - 1) {
				compatibleWithJ.push_back(arr[j - 1]);
				compatibleWithJ.push_back(arr[j + 1]);
			}
			size_t minCompatibleWithJ = min_node(compatibleWithJ, true);

			if ((minCompatibleWithJ == i) && (i != j))
				break;
		}
		parents[were - arr.size()] = makeParent(arr[i], arr[j], true);
		arr[i] = &parents[were - arr.size()];
		erase(arr, j);
		while (i > 0 && (arr[i - 1]->weight <= arr[i]->weight))
		{
			swap(arr[i - 1], arr[i]);
			--arr[i - 1]->id;
			++arr[i]->id;
			--i;
		}
	}
	return arr[0];
}