
#include <stdio.h>
#include <stdlib.h>

// Compilación: gcc Codificación_Huffman.c -o "nombre.exe"
 
// Esta constante se puede evitar calculando explícitamente el tamaño  del árbol de Huffman.
#define MAX_TREE_HT 100
 
// Nodo de árbol de Huffman
struct MinHeapNode {
 
    // caracteres de entrada
    char data;
 
    // Frecuencia del caracter
    unsigned freq;
 
    // Hijo izquierdo y derecho de este nodo
    struct MinHeapNode *left, *right;
};
 
// Min Heap:  Colección de nodos 
// min-heap (o árbol de Huffman  ) 
struct MinHeap {
 
    // Tamaño actual de  min heap
    unsigned size;
 
    // capacida de  min heap
    unsigned capacity;
 
    // Matriz de punteros de nodo minheap
    struct MinHeapNode** array;
};
 
// Función de utilidad Asignar un nuevo nodo de montón de min heap con el carácter y la frecuencia del carácter dados
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(
        sizeof(struct MinHeapNode));
 
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
 
    return temp;
}
 
// Función que crea 
//  el min heap y asigan  su capacidad 
struct MinHeap* createMinHeap(unsigned capacity)
 
{
 
    struct MinHeap* minHeap
        = (struct MinHeap*)malloc(sizeof(struct MinHeap));
 
   
    minHeap->size = 0;
 
    minHeap->capacity = capacity;
 
    minHeap->array = (struct MinHeapNode**)malloc(
        minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 

//Función de utilidad para intercambiar dos nodos 
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)
 
{
 
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// La función minHeapify estándar.
void minHeapify(struct MinHeap* minHeap, int idx)
 
{
 
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 
    if (left < minHeap->size
        && minHeap->array[left]->freq
               < minHeap->array[smallest]->freq)
        smallest = left;
 
    if (right < minHeap->size
        && minHeap->array[right]->freq
               < minHeap->array[smallest]->freq)
        smallest = right;
 
    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
 
// Función de utilidad para comprobar si el tamaño del montón es igual a 1
int isSizeOne(struct MinHeap* minHeap)
{
 
    return (minHeap->size == 1);
}
 
// Función estándar para extraer el nodo de valor mínimo del montón
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
 
{
 
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return temp;
}
 
// Función para insertar un nuevo nodo
void insertMinHeap(struct MinHeap* minHeap,
                   struct MinHeapNode* minHeapNode)
 
{
 
    ++minHeap->size;
    int i = minHeap->size - 1;
 
    while (i
           && minHeapNode->freq
                  < minHeap->array[(i - 1) / 2]->freq) {
 
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
 
    minHeap->array[i] = minHeapNode;
}
 
// Función estándar para crear un montón mínimo
void buildMinHeap(struct MinHeap* minHeap)
 
{
 
    int n = minHeap->size - 1;
    int i;
 
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
 
//Función de utilidad para imprimir una matriz de tamaño n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
 
    printf("\n");
}
 
// Función de utilidad para comprobar si este nodo es hoja
int isLeaf(struct MinHeapNode* root)
 
{
 
    return !(root->left) && !(root->right);
}
 
// Crea un montón mínimo de capacidad igual al tamaño e inserta todos los caracteres de los datos[] en el montón mínimo. 
//Inicialmente, el tamaño del montón mínimo es igual a la capacidad
struct MinHeap* createAndBuildMinHeap(char data[],
                                      int freq[], int size)
 
{
 
    struct MinHeap* minHeap = createMinHeap(size);
 
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
 
    minHeap->size = size;
    buildMinHeap(minHeap);
 
    return minHeap;
}
 
// La función principal que construye el árbol de Huffman
struct MinHeapNode* buildHuffmanTree(char data[],
                                     int freq[], int size)
 
{
    struct MinHeapNode *left, *right, *top;
 
    // Paso 1: Cree un montón mínimo de capacidad igual al tamaño.
    // Inicialmente, hay modos iguales al tamaño.
    struct MinHeap* minHeap
        = createAndBuildMinHeap(data, freq, size);
 
    // Iterar mientras el tamaño del montón no se convierte en 1
    while (!isSizeOne(minHeap)) {
 
        // Paso 2: Extrae los dos elementos de frecuencia mínima del montón mínimo
        left = extractMin(minHeap);
        right = extractMin(minHeap);
 
        // Paso 3: Cree un nuevo nodo interno con una frecuencia 
        //igual a la suma de las frecuencias de los dos nodos.
        //Haga que los dos nodos extraídos sean hijos izquierdo y derecho de este nuevo nodo.
        //Agregar este nodo al montón mínimo '$' es un valor especial para nodos internos, no se utiliza
        top = newNode('$', left->freq + right->freq);
 
        top->left = left;
        top->right = right;
 
        insertMinHeap(minHeap, top);
    }
 
    // Paso 4: El nodo restante es el nodo raíz 
    //y el árbol está completo.
    return extractMin(minHeap);
}
 
// Imprime códigos huffman desde la raíz del árbol Huffman.
// Utiliza arr[] para almecenar el código
void printCodes(struct MinHeapNode* root, int arr[],
                int top)
 
{
 
    // Asigna 0 al borde izquierdo
    if (root->left) {
 
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
 
    // Asigna 1 al borde derecho 
    if (root->right) {
 
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
 
  // Si se trata de un nodo hoja, entonces contiene uno de los caracteres de entrada, 
   //imprima el carácter y su código desde arr[]
    if (isLeaf(root)) {
 
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}
 
//La función principal que construye un árbol Huffman 
//e imprime códigos atravesando el árbol Huffman construido
void HuffmanCodes(char data[], int freq[], int size)
 
{
    // Construye el árbol 
    struct MinHeapNode* root
        = buildHuffmanTree(data, freq, size);
 
   //Imprime códigos Huffman usando el árbol Huffman construido arriba
    int arr[MAX_TREE_HT], top = 0;
 
    printCodes(root, arr, top);
}
 
// Main Principal
int main()
{
 
    char arr[] = { 'd', 'r', 'e', 'g', 'y' };
    int freq[] = { 1, 1, 2, 1, 1};
 
    int size = sizeof(arr) / sizeof(arr[0]);
 
    HuffmanCodes(arr, freq, size);
 
    return 0;
}

