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
bool  getCmdFlag(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end )
    {
        return true;
    }
    return false;
}

int printHelp(){
    std::cout << "QML SCANNER OPTIONS "<< std::endl;
    std::cout << "qmlscanner -f INPUT_PROJECT_FOLDER  -d DEPLOY_FOLDER -z RELEASE_ZIP_FILE -p PROJECTNAME -r release|debug" << std::endl;
    return 1;
}


bool scanQmlDir(const std::string &directory,const std::string &outputFile )
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
                        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end()); //eliminar saltos de linea
                        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); //eliminar saltos de linea
                        importList.push_back(line);
                    }
                }
            }
        }
    }

    std::sort(importList.begin(), importList.end());

    importList.erase( std::unique( importList.begin(), importList.end() ), importList.end() );//remove duplicates


    //generate import template
    std::ofstream file (outputFile);
    if (file.is_open())
    {
        for (auto &line:importList) {

            file<<line << '\n';
        }
        file << "Item{}\n";
        if(importList.size()==0)return false;
        else return true;
    }
    return false;
}

void stringNormalize(std::string &str){

#ifdef WIN32
    std::replace(str.begin(), str.end(), '/', '\\');
#endif
    str.erase(std::remove(str.begin(), str.end(), '\''),str.end());
}

int copyLibs(const std::string &originDirectory,const std::string &destDirectory )
{
    int copiedFiles=0;
    auto dirIt2=fs::directory_iterator(originDirectory);
    for(auto& p: dirIt2){
        if(p.path().extension() == ".a"){
            auto libprivateOri=p.path();

            std::string libprivateDest=destDirectory;
            stringNormalize(libprivateDest);

            std::error_code ec;
            fs::copy(libprivateOri,libprivateDest,ec);

            if(ec.value()) {
                std::cerr<<"ERROR COPY LIB "<<libprivateOri<<" --> "<<libprivateDest <<" "<<ec.message()<<std::endl;
            }
            else {
                std::cout << "COPY LIBS " << libprivateOri << " --> " << libprivateDest << std::endl;
                copiedFiles++;
            }


        }

    }

#ifdef WIN32
    if(copiedFiles==0){
        for(auto& p: dirIt2){
            if(p.path().extension() == ".lib"){
                auto libprivateOri=p.path();

                std::string libprivateDest=destDirectory;
                stringNormalize(libprivateDest);

                std::error_code ec;
                fs::copy(libprivateOri,libprivateDest,ec);
                if(ec.value()) {
                    std::cerr<<"ERROR COPY "<<libprivateOri<<" --> "<<libprivateDest <<" "<<ec.message()<<std::endl;
                }else copiedFiles++;
            }
        }
    }
#endif

return copiedFiles;
}





