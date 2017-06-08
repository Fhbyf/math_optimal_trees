#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <iomanip>  
#include <stack>
#include "nodes.h"
#include "Stack algorithm.h"
#include "pseudo_trees.h"

#include <fstream>
#include <map>


using namespace std;

vector<node> buildNodesFromMap(map<char, size_t>);
map<char, string> codeChars(node*);

int main()
{
	setlocale(0, "");
	map<char, size_t> chars;
	int HuTucker_or_GarsiaWachs = 0; // 0 � �������� ���������, 1 � �������� ������ � �����
	string filename, filename_for_code, filename_for_save;
	cout << "������� ��� �����" << endl;
	cin >> filename;
	ifstream in(filename);

	cout << endl << "������������ ����� �� ���������� �����, �������� �������� ��-������� (������� 0) ��� ������ � ����� (������� 1): ";
	cin >> HuTucker_or_GarsiaWachs;
	if (HuTucker_or_GarsiaWachs != 0 && HuTucker_or_GarsiaWachs != 1)
	{
		cout << endl << "������. ������� 0, ����� ��������� �������� ��-�������, ��� 1, ����� ��������� �������� ������ � �����: ";
		cin >> HuTucker_or_GarsiaWachs;
	}

	(bool)HuTucker_or_GarsiaWachs;

	// ������ ���� � �������
	if (!in.is_open())
		cout << "�� �� ������ ������� ����" << endl;
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

	// ��� 1. ������ ������������ ��� �������� �������
	node* parents = new node[nodes.size() - 1];
	node* pseudo_root = buildPseudoTree(HuTucker_or_GarsiaWachs, arr, nodes, parents);

	// ��� 2. �������� ��������
	node* root = buildTree(nodes, parents);
	map<char, string> coded = codeChars(root);


	cout << "�������, ������� ����������� � ������ � �� ����, ���������� � ������� ";
	if (!HuTucker_or_GarsiaWachs)
		cout << "��������� ��-�������\n\n";
	else
		cout << "��������� ������ � �����\n\n";
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

	cout << endl << "������� ��� �����, ���� �������� ����� �����������" << endl;
	cin >> filename_for_code;
	ofstream out(filename_for_code);
	
	for(auto it = coded.begin(); it != coded.end(); it++)
		out << it->first << " " << it->second << endl;
	out.close();

	cout << "������� ��� �����, � ������� ���� ��������� �������������� �����" << endl;
	cin >> filename_for_save;

	ifstream file_in(filename);
	ofstream file_out(filename_for_save);
	if (!file_in.is_open())
		cout << "�� �� ������ ������� ���� ��� ������" << endl;
	if (!file_out.is_open())
		cout << "�� �� ������ ������� ���� ��� ����������" << endl;
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