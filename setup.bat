@echo off
REM 编译脚本，生成所有版本的 PrintPDF

REM 基础编译命令
set BASE_CMD=g++ -I./include/hpdf -L./lib -o
set SOURCE_FILE=PrintPDF.cc
set LIBS=-lhpdf

echo Compiling all versions...

REM 组合 1: margin=5, image_size=standard (59x86)
echo Building PrintPDF_M5_59_86.exe...
%BASE_CMD% PrintPDF_M5_59_86.exe -DMARGIN_VALUE=5 -DIMAGE_SIZE_OPTION=1 %SOURCE_FILE% %LIBS%

REM 组合 2: margin=0, image_size=standard (59x86)
echo Building PrintPDF_M0_59_86.exe...
%BASE_CMD% PrintPDF_M0_59_86.exe -DMARGIN_VALUE=0 -DIMAGE_SIZE_OPTION=1 %SOURCE_FILE% %LIBS%

REM 组合 3: margin=5, image_size=adjusted
echo Building PrintPDF_M5_61_90.exe...
%BASE_CMD% PrintPDF_M5_61_90.exe -DMARGIN_VALUE=5 -DIMAGE_SIZE_OPTION=2 %SOURCE_FILE% %LIBS%

REM 组合 4: margin=0, image_size=adjusted
echo Building PrintPDF_M0_61_90.exe...
%BASE_CMD% PrintPDF_M0_61_90.exe -DMARGIN_VALUE=0 -DIMAGE_SIZE_OPTION=2 %SOURCE_FILE% %LIBS%

echo All versions compiled successfully.