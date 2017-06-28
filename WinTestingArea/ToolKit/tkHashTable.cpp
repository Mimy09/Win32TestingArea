#include "tkHashTable.h"
namespace tk {
	namespace std {
		template <class T>
		HashTable<T>::HashTable(const int size)
			: m_size(size) {
			m_hash = new u_int[size];
			m_values = new T*[size];
			for (int i = 0; i < size; i++) {
				m_hash[i] = NULL;
				m_values[i] = nullptr;
			}
		}
		template<typename T>
		HashTable<T>::HashTable() : m_size(0) {
			m_hash = new u_int[0];
			m_values = new T*[0];
		}
		template <class T>
		HashTable<T>::~HashTable() {
			TK_SAFE_ARRAY_DELETE(m_hash);
			TK_SAFE_ARRAY_DELETE(m_values);
		}
		template<typename T>
		void HashTable<T>::SetSize(const int size) {
			TK_SAFE_ARRAY_DELETE(m_hash);
			TK_SAFE_ARRAY_DELETE(m_values);
			m_hash = new u_int[size];
			m_values = new T*[size];
			for (int i = 0; i < size; i++) {
				m_hash[i] = NULL;
				m_values[i] = nullptr;
			} m_size = size;
		}
		template <class T>
		u_int HashTable<T>::add(char * key, T* value) {
			if (m_size == 0) return 0;
			if (m_hash == nullptr || m_values == nullptr) return 0;
			for (int i = 0; i < m_size; i++) {
				if (m_hash[i] == NULL) {
					m_hash[i] = hash(key, TK_SIZEOF(key));
					if (value != nullptr) m_values[i] = value;
					return m_hash[i];
				}
			} return 0;
		}
		template <class T>
		u_int HashTable<T>::add(char * key, T value) {
			if (m_size == 0) return 0;
			T* temp = new T;
			*temp = value;
			if (m_hash == nullptr || m_values == nullptr) return 0;
			for (int i = 0; i < m_size; i++) {
				if (m_hash[i] == NULL) {
					m_hash[i] = hash(key, TK_SIZEOF(key));
					m_values[i] = temp;
					return m_hash[i];
				}
			} return 0;
		}
		template <class T>
		bool HashTable<T>::remove(char * key) {
			if (m_size == 0) return false;
			for (int i = 0; i < m_size; i++) {
				if (m_hash[i] == hash(key, TK_SIZEOF(key))) {
					m_hash[i] = NULL;
					m_values[i] = nullptr;
					return true;
				}
			} return false;
		}
		template <class T>
		T* HashTable<T>::get(char * key) {
			if (m_size == 0) return nullptr;
			for (int i = 0; i < m_size; i++) {
				if (m_hash[i] == hash(key, TK_SIZEOF(key))) {
					if (m_values[i] == nullptr) return nullptr;
					return m_values[i];
				}
			} return nullptr;
		}
		template<typename T>
		T* HashTable<T>::get(u_int key) {
			if (m_size == 0) return nullptr;
			for (int i = 0; i < m_size; i++) {
				if (m_hash[i] == key) {
					if (m_values[i] == nullptr) return nullptr;
					return m_values[i];
				}
			} return nullptr;
		}
		template<typename T>
		void HashTable<T>::clear() {
			for (int i = 0; i < m_size; i++) {
				m_hash[i] = NULL;
				m_values[i] = nullptr;
			}
		}
		template <class T>
		u_int HashTable<T>::hash(char * key) {
			u_int hash = 0, x = 0;
			for (u_int i = 0; (int)i < TK_SIZEOF(key); i++) {
				hash = (hash << 4) + key[i];
				if ((x = hash & 0xF0000000L) != 0) {
					hash ^= (x >> 24);
					hash &= ~x;
				}
			} return (hash & 0x7FFFFFFF);
		}

		template<typename T>
		u_int HashTable<T>::hash(char * key, int size, u_int seed) {
			u_int hash = seed;
			while (*key)
				hash = fnv1a((unsigned char)*key++, hash);
			return hash;
		}

		// Fowler-Noll-Vo Hash (FNV 1a)
		template<typename T>
		u_int HashTable<T>::fnv1a(unsigned char oneByte, u_int hash) {
			return (oneByte ^ hash) * m_prime;
		}


		TK_TEMPLATE(HashTable) < int > ; TK_TEMPLATE(HashTable) < int* > ;
		TK_TEMPLATE(HashTable) < char > ; TK_TEMPLATE(HashTable) < char* > ;
		TK_TEMPLATE(HashTable) < long > ; TK_TEMPLATE(HashTable) < long* > ;
		TK_TEMPLATE(HashTable) < float > ; TK_TEMPLATE(HashTable) < float* > ;
		TK_TEMPLATE(HashTable) < double > ; TK_TEMPLATE(HashTable) < double* > ;
		TK_TEMPLATE(HashTable) < unsigned int > ; TK_TEMPLATE(HashTable) < unsigned int* > ;
		TK_TEMPLATE(HashTable) < unsigned char > ; TK_TEMPLATE(HashTable) < unsigned char* > ;
		TK_TEMPLATE(HashTable) < tk::String > ; TK_TEMPLATE(HashTable) < tk::String* > ;
	}
}