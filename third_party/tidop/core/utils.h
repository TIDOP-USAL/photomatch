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

#ifndef TL_CORE_UTILS_H
#define TL_CORE_UTILS_H

#include "config_tl.h"

#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <regex>
#include <thread>
#include <list>
#include <mutex>

//TODO: Incluir filesystem. Se simplificarian bastantes cosas
// filesystem
#if (__cplusplus >= 201703L)
//C++17
//http://en.cppreference.com/w/cpp/filesystem
#include <filesystem>
#else
//Boost
//http://www.boost.org/doc/libs/1_66_0/libs/filesystem/doc/index.htm
#include <boost/filesystem.hpp>
#endif
#include <boost/algorithm/string.hpp>

#ifdef HAVE_OPENCV
#include "opencv2/core/core.hpp"
#endif // HAVE_OPENCV

#ifdef HAVE_MINIZIP
#include "minizip/zip.h"
#include "minizip/unzip.h"
#endif // HAVE_MINIZIP

#include "tidop/core/defs.h"
//#include "core/datamodel.h"

namespace tl
{

/*!
 * \defgroup utilities Utilidades
 *
 * Utilidades de proposito general como manipulación de cadenas, información de la
 * aplicación etc
 * \{
 */

/* ---------------------------------------------------------------------------------- */
/*                           Información de la aplicación                             */
/* ---------------------------------------------------------------------------------- */

/*!
 * \brief Obtiene el path (directorio + nombre + extensión) de la aplicación
 * que esta corriendo
 * \return path de la aplicación
 */
TL_EXPORT const char *getRunfile();


/* ---------------------------------------------------------------------------------- */
/*                    Operaciones con directorios y archivos                          */
/* ---------------------------------------------------------------------------------- */


/*!
 * \brief Comprueba si existe un directorio
 * \param[in] path Ruta del directorio
 * \return true si existe.
 */
TL_EXPORT bool isDirectory(const char *path);
TL_EXPORT bool isDirectory(const std::string &path);

/*!
 * \brief Comprueba si existe el fichero
 * \param[in] file Fichero
 * \return true si existe.
 */
TL_EXPORT bool isFile(const char *file);
TL_EXPORT bool isFile(const std::string &file);

/*!
 * \brief Crea un directorio
 * \param[in] path Ruta del directorio
 * \return Error = -1, creado = 0 y existente = 1
 */
TL_EXPORT int createDir(const char *path);

/*!
 * \brief Crea un directorio
 * \param[in] path Ruta del directorio
 * \param[in] confirm Pide confirmación para borrar el archivo
 * \return Error
 */
TL_EXPORT int deleteDir(const char *path, bool confirm = false);

TL_EXPORT int move(const char *in, const char *out);


/*!
 * \brief Optiene el directorio de un archivo
 * \param[in] path Ruta del archivo
 * \param[out] dir Directorio del archivo
 * \param[in] size Tamaño de dir
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * char dir[TL_MAX_DIR];
 * if (getFileDir("c:\temp\file.txt", dir, TL_MAX_DIR) == 0) {
 * ...
 * }
 * \endcode
 */
TL_EXPORT int getFileDir(const char *path, char *dir, int size);

/*!
 * \brief Optiene la unidad de disco de un archivo
 * \param[in] path Ruta del archivo
 * \param[out] drive Unidad de disco
 * \param[in] size Tamaño de drive
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * char drive[TL_MAX_DRIVE];
 * if (getFileDrive("c:\temp\file.txt", drive, TL_MAX_DRIVE) == 0) {
 * ...
 * }
 * \endcode
 */
TL_EXPORT int getFileDrive(const char *path, char *drive, int size);

#ifdef TL_ENABLE_DEPRECATED_METHODS
/*!
 * \brief Optiene la extensión de un archivo
 * \param[in] path Ruta del archivo
 * \param[out] ext Extensión del archivo
 * \param[in] size Tamaño de ext
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * char ext[TL_MAX_EXT];
 * if (getFileExtension("c:\temp\file.txt", ext, TL_MAX_EXT) == 0) {
 * ...
 * }
 * \endcode
 * \deprecated Usar en su lugar boost::filesystem::extension()
 */
TL_DEPRECATED("boost::filesystem::extension()", "2.0")
TL_EXPORT int getFileExtension(const char *path, char *ext, int size);

/*!
 * \brief Optiene el nombre de un archivo
 * \param[in] path Ruta del archivo
 * \param[out] name Nombre del archivo
 * \param[in] size Tamaño de name
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * char name[TL_MAX_FNAME];
 * if (getFileName("c:\temp\file.txt", name, TL_MAX_FNAME) == 0) {
 * ...
 * }
 * \endcode
 * \deprecated Usar en su lugar boost::filesystem::extension()
 */
TL_DEPRECATED("boost::filesystem::filename()", "2.0")
TL_EXPORT int getFileName(const char *path, char *name, int size);
#endif // TL_ENABLE_DEPRECATED_METHODS

/*!
 * \brief Optiene el directorio de un archivo incluyendo la letra de la unidad
 * \param[in] path Ruta del archivo
 * \param[out] driveDir Unidad de disco y directorio del archivo
 * \param[in] size Tamaño de driveDir
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * char driveDir[TL_MAX_PATH];
 * if (getFileDriveDir("c:\temp\file.txt", driveDir, TL_MAX_PATH) == 0) {
 * ...
 * }
 * \endcode
 */
TL_EXPORT int getFileDriveDir(const char *path, char *driveDir, int size);

/*!
 * \brief Cambia el nombre de un archivo
 * \param[in] path Ruta del archivo
 * \param[in] newName Nuevo nombre
 * \param[out] pathOut Ruta del archivo modificada
 * \param[in] size Tamaño de pathOut
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * char new_name[TL_MAX_PATH];
 * if (changeFileName("c:\temp\old_name.txt", "new_name", new_name, TL_MAX_PATH) == 0) {
 * ...
 * }
 * \endcode
 */
TL_EXPORT int changeFileName(const char *path, const char *newName, char *pathOut, int size);

#ifdef TL_ENABLE_DEPRECATED_METHODS
/*!
 * \brief Cambia la extensión de un archivo
 * \param[in] path Ruta del archivo
 * \param[in] newExt Nueva extensión
 * \param[out] pathOut Ruta del archivo modificada
 * \param[in] size Tamaño de pathOut
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * char logfile[TL_MAX_PATH];
 * if (changeFileExtension(getRunfile(), "log", logfile, TL_MAX_PATH) == 0) {
 * ...
 * }
 * \endcode
 * \deprecated Usar en su lugar boost::filesystem::replace_extension() o std::filesystem::replace_extension()
 */
TL_DEPRECATED("filesystem::replace_extension()", "2.0")
TL_EXPORT int changeFileExtension(const char *path, const char *newExt, char *pathOut, int size);
#endif // TL_ENABLE_DEPRECATED_METHODS

/*!
 * \brief Cambia el nombre y la extensión de un archivo
 * \param[in] path Ruta del archivo
 * \param[in] newNameExt Nuevo nombre incluyendo la extensión
 * \param[out] pathOut Ruta del archivo modificada
 * \param[in] size Tamaño de pathOut
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * char logfile[TL_MAX_FNAME + TL_MAX_EXT];
 * if (changeFileNameAndExtension(getRunfile(), "error.log", logfile, TL_MAX_FNAME + TL_MAX_EXT) == 0) {
 * ...
 * }
 * \endcode
 */
TL_EXPORT int changeFileNameAndExtension(const char *path, const char *newNameExt, char *pathOut, int size);


TL_EXPORT void directoryList(const char *directory, std::list<std::string> *dirList);

#ifdef TL_ENABLE_DEPRECATED_METHODS
TL_DEPRECATED("fileList(const std::string &directory, std::list<std::string> *fileList, const std::regex &wildcard)", "2.0")
TL_EXPORT void fileList(const char *directory, std::list<std::string> *fileList, const char *wildcard = "");
#endif // TL_ENABLE_DEPRECATED_METHODS

/*!
 * \brief Devuelve el listado de archivos de un directorio
 * \param[in] directory Directorio que se quiere listar
 * \param[out] fileList Listado de archivos
 * \param[in] filter Filtro de busqueda
 */
TL_EXPORT void fileList(const std::string &directory, std::list<std::string> *fileList, const std::regex &filter);

/*!
 * \brief Devuelve el listado de archivos de un directorio filtrando por un tipo de archivo
 * \param[in] directory Directorio que se quiere listar
 * \param[out] fileList Listado de archivos
 * \param[in] ext Extensión de archivo (incluyendo el punto)
 *
 * <h4>Ejemplo</h4>
 * \code
 * std::list<std::string> fileList;
 * fileListByExt("D:\\dir", &fileList, ".ext"); 
 * \endcode
 */
TL_EXPORT void fileListByExt(const std::string &directory, std::list<std::string> *fileList, const std::string &ext);



#ifdef TL_ENABLE_DEPRECATED_METHODS

TL_DISABLE_WARNING(TL_WARNING_DEPRECATED)
/*!
 * \brief Clase para gestionar la ruta de ficheros o directorios
 * - Se admiten rutas absolutas y relativas
 * - Como separador admite "/" y "\\".
 *
 */
class TL_EXPORT TL_DEPRECATED("std::filesystem::path (c++17) or boost::filesystem::path", "2.0") Path
{
private:

