class FixedArray::BodyDescriptor final : public SuffixRangeBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return FixedArray::cast(raw_object).AllocatedSize();
  }

};
class WeakFixedArray::BodyDescriptor final : public SuffixRangeWeakBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return WeakFixedArray::cast(raw_object).AllocatedSize();
  }

};
class SloppyArgumentsElements::BodyDescriptor final : public SuffixRangeBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return SloppyArgumentsElements::cast(raw_object).AllocatedSize();
  }

};
class WeakArrayList::BodyDescriptor final : public SuffixRangeWeakBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return WeakArrayList::cast(raw_object).AllocatedSize();
  }

};
class OnHeapBasicBlockProfilerData::BodyDescriptor final : public SuffixRangeBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 28;
  }

};
class ConsString::BodyDescriptor final : public SuffixRangeBodyDescriptor<12> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 20;
  }

};
class SeqOneByteString::BodyDescriptor final : public DataOnlyBodyDescriptor {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return SeqOneByteString::cast(raw_object).AllocatedSize();
  }

};
class SeqTwoByteString::BodyDescriptor final : public DataOnlyBodyDescriptor {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return SeqTwoByteString::cast(raw_object).AllocatedSize();
  }

};
class SlicedString::BodyDescriptor final : public SuffixRangeBodyDescriptor<12> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 20;
  }

};
class ThinString::BodyDescriptor final : public SuffixRangeBodyDescriptor<12> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 16;
  }

};
class InternalClass::BodyDescriptor final : public SuffixRangeBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 12;
  }

};
class SmiPair::BodyDescriptor final : public SuffixRangeBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 12;
  }

};
class SmiBox::BodyDescriptor final : public SuffixRangeBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 12;
  }

};
class ExportedSubClassBase::BodyDescriptor final : public SuffixRangeBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 12;
  }

};
class ExportedSubClass::BodyDescriptor final : public BodyDescriptorBase {
 public:
  static bool IsValidSlot(Map map, HeapObject obj, int offset) {
      bool valid_slots[] = {1,1,1,0,0,1,};
      return valid_slots[static_cast<unsigned int>(offset)/kTaggedSize];
  }

  template <typename ObjectVisitor>
  static inline void IterateBody(Map map, HeapObject obj, int object_size, ObjectVisitor* v) {
    IteratePointers(obj, 4, 12, v);
    IteratePointer(obj, 20, v);
  }

  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 24;
  }

};
class AbstractInternalClassSubclass1::BodyDescriptor final : public DataOnlyBodyDescriptor {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 4;
  }

};
class AbstractInternalClassSubclass2::BodyDescriptor final : public DataOnlyBodyDescriptor {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 4;
  }

};
class InternalClassWithSmiElements::BodyDescriptor final : public SuffixRangeBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return InternalClassWithSmiElements::cast(raw_object).AllocatedSize();
  }

};
class InternalClassWithStructElements::BodyDescriptor final : public SuffixRangeBodyDescriptor<12> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return InternalClassWithStructElements::cast(raw_object).AllocatedSize();
  }

};
class ExportedSubClass2::BodyDescriptor final : public BodyDescriptorBase {
 public:
  static bool IsValidSlot(Map map, HeapObject obj, int offset) {
      bool valid_slots[] = {1,1,1,0,0,1,};
      return valid_slots[static_cast<unsigned int>(offset)/kTaggedSize];
  }

  template <typename ObjectVisitor>
  static inline void IterateBody(Map map, HeapObject obj, int object_size, ObjectVisitor* v) {
    IteratePointers(obj, 4, 12, v);
    IteratePointer(obj, 20, v);
  }

  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 24;
  }

};
class SortState::BodyDescriptor final : public SuffixRangeBodyDescriptor<4> {
 public:
  static inline int SizeOf(Map map, HeapObject raw_object) {
    return 68;
  }

};
