#ifndef V8_GEN_TORQUE_GENERATED_CLASS_DEFINITIONS_TQ_INL_H_
#define V8_GEN_TORQUE_GENERATED_CLASS_DEFINITIONS_TQ_INL_H_

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
template<class D, class P>
inline TorqueGeneratedPrimitiveHeapObject<D, P>::TorqueGeneratedPrimitiveHeapObject(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsPrimitiveHeapObject());
}
template<class D, class P>
inline TorqueGeneratedPrimitiveHeapObject<D, P>::TorqueGeneratedPrimitiveHeapObject(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsPrimitiveHeapObject());
}
template <class D, class P>
double TorqueGeneratedOddball<D, P>::to_number_raw() const {
  return this->template ReadField<double>(kToNumberRawOffset);
}
template <class D, class P>
void TorqueGeneratedOddball<D, P>::set_to_number_raw(double value) {
  this->template WriteField<double>(kToNumberRawOffset, value);
}

template <class D, class P>
String TorqueGeneratedOddball<D, P>::to_string() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedOddball::to_string(isolate);
}
template <class D, class P>
String TorqueGeneratedOddball<D, P>::to_string(const Isolate* isolate) const {
  auto value = TaggedField<String, kToStringOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedOddball<D, P>::set_to_string(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kToStringOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kToStringOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedOddball<D, P>::to_number() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedOddball::to_number(isolate);
}
template <class D, class P>
Object TorqueGeneratedOddball<D, P>::to_number(const Isolate* isolate) const {
  auto value = TaggedField<Object, kToNumberOffset>::load(isolate, *this);
  DCHECK(value.IsHeapNumber() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedOddball<D, P>::set_to_number(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapNumber() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kToNumberOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kToNumberOffset, value, mode);
}

template <class D, class P>
String TorqueGeneratedOddball<D, P>::type_of() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedOddball::type_of(isolate);
}
template <class D, class P>
String TorqueGeneratedOddball<D, P>::type_of(const Isolate* isolate) const {
  auto value = TaggedField<String, kTypeOfOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedOddball<D, P>::set_type_of(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kTypeOfOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTypeOfOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedOddball<D, P>::kind() const {
  return TaggedField<Smi, kKindOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedOddball<D, P>::set_kind(int value) {
  WRITE_FIELD(*this, kKindOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedOddball<D, P>::TorqueGeneratedOddball(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsOddball());
}
template<class D, class P>
inline TorqueGeneratedOddball<D, P>::TorqueGeneratedOddball(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsOddball());
}
template <class D, class P>
uint32_t TorqueGeneratedName<D, P>::hash_field() const {
  return this->template ReadField<uint32_t>(kHashFieldOffset);
}
template <class D, class P>
void TorqueGeneratedName<D, P>::set_hash_field(uint32_t value) {
  this->template WriteField<uint32_t>(kHashFieldOffset, value);
}

template<class D, class P>
inline TorqueGeneratedName<D, P>::TorqueGeneratedName(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsName());
}
template<class D, class P>
inline TorqueGeneratedName<D, P>::TorqueGeneratedName(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsName());
}
template <class D, class P>
uint32_t TorqueGeneratedSymbol<D, P>::flags() const {
  return this->template ReadField<uint32_t>(kFlagsOffset);
}
template <class D, class P>
void TorqueGeneratedSymbol<D, P>::set_flags(uint32_t value) {
  this->template WriteField<uint32_t>(kFlagsOffset, value);
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedSymbol<D, P>::description() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSymbol::description(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedSymbol<D, P>::description(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kDescriptionOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedSymbol<D, P>::set_description(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kDescriptionOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDescriptionOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedSymbol<D, P>::TorqueGeneratedSymbol(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSymbol());
}
template<class D, class P>
inline TorqueGeneratedSymbol<D, P>::TorqueGeneratedSymbol(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSymbol());
}
template <class D, class P>
int32_t TorqueGeneratedString<D, P>::length() const {
  return this->template ReadField<int32_t>(kLengthOffset);
}
template <class D, class P>
void TorqueGeneratedString<D, P>::set_length(int32_t value) {
  this->template WriteField<int32_t>(kLengthOffset, value);
}

template<class D, class P>
inline TorqueGeneratedString<D, P>::TorqueGeneratedString(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsString());
}
template<class D, class P>
inline TorqueGeneratedString<D, P>::TorqueGeneratedString(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsString());
}
template <class D, class P>
double TorqueGeneratedHeapNumber<D, P>::value() const {
  return this->template ReadField<double>(kValueOffset);
}
template <class D, class P>
void TorqueGeneratedHeapNumber<D, P>::set_value(double value) {
  this->template WriteField<double>(kValueOffset, value);
}

template<class D, class P>
inline TorqueGeneratedHeapNumber<D, P>::TorqueGeneratedHeapNumber(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsHeapNumber());
}
template<class D, class P>
inline TorqueGeneratedHeapNumber<D, P>::TorqueGeneratedHeapNumber(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsHeapNumber());
}
template <class D, class P>
int TorqueGeneratedFixedArrayBase<D, P>::length() const {
  return TaggedField<Smi, kLengthOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedFixedArrayBase<D, P>::set_length(int value) {
  WRITE_FIELD(*this, kLengthOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedFixedArrayBase<D, P>::TorqueGeneratedFixedArrayBase(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsFixedArrayBase());
}
template<class D, class P>
inline TorqueGeneratedFixedArrayBase<D, P>::TorqueGeneratedFixedArrayBase(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsFixedArrayBase());
}
template <class D, class P>
Object TorqueGeneratedFixedArray<D, P>::objects(int i) const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFixedArray::objects(isolate, i);
}
template <class D, class P>
Object TorqueGeneratedFixedArray<D, P>::objects(const Isolate* isolate, int i) const {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kObjectsOffset + i * kTaggedSize;
  auto value = TaggedField<Object>::Relaxed_Load(isolate, *this, offset);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedFixedArray<D, P>::set_objects(int i, Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kObjectsOffset + i * kTaggedSize;
  WRITE_FIELD(*this, offset, value);
  CONDITIONAL_WRITE_BARRIER(*this, offset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedFixedArray<D, P>::TorqueGeneratedFixedArray(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsFixedArray());
}
template<class D, class P>
inline TorqueGeneratedFixedArray<D, P>::TorqueGeneratedFixedArray(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsFixedArray());
}
template <class D, class P>
uint8_t TorqueGeneratedByteArray<D, P>::bytes(int i) const {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kBytesOffset + i * 1;
  return this->template ReadField<uint8_t>(offset);
}
template <class D, class P>
void TorqueGeneratedByteArray<D, P>::set_bytes(int i, uint8_t value) {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kBytesOffset + i * 1;
  this->template WriteField<uint8_t>(offset, value);
}

template<class D, class P>
inline TorqueGeneratedByteArray<D, P>::TorqueGeneratedByteArray(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsByteArray());
}
template<class D, class P>
inline TorqueGeneratedByteArray<D, P>::TorqueGeneratedByteArray(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsByteArray());
}
template <class D, class P>
int TorqueGeneratedWeakFixedArray<D, P>::length() const {
  return TaggedField<Smi, kLengthOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedWeakFixedArray<D, P>::set_length(int value) {
  WRITE_FIELD(*this, kLengthOffset, Smi::FromInt(value));
}

template <class D, class P>
MaybeObject TorqueGeneratedWeakFixedArray<D, P>::objects(int i) const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWeakFixedArray::objects(isolate, i);
}
template <class D, class P>
MaybeObject TorqueGeneratedWeakFixedArray<D, P>::objects(const Isolate* isolate, int i) const {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kObjectsOffset + i * kTaggedSize;
  auto value = TaggedField<MaybeObject>::Relaxed_Load(isolate, *this, offset);
  DCHECK(value.IsCleared() || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsHeapObject()) || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsSmi()) || value.IsWeak());
  return value;
}
template <class D, class P>
void TorqueGeneratedWeakFixedArray<D, P>::set_objects(int i, MaybeObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsCleared() || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsHeapObject()) || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsSmi()) || value.IsWeak());
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kObjectsOffset + i * kTaggedSize;
  RELAXED_WRITE_WEAK_FIELD(*this, offset, value);
  CONDITIONAL_WEAK_WRITE_BARRIER(*this, offset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedWeakFixedArray<D, P>::TorqueGeneratedWeakFixedArray(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsWeakFixedArray());
}
template<class D, class P>
inline TorqueGeneratedWeakFixedArray<D, P>::TorqueGeneratedWeakFixedArray(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsWeakFixedArray());
}
template<class D, class P>
inline TorqueGeneratedForeign<D, P>::TorqueGeneratedForeign(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsForeign());
}
template<class D, class P>
inline TorqueGeneratedForeign<D, P>::TorqueGeneratedForeign(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsForeign());
}
template <class D, class P>
FixedArrayBase TorqueGeneratedJSObject<D, P>::elements() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSObject::elements(isolate);
}
template <class D, class P>
FixedArrayBase TorqueGeneratedJSObject<D, P>::elements(const Isolate* isolate) const {
  auto value = TaggedField<FixedArrayBase, kElementsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArrayBase());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSObject<D, P>::set_elements(FixedArrayBase value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArrayBase());
  RELAXED_WRITE_FIELD(*this, kElementsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kElementsOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSObject<D, P>::TorqueGeneratedJSObject(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSObject());
}
template<class D, class P>
inline TorqueGeneratedJSObject<D, P>::TorqueGeneratedJSObject(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSObject());
}
template <class D, class P>
HeapObject TorqueGeneratedJSProxy<D, P>::target() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSProxy::target(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedJSProxy<D, P>::target(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kTargetOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSProxy<D, P>::set_target(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball());
  RELAXED_WRITE_FIELD(*this, kTargetOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTargetOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedJSProxy<D, P>::handler() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSProxy::handler(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedJSProxy<D, P>::handler(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kHandlerOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSProxy<D, P>::set_handler(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball());
  RELAXED_WRITE_FIELD(*this, kHandlerOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kHandlerOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSProxy<D, P>::TorqueGeneratedJSProxy(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSProxy());
}
template<class D, class P>
inline TorqueGeneratedJSProxy<D, P>::TorqueGeneratedJSProxy(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSProxy());
}
template<class D, class P>
inline TorqueGeneratedJSFunctionOrBoundFunction<D, P>::TorqueGeneratedJSFunctionOrBoundFunction(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSFunctionOrBoundFunction());
}
template<class D, class P>
inline TorqueGeneratedJSFunctionOrBoundFunction<D, P>::TorqueGeneratedJSFunctionOrBoundFunction(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSFunctionOrBoundFunction());
}
template <class D, class P>
JSReceiver TorqueGeneratedJSBoundFunction<D, P>::bound_target_function() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSBoundFunction::bound_target_function(isolate);
}
template <class D, class P>
JSReceiver TorqueGeneratedJSBoundFunction<D, P>::bound_target_function(const Isolate* isolate) const {
  auto value = TaggedField<JSReceiver, kBoundTargetFunctionOffset>::load(isolate, *this);
  DCHECK(value.IsJSObject() || value.IsJSProxy() || value.IsJSBoundFunction() || value.IsJSFunction());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSBoundFunction<D, P>::set_bound_target_function(JSReceiver value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSObject() || value.IsJSProxy() || value.IsJSBoundFunction() || value.IsJSFunction());
  RELAXED_WRITE_FIELD(*this, kBoundTargetFunctionOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBoundTargetFunctionOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSBoundFunction<D, P>::bound_this() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSBoundFunction::bound_this(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSBoundFunction<D, P>::bound_this(const Isolate* isolate) const {
  auto value = TaggedField<Object, kBoundThisOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi() || value.IsSourceTextModule());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSBoundFunction<D, P>::set_bound_this(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi() || value.IsSourceTextModule());
  RELAXED_WRITE_FIELD(*this, kBoundThisOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBoundThisOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedJSBoundFunction<D, P>::bound_arguments() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSBoundFunction::bound_arguments(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedJSBoundFunction<D, P>::bound_arguments(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kBoundArgumentsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSBoundFunction<D, P>::set_bound_arguments(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kBoundArgumentsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBoundArgumentsOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSBoundFunction<D, P>::TorqueGeneratedJSBoundFunction(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSBoundFunction());
}
template<class D, class P>
inline TorqueGeneratedJSBoundFunction<D, P>::TorqueGeneratedJSBoundFunction(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSBoundFunction());
}
template<class D, class P>
inline TorqueGeneratedJSCustomElementsObject<D, P>::TorqueGeneratedJSCustomElementsObject(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSCustomElementsObject());
}
template<class D, class P>
inline TorqueGeneratedJSCustomElementsObject<D, P>::TorqueGeneratedJSCustomElementsObject(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSCustomElementsObject());
}
template<class D, class P>
inline TorqueGeneratedJSSpecialObject<D, P>::TorqueGeneratedJSSpecialObject(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSSpecialObject());
}
template<class D, class P>
inline TorqueGeneratedJSSpecialObject<D, P>::TorqueGeneratedJSSpecialObject(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSSpecialObject());
}
template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::finalization_registry() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWeakCell::finalization_registry(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::finalization_registry(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kFinalizationRegistryOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsJSFinalizationRegistry());
  return value;
}
template <class D, class P>
void TorqueGeneratedWeakCell<D, P>::set_finalization_registry(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsJSFinalizationRegistry());
  RELAXED_WRITE_FIELD(*this, kFinalizationRegistryOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kFinalizationRegistryOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::target() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWeakCell::target(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::target(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kTargetOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedWeakCell<D, P>::set_target(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball());
  RELAXED_WRITE_FIELD(*this, kTargetOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTargetOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedWeakCell<D, P>::unregister_token() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWeakCell::unregister_token(isolate);
}
template <class D, class P>
Object TorqueGeneratedWeakCell<D, P>::unregister_token(const Isolate* isolate) const {
  auto value = TaggedField<Object, kUnregisterTokenOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedWeakCell<D, P>::set_unregister_token(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kUnregisterTokenOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kUnregisterTokenOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedWeakCell<D, P>::holdings() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWeakCell::holdings(isolate);
}
template <class D, class P>
Object TorqueGeneratedWeakCell<D, P>::holdings(const Isolate* isolate) const {
  auto value = TaggedField<Object, kHoldingsOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedWeakCell<D, P>::set_holdings(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kHoldingsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kHoldingsOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::prev() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWeakCell::prev(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::prev(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kPrevOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsWeakCell());
  return value;
}
template <class D, class P>
void TorqueGeneratedWeakCell<D, P>::set_prev(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsWeakCell());
  RELAXED_WRITE_FIELD(*this, kPrevOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPrevOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::next() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWeakCell::next(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::next(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kNextOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsWeakCell());
  return value;
}
template <class D, class P>
void TorqueGeneratedWeakCell<D, P>::set_next(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsWeakCell());
  RELAXED_WRITE_FIELD(*this, kNextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNextOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::key_list_prev() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWeakCell::key_list_prev(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::key_list_prev(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kKeyListPrevOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsWeakCell());
  return value;
}
template <class D, class P>
void TorqueGeneratedWeakCell<D, P>::set_key_list_prev(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsWeakCell());
  RELAXED_WRITE_FIELD(*this, kKeyListPrevOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kKeyListPrevOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::key_list_next() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWeakCell::key_list_next(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedWeakCell<D, P>::key_list_next(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kKeyListNextOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsWeakCell());
  return value;
}
template <class D, class P>
void TorqueGeneratedWeakCell<D, P>::set_key_list_next(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsWeakCell());
  RELAXED_WRITE_FIELD(*this, kKeyListNextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kKeyListNextOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedWeakCell<D, P>::TorqueGeneratedWeakCell(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsWeakCell());
}
template<class D, class P>
inline TorqueGeneratedWeakCell<D, P>::TorqueGeneratedWeakCell(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsWeakCell());
}
template <class D, class P>
Object TorqueGeneratedJSPromise<D, P>::reactions_or_result() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSPromise::reactions_or_result(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSPromise<D, P>::reactions_or_result(const Isolate* isolate) const {
  auto value = TaggedField<Object, kReactionsOrResultOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi() || value.IsPromiseReaction());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSPromise<D, P>::set_reactions_or_result(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi() || value.IsPromiseReaction());
  RELAXED_WRITE_FIELD(*this, kReactionsOrResultOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kReactionsOrResultOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedJSPromise<D, P>::flags() const {
  return TaggedField<Smi, kFlagsOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedJSPromise<D, P>::set_flags(int value) {
  WRITE_FIELD(*this, kFlagsOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedJSPromise<D, P>::TorqueGeneratedJSPromise(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSPromise());
}
template<class D, class P>
inline TorqueGeneratedJSPromise<D, P>::TorqueGeneratedJSPromise(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSPromise());
}
template<class D, class P>
inline TorqueGeneratedStruct<D, P>::TorqueGeneratedStruct(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsStruct());
}
template<class D, class P>
inline TorqueGeneratedStruct<D, P>::TorqueGeneratedStruct(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsStruct());
}
template <class D, class P>
HeapObject TorqueGeneratedPromiseCapability<D, P>::promise() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseCapability::promise(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedPromiseCapability<D, P>::promise(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kPromiseOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseCapability<D, P>::set_promise(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball());
  RELAXED_WRITE_FIELD(*this, kPromiseOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPromiseOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedPromiseCapability<D, P>::resolve() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseCapability::resolve(isolate);
}
template <class D, class P>
Object TorqueGeneratedPromiseCapability<D, P>::resolve(const Isolate* isolate) const {
  auto value = TaggedField<Object, kResolveOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseCapability<D, P>::set_resolve(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kResolveOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kResolveOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedPromiseCapability<D, P>::reject() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseCapability::reject(isolate);
}
template <class D, class P>
Object TorqueGeneratedPromiseCapability<D, P>::reject(const Isolate* isolate) const {
  auto value = TaggedField<Object, kRejectOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseCapability<D, P>::set_reject(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kRejectOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kRejectOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedPromiseCapability<D, P>::TorqueGeneratedPromiseCapability(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsPromiseCapability());
}
template<class D, class P>
inline TorqueGeneratedPromiseCapability<D, P>::TorqueGeneratedPromiseCapability(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsPromiseCapability());
}
template <class D, class P>
JSArrayBuffer TorqueGeneratedJSArrayBufferView<D, P>::buffer() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSArrayBufferView::buffer(isolate);
}
template <class D, class P>
JSArrayBuffer TorqueGeneratedJSArrayBufferView<D, P>::buffer(const Isolate* isolate) const {
  auto value = TaggedField<JSArrayBuffer, kBufferOffset>::load(isolate, *this);
  DCHECK(value.IsJSArrayBuffer());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSArrayBufferView<D, P>::set_buffer(JSArrayBuffer value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSArrayBuffer());
  RELAXED_WRITE_FIELD(*this, kBufferOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBufferOffset, value, mode);
}

template <class D, class P>
uintptr_t TorqueGeneratedJSArrayBufferView<D, P>::byte_offset() const {
  return this->template ReadField<uintptr_t>(kByteOffsetOffset);
}
template <class D, class P>
void TorqueGeneratedJSArrayBufferView<D, P>::set_byte_offset(uintptr_t value) {
  this->template WriteField<uintptr_t>(kByteOffsetOffset, value);
}

template <class D, class P>
uintptr_t TorqueGeneratedJSArrayBufferView<D, P>::byte_length() const {
  return this->template ReadField<uintptr_t>(kByteLengthOffset);
}
template <class D, class P>
void TorqueGeneratedJSArrayBufferView<D, P>::set_byte_length(uintptr_t value) {
  this->template WriteField<uintptr_t>(kByteLengthOffset, value);
}

template<class D, class P>
inline TorqueGeneratedJSArrayBufferView<D, P>::TorqueGeneratedJSArrayBufferView(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSArrayBufferView());
}
template<class D, class P>
inline TorqueGeneratedJSArrayBufferView<D, P>::TorqueGeneratedJSArrayBufferView(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSArrayBufferView());
}
template <class D, class P>
uintptr_t TorqueGeneratedJSTypedArray<D, P>::length() const {
  return this->template ReadField<uintptr_t>(kLengthOffset);
}
template <class D, class P>
void TorqueGeneratedJSTypedArray<D, P>::set_length(uintptr_t value) {
  this->template WriteField<uintptr_t>(kLengthOffset, value);
}

template <class D, class P>
Object TorqueGeneratedJSTypedArray<D, P>::base_pointer() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSTypedArray::base_pointer(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSTypedArray<D, P>::base_pointer(const Isolate* isolate) const {
  auto value = TaggedField<Object, kBasePointerOffset>::load(isolate, *this);
  DCHECK(value.IsSmi() || value.IsByteArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSTypedArray<D, P>::set_base_pointer(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSmi() || value.IsByteArray());
  RELAXED_WRITE_FIELD(*this, kBasePointerOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBasePointerOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSTypedArray<D, P>::TorqueGeneratedJSTypedArray(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSTypedArray());
}
template<class D, class P>
inline TorqueGeneratedJSTypedArray<D, P>::TorqueGeneratedJSTypedArray(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSTypedArray());
}
template <class D, class P>
AllocationSite TorqueGeneratedAllocationMemento<D, P>::allocation_site() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAllocationMemento::allocation_site(isolate);
}
template <class D, class P>
AllocationSite TorqueGeneratedAllocationMemento<D, P>::allocation_site(const Isolate* isolate) const {
  auto value = TaggedField<AllocationSite, kAllocationSiteOffset>::load(isolate, *this);
  DCHECK(value.IsAllocationSite());
  return value;
}
template <class D, class P>
void TorqueGeneratedAllocationMemento<D, P>::set_allocation_site(AllocationSite value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsAllocationSite());
  RELAXED_WRITE_FIELD(*this, kAllocationSiteOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kAllocationSiteOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedAllocationMemento<D, P>::TorqueGeneratedAllocationMemento(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsAllocationMemento());
}
template<class D, class P>
inline TorqueGeneratedAllocationMemento<D, P>::TorqueGeneratedAllocationMemento(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsAllocationMemento());
}
template <class D, class P>
Object TorqueGeneratedCallHandlerInfo<D, P>::callback() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedCallHandlerInfo::callback(isolate);
}
template <class D, class P>
Object TorqueGeneratedCallHandlerInfo<D, P>::callback(const Isolate* isolate) const {
  auto value = TaggedField<Object, kCallbackOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedCallHandlerInfo<D, P>::set_callback(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kCallbackOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCallbackOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedCallHandlerInfo<D, P>::js_callback() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedCallHandlerInfo::js_callback(isolate);
}
template <class D, class P>
Object TorqueGeneratedCallHandlerInfo<D, P>::js_callback(const Isolate* isolate) const {
  auto value = TaggedField<Object, kJsCallbackOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedCallHandlerInfo<D, P>::set_js_callback(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kJsCallbackOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kJsCallbackOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedCallHandlerInfo<D, P>::data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedCallHandlerInfo::data(isolate);
}
template <class D, class P>
Object TorqueGeneratedCallHandlerInfo<D, P>::data(const Isolate* isolate) const {
  auto value = TaggedField<Object, kDataOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedCallHandlerInfo<D, P>::set_data(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDataOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedCallHandlerInfo<D, P>::TorqueGeneratedCallHandlerInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsCallHandlerInfo());
}
template<class D, class P>
inline TorqueGeneratedCallHandlerInfo<D, P>::TorqueGeneratedCallHandlerInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsCallHandlerInfo());
}
template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::getter() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInterceptorInfo::getter(isolate);
}
template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::getter(const Isolate* isolate) const {
  auto value = TaggedField<Object, kGetterOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedInterceptorInfo<D, P>::set_getter(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kGetterOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kGetterOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::setter() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInterceptorInfo::setter(isolate);
}
template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::setter(const Isolate* isolate) const {
  auto value = TaggedField<Object, kSetterOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedInterceptorInfo<D, P>::set_setter(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kSetterOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSetterOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::query() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInterceptorInfo::query(isolate);
}
template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::query(const Isolate* isolate) const {
  auto value = TaggedField<Object, kQueryOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedInterceptorInfo<D, P>::set_query(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kQueryOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kQueryOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::descriptor() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInterceptorInfo::descriptor(isolate);
}
template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::descriptor(const Isolate* isolate) const {
  auto value = TaggedField<Object, kDescriptorOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedInterceptorInfo<D, P>::set_descriptor(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kDescriptorOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDescriptorOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::deleter() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInterceptorInfo::deleter(isolate);
}
template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::deleter(const Isolate* isolate) const {
  auto value = TaggedField<Object, kDeleterOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedInterceptorInfo<D, P>::set_deleter(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kDeleterOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDeleterOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::enumerator() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInterceptorInfo::enumerator(isolate);
}
template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::enumerator(const Isolate* isolate) const {
  auto value = TaggedField<Object, kEnumeratorOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedInterceptorInfo<D, P>::set_enumerator(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kEnumeratorOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kEnumeratorOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::definer() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInterceptorInfo::definer(isolate);
}
template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::definer(const Isolate* isolate) const {
  auto value = TaggedField<Object, kDefinerOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedInterceptorInfo<D, P>::set_definer(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kDefinerOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDefinerOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedInterceptorInfo::data(isolate);
}
template <class D, class P>
Object TorqueGeneratedInterceptorInfo<D, P>::data(const Isolate* isolate) const {
  auto value = TaggedField<Object, kDataOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedInterceptorInfo<D, P>::set_data(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDataOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedInterceptorInfo<D, P>::flags() const {
  return TaggedField<Smi, kFlagsOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedInterceptorInfo<D, P>::set_flags(int value) {
  WRITE_FIELD(*this, kFlagsOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedInterceptorInfo<D, P>::TorqueGeneratedInterceptorInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsInterceptorInfo());
}
template<class D, class P>
inline TorqueGeneratedInterceptorInfo<D, P>::TorqueGeneratedInterceptorInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsInterceptorInfo());
}
template <class D, class P>
Object TorqueGeneratedAccessCheckInfo<D, P>::callback() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessCheckInfo::callback(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessCheckInfo<D, P>::callback(const Isolate* isolate) const {
  auto value = TaggedField<Object, kCallbackOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessCheckInfo<D, P>::set_callback(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kCallbackOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCallbackOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedAccessCheckInfo<D, P>::named_interceptor() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessCheckInfo::named_interceptor(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessCheckInfo<D, P>::named_interceptor(const Isolate* isolate) const {
  auto value = TaggedField<Object, kNamedInterceptorOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsInterceptorInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessCheckInfo<D, P>::set_named_interceptor(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsInterceptorInfo());
  RELAXED_WRITE_FIELD(*this, kNamedInterceptorOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNamedInterceptorOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedAccessCheckInfo<D, P>::indexed_interceptor() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessCheckInfo::indexed_interceptor(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessCheckInfo<D, P>::indexed_interceptor(const Isolate* isolate) const {
  auto value = TaggedField<Object, kIndexedInterceptorOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsInterceptorInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessCheckInfo<D, P>::set_indexed_interceptor(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsInterceptorInfo());
  RELAXED_WRITE_FIELD(*this, kIndexedInterceptorOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kIndexedInterceptorOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedAccessCheckInfo<D, P>::data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessCheckInfo::data(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessCheckInfo<D, P>::data(const Isolate* isolate) const {
  auto value = TaggedField<Object, kDataOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessCheckInfo<D, P>::set_data(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDataOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedAccessCheckInfo<D, P>::TorqueGeneratedAccessCheckInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsAccessCheckInfo());
}
template<class D, class P>
inline TorqueGeneratedAccessCheckInfo<D, P>::TorqueGeneratedAccessCheckInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsAccessCheckInfo());
}
template <class D, class P>
Name TorqueGeneratedAccessorInfo<D, P>::name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessorInfo::name(isolate);
}
template <class D, class P>
Name TorqueGeneratedAccessorInfo<D, P>::name(const Isolate* isolate) const {
  auto value = TaggedField<Name, kNameOffset>::load(isolate, *this);
  DCHECK(value.IsName());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessorInfo<D, P>::set_name(Name value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsName());
  RELAXED_WRITE_FIELD(*this, kNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNameOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedAccessorInfo<D, P>::flags() const {
  return TaggedField<Smi, kFlagsOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedAccessorInfo<D, P>::set_flags(int value) {
  WRITE_FIELD(*this, kFlagsOffset, Smi::FromInt(value));
}

template <class D, class P>
Object TorqueGeneratedAccessorInfo<D, P>::expected_receiver_type() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessorInfo::expected_receiver_type(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessorInfo<D, P>::expected_receiver_type(const Isolate* isolate) const {
  auto value = TaggedField<Object, kExpectedReceiverTypeOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessorInfo<D, P>::set_expected_receiver_type(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kExpectedReceiverTypeOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kExpectedReceiverTypeOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedAccessorInfo<D, P>::setter() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessorInfo::setter(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessorInfo<D, P>::setter(const Isolate* isolate) const {
  auto value = TaggedField<Object, kSetterOffset>::load(isolate, *this);
  DCHECK(value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessorInfo<D, P>::set_setter(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kSetterOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSetterOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedAccessorInfo<D, P>::getter() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessorInfo::getter(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessorInfo<D, P>::getter(const Isolate* isolate) const {
  auto value = TaggedField<Object, kGetterOffset>::load(isolate, *this);
  DCHECK(value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessorInfo<D, P>::set_getter(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kGetterOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kGetterOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedAccessorInfo<D, P>::js_getter() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessorInfo::js_getter(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessorInfo<D, P>::js_getter(const Isolate* isolate) const {
  auto value = TaggedField<Object, kJsGetterOffset>::load(isolate, *this);
  DCHECK(value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessorInfo<D, P>::set_js_getter(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kJsGetterOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kJsGetterOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedAccessorInfo<D, P>::data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessorInfo::data(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessorInfo<D, P>::data(const Isolate* isolate) const {
  auto value = TaggedField<Object, kDataOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessorInfo<D, P>::set_data(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDataOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedAccessorInfo<D, P>::TorqueGeneratedAccessorInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsAccessorInfo());
}
template<class D, class P>
inline TorqueGeneratedAccessorInfo<D, P>::TorqueGeneratedAccessorInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsAccessorInfo());
}
template<class D, class P>
inline TorqueGeneratedJSArgumentsObject<D, P>::TorqueGeneratedJSArgumentsObject(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSArgumentsObject());
}
template<class D, class P>
inline TorqueGeneratedJSArgumentsObject<D, P>::TorqueGeneratedJSArgumentsObject(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSArgumentsObject());
}
template <class D, class P>
int TorqueGeneratedAliasedArgumentsEntry<D, P>::aliased_context_slot() const {
  return TaggedField<Smi, kAliasedContextSlotOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedAliasedArgumentsEntry<D, P>::set_aliased_context_slot(int value) {
  WRITE_FIELD(*this, kAliasedContextSlotOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedAliasedArgumentsEntry<D, P>::TorqueGeneratedAliasedArgumentsEntry(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsAliasedArgumentsEntry());
}
template<class D, class P>
inline TorqueGeneratedAliasedArgumentsEntry<D, P>::TorqueGeneratedAliasedArgumentsEntry(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsAliasedArgumentsEntry());
}
template <class D, class P>
Object TorqueGeneratedCell<D, P>::value() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedCell::value(isolate);
}
template <class D, class P>
Object TorqueGeneratedCell<D, P>::value(const Isolate* isolate) const {
  auto value = TaggedField<Object, kValueOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedCell<D, P>::set_value(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kValueOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kValueOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedCell<D, P>::TorqueGeneratedCell(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsCell());
}
template<class D, class P>
inline TorqueGeneratedCell<D, P>::TorqueGeneratedCell(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsCell());
}
template<class D, class P>
inline TorqueGeneratedFixedDoubleArray<D, P>::TorqueGeneratedFixedDoubleArray(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsFixedDoubleArray());
}
template<class D, class P>
inline TorqueGeneratedFixedDoubleArray<D, P>::TorqueGeneratedFixedDoubleArray(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsFixedDoubleArray());
}
template <class D, class P>
int TorqueGeneratedBreakPoint<D, P>::id() const {
  return TaggedField<Smi, kIdOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedBreakPoint<D, P>::set_id(int value) {
  WRITE_FIELD(*this, kIdOffset, Smi::FromInt(value));
}

template <class D, class P>
String TorqueGeneratedBreakPoint<D, P>::condition() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedBreakPoint::condition(isolate);
}
template <class D, class P>
String TorqueGeneratedBreakPoint<D, P>::condition(const Isolate* isolate) const {
  auto value = TaggedField<String, kConditionOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedBreakPoint<D, P>::set_condition(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kConditionOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kConditionOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedBreakPoint<D, P>::TorqueGeneratedBreakPoint(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsBreakPoint());
}
template<class D, class P>
inline TorqueGeneratedBreakPoint<D, P>::TorqueGeneratedBreakPoint(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsBreakPoint());
}
template <class D, class P>
int TorqueGeneratedBreakPointInfo<D, P>::source_position() const {
  return TaggedField<Smi, kSourcePositionOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedBreakPointInfo<D, P>::set_source_position(int value) {
  WRITE_FIELD(*this, kSourcePositionOffset, Smi::FromInt(value));
}

template <class D, class P>
HeapObject TorqueGeneratedBreakPointInfo<D, P>::break_points() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedBreakPointInfo::break_points(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedBreakPointInfo<D, P>::break_points(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kBreakPointsOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFixedArray() || value.IsBreakPoint());
  return value;
}
template <class D, class P>
void TorqueGeneratedBreakPointInfo<D, P>::set_break_points(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFixedArray() || value.IsBreakPoint());
  RELAXED_WRITE_FIELD(*this, kBreakPointsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBreakPointsOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedBreakPointInfo<D, P>::TorqueGeneratedBreakPointInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsBreakPointInfo());
}
template<class D, class P>
inline TorqueGeneratedBreakPointInfo<D, P>::TorqueGeneratedBreakPointInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsBreakPointInfo());
}
template <class D, class P>
SharedFunctionInfo TorqueGeneratedDebugInfo<D, P>::shared() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedDebugInfo::shared(isolate);
}
template <class D, class P>
SharedFunctionInfo TorqueGeneratedDebugInfo<D, P>::shared(const Isolate* isolate) const {
  auto value = TaggedField<SharedFunctionInfo, kSharedOffset>::load(isolate, *this);
  DCHECK(value.IsSharedFunctionInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedDebugInfo<D, P>::set_shared(SharedFunctionInfo value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSharedFunctionInfo());
  RELAXED_WRITE_FIELD(*this, kSharedOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSharedOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedDebugInfo<D, P>::debugger_hints() const {
  return TaggedField<Smi, kDebuggerHintsOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedDebugInfo<D, P>::set_debugger_hints(int value) {
  WRITE_FIELD(*this, kDebuggerHintsOffset, Smi::FromInt(value));
}

template <class D, class P>
HeapObject TorqueGeneratedDebugInfo<D, P>::script() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedDebugInfo::script(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedDebugInfo<D, P>::script(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kScriptOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsScript());
  return value;
}
template <class D, class P>
void TorqueGeneratedDebugInfo<D, P>::set_script(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsScript());
  RELAXED_WRITE_FIELD(*this, kScriptOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kScriptOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedDebugInfo<D, P>::original_bytecode_array() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedDebugInfo::original_bytecode_array(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedDebugInfo<D, P>::original_bytecode_array(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kOriginalBytecodeArrayOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsBytecodeArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedDebugInfo<D, P>::set_original_bytecode_array(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsBytecodeArray());
  RELAXED_WRITE_FIELD(*this, kOriginalBytecodeArrayOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kOriginalBytecodeArrayOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedDebugInfo<D, P>::debug_bytecode_array() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedDebugInfo::debug_bytecode_array(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedDebugInfo<D, P>::debug_bytecode_array(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kDebugBytecodeArrayOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsBytecodeArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedDebugInfo<D, P>::set_debug_bytecode_array(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsBytecodeArray());
  RELAXED_WRITE_FIELD(*this, kDebugBytecodeArrayOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDebugBytecodeArrayOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedDebugInfo<D, P>::break_points() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedDebugInfo::break_points(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedDebugInfo<D, P>::break_points(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kBreakPointsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedDebugInfo<D, P>::set_break_points(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kBreakPointsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBreakPointsOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedDebugInfo<D, P>::flags() const {
  return TaggedField<Smi, kFlagsOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedDebugInfo<D, P>::set_flags(int value) {
  WRITE_FIELD(*this, kFlagsOffset, Smi::FromInt(value));
}

template <class D, class P>
HeapObject TorqueGeneratedDebugInfo<D, P>::coverage_info() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedDebugInfo::coverage_info(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedDebugInfo<D, P>::coverage_info(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kCoverageInfoOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsCoverageInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedDebugInfo<D, P>::set_coverage_info(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsCoverageInfo());
  RELAXED_WRITE_FIELD(*this, kCoverageInfoOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCoverageInfoOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedDebugInfo<D, P>::TorqueGeneratedDebugInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsDebugInfo());
}
template<class D, class P>
inline TorqueGeneratedDebugInfo<D, P>::TorqueGeneratedDebugInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsDebugInfo());
}
template <class D, class P>
int32_t TorqueGeneratedCoverageInfo<D, P>::slot_count() const {
  return this->template ReadField<int32_t>(kSlotCountOffset);
}
template <class D, class P>
void TorqueGeneratedCoverageInfo<D, P>::set_slot_count(int32_t value) {
  this->template WriteField<int32_t>(kSlotCountOffset, value);
}

template<class D, class P>
inline TorqueGeneratedCoverageInfo<D, P>::TorqueGeneratedCoverageInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsCoverageInfo());
}
template<class D, class P>
inline TorqueGeneratedCoverageInfo<D, P>::TorqueGeneratedCoverageInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsCoverageInfo());
}
template <class D, class P>
int TorqueGeneratedWasmValue<D, P>::value_type() const {
  return TaggedField<Smi, kValueTypeOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedWasmValue<D, P>::set_value_type(int value) {
  WRITE_FIELD(*this, kValueTypeOffset, Smi::FromInt(value));
}

template <class D, class P>
Object TorqueGeneratedWasmValue<D, P>::bytes_or_ref() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWasmValue::bytes_or_ref(isolate);
}
template <class D, class P>
Object TorqueGeneratedWasmValue<D, P>::bytes_or_ref(const Isolate* isolate) const {
  auto value = TaggedField<Object, kBytesOrRefOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedWasmValue<D, P>::set_bytes_or_ref(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kBytesOrRefOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kBytesOrRefOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedWasmValue<D, P>::TorqueGeneratedWasmValue(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsWasmValue());
}
template<class D, class P>
inline TorqueGeneratedWasmValue<D, P>::TorqueGeneratedWasmValue(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsWasmValue());
}
template <class D, class P>
FixedArray TorqueGeneratedEnumCache<D, P>::keys() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedEnumCache::keys(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedEnumCache<D, P>::keys(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kKeysOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedEnumCache<D, P>::set_keys(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kKeysOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kKeysOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedEnumCache<D, P>::indices() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedEnumCache::indices(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedEnumCache<D, P>::indices(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kIndicesOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedEnumCache<D, P>::set_indices(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kIndicesOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kIndicesOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedEnumCache<D, P>::TorqueGeneratedEnumCache(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsEnumCache());
}
template<class D, class P>
inline TorqueGeneratedEnumCache<D, P>::TorqueGeneratedEnumCache(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsEnumCache());
}
template <class D, class P>
int TorqueGeneratedClassPositions<D, P>::start() const {
  return TaggedField<Smi, kStartOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedClassPositions<D, P>::set_start(int value) {
  WRITE_FIELD(*this, kStartOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedClassPositions<D, P>::end() const {
  return TaggedField<Smi, kEndOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedClassPositions<D, P>::set_end(int value) {
  WRITE_FIELD(*this, kEndOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedClassPositions<D, P>::TorqueGeneratedClassPositions(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsClassPositions());
}
template<class D, class P>
inline TorqueGeneratedClassPositions<D, P>::TorqueGeneratedClassPositions(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsClassPositions());
}
template <class D, class P>
Object TorqueGeneratedAccessorPair<D, P>::getter() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessorPair::getter(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessorPair<D, P>::getter(const Isolate* isolate) const {
  auto value = TaggedField<Object, kGetterOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessorPair<D, P>::set_getter(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kGetterOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kGetterOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedAccessorPair<D, P>::setter() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAccessorPair::setter(isolate);
}
template <class D, class P>
Object TorqueGeneratedAccessorPair<D, P>::setter(const Isolate* isolate) const {
  auto value = TaggedField<Object, kSetterOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedAccessorPair<D, P>::set_setter(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kSetterOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSetterOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedAccessorPair<D, P>::TorqueGeneratedAccessorPair(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsAccessorPair());
}
template<class D, class P>
inline TorqueGeneratedAccessorPair<D, P>::TorqueGeneratedAccessorPair(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsAccessorPair());
}
template <class D, class P>
uint16_t TorqueGeneratedDescriptorArray<D, P>::number_of_all_descriptors() const {
  return this->template ReadField<uint16_t>(kNumberOfAllDescriptorsOffset);
}
template <class D, class P>
void TorqueGeneratedDescriptorArray<D, P>::set_number_of_all_descriptors(uint16_t value) {
  this->template WriteField<uint16_t>(kNumberOfAllDescriptorsOffset, value);
}

template <class D, class P>
uint16_t TorqueGeneratedDescriptorArray<D, P>::number_of_descriptors() const {
  return this->template ReadField<uint16_t>(kNumberOfDescriptorsOffset);
}
template <class D, class P>
void TorqueGeneratedDescriptorArray<D, P>::set_number_of_descriptors(uint16_t value) {
  this->template WriteField<uint16_t>(kNumberOfDescriptorsOffset, value);
}

template <class D, class P>
uint16_t TorqueGeneratedDescriptorArray<D, P>::raw_number_of_marked_descriptors() const {
  return this->template ReadField<uint16_t>(kRawNumberOfMarkedDescriptorsOffset);
}
template <class D, class P>
void TorqueGeneratedDescriptorArray<D, P>::set_raw_number_of_marked_descriptors(uint16_t value) {
  this->template WriteField<uint16_t>(kRawNumberOfMarkedDescriptorsOffset, value);
}

template <class D, class P>
uint16_t TorqueGeneratedDescriptorArray<D, P>::filler16_bits() const {
  return this->template ReadField<uint16_t>(kFiller16BitsOffset);
}
template <class D, class P>
void TorqueGeneratedDescriptorArray<D, P>::set_filler16_bits(uint16_t value) {
  this->template WriteField<uint16_t>(kFiller16BitsOffset, value);
}

template <class D, class P>
EnumCache TorqueGeneratedDescriptorArray<D, P>::enum_cache() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedDescriptorArray::enum_cache(isolate);
}
template <class D, class P>
EnumCache TorqueGeneratedDescriptorArray<D, P>::enum_cache(const Isolate* isolate) const {
  auto value = TaggedField<EnumCache, kEnumCacheOffset>::load(isolate, *this);
  DCHECK(value.IsEnumCache());
  return value;
}
template <class D, class P>
void TorqueGeneratedDescriptorArray<D, P>::set_enum_cache(EnumCache value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsEnumCache());
  RELAXED_WRITE_FIELD(*this, kEnumCacheOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kEnumCacheOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedDescriptorArray<D, P>::TorqueGeneratedDescriptorArray(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsDescriptorArray());
}
template<class D, class P>
inline TorqueGeneratedDescriptorArray<D, P>::TorqueGeneratedDescriptorArray(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsDescriptorArray());
}
template <class D, class P>
int TorqueGeneratedEmbedderDataArray<D, P>::length() const {
  return TaggedField<Smi, kLengthOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedEmbedderDataArray<D, P>::set_length(int value) {
  WRITE_FIELD(*this, kLengthOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedEmbedderDataArray<D, P>::TorqueGeneratedEmbedderDataArray(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsEmbedderDataArray());
}
template<class D, class P>
inline TorqueGeneratedEmbedderDataArray<D, P>::TorqueGeneratedEmbedderDataArray(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsEmbedderDataArray());
}
template <class D, class P>
HeapObject TorqueGeneratedFeedbackCell<D, P>::value() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFeedbackCell::value(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFeedbackCell<D, P>::value(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kValueOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFixedArray() || value.IsFeedbackVector());
  return value;
}
template <class D, class P>
void TorqueGeneratedFeedbackCell<D, P>::set_value(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFixedArray() || value.IsFeedbackVector());
  RELAXED_WRITE_FIELD(*this, kValueOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kValueOffset, value, mode);
}

template <class D, class P>
int32_t TorqueGeneratedFeedbackCell<D, P>::interrupt_budget() const {
  return this->template ReadField<int32_t>(kInterruptBudgetOffset);
}
template <class D, class P>
void TorqueGeneratedFeedbackCell<D, P>::set_interrupt_budget(int32_t value) {
  this->template WriteField<int32_t>(kInterruptBudgetOffset, value);
}

template<class D, class P>
inline TorqueGeneratedFeedbackCell<D, P>::TorqueGeneratedFeedbackCell(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsFeedbackCell());
}
template<class D, class P>
inline TorqueGeneratedFeedbackCell<D, P>::TorqueGeneratedFeedbackCell(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsFeedbackCell());
}
template<class D, class P>
inline TorqueGeneratedArrayList<D, P>::TorqueGeneratedArrayList(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsArrayList());
}
template<class D, class P>
inline TorqueGeneratedArrayList<D, P>::TorqueGeneratedArrayList(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsArrayList());
}
template<class D, class P>
inline TorqueGeneratedTemplateList<D, P>::TorqueGeneratedTemplateList(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsTemplateList());
}
template<class D, class P>
inline TorqueGeneratedTemplateList<D, P>::TorqueGeneratedTemplateList(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsTemplateList());
}
template <class D, class P>
int TorqueGeneratedWeakArrayList<D, P>::capacity() const {
  return TaggedField<Smi, kCapacityOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedWeakArrayList<D, P>::set_capacity(int value) {
  WRITE_FIELD(*this, kCapacityOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedWeakArrayList<D, P>::length() const {
  return TaggedField<Smi, kLengthOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedWeakArrayList<D, P>::set_length(int value) {
  WRITE_FIELD(*this, kLengthOffset, Smi::FromInt(value));
}

template <class D, class P>
MaybeObject TorqueGeneratedWeakArrayList<D, P>::objects(int i) const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWeakArrayList::objects(isolate, i);
}
template <class D, class P>
MaybeObject TorqueGeneratedWeakArrayList<D, P>::objects(const Isolate* isolate, int i) const {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->capacity());
  int offset = kObjectsOffset + i * kTaggedSize;
  auto value = TaggedField<MaybeObject>::Relaxed_Load(isolate, *this, offset);
  DCHECK(value.IsCleared() || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsHeapObject()) || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsSmi()) || value.IsWeak());
  return value;
}
template <class D, class P>
void TorqueGeneratedWeakArrayList<D, P>::set_objects(int i, MaybeObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsCleared() || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsHeapObject()) || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsSmi()) || value.IsWeak());
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->capacity());
  int offset = kObjectsOffset + i * kTaggedSize;
  RELAXED_WRITE_WEAK_FIELD(*this, offset, value);
  CONDITIONAL_WEAK_WRITE_BARRIER(*this, offset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedWeakArrayList<D, P>::TorqueGeneratedWeakArrayList(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsWeakArrayList());
}
template<class D, class P>
inline TorqueGeneratedWeakArrayList<D, P>::TorqueGeneratedWeakArrayList(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsWeakArrayList());
}
template <class D, class P>
int TorqueGeneratedFreeSpace<D, P>::size() const {
  return TaggedField<Smi, kSizeOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedFreeSpace<D, P>::set_size(int value) {
  WRITE_FIELD(*this, kSizeOffset, Smi::FromInt(value));
}

template <class D, class P>
MaybeObject TorqueGeneratedFreeSpace<D, P>::next() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFreeSpace::next(isolate);
}
template <class D, class P>
MaybeObject TorqueGeneratedFreeSpace<D, P>::next(const Isolate* isolate) const {
  auto value = TaggedField<MaybeObject, kNextOffset>::load(isolate, *this);
  DCHECK(value.IsCleared() || value.IsWeak() || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsFreeSpace()));
  return value;
}
template <class D, class P>
void TorqueGeneratedFreeSpace<D, P>::set_next(MaybeObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsCleared() || value.IsWeak() || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsFreeSpace()));
  RELAXED_WRITE_WEAK_FIELD(*this, kNextOffset, value);
  CONDITIONAL_WEAK_WRITE_BARRIER(*this, kNextOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedFreeSpace<D, P>::TorqueGeneratedFreeSpace(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsFreeSpace());
}
template<class D, class P>
inline TorqueGeneratedFreeSpace<D, P>::TorqueGeneratedFreeSpace(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsFreeSpace());
}
template <class D, class P>
uintptr_t TorqueGeneratedJSArrayBuffer<D, P>::byte_length() const {
  return this->template ReadField<uintptr_t>(kByteLengthOffset);
}
template <class D, class P>
void TorqueGeneratedJSArrayBuffer<D, P>::set_byte_length(uintptr_t value) {
  this->template WriteField<uintptr_t>(kByteLengthOffset, value);
}

template <class D, class P>
void* TorqueGeneratedJSArrayBuffer<D, P>::extension() const {
  return this->template ReadField<void*>(kExtensionOffset);
}
template <class D, class P>
void TorqueGeneratedJSArrayBuffer<D, P>::set_extension(void* value) {
  this->template WriteField<void*>(kExtensionOffset, value);
}

template <class D, class P>
uint32_t TorqueGeneratedJSArrayBuffer<D, P>::bit_field() const {
  return this->template ReadField<uint32_t>(kBitFieldOffset);
}
template <class D, class P>
void TorqueGeneratedJSArrayBuffer<D, P>::set_bit_field(uint32_t value) {
  this->template WriteField<uint32_t>(kBitFieldOffset, value);
}

template<class D, class P>
inline TorqueGeneratedJSArrayBuffer<D, P>::TorqueGeneratedJSArrayBuffer(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSArrayBuffer());
}
template<class D, class P>
inline TorqueGeneratedJSArrayBuffer<D, P>::TorqueGeneratedJSArrayBuffer(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSArrayBuffer());
}
template<class D, class P>
inline TorqueGeneratedJSDataView<D, P>::TorqueGeneratedJSDataView(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSDataView());
}
template<class D, class P>
inline TorqueGeneratedJSDataView<D, P>::TorqueGeneratedJSDataView(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSDataView());
}
template <class D, class P>
Object TorqueGeneratedJSCollectionIterator<D, P>::table() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSCollectionIterator::table(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSCollectionIterator<D, P>::table(const Isolate* isolate) const {
  auto value = TaggedField<Object, kTableOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSCollectionIterator<D, P>::set_table(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kTableOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTableOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSCollectionIterator<D, P>::index() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSCollectionIterator::index(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSCollectionIterator<D, P>::index(const Isolate* isolate) const {
  auto value = TaggedField<Object, kIndexOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSCollectionIterator<D, P>::set_index(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kIndexOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kIndexOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSCollectionIterator<D, P>::TorqueGeneratedJSCollectionIterator(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSCollectionIterator());
}
template<class D, class P>
inline TorqueGeneratedJSCollectionIterator<D, P>::TorqueGeneratedJSCollectionIterator(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSCollectionIterator());
}
template <class D, class P>
Object TorqueGeneratedJSCollection<D, P>::table() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSCollection::table(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSCollection<D, P>::table(const Isolate* isolate) const {
  auto value = TaggedField<Object, kTableOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSCollection<D, P>::set_table(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kTableOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTableOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSCollection<D, P>::TorqueGeneratedJSCollection(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSCollection());
}
template<class D, class P>
inline TorqueGeneratedJSCollection<D, P>::TorqueGeneratedJSCollection(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSCollection());
}
template<class D, class P>
inline TorqueGeneratedJSSet<D, P>::TorqueGeneratedJSSet(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSSet());
}
template<class D, class P>
inline TorqueGeneratedJSSet<D, P>::TorqueGeneratedJSSet(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSSet());
}
template<class D, class P>
inline TorqueGeneratedJSMap<D, P>::TorqueGeneratedJSMap(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSMap());
}
template<class D, class P>
inline TorqueGeneratedJSMap<D, P>::TorqueGeneratedJSMap(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSMap());
}
template <class D, class P>
Object TorqueGeneratedJSWeakCollection<D, P>::table() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSWeakCollection::table(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSWeakCollection<D, P>::table(const Isolate* isolate) const {
  auto value = TaggedField<Object, kTableOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSWeakCollection<D, P>::set_table(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kTableOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTableOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSWeakCollection<D, P>::TorqueGeneratedJSWeakCollection(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSWeakCollection());
}
template<class D, class P>
inline TorqueGeneratedJSWeakCollection<D, P>::TorqueGeneratedJSWeakCollection(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSWeakCollection());
}
template<class D, class P>
inline TorqueGeneratedJSWeakSet<D, P>::TorqueGeneratedJSWeakSet(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSWeakSet());
}
template<class D, class P>
inline TorqueGeneratedJSWeakSet<D, P>::TorqueGeneratedJSWeakSet(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSWeakSet());
}
template<class D, class P>
inline TorqueGeneratedJSWeakMap<D, P>::TorqueGeneratedJSWeakMap(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSWeakMap());
}
template<class D, class P>
inline TorqueGeneratedJSWeakMap<D, P>::TorqueGeneratedJSWeakMap(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSWeakMap());
}
template <class D, class P>
JSFunction TorqueGeneratedJSGeneratorObject<D, P>::function() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSGeneratorObject::function(isolate);
}
template <class D, class P>
JSFunction TorqueGeneratedJSGeneratorObject<D, P>::function(const Isolate* isolate) const {
  auto value = TaggedField<JSFunction, kFunctionOffset>::load(isolate, *this);
  DCHECK(value.IsJSFunction());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSGeneratorObject<D, P>::set_function(JSFunction value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSFunction());
  RELAXED_WRITE_FIELD(*this, kFunctionOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kFunctionOffset, value, mode);
}

template <class D, class P>
Context TorqueGeneratedJSGeneratorObject<D, P>::context() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSGeneratorObject::context(isolate);
}
template <class D, class P>
Context TorqueGeneratedJSGeneratorObject<D, P>::context(const Isolate* isolate) const {
  auto value = TaggedField<Context, kContextOffset>::load(isolate, *this);
  DCHECK(value.IsContext());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSGeneratorObject<D, P>::set_context(Context value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsContext());
  RELAXED_WRITE_FIELD(*this, kContextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kContextOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSGeneratorObject<D, P>::receiver() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSGeneratorObject::receiver(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSGeneratorObject<D, P>::receiver(const Isolate* isolate) const {
  auto value = TaggedField<Object, kReceiverOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSGeneratorObject<D, P>::set_receiver(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kReceiverOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kReceiverOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSGeneratorObject<D, P>::input_or_debug_pos() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSGeneratorObject::input_or_debug_pos(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSGeneratorObject<D, P>::input_or_debug_pos(const Isolate* isolate) const {
  auto value = TaggedField<Object, kInputOrDebugPosOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSGeneratorObject<D, P>::set_input_or_debug_pos(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kInputOrDebugPosOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kInputOrDebugPosOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedJSGeneratorObject<D, P>::resume_mode() const {
  return TaggedField<Smi, kResumeModeOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedJSGeneratorObject<D, P>::set_resume_mode(int value) {
  WRITE_FIELD(*this, kResumeModeOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedJSGeneratorObject<D, P>::continuation() const {
  return TaggedField<Smi, kContinuationOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedJSGeneratorObject<D, P>::set_continuation(int value) {
  WRITE_FIELD(*this, kContinuationOffset, Smi::FromInt(value));
}

template <class D, class P>
FixedArray TorqueGeneratedJSGeneratorObject<D, P>::parameters_and_registers() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSGeneratorObject::parameters_and_registers(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedJSGeneratorObject<D, P>::parameters_and_registers(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kParametersAndRegistersOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSGeneratorObject<D, P>::set_parameters_and_registers(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kParametersAndRegistersOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kParametersAndRegistersOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSGeneratorObject<D, P>::TorqueGeneratedJSGeneratorObject(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSGeneratorObject());
}
template<class D, class P>
inline TorqueGeneratedJSGeneratorObject<D, P>::TorqueGeneratedJSGeneratorObject(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSGeneratorObject());
}
template <class D, class P>
JSPromise TorqueGeneratedJSAsyncFunctionObject<D, P>::promise() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSAsyncFunctionObject::promise(isolate);
}
template <class D, class P>
JSPromise TorqueGeneratedJSAsyncFunctionObject<D, P>::promise(const Isolate* isolate) const {
  auto value = TaggedField<JSPromise, kPromiseOffset>::load(isolate, *this);
  DCHECK(value.IsJSPromise());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSAsyncFunctionObject<D, P>::set_promise(JSPromise value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSPromise());
  RELAXED_WRITE_FIELD(*this, kPromiseOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPromiseOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSAsyncFunctionObject<D, P>::TorqueGeneratedJSAsyncFunctionObject(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSAsyncFunctionObject());
}
template<class D, class P>
inline TorqueGeneratedJSAsyncFunctionObject<D, P>::TorqueGeneratedJSAsyncFunctionObject(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSAsyncFunctionObject());
}
template <class D, class P>
HeapObject TorqueGeneratedJSAsyncGeneratorObject<D, P>::queue() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSAsyncGeneratorObject::queue(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedJSAsyncGeneratorObject<D, P>::queue(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kQueueOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSAsyncGeneratorObject<D, P>::set_queue(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject());
  RELAXED_WRITE_FIELD(*this, kQueueOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kQueueOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedJSAsyncGeneratorObject<D, P>::is_awaiting() const {
  return TaggedField<Smi, kIsAwaitingOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedJSAsyncGeneratorObject<D, P>::set_is_awaiting(int value) {
  WRITE_FIELD(*this, kIsAwaitingOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedJSAsyncGeneratorObject<D, P>::TorqueGeneratedJSAsyncGeneratorObject(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSAsyncGeneratorObject());
}
template<class D, class P>
inline TorqueGeneratedJSAsyncGeneratorObject<D, P>::TorqueGeneratedJSAsyncGeneratorObject(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSAsyncGeneratorObject());
}
template <class D, class P>
HeapObject TorqueGeneratedAsyncGeneratorRequest<D, P>::next() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAsyncGeneratorRequest::next(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedAsyncGeneratorRequest<D, P>::next(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kNextOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsAsyncGeneratorRequest());
  return value;
}
template <class D, class P>
void TorqueGeneratedAsyncGeneratorRequest<D, P>::set_next(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsAsyncGeneratorRequest());
  RELAXED_WRITE_FIELD(*this, kNextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNextOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedAsyncGeneratorRequest<D, P>::resume_mode() const {
  return TaggedField<Smi, kResumeModeOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedAsyncGeneratorRequest<D, P>::set_resume_mode(int value) {
  WRITE_FIELD(*this, kResumeModeOffset, Smi::FromInt(value));
}

template <class D, class P>
Object TorqueGeneratedAsyncGeneratorRequest<D, P>::value() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAsyncGeneratorRequest::value(isolate);
}
template <class D, class P>
Object TorqueGeneratedAsyncGeneratorRequest<D, P>::value(const Isolate* isolate) const {
  auto value = TaggedField<Object, kValueOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedAsyncGeneratorRequest<D, P>::set_value(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kValueOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kValueOffset, value, mode);
}

template <class D, class P>
JSPromise TorqueGeneratedAsyncGeneratorRequest<D, P>::promise() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedAsyncGeneratorRequest::promise(isolate);
}
template <class D, class P>
JSPromise TorqueGeneratedAsyncGeneratorRequest<D, P>::promise(const Isolate* isolate) const {
  auto value = TaggedField<JSPromise, kPromiseOffset>::load(isolate, *this);
  DCHECK(value.IsJSPromise());
  return value;
}
template <class D, class P>
void TorqueGeneratedAsyncGeneratorRequest<D, P>::set_promise(JSPromise value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSPromise());
  RELAXED_WRITE_FIELD(*this, kPromiseOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPromiseOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedAsyncGeneratorRequest<D, P>::TorqueGeneratedAsyncGeneratorRequest(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsAsyncGeneratorRequest());
}
template<class D, class P>
inline TorqueGeneratedAsyncGeneratorRequest<D, P>::TorqueGeneratedAsyncGeneratorRequest(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsAsyncGeneratorRequest());
}
template <class D, class P>
Object TorqueGeneratedJSGlobalProxy<D, P>::native_context() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSGlobalProxy::native_context(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSGlobalProxy<D, P>::native_context(const Isolate* isolate) const {
  auto value = TaggedField<Object, kNativeContextOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSGlobalProxy<D, P>::set_native_context(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kNativeContextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNativeContextOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSGlobalProxy<D, P>::TorqueGeneratedJSGlobalProxy(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSGlobalProxy());
}
template<class D, class P>
inline TorqueGeneratedJSGlobalProxy<D, P>::TorqueGeneratedJSGlobalProxy(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSGlobalProxy());
}
template <class D, class P>
Object TorqueGeneratedJSPrimitiveWrapper<D, P>::value() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSPrimitiveWrapper::value(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSPrimitiveWrapper<D, P>::value(const Isolate* isolate) const {
  auto value = TaggedField<Object, kValueOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSPrimitiveWrapper<D, P>::set_value(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kValueOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kValueOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSPrimitiveWrapper<D, P>::TorqueGeneratedJSPrimitiveWrapper(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSPrimitiveWrapper());
}
template<class D, class P>
inline TorqueGeneratedJSPrimitiveWrapper<D, P>::TorqueGeneratedJSPrimitiveWrapper(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSPrimitiveWrapper());
}
template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::value() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSDate::value(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::value(const Isolate* isolate) const {
  auto value = TaggedField<Object, kValueOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsHeapNumber() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSDate<D, P>::set_value(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsHeapNumber() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kValueOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kValueOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::year() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSDate::year(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::year(const Isolate* isolate) const {
  auto value = TaggedField<Object, kYearOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSDate<D, P>::set_year(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  RELAXED_WRITE_FIELD(*this, kYearOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kYearOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::month() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSDate::month(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::month(const Isolate* isolate) const {
  auto value = TaggedField<Object, kMonthOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSDate<D, P>::set_month(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  RELAXED_WRITE_FIELD(*this, kMonthOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kMonthOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::day() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSDate::day(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::day(const Isolate* isolate) const {
  auto value = TaggedField<Object, kDayOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSDate<D, P>::set_day(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  RELAXED_WRITE_FIELD(*this, kDayOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDayOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::weekday() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSDate::weekday(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::weekday(const Isolate* isolate) const {
  auto value = TaggedField<Object, kWeekdayOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSDate<D, P>::set_weekday(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  RELAXED_WRITE_FIELD(*this, kWeekdayOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kWeekdayOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::hour() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSDate::hour(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::hour(const Isolate* isolate) const {
  auto value = TaggedField<Object, kHourOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSDate<D, P>::set_hour(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  RELAXED_WRITE_FIELD(*this, kHourOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kHourOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::min() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSDate::min(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::min(const Isolate* isolate) const {
  auto value = TaggedField<Object, kMinOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSDate<D, P>::set_min(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  RELAXED_WRITE_FIELD(*this, kMinOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kMinOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::sec() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSDate::sec(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::sec(const Isolate* isolate) const {
  auto value = TaggedField<Object, kSecOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSDate<D, P>::set_sec(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  RELAXED_WRITE_FIELD(*this, kSecOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSecOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::cache_stamp() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSDate::cache_stamp(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSDate<D, P>::cache_stamp(const Isolate* isolate) const {
  auto value = TaggedField<Object, kCacheStampOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSDate<D, P>::set_cache_stamp(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi() || value.IsHeapNumber());
  RELAXED_WRITE_FIELD(*this, kCacheStampOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCacheStampOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSDate<D, P>::TorqueGeneratedJSDate(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSDate());
}
template<class D, class P>
inline TorqueGeneratedJSDate<D, P>::TorqueGeneratedJSDate(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSDate());
}
template <class D, class P>
JSReceiver TorqueGeneratedJSAsyncFromSyncIterator<D, P>::sync_iterator() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSAsyncFromSyncIterator::sync_iterator(isolate);
}
template <class D, class P>
JSReceiver TorqueGeneratedJSAsyncFromSyncIterator<D, P>::sync_iterator(const Isolate* isolate) const {
  auto value = TaggedField<JSReceiver, kSyncIteratorOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSAsyncFromSyncIterator<D, P>::set_sync_iterator(JSReceiver value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver());
  RELAXED_WRITE_FIELD(*this, kSyncIteratorOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSyncIteratorOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSAsyncFromSyncIterator<D, P>::next() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSAsyncFromSyncIterator::next(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSAsyncFromSyncIterator<D, P>::next(const Isolate* isolate) const {
  auto value = TaggedField<Object, kNextOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSAsyncFromSyncIterator<D, P>::set_next(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kNextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNextOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSAsyncFromSyncIterator<D, P>::TorqueGeneratedJSAsyncFromSyncIterator(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSAsyncFromSyncIterator());
}
template<class D, class P>
inline TorqueGeneratedJSAsyncFromSyncIterator<D, P>::TorqueGeneratedJSAsyncFromSyncIterator(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSAsyncFromSyncIterator());
}
template <class D, class P>
String TorqueGeneratedJSStringIterator<D, P>::string() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSStringIterator::string(isolate);
}
template <class D, class P>
String TorqueGeneratedJSStringIterator<D, P>::string(const Isolate* isolate) const {
  auto value = TaggedField<String, kStringOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSStringIterator<D, P>::set_string(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kStringOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kStringOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedJSStringIterator<D, P>::index() const {
  return TaggedField<Smi, kIndexOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedJSStringIterator<D, P>::set_index(int value) {
  WRITE_FIELD(*this, kIndexOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedJSStringIterator<D, P>::TorqueGeneratedJSStringIterator(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSStringIterator());
}
template<class D, class P>
inline TorqueGeneratedJSStringIterator<D, P>::TorqueGeneratedJSStringIterator(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSStringIterator());
}
template <class D, class P>
JSReceiver TorqueGeneratedJSRegExpStringIterator<D, P>::iterating_reg_exp() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSRegExpStringIterator::iterating_reg_exp(isolate);
}
template <class D, class P>
JSReceiver TorqueGeneratedJSRegExpStringIterator<D, P>::iterating_reg_exp(const Isolate* isolate) const {
  auto value = TaggedField<JSReceiver, kIteratingRegExpOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSRegExpStringIterator<D, P>::set_iterating_reg_exp(JSReceiver value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver());
  RELAXED_WRITE_FIELD(*this, kIteratingRegExpOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kIteratingRegExpOffset, value, mode);
}

template <class D, class P>
String TorqueGeneratedJSRegExpStringIterator<D, P>::iterated_string() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSRegExpStringIterator::iterated_string(isolate);
}
template <class D, class P>
String TorqueGeneratedJSRegExpStringIterator<D, P>::iterated_string(const Isolate* isolate) const {
  auto value = TaggedField<String, kIteratedStringOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSRegExpStringIterator<D, P>::set_iterated_string(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kIteratedStringOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kIteratedStringOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedJSRegExpStringIterator<D, P>::flags() const {
  return TaggedField<Smi, kFlagsOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedJSRegExpStringIterator<D, P>::set_flags(int value) {
  WRITE_FIELD(*this, kFlagsOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedJSRegExpStringIterator<D, P>::TorqueGeneratedJSRegExpStringIterator(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSRegExpStringIterator());
}
template<class D, class P>
inline TorqueGeneratedJSRegExpStringIterator<D, P>::TorqueGeneratedJSRegExpStringIterator(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSRegExpStringIterator());
}
template <class D, class P>
HeapObject TorqueGeneratedJSRegExp<D, P>::data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSRegExp::data(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedJSRegExp<D, P>::data(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kDataOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSRegExp<D, P>::set_data(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDataOffset, value, mode);
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedJSRegExp<D, P>::source() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSRegExp::source(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedJSRegExp<D, P>::source(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kSourceOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSRegExp<D, P>::set_source(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kSourceOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSourceOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedJSRegExp<D, P>::flags() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSRegExp::flags(isolate);
}
template <class D, class P>
Object TorqueGeneratedJSRegExp<D, P>::flags(const Isolate* isolate) const {
  auto value = TaggedField<Object, kFlagsOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSRegExp<D, P>::set_flags(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kFlagsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kFlagsOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSRegExp<D, P>::TorqueGeneratedJSRegExp(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSRegExp());
}
template<class D, class P>
inline TorqueGeneratedJSRegExp<D, P>::TorqueGeneratedJSRegExp(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSRegExp());
}
template <class D, class P>
HeapObject TorqueGeneratedJSWeakRef<D, P>::target() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSWeakRef::target(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedJSWeakRef<D, P>::target(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kTargetOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSWeakRef<D, P>::set_target(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball());
  RELAXED_WRITE_FIELD(*this, kTargetOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTargetOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSWeakRef<D, P>::TorqueGeneratedJSWeakRef(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSWeakRef());
}
template<class D, class P>
inline TorqueGeneratedJSWeakRef<D, P>::TorqueGeneratedJSWeakRef(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSWeakRef());
}
template <class D, class P>
int TorqueGeneratedArrayBoilerplateDescription<D, P>::flags() const {
  return TaggedField<Smi, kFlagsOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedArrayBoilerplateDescription<D, P>::set_flags(int value) {
  WRITE_FIELD(*this, kFlagsOffset, Smi::FromInt(value));
}

template <class D, class P>
FixedArrayBase TorqueGeneratedArrayBoilerplateDescription<D, P>::constant_elements() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedArrayBoilerplateDescription::constant_elements(isolate);
}
template <class D, class P>
FixedArrayBase TorqueGeneratedArrayBoilerplateDescription<D, P>::constant_elements(const Isolate* isolate) const {
  auto value = TaggedField<FixedArrayBase, kConstantElementsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArrayBase());
  return value;
}
template <class D, class P>
void TorqueGeneratedArrayBoilerplateDescription<D, P>::set_constant_elements(FixedArrayBase value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArrayBase());
  RELAXED_WRITE_FIELD(*this, kConstantElementsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kConstantElementsOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedArrayBoilerplateDescription<D, P>::TorqueGeneratedArrayBoilerplateDescription(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsArrayBoilerplateDescription());
}
template<class D, class P>
inline TorqueGeneratedArrayBoilerplateDescription<D, P>::TorqueGeneratedArrayBoilerplateDescription(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsArrayBoilerplateDescription());
}
template<class D, class P>
inline TorqueGeneratedMicrotask<D, P>::TorqueGeneratedMicrotask(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsMicrotask());
}
template<class D, class P>
inline TorqueGeneratedMicrotask<D, P>::TorqueGeneratedMicrotask(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsMicrotask());
}
template <class D, class P>
Foreign TorqueGeneratedCallbackTask<D, P>::callback() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedCallbackTask::callback(isolate);
}
template <class D, class P>
Foreign TorqueGeneratedCallbackTask<D, P>::callback(const Isolate* isolate) const {
  auto value = TaggedField<Foreign, kCallbackOffset>::load(isolate, *this);
  DCHECK(value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedCallbackTask<D, P>::set_callback(Foreign value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kCallbackOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCallbackOffset, value, mode);
}

template <class D, class P>
Foreign TorqueGeneratedCallbackTask<D, P>::data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedCallbackTask::data(isolate);
}
template <class D, class P>
Foreign TorqueGeneratedCallbackTask<D, P>::data(const Isolate* isolate) const {
  auto value = TaggedField<Foreign, kDataOffset>::load(isolate, *this);
  DCHECK(value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedCallbackTask<D, P>::set_data(Foreign value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kDataOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedCallbackTask<D, P>::TorqueGeneratedCallbackTask(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsCallbackTask());
}
template<class D, class P>
inline TorqueGeneratedCallbackTask<D, P>::TorqueGeneratedCallbackTask(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsCallbackTask());
}
template <class D, class P>
JSReceiver TorqueGeneratedCallableTask<D, P>::callable() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedCallableTask::callable(isolate);
}
template <class D, class P>
JSReceiver TorqueGeneratedCallableTask<D, P>::callable(const Isolate* isolate) const {
  auto value = TaggedField<JSReceiver, kCallableOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver());
  return value;
}
template <class D, class P>
void TorqueGeneratedCallableTask<D, P>::set_callable(JSReceiver value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver());
  RELAXED_WRITE_FIELD(*this, kCallableOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCallableOffset, value, mode);
}

template <class D, class P>
Context TorqueGeneratedCallableTask<D, P>::context() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedCallableTask::context(isolate);
}
template <class D, class P>
Context TorqueGeneratedCallableTask<D, P>::context(const Isolate* isolate) const {
  auto value = TaggedField<Context, kContextOffset>::load(isolate, *this);
  DCHECK(value.IsContext());
  return value;
}
template <class D, class P>
void TorqueGeneratedCallableTask<D, P>::set_context(Context value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsContext());
  RELAXED_WRITE_FIELD(*this, kContextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kContextOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedCallableTask<D, P>::TorqueGeneratedCallableTask(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsCallableTask());
}
template<class D, class P>
inline TorqueGeneratedCallableTask<D, P>::TorqueGeneratedCallableTask(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsCallableTask());
}
template <class D, class P>
Module TorqueGeneratedJSModuleNamespace<D, P>::module() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedJSModuleNamespace::module(isolate);
}
template <class D, class P>
Module TorqueGeneratedJSModuleNamespace<D, P>::module(const Isolate* isolate) const {
  auto value = TaggedField<Module, kModuleOffset>::load(isolate, *this);
  DCHECK(value.IsModule());
  return value;
}
template <class D, class P>
void TorqueGeneratedJSModuleNamespace<D, P>::set_module(Module value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsModule());
  RELAXED_WRITE_FIELD(*this, kModuleOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kModuleOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedJSModuleNamespace<D, P>::TorqueGeneratedJSModuleNamespace(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsJSModuleNamespace());
}
template<class D, class P>
inline TorqueGeneratedJSModuleNamespace<D, P>::TorqueGeneratedJSModuleNamespace(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsJSModuleNamespace());
}
template <class D, class P>
Object TorqueGeneratedPromiseReaction<D, P>::next() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseReaction::next(isolate);
}
template <class D, class P>
Object TorqueGeneratedPromiseReaction<D, P>::next(const Isolate* isolate) const {
  auto value = TaggedField<Object, kNextOffset>::load(isolate, *this);
  DCHECK(value.IsSmi() || value.IsPromiseReaction());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseReaction<D, P>::set_next(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSmi() || value.IsPromiseReaction());
  RELAXED_WRITE_FIELD(*this, kNextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNextOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedPromiseReaction<D, P>::reject_handler() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseReaction::reject_handler(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedPromiseReaction<D, P>::reject_handler(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kRejectHandlerOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsJSObject() || value.IsJSProxy() || value.IsJSBoundFunction() || value.IsJSFunction());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseReaction<D, P>::set_reject_handler(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsJSObject() || value.IsJSProxy() || value.IsJSBoundFunction() || value.IsJSFunction());
  RELAXED_WRITE_FIELD(*this, kRejectHandlerOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kRejectHandlerOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedPromiseReaction<D, P>::fulfill_handler() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseReaction::fulfill_handler(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedPromiseReaction<D, P>::fulfill_handler(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kFulfillHandlerOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsJSObject() || value.IsJSProxy() || value.IsJSBoundFunction() || value.IsJSFunction());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseReaction<D, P>::set_fulfill_handler(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsJSObject() || value.IsJSProxy() || value.IsJSBoundFunction() || value.IsJSFunction());
  RELAXED_WRITE_FIELD(*this, kFulfillHandlerOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kFulfillHandlerOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedPromiseReaction<D, P>::promise_or_capability() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseReaction::promise_or_capability(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedPromiseReaction<D, P>::promise_or_capability(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kPromiseOrCapabilityOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsJSPromise() || value.IsPromiseCapability());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseReaction<D, P>::set_promise_or_capability(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsJSPromise() || value.IsPromiseCapability());
  RELAXED_WRITE_FIELD(*this, kPromiseOrCapabilityOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPromiseOrCapabilityOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedPromiseReaction<D, P>::continuation_preserved_embedder_data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseReaction::continuation_preserved_embedder_data(isolate);
}
template <class D, class P>
Object TorqueGeneratedPromiseReaction<D, P>::continuation_preserved_embedder_data(const Isolate* isolate) const {
  auto value = TaggedField<Object, kContinuationPreservedEmbedderDataOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseReaction<D, P>::set_continuation_preserved_embedder_data(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kContinuationPreservedEmbedderDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kContinuationPreservedEmbedderDataOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedPromiseReaction<D, P>::TorqueGeneratedPromiseReaction(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsPromiseReaction());
}
template<class D, class P>
inline TorqueGeneratedPromiseReaction<D, P>::TorqueGeneratedPromiseReaction(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsPromiseReaction());
}
template <class D, class P>
Object TorqueGeneratedPromiseReactionJobTask<D, P>::argument() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseReactionJobTask::argument(isolate);
}
template <class D, class P>
Object TorqueGeneratedPromiseReactionJobTask<D, P>::argument(const Isolate* isolate) const {
  auto value = TaggedField<Object, kArgumentOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseReactionJobTask<D, P>::set_argument(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kArgumentOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kArgumentOffset, value, mode);
}

template <class D, class P>
Context TorqueGeneratedPromiseReactionJobTask<D, P>::context() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseReactionJobTask::context(isolate);
}
template <class D, class P>
Context TorqueGeneratedPromiseReactionJobTask<D, P>::context(const Isolate* isolate) const {
  auto value = TaggedField<Context, kContextOffset>::load(isolate, *this);
  DCHECK(value.IsContext());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseReactionJobTask<D, P>::set_context(Context value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsContext());
  RELAXED_WRITE_FIELD(*this, kContextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kContextOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedPromiseReactionJobTask<D, P>::handler() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseReactionJobTask::handler(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedPromiseReactionJobTask<D, P>::handler(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kHandlerOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsJSObject() || value.IsJSProxy() || value.IsJSBoundFunction() || value.IsJSFunction());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseReactionJobTask<D, P>::set_handler(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsJSObject() || value.IsJSProxy() || value.IsJSBoundFunction() || value.IsJSFunction());
  RELAXED_WRITE_FIELD(*this, kHandlerOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kHandlerOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedPromiseReactionJobTask<D, P>::promise_or_capability() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseReactionJobTask::promise_or_capability(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedPromiseReactionJobTask<D, P>::promise_or_capability(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kPromiseOrCapabilityOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsJSPromise() || value.IsPromiseCapability());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseReactionJobTask<D, P>::set_promise_or_capability(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsJSPromise() || value.IsPromiseCapability());
  RELAXED_WRITE_FIELD(*this, kPromiseOrCapabilityOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPromiseOrCapabilityOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedPromiseReactionJobTask<D, P>::continuation_preserved_embedder_data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseReactionJobTask::continuation_preserved_embedder_data(isolate);
}
template <class D, class P>
Object TorqueGeneratedPromiseReactionJobTask<D, P>::continuation_preserved_embedder_data(const Isolate* isolate) const {
  auto value = TaggedField<Object, kContinuationPreservedEmbedderDataOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseReactionJobTask<D, P>::set_continuation_preserved_embedder_data(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kContinuationPreservedEmbedderDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kContinuationPreservedEmbedderDataOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedPromiseReactionJobTask<D, P>::TorqueGeneratedPromiseReactionJobTask(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsPromiseReactionJobTask());
}
template<class D, class P>
inline TorqueGeneratedPromiseReactionJobTask<D, P>::TorqueGeneratedPromiseReactionJobTask(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsPromiseReactionJobTask());
}
template<class D, class P>
inline TorqueGeneratedPromiseFulfillReactionJobTask<D, P>::TorqueGeneratedPromiseFulfillReactionJobTask(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsPromiseFulfillReactionJobTask());
}
template<class D, class P>
inline TorqueGeneratedPromiseFulfillReactionJobTask<D, P>::TorqueGeneratedPromiseFulfillReactionJobTask(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsPromiseFulfillReactionJobTask());
}
template<class D, class P>
inline TorqueGeneratedPromiseRejectReactionJobTask<D, P>::TorqueGeneratedPromiseRejectReactionJobTask(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsPromiseRejectReactionJobTask());
}
template<class D, class P>
inline TorqueGeneratedPromiseRejectReactionJobTask<D, P>::TorqueGeneratedPromiseRejectReactionJobTask(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsPromiseRejectReactionJobTask());
}
template <class D, class P>
Context TorqueGeneratedPromiseResolveThenableJobTask<D, P>::context() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseResolveThenableJobTask::context(isolate);
}
template <class D, class P>
Context TorqueGeneratedPromiseResolveThenableJobTask<D, P>::context(const Isolate* isolate) const {
  auto value = TaggedField<Context, kContextOffset>::load(isolate, *this);
  DCHECK(value.IsContext());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseResolveThenableJobTask<D, P>::set_context(Context value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsContext());
  RELAXED_WRITE_FIELD(*this, kContextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kContextOffset, value, mode);
}

template <class D, class P>
JSPromise TorqueGeneratedPromiseResolveThenableJobTask<D, P>::promise_to_resolve() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseResolveThenableJobTask::promise_to_resolve(isolate);
}
template <class D, class P>
JSPromise TorqueGeneratedPromiseResolveThenableJobTask<D, P>::promise_to_resolve(const Isolate* isolate) const {
  auto value = TaggedField<JSPromise, kPromiseToResolveOffset>::load(isolate, *this);
  DCHECK(value.IsJSPromise());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseResolveThenableJobTask<D, P>::set_promise_to_resolve(JSPromise value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSPromise());
  RELAXED_WRITE_FIELD(*this, kPromiseToResolveOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPromiseToResolveOffset, value, mode);
}

template <class D, class P>
JSReceiver TorqueGeneratedPromiseResolveThenableJobTask<D, P>::thenable() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseResolveThenableJobTask::thenable(isolate);
}
template <class D, class P>
JSReceiver TorqueGeneratedPromiseResolveThenableJobTask<D, P>::thenable(const Isolate* isolate) const {
  auto value = TaggedField<JSReceiver, kThenableOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseResolveThenableJobTask<D, P>::set_thenable(JSReceiver value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver());
  RELAXED_WRITE_FIELD(*this, kThenableOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kThenableOffset, value, mode);
}

template <class D, class P>
JSReceiver TorqueGeneratedPromiseResolveThenableJobTask<D, P>::then() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPromiseResolveThenableJobTask::then(isolate);
}
template <class D, class P>
JSReceiver TorqueGeneratedPromiseResolveThenableJobTask<D, P>::then(const Isolate* isolate) const {
  auto value = TaggedField<JSReceiver, kThenOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver());
  return value;
}
template <class D, class P>
void TorqueGeneratedPromiseResolveThenableJobTask<D, P>::set_then(JSReceiver value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver());
  RELAXED_WRITE_FIELD(*this, kThenOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kThenOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedPromiseResolveThenableJobTask<D, P>::TorqueGeneratedPromiseResolveThenableJobTask(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsPromiseResolveThenableJobTask());
}
template<class D, class P>
inline TorqueGeneratedPromiseResolveThenableJobTask<D, P>::TorqueGeneratedPromiseResolveThenableJobTask(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsPromiseResolveThenableJobTask());
}
template <class D, class P>
int TorqueGeneratedPropertyDescriptorObject<D, P>::flags() const {
  return TaggedField<Smi, kFlagsOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedPropertyDescriptorObject<D, P>::set_flags(int value) {
  WRITE_FIELD(*this, kFlagsOffset, Smi::FromInt(value));
}

template <class D, class P>
Object TorqueGeneratedPropertyDescriptorObject<D, P>::value() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPropertyDescriptorObject::value(isolate);
}
template <class D, class P>
Object TorqueGeneratedPropertyDescriptorObject<D, P>::value(const Isolate* isolate) const {
  auto value = TaggedField<Object, kValueOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi() || value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedPropertyDescriptorObject<D, P>::set_value(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi() || value.IsOddball());
  RELAXED_WRITE_FIELD(*this, kValueOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kValueOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedPropertyDescriptorObject<D, P>::get() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPropertyDescriptorObject::get(isolate);
}
template <class D, class P>
Object TorqueGeneratedPropertyDescriptorObject<D, P>::get(const Isolate* isolate) const {
  auto value = TaggedField<Object, kGetOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi() || value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedPropertyDescriptorObject<D, P>::set_get(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi() || value.IsOddball());
  RELAXED_WRITE_FIELD(*this, kGetOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kGetOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedPropertyDescriptorObject<D, P>::set() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPropertyDescriptorObject::set(isolate);
}
template <class D, class P>
Object TorqueGeneratedPropertyDescriptorObject<D, P>::set(const Isolate* isolate) const {
  auto value = TaggedField<Object, kSetOffset>::load(isolate, *this);
  DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi() || value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedPropertyDescriptorObject<D, P>::set_set(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSReceiver() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsOddball() || value.IsSymbol() || value.IsString() || value.IsBigInt() || value.IsHeapNumber() || value.IsSmi() || value.IsOddball());
  RELAXED_WRITE_FIELD(*this, kSetOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSetOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedPropertyDescriptorObject<D, P>::TorqueGeneratedPropertyDescriptorObject(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsPropertyDescriptorObject());
}
template<class D, class P>
inline TorqueGeneratedPropertyDescriptorObject<D, P>::TorqueGeneratedPropertyDescriptorObject(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsPropertyDescriptorObject());
}
template <class D, class P>
HeapObject TorqueGeneratedPrototypeInfo<D, P>::module_namespace() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPrototypeInfo::module_namespace(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedPrototypeInfo<D, P>::module_namespace(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kModuleNamespaceOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsJSModuleNamespace());
  return value;
}
template <class D, class P>
void TorqueGeneratedPrototypeInfo<D, P>::set_module_namespace(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsJSModuleNamespace());
  RELAXED_WRITE_FIELD(*this, kModuleNamespaceOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kModuleNamespaceOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedPrototypeInfo<D, P>::prototype_users() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPrototypeInfo::prototype_users(isolate);
}
template <class D, class P>
Object TorqueGeneratedPrototypeInfo<D, P>::prototype_users(const Isolate* isolate) const {
  auto value = TaggedField<Object, kPrototypeUsersOffset>::load(isolate, *this);
  DCHECK(value.IsSmi() || value.IsWeakArrayList());
  return value;
}
template <class D, class P>
void TorqueGeneratedPrototypeInfo<D, P>::set_prototype_users(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSmi() || value.IsWeakArrayList());
  RELAXED_WRITE_FIELD(*this, kPrototypeUsersOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPrototypeUsersOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedPrototypeInfo<D, P>::prototype_chain_enum_cache() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPrototypeInfo::prototype_chain_enum_cache(isolate);
}
template <class D, class P>
Object TorqueGeneratedPrototypeInfo<D, P>::prototype_chain_enum_cache(const Isolate* isolate) const {
  auto value = TaggedField<Object, kPrototypeChainEnumCacheOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFixedArray() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedPrototypeInfo<D, P>::set_prototype_chain_enum_cache(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFixedArray() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kPrototypeChainEnumCacheOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPrototypeChainEnumCacheOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedPrototypeInfo<D, P>::registry_slot() const {
  return TaggedField<Smi, kRegistrySlotOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedPrototypeInfo<D, P>::set_registry_slot(int value) {
  WRITE_FIELD(*this, kRegistrySlotOffset, Smi::FromInt(value));
}

template <class D, class P>
MaybeObject TorqueGeneratedPrototypeInfo<D, P>::object_create_map() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedPrototypeInfo::object_create_map(isolate);
}
template <class D, class P>
MaybeObject TorqueGeneratedPrototypeInfo<D, P>::object_create_map(const Isolate* isolate) const {
  auto value = TaggedField<MaybeObject, kObjectCreateMapOffset>::load(isolate, *this);
  DCHECK(value.IsCleared() || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsOddball()) || (value.IsWeak() && value.GetHeapObjectOrSmi().IsMap()));
  return value;
}
template <class D, class P>
void TorqueGeneratedPrototypeInfo<D, P>::set_object_create_map(MaybeObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsCleared() || (!value.IsWeak() && value.GetHeapObjectOrSmi().IsOddball()) || (value.IsWeak() && value.GetHeapObjectOrSmi().IsMap()));
  RELAXED_WRITE_WEAK_FIELD(*this, kObjectCreateMapOffset, value);
  CONDITIONAL_WEAK_WRITE_BARRIER(*this, kObjectCreateMapOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedPrototypeInfo<D, P>::bit_field() const {
  return TaggedField<Smi, kBitFieldOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedPrototypeInfo<D, P>::set_bit_field(int value) {
  WRITE_FIELD(*this, kBitFieldOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedPrototypeInfo<D, P>::TorqueGeneratedPrototypeInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsPrototypeInfo());
}
template<class D, class P>
inline TorqueGeneratedPrototypeInfo<D, P>::TorqueGeneratedPrototypeInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsPrototypeInfo());
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedScript<D, P>::source() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedScript::source(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedScript<D, P>::source(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kSourceOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_source(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kSourceOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSourceOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedScript<D, P>::name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedScript::name(isolate);
}
template <class D, class P>
Object TorqueGeneratedScript<D, P>::name(const Isolate* isolate) const {
  auto value = TaggedField<Object, kNameOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_name(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNameOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedScript<D, P>::line_offset() const {
  return TaggedField<Smi, kLineOffsetOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_line_offset(int value) {
  WRITE_FIELD(*this, kLineOffsetOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedScript<D, P>::column_offset() const {
  return TaggedField<Smi, kColumnOffsetOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_column_offset(int value) {
  WRITE_FIELD(*this, kColumnOffsetOffset, Smi::FromInt(value));
}

template <class D, class P>
Object TorqueGeneratedScript<D, P>::context_data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedScript::context_data(isolate);
}
template <class D, class P>
Object TorqueGeneratedScript<D, P>::context_data(const Isolate* isolate) const {
  auto value = TaggedField<Object, kContextDataOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSymbol() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_context_data(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSymbol() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kContextDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kContextDataOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedScript<D, P>::script_type() const {
  return TaggedField<Smi, kScriptTypeOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_script_type(int value) {
  WRITE_FIELD(*this, kScriptTypeOffset, Smi::FromInt(value));
}

template <class D, class P>
HeapObject TorqueGeneratedScript<D, P>::line_ends() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedScript::line_ends(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedScript<D, P>::line_ends(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kLineEndsOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_line_ends(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kLineEndsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kLineEndsOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedScript<D, P>::id() const {
  return TaggedField<Smi, kIdOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_id(int value) {
  WRITE_FIELD(*this, kIdOffset, Smi::FromInt(value));
}

template <class D, class P>
HeapObject TorqueGeneratedScript<D, P>::eval_from_shared_or_wrapped_arguments() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedScript::eval_from_shared_or_wrapped_arguments(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedScript<D, P>::eval_from_shared_or_wrapped_arguments(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kEvalFromSharedOrWrappedArgumentsOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFixedArray() || value.IsSharedFunctionInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_eval_from_shared_or_wrapped_arguments(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFixedArray() || value.IsSharedFunctionInfo());
  RELAXED_WRITE_FIELD(*this, kEvalFromSharedOrWrappedArgumentsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kEvalFromSharedOrWrappedArgumentsOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedScript<D, P>::eval_from_position() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedScript::eval_from_position(isolate);
}
template <class D, class P>
Object TorqueGeneratedScript<D, P>::eval_from_position(const Isolate* isolate) const {
  auto value = TaggedField<Object, kEvalFromPositionOffset>::load(isolate, *this);
  DCHECK(value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_eval_from_position(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kEvalFromPositionOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kEvalFromPositionOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedScript<D, P>::shared_function_infos() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedScript::shared_function_infos(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedScript<D, P>::shared_function_infos(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kSharedFunctionInfosOffset>::load(isolate, *this);
  DCHECK(value.IsWeakFixedArray() || value.IsWeakArrayList());
  return value;
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_shared_function_infos(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsWeakFixedArray() || value.IsWeakArrayList());
  RELAXED_WRITE_FIELD(*this, kSharedFunctionInfosOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSharedFunctionInfosOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedScript<D, P>::flags() const {
  return TaggedField<Smi, kFlagsOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_flags(int value) {
  WRITE_FIELD(*this, kFlagsOffset, Smi::FromInt(value));
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedScript<D, P>::source_url() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedScript::source_url(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedScript<D, P>::source_url(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kSourceUrlOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_source_url(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kSourceUrlOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSourceUrlOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedScript<D, P>::source_mapping_url() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedScript::source_mapping_url(isolate);
}
template <class D, class P>
Object TorqueGeneratedScript<D, P>::source_mapping_url(const Isolate* isolate) const {
  auto value = TaggedField<Object, kSourceMappingUrlOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_source_mapping_url(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kSourceMappingUrlOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSourceMappingUrlOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedScript<D, P>::host_defined_options() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedScript::host_defined_options(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedScript<D, P>::host_defined_options(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kHostDefinedOptionsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedScript<D, P>::set_host_defined_options(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kHostDefinedOptionsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kHostDefinedOptionsOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedScript<D, P>::TorqueGeneratedScript(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsScript());
}
template<class D, class P>
inline TorqueGeneratedScript<D, P>::TorqueGeneratedScript(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsScript());
}
template <class D, class P>
int32_t TorqueGeneratedPreparseData<D, P>::data_length() const {
  return this->template ReadField<int32_t>(kDataLengthOffset);
}
template <class D, class P>
void TorqueGeneratedPreparseData<D, P>::set_data_length(int32_t value) {
  this->template WriteField<int32_t>(kDataLengthOffset, value);
}

template <class D, class P>
int32_t TorqueGeneratedPreparseData<D, P>::children_length() const {
  return this->template ReadField<int32_t>(kChildrenLengthOffset);
}
template <class D, class P>
void TorqueGeneratedPreparseData<D, P>::set_children_length(int32_t value) {
  this->template WriteField<int32_t>(kChildrenLengthOffset, value);
}

template<class D, class P>
inline TorqueGeneratedPreparseData<D, P>::TorqueGeneratedPreparseData(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsPreparseData());
}
template<class D, class P>
inline TorqueGeneratedPreparseData<D, P>::TorqueGeneratedPreparseData(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsPreparseData());
}
template <class D, class P>
String TorqueGeneratedUncompiledData<D, P>::inferred_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedUncompiledData::inferred_name(isolate);
}
template <class D, class P>
String TorqueGeneratedUncompiledData<D, P>::inferred_name(const Isolate* isolate) const {
  auto value = TaggedField<String, kInferredNameOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedUncompiledData<D, P>::set_inferred_name(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kInferredNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kInferredNameOffset, value, mode);
}

template <class D, class P>
int32_t TorqueGeneratedUncompiledData<D, P>::start_position() const {
  return this->template ReadField<int32_t>(kStartPositionOffset);
}
template <class D, class P>
void TorqueGeneratedUncompiledData<D, P>::set_start_position(int32_t value) {
  this->template WriteField<int32_t>(kStartPositionOffset, value);
}

template <class D, class P>
int32_t TorqueGeneratedUncompiledData<D, P>::end_position() const {
  return this->template ReadField<int32_t>(kEndPositionOffset);
}
template <class D, class P>
void TorqueGeneratedUncompiledData<D, P>::set_end_position(int32_t value) {
  this->template WriteField<int32_t>(kEndPositionOffset, value);
}

template<class D, class P>
inline TorqueGeneratedUncompiledData<D, P>::TorqueGeneratedUncompiledData(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsUncompiledData());
}
template<class D, class P>
inline TorqueGeneratedUncompiledData<D, P>::TorqueGeneratedUncompiledData(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsUncompiledData());
}
template<class D, class P>
inline TorqueGeneratedUncompiledDataWithoutPreparseData<D, P>::TorqueGeneratedUncompiledDataWithoutPreparseData(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsUncompiledDataWithoutPreparseData());
}
template<class D, class P>
inline TorqueGeneratedUncompiledDataWithoutPreparseData<D, P>::TorqueGeneratedUncompiledDataWithoutPreparseData(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsUncompiledDataWithoutPreparseData());
}
template <class D, class P>
PreparseData TorqueGeneratedUncompiledDataWithPreparseData<D, P>::preparse_data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedUncompiledDataWithPreparseData::preparse_data(isolate);
}
template <class D, class P>
PreparseData TorqueGeneratedUncompiledDataWithPreparseData<D, P>::preparse_data(const Isolate* isolate) const {
  auto value = TaggedField<PreparseData, kPreparseDataOffset>::load(isolate, *this);
  DCHECK(value.IsPreparseData());
  return value;
}
template <class D, class P>
void TorqueGeneratedUncompiledDataWithPreparseData<D, P>::set_preparse_data(PreparseData value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsPreparseData());
  RELAXED_WRITE_FIELD(*this, kPreparseDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPreparseDataOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedUncompiledDataWithPreparseData<D, P>::TorqueGeneratedUncompiledDataWithPreparseData(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsUncompiledDataWithPreparseData());
}
template<class D, class P>
inline TorqueGeneratedUncompiledDataWithPreparseData<D, P>::TorqueGeneratedUncompiledDataWithPreparseData(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsUncompiledDataWithPreparseData());
}
template <class D, class P>
HeapObject TorqueGeneratedSourceTextModule<D, P>::code() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModule::code(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedSourceTextModule<D, P>::code(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kCodeOffset>::load(isolate, *this);
  DCHECK(value.IsJSFunction() || value.IsJSGeneratorObject() || value.IsSharedFunctionInfo() || value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_code(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSFunction() || value.IsJSGeneratorObject() || value.IsSharedFunctionInfo() || value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kCodeOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCodeOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedSourceTextModule<D, P>::regular_exports() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModule::regular_exports(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedSourceTextModule<D, P>::regular_exports(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kRegularExportsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_regular_exports(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kRegularExportsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kRegularExportsOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedSourceTextModule<D, P>::regular_imports() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModule::regular_imports(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedSourceTextModule<D, P>::regular_imports(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kRegularImportsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_regular_imports(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kRegularImportsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kRegularImportsOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedSourceTextModule<D, P>::requested_modules() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModule::requested_modules(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedSourceTextModule<D, P>::requested_modules(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kRequestedModulesOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_requested_modules(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kRequestedModulesOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kRequestedModulesOffset, value, mode);
}

template <class D, class P>
Script TorqueGeneratedSourceTextModule<D, P>::script() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModule::script(isolate);
}
template <class D, class P>
Script TorqueGeneratedSourceTextModule<D, P>::script(const Isolate* isolate) const {
  auto value = TaggedField<Script, kScriptOffset>::load(isolate, *this);
  DCHECK(value.IsScript());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_script(Script value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsScript());
  RELAXED_WRITE_FIELD(*this, kScriptOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kScriptOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedSourceTextModule<D, P>::import_meta() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModule::import_meta(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedSourceTextModule<D, P>::import_meta(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kImportMetaOffset>::load(isolate, *this);
  DCHECK(value.IsJSObject() || value.IsOddball());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_import_meta(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSObject() || value.IsOddball());
  RELAXED_WRITE_FIELD(*this, kImportMetaOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kImportMetaOffset, value, mode);
}

template <class D, class P>
ArrayList TorqueGeneratedSourceTextModule<D, P>::async_parent_modules() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModule::async_parent_modules(isolate);
}
template <class D, class P>
ArrayList TorqueGeneratedSourceTextModule<D, P>::async_parent_modules(const Isolate* isolate) const {
  auto value = TaggedField<ArrayList, kAsyncParentModulesOffset>::load(isolate, *this);
  DCHECK(value.IsArrayList());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_async_parent_modules(ArrayList value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsArrayList());
  RELAXED_WRITE_FIELD(*this, kAsyncParentModulesOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kAsyncParentModulesOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedSourceTextModule<D, P>::top_level_capability() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModule::top_level_capability(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedSourceTextModule<D, P>::top_level_capability(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kTopLevelCapabilityOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsJSPromise());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_top_level_capability(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsJSPromise());
  RELAXED_WRITE_FIELD(*this, kTopLevelCapabilityOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTopLevelCapabilityOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedSourceTextModule<D, P>::dfs_index() const {
  return TaggedField<Smi, kDfsIndexOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_dfs_index(int value) {
  WRITE_FIELD(*this, kDfsIndexOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSourceTextModule<D, P>::dfs_ancestor_index() const {
  return TaggedField<Smi, kDfsAncestorIndexOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_dfs_ancestor_index(int value) {
  WRITE_FIELD(*this, kDfsAncestorIndexOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSourceTextModule<D, P>::pending_async_dependencies() const {
  return TaggedField<Smi, kPendingAsyncDependenciesOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_pending_async_dependencies(int value) {
  WRITE_FIELD(*this, kPendingAsyncDependenciesOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSourceTextModule<D, P>::flags() const {
  return TaggedField<Smi, kFlagsOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSourceTextModule<D, P>::set_flags(int value) {
  WRITE_FIELD(*this, kFlagsOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedSourceTextModule<D, P>::TorqueGeneratedSourceTextModule(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSourceTextModule());
}
template<class D, class P>
inline TorqueGeneratedSourceTextModule<D, P>::TorqueGeneratedSourceTextModule(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSourceTextModule());
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedSourceTextModuleInfoEntry<D, P>::export_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModuleInfoEntry::export_name(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedSourceTextModuleInfoEntry<D, P>::export_name(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kExportNameOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModuleInfoEntry<D, P>::set_export_name(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kExportNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kExportNameOffset, value, mode);
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedSourceTextModuleInfoEntry<D, P>::local_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModuleInfoEntry::local_name(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedSourceTextModuleInfoEntry<D, P>::local_name(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kLocalNameOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModuleInfoEntry<D, P>::set_local_name(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kLocalNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kLocalNameOffset, value, mode);
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedSourceTextModuleInfoEntry<D, P>::import_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSourceTextModuleInfoEntry::import_name(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedSourceTextModuleInfoEntry<D, P>::import_name(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kImportNameOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedSourceTextModuleInfoEntry<D, P>::set_import_name(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kImportNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kImportNameOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedSourceTextModuleInfoEntry<D, P>::module_request() const {
  return TaggedField<Smi, kModuleRequestOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSourceTextModuleInfoEntry<D, P>::set_module_request(int value) {
  WRITE_FIELD(*this, kModuleRequestOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSourceTextModuleInfoEntry<D, P>::cell_index() const {
  return TaggedField<Smi, kCellIndexOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSourceTextModuleInfoEntry<D, P>::set_cell_index(int value) {
  WRITE_FIELD(*this, kCellIndexOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSourceTextModuleInfoEntry<D, P>::beg_pos() const {
  return TaggedField<Smi, kBegPosOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSourceTextModuleInfoEntry<D, P>::set_beg_pos(int value) {
  WRITE_FIELD(*this, kBegPosOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedSourceTextModuleInfoEntry<D, P>::end_pos() const {
  return TaggedField<Smi, kEndPosOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSourceTextModuleInfoEntry<D, P>::set_end_pos(int value) {
  WRITE_FIELD(*this, kEndPosOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedSourceTextModuleInfoEntry<D, P>::TorqueGeneratedSourceTextModuleInfoEntry(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSourceTextModuleInfoEntry());
}
template<class D, class P>
inline TorqueGeneratedSourceTextModuleInfoEntry<D, P>::TorqueGeneratedSourceTextModuleInfoEntry(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSourceTextModuleInfoEntry());
}
template <class D, class P>
int TorqueGeneratedStackFrameInfo<D, P>::line_number() const {
  return TaggedField<Smi, kLineNumberOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_line_number(int value) {
  WRITE_FIELD(*this, kLineNumberOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedStackFrameInfo<D, P>::column_number() const {
  return TaggedField<Smi, kColumnNumberOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_column_number(int value) {
  WRITE_FIELD(*this, kColumnNumberOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedStackFrameInfo<D, P>::promise_combinator_index() const {
  return TaggedField<Smi, kPromiseCombinatorIndexOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_promise_combinator_index(int value) {
  WRITE_FIELD(*this, kPromiseCombinatorIndexOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedStackFrameInfo<D, P>::script_id() const {
  return TaggedField<Smi, kScriptIdOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_script_id(int value) {
  WRITE_FIELD(*this, kScriptIdOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedStackFrameInfo<D, P>::wasm_function_index() const {
  return TaggedField<Smi, kWasmFunctionIndexOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_wasm_function_index(int value) {
  WRITE_FIELD(*this, kWasmFunctionIndexOffset, Smi::FromInt(value));
}

template <class D, class P>
Object TorqueGeneratedStackFrameInfo<D, P>::script_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedStackFrameInfo::script_name(isolate);
}
template <class D, class P>
Object TorqueGeneratedStackFrameInfo<D, P>::script_name(const Isolate* isolate) const {
  auto value = TaggedField<Object, kScriptNameOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_script_name(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kScriptNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kScriptNameOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedStackFrameInfo<D, P>::script_name_or_source_url() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedStackFrameInfo::script_name_or_source_url(isolate);
}
template <class D, class P>
Object TorqueGeneratedStackFrameInfo<D, P>::script_name_or_source_url(const Isolate* isolate) const {
  auto value = TaggedField<Object, kScriptNameOrSourceUrlOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_script_name_or_source_url(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kScriptNameOrSourceUrlOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kScriptNameOrSourceUrlOffset, value, mode);
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedStackFrameInfo<D, P>::function_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedStackFrameInfo::function_name(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedStackFrameInfo<D, P>::function_name(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kFunctionNameOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_function_name(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kFunctionNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kFunctionNameOffset, value, mode);
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedStackFrameInfo<D, P>::method_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedStackFrameInfo::method_name(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedStackFrameInfo<D, P>::method_name(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kMethodNameOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_method_name(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kMethodNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kMethodNameOffset, value, mode);
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedStackFrameInfo<D, P>::type_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedStackFrameInfo::type_name(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedStackFrameInfo<D, P>::type_name(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kTypeNameOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_type_name(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kTypeNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTypeNameOffset, value, mode);
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedStackFrameInfo<D, P>::eval_origin() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedStackFrameInfo::eval_origin(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedStackFrameInfo<D, P>::eval_origin(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kEvalOriginOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_eval_origin(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kEvalOriginOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kEvalOriginOffset, value, mode);
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedStackFrameInfo<D, P>::wasm_module_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedStackFrameInfo::wasm_module_name(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedStackFrameInfo<D, P>::wasm_module_name(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kWasmModuleNameOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_wasm_module_name(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kWasmModuleNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kWasmModuleNameOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedStackFrameInfo<D, P>::wasm_instance() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedStackFrameInfo::wasm_instance(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedStackFrameInfo<D, P>::wasm_instance(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kWasmInstanceOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsOddball() || value.IsWasmInstanceObject());
  return value;
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_wasm_instance(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsOddball() || value.IsWasmInstanceObject());
  RELAXED_WRITE_FIELD(*this, kWasmInstanceOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kWasmInstanceOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedStackFrameInfo<D, P>::flag() const {
  return TaggedField<Smi, kFlagOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedStackFrameInfo<D, P>::set_flag(int value) {
  WRITE_FIELD(*this, kFlagOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedStackFrameInfo<D, P>::TorqueGeneratedStackFrameInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsStackFrameInfo());
}
template<class D, class P>
inline TorqueGeneratedStackFrameInfo<D, P>::TorqueGeneratedStackFrameInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsStackFrameInfo());
}
template <class D, class P>
HeapObject TorqueGeneratedStackTraceFrame<D, P>::frame_array() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedStackTraceFrame::frame_array(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedStackTraceFrame<D, P>::frame_array(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kFrameArrayOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedStackTraceFrame<D, P>::set_frame_array(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kFrameArrayOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kFrameArrayOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedStackTraceFrame<D, P>::frame_index() const {
  return TaggedField<Smi, kFrameIndexOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedStackTraceFrame<D, P>::set_frame_index(int value) {
  WRITE_FIELD(*this, kFrameIndexOffset, Smi::FromInt(value));
}

template <class D, class P>
HeapObject TorqueGeneratedStackTraceFrame<D, P>::frame_info() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedStackTraceFrame::frame_info(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedStackTraceFrame<D, P>::frame_info(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kFrameInfoOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsStackFrameInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedStackTraceFrame<D, P>::set_frame_info(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsStackFrameInfo());
  RELAXED_WRITE_FIELD(*this, kFrameInfoOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kFrameInfoOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedStackTraceFrame<D, P>::id() const {
  return TaggedField<Smi, kIdOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedStackTraceFrame<D, P>::set_id(int value) {
  WRITE_FIELD(*this, kIdOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedStackTraceFrame<D, P>::TorqueGeneratedStackTraceFrame(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsStackTraceFrame());
}
template<class D, class P>
inline TorqueGeneratedStackTraceFrame<D, P>::TorqueGeneratedStackTraceFrame(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsStackTraceFrame());
}
template <class D, class P>
String TorqueGeneratedConsString<D, P>::first() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedConsString::first(isolate);
}
template <class D, class P>
String TorqueGeneratedConsString<D, P>::first(const Isolate* isolate) const {
  auto value = TaggedField<String, kFirstOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedConsString<D, P>::set_first(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kFirstOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kFirstOffset, value, mode);
}

template <class D, class P>
String TorqueGeneratedConsString<D, P>::second() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedConsString::second(isolate);
}
template <class D, class P>
String TorqueGeneratedConsString<D, P>::second(const Isolate* isolate) const {
  auto value = TaggedField<String, kSecondOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedConsString<D, P>::set_second(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kSecondOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSecondOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedConsString<D, P>::TorqueGeneratedConsString(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsConsString());
}
template<class D, class P>
inline TorqueGeneratedConsString<D, P>::TorqueGeneratedConsString(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsConsString());
}
template<class D, class P>
inline TorqueGeneratedInternalizedString<D, P>::TorqueGeneratedInternalizedString(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsInternalizedString());
}
template<class D, class P>
inline TorqueGeneratedInternalizedString<D, P>::TorqueGeneratedInternalizedString(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsInternalizedString());
}
template<class D, class P>
inline TorqueGeneratedSeqString<D, P>::TorqueGeneratedSeqString(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSeqString());
}
template<class D, class P>
inline TorqueGeneratedSeqString<D, P>::TorqueGeneratedSeqString(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSeqString());
}
template <class D, class P>
char TorqueGeneratedSeqOneByteString<D, P>::chars(int i) const {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kCharsOffset + i * 1;
  return this->template ReadField<char>(offset);
}
template <class D, class P>
void TorqueGeneratedSeqOneByteString<D, P>::set_chars(int i, char value) {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kCharsOffset + i * 1;
  this->template WriteField<char>(offset, value);
}

template<class D, class P>
inline TorqueGeneratedSeqOneByteString<D, P>::TorqueGeneratedSeqOneByteString(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSeqOneByteString());
}
template<class D, class P>
inline TorqueGeneratedSeqOneByteString<D, P>::TorqueGeneratedSeqOneByteString(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSeqOneByteString());
}
template <class D, class P>
char16_t TorqueGeneratedSeqTwoByteString<D, P>::chars(int i) const {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kCharsOffset + i * 2;
  return this->template ReadField<char16_t>(offset);
}
template <class D, class P>
void TorqueGeneratedSeqTwoByteString<D, P>::set_chars(int i, char16_t value) {
  DCHECK_GE(i, 0);
  DCHECK_LT(i, this->length());
  int offset = kCharsOffset + i * 2;
  this->template WriteField<char16_t>(offset, value);
}

template<class D, class P>
inline TorqueGeneratedSeqTwoByteString<D, P>::TorqueGeneratedSeqTwoByteString(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSeqTwoByteString());
}
template<class D, class P>
inline TorqueGeneratedSeqTwoByteString<D, P>::TorqueGeneratedSeqTwoByteString(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSeqTwoByteString());
}
template <class D, class P>
String TorqueGeneratedSlicedString<D, P>::parent() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSlicedString::parent(isolate);
}
template <class D, class P>
String TorqueGeneratedSlicedString<D, P>::parent(const Isolate* isolate) const {
  auto value = TaggedField<String, kParentOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedSlicedString<D, P>::set_parent(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kParentOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kParentOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedSlicedString<D, P>::offset() const {
  return TaggedField<Smi, kOffsetOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedSlicedString<D, P>::set_offset(int value) {
  WRITE_FIELD(*this, kOffsetOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedSlicedString<D, P>::TorqueGeneratedSlicedString(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSlicedString());
}
template<class D, class P>
inline TorqueGeneratedSlicedString<D, P>::TorqueGeneratedSlicedString(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSlicedString());
}
template <class D, class P>
String TorqueGeneratedThinString<D, P>::actual() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedThinString::actual(isolate);
}
template <class D, class P>
String TorqueGeneratedThinString<D, P>::actual(const Isolate* isolate) const {
  auto value = TaggedField<String, kActualOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedThinString<D, P>::set_actual(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kActualOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kActualOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedThinString<D, P>::TorqueGeneratedThinString(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsThinString());
}
template<class D, class P>
inline TorqueGeneratedThinString<D, P>::TorqueGeneratedThinString(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsThinString());
}
template <class D, class P>
Object TorqueGeneratedTuple2<D, P>::value1() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedTuple2::value1(isolate);
}
template <class D, class P>
Object TorqueGeneratedTuple2<D, P>::value1(const Isolate* isolate) const {
  auto value = TaggedField<Object, kValue1Offset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedTuple2<D, P>::set_value1(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kValue1Offset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kValue1Offset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedTuple2<D, P>::value2() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedTuple2::value2(isolate);
}
template <class D, class P>
Object TorqueGeneratedTuple2<D, P>::value2(const Isolate* isolate) const {
  auto value = TaggedField<Object, kValue2Offset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedTuple2<D, P>::set_value2(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kValue2Offset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kValue2Offset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedTuple2<D, P>::TorqueGeneratedTuple2(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsTuple2());
}
template<class D, class P>
inline TorqueGeneratedTuple2<D, P>::TorqueGeneratedTuple2(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsTuple2());
}
template <class D, class P>
String TorqueGeneratedSyntheticModule<D, P>::name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSyntheticModule::name(isolate);
}
template <class D, class P>
String TorqueGeneratedSyntheticModule<D, P>::name(const Isolate* isolate) const {
  auto value = TaggedField<String, kNameOffset>::load(isolate, *this);
  DCHECK(value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedSyntheticModule<D, P>::set_name(String value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsString());
  RELAXED_WRITE_FIELD(*this, kNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNameOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedSyntheticModule<D, P>::export_names() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSyntheticModule::export_names(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedSyntheticModule<D, P>::export_names(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kExportNamesOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedSyntheticModule<D, P>::set_export_names(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kExportNamesOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kExportNamesOffset, value, mode);
}

template <class D, class P>
Foreign TorqueGeneratedSyntheticModule<D, P>::evaluation_steps() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedSyntheticModule::evaluation_steps(isolate);
}
template <class D, class P>
Foreign TorqueGeneratedSyntheticModule<D, P>::evaluation_steps(const Isolate* isolate) const {
  auto value = TaggedField<Foreign, kEvaluationStepsOffset>::load(isolate, *this);
  DCHECK(value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedSyntheticModule<D, P>::set_evaluation_steps(Foreign value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kEvaluationStepsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kEvaluationStepsOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedSyntheticModule<D, P>::TorqueGeneratedSyntheticModule(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsSyntheticModule());
}
template<class D, class P>
inline TorqueGeneratedSyntheticModule<D, P>::TorqueGeneratedSyntheticModule(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsSyntheticModule());
}
template <class D, class P>
int TorqueGeneratedCachedTemplateObject<D, P>::slot_id() const {
  return TaggedField<Smi, kSlotIdOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedCachedTemplateObject<D, P>::set_slot_id(int value) {
  WRITE_FIELD(*this, kSlotIdOffset, Smi::FromInt(value));
}

template <class D, class P>
JSArray TorqueGeneratedCachedTemplateObject<D, P>::template_object() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedCachedTemplateObject::template_object(isolate);
}
template <class D, class P>
JSArray TorqueGeneratedCachedTemplateObject<D, P>::template_object(const Isolate* isolate) const {
  auto value = TaggedField<JSArray, kTemplateObjectOffset>::load(isolate, *this);
  DCHECK(value.IsJSArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedCachedTemplateObject<D, P>::set_template_object(JSArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsJSArray());
  RELAXED_WRITE_FIELD(*this, kTemplateObjectOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kTemplateObjectOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedCachedTemplateObject<D, P>::next() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedCachedTemplateObject::next(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedCachedTemplateObject<D, P>::next(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kNextOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsCachedTemplateObject());
  return value;
}
template <class D, class P>
void TorqueGeneratedCachedTemplateObject<D, P>::set_next(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsCachedTemplateObject());
  RELAXED_WRITE_FIELD(*this, kNextOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNextOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedCachedTemplateObject<D, P>::TorqueGeneratedCachedTemplateObject(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsCachedTemplateObject());
}
template<class D, class P>
inline TorqueGeneratedCachedTemplateObject<D, P>::TorqueGeneratedCachedTemplateObject(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsCachedTemplateObject());
}
template <class D, class P>
FixedArray TorqueGeneratedTemplateObjectDescription<D, P>::raw_strings() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedTemplateObjectDescription::raw_strings(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedTemplateObjectDescription<D, P>::raw_strings(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kRawStringsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedTemplateObjectDescription<D, P>::set_raw_strings(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kRawStringsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kRawStringsOffset, value, mode);
}

template <class D, class P>
FixedArray TorqueGeneratedTemplateObjectDescription<D, P>::cooked_strings() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedTemplateObjectDescription::cooked_strings(isolate);
}
template <class D, class P>
FixedArray TorqueGeneratedTemplateObjectDescription<D, P>::cooked_strings(const Isolate* isolate) const {
  auto value = TaggedField<FixedArray, kCookedStringsOffset>::load(isolate, *this);
  DCHECK(value.IsFixedArray());
  return value;
}
template <class D, class P>
void TorqueGeneratedTemplateObjectDescription<D, P>::set_cooked_strings(FixedArray value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsFixedArray());
  RELAXED_WRITE_FIELD(*this, kCookedStringsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCookedStringsOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedTemplateObjectDescription<D, P>::TorqueGeneratedTemplateObjectDescription(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsTemplateObjectDescription());
}
template<class D, class P>
inline TorqueGeneratedTemplateObjectDescription<D, P>::TorqueGeneratedTemplateObjectDescription(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsTemplateObjectDescription());
}
template <class D, class P>
int TorqueGeneratedTemplateInfo<D, P>::tag() const {
  return TaggedField<Smi, kTagOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedTemplateInfo<D, P>::set_tag(int value) {
  WRITE_FIELD(*this, kTagOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedTemplateInfo<D, P>::serial_number() const {
  return TaggedField<Smi, kSerialNumberOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedTemplateInfo<D, P>::set_serial_number(int value) {
  WRITE_FIELD(*this, kSerialNumberOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedTemplateInfo<D, P>::number_of_properties() const {
  return TaggedField<Smi, kNumberOfPropertiesOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedTemplateInfo<D, P>::set_number_of_properties(int value) {
  WRITE_FIELD(*this, kNumberOfPropertiesOffset, Smi::FromInt(value));
}

template <class D, class P>
HeapObject TorqueGeneratedTemplateInfo<D, P>::property_list() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedTemplateInfo::property_list(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedTemplateInfo<D, P>::property_list(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kPropertyListOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsTemplateList());
  return value;
}
template <class D, class P>
void TorqueGeneratedTemplateInfo<D, P>::set_property_list(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsTemplateList());
  RELAXED_WRITE_FIELD(*this, kPropertyListOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPropertyListOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedTemplateInfo<D, P>::property_accessors() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedTemplateInfo::property_accessors(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedTemplateInfo<D, P>::property_accessors(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kPropertyAccessorsOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsTemplateList());
  return value;
}
template <class D, class P>
void TorqueGeneratedTemplateInfo<D, P>::set_property_accessors(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsTemplateList());
  RELAXED_WRITE_FIELD(*this, kPropertyAccessorsOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPropertyAccessorsOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedTemplateInfo<D, P>::TorqueGeneratedTemplateInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsTemplateInfo());
}
template<class D, class P>
inline TorqueGeneratedTemplateInfo<D, P>::TorqueGeneratedTemplateInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsTemplateInfo());
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::prototype_template() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateRareData::prototype_template(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::prototype_template(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kPrototypeTemplateOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsObjectTemplateInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateRareData<D, P>::set_prototype_template(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsObjectTemplateInfo());
  RELAXED_WRITE_FIELD(*this, kPrototypeTemplateOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPrototypeTemplateOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::prototype_provider_template() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateRareData::prototype_provider_template(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::prototype_provider_template(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kPrototypeProviderTemplateOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFunctionTemplateInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateRareData<D, P>::set_prototype_provider_template(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFunctionTemplateInfo());
  RELAXED_WRITE_FIELD(*this, kPrototypeProviderTemplateOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kPrototypeProviderTemplateOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::parent_template() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateRareData::parent_template(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::parent_template(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kParentTemplateOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFunctionTemplateInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateRareData<D, P>::set_parent_template(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFunctionTemplateInfo());
  RELAXED_WRITE_FIELD(*this, kParentTemplateOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kParentTemplateOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::named_property_handler() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateRareData::named_property_handler(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::named_property_handler(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kNamedPropertyHandlerOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsInterceptorInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateRareData<D, P>::set_named_property_handler(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsInterceptorInfo());
  RELAXED_WRITE_FIELD(*this, kNamedPropertyHandlerOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kNamedPropertyHandlerOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::indexed_property_handler() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateRareData::indexed_property_handler(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::indexed_property_handler(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kIndexedPropertyHandlerOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsInterceptorInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateRareData<D, P>::set_indexed_property_handler(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsInterceptorInfo());
  RELAXED_WRITE_FIELD(*this, kIndexedPropertyHandlerOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kIndexedPropertyHandlerOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::instance_template() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateRareData::instance_template(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::instance_template(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kInstanceTemplateOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsObjectTemplateInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateRareData<D, P>::set_instance_template(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsObjectTemplateInfo());
  RELAXED_WRITE_FIELD(*this, kInstanceTemplateOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kInstanceTemplateOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::instance_call_handler() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateRareData::instance_call_handler(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::instance_call_handler(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kInstanceCallHandlerOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsCallHandlerInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateRareData<D, P>::set_instance_call_handler(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsCallHandlerInfo());
  RELAXED_WRITE_FIELD(*this, kInstanceCallHandlerOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kInstanceCallHandlerOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::access_check_info() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateRareData::access_check_info(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateRareData<D, P>::access_check_info(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kAccessCheckInfoOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsAccessCheckInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateRareData<D, P>::set_access_check_info(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsAccessCheckInfo());
  RELAXED_WRITE_FIELD(*this, kAccessCheckInfoOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kAccessCheckInfoOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedFunctionTemplateRareData<D, P>::c_function() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateRareData::c_function(isolate);
}
template <class D, class P>
Object TorqueGeneratedFunctionTemplateRareData<D, P>::c_function(const Isolate* isolate) const {
  auto value = TaggedField<Object, kCFunctionOffset>::load(isolate, *this);
  DCHECK(value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateRareData<D, P>::set_c_function(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kCFunctionOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCFunctionOffset, value, mode);
}

template <class D, class P>
Object TorqueGeneratedFunctionTemplateRareData<D, P>::c_signature() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateRareData::c_signature(isolate);
}
template <class D, class P>
Object TorqueGeneratedFunctionTemplateRareData<D, P>::c_signature(const Isolate* isolate) const {
  auto value = TaggedField<Object, kCSignatureOffset>::load(isolate, *this);
  DCHECK(value.IsSmi() || value.IsForeign());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateRareData<D, P>::set_c_signature(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsSmi() || value.IsForeign());
  RELAXED_WRITE_FIELD(*this, kCSignatureOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCSignatureOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedFunctionTemplateRareData<D, P>::TorqueGeneratedFunctionTemplateRareData(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsFunctionTemplateRareData());
}
template<class D, class P>
inline TorqueGeneratedFunctionTemplateRareData<D, P>::TorqueGeneratedFunctionTemplateRareData(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsFunctionTemplateRareData());
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateInfo<D, P>::call_code() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateInfo::call_code(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateInfo<D, P>::call_code(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kCallCodeOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsCallHandlerInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateInfo<D, P>::set_call_code(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsCallHandlerInfo());
  RELAXED_WRITE_FIELD(*this, kCallCodeOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCallCodeOffset, value, mode);
}

template <class D, class P>
PrimitiveHeapObject TorqueGeneratedFunctionTemplateInfo<D, P>::class_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateInfo::class_name(isolate);
}
template <class D, class P>
PrimitiveHeapObject TorqueGeneratedFunctionTemplateInfo<D, P>::class_name(const Isolate* isolate) const {
  auto value = TaggedField<PrimitiveHeapObject, kClassNameOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsString());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateInfo<D, P>::set_class_name(PrimitiveHeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsString());
  RELAXED_WRITE_FIELD(*this, kClassNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kClassNameOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateInfo<D, P>::signature() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateInfo::signature(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateInfo<D, P>::signature(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kSignatureOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFunctionTemplateInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateInfo<D, P>::set_signature(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFunctionTemplateInfo());
  RELAXED_WRITE_FIELD(*this, kSignatureOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSignatureOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateInfo<D, P>::rare_data() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateInfo::rare_data(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateInfo<D, P>::rare_data(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kRareDataOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFunctionTemplateRareData());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateInfo<D, P>::set_rare_data(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFunctionTemplateRareData());
  RELAXED_WRITE_FIELD(*this, kRareDataOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kRareDataOffset, value, mode);
}

template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateInfo<D, P>::shared_function_info() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateInfo::shared_function_info(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedFunctionTemplateInfo<D, P>::shared_function_info(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kSharedFunctionInfoOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsSharedFunctionInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateInfo<D, P>::set_shared_function_info(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsSharedFunctionInfo());
  RELAXED_WRITE_FIELD(*this, kSharedFunctionInfoOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSharedFunctionInfoOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedFunctionTemplateInfo<D, P>::flag() const {
  return TaggedField<Smi, kFlagOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateInfo<D, P>::set_flag(int value) {
  WRITE_FIELD(*this, kFlagOffset, Smi::FromInt(value));
}

template <class D, class P>
int TorqueGeneratedFunctionTemplateInfo<D, P>::length() const {
  return TaggedField<Smi, kLengthOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateInfo<D, P>::set_length(int value) {
  WRITE_FIELD(*this, kLengthOffset, Smi::FromInt(value));
}

template <class D, class P>
Object TorqueGeneratedFunctionTemplateInfo<D, P>::cached_property_name() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedFunctionTemplateInfo::cached_property_name(isolate);
}
template <class D, class P>
Object TorqueGeneratedFunctionTemplateInfo<D, P>::cached_property_name(const Isolate* isolate) const {
  auto value = TaggedField<Object, kCachedPropertyNameOffset>::load(isolate, *this);
  DCHECK(value.IsHeapObject() || value.IsSmi());
  return value;
}
template <class D, class P>
void TorqueGeneratedFunctionTemplateInfo<D, P>::set_cached_property_name(Object value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsHeapObject() || value.IsSmi());
  RELAXED_WRITE_FIELD(*this, kCachedPropertyNameOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kCachedPropertyNameOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedFunctionTemplateInfo<D, P>::TorqueGeneratedFunctionTemplateInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsFunctionTemplateInfo());
}
template<class D, class P>
inline TorqueGeneratedFunctionTemplateInfo<D, P>::TorqueGeneratedFunctionTemplateInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsFunctionTemplateInfo());
}
template <class D, class P>
HeapObject TorqueGeneratedObjectTemplateInfo<D, P>::constructor() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedObjectTemplateInfo::constructor(isolate);
}
template <class D, class P>
HeapObject TorqueGeneratedObjectTemplateInfo<D, P>::constructor(const Isolate* isolate) const {
  auto value = TaggedField<HeapObject, kConstructorOffset>::load(isolate, *this);
  DCHECK(value.IsOddball() || value.IsFunctionTemplateInfo());
  return value;
}
template <class D, class P>
void TorqueGeneratedObjectTemplateInfo<D, P>::set_constructor(HeapObject value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsOddball() || value.IsFunctionTemplateInfo());
  RELAXED_WRITE_FIELD(*this, kConstructorOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kConstructorOffset, value, mode);
}

template <class D, class P>
int TorqueGeneratedObjectTemplateInfo<D, P>::data() const {
  return TaggedField<Smi, kDataOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedObjectTemplateInfo<D, P>::set_data(int value) {
  WRITE_FIELD(*this, kDataOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedObjectTemplateInfo<D, P>::TorqueGeneratedObjectTemplateInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsObjectTemplateInfo());
}
template<class D, class P>
inline TorqueGeneratedObjectTemplateInfo<D, P>::TorqueGeneratedObjectTemplateInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsObjectTemplateInfo());
}
template <class D, class P>
int TorqueGeneratedWasmExceptionTag<D, P>::index() const {
  return TaggedField<Smi, kIndexOffset>::load(*this).value();
}
template <class D, class P>
void TorqueGeneratedWasmExceptionTag<D, P>::set_index(int value) {
  WRITE_FIELD(*this, kIndexOffset, Smi::FromInt(value));
}

template<class D, class P>
inline TorqueGeneratedWasmExceptionTag<D, P>::TorqueGeneratedWasmExceptionTag(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsWasmExceptionTag());
}
template<class D, class P>
inline TorqueGeneratedWasmExceptionTag<D, P>::TorqueGeneratedWasmExceptionTag(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsWasmExceptionTag());
}
template <class D, class P>
Map TorqueGeneratedWasmTypeInfo<D, P>::parent() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWasmTypeInfo::parent(isolate);
}
template <class D, class P>
Map TorqueGeneratedWasmTypeInfo<D, P>::parent(const Isolate* isolate) const {
  auto value = TaggedField<Map, kParentOffset>::load(isolate, *this);
  DCHECK(value.IsMap());
  return value;
}
template <class D, class P>
void TorqueGeneratedWasmTypeInfo<D, P>::set_parent(Map value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsMap());
  RELAXED_WRITE_FIELD(*this, kParentOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kParentOffset, value, mode);
}

template <class D, class P>
ArrayList TorqueGeneratedWasmTypeInfo<D, P>::subtypes() const {
  const Isolate* isolate = GetIsolateForPtrCompr(*this);
  return TorqueGeneratedWasmTypeInfo::subtypes(isolate);
}
template <class D, class P>
ArrayList TorqueGeneratedWasmTypeInfo<D, P>::subtypes(const Isolate* isolate) const {
  auto value = TaggedField<ArrayList, kSubtypesOffset>::load(isolate, *this);
  DCHECK(value.IsArrayList());
  return value;
}
template <class D, class P>
void TorqueGeneratedWasmTypeInfo<D, P>::set_subtypes(ArrayList value, WriteBarrierMode mode) {
  SLOW_DCHECK(value.IsArrayList());
  RELAXED_WRITE_FIELD(*this, kSubtypesOffset, value);
  CONDITIONAL_WRITE_BARRIER(*this, kSubtypesOffset, value, mode);
}

template<class D, class P>
inline TorqueGeneratedWasmTypeInfo<D, P>::TorqueGeneratedWasmTypeInfo(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsWasmTypeInfo());
}
template<class D, class P>
inline TorqueGeneratedWasmTypeInfo<D, P>::TorqueGeneratedWasmTypeInfo(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsWasmTypeInfo());
}
template<class D, class P>
inline TorqueGeneratedWasmStruct<D, P>::TorqueGeneratedWasmStruct(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsWasmStruct());
}
template<class D, class P>
inline TorqueGeneratedWasmStruct<D, P>::TorqueGeneratedWasmStruct(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsWasmStruct());
}
template <class D, class P>
uint32_t TorqueGeneratedWasmArray<D, P>::length() const {
  return this->template ReadField<uint32_t>(kLengthOffset);
}
template <class D, class P>
void TorqueGeneratedWasmArray<D, P>::set_length(uint32_t value) {
  this->template WriteField<uint32_t>(kLengthOffset, value);
}

template<class D, class P>
inline TorqueGeneratedWasmArray<D, P>::TorqueGeneratedWasmArray(Address ptr)
  : P(ptr) {
  SLOW_DCHECK(this->IsWasmArray());
}
template<class D, class P>
inline TorqueGeneratedWasmArray<D, P>::TorqueGeneratedWasmArray(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi)
  : P(ptr, allow_smi) {
  SLOW_DCHECK((allow_smi == HeapObject::AllowInlineSmiStorage::kAllowBeingASmi && this->IsSmi()) || this->IsWasmArray());
}
}  // namespace internal
}  // namespace v8

#include "src/objects/object-macros-undef.h"
#endif  // V8_GEN_TORQUE_GENERATED_CLASS_DEFINITIONS_TQ_INL_H_
