// Sword2Offer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "list.h"
//#include "tree.h"
#include "ComplexListNode.h"

#include <stack>
#include<iostream>
#include<math.h>

#include<vector>

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
	cout << "index is " << index << endl;
	Swap(&data[index], &data[end]);
	for (int i = 0; i < 6; ++i) {
		cout << data[i] << "-";
	}cout << endl;

	int small = start - 1;
	cout << "small is " << small << endl;
	for (index = start; index < end; ++index) {
		cout << "data[index] is " << data[index] << endl;
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
//12
bool hasPathCore(const char* matrix, int rows, int cols, int row, int col, const char* str, int& pathLength, bool* visited) {
	if (str[pathLength] == '\0')
		return true;
	bool hasPath = true;
	if (row >= 0 && row < rows&&col >= 0 && col < cols&&matrix[row*cols + col] == str[pathLength] && !visited[row*cols + col]) {
		++pathLength;
		visited[row*cols + col] = true;
		hasPath = hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited);
		if (!hasPath) {
			--pathLength;
			visited[row*cols + col] = false;
		}
	}
	return hasPath;
}
bool hasPath(char* matrix, int rows, int cols, char* str) {
	if (matrix == nullptr || rows < 1 || cols < 1 || str == nullptr)
		return false;
	bool *visited = new bool[rows * cols];
	memset(visited, 0, rows*cols);//将visited初始化为[false,false...]
	int pathLength = 0;
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			if (hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited))
				return true;
		}
	}
	delete[] visited;
	return false;
}
//13
int getDigitSum(int number) {
	int sum = 0;
	while (number > 0) {
		sum += number % 10;
		number /= 10;
	}
	return sum;
}
bool check(int threshold, int rows, int cols, int row, int col, bool* visited) {
	if (row >= 0 && row < rows&&col >= 0 && col < cols&&getDigitSum(row) + getDigitSum(col) <= threshold && !visited[row*cols + col])
		return true;
	return false;
}
int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited) {
	int count = 0;
	if (check(threshold, rows, cols, row, col, visited)) {
		count = 1 + movingCountCore(threshold, rows, cols, row - 1, col, visited)
			+ movingCountCore(threshold, rows, cols, row, col - 1, visited)
			+ movingCountCore(threshold, rows, cols, row + 1, col, visited)
			+ movingCountCore(threshold, rows, cols, row, col + 1, visited);
	} 
	return count;
}
int movingCount(int threshold, int rows, int cols) {
	if (threshold < 0 || rows <= 0 || cols <= 0)
		return 0;
	bool *visited = new bool[rows*cols];
	for (int i = 0; i < rows*cols; ++i)
		visited[i] = false;
	int count = movingCountCore(threshold, rows, cols, 0, 0, visited);

	delete[] visited;
	return count;
}
//14
//动态规划法
int maxProductAfterCutting_solution(int length) {
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;
	int* products = new int[length + 1];
	products[0] = 0;
	products[1] = 1;
	products[2] = 2;
	products[3] = 3;
	int max = 0;

	for (int i = 4; i < length; ++i) {
		max = 0;
		for (int j = 1; j <= i / 2; ++j) {
			int product = products[j] * products[i - j];
			if (max < product)
				max = product;
			products[i] = max;
		}
	}
	max = products[length];
	delete[] products;
	return max;
}
//17全排列
void PrintNumber(char* number) {
	bool isBeginning0 = true;
	int nLength = strlen(number);

	for (int i = 0; i < nLength; ++i) {
		if (isBeginning0&&number[i] != '0')
			isBeginning0 = false;
		if (!isBeginning0)
			printf("%c", number[i]);
	}
	printf("\t");
}
void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index) {
	if (index == length - 1) {
		PrintNumber(number);
		return;
	}
	for (int i = 0; i < 10; ++i)
	{
		number[index + 1] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
	}
}
void Print1ToMaxOfNDigits(int n) {
	if (n < 0)
		return;
	char* number = new char[n + 1];
	number[n] = '\0';
	for (int i = 0; i < 10; ++i) {
		number[0] = i+'0';
		Print1ToMaxOfNDigitsRecursively(number, n, 0);
	}
	delete[] number;
}
//18_2
void DeleteDuplication(ListNode** pHead) {
	if (pHead == nullptr || *pHead == nullptr)
		return;
	ListNode* pPreNode = nullptr;
	ListNode* pNode = *pHead;
	while (pNode != nullptr) {
		ListNode* pNext = pNode->m_pNext;
		bool needDelete = false;
		if (pNext != nullptr&&pNext->m_nValue == pNode->m_nValue) {
			needDelete = true;
		}
		if (!needDelete) {
			pPreNode = pNode;
			pNode = pNode->m_pNext;
		}
		else {
			int value = pNode->m_nValue;
			ListNode* pToBeDel = pNode;
			while (pToBeDel != nullptr&&pToBeDel->m_nValue == value) {
				pNext = pToBeDel->m_pNext;
				delete pToBeDel;
				pToBeDel = nullptr;
				pToBeDel = pNext;
			}
			if (pPreNode == nullptr)
				*pHead = pNext;
			else
				pPreNode->m_pNext = pNext;
			pNode = pNext;
		}
	}
}
//19
bool matchCore(char*str, char*pattern) {
	if (*str == '\0'&&*pattern == '\0')
		return true;
	if (*str != '\0'&&pattern == '\0')
		return false;
	if(*(pattern+1)=='*'){
		if (*pattern == *str || (*pattern == '.'&&*str != '\0'))
			return matchCore(str + 1, pattern + 2) || matchCore(str + 1, pattern) || matchCore(str, pattern + 2);
		else
			return matchCore(str, pattern + 2);
	}
	if (*str == *pattern || (*pattern == '.'&&*str != '\0'))
		return matchCore(str + 1, pattern + 1);
	return false;
}
bool match(char*str, char*pattern) {
	if (str == nullptr || pattern == nullptr)
		return false;
	return matchCore(str, pattern);
}
//20
bool scanUnsignedInteger(const char** str) {
	const char* before = *str;
	while (**str != '\0'&&**str >= '0'&&**str <= '9')
		++(*str);
	return *str > before;
}
bool scanInteger(const char** str) {
	if (**str == '+' || **str == '-')
		++(*str);
	return scanUnsignedInteger(str);
}
bool isNumeric(const char* str) {
	if (str == nullptr)
		return false;
	bool numeric = scanInteger(&str);
	if (*str == '.') {
		++str;
		numeric = scanUnsignedInteger(&str) || numeric;
	}
	if (*str == 'e' || *str == 'E') {
		++str;
		numeric = numeric&&scanInteger(&str);
	}
	return numeric&&*str == '\0';
}
//21
void Recorder(int *pData, unsigned int length, bool (*func)(int)) {
	if (pData == nullptr || length == 0)
		return;
	int *pBegin = pData;
	int *pEnd = pData + length - 1;
	while (pBegin < pEnd) {
		while (pBegin < pEnd && !func(*pBegin))
			pBegin++;
		while (pBegin < pEnd && func(*pEnd))
			pEnd--;
		if (pBegin < pEnd) {
			int temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}
bool isEvent(int n) {
	return (n & 1) == 0;
}

//23
ListNode* MeetingNode(ListNode* pHead) {
	if (pHead == nullptr)
		return nullptr;
	ListNode* pSlow = pHead->m_pNext;
	if (pSlow == nullptr)
		return nullptr;
	ListNode* pFast = pSlow->m_pNext;
	while (pFast != nullptr&&pSlow != nullptr) {
		if (pFast == pSlow)
			return pFast;
		pSlow = pSlow->m_pNext;
		pFast = pFast->m_pNext;
		if (pFast != nullptr)
			pFast = pFast->m_pNext;
	}
	return nullptr;
}
ListNode* EntryNodeOfLoop(ListNode* pHead) {
	ListNode* meetingNode = MeetingNode(pHead);
	if (meetingNode == nullptr)
		return nullptr;
	int nodesInLoop = 1;
	ListNode* pNode1 = meetingNode;
	while (pNode1->m_pNext != meetingNode) {
		pNode1 = pNode1->m_pNext;
		++nodesInLoop;
	}
	pNode1 = pHead;
	for (int i = 0; i < nodesInLoop; ++i)
		pNode1 = pNode1->m_pNext;
	ListNode* pNode2 = pHead;
	while (pNode1 != pNode2) {
		pNode1 = pNode1->m_pNext;
		pNode2 = pNode2->m_pNext;
	}
	return pNode1;
}
//24
ListNode* ReverseList(ListNode* pHead) {
	ListNode* pReversedHead = nullptr;
	ListNode* pNode = pHead;
	ListNode* pPrev = nullptr;
	while (pNode != nullptr) {
		ListNode* pNext = pNode->m_pNext;
		if (pNext == nullptr)
			pReversedHead = pNext;
		pNode->m_pNext = pPrev;
		pPrev = pNode;
		pNode = pNext;
	}
	return pReversedHead;
}
//25
ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
	if (pHead1 == nullptr)
		return pHead2;
	if (pHead2 == nullptr)
		return pHead1;
	ListNode* pMergedHead = nullptr;
	if (pHead1->m_nValue < pHead2->m_nValue) {
		pMergedHead = pHead1;
		pMergedHead->m_pNext = Merge(pHead1->m_pNext, pHead2);
	}
	else {
		pMergedHead = pHead2;
		pMergedHead->m_pNext = Merge(pHead1, pHead2->m_pNext);
	}
	return pMergedHead;
}
//26
bool DoesTrere1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);
bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2) {
	bool result = false;
	if (pRoot1 != nullptr&&pRoot2 != nullptr) {
		if (pRoot1->m_nValue == pRoot2->m_nValue)
			result = DoesTrere1HaveTree2(pRoot1, pRoot2);
		if (!result)
			result = HasSubtree(pRoot1->m_pLeft, pRoot2);
		if (!result)
			result = HasSubtree(pRoot1->m_pRight, pRoot2);
	}
	return result;
}
bool DoesTrere1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2) {
	if (pRoot2 == nullptr)
		return true;
	if (pRoot1 == nullptr)
		return false;
	if (pRoot1->m_nValue!=pRoot2->m_nValue)
		return false;
	return DoesTrere1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) && DoesTrere1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}
