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

#ifndef TL_CORE_PROCESS_H
#define TL_CORE_PROCESS_H

#include <list>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>

#include "config_tl.h"

#include "tidop/core/defs.h"

//#define TL_OLD_PROCESS

namespace tl
{

class Progress;

/*!
 * \addtogroup utilities Utilidades
 *
 * Utilidades de proposito general como manipulación de cadenas, información de la
 * aplicación etc
 * \{
 */

 /* ---------------------------------------------------------------------------------- */


#ifndef TL_OLD_PROCESS

class TL_EXPORT Process
{
public:

  /*!
   * \brief Estados del proceso
   */
  enum class Status
  {
    start,             /*!< Inicio */
    running,           /*!< Corriendo */
    pausing,           /*!< Pausando */
    pause,             /*!< Pausado */
    stopped,           /*!< Detenido por el usuario */
    finalized,         /*!< Finalizado */
    error              /*!< Terminado con error */
  };

  /*!
   * \brief Interfaz que se debe implementar para recibir los eventos del proceso
   *
   * Las clases que implementen este listener y se subcriban mediante el método
   * addListener() recibiran los diferentes eventos que se emitan desde el proceso.
   */
  class Listener
  {

  public:

    /*!
     * \brief Constructora
     */
    Listener() {}

    /*!
     * \brief destructora
     */
    virtual ~Listener() = default;

    /*!
     * \brief Evento pausa
     * \param id Identificador del proceso
     */
    virtual void onPause(uint64_t id) = 0;

    /*!
     * \brief Evento reanudación
     * \param id Identificador del proceso
     */
    virtual void onResume(uint64_t id) = 0;

    /*!
     * \brief Evento proceso corriendo
     * \param id Identificador del proceso
     */
    virtual void onRun(uint64_t id) = 0;

    /*!
     * \brief Evento detención
     * \param id Identificador del proceso
     */
    virtual void onStop(uint64_t id) = 0;

    /*!
     * \brief
     * \param id Identificador del proceso
     */
    virtual void onEnd(uint64_t id) = 0;

    /*!
     * \brief
     * \param id Identificador del proceso
     */
    virtual void onError(uint64_t id) = 0;
  };

protected:

  /*!
   * \brief Estado del proceso
   */
  Status mStatus;

  /*!
   * \brief proceso padre
   */
  Process *mParent;

  /*!
   * \brief Lista con los escuchadores subscritos al gestor de eventos
   */
  std::list<Listener *> mListeners;

  /*!
   * \brief Identificador del proceso
   */
  unsigned long mProcessId;

  /*!
   * \brief Nombre del proceso
   */
  std::string mProcessName;

  std::thread mThread;

private:

  /*!
   * \brief Número de procesos
   */
  static unsigned long sProcessCount;

public:

  /*!
   * \brief Constructora
   */
  Process(Process *parent = nullptr);

  Process(const Process &) = delete;
  Process(Process &&) = delete;
  void operator=(const Process &) = delete;
  void operator=(Process &&) = delete;

  /*!
   * \brief Destructora
   */
  virtual ~Process();

  /*!
   * \brief Arranca el proceso
   */
  virtual Status run(Progress *progressBar = nullptr);

  /*!
   * \brief Arranca el proceso asincronamente
   */
  virtual void runAsync(Progress *progressBar = nullptr);

  /*!
   * \brief Pausa el proceso
   */
  virtual void pause();

  /*!
   * \brief Reinicia el proceso
   */
  virtual void reset();

  /*!
   * \brief Continua ejecutando el proceso
   */
  virtual void resume();

  /*!
   * \brief Detiene el proceso
   */
  virtual void stop();

  /*!
   * \brief Devuelve el estado actual de la ejecución
   */
  Status status();

  /*!
   * \brief Devuelve el identificador del proceso
   * \return
   */
  uint64_t id() const;

  /*!
   * \brief Devuelve el nombre del proceso
   */
  std::string name() const;

  /*!
   * \brief Añade un escuchador de eventos
   * \param[in] listener Objeto escuchador
   */
  void addListener(Listener *listener);
    