 /*!
  * \brief mPos
  */
  int mPos;

  /*!
   * \brief mPath
   */
  std::vector<std::string> mPath;

  std::string mFileName;
  std::string mFileExtension;

  /*!
   * \brief Directorio o fichero
   */
  bool bFile;


#if defined WIN32

  /*!
   * \brief Unidad de disco
   */
  std::string mDrive;

#endif

public:

  /*!
   * \brief Constructor por defecto
   */
  Path();

  /*!
   * \brief Constructor
   * \param path Ruta
   */
  Path(const std::string &path);

  /*!
   * \brief Constructor de copia
   * \param path Objeto Path que se copia
   */
  Path(const Path &path);

  /*!
   * \brief Operador de asignación
   * \param[in] path Objeto Path que se copia
   */
  Path &operator = (const Path& path);

  /*!
   * \brief Destructora
   */
  ~Path();

  /*!
   * \brief Parsea una cadena obteniendo los directorios de la ruta, unidad de disco y nombre si es un fichero
   * \param path Ruta
   * 
   */
  void parse(const std::string &path);

#if defined WIN32

  /*!
   * \brief getDrive
   * \return
   */
  const char *getDrive();

#endif

  /*!
   * \brief Sube una posición en el path
   */
  void up();

  /*!
   * \brief Baja una posición
   */
  void down();
  
