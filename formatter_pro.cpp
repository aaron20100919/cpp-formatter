#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

bool isInQuotes(const string &str, size_t pos)
{
    int count = 0;
    for (size_t i = 0; i < pos; ++i)
    {
        if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
        {
            count++;
        }
    }
    return count % 2 != 0;
}

bool isInSmallQuotes(const string &str, size_t pos)
{
    int count = 0;
    for (size_t i = 0; i < pos; ++i)
    {
        if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
        {
            count++;
        }
    }
    return count % 2 != 0;
}

bool isLineStartsWithHash(const string &line)
{
    istringstream iss(line);
    string word;
    iss >> word;
    return !word.empty() && word[0] == '#';
}

void replaceAll(string &str, const string &search, const string &replace)
{
    istringstream iss(str);
    ostringstream oss;
    string line;
    while (getline(iss, line))
    {
        line += '\n';
        if (isLineStartsWithHash(line))
        {
            oss << line; // Keep lines starting with '#'
            continue;
        }
        size_t pos = 0;
        while ((pos = line.find(search, pos)) != string::npos)
        {
            if (!isInQuotes(line, pos) && !isInSmallQuotes(line, pos))
            {
                line.replace(pos, search.length(), replace);
                pos += replace.length();
            }
            else
            {
                pos += search.length();
            }
        }
        oss << line;
    }
    str = oss.str();
}

string turn(vector<pair<string, string>> tables, string contant)
{
    for (auto table : tables)
    {
        replaceAll(contant, table.first, table.second);
    }
    return contant;
}

string read(string file)
{
    ifstream in(file);
    stringstream buffer;
    buffer << in.rdbuf();
    in.close();
    return buffer.str();
}

int main(int argc, char *argv[])
{
    vector<pair<string, string>> tables;
    tables.push_back({"(", " ( "});
    tables.push_back({")", ") "});
    tables.push_back({"[", " ["});
    tables.push_back({"]", " ]  "});
    tables.push_back({"++", " ++ "});
    tables.push_back({"--", " -- "});
    tables.push_back({",", " \n ,\n"});
    tables.push_back({".", " ."});
    tables.push_back({"->", "->  "});
    tables.push_back({"\t", "   "});          // 如果你非常希望你的代码面目全非，请不要注释它
    tables.push_back({" ", "\t"});            // 如果你非常希望你的代码面目全非，请不要注释它
    tables.push_back({"\n", "\t\t\n\n\t\t"}); // 如果你非常希望你的代码面目全非，请不要注释它

    string filein, fileout, contant;
    if (argc == 1)
    {
        cout << "Input file's name: ";
        cin >> filein;
        cout << "Output file's name: ";
        cin >> fileout;
    }
    else if (argc == 2)
    {
        filein = argv[1];
        cout << "Output file's name: ";
        cin >> fileout;
    }
    else
    {
        filein = argv[1];
        fileout = argv[2];
    }
    contant = read(filein);
    contant = turn(tables, contant);
    ofstream out(fileout);
    out << contant;
    out.close();

    return 0;
}
