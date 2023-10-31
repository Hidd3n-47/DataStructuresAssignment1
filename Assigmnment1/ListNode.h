#pragma once

// Internal struct used to hold information for the list.
template<class T>
struct _List_Node
{
	_List_Node() = default;
	_List_Node(T value) : _Value(value) { /* Empty. */ }

	T				_Value = { };
	_List_Node<T>* _Next = nullptr;
	_List_Node<T>* _Prev = nullptr;
};