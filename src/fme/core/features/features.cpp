#include "features.h"

#include <tidop/core/messages.h>

#include <QFileInfo>

namespace fme
{


void featuresWrite(const QString &fname, const std::vector<cv::KeyPoint> &keyPoints, const cv::Mat &descriptors)
{
  QByteArray ba = fname.toLocal8Bit();
  const char *feat_file = ba.data();
  QString ext = QFileInfo(fname).suffix();
  int flags = 0;
  if (ext.compare("xml") == 0) {
    flags = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML;
  } else if (ext.compare("yml") == 0) {
    flags = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML;
  } else if (ext.compare("bin") == 0) {

  } else {
    ba = ext.toLocal8Bit();
    const char *cext = ba.data();
    msgError("file extension '%s' not valid", cext);
    return;
  }
  if (ext.compare("bin") == 0) {
    FILE* fp = std::fopen(feat_file, "wb");
    if (fp) {
      // Cabecera
      // - KeyPoints
      int32_t size = static_cast<int32_t>(keyPoints.size());
      // - Descriptor
      int32_t rows = static_cast<int32_t>(descriptors.rows);
      int32_t cols = static_cast<int32_t>(descriptors.cols);
      int32_t type = descriptors.type();
      std::fwrite("TIDOPLIB-Features2D-#01", sizeof("TIDOPLIB-Features2D-#01"), 1, fp);
      std::fwrite(&size, sizeof(int32_t), 1, fp);
      std::fwrite(&rows, sizeof(int32_t), 1, fp);
      std::fwrite(&cols, sizeof(int32_t), 1, fp);
      std::fwrite(&type, sizeof(int32_t), 1, fp);
      char extraHead[200]; // Reserva de espacio para futuros usos
      std::fwrite(&extraHead, sizeof(char), 200, fp);
      //Cuerpo
      for (auto &kp : keyPoints) {
        std::fwrite(&kp.pt.x, sizeof(float), 1, fp);
        std::fwrite(&kp.pt.y, sizeof(float), 1, fp);
        std::fwrite(&kp.size, sizeof(float), 1, fp);
        std::fwrite(&kp.angle, sizeof(float), 1, fp);
        std::fwrite(&kp.response, sizeof(float), 1, fp);
        std::fwrite(&kp.octave, sizeof(float), 1, fp);
        std::fwrite(&kp.class_id, sizeof(float), 1, fp);
      }
      std::fwrite(descriptors.data, sizeof(float), rows*cols, fp);
      std::fclose(fp);
    } else {
      //msgError("No pudo escribir archivo %s", fname.c_str());
    }
  } else {
    cv::FileStorage fs(feat_file, flags);
    if (fs.isOpened()) {
      if (!keyPoints.empty()) write(fs, "keypoints", keyPoints);
      if (!descriptors.empty()) write(fs, "descriptors", descriptors);
      fs.release();
    } else {
      //msgError("No pudo escribir archivo %s", fname.c_str());
    }
  }
}

void featuresRead(const QString &fname, std::vector<cv::KeyPoint> &keyPoints, cv::Mat &descriptors)
{
  QByteArray ba = fname.toLocal8Bit();
  const char *feat_file = ba.data();
  QString ext = QFileInfo(fname).suffix();
  if (ext.isEmpty() == false) {
    if (ext.compare("bin") == 0) {
      if (FILE* fp = std::fopen(feat_file, "rb")) {
        //cabecera
        char h[24];
        int32_t size;
        int32_t rows;
        int32_t cols;
        int32_t type;
        char extraHead[200];
        std::fread(h, sizeof(char), 24, fp);
        std::fread(&size, sizeof(int32_t), 1, fp);
        std::fread(&rows, sizeof(int32_t), 1, fp);
        std::fread(&cols, sizeof(int32_t), 1, fp);
        std::fread(&type, sizeof(int32_t), 1, fp);
        std::fread(&extraHead, sizeof(char), 200, fp);
        //Cuerpo
        keyPoints.resize(size);
        for (auto &kp : keyPoints) {
          std::fread(&kp.pt.x, sizeof(float), 1, fp);
          std::fread(&kp.pt.y, sizeof(float), 1, fp);
          std::fread(&kp.size, sizeof(float), 1, fp);
          std::fread(&kp.angle, sizeof(float), 1, fp);
          std::fread(&kp.response, sizeof(float), 1, fp);
          std::fread(&kp.octave, sizeof(float), 1, fp);
          std::fread(&kp.class_id, sizeof(float), 1, fp);
        }
        cv::Mat aux(static_cast<int>(rows), static_cast<int>(cols), type);
        std::fread(aux.data, sizeof(float), rows*cols, fp);
        aux.copyTo(descriptors);
        std::fclose(fp);
      } else {
        //msgError("No pudo leer archivo %s", fname.c_str());
      }
    } else if (ext.compare("xml") == 0 || ext.compare("yml") == 0) {

      cv::FileStorage fs(feat_file, cv::FileStorage::READ);
      if (fs.isOpened()) {
        keyPoints.resize(0);
        descriptors.resize(0);
        fs["keypoints"] >> keyPoints;
        fs["descriptors"] >> descriptors;
        fs.release();
      } else {
        //msgError("No pudo leer archivo %s", fname.c_str());
      }
    }
  } else {
    //msgError("Fichero no valido: %s", fname.c_str());
  }
}


} // namespace fme
