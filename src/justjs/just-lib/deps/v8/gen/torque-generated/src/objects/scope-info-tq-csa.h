#ifndef V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_SCOPE_INFO_TQ_H_
#define V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_SCOPE_INFO_TQ_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

TNode<ScopeInfo> Cast_ScopeInfo_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);
  TNode<ScopeInfo> kEmptyScopeInfo_0(compiler::CodeAssemblerState* state_);
TNode<Uint32T> LoadScopeInfoFlags_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<ScopeInfo> p_scopeInfo);
TNode<ScopeInfo> DownCastForTorqueClass_ScopeInfo_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);
}  // namespace internal
}  // namespace v8

#endif  // V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_SCOPE_INFO_TQ_H_
