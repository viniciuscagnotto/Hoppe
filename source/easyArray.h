#if !defined(__EASY_ARRAY_H__)
#define __EASY_ARRAY_H__

template <typename T, unsigned int N>
class EasyArray
{
private:
	T *m_items;
	unsigned int m_numItems;
	unsigned int m_maxItems;

public:
	EasyArray() { 
		m_maxItems = N;
		m_items = new T[N];
		for (unsigned int i = 0; i < m_maxItems; i++)
			m_items[i] = 0;
		m_numItems = 0; 
	};
	
	~EasyArray(){
		for (unsigned int i = 0; i < m_maxItems; i++)
			m_items[i] = 0;
		m_numItems = 0;
		delete[] m_items;
	};

	void Add(T newItem){
		if (m_numItems == m_maxItems)
			return;
		m_items[m_numItems++] = newItem;
	}

	T GetAt(unsigned int index){
		if (index >= m_maxItems)
			return 0;
		return m_items[index];
	}

	void RemoveAt(unsigned int index){
		m_items[index] = 0;
		for (unsigned int i = index; i < m_numItems-1; i++){
			m_items[i] = m_items[i + 1];
		}

		m_numItems--;
	}

	void RemoveAll(){
		for (unsigned int i = 0; i < m_maxItems; i++)
			m_items[i] = 0;
		m_numItems = 0;
	}

	unsigned int Size(){ return m_numItems; };
	unsigned int MaxSize(){ return m_maxItems; };

	T& operator[](unsigned int index){ return GetAt(nIndex); };
};

#endif  // __EASY_ARRAY_H__

