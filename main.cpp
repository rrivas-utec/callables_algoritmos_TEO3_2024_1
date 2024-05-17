#include <iostream>
#include <vector>
using namespace std;

using Iterator = vector<int>::iterator;
using Callable = bool (*)(int);

bool EsPar(int item) { return item % 2 == 0; }
bool EsImpar(int item) { return item % 2 != 0; }
bool MayorA5(int item) { return item > 5; }

void ejemplo_callback() {   // Punteros a Funciones

  int x = 10;
  int* ptr = &x;
  Callable ptrFun = EsPar;
  cout << boolalpha << EsPar(2) << endl;
  cout << boolalpha << ptrFun(2) << endl;
}

auto crear_vector(Iterator inicio, Iterator fin, Callable condition) {
  vector<int> result;
  for (auto it = inicio; it != fin; ++it) {
    if (condition(*it))
      result.emplace_back(*it);
  }
  return result;
}

template <
        template <typename...> class Container = vector,
        typename Iterator,
        typename UnaryPreposicion>
auto create_container(Iterator first, Iterator last, UnaryPreposicion condition) {
  Container<typename Iterator::value_type> result;
  for (auto it = first; it != last; ++it) {
    if (condition(*it))
      result.emplace_back(*it);
  }
  return result;
}

template<typename Container>
void print(ostream& os, const Container& cnt) {
  for (const auto& item: cnt) {
    os << item << " ";
  }
}
void ejemplo_crear_vector () {
  vector v1 = {1, 2, 3, 4, 5, 6, 7, 8};
  auto v2 = crear_vector(begin(v1), end(v1), EsImpar);
  print(cout, v2);
}

void ejemplo_crear_container () {
  vector v1 = {1, 2, 3, 4, 5, 6, 7, 8};
  auto v2 = create_container(begin(v1), end(v1), EsImpar);
  print(cout, v2);
}

void ejemplo_crear_container_lambda () {
  vector v1 = {1, 2, 3, 4, 5, 6, 7, 8};
  auto v2 = create_container(
          begin(v1), end(v1),
          [](auto item) { return item % 2 != 0;});
  print(cout, v2);
}

void ejemplo_lambda (){
  int multiplo = 2;
  auto lambda_es_multiplo = [m=multiplo](int a) { return a % m == 0;};
  cout << boolalpha << lambda_es_multiplo(5) << endl;
  multiplo = 5;
  cout << boolalpha << lambda_es_multiplo(5) << endl;
}

void ejemplo_lambda2 (){
  int multiplo = 2;
  auto lambda_es_multiplo = [&multiplo](int a) { return a % multiplo == 0;};
  cout << boolalpha << lambda_es_multiplo(5) << endl;
  multiplo = 5;
  cout << boolalpha << lambda_es_multiplo(5) << endl;
}
int main() {
//  ejemplo_crear_vector();
//  ejemplo_crear_container();
//  ejemplo_lambda ();
  ejemplo_lambda2 ();
  return 0;
}
