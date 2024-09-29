#include "../SimpleLogger.h"
#include <iostream>

void testWriteToFile()
{
    SimpleLogger logger;
    logger.immediateMode(true);

    for (size_t i = 100; i < 200; i += 10)
    {
        logger.log("int:", i);
    }

    logger.writeToFile("simple.txt");
}

void testImmediateMode()
{
    SimpleLogger logger;
    logger.immediateMode(true);
    logger.setLogFile("immediate.txt", true);

    for (size_t i = 100; i < 200; i += 10)
    {
        logger.log("int:", i);
    }
}

void testDestroyMode()
{
    SimpleLogger logger;
    logger.writeOnDestroy(true);
    logger.setLogFile("destroy.txt", false);

    for (size_t i = 100; i < 200; i += 10)
    {
        logger.log("int:", i);
    }
}

int main()
{
    testWriteToFile();
    testImmediateMode();
    testDestroyMode();

    return 0;
}