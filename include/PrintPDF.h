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
// 设置页面尺寸
const float mm_to_points = 72.0 / 25.4;                      // 毫米到点的转换系数
const float page_width = 210.0 * mm_to_points;               // A4 width in points
const float page_height = 297.0 * mm_to_points;              // A4 height in points
const float margin = 0 * mm_to_points;                       // 页边距
const int images_per_row = 3;                                // 每行图片数量
const int images_per_col = 3;                                // 每列图片数量
const int images_per_page = images_per_row * images_per_col; // 每页图片数量
const float image_width = 59.0 * mm_to_points;               // 每个图片的宽度 (5.9 cm)
const float image_height = 86.0 * mm_to_points;              // 每个图片的高度 (8.6 cm)

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);
std::vector<std::wstring> load_image_paths_from_ydk(const std::wstring &ydk_path, const std::wstring &image_dir);
std::wstring string_to_wstring(const std::string &str);
std::string wstring_to_string(const std::wstring &wstr);
#endif // PRINTPDF_H