  /*!
   * \brief currentPath
   * \return
   */
  std::vector<std::string> currentPath();

  /*!
   * \brief convierte el path a una cadena
   * \return
   */
  std::string toString();

  //TODO: Un path no solo apunta a un directorio con lo cual habría que añadir utilidades para imagenes
  bool isDirectory();
  bool isFile();
  
  void createDir();
  void deleteDir();

  /*!
   * \brief
   */
  std::list<std::string> files(const std::string &wildcard);  // Listar ficheros o directorios. Posibilidad de filtrar con comodines (tipo de archivo, solo directorios, etc)

  std::list<std::string> dirs();

  Path &append(const std::string &dir);
};
TL_ENABLE_WARNING(TL_WARNING_DEPRECATED)

#endif // TL_ENABLE_DEPRECATED_METHODS


/* ---------------------------------------------------------------------------------- */
/*                             Operaciones con cadenas                                */
/* ---------------------------------------------------------------------------------- */

/*! \defgroup stringOper Operaciones con cadenas
 *  
 * \{
 */

/*!
 * \brief Separa una cadena en un array de enteros
 * \param[in] cad Cadena de texto que contiene una lista de numeros
 * \param[out] vOut Vector con los números extraidos
 * \param[in] chs Caracter separador de la cadena. Si se omite toma por defecto ","
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * std::string aux = "1102,3654";
 * std::vector<int> coord;
 * if ( splitToNumbers(aux, coord) == 0 ){
 *   ...
 * }
 * \endcode
 */
TL_EXPORT int splitToNumbers(const std::string &cad, std::vector<int> &vOut, const char *chs = ",");

/*!
 * \brief Separa una cadena en un array de dobles
 * \param[in] cad Cadena de texto que contiene una lista de numeros
 * \param[out] vOut Vector con los números extraidos
 * \param[in] chs Caracter separador de la cadena. Si se omite toma por defecto ","
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * std::string aux = "1102.52,3654.95";
 * std::vector<double> coord;
 * if ( splitToNumbers(aux, coord) == 0 ){
 *   ...
 * }
 * \endcode
 */
TL_EXPORT int splitToNumbers(const std::string &cad, std::vector<double> &vOut, const  char *chs = ",");

/*!
 * \brief Reemplaza una cadena por otra en un texto.
 * \param[in] str Cadena original
 * \param[in] str_old Cadena a remplazar
 * \param[out] str_new Nueva cadena
 *
 * <h4>Ejemplo</h4>
 * \code
 * std::string str = "Hola mundo";
 * replaceString(str, " ", "_");
 * \endcode
 */
TL_EXPORT void replaceString(std::string *str, const std::string &str_old, const std::string &str_new);


/*!
 * \brief Separa una cadena
 *
 * \param[in] in Cadena de entrada
 * \param[out] out vector con las cadenas resultantes
 * \param[in] chs cadena de separación. Si se omite toma por defecto ","
 * \return (1) error
 *
 * <h4>Ejemplo</h4>
 * \code
 * char *in = "cadena1,cadena2";
 * std::vector<std::string> out;
 *
 * if ( split(in, out, ",") == 0 ){
 * ...
 * }
 * \endcode
 */
TL_EXPORT int split(const std::string &in, std::vector<std::string> &out, const char *chs = ",");

/*! \} */ // end of stringOper

#ifdef TL_ENABLE_DEPRECATED_METHODS
/*!
 * \brief Convierte un número a una cadena de texto
 * \param[in] number Numero
 * \return Cadena de texto
 */
template <typename T> inline
TL_DEPRECATED("std::to_string()", "2.0")
std::string numberToString(T number)
{
  std::ostringstream ss;
  ss << number;
  return ss.str();
}
#endif // TL_ENABLE_DEPRECATED_METHODS


/*!
 * \brief Convierte una cadena de texto a un número
 * \param[in] text Texto
 * \return número
 */
template <typename T> inline 
T stringToNumber(const std::string &text)
{
  T number;
  return (std::istringstream(text) >> number) ? number : 0;
}

enum class Base : int8_t
{
  octal       =  8,
  decimal     = 10,
  hexadecimal = 16
#ifdef TL_ENABLE_DEPRECATED_METHODS
  ,
  OCTAL       =  8,
  DECIMAL     = 10,
  HEXADECIMAL = 16
#endif
};

/*!
 * \brief Convierte una cadena a un número entero.
 *
 * La cadena puede tener un número en base octal, decimal o hexadecimal
 * \param text Cadena de texto
 * \param base Base en la cual esta el número
 * \return Número
 * \see Base
 */
TL_EXPORT int stringToInteger(const std::string &text, Base base = Base::decimal);

/* ---------------------------------------------------------------------------------- */
/*                              Operaciones con vectores                              */
/* ---------------------------------------------------------------------------------- */

#ifdef HAVE_OPENCV

/*!
 * \brief Convierte una matriz de OpenCV en un vector
 * \param[in] m Matriz de entrada
 * \param[out] av Vector de salida
 */
template<typename T> inline 
void cvMatToVector(const cv::Mat &m, std::vector<T> *av)
{
  av->resize(m.rows*m.cols);
  if (m.isContinuous()) {
    av->assign((T*)m.datastart, (T*)m.dataend);
  } else {
    for (int i = 0; i < m.rows; ++i) {
      av->insert(av->end(), (T*)m.ptr<uchar>(i), (T*)m.ptr<uchar>(i)+m.cols);
    }
  }
}

#endif // HAVE_OPENCV

/*!
 * \brief Ordena un vector de menor a mayor
 * \param[in] v Vector
 */
template<typename T> inline 
void sortVector(std::vector<T> *v)
{
  std::sort(v->begin(), v->end());
}

/*!
 * \brief Ordena un vector de mayor a menor
 * \param[in] v Vector
 */
template<typename T> inline 
void sortVectorInv(std::vector<T> *v)
{
  std::sort(v->rbegin(),v->rend());
}

/*!
 * \brief Determinar el número de elementos iguales a un número.
 * Sobrecarga del operador == para determinar el número de elementos de un
 * vector que son iguales al valor pasado como parámetro.
 * \param[in] v Vector
 * \param[in] t Valor
 * \return Número de elementos que cumplen la condición
 */
template<typename T> inline 
int operator==(const std::vector<T> &v, const T t)
{
  sortVector(v);
  std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator> bounds;
  bounds = std::equal_range(v.begin(), v.end(), t);
  int ini = bounds.first - v.begin();
  int end = bounds.second - v.begin();
  return ( end - ini );
}

/*!
 * \brief Determina el número de elementos distintos a un número.
 * Sobrecarga del operador != para determinar el número de elementos de un
 * vector que son distintos al valor pasado como parámetro.
 * \param[in] v Vector
 * \param[in] t Valor
 * \return Número de elementos que cumplen la condición
 */
template<typename T> inline 
int operator!=(const std::vector<T> &v, const T t)
{
  sortVector(v);
  std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator> bounds;
  bounds = std::equal_range(v.begin(), v.end(), t);
  int r1 = bounds.first - v.begin();
  int r2 = v.end() - bounds.second;
  return (r1 + r2 );
}

/*!
 * \brief operator >=
 * \param[in] v
 * \param[in] t
 * \return
 */
template<typename T> inline 
int operator>=(const std::vector<T> &v, const T t)
{
  sortVector(v);
  typename std::vector<T>::iterator upOrEq;
  upOrEq = std::lower_bound(v.begin(), v.end(), t);
  return (v.end() - upOrEq);
}

template<typename T> inline 
int operator<=(const std::vector<T> &v, const T t)
{
  sortVector(v);
  typename std::vector<T>::iterator lowOrEq;
  lowOrEq = std::upper_bound(v.begin(), v.end(), t);
  return (lowOrEq - v.begin());
}

template<typename T> inline 
int operator> (const std::vector<T> &v, const T t)
{
  sortVector(v);
  typename std::vector<T>::iterator up;
  up = std::upper_bound(v.begin(), v.end(), t);
  return (v.end() - up);
}

template<typename T> inline 
int operator< (const std::vector<T> &v, const T t)
{
  sortVector(v);
  typename std::vector<T>::iterator low;
  low = std::lower_bound(v.begin(), v.end(), t);
  return (low - v.begin());
}

/* ---------------------------------------------------------------------------------- */



/*!
 * \brief Ordena los indices de un vector de menor a mayor
 * Para un vector [10,20,15,5] devuelve [3,0,2,1]. El elemento mas
 * pequeño esta en la posición 3, el segundo en la posición 0, ...
 * \param[in] v Vector
 * \return Vector con los indices ordenados
 */
template <typename T> inline 
std::vector<int> sortIdx(const std::vector<T> &v)
{
  std::vector<int> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  sort(idx.begin(), idx.end(), [&v](int i1, int i2) {return v[i1] < v[i2]; });

  return idx;
}

#ifdef HAVE_OPENCV


/* ---------------------------------------------------------------------------------- */
/*                Utilidades de carga y guardado para OpenCV                          */
/* ---------------------------------------------------------------------------------- */

TL_EXPORT void loadCameraParams(const std::string &file, cv::Size &imageSize, cv::Mat &cameraMatrix, cv::Mat &distCoeffs);

TL_EXPORT int loadBinMat(const char *file, cv::Mat *data);

TL_EXPORT int saveBinMat(const char *file, cv::Mat &data);

#endif // HAVE_OPENCV


/* ---------------------------------------------------------------------------------- */
/*                         Concurrencia, hilos y multiproceso                         */
/* ---------------------------------------------------------------------------------- */

/*!
 * \brief número optimo de hilos
 */
TL_EXPORT uint32_t getOptimalNumberOfThreads();

/*!
 * \brief Ejecuta una función en paralelo
 * \param[in] ini
 * \param[in] end
 * \param[in] f Función o lambda
 */
TL_EXPORT void parallel_for(size_t ini, size_t end, std::function<void(int)> f);

/*!
 * \brief Ejecuta una función en paralelo
 * Método sobrecargado para trabajar con contenedores
 * \param[in] it_begin
 * \param[in] it_end
 * \param[out] it_out_begin 
 * \param[in] f Función o lambda
 */
template<typename itIn, typename itOut> inline
void parallel_for(itIn it_begin, itIn it_end, itOut *it_out_begin, std::function<void(itIn, itIn, itOut *)> f)
{
//#ifdef TL_MSVS_CONCURRENCY
  //Concurrency::cancellation_token_source cts;
  //Concurrency::run_with_cancellation_token([ini, end, f]() {
  //  Concurrency::parallel_for(ini, end, f);
  //},cts.get_token());
  //Concurrency::parallel_for(ini, end, f);
//#else

  auto f_aux = [&](itIn ini, itIn end, itOut *out) {
    while (ini != end) {
      f(ini, end, out);
    }
  };

  int num_threads = getOptimalNumberOfThreads();
  std::vector<std::thread> threads(num_threads);
  auto size = std::distance(it_begin, it_end);
  int _size = size / num_threads;
  for (int i = 0; i < num_threads; i++) {
    itIn _ini = i * _size + it_begin;
    itIn _end = _ini + _size;
    itOut _out = i * _size + it_out_begin;
    if (i == num_threads -1) _end = it_end;
    threads[i] = std::thread(f_aux, _ini, it_out_begin, _end);
  }

  for (auto &_thread : threads) _thread.join();
//#endif
}


/* ---------------------------------------------------------------------------------- */
/*                                   Tiempo                                           */
/* ---------------------------------------------------------------------------------- */

/*!
 * \brief Genera una cadena con el tiempo actual en el formato especificado
 */
TL_EXPORT std::string formatTimeToString(const std::string &templ = "%d/%b/%Y %H:%M:%S");

/*!
 * \brief tiempo actual
 *
 * <h4>Ejemplo</h4>
 * \code
 * uint64_t time_ini = tickCount();
 * ...
 * double time = (tickCount() - time_ini) / 1000.;
 * msgInfo("Time %f", time);
 * \endcode
 */
TL_EXPORT uint64_t tickCount();

#ifdef TL_ENABLE_DEPRECATED_METHODS
/*!
 * \brief tiempo actual
 *
 * <h4>Ejemplo</h4>
 * \code
 * uint64_t time_ini = getTickCount();
 * ...
 * double time = (getTickCount() - time_ini) / 1000.;
 * msgInfo("Time %f", time);
 * \endcode
 * \deprecated Se cambia el nombre del método a tickCount()
 */
TL_DEPRECATED("tickCount()", "2.0") 
TL_EXPORT uint64_t getTickCount();
#endif // TL_ENABLE_DEPRECATED_METHODS

/*!
 * \brief Clase para medir tiempos.
 *
 * Su uso esta pensado para medir tiempos en depuración
 */
class TL_EXPORT Chrono
{
public:

  /*!
   * \brief Posibles estados del cronómetro
   */
  enum class Status {
    start,      /*!< Inicio */
    running,    /*!< Corriendo */
    pause,      /*!< Pausado */
    stopped,    /*!< Detenido */
    finalized   /*!< Finalizado */
#ifdef TL_ENABLE_DEPRECATED_METHODS
    ,
    START     = start,      /*!< Inicio */
    RUNNING   = running,    /*!< Corriendo */
    PAUSE     = pause,      /*!< Pausado */
    STOPPED   = stopped,    /*!< Detenido */
    FINALIZED = finalized   /*!< Finalizado */
#endif
  };

private:
  
  /*!
   * Tiempo de inicio en milisegundos
   */
  uint64_t mTimeIni;

  /*!
   * Tiempo acumulado en milisegundos
   */
  uint64_t mAccumulated;

  /*!
   * \brief Estado del cronómetro
   */
  Status mStatus;

  /*!
   * \brief Mensaje de información opcional
   */
  std::string mMessage;

  /*!
   * \brief Escribe mensajes en log y consola
   */
  bool bWriteMsg;

public:

  Chrono();

  /*!
   * \brief Constructor
   */
  Chrono(const char *msg, bool writeMsg = false);

  /*!
   * \brief Destructora
   * En la destructora se llama al método stop si este no ha sido llamado
   */
  ~Chrono();

