#ifdef VERIFY_HEAP

#include "src/objects/objects.h"
#include "src/ast/ast.h"
#include "src/builtins/builtins-array-gen.h"
#include "src/builtins/builtins-bigint-gen.h"
#include "src/builtins/builtins-collections-gen.h"
#include "src/builtins/builtins-constructor-gen.h"
#include "src/builtins/builtins-data-view-gen.h"
#include "src/builtins/builtins-iterator-gen.h"
#include "src/builtins/builtins-promise-gen.h"
#include "src/builtins/builtins-promise.h"
#include "src/builtins/builtins-proxy-gen.h"
#include "src/builtins/builtins-regexp-gen.h"
#include "src/builtins/builtins-string-gen.h"
#include "src/builtins/builtins-typed-array-gen.h"
#include "src/builtins/builtins-utils-gen.h"
#include "src/builtins/builtins-wasm-gen.h"
#include "src/builtins/builtins.h"
#include "src/codegen/code-factory.h"
#include "src/heap/factory-inl.h"
#include "src/ic/binary-op-assembler.h"
#include "src/objects/arguments.h"
#include "src/objects/bigint.h"
#include "src/objects/elements-kind.h"
#include "src/objects/free-space.h"
#include "src/objects/js-function.h"
#include "src/objects/js-generator.h"
#include "src/objects/js-objects.h"
#include "src/objects/js-promise.h"
#include "src/objects/js-regexp-string-iterator.h"
#include "src/objects/js-weak-refs.h"
#include "src/objects/objects.h"
#include "src/objects/ordered-hash-table.h"
#include "src/objects/property-array.h"
#include "src/objects/property-descriptor-object.h"
#include "src/objects/source-text-module.h"
#include "src/objects/stack-frame-info.h"
#include "src/objects/synthetic-module.h"
#include "src/objects/template-objects.h"
#include "src/torque/runtime-support.h"
#include "torque-generated/class-verifiers-tq.h"
#include "torque-generated/internal-class-definitions-tq-inl.h"
#include "torque-generated/exported-class-definitions-tq-inl.h"

