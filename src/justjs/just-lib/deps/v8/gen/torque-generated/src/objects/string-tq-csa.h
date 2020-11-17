#ifndef V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_STRING_TQ_H_
#define V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_STRING_TQ_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

TNode<String> Cast_String_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);
TNode<SeqOneByteString> AllocateSeqOneByteString_0(compiler::CodeAssemblerState* state_, TNode<Uint32T> p_length);
TNode<String> AllocateSeqTwoByteString_0(compiler::CodeAssemblerState* state_, TNode<Uint32T> p_length);
TNode<Int32T> LoadStringLength_0(compiler::CodeAssemblerState* state_, TNode<String> p_o);
TNode<String> LoadConsStringFirst_0(compiler::CodeAssemblerState* state_, TNode<ConsString> p_o);
void StoreConsStringFirst_0(compiler::CodeAssemblerState* state_, TNode<ConsString> p_o, TNode<String> p_v);
TNode<String> LoadConsStringSecond_0(compiler::CodeAssemblerState* state_, TNode<ConsString> p_o);
void StoreConsStringSecond_0(compiler::CodeAssemblerState* state_, TNode<ConsString> p_o, TNode<String> p_v);
TNode<ExternalPointerT> LoadExternalStringResource_0(compiler::CodeAssemblerState* state_, TNode<ExternalString> p_o);
void StoreExternalStringResource_0(compiler::CodeAssemblerState* state_, TNode<ExternalString> p_o, TNode<ExternalPointerT> p_v);
TNode<ExternalPointerT> LoadExternalStringResourceData_0(compiler::CodeAssemblerState* state_, TNode<ExternalString> p_o);
void StoreExternalStringResourceData_0(compiler::CodeAssemblerState* state_, TNode<ExternalString> p_o, TNode<ExternalPointerT> p_v);
TNode<Int8T> LoadSeqOneByteStringChars_0(compiler::CodeAssemblerState* state_, TNode<SeqOneByteString> p_o, TNode<IntPtrT> p_i);
void StoreSeqOneByteStringChars_0(compiler::CodeAssemblerState* state_, TNode<SeqOneByteString> p_o, TNode<IntPtrT> p_i, TNode<Int8T> p_v);
TNode<Uint16T> LoadSeqTwoByteStringChars_0(compiler::CodeAssemblerState* state_, TNode<SeqTwoByteString> p_o, TNode<IntPtrT> p_i);
void StoreSeqTwoByteStringChars_0(compiler::CodeAssemblerState* state_, TNode<SeqTwoByteString> p_o, TNode<IntPtrT> p_i, TNode<Uint16T> p_v);
TNode<String> LoadSlicedStringParent_0(compiler::CodeAssemblerState* state_, TNode<SlicedString> p_o);
void StoreSlicedStringParent_0(compiler::CodeAssemblerState* state_, TNode<SlicedString> p_o, TNode<String> p_v);
TNode<Smi> LoadSlicedStringOffset_0(compiler::CodeAssemblerState* state_, TNode<SlicedString> p_o);
void StoreSlicedStringOffset_0(compiler::CodeAssemblerState* state_, TNode<SlicedString> p_o, TNode<Smi> p_v);
TNode<String> LoadThinStringActual_0(compiler::CodeAssemblerState* state_, TNode<ThinString> p_o);
void StoreThinStringActual_0(compiler::CodeAssemblerState* state_, TNode<ThinString> p_o, TNode<String> p_v);
TNode<String> DownCastForTorqueClass_String_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);
TNode<SeqOneByteString> UnsafeCast_SeqOneByteString_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);
}  // namespace internal
}  // namespace v8

#endif  // V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_STRING_TQ_H_
