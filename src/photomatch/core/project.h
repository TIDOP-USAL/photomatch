/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#ifndef PHOTOMATCH_PROJECT_H
#define PHOTOMATCH_PROJECT_H

#include "photomatch/photomatch_global.h"

#include <memory>
#include <vector>
#include <mutex>

#include <QString>

#include "photomatch/core/image.h"
#include "photomatch/core/session.h"
#include "photomatch/core/preprocess/preprocess.h"
#include "photomatch/core/features/features.h"
#include "photomatch/core/features/matcher.h"

class QXmlStreamWriter;
class QXmlStreamReader;

namespace photomatch
{

/*!
 * \brief Interfaz Project
 */
class PHOTOMATCH_EXPORT Project
{

public:

  typedef std::vector<std::shared_ptr<Image>>::iterator image_iterator;
  typedef std::vector<std::shared_ptr<Image>>::const_iterator image_const_iterator;
  typedef std::vector<std::shared_ptr<Session>>::iterator session_iterator;
  typedef std::vector<std::shared_ptr<Session>>::const_iterator session_const_iterator;

public:

  Project() {}
  virtual ~Project() = default;

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
   * \brief Establece la verdad terreno
   * \param[in] groundTruth Fichero con la verdad terreno
   */
  virtual void setGroundTruth(const QString &groundTruth) = 0;

  /*!
   * \brief Fichero con la verdad terreno
   * \return
   */
  virtual QString groundTruth() const = 0;

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

  virtual std::shared_ptr<Image> findImageById(size_t id) = 0;
  virtual const std::shared_ptr<Image> findImageById(size_t id) const = 0;
  virtual std::shared_ptr<Image> findImageByName(const QString &imgName) = 0;
  virtual const std::shared_ptr<Image> findImageByName(const QString &imgName) const = 0;

  /*!
   * \brief Busca una imagen en el proyecto
   * \param[in] path Ruta de la imagen a buscar
   * \return Objeto Identificador de la imagen o std::numeric_limits<size_t>().max() si no se encuentra.
   */
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
class PHOTOMATCH_EXPORT ProjectController
{

public:

  ProjectController() {}
  virtual ~ProjectController() = default;

  /*!
   * \brief read
   * \param[in] file Ruta del fichero de proyecto
   * \param[out] prj
   * \return
   */
  virtual bool read(const QString &file, Project &prj) = 0;

