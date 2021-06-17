#pragma once
#include <string>
#include <utility>
#include <vector>
namespace qcor {
namespace mlir {
namespace utils {
using pauli_decomp_t = std::pair<std::string, double>;
// Input list of quantum gates: name and list of params (e.g. 1 for rx, ry, rz;
// 3 for u3, etc.)
using qop_t = std::pair<std::string, std::vector<double>>;
std::vector<pauli_decomp_t>
decompose_gate_sequence(const std::vector<qop_t> &op_list);
} // namespace utils
} // namespace mlir
} // namespace qcor