  /*!
   * \brief Pausa el cronometro
   */
  uint64_t pause();

  /*!
   * \brief Reinicio del cronometro
   */
  void reset();

  /*!
   * \brief Continua corriendo el cronometro cuando estaba pausado
   */
  void resume();

  /*!
   * \brief Arranca el cronometro
   */
  uint64_t run();

  /*!
   * \brief Detiene el cronometro
   */
  uint64_t stop();

  void setMessage(const char *msg);

private:

};


/* ---------------------------------------------------------------------------------- */
/*                               Plantillas html y xml                                */
/* ---------------------------------------------------------------------------------- */

/*!
 * \brief Clase virtual para la sustitución de etiquetas en textos, ficheros html o xml.
 */
class TL_EXPORT VrtTemplate
{

protected:

  /*!
   * \brief Texto con las etiquetas de reemplazo
   */
  std::string mText;

public:

  /*!
   * \brief Constructora por defecto
   */
  VrtTemplate();

  /*!
   * \brief Constructora
   */
  VrtTemplate(const char *text);


  /*!
   * \brief Destructora
   */
  virtual ~VrtTemplate();

  /*!
   * \brief Lee un fichero plantilla
   * \param[in] file Fichero plantilla
   * \return
   */
  virtual int read(const char *file);

  /*!
   * \brief Establece la plantilla
   * \param[in] templ Texto con la plantilla
   * \return
   */
  void setTemplate(const char *templ);

