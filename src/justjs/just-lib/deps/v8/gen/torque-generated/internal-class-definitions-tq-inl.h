#ifndef V8_GEN_TORQUE_GENERATED_INTERNAL_CLASS_DEFINITIONS_TQ_INL_H_
#define V8_GEN_TORQUE_GENERATED_INTERNAL_CLASS_DEFINITIONS_TQ_INL_H_

#include "torque-generated/internal-class-definitions-tq.h"
#include "torque-generated/class-definitions-tq-inl.h"
#include "torque-generated/class-definitions-tq.h"
#include "src/objects/js-function.h"
#include "src/objects/js-objects.h"
#include "src/objects/js-promise.h"
#include "src/objects/js-weak-refs.h"
#include "src/objects/module.h"
#include "src/objects/objects-inl.h"
#include "src/objects/script.h"
#include "src/objects/shared-function-info.h"
#include "src/objects/tagged-field.h"


// Has to be the last include (doesn't have include guards):
#include "src/objects/object-macros.h"
namespace v8 {
namespace internal {
template <class D, class P>
int TorqueGeneratedInternalClass<D, P>::a() const {
  return TaggedField<Smi, kAOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedInternalClass<D, P>::set_a(int value) {
  WRITE_FIELD(*this, kAOffset, Smi::FromInt(value));
}

template <class D, class P>
Object TorqueGeneratedInternalClass<D, P>::b() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInternalClass::b(isolate);
}
template <class D, class P>
Object TorqueGeneratedInternalClass<D, P>::b(const Isolate* isolate) const {
  auto value = TaggedField<Object, kBOffset>::load(isolate, *this);
  DCHECK(value.IsHeapNumber() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedInternalClass<D, P>::set_b(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapNumber() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kBOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedInternalClass<D, P>::TorqueGeneratedInternalClass(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsInternalClass());
}
template<class D, class P>
inline TorqueGeneratedInternalClass<D, P>::TorqueGeneratedInternalClass(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsInternalClass());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(InternalClass)
template <class D, class P>
int TorqueGeneratedSmiPair<D, P>::a() const {
  return TaggedField<Smi, kAOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSmiPair<D, P>::set_a(int value) {
  WRITE_FIELD(*this, kAOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSmiPair<D, P>::b() const {
  return TaggedField<Smi, kBOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSmiPair<D, P>::set_b(int value) {
  WRITE_FIELD(*this, kBOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedSmiPair<D, P>::TorqueGeneratedSmiPair(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSmiPair());
}
template<class D, class P>
inline TorqueGeneratedSmiPair<D, P>::TorqueGeneratedSmiPair(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSmiPair());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(SmiPair)
template <class D, class P>
int TorqueGeneratedSmiBox<D, P>::value() const {
  return TaggedField<Smi, kValueOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSmiBox<D, P>::set_value(int value) {
  WRITE_FIELD(*this, kValueOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSmiBox<D, P>::unrelated() const {
  return TaggedField<Smi, kUnrelatedOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSmiBox<D, P>::set_unrelated(int value) {
  WRITE_FIELD(*this, kUnrelatedOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedSmiBox<D, P>::TorqueGeneratedSmiBox(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSmiBox());
}
template<class D, class P>
inline TorqueGeneratedSmiBox<D, P>::TorqueGeneratedSmiBox(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSmiBox());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(SmiBox)
template<class D, class P>
inline TorqueGeneratedAbstractInternalClass<D, P>::TorqueGeneratedAbstractInternalClass(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsAbstractInternalClass());
}
template<class D, class P>
inline TorqueGeneratedAbstractInternalClass<D, P>::TorqueGeneratedAbstractInternalClass(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsAbstractInternalClass());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(AbstractInternalClass)
template<class D, class P>
inline TorqueGeneratedAbstractInternalClassSubclass1<D, P>::TorqueGeneratedAbstractInternalClassSubclass1(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsAbstractInternalClassSubclass1());
}
template<class D, class P>
inline TorqueGeneratedAbstractInternalClassSubclass1<D, P>::TorqueGeneratedAbstractInternalClassSubclass1(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsAbstractInternalClassSubclass1());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(AbstractInternalClassSubclass1)
template<class D, class P>
inline TorqueGeneratedAbstractInternalClassSubclass2<D, P>::TorqueGeneratedAbstractInternalClassSubclass2(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsAbstractInternalClassSubclass2());
}
template<class D, class P>
inline TorqueGeneratedAbstractInternalClassSubclass2<D, P>::TorqueGeneratedAbstractInternalClassSubclass2(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsAbstractInternalClassSubclass2());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(AbstractInternalClassSubclass2)
template <class D, class P>
int TorqueGeneratedInternalClassWithSmiElements<D, P>::data() const {
  return TaggedField<Smi, kDataOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedInternalClassWithSmiElements<D, P>::set_data(int value) {
  WRITE_FIELD(*this, kDataOffset, Smi::FromInt(value));
}

template <class D, class P>
Oddball TorqueGeneratedInternalClassWithSmiElements<D, P>::object() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInternalClassWithSmiElements::object(isolate);
}
template <class D, class P>
Oddball TorqueGeneratedInternalClassWithSmiElements<D, P>::object(const Isolate* isolate) const {
  auto value = TaggedField<Oddball, kObjectOffset>::load(isolate, *this);
  DCHECK(value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedInternalClassWithSmiElements<D, P>::set_object(Oddball value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball());
  RELAXED_WRITE_FIELD(*this, kObjectOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kObjectOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedInternalClassWithSmiElements<D, P>::entries(int i) const {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kEntriesOffset + i * kTaggedSize;
  return this->template ReadField<Smi>(offset).value();
}
template <class D, class P>
void TorqueGeneratedInternalClassWithSmiElements<D, P>::set_entries(int i, int value) {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kEntriesOffset + i * kTaggedSize;
  WRITE_FIELD(*this, offset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedInternalClassWithSmiElements<D, P>::TorqueGeneratedInternalClassWithSmiElements(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsInternalClassWithSmiElements());
}
template<class D, class P>
inline TorqueGeneratedInternalClassWithSmiElements<D, P>::TorqueGeneratedInternalClassWithSmiElements(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsInternalClassWithSmiElements());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(InternalClassWithSmiElements)
template <class D, class P>
int32_t TorqueGeneratedInternalClassWithStructElements<D, P>::dummy1() const {
  return this->template ReadField<int32_t>(kDummy1Offset);
}
template <class D, class P>
void TorqueGeneratedInternalClassWithStructElements<D, P>::set_dummy1(int32_t value) {
  this->template WriteField<int32_t>(kDummy1Offset, value);
}

template <class D, class P>
int32_t TorqueGeneratedInternalClassWithStructElements<D, P>::dummy2() const {
  return this->template ReadField<int32_t>(kDummy2Offset);
}
template <class D, class P>
void TorqueGeneratedInternalClassWithStructElements<D, P>::set_dummy2(int32_t value) {
  this->template WriteField<int32_t>(kDummy2Offset, value);
}

template <class D, class P>
int TorqueGeneratedInternalClassWithStructElements<D, P>::count() const {
  return TaggedField<Smi, kCountOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedInternalClassWithStructElements<D, P>::set_count(int value) {
  WRITE_FIELD(*this, kCountOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedInternalClassWithStructElements<D, P>::data() const {
  return TaggedField<Smi, kDataOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedInternalClassWithStructElements<D, P>::set_data(int value) {
  WRITE_FIELD(*this, kDataOffset, Smi::FromInt(value));
}

template <class D, class P>
Object TorqueGeneratedInternalClassWithStructElements<D, P>::object() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInternalClassWithStructElements::object(isolate);
}
template <class D, class P>
Object TorqueGeneratedInternalClassWithStructElements<D, P>::object(const Isolate* isolate) const {
  auto value = TaggedField<Object, kObjectOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedInternalClassWithStructElements<D, P>::set_object(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kObjectOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kObjectOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedInternalClassWithStructElements<D, P>::entries(int i) const {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->count());
  int offset = kEntriesOffset + i * kTaggedSize;
  return this->template ReadField<Smi>(offset).value();
}
template <class D, class P>
void TorqueGeneratedInternalClassWithStructElements<D, P>::set_entries(int i, int value) {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->count());
  int offset = kEntriesOffset + i * kTaggedSize;
  WRITE_FIELD(*this, offset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedInternalClassWithStructElements<D, P>::TorqueGeneratedInternalClassWithStructElements(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsInternalClassWithStructElements());
}
template<class D, class P>
inline TorqueGeneratedInternalClassWithStructElements<D, P>::TorqueGeneratedInternalClassWithStructElements(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsInternalClassWithStructElements());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(InternalClassWithStructElements)
template <class D, class P>
JSReceiver TorqueGeneratedSortState<D, P>::receiver() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSortState::receiver(isolate);
}
template <class D, class P>
JSReceiver TorqueGeneratedSortState<D, P>::receiver(const Isolate* isolate) const {
  auto value = TaggedField<JSReceiver, kReceiverOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver());
  return value;
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_receiver(JSReceiver value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver());
  RELAXED_WRITE_FIELD(*this, kReceiverOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kReceiverOffset, value, mode);
}

template <class D, class P>
Map TorqueGeneratedSortState<D, P>::initialReceiverMap() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSortState::initialReceiverMap(isolate);
}
template <class D, class P>
Map TorqueGeneratedSortState<D, P>::initialReceiverMap(const Isolate* isolate) const {
  auto value = TaggedField<Map, kInitialReceiverMapOffset>::load(isolate, *this);
  DCHECK(value.IsMap());
  return value;
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_initialReceiverMap(Map value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsMap());
  RELAXED_WRITE_FIELD(*this, kInitialReceiverMapOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kInitialReceiverMapOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedSortState<D, P>::initialReceiverLength() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSortState::initialReceiverLength(isolate);
}
template <class D, class P>
Object TorqueGeneratedSortState<D, P>::initialReceiverLength(const Isolate* isolate) const {
  auto value = TaggedField<Object, kInitialReceiverLengthOffset>::load(isolate, *this);
  DCHECK(value.IsHeapNumber() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_initialReceiverLength(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapNumber() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kInitialReceiverLengthOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kInitialReceiverLengthOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedSortState<D, P>::userCmpFn() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSortState::userCmpFn(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedSortState<D, P>::userCmpFn(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kUserCmpFnOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsJSObject() || value.IsJSProxy() || value.IsJSBoundFunction() || value.IsJSFunction());
  return value;
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_userCmpFn(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsJSObject() || value.IsJSProxy() || value.IsJSBoundFunction() || value.IsJSFunction());
  RELAXED_WRITE_FIELD(*this, kUserCmpFnOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kUserCmpFnOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedSortState<D, P>::sortComparePtr() const {
  return TaggedField<Smi, kSortComparePtrOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_sortComparePtr(int value) {
  WRITE_FIELD(*this, kSortComparePtrOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSortState<D, P>::loadFn() const {
  return TaggedField<Smi, kLoadFnOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_loadFn(int value) {
  WRITE_FIELD(*this, kLoadFnOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSortState<D, P>::storeFn() const {
  return TaggedField<Smi, kStoreFnOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_storeFn(int value) {
  WRITE_FIELD(*this, kStoreFnOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSortState<D, P>::deleteFn() const {
  return TaggedField<Smi, kDeleteFnOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_deleteFn(int value) {
  WRITE_FIELD(*this, kDeleteFnOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSortState<D, P>::canUseSameAccessorFn() const {
  return TaggedField<Smi, kCanUseSameAccessorFnOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_canUseSameAccessorFn(int value) {
  WRITE_FIELD(*this, kCanUseSameAccessorFnOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSortState<D, P>::minGallop() const {
  return TaggedField<Smi, kMinGallopOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_minGallop(int value) {
  WRITE_FIELD(*this, kMinGallopOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSortState<D, P>::pendingRunsSize() const {
  return TaggedField<Smi, kPendingRunsSizeOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_pendingRunsSize(int value) {
  WRITE_FIELD(*this, kPendingRunsSizeOffset, Smi::FromInt(value));
}

template <class D, class P>
FixedArray TorqueGeneratedSortState<D, P>::pendingRuns() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSortState::pendingRuns(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedSortState<D, P>::pendingRuns(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kPendingRunsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_pendingRuns(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kPendingRunsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPendingRunsOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedSortState<D, P>::workArray() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSortState::workArray(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedSortState<D, P>::workArray(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kWorkArrayOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_workArray(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kWorkArrayOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kWorkArrayOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedSortState<D, P>::tempArray() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSortState::tempArray(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedSortState<D, P>::tempArray(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kTempArrayOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_tempArray(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kTempArrayOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTempArrayOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedSortState<D, P>::sortLength() const {
  return TaggedField<Smi, kSortLengthOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_sortLength(int value) {
  WRITE_FIELD(*this, kSortLengthOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSortState<D, P>::numberOfUndefined() const {
  return TaggedField<Smi, kNumberOfUndefinedOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSortState<D, P>::set_numberOfUndefined(int value) {
  WRITE_FIELD(*this, kNumberOfUndefinedOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedSortState<D, P>::TorqueGeneratedSortState(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSortState());
}
template<class D, class P>
inline TorqueGeneratedSortState<D, P>::TorqueGeneratedSortState(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSortState());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(SortState)
}  // namespace internal
}  // namespace v8

#include "src/objects/object-macros-undef.h"
#endif  // V8_GEN_TORQUE_GENERATED_INTERNAL_CLASS_DEFINITIONS_TQ_INL_H_
