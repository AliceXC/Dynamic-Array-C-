#include <iostream>

using namespace std;

template <class T> class DynamicArrayIterator;
template <class T> class DynamicArray{
	
	private:
		T* elems;
		int capacity;
		int nextFreeSpot;
	public:
		int size;

		DynamicArray(){	
			elems = new T[10]; 
			capacity = 10;
			nextFreeSpot = 0;
			size=0;
		}

		~DynamicArray(){
			delete[] elems;
		}

		T& operator [] (int index){
			return elems[index];
		}
		T operator [] (int index) const{
			return elems[index];
		}

		void add(T item){
		   //double the size of the array if the old one is full
		   if(nextFreeSpot == capacity){
			capacity = 2*capacity;

			T* New = new T[capacity];
			for(int i=0; i<nextFreeSpot;i++){
				New[i] = elems[i]; 
			}
			delete elems;
			elems = New;
		   }
			elems[nextFreeSpot] = item;
			nextFreeSpot++;
			size++;
		}

		T remove(int i){
			T temp;
			if(i>=0 && i<size){
				T temp = elems[i];
				//shift positions
				nextFreeSpot--;	
				size--;
				for(int ptr=i;ptr<size;ptr++)
					elems[ptr]=elems[ptr+1];
				elems[i+1]= NULL;	
			}
			return temp;
		}

		DynamicArrayIterator<T> begin(){
		   DynamicArrayIterator<T>* b = new DynamicArrayIterator<T>(this,0,1);
		   return *b;
		}
		
		DynamicArrayIterator<T> end(){
		   DynamicArrayIterator<T>* b = new DynamicArrayIterator<T>(this,size,1);
		   return *b;
		}

		DynamicArrayIterator<T> r_begin(){
		   DynamicArrayIterator<T>* b = new DynamicArrayIterator<T>(this,size-1,-1);
		   return *b;
		}

		DynamicArrayIterator<T> r_end(){
		   DynamicArrayIterator<T>* b = new DynamicArrayIterator<T>(this,-1,-1);
		   return *b;
		}
		
};

template <class T> class DynamicArrayIterator{
	private:
		int currentPosition;
		DynamicArray<T> *array;
		int direction;

	public:
		DynamicArrayIterator<T>(DynamicArray<T> *ptr, int cP, int d){
			currentPosition = cP;
			array = ptr;   
			direction = d;
		}

		T& operator *(){
			return (*array)[currentPosition];		
		}
		void operator ++(){
		 	if(currentPosition>=0 && currentPosition <= (*array).size)
				currentPosition += direction;
		}

		bool operator ==(DynamicArrayIterator<T> other) const{
			return ((*array)[currentPosition]==*other);
		}
		bool operator !=(DynamicArrayIterator<T> other) const{
			return ((*array)[currentPosition]!=*other);		
		}

};


int main() {

	return 0;
	/*DynamicArray<int> foo;
	foo.add(3);
	foo.add(2);
	cout << foo[1] << endl;
	foo[1] = 10;
	cout << foo[1] << endl;
	for(DynamicArrayIterator<int> a = foo.begin(); a != foo.end(); ++a) {
	cout << *a << endl;
	}
	for(DynamicArrayIterator<int> a = foo.r_begin(); a != foo.r_end(); ++a) {
	cout << *a << endl;
	}*/

}

