#pragma once
#include "stdafx.h"
#include "nodes.h"
#include <vector>

using namespace std;

node* buildPseudoTree(bool,t_nodes&, vector<node>&, node*);
node* buildPseudoTree_HuTucker(t_nodes&, vector<node>&, node*);
node* buildPseudoTree_GarsiaWachs(t_nodes&, vector<node>&, node*);