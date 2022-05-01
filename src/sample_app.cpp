#include <iostream>
#include <vector>
#include <algorithm>
#include <vector_add.hpp>


int main(){
  std::vector<float> a(10, 1);
  std::vector<float> b(10, 1);
  std::vector<float> c(10);
  
  std::cout << "Summing vectors a and b" << std::endl;
  std::cout << "a: ";
  std::copy(a.begin(), a.end(), std::ostream_iterator<float>(std::cout, ", "));
  std::cout << "\nb: ";
  std::copy(b.begin(), b.end(), std::ostream_iterator<float>(std::cout, ", "));
  std::cout << std::endl;

  vector_add(a, b, c);

  for(int i = 0; i < 10; i++){
	if(c[i] != 2)
		throw std::runtime_error("vector_add failed: c[i] != 2");
  }

  std::cout << "TEST PASSED!" << std::endl;
}