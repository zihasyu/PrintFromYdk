#include "./include/PrintPDF.h"

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