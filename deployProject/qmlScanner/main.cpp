#include <fstream>
#include <iostream>
#include <algorithm>

#include <regex>
#ifndef NO_STD_FILESYSTEM
#include <filesystem>
namespace fs = std::filesystem;
#else
#include "ghc/filesystem.hpp"
namespace fs = ghc::filesystem;
#endif
char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}
int printHelp(){
    std::cout << "QML SCANNER OPTIONS "<< std::endl;
    std::cout << "qmlscanner -f INPUT_PROJECT_FOLDER  -q OUPUT_QML_FILE"<< std::endl;
    return 1;
}
int scanQmlDir2(const std::string &directory,const std::string &outputFile )
{
    std::vector<std::string> importList;
    std::regex re("^[ ]*import[ ]+[azA-Z]+");
    auto dirIt2=fs::recursive_directory_iterator(directory);
    for(auto& p: dirIt2){
        if(p.path().extension() == ".qml"){
            std::ifstream file (p.path());
            if (file.is_open())
            {
                std::string line;
                std::smatch match;
                while ( getline (file,line) )
                {
                    if (std::regex_search(line, match, re)){
                        importList.push_back(line);
                    }
                }
            }
        }
    }

    std::sort(importList.begin(), importList.end());
    importList.erase( unique( importList.begin(), importList.end() ), importList.end() );//remove duplicates

    //generate import template
    std::ofstream file (outputFile);
    if (file.is_open())
    {
        for (auto &line:importList) {
            file<<line << '\n';
        }
        file << "Item{}\n";
        if(importList.size()==0)return 1;
        else return 0;
    }
    return 1;
}


int main(int argc, char *argv[])
{
    char * filename = getCmdOption(argv, argv + argc, "-f");
    if (!filename) return printHelp();

    char * qmlFile = getCmdOption(argv, argv + argc, "-q");
    if (!qmlFile) return printHelp();
    std::string sfilename=filename;
    std::string sqmlFile=qmlFile;
#ifdef win32
    std::replace(sfilename.begin(), sfilename.end(), '/', '\\');
    std::replace(sqmlFile.begin(), sqmlFile.end(), '/', '\\');
#endif
	sfilename.erase(std::remove(sfilename.begin(), sfilename.end(), '\''),sfilename.end());
	sqmlFile.erase(std::remove(sqmlFile.begin(), sqmlFile.end(), '\''), sqmlFile.end());
	std::cout << sfilename << std::endl;
	std::cout << sqmlFile << std::endl;


    return scanQmlDir2(sfilename,sqmlFile);

}
