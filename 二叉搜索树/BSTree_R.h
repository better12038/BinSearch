//BSTree_R.h

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct BSTreeNode
{
	int key;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
}BSTreeNode;
//*递归*

//查找:找到返回0，找不到返回-1
int BSTreeSearch(BSTreeNode *root, int key)
{
	BSTreeNode *cur = root;
	while (cur != NULL)
	{
		if (cur->key == key)
		{
			printf("找到\n");
			return 0;
		}
		if (cur->key < key)
		{
			BSTreeSearch(root->right, key);
		}
		else
			BSTreeSearch(root->left, key);

	}
	printf("没找到\n");
	return -1;
}

//插入
int BSTreeInsert(BSTreeNode **root, int key)
{
	BSTreeNode *parent = NULL;
	BSTreeNode *cur = *root;
	while (cur != NULL)
	{
		if (cur->key == key)
			return -1;
		parent = cur;
		if (key < cur->key)
			cur = cur->left;
		else
			cur = cur->right;
	}

	BSTreeNode *node = (BSTreeNode *)malloc(sizeof(*node));
	node->key = key;
	node->left = node->right = NULL;
	if (parent == NULL)
	{
		*root = node;
		return 0;
	}
	if (key < parent->key)
	{
		parent->left = node;
	}
	else
		parent->right = node;
	return 0;

}

//删除
void Remove(BSTreeNode **root, BSTreeNode *parent, BSTreeNode *cur)
{
	//要删除节点的左子树为空
	if (cur->left == NULL)
	{
		if (parent == NULL)
		{
			*root = cur->right;
			free(cur);
			return;
		}
		else if (cur == parent->left)
		{
			parent->left = cur->right;
			free(cur);
			return;
		}
		else
		{
			parent->right = cur->right;
			free(cur);
			return;
		}
	}
	//要删除节点的右子树为空
	else if (cur->right == NULL)
	{
		if (parent == NULL)
		{
			*root = cur->left;
			free(cur);
			return;
		}
		else if (cur == parent->right)
		{
			parent->right = cur->left;
			free(cur);
			return;
		}
		else
		{
			parent->left = cur->left;
			free(cur);
			return;
		}
	}
	//要删除节点的左右子树都不为空,用替换法删除,找右子树中最小的
	else
	{
		BSTreeNode *del = cur->right;
		BSTreeNode *delParent = cur;
		if (del->left != NULL)
		{
			delParent = del;
			del = del->left;
		}
		cur->key = del->key;
		if (delParent == cur)
		{
			delParent->right = del->right;
		}
		else
			delParent->left = del->right;
		free(del);
	}

}


int BSTreeRemove(BSTreeNode **root, int key)
{
	BSTreeNode *cur = *root;
	BSTreeNode *parent = NULL;
	while (cur != NULL)
	{
		if (key == cur->key)
		{
			Remove(root, parent, cur);
			return 0;
		}
		parent = cur;
		if (key < cur->key)
		{
			cur = cur->left;
		}
		else
		{
			cur = cur->right;
		}
	}
	return -1;
}


int BSTreePrint(BSTreeNode *root)
{
	if (root != NULL)
	{
		printf("%d\n", root->key);
		if (root->left != NULL)
		{
			printf("%d\n", BSTreePrint(root->left));

		}
		if (root->right != NULL)
		{
			printf("%d\n", BSTreePrint(root->right));
		}
	}
	//printf("\n");
	return 0;
}

void test()
{
	BSTreeNode *bs = NULL;
	BSTreeInsert(&bs, 2);
	BSTreeInsert(&bs, 1);
	BSTreeInsert(&bs, 3);
	BSTreeSearch(bs, 2);
	BSTreeSearch(bs, 4);
	BSTreeSearch(bs, 3);
	BSTreePrint(bs);

	BSTreeRemove(&bs, 1);
	BSTreePrint(bs);


}