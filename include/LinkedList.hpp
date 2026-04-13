#pragma once

#include <filesystem>
#include <vector>
#include <fstream>

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

		void onAdd(int randIndex);

	public:
		LinkedList();

		void addNode(std::string_view data, int randIndex);

		~LinkedList();

		friend std::ostream& operator <<(std::ostream& stream, const LinkedList& list);

		friend std::ofstream& operator <<(std::ofstream& stream, const LinkedList& list);
	};
	
}
