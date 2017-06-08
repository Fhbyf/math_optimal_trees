#pragma once
#include "stdafx.h"
#include "nodes.h"
#include <vector>

using namespace std;

node* buildPseudoTree(bool, vector<node*>&, vector<node>&, node*);
node* buildPseudoTree_HuTucker(vector<node*>&, vector<node>&, node*);
node* buildPseudoTree_GarsiaWachs(vector<node*>&, vector<node>&, node*);