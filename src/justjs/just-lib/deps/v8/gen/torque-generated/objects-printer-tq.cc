#ifdef OBJECT_PRINT
#include "src/objects/objects.h"

#include <iosfwd>

#include "torque-generated/internal-class-definitions-tq-inl.h"
#include "torque-generated/exported-class-definitions-tq-inl.h"
#include "src/objects/struct-inl.h"

#include "src/objects/template-objects-inl.h"

namespace v8 {
namespace internal {
template <>
void TorqueGeneratedStruct<Struct, HeapObject>::StructPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedStruct");
  os << '\n';
}

template <>
void TorqueGeneratedInterceptorInfo<InterceptorInfo, Struct>::InterceptorInfoPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedInterceptorInfo");
  os << "\n - getter: " << Brief(this->getter());
  os << "\n - setter: " << Brief(this->setter());
  os << "\n - query: " << Brief(this->query());
  os << "\n - descriptor: " << Brief(this->descriptor());
  os << "\n - deleter: " << Brief(this->deleter());
  os << "\n - enumerator: " << Brief(this->enumerator());
  os << "\n - definer: " << Brief(this->definer());
  os << "\n - data: " << Brief(this->data());
  os << "\n - flags: " << this->flags();
  os << '\n';
}

template <>
void TorqueGeneratedAccessCheckInfo<AccessCheckInfo, Struct>::AccessCheckInfoPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedAccessCheckInfo");
  os << "\n - callback: " << Brief(this->callback());
  os << "\n - named_interceptor: " << Brief(this->named_interceptor());
  os << "\n - indexed_interceptor: " << Brief(this->indexed_interceptor());
  os << "\n - data: " << Brief(this->data());
  os << '\n';
}

template <>
void TorqueGeneratedAccessorInfo<AccessorInfo, Struct>::AccessorInfoPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedAccessorInfo");
  os << "\n - name: " << Brief(this->name());
  os << "\n - flags: " << this->flags();
  os << "\n - expected_receiver_type: " << Brief(this->expected_receiver_type());
  os << "\n - setter: " << Brief(this->setter());
  os << "\n - getter: " << Brief(this->getter());
  os << "\n - js_getter: " << Brief(this->js_getter());
  os << "\n - data: " << Brief(this->data());
  os << '\n';
}

template <>
void TorqueGeneratedSloppyArgumentsElements<SloppyArgumentsElements, FixedArrayBase>::SloppyArgumentsElementsPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedSloppyArgumentsElements");
  os << "\n - length: " << this->length();
  os << "\n - context: " << Brief(this->context());
  os << "\n - arguments: " << Brief(this->arguments());
  os << '\n';
}

template <>
void TorqueGeneratedAliasedArgumentsEntry<AliasedArgumentsEntry, Struct>::AliasedArgumentsEntryPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedAliasedArgumentsEntry");
  os << "\n - aliased_context_slot: " << this->aliased_context_slot();
  os << '\n';
}

template <>
void TorqueGeneratedCell<Cell, HeapObject>::CellPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedCell");
  os << "\n - value: " << Brief(this->value());
  os << '\n';
}

template <>
void TorqueGeneratedBreakPoint<BreakPoint, Struct>::BreakPointPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedBreakPoint");
  os << "\n - id: " << this->id();
  os << "\n - condition: " << Brief(this->condition());
  os << '\n';
}

template <>
void TorqueGeneratedBreakPointInfo<BreakPointInfo, Struct>::BreakPointInfoPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedBreakPointInfo");
  os << "\n - source_position: " << this->source_position();
  os << "\n - break_points: " << Brief(this->break_points());
  os << '\n';
}

template <>
void TorqueGeneratedDebugInfo<DebugInfo, Struct>::DebugInfoPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedDebugInfo");
  os << "\n - shared: " << Brief(this->shared());
  os << "\n - debugger_hints: " << this->debugger_hints();
  os << "\n - script: " << Brief(this->script());
  os << "\n - original_bytecode_array: " << Brief(this->original_bytecode_array());
  os << "\n - debug_bytecode_array: " << Brief(this->debug_bytecode_array());
  os << "\n - break_points: " << Brief(this->break_points());
  os << "\n - flags: " << this->flags();
  os << "\n - coverage_info: " << Brief(this->coverage_info());
  os << '\n';
}