  /*!
   * \brief write
   * \param prj
   * \param file
   * \return
   */
  virtual bool write(const QString &file, const Project &prj) const = 0;

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


class PHOTOMATCH_EXPORT ProjectImp
  : public Project
{

public:

  ProjectImp();
  ~ProjectImp() override = default;

// IProject interface

public:

  QString name() const override;
  void setName(const QString &name) override;
  QString description() const override;
  void setDescription(const QString &description) override;
  QString projectFolder() const override;
  void setProjectFolder(const QString &dir) override;
  QString version() const override;
  QString groundTruth() const override;
  void setGroundTruth(const QString &groundTruth) override;
  void addImage(const std::shared_ptr<Image> &img) override;
  void deleteImage(const QString &img) override;
  void deleteImage(size_t imgId) override;
  std::shared_ptr<Image> findImage(const QString &path) override;
  const std::shared_ptr<Image> findImage(const QString &path) const override;
  std::shared_ptr<Image> findImageById(size_t id) override;
  const std::shared_ptr<Image> findImageById(size_t id) const override;
  std::shared_ptr<Image> findImageByName(const QString &imgName) override;
  const std::shared_ptr<Image> findImageByName(const QString &imgName) const override;
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
  QString mGroundTruth;
  std::vector<std::shared_ptr<Image>> mImages;
  std::vector<std::shared_ptr<Session>> mSessions;
  int mCurrentSession;
};


class PHOTOMATCH_EXPORT ProjectControllerImp
  : public ProjectController
{

public:

  ProjectControllerImp();

// IProjectIO interface

public:

  bool read(const QString &file, Project &prj) override;
  bool write(const QString &file, const Project &prj) const override;
  bool checkOldVersion(const QString &file) const override;
  void oldVersionBak(const QString &file) const override;


protected:

  void readGeneral(QXmlStreamReader &stream, Project &prj);
  void readImages(QXmlStreamReader &stream, Project &prj);
  std::shared_ptr<Image> readImage(QXmlStreamReader &stream);
  void readGroundTruth(QXmlStreamReader &stream, Project &prj);
  void readSessions(QXmlStreamReader &stream, Project &prj);
  bool readActiveSession(QXmlStreamReader &stream);
  std::shared_ptr<Session> readSession(QXmlStreamReader &stream);
  void readSessionName(QXmlStreamReader &stream, Session *session);
  void readSessionDescription(QXmlStreamReader &stream, Session *session);
  void readSessionMaxImageSize(QXmlStreamReader &stream, Session *session);
  void readPreprocess(QXmlStreamReader &stream, Session *session);
  void readFeatures(QXmlStreamReader &stream, Session *session);
  void readFeaturesDetector(QXmlStreamReader &stream, Session *session);
  void readFeaturesDescriptor(QXmlStreamReader &stream, Session *session);
  void readFeaturesFiles(QXmlStreamReader &stream, Session *session);
  void readMatches(QXmlStreamReader &stream, Session *session);
  void readMatchingMethod(QXmlStreamReader &stream, Session *session);
  void readBruteForceMatching(QXmlStreamReader &stream, Session *session);
  BruteForceMatcher::Norm readBruteForceMatchingNormType(QXmlStreamReader &stream);
  void readFlannMatcher(QXmlStreamReader &stream, Session *session);
  void readMatchingStrategy(QXmlStreamReader &stream, Session *session);
  void readRobustMatching(QXmlStreamReader &stream, Session *session);
  void readRobustMatchingGeometricTest(QXmlStreamReader &stream, RobustMatcher *robustMatcher);
  void readRobustMatchingGeometricTestHomographyMatrix(QXmlStreamReader &stream, RobustMatcher *robustMatcher);
  RobustMatcher::HomographyComputeMethod readRobustMatchingGeometricTestHomographyMatrixComputeMethod(QXmlStreamReader &stream);
  void readRobustMatchingGeometricTestFundamentalMatrix(QXmlStreamReader &stream, RobustMatcher *robustMatcher);
  RobustMatcher::FundamentalComputeMethod readRobustMatchingGeometricTestFundamentalMatrixComputeMethod(QXmlStreamReader &stream);
  void readRobustMatchingGeometricTestEssentialMatrix(QXmlStreamReader &stream, RobustMatcher *robustMatcher);
  RobustMatcher::EssentialComputeMethod readRobustMatchingGeometricTestEssentialMatrixComputeMethod(QXmlStreamReader &stream);
  void readGms(QXmlStreamReader &stream, Session *session);
  void readMatchesImages(QXmlStreamReader &stream, Session *session);
  void readPassPoints(QXmlStreamReader &stream, Session *session);
  void readACEBSF(QXmlStreamReader &stream, Acebsf *acebsf) const;
  void readCLAHE(QXmlStreamReader &stream, Clahe *clahe) const;
  void readCMBFHE(QXmlStreamReader &stream, Cmbfhe *cmbfhe) const;
  void readDHE(QXmlStreamReader &stream, Dhe *dhe) const;
  void readFAHE(QXmlStreamReader &stream, Fahe *fahe) const;
  void readHMCLAHE(QXmlStreamReader &stream, Hmclahe *hmclahe) const;
  void readLCEBSESCS(QXmlStreamReader &stream, LceBsescs *lceBsescs) const;
  void readMSRCP(QXmlStreamReader &stream, Msrcp *msrcp) const;
  void readNOSHP(QXmlStreamReader &stream, Noshp *noshp) const;
  void readPOHE(QXmlStreamReader &stream, Pohe *pohe) const;
  void readRSWHE(QXmlStreamReader &stream, Rswhe *rswhe) const;
  void readWALLIS(QXmlStreamReader &stream, Wallis *wallis) const;

  void readAGAST(QXmlStreamReader &stream, Agast *agast) const;
  void readAKAZE(QXmlStreamReader &stream, Akaze *akaze) const;
  void readASIFT(QXmlStreamReader &stream, ASift *asift) const;
  void readBOOST(QXmlStreamReader &stream, Boost *boost) const;
  void readBRIEF(QXmlStreamReader &stream, Brief *brief) const;
  void readBRISK(QXmlStreamReader &stream, Brisk *brisk) const;
  void readD2NET(QXmlStreamReader &stream, D2Net *d2net) const;
  void readDAISY(QXmlStreamReader &stream, Daisy *daisy) const;
  void readFAST(QXmlStreamReader &stream, Fast *fast) const;
  void readFREAK(QXmlStreamReader &stream, Freak *freak) const;
  void readGFTT(QXmlStreamReader &stream, Gftt *gftt) const;
  void readHOG(QXmlStreamReader &stream, Hog *hog) const;
  void readKAZE(QXmlStreamReader &stream, Kaze *kaze) const;
  void readLATCH(QXmlStreamReader &stream, Latch *latch) const;
  void readLUCID(QXmlStreamReader &stream, Lucid *lucid) const;
  void readMSD(QXmlStreamReader &stream, Msd *msd) const;
  void readMSER(QXmlStreamReader &stream, Mser *mser) const;
  void readORB(QXmlStreamReader &stream, Orb *orb) const;
  void readSIFT(QXmlStreamReader &stream, Sift *sift) const;
  void readSTAR(QXmlStreamReader &stream, Star *star) const;
  void readSURF(QXmlStreamReader &stream, Surf *surf) const;
  void readVGG(QXmlStreamReader &stream, Vgg *vgg) const;

  void writeVersion(QXmlStreamWriter &stream, const QString &version) const;
  void writeGeneral(QXmlStreamWriter &stream, const Project &prj) const;
  void writeImages(QXmlStreamWriter &stream, const Project &prj) const;
  void writeImage(QXmlStreamWriter &stream, const Image *image) const;
  void writeGroundTruth(QXmlStreamWriter &stream, const QString &groundTruth) const;
  void writeSessions(QXmlStreamWriter &stream, const Project &prj) const;
  void writeSession(QXmlStreamWriter &stream, Session *session, bool activeSession) const;
  void writeSessionName(QXmlStreamWriter &stream, const QString &name) const;
  void writeSessionDescription(QXmlStreamWriter &stream, const QString &description) const;
  void writeSessionMaxImageSize(QXmlStreamWriter &stream, int maxImageSize) const;
  void writePreprocess(QXmlStreamWriter &stream, Session *session) const;
  void writePreprocessMethod(QXmlStreamWriter &stream, Preprocess *preprocess) const;
  void writePreprocessedImages(QXmlStreamWriter &stream, const std::vector<QString> &preprocessImages) const;
  void writeFeatures(QXmlStreamWriter &stream, Session *session) const;
  void writeFeatureDetector(QXmlStreamWriter &stream, Feature *detector) const;
  void writeFeatureExtractor(QXmlStreamWriter &stream, Feature *descriptor) const;
  void writeFeaturesFiles(QXmlStreamWriter &stream, const std::vector<QString> &features) const;
  void writeMatches(QXmlStreamWriter &stream, Session *session) const;
  void writeMatchingMethod(QXmlStreamWriter &stream, MatchingMethod *matchingMethod) const;
  void writeFlann(QXmlStreamWriter &stream, MatchingMethod *matchingMethod) const;
  void writeBruteForceMatching(QXmlStreamWriter &stream, MatchingMethod *matchingMethod) const;
  void writeMatchingStrategy(QXmlStreamWriter &stream, MatchingStrategy *matchingStrategy) const;
  void writeRobustMatching(QXmlStreamWriter &stream, MatchingStrategy *matchingStrategy) const;
  void writeRobustMatchingRatio(QXmlStreamWriter &stream, RobustMatcher *robustMatcher) const;
  void writeRobustMatchingCrossCheck(QXmlStreamWriter &stream, RobustMatcher *robustMatcher) const;
  void writeRobustMatchingGeometricTest(QXmlStreamWriter &stream, RobustMatcher *robustMatcher) const;
  void writeRobustMatchingGeometricTestHomographyMatrix(QXmlStreamWriter &stream, RobustMatcher *robustMatcher) const;
  void writeRobustMatchingGeometricTestFundamentalMatrix(QXmlStreamWriter &stream, RobustMatcher *robustMatcher) const;
  void writeRobustMatchingGeometricTestEssentialMatrix(QXmlStreamWriter &stream, RobustMatcher *robustMatcher) const;
  void writeGms(QXmlStreamWriter &stream, MatchingStrategy *matchingStrategy) const;
  void writeMatchingImages(QXmlStreamWriter &stream, const std::map<QString, std::vector<std::pair<QString, QString>>> &matches) const;
  void writeACEBSF(QXmlStreamWriter &stream, Acebsf *acebsf) const;
  void writeCLAHE(QXmlStreamWriter &stream, Clahe *clahe) const;
  void writeCMBFHE(QXmlStreamWriter &stream, Cmbfhe *cmbfhe) const;
  void writeDecolor(QXmlStreamWriter &stream, Decolor *decolor) const;
  void writeDHE(QXmlStreamWriter &stream, Dhe *dhe) const;
  void writeFAHE(QXmlStreamWriter &stream, Fahe *fahe) const;
  void writeHMCLAHE(QXmlStreamWriter &stream, Hmclahe *hmclahe) const;
  void writeLCEBSESCS(QXmlStreamWriter &stream, LceBsescs *lceBsescs) const;
  void writeMSRCP(QXmlStreamWriter &stream, Msrcp *msrcp) const;
  void writeNOSHP(QXmlStreamWriter &stream, Noshp *noshp) const;
  void writePOHE(QXmlStreamWriter &stream, Pohe *pohe) const;
  void writeRSWHE(QXmlStreamWriter &stream, Rswhe *rswhe) const;
  void writeWALLIS(QXmlStreamWriter &stream, Wallis *wallis) const;

  void writeAGAST(QXmlStreamWriter &stream, Agast *agast) const;
  void writeAKAZE(QXmlStreamWriter &stream, Akaze *akaze) const;
  void writeASIFT(QXmlStreamWriter &stream, ASift *asift) const;
  void writeBOOST(QXmlStreamWriter &stream, Boost *boost) const;
  void writeBRIEF(QXmlStreamWriter &stream, Brief *brief) const;
  void writeBRISK(QXmlStreamWriter &stream, Brisk *brisk) const;
  void writeD2NET(QXmlStreamWriter &stream, D2Net *d2net) const;
  void writeDAISY(QXmlStreamWriter &stream, Daisy *daisy) const;
  void writeFAST(QXmlStreamWriter &stream, Fast *fast) const;
  void writeFREAK(QXmlStreamWriter &stream, Freak *freak) const;
  void writeGFTT(QXmlStreamWriter &stream, Gftt *gftt) const;
  void writeHOG(QXmlStreamWriter &stream, Hog *hog) const;
  void writeKAZE(QXmlStreamWriter &stream, Kaze *kaze) const;
  void writeLATCH(QXmlStreamWriter &stream, Latch *latch) const;
  void writeLUCID(QXmlStreamWriter &stream, Lucid *lucid) const;
  void writeLSS(QXmlStreamWriter &stream, Lss *lss) const;
  void writeMSD(QXmlStreamWriter &stream, Msd *msd) const;
  void writeMSER(QXmlStreamWriter &stream, Mser *mser) const;
  void writeORB(QXmlStreamWriter &stream, Orb *orb) const;
  void writeSIFT(QXmlStreamWriter &stream, Sift *sift) const;
  void writeSTAR(QXmlStreamWriter &stream, Star *star) const;
  void writeSURF(QXmlStreamWriter &stream, Surf *surf) const;
  void writeVGG(QXmlStreamWriter &stream, Vgg *vgg) const;

  QSize readSize(QXmlStreamReader &stream) const;
  int readInt(QXmlStreamReader &stream) const;
  double readDouble(QXmlStreamReader &stream) const;
  bool readBoolean(QXmlStreamReader &stream) const;

protected:

  static std::mutex sMutex;

};

} // namespace photomatch

#endif // PHOTOMATCH_PROJECT_H
