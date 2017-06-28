// ################################################################## //
// ##							LINKED LIST						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 June 21 - AIE		   ## //
// ################################################################## //
#pragma once
#include "tkMacros.h"
#include "tkString.h"
#include "tkException.h"

namespace tk {
	namespace std {
		/* ---- LINKED LIST ---- */
		template<typename T> class LinkedList {
		private:
			/* ---- NODE ----
			Node struct to hold the value and
			a pointer to the next element*/
			struct Node {
				T value; Node *next;
				bool operator==(const Node& other) const {
					if (value == other.value &&
						next == other.next) return true;
					return false;
				}
				Node& operator+(const int value) {
					Node* temp;
					temp = this->next;
					for (int i = 0; i < value; i++) {
						if (temp->next == nullptr) return *temp;
						temp = temp->next;
					} return *temp;
				}
				//~Node() { TK_SAFE_DELETE(next); }
			};
			Node *m_head, *m_tail;
		public:
			/* DEFAULT CONSTRUCTOR */
			LinkedList()
				: m_size(0), m_head(nullptr), m_tail(nullptr) {
			}
			/* DEFAULT DECONSTRUCTOR */
			~LinkedList() {}

			/* ---- BEGIN ----
			Gets a pointer to the start of the linked list
			#return T* - Pointer to the start of the linked list*/
			Node* begin() const { return m_head; }
			/* ---- END ----
			Gets a pointer to the end of the linked list
			#return T* - Pointer to the end of the linked list*/
			Node* end() const { return m_tail; }
			/* ---- FRONT ----
			Gets a reference to the start of the linked list
			#return T* - Reference to the start of the linked list*/
			Node& front() { return *m_head; }
			/* ---- BACK ----
			Gets a reference to the end of the linked list
			#return T* - Reference to the end of the linked list*/
			Node& back() { return *m_tail; }

			/* ---- OPERATOR[] ----
			Returns the value found at the index
			#return T& - reference to the value found*/
			T& operator[](const unsigned int index) const {
				if (index == -1) TK_EXCEPTION("Out of range");
				Node* cur = new Node, *pre = new Node;
				cur = m_head;
				for (int i = 0; i < (int)index; i++) {
					if (cur->next == nullptr && i < (int)index)
						TK_EXCEPTION("Out of range");
					pre = cur;
					cur = cur->next;
				} return cur->value;
			}
			/* ---- FIND ----
			Returns the value found at the index
			#param index - The position in the linked list
			#return T& - reference to the value found*/
			T& find(const unsigned int index) const {
				if (index == -1) TK_EXCEPTION("Out of range");
				Node* cur = new Node, *pre = new Node;
				cur = m_head;
				for (int i = 0; i < (int)index; i++) {
					if (cur->next == nullptr && i <= (int)index)
						TK_EXCEPTION("Out of range");
					pre = cur;
					cur = cur->next;
				} return cur->value;
			}

			/* ---- FIND ----
			Returns the Node at the given position
			#param index - The position in the linked list
			#return T& - reference to the value found*/
			int find_n(Node node) const {
				Node* cur = new Node, *pre = new Node;
				cur = m_head;
				int count = 0;
				while (cur != nullptr) {
					if (*cur == node) break;
					if (cur->next == nullptr)
						return -1;
					pre = cur;
					cur = cur->next;
					count++;
				} return count;
			}
			/* ---- FIND ----
			Returns the Node at the given position
			#param index - The position in the linked list
			#return T& - reference to the value found*/
			int find_i(T value) const {
				Node* cur = new Node, *pre = new Node;
				cur = m_head;
				int count = 0;
				while (cur != nullptr) {
					if (cur->value == value) break;
					if (cur->next == nullptr)
						return -1;
					pre = cur;
					cur = cur->next;
					count++;
				} return count;
			}
			/* ---- OPERATOR= ----
			Copies the valuse across*/
			void operator=(LinkedList& other) {
				if (this->size() != other.size()) TK_EXCEPTION("Linked List Copy Size");
				for (int i = 0; i < m_size; i++)
					find(i) = other[i];
			}

			/* ---- SIZE ----
			Gets the size of the linked list
			#return int - Returns the size*/
			int size() const { return m_size; }
			/* ---- EMPTY ----
			Checks if the linked list is empty
			#return bool - true if list is empty*/
			bool empty() {
				if (m_size) return false;
				return true;
			}

			/* ---- CLEAR ----
			Clears the linked list*/
			void clear() {
				m_size = 0;
				Node* cur = new Node, *pre = new Node;
				cur = m_head;
				while (cur->next != nullptr) {
					pre = cur;
					cur = cur->next;
					TK_SAFE_DELETE(pre);
				} TK_SAFE_DELETE(cur);
				m_head = m_tail = nullptr;
			}
			/* ---- INSERT ----
			Creates a node at the given position in the linked list
			#param pos - The postion in the linked list where the value will be placed
			#param value - The value that will be put into the linked list*/
			void insert(const int pos, const T& value) {
				m_size++;
				Node* temp = new Node;
				if (pos != 0) {
					temp->value = value;
					temp->next = nullptr;

					Node* cur = new Node, *pre = new Node;
					cur = m_head;
					for (int i = 0; i < pos; i++) {
						pre = cur;
						cur = cur->next;
					}
					pre->next = temp;
					temp->next = cur;
				}
				else {
					temp->value = value;
					temp->next = m_head;
					m_head = temp;
				}
			}
			/* ---- INSERT ----
			Creates a node at the given position in the linked list
			#param pos - The postion in the linked list where the value will be placed
			#param value - The value that will be put into the linked list*/
			void insert(Node& node, const T& value) {
				m_size++;
				Node* temp = new Node;
				temp->value = value;
				temp->next = nullptr;

				Node* cur = new Node, *pre = new Node;
				cur = m_head;
				while (cur->next != nullptr) {
					if (*cur == node) {
						pre->next = temp;
						temp->next = cur;
						break;
					}
					pre = cur;
					cur = cur->next;
				}
			}
			/* ---- ERASE ----
			Deletes a node at a given position
			#param pos - The position that will be deleted in the linked list*/
			void erase(const int pos) {
				m_size--;
				Node* cur = new Node, *pre = new Node;
				cur = m_head;
				for (int i = 0; i < pos; i++) {
					pre = cur;
					cur = cur->next;
				}
				pre->next = cur->next;
				TK_SAFE_DELETE(cur);
			}
			/* ---- PUSH BACK ----
			Pushes a new value onto the end of the linked list
			#param value - The value that will be pushed*/
			void push_back(const T& value) {
				m_size++;
				Node* temp = new Node;
				temp->value = value;
				temp->next = nullptr;
				if (m_head == nullptr) {
					m_head = temp;
					m_tail = temp;
					temp = nullptr;
				}
				else {
					if (m_head == m_tail) {
						m_head->next = temp;
						m_tail = temp;
					}
					else {
						m_tail->next = temp;
						m_tail = temp;
					}
				}
			}
			/* ---- POP BACK ----
			Deletes the last value in the linked list*/
			void pop_back() {
				m_size--;
				Node* cur = new Node, *pre = new Node;
				cur = m_head;
				while (cur->next != nullptr) {
					pre = cur;
					cur = cur->next;
				}
				m_tail = pre;
				pre->next = nullptr;
				delete cur;
			}


			/* ---- PRINT ----
			Prints the list onto the console*/
			void print() {
				for (int i = 0; i < m_size; i++) {
					printf("%i: %i | ", i, find(i));
				} printf("\n");
			}
			
		private:
			// Stores the size of the linked list
			int m_size;
		};
	}
}