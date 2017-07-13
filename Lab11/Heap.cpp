#include "Heap.h"

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::Heap ( int maxNumber = DEFAULT_MAX_HEAP_SIZE )
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DataType[maxSize];
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::Heap ( const Heap& other )
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
Heap<DataType,KeyType,Comparator>& Heap<DataType,KeyType,Comparator>::operator= ( const Heap& other )
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
Heap<DataType,KeyType,Comparator>::~Heap ()
{
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::insert ( const DataType &newDataItem )
    throw ( logic_error )
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
DataType Heap<DataType,KeyType,Comparator>::remove () throw ( logic_error )
{
	DataType temp;
	return temp;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::clear ()
{
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>::isEmpty () const
{
	return false;
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>::isFull () const
{
	return false;
}

#include "show11.cpp"