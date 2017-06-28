#include "Testing.h"

Testing::Testing() {
	// Start testing the LinkedLists
	LinkedListTesting();
	// Start testing the HashMap
	HashMapTesting();
	// Start testing the HashTable
	HashTableTesting();
	// Start testing the Tree
	TreeTesting();
	// Start testing the ObjectPool
	ObjectPoolTesting();

	std::cout << "############ All Passed ############\n";
}
Testing::~Testing() {}

void Testing::LinkedListTesting() {
	std::cout << "############ Started Linked List ############\n";
	m_tkLinkedList.push_back(1);
	std::cout << "Linked List :: Added 1\n";
	m_tkLinkedList.push_back(2);
	std::cout << "Linked List :: Added 2\n";
	m_tkLinkedList.push_back(3);
	std::cout << "Linked List :: Added 3\n\n";

	m_stdLinkedList.push_back(1);
	m_stdLinkedList.push_back(2);
	m_stdLinkedList.push_back(3);

	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");
	
	m_tkLinkedList.print();
	std::cout << "\nLinked List :: Passed\n";

	m_tkLinkedList.erase(1);
	m_stdLinkedList.erase(m_stdLinkedList.begin() + 1);
	
	std::cout << "Linked List :: Deleted at pos 1\n\n";

	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");

	m_tkLinkedList.print();
	std::cout << "\nLinked List :: Passed\n";

	m_tkLinkedList.insert(m_tkLinkedList.find_n(m_tkLinkedList.front() + 1), 2);
	m_tkLinkedList.insert(m_tkLinkedList.find_n(m_tkLinkedList.front()), 0);
	m_stdLinkedList.insert(m_stdLinkedList.begin() + 1, 2);
	m_stdLinkedList.insert(m_stdLinkedList.begin(), 0);

	std::cout << "Linked List :: Added 2 at pos 1\n";
	std::cout << "Linked List :: Added 0 at pos 0\n\n";

	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");

	m_tkLinkedList.print();
	std::cout << "\nLinked List :: Passed\n";

	tk::std::LinkedList<int> m_tkLinkedList_temp;
	m_tkLinkedList_temp.push_back(3);
	m_tkLinkedList_temp.push_back(2);
	m_tkLinkedList_temp.push_back(1);
	m_tkLinkedList_temp.push_back(0);
	m_tkLinkedList = m_tkLinkedList_temp;

	m_stdLinkedList.clear();
	m_stdLinkedList.push_back(3);
	m_stdLinkedList.push_back(2);
	m_stdLinkedList.push_back(1);
	m_stdLinkedList.push_back(0);

	std::cout << "Linked List :: Copyed new {3, 2, 1, 0}\n\n";

	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");

	m_tkLinkedList.print();
	std::cout << "\nLinked List :: Passed\n";

	std::cout << "############ Passed Linked List ############\n\n";
}

