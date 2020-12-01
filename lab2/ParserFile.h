#ifndef WORKFLOW_PARSERFILE_H
#define WORKFLOW_PARSERFILE_H

#include "workflow.h"

class IParser{
public:virtual ~IParser() = default;
};

class ParserFile : public IParser{
private:
    static std::shared_ptr<IWorker::IWorker>
    parseString(std::string &string, int &numberFunction, int &idxRead, int &idxWrite);

    static std::vector<int> parseQueue(std::string &string);

public:
    static int parseFile(char *fileName);
};

#endif //WORKFLOW_PARSERFILE_H
