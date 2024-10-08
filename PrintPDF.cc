#include <iostream>
#include <vector>
#include <stdexcept>
#include "hpdf.h"

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
  std::cerr << "ERROR: error_no=" << error_no << ", detail_no=" << detail_no << std::endl;
  throw std::runtime_error("PDF generation error");
}

int main()
{
  // 图片路径和数量
  std::vector<std::string> image_paths = {
      "D://MyCardLibrary/ygopro/pics/2511.jpg",
      "D://MyCardLibrary/ygopro/pics/10000.jpg",
      "D://MyCardLibrary/ygopro/pics/27551.jpg",
      "D://MyCardLibrary/ygopro/pics/2511.jpg",
      "D://MyCardLibrary/ygopro/pics/10000.jpg",
      "D://MyCardLibrary/ygopro/pics/27551.jpg",
      "D://MyCardLibrary/ygopro/pics/2511.jpg",
      "D://MyCardLibrary/ygopro/pics/10000.jpg",
      "D://MyCardLibrary/ygopro/pics/27551.jpg",
      "D://MyCardLibrary/ygopro/pics/27551.jpg",
      // 添加更多图片路径
  };

  // 初始化 PDF 文档
  HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
  if (!pdf)
  {
    std::cerr << "Failed to create PDF object" << std::endl;
    return 1;
  }

  try
  {
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

    HPDF_Page page = nullptr;

    for (size_t i = 0; i < image_paths.size(); ++i)
    {
      if (i % images_per_page == 0)
      {
        // 添加新页面
        page = HPDF_AddPage(pdf);
        if (!page)
        {
          std::cerr << "Failed to add page" << std::endl;
          HPDF_Free(pdf);
          return 1;
        }
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
      }

      std::cout << "Processing image: " << image_paths[i] << std::endl;

      // 检查图像文件是否存在
      FILE *file = fopen(image_paths[i].c_str(), "rb");
      if (!file)
      {
        std::cerr << "Image file not found: " << image_paths[i] << std::endl;
        continue; // 跳过不存在的图像
      }
      fclose(file);

      // 加载图片
      HPDF_Image image = HPDF_LoadJpegImageFromFile(pdf, image_paths[i].c_str());
      if (!image)
      {
        std::cerr << "Failed to load image: " << image_paths[i] << std::endl;
        continue; // 跳过加载失败的图像
      }

      // 计算图片位置
      int row = (i % images_per_page) / images_per_row;
      int col = (i % images_per_page) % images_per_row;
      float x = margin + col * (image_width + margin);
      float y = page_height - margin - (row + 1) * (image_height + margin) + margin;

      // 绘制图片
      HPDF_Page_DrawImage(page, image, x, y, image_width, image_height);
    }

    // 保存 PDF 文件
    const char *pdf_path = "output.pdf";
    HPDF_SaveToFile(pdf, pdf_path);
    std::cout << "PDF saved to " << pdf_path << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
    HPDF_Free(pdf);
    return 1;
  }

  // 释放 PDF 对象
  HPDF_Free(pdf);
  return 0;
}