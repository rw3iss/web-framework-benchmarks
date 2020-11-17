#ifndef V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_STACK_FRAME_INFO_TQ_H_
#define V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_STACK_FRAME_INFO_TQ_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

TNode<StackFrameInfo> Cast_StackFrameInfo_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);
TNode<StackTraceFrame> Cast_StackTraceFrame_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);
TNode<Smi> LoadStackFrameInfoLineNumber_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoLineNumber_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<Smi> p_v);
TNode<Smi> LoadStackFrameInfoColumnNumber_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoColumnNumber_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<Smi> p_v);
TNode<Smi> LoadStackFrameInfoPromiseCombinatorIndex_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoPromiseCombinatorIndex_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<Smi> p_v);
TNode<Smi> LoadStackFrameInfoScriptId_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoScriptId_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<Smi> p_v);
TNode<Smi> LoadStackFrameInfoWasmFunctionIndex_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoWasmFunctionIndex_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<Smi> p_v);
TNode<Object> LoadStackFrameInfoScriptName_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoScriptName_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<Object> p_v);
TNode<Object> LoadStackFrameInfoScriptNameOrSourceUrl_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoScriptNameOrSourceUrl_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<Object> p_v);
TNode<PrimitiveHeapObject> LoadStackFrameInfoFunctionName_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoFunctionName_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<PrimitiveHeapObject> p_v);
TNode<PrimitiveHeapObject> LoadStackFrameInfoMethodName_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoMethodName_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<PrimitiveHeapObject> p_v);
TNode<PrimitiveHeapObject> LoadStackFrameInfoTypeName_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoTypeName_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<PrimitiveHeapObject> p_v);
TNode<PrimitiveHeapObject> LoadStackFrameInfoEvalOrigin_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoEvalOrigin_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<PrimitiveHeapObject> p_v);
TNode<PrimitiveHeapObject> LoadStackFrameInfoWasmModuleName_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoWasmModuleName_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<PrimitiveHeapObject> p_v);
TNode<HeapObject> LoadStackFrameInfoWasmInstance_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoWasmInstance_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<HeapObject> p_v);
TNode<Smi> LoadStackFrameInfoFlag_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o);
void StoreStackFrameInfoFlag_0(compiler::CodeAssemblerState* state_, TNode<StackFrameInfo> p_o, TNode<Smi> p_v);
TNode<HeapObject> LoadStackTraceFrameFrameArray_0(compiler::CodeAssemblerState* state_, TNode<StackTraceFrame> p_o);
void StoreStackTraceFrameFrameArray_0(compiler::CodeAssemblerState* state_, TNode<StackTraceFrame> p_o, TNode<HeapObject> p_v);
TNode<Smi> LoadStackTraceFrameFrameIndex_0(compiler::CodeAssemblerState* state_, TNode<StackTraceFrame> p_o);
void StoreStackTraceFrameFrameIndex_0(compiler::CodeAssemblerState* state_, TNode<StackTraceFrame> p_o, TNode<Smi> p_v);
TNode<HeapObject> LoadStackTraceFrameFrameInfo_0(compiler::CodeAssemblerState* state_, TNode<StackTraceFrame> p_o);
void StoreStackTraceFrameFrameInfo_0(compiler::CodeAssemblerState* state_, TNode<StackTraceFrame> p_o, TNode<HeapObject> p_v);
TNode<Smi> LoadStackTraceFrameId_0(compiler::CodeAssemblerState* state_, TNode<StackTraceFrame> p_o);
void StoreStackTraceFrameId_0(compiler::CodeAssemblerState* state_, TNode<StackTraceFrame> p_o, TNode<Smi> p_v);
TNode<StackFrameInfo> DownCastForTorqueClass_StackFrameInfo_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);
TNode<StackTraceFrame> DownCastForTorqueClass_StackTraceFrame_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);
}  // namespace internal
}  // namespace v8

#endif  // V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_STACK_FRAME_INFO_TQ_H_