// Has to be the last include (doesn't have include guards):
#include "src/objects/object-macros.h"
namespace v8 {
namespace internal {
void TorqueGeneratedClassVerifiers::HeapObjectVerify(HeapObject o, Isolate* isolate) {
  CHECK(o.IsHeapObject());
  {
    Object map__value = TaggedField<Object, 0>::load(o, 0);
    Object::VerifyPointer(isolate, map__value);
    CHECK(map__value.IsMap());
  }
}
void TorqueGeneratedClassVerifiers::ContextVerify(Context o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsContext());
  {
    Object length__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, length__value);
    CHECK(length__value.IsSmi());
  }
  for (int i = 0; i < TaggedField<Smi, Context::kLengthOffset>::load(o).value(); ++i) {
    Object elements__value = TaggedField<Object, 8>::load(o, 0 + i * kTaggedSize);
    Object::VerifyPointer(isolate, elements__value);
  }
}
void TorqueGeneratedClassVerifiers::JSReceiverVerify(JSReceiver o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsJSReceiver());
  {
    Object properties_or_hash__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, properties_or_hash__value);
    CHECK(properties_or_hash__value.IsSmi() || properties_or_hash__value.IsFixedArrayBase() || properties_or_hash__value.IsPropertyArray());
  }
}
void TorqueGeneratedClassVerifiers::PrimitiveHeapObjectVerify(PrimitiveHeapObject o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsPrimitiveHeapObject());
}
void TorqueGeneratedClassVerifiers::OddballVerify(Oddball o, Isolate* isolate) {
  o.PrimitiveHeapObjectVerify(isolate);
  CHECK(o.IsOddball());
  {
    Object to_string__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, to_string__value);
    CHECK(to_string__value.IsString());
  }
  {
    Object to_number__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, to_number__value);
    CHECK(to_number__value.IsHeapNumber() || to_number__value.IsSmi());
  }
  {
    Object type_of__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, type_of__value);
    CHECK(type_of__value.IsString());
  }
  {
    Object kind__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, kind__value);
    CHECK(kind__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::NameVerify(Name o, Isolate* isolate) {
  o.PrimitiveHeapObjectVerify(isolate);
  CHECK(o.IsName());
}
void TorqueGeneratedClassVerifiers::SymbolVerify(Symbol o, Isolate* isolate) {
  o.NameVerify(isolate);
  CHECK(o.IsSymbol());
  {
    Object description__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, description__value);
    CHECK(description__value.IsOddball() || description__value.IsString());
  }
}
void TorqueGeneratedClassVerifiers::StringVerify(String o, Isolate* isolate) {
  o.NameVerify(isolate);
  CHECK(o.IsString());
}
void TorqueGeneratedClassVerifiers::BigIntBaseVerify(BigIntBase o, Isolate* isolate) {
  o.PrimitiveHeapObjectVerify(isolate);
  CHECK(o.IsBigIntBase());
}
void TorqueGeneratedClassVerifiers::HeapNumberVerify(HeapNumber o, Isolate* isolate) {
  o.PrimitiveHeapObjectVerify(isolate);
  CHECK(o.IsHeapNumber());
}
void TorqueGeneratedClassVerifiers::FixedArrayBaseVerify(FixedArrayBase o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsFixedArrayBase());
  {
    Object length__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, length__value);
    CHECK(length__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::FixedArrayVerify(FixedArray o, Isolate* isolate) {
  o.FixedArrayBaseVerify(isolate);
  CHECK(o.IsFixedArray());
  for (int i = 0; i < TaggedField<Smi, FixedArray::kLengthOffset>::load(o).value(); ++i) {
    Object objects__value = TaggedField<Object, 8>::load(o, 0 + i * kTaggedSize);
    Object::VerifyPointer(isolate, objects__value);
  }
}
void TorqueGeneratedClassVerifiers::ByteArrayVerify(ByteArray o, Isolate* isolate) {
  o.FixedArrayBaseVerify(isolate);
  CHECK(o.IsByteArray());
}
void TorqueGeneratedClassVerifiers::WeakFixedArrayVerify(WeakFixedArray o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsWeakFixedArray());
  {
    Object length__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, length__value);
    CHECK(length__value.IsSmi());
  }
  for (int i = 0; i < TaggedField<Smi, WeakFixedArray::kLengthOffset>::load(o).value(); ++i) {
    MaybeObject objects__value = TaggedField<MaybeObject, 8>::load(o, 0 + i * kTaggedSize);
    MaybeObject::VerifyMaybeObjectPointer(isolate, objects__value);
    CHECK(objects__value.IsCleared() || (!objects__value.IsWeak() && objects__value.GetHeapObjectOrSmi().IsHeapObject()) || (!objects__value.IsWeak() && objects__value.GetHeapObjectOrSmi().IsSmi()) || objects__value.IsWeak());
  }
}
void TorqueGeneratedClassVerifiers::ForeignVerify(Foreign o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsForeign());
}
void TorqueGeneratedClassVerifiers::JSObjectVerify(JSObject o, Isolate* isolate) {
  o.JSReceiverVerify(isolate);
  CHECK(o.IsJSObject());
  {
    Object elements__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, elements__value);
    CHECK(elements__value.IsFixedArrayBase());
  }
}
void TorqueGeneratedClassVerifiers::JSProxyVerify(JSProxy o, Isolate* isolate) {
  o.JSReceiverVerify(isolate);
  CHECK(o.IsJSProxy());
  {
    Object target__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, target__value);
    CHECK(target__value.IsJSReceiver() || target__value.IsOddball());
  }
  {
    Object handler__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, handler__value);
    CHECK(handler__value.IsJSReceiver() || handler__value.IsOddball());
  }
}
void TorqueGeneratedClassVerifiers::JSFunctionOrBoundFunctionVerify(JSFunctionOrBoundFunction o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSFunctionOrBoundFunction());
}
void TorqueGeneratedClassVerifiers::JSBoundFunctionVerify(JSBoundFunction o, Isolate* isolate) {
  o.JSFunctionOrBoundFunctionVerify(isolate);
  CHECK(o.IsJSBoundFunction());
  {
    Object bound_target_function__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, bound_target_function__value);
    CHECK(bound_target_function__value.IsJSObject() || bound_target_function__value.IsJSProxy() || bound_target_function__value.IsJSBoundFunction() || bound_target_function__value.IsJSFunction());
  }
  {
    Object bound_this__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, bound_this__value);
    CHECK(bound_this__value.IsJSReceiver() || bound_this__value.IsOddball() || bound_this__value.IsOddball() || bound_this__value.IsOddball() || bound_this__value.IsOddball() || bound_this__value.IsSymbol() || bound_this__value.IsString() || bound_this__value.IsBigInt() || bound_this__value.IsHeapNumber() || bound_this__value.IsSmi() || bound_this__value.IsSourceTextModule());
  }
  {
    Object bound_arguments__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, bound_arguments__value);
    CHECK(bound_arguments__value.IsFixedArray());
  }
}
void TorqueGeneratedClassVerifiers::JSFunctionVerify(JSFunction o, Isolate* isolate) {
  o.JSFunctionOrBoundFunctionVerify(isolate);
  CHECK(o.IsJSFunction());
  {
    Object shared_function_info__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, shared_function_info__value);
    CHECK(shared_function_info__value.IsSharedFunctionInfo());
  }
  {
    Object context__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, context__value);
    CHECK(context__value.IsContext());
  }
  {
    Object feedback_cell__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, feedback_cell__value);
    CHECK(feedback_cell__value.IsFeedbackCell());
  }
  {
    Object code__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, code__value);
    CHECK(code__value.IsCode());
  }
}
void TorqueGeneratedClassVerifiers::JSCustomElementsObjectVerify(JSCustomElementsObject o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSCustomElementsObject());
}
void TorqueGeneratedClassVerifiers::JSSpecialObjectVerify(JSSpecialObject o, Isolate* isolate) {
  o.JSCustomElementsObjectVerify(isolate);
  CHECK(o.IsJSSpecialObject());
}
void TorqueGeneratedClassVerifiers::WeakCellVerify(WeakCell o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsWeakCell());
  {
    Object finalization_registry__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, finalization_registry__value);
    CHECK(finalization_registry__value.IsOddball() || finalization_registry__value.IsJSFinalizationRegistry());
  }
  {
    Object target__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, target__value);
    CHECK(target__value.IsJSReceiver() || target__value.IsOddball());
  }
  {
    Object unregister_token__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, unregister_token__value);
    CHECK(unregister_token__value.IsJSReceiver() || unregister_token__value.IsOddball() || unregister_token__value.IsOddball() || unregister_token__value.IsOddball() || unregister_token__value.IsOddball() || unregister_token__value.IsSymbol() || unregister_token__value.IsString() || unregister_token__value.IsBigInt() || unregister_token__value.IsHeapNumber() || unregister_token__value.IsSmi());
  }
  {
    Object holdings__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, holdings__value);
    CHECK(holdings__value.IsJSReceiver() || holdings__value.IsOddball() || holdings__value.IsOddball() || holdings__value.IsOddball() || holdings__value.IsOddball() || holdings__value.IsSymbol() || holdings__value.IsString() || holdings__value.IsBigInt() || holdings__value.IsHeapNumber() || holdings__value.IsSmi());
  }
  {
    Object prev__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, prev__value);
    CHECK(prev__value.IsOddball() || prev__value.IsWeakCell());
  }
  {
    Object next__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, next__value);
    CHECK(next__value.IsOddball() || next__value.IsWeakCell());
  }
  {
    Object key_list_prev__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, key_list_prev__value);
    CHECK(key_list_prev__value.IsOddball() || key_list_prev__value.IsWeakCell());
  }
  {
    Object key_list_next__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, key_list_next__value);
    CHECK(key_list_next__value.IsOddball() || key_list_next__value.IsWeakCell());
  }
}
void TorqueGeneratedClassVerifiers::MapVerify(Map o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsMap());
  {
    Object prototype__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, prototype__value);
    CHECK(prototype__value.IsJSReceiver() || prototype__value.IsOddball());
  }
  {
    Object constructor_or_back_pointer_or_native_context__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, constructor_or_back_pointer_or_native_context__value);
  }
  {
    Object instance_descriptors__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, instance_descriptors__value);
    CHECK(instance_descriptors__value.IsDescriptorArray());
  }
  {
    Object dependent_code__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, dependent_code__value);
    CHECK(dependent_code__value.IsWeakFixedArray());
  }
  {
    Object prototype_validity_cell__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, prototype_validity_cell__value);
    CHECK(prototype_validity_cell__value.IsSmi() || prototype_validity_cell__value.IsCell());
  }
  {
    MaybeObject transitions_or_prototype_info__value = TaggedField<MaybeObject, 36>::load(o, 0);
    MaybeObject::VerifyMaybeObjectPointer(isolate, transitions_or_prototype_info__value);
    CHECK(transitions_or_prototype_info__value.IsCleared() || (!transitions_or_prototype_info__value.IsWeak() && transitions_or_prototype_info__value.GetHeapObjectOrSmi().IsSmi()) || (!transitions_or_prototype_info__value.IsWeak() && transitions_or_prototype_info__value.GetHeapObjectOrSmi().IsTransitionArray()) || (!transitions_or_prototype_info__value.IsWeak() && transitions_or_prototype_info__value.GetHeapObjectOrSmi().IsMap()) || (transitions_or_prototype_info__value.IsWeak() && transitions_or_prototype_info__value.GetHeapObjectOrSmi().IsMap()) || (!transitions_or_prototype_info__value.IsWeak() && transitions_or_prototype_info__value.GetHeapObjectOrSmi().IsPrototypeInfo()));
  }
}
void TorqueGeneratedClassVerifiers::JSPromiseVerify(JSPromise o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSPromise());
  {
    Object reactions_or_result__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, reactions_or_result__value);
    CHECK(reactions_or_result__value.IsJSReceiver() || reactions_or_result__value.IsOddball() || reactions_or_result__value.IsOddball() || reactions_or_result__value.IsOddball() || reactions_or_result__value.IsOddball() || reactions_or_result__value.IsSymbol() || reactions_or_result__value.IsString() || reactions_or_result__value.IsBigInt() || reactions_or_result__value.IsHeapNumber() || reactions_or_result__value.IsSmi() || reactions_or_result__value.IsPromiseReaction());
  }
  {
    Object flags__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::StructVerify(Struct o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsStruct());
}
void TorqueGeneratedClassVerifiers::PromiseCapabilityVerify(PromiseCapability o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsPromiseCapability());
  {
    Object promise__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, promise__value);
    CHECK(promise__value.IsJSReceiver() || promise__value.IsOddball());
  }
  {
    Object resolve__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, resolve__value);
  }
  {
    Object reject__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, reject__value);
  }
}
void TorqueGeneratedClassVerifiers::JSArrayBufferViewVerify(JSArrayBufferView o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSArrayBufferView());
  {
    Object buffer__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, buffer__value);
    CHECK(buffer__value.IsJSArrayBuffer());
  }
}
void TorqueGeneratedClassVerifiers::JSTypedArrayVerify(JSTypedArray o, Isolate* isolate) {
  o.JSArrayBufferViewVerify(isolate);
  CHECK(o.IsJSTypedArray());
  {
    Object base_pointer__value = TaggedField<Object, 48>::load(o, 0);
    Object::VerifyPointer(isolate, base_pointer__value);
    CHECK(base_pointer__value.IsSmi() || base_pointer__value.IsByteArray());
  }
}
void TorqueGeneratedClassVerifiers::DataHandlerVerify(DataHandler o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsDataHandler());
  {
    Object smi_handler__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, smi_handler__value);
    CHECK(smi_handler__value.IsSmi() || smi_handler__value.IsCode());
  }
  {
    Object validity_cell__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, validity_cell__value);
    CHECK(validity_cell__value.IsSmi() || validity_cell__value.IsCell());
  }
}
void TorqueGeneratedClassVerifiers::AllocationMementoVerify(AllocationMemento o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsAllocationMemento());
  {
    Object allocation_site__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, allocation_site__value);
    CHECK(allocation_site__value.IsAllocationSite());
  }
}
void TorqueGeneratedClassVerifiers::CallHandlerInfoVerify(CallHandlerInfo o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsCallHandlerInfo());
  {
    Object callback__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, callback__value);
    CHECK(callback__value.IsOddball() || callback__value.IsSmi() || callback__value.IsForeign());
  }
  {
    Object js_callback__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, js_callback__value);
    CHECK(js_callback__value.IsOddball() || js_callback__value.IsSmi() || js_callback__value.IsForeign());
  }
  {
    Object data__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, data__value);
  }
}
void TorqueGeneratedClassVerifiers::InterceptorInfoVerify(InterceptorInfo o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsInterceptorInfo());
  {
    Object getter__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, getter__value);
    CHECK(getter__value.IsOddball() || getter__value.IsSmi() || getter__value.IsForeign());
  }
  {
    Object setter__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, setter__value);
    CHECK(setter__value.IsOddball() || setter__value.IsSmi() || setter__value.IsForeign());
  }
  {
    Object query__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, query__value);
    CHECK(query__value.IsOddball() || query__value.IsSmi() || query__value.IsForeign());
  }
  {
    Object descriptor__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, descriptor__value);
    CHECK(descriptor__value.IsOddball() || descriptor__value.IsSmi() || descriptor__value.IsForeign());
  }
  {
    Object deleter__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, deleter__value);
    CHECK(deleter__value.IsOddball() || deleter__value.IsSmi() || deleter__value.IsForeign());
  }
  {
    Object enumerator__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, enumerator__value);
    CHECK(enumerator__value.IsOddball() || enumerator__value.IsSmi() || enumerator__value.IsForeign());
  }
  {
    Object definer__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, definer__value);
    CHECK(definer__value.IsOddball() || definer__value.IsSmi() || definer__value.IsForeign());
  }
  {
    Object data__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, data__value);
  }
  {
    Object flags__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::AccessCheckInfoVerify(AccessCheckInfo o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsAccessCheckInfo());
  {
    Object callback__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, callback__value);
    CHECK(callback__value.IsOddball() || callback__value.IsSmi() || callback__value.IsForeign());
  }
  {
    Object named_interceptor__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, named_interceptor__value);
    CHECK(named_interceptor__value.IsOddball() || named_interceptor__value.IsSmi() || named_interceptor__value.IsInterceptorInfo());
  }
  {
    Object indexed_interceptor__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, indexed_interceptor__value);
    CHECK(indexed_interceptor__value.IsOddball() || indexed_interceptor__value.IsSmi() || indexed_interceptor__value.IsInterceptorInfo());
  }
  {
    Object data__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, data__value);
  }
}
void TorqueGeneratedClassVerifiers::AccessorInfoVerify(AccessorInfo o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsAccessorInfo());
  {
    Object name__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, name__value);
    CHECK(name__value.IsName());
  }
  {
    Object flags__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsSmi());
  }
  {
    Object expected_receiver_type__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, expected_receiver_type__value);
  }
  {
    Object setter__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, setter__value);
    CHECK(setter__value.IsSmi() || setter__value.IsForeign());
  }
  {
    Object getter__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, getter__value);
    CHECK(getter__value.IsSmi() || getter__value.IsForeign());
  }
  {
    Object js_getter__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, js_getter__value);
    CHECK(js_getter__value.IsSmi() || js_getter__value.IsForeign());
  }
  {
    Object data__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, data__value);
  }
}
void TorqueGeneratedClassVerifiers::JSArgumentsObjectVerify(JSArgumentsObject o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSArgumentsObject());
}
void TorqueGeneratedClassVerifiers::SloppyArgumentsElementsVerify(SloppyArgumentsElements o, Isolate* isolate) {
  o.FixedArrayBaseVerify(isolate);
  CHECK(o.IsSloppyArgumentsElements());
  {
    Object context__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, context__value);
    CHECK(context__value.IsContext());
  }
  {
    Object arguments__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, arguments__value);
    CHECK(arguments__value.IsFixedArray());
  }
  for (int i = 0; i < TaggedField<Smi, SloppyArgumentsElements::kLengthOffset>::load(o).value(); ++i) {
    Object mapped_entries__value = TaggedField<Object, 16>::load(o, 0 + i * kTaggedSize);
    Object::VerifyPointer(isolate, mapped_entries__value);
    CHECK(mapped_entries__value.IsSmi() || mapped_entries__value.IsOddball());
  }
}
void TorqueGeneratedClassVerifiers::AliasedArgumentsEntryVerify(AliasedArgumentsEntry o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsAliasedArgumentsEntry());
  {
    Object aliased_context_slot__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, aliased_context_slot__value);
    CHECK(aliased_context_slot__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::CellVerify(Cell o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsCell());
  {
    Object value__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, value__value);
  }
}
void TorqueGeneratedClassVerifiers::BytecodeArrayVerify(BytecodeArray o, Isolate* isolate) {
  o.FixedArrayBaseVerify(isolate);
  CHECK(o.IsBytecodeArray());
  {
    Object constant_pool__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, constant_pool__value);
    CHECK(constant_pool__value.IsFixedArray());
  }
  {
    Object handler_table__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, handler_table__value);
    CHECK(handler_table__value.IsByteArray());
  }
  {
    Object source_position_table__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, source_position_table__value);
    CHECK(source_position_table__value.IsOddball() || source_position_table__value.IsByteArray() || source_position_table__value.IsOddball());
  }
}
void TorqueGeneratedClassVerifiers::FixedDoubleArrayVerify(FixedDoubleArray o, Isolate* isolate) {
  o.FixedArrayBaseVerify(isolate);
  CHECK(o.IsFixedDoubleArray());
}
void TorqueGeneratedClassVerifiers::RegExpMatchInfoVerify(RegExpMatchInfo o, Isolate* isolate) {
  o.FixedArrayVerify(isolate);
  CHECK(o.IsRegExpMatchInfo());
}
void TorqueGeneratedClassVerifiers::BreakPointVerify(BreakPoint o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsBreakPoint());
  {
    Object id__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, id__value);
    CHECK(id__value.IsSmi());
  }
  {
    Object condition__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, condition__value);
    CHECK(condition__value.IsString());
  }
}
void TorqueGeneratedClassVerifiers::BreakPointInfoVerify(BreakPointInfo o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsBreakPointInfo());
  {
    Object source_position__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, source_position__value);
    CHECK(source_position__value.IsSmi());
  }
  {
    Object break_points__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, break_points__value);
    CHECK(break_points__value.IsOddball() || break_points__value.IsFixedArray() || break_points__value.IsBreakPoint());
  }
}
void TorqueGeneratedClassVerifiers::DebugInfoVerify(DebugInfo o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsDebugInfo());
  {
    Object shared__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, shared__value);
    CHECK(shared__value.IsSharedFunctionInfo());
  }
  {
    Object debugger_hints__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, debugger_hints__value);
    CHECK(debugger_hints__value.IsSmi());
  }
  {
    Object script__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, script__value);
    CHECK(script__value.IsOddball() || script__value.IsScript());
  }
  {
    Object original_bytecode_array__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, original_bytecode_array__value);
    CHECK(original_bytecode_array__value.IsOddball() || original_bytecode_array__value.IsBytecodeArray());
  }
  {
    Object debug_bytecode_array__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, debug_bytecode_array__value);
    CHECK(debug_bytecode_array__value.IsOddball() || debug_bytecode_array__value.IsBytecodeArray());
  }
  {
    Object break_points__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, break_points__value);
    CHECK(break_points__value.IsFixedArray());
  }
  {
    Object flags__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsSmi());
  }
  {
    Object coverage_info__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, coverage_info__value);
    CHECK(coverage_info__value.IsOddball() || coverage_info__value.IsCoverageInfo());
  }
}
void TorqueGeneratedClassVerifiers::CoverageInfoVerify(CoverageInfo o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsCoverageInfo());
  for (int i = 0; i < o.ReadField<int32_t>(CoverageInfo::kSlotCountOffset); ++i) {
  }
}
void TorqueGeneratedClassVerifiers::WasmValueVerify(WasmValue o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsWasmValue());
  {
    Object value_type__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, value_type__value);
    CHECK(value_type__value.IsSmi());
  }
  {
    Object bytes_or_ref__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, bytes_or_ref__value);
  }
}
void TorqueGeneratedClassVerifiers::EnumCacheVerify(EnumCache o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsEnumCache());
  {
    Object keys__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, keys__value);
    CHECK(keys__value.IsFixedArray());
  }
  {
    Object indices__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, indices__value);
    CHECK(indices__value.IsFixedArray());
  }
}
void TorqueGeneratedClassVerifiers::ClassPositionsVerify(ClassPositions o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsClassPositions());
  {
    Object start__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, start__value);
    CHECK(start__value.IsSmi());
  }
  {
    Object end__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, end__value);
    CHECK(end__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::AccessorPairVerify(AccessorPair o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsAccessorPair());
  {
    Object getter__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, getter__value);
  }
  {
    Object setter__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, setter__value);
  }
}
void TorqueGeneratedClassVerifiers::DescriptorArrayVerify(DescriptorArray o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsDescriptorArray());
  {
    Object enum_cache__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, enum_cache__value);
    CHECK(enum_cache__value.IsEnumCache());
  }
  for (int i = 0; i < o.ReadField<uint16_t>(DescriptorArray::kNumberOfAllDescriptorsOffset); ++i) {
  }
}
void TorqueGeneratedClassVerifiers::EmbedderDataArrayVerify(EmbedderDataArray o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsEmbedderDataArray());
  {
    Object length__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, length__value);
    CHECK(length__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::FeedbackCellVerify(FeedbackCell o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsFeedbackCell());
  {
    Object value__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, value__value);
    CHECK(value__value.IsOddball() || value__value.IsFixedArray() || value__value.IsFeedbackVector());
  }
}
void TorqueGeneratedClassVerifiers::FeedbackVectorVerify(FeedbackVector o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsFeedbackVector());
  {
    Object shared_function_info__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, shared_function_info__value);
    CHECK(shared_function_info__value.IsSharedFunctionInfo());
  }
  {
    MaybeObject optimized_code_weak_or_smi__value = TaggedField<MaybeObject, 8>::load(o, 0);
    MaybeObject::VerifyMaybeObjectPointer(isolate, optimized_code_weak_or_smi__value);
    CHECK(optimized_code_weak_or_smi__value.IsCleared() || (!optimized_code_weak_or_smi__value.IsWeak() && optimized_code_weak_or_smi__value.GetHeapObjectOrSmi().IsSmi()) || (optimized_code_weak_or_smi__value.IsWeak() && optimized_code_weak_or_smi__value.GetHeapObjectOrSmi().IsCode()));
  }
  {
    Object closure_feedback_cell_array__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, closure_feedback_cell_array__value);
    CHECK(closure_feedback_cell_array__value.IsFixedArray());
  }
}
void TorqueGeneratedClassVerifiers::ArrayListVerify(ArrayList o, Isolate* isolate) {
  o.FixedArrayVerify(isolate);
  CHECK(o.IsArrayList());
}
void TorqueGeneratedClassVerifiers::TemplateListVerify(TemplateList o, Isolate* isolate) {
  o.FixedArrayVerify(isolate);
  CHECK(o.IsTemplateList());
}
void TorqueGeneratedClassVerifiers::WeakArrayListVerify(WeakArrayList o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsWeakArrayList());
  {
    Object capacity__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, capacity__value);
    CHECK(capacity__value.IsSmi());
  }
  {
    Object length__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, length__value);
    CHECK(length__value.IsSmi());
  }
  for (int i = 0; i < TaggedField<Smi, WeakArrayList::kCapacityOffset>::load(o).value(); ++i) {
    MaybeObject objects__value = TaggedField<MaybeObject, 12>::load(o, 0 + i * kTaggedSize);
    MaybeObject::VerifyMaybeObjectPointer(isolate, objects__value);
    CHECK(objects__value.IsCleared() || (!objects__value.IsWeak() && objects__value.GetHeapObjectOrSmi().IsHeapObject()) || (!objects__value.IsWeak() && objects__value.GetHeapObjectOrSmi().IsSmi()) || objects__value.IsWeak());
  }
}
void TorqueGeneratedClassVerifiers::FreeSpaceVerify(FreeSpace o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsFreeSpace());
  {
    Object size__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, size__value);
    CHECK(size__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::JSArrayBufferVerify(JSArrayBuffer o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSArrayBuffer());
}
void TorqueGeneratedClassVerifiers::JSDataViewVerify(JSDataView o, Isolate* isolate) {
  o.JSArrayBufferViewVerify(isolate);
  CHECK(o.IsJSDataView());
}
void TorqueGeneratedClassVerifiers::JSArrayIteratorVerify(JSArrayIterator o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSArrayIterator());
  {
    Object iterated_object__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, iterated_object__value);
    CHECK(iterated_object__value.IsJSReceiver());
  }
  {
    Object next_index__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, next_index__value);
    CHECK(next_index__value.IsHeapNumber() || next_index__value.IsSmi());
  }
  {
    Object kind__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, kind__value);
    CHECK(kind__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::JSArrayVerify(JSArray o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSArray());
  {
    Object length__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, length__value);
    CHECK(length__value.IsHeapNumber() || length__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::JSCollectionIteratorVerify(JSCollectionIterator o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSCollectionIterator());
  {
    Object table__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, table__value);
  }
  {
    Object index__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, index__value);
  }
}
void TorqueGeneratedClassVerifiers::JSCollectionVerify(JSCollection o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSCollection());
  {
    Object table__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, table__value);
  }
}
void TorqueGeneratedClassVerifiers::JSSetVerify(JSSet o, Isolate* isolate) {
  o.JSCollectionVerify(isolate);
  CHECK(o.IsJSSet());
}
void TorqueGeneratedClassVerifiers::JSMapVerify(JSMap o, Isolate* isolate) {
  o.JSCollectionVerify(isolate);
  CHECK(o.IsJSMap());
}
void TorqueGeneratedClassVerifiers::JSWeakCollectionVerify(JSWeakCollection o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSWeakCollection());
  {
    Object table__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, table__value);
  }
}
void TorqueGeneratedClassVerifiers::JSWeakSetVerify(JSWeakSet o, Isolate* isolate) {
  o.JSWeakCollectionVerify(isolate);
  CHECK(o.IsJSWeakSet());
}
void TorqueGeneratedClassVerifiers::JSWeakMapVerify(JSWeakMap o, Isolate* isolate) {
  o.JSWeakCollectionVerify(isolate);
  CHECK(o.IsJSWeakMap());
}
void TorqueGeneratedClassVerifiers::JSGeneratorObjectVerify(JSGeneratorObject o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSGeneratorObject());
  {
    Object function__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, function__value);
    CHECK(function__value.IsJSFunction());
  }
  {
    Object context__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, context__value);
    CHECK(context__value.IsContext());
  }
  {
    Object receiver__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, receiver__value);
    CHECK(receiver__value.IsJSReceiver() || receiver__value.IsOddball() || receiver__value.IsOddball() || receiver__value.IsOddball() || receiver__value.IsOddball() || receiver__value.IsSymbol() || receiver__value.IsString() || receiver__value.IsBigInt() || receiver__value.IsHeapNumber() || receiver__value.IsSmi());
  }
  {
    Object input_or_debug_pos__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, input_or_debug_pos__value);
  }
  {
    Object resume_mode__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, resume_mode__value);
    CHECK(resume_mode__value.IsSmi());
  }
  {
    Object continuation__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, continuation__value);
    CHECK(continuation__value.IsSmi());
  }
  {
    Object parameters_and_registers__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, parameters_and_registers__value);
    CHECK(parameters_and_registers__value.IsFixedArray());
  }
}
void TorqueGeneratedClassVerifiers::JSAsyncFunctionObjectVerify(JSAsyncFunctionObject o, Isolate* isolate) {
  o.JSGeneratorObjectVerify(isolate);
  CHECK(o.IsJSAsyncFunctionObject());
  {
    Object promise__value = TaggedField<Object, 40>::load(o, 0);
    Object::VerifyPointer(isolate, promise__value);
    CHECK(promise__value.IsJSPromise());
  }
}
void TorqueGeneratedClassVerifiers::JSAsyncGeneratorObjectVerify(JSAsyncGeneratorObject o, Isolate* isolate) {
  o.JSGeneratorObjectVerify(isolate);
  CHECK(o.IsJSAsyncGeneratorObject());
  {
    Object queue__value = TaggedField<Object, 40>::load(o, 0);
    Object::VerifyPointer(isolate, queue__value);
    CHECK(queue__value.IsHeapObject());
  }
  {
    Object is_awaiting__value = TaggedField<Object, 44>::load(o, 0);
    Object::VerifyPointer(isolate, is_awaiting__value);
    CHECK(is_awaiting__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::AsyncGeneratorRequestVerify(AsyncGeneratorRequest o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsAsyncGeneratorRequest());
  {
    Object next__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, next__value);
    CHECK(next__value.IsOddball() || next__value.IsAsyncGeneratorRequest());
  }
  {
    Object resume_mode__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, resume_mode__value);
    CHECK(resume_mode__value.IsSmi());
  }
  {
    Object value__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, value__value);
  }
  {
    Object promise__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, promise__value);
    CHECK(promise__value.IsJSPromise());
  }
}
void TorqueGeneratedClassVerifiers::JSGlobalProxyVerify(JSGlobalProxy o, Isolate* isolate) {
  o.JSSpecialObjectVerify(isolate);
  CHECK(o.IsJSGlobalProxy());
  {
    Object native_context__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, native_context__value);
  }
}
void TorqueGeneratedClassVerifiers::JSGlobalObjectVerify(JSGlobalObject o, Isolate* isolate) {
  o.JSSpecialObjectVerify(isolate);
  CHECK(o.IsJSGlobalObject());
  {
    Object native_context__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, native_context__value);
    CHECK(native_context__value.IsNativeContext());
  }
  {
    Object global_proxy__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, global_proxy__value);
    CHECK(global_proxy__value.IsJSGlobalProxy());
  }
}
void TorqueGeneratedClassVerifiers::JSPrimitiveWrapperVerify(JSPrimitiveWrapper o, Isolate* isolate) {
  o.JSCustomElementsObjectVerify(isolate);
  CHECK(o.IsJSPrimitiveWrapper());
  {
    Object value__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, value__value);
    CHECK(value__value.IsJSReceiver() || value__value.IsOddball() || value__value.IsOddball() || value__value.IsOddball() || value__value.IsOddball() || value__value.IsSymbol() || value__value.IsString() || value__value.IsBigInt() || value__value.IsHeapNumber() || value__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::JSMessageObjectVerify(JSMessageObject o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSMessageObject());
  {
    Object message_type__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, message_type__value);
    CHECK(message_type__value.IsSmi());
  }
  {
    Object arguments__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, arguments__value);
  }
  {
    Object script__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, script__value);
    CHECK(script__value.IsScript());
  }
  {
    Object stack_frames__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, stack_frames__value);
  }
  {
    Object shared_info__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, shared_info__value);
    CHECK(shared_info__value.IsOddball() || shared_info__value.IsSharedFunctionInfo());
  }
  {
    Object bytecode_offset__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, bytecode_offset__value);
    CHECK(bytecode_offset__value.IsSmi());
  }
  {
    Object start_position__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, start_position__value);
    CHECK(start_position__value.IsSmi());
  }
  {
    Object end_position__value = TaggedField<Object, 40>::load(o, 0);
    Object::VerifyPointer(isolate, end_position__value);
    CHECK(end_position__value.IsSmi());
  }
  {
    Object error_level__value = TaggedField<Object, 44>::load(o, 0);
    Object::VerifyPointer(isolate, error_level__value);
    CHECK(error_level__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::JSDateVerify(JSDate o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSDate());
  {
    Object value__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, value__value);
    CHECK(value__value.IsOddball() || value__value.IsHeapNumber() || value__value.IsSmi());
  }
  {
    Object year__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, year__value);
    CHECK(year__value.IsOddball() || year__value.IsSmi() || year__value.IsHeapNumber());
  }
  {
    Object month__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, month__value);
    CHECK(month__value.IsOddball() || month__value.IsSmi() || month__value.IsHeapNumber());
  }
  {
    Object day__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, day__value);
    CHECK(day__value.IsOddball() || day__value.IsSmi() || day__value.IsHeapNumber());
  }
  {
    Object weekday__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, weekday__value);
    CHECK(weekday__value.IsOddball() || weekday__value.IsSmi() || weekday__value.IsHeapNumber());
  }
  {
    Object hour__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, hour__value);
    CHECK(hour__value.IsOddball() || hour__value.IsSmi() || hour__value.IsHeapNumber());
  }
  {
    Object min__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, min__value);
    CHECK(min__value.IsOddball() || min__value.IsSmi() || min__value.IsHeapNumber());
  }
  {
    Object sec__value = TaggedField<Object, 40>::load(o, 0);
    Object::VerifyPointer(isolate, sec__value);
    CHECK(sec__value.IsOddball() || sec__value.IsSmi() || sec__value.IsHeapNumber());
  }
  {
    Object cache_stamp__value = TaggedField<Object, 44>::load(o, 0);
    Object::VerifyPointer(isolate, cache_stamp__value);
    CHECK(cache_stamp__value.IsOddball() || cache_stamp__value.IsSmi() || cache_stamp__value.IsHeapNumber());
  }
}
void TorqueGeneratedClassVerifiers::JSAsyncFromSyncIteratorVerify(JSAsyncFromSyncIterator o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSAsyncFromSyncIterator());
  {
    Object sync_iterator__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, sync_iterator__value);
    CHECK(sync_iterator__value.IsJSReceiver());
  }
  {
    Object next__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, next__value);
  }
}
void TorqueGeneratedClassVerifiers::JSStringIteratorVerify(JSStringIterator o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSStringIterator());
  {
    Object string__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, string__value);
    CHECK(string__value.IsString());
  }
  {
    Object index__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, index__value);
    CHECK(index__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::JSRegExpStringIteratorVerify(JSRegExpStringIterator o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSRegExpStringIterator());
  {
    Object iterating_reg_exp__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, iterating_reg_exp__value);
    CHECK(iterating_reg_exp__value.IsJSReceiver());
  }
  {
    Object iterated_string__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, iterated_string__value);
    CHECK(iterated_string__value.IsString());
  }
  {
    Object flags__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::JSRegExpVerify(JSRegExp o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSRegExp());
  {
    Object data__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, data__value);
    CHECK(data__value.IsOddball() || data__value.IsFixedArray());
  }
  {
    Object source__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, source__value);
    CHECK(source__value.IsOddball() || source__value.IsString());
  }
  {
    Object flags__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsOddball() || flags__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::JSFinalizationRegistryVerify(JSFinalizationRegistry o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSFinalizationRegistry());
  {
    Object native_context__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, native_context__value);
    CHECK(native_context__value.IsNativeContext());
  }
  {
    Object cleanup__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, cleanup__value);
    CHECK(cleanup__value.IsJSObject() || cleanup__value.IsJSProxy() || cleanup__value.IsJSBoundFunction() || cleanup__value.IsJSFunction());
  }
  {
    Object active_cells__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, active_cells__value);
    CHECK(active_cells__value.IsOddball() || active_cells__value.IsWeakCell());
  }
  {
    Object cleared_cells__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, cleared_cells__value);
    CHECK(cleared_cells__value.IsOddball() || cleared_cells__value.IsWeakCell());
  }
  {
    Object key_map__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, key_map__value);
  }
  {
    Object next_dirty__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, next_dirty__value);
    CHECK(next_dirty__value.IsOddball() || next_dirty__value.IsJSFinalizationRegistry());
  }
  {
    Object flags__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::JSWeakRefVerify(JSWeakRef o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsJSWeakRef());
  {
    Object target__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, target__value);
    CHECK(target__value.IsJSReceiver() || target__value.IsOddball());
  }
}
void TorqueGeneratedClassVerifiers::ArrayBoilerplateDescriptionVerify(ArrayBoilerplateDescription o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsArrayBoilerplateDescription());
  {
    Object flags__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsSmi());
  }
  {
    Object constant_elements__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, constant_elements__value);
    CHECK(constant_elements__value.IsFixedArrayBase());
  }
}
void TorqueGeneratedClassVerifiers::MicrotaskVerify(Microtask o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsMicrotask());
}
void TorqueGeneratedClassVerifiers::CallbackTaskVerify(CallbackTask o, Isolate* isolate) {
  o.MicrotaskVerify(isolate);
  CHECK(o.IsCallbackTask());
  {
    Object callback__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, callback__value);
    CHECK(callback__value.IsForeign());
  }
  {
    Object data__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, data__value);
    CHECK(data__value.IsForeign());
  }
}
void TorqueGeneratedClassVerifiers::CallableTaskVerify(CallableTask o, Isolate* isolate) {
  o.MicrotaskVerify(isolate);
  CHECK(o.IsCallableTask());
  {
    Object callable__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, callable__value);
    CHECK(callable__value.IsJSReceiver());
  }
  {
    Object context__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, context__value);
    CHECK(context__value.IsContext());
  }
}
void TorqueGeneratedClassVerifiers::ModuleVerify(Module o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsModule());
  {
    Object exports__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, exports__value);
    CHECK(exports__value.IsObjectHashTable());
  }
  {
    Object hash__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, hash__value);
    CHECK(hash__value.IsSmi());
  }
  {
    Object status__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, status__value);
    CHECK(status__value.IsSmi());
  }
  {
    Object module_namespace__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, module_namespace__value);
    CHECK(module_namespace__value.IsOddball() || module_namespace__value.IsJSModuleNamespace());
  }
  {
    Object exception__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, exception__value);
  }
}
void TorqueGeneratedClassVerifiers::JSModuleNamespaceVerify(JSModuleNamespace o, Isolate* isolate) {
  o.JSSpecialObjectVerify(isolate);
  CHECK(o.IsJSModuleNamespace());
  {
    Object module__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, module__value);
    CHECK(module__value.IsModule());
  }
}
void TorqueGeneratedClassVerifiers::PromiseReactionVerify(PromiseReaction o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsPromiseReaction());
  {
    Object next__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, next__value);
    CHECK(next__value.IsSmi() || next__value.IsPromiseReaction());
  }
  {
    Object reject_handler__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, reject_handler__value);
    CHECK(reject_handler__value.IsOddball() || reject_handler__value.IsJSObject() || reject_handler__value.IsJSProxy() || reject_handler__value.IsJSBoundFunction() || reject_handler__value.IsJSFunction());
  }
  {
    Object fulfill_handler__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, fulfill_handler__value);
    CHECK(fulfill_handler__value.IsOddball() || fulfill_handler__value.IsJSObject() || fulfill_handler__value.IsJSProxy() || fulfill_handler__value.IsJSBoundFunction() || fulfill_handler__value.IsJSFunction());
  }
  {
    Object promise_or_capability__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, promise_or_capability__value);
    CHECK(promise_or_capability__value.IsOddball() || promise_or_capability__value.IsJSPromise() || promise_or_capability__value.IsPromiseCapability());
  }
  {
    Object continuation_preserved_embedder_data__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, continuation_preserved_embedder_data__value);
  }
}
void TorqueGeneratedClassVerifiers::PromiseReactionJobTaskVerify(PromiseReactionJobTask o, Isolate* isolate) {
  o.MicrotaskVerify(isolate);
  CHECK(o.IsPromiseReactionJobTask());
  {
    Object argument__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, argument__value);
  }
  {
    Object context__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, context__value);
    CHECK(context__value.IsContext());
  }
  {
    Object handler__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, handler__value);
    CHECK(handler__value.IsOddball() || handler__value.IsJSObject() || handler__value.IsJSProxy() || handler__value.IsJSBoundFunction() || handler__value.IsJSFunction());
  }
  {
    Object promise_or_capability__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, promise_or_capability__value);
    CHECK(promise_or_capability__value.IsOddball() || promise_or_capability__value.IsJSPromise() || promise_or_capability__value.IsPromiseCapability());
  }
  {
    Object continuation_preserved_embedder_data__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, continuation_preserved_embedder_data__value);
  }
}
void TorqueGeneratedClassVerifiers::PromiseFulfillReactionJobTaskVerify(PromiseFulfillReactionJobTask o, Isolate* isolate) {
  o.PromiseReactionJobTaskVerify(isolate);
  CHECK(o.IsPromiseFulfillReactionJobTask());
}
void TorqueGeneratedClassVerifiers::PromiseRejectReactionJobTaskVerify(PromiseRejectReactionJobTask o, Isolate* isolate) {
  o.PromiseReactionJobTaskVerify(isolate);
  CHECK(o.IsPromiseRejectReactionJobTask());
}
void TorqueGeneratedClassVerifiers::PromiseResolveThenableJobTaskVerify(PromiseResolveThenableJobTask o, Isolate* isolate) {
  o.MicrotaskVerify(isolate);
  CHECK(o.IsPromiseResolveThenableJobTask());
  {
    Object context__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, context__value);
    CHECK(context__value.IsContext());
  }
  {
    Object promise_to_resolve__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, promise_to_resolve__value);
    CHECK(promise_to_resolve__value.IsJSPromise());
  }
  {
    Object thenable__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, thenable__value);
    CHECK(thenable__value.IsJSReceiver());
  }
  {
    Object then__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, then__value);
    CHECK(then__value.IsJSReceiver());
  }
}
void TorqueGeneratedClassVerifiers::PropertyArrayVerify(PropertyArray o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsPropertyArray());
  {
    Object length_and_hash__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, length_and_hash__value);
    CHECK(length_and_hash__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::PropertyCellVerify(PropertyCell o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsPropertyCell());
  {
    Object name__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, name__value);
    CHECK(name__value.IsString() || name__value.IsSymbol() || name__value.IsSymbol());
  }
  {
    Object property_details_raw__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, property_details_raw__value);
    CHECK(property_details_raw__value.IsSmi());
  }
  {
    Object value__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, value__value);
  }
  {
    Object dependent_code__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, dependent_code__value);
    CHECK(dependent_code__value.IsWeakFixedArray());
  }
}
void TorqueGeneratedClassVerifiers::PropertyDescriptorObjectVerify(PropertyDescriptorObject o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsPropertyDescriptorObject());
  {
    Object flags__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsSmi());
  }
  {
    Object value__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, value__value);
    CHECK(value__value.IsJSReceiver() || value__value.IsOddball() || value__value.IsOddball() || value__value.IsOddball() || value__value.IsOddball() || value__value.IsSymbol() || value__value.IsString() || value__value.IsBigInt() || value__value.IsHeapNumber() || value__value.IsSmi() || value__value.IsOddball());
  }
  {
    Object get__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, get__value);
    CHECK(get__value.IsJSReceiver() || get__value.IsOddball() || get__value.IsOddball() || get__value.IsOddball() || get__value.IsOddball() || get__value.IsSymbol() || get__value.IsString() || get__value.IsBigInt() || get__value.IsHeapNumber() || get__value.IsSmi() || get__value.IsOddball());
  }
  {
    Object set__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, set__value);
    CHECK(set__value.IsJSReceiver() || set__value.IsOddball() || set__value.IsOddball() || set__value.IsOddball() || set__value.IsOddball() || set__value.IsSymbol() || set__value.IsString() || set__value.IsBigInt() || set__value.IsHeapNumber() || set__value.IsSmi() || set__value.IsOddball());
  }
}
void TorqueGeneratedClassVerifiers::PrototypeInfoVerify(PrototypeInfo o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsPrototypeInfo());
  {
    Object module_namespace__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, module_namespace__value);
    CHECK(module_namespace__value.IsOddball() || module_namespace__value.IsJSModuleNamespace());
  }
  {
    Object prototype_users__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, prototype_users__value);
    CHECK(prototype_users__value.IsSmi() || prototype_users__value.IsWeakArrayList());
  }
  {
    Object prototype_chain_enum_cache__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, prototype_chain_enum_cache__value);
    CHECK(prototype_chain_enum_cache__value.IsOddball() || prototype_chain_enum_cache__value.IsFixedArray() || prototype_chain_enum_cache__value.IsSmi());
  }
  {
    Object registry_slot__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, registry_slot__value);
    CHECK(registry_slot__value.IsSmi());
  }
  {
    MaybeObject object_create_map__value = TaggedField<MaybeObject, 20>::load(o, 0);
    MaybeObject::VerifyMaybeObjectPointer(isolate, object_create_map__value);
    CHECK(object_create_map__value.IsCleared() || (!object_create_map__value.IsWeak() && object_create_map__value.GetHeapObjectOrSmi().IsOddball()) || (object_create_map__value.IsWeak() && object_create_map__value.GetHeapObjectOrSmi().IsMap()));
  }
  {
    Object bit_field__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, bit_field__value);
    CHECK(bit_field__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::ScriptVerify(Script o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsScript());
  {
    Object source__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, source__value);
    CHECK(source__value.IsOddball() || source__value.IsString());
  }
  {
    Object name__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, name__value);
  }
  {
    Object line_offset__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, line_offset__value);
    CHECK(line_offset__value.IsSmi());
  }
  {
    Object column_offset__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, column_offset__value);
    CHECK(column_offset__value.IsSmi());
  }
  {
    Object context_data__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, context_data__value);
    CHECK(context_data__value.IsOddball() || context_data__value.IsSymbol() || context_data__value.IsSmi());
  }
  {
    Object script_type__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, script_type__value);
    CHECK(script_type__value.IsSmi());
  }
  {
    Object line_ends__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, line_ends__value);
    CHECK(line_ends__value.IsOddball() || line_ends__value.IsFixedArray());
  }
  {
    Object id__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, id__value);
    CHECK(id__value.IsSmi());
  }
  {
    Object eval_from_shared_or_wrapped_arguments__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, eval_from_shared_or_wrapped_arguments__value);
    CHECK(eval_from_shared_or_wrapped_arguments__value.IsOddball() || eval_from_shared_or_wrapped_arguments__value.IsFixedArray() || eval_from_shared_or_wrapped_arguments__value.IsSharedFunctionInfo());
  }
  {
    Object eval_from_position__value = TaggedField<Object, 40>::load(o, 0);
    Object::VerifyPointer(isolate, eval_from_position__value);
    CHECK(eval_from_position__value.IsSmi() || eval_from_position__value.IsForeign());
  }
  {
    Object shared_function_infos__value = TaggedField<Object, 44>::load(o, 0);
    Object::VerifyPointer(isolate, shared_function_infos__value);
    CHECK(shared_function_infos__value.IsWeakFixedArray() || shared_function_infos__value.IsWeakArrayList());
  }
  {
    Object flags__value = TaggedField<Object, 48>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsSmi());
  }
  {
    Object source_url__value = TaggedField<Object, 52>::load(o, 0);
    Object::VerifyPointer(isolate, source_url__value);
    CHECK(source_url__value.IsOddball() || source_url__value.IsString());
  }
  {
    Object source_mapping_url__value = TaggedField<Object, 56>::load(o, 0);
    Object::VerifyPointer(isolate, source_mapping_url__value);
  }
  {
    Object host_defined_options__value = TaggedField<Object, 60>::load(o, 0);
    Object::VerifyPointer(isolate, host_defined_options__value);
    CHECK(host_defined_options__value.IsFixedArray());
  }
}
void TorqueGeneratedClassVerifiers::PreparseDataVerify(PreparseData o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsPreparseData());
}
void TorqueGeneratedClassVerifiers::InterpreterDataVerify(InterpreterData o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsInterpreterData());
  {
    Object bytecode_array__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, bytecode_array__value);
    CHECK(bytecode_array__value.IsBytecodeArray());
  }
  {
    Object interpreter_trampoline__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, interpreter_trampoline__value);
    CHECK(interpreter_trampoline__value.IsCode());
  }
}
void TorqueGeneratedClassVerifiers::SharedFunctionInfoVerify(SharedFunctionInfo o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsSharedFunctionInfo());
  {
    Object function_data__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, function_data__value);
  }
  {
    Object name_or_scope_info__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, name_or_scope_info__value);
    CHECK(name_or_scope_info__value.IsString() || name_or_scope_info__value.IsSmi() || name_or_scope_info__value.IsScopeInfo());
  }
  {
    Object outer_scope_info_or_feedback_metadata__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, outer_scope_info_or_feedback_metadata__value);
    CHECK(outer_scope_info_or_feedback_metadata__value.IsHeapObject());
  }
  {
    Object script_or_debug_info__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, script_or_debug_info__value);
    CHECK(script_or_debug_info__value.IsOddball() || script_or_debug_info__value.IsDebugInfo() || script_or_debug_info__value.IsScript());
  }
}
void TorqueGeneratedClassVerifiers::UncompiledDataVerify(UncompiledData o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsUncompiledData());
  {
    Object inferred_name__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, inferred_name__value);
    CHECK(inferred_name__value.IsString());
  }
}
void TorqueGeneratedClassVerifiers::UncompiledDataWithoutPreparseDataVerify(UncompiledDataWithoutPreparseData o, Isolate* isolate) {
  o.UncompiledDataVerify(isolate);
  CHECK(o.IsUncompiledDataWithoutPreparseData());
}
void TorqueGeneratedClassVerifiers::UncompiledDataWithPreparseDataVerify(UncompiledDataWithPreparseData o, Isolate* isolate) {
  o.UncompiledDataVerify(isolate);
  CHECK(o.IsUncompiledDataWithPreparseData());
  {
    Object preparse_data__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, preparse_data__value);
    CHECK(preparse_data__value.IsPreparseData());
  }
}
void TorqueGeneratedClassVerifiers::OnHeapBasicBlockProfilerDataVerify(OnHeapBasicBlockProfilerData o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsOnHeapBasicBlockProfilerData());
  {
    Object block_ids__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, block_ids__value);
    CHECK(block_ids__value.IsByteArray());
  }
  {
    Object counts__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, counts__value);
    CHECK(counts__value.IsByteArray());
  }
  {
    Object name__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, name__value);
    CHECK(name__value.IsString());
  }
  {
    Object schedule__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, schedule__value);
    CHECK(schedule__value.IsString());
  }
  {
    Object code__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, code__value);
    CHECK(code__value.IsString());
  }
  {
    Object hash__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, hash__value);
    CHECK(hash__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::SourceTextModuleVerify(SourceTextModule o, Isolate* isolate) {
  o.ModuleVerify(isolate);
  CHECK(o.IsSourceTextModule());
  {
    Object code__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, code__value);
    CHECK(code__value.IsJSFunction() || code__value.IsJSGeneratorObject() || code__value.IsSharedFunctionInfo() || code__value.IsFixedArray());
  }
  {
    Object regular_exports__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, regular_exports__value);
    CHECK(regular_exports__value.IsFixedArray());
  }
  {
    Object regular_imports__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, regular_imports__value);
    CHECK(regular_imports__value.IsFixedArray());
  }
  {
    Object requested_modules__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, requested_modules__value);
    CHECK(requested_modules__value.IsFixedArray());
  }
  {
    Object script__value = TaggedField<Object, 40>::load(o, 0);
    Object::VerifyPointer(isolate, script__value);
    CHECK(script__value.IsScript());
  }
  {
    Object import_meta__value = TaggedField<Object, 44>::load(o, 0);
    Object::VerifyPointer(isolate, import_meta__value);
    CHECK(import_meta__value.IsJSObject() || import_meta__value.IsOddball());
  }
  {
    Object async_parent_modules__value = TaggedField<Object, 48>::load(o, 0);
    Object::VerifyPointer(isolate, async_parent_modules__value);
    CHECK(async_parent_modules__value.IsArrayList());
  }
  {
    Object top_level_capability__value = TaggedField<Object, 52>::load(o, 0);
    Object::VerifyPointer(isolate, top_level_capability__value);
    CHECK(top_level_capability__value.IsOddball() || top_level_capability__value.IsJSPromise());
  }
  {
    Object dfs_index__value = TaggedField<Object, 56>::load(o, 0);
    Object::VerifyPointer(isolate, dfs_index__value);
    CHECK(dfs_index__value.IsSmi());
  }
  {
    Object dfs_ancestor_index__value = TaggedField<Object, 60>::load(o, 0);
    Object::VerifyPointer(isolate, dfs_ancestor_index__value);
    CHECK(dfs_ancestor_index__value.IsSmi());
  }
  {
    Object pending_async_dependencies__value = TaggedField<Object, 64>::load(o, 0);
    Object::VerifyPointer(isolate, pending_async_dependencies__value);
    CHECK(pending_async_dependencies__value.IsSmi());
  }
  {
    Object flags__value = TaggedField<Object, 68>::load(o, 0);
    Object::VerifyPointer(isolate, flags__value);
    CHECK(flags__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::SourceTextModuleInfoEntryVerify(SourceTextModuleInfoEntry o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsSourceTextModuleInfoEntry());
  {
    Object export_name__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, export_name__value);
    CHECK(export_name__value.IsOddball() || export_name__value.IsString());
  }
  {
    Object local_name__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, local_name__value);
    CHECK(local_name__value.IsOddball() || local_name__value.IsString());
  }
  {
    Object import_name__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, import_name__value);
    CHECK(import_name__value.IsOddball() || import_name__value.IsString());
  }
  {
    Object module_request__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, module_request__value);
    CHECK(module_request__value.IsSmi());
  }
  {
    Object cell_index__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, cell_index__value);
    CHECK(cell_index__value.IsSmi());
  }
  {
    Object beg_pos__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, beg_pos__value);
    CHECK(beg_pos__value.IsSmi());
  }
  {
    Object end_pos__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, end_pos__value);
    CHECK(end_pos__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::StackFrameInfoVerify(StackFrameInfo o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsStackFrameInfo());
  {
    Object line_number__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, line_number__value);
    CHECK(line_number__value.IsSmi());
  }
  {
    Object column_number__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, column_number__value);
    CHECK(column_number__value.IsSmi());
  }
  {
    Object promise_combinator_index__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, promise_combinator_index__value);
    CHECK(promise_combinator_index__value.IsSmi());
  }
  {
    Object script_id__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, script_id__value);
    CHECK(script_id__value.IsSmi());
  }
  {
    Object wasm_function_index__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, wasm_function_index__value);
    CHECK(wasm_function_index__value.IsSmi());
  }
  {
    Object script_name__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, script_name__value);
  }
  {
    Object script_name_or_source_url__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, script_name_or_source_url__value);
  }
  {
    Object function_name__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, function_name__value);
    CHECK(function_name__value.IsOddball() || function_name__value.IsOddball() || function_name__value.IsString());
  }
  {
    Object method_name__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, method_name__value);
    CHECK(method_name__value.IsOddball() || method_name__value.IsOddball() || method_name__value.IsString());
  }
  {
    Object type_name__value = TaggedField<Object, 40>::load(o, 0);
    Object::VerifyPointer(isolate, type_name__value);
    CHECK(type_name__value.IsOddball() || type_name__value.IsOddball() || type_name__value.IsString());
  }
  {
    Object eval_origin__value = TaggedField<Object, 44>::load(o, 0);
    Object::VerifyPointer(isolate, eval_origin__value);
    CHECK(eval_origin__value.IsOddball() || eval_origin__value.IsOddball() || eval_origin__value.IsString());
  }
  {
    Object wasm_module_name__value = TaggedField<Object, 48>::load(o, 0);
    Object::VerifyPointer(isolate, wasm_module_name__value);
    CHECK(wasm_module_name__value.IsOddball() || wasm_module_name__value.IsOddball() || wasm_module_name__value.IsString());
  }
  {
    Object wasm_instance__value = TaggedField<Object, 52>::load(o, 0);
    Object::VerifyPointer(isolate, wasm_instance__value);
    CHECK(wasm_instance__value.IsOddball() || wasm_instance__value.IsOddball() || wasm_instance__value.IsWasmInstanceObject());
  }
  {
    Object flag__value = TaggedField<Object, 56>::load(o, 0);
    Object::VerifyPointer(isolate, flag__value);
    CHECK(flag__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::StackTraceFrameVerify(StackTraceFrame o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsStackTraceFrame());
  {
    Object frame_array__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, frame_array__value);
    CHECK(frame_array__value.IsOddball() || frame_array__value.IsFixedArray());
  }
  {
    Object frame_index__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, frame_index__value);
    CHECK(frame_index__value.IsSmi());
  }
  {
    Object frame_info__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, frame_info__value);
    CHECK(frame_info__value.IsOddball() || frame_info__value.IsStackFrameInfo());
  }
  {
    Object id__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, id__value);
    CHECK(id__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::ConsStringVerify(ConsString o, Isolate* isolate) {
  o.StringVerify(isolate);
  CHECK(o.IsConsString());
  {
    Object first__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, first__value);
    CHECK(first__value.IsString());
  }
  {
    Object second__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, second__value);
    CHECK(second__value.IsString());
  }
}
void TorqueGeneratedClassVerifiers::ExternalStringVerify(ExternalString o, Isolate* isolate) {
  o.StringVerify(isolate);
  CHECK(o.IsExternalString());
}
void TorqueGeneratedClassVerifiers::ExternalOneByteStringVerify(ExternalOneByteString o, Isolate* isolate) {
  o.ExternalStringVerify(isolate);
  CHECK(o.IsExternalOneByteString());
}
void TorqueGeneratedClassVerifiers::ExternalTwoByteStringVerify(ExternalTwoByteString o, Isolate* isolate) {
  o.ExternalStringVerify(isolate);
  CHECK(o.IsExternalTwoByteString());
}
void TorqueGeneratedClassVerifiers::InternalizedStringVerify(InternalizedString o, Isolate* isolate) {
  o.StringVerify(isolate);
  CHECK(o.IsInternalizedString());
}
void TorqueGeneratedClassVerifiers::SeqStringVerify(SeqString o, Isolate* isolate) {
  o.StringVerify(isolate);
  CHECK(o.IsSeqString());
}
void TorqueGeneratedClassVerifiers::SeqOneByteStringVerify(SeqOneByteString o, Isolate* isolate) {
  o.SeqStringVerify(isolate);
  CHECK(o.IsSeqOneByteString());
}
void TorqueGeneratedClassVerifiers::SeqTwoByteStringVerify(SeqTwoByteString o, Isolate* isolate) {
  o.SeqStringVerify(isolate);
  CHECK(o.IsSeqTwoByteString());
}
void TorqueGeneratedClassVerifiers::SlicedStringVerify(SlicedString o, Isolate* isolate) {
  o.StringVerify(isolate);
  CHECK(o.IsSlicedString());
  {
    Object parent__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, parent__value);
    CHECK(parent__value.IsString());
  }
  {
    Object offset__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, offset__value);
    CHECK(offset__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::ThinStringVerify(ThinString o, Isolate* isolate) {
  o.StringVerify(isolate);
  CHECK(o.IsThinString());
  {
    Object actual__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, actual__value);
    CHECK(actual__value.IsString());
  }
}
void TorqueGeneratedClassVerifiers::Tuple2Verify(Tuple2 o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsTuple2());
  {
    Object value1__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, value1__value);
  }
  {
    Object value2__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, value2__value);
  }
}
void TorqueGeneratedClassVerifiers::SyntheticModuleVerify(SyntheticModule o, Isolate* isolate) {
  o.ModuleVerify(isolate);
  CHECK(o.IsSyntheticModule());
  {
    Object name__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, name__value);
    CHECK(name__value.IsString());
  }
  {
    Object export_names__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, export_names__value);
    CHECK(export_names__value.IsFixedArray());
  }
  {
    Object evaluation_steps__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, evaluation_steps__value);
    CHECK(evaluation_steps__value.IsForeign());
  }
}
void TorqueGeneratedClassVerifiers::CachedTemplateObjectVerify(CachedTemplateObject o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsCachedTemplateObject());
  {
    Object slot_id__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, slot_id__value);
    CHECK(slot_id__value.IsSmi());
  }
  {
    Object template_object__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, template_object__value);
    CHECK(template_object__value.IsJSArray());
  }
  {
    Object next__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, next__value);
    CHECK(next__value.IsOddball() || next__value.IsCachedTemplateObject());
  }
}
void TorqueGeneratedClassVerifiers::TemplateObjectDescriptionVerify(TemplateObjectDescription o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsTemplateObjectDescription());
  {
    Object raw_strings__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, raw_strings__value);
    CHECK(raw_strings__value.IsFixedArray());
  }
  {
    Object cooked_strings__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, cooked_strings__value);
    CHECK(cooked_strings__value.IsFixedArray());
  }
}
void TorqueGeneratedClassVerifiers::TemplateInfoVerify(TemplateInfo o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsTemplateInfo());
  {
    Object tag__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, tag__value);
    CHECK(tag__value.IsSmi());
  }
  {
    Object serial_number__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, serial_number__value);
    CHECK(serial_number__value.IsSmi());
  }
  {
    Object number_of_properties__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, number_of_properties__value);
    CHECK(number_of_properties__value.IsSmi());
  }
  {
    Object property_list__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, property_list__value);
    CHECK(property_list__value.IsOddball() || property_list__value.IsTemplateList());
  }
  {
    Object property_accessors__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, property_accessors__value);
    CHECK(property_accessors__value.IsOddball() || property_accessors__value.IsTemplateList());
  }
}
void TorqueGeneratedClassVerifiers::FunctionTemplateRareDataVerify(FunctionTemplateRareData o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsFunctionTemplateRareData());
  {
    Object prototype_template__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, prototype_template__value);
    CHECK(prototype_template__value.IsOddball() || prototype_template__value.IsObjectTemplateInfo());
  }
  {
    Object prototype_provider_template__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, prototype_provider_template__value);
    CHECK(prototype_provider_template__value.IsOddball() || prototype_provider_template__value.IsFunctionTemplateInfo());
  }
  {
    Object parent_template__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, parent_template__value);
    CHECK(parent_template__value.IsOddball() || parent_template__value.IsFunctionTemplateInfo());
  }
  {
    Object named_property_handler__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, named_property_handler__value);
    CHECK(named_property_handler__value.IsOddball() || named_property_handler__value.IsInterceptorInfo());
  }
  {
    Object indexed_property_handler__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, indexed_property_handler__value);
    CHECK(indexed_property_handler__value.IsOddball() || indexed_property_handler__value.IsInterceptorInfo());
  }
  {
    Object instance_template__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, instance_template__value);
    CHECK(instance_template__value.IsOddball() || instance_template__value.IsObjectTemplateInfo());
  }
  {
    Object instance_call_handler__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, instance_call_handler__value);
    CHECK(instance_call_handler__value.IsOddball() || instance_call_handler__value.IsCallHandlerInfo());
  }
  {
    Object access_check_info__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, access_check_info__value);
    CHECK(access_check_info__value.IsOddball() || access_check_info__value.IsAccessCheckInfo());
  }
  {
    Object c_function__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, c_function__value);
    CHECK(c_function__value.IsSmi() || c_function__value.IsForeign());
  }
  {
    Object c_signature__value = TaggedField<Object, 40>::load(o, 0);
    Object::VerifyPointer(isolate, c_signature__value);
    CHECK(c_signature__value.IsSmi() || c_signature__value.IsForeign());
  }
}
void TorqueGeneratedClassVerifiers::FunctionTemplateInfoVerify(FunctionTemplateInfo o, Isolate* isolate) {
  o.TemplateInfoVerify(isolate);
  CHECK(o.IsFunctionTemplateInfo());
  {
    Object call_code__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, call_code__value);
    CHECK(call_code__value.IsOddball() || call_code__value.IsCallHandlerInfo());
  }
  {
    Object class_name__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, class_name__value);
    CHECK(class_name__value.IsOddball() || class_name__value.IsString());
  }
  {
    Object signature__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, signature__value);
    CHECK(signature__value.IsOddball() || signature__value.IsFunctionTemplateInfo());
  }
  {
    Object rare_data__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, rare_data__value);
    CHECK(rare_data__value.IsOddball() || rare_data__value.IsFunctionTemplateRareData());
  }
  {
    Object shared_function_info__value = TaggedField<Object, 40>::load(o, 0);
    Object::VerifyPointer(isolate, shared_function_info__value);
    CHECK(shared_function_info__value.IsOddball() || shared_function_info__value.IsSharedFunctionInfo());
  }
  {
    Object flag__value = TaggedField<Object, 44>::load(o, 0);
    Object::VerifyPointer(isolate, flag__value);
    CHECK(flag__value.IsSmi());
  }
  {
    Object length__value = TaggedField<Object, 48>::load(o, 0);
    Object::VerifyPointer(isolate, length__value);
    CHECK(length__value.IsSmi());
  }
  {
    Object cached_property_name__value = TaggedField<Object, 52>::load(o, 0);
    Object::VerifyPointer(isolate, cached_property_name__value);
  }
}
void TorqueGeneratedClassVerifiers::ObjectTemplateInfoVerify(ObjectTemplateInfo o, Isolate* isolate) {
  o.TemplateInfoVerify(isolate);
  CHECK(o.IsObjectTemplateInfo());
  {
    Object constructor__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, constructor__value);
    CHECK(constructor__value.IsOddball() || constructor__value.IsFunctionTemplateInfo());
  }
  {
    Object data__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, data__value);
    CHECK(data__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::WasmExportedFunctionDataVerify(WasmExportedFunctionData o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsWasmExportedFunctionData());
  {
    Object wrapper_code__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, wrapper_code__value);
    CHECK(wrapper_code__value.IsCode());
  }
  {
    Object instance__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, instance__value);
    CHECK(instance__value.IsWasmInstanceObject());
  }
  {
    Object jump_table_offset__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, jump_table_offset__value);
    CHECK(jump_table_offset__value.IsSmi());
  }
  {
    Object function_index__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, function_index__value);
    CHECK(function_index__value.IsSmi());
  }
  {
    Object c_wrapper_code__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, c_wrapper_code__value);
  }
  {
    Object wasm_call_target__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, wasm_call_target__value);
    CHECK(wasm_call_target__value.IsSmi() || wasm_call_target__value.IsForeign());
  }
  {
    Object packed_args_size__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, packed_args_size__value);
    CHECK(packed_args_size__value.IsSmi());
  }
  {
    Object signature_type__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, signature_type__value);
    CHECK(signature_type__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::WasmJSFunctionDataVerify(WasmJSFunctionData o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsWasmJSFunctionData());
  {
    Object callable__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, callable__value);
    CHECK(callable__value.IsJSReceiver());
  }
  {
    Object wrapper_code__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, wrapper_code__value);
    CHECK(wrapper_code__value.IsCode());
  }
  {
    Object serialized_return_count__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, serialized_return_count__value);
    CHECK(serialized_return_count__value.IsSmi());
  }
  {
    Object serialized_parameter_count__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, serialized_parameter_count__value);
    CHECK(serialized_parameter_count__value.IsSmi());
  }
  {
    Object serialized_signature__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, serialized_signature__value);
    CHECK(serialized_signature__value.IsByteArray());
  }
}
void TorqueGeneratedClassVerifiers::WasmCapiFunctionDataVerify(WasmCapiFunctionData o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsWasmCapiFunctionData());
  {
    Object embedder_data__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, embedder_data__value);
    CHECK(embedder_data__value.IsForeign());
  }
  {
    Object wrapper_code__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, wrapper_code__value);
    CHECK(wrapper_code__value.IsCode());
  }
  {
    Object serialized_signature__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, serialized_signature__value);
    CHECK(serialized_signature__value.IsByteArray());
  }
}
void TorqueGeneratedClassVerifiers::WasmIndirectFunctionTableVerify(WasmIndirectFunctionTable o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsWasmIndirectFunctionTable());
  {
    Object managed_native_allocations__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, managed_native_allocations__value);
    CHECK(managed_native_allocations__value.IsOddball() || managed_native_allocations__value.IsForeign());
  }
  {
    Object refs__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, refs__value);
    CHECK(refs__value.IsFixedArray());
  }
}
void TorqueGeneratedClassVerifiers::WasmExceptionTagVerify(WasmExceptionTag o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsWasmExceptionTag());
  {
    Object index__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, index__value);
    CHECK(index__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::WasmModuleObjectVerify(WasmModuleObject o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsWasmModuleObject());
  {
    Object native_module__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, native_module__value);
    CHECK(native_module__value.IsForeign());
  }
  {
    Object export_wrappers__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, export_wrappers__value);
    CHECK(export_wrappers__value.IsFixedArray());
  }
  {
    Object script__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, script__value);
    CHECK(script__value.IsScript());
  }
}
void TorqueGeneratedClassVerifiers::WasmTableObjectVerify(WasmTableObject o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsWasmTableObject());
  {
    Object entries__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, entries__value);
    CHECK(entries__value.IsFixedArray());
  }
  {
    Object current_length__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, current_length__value);
    CHECK(current_length__value.IsSmi());
  }
  {
    Object maximum_length__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, maximum_length__value);
    CHECK(maximum_length__value.IsOddball() || maximum_length__value.IsHeapNumber() || maximum_length__value.IsSmi());
  }
  {
    Object dispatch_tables__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, dispatch_tables__value);
    CHECK(dispatch_tables__value.IsFixedArray());
  }
  {
    Object raw_type__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, raw_type__value);
    CHECK(raw_type__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::WasmMemoryObjectVerify(WasmMemoryObject o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsWasmMemoryObject());
  {
    Object array_buffer__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, array_buffer__value);
    CHECK(array_buffer__value.IsJSArrayBuffer());
  }
  {
    Object maximum_pages__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, maximum_pages__value);
    CHECK(maximum_pages__value.IsSmi());
  }
  {
    Object instances__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, instances__value);
    CHECK(instances__value.IsOddball() || instances__value.IsWeakArrayList());
  }
}
void TorqueGeneratedClassVerifiers::WasmGlobalObjectVerify(WasmGlobalObject o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsWasmGlobalObject());
  {
    Object untagged_buffer__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, untagged_buffer__value);
    CHECK(untagged_buffer__value.IsOddball() || untagged_buffer__value.IsJSArrayBuffer());
  }
  {
    Object tagged_buffer__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, tagged_buffer__value);
    CHECK(tagged_buffer__value.IsOddball() || tagged_buffer__value.IsFixedArray());
  }
  {
    Object offset__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, offset__value);
    CHECK(offset__value.IsSmi());
  }
  {
    Object raw_type__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, raw_type__value);
    CHECK(raw_type__value.IsSmi());
  }
  {
    Object is_mutable__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, is_mutable__value);
    CHECK(is_mutable__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::WasmExceptionObjectVerify(WasmExceptionObject o, Isolate* isolate) {
  o.JSObjectVerify(isolate);
  CHECK(o.IsWasmExceptionObject());
  {
    Object serialized_signature__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, serialized_signature__value);
    CHECK(serialized_signature__value.IsByteArray());
  }
  {
    Object exception_tag__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, exception_tag__value);
    CHECK(exception_tag__value.IsHeapObject());
  }
}
void TorqueGeneratedClassVerifiers::AsmWasmDataVerify(AsmWasmData o, Isolate* isolate) {
  o.StructVerify(isolate);
  CHECK(o.IsAsmWasmData());
  {
    Object managed_native_module__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, managed_native_module__value);
    CHECK(managed_native_module__value.IsForeign());
  }
  {
    Object export_wrappers__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, export_wrappers__value);
    CHECK(export_wrappers__value.IsFixedArray());
  }
  {
    Object uses_bitset__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, uses_bitset__value);
    CHECK(uses_bitset__value.IsHeapNumber());
  }
}
void TorqueGeneratedClassVerifiers::WasmTypeInfoVerify(WasmTypeInfo o, Isolate* isolate) {
  o.ForeignVerify(isolate);
  CHECK(o.IsWasmTypeInfo());
  {
    Object parent__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, parent__value);
    CHECK(parent__value.IsMap());
  }
  {
    Object subtypes__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, subtypes__value);
    CHECK(subtypes__value.IsArrayList());
  }
}
void TorqueGeneratedClassVerifiers::WasmStructVerify(WasmStruct o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsWasmStruct());
}
void TorqueGeneratedClassVerifiers::WasmArrayVerify(WasmArray o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsWasmArray());
}
void TorqueGeneratedClassVerifiers::InternalClassVerify(InternalClass o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsInternalClass());
  {
    Object a__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, a__value);
    CHECK(a__value.IsSmi());
  }
  {
    Object b__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, b__value);
    CHECK(b__value.IsHeapNumber() || b__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::SmiPairVerify(SmiPair o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsSmiPair());
  {
    Object a__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, a__value);
    CHECK(a__value.IsSmi());
  }
  {
    Object b__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, b__value);
    CHECK(b__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::SmiBoxVerify(SmiBox o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsSmiBox());
  {
    Object value__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, value__value);
    CHECK(value__value.IsSmi());
  }
  {
    Object unrelated__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, unrelated__value);
    CHECK(unrelated__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::ExportedSubClassBaseVerify(ExportedSubClassBase o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsExportedSubClassBase());
  {
    Object a__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, a__value);
    CHECK(a__value.IsHeapObject());
  }
  {
    Object b__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, b__value);
    CHECK(b__value.IsHeapObject());
  }
}
void TorqueGeneratedClassVerifiers::ExportedSubClassVerify(ExportedSubClass o, Isolate* isolate) {
  o.ExportedSubClassBaseVerify(isolate);
  CHECK(o.IsExportedSubClass());
  {
    Object e_field__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, e_field__value);
    CHECK(e_field__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::AbstractInternalClassVerify(AbstractInternalClass o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsAbstractInternalClass());
}
void TorqueGeneratedClassVerifiers::AbstractInternalClassSubclass1Verify(AbstractInternalClassSubclass1 o, Isolate* isolate) {
  o.AbstractInternalClassVerify(isolate);
  CHECK(o.IsAbstractInternalClassSubclass1());
}
void TorqueGeneratedClassVerifiers::AbstractInternalClassSubclass2Verify(AbstractInternalClassSubclass2 o, Isolate* isolate) {
  o.AbstractInternalClassVerify(isolate);
  CHECK(o.IsAbstractInternalClassSubclass2());
}
void TorqueGeneratedClassVerifiers::InternalClassWithSmiElementsVerify(InternalClassWithSmiElements o, Isolate* isolate) {
  o.FixedArrayBaseVerify(isolate);
  CHECK(o.IsInternalClassWithSmiElements());
  {
    Object data__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, data__value);
    CHECK(data__value.IsSmi());
  }
  {
    Object object__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, object__value);
    CHECK(object__value.IsOddball());
  }
  for (int i = 0; i < TaggedField<Smi, InternalClassWithSmiElements::kLengthOffset>::load(o).value(); ++i) {
    Object entries__value = TaggedField<Object, 16>::load(o, 0 + i * kTaggedSize);
    Object::VerifyPointer(isolate, entries__value);
    CHECK(entries__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::InternalClassWithStructElementsVerify(InternalClassWithStructElements o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsInternalClassWithStructElements());
  {
    Object count__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, count__value);
    CHECK(count__value.IsSmi());
  }
  {
    Object data__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, data__value);
    CHECK(data__value.IsSmi());
  }
  {
    Object object__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, object__value);
  }
  for (int i = 0; i < TaggedField<Smi, InternalClassWithStructElements::kCountOffset>::load(o).value(); ++i) {
    Object entries__value = TaggedField<Object, 24>::load(o, 0 + i * kTaggedSize);
    Object::VerifyPointer(isolate, entries__value);
    CHECK(entries__value.IsSmi());
  }
  for (int i = 0; i < TaggedField<Smi, InternalClassWithStructElements::kCountOffset>::load(o).value(); ++i) {
  }
}
void TorqueGeneratedClassVerifiers::ExportedSubClass2Verify(ExportedSubClass2 o, Isolate* isolate) {
  o.ExportedSubClassBaseVerify(isolate);
  CHECK(o.IsExportedSubClass2());
  {
    Object z_field__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, z_field__value);
    CHECK(z_field__value.IsSmi());
  }
}
void TorqueGeneratedClassVerifiers::SortStateVerify(SortState o, Isolate* isolate) {
  HeapObjectVerify(o, isolate);
  CHECK(o.IsSortState());
  {
    Object receiver__value = TaggedField<Object, 4>::load(o, 0);
    Object::VerifyPointer(isolate, receiver__value);
    CHECK(receiver__value.IsJSReceiver());
  }
  {
    Object initialReceiverMap__value = TaggedField<Object, 8>::load(o, 0);
    Object::VerifyPointer(isolate, initialReceiverMap__value);
    CHECK(initialReceiverMap__value.IsMap());
  }
  {
    Object initialReceiverLength__value = TaggedField<Object, 12>::load(o, 0);
    Object::VerifyPointer(isolate, initialReceiverLength__value);
    CHECK(initialReceiverLength__value.IsHeapNumber() || initialReceiverLength__value.IsSmi());
  }
  {
    Object userCmpFn__value = TaggedField<Object, 16>::load(o, 0);
    Object::VerifyPointer(isolate, userCmpFn__value);
    CHECK(userCmpFn__value.IsOddball() || userCmpFn__value.IsJSObject() || userCmpFn__value.IsJSProxy() || userCmpFn__value.IsJSBoundFunction() || userCmpFn__value.IsJSFunction());
  }
  {
    Object sortComparePtr__value = TaggedField<Object, 20>::load(o, 0);
    Object::VerifyPointer(isolate, sortComparePtr__value);
    CHECK(sortComparePtr__value.IsSmi());
  }
  {
    Object loadFn__value = TaggedField<Object, 24>::load(o, 0);
    Object::VerifyPointer(isolate, loadFn__value);
    CHECK(loadFn__value.IsSmi());
  }
  {
    Object storeFn__value = TaggedField<Object, 28>::load(o, 0);
    Object::VerifyPointer(isolate, storeFn__value);
    CHECK(storeFn__value.IsSmi());
  }
  {
    Object deleteFn__value = TaggedField<Object, 32>::load(o, 0);
    Object::VerifyPointer(isolate, deleteFn__value);
    CHECK(deleteFn__value.IsSmi());
  }
  {
    Object canUseSameAccessorFn__value = TaggedField<Object, 36>::load(o, 0);
    Object::VerifyPointer(isolate, canUseSameAccessorFn__value);
    CHECK(canUseSameAccessorFn__value.IsSmi());
  }
  {
    Object minGallop__value = TaggedField<Object, 40>::load(o, 0);
    Object::VerifyPointer(isolate, minGallop__value);
    CHECK(minGallop__value.IsSmi());
  }
  {
    Object pendingRunsSize__value = TaggedField<Object, 44>::load(o, 0);
    Object::VerifyPointer(isolate, pendingRunsSize__value);
    CHECK(pendingRunsSize__value.IsSmi());
  }
  {
    Object pendingRuns__value = TaggedField<Object, 48>::load(o, 0);
    Object::VerifyPointer(isolate, pendingRuns__value);
    CHECK(pendingRuns__value.IsFixedArray());
  }
  {
    Object workArray__value = TaggedField<Object, 52>::load(o, 0);
    Object::VerifyPointer(isolate, workArray__value);
    CHECK(workArray__value.IsFixedArray());
  }
  {
    Object tempArray__value = TaggedField<Object, 56>::load(o, 0);
    Object::VerifyPointer(isolate, tempArray__value);
    CHECK(tempArray__value.IsFixedArray());
  }
  {
    Object sortLength__value = TaggedField<Object, 60>::load(o, 0);
    Object::VerifyPointer(isolate, sortLength__value);
    CHECK(sortLength__value.IsSmi());
  }
  {
    Object numberOfUndefined__value = TaggedField<Object, 64>::load(o, 0);
    Object::VerifyPointer(isolate, numberOfUndefined__value);
    CHECK(numberOfUndefined__value.IsSmi());
  }
}
}  // namespace internal
}  // namespace v8

#include "src/objects/object-macros-undef.h"
#endif  // VERIFY_HEAP