//27
void MirrorRecursively(BinaryTreeNode* pNode) {
	if (pNode == nullptr)
		return;
	if (pNode->m_pLeft == nullptr&&pNode->m_pRight == nullptr)
		return;
	BinaryTreeNode* pTemp = pNode->m_pLeft;
	pNode->m_pLeft = pNode->m_pRight;
	pNode->m_pRight = pTemp;

	if (pNode->m_pLeft)
		MirrorRecursively(pNode->m_pLeft);
	if (pNode->m_pRight)
		MirrorRecursively(pNode->m_pRight);
}
//28
void printNumber(int number) {
	printf(number+ " ");
}
void PrintMatrixInCircle(int** numbers, int columns, int rows, int start) {
	int endX = columns - 1 - start;
	int endY = rows - 1 - start;

	//从左到右
	for (int i = start; i <= endX; ++i) {
		int number = numbers[start][i];
		printNumber(number);
	}
	//从上到下
	if (start < endY) {
		for (int i = start + 1; i < endY; ++i) {
			int number = numbers[i][endY];
			printNumber(number);
		}
	}
	//从右到左
	if (start < endX && start < endY) {
		for (int i = endX - 1; i >= start; --i) {
			int number = numbers[endY][i];
			printNumber(number);
		}
	}
	//从下到上
	if (start < endY && start < endY - 1) {
		for (int i = endY - 1; i >= start + 1; --i) {
			int number = numbers[i][start];
			printNumber(number);
		}
	}
}
void PrintMatrixClockwisely(int** numbers, int columns, int rows) {
	if (numbers == nullptr || columns <= 0 || rows <= 0)
		return;
	int start = 0;
	while (columns > start * 2 && rows > start * 2) {
		PrintMatrixInCircle(numbers, columns, rows, start);
		++start;
	}
}