  /*!
   * \brief Remplaza todas las ocurrencias de las etiquetas
   * de plantilla
   * \param[out] output Texto con las etiquetas sustituidas
   * \return
   */
  virtual int replace(std::string *output) const;

  /*!
   * \brief Reemplaza una etiqueta por su valor
   * \param tag Etiqueta que se sustituye
   * \param replaceText Texto que sustituye a la etiqueta
   */
  virtual void replaceTag(const std::string &tag, std::string *replaceText) const = 0;

};


class TL_EXPORT HtmlTemplate : public VrtTemplate
{

protected:

  std::map<std::string, std::string> mTagValues;

public:

  /*!
   * \brief Constructora por defecto
   */
  HtmlTemplate();

  /*!
   * \brief Constructora
   */
  HtmlTemplate(const char *text, const std::map<std::string, std::string> &tag_values);

  /*!
   * \brief Destructora
   */
  ~HtmlTemplate();

  /*!
   * \brief Reemplaza una etiqueta por su valor
   * \param tag Etiqueta que se sustituye
   * \param replaceText Texto que sustituye a la etiqueta
   */
  void replaceTag(const std::string &tag, std::string *replaceText) const override;
};


/* ---------------------------------------------------------------------------------- */

/*!
 * \brief Opciones del formato
 */
class FileOptions
{
public:

  FileOptions();
  virtual ~FileOptions();

  virtual const char *getOptions() = 0;
};

/*!
 * \brief Clase base para manejo de ficheros.
 *
 * Esta clase define la interfaz básica para lectura, creación y escritura de ficheros
 */
class TL_EXPORT File
{
public:

  //TODO: Revisar los modos. Igual es mejor utilizar flags
  /*!
   * \brief Modos de apertura de ficheros
   */
  enum class Mode : int8_t
  {
    read,      /*!< Lectura */
    update,    /*!< Lectura y escritura. */
    create     /*!< Creación */
#ifdef TL_ENABLE_DEPRECATED_METHODS
    ,
    Read   = read,     /*!< Lectura */
    Update = update,   /*!< Lectura y escritura. */
    Create = create    /*!< Creación */
 #endif
  };

  /*!
   * \brief Estado
   */
  enum class Status : int8_t
  {
    open_ok,
    open_fail,
    save_ok,
    success,
    failure
#ifdef TL_ENABLE_DEPRECATED_METHODS
    ,
    OPEN_OK   = open_ok,
    OPEN_FAIL = open_fail,
    SAVE_OK   = save_ok,
    SUCCESS   = success,
    FAILURE   = failure
#endif
  };

protected:
  
  /*!
   * \brief Fichero
   */
  std::string mFile;

  Mode mMode;

public:

  /*!
   * \brief Constructora
   */
  File() : mFile("") {}

  //File(const char *file, Mode mode = Mode::Update) : mFile(file), mMode(mode) { }
  File(const std::string &file, Mode mode = Mode::update) : mFile(file), mMode(mode) { }

  /*!
   * \brief Destructora
   */
  virtual ~File(){}