void Testing::HashTableTesting() {
	std::cout << "############ Started Hash Table ############\n";

	m_tkHashTable.SetSize(3);
	m_tkHashTable.add("Five", 5);
	std::cout << "Hash Table :: Added {'Five', 5}\n";
	m_tkHashTable.add("Six", 6);
	std::cout << "Hash Table :: Added {'Six', 6}\n";
	m_tkHashTable.add("Seven", 7);
	std::cout << "Hash Table :: Added {'Seven', 7}\n";

	if (m_tkHashTable.get("Five") == nullptr) TK_EXCEPTION("Failed Adding {'Five', 5}");
	if (m_tkHashTable.get("Six") == nullptr) TK_EXCEPTION("Failed Adding {'Six', 6}");
	if (m_tkHashTable.get("Seven") == nullptr) TK_EXCEPTION("Failed Adding {'Seven', 7}");

	std::cout << "\nV: " << *m_tkHashTable.get("Five") << " K: " << TK_HASH("Five") << " || ";
	std::cout << "V: " << *m_tkHashTable.get("Six") << " K: " << TK_HASH("Six") << " || ";
	std::cout << "V: " << *m_tkHashTable.get("Seven") << " K: " << TK_HASH("Seven") << "\n\n";

	std::cout << "Hash Table :: Removing {'Six'}\n";
	m_tkHashTable.remove("Six");

	if (m_tkHashTable.get("Six") != nullptr) TK_EXCEPTION("Failed Removing {'Six', 6}");

	std::cout << "\nV: " << *m_tkHashTable.get("Five") << " K: " << TK_HASH("Five") << " || ";
	std::cout << "V: " << *m_tkHashTable.get("Seven") << " K: " << TK_HASH("Seven") << "\n\n";

	std::cout << "Hash Table :: Added {'Six', nullptr}\n";
	m_tkHashTable.add("Six", nullptr);

	if (m_tkHashTable.get("Six") != nullptr) TK_EXCEPTION("Failed Removing {'Six', 6}");

	std::cout << "\nV: " << *m_tkHashTable.get("Five") << " K: " << TK_HASH("Five") << " || ";
	std::cout << "V: 0x" << m_tkHashTable.get("Six") << " K: " << TK_HASH("Six") << " || ";
	std::cout << "V: " << *m_tkHashTable.get("Seven") << " K: " << TK_HASH("Seven") << "\n\n";

	std::cout << "Hash Table :: Printing {'Foo'}\n";
	std::cout << "\nV: 0x" << m_tkHashTable.get("Foo") << " K: " << TK_HASH("Foo") << "\n\n";

	std::cout << "Hash Table :: Clearing Hash Table\n";
	m_tkHashTable.clear();

	if (m_tkHashTable.get("Five") != nullptr) TK_EXCEPTION("Failed Adding {'Five', 5}");
	if (m_tkHashTable.get("Six") != nullptr) TK_EXCEPTION("Failed Adding {'Six', 6}");
	if (m_tkHashTable.get("Seven") != nullptr) TK_EXCEPTION("Failed Adding {'Seven', 7}");

	std::cout << "\nV: 0x" << m_tkHashTable.get("Five") << " K: " << TK_HASH("Five") << " || ";
	std::cout << "V: 0x" << m_tkHashTable.get("Six") << " K: " << TK_HASH("Six") << " || ";
	std::cout << "V: 0x" << m_tkHashTable.get("Seven") << " K: " << TK_HASH("Seven") << "\n\n";

	std::cout << "############ Passed Hash Table ############\n\n";
}

void Testing::HashMapTesting() {
	std::cout << "############ Started Hash Map ############\n";

	m_tkHashMap.Add("One", 1);
	std::cout << "Hash Map :: Added {'One', 1}\n";
	m_tkHashMap.Add("Two", 2);
	std::cout << "Hash Map :: Added {'Two', 2}\n";
	m_tkHashMap.Add("Three", 3);
	std::cout << "Hash Map :: Added {'Three', 3}\n\n";

	if (m_tkHashMap.Get("One") != 1) TK_EXCEPTION("Failed Adding One");
	if (m_tkHashMap.Get("Two") != 2) TK_EXCEPTION("Failed Adding Two");
	if (m_tkHashMap.Get("Three") != 3) TK_EXCEPTION("Failed Adding Three");

	m_tkHashMap.print();
	std::cout << "\nHash Map :: Passed\n";

	m_tkHashMap.Remove("Two");

	std::cout << "Hash Map :: Removed {'Two', 2}\n\n";

	m_tkHashMap.print();
	std::cout << "\nHash Map :: Passed\n";

	std::cout << "############ Passed Hash Map ############\n\n";
}

