
// Конструктор по умолчанию
template<class T>
TQueue<T>::TQueue(){
    size = 0;
    capacity = 1;
    storage.reset(new T[1]);
}
// Конструктор копирования очереди.
template<class T>
TQueue<T>::TQueue(const TQueue<T>& other){
    size = other.size;
    capacity = other.capacity;
    storage = std::make_shared<T[]>(capacity);
    for(int  i = 0; i < size; i++){
        storage[i]=other.storage[i];
    }
}
// Метод, добавляющий фигуру в конец очереди.
template<class T>
void TQueue<T>::Push(const T& polygon){
    if(capacity == size) extend();
    storage[size]=polygon;
    size++;
}
// Метод, убирающий первую фигуру из очереди.
template<class T>
const T TQueue<T>::Pop(){
    if(size > 0){
        size--;
        return(storage[size]);
    }
    else{
        return T();
    }
}
// Метод, возвращающий ссылку на первую в очереди фигуру
template<class T>
const T& TQueue<T>::Top(){
    return storage[size-1];
}
// Метод, проверяющий пустоту очереди
template<class T>
bool TQueue<T>::Empty(){
    return bool(size);
}
// Метод, возвращающий длину очереди
template<class T>
size_t TQueue<T>::Length(){
    return size;
}
// Оператор вывода очереди в формате:
// "=> Sn Sn-1 ... S1 =>", где Si - площадь фигуры,
//  а n – номер последней фигуры в очереди
template<class T>
std::ostream& operator<< (std::ostream& os, const TQueue<T>& queue){
    os<<"Queue:\nsize: "<<queue.size<<"\ncapacity:"<< queue.capacity<<"\n"<<"=> ";
    for(int i = 0; i < queue.size; i++){
        os << queue.storage[i].Area() << ' ';
    }
    os << "=>\n";
    return os;
}
// Метод, удаляющий все элементы контейнера,
// но позволяющий пользоваться им.
template<class T>
void TQueue<T>::Clear(){
    size = 0;
    capacity = 1;
    storage.reset(new T[1]);
}
// Деструктор
template<class T>
TQueue<T>::~TQueue(){
    size = 0;
    capacity = 0;
    storage.reset();
}

template<class T>
void TQueue<T>::extend(){
    T* tmp;
    capacity*=2;
    tmp = new T[capacity];
    for(int i = 0; i < size; i++){
      tmp[i]=storage[i];
    }
    storage.reset();
    storage.reset(tmp);
  }

template<class T>
Iterator<T> TQueue<T>::begin(){
    return Iterator(storage.get(), 0, size);
}

template<class T>
Iterator<T> TQueue<T>::end(){
    return Iterator(storage.get()+size, size, size);
}

template<class T>
Iterator<T>::Iterator(T* ptr, size_t i,size_t s){
    array =ptr;
    index= i;
    size = s; 
}

template<class T>
T Iterator<T>::operator * (){
    return *array;
}

template<class T>
T Iterator<T>::operator -> (){
    return *array;
}

template<class T>
bool Iterator<T>::operator != (const Iterator<T> &  other) const{
    return array != other.array;
}

template<class T>
Iterator<T> & Iterator<T>::operator ++ (){
    this->array++;
    return *this;
}