template<class T>class StackNode
{
public:
	T data;
	StackNode*next;
};
template<class T>class Stack
{
private:
	StackNode<T>*top;
public:
	Stack(void) :top(NULL){};
	bool IsEmpty(void)const
	{
		return top == NULL;
	}
	void Push(const T data);
	bool Pop(T*data);
	bool Peek(T*data)const;
	StackNode<T>*GetStackNode();
};
template<class T>StackNode<T>* Stack<T>::GetStackNode()
{
	return top;
}
template<class T>void Stack<T>::Push(const T data)
{
	StackNode<T>*node = new StackNode<T>();
	node->data = data;
	node->next = top;
	top = node;
}
template<class T>bool Stack<T>::Peek(T*data)const
{
	//peek Æ²Ò»ÑÛ
	if (IsEmpty())
		return false;
	*data = top->data;
	return true;
}
template<class T>bool Stack<T>::Pop(T*data)
{
	if (IsEmpty())
		return false;
	*data = top->data;
	StackNode<T>*node = top;
	top = top->next;
	delete(node);
	return true;
}