  /*!
   * \brief Quita un escuchador de mensajes
   * \param[in] listener Objeto escuchador
   */
  void removeListener(Listener *listener);

  /*!
   * \brief Establece el contador de procesos a cero
   */
  static void processCountReset();

protected:

  /*!
   * \brief Ejecuta el proceso
   */
  virtual void execute(Progress *progressBar = nullptr) = 0;

  // Eventos que se lanzan
  void endTriggered();
  void pauseTriggered();
  void resumeTriggered();
  void runTriggered();
  void stopTriggered();
  void errorTriggered();
};


/* ---------------------------------------------------------------------------------- */

///TODO: Por ahora se ha copiado directamente de la clase BatchProcess pero hay que revisarlo completamente
class TL_EXPORT BatchProcessing
  : public Process::Listener
{

public:

  /*!
   * \brief Estados de Batch
   */
  enum class Status
  {
    start,             /*!< Inicio */
    running,           /*!< Corriendo */
    pausing,           /*!< Pausando */
    pause,             /*!< Pausado */
    stopping,          /*!< Deteniendose */
    stopped,           /*!< Detenido por el usuario*/
    finalized,         /*!< Finalizado */
    error              /*!< Terminado con error */
  };

  /*!
   * \brief Interfaz que se debe implementar para recibir los eventos del batch
   *
   * Las clases que implementen este listener y se subcriban mediante el método
   * addListener() recibiran los diferentes eventos que se emitan desde el batch.
   */
  class Listener
  {
  public:

    /*!
     * \brief Constructora
     */
    Listener();

    /*!
     * \brief destructora
     */
    virtual ~Listener();

    /*!
     * \brief
     */
    virtual void onEnd() = 0;

    /*!
     * \brief
     */
    virtual void onError() = 0;
  };

protected:

  /*!
   * \brief Estado del batch
   */
  Status mStatus;

  /*!
   * \brief Lista de procesos
   */
  std::list<std::shared_ptr<Process>> mProcessList;

  /*!
   * \brief Lista con los escuchadores subscritos al gestor de eventos
   */
  std::list<Listener *> mListeners;

  std::thread mThread;
  std::mutex mMutex;
  Process *mCurrentProcess;

public:

  /*!
   * \brief Constructora por defecto
   */
  BatchProcessing();

  /*!
   * \brief Constructor de copia
   * \param[in] batchProcess Procesos que se copia
   */
  BatchProcessing(const BatchProcessing &batchProcess);

  /*!
   * \brief Constructor de lista
   * \param[in] procList Listado de procesos
   */
  BatchProcessing(std::initializer_list<std::shared_ptr<Process>> procList);

  /*!
   * \brief Destructora
   */
  ~BatchProcessing() override;

  /*!
   * \brief Corre los procesos
   * \param[in] progressBarTotal Barra de progreso total
   * \param[in] progressBarPartial Barra de progreso parcial
   */
  Status run(Progress *progressBarTotal = nullptr, Progress *progressBarPartial = nullptr);

  /*!
   * \brief Corre los procesos en otro hilo de ejecución
   * \param[in] progressBarTotal Barra de progreso total
   * \param[in] progressBarPartial Barra de progreso parcial
   */
  Status run_async(Progress *progressBarTotal = nullptr, Progress *progressBarPartial = nullptr);

  /*!
   * \brief Añade un nuevo proceso a la lista
   * \param[in] process Proceso que se añade
   */
  void push_back(const std::shared_ptr<Process> &process);
  
  TL_TODO("completar los metodos para poder utilizarlo como contenedor")

  /*!
   * \brief Añade un escuchador de eventos
   * \param[in] listener Objeto escuchador
   */
  void addListener(Listener *listener);

  /*!
   * \brief Quita un escuchador de mensajes
   * \param[in] listener Objeto escuchador
   */
  void removeListener(Listener *listener);

  /*!
   * \brief Elimina el proceso
   * \param[in] id Identificador del proceso que se quiere eliminar
   */
  void remove(uint64_t id);

  /*!
   * \brief Elimina el proceso
   * \param[in] process Proceso que se va a eliminar
   */
  void remove(const std::shared_ptr<Process> &process);

  /*!
   * \brief Comprueba si esta corriendo
   */
  bool isRunning() const;

  /*!
   * \brief Pausa los procesos
   */
  void pause();

  /*!
   * \brief Reinicio los procesos
   */
  void reset();

  /*!
   * \brief Continua corriendo los procesos
   */
  void resume();

  /*!
   * \brief Detiene los procesos
   */
  void stop();

  /*!
   * \brief Inicia el contador
   */
  void initCounter();

protected:

  virtual void onPause(uint64_t id) override;
  virtual void onResume(uint64_t id) override;
  virtual void onRun(uint64_t id) override;
  virtual void onStop(uint64_t id) override;
  virtual void onEnd(uint64_t id) override;
  virtual void onError(uint64_t id) override;

private:

  // Eventos que se lanzan
  void endTriggered();
  void errorTriggered();
};


/* ---------------------------------------------------------------------------------- */

#else

class TL_EXPORT Process
{

public:
  
