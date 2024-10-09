# PrintFromYdk -en

- Print PDF from ydk in ygopro or ygopro2. 
- This project generates PDF files using the Haru Free PDF Library (libharu, https://github.com/libharu/libharu).
## For Developers

1. Ensure that the latest version of `g++` and `libharu` are installed. It doesn't matter if the 'libharu' library is missing, because the repo executable already has the library's dll in the path.
2. Please **use ygopro/ as the directory** to open the terminal & clone repo
```shell
# cd D:\MyCardLibrary\ygopro 
git clone https://github.com/zihasyu/PrintFromYdk.git
# I hope your repo is here
tree
ygopro
├── deck
├── pics
└── PrintFromYdk
    └── PrintPDF.cc
or
ygopro2
├── deck
├── picture
│   └── card
└── PrintFromYdk
    └── PrintPDF.cc
```
3. Compile the program using the following command:
```shell
g++ -I./include/hpdf -L./lib -o PrintPDF PrintPDF.cc -lhpdf
```
4. Run
```shell
./PrintPDF.exe
```
## For General Users
1. Download and extract the package from the Release Page.
2. Please **use ygopro/ as the directory** to unzip the package.
```shell
ygopro
├── deck
├── pics
└── PrintFromYdk
    ├── PrintPDF.exe
    ├── libstdc++-6.dll
    ├── libgcc_s_seh-1.dll
    ├── libhpdf.dll
    └── outputPDF

or
ygopro2
├── deck
├── picture
│   └── card
└── PrintFromYdk
    ├── PrintPDF.exe
    ├── libstdc++-6.dll
    ├── libgcc_s_seh-1.dll
    ├── libhpdf.dll
    └── outputPDF
```
3. Double-click `PrintPDF.exe`, and the program will automatically generate PDF files and save them in ./outputPDF/.
4. If the PDF file does not appear in the current directory, check the directory permissions or firewall settings.

## Tested Systems & Platform

| System Version | YGOPro | YGOPro2 | others |
| -------------- | ------ | ------- | ------ |
| Windows 10     | Passed | Passed  | -      |
| Windows 11     | Passed | Passed  | -      |
| others         | -      | -       | -      |

# PrintFromYdk -cn

- 从`ygopro`或`ygopro2`的`ydk`文件生成PDF。
- 本项目使用Haru Free PDF Library (libharu, https://github.com/libharu/libharu)生成PDF文件。

## 开发者

1. 确保安装了最新版本的`g++`，且`libharu`已安装。即使'libharu'库缺失也无妨，因为库的dll文件已经包含在项目的可执行文件路径中。
2. 请**使用 `ygopro/` 作为目录**打开终端并克隆仓库：
```shell
# cd D:\MyCardLibrary\ygopro 
git clone https://github.com/zihasyu/PrintFromYdk.git
# 希望你的仓库结构是这样的
tree
ygopro
├── deck
├── pics
└── PrintFromYdk
    └── PrintPDF.cc
or
ygopro2
├── deck
├── picture
│   └── card
└── PrintFromYdk
    └── PrintPDF.cc
```
3. 使用以下命令编译程序：
```shell
g++ -I./include/hpdf -L./lib -o PrintPDF PrintPDF.cc -lhpdf
```
4. 运行
```shell
./PrintPDF.exe
```
## 用户

1. 从Release页面下载并解压程序包。
2. 请**使用 `ygopro/` 作为目录**解压程序包。
```shell 
ygopro
├── deck
├── pics
└── PrintFromYdk
    ├── PrintPDF.exe
    ├── libstdc++-6.dll
    ├── libgcc_s_seh-1.dll
    ├── libhpdf.dll
    └── outputPDF

or
ygopro2
├── deck
├── picture
│   └── card
└── PrintFromYdk
    ├── PrintPDF.exe
    ├── libstdc++-6.dll
    ├── libgcc_s_seh-1.dll
    ├── libhpdf.dll
    └── outputPDF

```
3. 双击`PrintPDF.exe`，程序将自动生成PDF文件并保存在`./outputPDF/`目录中。
4.  如果PDF文件没有出现在当前目录中，请检查目录权限或防火墙设置。
## 测试过的系统和平台

|系统版本|YGOPro|YGOPro2|其他|
|---|---|---|---|
|Windows 10|通过|通过|-|
|Windows 11|通过|通过|-|
|其他系统|-|-|-|