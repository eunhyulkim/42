#include <iostream>
#include <string>

class aa {
	public:
		int data;
		aa(int numb);
		int get_data(void);
};

aa::aa(int numb) { data = numb;}
int aa::get_data(void) { return (this->data); }

class bb : public aa {
	public:
		int data;
		bb(int numb);
};

bb::bb(int numb) : aa(numb) { data = numb * 2; }

int main(void)
{
	bb d(100);
	std::cout << d.get_data() << std::endl;
	return (0);
}
