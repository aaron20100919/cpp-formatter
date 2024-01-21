#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int counts(string str, char ch)
{
    int count = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] == ch && (i == 0 || str[i - 1] != '\\'))
        {
            count++;
        }
    }
    return count;
}

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

bool comp(pair<string, string> __a, pair<string, string> __b)
{
    return __a.first.size() > __b.first.size();
}

void get_tables(vector<pair<string, string>> &tables, string str)
{
    int cnt = 2;
    while (!tables.empty())
    {
        tables.pop_back();
    }
    istringstream iss(str);
    string line;
    while (getline(iss, line))
    {
        if (isLineStartsWithHash(line))
        {
            continue;
        }
        string word, all;
        istringstream ls(line);
        char ch = 0, tmp = 0;
        while (ls >> word)
        {
            all.clear();
            ch = 0;
            for (char cc : word)
            {
                if (!ch && (cc == '"' || cc == '\''))
                {
                    ch = cc;
                }
                if (ch)
                {
                    all += cc;
                }
            }
            if (ch)
            {
                while (counts(all, ch) & 1)
                {
                    tmp = ls.get();
                    if (tmp == EOF)
                    {
                        cerr << "FUCK!";
                        exit(-1);
                    }
                    all += tmp;
                }
                bool flag = 1;
                for (auto table : tables)
                {
                    if (table.first == all)
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag)
                {
                    tables.push_back({all, string(++cnt, '_')});
                }
            }

            bool flag = 1;
            for (auto table : tables)
            {
                if (table.first == word)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                tables.push_back({word, string(++cnt, '_')});
            }
        }
    }
    sort(tables.begin(), tables.end(), comp);
    for (auto &table : tables)
    {
        table.second = string(cnt--, '_');
    }
}

int main(int argc, char *argv[])
{
    vector<pair<string, string>> tables;
    tables.push_back({">>=", " _1 "});
    tables.push_back({"<<=", " _2 "});
    tables.push_back({"->", " _3 "});
    tables.push_back({"==", " _4 "});
    tables.push_back({"+=", " _5 "});
    tables.push_back({"-=", " _6 "});
    tables.push_back({"*=", " _7 "});
    tables.push_back({"/=", " _8 "});
    tables.push_back({"%=", " _9 "});
    tables.push_back({"~=", " _10 "});
    tables.push_back({"!=", " _11 "});
    tables.push_back({"^=", " _12 "});
    tables.push_back({"&=", " _13 "});
    tables.push_back({"<=", " _14 "});
    tables.push_back({">=", " _15 "});
    tables.push_back({"|=", " _16 "});
    tables.push_back({"||", " _17 "});
    tables.push_back({"&&", " _18 "});
    tables.push_back({"++", " _19 "});
    tables.push_back({"--", " _20 "});
    tables.push_back({"[", " [ "});
    tables.push_back({"]", " ] "});
    tables.push_back({"(", " ( "});
    tables.push_back({")", " ) "});
    tables.push_back({"{", " { "});
    tables.push_back({"}", " } "});
    tables.push_back({":", " : "});
    tables.push_back({";", " ; "});
    tables.push_back({",", " , "});
    tables.push_back({"?", " ? "});
    tables.push_back({">>", " >> "});
    tables.push_back({"<<", " << "});
    tables.push_back({"=", " = "});
    tables.push_back({"+", " + "});
    tables.push_back({"-", " - "});
    tables.push_back({"*", " * "});
    tables.push_back({"/", " / "});
    tables.push_back({"%", " % "});
    tables.push_back({"~", " ~ "});
    tables.push_back({"!", " ! "});
    tables.push_back({"^", " ^ "});
    tables.push_back({"&", " & "});
    tables.push_back({"<", " < "});
    tables.push_back({">", " > "});
    tables.push_back({"|", " | "});

    sort(tables.begin(), tables.end(), comp);

    string filein, fileout, contant;
    if (argc == 1)
    {
        cout << "Input file's name: ";
        getline(cin, filein);
        cout << "Output file's name: ";
        getline(cin, fileout);
    }
    else if (argc == 2)
    {
        filein = argv[1];
        cout << "Output file's name: ";
        getline(cin, fileout);
    }
    else
    {
        filein = argv[1];
        fileout = argv[2];
    }
    contant = read(filein);

    contant = turn(tables, contant);
    tables.clear();
    tables.push_back({"_1", " >>= "});
    tables.push_back({"_2", " <<= "});
    tables.push_back({"_3", " -> "});
    tables.push_back({"_4", " == "});
    tables.push_back({"_5", " += "});
    tables.push_back({"_6", " -= "});
    tables.push_back({"_7", " *= "});
    tables.push_back({"_8", " /= "});
    tables.push_back({"_9", " %= "});
    tables.push_back({"_10", " ~= "});
    tables.push_back({"_11", " != "});
    tables.push_back({"_12", " ^= "});
    tables.push_back({"_13", " &= "});
    tables.push_back({"_14", " <= "});
    tables.push_back({"_15", " >= "});
    tables.push_back({"_16", " |= "});
    tables.push_back({"_17", " || "});
    tables.push_back({"_18", " && "});
    tables.push_back({"_19", " ++ "});
    tables.push_back({"_20", " -- "});
    sort(tables.begin(), tables.end(), comp);
    contant = turn(tables, contant);

    get_tables(tables, contant);
    contant = turn(tables, contant);
    string header;
    for (auto x : tables)
    {
        header += "#define " + x.second + " " + x.first + "\n";
    }
    contant = header + contant;
    ofstream out(fileout);
    out << contant;
    out.close();

    return 0;
}
