// Sword2Offer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "list.h"
//#include "tree.h"

#include <stack>
#include<iostream>
#include<math.h>

using namespace std;
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
/*
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
*/

//08
struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
	BinaryTreeNode* m_pParent;
};
BinaryTreeNode* GetNext(BinaryTreeNode* pNode) {
	if (pNode == nullptr)
		return nullptr;
	BinaryTreeNode* pNext = nullptr;
	if (pNode->m_pRight != nullptr) {
		BinaryTreeNode* pRight = pNode->m_pRight;
		if (pRight->m_pLeft != nullptr)
			pRight = pRight->m_pLeft;
		pNext = pRight;
	}
	else if (pNode->m_pParent != nullptr) {
		BinaryTreeNode* pCurrent = pNode;
		BinaryTreeNode* pParent = pNode->m_pParent;
		while (pParent != nullptr && pCurrent == pParent->m_pRight) {
			pCurrent = pParent;
			pParent = pParent->m_pParent;
		}
		pNext = pParent;
	}
	return pNext;
}
//10
long long Fibonacci(unsigned n) {
	int result[2] = { 0,1 };
	if (n < 2)
		return result[n];
	long long fibNMinusOne = 1;
	long long fibNMinusTwo = 0;
	long long fibN = 0;
	for (unsigned int i = 2; i <= n; ++i) {
		fibN = fibNMinusOne + fibNMinusTwo;
		fibNMinusTwo = fibNMinusOne;
		fibNMinusOne = fibN;
	}
	return fibN;
}
//2.4.2
int RandomInRange(int start, int end) {
	int dis = end - start;
	return rand()%dis + start;
}
void Swap(int *da, int *db) {
	int temp = *da;
	*da = *db;
	*db = temp;
}
int Partition(int data[], int length, int start, int end) {
	if (data == nullptr || length <= 0 || start < 0 || end >= length) {
		throw new std::exception("Invalid Paremeters");
	}
	int index = RandomInRange(start, end);
	Swap(&data[index], &data[end]);
	for (int i = 0; i < 6; ++i) {
		cout << data[i] << "-";
	}cout << endl;

	int small = start - 1;
	for (index = start; index < end; ++index) {
		if (data[index] < data[end]) {
			++small;
			if (small != index)
				Swap(&data[index], &data[small]);
			for (int i = 0; i < 6; ++i) {
				cout << data[i] << "-";
			}cout << endl;
		}
	}
	++small;
	Swap(&data[small], &data[end]);
	for (int i = 0; i < 6; ++i) {
		cout << data[i] << "-";
	}cout << endl;
	return small;
}
void QuickSort(int data[], int length, int start, int end) {
	if (start == end)
		return;
	int index = Partition(data, length, start, end);
	cout << "partition is " << index << endl;
	if (index > start)
		QuickSort(data, length, start, index - 1);
	if (index < end)
		QuickSort(data, length, index + 1, end);

}
//11
int MinInOrder(int* numbers, int index1, int index2) {
	int result = numbers[index1];
	for (int i = index1 + 1; i <= index2; ++i) {
		if (result > numbers[i])
			result = numbers[i];
	}
	return result;
}
int Min(int * numbers, int length) {
	if (numbers == nullptr || length <= 0)
		throw new exception("Invalid parameters");
	int index1 = 0;
	int index2 = length - 1;
	int indexMid = index1;
	while (numbers[index1] >= numbers[index2]) {
		if (index2 - index1 == 1) {
			indexMid = index2;
			break;
		}
		indexMid = (index1 + index2) / 2;
		if (numbers[index1] == numbers[index2] && numbers[indexMid] == numbers[index1])
			return MinInOrder(numbers, index1, index2);
		if (numbers[indexMid] >= numbers[index1])
			index1 = indexMid;
		else if (numbers[indexMid] <= numbers[index2])
			index2 = indexMid;
	}
	return numbers[indexMid];
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

	std::cout << endl << "1:10随机数：" << RandomInRange(1, 10) << endl;
	int a[2] = { 1,2 };
	Swap(&a[0], &a[1]);
	cout << "a=" << a[0] << endl << "b=" << a[1] << endl;
	//10
	int data[6] = { 3, 1, 2, 6, 9, 7 };
	QuickSort(data, 6, 0, 5);
	for (int i = 0; i < 6; ++i) {
		cout << data[i]<<"-";
	}cout << endl;

    return 0;
}
