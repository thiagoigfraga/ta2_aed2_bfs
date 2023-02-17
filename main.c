#include <stdio.h>
#include <stdlib.h>

/* Estrutura do nó utilizada. Dentro dele, um valor inteiro que será armazenado 
no valor e dois outros nós, um indo pela esquerda e outro indo pela direita
*/
struct node {
	int valor;
	struct node *esquerda, *direita;
};

/* Seguindo as boas práticas, os protótipos das funções utilizadas */
void printLevelOrder(struct node* root)
void printCurrentLevel(struct node* root, int level);
int height(struct node* node);
struct node* newNode(int valor);

/* Função que tem como parâmetro o nó raíz da árvore. primeiro usa a função
height para identificar quantos níveis terá que percorrer no enlace.
*/
void printLevelOrder(struct node* root)
{
	int h = height(root);
	for (int i = 1; i <= h; i++)
		printCurrentLevel(root, i);
}

/* Aproveitando o cenário em que é possível percorrer pela recursão, a função irá
chamar a si mesma, até que atinja o último nível (1), tanto pela 
esquerda quanto pela direita.
  Fora a raíz ser nula, como critério de parada, o segundo parâmetro (nível) irá 
  decrementar conforme a árvore vai descendo. Assim que seu valor for 1, vai 
  entrar no segundo if ao invés de ir pelo else, imprimindo o valor 
  e encerrando a recursão.
*/
void printCurrentLevel(struct node* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
		printf("%d ", root->valor);
	else if (level > 1) {
		printCurrentLevel(root->esquerda, level - 1);
		printCurrentLevel(root->direita, level - 1);
	}
}

/* A altura é conhecida também pela recursão, sendo que o primeiro if só vai
entrar caso a raíz seja nula ou quando o nó filho for nulo. Do contrário a operação vai ir pelo else.
Importante ressaltar que a recursão irá se preocupar de ir até os nós que não terão filhos pra continuar, ou seja, o último nível possível. Mas como um lado pode ter mais filhos que o outro, isso faz com que seja necessário verificar, e assim
ter a certeza de que a altura retornada é a certa, com o incremento de 1 necessário para garantir o nível começando em 1. 
*/
int height(struct node* node)
{
	if (node == NULL)
		return 0;
	else {
		int lheight = height(node->esquerda);
		int rheight = height(node->direita);

		if (lheight > rheight)
			return (lheight + 1);
		else
			return (rheight + 1);
	}
}

/* Função utilizada para a criação de um novo nó, com seus filhos nulos e o valor
indicado em sua criação */
struct node* newNode(int valor)
{
	struct node* node
		= (struct node*)malloc(sizeof(struct node));
	node->valor = valor;
	node->esquerda = NULL;
	node->direita = NULL;

	return (node);
}

/*No main, o nó raíz é criado, e seu preenchimento está sendo feito de forma manual.
Como o foco está sendo na impressão, não vi como um problema nessa implementação.
*/
int main()
{
	struct node* root = newNode(1);
	root->direita = newNode(3);
	root->esquerda = newNode(2);
	root->esquerda->direita = newNode(5);
	root->esquerda->esquerda = newNode(4);
	root->direita->esquerda = newNode(8);
	root->direita->direita = newNode(10);

	printf("Level Order traversal of binary tree is \n");
	printLevelOrder(root);

	return 0;
}

//Referência utilizada: https://www.geeksforgeeks.org/level-order-tree-traversal/