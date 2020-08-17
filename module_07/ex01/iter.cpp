# include <string>
# include <iostream>

void	print(std::string msg) {
    std::cout << "\033[1;37;41m" << msg << "\033[0m";
}

template<typename T>
void display(const T& element) {
    std::cout << element << " ";
}

template<typename T>
void iter(T *array, size_t length, void (*f)(const T& element))
{
    for (size_t i = 0; i < length; i++)
        (*f)(array[i]);
}

int main(void)
{
	int intArrayOne[5] = { 0, 1, 2, 3, 4 };
    print("intArray");
    std::cout << " : ";
	iter(intArrayOne, 5, &display);
    std::cout << std::endl;

	int *intArrayTwo = new int[5];
    for (int i = 0; i < 5; i++)
        intArrayTwo[i] = intArrayOne[i];
    print("intArray");
    std::cout << " : ";
	iter(intArrayTwo, 5, &display);
    std::cout << std::endl;
    delete[] intArrayTwo;

	char charArrayOne[5] = { 'a', 'b', 'c', 'd', 'e' };
    print("charArray");
    std::cout << " : ";
	iter(charArrayOne, 5, &display);
    std::cout << std::endl;

	char *charArrayTwo = new char[5];
    for (int i = 0; i < 5; i++)
        charArrayTwo[i] = charArrayOne[i];
    print("charArray");
    std::cout << " : ";
	iter(charArrayTwo, 5, &display);
    std::cout << std::endl;
    delete[] charArrayTwo;

	float floatArrayOne[5] = { -1.5f, -1.2f, 0, 0.5f, 1.2f };
    print("floatArray");
    std::cout << " : ";
	iter(floatArrayOne, 5, &display);
    std::cout << std::endl;

	float *floatArrayTwo = new float[5];
    for (int i = 0; i < 5; i++)
        floatArrayTwo[i] = floatArrayOne[i];
    print("floatArray");
    std::cout << " : ";
	iter(floatArrayTwo, 5, &display);
    std::cout << std::endl;
    delete[] floatArrayTwo;

	double doubleArrayOne[5] = { -1.5, -1.2, 0, 0.5, 1.2 };
    print("doubleArray");
    std::cout << " : ";
	iter(doubleArrayOne, 5, &display);
    std::cout << std::endl;

	double *doubleArrayTwo = new double[5];
    for (int i = 0; i < 5; i++)
        doubleArrayTwo[i] = doubleArrayOne[i];
    print("doubleArray");
    std::cout << " : ";
	iter(doubleArrayTwo, 5, &display);
    std::cout << std::endl;
    delete[] doubleArrayTwo;

	std::string stringArrayOne[5] = { "hello", "cpp", "42", "cadet", "ecole" };
    print("stringArray");
    std::cout << " : ";
	iter(stringArrayOne, 5, &display);
    std::cout << std::endl;

	std::string *stringArrayTwo = new std::string[5];
    for (int i = 0; i < 5; i++)
        stringArrayTwo[i] = stringArrayOne[i];
    print("stringArray");
    std::cout << " : ";
	iter(stringArrayTwo, 5, &display);
    std::cout << std::endl;
    delete[] stringArrayTwo;

	return (0);
}
