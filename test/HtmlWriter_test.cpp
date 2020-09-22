#include "HtmlWriter.hpp"
# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>
# include <fcntl.h>
# include <dirent.h>
# include <sys/dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>
# include <time.h>
# include "libft.hpp"

int main(int ac, char *av[])
{
    HtmlWriter html;

    std::string title = "Index of /test/";
    html.add_title(title);
    html.add_bgcolor("white");
    html.add_tag("\"white\">\n", "h1", title, false);
    html.add_tag("/h1>\n", "hr", "", true);
    html.add_tag("hr>\n", "pre", "", true);
    
    DIR *dir = NULL;
    struct dirent *de = NULL;
    bool first = true;
    char temp[1024];
    int idx = 7;

    getcwd(temp, sizeof(temp));
    std::cout << temp << std::endl;
    if ((dir = opendir(temp)) == NULL)
        return (0);
    while ((de = readdir(dir)) != NULL) {
        if (de->d_type == 4 || de->d_type == 8) // 4 dir, 8 file
        { 
            std::string content;
            std::string name(de->d_name);
            if (name == "." || (name != ".." && name[0] == '.'))
                continue ;
            content.append(html.makeLink(name));
            content.append(std::string(51 - std::string(de->d_name).size(), ' '));
            struct stat buf;
            struct tm t;
            ft::bzero(&buf, sizeof(struct stat));
            ft::bzero(&t, sizeof(struct tm));
            stat((temp + std::string("/") + name).c_str(), &buf);
            ft::convertTimespecToTm(&buf.st_mtimespec, &t);
            char buff[1024];
            strftime(buff, sizeof(buff), "%d-%h-%G %H:%M", &t);
            content.append(std::string(buff));
            content.append(std::string(20 - std::to_string(de->d_reclen).size(), ' '));
            content.append(std::to_string(de->d_reclen));
            html.add_line(idx++, content);
        }
    }
    std::cout << html.get_m_body();
    return (0);
}
