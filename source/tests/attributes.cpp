#include <iostream>
#include "../attribute/list.h"

using namespace Voltam::Attribute;


int main(int argc, char * argv[])
{
	//Create a attribute list.
	List a1, a2;
	std::cout << "a1 = " << (std::string)a1 << std::endl;
	std::cout << "a2 = " << (std::string)a2 << std::endl;
	
	//Add some attributes.
	std::cout << "Adding attributes…" << std::endl;
	a1.set("hallo", new IAttribute());
	a2.set("welt", new IAttribute());
	a1["alpha"] = new IAttribute();
	a2["beta"] = new IAttribute();
	std::cout << "a1 = " << (std::string)a1 << std::endl;
	std::cout << "a2 = " << (std::string)a2 << std::endl;
	
	//Merge a2 into a1.
	std::cout << "Merging a2 into a1…" << std::endl;
	a1.merge(a2);
	std::cout << "a1 = " << (std::string)a1 << std::endl;
	
	return 0;
}
