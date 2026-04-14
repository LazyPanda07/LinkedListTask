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

		LinkedList(const LinkedList&) = delete;

		LinkedList(LinkedList&& other) noexcept;

		LinkedList& operator =(const LinkedList&) = delete;

		LinkedList& operator =(LinkedList&& other) noexcept;

		void addNode(std::string_view data, int randIndex);

		~LinkedList();

		friend std::ostream& operator <<(std::ostream& stream, const LinkedList& list);

		/**
		 * @brief Serialize to binary file. Structure: <1 byte> - has rand, <8 bytes> - data size, <data size bytes> - data. If has rand: <8 bytes> - rand data size, <rand data size bytes> - rand data
		 * @param stream 
		 * @param list 
		 * @return 
		 */
		friend std::ofstream& operator <<(std::ofstream& stream, const LinkedList& list);
	};
}
