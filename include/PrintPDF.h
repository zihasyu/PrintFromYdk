#ifndef PRINTPDF_H
#define PRINTPDF_H
#include <iostream>
#include <vector>
#include <stdexcept>
#include "./include/hpdf/hpdf.h"

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

#endif // PRINTPDF_H
