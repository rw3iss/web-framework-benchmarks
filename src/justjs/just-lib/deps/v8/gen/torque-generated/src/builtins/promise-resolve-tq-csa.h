#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_PROMISE_RESOLVE_TQ_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_PROMISE_RESOLVE_TQ_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

  TNode<String> kConstructorString_0(compiler::CodeAssemblerState* state_);
  TNode<String> kThenString_0(compiler::CodeAssemblerState* state_);
TNode<JSPromise> Cast_JSPromise_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError);
TorqueStructReference_JSObject_0 NativeContextSlot_Context_JSObject_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index);
}  // namespace internal
}  // namespace v8

#endif  // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_PROMISE_RESOLVE_TQ_H_
