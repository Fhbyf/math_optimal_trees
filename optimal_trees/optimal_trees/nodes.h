#pragma once
#include <vector>

using namespace std;

struct node {

	size_t id;
	char sign;
	size_t weight, level;
	node* left;
	node* right;
	node() {
		id = NULL;
		sign = 0;
		weight = 0;
		level = 0;
		left = nullptr;
		right = nullptr;
	}
	node(size_t i, char s, size_t w) {
		id = i;
		sign = s;
		weight = w;
		level = 0;
		left = nullptr;
		right = nullptr;
	}
	node(char s, size_t w, size_t l, node *lt, node *rt) {
		id = NULL;
		sign = s;
		weight = w;
		level = l;
		left = lt;
		right = rt;
	}
	node(size_t i, char s, size_t w, size_t l, node *lt, node *rt) {
		id = i;
		sign = s;
		weight = w;
		level = l;
		left = lt;
		right = rt;
	}
	node(const node&Ob) {
		id = Ob.id;
		sign = Ob.sign;
		weight = Ob.weight;
		level = Ob.level;
		left = Ob.left;
		right = Ob.right;
	}
};

vector<node*> makePointersVector(vector<node>&);

bool isCompatible(vector<node*>&, size_t, size_t);  //поиск всех своместимых для i-того элемента
vector<node*> findAllCompatibles(vector<node*>&, size_t);
node makeParent(node*, node*, bool);
size_t min_node(vector<node*>, bool);
void erase(vector<node*>&, size_t);