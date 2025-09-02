/**
  @file stack.hpp

  @brief File header della classe Stack templata

  File di dichiarazioni/definizioni della classe stack templata
*/

#ifndef STACK_HPP
#define STACK_HPP
#include<algorithm> //std::swap
#include <iterator> // std::forward_iterator_tag
#include<iostream>

/**
  @brief Classe stack

  La classe imlementa un genrico stack di oggetti T.
*/


template <typename T>

class Stack{

private:

    T * _stack;         ///<puntatore al fondo dello stack
    unsigned int _size; ///<dato che rappresenta lo spazio allocato per lo stack
    int _top;  ///<puntatore alla cima della lista

public:

    /**
      Costruttore parametrico
      @param size spazio da allocare per lo stack

      @post _size impostato al parametro passato, in caso non venga passato niente viene settato di default a 10
      @post _top == -1
      @post _stack allocato un numero di celle uguali al parametro passato
    */   

    Stack(unsigned int size = 10) : _stack(nullptr), _size(size), _top(-1) {
        try{
            _stack = new T[_size];
        }catch(...){
            clear();
            throw; 
        }
    } 

    /**
    Costruttore che crea uno stacl riempito con dati
    presi da una sequenza identificata da un iteratore di 
    inizio e uno di fine. Gli iteratori possono essere di
    qualunque tipo. 

    @param b iteratore di inizio sequenza
    @param e iteratore di fine sequenza

    @throw std::bad_alloc possibile eccezione di allocazione
    */

    template <typename IterT>
    Stack(IterT b, IterT e): _stack(nullptr), _top(-1), _size(0){
        unsigned int size = 0;
        IterT app = b;
        //Utiliziamo il ciclo per comprendere quanti valori
        //sono presenti nella sequenza rappresentata dalla
        //coppia di iteratori
        while(app != e) {
            ++size;
            ++app;
        }
        //Allochiamo memoria per lo stack che stiamo creando
        //Cicliamo sui valori dei due array
        //La new può fallire, quindi effettuiamo una gestione
        //dell'eccezione con try e catch
        try{
            _stack = new T[size];
            _size = size;
            while(b != e){
                push(static_cast<T>(*b));
                ++b;
            }   
        }catch(...){
            // Se c'e' un problema, svuotiamo la lista e rilanciamo
            // l'eccezione
            clear();
            throw;
        }
        
    }

    /**
    Copy constructor

    @param other lista da copiare

    @throw std::bad_alloc possibile eccezione di allocazione
    */

    Stack(const Stack &other): _size(other._size), _top(other._top) {
        //Allochiamo memoria per lo stack che stiamo creando
        //Cicliamo sui valori dei due array
        //La new può fallire, quindi effettuiamo una gestione
        //dell'eccezione con try e catch
        try{
            _stack = new T[other._size];
            for(unsigned int i = 0; i < _size; ++i){
                _stack[i] = other._stack[i];
            }
        }catch(...){
            // Se c'e' un problema, svuotiamo la lista e rilanciamo
            // l'eccezione
            clear();
            throw;
        }
    }

    /**
    Operatore di assegnamento

    @param other lista da copiare

    @return reference alla lista this
    
    @throw std::bad_alloc possibile eccezione di allocazione
  */

    Stack &operator=(const Stack &other){
        if (this != &other) {
            Stack temp(other);
            this->swap(temp);
        }   
        return *this;
    }

    /**
    Distruttore 

    @post _stack == nullptr
    @post _size = 0
    @post _top = -1
    */

    ~Stack(){
        clear();
    }

    /**
    Svuota la lista e dealloca la memoria 

    @post _stack == nullptr
    @post _size = 0
    @post _top = -1
    */

    void clear(){
        _size = 0;
        _top = -1;
        delete [] _stack;
        _stack = nullptr;
    }

    /**
    Funzione che ritorna la grandezza dello stack

    @return grandezza dello stack
     */

    unsigned int size() const{
        return _size;
    }

    /**
    Funzione scambia lo stato tra l'istanza corrente di
    stack e quella passata come parametro.

    @param other stack con cui scambiare o stato
    */

