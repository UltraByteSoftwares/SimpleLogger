#ifndef SIMPLELOGGER_H
#define SIMPLELOGGER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

/**
 * A simple class to log messages.
 *
 * Usage example:
 * SimpleLogger logger;
 * 
 * logger.log("A simple string");
 * logger.log(1024);
 * logger.log("A tag with integer:", 26);
 * logger.log("A tag with double:", 20.5);
 */
class SimpleLogger
{
public:
    /**
    * @brief Instantiate a logger.
    * 
    * By default, logging is turned ON. You can turn logging
    * ON or OFF with setLogging() method
    */
    SimpleLogger() : _isLogging(true), _immediateMode(false),
        _writeOnDestroy(false), _appendToFile(false)
    {}

    ~SimpleLogger()
    {
        if (writeOnDestroy() && !_fileName.empty())
            writeToFile(_fileName, _appendToFile);
    }

    /**
    * @brief Set a log file to write the logs to during immediate
    * mode or on destruction.
    * 
    * @param[in] fileName File to write logs to
    * @param[in] append Whether the contents should be appended to
    * the file represented by fileName
    */
    void setLogFile(const std::string& fileName, bool append)
    {
        _fileName = fileName;
        _appendToFile = append;
    }

    /**
    * @brief Check whether the logger is logging.
    * @return true if logging, false otherwise
    */
    bool logging() const
    {
        return _isLogging;
    }

    /**
    * @brief Turn logging on or off.
    *
    * @param[in] option true to turn ON logging
    */
    void logging(bool option)
    {
        _isLogging = option;
    }

    /**
    * @brief Check whether immediate mode is ON.
    * 
    * @return true if immediate mode is ON
    */
    bool immediateMode() const
    {
        return _immediateMode;
    }

    /**
    * @brief Turn immediate mode ON or OFF.
    * 
    * In immediate mode, log messages are written to file as
    * soon as they are logged. A log file must be set by calling
    * setLogFile() prior to turning immediate mode ON. Although 
    * writing logs to file everytime can be slow but can be useful 
    * for investigating crashes.
    * 
    * @param[in] mode true to turn ON immediate mode
    */
    void immediateMode(bool option)
    {
        _immediateMode = option;
    }

    /**
    * @brief Check if logs would be written to file when logger instance 
    * is destroyed.
    * 
    * @return true if logs will be written to file on destruction
    */
    bool writeOnDestroy() const
    {
        return _writeOnDestroy;
    }

    /**
    * @brief Write logs to a file on when logger instance is destroyed.
    * 
    * Call setLogFile() method to set the file where the logs would be
    * written on destruction
    * 
    * @param[in] option true to write logs to a file on destruction
    */
    void writeOnDestroy(bool option)
    {
        _writeOnDestroy = option;
    }

    /**
    * @brief Log a message.
    * 
    * Any printable data can be logged as message, be it string, int,
    * double etc.
    * 
    * @param[in] message Any printable datatype or object
    */
    template <typename T>
    void log(const T& message)
    {
        if (!_isLogging)
            return;

        std::stringstream ss;
        ss << message;

        _messages.push_back(ss.str());

        if (_immediateMode && !_fileName.empty())
        {
            std::ios::openmode mode = _appendToFile ? std::ios::app : std::ios::out;
            std::ofstream ofs(_fileName, mode);
            if (ofs.is_open())
                ofs << ss.str() << "\n";
        }
    }

    /**
    * @brief Log a message along with a tag.
    * 
    * The tag will appear before the message
    * 
    * @param[in] tag A tag to identify a message
    * @param[in] message Any printable datatype or object
    */
    template <typename T>
    void log(const std::string& tag, const T& message)
    {
        if (!_isLogging)
            return;

        std::stringstream ss;
        ss << tag << " " << message;

        log<std::string>(ss.str());
    }

    /**
    * @brief Write to any ostream object.
    * 
    * This can be used to write to any stream like stringstream,
    * std::cout, fstream etc. Log entries are separated by new lines
    * 
    * @param[in] stream any ostream derived object
    */
    void write(std::ostream& stream) const
    {
        for (const auto& msg : _messages)
        {
            stream << msg << "\n";
        }
    }

    /**
    * @brief Write the log to a file.
    * 
    * @param[in] fileName Name of the file to write logs to
    * @param[in] append Append to the file represented by fileName
    */
    void writeToFile(const std::string& fileName, bool append = false) const
    {
        std::ios::openmode mode = append ? std::ios::app : std::ios::out;

        std::ofstream ofs(fileName, mode);

        if (ofs.is_open())
            write(ofs);
    }

    /**
    * @brief Clear all logs.
    */
    void clear()
    {
        _messages.clear();
    }

private:
    std::vector<std::string> _messages;
    std::string _fileName;
    bool _isLogging;
    bool _immediateMode;
    bool _writeOnDestroy;
    bool _appendToFile;
};

#endif // SIMPLELOGGER_H

