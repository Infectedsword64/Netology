#pragma once

template <typename T>
void print_container(const T& container) {
    auto it = container.begin();
    if (it != container.end()) {
        std::cout << *it;
        ++it;
    }

    for (; it != container.end(); ++it) {
        std::cout << ", " << *it;
    }

    std::cout << std::endl;
}