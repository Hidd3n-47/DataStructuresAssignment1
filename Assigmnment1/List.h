#pragma once

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
public:
	T value() const { return _pNode->_Value; }

	inline _iterator<T>& operator++(int)
	{
		// TODO (Christian): Add assert here if there is no next value.
		this->_pNode = _pNode->_pNext;

		return *this;
	}

	inline _iterator<T>& operator++()
	{
		// TODO (Christian): Add assert here if there is no next value.

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

	_iterator(_List_Node<T>* _node) : _pNode(_node) { /* Empty. */ }
private:
	_List_Node<T>* _pNode;
};

template<typename T>
class List
{
public:
	inline List<T>() { _pEnd = new _List_Node<T>(); }
	inline ~List<T>() { clear(); }

	/// <<< ----- Inserting into the List.
	// TODO (Christian): Look at adding a list/array at once, eg. push_back({ 1, 2});
	inline void push_back(T _Value)
	{
		++_MySize;

		_List_Node<T>* node = _pFirst;
		_List_Node<T>* _new = new _List_Node<T>(_Value);

		if (!_pFirst) { _pLast = _pFirst = _new; SetEndAndLast();  return; }

		while (node->_pNext != _pEnd)
		{
			node = node->_pNext;
		}

		node->_pNext = _new;
		_new->_pPrev = node;
		_pLast = _new;

		SetEndAndLast();
	}

	inline void push_front(T _Value)
	{
		++_MySize;

		_List_Node<T>* _new = new _List_Node<T>(_Value);

		if (!_pFirst) { _pLast = _pFirst = _new; SetEndAndLast();  return; }

		_new->_pNext = _pFirst;
		_pFirst->_pPrev = _new;
		_pFirst = _new;

		if (_MySize == 1) 
		{ 
			_pLast = _new; 
			SetEndAndLast();
		}
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
			SetEndAndLast();
			return;
		}

		_pLast = _pFirst;

		while (_pLast->_pNext->_pNext != _pEnd)
		{
			_pLast = _pLast->_pNext;
		}

		delete _pLast->_pNext;
		_pLast->_pNext = nullptr;

		SetEndAndLast();
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
	/// ================================

	///<<< ----- Iterators.
	inline _iterator<T> begin()		{  return _iterator<T>(_pFirst); }
	inline _iterator<T> end()		{  return _iterator<T>(_pEnd); }
	/// ================================


	///<<< ----- Accessors.
	inline T front() const { return _pFirst->_Value; }
	inline T back() const { return _pLast->_Value; }
	/// ================================
private:
	_List_Node<T>* _pFirst = nullptr;
	_List_Node<T>* _pLast = nullptr;
	_List_Node<T>* _pEnd = nullptr;
	uint64_t _MySize = 0;

	inline void SetEndAndLast()
	{
		_pLast->_pNext = _pEnd;
		_pEnd->_pNext = _pLast;
	}
};

