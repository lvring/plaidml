// Copyright 2018, Intel Corporation

#pragma once

#include <map>
#include <string>
#include <vector>

#include "base/util/lookup.h"
#include "tile/stripe/stripe.h"

namespace vertexai {
namespace tile {
namespace codegen {

enum class AliasType {
  None,     // Buffers access unrelated spaces
  Partial,  // Buffers overlap
  Exact,    // Buffers are indentical for every index state
};

struct AliasInfo {
 public:
  static AliasType Compare(const AliasInfo& a, const AliasInfo& b);
  stripe::Block* base_block;
  stripe::Refinement* base_ref;
  std::string base_name;
  std::vector<stripe::Affine> access;
  TensorShape shape;
};

class AliasMap {
 public:
  // Constructs a root level alias info
  AliasMap();
  // Construct info for an inner block
  AliasMap(const AliasMap& outer, stripe::Block* block);
  // Lookup an AliasInfo by name
  const AliasInfo& at(const std::string& name) const { return safe_at(info_, name); }

 private:
  size_t depth_;                           // How deep is this AliasInfo
  std::map<std::string, AliasInfo> info_;  // Per buffer data
};

}  // namespace codegen
}  // namespace tile
}  // namespace vertexai
