#include "features.h"

#include <tidop/core/messages.h>

#include <QFileInfo>


namespace photomatch
{

void featuresWrite(const QString &fname,
                   const std::vector<cv::KeyPoint> &keyPoints,
                   const cv::Mat &descriptors)
{
  QByteArray ba = fname.toLocal8Bit();
  const char *feat_file = ba.data();
  QString ext = QFileInfo(fname).suffix();
  if (ext.compare("bin", Qt::CaseInsensitive) == 0) {

    TL_TODO("Comprobar la escritura/lectura en ORB.")
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
      std::fwrite(descriptors.data, sizeof(float), static_cast<size_t>(rows*cols), fp);
      std::fclose(fp);
    } else {
      //msgError("No pudo escribir archivo %s", fname.c_str());
    }

  } else if (ext.compare("txt", Qt::CaseInsensitive) == 0) {
    
    int32_t size = static_cast<int32_t>(keyPoints.size());
    std::ofstream ofs(feat_file, std::ofstream::trunc);
    if (ofs.is_open()) {
      
      int type = descriptors.type();

      ofs << size << " " <<  descriptors.cols << " " << type << std::endl;

      for (int r = 0; r < size; r++) {
        cv::KeyPoint kp = keyPoints[static_cast<size_t>(r)];
        ofs << kp.pt.x << " " << kp.pt.y << " " << kp.size << " " << kp.angle;
        for (int c = 0; c < descriptors.cols; c++) {
          
          switch (type) {
            case CV_8U:
              ofs << " " << descriptors.at<uchar>(r,c);
              break;  
            case CV_8S:
              ofs << " "  << descriptors.at<schar>(r,c);
              break;  
            case CV_16U: 
              ofs << " "  << descriptors.at<ushort>(r,c);
              break; 
            case CV_16S: 
              ofs << " "  << descriptors.at<short>(r,c);
              break; 
            case CV_32S:
              ofs << " "  << descriptors.at<int>(r,c);
              break; 
            case CV_32F:
              ofs << " "  << descriptors.at<float>(r,c);
              break; 
            case CV_64F:
              ofs << " "  << descriptors.at<double>(r,c);
              break; 
            default:   
              ofs << " "  << -1;
              break; 
          }   
        }
        ofs << std::endl;
      }

      ofs.close();
    }

  } else if (ext.compare("xml", Qt::CaseInsensitive) == 0 || 
             ext.compare("yml", Qt::CaseInsensitive) == 0) {

    int flags = 0;
    if (ext.compare("xml", Qt::CaseInsensitive) == 0) {
      flags = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML;
    } else if (ext.compare("yml", Qt::CaseInsensitive) == 0) {
      flags = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML;
    }
    cv::FileStorage fs(feat_file, flags);
    if (fs.isOpened()) {
      if (!keyPoints.empty()) write(fs, "keypoints", keyPoints);
      if (!descriptors.empty()) write(fs, "descriptors", descriptors);
      fs.release();
    } else {
      //msgError("No pudo escribir archivo %s", fname.c_str());
    }

  } else {
    ba = ext.toLocal8Bit();
    const char *cext = ba.data();
    msgError("file extension '%s' not valid", cext);
    return;
  }
}

void featuresRead(const QString &fname,
                  std::vector<cv::KeyPoint> &keyPoints,
                  cv::Mat &descriptors)
{
  QByteArray ba = fname.toLocal8Bit();
  const char *feat_file = ba.data();
  QString ext = QFileInfo(fname).suffix();
  if (ext.isEmpty() == false) {
    if (ext.compare("bin", Qt::CaseInsensitive) == 0) {

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
        keyPoints.resize(static_cast<size_t>(size));
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
        std::fread(aux.data, sizeof(float), static_cast<size_t>(rows*cols), fp);
        aux.copyTo(descriptors);
        aux.release();
        std::fclose(fp);
      } else {
        //msgError("No pudo leer archivo %s", fname.c_str());
      }

    } else if (ext.compare("txt", Qt::CaseInsensitive) == 0) {

      std::ifstream ifs(feat_file);
      std::string line;
      if (ifs.is_open()) {

        int type;
        int size;
        int cols;

        std::getline(ifs, line);
        std::istringstream stream(line);
        stream >> type >> size >> cols;

        keyPoints.resize(static_cast<size_t>(size));
        descriptors = cv::Mat(size, cols, type);

        int r = 0;
        while (std::getline(ifs, line)) {

          QStringList list = QString(line.c_str()).split(" ");
          keyPoints[static_cast<size_t>(r)].pt.x = list[0].toFloat();
          keyPoints[static_cast<size_t>(r)].pt.y = list[1].toFloat();
          keyPoints[static_cast<size_t>(r)].size = list[2].toFloat();
          keyPoints[static_cast<size_t>(r)].angle = list[3].toFloat();

          for (int c = 0; c < cols; c++) {
            switch (type) {
              case CV_8U:
                descriptors.at<uchar>(r,c) = static_cast<uchar>(list[c+4].toFloat());
                break;
              case CV_8S:
                descriptors.at<schar>(r,c) = static_cast<schar>(list[c+4].toFloat());
                break;
              case CV_16U:
                descriptors.at<ushort>(r,c) = static_cast<ushort>(list[c+4].toFloat());
                break;
              case CV_16S:
                descriptors.at<short>(r,c) = static_cast<short>(list[c+4].toFloat());
                break;
              case CV_32S:
                descriptors.at<int>(r,c) = static_cast<int>(list[c+4].toFloat());
                break;
              case CV_32F:
                descriptors.at<float>(r,c) = list[c+4].toFloat();
                break;
              case CV_64F:
                descriptors.at<double>(r,c) = static_cast<double>(list[c+4].toFloat());
                break;
              default:
                break;
            }
          }
          r++;
        }

        ifs.close();
      }

    } else if (ext.compare("xml", Qt::CaseInsensitive) == 0 ||
               ext.compare("yml", Qt::CaseInsensitive) == 0) {

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
    } else {
      ba = ext.toLocal8Bit();
      const char *cext = ba.data();
      msgError("file extension '%s' not valid", cext);
      return;
    }
  } else {
    //msgError("Fichero no valido: %s", fname.c_str());
  }
}


} // namespace photomatch
