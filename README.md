# Trabalho 2: **Buracos de Minhoca**

## How to use it

 1. Run **make** all to build the executable;  
   - Export *DEBUG=-DDEBUG* to activate debug flag;  
 2. Execute the **BlackHole.out**  
   - There're 3 Input exemples in *Inputs/*

## Especificação
Buraco de minhoca é o termo popular usado para definir uma espécie de túnel no espaço-tempo que conecta duas áreas distantes do Universo. O conceito foi inicialmente proposto em 1921 pelo físico alemão Hermann Weyl, mas o termo em inglês, wormhole, foi popularizado pelo físico americano John Wheeler em 1957. Um físico teórico contemporâneo, João Bogus, afirma ter mapeado diversos buracos de minhocas no Universo e ter descoberto várias de suas propriedades. As mais interessantes são:  

  - O tempo para atravessar um buraco de minhoca é infinitesimal e negligível;  
  - Um buraco de minhoca tem uma entrada e uma saída, cada uma situada em uma Galáxia distinta;  
  - Buracos de minhoca tem apenas uma direção;  
  - Uma Galáxia pode ter um ou mais buracos de minhocas;  
  - Por uma razão desconhecida, iniciando em nossa Galáxia, é sempre possível chegar em qualquer outra Galáxia através de uma seqüência de buracos de minhoca;  
  - Entre qualquer par de Galáxias, há no máximo um buraco de minhoca em cada direção;  

Interessantemente, todo buraco de minhoca possui uma diferença de tempo constante entre sua entrada e saída. Por exemplo, uma pessoa atravessando um buraco de minhoca pode sair do outro lado 15 anos no futuro. Outro buraco de minhoca pode levar a pessoa para 42 anos no passado.  

O físico Bogus pensa que deve ser possível utilizar os buracos de minhoca para voltar ao passado o suficiente para ver o Big Bang com os próprios olhos, se este realmente aconteceu. Um problema é que os buracos de minhoca conhecidos apenas levam, no máximo, a 1000 anos no passado ou 1000 anos no futuro, tempo insuficiente para chegar ao Big Bang. Porém, Bogus acredita ter a solução para isso. Se em seu mapeamento existir uma seqüência de buracos de minhoca que o levem incrementalmente ao passado, então bastará ele percorrer essa seqüência um certo número de vezes para voltar ao Big Bang.  

Apesar de "brilhante", Bogus não sabe como verificar se é possível tal façanha. É sua tarefa construir um programa que verifique se um dado conjunto de buracos de minhoca permite a volta ao Big Bang.  

#### Entrada  

A entrada inicia com um valor inteiro indicando o número de conjuntos a serem testados. Cada conjunto inicia com uma linha contendo dois inteiros, n e m. Estes indicam o número de Galáxias (1 <= n <= 1000) e o número de buracos de minhoca (1 <= m <= 2000). As galáxias são numeradas de 0 até n-1. Em seguida, para cada buraco de minhoca, há uma linha contendo três números inteiros, x, y e t. Estes números indicam em que galáxia está a entrada do buraco (x), a galáxia de saída do buraco (y) e a diferença de tempo, em anos, entre entrada e saída (-1000 <= t <= 1000).  

#### Saída  
A saída consiste de uma linha para cada conjunto na entrada, contendo a palavra "possivel" se for possível utilizar o conjunto de buracos de minhoca para voltar indefinidamente ao passado ou "impossivel" se não for possível.  

Exemplo de Entrada
```
2
3 3
0 1 1000
1 2 15
2 1 -42
4 4
0 1 10
1 2 20
2 3 30
3 0 -60
```

Exemplo de Saída
```
possivel
impossivel
```
