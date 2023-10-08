#pragma once

#define ASSERT(x) if(x) __debugbreak();

// Struct to hold the memory that has been allocated and freed. Unnamed to have single instance.
struct
{
	uint32_t _allocated		= 0; 
	uint32_t _freed			= 0;
} MEM_ALLOCATION;

// 'new' Keyword override.
void* operator new(size_t size)
{
	MEM_ALLOCATION._allocated += size;
	return malloc(size);
}

// 'delete' Keyword override.
void operator delete(void* memory, size_t size)
{
	MEM_ALLOCATION._freed += size;
	free(memory);
}

// Internal struct used to hold information for the list.
template<class T>
struct _List_Node
{
	_List_Node() = default;
	_List_Node(T value) : _Value(value) { /* Empty. */ }

	T				_Value	= { };
	_List_Node<T>*	_Next	= nullptr;
	_List_Node<T>*	_Prev	= nullptr;
};

// Iterator class for iterating through a list.
template<class T>
class _iterator
{
	template<typename T>
	friend class List;
public:
	T value() const { return _Node->_Value; }

	// [Post] Increment iterator to next iteration.
	inline _iterator<T>& operator++(int)
	{
		ASSERT(!_Node->_Next);	/* Ensure that there is another value for the iterator to increment to.		*/	

		this->_Node = _Node->_Next;

		return *this;
	}

	// [Pre] Increment iterator to next iteration.
	inline _iterator<T>& operator++()
	{
		ASSERT(!_Node->_Next);	/* Ensure that there is another value for the iterator to increment to.		*/

		this->_Node = _Node->_Next;

		return *this;
	}

	// Query if two iterators are equal.
	inline bool operator== (const _iterator<T>& _rhs) const
	{
		return (this->_Node == _rhs._Node);
	}

	// Query if two iterators are not equal.
	inline bool operator!= (const _iterator<T>& _rhs) const
	{
		return (this->_Node != _rhs._Node);
	}

	// Move iterator by '_num' counts to the right.
	inline _iterator<T> operator+(unsigned int _num)
	{
		ASSERT(_num == 0); // Ensure that a valid number is added to the operator.

		_iterator<T>* _it = this;
		int _counter = 0;
		while (_counter++ != _num)
		{
			ASSERT(!(_it->_Node->_Next));			/* Ensure the iterator is not list.end().				*/
			ASSERT(!(_it->_Node->_Next->_Next));	/* Ensure that the next iterator is not list.end().		*/


			_it->_Node = _it->_Node->_Next;
		}

		return *_it;
	}

	// Move the iterator by '_num' counts to the left. NOTE: only works for _num == 1.
	inline _iterator<T> operator-(unsigned int _num)
	{
		ASSERT(_num != 1);		/* Check that it is only '_iterator - 1'. Not implemented for subtracting more values.	*/
		ASSERT(!this->_Node);	/* Ensure that the Node exists, i.e. the list is non-empty.								*/

		return _iterator<T>(this->_Node->_Prev);
	}
private:
	_iterator(_List_Node<T>* _node) : _Node(_node) { /* Empty. */ }
	_List_Node<T>* _Node;
};

// A double linked-list of any type T.
template<class T>
class List
{
public:
	inline List<T>()	{ _End = new _List_Node<T>(); }
	inline ~List<T>()	{ clear(); delete _End; }

	// Create a list with multiple values inserted in.
	template<class ...Args>
	inline List<T>(Args&&... _args)
	{
		_End = new _List_Node<T>();
		([&] { push_back(_args); } (), ...);
	}

	/// <<< ----- Inserting into the List.

	// Add all the values passed in into the back of list. Note, inserted in the order they are passed in.
	template<class ...Args>
	inline void push_back(Args&&... _args)
	{
		([&] { push_back(_args); } (), ...);
	}

	// Add a single value into the back of the list.
	inline void push_back(T _Value)
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

	// Add a single value into the front of the list.
	inline void push_front(T _Value)
	{
		++_MySize;

		if (!_First) { _InsertOnEmpty(_Value); return; }

		_List_Node<T>* _new = new _List_Node<T>(_Value);

		_new->_Next = _First;
		_First->_Prev = _new;
		_First = _new;
	}

	// Insert a value at the given position of the iterator.
	inline void insert(_iterator<T> _Position, T _Value)
	{
		_List_Node<T>* _new = new _List_Node<T>(_Value);
		
		_new->_Next = _Position._Node;
		_new->_Prev = _Position._Node->_Prev;
		_new->_Prev->_Next = _new;
		_Position._Node->_Prev = _new;
	}
	/// ================================

	/// <<< ----- Removing from the List.

	// Remove one item from the back of the list.
	inline void pop_back()
	{
		ASSERT(_MySize == 0);	/* Ensure that you are not removing an element from an empty list.	*/

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

	// Remove one item from the front of the list.
	inline void pop_front()
	{
		ASSERT(_MySize == 0);	/* Ensure that you are not removing an element from an empty list.	*/

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

	// Clear the list to have no values.
	inline void clear()
	{
		ASSERT(_MySize == 0); 	/* Ensure that you are not clearing an empty list.	*/

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

	// Swap the values of two items in the list. 
	// Note: ONLY swaps the values of the items and not the memory addresses, therefore be careful for stale pointers when swapping.
	inline void swap(_iterator<T> _val1, _iterator<T> _val2)
	{
		ASSERT(_val1 == _val2);		/* Ensures that you cannot swap an element with itself.		*/

		T tmp = _val1.value();

		_val1._Node->_Value = _val2._Node->_Value;
		_val2._Node->_Value = tmp;
	}
	/// ================================

	///<<< ----- Iterators.

	// Iterator pointing to the beginning of the list, i.e. the first item in the list.
	inline _iterator<T> begin() const	{ return _iterator<T>(_First); }
	// Iterator pointing to one after the last item on the list.
	inline _iterator<T> end()	const	{ return _iterator<T>(_End); }

	/// ================================

	///<<< ----- Accessors.

	// Returns the first value of the list.
	inline T front()		const	{ return _First->_Value; }
	// Returns the last value of the list.
	inline T back()			const	{ return _Last->_Value; }
	// Returns the number of items in the list.
	inline uint64_t size()	const	{ return _MySize; }

	/// ================================

	// Operator to acces the _index item in the list.
	inline T& operator[](unsigned int _index)
	{
		ASSERT(_index >= _MySize);		/* Ensure that the index is not outside the size of the list.	*/

		_List_Node<T>* _nodePtr = _First;

		unsigned int _counter = 0;
		while (_counter++ != _index)
		{
			_nodePtr = _nodePtr->_Next;
		}

		return _nodePtr->_Value;
	}
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