  /*!
   * \brief Estados del proceso
   */
  enum class Status {
    start,             /*!< Inicio */
    running,           /*!< Corriendo */
    pausing,           /*!< Pausando */
    pause,             /*!< Pausado */
    stopped,           /*!< Detenido por el usuario*/
    finalized,         /*!< Finalizado */
    error              /*!< Terminado con error */
#ifdef TL_ENABLE_DEPRECATED_METHODS
    ,
    START           = start,             /*!< Inicio */
    RUNNING         = running,           /*!< Corriendo */
    PAUSING         = pausing,           /*!< Pausando */
    PAUSE           = pause,             /*!< Pausado */
    STOPPED         = stopped,           /*!< Detenido por el usuario*/
    FINALIZED       = finalized,         /*!< Finalizado */
    FINALIZED_ERROR = error              /*!< Terminado con error */
#endif
  };

  /*!
   * \brief Interfaz que se debe implementar para recibir los eventos del proceso
   *
   * Las clases que implementen este listener y se subcriban mediante el método 
   * addListener() recibiran los diferentes eventos que se emitan desde el proceso.
   */
  class Listener
  {
  public:

    /*!
     * \brief Constructora
     */
    Listener(){}

    /*!
     * \brief destructora
     */
    virtual ~Listener() = default;

    /*!
     * \brief Evento pausa
     * \param id Identificador del proceso
     */
    virtual void onPause(uint64_t id) = 0;

    /*!
     * \brief Evento reanudación
     * \param id Identificador del proceso
     */
    virtual void onResume(uint64_t id) = 0;

    /*!
     * \brief Evento proceso corriendo
     * \param id Identificador del proceso
     */
    virtual void onRun(uint64_t id) = 0;

    /*!
     * \brief Evento inicio procesos
     * \param id Identificador del proceso
     */
    virtual void onStart(uint64_t id) = 0;

    /*!
     * \brief Evento detención
     * \param id Identificador del proceso
     */
    virtual void onStop(uint64_t id) = 0;

    /*!
     * \brief 
     * \param id Identificador del proceso
     */
    virtual void onEnd(uint64_t id) = 0;

    /*!
     * \brief 
     * \param id Identificador del proceso
     */
    virtual void onError(uint64_t id) = 0;
  };

protected:

  Status mStatus;
  Process *mParentProcess;

  /*!
   * \brief Lista con los escuchadores subscritos al gestor de eventos
   */
  std::list<Listener *> mListeners;

  /*!
   * \brief Identificador del proceso 
   */    
  unsigned long mProcessId;

  /*!
   * \brief Nombre del proceso 
   */  
  std::string mProcessName;

private:

  /*!
   * \brief Número de procesos
   */
  static unsigned long sProcessCount;

public:

  /*!
   * \brief Constructora
   */
  Process(Process *parentProcess = nullptr);

  /*!
   * \brief Destructora
   */
  virtual ~Process();

  /*!
   * \brief Añade un escuchador de eventos
   * \param[in] listener Objeto escuchador
   */
  void addListener(Listener *listener);

