#include "Heap.h"

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber = DEFAULT_MAX_HEAP_SIZE)
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DataType[maxSize];
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::Heap(const Heap& other)
{
	maxSize = other.maxSize;
	size = other.size;

	dataItems = new DataType[maxSize];
	for (int i = 0; i < size; i++)
	{
		dataItems[i] = other.dataItems[i];
	}

}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator= (const Heap& other)
{
	maxSize = other.maxSize;
	size = other.size;
	dataItems = new DataType[maxSize];
	for (int i = 0; i < size; i++)
	{
		dataItems[i] = other.dataItems[i];
	}
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::~Heap()
{
	clear();
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::insert(const DataType &newDataItem)
throw (logic_error)
{
	int parentj, j;
	if (maxSize <= size)
		throw logic_error("FULL");

	else {
		j = size;

		parentj = (j - 1) / 2;
		for (; j > 1 && comparator(newDataItem.getPriority(), dataItems[parentj].getPriority()); j = parentj)
		{
			parentj = (j - 1) / 2;
			dataItems[j] = dataItems[parentj];
		}

		dataItems[j] = newDataItem;
		size++;

	}

}

template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType, KeyType, Comparator>::remove() throw (logic_error)
{
	if (isEmpty())
	{
		throw logic_error("Empty");
	}

	size--;
	DataType p = dataItems[0];
	dataItems[0] = dataItems[size];
	int i = 0;
	while (size > i)
	{
		if ((i * 2) + 2 <= size)
		{
			if (comparator(dataItems[i].getPriority(), dataItems[(i * 2) + 1].getPriority()) && comparator(dataItems[i].getPriority(), dataItems[(i * 2) + 2].getPriority()))
			{
				return p;
			}
			else if (comparator(dataItems[(i * 2) + 2].getPriority(), dataItems[(i * 2) + 1].getPriority()))
				{
					DataType temp = dataItems[i];
					dataItems[i] = dataItems[(i * 2) + 2];
					dataItems[(i * 2) + 2] = temp;
					i = (i * 2) + 2;
				}
			//less
			else
			{
				DataType temp = dataItems[i];
				dataItems[i] = dataItems[i + 1];
				dataItems[(i * 2) + 1] = temp;
				i = (i * 2) + 1;
			}
		}
		else if ((i * 2) + 1 <= size)
			{
				if (comparator(dataItems[(i * 2) + 1].getPriority(), dataItems[i].getPriority()))
				{
					DataType temp = dataItems[i];
					dataItems[i] = dataItems[(i * 2) + 1];
					dataItems[(i * 2) + 1] = temp;
					i = (i * 2) + 1;
				}
				else
				{
					return p;
				}
			}
		else
		{
			return p;
		}
	}
	return p;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::clear ()
{
	delete[]dataItems;
	dataItems = new DataType[maxSize];
	size = NULL;
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>::isEmpty () const
{

	return (size == 0);
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>::isFull () const
{
	return (size ==maxSize);
}
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::writeLevels() const               // Output in level order
{
	int countLevel = 1;
	int print = 0;
	for (int i = 0; i < size; i++, print++)
	{
		if (print == countLevel)
		{
			cout << "\n";
			print = 0;
			countLevel *= 2;
		}
		cout << dataItems[i].getPriority() << " ";
	}
	cout << "\n";
}
#include "show11.cpp"