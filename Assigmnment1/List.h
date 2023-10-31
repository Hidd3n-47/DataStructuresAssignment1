#pragma once

#include "Iterator.h"

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

	/// <<< --------------------------------------------------------------------- Inserting into the List.

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
	// Note, inserting will put the value at the given position, and shift everything from _Position to the end of the list by one index value.
	inline void insert(_iterator<T> _Position, T _Value)
	{
		_List_Node<T>* _new = new _List_Node<T>(_Value);
		
		_new->_Next = _Position._Node;
		_new->_Prev = _Position._Node->_Prev;
		_new->_Prev->_Next = _new;
		_Position._Node->_Prev = _new;
	}

	// Insert a value at the given position of the iterator. 
	// Note, inserting will put the value at the given position, and shift everything from _Position to the end of the list by one index value.
	inline void insert(uint64_t _Index, T _Value)
	{
		ASSERT(_Index < _MySize);		/* Ensure that you pass in a valid index that is less than the size of the list. */

		_List_Node<T>* it = _First;
		uint64_t _currentIndex = 0;
		while (_currentIndex < _Index)
		{
			it = it->_Next;
		}

		_List_Node<T>* _new = new _List_Node<T>(_Value);
		_new->_Next = it;
		_new->_Prev = it->_Prev;
		_new->_Prev->_Next = _new;
		it->_Prev = _new;
	}
	/// ================================

	/// <<< --------------------------------------------------------------------- Removing from the List.

	// Remove one item from the back of the list.
	inline void pop_back()
	{
		ASSERT(_MySize != 0);	/* Ensure that you are not removing an element from an empty list.	*/

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
		ASSERT(_MySize != 0);	/* Ensure that you are not removing an element from an empty list.	*/

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
		ASSERT(_MySize != 0); 	/* Ensure that you are not clearing an empty list.	*/

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
		ASSERT(_val1 != _val2);		/* Ensure that you are not swappping an element with itself.		*/

		T tmp = _val1.value();

		_val1._Node->_Value = _val2._Node->_Value;
		_val2._Node->_Value = tmp;
	}
	/// ================================

	///<<< --------------------------------------------------------------------- Sorting.

	// Bubble Sort Algorithm to sort the list into assending order.
	void sort()
	{
		for (int i = size(); i > 0; i--)
		{
			int counter = 0;
			auto previous = begin();

			for (auto it = begin(); counter++ < i; it++)
			{
				if (it == begin()) { continue; }

				if (previous.value() > it.value())
				{
					swap(previous, it);
				}
				previous = it;
			}
		}
	}
	/// ================================

	///<<< --------------------------------------------------------------------- Iterators.

	// Iterator pointing to the beginning of the list, i.e. the first item in the list.
	inline _iterator<T> begin() const	{ return _iterator<T>(_First); }
	// Iterator pointing to one after the last item on the list.
	inline _iterator<T> end()	const	{ return _iterator<T>(_End); }

	/// ================================

	///<<< --------------------------------------------------------------------- Accessors.

	// Returns the first value of the list.
	inline T front()		const	{ return _First->_Value; }
	// Returns the last value of the list.
	inline T back()			const	{ return _Last->_Value; }
	// Returns the number of items in the list.
	inline uint64_t size()	const	{ return _MySize; }

	/// ================================

	///<<< --------------------------------------------------------------------- Operators.

	// Operator to acces the _index item in the list.
	inline T& operator[](unsigned int _index)
	{
		ASSERT(_index < _MySize);		/* Ensure that the index is not outside the size of the list.	*/

		_List_Node<T>* _nodePtr = _First;

		unsigned int _counter = 0;
		while (_counter++ != _index)
		{
			_nodePtr = _nodePtr->_Next;
		}

		return _nodePtr->_Value;
	}
	/// ================================

private:
	_List_Node<T>* _First	= nullptr;	// First element in the list.
	_List_Node<T>* _Last	= nullptr;	// Last element in the list.
	_List_Node<T>* _End		= nullptr;	// One past the last element of the list.
	uint64_t _MySize		= 0;		// The number of elements in the list.

	inline void _InsertOnEmpty(T _Value)
	{
		_List_Node<T>* _new	= new _List_Node<T>(_Value);

		_Last = _First	= _new;

		_First->_Next	= _End;
		_Last->_Next	= _End;
		_End->_Prev		= _Last;
	}
};
