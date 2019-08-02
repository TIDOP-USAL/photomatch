#ifndef FME_PROJECT_H
#define FME_PROJECT_H

#include "fme/fme_global.h"

#include <memory>
#include <vector>
#include <mutex>

#include <QString>

#include "fme/core/image.h"
#include "fme/core/session.h"
#include "fme/core/preprocess.h"

class QXmlStreamWriter;
class QXmlStreamReader;

namespace fme
{

/*!
 * \brief Interfaz Project
 */
class FME_EXPORT IProject
{

public:

  typedef std::vector<std::shared_ptr<Image>>::iterator image_iterator;
  typedef std::vector<std::shared_ptr<Image>>::const_iterator image_const_iterator;
  typedef std::vector<std::shared_ptr<Session>>::iterator session_iterator;
  typedef std::vector<std::shared_ptr<Session>>::const_iterator session_const_iterator;

public:

  IProject() {}
  virtual ~IProject() = default;

  /*!
   * \brief Devuelve el nombre del proyecto
   * \return Nombre del proyecto
   */
  virtual QString name() const = 0;

  /*!
   * \brief Establece el nombre del proyecto
   * \param[in] name Nombre del proyecto
   */
  virtual void setName(const QString &name) = 0;

  /*!
   * \brief Devuelve la descripción del proyecto
   * \return Descripción del proyecto
   */
  virtual QString description() const = 0;

  /*!
   * \brief Establece la descripción del proyecto
   * \param[in] description Descripción del proyecto
   */
  virtual void setDescription(const QString &description) = 0;

  /*!
   * \brief Devuelve el directorio del proyecto
   * \return Directorio del proyecto
   */
  virtual QString projectFolder() const = 0;

  /*!
   * \brief Establece el directorio del proyecto
   * \param[in] path Directorio del proyecto
   */
  virtual void setProjectFolder(const QString &dir) = 0;

  /*!
   * \brief Versión del fichero de proyecto
   * La versión del fichero de proyecto se utiliza para actualizar proyectos antiguos
   * \return Versión del fichero de proyecto
   */
  virtual QString version() const = 0;

  /*!
   * \brief Añade una imagen al proyecto
   * \param[in] img Imagen
   */
  virtual void addImage(const std::shared_ptr<Image> &img) = 0;

  /*!
   * \brief Elimina una imagen del proyecto
   * \param[in] img Ruta de la imagen que se quiere eliminar
   */
  virtual void deleteImage(const QString &img) = 0;

  /*!
   * \brief Elimina una imagen del proyecto
   * \param[in] imgId Identificador de la imagen que se quiere eliminar
   */
  virtual void deleteImage(size_t imgId) = 0;

  /*!
   * \brief Busca una imagen en el proyecto
   * \param[in] path Ruta de la imagen a buscar
   * \return Objeto Image correspondiente o puntero nulo si no se encuentra
   */
  virtual std::shared_ptr<Image> findImage(const QString &path) = 0;
  virtual const std::shared_ptr<Image> findImage(const QString &path) const = 0;

  /*!
   * \brief Busca una imagen en el proyecto
   * \param[in] path Ruta de la imagen a buscar
   * \return Objeto Identificador de la imagen o std::numeric_limits<size_t>().max() si no se encuentra.
   */
  //virtual size_t findImageId(const QString &path) = 0;
  virtual size_t findImageId(const QString &path) const = 0;


  /// Iteradores para el acceso a las imágenes y las cámaras

  /*!
   * \brief Devuelve un iterador al inicio del listado de imágenes
   * \return Iterador al primer elemento del listado de imágenes
   */
  virtual image_iterator imageBegin() = 0;

  /*!
   * \brief Devuelve un iterador constante al inicio del listado de imágenes
   * \return Iterador al primer elemento del listado de imágenes
   */
  virtual image_const_iterator imageBegin() const = 0;

  /*!
   * \brief Devuelve un iterador al siguiente elemento después después de la última imagen
   * Este elemento actúa como un marcador de posición, intentar acceder a él resulta en un comportamiento no definido
   * \return Iterador al siguiente elemento después de la última imagen
   */
  virtual image_iterator imageEnd() = 0;

