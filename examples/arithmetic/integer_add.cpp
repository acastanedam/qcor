#include <qcor_arithmetic>

__qpu__ void test_add_integer(qreg q) {
  H(q[2]); // |000> + |001>
  add_integer(q, 3); // ==> |111> + |110>
  Measure(q);
}

__qpu__ void test_add_integer_mod(qreg q, qubit anc) {
  H(q[2]); // |000> + |001>
  add_integer_mod(q, anc, 3, 5); // |3 mod 5> and |7 mod 5>
  Measure(q);
  Measure(anc);
}

int main(int argc, char **argv) {
  set_shots(1024);
  auto a = qalloc(3);
  test_add_integer::print_kernel(a);
  test_add_integer(a);
  a.print();
  // Add 3 to a superposition of 0 and 4
  // => superposition of 3 and 7
  qcor_expect(a.counts().size() == 2);
  qcor_expect(a.counts()["111"] > 400);
  qcor_expect(a.counts()["110"] > 400);

  // Test modular add
  auto b = qalloc(3);
  auto anc = qalloc(1);
  test_add_integer_mod::print_kernel(b, anc[0]);
  test_add_integer_mod(b, anc[0]);
  // |3 mod 5> and |7 mod 5> == |2> + |3>
  b.print();
  qcor_expect(b.counts().size() == 2);
  qcor_expect(b.counts()["110"] > 400);
  qcor_expect(b.counts()["010"] > 400);
  anc.print();
  // anc returns to 0
  qcor_expect(anc.counts()["0"] == 1024);
  return 0;
}