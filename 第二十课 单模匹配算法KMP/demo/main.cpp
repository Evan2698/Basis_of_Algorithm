
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

typedef std::vector<int> PMT;

PMT build_PMT_0(const std::string &pattern)
{
    if (pattern.empty())
    {
        return PMT();
    }

    int n = pattern.length();
    PMT pmt(n, 0);
    for (int i = 1; i < n; ++i)
    {
        std::string substring = pattern.substr(0, i + 1);

        std::set<std::string> prefixes;
        std::set<std::string> suffixes;
        for (int len = 1; len <= i; ++len)
        {
            prefixes.insert(substring.substr(0, len));
            suffixes.insert(substring.substr(substring.length() - len, len));
        }

        std::set<std::string> result;
        std::set_intersection(prefixes.begin(), prefixes.end(),
                              suffixes.begin(), suffixes.end(),
                              std::inserter(result, result.begin()));
        if (!result.empty())
        {
            auto value = std::max_element(result.begin(), result.end(), [](const std::string &a, const std::string &b)
                                          { return a.length() < b.length(); });

            std::cout << "Longest prefix-suffix match for pattern " << substring << ": " << *value << std::endl;
            pmt[i] = value->length();
        }
        else
        {
            pmt[i] = 0;
        }
    }

    return pmt;
}

PMT build_PMT_1(const std::string &pattern)
{
    int m = pattern.length();
    PMT pmt(m, 0);

    int length = 0; // length of the previous longest prefix suffix
    int i = 1;

    pmt[0] = 0;

    while (i < m)
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            pmt[i] = length;
            i++;
        }
        else
        {
            if (length != 0)
            {
                length = pmt[length - 1];
            }
            else
            {
                pmt[i] = 0;
                i++;
            }
        }
    }
    return pmt;
}

int kmp_search(const std::string &text, const std::string &pattern)
{
    int n = text.length();
    int m = pattern.length();

    PMT pmt = build_PMT_0(pattern);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            return i - j; // match found
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = pmt[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
    return -1; // no match found
}

int main()
{
    std::string pattern = "ABCDABC";
    std::string text = "ABC ABCDAB ABCDABCDF";
    PMT pmt = build_PMT_0(pattern);
    PMT pmt1 = build_PMT_1(pattern);

    std::cout << "PMT: ";
    for (int i = 0; i < pmt.size(); ++i)
    {
        std::cout << pmt[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "PMT1: ";
    for (int i = 0; i < pmt1.size(); ++i)
    {
        std::cout << pmt1[i] << " ";
    }
    std::cout << std::endl;

    int pos = kmp_search(text, pattern);

    if (pos != -1)
    {
        std::cout << "模式在文本中找到，起始位置: " << pos << std::endl;
    }
    else
    {
        std::cout << "模式在文本中未找到" << std::endl;
    }

    return 0;
}
