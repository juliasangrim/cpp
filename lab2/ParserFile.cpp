#include "ParserFile.h"

int ParserFile::parseFile(char *fileName) {
    int indexFunc;
    int idxRead = 0;
    int idxWrite = 0;
    std::map<int, std::shared_ptr<IWorker::IWorker>> block;
    std::vector<int> queue;
    std::ifstream fin(fileName);
    std::string part;
    if (!fin.is_open()) { //check file
        Validator("Wrong name Workflow file. Please check your workflow.");
    }
    std::string newLine;
    getline(fin, newLine);
    if (newLine != "desc") { //check existing desc
        Validator("There's no 'desc' in file. Please check your workflow.");
    }
    getline(fin, newLine);
    while (newLine != "csed") {
        auto ptrBlock= ParserFile::parseString(newLine, indexFunc, idxRead, idxWrite);
        auto error = block.find(indexFunc);//check repeating indexes
        if (error != block.end()) {
            Validator("Repeat index. Please check your workflow");
        }
        block[indexFunc] = ptrBlock;
        getline(fin, newLine);
    }
    if (fin.eof()) { //check existing queue
        Validator("There's no queue. Please check your workflow.");
    }
    getline(fin, newLine);
    queue = ParserFile::parseQueue(newLine);
    if  (queue[0] != idxRead) { //check the begin of queue
        Validator("Queue doesn't begin function readfile.  Please check your workflow.");
    }
    if (queue[queue.size() - 1] != idxWrite) { //check the end of queue
        Validator("Queue doesn't end function writefile.  Please check your workflow.");
    }

    //check queue
    for (int i = 1; i < queue.size() - 1; i++) {
        if ((queue[i] == idxRead) || (queue[i] == idxWrite)) { //check existing index of write and read in the middle
            Validator("Block write or read in the middle of queue.  Please check your workflow.");
        }
        auto error = block.find(queue[i]);//check existing index in workflow
        if (error == block.end()) {
            Validator("No such index in workflow. Please check your workflow");
        }
    }
    IWorker::Block work(block, queue);
    std::vector<std::string> text;
    work.executor(text);
    fin.close();
    return 0;

}

std::shared_ptr<IWorker::IWorker> ParserFile::parseString(std::string &string, int &indexFunc, int &idxRead, int &idxWrite) {
    std::string partString;
    std::string arg1;
    std::string arg2;
    std::istringstream stream(string);
    std::shared_ptr <IWorker::IWorker> blockError;
    stream >> partString;
    indexFunc = stoi(partString);
    if (indexFunc < 0) { //check index for negative value
        Validator("Negative index of function. Please check your workflow.");
    }
    stream >> partString;
    if (partString != "=") { //check for =
        Validator("There's no '='. Please check your workflow.");
    }
    stream >> partString;
    if (partString == "readfile") {
        idxRead = indexFunc;
        if (stream.eof()) {
            Validator("Not enough arguments for function readfile. Please check your workflow.");
        }
        stream >> arg1;
        if (!stream.eof()) {
            Validator("Too many arguments for function readfile. Please check your workflow.");
        }
        auto block = std::make_shared<IWorker::ReadFileBlock>(arg1);
        return block;
    }
    else if (partString == "writefile") {
        idxWrite = indexFunc;
        if (stream.eof()) {
            Validator("Not enough arguments for function writefile. Please check your workflow.");
        }
        stream >> arg1;
        if (!stream.eof()) {
            Validator("Too many arguments for function writefile. Please check your workflow.");
        }
        auto block = std::make_shared<IWorker::WriteFileBlock>(arg1);
        return block;
    }
    else if (partString == "grep") {
        if (stream.eof()) {
            Validator("Not enough arguments for function grep. Please check your workflow.");
        }
        stream >> arg1;
        if (!stream.eof()) {
            Validator("Too many arguments for function grep. Please check your workflow.");
        }
        auto block = std::make_shared<IWorker::GrepBlock>(arg1);
        return block;
    }
    else if (partString == "sort") {
        if (!stream.eof()) {
            Validator("Too many arguments for function sort. Please check your workflow.");
        }
        auto block = std::make_shared<IWorker::SortBlock>();
        return block;
    }
    else if (partString == "replace") {
        if (stream.eof()) {
            Validator("Not enough arguments for function replace(no arg 1 and arg 2). Please check your workflow.");
        }
        stream >> arg1 ;
        if (stream.eof()) {
            Validator("Not enough arguments for function replace(no arg 2). Please check your workflow.");
        }
        stream >> arg2;
        if (!stream.eof()) {
            Validator("Too many arguments for function replace. Please check your workflow.");
        }
        auto block = std::make_shared<IWorker::ReplaceBlock>(arg1, arg2);
        return block;
    } else if (partString == "dump"){
        if (stream.eof()) {
            Validator("Not enough arguments for function grep. Please check your workflow.");
        }
        stream >> arg1;
        if (!stream.eof()) {
            Validator("Too many arguments for function replace. Please check your workflow.");
        }
        auto block = std::make_shared<IWorker::DumpBlock>(arg1);
        return block;
    }
    Validator("There's no function with your name. Please check your workflow."); //if we find nothing we go here
    return blockError;
}

std::vector<int> ParserFile::parseQueue(std::string &string) {
    std::vector<int> queue;
    std::string partString;
    std::istringstream stream(string);
    while (!stream.eof()) {
        stream >> partString;
        if (partString == "->") {
            continue;
        }
        queue.push_back(stoi(partString));
    }
    return queue;
}

