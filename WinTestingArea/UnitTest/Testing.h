#pragma once
#include <iostream>
#include <tkexception.h>

/* ---- TK LIBRARY ---- */
#include <tkObjectPool.h>
#include <tkLinkedList.h>
#include <tkHashMap.h>
#include <tkHashTable.h>
#include <tkTree.h>
/* ---- STD LIBRARY ---- */
#include <vector>

class Testing {
public:
	Testing();
	~Testing();
	

private:
	void ObjectPoolTesting();
	void LinkedListTesting();
	void HashTableTesting();
	void HashMapTesting();
	void TreeTesting();

	/* ---- TK LIBRARY ---- */
	tk::std::LinkedList<int> m_tkLinkedList;
	tk::std::ObjectPool<int> m_tkObjectPool;
	tk::std::HashTable<int> m_tkHashTable;
	tk::std::HashMap<int> m_tkHashMap;
	tk::std::Tree<int> m_tkTree;

	/* ---- STD LIBRARY ---- */
	std::vector<int> m_stdLinkedList;
};
