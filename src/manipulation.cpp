#include "manipulation.hpp"

string clearString(string s){
	string aux;

	for (int i = 0; i < int(s.size()); i++) {
		if (s[i] != '.' && s[i]!= ',' && s[i] != ':' && s[i] != ';' && s[i] != '?' && s[i] != '!' && s[i] != '(' && s[i] != ')' && s[i] != '[' && s[i] != ']' && s[i] != '{'
			&& s[i] != '}' && s[i] != '+'&& s[i] != '=' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '%' && !isdigit(s[i])) {
			
			s[i] = tolower(s[i]);
            aux += s[i];
		}
	}
 
	return aux;
}

void readText_insertList(TlistaHuff &l){
	ifstream myfile;
	string line, auxWord;
	vector<string> token;

	int auxCount = 1;
	float rpMax = 0, rpMin = 99;

	float normalize;

	myfile.open("document.txt");

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

	token.clear();
}

void saveCodeHuffman(tabelaSimbolos tabela){
	ifstream myfile;
	string line;
	vector<string> token;

	vector<bool> binarie;
	char varTrue = '1';
	char varFalse = '0';

	myfile.open("document.txt");

	if(myfile.is_open()){
		while(! myfile.eof()){
			getline(myfile, line, ' ');
			line = clearString(line);
			// cout << line << endl;
			token.push_back(line);
		}
		myfile.close();
	}
	else{
		cout << "Error!" << endl;
	}

	FILE *binArq = fopen("binaryFile.bin", "wb");

	if(!binArq){
		cout << "Error!" << endl;
		return;
	}

	string codeComplete;

	for(int i = 0; i < int(token.size()); i++){
		cout << codificacao_huff(tabela, token[i]) << " ";
		codeComplete += codificacao_huff(tabela, token[i]);
	}

	token.clear();

	for(int i = 0; i < int(codeComplete.length()); i++){
		if(codeComplete.at(i) == varTrue){
			binarie.push_back(true);
		}
		else if(codeComplete.at(i) == varFalse){
			binarie.push_back(false);
		}
	}

	for(int i = 0; i < int(binarie.size()); i++){
		bool aux = binarie[i];
		fwrite(&aux, sizeof(bool), 1, binArq);
	}

	binarie.clear();

	cout << endl << endl << "- C??digo gravado no arquivo bin??rio." << endl;

	fclose(binArq);

	cout << "- Arquivo bin??rio fechado." << endl;
}