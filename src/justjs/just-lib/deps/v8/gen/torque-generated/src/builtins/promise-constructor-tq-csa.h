#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_PROMISE_CONSTRUCTOR_TQ_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_PROMISE_CONSTRUCTOR_TQ_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

TNode<BoolT> HasAccessCheckFailed_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<NativeContext> p_nativeContext, TNode<Object> p_promiseFun, TNode<Object> p_executor);
TNode<JSPromise> UnsafeCast_JSPromise_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);
}  // namespace internal
}  // namespace v8

#endif  // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_PROMISE_CONSTRUCTOR_TQ_H_
