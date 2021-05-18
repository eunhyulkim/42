# include <string>
# include <iostream>
# include <random>
# include <limits>

struct 			Data
{
	std::string s1;
	int			n;
	std::string s2;
};

namespace {
	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;37;41m" << msg << "\033[0m"
		<< std::endl;
	}

	std::string get_random_string()
	{
		std::string option_list = "abcdefghijklmnopqrstuvwxyz0123456789";
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> string_dis(0, 35);

		std::string str;
		for (int i = 0; i < 8; i++)
			str.push_back(option_list[string_dis(gen)]);
		return (str);
	}

	int get_random_int()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> int_dis(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

		return (int_dis(gen));
	}

	void	*serialize(void)
	{
		std::string strA = get_random_string();
		std::string strB = get_random_string();
		int num = get_random_int();
		
		print("RANDOM STRING AND NUMBER GENERATE");
		std::cout << "\ns1: " << strA << std::endl;
		std::cout << "n: " << num << std::endl;
		std::cout << "s2: " << strB << std::endl;

		print("MEMORY ALLOCATE");
		char *data = new char[16 + sizeof(int)];

		if (data == nullptr)
			return (data);
		print("SERIALIZE");
		for (int i = 0; i < 8; i++)
		{
			data[i] = strA[i];
			data[8 + sizeof(int) + i] = strB[i];
		}
		*reinterpret_cast<int *>(data + 8) = num;
		return (data);
	}
	
	Data* deserialize(void * raw)
	{
		print("DESERIALIZE");
		Data *data = new Data;

		data->s1 = std::string(reinterpret_cast<char *>(raw), 8);
		data->n = *(reinterpret_cast<int *>(reinterpret_cast<char *>(raw) + 8));
		data->s2 = std::string(reinterpret_cast<char *>(raw) + 8 + sizeof(int), 8);

		return (data);
	}
}

int main(void)
{
	void	*raw = serialize();

	if (raw == nullptr)
	{
		std::cerr << "Memory allocation failure." << std::endl;
		return (1);
	}
	
	Data *data = deserialize(raw);
	print("DESERIALIZE RESULT");
	std::cout << std::endl;
	std::cout << "s1: " << data->s1 << std::endl;
	std::cout << "n: " << data->n << std::endl;
	std::cout << "s2: " << data->s2 << std::endl;

	delete[] reinterpret_cast<char *>(raw);
	delete data;

	print("TEST END");

	return 0;
}
