#ifndef V8_GEN_TORQUE_GENERATED_EXPORTED_CLASS_DEFINITIONS_TQ_INL_H_
#define V8_GEN_TORQUE_GENERATED_EXPORTED_CLASS_DEFINITIONS_TQ_INL_H_

#include "torque-generated/exported-class-definitions-tq.h"
#include "src/objects/fixed-array-inl.h"

// Has to be the last include (doesn't have include guards):
#include "src/objects/object-macros.h"
namespace v8 {
namespace internal {
template <class D, class P>
Context TorqueGeneratedSloppyArgumentsElements<D, P>::context() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSloppyArgumentsElements::context(isolate);
}
template <class D, class P>
Context TorqueGeneratedSloppyArgumentsElements<D, P>::context(const Isolate* isolate) const {
  auto value = TaggedField<Context, kContextOffset>::load(isolate, *this);
  DCHECK(value.IsContext());
  return value;
}
template <class D, class P>
void TorqueGeneratedSloppyArgumentsElements<D, P>::set_context(Context value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsContext());
  RELAXED_WRITE_FIELD(*this, kContextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kContextOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedSloppyArgumentsElements<D, P>::arguments() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSloppyArgumentsElements::arguments(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedSloppyArgumentsElements<D, P>::arguments(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kArgumentsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedSloppyArgumentsElements<D, P>::set_arguments(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kArgumentsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kArgumentsOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedSloppyArgumentsElements<D, P>::mapped_entries(int i) const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSloppyArgumentsElements::mapped_entries(isolate, i);
}
template <class D, class P>
Object TorqueGeneratedSloppyArgumentsElements<D, P>::mapped_entries(const Isolate* isolate, int i) const {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kMappedEntriesOffset + i * kTaggedSize;
  auto value = TaggedField<Object>::Relaxed_Load(isolate, *this, offset);
  DCHECK(value.IsSmi() || value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedSloppyArgumentsElements<D, P>::set_mapped_entries(int i, Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSmi() || value.IsOddball());
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kMappedEntriesOffset + i * kTaggedSize;
  WRITE_FIELD(*this, offset, value);
  CONDITIONAL_WRITE_BARRIER(*this, offset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedSloppyArgumentsElements<D, P>::TorqueGeneratedSloppyArgumentsElements(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSloppyArgumentsElements());
}
template<class D, class P>
inline TorqueGeneratedSloppyArgumentsElements<D, P>::TorqueGeneratedSloppyArgumentsElements(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSloppyArgumentsElements());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(SloppyArgumentsElements)
template <class D, class P>
ByteArray TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::block_ids() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedOnHeapBasicBlockProfilerData::block_ids(isolate);
}
template <class D, class P>
ByteArray TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::block_ids(const Isolate* isolate) const {
  auto value = TaggedField<ByteArray, kBlockIdsOffset>::load(isolate, *this);
  DCHECK(value.IsByteArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::set_block_ids(ByteArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsByteArray());
  RELAXED_WRITE_FIELD(*this, kBlockIdsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBlockIdsOffset, value, mode);
}

template <class D, class P>
ByteArray TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::counts() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedOnHeapBasicBlockProfilerData::counts(isolate);
}
template <class D, class P>
ByteArray TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::counts(const Isolate* isolate) const {
  auto value = TaggedField<ByteArray, kCountsOffset>::load(isolate, *this);
  DCHECK(value.IsByteArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::set_counts(ByteArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsByteArray());
  RELAXED_WRITE_FIELD(*this, kCountsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCountsOffset, value, mode);
}

template <class D, class P>
String TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedOnHeapBasicBlockProfilerData::name(isolate);
}
template <class D, class P>
String TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::name(const Isolate* isolate) const {
  auto value = TaggedField<String, kNameOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::set_name(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNameOffset, value, mode);
}

template <class D, class P>
String TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::schedule() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedOnHeapBasicBlockProfilerData::schedule(isolate);
}
template <class D, class P>
String TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::schedule(const Isolate* isolate) const {
  auto value = TaggedField<String, kScheduleOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::set_schedule(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kScheduleOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kScheduleOffset, value, mode);
}

template <class D, class P>
String TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::code() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedOnHeapBasicBlockProfilerData::code(isolate);
}
template <class D, class P>
String TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::code(const Isolate* isolate) const {
  auto value = TaggedField<String, kCodeOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::set_code(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kCodeOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCodeOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::hash() const {
  return TaggedField<Smi, kHashOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::set_hash(int value) {
  WRITE_FIELD(*this, kHashOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::TorqueGeneratedOnHeapBasicBlockProfilerData(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsOnHeapBasicBlockProfilerData());
}
template<class D, class P>
inline TorqueGeneratedOnHeapBasicBlockProfilerData<D, P>::TorqueGeneratedOnHeapBasicBlockProfilerData(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsOnHeapBasicBlockProfilerData());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(OnHeapBasicBlockProfilerData)
template <class D, class P>
HeapObject TorqueGeneratedExportedSubClassBase<D, P>::a() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedExportedSubClassBase::a(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedExportedSubClassBase<D, P>::a(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kAOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject());
  return value;
}
template <class D, class P>
void TorqueGeneratedExportedSubClassBase<D, P>::set_a(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject());
  RELAXED_WRITE_FIELD(*this, kAOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kAOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedExportedSubClassBase<D, P>::b() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedExportedSubClassBase::b(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedExportedSubClassBase<D, P>::b(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kBOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject());
  return value;
}
template <class D, class P>
void TorqueGeneratedExportedSubClassBase<D, P>::set_b(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject());
  RELAXED_WRITE_FIELD(*this, kBOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedExportedSubClassBase<D, P>::TorqueGeneratedExportedSubClassBase(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsExportedSubClassBase());
}
template<class D, class P>
inline TorqueGeneratedExportedSubClassBase<D, P>::TorqueGeneratedExportedSubClassBase(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsExportedSubClassBase());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(ExportedSubClassBase)
template <class D, class P>
int32_t TorqueGeneratedExportedSubClass<D, P>::c_field() const {
  return this->template ReadField<int32_t>(kCFieldOffset);
}
template <class D, class P>
void TorqueGeneratedExportedSubClass<D, P>::set_c_field(int32_t value) {
  this->template WriteField<int32_t>(kCFieldOffset, value);
}

template <class D, class P>
int32_t TorqueGeneratedExportedSubClass<D, P>::d_field() const {
  return this->template ReadField<int32_t>(kDFieldOffset);
}
template <class D, class P>
void TorqueGeneratedExportedSubClass<D, P>::set_d_field(int32_t value) {
  this->template WriteField<int32_t>(kDFieldOffset, value);
}

template <class D, class P>
int TorqueGeneratedExportedSubClass<D, P>::e_field() const {
  return TaggedField<Smi, kEFieldOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedExportedSubClass<D, P>::set_e_field(int value) {
  WRITE_FIELD(*this, kEFieldOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedExportedSubClass<D, P>::TorqueGeneratedExportedSubClass(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsExportedSubClass());
}
template<class D, class P>
inline TorqueGeneratedExportedSubClass<D, P>::TorqueGeneratedExportedSubClass(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsExportedSubClass());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(ExportedSubClass)
template <class D, class P>
int32_t TorqueGeneratedExportedSubClass2<D, P>::x_field() const {
  return this->template ReadField<int32_t>(kXFieldOffset);
}
template <class D, class P>
void TorqueGeneratedExportedSubClass2<D, P>::set_x_field(int32_t value) {
  this->template WriteField<int32_t>(kXFieldOffset, value);
}

template <class D, class P>
int32_t TorqueGeneratedExportedSubClass2<D, P>::y_field() const {
  return this->template ReadField<int32_t>(kYFieldOffset);
}
template <class D, class P>
void TorqueGeneratedExportedSubClass2<D, P>::set_y_field(int32_t value) {
  this->template WriteField<int32_t>(kYFieldOffset, value);
}

template <class D, class P>
int TorqueGeneratedExportedSubClass2<D, P>::z_field() const {
  return TaggedField<Smi, kZFieldOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedExportedSubClass2<D, P>::set_z_field(int value) {
  WRITE_FIELD(*this, kZFieldOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedExportedSubClass2<D, P>::TorqueGeneratedExportedSubClass2(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsExportedSubClass2());
}
template<class D, class P>
inline TorqueGeneratedExportedSubClass2<D, P>::TorqueGeneratedExportedSubClass2(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsExportedSubClass2());
}
TQ_OBJECT_CONSTRUCTORS_IMPL(ExportedSubClass2)
}  // namespace internal
}  // namespace v8

#include "src/objects/object-macros-undef.h"
#endif  // V8_GEN_TORQUE_GENERATED_EXPORTED_CLASS_DEFINITIONS_TQ_INL_H_