template <>
void TorqueGeneratedWasmValue<WasmValue, Struct>::WasmValuePrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedWasmValue");
  os << "\n - value_type: " << this->value_type();
  os << "\n - bytes_or_ref: " << Brief(this->bytes_or_ref());
  os << '\n';
}

template <>
void TorqueGeneratedEnumCache<EnumCache, Struct>::EnumCachePrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedEnumCache");
  os << "\n - keys: " << Brief(this->keys());
  os << "\n - indices: " << Brief(this->indices());
  os << '\n';
}

template <>
void TorqueGeneratedPropertyDescriptorObject<PropertyDescriptorObject, Struct>::PropertyDescriptorObjectPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedPropertyDescriptorObject");
  os << "\n - flags: " << this->flags();
  os << "\n - value: " << Brief(this->value());
  os << "\n - get: " << Brief(this->get());
  os << "\n - set: " << Brief(this->set());
  os << '\n';
}

template <>
void TorqueGeneratedOnHeapBasicBlockProfilerData<OnHeapBasicBlockProfilerData, HeapObject>::OnHeapBasicBlockProfilerDataPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedOnHeapBasicBlockProfilerData");
  os << "\n - block_ids: " << Brief(this->block_ids());
  os << "\n - counts: " << Brief(this->counts());
  os << "\n - name: " << Brief(this->name());
  os << "\n - schedule: " << Brief(this->schedule());
  os << "\n - code: " << Brief(this->code());
  os << "\n - hash: " << this->hash();
  os << '\n';
}

template <>
void TorqueGeneratedTuple2<Tuple2, Struct>::Tuple2Print(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedTuple2");
  os << "\n - value1: " << Brief(this->value1());
  os << "\n - value2: " << Brief(this->value2());
  os << '\n';
}

template <>
void TorqueGeneratedCachedTemplateObject<CachedTemplateObject, Struct>::CachedTemplateObjectPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedCachedTemplateObject");
  os << "\n - slot_id: " << this->slot_id();
  os << "\n - template_object: " << Brief(this->template_object());
  os << "\n - next: " << Brief(this->next());
  os << '\n';
}

template <>
void TorqueGeneratedTemplateObjectDescription<TemplateObjectDescription, Struct>::TemplateObjectDescriptionPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedTemplateObjectDescription");
  os << "\n - raw_strings: " << Brief(this->raw_strings());
  os << "\n - cooked_strings: " << Brief(this->cooked_strings());
  os << '\n';
}

template <>
void TorqueGeneratedFunctionTemplateRareData<FunctionTemplateRareData, Struct>::FunctionTemplateRareDataPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedFunctionTemplateRareData");
  os << "\n - prototype_template: " << Brief(this->prototype_template());
  os << "\n - prototype_provider_template: " << Brief(this->prototype_provider_template());
  os << "\n - parent_template: " << Brief(this->parent_template());
  os << "\n - named_property_handler: " << Brief(this->named_property_handler());
  os << "\n - indexed_property_handler: " << Brief(this->indexed_property_handler());
  os << "\n - instance_template: " << Brief(this->instance_template());
  os << "\n - instance_call_handler: " << Brief(this->instance_call_handler());
  os << "\n - access_check_info: " << Brief(this->access_check_info());
  os << "\n - c_function: " << Brief(this->c_function());
  os << "\n - c_signature: " << Brief(this->c_signature());
  os << '\n';
}

template <>
void TorqueGeneratedInternalClass<InternalClass, HeapObject>::InternalClassPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedInternalClass");
  os << "\n - a: " << this->a();
  os << "\n - b: " << Brief(this->b());
  os << '\n';
}

template <>
void TorqueGeneratedSmiPair<SmiPair, HeapObject>::SmiPairPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedSmiPair");
  os << "\n - a: " << this->a();
  os << "\n - b: " << this->b();
  os << '\n';
}

template <>
void TorqueGeneratedSmiBox<SmiBox, HeapObject>::SmiBoxPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedSmiBox");
  os << "\n - value: " << this->value();
  os << "\n - unrelated: " << this->unrelated();
  os << '\n';
}

