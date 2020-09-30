#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

int parserLine(std::string line, std::map<std::string, int> &wordMap) {
	int wordsCount = 0; 
	int sizeLine = line.length();
	std::string newWord = "";
	for (int i = 0; i <= sizeLine; i++) {
		if ((line[i] >= 'A') && (line[i] <= 'Z') || (line[i] >= 'a') && (line[i] <= 'z') || (line[i] >= '1') && (line[i] <= '9')) {
			newWord += line[i];
		}
		else {
			if (newWord == "") continue;
			wordMap[newWord]++;
			wordsCount++;
			newWord = "";
		}
 	}
	return wordsCount;
}

int parserFile(std::ifstream &fin, std::map<std::string, int> &wordMap) {
	int wordsCount = 0;
	while (!fin.eof()) {
		std::string newLine = "";
		while (!fin.eof()) {
			std::getline(fin, newLine);
			wordsCount += parserLine(newLine, wordMap);
		}

	}
	return wordsCount;
}

bool comp(std::pair<std::string, int> a,std::pair<std::string, int> b){
	return (a.second > b.second);
}

void sortWordsFreq(std::map <std::string, int> unsortWords, std::vector < std::pair<std::string, int >> &sortWords) {
	copy(unsortWords.begin(),unsortWords.end(), back_inserter(sortWords));
	sort(sortWords.begin(), sortWords.end(), comp);
}


void writeFile(std::ofstream &fout, std::vector < std::pair<std::string, int >> sortWords, int wordsCount) {
	fout << "Word" << ";"<< "Frequency" << ";" << "Frequency(%)" << std::endl;
	for (unsigned int i = 0; i < sortWords.size(); i++) {
		double percent = (double)((sortWords[i].second * 100)/ (double)wordsCount);
		fout << sortWords[i].first << ";" << sortWords[i].second<< ";" << percent << std::endl;
	}
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout<< "Please, enter the name of file."<<std::endl;
	}
	else {
		std::ifstream fin(argv[1]);
		if (!fin.is_open()) {
			std::cout << "File cannot open";
		}
		else {
			std::map <std::string, int> wordMap{};
			int wordsCount;
			wordsCount = parserFile(fin, wordMap);
			fin.close();
			std::vector < std::pair<std::string, int >> sortWords;
			sortWordsFreq(wordMap, sortWords);
			std::ofstream fout(argv[2]);
			if (!fout.is_open()) {
				std::cout << argv[2];
				std::cout << " File cannot open";
			}
			else {
				writeFile(fout, sortWords, wordsCount);
				fout.close();
			}
		}
	}
	return 0;
}
