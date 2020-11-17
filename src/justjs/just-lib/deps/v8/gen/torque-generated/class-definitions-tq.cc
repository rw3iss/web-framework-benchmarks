#include "torque-generated/class-definitions-tq.h"

#include "torque-generated/class-verifiers-tq.h"

#include "src/objects/class-definitions-tq-deps-inl.h"

#include "torque-generated/internal-class-definitions-tq-inl.h"

#include "torque-generated/exported-class-definitions-tq-inl.h"

namespace v8 {
namespace internal {
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedPrimitiveHeapObject<PrimitiveHeapObject, HeapObject>::PrimitiveHeapObjectVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::PrimitiveHeapObjectVerify(PrimitiveHeapObject::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedOddball<Oddball, PrimitiveHeapObject>::OddballVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::OddballVerify(Oddball::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedName<Name, PrimitiveHeapObject>::NameVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::NameVerify(Name::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSymbol<Symbol, Name>::SymbolVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SymbolVerify(Symbol::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedString<String, Name>::StringVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::StringVerify(String::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedHeapNumber<HeapNumber, PrimitiveHeapObject>::HeapNumberVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::HeapNumberVerify(HeapNumber::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedFixedArrayBase<FixedArrayBase, HeapObject>::FixedArrayBaseVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::FixedArrayBaseVerify(FixedArrayBase::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedFixedArray<FixedArray, FixedArrayBase>::FixedArrayVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::FixedArrayVerify(FixedArray::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedByteArray<ByteArray, FixedArrayBase>::ByteArrayVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ByteArrayVerify(ByteArray::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedWeakFixedArray<WeakFixedArray, HeapObject>::WeakFixedArrayVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::WeakFixedArrayVerify(WeakFixedArray::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedForeign<Foreign, HeapObject>::ForeignVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ForeignVerify(Foreign::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSObject<JSObject, JSReceiver>::JSObjectVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSObjectVerify(JSObject::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSProxy<JSProxy, JSReceiver>::JSProxyVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSProxyVerify(JSProxy::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSFunctionOrBoundFunction<JSFunctionOrBoundFunction, JSObject>::JSFunctionOrBoundFunctionVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSFunctionOrBoundFunctionVerify(JSFunctionOrBoundFunction::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSBoundFunction<JSBoundFunction, JSFunctionOrBoundFunction>::JSBoundFunctionVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSBoundFunctionVerify(JSBoundFunction::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSCustomElementsObject<JSCustomElementsObject, JSObject>::JSCustomElementsObjectVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSCustomElementsObjectVerify(JSCustomElementsObject::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSSpecialObject<JSSpecialObject, JSCustomElementsObject>::JSSpecialObjectVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSSpecialObjectVerify(JSSpecialObject::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedWeakCell<WeakCell, HeapObject>::WeakCellVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::WeakCellVerify(WeakCell::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSPromise<JSPromise, JSObject>::JSPromiseVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSPromiseVerify(JSPromise::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedStruct<Struct, HeapObject>::StructVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::StructVerify(Struct::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedPromiseCapability<PromiseCapability, Struct>::PromiseCapabilityVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::PromiseCapabilityVerify(PromiseCapability::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSArrayBufferView<JSArrayBufferView, JSObject>::JSArrayBufferViewVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSArrayBufferViewVerify(JSArrayBufferView::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSTypedArray<JSTypedArray, JSArrayBufferView>::JSTypedArrayVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSTypedArrayVerify(JSTypedArray::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedAllocationMemento<AllocationMemento, Struct>::AllocationMementoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::AllocationMementoVerify(AllocationMemento::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedCallHandlerInfo<CallHandlerInfo, Struct>::CallHandlerInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::CallHandlerInfoVerify(CallHandlerInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedInterceptorInfo<InterceptorInfo, Struct>::InterceptorInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::InterceptorInfoVerify(InterceptorInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedAccessCheckInfo<AccessCheckInfo, Struct>::AccessCheckInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::AccessCheckInfoVerify(AccessCheckInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedAccessorInfo<AccessorInfo, Struct>::AccessorInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::AccessorInfoVerify(AccessorInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSArgumentsObject<JSArgumentsObject, JSObject>::JSArgumentsObjectVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSArgumentsObjectVerify(JSArgumentsObject::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSloppyArgumentsElements<SloppyArgumentsElements, FixedArrayBase>::SloppyArgumentsElementsVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SloppyArgumentsElementsVerify(SloppyArgumentsElements::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedAliasedArgumentsEntry<AliasedArgumentsEntry, Struct>::AliasedArgumentsEntryVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::AliasedArgumentsEntryVerify(AliasedArgumentsEntry::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedCell<Cell, HeapObject>::CellVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::CellVerify(Cell::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedFixedDoubleArray<FixedDoubleArray, FixedArrayBase>::FixedDoubleArrayVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::FixedDoubleArrayVerify(FixedDoubleArray::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedBreakPoint<BreakPoint, Struct>::BreakPointVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::BreakPointVerify(BreakPoint::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedBreakPointInfo<BreakPointInfo, Struct>::BreakPointInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::BreakPointInfoVerify(BreakPointInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedDebugInfo<DebugInfo, Struct>::DebugInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::DebugInfoVerify(DebugInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedCoverageInfo<CoverageInfo, HeapObject>::CoverageInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::CoverageInfoVerify(CoverageInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedWasmValue<WasmValue, Struct>::WasmValueVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::WasmValueVerify(WasmValue::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedEnumCache<EnumCache, Struct>::EnumCacheVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::EnumCacheVerify(EnumCache::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedClassPositions<ClassPositions, Struct>::ClassPositionsVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ClassPositionsVerify(ClassPositions::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedAccessorPair<AccessorPair, Struct>::AccessorPairVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::AccessorPairVerify(AccessorPair::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedDescriptorArray<DescriptorArray, HeapObject>::DescriptorArrayVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::DescriptorArrayVerify(DescriptorArray::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedEmbedderDataArray<EmbedderDataArray, HeapObject>::EmbedderDataArrayVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::EmbedderDataArrayVerify(EmbedderDataArray::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedFeedbackCell<FeedbackCell, Struct>::FeedbackCellVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::FeedbackCellVerify(FeedbackCell::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedArrayList<ArrayList, FixedArray>::ArrayListVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ArrayListVerify(ArrayList::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedTemplateList<TemplateList, FixedArray>::TemplateListVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::TemplateListVerify(TemplateList::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedWeakArrayList<WeakArrayList, HeapObject>::WeakArrayListVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::WeakArrayListVerify(WeakArrayList::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedFreeSpace<FreeSpace, HeapObject>::FreeSpaceVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::FreeSpaceVerify(FreeSpace::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSArrayBuffer<JSArrayBuffer, JSObject>::JSArrayBufferVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSArrayBufferVerify(JSArrayBuffer::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSDataView<JSDataView, JSArrayBufferView>::JSDataViewVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSDataViewVerify(JSDataView::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSCollectionIterator<JSCollectionIterator, JSObject>::JSCollectionIteratorVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSCollectionIteratorVerify(JSCollectionIterator::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSCollection<JSCollection, JSObject>::JSCollectionVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSCollectionVerify(JSCollection::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSSet<JSSet, JSCollection>::JSSetVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSSetVerify(JSSet::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSMap<JSMap, JSCollection>::JSMapVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSMapVerify(JSMap::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSWeakCollection<JSWeakCollection, JSObject>::JSWeakCollectionVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSWeakCollectionVerify(JSWeakCollection::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSWeakSet<JSWeakSet, JSWeakCollection>::JSWeakSetVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSWeakSetVerify(JSWeakSet::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSWeakMap<JSWeakMap, JSWeakCollection>::JSWeakMapVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSWeakMapVerify(JSWeakMap::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSGeneratorObject<JSGeneratorObject, JSObject>::JSGeneratorObjectVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSGeneratorObjectVerify(JSGeneratorObject::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSAsyncFunctionObject<JSAsyncFunctionObject, JSGeneratorObject>::JSAsyncFunctionObjectVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSAsyncFunctionObjectVerify(JSAsyncFunctionObject::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSAsyncGeneratorObject<JSAsyncGeneratorObject, JSGeneratorObject>::JSAsyncGeneratorObjectVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSAsyncGeneratorObjectVerify(JSAsyncGeneratorObject::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedAsyncGeneratorRequest<AsyncGeneratorRequest, Struct>::AsyncGeneratorRequestVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::AsyncGeneratorRequestVerify(AsyncGeneratorRequest::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSGlobalProxy<JSGlobalProxy, JSSpecialObject>::JSGlobalProxyVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSGlobalProxyVerify(JSGlobalProxy::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSPrimitiveWrapper<JSPrimitiveWrapper, JSCustomElementsObject>::JSPrimitiveWrapperVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSPrimitiveWrapperVerify(JSPrimitiveWrapper::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSDate<JSDate, JSObject>::JSDateVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSDateVerify(JSDate::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSAsyncFromSyncIterator<JSAsyncFromSyncIterator, JSObject>::JSAsyncFromSyncIteratorVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSAsyncFromSyncIteratorVerify(JSAsyncFromSyncIterator::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSStringIterator<JSStringIterator, JSObject>::JSStringIteratorVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSStringIteratorVerify(JSStringIterator::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSRegExpStringIterator<JSRegExpStringIterator, JSObject>::JSRegExpStringIteratorVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSRegExpStringIteratorVerify(JSRegExpStringIterator::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSRegExp<JSRegExp, JSObject>::JSRegExpVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSRegExpVerify(JSRegExp::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSWeakRef<JSWeakRef, JSObject>::JSWeakRefVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSWeakRefVerify(JSWeakRef::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedArrayBoilerplateDescription<ArrayBoilerplateDescription, Struct>::ArrayBoilerplateDescriptionVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ArrayBoilerplateDescriptionVerify(ArrayBoilerplateDescription::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedMicrotask<Microtask, Struct>::MicrotaskVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::MicrotaskVerify(Microtask::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedCallbackTask<CallbackTask, Microtask>::CallbackTaskVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::CallbackTaskVerify(CallbackTask::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedCallableTask<CallableTask, Microtask>::CallableTaskVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::CallableTaskVerify(CallableTask::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedJSModuleNamespace<JSModuleNamespace, JSSpecialObject>::JSModuleNamespaceVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::JSModuleNamespaceVerify(JSModuleNamespace::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedPromiseReaction<PromiseReaction, Struct>::PromiseReactionVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::PromiseReactionVerify(PromiseReaction::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedPromiseReactionJobTask<PromiseReactionJobTask, Microtask>::PromiseReactionJobTaskVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::PromiseReactionJobTaskVerify(PromiseReactionJobTask::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedPromiseFulfillReactionJobTask<PromiseFulfillReactionJobTask, PromiseReactionJobTask>::PromiseFulfillReactionJobTaskVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::PromiseFulfillReactionJobTaskVerify(PromiseFulfillReactionJobTask::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedPromiseRejectReactionJobTask<PromiseRejectReactionJobTask, PromiseReactionJobTask>::PromiseRejectReactionJobTaskVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::PromiseRejectReactionJobTaskVerify(PromiseRejectReactionJobTask::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedPromiseResolveThenableJobTask<PromiseResolveThenableJobTask, Microtask>::PromiseResolveThenableJobTaskVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::PromiseResolveThenableJobTaskVerify(PromiseResolveThenableJobTask::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedPropertyDescriptorObject<PropertyDescriptorObject, Struct>::PropertyDescriptorObjectVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::PropertyDescriptorObjectVerify(PropertyDescriptorObject::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedPrototypeInfo<PrototypeInfo, Struct>::PrototypeInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::PrototypeInfoVerify(PrototypeInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedScript<Script, Struct>::ScriptVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ScriptVerify(Script::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedPreparseData<PreparseData, HeapObject>::PreparseDataVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::PreparseDataVerify(PreparseData::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedUncompiledData<UncompiledData, HeapObject>::UncompiledDataVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::UncompiledDataVerify(UncompiledData::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedUncompiledDataWithoutPreparseData<UncompiledDataWithoutPreparseData, UncompiledData>::UncompiledDataWithoutPreparseDataVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::UncompiledDataWithoutPreparseDataVerify(UncompiledDataWithoutPreparseData::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedUncompiledDataWithPreparseData<UncompiledDataWithPreparseData, UncompiledData>::UncompiledDataWithPreparseDataVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::UncompiledDataWithPreparseDataVerify(UncompiledDataWithPreparseData::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedOnHeapBasicBlockProfilerData<OnHeapBasicBlockProfilerData, HeapObject>::OnHeapBasicBlockProfilerDataVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::OnHeapBasicBlockProfilerDataVerify(OnHeapBasicBlockProfilerData::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSourceTextModule<SourceTextModule, Module>::SourceTextModuleVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SourceTextModuleVerify(SourceTextModule::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSourceTextModuleInfoEntry<SourceTextModuleInfoEntry, Struct>::SourceTextModuleInfoEntryVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SourceTextModuleInfoEntryVerify(SourceTextModuleInfoEntry::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedStackFrameInfo<StackFrameInfo, Struct>::StackFrameInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::StackFrameInfoVerify(StackFrameInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedStackTraceFrame<StackTraceFrame, Struct>::StackTraceFrameVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::StackTraceFrameVerify(StackTraceFrame::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedConsString<ConsString, String>::ConsStringVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ConsStringVerify(ConsString::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedInternalizedString<InternalizedString, String>::InternalizedStringVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::InternalizedStringVerify(InternalizedString::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSeqString<SeqString, String>::SeqStringVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SeqStringVerify(SeqString::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSeqOneByteString<SeqOneByteString, SeqString>::SeqOneByteStringVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SeqOneByteStringVerify(SeqOneByteString::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSeqTwoByteString<SeqTwoByteString, SeqString>::SeqTwoByteStringVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SeqTwoByteStringVerify(SeqTwoByteString::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSlicedString<SlicedString, String>::SlicedStringVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SlicedStringVerify(SlicedString::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedThinString<ThinString, String>::ThinStringVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ThinStringVerify(ThinString::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedTuple2<Tuple2, Struct>::Tuple2Verify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::Tuple2Verify(Tuple2::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSyntheticModule<SyntheticModule, Module>::SyntheticModuleVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SyntheticModuleVerify(SyntheticModule::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedCachedTemplateObject<CachedTemplateObject, Struct>::CachedTemplateObjectVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::CachedTemplateObjectVerify(CachedTemplateObject::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedTemplateObjectDescription<TemplateObjectDescription, Struct>::TemplateObjectDescriptionVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::TemplateObjectDescriptionVerify(TemplateObjectDescription::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedTemplateInfo<TemplateInfo, Struct>::TemplateInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::TemplateInfoVerify(TemplateInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedFunctionTemplateRareData<FunctionTemplateRareData, Struct>::FunctionTemplateRareDataVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::FunctionTemplateRareDataVerify(FunctionTemplateRareData::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedFunctionTemplateInfo<FunctionTemplateInfo, TemplateInfo>::FunctionTemplateInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::FunctionTemplateInfoVerify(FunctionTemplateInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedObjectTemplateInfo<ObjectTemplateInfo, TemplateInfo>::ObjectTemplateInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ObjectTemplateInfoVerify(ObjectTemplateInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedWasmExceptionTag<WasmExceptionTag, Struct>::WasmExceptionTagVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::WasmExceptionTagVerify(WasmExceptionTag::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedWasmTypeInfo<WasmTypeInfo, Foreign>::WasmTypeInfoVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::WasmTypeInfoVerify(WasmTypeInfo::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedWasmStruct<WasmStruct, HeapObject>::WasmStructVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::WasmStructVerify(WasmStruct::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedWasmArray<WasmArray, HeapObject>::WasmArrayVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::WasmArrayVerify(WasmArray::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedInternalClass<InternalClass, HeapObject>::InternalClassVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::InternalClassVerify(InternalClass::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSmiPair<SmiPair, HeapObject>::SmiPairVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SmiPairVerify(SmiPair::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSmiBox<SmiBox, HeapObject>::SmiBoxVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SmiBoxVerify(SmiBox::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedExportedSubClassBase<ExportedSubClassBase, HeapObject>::ExportedSubClassBaseVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ExportedSubClassBaseVerify(ExportedSubClassBase::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedExportedSubClass<ExportedSubClass, ExportedSubClassBase>::ExportedSubClassVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ExportedSubClassVerify(ExportedSubClass::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedAbstractInternalClass<AbstractInternalClass, HeapObject>::AbstractInternalClassVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::AbstractInternalClassVerify(AbstractInternalClass::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedAbstractInternalClassSubclass1<AbstractInternalClassSubclass1, AbstractInternalClass>::AbstractInternalClassSubclass1Verify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::AbstractInternalClassSubclass1Verify(AbstractInternalClassSubclass1::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedAbstractInternalClassSubclass2<AbstractInternalClassSubclass2, AbstractInternalClass>::AbstractInternalClassSubclass2Verify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::AbstractInternalClassSubclass2Verify(AbstractInternalClassSubclass2::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedInternalClassWithSmiElements<InternalClassWithSmiElements, FixedArrayBase>::InternalClassWithSmiElementsVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::InternalClassWithSmiElementsVerify(InternalClassWithSmiElements::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedInternalClassWithStructElements<InternalClassWithStructElements, HeapObject>::InternalClassWithStructElementsVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::InternalClassWithStructElementsVerify(InternalClassWithStructElements::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedExportedSubClass2<ExportedSubClass2, ExportedSubClassBase>::ExportedSubClass2Verify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::ExportedSubClass2Verify(ExportedSubClass2::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
#ifdef VERIFY_HEAP

template <>
void TorqueGeneratedSortState<SortState, HeapObject>::SortStateVerify(Isolate* isolate) {
  TorqueGeneratedClassVerifiers::SortStateVerify(SortState::cast(*this), isolate);
}
#endif  // VERIFY_HEAP
}  // namespace internal
}  // namespace v8
