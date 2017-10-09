# connect4
Connect 4 game in C++

Trabalho realizado por Bruno Carvalho 	201508043

Programa foi testado em Ubuntu 16.04 LTS e Windows 10 Pro 64-bit

---------------------------------------------------------------------------------------

Para compilar:

	g++ -Wall con4.cpp -o con4	

---------------------------------------------------------------------------------------

Para executar:

	./con4

---------------------------------------------------------------------------------------

Input:

	P v P = player vs player
	P v AI = player vs artificial intelligence 
	AI v AI = artificial intelligence vs artificial intelligence
	
	Durante o jogo escolher onde jogar dando o numero da coluna (de 1 a 7)
	O '^' mostra onde foi realizada a ultima jogada
	O '-' mostra os espaços em branco 

	Exemplo de tabuleiro de jogo:

		 1 2 3 4 5 6 7
		 - - - - - - -
		 - - - - - - -
		 - - - - - - -
		 - - X - - - -
		 - - O X - - -
		 O X O O X - -
		     ^          
---------------------------------------------------------------------------------------

Para mudar limite de procura / metodo usado:

	Abrir ficheiro con4.cpp (ou con4Win.cpp) com editor de texto
	Linha 673 e 674
	Mudar o valor da variavel 'maxD' para alterar limite de procura
		(apenas entre os numeros 1,3,5,7)
	Mudar o valor da variavel 'mode' alternar entre minimax (0) / alpha-beta (1)

---------------------------------------------------------------------------------------

Atenção!!

	Se o programa estiver a dar output a letras e simbolos esquesitos:
	Compilar e executar o ficheiro con4Win.cpp (nao tem cores no output)
