#include "LinkedList.h"
#include <cstdlib>

using namespace std, jcw;
int main()
{
	std::cout << "Howdy. Testing Linked List Operations.\n";
	std::cout << "1) Push_Front(value)";
	
	LinkedList list;
	list.push_front(5);
	list.display();
}
