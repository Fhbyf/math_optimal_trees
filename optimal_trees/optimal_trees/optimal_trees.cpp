#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <iomanip>  
#include <stack>

#include "includes/nodes.h"
#include "includes/stack_algorithm.h"
#include "includes/pseudo_trees.h"

#include <fstream>
#include <map>


using namespace std;

vector<node> buildNodesFromMap(map<char, size_t>);
map<char, string> codeChars(node*);

int main()
{
	setlocale(0, "");
	map<char, size_t> chars;
	short int HuTucker_or_GarsiaWachs = 0; // 0 — алгоритм Ху—Таккера, 1 — алгоритм Гарсия и Уочса
	string filename, filename_for_code, filename_for_save;
	cout << "Введите имя файла" << endl;
	cin >> filename;
	ifstream in(filename);

	cout << endl << "Закодировать текст из выбранного файла, применив алгоритм Ху-Таккера (нажмите 0) или Гарсия и Уочса (нажмите 1): ";
	cin >> HuTucker_or_GarsiaWachs;
	if (HuTucker_or_GarsiaWachs != 0 && HuTucker_or_GarsiaWachs != 1)
	{
		cout << endl << "Ошибка. Нажмите 0, чтобы применить алгоритм Ху-Таккера, или 1, чтобы применить алгоритм Гарсия и Уочса: ";
		cin >> HuTucker_or_GarsiaWachs;
	}


	// читаем файл с текстом
	if (!in.is_open()) {
		cout << "Мы не смогли открыть файл" << endl;
		system("pause");
		return 0;
	}
		
	system("cls");

	while (!in.eof())
	{
		char c;
		in.get(c);
		if (!in.eof())
			++chars[c];
	}
	in.close();

	vector<node> nodes = buildNodesFromMap(chars);
	vector<node*> arr = makePointersVector(nodes);

	// ШАГ 1. Строим псевдодерево для рассчёта уровней
	node* parents = new node[nodes.size() - 1];
	node* pseudo_root = buildPseudoTree((bool)HuTucker_or_GarsiaWachs, arr, nodes, parents);

	// ШАГ 2. Стековый алгоритм
	node* root = buildTree(nodes, parents);
	map<char, string> coded = codeChars(root);


	cout << "Символы, которые встречаются в тексте и их коды, полученные с помощью ";
	if (!HuTucker_or_GarsiaWachs)
		cout << "алгоритма Ху-Таккера\n\n";
	else
		cout << "алгоритма Гарсиа и Уочса\n\n";
	for (auto it = coded.begin(); it != coded.end(); it++)
	{
		char sym = it->first;
		switch (sym)
		{
		case ' ':
			cout << "\" \" ";
			break;
		case '\t':
			cout << "\\" << "t  ";
			break;
		case '\n':
			cout << "\\" << "n  ";
			break;
		case '\r':
			cout << "\\" << "r  ";
			break;
		case '\v':
			cout << "\\" << "v  ";
			break;
		default:
			cout << sym << "   ";
			break;
		}
		cout << it->second << endl;
	}

	cout << endl << "Введите имя файла, куда записать ключи кодирования" << endl;
	cin >> filename_for_code;
	ofstream out(filename_for_code);
	
	for(auto it = coded.begin(); it != coded.end(); it++)
		out << it->first << " " << it->second << endl;
	out.close();

	cout << "Введите имя файла, в который надо сохранить закодированный текст" << endl;
	cin >> filename_for_save;

	ifstream file_in(filename);
	ofstream file_out(filename_for_save);
	if (!file_in.is_open())
		cout << "Мы не смогли открыть файл для чтения" << endl;
	if (!file_out.is_open())
		cout << "Мы не смогли открыть файл для сохранения" << endl;
	while (!file_in.eof())
	{
		char sym = file_in.get();
		file_out << coded[sym];
	}
	file_in.close();
	file_out.close();
	system("Pause");
    return 0;
}


void codeChar(node* curr, map<char, string>& codedChars, string route) {
	
	if (curr->left) {
		string route_left = route;
		string route_right = route;
		route_left.push_back('0');
		route_right.push_back('1');
		codeChar(curr->left, codedChars, route_left);
		codeChar(curr->right, codedChars, route_right);
	} else
		codedChars[curr->sign] = route;
}

map<char, string> codeChars(node* curr) {
	map<char, string> codedChars;
	string route_left = "0";
	string route_right = "1";
	codeChar(curr->left, codedChars, route_left);
	codeChar(curr->right, codedChars, route_right);
	return codedChars;
}

vector<node> buildNodesFromMap(map<char, size_t> chars) {
	vector<node> r;
	auto it = chars.begin();
	size_t i = 0;
	for (auto it = chars.begin(); it != chars.end(); ++it, ++i) {
		r.push_back({ i, it->first, it->second });
	}
	return r;
}