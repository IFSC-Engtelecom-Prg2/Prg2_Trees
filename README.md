# Prg2_Trees
Um exemplo de árvore de pesquisa binária

A árvore aqui disponibilizada tem fins puramente didáticos, não devendo ser usada para aplicações reais. O objetivo de criá-la foi oferecer uma árvore para realizar experimentos e exercícios introdutórios sobre estruturas de dados. Por isso ela possui muitas limitações, como se pode deprender pela leitura do código.

# Uso da árvore

## Criação da árvore 

A árvore pode ser criada de duas maneiras:
1. Instanciando-a diretamente:
   ```c++
   // cria uma árvore vazia capaz de conter strings
   arvore<string> arv1;

   // cria uma árvore que contém três strings
   arvore<string> arv2({"um", "dois", "três"});
   
   // cria uma ávore a partir de um container iterável (vector, list, ...)
   vector<string> v = {"um", "dois", "três"};
   arvore<string> arv3(v);
   
   // cria uma árvore a partir de outra árvore (faz uma cópia)
   arvore<string> arv4(arv1);
   
   // cria uma árvore a partir de outra árvore (movendo seu estado para a nova árvore: árvore original se torna vazia)
   arvore<string> arv5(std::move(arv1));   
   ```
   Para criar a árvore dessa maneira, o tipo de dados dos valores armazenados deve ser comparável com operador<. Tipos predefinidos da linguagem C++ (nativos ou da STL) já possuem esse oṕerador definido, quando cabível. No caso de usar um tipo de dados definido pelo programador, deve-se então definir seu operador <:
   
   ```c++
   struct Tipo {
     int k;
     string nome;
   };
   
   bool operator<(const Tipo& x1, const Tipo & x2) {
     // retorna true se x1 < x2
   }
   
   int main() {
     arvore<Tipo> arv;
   ```   
2. Usando a função utilitária __cria_arvore__, que possibilita informar uma função comparadora para o tipo de dados armazenado:
   ```c++
   // a função de comparação deve comparar dois valores e retornar
   // true: se s1 < s2
   // false: caso contrário
   bool compare(const string & s1, const string & s2) {
     return s1.size() < s2.size();
   }
   
   int main() {
     auto arv = prglib::cria_arvore(compare);
   ```
   
