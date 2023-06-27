#include "FileIO.h"


namespace Twili {
    std::string getFilePath()
    {
        return std::filesystem::current_path().string();
    }
}
