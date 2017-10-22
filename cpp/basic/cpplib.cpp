#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <iostream>
#include <string>

#include <cstdlib>

using namespace std;
using namespace std::placeholders;

// INSERT_ELEMENTS (collection, first, last)
// - fill values from first to last into the collection
// - NOTE: NO half-open range
template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
	for (int i = first; i <= last; ++i) {
		coll.insert(coll.end(), i);
	}
}

// PRINT_ELEMENTS()
// - prints optional string optcstr followed by
// - all elements of the collection coll
// - separated by spaces
template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
	const std::string& optcstr = "")
{
	std::cout << optcstr;
	for (auto elem : coll) {
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}

// PRINT_MAPPED_ELEMENTS()
// - prints optional string optcstr followed by
// - all elements of the key/value collection coll
// - separated by spaces
template <typename T>
inline void PRINT_MAPPED_ELEMENTS(const T& coll,
	const std::string& optcstr = "")
{
	std::cout << optcstr;
	for (auto elem : coll) {
		std::cout << '[' << elem.first
			<< ',' << elem.second << "] ";
	}
	std::cout << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////
void print(int elem) 
{
	cout << elem << " ";
}

class Print {
public:
	void operator() (int elem) const {
		cout << elem << ' ';
	}
};

class MeanValue {
private:
	long num;
	long sum;
public:
	MeanValue() : num(0), sum(0) {
	}

	void operator() (int elem) {
		num++;
		sum += elem;
	}

	operator double() {
		return static_cast<double>(sum) / static_cast<double>(num);
	}
};

void t_foreach() 
{
	vector<int> coll;
	INSERT_ELEMENTS(coll, 1, 9);
	//lambda
	for_each(coll.begin(), coll.end(), [](int elem) {cout << elem << " "; });
	cout << endl;
	//function
	for_each(coll.begin(), coll.end(), print);
	cout << endl;

	//pass by ref
	for_each(coll.begin(), coll.end(), [](int& elem) { elem += 10; });
	PRINT_ELEMENTS(coll);
	//pass by ref with value arg
	for_each(coll.begin(), coll.end(), [=](int& elem) { elem += *coll.begin(); });
	PRINT_ELEMENTS(coll);
	//pass by ref with ref arg
	for_each(coll.begin(), coll.end(), [&](int& elem) { elem += *coll.begin(); });
	PRINT_ELEMENTS(coll);
	//function object
	for_each(coll.begin(), coll.end(), Print());
	cout << endl;
	//avage
	double mv = for_each(coll.begin(), coll.end(),MeanValue());
	cout << "mean value: " << mv << endl;
}

/////////////////////////////////////////////////////////////////////////////////
void t_count()
{
	vector<int> coll;
	int num = 0;

	INSERT_ELEMENTS(coll, 1, 9);
	PRINT_ELEMENTS(coll);

	num = count(coll.begin(), coll.end(), 4);
	cout << "num of elem equal 4 = " << num << endl;

	num = count_if(coll.begin(), coll.end(), [](int elem) {return elem % 2 == 0; });
	cout << "num of elem with even value = " << num << endl;

	num = count_if(coll.begin(), coll.end(), [](int elem) {return elem > 4; });
	cout << "num of elem greater than 4 = " << num << endl;

}

////////////////////////////////////////////////////////////////////////////////
bool absLess(int i, int j) 
{
	return abs(i) < abs(j);
}


void t_minmax() 
{
	deque<int> coll;

	INSERT_ELEMENTS(coll, 2, 6);
	INSERT_ELEMENTS(coll, -3, 6);

	PRINT_ELEMENTS(coll);

	cout << "min: " << *min_element(coll.begin(), coll.end()) << endl;
	cout << "max: " << *max_element(coll.begin(), coll.end()) << endl;

	auto mm = minmax_element(coll.begin(), coll.end());
	cout << "min: " << *mm.first << endl;
	cout << "max: " << *mm.second<< endl;
	cout << "distance: " << distance(mm.first, mm.second) << endl;

	cout << "min with abs: " << *min_element(coll.begin(), coll.end(),absLess) << endl;
	cout << "max with abs: " << *max_element(coll.begin(), coll.end(),absLess) << endl;

}
////////////////////////////////////////////////////////////////////////////////

void t_find() 
{
	list<int> coll;

	INSERT_ELEMENTS(coll, 1, 9);
	INSERT_ELEMENTS(coll, 1, 9);

	PRINT_ELEMENTS(coll, "coll: ");

	list<int>::iterator pos1;
	pos1 = find(coll.begin(), coll.end(),4);

	list<int>::iterator pos2;
	if (pos1 != coll.end()) 
	{
		pos2 = find(++pos1, coll.end(),4);
	}

	if (pos1 != coll.end() && pos2 != coll.end()) 
	{
		copy(--pos1, ++pos2,ostream_iterator<int>(cout, " "));
		cout << endl;
	}

	pos1 = find_if(coll.begin(), coll.end(), [](int elem) { return elem % 3 == 0; });
	cout << "the "<< distance(coll.begin(), pos1) + 1 << ". element is the first divisible by 3" << endl;

	pos1 = find_if(coll.begin(), coll.end(), bind(greater<int>(), _1, 3));
	cout << "the " << distance(coll.begin(), pos1) + 1 << ". element is the first greater than 3" << endl;

	pos1 = find_if(coll.begin(), coll.end(), bind(less<int>(), 5, _1));
	cout << "the " << distance(coll.begin(), pos1) + 1 << ". element is the first not less than 5" << endl;

}

////////////////////////////////////////////////////////////////////////////////
void t_seach_n() 
{
	deque<int> coll;
	coll = { 1,2,7,6,3,9,5,7,7,7,3,6 };
	PRINT_ELEMENTS(coll);

	deque<int>::iterator pos;

	pos = search_n(coll.begin(), coll.end(), 3, 7);
	if (pos != coll.end())
	{
		cout << "first three consecutive seven offset = " << distance(coll.begin(), pos) + 1 << endl;
	}

	pos = search_n(coll.begin(), coll.end(), 4, 0, [](int elem, int value) { return elem % 2 == 1; });
	if (pos != coll.end())
	{
		cout << "first four consecutive odd elements are: ";
		for (int i = 0; i < 4; ++i, ++pos) 
		{
			cout << *pos << ' ';
		}
	}


}

bool checkEven(int elem, bool even)
{
	if (even) {
		return elem % 2 == 0;
	}
	else {
		return elem % 2 == 1;
	}
}

void t_seach() 
{
	deque<int> coll;
	list<int> subcoll;

	INSERT_ELEMENTS(coll, 1, 7);
	INSERT_ELEMENTS(coll, 1, 7);
	INSERT_ELEMENTS(subcoll, 3, 6);

	deque<int>::iterator pos;
	pos = search(coll.begin(), coll.end(), subcoll.begin(), subcoll.end());
	while (pos != coll.end())
	{
		cout << "subcoll found starting with element " << distance(coll.begin(), pos) + 1 << endl;
		pos = search(++pos, coll.end(), subcoll.begin(), subcoll.end());
	}

	vector<int> vcoll{ 1,2,3,4,5,6,7,8,9 };
	bool checkEvenArgs[3] = { true, false, true };
	vector<int>::iterator vpos;
	vpos = search(vcoll.begin(), vcoll.end(), checkEvenArgs, checkEvenArgs + 3, checkEven);

	while (vpos != vcoll.end()) {
		cout << "subrange found starting with element " << distance(vcoll.begin(), vpos) + 1 << endl;
		vpos = search(++vpos, vcoll.end(), checkEvenArgs, checkEvenArgs + 3, checkEven);
	}
}