  /*!
   * \brief Cierra el fichero
   */
  virtual void close() = 0;

  /*!
   * \brief Abre un fichero especificando las opciones del formato
   * \param[in] file Fichero
   * \param[in] mode Modo de apertura
   * \param[in] options Opciones del formato
   * \return
   * \see Mode
   */
  //virtual Status open(const char *file, Mode mode = Mode::Update, FileOptions *options = nullptr) = 0;
  virtual Status open(const std::string &file, Mode mode = Mode::update, FileOptions *options = nullptr) = 0;

  /*!
   * \brief Guarda una copia con otro nonbre
   */
  //virtual Status createCopy(const char *fileOut) = 0;
  virtual Status createCopy(const std::string &fileOut) = 0;
};

//Es un fichero y es un modelo de datos con lo cual tendria que heredar de forma publica tambien de 
// DataTable
class TL_EXPORT Csv : public File/*, private DataTable*/
{
private:

  std::fstream fs;

public:

  /*!
   * \brief Constructora
   */
  Csv();

  Csv(const char *file, Mode mode = Mode::update);

  Csv(const Csv &csv);

  /*!
   * \brief Destructora
   */
  ~Csv() override;

  /*!
   * \brief Cierra el fichero csv
   */
  void close() override;

  /*!
   * \brief Crea el fichero
   */
  Status create(const std::string &header);
  
  /*!
   * \brief Crea el fichero
   */  
  //Status create(const DataTable &dataTable);

  /*!
   * \brief Guarda una copia con otro nonbre
   */
  Status createCopy(const std::string &fileOut) override;

  /*!
   * \brief Abre un fichero especificando las opciones del formato
   * \param[in] file Fichero
   * \param[in] mode Modo de apertura
   * \param[in] options Opciones del formato
   * \return
   * \see Mode
   */
  Status open(const std::string &file, Mode mode = Mode::update, FileOptions *options = nullptr) override;

  /*!
   * \brief Lee un registro de la tabla
   */
  //TableRegister *read(int id);

  /*!
   * \brief Escribe una linea en el fichero
   * \return
   */
  //Status write(std::shared_ptr<TableRegister> _register);
  Status write(const std::vector<std::string> &_register);

  /*!
   * \brief carga todo el fichero a memoria
   */
  //Status load();

  /*!
   * \brief Salva el fichero cuando se esta trabajando en memoria
   */
  Status save();

private:

  /*!
   * \brief Lee la cabecera
   */
  //Status readHeader();

};


//TL_EXPORT void compressFile(const char *file, const char *zip);

#ifdef HAVE_MINIZIP

// Clase para compresión de archivos
class Compression : public File
{
private:

  zipFile mZipFile; 
  unzFile mUnZipFile;
  unz_global_info mGlobalInfo;

public:

  Compression();
  Compression(const char *file, Mode mode = Mode::Update);
  Compression(const Compression &compression);
  ~Compression();

  /*!
   * \brief Cierra el fichero
   */
  void close() override;

  /*!
   * \brief Guarda una copia con otro nonbre
   */
  Status createCopy(const char *fileOut) override;

  /*!
   * \brief Abre un fichero
   * \param[in] file Nombre del fichero
   * \param[in] mode Modo de apertura
   * \return
   * \see Mode
   */
  Status open(const char *file, Mode mode = Mode::Read) override;

  Status compress(const std::string &file, const std::string &directory = {});
  Status decompress();

private:

};

#endif // HAVE_MINIZIP


/*! \} */ // end of utilities


#ifdef HAVE_GDAL

/*!
 * \brief Clase singleton para registrar los drivers de GDAL
 *
 */
class TL_EXPORT RegisterGdal
{
private:

  static std::unique_ptr<RegisterGdal> sRegisterGdal;
  static std::mutex sMutex;

  /*!
   * \brief Constructor privado
   */
  RegisterGdal() {}

public:

  ~RegisterGdal() {}

  // Se impide la copia y asignación
  RegisterGdal(RegisterGdal const&) = delete;
  void operator=(RegisterGdal const&) = delete;

  /*!
   * \brief Método para iniciar GDAL una unica vez
   */
  static void init();

};

#endif // HAVE_GDAL


} // End namespace tl

#endif // TL_CORE_UTILS_H
