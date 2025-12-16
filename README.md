
# PrintFromYdk -cn

- 从`ygopro`或`ygopro2`的`ydk`文件生成PDF。
- 本项目使用Haru Free PDF Library (libharu, https://github.com/libharu/libharu)生成PDF文件。
- 视频演示：https://www.bilibili.com/video/BV17wfFYUEY8

## 用户

1. 从Release页面下载并解压程序包。
2. 请**使用 `ygopro/` 作为目录**解压程序包。
```shell 
ygopro
├── deck
├── pics
└── PrintFromYdk
    ├── PrintPDF_M0_59_86.exe
    ├── PrintPDF_M0_61_90.exe
    ├── PrintPDF_M5_59_86.exe
    ├── PrintPDF_M5_61_90.exe
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
    ├── PrintPDF_M0_59_86.exe
    ├── PrintPDF_M0_61_90.exe
    ├── PrintPDF_M5_59_86.exe
    ├── PrintPDF_M5_61_90.exe
    ├── libstdc++-6.dll
    ├── libgcc_s_seh-1.dll
    ├── libhpdf.dll
    └── outputPDF

```
3. 根据你的需求，双击对应的`.exe`文件。程序将自动生成PDF文件并保存在`./outputPDF/`目录中。
    - `M0`: 代表卡片之间**无间距**，只需6次裁剪即可获得9张卡。
    - `M5`: 代表卡片之间有**5mm间距**，可防止裁剪失误。
    - `59_86`: 代表卡片尺寸为 **59x86mm** (标准游戏王卡片尺寸)。
    - `61_90`: 代表卡片尺寸为 **~61x90mm** (适合某些打印机会自动缩放时的尺寸，例如某电文印中心)。
4.  如果PDF文件没有出现在当前目录中，请检查目录权限或防火墙设置。

## 开发者

1. 确保安装了最新版本的`g++`，且`libharu`已安装。
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

## 测试过的系统和平台

|系统版本|YGOPro|YGOPro2|其他|
|---|---|---|---|
|Windows 10|通过|通过|-|
|Windows 11|通过|通过|-|
|其他系统|-|-|-|

# PrintFromYdk -en

- Print PDF from ydk in ygopro or ygopro2. 
- This project generates PDF files using the Haru Free PDF Library (libharu, https://github.com/libharu/libharu).
- - Video Demo: https://www.bilibili.com/video/BV17wfFYUEY8

## For General Users
1. Download and extract the package from the Release Page.
2. Please **use ygopro/ as the directory** to unzip the package.
```shell
ygopro
├── deck
├── pics
└── PrintFromYdk
    ├── PrintPDF_M0_59_86.exe
    ├── PrintPDF_M0_61_90.exe
    ├── PrintPDF_M5_59_86.exe
    ├── PrintPDF_M5_61_90.exe
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
    ├── PrintPDF_M0_59_86.exe
    ├── PrintPDF_M0_61_90.exe
    ├── PrintPDF_M5_59_86.exe
    ├── PrintPDF_M5_61_90.exe
    ├── libstdc++-6.dll
    ├── libgcc_s_seh-1.dll
    ├── libhpdf.dll
    └── outputPDF
```
3. Double-click the corresponding `.exe` file according to your needs. The program will automatically generate PDF files and save them in ./outputPDF/.
    - `M0`: Means **no margin** between cards. You can get 9 cards with just 6 cuts.
    - `M5`: Means a **5mm margin** between cards to prevent cutting errors.
    - `59_86`: Means the card size is **59x86mm** (standard ygo's card size).
    - `61_90`: Means the card size is **~61x90mm**. This is adjusted for printers that may automatically scale the output (e.g., the print center at UESTC), ensuring the final card fits standard sleeves.
4. If the PDF file does not appear in the current directory, check the directory permissions or firewall settings.

## For Developers

1. Ensure that the latest version of `g++` and `libharu` are installed. 
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

## Tested Systems & Platform

| System Version | YGOPro | YGOPro2 | others |
| -------------- | ------ | ------- | ------ |
| Windows 10     | Passed | Passed  | -      |
| Windows 11     | Passed | Passed  | -      |
| others         | -      | -       | -      |
