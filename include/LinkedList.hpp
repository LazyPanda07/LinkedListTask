#pragma once

#include <filesystem>
#include <vector>
#include <ostream>

namespace list
{
	class LinkedList
	{
	private:
		struct ListNode
		{
			ListNode* prev = nullptr;
			ListNode* next = nullptr;
			ListNode* rand = nullptr;
			std::string data;
		};

		struct PendingIndex
		{
			ListNode* node;
			int index;

			PendingIndex(ListNode* node, int index);
		};

	private:
		std::vector<PendingIndex> pendingRandIndices;
		ListNode* head;
		ListNode* current;
		size_t size;

	private:
		ListNode* find(int index) const;

		void addPendingRandIndex(ListNode* node, int index);

	public:
		LinkedList();

		void addNode(std::string_view data, int randIndex);

		~LinkedList();

		friend std::ostream& operator <<(std::ostream& stream, const LinkedList& list);
	};
	
}
