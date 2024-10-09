#include "./include/PrintPDF.h"

int main()
{
  std::string ydk_file_path = "D://MyCardLibrary/ygopro/deck/24.4甜点.ydk";
  std::wstring ydk_file_wpath = string_to_wstring(ydk_file_path);
  std::string image_dir = "D://MyCardLibrary/ygopro/pics";
  std::wstring image_wdir = string_to_wstring(image_dir);

  std::vector<std::wstring> image_paths = load_image_paths_from_ydk(ydk_file_wpath, image_wdir);

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

      std::string image_path_utf8 = wstring_to_string(image_paths[i]);

      // 检查图像文件是否存在
      FILE *file = fopen(image_path_utf8.c_str(), "rb");
      if (!file)
      {
        std::cerr << "Image file not found: " << image_path_utf8 << std::endl;
        continue; // 跳过不存在的图像
      }
      fclose(file);

      // 加载图片
      HPDF_Image image = HPDF_LoadJpegImageFromFile(pdf, image_path_utf8.c_str());
      if (!image)
      {
        std::cerr << "Failed to load image: " << image_path_utf8 << std::endl;
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

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
  std::cerr << "ERROR: error_no=" << error_no << ", detail_no=" << detail_no << std::endl;
  throw std::runtime_error("PDF generation error");
}

std::vector<std::wstring> load_image_paths_from_ydk(const std::wstring &ydk_path, const std::wstring &image_dir)
{
  std::vector<std::wstring> image_paths;
  std::wifstream ydk_file(ydk_path.c_str());
  std::wstring line;

  // 设置本地语言环境，确保可以处理宽字符
  ydk_file.imbue(std::locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>));

  if (!ydk_file.is_open())
  {
    std::wcerr << L"Failed to open file: " << ydk_path << std::endl;
    return image_paths;
  }

  while (std::getline(ydk_file, line))
  {
    // 跳过以 '#' 或 '!' 开头的非数字行
    if (line.empty() || line[0] == L'#' || line[0] == L'!')
    {
      continue;
    }

    // 假设每个数字对应一个图片文件，文件名为数字 + ".jpg"
    std::wstring image_path = image_dir + L"/" + line + L".jpg";
    image_paths.push_back(image_path);
  }

  ydk_file.close();
  return image_paths;
}

std::string wstring_to_string(const std::wstring &wstr)
{
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.to_bytes(wstr);
}
std::wstring string_to_wstring(const std::string &str)
{
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.from_bytes(str);
}