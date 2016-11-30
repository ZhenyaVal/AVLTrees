/*---------------------------------------------------------
*    ������������ ����, ����������� ��������� ����� --- Adelson-Velskii Tree  (AVL -- tree)
*       �������� Eugenue Meldin(1),Artemii Mikhailov(2), Olga Nosova(3) 03.11.2016
*     ����� � ������������ ��� MyMath
(1) SpbETU, evg-meldin[]ya.ru
(2) SpbETU,
*--------------------------------------------------------*/
#include <iostream>
#pragma once
#include <iostream>
#include <Windows.h>
#include "graphics.h"
#include <cstdio>
#include <cstdlib>
#pragma comment(lib,"openbgi_vc90x.lib")
//setlocale(LC_ALL, "rus");
using namespace std;
template<typename T> class AVLTree // ���������� ���������� ������.
{
private:
	template<typename T> struct Elem // ��������� ��������� ���-���
	{
		T key;
		Elem<T> * right;
		Elem<T> * left;
		int height;
		Elem(T k) // �������� �������� � ������ (T k).
		{
			key = k;
			right = left = 0;
			height = 1;
		}
	};

public:
	Elem<T> * main_root; // ��������� �� �������� ������.
	AVLTree() // �����������
	{
		main_root = 0; // ��������� ��������� ���������, ��� ��� ������ ��� �����������.
	}
	template<typename T> int height(Elem<T> * root) // �������, ������������ ������ �������� ���������.
	{
		return root ? root->height : 0;
	}
	template<typename T> int bfactor(Elem<T> * root) // �������, ������������ ������ ������� �������� ���������.
	{
		return height(root->right) - height(root->left);
	}
	template<typename T> int fixheight(Elem<T> * root) // �������, ����������� ������ �������� ���������.
	{
		int rootl = height(root->left);
		int rootr = height(root->right);
		return (rootl > rootr ? rootl : rootr) + 1;
	}
	template<typename T> Elem<T> * rotleft(Elem<T> * root) // ������� ������� ����� ����� �������� ����� ������ ������ �����.
	{
		Elem<T> * q = root->left;
		root->left = q->right;
		q->right = root;
		root->height = fixheight(root);
		q->height = fixheight(q);
		return q;
	}
	template<typename T> Elem<T> * rotright(Elem<T> * root) // ������� �������� ������ ����� �������� ����� ������ ������ �����.
	{
		Elem<T> * q = root->right;
		root->right = q->left;
		q->left = root;
		root->height = fixheight(root);
		q->height = fixheight(q);
		return q;
	}
	template<typename T> Elem<T> * balance(Elem<T> * root) // �������, ������������� �������� ������.
	{
		cout << "������ ������� � ������� ������ - " << bfactor(root) << endl;
		printTree(root, 0);
		cout << endl;
		if (bfactor(root) == 2) // ���� ������ ������ ��������� �������� ����� ��������� ������ ������� �� 2.
		{
			cout << "��������� ������������." << endl;
			if (bfactor(root->right) < 0)
				root->right = rotleft(root->right);
			return rotright(root);
			cout << "������ ����� ������������: " << endl;
			printTree(root, 0);
			cout << endl;
		}
		if (bfactor(root) == -2) // ���� ������ ������� ��������� �������� ����� ��������� ������ ������ �� 2.
		{
			cout << "��������� ������������." << endl;
			if (bfactor(root->left) > 0)
				root->left = rotright(root->left);
			return rotleft(root);
		}
		cout << "������������ �� ���������." << endl;
		return root;
	}
	template<typename T> Elem<T> * insert(Elem<T> * root, T key) // �������, ����������� ������� � �������� ������ � ������.
	{
		if (!root) return new Elem<T>(key);
		if (key < root->key) // ���� ������
		{
			root->left = insert(root->left, key);
			root->height = fixheight(root);
		}
		else // ���� ������ ��� �����.
		{
			root->right = insert(root->right, key);
			root->height = fixheight(root);
		}
		return balance(root);
	}
	template<typename T> Elem<T> * findmin(Elem<T> * root) // ����� ������������ �������� �������� ������.
	{
		return root->left ? findmin(root->left) : root;
	}
	template<typename T> Elem<T> * removemin(Elem<T> * root) // �������� �� ������ ���. ��������.
	{
		if (root->left == 0)
			return root->right;
		root->left = removemin(root->left);
		return balance(root);
	}
	template<typename T> Elem<T> * remove(Elem<T> * root, T key) // �������� �������� � �������� ������.
	{
		if (!root)
			return 0;
		if (key < root->key)
			root->left = remove(root->left, key);
		else
			if (key > root->key)
				root->right = remove(root->right, key);
			else
			{
				Elem<T> * left = root->left;
				Elem<T> * right = root->right;
				delete root;
				if (!right)
					return left;
				Elem<T> * min = findmin(right);
				min->right = removemin(right);
				min->left = left;
				min->height = fixheight(min);
				return balance(min);
			}
		return balance(root);
	}
	template<typename T> void delTree(Elem<T> * root) // �������� ������.
	{
		if (root)
		{
			delTree(root->left);
			delTree(root->right);
			delete root;
		}
	}
	template<typename T> void printTree(Elem<T> * root, int lvl)
	{
		if (root)
		{
			printTree(root->right, ++lvl);
			for (int i = lvl; i > 0; i--)
				cout << "  ";
			cout << root->key << endl;
			printTree(root->left, lvl);
		}
	}
	template<typename T> void del_ins(Elem<T> * root, T key)
	{
		if (root)
		{
			Elem<T> * el = findel(root, key);
			if (el)
			{
				cout << "�������� ������. ������� ���. " << endl;
				main_root = remove(root, key);
			}
			else
			{
				cout << "������� �� ������. ��������� ���. " << endl;
				main_root = insert(root, key);
			}
		}
	}
	template<typename T> Elem<T> * findel(Elem<T> * root, T key) // ����� �������� �� ������.
	{
		if (root)
		{
			Elem<T> * el = root;
			if (key < root->key)
			{
				cout << "��������������� ������ - " << root->key << ". [" << key << "] < [" << root->key << "], �������� �� ����� �����." << endl;
				el = findel(root->left, key);
			}
			else
				if (key > root->key)
				{
					cout << "��������������� ������ - " << root->key << ". [" << key << "] > [" << root->key << "], �����, �������� �� ������ �����." << endl;
					el = findel(root->right, key);
				}
				else
					return el;
			return el;
		}
		else
			return 0;
	}
	template<typename T> bool isEmpty(Elem<T>* root)
	{
		if (root == 0) return 1; else return 0;
	}
	template <typename T> void paintBT(Elem<T>*main_root)
	{
		int gd = DETECT; //�������������� ��������� ����
		int dm = 0;
		initgraph(&dm, &gd, "");

		int maxx = getmaxx();
		int maxy = getmaxy();

		setactivepage(0);// ������������� ��������? ��������
		setvisualpage(0);

		setcolor(15);
		settextstyle(0, 0, 5);
		std::cout << "\nBynary Tree:\n";

		if (isEmpty(main_root))
		{
			std::cout << "\nForest is Empty\n";
			moveto(100, 100);
			outtext("Binary Tree is empty");
		}
		else
		{
			moveto(0, 0);
			outtext("Binary Tree");
			PaintLeafBT(5, maxx - 5, 5, main_root, 50, 'k'); //������ ������
		}
		std::cout << "...............................\n";
	}
	template <typename T>	bool PaintLeafBT(int x1, int x2, int y,Elem<T>* leaf, int level, char f)
	{
		if (isEmpty(leaf))
		{
			return false;
		}
		//char ch[2] = { 0 };
		char ch[2]={0};
		int x = (x1 + x2) / 2;
		int i = 0;
		ch[0] = leaf->key;
		moveto(x, y);
		outtext(ch);
		if (PaintLeafBT(x1 - 5, x, y + 20, leaf->left, level - 5, 'l')) //������ ���? ����
		{
			line(x + 2, y + 15, (x + x1) / 2 + 10, y + 25);
		}
		if (PaintLeafBT(x, x2 + 5, y + 20, leaf->right, level - 5, 'r'))//������ ����? ����
		{
			line(x + 2, y + 15, (x + x2) / 2 - 2, y + 25);
		}
		return true;
	}
	~AVLTree()
	{
		delTree(main_root);
	}
};