  /*!
   * \brief Devuelve un iterador constante al siguiente elemento después de la última imagen
   * Este elemento actúa como un marcador de posición, intentar acceder a él resulta en un comportamiento no definido
   * \return Iterador constante al siguiente elemento después de la última imagen
   */
  virtual image_const_iterator imageEnd() const = 0;

  /*!
   * \brief Número de imagenes cargadas en el proyecto
   * \return
   */
  virtual size_t imagesCount() const = 0;

  /*!
   * \brief Añade una sesión
   * \param[in] name Nombre de la sesión
   * \param[in] description Descripción de la sesión
   */
  virtual void addSession(const QString &name, const QString &description) = 0;

  /*!
   * \brief Añade una sesión
   * \param[in] session Sesión
   */
  virtual void addSession(const std::shared_ptr<Session> &session) = 0;

  /*!
   * \brief Borra una sesión
   * \param[in] nameSession Nombre de la sesión
   */
  virtual void deleteSession(const QString &nameSession) = 0;

  /*!
   * \brief Borra una sesión
   * \param[in] sessionId Identificador de la sesión
   */
  virtual void deleteSession(size_t sessionId) = 0;

  /*!
   * \brief Busca una sesión en el proyecto
   * \param[in] sessionName Nombre de la sesión
   * \return
   */
  virtual std::shared_ptr<Session> findSession(const QString &sessionName) = 0;

  /*!
   * \brief Busca una sesión en el proyecto
   * \param[in] sessionName Nombre de la sesión
   * \return
   */
  virtual const std::shared_ptr<Session> findSession(const QString &sessionName) const = 0;

  /*!
   * \brief Busca el identificador de una sesión en el proyecto
   * \param[in] sessionName Nombre de la sesión
   * \return
   */
  virtual size_t findSessionId(const QString &sessionName) = 0;

  /*!
   * \brief Busca el identificador de una sesión en el proyecto
   * \param[in] sessionName Nombre de la sesión
   * \return
   */
  virtual size_t findSessionId(const QString &sessionName) const = 0;

  /*!
   * \brief Devuelve un iterador al inicio del listado de sessiones
   * \return Iterador al primer elemento del listado de sessiones
   */
  virtual session_iterator sessionBegin() = 0;

  /*!
   * \brief Devuelve un iterador constante al inicio del listado de sessiones
   * \return Iterador al primer elemento del listado de sessiones
   */
  virtual session_const_iterator sessionBegin() const = 0;

  /*!
   * \brief Devuelve un iterador al siguiente elemento después después de la última sesión
   * Este elemento actúa como un marcador de posición, intentar acceder a él
   * resulta en un comportamiento no definido
   * \return Iterador al siguiente elemento después de la última sesión
   */
  virtual session_iterator sessionEnd() = 0;

  /*!
   * \brief Devuelve un iterador constante al siguiente elemento después de la última sesión
   * Este elemento actúa como un marcador de posición, intentar acceder a él
   * resulta en un comportamiento no definido
   * \return Iterador constante al siguiente elemento después de la última sesión
   */
  virtual session_const_iterator sessionEnd() const = 0;

  /*!
   * \brief Número de sesiones del proyecto
   * \return
   */
  virtual size_t sessionCount() const = 0;

  virtual std::shared_ptr<Session> currentSession() = 0;
  virtual const std::shared_ptr<Session> currentSession() const = 0;
  virtual void setCurrentSession(const QString &sessionName) = 0;

  /*!
   * \brief Limpia el proyecto
   */
  virtual void clear() = 0;

};



/*!
 * \brief Interfaz para las operaciones de lectura y escritura del proyecto
 */
class FME_EXPORT IProjectRW
{

public:

  IProjectRW() {}
  virtual ~IProjectRW() = default;

  /*!
   * \brief read
   * \param[in] file Ruta del fichero de proyecto
   * \param[out] prj
   * \return
   */
  virtual bool read(const QString &file, IProject &prj) = 0;

