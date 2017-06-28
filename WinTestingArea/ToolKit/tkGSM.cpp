#include "tkGSM.h"

namespace tk {
	GSM::GSM() : m_size(0) { m_currentState = new u_int[0]; }
	GSM::GSM(int size) : m_size(size) {
		m_states.SetSize(size);
		m_currentState = new u_int[size];
		for (int i = 0; i < size; i++) {
			m_currentState[i] = NULL;
		}
	}
	GSM::~GSM() {
		TK_SAFE_ARRAY_DELETE(m_currentState);
	}


	void GSM::SetSize(int size) {
		m_states.SetSize(size);
		m_size = size;
		if (TK_SIZEOF(m_currentState) > 0) {
			TK_SAFE_ARRAY_DELETE(m_currentState);
		} m_currentState = new u_int[size];

		for (int i = 0; i < size; i++) {
			m_currentState[i] = NULL;
		}
	}

	bool GSM::addState(char * state, int level) {
		return m_states.add(state, level);
	}
	bool GSM::removeState(char * state) {
		return m_states.remove(state);
	}
	void GSM::SetState(char * state) {
		for (int i = 0; i < m_size; i++) {
			m_currentState[i] = NULL;
		} m_currentState[0] = m_states.hash(state, TK_SIZEOF(state));
	}
	void GSM::SetState(int size, ...) {
		for (int i = 0; i < m_size; i++) {
			m_currentState[i] = NULL;
		}
		va_list arg;
		va_start(arg, size);
		for (int i = 0; i < size; i++) {
			m_currentState[i] = m_states.hash(va_arg(arg, char*), TK_SIZEOF(va_arg(arg, char*)));
		} va_end(arg);

		u_int temp = 0;
		for (int i = 1; i < m_size; ++i) {
			for (int j = 0; j < (m_size - i); ++j) {
				if (m_states.get( m_currentState[j] ) < m_states.get(m_currentState[j + 1])) {
					temp = m_currentState[j];
					m_currentState[j] = m_currentState[j + 1];
					m_currentState[j + 1] = temp;
				} if (m_currentState[j + 1] == NULL && m_currentState[j] == NULL) break;
			}if (m_currentState[i + 1] == NULL && m_currentState[i] == NULL) break;
		} 
	}
}