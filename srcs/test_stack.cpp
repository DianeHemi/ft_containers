#include "tests.hpp"

void stack_basic_tests()
{
	std::cout << "Empty stack" << std::endl;
	NAMESPACE::stack<int> s1;
	std::cout << "S1 size : " << s1.size() << " | Empty : " << s1.empty() << std::endl;


	std::cout << "\nEmpty stack using std::vector" << std::endl;
	NAMESPACE::stack<int, std::vector<int> > s2;
	std::cout << "S2 size : " << s2.size() << " | Empty : " << s2.empty() << std::endl;
	std::cout << "Pushing elements in the stack... ";
	for (int i = 0; i < 5; i++)
	{
		std::cout << i << ' ';
		s2.push(i);
	} 
	std::cout << "\nS2 size : " << s2.size() << " | Empty : " << s2.empty() << std::endl;
	std::cout << "Popping out elements... ";
	while(!s2.empty())
	{
		std::cout << ' ' << s2.top();
		s2.pop();
	}
	std::cout << std::endl;
	std::cout << "S2 size : " << s2.size() << " | Empty : " << s2.empty() << std::endl;


	std::cout << "\nEmpty stack using vector" << std::endl;
	NAMESPACE::stack<char, NAMESPACE::vector<char> > s3;
	std::cout << "S3 size : " << s3.size() << " | Empty : " << s3.empty() << std::endl;
	std::cout << "Pushing elements in the stack... ";
	for (int i = 'a'; i != 'f'; i++)
	{
		std::cout << (char)i << ' ';
		s3.push(i);
	} 
	std::cout << "\nS3 size : " << s3.size() << " | Empty : " << s3.empty() << std::endl;
	std::cout << "Popping out elements... ";
	while(!s3.empty())
	{
		std::cout << ' ' << s3.top();
		s3.pop();
	}
	std::cout << std::endl;
	std::cout << "S4 size : " << s3.size() << " | Empty : " << s3.empty() << std::endl;

	std::cout << "\nCreating a stack from a vector<int> (2, 8)" << std::endl;
	std::vector<int> v1 (2, 8);
	NAMESPACE::stack<int, std::vector<int> > s4 (v1);
	std::cout << "S4 size : " << s4.size() << " | Empty : " << s4.empty() << std::endl;
	std::cout << "Popping out elements... ";
	while(!s4.empty())
	{
		std::cout << ' ' << s4.top();
		s4.pop();
	}
	std::cout << std::endl;
	std::cout << "S4 size : " << s4.size() << " | Empty : " << s4.empty() << std::endl;

	std::cout << "\nTesting the = operator" << std::endl;
	NAMESPACE::stack<int> s5;
	std::cout << "S5 size : " << s5.size() << " | Empty : " << s5.empty() << std::endl;
	std::cout << "Pushing elements in the stack... ";
	for (int i = 5; i < 12; i++)
	{
		std::cout << i << ' ';
		s5.push(i);
	} 
	std::cout << "\nS5 size : " << s5.size() << " | Empty : " << s5.empty() << std::endl;
	std::cout << "S1 size : " << s1.size() << " | Empty : " << s1.empty() << std::endl;
	s1 = s5;
	std::cout << "Copy" << std::endl;
	std::cout << "S1 size : " << s1.size() << " | Empty : " << s1.empty() << std::endl;
}

void print_cmp( const NAMESPACE::stack<unsigned int>& a, const NAMESPACE::stack<unsigned int>& b )
{
	static int i = 0;

	std::cout << "\n\t******** " << i++ << " ********" << std::endl;
	std::cout << "Equality : \t" << (a == b) << " | Difference : \t" << (a != b) << std::endl;
	std::cout << "Lower : \t" << (a < b) << " | Lower or equal : \t" << (a <= b) << std::endl;
	std::cout << "Greater : \t" << (a > b) << " | Greater or equal : \t" << (a >= b) << std::endl;
}

void print_cmp_list( const NAMESPACE::stack<char, std::list<char> >& a, const NAMESPACE::stack<char, std::list<char> >& b )
{
	static int i = 0;

	std::cout << "\n\t******** " << i++ << " ********" << std::endl;
	std::cout << "Equality : \t" << (a == b) << " | Difference : \t" << (a != b) << std::endl;
	std::cout << "Lower : \t" << (a < b) << " | Lower or equal : \t" << (a <= b) << std::endl;
	std::cout << "Greater : \t" << (a > b) << " | Greater or equal : \t" << (a >= b) << std::endl;
}

void stack_relational_test()
{
	NAMESPACE::stack<unsigned int> s1;
	s1.push(4);
	s1.push(8);
	s1.push(16);
	s1.push(32);
	s1.push(64);
	s1.push(128);
	NAMESPACE::stack<unsigned int> s2(s1);

	print_cmp(s1, s1);
	print_cmp(s1, s2);

	s2.push(256);
	s2.push(512);
	print_cmp(s1, s2);
	print_cmp(s2, s1);

	s1.push(256);
	print_cmp(s1, s2);
	print_cmp(s2, s1);

	s1.push(2048);
	print_cmp(s1, s2);
	print_cmp(s2, s1);
}

void stack_list_test()
{
	std::list<char> l1;
	l1.push_back('a');
	l1.push_back('e');
	l1.push_back('i');
	l1.push_back('o');
	l1.push_back('u');
	l1.push_back('y');

	NAMESPACE::stack<char, std::list<char> > s1(l1);
	std::cout << "S1 size : " << s1.size() << " | Empty : " << s1.empty() << std::endl;

	s1.push('b');
	s1.push('c');
	s1.push('d');
	std::cout << "Pushed 3 elements" << std::endl;
	std::cout << "S1 size : " << s1.size() << " | Empty : " << s1.empty() << std::endl;

	NAMESPACE::stack<char, std::list<char> > s2(s1);
	std::cout << "\nCreated a copy of S1" << std::endl;
	std::cout << "S2 size : " << s2.size() << " | Empty : " << s2.empty() << std::endl;
	print_cmp_list(s1, s2);
	std::cout << "\nPopping out elements of S2... ";
	for (int i = 0; i < 3; i++)
	{
		std::cout << ' ' << s2.top();
		s2.pop();
	}
	std::cout << std::endl;
	std::cout << "Comparing S1 to S2 and reverse" << std::endl;
	print_cmp_list(s1, s2);
	print_cmp_list(s2, s1);

	std::cout << "\nPopping out elements of S1... ";
	for (int i = 0; i < 3; i++)
	{
		std::cout << ' ' << s1.top();
		s1.pop();
	}
	std::cout << std::endl;
	std::cout << "Comparing S1 to S2 and reverse" << std::endl;
	print_cmp_list(s1, s2);
	print_cmp_list(s2, s1);

	std::cout << "\nPopping out elements of S1... ";
	for (int i = 0; i < 6; i++)
	{
		std::cout << ' ' << s1.top();
		s1.pop();
	}
	std::cout << std::endl;
	std::cout << "Comparing S1 to S2 and reverse" << std::endl;
	print_cmp_list(s1, s2);
	print_cmp_list(s2, s1);
}
