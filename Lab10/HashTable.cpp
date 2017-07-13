
#include "HashTable.h"

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize) :tableSize(initTableSize)
{
	dataTable = new BSTree<DataType, KeyType>[tableSize];
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
{
	tableSize = other.tableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
	copyTable(other);
}

template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other)
{
	clear();
	copyTable(other);
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
	clear();
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{
	unsigned int loc = DataType::hash(newDataItem.getKey()) % tableSize;
	dataTable[loc].insert(newDataItem);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	unsigned int loc = DataType::hash(deleteKey) % tableSize;
	return dataTable[loc].remove(deleteKey);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
{
	unsigned int loc = DataType::hash(searchKey) % tableSize;
	return dataTable[loc].retrieve(searchKey, returnItem);
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
{
	for (int i = 0; i < tableSize; i++)
	{
		dataTable[i].clear();
	}
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const
{
	for (int i = 0; i < tableSize; i++)
	{
		if (!dataTable[i].isEmpty())
			return false;
	}
	return true;
}

#include "show10.cpp"

template <typename DataType, typename KeyType>
double HashTable<DataType, KeyType>::standardDeviation() const
{
	int t = 0;
	double sum = 0;

	for (int i = 0; i < tableSize; i++)
	{
		t += dataTable[i].getCount();
	}
	double load = t / tableSize; 
	for (int i = 0; i < tableSize; i++)
	{
		int n = dataTable.getCount();
		sum += (n - load) *(n - load);
	}
	return sqrt(sum / (tableSize - 1));

}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::copyTable(const HashTable& source)
{
	delete dataTable; //get rid of the old datatable

	
	dataTable = new BSTree<DataType, KeyType>[source.table];

	//copy every element
	for (int i = 0; i < source.tableSize; i++)
		dataTable[i] = source.dataTable[i];

}
