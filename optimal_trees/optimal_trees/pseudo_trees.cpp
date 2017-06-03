#pragma once
#include "stdafx.h"
#include "pseudo_trees.h"
#include "nodes.h"
#include <vector>

using namespace std;
node* buildPseudoTree(bool alg, t_nodes& arr, vector<node>& nodes, node * parents) {
	if (!alg) 
		return buildPseudoTree_HuTucker(arr, nodes, parents);
	else 
		return buildPseudoTree_GarsiaWachs(arr, nodes, parents);
}
node* buildPseudoTree_HuTucker(t_nodes& arr, vector<node>& nodes, node * parents) {
	size_t were = nodes.size();
	size_t  i, j;
	while (arr.size - 1)
	{
		for (i = 0; i < arr.size; i++) //перебор первого члена пары
		{
			vector<node*> compatibleWithI = findAllCompatibles(arr, i);
			j = min_node(compatibleWithI, false);
			vector<node*> compatibleWithJ = findAllCompatibles(arr, j);
			size_t minCompatibleWithJ = min_node(compatibleWithJ, true);

			if ((minCompatibleWithJ == i) && (i != j))
				break;
		}
		parents[were - arr.size] = makeParent(arr.nodes[i], arr.nodes[j], true);
		arr.nodes[i] = &parents[were - arr.size];
		erase(arr, j);
	}
	return arr.nodes[0];
}

node* buildPseudoTree_GarsiaWachs(t_nodes& arr, vector<node>& nodes, node * parents) {
	size_t were = nodes.size();
	size_t  i, j;
	while (arr.size - 1)
	{
		for (i = 0; i < arr.size-1; i++) //перебор первого члена пары
		{
			vector<node*> compatibleWithI;
			if (i == 0)
				compatibleWithI.push_back(arr.nodes[i + 1]);
			else {
				compatibleWithI.push_back(arr.nodes[i - 1]);
				compatibleWithI.push_back(arr.nodes[i + 1]);
			}
			j = min_node(compatibleWithI, false);
			vector<node*> compatibleWithJ;
			if (j == 0)
				compatibleWithJ.push_back(arr.nodes[j + 1]);
			if (j == arr.size - 1)
				compatibleWithJ.push_back(arr.nodes[j - 1]);
			if (j > 0 && j < arr.size - 1) {
				compatibleWithJ.push_back(arr.nodes[j - 1]);
				compatibleWithJ.push_back(arr.nodes[j + 1]);
			}
			size_t minCompatibleWithJ = min_node(compatibleWithJ, true);

			if ((minCompatibleWithJ == i) && (i != j))
				break;
		}
		parents[were - arr.size] = makeParent(arr.nodes[i], arr.nodes[j], true);
		arr.nodes[i] = &parents[were - arr.size];
		erase(arr, j);
		while (i > 0 && (arr.nodes[i - 1]->weight <= arr.nodes[i]->weight))
		{
			swap(arr.nodes[i - 1], arr.nodes[i]);
			--arr.nodes[i - 1]->id;
			++arr.nodes[i]->id;
			--i;
		}
	}
	return arr.nodes[0];
}