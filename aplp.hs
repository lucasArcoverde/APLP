import System.Random as Random

--Main da aplicação
main :: IO ()
main = do
 mostrarMenu

 opcaoInput <- getLine
 let opcao = read opcaoInput :: Int

 if(opcao == 1) then umJogador
  else if (opcao == 2) then doisJogadores
   else putStrLn ("Até mais!")


--Mostra o menu do programa
mostrarMenu :: IO ()
mostrarMenu = do
 putStrLn ("------------------------")
 putStrLn ("Projeto APLP - Haskell")
 putStrLn ("------------------------")
 putStrLn ("Escolha um modo de jogo:")
 putStrLn ("1 - Um jogador")
 putStrLn ("2 - Dois jogadores")
 putStrLn ("3 - Sair")

--Modo de jogo para um jogador
umJogador :: IO ()
umJogador = do
  let rodadaInicial = 1
  let placar1 = 0
  let placar2 = 0

  rodadas1jogador rodadaInicial placar1 placar2
 
--Executa as cinco rodadas para o modo de um jogador
rodadas1jogador :: Int -> Int -> Int -> IO()
rodadas1jogador 6 placar1 placar2 = do
  mostrarPlacar placar1 placar2
  let resultadoFinal = resultadoUmJogador placar1 placar2
  putStrLn(resultadoFinal)

rodadas1jogador rodadaAtual placar1 placar2 = do
  putStrLn(" ")
  imprimirRodada rodadaAtual
  mostrarPlacar placar1 placar2

  putStrLn("JOGADOR:")
  opcoesDeChute
  localChute1 <- getLine
  let chute1 = read localChute1 :: Int
  puloGoleiro <- randomRIO(chute1, chute1+1)
  let foiGol = chutar chute1 puloGoleiro
  imprimirPuloGoleiro chute1 foiGol
  checarGol(foiGol)
  let novoPlacar1 = placar1 + foiGol

  putStrLn("PC:")
  chute2 <- randomRIO(1 :: Int, 6 :: Int)
  puloGoleiro <- randomRIO(chute2, chute2+1)
  let foiGol = chutar chute2 puloGoleiro
  imprimirPuloGoleiro chute2 foiGol
  checarGol(foiGol)
  let novoPlacar2 = placar2 + foiGol

  rodadas1jogador (rodadaAtual+1) novoPlacar1 novoPlacar2

--Mostra o placar da partida de um jogador
mostrarPlacar :: Int -> Int -> IO ()
mostrarPlacar placar1 placar2 = do
  putStrLn(" ")
  putStrLn("Jogador: "++ (show placar1) ++ " x " ++ (show placar2) ++ " :PC")
  putStrLn(" ")

--Mostra o resultado da partida no modo de um jogador
resultadoUmJogador :: Int -> Int -> String
resultadoUmJogador placar1 placar2 =
  if(placar1 > placar2 ) then "Jogador venceu!!!"
   else
    if(placar1 < placar2) then"PC venceu!!!"
     else "Empate!!!"

--Modo de jogo para dois jogadores
doisJogadores :: IO ()
doisJogadores = do

 let rodadaInicial = 1
 let placar1 = 0
 let placar2 = 0

 rodadas2jogadores rodadaInicial placar1 placar2

--Executa as cinco rodadas para o modo de dois jogadores
rodadas2jogadores :: Int -> Int -> Int -> IO()
rodadas2jogadores 6 placar1 placar2 = do
  mostrarPlacar2 placar1 placar2
  let resultadoFinal = resultado placar1 placar2
  putStrLn(resultadoFinal)

rodadas2jogadores rodadaAtual placar1 placar2 = do
  putStrLn(" ")
  imprimirRodada rodadaAtual
  mostrarPlacar2 placar1 placar2
  putStrLn("JOGADOR 1:")
  opcoesDeChute
  localChute1 <- getLine
  let chute1 = read localChute1 :: Int
  puloGoleiro <- randomRIO(chute1, chute1+1)
  let foiGol = chutar chute1 puloGoleiro
  imprimirPuloGoleiro chute1 foiGol
  checarGol(foiGol)

  let novoPlacar1 = placar1 + foiGol

  putStrLn("JOGADOR 2:")
  opcoesDeChute
  localChute2 <- getLine
  let chute2 = read localChute2 :: Int
  puloGoleiro <- randomRIO(chute2, chute2+1)
  let foiGol = chutar chute2 puloGoleiro
  imprimirPuloGoleiro chute2 foiGol
  checarGol(foiGol)

  let novoPlacar2 = placar2 + foiGol

  rodadas2jogadores (rodadaAtual+1) novoPlacar1 novoPlacar2
 
--Mostra o placar da partida entre dois jogadores
mostrarPlacar2 :: Int -> Int -> IO ()
mostrarPlacar2 placar1 placar2 = do
  putStrLn(" ")
  putStrLn("Jogador 1: "++ (show placar1) ++ " x " ++ (show placar2) ++ " :Jogador 2")
  putStrLn(" ")

--Calcula o vencedor da partida no modo de dois jogadores
resultado :: Int -> Int -> String
resultado placar1 placar2 =
 if(placar1 > placar2 ) then "Jogador 1 venceu!!!"
  else
   if(placar1 < placar2) then"Jogador 2 venceu!!!"
    else "Empate!!!"

