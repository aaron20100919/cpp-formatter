#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void replaceAll(string &str, const string &search, const string &replace)
{
    istringstream iss(str);
    ostringstream oss;
    string line;
    while (getline(iss, line))
    {
        line += '\n';
        size_t pos = 0;
        while ((pos = line.find(search, pos)) != string::npos)
        {
            line.replace(pos, search.length(), replace);
            pos += replace.length();
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
    tables.push_back({".", "。"});  // 句号
    tables.push_back({",", "，"});  // 逗号
    tables.push_back({":", "："});  // 冒号
    tables.push_back({";", "；"});  // 分号
    tables.push_back({"?", "？"});  // 问号
    tables.push_back({"!", "！"});  // 感叹号
    tables.push_back({"'", "’"});   // 单引号
    tables.push_back({"\"", "“"});  // 双引号
    tables.push_back({"-", "－"});  // 连字符
    tables.push_back({"_", "＿"});  // 下划线
    tables.push_back({"+", "＋"});  // 加号
    tables.push_back({"=", "＝"});  // 等号
    tables.push_back({"*", "＊"});  // 星号
    tables.push_back({"/", "／"});  // 斜线
    tables.push_back({"\\", "＼"}); // 反斜线
    tables.push_back({"%", "％"});  // 百分号
    tables.push_back({"&", "＆"});  // 和号
    tables.push_back({"#", "＃"});  // 井号
    tables.push_back({"$", "＄"});  // 美元符号
    tables.push_back({"@", "＠"});  // 小老鼠
    tables.push_back({"^", "＾"});  // 脱字符
    tables.push_back({"(", "（"});  // 左圆括号
    tables.push_back({")", "）"});  // 右圆括号
    tables.push_back({"[", "［"});  // 左方括号
    tables.push_back({"]", "］"});  // 右方括号
    tables.push_back({"{", "｛"});  // 左花括号
    tables.push_back({"}", "｝"});  // 右花括号
    tables.push_back({"<", "＜"});  // 左尖括号
    tables.push_back({">", "＞"});  // 右尖括号
    tables.push_back({"|", "｜"});  // 竖线
    tables.push_back({"~", "～"});  // 波浪号
    tables.push_back({"`", "｀"});  // 反引号

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
