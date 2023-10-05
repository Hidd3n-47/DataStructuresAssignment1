#pragma once

struct _MemAllocation
{
	uint32_t _allocated		= 0; 
	uint32_t _freed			= 0;
};

static _MemAllocation MEM_ALLOCATION;

void* operator new(size_t size)
{
	MEM_ALLOCATION._allocated += size;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	MEM_ALLOCATION._freed += size;
	free(memory);
}

template<typename T>
struct _List_Node
{
	_List_Node() = default;
	_List_Node(T value) : _Value(value) { /* Empty. */ }

	T				_Value	= NULL;
	_List_Node<T>*	_Next	= nullptr;
	_List_Node<T>*	_Prev	= nullptr;
};

template<typename T>
class _iterator
{
	template<typename T>
	friend class List;
public:
	T value() const { return _Node->_Value; }

	inline _iterator<T>& operator++(int)
	{
		// TODO (Christian): Add assert here if there is no next value.
		this->_Node = _Node->_Next;

		return *this;
	}

	inline _iterator<T>& operator++()
	{
		// TODO (Christian): Add assert here if there is no next value.
		this->_Node = _Node->_Next;

		return *this;
	}

	inline bool operator== (const _iterator<T>& _rhs) const
	{
		return (this->_Node == _rhs._Node);
	}

	inline bool operator!= (const _iterator<T>& _rhs) const
	{
		return (this->_Node != _rhs._Node);
	}

private:
	_iterator(_List_Node<T>* _node) : _Node(_node) { /* Empty. */ }
	_List_Node<T>* _Node;
};

template<typename T>
class List
{
public:
	inline List<T>()	{ _End = new _List_Node<T>(); }
	inline ~List<T>()	{ clear(); delete _End; }

	/// <<< ----- Inserting into the List.
	template<typename ...Args>
	inline void push_back(Args&&... _args)
	{
		([&] { push_back(_args); } (), ...);
	}

	inline void push_back(T _Value) // Refactored.
	{
		++_MySize;

		if (!_First) { _InsertOnEmpty(_Value); return; }

		_List_Node<T>* _new = new _List_Node<T>(_Value);

		_new->_Next = _End;
		_End->_Prev = _new;
		_new->_Prev = _Last;
		_Last->_Next = _new;
		_Last = _new;
	}

	inline void push_front(T _Value) // Refactored.
	{
		++_MySize;

		if (!_First) { _InsertOnEmpty(_Value); return; }

		_List_Node<T>* _new = new _List_Node<T>(_Value);

		_new->_Next = _First;
		_First->_Prev = _new;
		_First = _new;
	}

	// TODO (Christian): Implement insert method: void insert(_iterator _Where, T* _Value);
	/// ================================

	/// <<< ----- Removing from the List.
	inline void pop_back()
	{
		if (_MySize == 0) { return; } // TODO (Christian): Assert here due to the list being already empty.

		--_MySize;

		if (_MySize == 0) 
		{ 
			delete _First; 
			_First = _Last = _End = nullptr; 
			return; 
		}

		_End->_Prev = _Last->_Prev;
		delete _Last;
		_Last = _End->_Prev;
		_Last->_Next = _End;
	}

	inline void pop_front()
	{
		if (_MySize == 0) { return; } // TODO (Christian): Assert here due to the list being already empty.

		--_MySize;

		if (_MySize == 0) 
		{ 
			delete _First; 
			_First = _Last = _End = nullptr; 
			return; 
		}

		_First = _First->_Next;
		delete _First->_Prev;
		_First->_Prev = nullptr;
	}

	inline void clear()
	{
		if (_MySize == 0) { return; } // TODO (Christian): Assert here due to the list being already empty.

		_List_Node<T>* node = _First;

		while (_First->_Next != _End)
		{
			node = _First;
			_First = _First->_Next;
			delete node;
		}

		delete _First;

		_First = _Last = nullptr;
		_MySize = 0;

		_End->_Prev = nullptr;
	}

	inline void swap(_iterator<T> _val1, _iterator<T> _val2)
	{
		// TODO (Christian): Assert if the iterators are the same.

		T tmp = _val1.value();

		_val1._Node->_Value = _val2._Node->_Value;
		_val2._Node->_Value = tmp;
	}
	/// ================================

	///<<< ----- Iterators.
	inline _iterator<T> begin()		{ return _iterator<T>(_First); }
	inline _iterator<T> end()		{ return _iterator<T>(_End); }
	/// ================================


	///<<< ----- Accessors.
	inline T front() const			{ return _First->_Value; }
	inline T back() const			{ return _Last->_Value; }
	inline uint64_t size()	const	{ return _MySize; }
	/// ================================
private:
	_List_Node<T>* _First	= nullptr;
	_List_Node<T>* _Last	= nullptr;
	_List_Node<T>* _End		= nullptr;
	uint64_t _MySize		= 0;

	inline void _InsertOnEmpty(T _Value)
	{
		_List_Node<T>* _new	= new _List_Node<T>(_Value);

		_Last = _First	= _new;

		_First->_Next	= _End;
		_Last->_Next	= _End;
		_End->_Prev		= _Last;
	}
};
