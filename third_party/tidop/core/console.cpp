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

#include "tidop/core/console.h"

#include "tidop/core/defs.h"
#include "tidop/core/utils.h"
#include "tidop/core/messages.h"

#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>

namespace tl
{

struct msgProperties {
  const char *normal;
  const char *extend;
  Console::Color foreColor;
  Console::Intensity intensity;
};

static struct msgProperties msgTemplate[] = {   
  { "Debug:   %s", "Debug:   %s (%s:%u, %s)", Console::Color::white, Console::Intensity::normal},
  { "Info:    %s", "Info:    %s (%s:%u, %s)", Console::Color::white, Console::Intensity::bright},
  { "Warning: %s", "Warning: %s (%s:%u, %s)", Console::Color::magenta, Console::Intensity::bright},
  { "Error:   %s", "Error:   %s (%s:%u, %s)", Console::Color::red, Console::Intensity::bright}
};

msgProperties getMessageProperties( MessageLevel msgLevel ) 
{
  int iLevel = 0;
  switch (msgLevel) {
  case MessageLevel::msg_debug:
    iLevel = 0;
    break;
  case MessageLevel::msg_info:
    iLevel = 1;
    break;
  case MessageLevel::msg_warning:
    iLevel = 2;
    break;
  case MessageLevel::msg_error:
    iLevel = 3;
    break;
  default:
    iLevel = 3;
    break;
  }
  return msgTemplate[iLevel];
}



EnumFlags<MessageLevel> Console::sLevel = MessageLevel::msg_error;
std::unique_ptr<Console> Console::sObjConsole;
std::mutex Console::mtx;

Console::Console()
#ifdef TL_MESSAGE_HANDLER 
  : MessageManager::Listener(false)
#endif
{ 
#ifdef WIN32
  init(STD_OUTPUT_HANDLE);
#else
  init(stdout);
#endif
}

Console::~Console() 
{
  reset();
  sObjConsole.release();
}

Console &Console::instance()
{
  if (sObjConsole.get() == nullptr) {
    std::lock_guard<std::mutex> lck(Console::mtx);
    if (sObjConsole.get() == nullptr) {
      sObjConsole.reset(new Console());
    }
  }
  return *sObjConsole;
}



void Console::printMessage(const std::string &msg)
{
  // Por si esta corriendo la barra de progreso
  std::cout << "\r";

  std::string aux(msg);
  replaceString(&aux, "%", "%%");
  printf_s("%s\n", aux.c_str());
}

void Console::printErrorMessage(const std::string &msg)
{
  setConsoleForegroundColor(getMessageProperties(MessageLevel::msg_error).foreColor,
                            getMessageProperties(MessageLevel::msg_error).intensity);
  printMessage(msg);
  reset();
}



void Console::setConsoleBackgroundColor(Console::Color backColor, Console::Intensity intensity)
{
#ifdef WIN32
  switch (backColor) {
  case tl::Console::Color::black:
    mBackColor = 0;
    break;
  case tl::Console::Color::blue:
    mBackColor = BACKGROUND_BLUE;
    break;
  case tl::Console::Color::green:
    mBackColor = BACKGROUND_GREEN;
    break;
  case tl::Console::Color::cyan:
    mBackColor = BACKGROUND_GREEN | BACKGROUND_BLUE;
    break;
  case tl::Console::Color::red:
    mBackColor = BACKGROUND_RED;
    break;
  case tl::Console::Color::magenta:
    mBackColor = BACKGROUND_RED | BACKGROUND_BLUE;
    break;
  case tl::Console::Color::yellow:
    mBackColor = BACKGROUND_GREEN | BACKGROUND_RED;
    break;
  case tl::Console::Color::white:
    mBackColor = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED;
    break;
  default:
    mBackColor = 0;
    break;
  }
  if(intensity == Console::Intensity::normal)
      mBackIntensity = 0;
  else
      mBackIntensity = BACKGROUND_INTENSITY;
#else
  mBackColor = static_cast<int>(backColor) + 40 + static_cast<int>(intensity) * 60;
#endif
  update();
}

void Console::setConsoleForegroundColor(Console::Color foreColor, Console::Intensity intensity)
      {
#ifdef WIN32
  switch (foreColor) {
  case tl::Console::Color::black:
    mForeColor = 0;
    break;
  case tl::Console::Color::blue:
    mForeColor = FOREGROUND_BLUE;
    break;
  case tl::Console::Color::green:
    mForeColor = FOREGROUND_GREEN;
    break;
  case tl::Console::Color::cyan:
    mForeColor = FOREGROUND_GREEN | FOREGROUND_BLUE;
    break;
  case tl::Console::Color::red:
    mForeColor = FOREGROUND_RED;
    break;
  case tl::Console::Color::magenta:
    mForeColor = FOREGROUND_RED | FOREGROUND_BLUE;
    break;
  case tl::Console::Color::yellow:
    mForeColor = FOREGROUND_GREEN | FOREGROUND_RED;
    break;
  case tl::Console::Color::white:
    mForeColor = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    break;
  default:
    mForeColor = 0;
    break;
  }

  if(intensity == Console::Intensity::normal)
      mForeIntensity = 0;
  else
      mForeIntensity = FOREGROUND_INTENSITY;
#else
  mForeColor = static_cast<int>(foreColor) + 30 + static_cast<int>(intensity) * 60;
#endif

  update();
}

void Console::setConsoleUnicode() 
{
#ifdef WIN32
  //SetConsoleOutputCP(1252);     
  //SetConsoleCP(1252);
  SetConsoleOutputCP(CP_UTF8/*65001*/);
#endif
}

void Console::setFontBold(bool bBold)
{
#ifdef WIN32
  if (bBold) {
    mCurrentFont.FontWeight = FW_BOLD;
  } else {
    mCurrentFont.FontWeight = FW_NORMAL;
  }
#else
  if (bBold) {
    mBold = 1;
  } else {
    mBold = 21;
  }
#endif
  update();
}



#ifdef TL_MESSAGE_HANDLER 

TL_DISABLE_WARNING(TL_UNREFERENCED_FORMAL_PARAMETER)

void Console::onMsgDebug(const char *msg, const char *date)
{
  if (sLevel.isActive(MessageLevel::msg_debug)) {
    setConsoleForegroundColor(getMessageProperties(MessageLevel::msg_debug).foreColor,
                              getMessageProperties(MessageLevel::msg_debug).intensity);
    printMessage(msg);
    reset();
  }
}

void Console::onMsgInfo(const char *msg, const char *date)
{
  if (sLevel.isActive(MessageLevel::msg_info)) {
    setConsoleForegroundColor(getMessageProperties(MessageLevel::msg_info).foreColor,
                              getMessageProperties(MessageLevel::msg_info).intensity);
    printMessage(msg);
    reset();
  }
}

void Console::onMsgWarning(const char *msg, const char *date)
{
  if (sLevel.isActive(MessageLevel::msg_warning)) {
    setConsoleForegroundColor(getMessageProperties(MessageLevel::msg_warning).foreColor,
                              getMessageProperties(MessageLevel::msg_warning).intensity);
    printMessage(msg);
    reset();
  }
}

void Console::onMsgError(const char *msg, const char *date)
{
  if (sLevel.isActive(MessageLevel::msg_error)) {
    printErrorMessage(msg);
  }
}

TL_ENABLE_WARNING(TL_UNREFERENCED_FORMAL_PARAMETER)

#endif // TL_MESSAGE_HANDLER 

#ifdef WIN32
void Console::init(DWORD handle) 
{
  setConsoleUnicode();
  mHandle = GetStdHandle(handle);
  CONSOLE_SCREEN_BUFFER_INFO info; 
  if (! GetConsoleScreenBufferInfo(mHandle, &info)) {
    mOldColorAttrs = 0x0007;
  } else {
    mOldColorAttrs = info.wAttributes; 
  }
  mForeColor = (mOldColorAttrs & 0x0007);
  mForeIntensity = (mOldColorAttrs & 0x0008);
  mBackColor = (mOldColorAttrs & 0x0070);
  mBackIntensity = (mOldColorAttrs & 0x0080);

  mIniFont.cbSize = sizeof(mIniFont);
  GetCurrentConsoleFontEx(mHandle, FALSE, &mIniFont);
  mCurrentFont.cbSize = sizeof(mCurrentFont);
  mCurrentFont = mIniFont;
  //COORD fontSize = GetConsoleFontSize(mHandle, mIniFont.nFont);
}
#else
void Console::init(FILE *stream)
{
  mStream = stream;
  mForeColor = 0;
  mBackColor = 0;
  mBold = 21;
}
#endif

void Console::update()
{
#ifdef WIN32
  SetConsoleTextAttribute(mHandle, mForeColor | mBackColor | mForeIntensity | mBackIntensity);
  SetCurrentConsoleFontEx(mHandle, FALSE, &mCurrentFont);
#else
  std::stringstream ss;
  ss << "\x1B[" << mBold;
  if (mForeColor != 0)
    ss << ";" << mForeColor;
  if (mBackColor != 0)
    ss << ";" << mBackColor;
  ss << "m";
  fprintf(mStream, "%s", ss.str().c_str());
#endif
}

#ifdef TL_ENABLE_DEPRECATED_METHODS
Console &Console::getInstance()
{
  if (sObjConsole.get() == nullptr) {
    std::lock_guard<std::mutex> lck(Console::mtx);
    if (sObjConsole.get() == nullptr) {
      sObjConsole.reset(new Console());
    }
  }
  return *sObjConsole;
}

EnumFlags<MessageLevel> Console::getMessageLevel() const
{
  return sLevel;
}
#endif // TL_ENABLE_DEPRECATED_METHODS


/* ---------------------------------------------------------------------------------- */

Argument::Argument(const std::string &name, const std::string &description)
  : mName(name),
    mDescription(description),
    mShortName()
{

}

Argument::Argument(const char &shortName, const std::string &description)
  : mName(""),
    mDescription(description),
    mShortName(shortName)
{
}

Argument::Argument(const std::string &name, const char &shortName, const std::string &description)
  : mName(name),
    mDescription(description),
    mShortName(shortName)
{
}

Argument::Argument(const Argument &argument)
  : mName(argument.mName),
    mDescription(argument.mDescription),
    mShortName(argument.mShortName)
{
}

Argument::Argument(Argument &&argument) TL_NOEXCEPT
  : mName(std::move(argument.mName)),
    mDescription(std::move(argument.mDescription)),
    mShortName(std::move(argument.mShortName))
{
}

Argument::~Argument()
{
}

Argument &Argument::operator=(const Argument &arg)
{
  if (this != &arg){
    this->mName = arg.mName;
    this->mDescription = arg.mName;
    this->mShortName = arg.mShortName;
  }
  return *this;
}

Argument &Argument::operator = (Argument &&arg) TL_NOEXCEPT
{
  if (this != &arg){
    this->mName = std::move(arg.mName);
    this->mDescription = std::move(arg.mName);
    this->mShortName = std::move(arg.mShortName);
  }
  return *this;
}

/* ---------------------------------------------------------------------------------- */

Command::Command()
  : mName(""),
    mDescription(""),
    mCmdArgs(0),
    mVersion("0.0.0"),
    mExamples()
{
    init();
}

Command::Command(const Command &command)
  : mName(command.mName),
    mDescription(command.mDescription),
    mCmdArgs(command.mCmdArgs),
    mVersion(command.mVersion),
    mExamples(command.mExamples)
{

}

Command::Command(const std::string &name, const std::string &description)
  : mName(name),
    mDescription(description),
    mCmdArgs(0),
    mVersion("0.0.0"),
    mExamples()
{
  init();
}
  
Command::Command(const std::string &name, const std::string &description,
                 std::initializer_list<std::shared_ptr<Argument>> arguments)
  : mName(name),
    mDescription(description),
    mCmdArgs(arguments),
    mVersion("0.0.0"),
    mExamples()
{
}

Command::Status Command::parse(int argc, const char * const argv[])
{

  std::map<std::string, std::string> cmd_in;

  for (int i = 1; i < argc; ++i) {
    std::string arg_cmd_name = std::string(argv[i]);
    std::size_t found_name = arg_cmd_name.find("--");
    std::size_t found_short_name = arg_cmd_name.find("-");

    if (found_name != std::string::npos && found_name == 0) {
      arg_cmd_name = (argv[i])+2;
      /// argumento-valor separado por =
      std::vector<std::string> v;
      split(arg_cmd_name, v, "=");
      if(v.size() == 2){
        cmd_in[v[0]] = v[1];
        continue;
      }
    } else if (found_short_name != std::string::npos && found_short_name == 0) {
      arg_cmd_name = (argv[i])+1;
      if (arg_cmd_name.size() > 1) {
        /// Se da el caso de combinación de multiples opciones o
        /// parametro corto seguido de argumento
        /// Habría que ver si lo que sigue son todo nombres cortos
        bool check_combined = true;
        for (auto &opt : arg_cmd_name){
          bool bFind = false;
          for (auto &arg : mCmdArgs) {
            if (arg->shortName()){
              if (arg->shortName() == opt){
                bFind = true;
                break;
              }
            }
          }
          if (bFind == false) {
            /// Si no encuentra no es opción
            check_combined = false;
            break;
          }
        }

        if (check_combined){
          for (auto &opt : arg_cmd_name){
            std::stringstream ss;
            std::string short_name;
            ss << opt;
            ss >> short_name;
            cmd_in[short_name] = "true";
          }
        } else {
          std::string short_name = arg_cmd_name.substr(0, 1);
          std::string arg_value = arg_cmd_name.substr(1, arg_cmd_name.size()-1);
          cmd_in[short_name] = arg_value;
        }
        continue;
      }
    } else {
      continue;
    }

    std::string value;

    if (i+1 < argc) {
      /// Se comprueba si el elemento siguiente es un valor
      std::string arg_value = std::string(argv[i+1]);
      std::size_t found_next_name = arg_value.find("--");
      std::size_t found_next_short_name = arg_value.find("-");
      if ((found_next_name != std::string::npos  && found_next_name == 0) ||
          (found_next_short_name != std::string::npos && found_next_short_name == 0)){
        //value = "true";
      } else {
        value = arg_value;
        i++;
      }
    } else {
      //value = "true";
    }

    cmd_in[arg_cmd_name] = value;

  }

  std::map<std::string, std::string>::iterator it;
  if (cmd_in.find("h") != cmd_in.end() || cmd_in.find("help") != cmd_in.end()){
    showHelp();
    return Command::Status::show_help;
  }

  if (cmd_in.find("version") != cmd_in.end()){
    showVersion();
    return Command::Status::show_version;
  }

  if (cmd_in.find("licence") != cmd_in.end()){
    showLicence();
    return Command::Status::show_licence;
  }


  for (auto &arg : mCmdArgs) {
    bool bOptional = !arg->isRequired();
    bool bFind = false;
    bool bFindValue = false;

    std::stringstream ss;
    std::string short_name;
    ss << arg->shortName();
    ss >> short_name;
    if (cmd_in.find(short_name) != cmd_in.end()){
      bFind = true;
      std::string value = cmd_in.find(short_name)->second;
      if (value.empty()){
        if (arg->typeName() == "bool"){
          value = "true";
          bFindValue = true;
        }
      } else {
        bFindValue = true;
      }

      if (bFindValue)
        arg->fromString(value);

    } else if (cmd_in.find(arg->name()) != cmd_in.end()){
      bFind = true;
      std::string value = cmd_in.find(arg->name())->second;
      if (value.empty()){
        if (arg->typeName() == "bool"){
          value = "true";
          bFindValue = true;
        }
      } else {
        bFindValue = true;
      }

      if (bFindValue)
        arg->fromString(value);

    } else {
      bFind = false;
    }

    if (bFind == false && bOptional == false) {
      msgError("Missing mandatory argument: %s", arg->name().c_str());
      return Command::Status::parse_error;
    } else if (bFind == true && bFindValue == false) {
      msgError("Missing value for argument: %s", arg->name().c_str());
      return Command::Status::parse_error;
    } else if (!arg->isValid()){
      msgError("Invalid argument (%s) value", arg->name().c_str());
      return Command::Status::parse_error;
    }
  }

  return Command::Status::parse_success;
}

Command &Command::operator=(const Command &command)
{
  if (this != &command) {
    this->mName = command.mName;
    this->mDescription = command.mDescription;
    this->mCmdArgs = command.mCmdArgs;
    this->mVersion = command.mVersion;
  }
  return (*this);
}

Command &Command::operator=(Command &&command) TL_NOEXCEPT
{
  if (this != &command) {
    this->mName = std::move(command.mName);
    this->mDescription = std::move(command.mDescription);
    this->mCmdArgs = std::move(command.mCmdArgs);
    this->mVersion = std::move(command.mVersion);
  }
  return (*this);
}

void Command::showHelp() const
{

  /// Linux syntax
  TL_TODO("Solucion rapida. revisar")

  /// Uso
  Console &console = Console::instance();
  console.setConsoleForegroundColor(Console::Color::green, Console::Intensity::bright);
  console.setFontBold(true);
  printf("\nUsage: %s [OPTION...] \n\n", mName.c_str());
  console.reset();

  /// Descripción del comando
  printf("%s \n\n", mDescription.c_str());

  size_t max_name_size = 7;
  for (auto arg : mCmdArgs) {
    max_name_size = std::max(max_name_size, arg->name().size());
  }
  std::string name_tmpl = std::string("%s%-").append(std::to_string(max_name_size)).append("s %s %s");
  printf( "  -h, ");
  printf(name_tmpl.c_str(), "--", "help", "   ", "Display this help and exit\n");
  printf( "    , ");
  printf(name_tmpl.c_str(), "--", "version", "   ", "Output version information and exit\n");

  for (auto arg : mCmdArgs) {
    if (arg->shortName()){
      printf( "  -%c, ", arg->shortName());
    } else {
      printf( "    , ");
    }
    if (!arg->name().empty()){
      printf(name_tmpl.c_str(), "--", arg->name().c_str(), (arg->isRequired() ? "[R]" : "[O]"), arg->description().c_str());
    } else {
      printf(name_tmpl.c_str(), "  ", "", (arg->isRequired() ? "[R]" : "[O]"), arg->description().c_str());
    }
    printf("\n");
  }
  printf("\n\n");

  printf("R: Required argument\n");
  printf("O: Optional argument\n\n");


  console.setConsoleForegroundColor(Console::Color::green, Console::Intensity::bright);
  console.setFontBold(true);
  printf("Argument Syntax Conventions\n\n");
  console.reset();

  printf_s("  - Arguments are options if they begin with a hyphen delimiter (-).\n");
  printf_s("  - Multiple options may follow a hyphen delimiter in a single token if the options do not take arguments. ‘-abc’ is equivalent to ‘-a -b -c’.\n");
  printf_s("  - Option names are single alphanumeric characters.\n");
  printf_s("  - An option and its argument may or may not appear as separate tokens. ‘-o foo’ and ‘-ofoo’ are equivalent.\n");
  printf_s("  - Long options (--) can have arguments specified after space or equal sign (=).  ‘--name=value’ is equivalent to ‘--name value’.\n\n");

  if (!mExamples.empty()){
    console.setConsoleForegroundColor(Console::Color::green, Console::Intensity::bright);
    console.setFontBold(true);
    printf("Examples\n\n");
    console.reset();

    for (auto &example : mExamples){
      printf_s("  %s\n", example.c_str());
    }
  }
}

void Command::showVersion() const
{
  Console &console = Console::instance();
  console.setConsoleForegroundColor(Console::Color::green, Console::Intensity::bright);
  console.setFontBold(true);

  printf_s("Version: %s\n", mVersion.c_str());

  console.reset();
}

void Command::showLicence() const
{
  Console &console = Console::instance();
  console.setConsoleForegroundColor(Console::Color::green, Console::Intensity::bright);
  console.setFontBold(true);
}



void Command::init()
{

}


/* ---------------------------------------------------------------------------------- */

CommandList::CommandList()
  : mVersion("0.0.0")
{
}

CommandList::CommandList(const std::string &name, const std::string &description)
  : mName(name),
    mDescription(description),
    mVersion("0.0.0")
{
}

CommandList::CommandList(const CommandList &commandList)
  : mName(commandList.mName),
    mDescription(commandList.mDescription),
    mCommands(commandList.mCommands),
    mVersion(commandList.mVersion)
{
}

CommandList::CommandList(CommandList &&commandList) TL_NOEXCEPT
  : mName(std::move(commandList.mName)),
    mDescription(std::move(commandList.mDescription)),
    mCommands(std::move(commandList.mCommands)),
    mVersion(std::move(commandList.mVersion))
{
}

CommandList::CommandList(const std::string &name, const std::string &description,
                 std::initializer_list<std::shared_ptr<Command>> commands)
  : mName(name),
    mDescription(description),
    mCommands(commands),
    mVersion("0.0.0")
{
}

CommandList::Status CommandList::parse(int argc, const char * const argv[])
{
  if (argc < 1) return Status::parse_error;

  std::string arg_cmd_name = std::string(argv[1]);
  std::size_t found_name = arg_cmd_name.find("--");
  std::size_t found_short_name = arg_cmd_name.find("-");
  if (found_name != std::string::npos && found_name == 0) {
    arg_cmd_name = (argv[1])+2;
  } else if (found_short_name != std::string::npos && found_short_name == 0) {
    arg_cmd_name = (argv[1])+1;
  }

  if (arg_cmd_name.compare("h") == 0 || arg_cmd_name.compare("help") == 0){
    showHelp();
    return Status::show_help;
  }

  if (arg_cmd_name.compare("version") == 0){
    showVersion();
    return Status::show_version;
  }

  if (arg_cmd_name.compare("licence") == 0){
    showLicence();
    return Status::show_licence;
  }

  for (auto &command : mCommands){
    if(command->name().compare(arg_cmd_name) == 0){
      std::vector<char const*> cmd_argv;
      for (size_t i = 0; i < static_cast<size_t>(argc); ++i) {
        if (i != 1)
          cmd_argv.push_back(argv[i]);
      }
      Command::Status status = command->parse(argc-1, cmd_argv.data());
      if (status == Command::Status::parse_error) {
        return Status::parse_error;
      } else if (status == Command::Status::show_help) {
        return Status::show_help;
      } else if (status == Command::Status::show_licence) {
        return Status::show_licence;
      } else if (status == Command::Status::show_version) {
        return Status::show_version;
      }
    }
  }

  for (auto &command : mCommands){
    if(command->name().compare(arg_cmd_name) == 0){
      std::vector<char const*> cmd_argv;
      for (size_t i = 0; i < static_cast<size_t>(argc); ++i) {
        if (i != 1)
          cmd_argv.push_back(argv[i]);
      }
      Command::Status status = command->parse(argc-1, cmd_argv.data());
      if (status == Command::Status::parse_error) {
        return Status::parse_error;
      } else if (status == Command::Status::show_help) {
        return Status::show_help;
      } else if (status == Command::Status::show_licence) {
        return Status::show_licence;
      } else if (status == Command::Status::show_version) {
        return Status::show_version;
      }
    }
  }

  return Status::parse_error;
}

CommandList &CommandList::operator=(const CommandList &cmdList)
{
  if (this != &cmdList) {
    this->mName = cmdList.mName;
    this->mDescription = cmdList.mDescription;
    this->mCommands = cmdList.mCommands;
    this->mVersion = cmdList.mVersion;
  }
  return (*this);
}

CommandList &CommandList::operator=(CommandList &&cmdList) TL_NOEXCEPT
{
  if (this != &cmdList) {
    this->mName = std::move(cmdList.mName);
    this->mDescription = std::move(cmdList.mDescription);
    this->mCommands = std::move(cmdList.mCommands);
    this->mVersion = std::move(cmdList.mVersion);
  }
  return (*this);
}

void CommandList::showHelp() const
{

  Console &console = Console::instance();
  console.setConsoleForegroundColor(Console::Color::green, Console::Intensity::bright);
  console.setFontBold(true);
  printf("\nUsage: %s [--version] [-h | --help] [--licence] <command> [<args>] \n\n", mName.c_str());
  console.reset();

  printf("%s \n\n", mDescription.c_str());

  console.setConsoleForegroundColor(Console::Color::green, Console::Intensity::bright);
  console.setFontBold(true);
  printf("Command list: \n\n");
  console.reset();

  size_t max_name_size = 7;
  for (auto &arg : mCommands) {
    max_name_size = std::max(max_name_size, arg->name().size());
  }
  std::string name_tmpl = std::string("%-").append(std::to_string(max_name_size)).append("s %s\n");

  for (auto &arg : mCommands) {
    printf(name_tmpl.c_str(), arg->name().c_str(), arg->description().c_str());
  }

}

void CommandList::showVersion() const
{
  Console &console = Console::instance();
  console.setConsoleForegroundColor(Console::Color::green, Console::Intensity::bright);
  console.setFontBold(true);

  printf_s("Version: %s\n", mVersion.c_str());

  console.reset();
}

void CommandList::showLicence() const
{
  Console &console = Console::instance();
  console.setConsoleForegroundColor(Console::Color::green, Console::Intensity::bright);
  console.setFontBold(true);
}


/* ---------------------------------------------------------------------------------- */


std::mutex Progress::sMutex;

Progress::Progress() 
  : mProgress(0.), 
    mMinimun(0.), 
    mMaximun(100.), 
    mPercent(-1), 
    mMsg(""),
    onProgress(nullptr),
    onInitialize(nullptr),
    onTerminate(nullptr)
{
  updateScale();
}

Progress::Progress(double min, double max, const std::string &msg) 
  : mProgress(0.), 
    mMinimun(min), 
    mMaximun(max), 
    mPercent(-1), 
    mMsg(msg),
    onProgress(nullptr),
    onInitialize(nullptr),
    onTerminate(nullptr)
{
  updateScale();
}

bool Progress::operator()(double increment) 
{ 
  std::lock_guard<std::mutex> lck(Progress::sMutex);
  if (mProgress == 0.) initialize();
  mProgress += increment;
  int percent = TL_ROUND_TO_INT(mProgress * mScale);
  if (percent > mPercent) {
    mPercent = percent;
    updateProgress();
  }
  if (mProgress == mMaximun) terminate();
  return true;
}

void Progress::init(double min, double max, const std::string &msg)
{
  mMinimun = min;
  mMaximun = max;
  mMsg = msg;
  restart();
  updateScale();
}

void Progress::setMinimun(double min)
{
  mMinimun = min;
}

void Progress::setMaximun(double max)
{
  mMaximun = max;
}

void Progress::restart()
{
  mPercent = 0;
  mProgress = 0.;
}

void Progress::setOnProgressListener(std::function<void(double)> &progressFunction)
{
  *onProgress = progressFunction;
}

void Progress::setOnInitializeListener(std::function<void(void)> &initializeFunction)
{
  *onInitialize = initializeFunction;
}

void Progress::setOnTerminateListener(std::function<void(void)> &terminateFunction)
{
  *onTerminate = terminateFunction;
}

/* metodos protected*/

void Progress::initialize()
{
  printf_s("%s\n", mMsg.c_str());

  if (onInitialize) (*onInitialize)();
}

//void Progress::updateProgress() 
//{
//  if (onProgress) (*onProgress)(mPercent);
//}

void Progress::updateScale()
{
  mScale = 100./(mMaximun - mMinimun);
}

//void Progress::terminate()
//{
//  printf("\n");
//  if (onTerminate) (*onTerminate)();
//}


/* ---------------------------------------------------------------------------------- */

ProgressBar::ProgressBar(bool customConsole)
  : Progress(), 
    bCustomConsole(customConsole) 
{
}

ProgressBar::ProgressBar(double min, double max, bool customConsole)
  : Progress(min, max),
    bCustomConsole(customConsole) 
{
}

void ProgressBar::updateProgress() 
{
  if (onProgress == nullptr) {
    
    std::cout << "\r";

    Console &console = Console::instance();
    int posInBar = TL_ROUND_TO_INT(mPercent * mSize / 100.);

    int ini = mSize / 2 - 2;
    for (int i = 0; i < mSize; i++) {
      if (i < posInBar) {
        if (bCustomConsole) {
          console.setConsoleBackgroundColor(Console::Color::green);
        } else {
          std::cout << "#";
        }
      } else {
        if (bCustomConsole) {
          console.setConsoleBackgroundColor(Console::Color::yellow);
        } else {
          std::cout << "-";
        }
      }
      if (bCustomConsole) {
        int n;
        if (i == ini) {
          n = mPercent / 100 % 10;
          if ( n > 0 ) std::cout << n;
          else std::cout << " ";
        } else if (i == ini + 1) {
          n = mPercent / 10 % 10;
          if ( n > 0 || mPercent >= 10) std::cout << n;
          else std::cout << " ";
        } else if (i == ini + 2) {
          n = mPercent % 10;
          std::cout << n;
        } else if (i == ini + 3) {
          std::cout << "%";
        } else {
          std::cout << " ";
        }
      }
    }

    if (bCustomConsole) {
      console.reset();
    } else {
      std::cout << " " << mPercent << "%  completed" << std::flush;
    }
  } else {
    (*onProgress)(mPercent);
  }
}

void ProgressBar::terminate()
{
  if (onTerminate == nullptr)
    printf("\n");
  else 
    (*onTerminate)();
}

/* ---------------------------------------------------------------------------------- */

ProgressPercent::ProgressPercent(bool customConsole)
  : Progress(),
    bCustomConsole(customConsole) 
{
}

ProgressPercent::ProgressPercent(double min, double max, bool customConsole)
  : Progress(min, max), 
    bCustomConsole(customConsole) 
{
}

void ProgressPercent::updateProgress() 
{
  if (onProgress == nullptr) {
    std::cout << "\r";
    std::cout << " " << mPercent << "%  completed" << std::flush;
  } else
    (*onProgress)(mPercent);
}

void ProgressPercent::terminate()
{
  if (onTerminate == nullptr)
    printf("\n");
  else 
    (*onTerminate)();
}




/* ---------------------------------------------------------------------------------- */

#ifdef TL_ENABLE_DEPRECATED_METHODS

/* Deprecated class */

CmdArgument::CmdArgument(const char *name, const char *description, bool optional)
  : mName(name),
    mDescription(description),
    bOptional(optional)
{
}

const char *CmdArgument::getDescription() const
{
  return mDescription.c_str();
}

const char *CmdArgument::getName() const
{
  return mName.c_str();
}

bool CmdArgument::isOptional() const
{
  return bOptional;
}


/* ---------------------------------------------------------------------------------- */

CmdOption::CmdOption(const char *name, const char *description)
  : CmdArgument(name, description, true), mValue(false)
{
}

CmdArgument::Type CmdOption::getType() const
{
  return CmdArgument::Type::OPTION;
}

bool CmdOption::isActive() const
{
  return mValue;
}

void CmdOption::setActive(bool active)
{
  mValue = active;
}


/* ---------------------------------------------------------------------------------- */

CmdParameter::CmdParameter(const char *name, const char *description, bool optional, const char *defValue)
  : CmdArgument(name, description, optional), mValue(defValue)
{
}

CmdArgument::Type CmdParameter::getType() const
{
  return CmdArgument::Type::PARAMETER;
}

const char *CmdParameter::getValue() const
{
  return mValue.c_str();
}

void CmdParameter::setValue(const std::string &value)
{
  mValue = value;
}


/* ---------------------------------------------------------------------------------- */

CmdParameterOptions::CmdParameterOptions(const char *name, const char *options, const char *description, bool optional, const char *defValue)
  : CmdArgument(name, description, optional), mValue(defValue)
{
  split(options, mOptions, ",");
}

int CmdParameterOptions::getIndex() const
{
  for ( size_t i = 0; i < mOptions.size(); i++ ) {
    if (mOptions[i] == mValue) {
      return static_cast<int>(i);
      break;
    }
  }
  return 0;
}

int CmdParameterOptions::getIndex(const std::string &value) const
{
  for ( size_t i = 0; i < mOptions.size(); i++ ) {
    if (mOptions[i] == value) {
      return static_cast<int>(i);
      break;
    }
  }
  return 0;
}

std::vector<std::string> CmdParameterOptions::getOptions() const
{
  return mOptions;
}

CmdArgument::Type CmdParameterOptions::getType() const
{
  return CmdArgument::Type::PARAMETER_OPTIONS;
}

const char *CmdParameterOptions::getValue() const
{
  return mValue.c_str();
}

void CmdParameterOptions::setValue(const std::string &value)
{
  for (auto opt : mOptions) {
    if (value == opt) {
      mValue = value;
      break;
    }
  }
}

/* ---------------------------------------------------------------------------------- */

CmdParser::CmdParser()
  : mCmdName(""),
    mCmdDescription(""),
    mCmdArgs(0)
{
}

CmdParser::CmdParser(const char *name, const char *description)
  : mCmdName(name),
    mCmdDescription(description),
    mCmdArgs(0)
{
}

CmdParser::CmdParser(const char *name, const char *description, std::initializer_list<std::shared_ptr<CmdArgument>> cmd_args)
  : mCmdName(name),
    mCmdDescription(description),
    mCmdArgs(cmd_args)
{
}

void CmdParser::addParameter(const char *name, const char *description, bool optional, const char *defValue)
{
  mCmdArgs.push_back(std::make_shared<CmdParameter>(name, description, optional, defValue));
}


void CmdParser::addParameterOption(const char *name, const char *options, const char *description, bool optional, const char *defValue)
{
  mCmdArgs.push_back(std::make_shared<CmdParameterOptions>(name, options, description, optional, defValue));
}


void CmdParser::addOption(const char *name, const char *description)
{
  mCmdArgs.push_back(std::make_shared<CmdOption>(name, description));
}

CmdParser::Status CmdParser::parse(int argc, const char* const argv[])
{
  for (auto arg : mCmdArgs) {
    // Comando de ayuda
    if (argc > 1 && strcmp(argv[1], "-help") == 0) {
      printHelp();
      return CmdParser::Status::PARSE_HELP;
    }
    bool bOptional = arg->isOptional();
    std::string argName = (arg->getType() == CmdArgument::Type::OPTION) ? "-" : "--";
    argName += arg->getName();
    bool bFind = false;
    for (int i = 1; i < argc; ++i) {
      std::string arg_name = std::string(argv[i]);
      std::size_t found = arg_name.find(argName);
      if (found != std::string::npos) {
        if (arg_name == argName && arg->getType() == CmdArgument::Type::OPTION) {
          dynamic_cast<CmdOption *>(arg.get())->setActive(true);
          break;
        } else {
          std::size_t val_pos = arg_name.find("=",found);
          std::string name = arg_name.substr(0, val_pos);
          if (val_pos != std::string::npos && name == argName) {
            if (arg->getType() == CmdArgument::Type::PARAMETER) {
              std::string value = arg_name.substr(val_pos+1, arg_name.size() - val_pos);
              tl::replaceString(&value, "\"", "\\");
              dynamic_cast<CmdParameter *>(arg.get())->setValue(value);
              bFind = true;
              break;
            } else if (arg->getType() == CmdArgument::Type::PARAMETER_OPTIONS) {
              std::string value = arg_name.substr(val_pos+1, arg_name.size() - val_pos);
              dynamic_cast<CmdParameterOptions *>(arg.get())->setValue(value);
              bFind = true;
              break;
            }
          }
        }
      }
    }
    // Ver si no es opcional y devolver un error si no existe
    if (bFind == false && bOptional == false) {
      msgError("Falta %s. Parámetro obligatorio ", arg->getName());
      printHelp();
      return CmdParser::Status::PARSE_ERROR;
    }
  }
  return CmdParser::Status::PARSE_SUCCESS;
}

void CmdParser::printHelp()
{

  Console &console = Console::instance();

  console.setConsoleForegroundColor(Console::Color::GREEN, Console::Intensity::BRIGHT);
  console.setFontBold(true);
  //TODO: Solución rapida. modificar
  printf("%s: %s \n\n", mCmdName.c_str(), mCmdDescription.c_str());
  //printf_s("%s: %s \n", mCmdName.c_str(), mCmdDescription.c_str());

  console.setConsoleForegroundColor(Console::Color::WHITE, Console::Intensity::BRIGHT);
  console.setFontBold(false);

  printf("Listado de parámetros: \n\n");

  //TODO: Añadir automaticamente el valor por defecto
  for (auto arg : mCmdArgs) {
    std::string s_type, s_description;
    if (arg->getType() == CmdArgument::Type::OPTION) {
      s_type = "Opción";
      s_description = arg->getDescription();
    } else if (arg->getType() == CmdArgument::Type::PARAMETER) {
      s_type = "Parámetro";
      s_description = arg->getDescription();
    } else if (arg->getType() == CmdArgument::Type::PARAMETER_OPTIONS) {
      s_type = "Lista de opciones";
      s_description = arg->getDescription();
      s_description = ". Los valores posibles son: ";
      for (auto opt : dynamic_cast<CmdParameterOptions *>(arg.get())->getOptions()) {
        s_description += " ";
        s_description += opt;
      }
    } else continue;
     printf_s("- %s [%s | %s]: %s \n", arg->getName(), s_type.c_str(), (arg->isOptional() ? "O" : "R"), s_description.c_str());
    //printf_s("%s [%s | %s]: %s \n", arg->getName(), ((ArgType::OPTION == arg->getType())? "Option" : "Parameter"), (arg->isOptional() ? "O" : "R"), arg->getDescription().c_str());
  }
  printf_s("\nUso:\n\n");
  printf_s("%s", mCmdName.c_str());
  for (auto arg : mCmdArgs) {
    printf_s( " %s%s%s", ((CmdArgument::Type::OPTION == arg->getType())? "-" : "--"),
             arg->getName(), ((CmdArgument::Type::OPTION == arg->getType())? "" : "=[value]"));
  }
  printf_s("\n\n");
  //printf_s("\n\nPulse intro para continuar");
  //getchar();
}

bool CmdParser::hasOption(const std::string &option) const
{
  for (auto arg : mCmdArgs) {
    if (arg->getType() == CmdArgument::Type::OPTION) {
      if (arg->getName() == option) {
        return dynamic_cast<CmdOption *>(arg.get())->isActive();
      }
    }
  }
  return false;
}

/* End deprecated class */

#endif // TL_ENABLE_DEPRECATED_METHODS

/* ---------------------------------------------------------------------------------- */

} // End mamespace tl


