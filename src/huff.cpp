#include "huff.hpp"

string clearString(string line){
	transform(line.begin(), line.end(), line.begin(), ::tolower);

	line.erase(remove(line.begin(), line.end(), ','), line.end());
	line.erase(remove(line.begin(), line.end(), '.'), line.end());
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	line.erase(remove(line.begin(), line.end(), '\t'), line.end());
	line.erase(remove(line.begin(), line.end(), ')'), line.end());
	line.erase(remove(line.begin(), line.end(), '('), line.end());
	line.erase(remove(line.begin(), line.end(), '<'), line.end());
	line.erase(remove(line.begin(), line.end(), '>'), line.end());
	line.erase(remove(line.begin(), line.end(), ':'), line.end());
	line.erase(remove(line.begin(), line.end(), ';'), line.end());
	line.erase(remove(line.begin(), line.end(), '?'), line.end());
	line.erase(remove(line.begin(), line.end(), '!'), line.end());

	return line;
}

void readText_insertList(TlistaHuff &l){
	ifstream myfile;
	string line, auxWord;
	vector<string> token;

	int auxCount = 1;
	float rpMax = 0, rpMin = 99;

	float normalize;

	myfile.open("filosofia2.txt");

	if(myfile.is_open()){
		while(! myfile.eof()){
			getline(myfile, line, ' ');
			line = clearString(line);
			token.push_back(line);
		}
		myfile.close();
	}
	else{
		cout << "Error!" << endl;
	}

	for(int i = 0; i < int(token.size()-1); i++){
		auxWord = token[i];
		auxCount = 1;

		for(int j = i+1; j < int(token.size()); j++){
			if(token[i] == token[j]){
				auxCount++;
			}
			if(auxCount > rpMax){
				rpMax = auxCount;
			}
			if(auxCount < rpMin){
				rpMin = auxCount;
			}
		}
	}

	for(int i = 0; i < int(token.size()-1); i++){
		auxWord = token[i];
		auxCount = 1;
		
		for(int j = i+1; j < int(token.size()); j++){
			if((token[i] == token[j]) && (token[j] != "\0")){
				auxCount++;
				token[j] = "\0";
			}
		}
		
		normalize = auxCount/(rpMax - rpMin);
		
		if(auxWord != "\0"){
			insere_dado_inicio_huff(l, auxWord, normalize);
		}
	}
}
