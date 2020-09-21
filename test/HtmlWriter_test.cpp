#include "HtmlWriter.hpp"
# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>
# include <fcntl.h>
# include <dirent.h>
# include <sys/dirent.h>
# include <unistd.h>

int main(int ac, char *av[])
{
    HtmlWriter html;

    html.add_title("Index of /test/");
    html.add_bgcolor("white");
    html.add_tag("\"white\">\n", "hr", "", true);
    html.add_tag("hr>\n", "pre", "", true);
    
    DIR *dir = NULL;
    struct dirent *de = NULL;
    bool first = true;
    char temp[1024];

    getcwd(temp, sizeof(temp));
    std::cout << temp << std::endl;
    if ((dir = opendir(temp)) == NULL)
        return (0);
    while ((de = readdir(dir)) != NULL) {
        if (de->d_type == 4 || de->d_type == 8) // 4 dir, 8 file
        {
            if (first) {
                html.add_link(de->d_name, "<pre>\n");
                first = false;
            }
            html.add_link(de->d_name);
        }
    }
    std::cout << html.get_m_body();
    return (0);
}
