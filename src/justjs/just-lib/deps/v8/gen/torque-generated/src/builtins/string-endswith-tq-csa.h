#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_STRING_ENDSWITH_TQ_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_STRING_ENDSWITH_TQ_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

TNode<Oddball> TryFastStringCompareSequence_0(compiler::CodeAssemblerState* state_, TNode<String> p_string, TNode<String> p_searchStr, TNode<UintPtrT> p_start, TNode<UintPtrT> p_searchLength, compiler::CodeAssemblerLabel* label_Slow);
}  // namespace internal
}  // namespace v8

#endif  // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_STRING_ENDSWITH_TQ_H_