//35 复制复杂链表
void CloneNodes(ComplexListNode* pHead) {
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr) {
		ComplexListNode* pCloned = new ComplexListNode();
		pCloned->m_nValue = pNode->m_nValue;
		pCloned->m_pNext = pNode->m_pNext;
		pCloned->m_pSibling = nullptr;

		pNode->m_pNext = pCloned;
		pNode = pCloned->m_pNext;
	}
}
void ConnectSiblingNOdes(ComplexListNode* pHead) {
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr) {
		ComplexListNode* pCloned = pNode->m_pNext;
		if (pNode->m_pSibling != nullptr) {
			pCloned->m_pSibling = pNode->m_pSibling->m_pNext;
		}
		pNode = pCloned->m_pNext;
	}
}
ComplexListNode* ReconnectNodes(ComplexListNode* pHead) {
	ComplexListNode* pNode = pHead;
	ComplexListNode* pClonedHead = nullptr;
	ComplexListNode* pClonedNode = nullptr;

	if (pNode != nullptr) {
		pClonedHead = pClonedNode = pNode->m_pNext;
		pNode->m_pNext = pClonedNode->m_pNext;
		pNode = pNode->m_pNext;
	}
	while (pNode != nullptr) {
		pClonedNode->m_pNext = pNode->m_pNext;
		pClonedNode = pClonedNode->m_pNext;
		pNode->m_pNext = pClonedNode->m_pNext;
		pNode = pNode->m_pNext;
	}
	return pClonedHead;
}
//36
struct BInaryTreeNode {
	int m_nValue;
	BInaryTreeNode* m_pLeft;
	BInaryTreeNode* m_pRight;
};
void ConvertNode(BInaryTreeNode* pNode, BInaryTreeNode** pLastNodeInList);

