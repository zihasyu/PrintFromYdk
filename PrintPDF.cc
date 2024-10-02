#include <hpdf.h>
#include <iostream>
#include <vector>
#include <string>

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
  std::cerr << "ERROR: error_no=" << error_no << ", detail_no=" << detail_no << std::endl;
  throw std::runtime_error("PDF generation error");
}

int main()
{
  // 图片路径和数量
  std::vector<std::string> image_paths = {
      "image1.jpg", "image2.jpg", "image3.jpg", // 添加更多图片路径
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
    const float page_width = 210.0;  // A4 width in mm
    const float page_height = 297.0; // A4 height in mm
    const float img_width = 86.0;    // Image width in mm
    const float img_height = 59.0;   // Image height in mm

    HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

    int images_per_page = 9;
    int image_count = image_paths.size();
    int num_pages = (image_count + images_per_page - 1) / images_per_page;

    for (int page_num = 0; page_num < num_pages; ++page_num)
    {
      HPDF_Page page = HPDF_AddPage(pdf);
      HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

      for (int i = 0; i < images_per_page; ++i)
      {
        int img_index = page_num * images_per_page + i;
        if (img_index >= image_count)
          break;

        HPDF_Image image = HPDF_LoadJpegImageFromFile(pdf, image_paths[img_index].c_str());

        int col = i % 3;
        int row = i / 3;

        float x = col * img_width;
        float y = page_height - (row + 1) * img_height;

        HPDF_Page_DrawImage(page, image, x, y, img_width, img_height);
      }
    }

    HPDF_SaveToFile(pdf, "output.pdf");
    HPDF_Free(pdf);
  }
  catch (const std::exception &e)
  {
    HPDF_Free(pdf);
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}