int main(int argc, char *argv[])
{

    try{
        char * projectFolderName = getCmdOption(argv, argv + argc, "-f");
        if (!projectFolderName) return printHelp();


        char * dFolder = getCmdOption(argv, argv + argc, "-d");
        if (!dFolder) return printHelp();

        char * zFile = getCmdOption(argv, argv + argc, "-z");
        if (!zFile) return printHelp();

        char * cprojectName= getCmdOption(argv, argv + argc, "-p");
        if (!cprojectName) return printHelp();

        char * releaseMode= getCmdOption(argv, argv + argc, "-r");
        if (!releaseMode) return printHelp();
        std::string isRelease(releaseMode);
#ifdef WIN32
        bool release=false;
        if(isRelease=="release")release=true;
#endif

        bool verbose =getCmdFlag(argv, argv + argc, "-v");



        std::string sprojectFolderName=std::string(projectFolderName);
        stringNormalize(sprojectFolderName);

        std::string sprivateprojectFolderName=std::string(projectFolderName)+"/privateProject/";
        stringNormalize(sprivateprojectFolderName);

        std::string sqmlFile=sprojectFolderName+"/main/autogeneratedIncludes.qml";

        stringNormalize(sqmlFile);

        std::string destinationFolder=dFolder;
        stringNormalize(destinationFolder);

        std::string zipFile=zFile;

        stringNormalize(zipFile);

        std::string projectName=cprojectName;
        stringNormalize(projectName);




        std::ofstream outfile ("deployProject.txt");


        std::cout<<"STARTING PROJECT DEPLOY "<<projectFolderName<<" -> "<<destinationFolder<<std::endl;
        outfile<<"STARTING PROJECT DEPLOY "<<projectFolderName<<" -> "<<destinationFolder<<std::endl;

        //SCAM QML PROJECT DEPENDECIES
        if(!scanQmlDir(sprivateprojectFolderName,sqmlFile)) {
            std::cerr<<"ERROR IN QML SCANDIR "<<sprivateprojectFolderName<<" -> "<<sqmlFile<<std::endl;
            outfile<<"ERROR IN QML SCANDIR "<<sprivateprojectFolderName<<" -> "<<sqmlFile<<std::endl;
            return EXIT_FAILURE;
        }


        if(verbose){
            std::cout<<" QML SCANDIR "<<sprivateprojectFolderName<<" -> "<<sqmlFile<<std::endl;
            outfile<<" QML SCANDIR "<<sprivateprojectFolderName<<" -> "<<sqmlFile<<std::endl;
        }

        //REMOVE PREVIOUS .ZIP FILE
        if(fs::exists(zipFile)){
            if(!fs::remove(zipFile)){
                std::cerr<<"ERROR DELETING ZIP FILE "<<zipFile<<std::endl;
                outfile<<"ERROR DELETING ZIP FILE "<<zipFile<<std::endl;
                return EXIT_FAILURE;
            }
            if(verbose){
                std::cout <<zipFile<<" REMOVED"<<std::endl;
                outfile<<zipFile<<" REMOVED"<<std::endl;
            }
        }



        //REMOVE DEPLOY DEST FOLDER
        std::string deployFolder=destinationFolder+"/"+projectName+"/";
        stringNormalize(deployFolder);
        auto ret=fs::remove_all(deployFolder);
        if(verbose){
            std::cout << "REMOVED FOLDER "<<deployFolder<<" "<<ret<<std::endl;
            outfile<< "REMOVED FOLDER "<<deployFolder<<" "<<ret<<std::endl;
        }



        //CREATE DEPLOY DEST FOLDER
        {
            std::string subfolder1=deployFolder+"/publicLibs";
            stringNormalize(subfolder1);

            std::string subfolder2=deployFolder+"/main";
            stringNormalize(subfolder2);


            std::string ori=sprojectFolderName +"/publicLibs/";
            stringNormalize(ori);

            if(fs::exists(ori)){
                if(!fs::create_directories(subfolder1)) {
                    std::cerr<<"ERROR CREATING DIRECTORY "<<subfolder1<<std::endl;
                    outfile<<"ERROR CREATING DIRECTORY "<<subfolder1<<std::endl;
                    return EXIT_FAILURE;
                }
                if(verbose){
                    std::cout<<"CREATING DIRECTORY "<<subfolder1<<std::endl;
                    outfile<<"CREATING DIRECTORY "<<subfolder1<<std::endl;
                }
            }else{
                if(verbose){
                    std::cout<<"SKIPPING DIRECTORY "<<ori<<std::endl;
                    outfile<<"SKIPPING DIRECTORY "<<ori<<std::endl;
                }
            }
            if(!fs::create_directories(subfolder2)) {
                std::cerr<<"ERROR CREATING DIRECTORY "<<subfolder2<<std::endl;
                outfile<<"ERROR CREATING DIRECTORY "<<subfolder2<<std::endl;
                return EXIT_FAILURE;
            }
            if(verbose){
                std::cout<<"CREATING DIRECTORY "<<subfolder2<<std::endl;
                outfile<<"CREATING DIRECTORY "<<subfolder2<<std::endl;
            }

        }



        //COPY PRIVATE LIBRARY
        {
            std::error_code ec;
            std::string libprivateOri=destinationFolder +"/privateProject/libprivateProject.a";
            stringNormalize(libprivateOri);
            std::string libprivateDest=deployFolder+"/main/libprivateProject.a";
            stringNormalize(libprivateDest);
            bool tryCopyLib=false;
#ifdef WIN32
            std::string libprivateOri1= destinationFolder +"\\privateProject\\" + (release?"release\\":"debug\\")   +  "privateProject.lib";
            stringNormalize(libprivateOri1);
            std::string libprivateDest1=deployFolder+"/main/privateProject.lib";
            stringNormalize(libprivateDest1);

            std::string libprivateOri2= destinationFolder +"/privateProject/" + (release?"release/":"debug/")   +  "libprivateProject.a";
            stringNormalize(libprivateOri2);
            std::string libprivateDest2=deployFolder+"/main/libprivateProject.a";
            stringNormalize(libprivateDest2);

            if(fs::exists(libprivateOri1)){
                fs::copy(libprivateOri1,libprivateDest1,ec);
                tryCopyLib=true;
            }
            else if(fs::exists(libprivateOri2)){
                fs::copy(libprivateOri2,libprivateDest2,ec);
                tryCopyLib=true;
            }
            else
#endif
                if(fs::exists(libprivateOri)) {
                    fs::copy(libprivateOri,libprivateDest,ec);
                    tryCopyLib=true;
                }


            if(!tryCopyLib || ec.value()) // TRY TO COPY OTHER LIBRARIES
            {
                std::string libprivateOriFolder=destinationFolder +"/privateProject/release";
                if(!fs::exists(libprivateOriFolder)) libprivateOriFolder=destinationFolder +"/privateProject/";

                stringNormalize(libprivateOriFolder);
                std::string libprivateDestFolder=deployFolder+"/main/";
                stringNormalize(libprivateDestFolder);
                //try copilibs
                auto copied=copyLibs(libprivateOriFolder,libprivateDestFolder);
                if(copied==0){
                    std::cerr<<"ERROR COPY LIBS "<<libprivateOriFolder<<" --> "<<libprivateDestFolder <<" "<<ec.message()<<std::endl;
                    outfile<<"ERROR COPY LIBS "<<libprivateOriFolder<<" --> "<<libprivateDestFolder <<" "<<ec.message()<<std::endl;
                    return EXIT_FAILURE;
                }else {
                    if(verbose){
                        std::cout<<"COPIED "<<copied<<" "<<libprivateOriFolder<<" --> "<<libprivateDestFolder <<std::endl;
                        outfile<<"COPIED "<<copied<<" "<<libprivateOriFolder<<" --> "<<libprivateDestFolder<<std::endl;
                    }

                }
            }
            if(verbose && !ec.value()){
                std::cout<<"COPY "<<libprivateOri<<" --> "<<libprivateDest <<std::endl;
                outfile<<"COPY "<<libprivateOri<<" --> "<<libprivateDest <<std::endl;
            }
        }



        {
            std::string ori=sprojectFolderName +"/privateProject/privateProjectQtModules.pri";
            stringNormalize(ori);

            std::string dest=deployFolder+"/main/privateProjectQtModules.pri";
            stringNormalize(dest);
            std::error_code ecCode;
            fs::copy(ori,dest,ecCode);
            if(ecCode.value()) {
                std::cerr<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                outfile<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                return EXIT_FAILURE;

            }
            if(verbose){
                std::cout<<"COPY "<<ori<<" --> "<<dest <<std::endl;
                outfile<<" COPY "<<ori<<" --> "<<dest <<std::endl;
            }
        }



        {
            std::string ori=sprojectFolderName +"/privateProject/main.h";
            stringNormalize(ori);

            std::string dest=deployFolder+"/main/main.h";
            stringNormalize(dest);
            std::error_code ecCode;
            fs::copy(ori,dest,ecCode);
            if(ecCode.value()) {
                std::cerr<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                outfile<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                return EXIT_FAILURE;

            }
            if(verbose){
                std::cout<<"COPY "<<ori<<" --> "<<dest<<std::endl;
                outfile<<" COPY "<<ori<<" --> "<<dest<<std::endl;
            }
        }



        {
            std::string ori=sprojectFolderName +"/config.pri";
            stringNormalize(ori);

            std::string dest=deployFolder+"/main/config.pri";
            stringNormalize(dest);
            std::error_code ecCode;
            fs::copy(ori,dest,ecCode);
            if(ecCode.value()) {
                std::cerr<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                outfile<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                return EXIT_FAILURE;
            }
            if(verbose){
                std::cout<<"COPY "<<ori<<" --> "<<dest<<std::endl;
                outfile<<" COPY "<<ori<<" --> "<<dest <<std::endl;
            }
        }



        {
            std::string ori=sprojectFolderName +"/main/";
            stringNormalize(ori);

            std::string dest=deployFolder+"/main/";
            stringNormalize(dest);
            std::error_code ecCode;
            const auto copyOptions = fs::copy_options::update_existing
                    | fs::copy_options::recursive;
            fs::copy(ori,dest,copyOptions,ecCode);
            if(ecCode.value()) {
                std::cerr<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                outfile<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                return EXIT_FAILURE;
            }
            if(verbose){
                std::cout<<"RCOPY "<<ori<<" --> "<<dest <<std::endl;
                outfile<<" COPY "<<ori<<" --> "<<dest <<std::endl;
            }
        }



        {
            std::string ori=sprojectFolderName +"/publicLibs/";
            stringNormalize(ori);
            if(fs::exists(ori)){
                std::string dest=deployFolder+"/publicLibs/";
                stringNormalize(dest);
                std::error_code ecCode;
                const auto copyOptions = fs::copy_options::update_existing
                        | fs::copy_options::recursive;
                fs::copy(ori,dest,copyOptions,ecCode);
                if(ecCode.value()) {
                    std::cerr<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                    outfile<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                    return EXIT_FAILURE;

                }
                if(verbose){
                    std::cout<<"COPY "<<ori<<" --> "<<dest <<std::endl;
                    outfile<<" COPY "<<ori<<" --> "<<dest <<std::endl;
                }
            }else{
                if(verbose){
                    std::cout<<"SKIPPING DIRECTORY "<<ori<<std::endl;
                    outfile<<"SKIPPING DIRECTORY "<<ori<<std::endl;
                }
            }
        }


        {
            std::string ori=sprojectFolderName +"/deployProject/subdirsTemplate.pro";
            stringNormalize(ori);

            std::string dest=deployFolder+"/" +projectName+".pro";
            stringNormalize(dest);
            std::error_code ecCode;
            fs::copy(ori,dest,ecCode);
            if(ecCode.value()) {
                std::cerr<<"ERROR COPY "<<ori<<" --> "<<dest << " "<<ecCode.message()<<std::endl;
                outfile<<"ERROR COPY "<<ori<<" --> "<<dest <<" "<<ecCode.message()<<std::endl;
                return EXIT_FAILURE;

            }
            if(verbose){
                std::cout<<"COPY "<<ori<<" --> "<<dest <<std::endl;
                outfile<<" COPY "<<ori<<" --> "<<dest <<std::endl;
            }
        }


        std::cout<<"DONE"<<std::endl;
        outfile<<"DONE" <<std::endl;

    }catch(const std::exception &e){
        std::cerr<<"ERROR EXCEPTION "<<e.what()<<std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
