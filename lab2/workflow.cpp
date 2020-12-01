
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
    for(int i = 0; i < text.size(); i++) {
        fout << text[i] <<std::endl;
    }
    fout.close();
}


void IWorker::GrepBlock::executor (std::vector<std::string> &text){
    std::vector<std::string> newText;
    int j = 0;
    for(int i = 0; i < text.size(); i++) {
        if (std::string::npos != text[i].find(m_word)) {
            newText.push_back(text[i]);
            j++;
        }
    }
    text = newText;
}

void IWorker::SortBlock::executor (std::vector<std::string> &text) {
    std::sort(text.begin(), text.end());
}

void IWorker::ReplaceBlock::executor (std::vector<std::string> &text){
    for(int i = 0; i < text.size(); i++) {
        int pos = 0;
        pos = text[i].find(m_world1, pos);
        while (pos != std::string::npos) {
            text[i].replace(pos, m_world1.size(), m_world2);
            pos = text[i].find(m_world1, pos);
        }
    }
}


void IWorker::DumpBlock::executor (std::vector<std::string> &text) {
    std::ofstream fout(m_fileName);
    if (!fout.is_open()) {
        Validator("File can't open in function dump. Please, check your workflow");
    }
    for(int i = 0; i < text.size(); i++) {
        fout << text[i] << std::endl;
    }
    fout.close();
}

void IWorker::Block::executor (std::vector<std::string> &text) {
    for (int i = 0; i < m_queue.size(); i++){
        m_block[m_queue[i]]->executor(text);
    }
}
