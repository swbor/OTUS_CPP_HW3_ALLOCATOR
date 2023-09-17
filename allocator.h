#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<unsigned char> split(const std::string &str, char d)
{
    std::vector<unsigned char> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(std::stoi(str.substr(start, stop - start)));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(std::stoi(str.substr(start)));

    return r;
}

void print_ip_pool(std::vector<std::vector<unsigned char>>& ip_pool)
{
    bool first;
    for (const auto& ip : ip_pool)
    {
        first = true;
        for (const auto& byte : ip)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                std::cout << ".";
            }
            std::cout << std::to_string(byte);
        }
        std::cout<<std::endl;
    }
}


auto filter(std::vector<std::vector<unsigned char>>& ip_pool, int param0, int param1 = -1, int param2 = -1, int param3 = -1)
{
    std::remove_reference<decltype(ip_pool)>::type result;
    for (const auto& ip : ip_pool)
    {
        if (ip[0]==param0&&(param1==-1||ip[1]==param1) && (param2 == -1 || ip[2] == param2) && (param3 == -1 || ip[3] == param3))
            result.push_back(ip);
    }
    return result;
}

auto filter_any(std::vector<std::vector<unsigned char>>& ip_pool, int param)
{
    std::remove_reference<decltype(ip_pool)>::type result;
        for (const auto& ip : ip_pool)
        {
            if (ip[0] == param || ip[1] == param|| ip[2] == param || ip[3] == param)
                result.push_back(ip);
        }
    return result;
}

int main(/*int argc, char const *argv[]*/)
{
    try
    {
        std::vector<std::vector<unsigned char> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '.');
            ip_pool.push_back(v); 
        }

        print_ip_pool(ip_pool);
        // TODO reverse lexicographically sort

        std::sort(ip_pool.begin(), ip_pool.end(), [](std::vector<unsigned char> a, std::vector<unsigned char> b)
            {
                for (std::size_t i = 0; i < a.size(); i++)
                {
                    if (a[i] > b[i])
                        return true;
                    else if (a[i] < b[i])
                        return false;
                }
                return false;
            });
        print_ip_pool(ip_pool);
        auto res1 = filter(ip_pool, 1);
        print_ip_pool(res1);
        res1.clear();
        res1 = filter(ip_pool, 46, 70);
        print_ip_pool(res1);
        res1.clear();
        res1 = filter_any(ip_pool, 46);
        print_ip_pool(res1);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
