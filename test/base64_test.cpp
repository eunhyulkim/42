# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>
# include <vector>
# include "base64.hpp"
# include "libft.hpp"

void basic_decode(std::string data, std::string& key, std::string& value)
{
	std::string decodedData = ft::containerToString(ft::base64_decode(data), "");
	if (decodedData.find(":") == std::string::npos || decodedData.find(":") == decodedData.size() - 1)
		return ;
	int idx = decodedData.find(":");
	key = decodedData.substr(0, idx);
    std::vector<unsigned char> value_base(decodedData.begin() + idx + 1, decodedData.end());
    value = ft::base64_encode(&value_base[0], value_base.size());
}

int main(void)
{
    std::string data = "ZXVuaGtpbTpuZXh0b21vcnJvdw==";
    std::string key, value;
    basic_decode(data, key, value);
    std::cout << key << std::endl;
    std::cout << value << std::endl;
    return (0);
}
