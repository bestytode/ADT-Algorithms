#pragma once

#include <vector>
#include <unordered_set>

using namespace std;

// simple Node struct
struct ListNode 
{
	int val;
	ListNode* next;

	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Time Complexity: O(n), where n is the number of nodes
// Space Complexity: O(1)
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

    // to delete head node
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
	
	ListNode* evenHead = head->next; 
	ListNode* odd = head; 
	ListNode* even = evenHead;  
	while (even != nullptr && even->next != nullptr) {
		odd->next = even->next;
		odd = odd->next;
		even->next = odd->next;
		even = even->next;
	}
	odd->next = evenHead; // connect odd to evenhead 
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

// Time complexity: O(max(m ,n)), where m and n are the lengths of the two linked lists.
// Space complexity: O(max(m,n)).
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode* dummyHead = new ListNode(0);
	ListNode* current = dummyHead;

	int carry = 0; // init carry with 0

	while (l1 || l2) {
		int x = l1 ? l1->val : 0;
		int y = l2 ? l2->val : 0;
		int sum = x + y + carry;

		carry = sum / 10; // if sum > 10, carry will be 1 in the next digit, otherwise will be 0 in the next digit
		current->next = new ListNode(sum % 10); // sum will only add one digit to current
		current = current->next;

		if (l1->next) l1 = l1->next;
		if (l2->next) l2 = l2->next;
	}

	// if any carry left, add a new digit for it
	if (carry > 0) current->next = new ListNode(carry);

	// return the 2nd ListNode
	return dummyHead->next;
}