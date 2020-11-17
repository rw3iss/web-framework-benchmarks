#ifndef V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_FEEDBACK_VECTOR_TQ_H_
#define V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_FEEDBACK_VECTOR_TQ_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

TNode<FeedbackVector> Cast_FeedbackVector_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);
TNode<FeedbackMetadata> Cast_FeedbackMetadata_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);
TNode<SharedFunctionInfo> LoadFeedbackVectorSharedFunctionInfo_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o);
void StoreFeedbackVectorSharedFunctionInfo_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o, TNode<SharedFunctionInfo> p_v);
TNode<MaybeObject> LoadFeedbackVectorOptimizedCodeWeakOrSmi_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o);
void StoreFeedbackVectorOptimizedCodeWeakOrSmi_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o, TNode<MaybeObject> p_v);
TNode<FixedArray> LoadFeedbackVectorClosureFeedbackCellArray_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o);
void StoreFeedbackVectorClosureFeedbackCellArray_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o, TNode<FixedArray> p_v);
TNode<Int32T> LoadFeedbackVectorLength_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o);
TNode<Int32T> LoadFeedbackVectorInvocationCount_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o);
void StoreFeedbackVectorInvocationCount_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o, TNode<Int32T> p_v);
TNode<Int32T> LoadFeedbackVectorProfilerTicks_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o);
void StoreFeedbackVectorProfilerTicks_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o, TNode<Int32T> p_v);
TNode<Uint32T> LoadFeedbackVectorPadding_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o);
void StoreFeedbackVectorPadding_0(compiler::CodeAssemblerState* state_, TNode<FeedbackVector> p_o, TNode<Uint32T> p_v);
TNode<FeedbackVector> DownCastForTorqueClass_FeedbackVector_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);
TNode<FeedbackMetadata> DownCastForTorqueClass_FeedbackMetadata_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);
}  // namespace internal
}  // namespace v8

#endif  // V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_FEEDBACK_VECTOR_TQ_H_
