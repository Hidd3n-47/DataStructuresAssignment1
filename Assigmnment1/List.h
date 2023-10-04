#pragma once
#include <list>

// TODO (Christian): Need to fix the list.end() to be the node past the last node so that the iterators work correctly.

template<typename T>
struct _List_Node
{
	_List_Node(T value) : _Value(value) { /* Empty. */ }

	T _Value = nullptr;
	_List_Node<T>* _pNext = nullptr;
};

template<typename T>
class _iterator
{
public:
	T value() const { return _pNode->_Value; }

	inline _iterator<T>& operator++(int)
	{
		// TODO (Christian): Add assert here if there is no next value.

		this->_index++;
		this->_pNode = _pNode->_pNext;

		return *this;
	}

	inline _iterator<T>& operator++()
	{
		// TODO (Christian): Add assert here if there is no next value.

		this->_index++;
		this->_pNode = _pNode->_pNext;

		return *this;
	}

	inline bool operator== (const _iterator<T>& _rhs) const 
	{
		return this->_pNode == _rhs._pNode;
	}

	inline bool operator!= (const _iterator<T>& _rhs) const 
	{
		return this->_pNode != _rhs._pNode;
	}

	_iterator(_List_Node<T>* _node, uint64_t _index) : _pNode(_node), _index(_index) { /* Empty. */ /*_pNode = _node; this->_index = _index - 1;*/ }
private:
	_List_Node<T>* _pNode;
	uint64_t _index;
};

template<typename T>
class List
{
public:
	List<T>() { /* Empty. */ }
	~List<T>() { /* TODO (Christian): Clear memory here! */ }

	// Iterator first.
	// Iterator end.

	/// <<< ----- Inserting into the List.
	// TODO (Christian): Look at adding a list/array at once, eg. push_back({ 1, 2});
	inline void push_back(T _Value)
	{
		++_MySize;

		_List_Node<T>* node = _pFirst;
		_List_Node<T>* _new = new _List_Node<T>(_Value);

		if (!_pFirst) { _pLast = _pFirst = _new; return; }

		while (node->_pNext)
		{
			node = node->_pNext;
		}

		node->_pNext = _new;
		_pLast = _new;
	}

	inline void push_front(T _Value)
	{
		++_MySize;

		_List_Node<T>* _new = new _List_Node<T>(_Value);
		_new->_pNext = _pFirst;
		_pFirst = _new;

		if (_MySize == 1) { _pLast = _new; }
	}

	//void insert(_iterator _Where, T* _Value); // TODO (Christian): Implement iterator.
	/// ================================

	/// <<< ----- Removing from the List.
	inline void pop_back()
	{
		if (_MySize == 0) { return; } // TODO (Christian): Assert here due to the list being already empty.

		--_MySize;

		if (!_pFirst->_pNext)
		{
			delete _pFirst;
			_pLast = _pFirst = nullptr;
			return;
		}

		if (!_pFirst->_pNext->_pNext)
		{
			delete _pFirst->_pNext;
			_pLast = _pFirst;
			return;
		}

		_pLast = _pFirst;

		while (_pLast->_pNext->_pNext)
		{
			_pLast = _pLast->_pNext;
		}

		delete _pLast->_pNext;
		_pLast->_pNext = nullptr;
	}

	inline void pop_front()
	{
		if (_MySize == 0) { return; } // TODO (Christian): Assert here due to the list being already empty.

		--_MySize;

		_List_Node<T> _tmp = _pFirst->_pNext;
		delete _pFirst;
		_pFirst = _tmp;
	}

	inline void clear()
	{
		// TODO (Christian): implement the clear method.
	}
	/// ================================

	///<<< ----- Iterators.
	inline _iterator<T> begin() { /*return _pFirst;*/ return _iterator<T>(_pFirst, 0); }

	inline _iterator<T> end() { /*return _pLast;*/ return _iterator<T>(_pLast, _MySize - 1); }
	/// ================================


	///<<< ----- Accessors.
	inline T front() const { return _pFirst->_Value; }

	inline T back() const { return _pLast->_Value; }
	/// ================================
private:
	_List_Node<T>* _pFirst = nullptr;
	_List_Node<T>* _pLast = nullptr;
	uint64_t _MySize = 0;
};

