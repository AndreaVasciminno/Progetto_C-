/**
  @file main.cpp

  @brief File header della classe ordered_list templata

  File di dichiarazioni/definizioni della classe ordered_list templata
*/

#include "stack.hpp"
#include<iostream>
#include<cassert>

/**
  @brief Funtore predicato su interi 

  Ritorna true se il valore intero passato è pari 
*/

struct is_even {
  bool operator()(int v) const {
    return (v%2)==0;
  }
};

/**
  @brief Funtore su interi 

  Moltiplica per due l'intero passato
*/

struct  MultiplyByTwo{
    int operator()(int x) const {
        return x * 2;  
    }
};

/**
  Test dei metodi fondamentali

  @brief Test dei metodi fondamentali
*/
void test_metodi_fondamentali_int() {
    std::cout<<"******** Test metodi fondamentali di uno stack di interi ********"<<std::endl;

    Stack<int> st;  // ctor default

    st.push(5); // push 
    st.push(8);
    st.push(1);
    st.push(4);

    std::cout << "Stampa di st dopo inserimenti:" << std::endl;
    st.print();

    Stack<int> st2(st);  // copy constructor

    std::cout << "Stampa di st2 dopo copy constructor:" << std::endl;
    st2.print();

    Stack<int> st3;

    st3 = st; // operator=

    std::cout << "Stampa di st3 dopo assegnamento:" << std::endl;
    st3.print();

} // ~Stack()


/**
  Test d'uso dello stack

  @brief Test d'uso dello stack
*/
void test_uso_int() {
    std::cout<<"******** Test d'uso dello stack di interi ********"<<std::endl;
    is_even ie;
    MultiplyByTwo t;

    int a[5] = {20,10,5,100,80};

    Stack<int> st(a,a+5); // constructor con i due iteratori

    std::cout << "Stampa di st dopo costruttore secondario:" << std::endl;
    st.print();

    std::cout << "Dimensione di st:" << std::endl;
    std::cout << st.size() << std::endl;
    assert(st.size() == 5);

    std::cout << "Solo valori pari di st:" << std::endl;
    Stack<int> st2 = st.filter_out(ie);
    st2.print();

    std::cout << "Stack after transform:" << std::endl;
    transform(st, t);
    st.print();

    std::cout << "Svuota stack:" << std::endl;
    st.svuotaStack();
    assert(st.stackEmpty());
    std::cout << st.stackEmpty() << std::endl;

}

/**
  @brief Test della funzione riempiStack

  Test della funzione riempiStack
*/

void test_riempi_stack(){
  std::cout<<"******** Test d'uso della funzione riempiStack********"<<std::endl;
  Stack<int> st;
  st.push(3);
  st.push(8);
  
  std::cout<<"Stampa iniziale stack:"<< std::endl;
  st.print();

  int a[5] = {20,10,5,100,80};
  st.riempiStack(a, a + 5);
  std::cout<<"Stampa finale stack:"<< std::endl;
  st.print();

}

/**
  @brief Test della gestione dell'overflow
*/

void test_overflow(){
  Stack <int> st(2);
  st.push(2);
  st.push(2);
  st.push(2);
}

/**
  @brief Test della gestione dell'overflow
*/

void test_underflow(){
  Stack <int> st(2);
  st.push(2);
  st.push(2);
  st.pop();
  st.pop();
  st.pop();
}


int main(){

    test_metodi_fondamentali_int();
    test_uso_int();
    test_riempi_stack();
    //test_overflow();
    //test_underflow();
    return 0;

}