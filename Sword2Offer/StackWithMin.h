#pragma once
#include <stack>
template <typename T> class StackWithMin {
	
public:
	StackWithMin();
	~StackWithMin();

private:
	std::stack<int> m_data;
	std::stack<int> m_min;

	void push(const T& value);
	void pop();
	const T& min() const;
};