#ifndef __HASHTABLA_HPP__
#define __HASHTABLA_HPP__
#include <vector>
#include <list>
#include <string>
using namespace std;

template <typename HashedObj>
class HashTabla {
private:
	vector<list<HashedObj>> theLists;   // The array of Lists
	int  currentSize;

public:
	explicit HashTabla(int size = 101) : currentSize{ 0 }
	{
		theLists.resize(101);
	}

	bool contains(const HashedObj& x) const
	{
		auto& whichList = theLists[myhash(x)];
		return find(begin(whichList), end(whichList), x) != end(whichList);
	}

	void makeEmpty()
	{
		for (auto& thisList : theLists)
			thisList.clear();
	}

	bool insert(const HashedObj& x)
	{
		auto& whichList = theLists[myhash(x)];
		if (find(begin(whichList), end(whichList), x) != end(whichList))
			return false;
		whichList.push_back(x);

		// Rehash; 
		if (++currentSize > theLists.size())
			rehash();

		return true;
	}

	bool insert(HashedObj&& x)
	{
		auto& whichList = theLists[myhash(x)];
		if (find(begin(whichList), end(whichList), x) != end(whichList))
			return false;
		whichList.push_back(std::move(x));

		// Rehash; 
		if (++currentSize > theLists.size())
			rehash();

		return true;
	}

	bool remove(const HashedObj& x)
	{
		auto& whichList = theLists[myhash(x)];
		auto itr = find(begin(whichList), end(whichList), x);

		if (itr == end(whichList))
			return false;

		whichList.erase(itr);
		--currentSize;
		return true;
	}

	void DispAll() {
		int pos = 0;
		for (auto& thisList : theLists) {
			cout << "Key: " + to_string(pos) << " | ";
			for (auto& it : theLists[pos]) {
				cout << it << ",";
			}
			cout << endl;
			pos++;
		}
	}

private:
	/**
	* Internal method to test if a positive number is prime.
	* Not an efficient algorithm.
	*/
	bool isPrime(int n)
	{
		if (n == 2 || n == 3)
			return true;

		if (n == 1 || n % 2 == 0)
			return false;

		for (int i = 3; i * i <= n; i += 2)
			if (n % i == 0)
				return false;

		return true;
	}

	/**
	* Internal method to return a prime number at least as large as n.
	* Assumes n > 0.
	*/
	int nextPrime(int n)
	{
		if (n % 2 == 0)
			++n;

		for (; !isPrime(n); n += 2)
			;

		return n;
	}

	void rehash()
	{
		vector<list<HashedObj>> oldLists = theLists;

		// Create new double-sized, empty table
		theLists.resize(nextPrime(2 * theLists.size()));
		for (auto& thisList : theLists)
			thisList.clear();

		// Copy table over
		currentSize = 0;
		for (auto& thisList : oldLists)
			for (auto& x : thisList)
				insert(std::move(x));
	}

	/**
	* A hash routine for string objects.
	*/
	size_t hash(const HashedObj& key) const
	{
		size_t hashVal = 0;

		for (char ch : key)
			hashVal = 37 * hashVal + ch;

		return hashVal;
	}

	/**
	* A hash routine for ints.
	*/
	size_t hash(int key)
	{
		return key;
	}

	size_t myhash(const HashedObj& x) const {
		size_t hashVal = hash(x);
		hashVal %= theLists.size();
		if (hashVal < 0)
			hashVal += theLists.size();
		return(hashVal);
	}
};

#endif // !__HASHTABLA_HPP__