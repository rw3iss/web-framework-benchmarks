#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_STRING_REPLACEALL_TQ_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_STRING_REPLACEALL_TQ_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

TNode<Smi> TryFastAbstractStringIndexOf_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<String> p_string, TNode<String> p_searchString, TNode<Smi> p_fromIndex, compiler::CodeAssemblerLabel* label_Slow);
TNode<Smi> AbstractStringIndexOf_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<String> p_string, TNode<String> p_searchString, TNode<Smi> p_fromIndex);
void ThrowIfNotGlobal_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_searchValue);
TNode<Number> Convert_Number_Smi_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_i);
}  // namespace internal
}  // namespace v8

#endif  // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_STRING_REPLACEALL_TQ_H_
