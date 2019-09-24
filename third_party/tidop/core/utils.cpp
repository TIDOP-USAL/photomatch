/****************************************************************************
 *                                                                          *
 *  This file is part of TidopLib and can not be copied and/or distributed  *
 *  without the express permision of ITOS3D ENGINEERING S.L                 *
 *                                                                          *
 *  Contact: http://www.itos3d.com                                          *
 *           http://tidop.usal.es                                           *
 *                                                                          *
 *--------------------------------------------------------------------------*
 *                                                                          *
 *  Copyright (C) 2018, ITOS3D ENGINEERING S.L - All rights reserved        *
 *                                                                          *
 ****************************************************************************/

#include "tidop/core/utils.h"

#include "tidop/core/messages.h"
#include "tidop/core/console.h"
#include "tidop/core/exception.h"

#ifdef HAVE_GDAL
TL_SUPPRESS_WARNINGS
#include "gdal.h"
TL_DEFAULT_WARNINGS
#endif // HAVE_GDAL

#if defined __linux__ || defined __GNUC__
#include <unistd.h>
#include <sys/stat.h>
#include <libgen.h>
#include <dirent.h>
#endif

#define __STDC_WANT_LIB_EXT1__ 1
#include <ctime>
#include <cstring>

// Paralelismo
#if defined HAVE_OMP
#  include <omp.h>  // OpenMP
#elif defined (HAVE_PPL) && ( defined (_MSC_VER) && _MSC_VER >= 1600)
#  define TL_MSVS_CONCURRENCY
#  include <ppl.h>  // Parallel Patterns Library (PPL)
#else
#  include <thread>
#endif

#if (__cplusplus >= 201703L)
namespace fs = std::filesystem;
#else
namespace fs = boost::filesystem;
#endif

