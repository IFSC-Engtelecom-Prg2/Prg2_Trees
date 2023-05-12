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
   // a função de comparação deve comparar dois valores e retornar:
   // -1: se s1 < s2
   // 0: se s1 == s2
   // 1: se s1 > s2
   int compare(const string & s1, const string & s2) {
     return s1.size() < s2.size()?-1:size.size()!=s2.size();
   }
   
   int main() {
     auto arv = prglib::cria_arvore(compare);
   ```
   Um detalhe a ser observado é com respeito ao tipo dessa árvore, o que é necessário quando for passá-la como parâmetro ou retorná-la como resultado de função. O tipo dela deve informar tanto o tipo de dados armazenado, quanto o tipo da função de comparação. Uma forma de fazer isso é mostrada a seguir:
   ```c++
   int compare(const string & s1, const string & s2) {
     return s1.size() < s2.size()?-1:size.size()!=s2.size();
   }

   // aqui se cria um identificador para o tipo da função de comparação
   using comp_func = decltype(&compare);
   
   // a função a seguir recebe uma árvore como parâmetro ... veja que ela indica o tipo da função de comparação no segundo argumento do template da arvore
   void mostra(arvore<string,comp_func> & arv) {
     for (auto & s: arv) {
       cout << s << ' ';
     }
     cout << endl;
   }
   
   int main() {
     auto arv = prglib::cria_arvore(compare);
     arv.adiciona("um", "dois", "tres"});
     
     mostra(arv);
   ```
   
