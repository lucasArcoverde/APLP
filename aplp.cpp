#include <bits/stdc++.h>

using namespace std;

const int ALTURA = 6, LARGURA = 11, SINGLEPLAYER = 0, MAX_SHIFT = 3, MIN_SHIFT = -3;

const int REDE = 0, TRAVE_CIMA = -1, TRAVE_LADO = -2, CABECA = 1, BRACO_ESQUERDO = 2, BRACO_DIREITO = 3, 
			CORPO = 4, PERNA_ESQUERDA = 5, PERNA_DIREITA = 6, BOLA = 7;
			
const int ESQUERDA_CIMA = 1, ESQUERDA_BAIXO = 2, MEIO_CIMA = 3, 
		MEIO_BAIXO = 4, DIREITA_CIMA = 5, DIREITA_BAIXO = 6;
		  
map<int, char> chars;
int modoDePartida;

/*
	Inicializa o map de chars
*/
void buildMap()
{
	chars[BOLA] = 'X';
	chars[TRAVE_CIMA] = '_';
	chars[TRAVE_LADO] = '|';
	chars[REDE] = ' ';
	chars[CABECA] = 'O';
	chars[BRACO_ESQUERDO] = '\\';
	chars[BRACO_DIREITO] = '/';
	chars[CORPO] = '|';
	chars[PERNA_ESQUERDA] = '/';
	chars[PERNA_DIREITA] = '\\';
}
 
int trave[ALTURA][LARGURA] = {0};

/*
	A trave tem tamanho 11, sendo a posicao da trave[i][0] e trave[i][10] correspondentes as traves laterais
	e a trave[0][i] correspondente ao travessao

	0 1 2 3 4 5 6 7 8 9 10  
	_ _ _ _ _ _ _ _ _ _ _   
	|		  O			 |     
	|		 \|/		 |  
	|		  |			 |  
	|		  |			 |  
	|		 / \		 |  

	Sendo assim de 1 -> 9 equivale a parte de dentro do gol, o shift passado eh em relacao a cabeca do goleiro,
	quando o shit eh igual a 0, o goleiro esta no meio do gol (posicao 5)
	A cabeça do goleiro so pode ir da posicao 2 -> 8, se ficar na 1 ou na 9 a mao e a perna dele fica na trave
	O shift eh um numero randomico entre 3 e -3

*/
void montarTrave(int shift)
{	
	for (int i = 0; i<LARGURA; i++)
	{
		trave[0][i] = TRAVE_CIMA;
	}
	
	for (int i = 1; i<ALTURA; i++)
	{
		trave[i][0] = TRAVE_LADO;
		trave[i][LARGURA-1] = TRAVE_LADO;
	}
	
	trave[1][5 + shift] = CABECA;
	trave[2][4 + shift] = BRACO_ESQUERDO;
	trave[2][5 + shift] = CORPO;
	trave[2][6 + shift] = BRACO_DIREITO;
	trave[3][5 + shift] = CORPO;
	trave[4][5 + shift] = CORPO;
	trave[5][4 + shift] = PERNA_ESQUERDA;
	trave[5][6 + shift] = PERNA_DIREITA;
}

/*
	Printa a trave, o chars[] representa um numero que ta no array em forma de char, por exemplo: se o numero
	for igual a const CABECA, qr dizer que tem que ser printado a cabeca, chars[CABECA] = 'O'
*/
void exibirTrave()
{
	for(int i = 0; i<ALTURA; i++)
	{
		cout<<"     ";
		for(int  j = 0; j<LARGURA; j++)
		{
			cout<<chars[trave[i][j]];
		}
		cout<<endl;
	}
	cout<<"-----------------------"<<endl;
	memset(trave, REDE, sizeof trave);
}

void exibirPlacar(int p1, int p2)
{
	cout<<"Placar => Jogador 1: "<<p1<<" gol(s)."<<endl;
	cout<<"          Jogador 2: "<<p2<<" gol(s).\n"<<endl;
}

void exibirOpcoes()
{
	cout<<"1 - Esquerda cima"<<endl;
	cout<<"2 - Esquerda baixo"<<endl;
	cout<<"3 - Meio cima"<<endl;
	cout<<"4 - Meio baixo"<<endl;
	cout<<"5 - Direita cima"<<endl;
	cout<<"6 - Direita baixo\n"<<endl;
}

void exibirMenu()
{
	cout<<"####PENALTIS####"<<endl;
	cout<<"# Menu inicial #"<<endl;
	cout<<"################\n"<<endl;
	
	cout<<"0 - SINGLEPLAYER"<<endl;
	cout<<"1 - MULTIPLAYER\n"<<endl;
	
	cout<<"Escolha um modo de partida: ";	
	cin >> modoDePartida;
	cout<<endl;
}

