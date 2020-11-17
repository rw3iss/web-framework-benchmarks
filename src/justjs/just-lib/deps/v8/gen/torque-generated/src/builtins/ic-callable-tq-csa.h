#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_IC_CALLABLE_TQ_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_IC_CALLABLE_TQ_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

TNode<BoolT> IsMonomorphic_0(compiler::CodeAssemblerState* state_, TNode<MaybeObject> p_feedback, TNode<Object> p_target);
TNode<BoolT> InSameNativeContext_0(compiler::CodeAssemblerState* state_, TNode<Context> p_lhs, TNode<Context> p_rhs);
TNode<HeapObject> MaybeObjectToStrong_0(compiler::CodeAssemblerState* state_, TNode<MaybeObject> p_maybeObject, compiler::CodeAssemblerLabel* label_IfCleared);
void TryInitializeAsMonomorphic_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_maybeTarget, TNode<FeedbackVector> p_feedbackVector, TNode<UintPtrT> p_slotId, compiler::CodeAssemblerLabel* label_TransitionToMegamorphic);
void TransitionToMegamorphic_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FeedbackVector> p_feedbackVector, TNode<UintPtrT> p_slotId);
void CollectCallFeedback_0(compiler::CodeAssemblerState* state_, TNode<Object> p_maybeTarget, TNode<Context> p_context, TNode<HeapObject> p_maybeFeedbackVector, TNode<UintPtrT> p_slotId);
void CollectInstanceOfFeedback_0(compiler::CodeAssemblerState* state_, TNode<Object> p_maybeTarget, TNode<Context> p_context, TNode<HeapObject> p_maybeFeedbackVector, TNode<UintPtrT> p_slotId);
TNode<BoolT> BothTaggedEqualArrayFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_first, TNode<Object> p_second);
void CollectConstructFeedback_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_target, TNode<Object> p_newTarget, TNode<HeapObject> p_maybeFeedbackVector, TNode<UintPtrT> p_slotId, compiler::CodeAssemblerLabel* label_ConstructGeneric, compiler::CodeAssemblerLabel* label_ConstructArray, compiler::TypedCodeAssemblerVariable<AllocationSite>* label_ConstructArray_parameter_0);
TNode<HeapObject> WeakToStrong_HeapObject_0(compiler::CodeAssemblerState* state_, TNode<MaybeObject> p_x, compiler::CodeAssemblerLabel* label_ClearedWeakPointer);
TNode<BoolT> Is_JSBoundFunction_HeapObject_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<HeapObject> p_o);
TNode<JSBoundFunction> UnsafeCast_JSBoundFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);
TNode<BoolT> Is_AllocationSite_Object_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);
TNode<AllocationSite> UnsafeCast_AllocationSite_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);
}  // namespace internal
}  // namespace v8

#endif  // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_IC_CALLABLE_TQ_H_
