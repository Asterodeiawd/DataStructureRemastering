#include <list>
#include <iostream>
#include "ForwardList.hpp"

using std::cout;
using std::endl;

int main()
{
	ForwardList<int> list;
	list.append(1).append(3).append(8);
	cout << list.count() << endl;
	cout << list.find(1) << endl;

	ListNode<int>* pos = list.find(3);
	list.insert(2, pos);

	cout << list;
	list.remove(1);
	cout << list;
	list.insert(9, list.find(2));

	list.append(6);

	cout << list;

	ForwardList<int> list2;
	std::cout << "list2 count: " << list2.count();
	list2.remove(1);

	double b[] = { 3.1, 5, 8.8, 12, 33.6 };
	ForwardList<double> l3(b, sizeof(b) / sizeof(b[0]));
	cout << l3;

	l3.append(12.1);
	cout << l3;
	
}
