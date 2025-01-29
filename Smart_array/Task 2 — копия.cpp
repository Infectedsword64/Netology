#include <iostream>

class smart_array {
public:
    smart_array(int size) {
       this->actual_size = size;
       this->data = new int[size];
    }
    
    smart_array(const smart_array& a)
	{
		this->data = a.data;
		this->actual_size = a.actual_size;
		this->logical_size = a.logical_size;
		for (int i = 0; i < this->actual_size; ++i)
		{
			this->data[i] = a.data[i];
		}
	}
	
    ~smart_array() {
        delete[] data;
    }
    void add_element(int el) {
        if (logical_size < actual_size) {
            data[logical_size] = el;
            logical_size++;
        }
        else {
            data = allocate_new_memory(this->data);
            data[logical_size] = el;
        }
    }
    
    const smart_array& operator=(smart_array& arr) {
        delete[] this->data;
        this->data = new int[arr.actual_size]; 
        this->actual_size = arr.actual_size;
        this->logical_size = arr.logical_size;
        for (int i = 0; i < this->actual_size; i++)
        {
            this->data[i] = arr.data[i];
        }    
        return *this;
    }
    
    int* allocate_new_memory(int* arr){
        this->actual_size *= 2;
        int* new_arr = new int[this->actual_size];
        for (int i = 0; i < this->logical_size; i++){
            new_arr[i] = arr[i];
        }
        delete[] arr;
        return new_arr;
    }
    
    int get_element(int index) {
        if (index < logical_size) {
            return data[index];
        }
        return false;
    }

protected:
    int* data;
    int logical_size = 0;
    int actual_size = 0;
};

int main() {
    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);

    smart_array new_array(2);
    new_array.add_element(44); 
    new_array.add_element(34);

    arr = new_array;
    return 0;
}