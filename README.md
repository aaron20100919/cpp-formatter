# [c++ 代码格式化神器!](https://github.com/aaron20100919/cpp-formatter.git)

可以让你的代码焕然一新，**代码查重率**直接为 $0$ !

请**自行编译**，其中：

- `formatter.cpp` 是标准格式化
- `formatter_pro.cpp` 是加强版格式化
- `chinese.cpp` 是英文标点符号转中文标点符号
- `_formatter.cpp` 是将全部内容改成下划线

## 使用方法：

### 1. 默认格式化

```
formatter.exe
OR
formatter.exe InputFile
OR
formatter.exe InputFile OutputFile 
```

### 2. 自定义

你可以自己更改 `tables` 里的内容。

使用方法如下：

```cpp
tables.push_back({"要替换的字符串", "替换成的字符串"});
```
