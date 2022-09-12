# Árvore de Huffman para compactação de arquivos

[![Linguagem C++](https://img.shields.io/badge/Linguagem-C%2B%2B-green.svg)]()
[![requirement](https://img.shields.io/badge/IDE-Sublime%20Text-orange)](https://www.sublimetext.com)
![ISO](https://img.shields.io/badge/ISO-Linux-blueviolet)

Elaborar uma árvore binária que utilize o código de Huffman para comprimir arquivos. Para tanto: 
<ol>
  <li>Contabilizar a recorrência de cada palavra (RP) no arquivo.</li>
  <li>Normalizar a contabilização entre 0 e 1 utilizando a seguinte fórmula: $$\frac{RP}{max(RP) - min(RP)}$$</li>
  <li>Montar a árvore com as regras apresentadas por Huffman.</li>
  <li>Troque as palavras pela codificação binária utilizando booleano para representar 0 e 1.</li>
  <li>Salve o arquivo em formato binário e observe qual foi o ganho de espaço obtido.</li>
</ol>

Elabore um Readme.mb explicando toda lógica utilizada na implementação, bem como, exemplos para representar funcionalidades da aplicação. Feito isso, demonstre um desses exemplos em execução para detalhar para o leitor o que ele deve esperar como saída. Além disso, detalhe tudo que for importante no código e mostre como deve ser compilado.

## Arquivos usados

<ul>
  <li>Nos arquivos nomeados como <code>huffmanTree</code> encontra-se a codificação da árvore de Huffman.</li>
  <li>Nos arquivos nomeados como <code>simbolTable</code> encontra-se a codificação que dá o código binário às palavras do texto extraído.</li>
  <li>Nos arquivos nomeados como <code>manipulation</code> encontra-se a codificação da leitura do arquivo de texto, juntamente com a limpeza das strings encontradas nesse arquivo para que as palavras sejam analisadas de forma correta e também o retorno do código de Huffman para cada palavra.</li>
</ul>

## Código

Desconsiderando a codificação para o funcionamento da árvore de Huffman, foram usadas apenas três funções para realizar a compactação do arquivo de texto, são elas: <code>clearString(string line)</code>, <code>readText_insertList(TlistaHuff &l)</code> e <code>saveCodeHuffman(tabelaSimbolos tabela)</code>.

### <i>clearString(string line)</i>

<ol>
  <li>Passado um parâmetro para transformar toda a string recebida em uma string lower case.</li>
  <li>Criada uma variável string temporária.</li>
  <li>Loop para percorrer toda a extensão da string recebida, onde irá salvar concatenando na string temporária somente caracteres que vão de <strong>A</strong> a <strong>Z</strong>.</li>
  <li>Após percorrer o loop, iguala a string recebida à string temporária, completando a limpeza da string.</li>
  <li>Retorna a string recebida.</li>
</ol>

Segue a codificação:

```C++
string clearString(string line){
  transform(line.begin(), line.end(), line.begin(), ::tolower);

  string temp;

  for(int i = 0; i < int(line.size()); i++){
    if(line[i] >= 'a' && line[i] <= 'z'){
      temp = temp + line[i];
    }
  }

  line = temp;

  return line;
}
```

### <i>readText_insertList(TlistaHuff &l)</i>

<ol>
  <li>Declaração das variáveis que serão necessárias, como a variável para abrir o arquivo de texto, a string para receber as palavras do arquivo de texto, um vetor de strings onde serão colocados as palavras do arquivo de texto, uma variável para contar a repetição de cada palavra, as variáveis para salvar qual foi o número máximo e mínimo de repetições e a variável para salvar o cálculo de normalização.</li>
  <li>O documento de texto é aberto.</li>
  <li>Inicia um loop que não é encerrado até o fim do arquivo de texto.
    <ol>
      <li>Feita a leitura do arquivo onde, é extraído palavra por palavra separadas por um espaço.</li>
      <li>Logo após extrair a palavra é feita a limpeza dessa palavra usando a função <code>clearString(line)</code></li>
      <li>Insere a palavra já limpa no vetor de strings.</li>
    </ol>
  <li>Encerra o loop e o arquivo de texto.</li>
  <li>Inicia um loop dentro de outro loop para fazer a comparação das palavras, com isso, contar as repetições de cada palavra e no fim salvar o máximo e o mínimo de repetiçoes que o texto possui, salvando nas variáveis <i>rpMax</i> e <i>rpMin</i>.</li>
  <li>Inicia outro loop dentro de outro loop, dessa vez para contar as repetições de cada palavra, realizar o cálculo de normalização de cada palavra e, com isso, salvar na lista dinâmica da árvore de Huffman a palavra juntamente com seu cálculo de normalização.</li>
</ol>

Segue a codificação:

```C++
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
```

### <i>saveCodeHuffman(tabelaSimbolos tabela)</i>

<ol>
  <li>Declaração das variáveis que serão necessárias, como a variável para abrir o arquivo de texto, a string para receber as palavras do arquivo de texto, um vetor de strings onde serão colocados as palavras do arquivo de texto, um vetor de booleanos para salvar o código de Huffman e mandá-lo para um arquivo binário.</li>
  <li>O documento de texto é aberto.</li>
  <li>Inicia um loop que não é encerrado até o fim do arquivo de texto.
    <ol>
      <li>Feita a leitura do arquivo onde, é extraído palavra por palavra separadas por um espaço.</li>
      <li>Logo após extrair a palavra é feita a limpeza dessa palavra usando a função <code>clearString(line)</code></li>
      <li>Insere a palavra já limpa no vetor de strings.</li>
    </ol>
<li>Encerra o loop e o arquivo de texto.</li>
  <li>É feito a criação do arquivo binário para escrita.</li>
  <li>Criação de uma string para salvar o código de Huffman completo.</li>
  <li>Inicia um loop que percorre todo o vetor de strings, retorna o código de Huffman da palavra naquele instante e concatena o código de Huffman na string criada para salvar o mesmo, tudo isso utilizando a função <code>codificacao_huff(tabelaSimbolos t, string palavra)</code>.</li>
  <li>Todo o código de Huffman do texto estando salvo na string criada para esse intuito, é percorrido a string com um loop para extrair cada caractere da string, onde se o caractere for <i>'1'</i>, salva um <code>True</code> no vetor de booleanos, e se o caractere for <i>'0'</i>, salva um <code>False</code> no vetor de booleanos.</li>
  <li>Inicia outro loop, dessa vez para percorrer o vetor de booleanos e inserir todo o vetor no arquivo binário.</li>
  <li>Feita a inserção do código de Huffman do texto no arquivo binário, fecha o arquivo.</li>
</ol>

Segue a codificação:

```C++
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
		cout << codificacao_huff(tabela, token[i]);
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

	cout << endl << endl << "- Código gravado no arquivo binário." << endl;

	fclose(binArq);

	cout << "- Arquivo binário fechado." << endl;
}
```

## Observações

<ul>
  <li>O texto a ser codificado deve estar em inglês, ou seja, sem acentuações.</li>
  <li>O arquivo de texto a ser lido, deve ser nomeado como <code>document.txt</code></li>
  <li>O número de repetições máximo deve ser maior que o número de repetições mínima, para que o cálculo de normalização não dê errado.</li>
  <li>O texto não deve possuir parágrafos nem espaços após sua última palavra.</li>
</ul>

## Funcionamento

<ul>
 <li>Inicialmente o arquivo deve ser baseado como o arquivo de texto abaixo:</li>
  	<p align="center">
  		<img src="/imgs/text.jpg">
	</p>	
 <li>Possuindo o arquivo de texto no padrão requerido, podemos executar o programa utilizando o método de compilação e execução. Executando o programa, o usuário receberá uma impressão do código de Huffman do texto utilizado e as mensagens de que o código foi escrito no arquivo binário e que o arquivo binário foi encerrado. Segue abaixo a demonstração:</li>
 	<p align="center">
  		<img src="/imgs/execute.jpg">
	</p>
	Lembrando que é sempre preferível dar um <code>make clean</code> antes de um <code>make</code> para executar o programa.
 <li>O arquivo binário será gerado e salvo na mesma pasta do arquivo de texto a ser codificado com o nome de <i>binaryFile</i>. Abaixo podemos ver o código gerado no arquivo binário aberto em um Blocos de Notas do Windows 11:</li>
 	<p align="center">
  		<img src="/imgs/binary.jpg">
	</p>
</ul>

## Compilação e Execução

O repositório possui um arquivo <i>Makefile</i> que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:

<table align="center">
  <tr>
    <td><strong>Comando</strong></td>
    <td><strong>Função</strong></td>
  </tr>
  <tr>
    <td><code>make clean</code></td>
    <td>Apaga a última compilação realizada contida na pasta build.</td>
  </tr>
  <tr>
    <td><code>make</code></td>
    <td>Executa a compilação do programa utilizando o g++, e o resultado vai para a pasta build.</td>
  </tr>
  <tr>
    <td><code>make run</code></td>
    <td>Executa o programa da pasta build após a realização da compilação.</td>
  </tr>
</table>