void Testing::TreeTesting() {
	std::cout << "############ Started AA Tree ############\n";

	m_tkTree.Insert(1);
	std::cout << "Tree :: Added 1\n";
	m_tkTree.Insert(2);
	std::cout << "Tree :: Added 2\n";
	m_tkTree.Insert(3);
	std::cout << "Tree :: Added 3\n";
	m_tkTree.Insert(4);
	std::cout << "Tree :: Added 4\n";
	m_tkTree.Insert(5);
	std::cout << "Tree :: Added 5\n";

	if (m_tkTree.Search(1)->data != 1) TK_EXCEPTION("Failed Adding 1");
	if (m_tkTree.Search(2)->data != 2) TK_EXCEPTION("Failed Adding 2");
	if (m_tkTree.Search(3)->data != 3) TK_EXCEPTION("Failed Adding 3");
	if (m_tkTree.Search(4)->data != 4) TK_EXCEPTION("Failed Adding 4");
	if (m_tkTree.Search(5)->data != 5) TK_EXCEPTION("Failed Adding 5");

	std::cout << "Tree :: Passed\n";

	m_tkTree.DeleteNode(2);
	std::cout << "Tree :: Deleting 2\n";
	m_tkTree.DeleteNode(3);
	std::cout << "Tree :: Deleting 3\n";

	std::cout << "Tree :: Passed\n";

	m_tkTree.Insert(8);
	std::cout << "Tree :: Added 3\n";
	m_tkTree.Insert(9);
	std::cout << "Tree :: Added 4\n";
	m_tkTree.Insert(56);
	std::cout << "Tree :: Added 5\n";

	if (m_tkTree.Search(8)->data != 8) TK_EXCEPTION("Failed Adding 8");
	if (m_tkTree.Search(9)->data != 9) TK_EXCEPTION("Failed Adding 9");
	if (m_tkTree.Search(56)->data != 56) TK_EXCEPTION("Failed Adding 56");

	std::cout << "Tree :: Passed\n";

	std::cout << "############ Passed AA Tree ############\n\n";
}

void Testing::ObjectPoolTesting() {
	std::cout << "############ Started Object Pool ############\n";

	m_tkObjectPool.AddObject(1);
	std::cout << "Object Pool :: Added 1 | ADDRESS:" << m_tkObjectPool.ReturnObject(1) << "\n";
	m_tkObjectPool.AddObject(2);
	std::cout << "Object Pool :: Added 2 | ADDRESS:" << m_tkObjectPool.ReturnObject(2) << "\n";
	m_tkObjectPool.AddObject(3);
	std::cout << "Object Pool :: Added 3 | ADDRESS:" << m_tkObjectPool.ReturnObject(3) << "\n\n";

	if (*m_tkObjectPool.ReturnObject(1) != 1) TK_EXCEPTION("Failed Adding 1");
	if (*m_tkObjectPool.ReturnObject(1) != 1) TK_EXCEPTION("Failed Adding 2");
	if (*m_tkObjectPool.ReturnObject(1) != 1) TK_EXCEPTION("Failed Adding 3");

	m_tkObjectPool.print();
	std::cout << "\nObject Pool :: Passed\n";

	std::cout << "Object Pool :: Deleting at pos 1\n\n";
	m_tkObjectPool.RemoveObejct(2);

	m_tkObjectPool.print();
	std::cout << "\nObject Pool :: Passed\n";

	std::cout << "Object Pool :: Getting objects by index\n";

	for (int i = 0; i < 2; i++)
		std::cout <<"ADDRESS: "<< m_tkObjectPool.ReturnObjectIndex(i) << "\n";

	std::cout << "\n";
	m_tkObjectPool.print();
	std::cout << "\nObject Pool :: Passed\n";

	std::cout << "Object Pool :: Getting objects by value\n";

	std::cout << "ADDRESS: " << m_tkObjectPool.ReturnObject(1) << "\n";
	std::cout << "ADDRESS: " << m_tkObjectPool.ReturnObject(3) << "\n\n";

	m_tkObjectPool.print();
	std::cout << "\nObject Pool :: Passed\n";

	std::cout << "############ Passed Object Pool ############\n\n";
}
