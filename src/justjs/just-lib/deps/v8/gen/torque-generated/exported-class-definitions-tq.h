#ifndef V8_GEN_TORQUE_GENERATED_EXPORTED_CLASS_DEFINITIONS_TQ_H_
#define V8_GEN_TORQUE_GENERATED_EXPORTED_CLASS_DEFINITIONS_TQ_H_

#include "src/objects/fixed-array.h"
#include "torque-generated/class-definitions-tq.h"

// Has to be the last include (doesn't have include guards):
#include "src/objects/object-macros.h"
namespace v8 {
namespace internal {
template <class D, class P>
class TorqueGeneratedSloppyArgumentsElements : public P {
  static_assert(std::is_same<SloppyArgumentsElements, D>::value,
    "Use this class as direct base for SloppyArgumentsElements.");
  static_assert(std::is_same<FixedArrayBase, P>::value,
    "Pass in FixedArrayBase as second template parameter for TorqueGeneratedSloppyArgumentsElements.");
 public: 
  using Super = P;

  inline Context context() const;
  inline Context context(const Isolate* isolates) const;
  inline void set_context(Context value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline FixedArray arguments() const;
  inline FixedArray arguments(const Isolate* isolates) const;
  inline void set_arguments(FixedArray value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  // Torque type: (Smi | TheHole)
  inline Object mapped_entries(int i) const;
  inline Object mapped_entries(const Isolate* isolates, int i) const;
  inline void set_mapped_entries(int i, Object value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(SloppyArgumentsElements)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void SloppyArgumentsElementsVerify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kStartOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kContextOffset = P::kHeaderSize;
  static constexpr int kContextOffsetEnd = kContextOffset + kTaggedSize - 1;
  static constexpr int kArgumentsOffset = kContextOffsetEnd + 1;
  static constexpr int kArgumentsOffsetEnd = kArgumentsOffset + kTaggedSize - 1;
  static constexpr int kHeaderSize = kArgumentsOffsetEnd + 1;
  static constexpr int kMappedEntriesOffset = kArgumentsOffsetEnd + 1;
  static constexpr int kMappedEntriesOffsetEnd = kMappedEntriesOffset + 0 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kMappedEntriesOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kMappedEntriesOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kMappedEntriesOffsetEnd + 1;

  V8_INLINE static constexpr int32_t SizeFor(int length) {
    int32_t size = kHeaderSize;
    size += length * 4;
    return size;
  }

  V8_INLINE int32_t AllocatedSize() {
    return SizeFor(this->length());
  }

  friend class Factory;

 public:
  template <class DAlias = D>
  constexpr TorqueGeneratedSloppyArgumentsElements() : P() {
    static_assert(std::is_base_of<TorqueGeneratedSloppyArgumentsElements, 
      DAlias>::value,
      "class TorqueGeneratedSloppyArgumentsElements should be used as direct base for SloppyArgumentsElements.");
  }
protected:
  inline explicit TorqueGeneratedSloppyArgumentsElements(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedSloppyArgumentsElements(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class SloppyArgumentsElements : public TorqueGeneratedSloppyArgumentsElements<SloppyArgumentsElements, FixedArrayBase> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(SloppyArgumentsElements)
};

template <class D, class P>
class TorqueGeneratedOnHeapBasicBlockProfilerData : public P {
  static_assert(std::is_same<OnHeapBasicBlockProfilerData, D>::value,
    "Use this class as direct base for OnHeapBasicBlockProfilerData.");
  static_assert(std::is_same<HeapObject, P>::value,
    "Pass in HeapObject as second template parameter for TorqueGeneratedOnHeapBasicBlockProfilerData.");
 public: 
  using Super = P;

  inline ByteArray block_ids() const;
  inline ByteArray block_ids(const Isolate* isolates) const;
  inline void set_block_ids(ByteArray value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline ByteArray counts() const;
  inline ByteArray counts(const Isolate* isolates) const;
  inline void set_counts(ByteArray value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline String name() const;
  inline String name(const Isolate* isolates) const;
  inline void set_name(String value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline String schedule() const;
  inline String schedule(const Isolate* isolates) const;
  inline void set_schedule(String value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline String code() const;
  inline String code(const Isolate* isolates) const;
  inline void set_code(String value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline int hash() const;
  inline void set_hash(int value);

  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(OnHeapBasicBlockProfilerData)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void OnHeapBasicBlockProfilerDataVerify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kStartOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kBlockIdsOffset = P::kHeaderSize;
  static constexpr int kBlockIdsOffsetEnd = kBlockIdsOffset + kTaggedSize - 1;
  static constexpr int kCountsOffset = kBlockIdsOffsetEnd + 1;
  static constexpr int kCountsOffsetEnd = kCountsOffset + kTaggedSize - 1;
  static constexpr int kNameOffset = kCountsOffsetEnd + 1;
  static constexpr int kNameOffsetEnd = kNameOffset + kTaggedSize - 1;
  static constexpr int kScheduleOffset = kNameOffsetEnd + 1;
  static constexpr int kScheduleOffsetEnd = kScheduleOffset + kTaggedSize - 1;
  static constexpr int kCodeOffset = kScheduleOffsetEnd + 1;
  static constexpr int kCodeOffsetEnd = kCodeOffset + kTaggedSize - 1;
  static constexpr int kHashOffset = kCodeOffsetEnd + 1;
  static constexpr int kHashOffsetEnd = kHashOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kHashOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kHashOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kHashOffsetEnd + 1;
  static constexpr int kHeaderSize = kHashOffsetEnd + 1;
  static constexpr int kSize = kHashOffsetEnd + 1;

  V8_INLINE static constexpr int32_t SizeFor() {
    DCHECK(kHeaderSize == kSize && kHeaderSize == 28);
    int32_t size = kHeaderSize;
    return size;
  }

  V8_INLINE int32_t AllocatedSize() {
    return SizeFor();
  }

  friend class Factory;

 public:
  template <class DAlias = D>
  constexpr TorqueGeneratedOnHeapBasicBlockProfilerData() : P() {
    static_assert(std::is_base_of<TorqueGeneratedOnHeapBasicBlockProfilerData, 
      DAlias>::value,
      "class TorqueGeneratedOnHeapBasicBlockProfilerData should be used as direct base for OnHeapBasicBlockProfilerData.");
  }
protected:
  inline explicit TorqueGeneratedOnHeapBasicBlockProfilerData(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedOnHeapBasicBlockProfilerData(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class OnHeapBasicBlockProfilerData : public TorqueGeneratedOnHeapBasicBlockProfilerData<OnHeapBasicBlockProfilerData, HeapObject> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(OnHeapBasicBlockProfilerData)
};

template <class D, class P>
class TorqueGeneratedExportedSubClassBase : public P {
  static_assert(std::is_same<ExportedSubClassBase, D>::value,
    "Use this class as direct base for ExportedSubClassBase.");
  static_assert(std::is_same<HeapObject, P>::value,
    "Pass in HeapObject as second template parameter for TorqueGeneratedExportedSubClassBase.");
 public: 
  using Super = P;

  inline HeapObject a() const;
  inline HeapObject a(const Isolate* isolates) const;
  inline void set_a(HeapObject value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline HeapObject b() const;
  inline HeapObject b(const Isolate* isolates) const;
  inline void set_b(HeapObject value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(ExportedSubClassBase)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void ExportedSubClassBaseVerify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kStartOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kAOffset = P::kHeaderSize;
  static constexpr int kAOffsetEnd = kAOffset + kTaggedSize - 1;
  static constexpr int kBOffset = kAOffsetEnd + 1;
  static constexpr int kBOffsetEnd = kBOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kBOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kBOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kBOffsetEnd + 1;
  static constexpr int kHeaderSize = kBOffsetEnd + 1;
  static constexpr int kSize = kBOffsetEnd + 1;

  V8_INLINE static constexpr int32_t SizeFor() {
    DCHECK(kHeaderSize == kSize && kHeaderSize == 12);
    int32_t size = kHeaderSize;
    return size;
  }

  V8_INLINE int32_t AllocatedSize() {
    return SizeFor();
  }

  friend class Factory;

 public:
  template <class DAlias = D>
  constexpr TorqueGeneratedExportedSubClassBase() : P() {
    static_assert(std::is_base_of<TorqueGeneratedExportedSubClassBase, 
      DAlias>::value,
      "class TorqueGeneratedExportedSubClassBase should be used as direct base for ExportedSubClassBase.");
  }
protected:
  inline explicit TorqueGeneratedExportedSubClassBase(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedExportedSubClassBase(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class ExportedSubClassBase : public TorqueGeneratedExportedSubClassBase<ExportedSubClassBase, HeapObject> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(ExportedSubClassBase)
};

template <class D, class P>
class TorqueGeneratedExportedSubClass : public P {
  static_assert(std::is_same<ExportedSubClass, D>::value,
    "Use this class as direct base for ExportedSubClass.");
  static_assert(std::is_same<ExportedSubClassBase, P>::value,
    "Pass in ExportedSubClassBase as second template parameter for TorqueGeneratedExportedSubClass.");
 public: 
  using Super = P;

  inline int32_t c_field() const;
  inline void set_c_field(int32_t value);

  inline int32_t d_field() const;
  inline void set_d_field(int32_t value);

  inline int e_field() const;
  inline void set_e_field(int value);

  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(ExportedSubClass)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void ExportedSubClassVerify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kCFieldOffset = P::kHeaderSize;
  static constexpr int kCFieldOffsetEnd = kCFieldOffset + kInt32Size - 1;
  static constexpr int kDFieldOffset = kCFieldOffsetEnd + 1;
  static constexpr int kDFieldOffsetEnd = kDFieldOffset + kInt32Size - 1;
  static constexpr int kStartOfStrongFieldsOffset = kDFieldOffsetEnd + 1;
  static constexpr int kEFieldOffset = kDFieldOffsetEnd + 1;
  static constexpr int kEFieldOffsetEnd = kEFieldOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kEFieldOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kEFieldOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kEFieldOffsetEnd + 1;
  static constexpr int kHeaderSize = kEFieldOffsetEnd + 1;
  static constexpr int kSize = kEFieldOffsetEnd + 1;

  V8_INLINE static constexpr int32_t SizeFor() {
    DCHECK(kHeaderSize == kSize && kHeaderSize == 24);
    int32_t size = kHeaderSize;
    return size;
  }

  V8_INLINE int32_t AllocatedSize() {
    return SizeFor();
  }

  friend class Factory;

 public:
  template <class DAlias = D>
  constexpr TorqueGeneratedExportedSubClass() : P() {
    static_assert(std::is_base_of<TorqueGeneratedExportedSubClass, 
      DAlias>::value,
      "class TorqueGeneratedExportedSubClass should be used as direct base for ExportedSubClass.");
  }
protected:
  inline explicit TorqueGeneratedExportedSubClass(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedExportedSubClass(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class ExportedSubClass : public TorqueGeneratedExportedSubClass<ExportedSubClass, ExportedSubClassBase> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(ExportedSubClass)
};

template <class D, class P>
class TorqueGeneratedExportedSubClass2 : public P {
  static_assert(std::is_same<ExportedSubClass2, D>::value,
    "Use this class as direct base for ExportedSubClass2.");
  static_assert(std::is_same<ExportedSubClassBase, P>::value,
    "Pass in ExportedSubClassBase as second template parameter for TorqueGeneratedExportedSubClass2.");
 public: 
  using Super = P;

  inline int32_t x_field() const;
  inline void set_x_field(int32_t value);

  inline int32_t y_field() const;
  inline void set_y_field(int32_t value);

  inline int z_field() const;
  inline void set_z_field(int value);

  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(ExportedSubClass2)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void ExportedSubClass2Verify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kXFieldOffset = P::kHeaderSize;
  static constexpr int kXFieldOffsetEnd = kXFieldOffset + kInt32Size - 1;
  static constexpr int kYFieldOffset = kXFieldOffsetEnd + 1;
  static constexpr int kYFieldOffsetEnd = kYFieldOffset + kInt32Size - 1;
  static constexpr int kStartOfStrongFieldsOffset = kYFieldOffsetEnd + 1;
  static constexpr int kZFieldOffset = kYFieldOffsetEnd + 1;
  static constexpr int kZFieldOffsetEnd = kZFieldOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kZFieldOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kZFieldOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kZFieldOffsetEnd + 1;
  static constexpr int kHeaderSize = kZFieldOffsetEnd + 1;
  static constexpr int kSize = kZFieldOffsetEnd + 1;

  V8_INLINE static constexpr int32_t SizeFor() {
    DCHECK(kHeaderSize == kSize && kHeaderSize == 24);
    int32_t size = kHeaderSize;
    return size;
  }

  V8_INLINE int32_t AllocatedSize() {
    return SizeFor();
  }

  friend class Factory;

 public:
  template <class DAlias = D>
  constexpr TorqueGeneratedExportedSubClass2() : P() {
    static_assert(std::is_base_of<TorqueGeneratedExportedSubClass2, 
      DAlias>::value,
      "class TorqueGeneratedExportedSubClass2 should be used as direct base for ExportedSubClass2.");
  }
protected:
  inline explicit TorqueGeneratedExportedSubClass2(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedExportedSubClass2(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class ExportedSubClass2 : public TorqueGeneratedExportedSubClass2<ExportedSubClass2, ExportedSubClassBase> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(ExportedSubClass2)
};

}  // namespace internal
}  // namespace v8

#include "src/objects/object-macros-undef.h"
#endif  // V8_GEN_TORQUE_GENERATED_EXPORTED_CLASS_DEFINITIONS_TQ_H_