BInaryTreeNode* Convert(BInaryTreeNode* pRootOfTree) {
	BInaryTreeNode* pLastNodeInList = nullptr;
	ConvertNode(pRootOfTree, &pLastNodeInList);

	BInaryTreeNode* pHeadOfList = pLastNodeInList;
	while (pHeadOfList != nullptr && pHeadOfList->m_pLeft != nullptr) {
		pHeadOfList = pHeadOfList->m_pLeft;
	}
	return pHeadOfList;
}
void ConvertNode(BInaryTreeNode* pNode, BInaryTreeNode** pLastNodeInList) {
	if (pNode == nullptr)
		return;
	BInaryTreeNode* pCurrent = pNode;
	if (pCurrent->m_pLeft != nullptr)
		ConvertNode(pCurrent->m_pLeft, pLastNodeInList);

	pCurrent->m_pLeft = *pLastNodeInList;
	if (*pLastNodeInList != nullptr)
		(*pLastNodeInList)->m_pRight = pCurrent;
	*pLastNodeInList = pCurrent;
	if (pCurrent->m_pRight != nullptr)
		ConvertNode(pCurrent->m_pRight, pLastNodeInList);
}

//38
void Permutation(char* pStr, char* pBegin);
void Permutation(char* pStr) {
	if (pStr == nullptr)
		return;
	Permutation(pStr, pStr);
}
void Permutation(char* pStr, char* pBegin) {
	if (*pBegin == '\0') {
		printf("%s\n", pStr);
	}
	else {
		for (char* pCh = pBegin; *pCh != '\0'; ++pCh) {
			char temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;

			Permutation(pStr, pBegin + 1);

			temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;
		}
	}
}
//39_2
int MoreThanHalfNum(int* numbers, int length) {
	//
	int result = numbers[0];
	int times = 1;
	for (int i = 1; i < length; ++i) {
		if (times == 0) {
			result = numbers[i];
			times = 1;
		}
		else if(numbers[i]==result) {
			times++;
		}
		else {
			times--;
		}
		cout << i<<"::"<<result<<endl;
	}
	return result;
	//
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
	//cout << "a=" << a[0] << endl << "b=" << a[1] << endl;
	//10
	int data[6] = { 3, 1, 2, 6, 9, 7 };
	QuickSort(data, 6, 0, 5);
	for (int i = 0; i < 6; ++i) {
		cout << data[i]<<"-";
	}cout << endl;
	//12
	char* matrix = "abtgcfcsjdeh";
	char* str = "bfce";
	if (hasPath(matrix, 3, 4, str))
		cout << "There is a path found" << endl;
	else
		cout << "No path found" << endl;

	char num[] = "56";
	int mn = num[1] - '0' + 1;
	cout << "mn = " << mn << endl;
	//17
	//Print1ToMaxOfNDigits(3);
	//19
	if (match("aaa", "ab*ac*a"))
		cout << "match!" << endl;
	else
		cout << "not match!" << endl;
	//20
	if (isNumeric("123.45e+7"))
		cout << "It is a number!" << endl;
	else
		cout << "It is not a number!" << endl;
	//21
	int mData[] = { 1, 2, 3, 4, 5, 6, 7 };
	Recorder(mData, 7, isEvent);
	
	for each (int index in mData)
	{
		cout << index << "  ";
	}cout << endl;

	//38
	char dString[] = "abcd";
	Permutation(dString, dString);
	//39
	int mNum[] = { 1,2,3,2,2,2,5,4,2 };
	cout << MoreThanHalfNum(mNum, 9)<<endl;

	return 0;
}
