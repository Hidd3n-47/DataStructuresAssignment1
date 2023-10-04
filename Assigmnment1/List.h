#pragma once

#include <vector>

template<typename T>
struct _List_Node
{
	_List_Node() = default;
	_List_Node(T value) : _Value(value) { /* Empty. */ }

	T _Value = NULL;
	_List_Node<T>* _pNext = nullptr;
	_List_Node<T>* _pPrev = nullptr;
};

template<typename T>
class _iterator
{
	template<typename T>
	friend class List;
public:
	T value() const { return _pNode->_Value; }

	inline _iterator<T>& operator++(int)
	{
		// TODO (Christian): Add assert here if there is no next value.
		++_index;
		this->_pNode = _pNode->_pNext;

		return *this;
	}

	inline _iterator<T>& operator++()
	{
		// TODO (Christian): Add assert here if there is no next value.
		++_index;
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

private:
	_iterator(_List_Node<T>* _node, uint64_t _index) : _pNode(_node), _index(_index) { /* Empty. */ }
	_List_Node<T>* _pNode;
	uint64_t _index = 0;
};

template<typename T>
class List
{
public:
	inline List<T>() { _pEnd = new _List_Node<T>(); }
	inline ~List<T>() { clear(); }
	
	/// <<< ----- Inserting into the List.
	template<typename ...Args>
	inline void push_back(Args&&... args)
	{
		([&] { push_back(args); } (), ...);
	}

	inline void push_back(T _Value) // Refactored.
	{
		++_MySize;

		_List_Node<T>* _new = new _List_Node<T>(_Value);

		if (!_pFirst) { _InsertOnEmpty(_Value); return; }

		_new->_pNext = _pEnd;
		_pEnd->_pPrev = _new;
		_new->_pPrev = _pLast;
		_pLast->_pNext = _new;
		_pLast = _new;
	}

	inline void push_front(T _Value) // Refactored.
	{
		++_MySize;

		_List_Node<T>* _new = new _List_Node<T>(_Value);

		if (!_pFirst) { _InsertOnEmpty(_Value); return; }

		_new->_pNext = _pFirst;
		_pFirst->_pPrev = _new;
		_pFirst = _new;
	}

	// TODO (Christian): Implement insert method: void insert(_iterator _Where, T* _Value);
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
			//SetEndAndLast();
			return;
		}

		_pLast = _pFirst;

		while (_pLast->_pNext->_pNext != _pEnd)
		{
			_pLast = _pLast->_pNext;
		}

		delete _pLast->_pNext;
		_pLast->_pNext = nullptr;

		//SetEndAndLast();
	}

	inline void pop_front()
	{
		if (_MySize == 0) { return; } // TODO (Christian): Assert here due to the list being already empty.

		--_MySize;

		_List_Node<T> _tmp = _pFirst->_pNext;
		delete _pFirst;
		_pFirst = _tmp;
		_pFirst->_pPrev = nullptr;
	}

	inline void clear()
	{
		if (_MySize == 0) { return; } // TODO (Christian): Assert here due to the list being already empty.

		_List_Node<T>* node = _pFirst;

		while (_pFirst->_pNext != _pEnd)
		{
			node = _pFirst;
			_pFirst = _pFirst->_pNext;
			delete node;
		}

		delete _pFirst;
		delete _pEnd;

		_pFirst = _pLast = _pEnd = nullptr;
		_MySize = 0;
	}

	inline void swap(_iterator<T> _val1, _iterator<T> _val2)
	{
		// TODO (Christian): Assert if the iterators are the same.

		/*if (_val1._index > _val2._index)
		{
			swap(_val2, _val1);
			return;
		}
		_List_Node<T>* tmp = _val1._pNode;
		uint64_t tmpIndex = _val1._index;
		
		_val1._pNode->_pNext = _val2._pNode->_pNext;
		_val1._pNode->_pPrev = _val2._pNode->_pPrev;
		_val1._index = _val2._index;
		_val2._pNode->_pPrev->_pNext = _val1._pNode;

		_val2._pNode->_pNext = tmp->_pNext;
		_val2._pNode->_pPrev = tmp->_pPrev;
		_val2._index = tmpIndex;
		tmp->_pNext->_pPrev = _val2._pNode;

		if (_val2._index == 0)
		{
			_pFirst = _val2._pNode;
		}
		if (_val1._index == _MySize)
		{
			_pLast = _val2._pNode;
		}*/

		// QUESTION (Christian): this does not change the memory locations, meaning there could be consequences with pointers?? Eg. should point to 3rd index, after swap(1,3), will point to 1st index. Issue?

		T tmp = _val1.value();
		_val1._pNode->_Value = _val2._pNode->_Value;
		_val2._pNode->_Value = tmp;
	}
	/// ================================

	///<<< ----- Iterators.
	inline _iterator<T> begin()		{  return _iterator<T>(_pFirst, 0); }
	inline _iterator<T> end()		{  return _iterator<T>(_pEnd, _MySize); }
	/// ================================


	///<<< ----- Accessors.
	inline T front() const			{ return _pFirst->_Value; }
	inline T back() const			{ return _pLast->_Value; }
	inline uint64_t size() const	{ return _MySize; }
	/// ================================
private:
	_List_Node<T>* _pFirst = nullptr;
	_List_Node<T>* _pLast = nullptr;
	_List_Node<T>* _pEnd = nullptr;
	uint64_t _MySize = 0;

	inline void _InsertOnEmpty(T _Value)
	{
		_List_Node<T>* _new = new _List_Node<T>(_Value);
		_pLast = _pFirst = _new;

		_pLast->_pNext = _pEnd;
		_pEnd->_pPrev = _pLast;
	}
};

