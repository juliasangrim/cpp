#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Validator.h"

#ifndef WORKFLOW_WORKFLOW_H
#define WORKFLOW_WORKFLOW_H

namespace IWorker {
    class IWorker {
    public:
        virtual ~IWorker() = default;
        virtual void executor(std::vector<std::string> &text) = 0;
    };

    class ReadFileBlock : public IWorker {
    private:
        std::string m_fileName;
    public:
        ReadFileBlock(std::string &str);
        void executor(std::vector<std::string> &text) override;
    };

    class WriteFileBlock : public IWorker {
    private:
        std::string m_fileName;
    public:
        WriteFileBlock(std::string &str);
        void executor(std::vector<std::string> &text) override;
    };

    class GrepBlock : public IWorker {
    private:
        std::string m_word;
    public:
        GrepBlock(std::string &str);
        void executor(std::vector<std::string> &text) override;
    };

    class SortBlock : public IWorker {
    public:
        void executor(std::vector<std::string> &text) override;
    };

    class ReplaceBlock : public IWorker {
    private:
        std::string m_world1;
        std::string m_world2;
    public:
        ReplaceBlock(std::string &str1, std::string &str2);
        void executor(std::vector<std::string> &text) override;
    };

    class DumpBlock : public IWorker {
    private:
        std::string m_fileName;
    public:
        DumpBlock(std::string &str);
        void executor(std::vector<std::string> &text) override;
    };


    class Block : public IWorker {
    private:
        std::map<int, std::shared_ptr<IWorker>> m_block;
        std::vector<int> m_queue;
    public:
        Block(std::map<int, std::shared_ptr<IWorker>> &block, std::vector<int> &queue);

        void executor(std::vector<std::string> &text) override;
    };
}
#endif //WORKFLOW_WORKFLOW_H
