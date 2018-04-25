# Detecção de Catarata - Projeto ITP - 2017.2

## Autores
- [Daniel Oliveira Guerra](https://github.com/Codigos-de-Guerra)
- Pedro Augusto Pessoa Paraense


### Funcionalidas Extras
	1. Imagem em RGB com contorno da pupila; (Ver processos.c)
	2. Definição da quantidade de vezes que se gostaria de aplicar o filtro de Gauss/Sobel; (Definiçao da quantidade no main.c)
	3. Ignorar comentários nas imagens (seja antes do formato; entre o formato e a linha com largura e altura; seja entre a linha com largura e altura e a linha contendo o max); (Ver em read.c e read.h)
	4. Diagnóstico também diz qual foi a imagem analisada; (Ver uteis.c)
	5. A imagem entrada pode ter qualquer diretório escrito na execução do programa (função 'tirar_diretorio_do_nome_da_imagem'; checar uteis.c e uteis.h);
	6. Perguntas para dar o poder de decisão ao usuário;
	7. Programa funcionando com imagens extras; (Ver diretório in)
	8. Segmentação do flash tanto das imagens base quanto das imagens extras, melhorando um pouco a precisão de detecção; (Ver processos.c)
	9. Manutenção da memória do computador ao dar free em todas as imagens;
	10. Programa executa normalmente, mesmo alterando os nomes das imagens, reconhecendo cada imagem pelo cabeçalho; (Ver main.c)


### Funcionalidades básicas
	Todos funcionalidas básicas foram atendidas.


### O que seria feito diferente
	Implementação de uma função que obtivesse o limiar de Binarização, para uma imagem, automaticamente;
	Otimização da Transformada de Hough. Existem formas de otimizá-lo, mas a partir do momento em que percebemos, o tempo já estava curto.
	

### Para compilar:
```bash
# Entre no diretório raiz do projeto
# Digite `make` para compilar tudo e gerar os objetos e executáveis(arquivos binários)
$ make

# Execute `make clean` para limpar todos os dados residuais
$ make clean
```
### Para execução
```bash
$ ./catarata -i <input-image> -f <input-image-format> -o <diagnose-file>.
```
- ``<input-image>:``
Refere-se a imagem a ser analisada pelo programa. Caso inexistente, programa não rodará.
- ``<input-image-format>:``
Refere-se ao formato da imagem a ser lida, como, por exemplo, ``PPM``, ``PGM``, ``BPM`` e etc.
- ``<diagnose-file>:``
Refere ao arquivo de saída contendo os dados obtidos ao final do programa. Caso arquivo já exista, será sobrescrito.

#### Exemplo de Execução
```bash
$ ./catarata -i image1.ppm -f ppm -o diagnóstico.txt.
```
O programa lerá a imagem definida em `image1.ppm`, cujo formato é ``ppm``, e gerará os dados obtidos quanto ao olho em questão e seu diasgnóstico, em um arquivo texto chamado `diagnóstico.txt`

### Informações adicionais:
Caso queira, pode acessar o arquivo makefile para maiores orientações quanto ás compilações.