  /*!
   * \brief Pausa el proceso
   */
  virtual void pause();

  /*!
   * \brief Quita un escuchador de mensajes
   * \param[in] listener Objeto escuchador
   */
  void removeListener(Listener *listener);

  /*!
   * \brief Reinicia el proceso
   */
  virtual void reset();

  /*!
   * \brief Continua ejecutando el proceso
   */
  virtual void resume();

  /*!
   * \brief Arranca el proceso
   * Aunque es virtual pura se define el comportamiento por defecto.
   * Desde la implementación del método en la clase hija se debe incluir 
   * Process::run() o establecer directamente mStatus = Status::RUNNING
   * al inicio del método para establecer que el proceso esta corriendo.
   */
  virtual Status run(Progress *progressBar = nullptr) = 0;

  /*!
   * \brief Detiene el proceso
   */
  virtual void stop();

  /*!
   * \brief Devuelve el estado actual de la ejecución
   */
  Status status();

  /*!
   * \brief Establece el estado
   * \param[in] status
   */
  void setStatus(Status status);

  /*!
   * \brief Devuelve el identificador del proceso
   * \return
   */
  uint64_t id() const;

  /*!
   * \brief Devuelve el nombre del proceso
   */
  std::string name() const;

  /*!
   * \brief Establece el contador de procesos a cero
   */
  static void processCountReset();

protected:

  // Eventos que se lanzan
  void endTriggered();
  void pauseTriggered();
  void resumeTriggered();
  void runTriggered();
  void startTriggered();
  void stopTriggered();
  void errorTriggered();

  /*!
   * \brief Chequeo del estado del proceso
   * 
   * Este método puede llamarse para comprobar el estado actual del proceso
   * y actuar en consecuencia (poner el proceso en pausa, reanudarlo, finalizar)
   *
   */
  virtual Status checkStatus();
  
public:

#ifdef TL_ENABLE_DEPRECATED_METHODS
  /*!
   * \brief Devuelve el estado actual de la ejecución
   * \deprecated Use 'status()'  en su lugar
   */
  TL_DEPRECATED("status", "2.0")
  Status getStatus();
  
  /*!
   * \brief Devuelve el identificador del proceso
   * \return
   * \deprecated Use 'status()'  en su lugar
   */
  TL_DEPRECATED("id", "2.0")
  uint64_t getProcessId() const;

