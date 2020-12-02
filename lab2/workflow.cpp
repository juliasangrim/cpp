
#include "workflow.h"

IWorker::ReadFileBlock::ReadFileBlock (std::string &str) {
    m_fileName = str;
}


IWorker::WriteFileBlock::WriteFileBlock(std::string &str) {
    m_fileName = str;
}

IWorker::GrepBlock::GrepBlock(std::string &str) {
    m_word = str;
}

IWorker::ReplaceBlock::ReplaceBlock(std::string &str1, std::string &str2) {
    m_world1 = str1;
    m_world2 = str2;
}

IWorker::DumpBlock::DumpBlock(std::string &str) {
    m_fileName = str;
}

IWorker::Block::Block(std::map<int, std::shared_ptr<IWorker>> &block, std::vector<int> &queue) {
    m_block = block;
    m_queue = queue;
}



void IWorker::ReadFileBlock::executor (std::vector<std::string> &text){
    std::ifstream fin(m_fileName);
    if (!fin.is_open()) {
        Validator("File can't open in function readfile. Please, check your workflow");
    }
    std::string tmp;
    for (int i = 0; !fin.eof(); i++) {
        getline(fin, tmp);
        text.push_back(tmp);
    }
    fin.close();
}

void IWorker::WriteFileBlock::executor (std::vector<std::string> &text) {
    std::ofstream fout(m_fileName);
    if (!fout.is_open()) {
        Validator("File can't open in function writefile. Please, check your workflow");
    }
    for(auto & i : text) {
        fout << i <<std::endl;
    }
    fout.close();
}


void IWorker::GrepBlock::executor (std::vector<std::string> &text){
    std::vector<std::string> newText;
    int j = 0;
    for(auto & i : text) {
        if (std::string::npos != i.find(m_word)) {
            newText.push_back(i);
            j++;
        }
    }
    text = newText;
}

void IWorker::SortBlock::executor (std::vector<std::string> &text) {
    std::sort(text.begin(), text.end());
}

void IWorker::ReplaceBlock::executor (std::vector<std::string> &text){
    for(auto & i : text) {
        int pos = 0;
        pos = i.find(m_world1, pos);
        while (pos != std::string::npos) {
            i.replace(pos, m_world1.size(), m_world2);
            pos = i.find(m_world1, pos);
        }
    }
}


void IWorker::DumpBlock::executor (std::vector<std::string> &text) {
    std::ofstream fout(m_fileName);
    if (!fout.is_open()) {
        Validator("File can't open in function dump. Please, check your workflow");
    }
    for(auto & i : text) {
        fout << i << std::endl;
    }
    fout.close();
}

void IWorker::Block::executor (std::vector<std::string> &text) {
    for (int & i : m_queue){
        m_block[i]->executor(text);
    }
}
