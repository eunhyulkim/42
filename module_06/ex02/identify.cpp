#include <string>
#include <iostream>
#include <random>

class Base
{
	public:
		virtual ~Base(void);
};

class A : public Base {};
class B : public Base {};
class C : public Base {};

Base::~Base(void) {}

enum Eclass {
	CLASS_A,
	CLASS_B,
	CLASS_C
};

namespace {
	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;37;41m" << msg << "\033[0m"
		<< std::endl;
	}

	int get_random_class()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> class_dis(0, 2);
		return (class_dis(gen));
	}

	Base* generate(void)
	{
		Base *p = nullptr;
		int eclass = get_random_class();

		if (eclass == CLASS_A)
		{
			std::cout << "A CONSTRUCTOR CALLED" << std::endl;
			p = new A();
		}
		else if (eclass == CLASS_B)
		{
			std::cout << "B CONSTRUCTOR CALLED" << std::endl;
			p = new B();
		}
		else if (eclass == CLASS_C)
		{
			std::cout << "C CONSTRUCTOR CALLED" << std::endl;
			p = new C();
		}
		else
			std::cerr << "ERROR" << std::endl;
		return (p);
	}

	void identify_from_pointer(Base * p)
	{
		if (dynamic_cast<A *>(p) != nullptr)
			std::cout << "A FROM POINTER" << std::endl;
		else if (dynamic_cast<B *>(p) != nullptr)
			std::cout << "B FROM POINTER" << std::endl;
		else if (dynamic_cast<C *>(p) != nullptr)
			std::cout << "C FROM POINTER" << std::endl;
		return ;
	}

	void identify_from_reference( Base & p)
	{
		Base *t = &p;
		if (dynamic_cast<A *>(t) != nullptr)
			std::cout << "A FROM REFERENCE" << std::endl;
		else if (dynamic_cast<B *>(t) != nullptr)
			std::cout << "B FROM REFERENCE" << std::endl;
		else if (dynamic_cast<C *>(t) != nullptr)
			std::cout << "C FROM REFERENCE" << std::endl;
		else
			std::cout << t << std::endl;
		return ;
	}
}

int		main(void)
{
	for (int i = 0; i < 5; i++)
	{
		print("NO." + std::to_string(i) + " TRY IDENTIFY");
		Base *p = generate();
		identify_from_pointer(p);
		identify_from_reference(*p);
		delete p;		
	}
	return (0);
}
