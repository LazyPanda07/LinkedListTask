#include "LinkedList.hpp"

#include <format>

namespace list
{
	LinkedList::PendingIndex::PendingIndex(ListNode* node, int index) :
		node(node),
		index(index)
	{

	}

	LinkedList::ListNode* LinkedList::find(int index) const
	{
		ListNode* node = head;

		for (int i = 0; i < index; i++)
		{
			node = node->next;
		}

		return node;
	}

	void LinkedList::addPendingRandIndex(ListNode* node, int index)
	{
		if (index != -1 && index >= size)
		{
			pendingRandIndices.emplace_back(node, index);
		}
	}

	LinkedList::LinkedList() :
		head(new ListNode()),
		current(head),
		size(0)
	{

	}

	void LinkedList::addNode(std::string_view data, int randIndex)
	{
		if (current->data.empty())
		{
			current->data = data;

			size = 1;

			this->addPendingRandIndex(current, randIndex);

			return;
		}

		ListNode* node = new ListNode();
		node->data = data;

		current->next = node;
		node->prev = current;

		current = node;

		size++;

		this->addPendingRandIndex(current, randIndex);

		if (randIndex < size)
		{
			current->rand = this->find(randIndex);
		}

		if (pendingRandIndices.size())
		{
			std::vector<int> removes;

			for (auto& [pendingNode, pendingIndex] : pendingRandIndices)
			{
				if (pendingIndex < size)
				{
					removes.push_back(pendingIndex);

					pendingNode->rand = this->find(pendingIndex);
				}
			}

			for (int removeIndex : removes)
			{
				std::erase_if(pendingRandIndices, [removeIndex](const PendingIndex& index) { return index.index == removeIndex; });
			}
		}
	}

	LinkedList::~LinkedList()
	{
		ListNode* node = head;

		while (node)
		{
			ListNode* next = node->next;

			delete node;

			node = next;
		}
	}

	std::ostream& operator <<(std::ostream& stream, const LinkedList& list)
	{
		if (!list.size)
		{
			return stream;
		}

		const LinkedList::ListNode* node = list.head;
		size_t index = 0;

		while (node)
		{
			stream << std::format("{}: \"{}\" => \"{}\"\n", index, node->data, (node->rand ? node->rand->data : "nullptr"));

			node = node->next;
			index++;
		}

		return stream;
	}

	std::ofstream& operator <<(std::ofstream& stream, const LinkedList& list)
	{
		if (!list.size)
		{
			return stream;
		}
		auto writeNodeData = [&stream](const LinkedList::ListNode* node)
			{
				uint64_t dataSize = node->data.size();

				stream.write(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
				stream.write(node->data.data(), dataSize);
			};

		const LinkedList::ListNode* node = list.head;

		while (node)
		{
			bool hasRand = static_cast<bool>(node->rand);

			stream.write(reinterpret_cast<char*>(&hasRand), sizeof(hasRand));
			
			writeNodeData(node);
			
			if (hasRand)
			{
				writeNodeData(node->rand);
			}

			node = node->next;
		}

		return stream;
	}
}
