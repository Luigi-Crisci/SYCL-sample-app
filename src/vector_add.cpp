#include <vector_add.hpp>

void vector_add(
	std::vector<float> &a,
	std::vector<float> &b,
	std::vector<float> &c) {
  const auto n = a.size();
  sycl::queue q{sycl::gpu_selector()};

  sycl::buffer<float,1> b_a(a.data(), n);
  sycl::buffer<float,1> b_b(b.data(), n);
  sycl::buffer<float,1> b_c(c.data(), n);

  q.submit([&](sycl::handler &cgh) {
	sycl::accessor a_acc{b_a, cgh, sycl::read_only};
	sycl::accessor b_acc{b_b, cgh, sycl::read_only};
	sycl::accessor c_acc{b_c, cgh, sycl::write_only, sycl::no_init};

	cgh.parallel_for<class vector_add>(
		sycl::range(n), [=](sycl::item<1> idx) {
		  c_acc[idx] = a_acc[idx] + b_acc[idx];
		});
  });
}