  /*!
   * \brief write
   * \param prj
   * \param file
   * \return
   */
  virtual bool write(const QString &file, const IProject &prj) const = 0;

  /*!
   * \brief checkOldVersion
   * \param file
   * \return
   */
  virtual bool checkOldVersion(const QString &file) const = 0;

  /*!
   * \brief Crea una copia de un proyecto antiguo con el mismo nombre y un sufijo con la versión
   * \param[in] file
   */
  virtual void oldVersionBak(const QString &file) const = 0;

};


class FME_EXPORT Project
  : public IProject
{

public:

  Project();
  ~Project() override = default;

// IProject interface

public:

  QString name() const override;
  void setName(const QString &name) override;
  QString description() const override;
  void setDescription(const QString &description) override;
  QString projectFolder() const override;
  void setProjectFolder(const QString &dir) override;
  QString version() const override;
  void addImage(const std::shared_ptr<Image> &img) override;
  void deleteImage(const QString &img) override;
  void deleteImage(size_t imgId) override;
  std::shared_ptr<Image> findImage(const QString &path) override;
  const std::shared_ptr<Image> findImage(const QString &path) const override;
  //size_t findImageId(const QString &path) override;
  size_t findImageId(const QString &path) const override;
  image_iterator imageBegin() override;
  image_const_iterator imageBegin() const override;
  image_iterator imageEnd() override;
  image_const_iterator imageEnd() const override;
  size_t imagesCount() const override;
  void addSession(const QString &name, const QString &description) override;
  void addSession(const std::shared_ptr<Session> &session) override;
  void deleteSession(const QString &sessionName) override;
  void deleteSession(size_t sessionId) override;
  std::shared_ptr<Session> findSession(const QString &sessionName) override;
  const std::shared_ptr<Session> findSession(const QString &sessionName) const override;
  size_t findSessionId(const QString &sessionName) override;
  size_t findSessionId(const QString &sessionName) const override;
  session_iterator sessionBegin() override;
  session_const_iterator sessionBegin() const override;
  session_iterator sessionEnd() override;
  session_const_iterator sessionEnd() const override;
  size_t sessionCount() const override;
  std::shared_ptr<Session> currentSession() override;
  const std::shared_ptr<Session> currentSession() const override;
  void setCurrentSession(const QString &sessionName) override;
  void clear() override;


protected:

  QString mName;
  QString mDescription;
  QString mPath;
  QString mProjectFolder;
  QString mVersion;
  std::vector<std::shared_ptr<Image>> mImages;
  std::vector<std::shared_ptr<Session>> mSessions;
  int mCurrentSession;
};


class FME_EXPORT ProjectRW
  : public IProjectRW
{

public:

  ProjectRW();

// IProjectIO interface

public:

  bool read(const QString &file, IProject &prj) override;
  bool write(const QString &file, const IProject &prj) const override;
  bool checkOldVersion(const QString &file) const override;
  void oldVersionBak(const QString &file) const override;

private:

  void readCLAHE(QXmlStreamReader *stream, IClahe *clahe) const;
  void readCMBFHE(QXmlStreamReader *stream, ICmbfhe *cmbfhe) const;
  void readDHE(QXmlStreamReader *stream, IDhe *dhe) const;
  void readFAHE(QXmlStreamReader *stream, IFahe *fahe) const;
  void readHMCLAHE(QXmlStreamReader *stream, IHmclahe *hmclahe) const;
  void readLCEBSESCS(QXmlStreamReader *stream, ILceBsescs *lceBsescs) const;
  void readMSRCP(QXmlStreamReader *stream, IMsrcp *msrcp) const;
  void readNOSHP(QXmlStreamReader *stream, INoshp *noshp) const;
  void readPOHE(QXmlStreamReader *stream, IPohe *pohe) const;
  void readRSWHE(QXmlStreamReader *stream, IRswhe *rswhe) const;
  void readWALLIS(QXmlStreamReader *stream, IWallis *wallis) const;

  void readAGAST(QXmlStreamReader *stream, IAgast *agast) const;
  void readAKAZE(QXmlStreamReader *stream, IAkaze *akaze) const;
  void readBRIEF(QXmlStreamReader *stream, IBrief *brief) const;
  void readBRISK(QXmlStreamReader *stream, IBrisk *brisk) const;
  void readDAISY(QXmlStreamReader *stream, IDaisy *daisy) const;
  void readFAST(QXmlStreamReader *stream, IFast *fast) const;
  void readFREAK(QXmlStreamReader *stream, IFreak *freak) const;
  void readGFTT(QXmlStreamReader *stream, IGftt *gftt) const;
  void readHOG(QXmlStreamReader *stream, IHog *hog) const;
  void readKAZE(QXmlStreamReader *stream, IKaze *kaze) const;
  void readLATCH(QXmlStreamReader *stream, ILatch *latch) const;
  void readLUCID(QXmlStreamReader *stream, ILucid *lucid) const;
  void readMSD(QXmlStreamReader *stream, IMsd *msd) const;
  void readMSER(QXmlStreamReader *stream, IMser *mser) const;
  void readORB(QXmlStreamReader *stream, IOrb *orb) const;
  void readSIFT(QXmlStreamReader *stream, ISift *sift) const;
  void readSTAR(QXmlStreamReader *stream, IStar *star) const;
  void readSURF(QXmlStreamReader *stream, ISurf *surf) const;

  void writeCLAHE(QXmlStreamWriter *stream, IClahe *clahe) const;
  void writeCMBFHE(QXmlStreamWriter *stream, ICmbfhe *cmbfhe) const;
  void writeDHE(QXmlStreamWriter *stream, IDhe *dhe) const;
  void writeFAHE(QXmlStreamWriter *stream, IFahe *fahe) const;
  void writeHMCLAHE(QXmlStreamWriter *stream, IHmclahe *hmclahe) const;
  void writeLCEBSESCS(QXmlStreamWriter *stream, ILceBsescs *lceBsescs) const;
  void writeMSRCP(QXmlStreamWriter *stream, IMsrcp *msrcp) const;
  void writeNOSHP(QXmlStreamWriter *stream, INoshp *noshp) const;
  void writePOHE(QXmlStreamWriter *stream, IPohe *pohe) const;
  void writeRSWHE(QXmlStreamWriter *stream, IRswhe *rswhe) const;
  void writeWALLIS(QXmlStreamWriter *stream, IWallis *wallis) const;

  void writeAGAST(QXmlStreamWriter *stream, IAgast *agast) const;
  void writeAKAZE(QXmlStreamWriter *stream, IAkaze *akaze) const;
  void writeBRIEF(QXmlStreamWriter *stream, IBrief *brief) const;
  void writeBRISK(QXmlStreamWriter *stream, IBrisk *brisk) const;
  void writeDAISY(QXmlStreamWriter *stream, IDaisy *daisy) const;
  void writeFAST(QXmlStreamWriter *stream, IFast *fast) const;
  void writeFREAK(QXmlStreamWriter *stream, IFreak *freak) const;
  void writeGFTT(QXmlStreamWriter *stream, IGftt *gftt) const;
  void writeHOG(QXmlStreamWriter *stream, IHog *hog) const;
  void writeKAZE(QXmlStreamWriter *stream, IKaze *kaze) const;
  void writeLATCH(QXmlStreamWriter *stream, ILatch *latch) const;
  void writeLUCID(QXmlStreamWriter *stream, ILucid *lucid) const;
  void writeMSD(QXmlStreamWriter *stream, IMsd *msd) const;
  void writeMSER(QXmlStreamWriter *stream, IMser *mser) const;
  void writeORB(QXmlStreamWriter *stream, IOrb *orb) const;
  void writeSIFT(QXmlStreamWriter *stream, ISift *sift) const;
  void writeSTAR(QXmlStreamWriter *stream, IStar *star) const;
  void writeSURF(QXmlStreamWriter *stream, ISurf *surf) const;

protected:

  static std::mutex sMutex;

};

} // namespace fme

#endif // FME_PROJECT_H