    void swap(Stack& other) {
        std::swap(_stack, other._stack);
        std::swap(_size, other._size);
        std::swap(_top, other._top);
    }

    /**
    Funzione che controlla se lo stack sia o meno vuoto

    @return booleano che definisce se lo stack è pieno
     */

    bool stackEmpty() const{
        return _top == -1;
    }

    /**
    Aggiunge un elemento nello stack nella cima dello stack

    @param value valore da inserire nella lista

    @throw std::overflow:error possibile eccezione di stack overflow

    @post _top = _top+1
    */

    void push(T value){
        if(_top + 1 == _size)
            throw std::overflow_error("Stack overflow");
        ++_top;
        _stack[_top] = value;
    }

    /**
    Rimuove un elemento dalla cima dello stack e lo restituisce

    @return valore rimosso dalla cima dello stack

    @throw std::underflow:error possibile eccezione di stack underflow

    @post _top = _top+1
    */

    T pop(){
        if(_top == -1)
            throw std::underflow_error("Stack underflow");
        int tmp = _top;
        --_top;
        return _stack[tmp];
    }

   /**
    Funzione che effettua la stampa di uno stack dalla cima verso il fondo
    */

   void print(){
        Stack tmp(*this);
        while(!tmp.stackEmpty()){
            std::cout<<tmp.pop()<< " ";
        }
        std::cout<< std::endl;
   }

   /**
    Svuota la lista

    @post _top = -1
    */

    void svuotaStack(){
        T r;
        while(!stackEmpty()){
            r = pop();
        }
        _top = -1;
    }

    /**
    @brief funzione templata RiempiStack

    Prende in input una sequenza di iteratori che
    rappresentano una sequenza da inserire all'interno
    di uno stack. In caso questo contenga giò dei dati, 
    viene prima svuotato e poi riempito nuovamente

    @param b inizio sequenza iteratori
    @param e fine sequenza iteratori

    @throw std::overflow_error possibile eccezione per mancanza di spazio
     */


    template <typename IterT>
    void riempiStack(IterT b, IterT e){
        unsigned int size = 0;
        IterT app = b;
        while(app != e) {
            ++size;
            ++app;
        }
        if(size > _size){
            throw std::overflow_error("Spazio allocato insufficiente");
        }
        if(_top >= 0){
            svuotaStack();
        }
        try{
            _size = size;
            while(b != e){
                push(static_cast<T>(*b));
                ++b;
            }   
        }catch(...){
            clear();
            throw;
        }
    }

   /**
    @brief funzione templata filter_out

    Prende in input un predicato generico e costruisce un
    nuovo stack utilizzando solo i valori nello stack attuale
    che rispettano il parametro. Svuota e riempe due volte
    per mantenere l'ordine corretto nello stack

    @param Pred predicato su cui costruire il nuovo stack

    @return un nuovo stack contenente solo gli elementi corretti

    */

    template <typename P>
    Stack filter_out(P Pred){
        T r;
        Stack stack(_size);
        Stack tmp(*this);
        Stack::const_iterator b,e;

        //Vengono iterati gli elementi dello stack e filtrati
        //quelli che rispettano il predicato
        for(b = tmp.cbegin(), e = tmp.cend(); b != e; ++b){
            r = tmp.pop();
            if(Pred(r)){
                stack.push(r);
            }
        }

        //viene ripristinato l'ordire corretto dello stack
        for(b = stack.cbegin(), e = stack.cend(); b != e; ++b){
            r = stack.pop();
            tmp.push(r);
        }
        return tmp;
    }

    /**
    Gli iteratori devono iterare sui dati inseriti nella classe
    principale. Siccome nello stack mettiamo dei dati di 
    tipo T, l'iteratore deve iterare sui dati di tipo T. L'ordine
    di iterazione è opposto rispetto al canonico per lo stack. 
    L'iteratore itera, infatti, dal fondo alla cima
    */

    class iterator {
        public:
            typedef std::forward_iterator_tag iterator_category;
            typedef T                         value_type;
            typedef ptrdiff_t                 difference_type;
            typedef T*                        pointer;
            typedef T&                        reference;

            // Costruttore default
            iterator() : _ptr(nullptr) {}