template <>
void TorqueGeneratedExportedSubClassBase<ExportedSubClassBase, HeapObject>::ExportedSubClassBasePrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedExportedSubClassBase");
  os << "\n - a: " << Brief(this->a());
  os << "\n - b: " << Brief(this->b());
  os << '\n';
}

template <>
void TorqueGeneratedExportedSubClass<ExportedSubClass, ExportedSubClassBase>::ExportedSubClassPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedExportedSubClass");
  os << "\n - a: " << Brief(this->a());
  os << "\n - b: " << Brief(this->b());
  os << "\n - c_field: " << this->c_field();
  os << "\n - d_field: " << this->d_field();
  os << "\n - e_field: " << this->e_field();
  os << '\n';
}

template <>
void TorqueGeneratedAbstractInternalClass<AbstractInternalClass, HeapObject>::AbstractInternalClassPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedAbstractInternalClass");
  os << '\n';
}

template <>
void TorqueGeneratedAbstractInternalClassSubclass1<AbstractInternalClassSubclass1, AbstractInternalClass>::AbstractInternalClassSubclass1Print(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedAbstractInternalClassSubclass1");
  os << '\n';
}

template <>
void TorqueGeneratedAbstractInternalClassSubclass2<AbstractInternalClassSubclass2, AbstractInternalClass>::AbstractInternalClassSubclass2Print(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedAbstractInternalClassSubclass2");
  os << '\n';
}

template <>
void TorqueGeneratedInternalClassWithSmiElements<InternalClassWithSmiElements, FixedArrayBase>::InternalClassWithSmiElementsPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedInternalClassWithSmiElements");
  os << "\n - length: " << this->length();
  os << "\n - data: " << this->data();
  os << "\n - object: " << Brief(this->object());
  os << '\n';
}

template <>
void TorqueGeneratedInternalClassWithStructElements<InternalClassWithStructElements, HeapObject>::InternalClassWithStructElementsPrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedInternalClassWithStructElements");
  os << "\n - dummy1: " << this->dummy1();
  os << "\n - dummy2: " << this->dummy2();
  os << "\n - count: " << this->count();
  os << "\n - data: " << this->data();
  os << "\n - object: " << Brief(this->object());
  os << '\n';
}

template <>
void TorqueGeneratedExportedSubClass2<ExportedSubClass2, ExportedSubClassBase>::ExportedSubClass2Print(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedExportedSubClass2");
  os << "\n - a: " << Brief(this->a());
  os << "\n - b: " << Brief(this->b());
  os << "\n - x_field: " << this->x_field();
  os << "\n - y_field: " << this->y_field();
  os << "\n - z_field: " << this->z_field();
  os << '\n';
}

template <>
void TorqueGeneratedSortState<SortState, HeapObject>::SortStatePrint(std::ostream& os) {
  this->PrintHeader(os, "TorqueGeneratedSortState");
  os << "\n - receiver: " << Brief(this->receiver());
  os << "\n - initialReceiverMap: " << Brief(this->initialReceiverMap());
  os << "\n - initialReceiverLength: " << Brief(this->initialReceiverLength());
  os << "\n - userCmpFn: " << Brief(this->userCmpFn());
  os << "\n - sortComparePtr: " << this->sortComparePtr();
  os << "\n - loadFn: " << this->loadFn();
  os << "\n - storeFn: " << this->storeFn();
  os << "\n - deleteFn: " << this->deleteFn();
  os << "\n - canUseSameAccessorFn: " << this->canUseSameAccessorFn();
  os << "\n - minGallop: " << this->minGallop();
  os << "\n - pendingRunsSize: " << this->pendingRunsSize();
  os << "\n - pendingRuns: " << Brief(this->pendingRuns());
  os << "\n - workArray: " << Brief(this->workArray());
  os << "\n - tempArray: " << Brief(this->tempArray());
  os << "\n - sortLength: " << this->sortLength();
  os << "\n - numberOfUndefined: " << this->numberOfUndefined();
  os << '\n';
}

}  // namespace internal
}  // namespace v8
#endif  // OBJECT_PRINT
