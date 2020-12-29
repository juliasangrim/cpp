#ifndef CSV_CSVPARSER_H
#define CSV_CSVPARSER_H

#include "ParserException.h"
#include "printTuple.h"
namespace Parser {
    ////////PARSER////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename ... Arg>
    class CSVParser {
    private:
        std::ifstream &_input;
        int _idxBegin;
        char _columnDelim;
        char _lineDelim;
        char _fieldDelim;
    public:
        ////////ITERATOR////////////////////////////////////////////////////////////////////////////////////////////////////////////
        class CSVIterator {
        private:
            CSVParser<Arg...> &_csvParser;
            std::string _str;
            int _index;
            std::vector<std::string> _parsedLine;
            std::vector<int> _pos;
            int _currIndex = 0;
        public:
            CSVIterator(int idx, CSVParser<Arg ...> &parse);
            void getIndexLine();
            CSVIterator operator++();
            bool operator ==(CSVIterator secondIterator);
            bool operator !=(CSVIterator secondIterator);
            std::tuple<Arg...> operator *();
            void parseLine ();
            std::tuple<Arg...>vectorIntoTuple();
        };
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        explicit CSVParser(std::ifstream &file, int index = 0, char columnDelim = ',',char lineDelim = '\n', char fieldDelim = '"');
        std::string getLine();
        int getSize();
        char getColumnDelim();
        char getFieldDelim();
        void changePosition();
        CSVIterator begin();
        CSVIterator end();
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////CSVIterator methods////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename ... Arg>
    CSVParser<Arg...>::CSVIterator::CSVIterator(int idx, CSVParser<Arg ...> &parse) : _index(idx), _csvParser(parse) {
        this->getIndexLine();
    }

    template<typename ... Arg>
    void CSVParser<Arg...>::CSVIterator::getIndexLine() {
        int tmpSize = _csvParser.getSize();
        _csvParser.changePosition();
        if (_index <= tmpSize) //TODO indexation
        for (auto i = 0; i < _index; ++i) {
            _str = _csvParser.getLine();
        }
        else {
            _str = "";
        }
    }

    template<typename ... Arg>
    typename CSVParser<Arg...>::CSVIterator CSVParser<Arg...>::CSVIterator::operator++() {
        _index++;
        getIndexLine();
        return *this;
    }

    template<typename ... Arg>
    bool CSVParser<Arg...>::CSVIterator::operator==(CSVIterator secondIterator) {
        return this->_str == secondIterator._str && this->_index == secondIterator._index;
    }

    template<typename ... Arg>
    bool CSVParser<Arg...>::CSVIterator::operator!=(CSVIterator secondIterator) {
        return this->_str != secondIterator._str || this->_index != secondIterator._index;
    }

    template<typename... Arg>
    std::tuple<Arg...> CSVParser<Arg...>::CSVIterator::operator*() {
        this->parseLine();
        return this->vectorIntoTuple();
    }

    template<typename... Arg>
    typename CSVParser<Arg...>::CSVIterator CSVParser<Arg...>::begin() {
        CSVIterator begin(1, *this);
        return begin;
    }

    template<typename... Arg>
    typename CSVParser<Arg...>::CSVIterator CSVParser<Arg...>::end() {
        int indexEnd = this->getSize();
        indexEnd++;
        CSVIterator end(indexEnd, *this);
        return end;
    }

    template<typename T>
    void makeTuple(T& t, std::string &str, int &currIndex, int &lineNumber){
        std::istringstream stream(str);
        if ((stream >> t).fail() || !(stream >> std::ws).eof()){
           throw ParserException("Error: incorrect field", lineNumber, currIndex);
        };
    currIndex ++;
}

    void makeTuple(std::string &t, std::string &str, int &currIndex, int &lineNumber) {
        t = str;
        currIndex ++;
    }

    template<typename ...Arg, std::size_t ... I>
    void forEach(std::tuple<Arg...> &t, std::index_sequence<I...>, std::vector<std::string> parsedLine, int &currIndex, int &lineNumber){
        ((makeTuple(std::get<I>(t), parsedLine[I], currIndex, lineNumber)), ...);
    }

    template<typename... Arg>
    std::tuple<Arg...> CSVParser<Arg...>::CSVIterator::vectorIntoTuple() {
        _currIndex = 0;
        std::tuple<Arg...>tup;
        forEach(tup, std::index_sequence_for<Arg...>(), _parsedLine, _currIndex, _index);
        if (_currIndex != _parsedLine.size()){
            throw ParserException("Error: tuple size != line elements", _index, _currIndex);
        }
        return tup;
    }

////////CSVParser methods///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename ... Arg>
    CSVParser<Arg ...>::CSVParser(std::ifstream &file, int index, char columnDelim, char lineDelim,
                                  char fieldDelim) : _input(file) {
        _idxBegin = index;
        _columnDelim = columnDelim;
        _lineDelim = lineDelim;
        _fieldDelim = fieldDelim;
    }

    template<typename ... Arg>
    int CSVParser<Arg ...>::getSize() {
        int size = 0;
        this->changePosition();
        while (!_input.eof()) {
            getLine();
            size++;
        }
        return size;
    }
    template<typename ... Arg>
    std::string CSVParser<Arg ...>::getLine() {
        std::string line;
        char ch;
        while (_input.get(ch)) {
            if (ch == _lineDelim) break;
            line += ch;
        }
        return line;
    }

    template<typename ... Arg>
    void CSVParser<Arg ...>::changePosition() {
        _input.clear();
        _input.seekg(0, std::ios_base::beg);
        for (auto i = 0; i < _idxBegin; i++) {
            this->getLine();
        }
    }

    template<typename... Arg>
    char CSVParser<Arg...>::getColumnDelim() {
        return _columnDelim;
    }

    template<typename... Arg>
    char CSVParser<Arg...>::getFieldDelim() {
        return _fieldDelim;
    }

    enum class CSVState
    {
        ReadField,
        ReadDelimField,
        ReadDelimDelimField,
    };

    template<typename... Arg>
    void CSVParser<Arg...>::CSVIterator::parseLine() {
        CSVState state = CSVState::ReadField;
        _parsedLine.clear();
        _parsedLine.emplace_back("");
        _pos.clear();
        char columnDelim = _csvParser.getColumnDelim();
        char fieldDelim = _csvParser.getFieldDelim();
        size_t i = 0; // index of the current field
        size_t curPos = 0;
        for (char c : _str) {
            switch (state) {
                case CSVState::ReadField:
                    if (c == columnDelim) {
                        _parsedLine.emplace_back("");
                        _pos.push_back(curPos);
                        i++;
                    }
                    else if (c == fieldDelim) {
                        state = CSVState::ReadDelimField;
                    }
                    else {
                        _parsedLine[i].push_back(c);
                    }
                break;
                case CSVState::ReadDelimField:
                    if (c == fieldDelim) {
                        state = CSVState::ReadDelimDelimField;
                    }
                    else {
                        _parsedLine[i].push_back(c);
                    }
                break;
                case CSVState::ReadDelimDelimField:
                    if (c == columnDelim) {
                        _parsedLine.emplace_back("");
                        _pos.push_back(curPos);
                        i++;
                        state = CSVState::ReadField;
                    }
                    else if (c == fieldDelim) {
                        _parsedLine[i].push_back(fieldDelim);
                        state = CSVState::ReadDelimField;
                    }
                    else {
                        state = CSVState::ReadField;
                    }
                break;
            }
            curPos++;
        }
        if (state != CSVState::ReadField) {
            throw ParserException("Error: wrong field", _index, _pos.size());
        }
    }
}
#endif //CSV_CSVPARSER_H
