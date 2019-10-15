#include <iostream>
#include <filesystem>

#include <StormLib.h>

using namespace std;
namespace fs = std::filesystem;

struct ImportFileHeader {
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

void addFilesFromDirectory(HANDLE *mpqArchive, const string &importFolder) {
    for (const auto & entry : fs::directory_iterator(importFolder)) {
           cout << entry.path() << endl;
    }
    // TODO Add each file recursively keeping the relative path to the import folder but adding it into the folder "war3campaignImported\"
  // bool   WINAPI SFileAddFile(HANDLE hMpq, const TCHAR * szFileName, const char * szArchivedName, DWORD dwFlags);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Missing parameter(s). Usage ./campaignimporter <campaign file> <import folder>" << std::endl;
        return 1;
    }

    const std::string campaignFile = argv[0];
    const std::string importFolder = argv[1];

    HANDLE mpqArchive;

    if (!SFileOpenArchive(campaignFile.c_str(), 0, 0, &mpqArchive)) {
        std::cerr << "Failed to open MPQ archive " << campaignFile << std::endl;
        return 1;
    }

    if (SFileHasFile(&mpqArchive, "war3campaign.imp")) {
        HANDLE importFile;

       if (!SFileOpenFileEx(&mpqArchive, "war3campaign.imp", 0, &importFile)) {
           SFileCloseArchive(&mpqArchive);
            std::cerr << "Failed to open war3campaign.imp file inside of campaign file " << campaignFile << std::endl;
           return 1;

       }
       DWORD fileSizeHigh = 0;
        DWORD fileSize = SFileGetFileSize(importFile, &fileSizeHigh);
        LONG filePosHigh = 0;
        DWORD filePointer = SFileSetFilePointer(importFile, 0, &filePosHigh, 0);

        char buffer[fileSize];

        if (!SFileReadFile(importFile,buffer, fileSize, &fileSizeHigh, 0)) {
             SFileCloseArchive(&mpqArchive);
            std::cerr << "Failed read content of war3campaign.imp file inside of campaign file " << campaignFile << std::endl;
           return 1;
        }


       if (!SFileCloseFile(importFile)) {
           std::cerr << "Failed close file war3campaign.imp inside of campaign file " << campaignFile << std::endl;
          return 1;
       }

       // TODO read the file header and the existing file
    }

    addFilesFromDirectory(&mpqArchive, importFolder);


    SFileCloseArchive(&mpqArchive);

    return 0;
}