namespace tl
{

/* ---------------------------------------------------------------------------------- */

const char *getRunfile()
{
  static char runfile[TL_MAX_PATH];
#ifdef WIN32
  ::GetModuleFileNameA(nullptr, runfile, TL_MAX_PATH);
#else
   char szTmp[32];
   sprintf(runfile, "/proc/%d/exe", getpid());
   int len = readlink(szTmp, runfile, TL_MAX_PATH);
   if(len >= 0)
     runfile[len] = '\0';
#endif
  return runfile;
}

bool isDirectory(const char *path)
{
#ifdef WIN32
  DWORD ftyp = GetFileAttributesA(path);
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;
  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;
#else
  struct stat sb;
  if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
    return true;

#endif
  return false;
}
bool isDirectory(const std::string &path)
{
  return isDirectory(path.c_str());
}

bool isFile(const char *file)
{
#ifdef WIN32
  FILE *fp;
  errno_t err = fopen_s(&fp, file, "rb");
  if (err != 0) {
    return false;
  } else {
    std::fclose(fp);
    return true;
  }
#else
  struct stat buffer;
  return (stat(file, &buffer) == 0);
#endif
}
bool isFile(const std::string &file)
{
  return isFile(file.c_str());
}

int createDir(const char *path)
{
  int i_ret = 0;
  if (isDirectory(path)) return 1;

  std::vector<std::string> splitPath;
  split(path, splitPath, "\\");
  if (splitPath.size() == 1)
    split(path, splitPath, "/");

  std::string _path = "";
  try {
    for (size_t i = 0; i < splitPath.size(); i++) {
      _path += splitPath[i];
      _path += "\\";
      if (!isDirectory(_path.c_str())) {

#ifdef _MSC_VER

        if (!CreateDirectoryA(_path.c_str(), nullptr)) {
          i_ret = -1;
        }

#else

        std::string mkdir = "mkdir \"";
        mkdir.append(_path);
        mkdir.append("\"");
        if(system(mkdir.c_str())==0)
          i_ret = -1;
#endif
      }
    }
  } catch (std::exception &e) {
    msgError(e.what());
    i_ret = -1;
  }

  return i_ret;
}

int deleteDir(const char *path, bool confirm)
{
  int i_ret = 0;
  try {
    if (isDirectory(path)) {
      std::string delDir = "rmdir /s ";
      if (!confirm) delDir += "/q ";
      std::string str = path;
      replaceString(&str, "/", "\\");
      delDir += str;
      if(system(delDir.c_str()))
        i_ret = 0;
      else i_ret = 1;
    } else {
      i_ret = 1;
    }
  } catch (std::exception &e) {
    msgError(e.what());
    i_ret = -1;
  }
  return i_ret;
}

int move(const char *in, const char *out)
{
#ifdef WIN32

  size_t len = strlen(in) + 1;
  wchar_t * w_in = new wchar_t[len];
  size_t convertedChars = 0;
  mbstowcs_s(&convertedChars, w_in, len, in, _TRUNCATE);

  len = strlen(out) + 1;
  wchar_t * w_out = new wchar_t[len];
  convertedChars = 0;
  mbstowcs_s(&convertedChars, w_out, len, out, _TRUNCATE);

  if (!MoveFileEx(w_in, w_out, MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
    //printf("MoveFileEx failed with error %d\n", GetLastError());
    msgError("%s", formatWindowsErrorMsg(GetLastError()).c_str());
    return 1;
  } else {
    //tprintf(TEXT("%s has been moved to %s\n"), argv[1], argv[2]);
    return 0;
  }

  delete[] w_in;
  delete[] w_out;

#else
  ///TODO: Completar
#endif
}

int getFileDir(const char *path, char *dir, int size)
{
#ifdef _MSC_VER
  return _splitpath_s(path, NULL, NULL, dir, size, NULL, NULL, NULL, NULL);
#else
  char *dirc = (char *)malloc(size);//strdup(path);
  if (dirc) dir = dirname(dirc);
  return (dir) ? 0 : 1;
#endif
}

#ifdef _MSC_VER
int getFileDrive(const char *path, char *drive, int size)
{
  int r_err = 0;
  r_err = _splitpath_s(path, drive, size, NULL, NULL, NULL, NULL, NULL, NULL);
  return r_err;
}

int getFileExtension(const char *path, char *ext, int size)
{
  int r_err = 0;
  r_err = _splitpath_s(path, NULL, NULL, NULL, NULL, NULL, NULL, ext, size);
  return r_err;
}
#endif

int getFileName(const char *path, char *name, int size)
{
#ifdef _MSC_VER
  return _splitpath_s(path, NULL, NULL, NULL, NULL, name, size, NULL, NULL);
#elif defined __GNUC__
  ///TODO: Completar
#else
  char *basec = (char *)malloc(size);
  if (basec) name = basename(basec);
  return (name) ? 0 : 1;
#endif
}

int getFileDriveDir(const char *path, char *drivedir, int size)
{
  int r_err = 0;
  char drive[TL_MAX_DRIVE];
  char dir[TL_MAX_DIR];
#ifdef _MSC_VER
  r_err = _splitpath_s(path, drive, TL_MAX_DRIVE, dir, TL_MAX_DIR, NULL, NULL, NULL, NULL);
  strcpy_s(drivedir, size, drive);
  strcat_s(drivedir, size, dir);
#else
  char *dirc = (char *)malloc(size);
  if (dirc) drivedir = dirname(dirc);
  return (drivedir) ? 0 : 1;
#endif
  return r_err;
}

int changeFileName(const char *path, const char *newName, char *pathOut, int size)
{
  int r_err = 0;
  char drive[TL_MAX_DRIVE];
  char dir[TL_MAX_DIR];
  char ext[TL_MAX_EXT];
#ifdef _MSC_VER

  r_err = _splitpath_s(path, drive, TL_MAX_DRIVE, dir, TL_MAX_DIR, NULL, NULL, ext, TL_MAX_EXT);
  if (r_err == 0)
    r_err = _makepath_s(pathOut, size, drive, dir, newName, ext);
#else
  ///TODO: Completar
#endif
  return r_err;
}

int changeFileExtension(const char *path, const char *newExt, char *pathOut, int size)
{
  int r_err = 0;
  char drive[TL_MAX_DRIVE];
  char dir[TL_MAX_DIR];
  char fname[TL_MAX_FNAME];
#ifdef _MSC_VER

  r_err = _splitpath_s(path, drive, TL_MAX_DRIVE, dir, TL_MAX_DIR, fname, TL_MAX_FNAME, NULL, NULL);
  if (r_err == 0)
    r_err = _makepath_s(pathOut, size, drive, dir, fname, newExt);
#else
  ///TODO: Completar
#endif
  return r_err;
}

int changeFileNameAndExtension(const char *path, const char *newNameExt, char *pathOut, int size)
{
  int r_err = 0;
  char drive[TL_MAX_DRIVE];
  char dir[TL_MAX_DIR];
#ifdef _MSC_VER

  r_err = _splitpath_s(path, drive, TL_MAX_DRIVE, dir, TL_MAX_DIR, NULL, NULL, NULL, NULL);
  if (r_err == 0) {
    std::vector<std::string> nameext;
    split(newNameExt, nameext, ".");
    r_err = _makepath_s(pathOut, size, drive, dir, nameext[0].c_str(), nameext[1].c_str());
  }
#else
  ///TODO: Completar
#endif
  return r_err;
}

void directoryList(const char *directory, std::list<std::string> *dirList)
{
#ifdef _MSC_VER
  WIN32_FIND_DATAA findData;
  HANDLE hFind;

  char dir[TL_MAX_PATH];
  strcpy_s(dir, TL_MAX_PATH, directory);
  strcat_s(dir, TL_MAX_PATH, "/*");

  hFind = FindFirstFileA(dir, &findData);
  if (hFind == INVALID_HANDLE_VALUE) {
    msgError("FindFirstFile failed (%d)\n", GetLastError());
    return;
  } else {
    while (FindNextFileA(hFind, &findData) != 0) {
      if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        if (strcmp(findData.cFileName, "..") == 0) continue;
        dirList->push_back(findData.cFileName);
      }
    }
    FindClose(hFind);
  }
#else
  //TODO: Sin probar...
  DIR *dir = opendir(directory);

  struct dirent *entry = readdir(dir);

  while (entry != NULL) {
    if (entry->d_type == DT_DIR)
      dirList->push_back(entry->d_name);

    entry = readdir(dir);
  }
  closedir(dir);
#endif
}

TL_DISABLE_WARNING(TL_WARNING_DEPRECATED)
void fileList(const char *directory, std::list<std::string> *fileList, const char *wildcard)
{
#ifdef _MSC_VER
  WIN32_FIND_DATAA findData;
  HANDLE hFind;

  //char dir[TL_MAX_PATH];
  //strcpy(dir, directory);
  //strcat(dir, "\\"); // TODO: el tema de las barras aunque a efectos practicos de igual no queda elegante el mezclar los dos tipos de barras...
  //strcat(dir, wildcard);
  //Path _path(directory);
  fs::path _path(directory);
  msgInfo(_path.string().c_str());
  _path.append(wildcard);
  msgInfo(_path.string().c_str());
  hFind = FindFirstFileA(/*dir*/ fs::path(directory).append(wildcard).string().c_str(), &findData);

  if (hFind == INVALID_HANDLE_VALUE) {
    msgError("FindFirstFile failed (%d)\n", GetLastError());
    return;
  } else {
    fileList->push_back(findData.cFileName);
    while (FindNextFileA(hFind, &findData) != 0) {
      fileList->push_back(findData.cFileName);
    }
    FindClose(hFind);
  }
#else
   ///TODO: Completar
#endif
}
TL_ENABLE_WARNING(TL_WARNING_DEPRECATED)

/// https://stackoverflow.com/questions/1257721/can-i-use-a-mask-to-iterate-files-in-a-directory-with-boost
void fileList(const std::string &directory, std::list<std::string> *fileList, const std::regex &filter)
{

  fs::directory_iterator itr_end;
  for (fs::directory_iterator it(directory); it != itr_end; ++it) {
    // Skip if not a file
    if (!fs::is_regular_file(it->status())) continue;

    std::smatch what;
    std::string fname = it->path().filename().string();
    if (!std::regex_match(fname, what, filter)) continue;

    // File matches, store it
    if (fileList)
      fileList->push_back(it->path().filename().string());
  }

}

void fileListByExt(const std::string &directory, std::list<std::string> *fileList, const std::string &ext)
{

  fs::directory_iterator itr_end;
  for (fs::directory_iterator it(directory); it != itr_end; ++it) {
    // Skip if not a file
    if (!fs::is_regular_file(it->status())) continue;

    fs::path _path = it->path();

    TL_TODO("Compare es case sensitive");
    std::string _ext = it->path().extension().string();

    if (it->path().extension().compare(ext) == 0) {
      // File matches, store it
      if (fileList)
        fileList->push_back(it->path().filename().string());
    }
  }

}

/* ---------------------------------------------------------------------------------- */

#ifdef TL_ENABLE_DEPRECATED_METHODS

// TODO: C++17 incluye filesystem que tiene una clase path.
//       Ahora se incluye con BOOST. La podria utilizar directamente y si el compilador
//       no soporta c++17 se utilizar?a BOOST

// Se desactiva el warning que se establece al hacer la clase deprecated para la propia clase
//TL_DISABLE_WARNING(4996)
TL_DISABLE_WARNING(TL_WARNING_DEPRECATED)
Path::Path()
  : mPos(0),
    mPath(0),
    mFileName(""),
    mFileExtension(""),
    bFile(false)
{
}

Path::Path(const std::string &path)
  : mPos(0),
    mPath(0),
    mFileName(""),
    mFileExtension(""),
    bFile(false)
{
  parse(path);
}

Path::Path(const Path &path)
  : mPos(path.mPos),
    mPath(path.mPath),
    mFileName(path.mFileName),
    mFileExtension(path.mFileExtension),
    bFile(path.bFile)
{
}

Path::~Path()
{
}

Path &Path::operator=(const Path &path)
{
  mPos = path.mPos;
  mPath = path.mPath;
  mFileName = path.mFileName;
  mFileExtension = path.mFileExtension;
  bFile = path.bFile;
  return *this;
}

void Path::parse(const std::string &path)
{
//  char name[TL_MAX_FNAME];
//  char drive[TL_MAX_DRIVE];
//  char dir[TL_MAX_DIR];
//  char ext[TL_MAX_EXT];
//#ifdef _MSC_VER
//  int r_err = _splitpath_s(path, drive, TL_MAX_DRIVE, dir, TL_MAX_DIR, name, TL_MAX_FNAME, ext, TL_MAX_EXT);
//
//#endif

  // Se comprueba si es un fichero
  //char name[TL_MAX_FNAME];
  //if (getFileName(path.c_str(), name, TL_MAX_FNAME) == 0) {
  //  mFileName = name;
  //  bFile = true;
  //}

  // Extensi?n
  //char ext[TL_MAX_EXT];
  //if (getFileExtension(path.c_str(), ext, TL_MAX_EXT) == 0) {
  //  mFileExtension = ext;
  //}

  //char drive[TL_MAX_DRIVE];
  //if (getFileDrive(path.c_str(), drive, TL_MAX_DRIVE) == 0) {
  //  mDrive = drive;
  //}

  //char dir[TL_MAX_DIR];
  //if (getFileDir(path.c_str(), dir, TL_MAX_DIR) == 0) {
  //
  //}

  split(path, mPath, "/\\");
  mPos = static_cast<int>(mPath.size());
  if (mPath.size() == 0) return;

  // rutas relativas
  if (mPath[0] == std::string("..")) {
    char dir[TL_MAX_DIR];
    getFileDriveDir(getRunfile(), dir, TL_MAX_DIR);
    //std::string runFilePath = getRunfile();
    Path runPath(dir);
    int i = 0;
    for (; mPath[i] == std::string(".."); i++) {
      runPath.down();
    }

    std::vector<std::string> current = runPath.currentPath();
    for (int j = i; j < mPath.size(); j++)
      current.push_back(mPath[j]);
    mPath = current;
    mPos = static_cast<int>(mPath.size());
  } else if (mPath[0] == std::string(".")) {
    char dir[TL_MAX_DIR];
    getFileDriveDir(getRunfile(), dir, TL_MAX_DIR);
    Path runPath(dir);
    std::vector<std::string> current = runPath.currentPath();
    for (int j = 1; j < mPath.size(); j++)
      current.push_back(mPath[j]);
    mPath = current;
    mPos = static_cast<int>(mPath.size());
  }
}

#if defined WIN32
const char *Path::getDrive()
{
  //TODO: Esto s?lo en Windows...
  //return mPath[0].c_str();
  return mDrive.c_str();
}
#endif

void Path::up()
{
  if (mPos < mPath.size())
    mPos++;
}

void Path::down()
{
  if (mPos != 0)
    mPos--;
}

std::vector<std::string> Path::currentPath()
{
  std::vector<std::string> cur_path;
  for (int i = 0; i < mPos; i++) {
    cur_path.push_back(mPath[i]);
  }
  return cur_path;
}


std::string Path::toString()
{
  std::string _path;
  for (int i = 0; i < mPos; i++) {
    _path.append(mPath[i]);
    if (i < mPos - 1) _path.append("\\");
  }
  return _path;
}

std::list<std::string> Path::files(const std::string &wildcard)
{
  std::list<std::string> files;
  fileList(toString().c_str(), &files, wildcard.c_str());
  return files;
}

std::list<std::string> Path::dirs()
{
  std::list<std::string> dirs;
  directoryList(toString().c_str(), &dirs);
  return dirs;
}

bool Path::isDirectory()
{
  return !bFile;
}

bool Path::isFile()
{
  return bFile;
}

void Path::createDir()
{
  tl::createDir(toString().c_str());
}

void Path::deleteDir()
{
  tl::deleteDir(toString().c_str());
}

Path &Path::append(const std::string &dir)
{
  //TODO: Si el path es de un fichero no se puede a?adir...
  mPath.push_back(dir);
  return *this;
}

TL_ENABLE_WARNING(TL_WARNING_DEPRECATED)

#endif // TL_ENABLE_DEPRECATED_METHODS

/* ---------------------------------------------------------------------------------- */
/*                             Operaciones con cadenas                                */
/* ---------------------------------------------------------------------------------- */

int splitToNumbers(const std::string &cad, std::vector<int> &vOut, const char *chs)
{
  int r_err = 0;
  char *dup = strdup(cad.c_str()); // -> warning C4996: 'strdup': The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strdup
  //char *dup = _strdup(cad.c_str());
  vOut.resize(0);

  try {
    char *token = strtok(dup, chs);
    //char *context = NULL;
    //char *token = strtok_s(dup, chs, &context);
    while (token != nullptr) {
      char *pEnd;
      int number = strtol(token, &pEnd, 10);
      if (*pEnd == 0) {
        vOut.push_back(number);
        token = strtok(nullptr, chs);
        //token = strtok_s(dup, chs, &context);
      } else
        throw std::runtime_error("Split string to numbers fail");
    }
  } catch (std::exception &e) {
    vOut.resize(0);
    msgError(e.what());
    r_err = 1;
  }

  free(dup);
  return r_err;
}

int splitToNumbers(const std::string &cad, std::vector<double> &vOut, const char *chs)
{
  int r_err = 0;
  char *dup = strdup(cad.c_str());
  //char *dup = _strdup(cad.c_str());
  vOut.resize(0);

  try {
    char *token = strtok(dup, chs);
    //char *context = NULL;
    //char *token = strtok_s(dup, chs, &context);
    while (token != NULL) {
      //vOut.push_back(atof(token));
      char *pEnd;
      double number = strtod(token, &pEnd);
      if (*pEnd == 0) {
        vOut.push_back(number);
        token = strtok(nullptr, chs);
        //token = strtok_s(dup, chs, &context);
      } else
        throw std::runtime_error("Split string to numbers fail");
    }
  } catch (std::exception &e) {
    vOut.resize(0);
    msgError(e.what());
    r_err = 1;
  }

  free(dup);
  return r_err;
}

void replaceString(std::string *str, const std::string &str_old, const std::string &str_new)
{
  std::size_t ini = str->find(str_old);
  //std::size_t end;
  while (ini != std::string::npos) {
    //end = ini + str_old.size();
    str->replace(ini, str_old.size(), str_new);
    ini = str->find(str_old, str_new.size() + ini);
  }
}

int split(const std::string &in, std::vector<std::string> &out, const char *chs)
{
  out.resize(0);
  int r_err = 0;
  char *dup;
#ifdef __GNUC__
  size_t len = strlen(in.c_str())+1;
  char *s = (char *)malloc(len);
  if (!s) return 1;
  dup = (char *)memcpy(s, in.c_str(), len);
#else
  dup = _strdup(in.c_str());
#endif
  try {
#ifdef __STDC_LIB_EXT1__
    char *context = nullptr;
    char *token = strtok_s(dup, chs, &context);
    while (token != nullptr) {
      out.push_back(std::string(token));
      token = strtok_s(nullptr, chs, &context);
    }
#else
    char *token = strtok(dup, chs);
    while (token != nullptr) {
      out.push_back(std::string(token));
      token = strtok(nullptr, chs);
    }
#endif
  } catch (std::exception &e) {
    msgError(e.what());
    r_err = 1;
  }
  free(dup);
  return r_err;
}

int stringToInteger(const std::string &text, Base base)
{
  std::istringstream ss(text);
  switch (base) {
  case Base::octal:
    ss.setf(std::ios_base::oct, std::ios::basefield);
    break;
  case Base::decimal:
    ss.setf(std::ios_base::dec, std::ios::basefield);
    break;
  case Base::hexadecimal:
    ss.setf(std::ios_base::hex, std::ios::basefield);
    break;
  default:
    break;
  }
  int number;
  return ss >> number ? number : 0;
}

/* ---------------------------------------------------------------------------------- */
/*                Utilidades de carga y guardado para OpenCV                          */
/* ---------------------------------------------------------------------------------- */

#ifdef HAVE_OPENCV

void loadCameraParams(const std::string &file, cv::Size &imageSize, cv::Mat &cameraMatrix, cv::Mat& distCoeffs)
{
  cv::FileStorage fs(file, cv::FileStorage::READ);
  fs["image_width"] >> imageSize.width;
  fs["image_height"] >> imageSize.height;
  fs["camera_matrix"] >> cameraMatrix;
  fs["distortion_coefficients"] >> distCoeffs;
  fs.release();
}

int loadBinMat(const char *file, cv::Mat *data)
{
  FILE *fp = std::fopen(file, "rb");
  if (!fp) {
    return 1;
  }
  int i_ret = 0;
  //cabecera
  int32_t rows;
  int32_t cols;
  int32_t type;
  try {
    size_t err = std::fread(&rows, sizeof(int32_t), 1, fp);
    TL_THROW_ASSERT(err != 1, "Reading error")
    err = std::fread(&cols, sizeof(int32_t), 1, fp);
    TL_THROW_ASSERT(err != 1, "Reading error")
    err = std::fread(&type, sizeof(int32_t), 1, fp);
    TL_THROW_ASSERT(err != 1, "Reading error")
    //Cuerpo
    cv::Mat aux(rows, cols, type);
    err = std::fread(aux.data, sizeof(float), rows*cols, fp);
    TL_THROW_ASSERT(err != rows*cols, "Reading error")
    aux.copyTo(*data);
  } catch (std::exception &e) {
    msgError(e.what());
    i_ret = 1;
  }
  std::fclose(fp);
  return i_ret;
}

int saveBinMat(const char *file, cv::Mat &data)
{
  FILE* fp = std::fopen(file, "wb");
  if (!fp) {
    return 1;
  }
  int i_ret = 0;
  //cabecera
  int32_t rows = data.rows;
  int32_t cols = data.cols;
  int32_t type = data.type();
  try {
    std::fwrite(&data.rows, sizeof(int32_t), 1, fp);
    std::fwrite(&data.cols, sizeof(int32_t), 1, fp);
    std::fwrite(&type, sizeof(int32_t), 1, fp);
    //Cuerpo
    std::fwrite(data.data, sizeof(float), rows*cols, fp);
  } catch (std::exception &e) {
    msgError(e.what());
    i_ret = 1;
  }
  std::fclose(fp);
  return i_ret;
}

#endif // HAVE_OPENCV

/* ---------------------------------------------------------------------------------- */
/*                         Concurrencia, hilos y multiproceso                         */
/* ---------------------------------------------------------------------------------- */

// A?adir cancelaci?n para poder detener los procesos en caso de error

uint32_t getOptimalNumberOfThreads()
{
#ifdef HAVE_OMP
  //TODO: Sin probar
  return omp_get_max_threads();
#elif defined TL_MSVS_CONCURRENCY
  return Concurrency::CurrentScheduler::Get()->GetNumberOfVirtualProcessors();
#else
  uint32_t n_threads = std::thread::hardware_concurrency();
  return n_threads == 0 ? 1 : n_threads;
#endif
}

void parallel_for(size_t ini, size_t end, std::function<void(int)> f)
{
  //uint64_t time_ini = getTickCount();
#ifdef HAVE_OMP
  //TODO: Sin probar
  #pragma omp parallel for
  for (size_t i = ini; i < end; i++) {
    f(i);
  }
#elif defined TL_MSVS_CONCURRENCY
  Concurrency::cancellation_token_source cts;
  //Concurrency::run_with_cancellation_token([ini, end, f]() {
  //  Concurrency::parallel_for(ini, end, f);
  //},cts.get_token());
  Concurrency::parallel_for(ini, end, f);
#else

  auto f_aux = [&](int ini, int end) {
    for (int r = ini; r < end; r++) {
      f(r);
    }
  };

  size_t num_threads = getOptimalNumberOfThreads();
  std::vector<std::thread> threads(num_threads);

  size_t size = (end - ini) / num_threads;
  for (size_t i = 0; i < num_threads; i++) {
    size_t _ini = i * size + ini;
    size_t _end = _ini + size;
    if (i == num_threads -1) _end = end;
    threads[i] = std::thread(f_aux, _ini, _end);
  }

  for (auto &_thread : threads) _thread.join();
#endif
  //double time = (getTickCount() - time_ini) / 1000.;
  //printf("Time %f", time);
}


///TODO: A?adir m?todo para ejecutar c?digo de forma asincrona
// std::async
// Concurrency::task<T> (PPL)

/* ---------------------------------------------------------------------------------- */
/*                                 Medici?n de tiempos                                */
/* ---------------------------------------------------------------------------------- */

std::string formatTimeToString(const std::string &templ)
{
  std::string time_format;
  char date[80];
  struct tm _tm;
  std::time_t now = std::time(NULL);
#ifdef __STDC_LIB_EXT1__
    _tm = *std::localtime_s(&now, &_tm);
#else
    _tm = *std::localtime(&now);
#endif

  std::strftime(date, 80, templ.c_str(), &_tm);
  time_format = std::string(date);

  return time_format;
}


uint64_t tickCount()
{
#if defined _MSC_VER
  return GetTickCount64();
#else
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
#endif
}
uint64_t getTickCount()
{
  return tickCount();
}


Chrono::Chrono()
  : mTimeIni(0),
    mAccumulated(0),
    mStatus(Chrono::Status::start),
    mMessage(""),
    bWriteMsg(false)
{
  //run();
}

Chrono::Chrono(const char *msg, bool writeMsg)
  : mTimeIni(0),
    mAccumulated(0),
    mStatus(Chrono::Status::start),
    mMessage(msg),
    bWriteMsg(writeMsg)
{
  //run();
}

Chrono::~Chrono()
{
  if (mStatus == Status::running || mStatus == Status::pause) {
    stop();
  }
  mStatus = Status::finalized;
}

uint64_t Chrono::pause()
{
  if (mStatus == Status::running) {
    mAccumulated += tickCount() - mTimeIni;
    mStatus = Status::pause;
    //if (bWriteMsg) msgDebug("Chrono paused");
  }
  return mAccumulated;
}

void Chrono::reset()
{
  mTimeIni = 0;
  mAccumulated = 0;
  mStatus = Status::start;
  mMessage = "";
  //if (bWriteMsg) msgDebug("Chrono reset");
}

void Chrono::resume()
{
  if (mStatus == Status::pause) {
    mTimeIni = tickCount();
    mStatus = Status::running;
    //if (bWriteMsg) msgDebug("Chrono resume");
  }
}

uint64_t Chrono::run()
{
  mTimeIni = tickCount();
  mAccumulated = 0;
  mStatus = Status::running;
  //if (bWriteMsg) msgDebug("Chrono run");
  return mTimeIni;
}

uint64_t Chrono::stop()
{
  uint64_t time;
  if (mStatus == Status::running) {
    time = tickCount() - mTimeIni + mAccumulated;
    mStatus = Status::stopped;
  } else if (mStatus == Status::pause) {
    // Puede estar pausado y querer terminar
    mStatus = Status::stopped;
    time = mAccumulated;
  } else
    time = 0;
  if (bWriteMsg) msgInfo("%s [Time: %f seconds]", mMessage.c_str(), time / 1000.);
  return time;
}

void Chrono::setMessage(const char *msg)
{
  mMessage = msg;
}


/* ---------------------------------------------------------------------------------- */

int readToString(const char *file, std::string *text)
{
  //TODO: Forma muy sencilla para salir de paso por ahora
  std::ifstream in(file);
  *text = static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str();
  //TODO: Por ahora se devuelve 0. Cuando se controlen los errores se devolvera 1 en caso de error
  return 0;
}

VrtTemplate::VrtTemplate() : mText("")
{}

VrtTemplate::VrtTemplate(const char *text) : mText(text)
{}

VrtTemplate::~VrtTemplate()
{}

int VrtTemplate::read(const char *file)
{
  return readToString(file, &mText);
}

int VrtTemplate::replace(std::string *output) const
{
  int i_ret = 0;
  output->append(mText);
  size_t ini = output->find("<#");
  size_t end;
  while (ini != std::string::npos) {
    end = output->find(">", ini);
    size_t size = end - ini + 1;
    std::string tagString = output->substr(ini + 2, end - (ini + 2));
    std::string replaceText;
    replaceTag(tagString, &replaceText);
    output->replace(ini, size, replaceText);
    ini = output->find("<#", replaceText.size());
  }
  return i_ret;
}

void VrtTemplate::setTemplate(const char *templ)
{
  mText = templ;
}


HtmlTemplate::HtmlTemplate()
  : VrtTemplate(),
  mTagValues()
{}

HtmlTemplate::HtmlTemplate(const char *text, const std::map<std::string, std::string> &tag_values)
  : VrtTemplate(text),
  mTagValues(tag_values)
{

}

HtmlTemplate::~HtmlTemplate()
{

}

void HtmlTemplate::replaceTag(const std::string &tag, std::string *replaceText) const
{
  std::map<std::string, std::string>::const_iterator it = mTagValues.find(tag);
  if (it != mTagValues.end())
    *replaceText = it->second;
  else
    *replaceText = "";
}


/* ---------------------------------------------------------------------------------- */

Csv::Csv()
  : File()
{
}

Csv::Csv(const char *file, Mode mode)
  : File(file, mode)
{
  open(file, mode);
}

Csv::Csv(const Csv &csv)
  : File(csv)
{
}

Csv::~Csv()
{
  close();
}

void Csv::close()
{
  if (fs.is_open())
    fs.close();
}

//Csv::Status Csv::create(std::shared_ptr<TableHeader> tableHeader)
//{
//  if (!fs.is_open()) {
//    msgError("No se ha abierto el archivo");
//    return Status::FAILURE;
//  }
//
//  if (mMode != Mode::Create) {
//    msgError("Utilice el modo 'Create' para abrir el archivo");
//    return Status::FAILURE;
//  }
//
//  setName(File::mName.c_str());
//  setTableHeader(tableHeader);
//
//  size_t size = getFieldCount();
//  for (size_t i = 0; i < size; i++) {
//    fs << tableHeader->getTableHeaderField(i)->getName();
//    if (i != size -1) fs << ";";
//  }
//  fs << std::endl;
//
//  return Status::SUCCESS;
//}

Csv::Status Csv::create(const std::string &header)
{
  if (!fs.is_open()) {
    msgError("No se ha abierto el archivo %s", mFile.c_str());
    return Status::failure;
  }

  if (mMode != Mode::create) {
    msgError("Utilice el modo 'Create' al abrir el archivo");
    return Status::failure;
  }

  //setName(File::mName.c_str());


  std::vector<std::string> out;
  if (split(header, out, ";") == 0) {
    size_t size = out.size();
    for (size_t i = 0; i < size; i++) {
      fs << out[i];
      if (i != size - 1) fs << ";";
    }
    fs << std::endl;
    return Status::success;
  } else
    return Status::failure;
}

//Csv::Status Csv::create(const DataTable &dataTable)
//{
//  if (!fs.is_open()) {
//    msgError("No se ha abierto el archivo");
//    return Status::FAILURE;
//  }
//
//  if (mMode != Mode::Create) {
//    msgError("Utilice el modo 'Create' para abrir el archivo");
//    return Status::FAILURE;
//  }
//
//  size_t size = dataTable.getFieldCount();
//
//  // Cabecera
//
//  const TableHeader *header = dataTable.getTableHeader();
//  for (size_t i = 0; i < size; i++) {
//    fs << header->getTableHeaderField(i)->getName();
//    if (i != size -1) fs << ";";
//  }
//  fs << std::endl;
//
//  // datos
//  for (auto &reg : dataTable) {
//    size_t size = getFieldCount();
//    for (size_t i = 0; i < size; i++) {
//      fs << reg->getValue(i);
//      if (i != size -1) fs << ";";
//    }
//    fs << std::endl;
//  }
//
//  return Status::SUCCESS;
//}

Csv::Status Csv::createCopy(const std::string &fileOut)
{
  Csv csv;
  csv.open(fileOut, Mode::create);
  //csv.create(std::make_shared<TableHeader>(getTableHeader()));
  return Status::failure;
}

Csv::Status Csv::open(const std::string &file, Mode mode, FileOptions *options)
{
  close();

  mFile = file;
  mMode = mode;

  //fs::path _path(file);
  //fs::path ext = _path.extension().string();
  
  if (boost::iequals(fs::path(file).extension().string(), ".csv") == false) return Status::open_fail;

  std::ios_base::openmode _mode;
  switch (mMode) {
  case Mode::read:
    _mode = std::fstream::in;
    break;
  case Mode::update:
    _mode = std::fstream::in | std::fstream::out | std::fstream::app;
    break;
  case Mode::create:
    _mode = std::fstream::out | std::fstream::trunc;
    break;
  }

  fs.open(file, _mode);

  if (fs.is_open()) {
    if (mMode == Mode::create) {
      char dir[TL_MAX_PATH];
      if ( getFileDriveDir(file.c_str(), dir, TL_MAX_PATH) == 0 )
        if ( createDir(dir) == -1) return Status::open_fail;
    }
    return Status::open_ok;
  } else {
    msgError("File open failed: %s", std::strerror(errno));
    return Status::open_fail;
  }
}

//TableRegister *Csv::read(int id)
//{
//  return getRegister(id).get();
//}

//Csv::Status Csv::readHeader()
//{
//  return Status::SUCCESS;
//}

//Csv::Status Csv::write(std::shared_ptr<TableRegister> _register)
//{
//  addRegister(_register);
//
//  TableRegister *reg = getRegister(size()-1).get();
//  size_t size = getFieldCount();
//  for (size_t i = 0; i < size; i++) {
//    fs << reg->getValue(i);
//    if (i != size -1) fs << ";";
//  }
//  fs << std::endl;
//  return Status::SUCCESS;
//}

Csv::Status Csv::write(const std::vector<std::string> &_register)
{
  size_t size = _register.size();
  for (size_t i = 0; i < size; i++) {
    fs << _register[i];
    if (i != size -1) fs << ";";
  }
  fs << std::endl;
  return Status::success;
}

//Csv::Status Csv::load(std::shared_ptr<TableRegister> _register)
//{
//
//  return Status::SUCCESS;
//}
//
//Csv::Status Csv::save()
//{
//
//  return Status::SUCCESS;
//}


//void compressFile(const char *file, const char *zip)
//{
//  std::string cmd;
//  std::string pto_gen_cmd("/c \"C:\\Desarrollo\\Libs_sources\\lzma1701\\bin\\x64\\7za.exe\" a ");
//  pto_gen_cmd.append(zip).append(" ").append(file);
//
//  CmdProcess process(cmd);
//  CmdProcess::Status status = process.run();
//}

#ifdef HAVE_MINIZIP

Compression::Compression()
  : File()
{

}

Compression::Compression(const char *file, Mode mode)
  : File(file, mode)
{
  open(file, mode);
}

Compression::Compression(const Compression &compression)
  : File(compression)
{

}

Compression::~Compression()
{
  close();
}

void Compression::close()
{
  if (mZipFile == nullptr)
    zipClose(mZipFile, nullptr);
}

Compression::Status Compression::createCopy(const char *fileOut)
{

  return Status::FAILURE;
}

Compression::Status Compression::open(const char *file, Compression::Mode mode)
{
  close();

  mFile = file;
  mMode = mode;

  int open_mode{};
  switch (mMode) {
  case Mode::Read:

    break;
  case Mode::Update:
    open_mode = APPEND_STATUS_ADDINZIP;
    break;
  case Mode::Create:
    open_mode = APPEND_STATUS_CREATE;
    break;
  default:

    break;
  }

  if (mMode == Mode::Read) {
    mUnZipFile = libkml_unzOpen(mFile.c_str());
    return Status::OPEN_OK;
  } else {
    mZipFile = zipOpen(mFile.c_str(), open_mode);
    if (mZipFile == nullptr)
      return Status::OPEN_FAIL;
    else {

      if (libkml_unzGetGlobalInfo(mZipFile, &mGlobalInfo) != UNZ_OK) {
          msgError("could not read file global info");
          libkml_unzClose(mZipFile);
          return Status::OPEN_FAIL;
      }

      return Status::OPEN_OK;
    }
  }

}

Compression::Status Compression::compress(const std::string &file, const std::string &directory)
{
  // Se comprueba si es un directorio

  fs::path _path(file);
  if (is_directory(_path)) {
    for (auto &p : fs::directory_iterator(_path)) {
      compress(p.path().string());
    }
  } else {
    file_name = _path.filename().string();
    std::string _dir = directory;
    std::fstream fz(file, std::ios::binary | std::ios::in);
    if (fz.is_open()) {
      fz.seekg(0, std::ios::end);
      long size = fz.tellg();
      fz.seekg(0, std::ios::beg);

      std::vector<char> buffer(size);
      if (size == 0 || fz.read(&buffer[0], size)) {
        zip_fileinfo zfi = { 0 };

        if (0 == zipOpenNewFileInZip(mZipFile, _path.filename().string().c_str() , &zfi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION)){
          zipWriteInFileInZip(mZipFile, size == 0 ? "" : &buffer[0], size);
          zipCloseFileInZip(mZipFile);
          fz.close();
        }
      }
    }
  }
  return Status::SUCCESS;
}

Compression::Status Compression::decompress()
{
  return Status::SUCCESS;
}

#endif // HAVE_MINIZIP





#ifdef HAVE_GDAL

/* ---------------------------------------------------------------------------------- */

std::unique_ptr<RegisterGdal> RegisterGdal::sRegisterGdal;
std::mutex RegisterGdal::sMutex;

void RegisterGdal::init()
{
  if (sRegisterGdal.get() == nullptr) {
    std::lock_guard<std::mutex> lck(RegisterGdal::sMutex);
    if (sRegisterGdal.get() == nullptr) {
      sRegisterGdal.reset(new RegisterGdal());
      GDALAllRegister();
    }
  }
}

#endif


} // End namespace tl

