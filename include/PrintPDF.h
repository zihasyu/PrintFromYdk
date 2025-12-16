#ifndef PRINTPDF_H
#define PRINTPDF_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include "./hpdf/hpdf.h"
#include <fstream>
#include <sstream>
#include <windows.h>
#include <locale>
#include <codecvt>
#include <filesystem>
namespace fs = std::filesystem;
// 设置页面尺寸
const float mm_to_points = 72.0 / 25.4;         // 毫米到点的转换系数
const float page_width = 210.0 * mm_to_points;  // A4 width in points
const float page_height = 297.0 * mm_to_points; // A4 height in points
// const float margin = 5 * mm_to_points;                       // 页边距
// const int images_per_row = 3;                                // 每行图片数量
// const int images_per_col = 3;                                // 每列图片数量
// const int images_per_page = images_per_row * images_per_col; // 每页图片数量
// const float image_width = 59.0 * mm_to_points;               // 每个图片的宽度 (5.9 cm)
// const float image_height = 86.0 * mm_to_points;              // 每个图片的高度 (8.6 cm)
// const float image_width = (59.0 + 59.0 * 4.0 / 86.0) * mm_to_points; // 每个图片的宽度 (5.9 cm)
// const float image_height = (86.0 + 4.0) * mm_to_points;

#ifndef MARGIN_VALUE
#define MARGIN_VALUE 5
#endif

#ifndef IMAGE_SIZE_OPTION
#define IMAGE_SIZE_OPTION 1
#endif

const float margin = MARGIN_VALUE * mm_to_points;            // 页边距
const int images_per_row = 3;                                // 每行图片数量
const int images_per_col = 3;                                // 每列图片数量
const int images_per_page = images_per_row * images_per_col; // 每页图片数量

#if IMAGE_SIZE_OPTION == 1
const float image_width = 59.0 * mm_to_points;  // 每个图片的宽度 (5.9 cm)
const float image_height = 86.0 * mm_to_points; // 每个图片的高度 (8.6 cm)
#elif IMAGE_SIZE_OPTION == 2
const float image_width = (59.0 + 59.0 * 4.0 / 86.0) * mm_to_points; // 每个图片的宽度
const float image_height = 90.0 * mm_to_points;                      // 每个图片的高度 (9.0 cm)
#endif

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);
std::vector<std::wstring> load_image_paths_from_ydk(const std::wstring &ydk_path, const std::wstring &image_dir);
std::wstring string_to_wstring(const std::string &str);
std::string wstring_to_string(const std::wstring &wstr);
void print_pdf(const std::wstring &ydk_file_wpath, const std::wstring &image_wdir);
std::vector<std::wstring> get_ydk_files(const std::wstring &directory);
#endif // PRINTPDF_H
