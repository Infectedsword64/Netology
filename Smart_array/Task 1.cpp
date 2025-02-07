#include <iostream>

class smart_array {
public:
    smart_array(int size) {
       this->logical_size = size;
       this->actual_size = size;
       this->data = new int[size];
    }
    ~smart_array() {
       delete[] data;
    }
	smart_array() {
       this->actual_size = 0;
       this->data = new int[0];
    }
    void add_element(int el) {
        if (logical_size < actual_size) {
            data[logical_size] = el;
        }
        else {
            data = allocate_new_memory(this->data);
            data[logical_size] = el;
        }
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
        throw "error";
    }

private:
    int* data{nullptr};
    int logical_size;
    int actual_size;
};

int main() {
    try {
    	smart_array arr(5);
    	arr.add_element(1);
    	arr.add_element(4);
    	arr.add_element(155);
    	arr.add_element(14);
    	arr.add_element(15);
    	std::cout << arr.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
    	std::cout << ex.what() << std::endl;
    }
        return 0;
}