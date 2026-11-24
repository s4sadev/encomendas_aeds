PERSISTENCIA DE DADOS - SISTEMA DE ENCOMENDAS

Implementacao:
- Os registros de clientes, entregadores, localizacoes e encomendas sao gravados em arquivos binarios.
- Ao iniciar, o programa tenta carregar os quatro arquivos .dat.
- Ao escolher a opcao 0 no menu principal, o programa salva os dados e encerra.
- Os arquivos sao criados na pasta de trabalho (diretorio de onde o executavel e iniciado).

Arquivos gerados:
  clientes.dat
  entregadores.dat
  localizacoes.dat
  encomendas.dat

Compilacao (GCC):
  gcc -std=c99 -Wall -Wextra -pedantic main.c cliente.c entregador.c localizacao.c encomenda.c utils.c -o sistema_encomendas

Execucao:
  ./sistema_encomendas

Importante:
- Nao apague os arquivos .dat se quiser manter os cadastros.
- Para garantir a gravacao, encerre pelo menu principal usando a opcao 0.
- Os arquivos armazenam os dados em formato binario, portanto nao devem ser editados em um editor de texto.
