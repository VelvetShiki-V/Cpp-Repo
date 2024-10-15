#ifndef __TREE_NODE_HPP
#define __TREE_NODE_HPP
#pragma once

template<class T>
class TreeNode {
public:
	TreeNode()
		:value(0)
		,left(nullptr)
		,right(nullptr)
	{}
	TreeNode<T>* left;
	TreeNode<T>* right;
	T value;
};

#endif