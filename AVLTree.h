/*---------------------------------------------------------
*    Заголовочный файл, реализиующий шаблонный класс --- Adelson-Velskii Tree  (AVL -- tree)
*       написан Eugenue Meldin(1),Artemii Mikhailov(2), Olga Nosova(3) 01.12.2016
(1) SpbETU, evg-meldin[]ya.ru
(2) SpbETU,
(3) SpbETU,
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
template<typename T> class AVLTree // Объявление шаблонного класса
{
private:
	template<typename T> struct Elem // Структура элемента АВЛ-дерева
	{
		T key;
		Elem<T> * right;
		Elem<T> * left;
		int height;
		Elem(T k) // Создание элемента с ключом (T k).
		{
			key = k;
			right = left = 0;
			height = 1;
		}
	};

public:
	//Текущее дерево = дерево с корнем в root
	Elem<T> * main_root; // Указатель на головное дерево.
	AVLTree() // Конструктор
	{
		main_root = 0; // Обнуление головного указателя, так как дерево ещё отсутствует.
	}
	template<typename T> int height(Elem<T> * root) // Функция, возвращающая высоту текущего дерева.
	{
		return root ? root->height : 0;
	}
	template<typename T> int bfactor(Elem<T> * root) // Функция, возвращающая фактор баланса текущего дерева.
	{
		return height(root->right) - height(root->left);
	}
	template<typename T> int fixheight(Elem<T> * root) // Функция, фиксирующая высоту текущего дерева.
	{
		int rootl = height(root->left);
		int rootr = height(root->right);
		return (rootl > rootr ? rootl : rootr) + 1;
	}
	template<typename T> Elem<T> * rotleft(Elem<T> * root) // Функция левого поворота текущего дерева.
	{
		Elem<T> * q = root->left;
		root->left = q->right;
		q->right = root;
		root->height = fixheight(root);
		q->height = fixheight(q);
		return q;
	}
	template<typename T> Elem<T> * rotright(Elem<T> * root) // Функция правого поворота текущего дерева.
	{
		Elem<T> * q = root->right;
		root->right = q->left;
		q->left = root;
		root->height = fixheight(root);
		q->height = fixheight(q);
		return q;
	}
	template<typename T> Elem<T> * balance(Elem<T> * root) // Функция балансировки текущего дерева.
	{
		cout << "Фактор баланса в текущем дереве --- " << bfactor(root) << endl;
		printTree(root, 0);
		cout << endl;
		if (bfactor(root) == 2) // Если высота левого поддерева текущего корня больше правого на 2.
		{
			cout << "Балансировка требуется." << endl;
			if (bfactor(root->right) < 0)
				root->right = rotleft(root->right);
			return rotright(root);
			cout << "Дерево после балансировки: " << endl;
			printTree(root, 0);
			cout << endl;
		}
		if (bfactor(root) == -2) // Если высота правого поддерева текущего корня больше левого на 2.
		{
			cout << "Балансировка требуется." << endl;
			if (bfactor(root->left) > 0)
				root->left = rotright(root->left);
			return rotleft(root);
		}
		cout << "Балансировка не требуется." << endl;
		return root;
	}
	template<typename T> Elem<T> * insert(Elem<T> * root, T key) // Функция вставки элемента в дерево.
	{
		if (!root) return new Elem<T>(key);
		if (key < root->key) // Ключ меньше
		{
			root->left = insert(root->left, key);
			root->height = fixheight(root);
		}
		else // Ключ больше или равен.
		{
			root->right = insert(root->right, key);
			root->height = fixheight(root);
		}
		return balance(root);
	}
	template<typename T> Elem<T> * findmin(Elem<T> * root) // Поиск минимума в текущем дереве.
	{
		return root->left ? findmin(root->left) : root;
	}
	template<typename T> Elem<T> * removemin(Elem<T> * root) // Удаление минимума в поддереве.
	{
		if (root->left == 0)
			return root->right;
		root->left = removemin(root->left);
		return balance(root);
	}
	template<typename T> Elem<T> * remove(Elem<T> * root, T key) // Удаление элемента с текущим ключом.
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
	template<typename T> void delTree(Elem<T> * root) // Удаление текущего дерева.
	{
		if (root)
		{
			delTree(root->left);
			delTree(root->right);
			delete root;
		}
	}
	template<typename T> void printTree(Elem<T> * root, int lvl) // Вывод "левого дерева" в консоль
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
	template<typename T> void del_ins(Elem<T> * root, T key) // Поиск элемента в дереве: удаление если есть и вставка, если нет.
	{
		if (root)
		{
			Elem<T> * el = findel(root, key);
			if (el)
			{
				cout << "Элемент найден. Удаляем его. " << endl;
				main_root = remove(root, key);
			}
			else
			{
				cout << "Элемент не найден. Вставляем его. " << endl;
				main_root = insert(root, key);
			}
		}
	}
	template<typename T> Elem<T> * findel(Elem<T> * root, T key) // Функция поиска элемента по дереву.
	{
		if (root)
		{
			Elem<T> * el = root;
			if (key < root->key)
			{
				cout << "Текущий корень --- " << root->key << ". [" << key << "] < [" << root->key << "], Движемся по левой ветви." << endl;
				el = findel(root->left, key);
			}
			else
				if (key > root->key)
				{
					cout << "Текущий корень --- " << root->key << ". [" << key << "] > [" << root->key << "],  Движемся по правой ветви." << endl;
					el = findel(root->right, key);
				}
				else
					return el;
			return el;
		}
		else
			return 0;
	}
	template<typename T> bool isEmpty(Elem<T>* root) //Проверка на пустоту текущего дерева
	{
		if (root == 0) return 1; else return 0;
	}
	template <typename T> void paintBT(Elem<T>*main_root) // Отрисовка красивого АВЛ
	{
		int gd = DETECT; //Инициализация графического режима
		int dm = 0;
		initgraph(&dm, &gd, "");

		int maxx = getmaxx();
		int maxy = getmaxy();

		setactivepage(0);
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
			PaintLeafBT(5, maxx - 5, 5, main_root, 50, 'k');
		}
		std::cout << "...............................\n";
	}
	template <typename T>	bool PaintLeafBT(int x1, int x2, int y,Elem<T>* leaf, int level, char f) //Функция отрисовки листа
	{
		if (isEmpty(leaf))
		{
			return false;
		}
		char ch[2] = { 0 };
		int x = (x1 + x2) / 2;
		int i = 0;
		ch[0] = Ttochar(leaf->key);
		moveto(x, y);
		outtext(ch);
		if (PaintLeafBT(x1 - 5, x, y + 20, leaf->left, level - 5, 'l')) //Рисуем левую ветвь
		{
			line(x + 2, y + 15, (x + x1) / 2 + 10, y + 25);
		}
		if (PaintLeafBT(x, x2 + 5, y + 20, leaf->right, level - 5, 'r'))//Рисуем правую ветвь
		{
			line(x + 2, y + 15, (x + x2) / 2 - 2, y + 25);
		}
		return true;
	}
	template <typename T>	char Ttochar(T x) //Функция перевода в символ
{
	int r = x % 10;
	switch (r)
	{
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	default: return '0';
		break;
	}
}
~AVLTree()
{
	delTree(main_root);
}

// Дополнительные функции (если нужно прицеплять готовое решение)
	~AVLTree()
	{
		delTree(main_root);
	}
};