/*
	Retorna o local que a bola esta. Funciona da seguinte forma: se eu escolhi esquerda cima ele nao ira chutar
	no mesmo canto sempre, tem uma regiao que representa esquerda cima, sendo assim eh escolhido um local aleatorio 
	toda vez que eh escolhido o local do chute

	localDoChute representa a opcao escolhida em exibirOpcoes()
*/
int simularChute(int localDoChute)
{	
	int i, j, min_i, max_i, min_j, max_j;
	
	if (localDoChute == ESQUERDA_CIMA) 
	{
		min_i = 0; max_i = 3; min_j = 0; max_j = 3;
	}
	else if (localDoChute == ESQUERDA_BAIXO) 
	{
		min_i = 4; max_i = 5; min_j = 0; max_j = 3;
	}
	else if (localDoChute == MEIO_CIMA) 
	{
		min_i = 0; max_i = 3; min_j = 4; max_j = 6;
	}
	else if (localDoChute == MEIO_BAIXO) 
	{
		min_i = 4; max_i = 5; min_j = 4; max_j = 6;
	}
	else if (localDoChute == DIREITA_CIMA) 
	{
		min_i = 0; max_i = 3; min_j = 7; max_j = 10;
	}
	else if (localDoChute == DIREITA_BAIXO)
	{
		min_i = 4; max_i = 5; min_j = 7; max_j = 10;
	}
	
	srand(time(NULL));
	i = min_i + (rand() % static_cast<int>(max_i - min_i + 1));
	j = min_j + (rand() % static_cast<int>(max_j - min_j + 1));
	
	int local = trave[i][j];
	trave[i][j] = BOLA;
	
	return local;
}
/*
	Inicialmente monta a trave com o goleiro no meio, q representa antes do jogador chutar
	
	Apos o jogador escolher o local do chute eh criado o shift para saber a posicao em que o goleiro ira ficar,
	depois eh montado a trave de novo com o goleiro reposicionado e depois simulaOChute(), que ira marcar a bola
	na matriz trave[][]

	Depois eh feito as verificacoes pra saber se foi gol ou nao
*/
void realizarJogada(int &p, int jogador)
{
	cout<<"@@@@@@@@@@@"<<endl;
	cout<<"@JOGADOR "<<jogador<<"@"<<endl;
	cout<<"@@@@@@@@@@@"<<endl;
	montarTrave(0);
	exibirTrave();
	exibirOpcoes();
	
	int localDoChute;
	
	cout<<"Insira o numero correspondente ao local em que deseja chutar: ";
	cin >> localDoChute; cout<<endl;
	
	while(localDoChute<1 or localDoChute>6)
	{
		cout<<"Numero invalido!! Insira o numero correspondente ao local em que deseja chutar: ";
		cin >> localDoChute; cout<<endl;
	}
	
	cout<<"Ele escolhe um canto, se prepara pra chutar e....\n"<<endl;
	
	srand(time(NULL));
	int shift = MIN_SHIFT + (rand() % static_cast<int>(MAX_SHIFT - MIN_SHIFT + 1));
	montarTrave(shift);
	
	int local = simularChute(localDoChute);
	
	exibirTrave();
	
	if(local==REDE)
	{
		cout<<"GOLL!!\n"<<endl;
		p++;
	}
	else if(local==TRAVE_CIMA or local==TRAVE_LADO)
	{
		cout<<"NA TRAVEE!!\n"<<endl;
	}
	else
	{
		cout<<"O GOLEIRO DEFENDE!!\n"<<endl;
	}
}

/* 
	Realizar jogada PC faz a mesma coisa sendo que com numero randomico para o local do chute
*/
void realizarJogadaPC(int &p, int jogador)
{
	cout<<"@@@@@@@@@@@@@@@@"<<endl;
	cout<<"@JOGADOR "<<jogador<<"(PC)@"<<endl;
	cout<<"@@@@@@@@@@@@@@@@"<<endl;
	montarTrave(0);
	exibirTrave();
	
	int localDoChute;
	
	localDoChute = 1 + (rand() % static_cast<int>(6 - 1 + 1));
	
	srand(time(NULL));
	int shift = MIN_SHIFT + (rand() % static_cast<int>(MAX_SHIFT - MIN_SHIFT + 1));
	montarTrave(shift);
	
	cout<<"Ele escolhe um canto, se prepara pra chutar e....\n"<<endl;
	
	int local = simularChute(localDoChute);
	
	exibirTrave();
	
	if(local==REDE)
	{
		cout<<"GOLL!!\n"<<endl;
		p++;
	}
	else if(local==TRAVE_CIMA or local==TRAVE_LADO)
	{
		cout<<"NA TRAVEE!!\n"<<endl;
	}
	else
	{
		cout<<"O GOLEIRO DEFENDE!!\n"<<endl;
	}	
}

int main()
{	
	buildMap();
	
	exibirMenu();
	
	if(modoDePartida==SINGLEPLAYER)
	{
		int p1 =0 , pc = 0, rodadas = 0;
	
		while((rodadas<5 and abs(p1-pc<3)) or (rodadas>=5 and p1==pc))
		{
			cout<<"############"<<endl;
			cout<<"#RODADA "<<rodadas+1<<"!!#"<<endl;
			cout<<"############\n"<<endl;
			
			exibirPlacar(p1,pc);
			realizarJogada(p1, 1);
			realizarJogadaPC(pc, 2);
			rodadas++;	
		}
		
		cout<< "FINAL DE PARTIDA!!\n"<<endl;
		exibirPlacar(p1,pc);
		if(p1>pc)
		{
			cout<< "VOCE VENCEU!"<<endl;
		}
		else
		{
			cout<< "NAO FOI DESSA VEZ.."<<endl;
		}
	}
	else
	{
		int p1 =0 , p2 = 0, rodadas = 0;
	
		while((rodadas<5 and abs(p1-p2<3)) or (rodadas>=5 and p1==p2))
		{
			cout<<"############"<<endl;
			cout<<"#RODADA "<<rodadas+1<<"!!#"<<endl;
			cout<<"############\n"<<endl;
			
			exibirPlacar(p1,p2);
			realizarJogada(p1, 1);
			realizarJogada(p2, 2);
			rodadas++;	
		}
		
		cout<< "FINAL DE PARTIDA!!\n"<<endl;
		exibirPlacar(p1,p2);
		if(p1>p2)
		{
			cout<< "O JOGADOR 1 VENCEU!"<<endl;
		}
		else
		{
			cout<< "O JOGADOR 2 VENCEU!"<<endl;
		}
	}	
}
