#include "./include/PrintPDF.h"

int main()
{
  std::string deck_dir = "../deck";
  std::wstring deck_wdir = string_to_wstring(deck_dir);
  std::string image_dir = "../pics";
  std::wstring image_wdir = string_to_wstring(image_dir);
  std::vector<std::wstring> ydk_files = get_ydk_files(deck_wdir);
  for (const auto &ydk_file : ydk_files)
  {
    std::wcout << L"Processing YDK file: " << ydk_file << std::endl;
    // 调用 print_pdf 函数
    print_pdf(ydk_file, image_wdir);
  }
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

void print_pdf(const std::wstring &ydk_file_wpath, const std::wstring &image_wdir)
{
  std::vector<std::wstring> image_paths = load_image_paths_from_ydk(ydk_file_wpath, image_wdir);

  // 初始化 PDF 文档
  HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
  if (!pdf)
  {
    std::cerr << "Failed to create PDF object" << std::endl;
    return;
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
          return;
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
    // fs::path ydk_path(ydk_file_wpath);
    // std::wstring output_pdf_wname = ydk_path.stem().wstring() + L".pdf";
    // std::string output_pdf_name = "./outputPDF/" + wstring_to_string(output_pdf_wname);
    // // 保存 PDF 文件
    // HPDF_SaveToFile(pdf, output_pdf_name.c_str());
    // std::wcout << "PDF saved to " << output_pdf_wname << std::endl;
    fs::path ydk_path(ydk_file_wpath);
    std::wstring output_pdf_wname = ydk_path.stem().wstring() + L".pdf";
    std::string temp_pdf_name = "temp_output.pdf"; // 临时文件名

    // 保存 PDF 文件到临时文件
    HPDF_SaveToFile(pdf, temp_pdf_name.c_str());

    // 使用 _wrename 来重命名文件为宽字符路径
    std::wstring output_pdf_wpath = L"./outputPDF/" + output_pdf_wname;
    if (_wrename(std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(temp_pdf_name).c_str(),
                 output_pdf_wpath.c_str()) != 0)
    {
      std::wcerr << L"Failed to rename PDF to " << output_pdf_wpath << std::endl;
    }
    else
    {
      std::wcout << L"PDF saved to " << output_pdf_wname << std::endl;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
    HPDF_Free(pdf);
    return;
  }

  // 释放 PDF 对象
  HPDF_Free(pdf);
  return;
}

std::vector<std::wstring> get_ydk_files(const std::wstring &directory)
{
  std::vector<std::wstring> ydk_files;
  for (const auto &entry : fs::directory_iterator(directory))
  {
    if (entry.path().extension() == L".ydk")
    {
      ydk_files.push_back(entry.path().wstring());
    }
  }
  return ydk_files;
}