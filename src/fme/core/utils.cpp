#include "utils.h"

namespace fme
{

cv::Mat fme::qImageToCvMat(const QImage &image)
{
  QImage::Format qt_format = image.format();

  cv::Mat img;
  if (
#if QT_VERSION > QT_VERSION_CHECK(5, 5, 0)
      qt_format == QImage::Format_Grayscale8 ||
#endif
      qt_format == QImage::Format_Indexed8){

    img = cv::Mat(image.height(), image.width(), CV_8UC1,
                                const_cast<uchar*>(image.bits()),
                                static_cast<size_t>(image.bytesPerLine())
                                ).clone();
  }
#if QT_VERSION > QT_VERSION_CHECK(5, 13, 0)
  else if (qt_format == QImage::Format_Grayscale16) {
    img = cv::Mat(image.height(), image.width(), CV_16UC1,
                                const_cast<uchar*>(image.bits()),
                                static_cast<size_t>(image.bytesPerLine())
                                ).clone();
  }
#endif
  else if (qt_format == QImage::Format_RGB888) {

    /// Opción 1
//      QImage swapped = image.rgbSwapped();
//      img = cv::Mat(swapped.height(), swapped.width(), CV_8UC3,
//                                  const_cast<uchar*>(swapped.bits()),
//                                  static_cast<size_t>(swapped.bytesPerLine())
//                                  ).clone();

    /// Opción 2
    img = cv::Mat(image.height(), image.width(), CV_8UC3,
                  const_cast<uchar*>(image.constBits()),
                  static_cast<size_t>(image.bytesPerLine())).clone();
    cvtColor(img, img, cv::COLOR_RGB2BGR);

  }
#if QT_VERSION > QT_VERSION_CHECK(5, 2, 0)
  else if (qt_format == QImage::Format_RGBA8888 || qt_format == QImage::Format_RGBX8888 || qt_format == QImage::Format_RGBA8888_Premultiplied) {
    img = cv::Mat(image.height(), image.width(), CV_8UC4,
                  const_cast<uchar*>(image.constBits()),
                  static_cast<size_t>(image.bytesPerLine())).clone();
    cvtColor(img, img, cv::COLOR_RGBA2BGRA);
  }
#endif
  else if (qt_format == QImage::Format_RGB32){
    img = cv::Mat(image.height(), image.width(), CV_8UC4,
                  const_cast<uchar*>(image.constBits()),
                  static_cast<size_t>(image.bytesPerLine())).clone();
    cv::cvtColor(img, img, cv::COLOR_BGRA2BGR);
  } else if (qt_format == QImage::Format_ARGB32 || qt_format == QImage::Format_ARGB32_Premultiplied) {
    img = cv::Mat(image.height(), image.width(), CV_8UC4,
                  const_cast<uchar*>(image.constBits()),
                  static_cast<size_t>(image.bytesPerLine())).clone();
  } else if (qt_format == QImage::Format_RGB16) {

  }
#if QT_VERSION > QT_VERSION_CHECK(5, 12, 0)
  else if (qt_format == QImage::Format_RGBX64 || qt_format == QImage::Format_RGBA64 || qt_format == QImage::Format_RGBA64_Premultiplied) {

  }
#endif
  return img;
}

} // namespace fme