--Mostra a rodada atual
imprimirRodada :: Int -> IO()
imprimirRodada rodadaAtual
 | rodadaAtual == 1 = putStrLn("Primeira Rodada!")
 | rodadaAtual == 2 = putStrLn("Segunda Rodada!")
 | rodadaAtual == 3 = putStrLn("Terceira Rodada!")
 | rodadaAtual == 4 = putStrLn("Quarta Rodada!")
 | rodadaAtual == 5 = putStrLn("Quinta Rodada!")
 | otherwise = putStrLn("Fim de jogo")

--Checa se o chute foi gol
chutar :: Int -> Int -> Int
chutar localDoChute puloGoleiro=
  if(localDoChute == puloGoleiro) then 0
   else 1

--Checa se o chute foi gol
checarGol :: Int -> IO ()
checarGol foiGol = do
 if(foiGol == 1) then putStrLn("GOOOOOOOL!!!")
  else putStrLn("ERROOOOU!!!")

--Mostra as opções de chute
opcoesDeChute :: IO ()
opcoesDeChute = do
 putStrLn ("Selecione um local de chute:")
 putStrLn ("1 - Esquerda Baixo")
 putStrLn ("2 - Esquerda Cima")
 putStrLn ("3 - Meio Baixo")
 putStrLn ("4 - Meio Cima")
 putStrLn ("5 - Direita Baixo")
 putStrLn ("6 - Direita Cima")

--Impressões para o pulo do goleiro de acordo com a posição
imprimirPuloGoleiro :: Int -> Int -> IO()
imprimirPuloGoleiro localChute foiGol
 | (localChute == 1 && foiGol == 1) = golBaixoEsquerda
 | (localChute == 1 && foiGol == 0) = errouBaixoEsquerda
 | (localChute == 2 && foiGol == 1) = golCimaEsquerda 
 | (localChute == 2 && foiGol == 0) = errouCimaEsquerda
 | (localChute == 3 && foiGol == 1) = golBaixoMeio
 | (localChute == 3 && foiGol == 0) = errouBaixoMeio
 | (localChute == 4 && foiGol == 1) = golCimaMeio
 | (localChute == 4 && foiGol == 0) = errouCimaMeio
 | (localChute == 5 && foiGol == 1) = golBaixoDireita
 | (localChute == 5 && foiGol == 0) = errouBaixoDireita
 | (localChute == 6 && foiGol == 1) = golCimaDireita
 | otherwise = errouCimaDireita

golBaixoEsquerda :: IO()
golBaixoEsquerda = do
 putStrLn("---------------------------")
 putStrLn("|   |  O  |               |")
 putStrLn("|    |_|_|                |")
 putStrLn("|      |                  |")
 putStrLn("|  O  | |                 |")

errouBaixoEsquerda :: IO()
errouBaixoEsquerda = do
 putStrLn("---------------------------")
 putStrLn("| |  O  |                 |")
 putStrLn("|  |_|_|                  |")
 putStrLn("|    |                    |")
 putStrLn("|   X |                   |")

golCimaEsquerda :: IO()
golCimaEsquerda = do
 putStrLn("---------------------------")
 putStrLn("| O |  O  |               |")
 putStrLn("|    |_|_|                |")
 putStrLn("|      |                  |")
 putStrLn("|     | |                 |")

errouCimaEsquerda :: IO()
errouCimaEsquerda = do
 putStrLn("---------------------------")
 putStrLn("|  X O  |                 |")
 putStrLn("|  |_|_|                  |")
 putStrLn("|    |                    |")
 putStrLn("|   | |                   |")

golBaixoMeio :: IO()
golBaixoMeio = do
 putStrLn("---------------------------")
 putStrLn("|        |  O  |          |")
 putStrLn("|         |_|_|           |")
 putStrLn("|           |             |")
 putStrLn("|          |O|            |")

errouBaixoMeio :: IO()
errouBaixoMeio = do
 putStrLn("---------------------------")
 putStrLn("|        |  O  |          |")
 putStrLn("|         |_|_|           |")
 putStrLn("|           |             |")
 putStrLn("|          X |            |")

golCimaMeio :: IO()
golCimaMeio = do
 putStrLn("---------------------------")
 putStrLn("|        O  |  O  |       |")
 putStrLn("|            |_|_|        |")
 putStrLn("|              |          |")
 putStrLn("|             | |         |")

errouCimaMeio :: IO()
errouCimaMeio = do
 putStrLn("---------------------------")
 putStrLn("|        |  x  |          |")
 putStrLn("|         |_|_|           |")
 putStrLn("|           |             |")
 putStrLn("|          | |            |")

golBaixoDireita :: IO()
golBaixoDireita = do
 putStrLn("---------------------------")
 putStrLn("|              |  O  |    |")
 putStrLn("|               |_|_|     |")
 putStrLn("|                 |       |")
 putStrLn("|                | |   O  |")

errouBaixoDireita :: IO()
errouBaixoDireita = do
 putStrLn("---------------------------")
 putStrLn("|                |  O  |  |")
 putStrLn("|                 |_|_|   |")
 putStrLn("|                   |     |")
 putStrLn("|                  | X    |")

golCimaDireita :: IO()
golCimaDireita = do
 putStrLn("---------------------------")
 putStrLn("|              |  O  |  O |")
 putStrLn("|               |_|_|     |")
 putStrLn("|                 |       |")
 putStrLn("|                | |      |")

errouCimaDireita :: IO()
errouCimaDireita = do
 putStrLn("---------------------------")
 putStrLn("|                |  O  X  |")
 putStrLn("|                 |_|_|   |")
 putStrLn("|                   |     |")
 putStrLn("|                  | |    |")