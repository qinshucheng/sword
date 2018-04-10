// Sword2Offer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "list.h"
#include "tree.h"

#include <stack>

//02
int GetSize(int data[]) {
	return sizeof(data);
}
//03_01
bool duplicate(int numbers[], int length, int* duplication) {
	if (numbers == nullptr || length == 0) {
		return false;
	}
	for (int i = 0; i < length; ++i) {
		if (numbers[i]<0 || numbers[i]>length - 1) {
			return false;
		}
	}
	for (int i = 0; i < length; ++i) {
		while (numbers[i] != i) {
			if (numbers[i] == numbers[numbers[i]]) {
				*duplication = numbers[i];
				return true;
			}
			int temp = numbers[i];
			numbers[i] = numbers[temp];
			numbers[temp] = temp;
		}
	}
	return false;
}

//03_02
int countRange(const int* numbers, int length, int start, int end) {
	if (numbers == nullptr) {
		return 0;
	}
	int count = 0;
	for (int i = 0; i < length; i++) {
		if (numbers[i] >= start&&numbers[i] <= end) {
			++count;
		}
	}
}
int getDuplication(const int* numbers, int length) {
	if (numbers == nullptr || length <= 0) {
		return -1;
	}
	int start = 1;
	int end = length - 1;
	while (end >= start) {
		int middle = ((end - start) >> 1) + start;
		int count = countRange(numbers, length, start, middle);
			if (end == start) {
				if (count > 1)
					return start;
				else
					break;
			}
			if (count > (middle - start + 1))
				end = middle;
			else
				start = middle + 1;
	}
	return -1;
}

//04
bool find(int* matrix, int rows, int columns, int number) {
	bool found = false;
	if (matrix != nullptr&&rows > 0 && columns > 0) {
		int row = 0;
		int column = columns - 1;
		while (row < rows&&column>0) {
			if (matrix[row*columns + column] == number) {
				found = true;
				break;
			}
			else if(matrix[row*columns+column]<number){
				--column;
			}
			else {
				++row;
			}
		}
	}
	return found;
}
//05
void replaceBlank(char string[], int length) {
	//length为string的总容量
	//originalLength为string的实际长度
	if (string == nullptr || length <= 0) {
		return;
	}
	int originalLength = 0;
	int numberOfBlank = 0;
	int i = 0;
	while (string[i] != '\0') {
		++originalLength;
		if (string[i] == ' ')
			++numberOfBlank;
		++i;
	}
	int newLength = originalLength + numberOfBlank * 2;
	if (newLength > length)
		return;
	int indexOfOriginal = originalLength;
	int indexOfNew = newLength;
	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal) {
		if (string[indexOfOriginal] == ' ') {
			string[indexOfNew--] = '0';
			string[indexOfNew--] = '2';
			string[indexOfNew--] = '%';
		}
		else {
			string[indexOfNew--] = string[indexOfOriginal];
		}
		--indexOfOriginal;
	}
}
//2.3.3_1
//链表节点

void AddToTail(ListNode** pHead, int value) {
	ListNode* pNew = new ListNode();
	pNew->m_nValue = value;
	pNew->m_pNext = nullptr;
	if (*pHead == nullptr) {
		*pHead = pNew;
	}
	else {
		ListNode* pNode = *pHead;
		while (pNode->m_pNext != nullptr)
			pNode = pNode->m_pNext;
		pNode->m_pNext = pNew;
	}
}
//2.3.3_2
void RemoveNode(ListNode** pHead, int value) {
	if (pHead == nullptr || *pHead == nullptr)
		return;
	ListNode* pToDelete = nullptr;
	if ((*pHead)->m_nValue == value) {
		pToDelete = *pHead;
		*pHead = (*pHead)->m_pNext;
	}
	else {
		ListNode* pNode = *pHead;
		while (pNode->m_pNext != nullptr&&pNode->m_pNext->m_nValue != value)
			pNode = pNode->m_pNext;
		if (pNode->m_pNext != nullptr&&pNode->m_pNext->m_nValue == value) {
			pToDelete = pNode->m_pNext;
			pNode->m_pNext = pNode->m_pNext->m_pNext;
		}
		if (pToDelete != nullptr) {
			delete pToDelete;
			pToDelete = nullptr;
		}
	}
}

//06
void PrintListReversingly_Iteratively(ListNode* pHead) {
	std::stack<ListNode*> nodes;
	ListNode* pNode = pHead;
	while (pNode != nullptr) {
		nodes.push(pNode);
		pNode = pNode->m_pNext;
	}
	while (!nodes.empty()) {
		pNode = nodes.top();
		printf("%d\t", pNode->m_nValue);
		nodes.pop();
	}
}
void PrintListReversingly_Recursively(ListNode* pHead) {
	if (pHead != nullptr) {
		if (pHead->m_pNext != nullptr) {
			PrintListReversingly_Recursively(pHead->m_pNext);
		}
		printf("%d\t", pHead->m_nValue);
	}
}

//07
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, 
	int* startInorder, int* endInorder) {
	int rootValue = startPreorder[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = nullptr;

	if (startPreorder == endPreorder) {
		if (startInorder == endInorder && *startPreorder == *startInorder)
			return root;
		else
			throw std::exception("Invalid input!");
	}
	//在中序遍历中寻找根节点
	int* rootInorder = startInorder;
	while (rootInorder <= endInorder&&*rootInorder != rootValue)
		++rootInorder;
	if (rootInorder == endInorder&&*rootInorder != rootValue)
		throw std::exception("Invalid input");
	int leftLength = rootInorder - startInorder;
	int* leftPreorderEnd = startPreorder + leftLength;
	if (leftLength > 0) {
		//构建左子树
		root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	}
	if (leftLength < endPreorder - startPreorder) {
		//构建右子树
		root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	}

	return root;
}
BinaryTreeNode* Construct(int*preorder, int*inorder, int length) {
	if (preorder == nullptr || inorder == nullptr || length <= 0) {
		return nullptr;
	}
	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}


int main()
{	//2
	int data1[] = { 1,2,3,4,5 };
	int size1 = sizeof(data1);
	int *data2 = data1;
	int size2 = sizeof(data2);
	int size3 = GetSize(data1);
	printf("%d\n%d\n%d\n", size1, size2, size3);
	//
	char str1[] = "hello world";
	char str2[] = "hello world";
	char* str3 = "hello world";
	char* str4 = "hello world";
	if (str1 == str2) { printf("str1 and str2 are same"); }
	else { printf("str1 and str2 are not same"); }
	if (str3 == str4) { printf("str3 and str4 are same"); }
	else { printf("str3 and str4 are not same"); }

    return 0;
}