            //Copy constructor
            iterator(const iterator& other) : _ptr(other._ptr) {}

            //Operatore di uguaglianza
            iterator& operator=(const iterator& other) {
                if (this != &other) {
                    _ptr = other._ptr;
                }
                return *this;
            }

            //Distruttore
            ~iterator(){ };

            // Ritorna il dato riferito dall'iteratore (dereferenziamento)
            reference operator*() const {
                return *_ptr;
            }

            // Ritorna il puntatore al dato riferito dall'iteratore
            pointer operator->() const {
                return _ptr;
            }

            // Operatore di iterazione pre-incremento
            iterator& operator++() {
                ++_ptr; 
                return *this;
            }

            // Operatore di iterazione post-incremento
            iterator operator++(int) { 
                iterator temp(*this);
                ++_ptr;
                return temp;
            }

            // Uguaglianza
            bool operator==(const iterator& other) const {
                return _ptr == other._ptr;
            }

            // Diversità
            bool operator!=(const iterator& other) const {
                return _ptr != other._ptr;
            }

        private:
            T* _ptr; // Puntatore all'elemento corrente

            // Permetti alla classe Stack di accedere al costruttore privato
            friend class Stack;

            // Costruttore parametrico utilizzato dalla classe container
            explicit iterator(T* ptr) : _ptr(ptr) {}

    };

    class const_iterator {
        public:
            typedef std::forward_iterator_tag iterator_category;
            typedef T                         value_type;
            typedef ptrdiff_t                 difference_type;
            typedef const T*                  pointer;
            typedef const T&                  reference;


            // Costruttore default
            const_iterator() : _ptr(nullptr) {}
            
             //Copy constructor
            const_iterator(const const_iterator& other) : _ptr(other._ptr) {}

            //Operatore di uguaglianza
            const_iterator& operator=(const const_iterator& other) {
                if (this != &other) {
                    _ptr = other._ptr;
                }
                return *this;
            }

            //Distruttore
            ~const_iterator() {}

            // Ritorna il dato riferito dall'iteratore (dereferenziamento)
            reference operator*() const {
                return *_ptr;
            }

            // Ritorna il puntatore al dato riferito dall'iteratore
            pointer operator->() const {
                return _ptr;
            }

            // Operatore di iterazione pre-incremento
            const_iterator& operator++() { 
                ++_ptr; 
                return *this;
            }

            // Operatore di iterazione post-incremento
           const_iterator operator++(int) { 
                const_iterator temp(*this);
                ++_ptr;
                return temp;
            }

            // Uguaglianza
            bool operator==(const const_iterator& other) const {
                return _ptr == other._ptr;
            }

            // Diversità
            bool operator!=(const const_iterator& other) const {
                return _ptr != other._ptr;
            }

        private:
            const T* _ptr; // Puntatore all'elemento corrente

            // Permetti alla classe Stack di accedere al costruttore privato
            friend class Stack;

            // Costruttore parametrico utilizzato dalla classe container
            explicit const_iterator(const T* ptr) : _ptr(ptr) {}


    };

    // Ritorna l'iteratore all'inizio della sequenza dati
    iterator begin() {
        return iterator(_stack);  
    }

    // Ritorna l'iteratore alla fine della sequenza dati
    iterator end() {
        return iterator(_stack + _top + 1); 
    }

    // Ritorna l'iteratore all'inizio della sequenza dati
    const_iterator cbegin() const {
        return const_iterator(_stack); 
    }

    // Ritorna l'iteratore alla fine della sequenza dati
    const_iterator cend() const {
        return const_iterator(_stack + _top + 1);  
    }



};

/**
 @brief funzione globale templata transform

 Trasforma uno stack in input sovrascrivendo i dati già
 presenti in base al funtore passato in input

 @param _stack stack di input su cui effettuare le modifiche
 @param f funtore generico da applicare agli elementi dello stack 
 */

template <typename T, typename Funt>
void transform(Stack<T> &_stack, Funt f){
    typename Stack<T>::iterator b, e;
    for(b = _stack.begin(), e = _stack.end(); b != e; ++b){
        *b = f(*b);
    }
}


#endif