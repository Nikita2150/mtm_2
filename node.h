#ifndef NODE_H
#define NODE_H



namespace mtm
{
	

	template<class T>
	class Node
	{
		T data;
		Node<T>* next;
	public:
		explicit Node<T>(T data) : data(data), next(nullptr) { }

		Node<T>(const Node<T>& node) : data(node.data), next(nullptr)
		{
			Node<T>* this_head = this;
			Node<T>* temp = node.next;
			while(temp != nullptr)
			{
				this_head->next = new Node<T>(temp->data);
				this_head = this_head->next;
				temp = temp->next;
			}
		}

		~Node()
		{		}

		Node<T>* add_element_sorted(T new_data)
		{
			Node<T>* new_node = new Node<T>(new_data);
			if(new_data < this->data)
			{
				new_node->next = this;
				return new_node;
			}
			Node<T>* temp = this;
			while(temp->next != nullptr)
			{
				if(new_data < temp->next->data)
				{
					Node<T>* temp_after_add = temp->next;
					temp->next = new_node;
					new_node->next = temp_after_add;
					return this;
				}
				temp = temp->next;
			}
			temp->next = new_node;
			return this;
		}

		Node<T>* removeNode(T data)
		{
			if(!(this->data < data || data < this->data))
			{
				Node<T>* to_return = this->next;
				this->next = nullptr;
				destroyList(this);
				return to_return;
			}
			Node<T>* temp = this;
			while(temp->next != nullptr)
			{
				if(!(temp->next->data < data || data < temp->next->data))
				{
					Node<T>* toDelete = temp->next;
					temp->next = temp->next->next;
					toDelete->next = nullptr;
					destroyList(toDelete);
					return this;
				}
				temp = temp->next;
			}
			return this;
		}
		int length() const
		{
			int counter = 1;
			Node<T>* temp = this->next;
			while(temp != nullptr)
			{
				counter++;
				temp = temp->next;
			}
			return counter;
		}
		static void destroyList(Node<T>* list)
		{
			while(list != nullptr)
			{
				Node<T>* next_element = list->next;
				delete list;
				list = next_element;
			}
		}
		const T& getCurrentIteratorData() const
		{
			return this->data;
		}
		Node<T>* const getNextIterator() const
		{
			return this->next;
		}
	};
}


#endif //NODE_H
