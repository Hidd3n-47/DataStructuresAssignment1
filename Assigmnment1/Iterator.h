#pragma once

#include "ListNode.h"

// Iterator class for iterating through a list.
template<class T>
class _iterator
{
	template<class T>
	friend class List;
public:
	inline T value() const { return _Node->_Value; }

	// [Post] Increment iterator to next iteration.
	inline _iterator<T>& operator++(int)
	{
		ASSERT(_Node->_Next);	/* Ensure that there is another value for the iterator to increment to.		*/

		this->_Node = _Node->_Next;

		return *this;
	}

	// [Pre] Increment iterator to next iteration.
	inline _iterator<T>& operator++()
	{
		ASSERT(_Node->_Next);	/* Ensure that there is another value for the iterator to increment to.		*/

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
		ASSERT(_num != 0); // Ensure that a valid number is added to the operator.

		_iterator<T>* _it = this;
		int _counter = 0;
		while (_counter++ != _num)
		{
			ASSERT(_it->_Node->_Next);			/* Ensure the iterator is not list.end().				*/
			ASSERT(_it->_Node->_Next->_Next);	/* Ensure that the next iterator is not list.end().		*/


			_it->_Node = _it->_Node->_Next;
		}

		return *_it;
	}

	// Move the iterator by '_num' counts to the left. NOTE: only works for _num == 1.
	inline _iterator<T> operator-(unsigned int _num)
	{
		ASSERT(_num == 1);		/* Check that it is only '_iterator - 1'. Not implemented for subtracting more values.	*/
		ASSERT(this->_Node);	/* Ensure that the Node exists, i.e. the list is non-empty.								*/

		return _iterator<T>(this->_Node->_Prev);
	}
private:
	_iterator(_List_Node<T>* _node) : _Node(_node) { /* Empty. */ }
	_List_Node<T>* _Node;
};