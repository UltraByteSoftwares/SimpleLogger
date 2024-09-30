# SimpleLogger

A simple header-only logger class for C++. Just add *SimpleLogger.h* to your project and `#include "SimpleLogger.h"` in your file.

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

// Clear all the logs
logger.clear();
```

## Features

### Write on destruction

Write logs to a file on destruction of `SimpleLogger` instance

```c++
// A log file must be set to be able to write on destruction
logger.setLogFile("file.log", false);
logger.writeOnDestroy(true);
```
### Write immediately

Write logs to a file on every call to `log()`. This can be slow but can be helpful when investigating crashes.

```c++
// A log file must be set for immediate mode
logger.setLogFile("file.log", true);
logger.immediateMode(true);
```

### Write to any stream

The stream can be `std::cout`, `std::stringstream`, `std::ofstream` or just any stream derived from `std::ostream`

```c++
// To print to console (std::cout)
logger.write(std::cout);

// To print to a stringstream
std::stringstream ss;
logger.write(ss);
```

### Block/unblock logging at any time

```c++
// Block logging
logger.logging(false);

// Unblock logging
logger.logging(true);
```
