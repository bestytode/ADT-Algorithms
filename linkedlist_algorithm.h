#pragma once

#include <vector>
#include <unordered_set>

using namespace std;

//环形链表
bool hasCycle(ListNode* head);

//反转链表
ListNode* reverseList(ListNode* head);

//移除链表元素
struct ListNode* removeElements(struct ListNode* head, int val);

//奇偶链表
ListNode* oddEvenList(ListNode* head);

//回文链表
bool isPalindrome(ListNode* head);

// 83.删除排序链表中的重复元素
ListNode* deleteDuplicates(ListNode* head);

struct ListNode 
{
	int val;
	ListNode* next;

	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

int getLength(ListNode* head)
{
	int length = 0;
	while (head) {
		++length;
		head = head->next;
	}
	return length;
}

bool hasCycle(ListNode* head) 
{
	unordered_set<ListNode*>seen;
	while (head) {
		if (seen.count(head))
			return true;

		seen.insert(head);
		head = head->next;
	}
	return false;
}

bool hasCycle(ListNode* head) 
{
	if (!head || !head->next)
		return false;

	ListNode* slow = head;
	ListNode* fast = head->next;

	while (fast && fast->next) {
		if (slow == fast)
			return true;

		slow = slow->next;
		fast = fast->next->next;
	}
	return false;
}

ListNode* removeNthFromEnd(ListNode* head, int n) 
{
	int length = getLength(head);

    //若要删除的是头节点
	if (length == n) {
		head = head->next;
		return head;
	}
	ListNode* curr = head;
	for (int i = 0; i < length - n - 1; ++i)
		curr = curr->next;
	curr->next = curr->next->next;
	return head;
}

ListNode* reverseList(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
		return head;
	
	ListNode* prev = nullptr;
	ListNode* curr = head;
	while (curr != nullptr) {
		ListNode* next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}

struct ListNode* removeElements(struct ListNode* head, int val)
{
	if (head == nullptr)
		return nullptr;
	if (head != nullptr && head->val == val)
		head = head->next;
		
	ListNode* curr = head;
	while (curr->next != nullptr) {
		if (curr->next->val == val)
			curr->next = curr->next->next;
		else
			curr = curr->next;
	}
	return head;
}

ListNode* oddEvenList(ListNode* head)
{
	if (head == nullptr)
		return head;
	
	ListNode* evenHead = head->next; //偶项链表的头节点
	ListNode* odd = head; //维护奇项的指针
	ListNode* even = evenHead;  //维护偶项的指针
	while (even != nullptr && even->next != nullptr) {
		odd->next = even->next;
		odd = odd->next;
		even->next = odd->next;
		even = even->next;
	}
	odd->next = evenHead; //将最后一个奇项与偶项链表的头节点连接起来
	return head;
}

bool isPalindrome(ListNode* head)
{
	vector<int> vals;
	while (head != nullptr) {
		vals.emplace_back(head->val);
		head = head->next;
	}
	for (int i = 0, j = (int)vals.size() - 1; i < j; ++i, --j) {
		if (vals[i] != vals[j])
			return false;
	}
	return true;
}

ListNode* deleteDuplicates(ListNode* head)
{
	if (!head)
		return head;

	ListNode* curr = head;
	while (curr->next) {
		if (curr->val == curr->next->val)
			curr->next = curr->next->next;
		else
			curr = curr->next;
	}
	return head;
}