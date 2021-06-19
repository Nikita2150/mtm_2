
#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include "node.h"
#include <cassert>
#include <stdexcept>

#include <iostream>
namespace mtm
{
	const bool ENDED = true;

	template<class T>
	class SortedList
	{

		Node<T>* list;

	public:
		class const_iterator
		{
			const SortedList* sorted_list;
			Node<T>* current_node;

			explicit const_iterator(const SortedList* sorted_list, bool ended = false) : sorted_list(sorted_list),
																	current_node(nullptr)
			{
				if(!ended && sorted_list->list != nullptr)
				{
					current_node = new Node<T>(*(sorted_list->list));
				}
			}
			friend class SortedList<T>;

		public:
			const_iterator(const const_iterator& iterator) : sorted_list(iterator.sorted_list),
															current_node(nullptr) 
			{
				if(iterator.current_node != nullptr)
				{
					this->current_node = new Node<T>(*iterator.current_node);
				}
			}

			const_iterator& operator=(const const_iterator& iterator)
			{
				Node<T>* temp_node = nullptr;
				if(iterator.current_node != nullptr)
				{
					temp_node = new Node<T>(*iterator.current_node);
					Node<T>::destroyList(this->current_node);
				}
				sorted_list = iterator.sorted_list;
				current_node = temp_node;
				return *this;
			}

			~const_iterator() 
			{
				Node<T>::destroyList(this->current_node);
			}
			const_iterator& operator++()
			{
				if(this->current_node == nullptr)
				{
					throw std::out_of_range("Out of bounds");
				}
				Node<T>* temp = this->current_node;
				this->current_node = this->current_node->getNextIterator();
				delete temp; 

				return *this;

			}
			const_iterator operator++(int)
			{
				if(this->current_node == nullptr)
				{
					throw std::out_of_range("Out of bounds");
				}
				const_iterator result = *this;
				++*this;
				return result;
			}
			bool operator==(const const_iterator& iterator) const
			{
				if(this->sorted_list != iterator.sorted_list)
				{
					return false; //maybe should throw something
				}
				if(this->current_node == NULL || iterator.current_node == NULL)
				{
					return this->current_node == NULL && iterator.current_node == NULL;
				}
				return !(this->current_node->getCurrentIteratorData() < iterator.current_node->getCurrentIteratorData()
				 || iterator.current_node->getCurrentIteratorData()< this->current_node->getCurrentIteratorData());
			}
			const T& operator*() const
			{
				if(this->current_node == nullptr)
				{
					throw std::out_of_range("Out of bounds");
				}
				return this->current_node->getCurrentIteratorData();
			}
		};



		SortedList<T>() : list(nullptr) { }
		~SortedList<T>()
		{
			Node<T>::destroyList(this->list);
		}
		SortedList<T>(const SortedList<T>& sorted_list) : list(nullptr)
		{
			if(sorted_list.list != nullptr)
			{
				this->list = new Node<T>(*sorted_list.list);
			}
		}
		SortedList<T>& operator=(const SortedList<T>& sorted_list)
		{
			Node<T>* list_temp = nullptr;
			if(sorted_list.list != nullptr)
			{
				list_temp = new Node<T>(*sorted_list.list);
			}
			Node<T>::destroyList(this->list);
			this->list = list_temp;
			return *this;
		}

		void insert(T new_data)
		{
			if(list == nullptr)
			{

				list = new Node<T>(new_data);
			}
			else
			{
				list = (*list).add_element_sorted(new_data);
			}
		}

		void remove(const const_iterator& iterator)
		{
			if(list != nullptr)
			{
				list = (*list).removeNode(*iterator);
			}
		}

		int length() const
		{
			if(list == nullptr)
			{
				return 0;
			}
			return (*list).length();
		}

		template<typename Predicate>
		SortedList<T> filter(Predicate pred) const
		{
			SortedList<T> new_list = SortedList<T>();
			const_iterator iterator = this->begin();
			for(; !(iterator == this->end()); ++iterator)
			{
				if(pred(*iterator))
				{
					new_list.insert(*iterator);
				}
			}
			return new_list;
		}

		template<typename TransformationFunction>
		SortedList<T> apply(TransformationFunction func) const
		{
			SortedList<T> new_list = SortedList<T>();
			const_iterator iterator = this->begin();
			for(; !(iterator == this->end()); ++iterator)
			{
				new_list.insert(func(*iterator));
			}
			return new_list;
		}
		const_iterator begin() const
		{
			return const_iterator(this);
		}
		const_iterator end() const
		{
			return const_iterator(this, ENDED);
		}


	};
}




#endif //SORTEDLIST_H
