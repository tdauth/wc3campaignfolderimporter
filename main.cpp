#include <iostream>

#include <StormLib.h>

using namespace std;

struct ImportFile {
    int fileFormatVersion;
    int numberOfImportedFiles;
};

enum class PathFlag : u8
{
    StandardPath = 5,
    StandardPath2 = 8,
    CustomPath = 10,
    CustomPath2 = 13
};

struct Data {
    PathFlag pathFlag;
    char*path;
};

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Missing parameter(s). Usage ./campaignimporter <campaign file> <import folder>" << std::endl;
        return 1;
    }

    const std::string campaignFile = argv[0];
    const std::string importFolder = argv[1];

    cout << "Hello World!" << endl;
    return 0;
}
