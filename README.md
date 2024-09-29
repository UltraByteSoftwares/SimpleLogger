# SimpleLogger

A simple header-only logger class for C++.

## Usage

```c++
// Create a SimpleLogger instance
SimpleLogger logger;

// Log any printable datatype, be it string, int, double etc.
logger.log("A simple message");
logger.log(1024);
logger.log("A tag and the message:", 26.0);

// Write the logs to a file
logger.writeToFile("file.log");

// Clear the all the logs
logger.clear();
```

## Features

### Destroy mode

Write logs to a file on destruction of `SimpleLogger` instance

```c++
// A log file must be set to be able to write on destruction
logger.setLogFile("file.log", false);
logger.writeOnDestroy(true);
```
### Immediate mode

Write logs to a file on every call to `log()`. This can be slow but can be helpful when investigating crashes.

```c++
// A log file must be set for immediate mode
logger.setLogFile("file.log", true);
logger.immediateMode(true);
```

### Write logs to any stream

The stream can be `std::cout`, `std::stringstream`, `std::ofstream` or just any stream derived from `std::ostream`

```c++
// To print to console (std::cout)
logger.write(std::cout);

// To print to a stringstream
std::stringstream ss;
logger.write(ss);
```
