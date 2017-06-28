#pragma once
#include "tkHashTable.h"
#include <stdarg.h>

namespace tk {
	class GSM {
	public:
		GSM();
		GSM(int size);
		~GSM();

		inline int Size() { return m_size; }
		void SetSize(int size);
		bool addState(char* state, int level = 0);
		bool removeState(char* state);

		void SetState(char* state);
		void SetState(int size, ...);
		u_int* GetState() { return m_currentState; }

	private:
		int m_size;
		tk::std::HashTable<int> m_states;
		u_int* m_currentState;
	};
}