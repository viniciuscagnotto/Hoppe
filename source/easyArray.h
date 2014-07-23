#if !defined(__EASY_ARRAY_H__)
#define __EASY_ARRAY_H__

template <typename T, uint N>
class EasyArray
{
private:
	T m_items[N];

public:
	void RemoveAt(uint index){
		for (uint i = index + 1; i < N; i++){
			m_items[i - 1] = m_items[i];
		}
	}

	unsigned int MaxSize(){ return N; };

	T& operator[](uint index){ return m_items[index]; };
	const T& operator[](uint index) const { return m_items[index]; };
};

#endif  // __EASY_ARRAY_H__