  /*!
   * \brief Devuelve el nombre del proceso 
   * \deprecated Use 'processName()'  en su lugar
   */
  TL_DEPRECATED("processName", "2.0")
  std::string getProcessName() const;

#endif // TL_ENABLE_DEPRECATED_METHODS

};


/* ---------------------------------------------------------------------------------- */

//TODO: Pendiente para Linux
class TL_EXPORT CmdProcess
  : public Process
{
public:

#ifdef WIN32
  //// Añadir prioridad https://msdn.microsoft.com/en-us/library/windows/desktop/ms683211(v=vs.85).aspx
  enum class Priority
  {
    realtime = REALTIME_PRIORITY_CLASS,
    high = HIGH_PRIORITY_CLASS,
    above_normal = ABOVE_NORMAL_PRIORITY_CLASS,
    normal = NORMAL_PRIORITY_CLASS,
    below_normal = BELOW_NORMAL_PRIORITY_CLASS,
    idle = IDLE_PRIORITY_CLASS
  };
#ifdef TL_ENABLE_DEPRECATED_METHODS
  enum class PRIORITY
  {
    REALTIME = REALTIME_PRIORITY_CLASS,
    HIGH = HIGH_PRIORITY_CLASS,
    ABOVE_NORMAL = ABOVE_NORMAL_PRIORITY_CLASS,
    NORMAL = NORMAL_PRIORITY_CLASS,
    BELOW_NORMAL = BELOW_NORMAL_PRIORITY_CLASS,
    IDLE = IDLE_PRIORITY_CLASS
  };
#endif
#endif

protected:

#ifdef WIN32
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  static DWORD sPriority;
#endif
  std::string mCmd;

public:

  CmdProcess(const std::string &cmd, Process *parentProcess = nullptr);
  ~CmdProcess() override;

  virtual Process::Status run(Progress *progressBar = nullptr) override;

  /*!
  * \brief Establece la prioridad del proceso
  * \param[in] priority
  */
  static void setPriority(int priority);

private:

#ifdef WIN32
  std::string formatErrorMsg(DWORD errorCode);
#endif
};


/* ---------------------------------------------------------------------------------- */

class BatchProcess
  : public Process::Listener
{
public:

  /*!
  * \brief Estados de Batch
  */
  enum class Status
  {
    start,             /*!< Inicio */
    running,           /*!< Corriendo */
    pausing,           /*!< Pausando */
    pause,             /*!< Pausado */
    stopped,           /*!< Detenido por el usuario*/
    finalized,         /*!< Finalizado */
    error              /*!< Terminado con error */
#ifdef TL_ENABLE_DEPRECATED_METHODS
    ,
    START = start,             /*!< Inicio */
    RUNNING = running,           /*!< Corriendo */
    PAUSING = pausing,           /*!< Pausando */
    PAUSE = pause,             /*!< Pausado */
    STOPPED = stopped,           /*!< Detenido por el usuario*/
    FINALIZED = finalized,         /*!< Finalizado */
    FINALIZED_ERROR = error              /*!< Terminado con error */
#endif
  };

  /*!
  * \brief Interfaz que se debe implementar para recibir los eventos del batch
  *
  * Las clases que implementen este listener y se subcriban mediante el método
  * addListener() recibiran los diferentes eventos que se emitan desde el batch.
  */
  class Listener
  {
  public:

    /*!
    * \brief Constructora
    */
    Listener();

    /*!
    * \brief destructora
    */
    virtual ~Listener();

    /*!
    * \brief
    */
    virtual void onEnd() = 0;

    /*!
    * \brief
    */
    virtual void onError() = 0;
  };

protected:

  /*!
  * \brief Estado del batch
  */
  Status mStatus;

  /*!
  * \brief Lista de procesos
  */
  std::list<std::shared_ptr<Process>> mProcessList;

  /*!
  * \brief Lista con los escuchadores subscritos al gestor de eventos
  */
  std::list<Listener *> mListeners;

  std::thread _thread;
  std::mutex mtx;
  Process *mCurrentProcess;

public:

  /*!
  * \brief Constructora por defecto
  */
  BatchProcess();

  /*!
  * \brief Constructor de copia
  * \param[in] batchProcess Procesos que se copia
  */
  BatchProcess(const BatchProcess &batchProcess);

  /*!
  * \brief Constructor de lista
  * \param[in] procList Listado de procesos
  */
  BatchProcess(std::initializer_list<std::shared_ptr<Process>> procList);

  /*!
  * \brief Destructora
  */
  ~BatchProcess() override;

  /*!
  * \brief Añade un nuevo proceso a la lista
  * \param[in] process Proceso que se añade
  */
  void add(const std::shared_ptr<Process> &process);

  /*!
  * \brief Añade un escuchador de eventos
  * \param[in] listener Objeto escuchador
  */
  void addListener(Listener *listener);

  /*!
  * \brief Quita un escuchador de mensajes
  * \param[in] listener Objeto escuchador
  */
  void removeListener(Listener *listener);

#ifdef TL_ENABLE_DEPRECATED_METHODS

  /*!
  * \brief Limpia la lista de procesos
  * \deprecated Use reset() en su lugar
  */
  TL_DEPRECATED("BatchProcess::reset()", "2.0")
    void clear();

#endif // TL_ENABLE_DEPRECATED_METHODS

  /*!
  * \brief Elimina el proceso
  * \param[in] id Identificador del proceso que se quiere eliminar
  */
  void remove(uint64_t id);

  /*!
  * \brief Elimina el proceso
  * \param[in] process Proceso que se va a eliminar
  */
  void remove(const std::shared_ptr<Process> &process);

  /*!
  * \brief Comprueba si esta corriendo
  */
  bool isRunning() const;

  /*!
  * \brief Pausa los procesos
  */
  void pause();

  /*!
  * \brief Reinicio los procesos
  */
  void reset();

  /*!
  * \brief Continua corriendo los procesos
  */
  void resume();

  /*!
  * \brief Corre los procesos
  * \param[in] progressBarTotal Barra de progreso total
  * \param[in] progressBarPartial Barra de progreso parcial
  */
  Status run(Progress *progressBarTotal = nullptr, Progress *progressBarPartial = nullptr);

  /*!
  * \brief Corre los procesos en otro hilo de ejecución
  * \param[in] progressBarTotal Barra de progreso total
  * \param[in] progressBarPartial Barra de progreso parcial
  */
  Status run_async(Progress *progressBarTotal = nullptr, Progress *progressBarPartial = nullptr);

  /*!
  * \brief Detiene los procesos
  */
  void stop();

  /*!
  * \brief Inicia el contador
  */
  void initCounter();

protected:

  virtual void onPause(uint64_t id) override;
  virtual void onResume(uint64_t id) override;
  virtual void onRun(uint64_t id) override;
  virtual void onStart(uint64_t id) override;
  virtual void onStop(uint64_t id) override;
  virtual void onEnd(uint64_t id) override;
  virtual void onError(uint64_t id) override;

private:

  // Eventos que se lanzan
  void endTriggered();
  void errorTriggered();

};

#endif


/* ---------------------------------------------------------------------------------- */

//class TL_EXPORT ExternalProcess
//  : public Process
//{
//
//#ifdef WIN32
//  //// Añadir prioridad https://msdn.microsoft.com/en-us/library/windows/desktop/ms683211(v=vs.85).aspx
//  enum class Priority
//  {
//    realtime = REALTIME_PRIORITY_CLASS,
//    high = HIGH_PRIORITY_CLASS,
//    above_normal = ABOVE_NORMAL_PRIORITY_CLASS,
//    normal = NORMAL_PRIORITY_CLASS,
//    below_normal = BELOW_NORMAL_PRIORITY_CLASS,
//    idle = IDLE_PRIORITY_CLASS
//  };
//#endif
//
//protected:
//
//  std::string mProcess;
//  std::vector<std::string> mArg;
//#ifdef WIN32
//  STARTUPINFO si;
//  PROCESS_INFORMATION pi;
//  static DWORD sPriority;
//#endif
//
//public:
//
//  ExternalProcess(const std::string &process, const std::vector<std::string> &arg);
//  ~ExternalProcess() override {}
//
//// Process interface
//
//public:
//
//  Status run(Progress *progressBar) override;
//};

/* ---------------------------------------------------------------------------------- */


///*!
// * \brief Wrapper de una función para ejecutarla como un proceso.
// * 
// */
//class TL_EXPORT FunctionProcess : public Process
//{
//
//private:
//
//  /*!
//   * \brief Función
//   */
//  std::function<void()> f;
//
//public:
//
//  /*!
//   * \brief Constructora
//   * \param[in] f Función de la forma std::function<void(const cv::Mat &,cv::Mat *)>
//   */
//  FunctionProcess(std::function<void()> f);
//
//  ~FunctionProcess();
//
//  virtual Process::Status run(Progress *progressBar = NULL) override;
//
//};


/* ---------------------------------------------------------------------------------- */

/*!
 * \brief Clase para separar en bloques un proceso
 *
 * Por bloque se entiende una tarea particular del proceso que se
 * ejecuta sin comprobación del estado de ejecución del batch.
 * Al finalizar un bloque se comprueba el estado del batch poniendolo 
 * a pausa o obligando a su terminación. Si se indica una barra de proceso
 * también se avanza una posición
 *
 */
//class ProcessBlock
//{
//
//private:
//
//  int mCount;
//  tl::Progress *mProgressBar;
//
//public:
//
//  ProcessBlock(int nBlocks, tl::Progress *progressBar = nullptr);
//  ~ProcessBlock();
//  
//  void next();
//
//private:
//
//};



/*! \} */ // end of utilities



/* ---------------------------------------------------------------------------------- */

} // End namespace tl

#endif // TL_CORE_PROCESS_H
