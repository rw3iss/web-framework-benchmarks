#ifndef V8_GEN_TORQUE_GENERATED_INTERNAL_CLASS_DEFINITIONS_TQ_H_
#define V8_GEN_TORQUE_GENERATED_INTERNAL_CLASS_DEFINITIONS_TQ_H_

#include "torque-generated/class-definitions-tq.h"
#include "src/objects/fixed-array.h"
#include "src/objects/objects.h"
#include "src/objects/heap-object.h"
#include "src/objects/smi.h"
#include "torque-generated/field-offsets-tq.h"
#include <type_traits>


// Has to be the last include (doesn't have include guards):
#include "src/objects/object-macros.h"
namespace v8 {
namespace internal {
class HeapObject;
class Context;
class JSReceiver;
class PrimitiveHeapObject;
class Oddball;
class Name;
class Symbol;
class String;
class BigInt;
class HeapNumber;
class FixedArrayBase;
class FixedArray;
class FixedArray;
class OrderedHashMap;
class OrderedHashSet;
class OrderedNameDictionary;
class NameDictionary;
class GlobalDictionary;
class SimpleNumberDictionary;
class EphemeronHashTable;
class NumberDictionary;
class Code;
class ObjectBoilerplateDescription;
class ClosureFeedbackCellArray;
class ScriptContextTable;
class ByteArray;
class WeakFixedArray;
class TransitionArray;
class Foreign;
class JSObject;
class JSProxy;
class JSFunctionOrBoundFunction;
class JSBoundFunction;
class JSFunction;
class HeapObject;
class JSObject;
class JSCustomElementsObject;
class JSSpecialObject;
class JSSpecialObject;
class JSObject;
class JSObject;
class WeakCell;
class Map;
class BigInt;
class Context;
class JSPromise;
class Struct;
class PromiseCapability;
class JSArrayBufferView;
class JSTypedArray;
class DataHandler;
class LoadHandler;
class StoreHandler;
class AllocationSite;
class AllocationMemento;
class CallHandlerInfo;
class InterceptorInfo;
class AccessCheckInfo;
class AccessorInfo;
class JSArgumentsObject;
class JSArgumentsObject;
class JSArgumentsObject;
class SloppyArgumentsElements;
class AliasedArgumentsEntry;
class Cell;
class BytecodeArray;
class CodeDataContainer;
class Context;
class Context;
class Context;
class Context;
class Context;
class Context;
class Context;
class Context;
class NativeContext;
class ScopeInfo;
class FixedDoubleArray;
class RegExpMatchInfo;
class BreakPoint;
class BreakPointInfo;
class DebugInfo;
class CoverageInfo;
class WasmValue;
class EnumCache;
class ClassPositions;
class AccessorPair;
class DescriptorArray;
class EmbedderDataArray;
class FeedbackCell;
class FeedbackVector;
class FeedbackMetadata;
class ArrayList;
class TemplateList;
class WeakArrayList;
class FreeSpace;
class JSArrayBuffer;
class JSDataView;
class JSArrayIterator;
class JSArray;
class JSCollectionIterator;
class JSCollection;
class JSSet;
class JSMap;
class JSWeakCollection;
class JSWeakSet;
class JSWeakMap;
class JSMapIterator;
class JSMapIterator;
class JSMapIterator;
class JSMapIterator;
class JSSetIterator;
class JSSetIterator;
class JSSetIterator;
class JSGeneratorObject;
class JSAsyncFunctionObject;
class JSAsyncGeneratorObject;
class AsyncGeneratorRequest;
class JSGlobalProxy;
class JSGlobalObject;
class JSPrimitiveWrapper;
class JSMessageObject;
class JSDate;
class JSAsyncFromSyncIterator;
class JSStringIterator;
class JSObject;
class JSRegExpStringIterator;
class JSRegExp;
class JSArray;
class JSArray;
class JSFinalizationRegistry;
class JSWeakRef;
class ArrayBoilerplateDescription;
class Microtask;
class CallbackTask;
class CallableTask;
class Module;
class JSModuleNamespace;
class HeapObject;
class SmallOrderedHashSet;
class SmallOrderedHashMap;
class SmallOrderedNameDictionary;
class PromiseReaction;
class PromiseReactionJobTask;
class PromiseFulfillReactionJobTask;
class PromiseRejectReactionJobTask;
class PromiseResolveThenableJobTask;
class PropertyArray;
class PropertyCell;
class PropertyDescriptorObject;
class PrototypeInfo;
class Script;
class PreparseData;
class InterpreterData;
class SharedFunctionInfo;
class UncompiledData;
class UncompiledDataWithoutPreparseData;
class UncompiledDataWithPreparseData;
class OnHeapBasicBlockProfilerData;
class SourceTextModule;
class SourceTextModuleInfoEntry;
class StackFrameInfo;
class StackTraceFrame;
class ConsString;
class ExternalString;
class ExternalOneByteString;
class ExternalTwoByteString;
class InternalizedString;
class SeqString;
class SeqOneByteString;
class SeqTwoByteString;
class SlicedString;
class ThinString;
class Tuple2;
class SyntheticModule;
class CachedTemplateObject;
class TemplateObjectDescription;
class TemplateInfo;
class FunctionTemplateRareData;
class FunctionTemplateInfo;
class ObjectTemplateInfo;
class WasmInstanceObject;
class WasmExportedFunctionData;
class WasmJSFunctionData;
class WasmCapiFunctionData;
class WasmIndirectFunctionTable;
class WasmExceptionTag;
class WasmModuleObject;
class WasmTableObject;
class WasmMemoryObject;
class WasmGlobalObject;
class WasmExceptionObject;
class AsmWasmData;
class WasmTypeInfo;
class WasmStruct;
class WasmArray;
class InternalClass;
class SmiPair;
class SmiBox;
class ExportedSubClassBase;
class ExportedSubClass;
class AbstractInternalClass;
class AbstractInternalClassSubclass1;
class AbstractInternalClassSubclass2;
class InternalClassWithSmiElements;
class InternalClassWithStructElements;
class ExportedSubClass2;
class SortState;
using BuiltinPtr = Smi;

template <class D, class P>
class TorqueGeneratedInternalClass : public P {
  static_assert(std::is_same<InternalClass, D>::value,
    "Use this class as direct base for InternalClass.");
  static_assert(std::is_same<HeapObject, P>::value,
    "Pass in HeapObject as second template parameter for TorqueGeneratedInternalClass.");
 public: 
  using Super = P;

 protected: // not extern or @export
  inline int a() const;
  inline void set_a(int value);

  // Torque type: Number
  inline Object b() const;
  inline Object b(const Isolate* isolates) const;
  inline void set_b(Object value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

 public:
  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(InternalClass)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void InternalClassVerify(Isolate* isolate);
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
  constexpr TorqueGeneratedInternalClass() : P() {
    static_assert(std::is_base_of<TorqueGeneratedInternalClass, 
      DAlias>::value,
      "class TorqueGeneratedInternalClass should be used as direct base for InternalClass.");
  }
protected:
  inline explicit TorqueGeneratedInternalClass(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedInternalClass(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class InternalClass : public TorqueGeneratedInternalClass<InternalClass, HeapObject> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(InternalClass)
};

template <class D, class P>
class TorqueGeneratedSmiPair : public P {
  static_assert(std::is_same<SmiPair, D>::value,
    "Use this class as direct base for SmiPair.");
  static_assert(std::is_same<HeapObject, P>::value,
    "Pass in HeapObject as second template parameter for TorqueGeneratedSmiPair.");
 public: 
  using Super = P;

 protected: // not extern or @export
  inline int a() const;
  inline void set_a(int value);

  inline int b() const;
  inline void set_b(int value);

 public:
  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(SmiPair)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void SmiPairVerify(Isolate* isolate);
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
  constexpr TorqueGeneratedSmiPair() : P() {
    static_assert(std::is_base_of<TorqueGeneratedSmiPair, 
      DAlias>::value,
      "class TorqueGeneratedSmiPair should be used as direct base for SmiPair.");
  }
protected:
  inline explicit TorqueGeneratedSmiPair(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedSmiPair(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class SmiPair : public TorqueGeneratedSmiPair<SmiPair, HeapObject> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(SmiPair)
};

template <class D, class P>
class TorqueGeneratedSmiBox : public P {
  static_assert(std::is_same<SmiBox, D>::value,
    "Use this class as direct base for SmiBox.");
  static_assert(std::is_same<HeapObject, P>::value,
    "Pass in HeapObject as second template parameter for TorqueGeneratedSmiBox.");
 public: 
  using Super = P;

 protected: // not extern or @export
  inline int value() const;
  inline void set_value(int value);

  inline int unrelated() const;
  inline void set_unrelated(int value);

 public:
  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(SmiBox)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void SmiBoxVerify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kStartOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kValueOffset = P::kHeaderSize;
  static constexpr int kValueOffsetEnd = kValueOffset + kTaggedSize - 1;
  static constexpr int kUnrelatedOffset = kValueOffsetEnd + 1;
  static constexpr int kUnrelatedOffsetEnd = kUnrelatedOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kUnrelatedOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kUnrelatedOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kUnrelatedOffsetEnd + 1;
  static constexpr int kHeaderSize = kUnrelatedOffsetEnd + 1;
  static constexpr int kSize = kUnrelatedOffsetEnd + 1;

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
  constexpr TorqueGeneratedSmiBox() : P() {
    static_assert(std::is_base_of<TorqueGeneratedSmiBox, 
      DAlias>::value,
      "class TorqueGeneratedSmiBox should be used as direct base for SmiBox.");
  }
protected:
  inline explicit TorqueGeneratedSmiBox(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedSmiBox(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class SmiBox : public TorqueGeneratedSmiBox<SmiBox, HeapObject> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(SmiBox)
};

template <class D, class P>
class TorqueGeneratedAbstractInternalClass : public P {
  static_assert(std::is_same<AbstractInternalClass, D>::value,
    "Use this class as direct base for AbstractInternalClass.");
  static_assert(std::is_same<HeapObject, P>::value,
    "Pass in HeapObject as second template parameter for TorqueGeneratedAbstractInternalClass.");
 public: 
  using Super = P;

 protected: // not extern or @export
 public:
  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(AbstractInternalClass)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void AbstractInternalClassVerify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kStartOfWeakFieldsOffset = P::kHeaderSize;
  static constexpr int kEndOfWeakFieldsOffset = P::kHeaderSize;
  static constexpr int kStartOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kEndOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kHeaderSize = P::kHeaderSize;

  friend class Factory;

 public:
  template <class DAlias = D>
  constexpr TorqueGeneratedAbstractInternalClass() : P() {
    static_assert(std::is_base_of<TorqueGeneratedAbstractInternalClass, 
      DAlias>::value,
      "class TorqueGeneratedAbstractInternalClass should be used as direct base for AbstractInternalClass.");
  }
protected:
  inline explicit TorqueGeneratedAbstractInternalClass(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedAbstractInternalClass(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class AbstractInternalClass : public TorqueGeneratedAbstractInternalClass<AbstractInternalClass, HeapObject> {
 public:
  TQ_OBJECT_CONSTRUCTORS(AbstractInternalClass)
};

template <class D, class P>
class TorqueGeneratedAbstractInternalClassSubclass1 : public P {
  static_assert(std::is_same<AbstractInternalClassSubclass1, D>::value,
    "Use this class as direct base for AbstractInternalClassSubclass1.");
  static_assert(std::is_same<AbstractInternalClass, P>::value,
    "Pass in AbstractInternalClass as second template parameter for TorqueGeneratedAbstractInternalClassSubclass1.");
 public: 
  using Super = P;

 protected: // not extern or @export
 public:
  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(AbstractInternalClassSubclass1)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void AbstractInternalClassSubclass1Verify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kStartOfWeakFieldsOffset = P::kHeaderSize;
  static constexpr int kEndOfWeakFieldsOffset = P::kHeaderSize;
  static constexpr int kStartOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kEndOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kHeaderSize = P::kHeaderSize;
  static constexpr int kSize = P::kHeaderSize;

  V8_INLINE static constexpr int32_t SizeFor() {
    DCHECK(kHeaderSize == kSize && kHeaderSize == 4);
    int32_t size = kHeaderSize;
    return size;
  }

  V8_INLINE int32_t AllocatedSize() {
    return SizeFor();
  }

  friend class Factory;

 public:
  template <class DAlias = D>
  constexpr TorqueGeneratedAbstractInternalClassSubclass1() : P() {
    static_assert(std::is_base_of<TorqueGeneratedAbstractInternalClassSubclass1, 
      DAlias>::value,
      "class TorqueGeneratedAbstractInternalClassSubclass1 should be used as direct base for AbstractInternalClassSubclass1.");
  }
protected:
  inline explicit TorqueGeneratedAbstractInternalClassSubclass1(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedAbstractInternalClassSubclass1(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class AbstractInternalClassSubclass1 : public TorqueGeneratedAbstractInternalClassSubclass1<AbstractInternalClassSubclass1, AbstractInternalClass> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(AbstractInternalClassSubclass1)
};

template <class D, class P>
class TorqueGeneratedAbstractInternalClassSubclass2 : public P {
  static_assert(std::is_same<AbstractInternalClassSubclass2, D>::value,
    "Use this class as direct base for AbstractInternalClassSubclass2.");
  static_assert(std::is_same<AbstractInternalClass, P>::value,
    "Pass in AbstractInternalClass as second template parameter for TorqueGeneratedAbstractInternalClassSubclass2.");
 public: 
  using Super = P;

 protected: // not extern or @export
 public:
  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(AbstractInternalClassSubclass2)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void AbstractInternalClassSubclass2Verify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kStartOfWeakFieldsOffset = P::kHeaderSize;
  static constexpr int kEndOfWeakFieldsOffset = P::kHeaderSize;
  static constexpr int kStartOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kEndOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kHeaderSize = P::kHeaderSize;
  static constexpr int kSize = P::kHeaderSize;

  V8_INLINE static constexpr int32_t SizeFor() {
    DCHECK(kHeaderSize == kSize && kHeaderSize == 4);
    int32_t size = kHeaderSize;
    return size;
  }

  V8_INLINE int32_t AllocatedSize() {
    return SizeFor();
  }

  friend class Factory;

 public:
  template <class DAlias = D>
  constexpr TorqueGeneratedAbstractInternalClassSubclass2() : P() {
    static_assert(std::is_base_of<TorqueGeneratedAbstractInternalClassSubclass2, 
      DAlias>::value,
      "class TorqueGeneratedAbstractInternalClassSubclass2 should be used as direct base for AbstractInternalClassSubclass2.");
  }
protected:
  inline explicit TorqueGeneratedAbstractInternalClassSubclass2(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedAbstractInternalClassSubclass2(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class AbstractInternalClassSubclass2 : public TorqueGeneratedAbstractInternalClassSubclass2<AbstractInternalClassSubclass2, AbstractInternalClass> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(AbstractInternalClassSubclass2)
};

template <class D, class P>
class TorqueGeneratedInternalClassWithSmiElements : public P {
  static_assert(std::is_same<InternalClassWithSmiElements, D>::value,
    "Use this class as direct base for InternalClassWithSmiElements.");
  static_assert(std::is_same<FixedArrayBase, P>::value,
    "Pass in FixedArrayBase as second template parameter for TorqueGeneratedInternalClassWithSmiElements.");
 public: 
  using Super = P;

 protected: // not extern or @export
  inline int data() const;
  inline void set_data(int value);

  inline Oddball object() const;
  inline Oddball object(const Isolate* isolates) const;
  inline void set_object(Oddball value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline int entries(int i) const;
  inline void set_entries(int i, int value);

  inline int entries() const;
  inline void set_entries(int value);

 public:
  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(InternalClassWithSmiElements)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void InternalClassWithSmiElementsVerify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kStartOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kDataOffset = P::kHeaderSize;
  static constexpr int kDataOffsetEnd = kDataOffset + kTaggedSize - 1;
  static constexpr int kObjectOffset = kDataOffsetEnd + 1;
  static constexpr int kObjectOffsetEnd = kObjectOffset + kTaggedSize - 1;
  static constexpr int kHeaderSize = kObjectOffsetEnd + 1;
  static constexpr int kEntriesOffset = kObjectOffsetEnd + 1;
  static constexpr int kEntriesOffsetEnd = kEntriesOffset + 0 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kEntriesOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kEntriesOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kEntriesOffsetEnd + 1;

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
  constexpr TorqueGeneratedInternalClassWithSmiElements() : P() {
    static_assert(std::is_base_of<TorqueGeneratedInternalClassWithSmiElements, 
      DAlias>::value,
      "class TorqueGeneratedInternalClassWithSmiElements should be used as direct base for InternalClassWithSmiElements.");
  }
protected:
  inline explicit TorqueGeneratedInternalClassWithSmiElements(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedInternalClassWithSmiElements(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class InternalClassWithSmiElements : public TorqueGeneratedInternalClassWithSmiElements<InternalClassWithSmiElements, FixedArrayBase> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(InternalClassWithSmiElements)
};

template <class D, class P>
class TorqueGeneratedInternalClassWithStructElements : public P {
  static_assert(std::is_same<InternalClassWithStructElements, D>::value,
    "Use this class as direct base for InternalClassWithStructElements.");
  static_assert(std::is_same<HeapObject, P>::value,
    "Pass in HeapObject as second template parameter for TorqueGeneratedInternalClassWithStructElements.");
 public: 
  using Super = P;

 protected: // not extern or @export
  inline int32_t dummy1() const;
  inline void set_dummy1(int32_t value);

  inline int32_t dummy2() const;
  inline void set_dummy2(int32_t value);

  inline int count() const;
  inline void set_count(int value);

  inline int data() const;
  inline void set_data(int value);

  inline Object object() const;
  inline Object object(const Isolate* isolates) const;
  inline void set_object(Object value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline int entries(int i) const;
  inline void set_entries(int i, int value);

  inline int entries() const;
  inline void set_entries(int value);

 public:
  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(InternalClassWithStructElements)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void InternalClassWithStructElementsVerify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kDummy1Offset = P::kHeaderSize;
  static constexpr int kDummy1OffsetEnd = kDummy1Offset + kInt32Size - 1;
  static constexpr int kDummy2Offset = kDummy1OffsetEnd + 1;
  static constexpr int kDummy2OffsetEnd = kDummy2Offset + kInt32Size - 1;
  static constexpr int kStartOfStrongFieldsOffset = kDummy2OffsetEnd + 1;
  static constexpr int kCountOffset = kDummy2OffsetEnd + 1;
  static constexpr int kCountOffsetEnd = kCountOffset + kTaggedSize - 1;
  static constexpr int kDataOffset = kCountOffsetEnd + 1;
  static constexpr int kDataOffsetEnd = kDataOffset + kTaggedSize - 1;
  static constexpr int kObjectOffset = kDataOffsetEnd + 1;
  static constexpr int kObjectOffsetEnd = kObjectOffset + kTaggedSize - 1;
  static constexpr int kHeaderSize = kObjectOffsetEnd + 1;
  static constexpr int kEntriesOffset = kObjectOffsetEnd + 1;
  static constexpr int kEntriesOffsetEnd = kEntriesOffset + 0 - 1;
  static constexpr int kMoreEntriesOffset = kEntriesOffsetEnd + 1;
  static constexpr int kMoreEntriesOffsetEnd = kMoreEntriesOffset + 0 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kMoreEntriesOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kMoreEntriesOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kMoreEntriesOffsetEnd + 1;

  V8_INLINE static constexpr int32_t SizeFor(int count) {
    int32_t size = kHeaderSize;
    size += count * 4;
    size += count * 8;
    return size;
  }

  V8_INLINE int32_t AllocatedSize() {
    return SizeFor(this->count());
  }

  friend class Factory;

 public:
  template <class DAlias = D>
  constexpr TorqueGeneratedInternalClassWithStructElements() : P() {
    static_assert(std::is_base_of<TorqueGeneratedInternalClassWithStructElements, 
      DAlias>::value,
      "class TorqueGeneratedInternalClassWithStructElements should be used as direct base for InternalClassWithStructElements.");
  }
protected:
  inline explicit TorqueGeneratedInternalClassWithStructElements(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedInternalClassWithStructElements(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class InternalClassWithStructElements : public TorqueGeneratedInternalClassWithStructElements<InternalClassWithStructElements, HeapObject> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(InternalClassWithStructElements)
};

template <class D, class P>
class TorqueGeneratedSortState : public P {
  static_assert(std::is_same<SortState, D>::value,
    "Use this class as direct base for SortState.");
  static_assert(std::is_same<HeapObject, P>::value,
    "Pass in HeapObject as second template parameter for TorqueGeneratedSortState.");
 public: 
  using Super = P;

 protected: // not extern or @export
  inline JSReceiver receiver() const;
  inline JSReceiver receiver(const Isolate* isolates) const;
  inline void set_receiver(JSReceiver value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline Map initialReceiverMap() const;
  inline Map initialReceiverMap(const Isolate* isolates) const;
  inline void set_initialReceiverMap(Map value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  // Torque type: Number
  inline Object initialReceiverLength() const;
  inline Object initialReceiverLength(const Isolate* isolates) const;
  inline void set_initialReceiverLength(Object value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  // Torque type: (Undefined | CallableApiObject | CallableJSProxy | class JSBoundFunction | class JSFunction)
  inline HeapObject userCmpFn() const;
  inline HeapObject userCmpFn(const Isolate* isolates) const;
  inline void set_userCmpFn(HeapObject value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline int sortComparePtr() const;
  inline void set_sortComparePtr(int value);

  inline int loadFn() const;
  inline void set_loadFn(int value);

  inline int storeFn() const;
  inline void set_storeFn(int value);

  inline int deleteFn() const;
  inline void set_deleteFn(int value);

  inline int canUseSameAccessorFn() const;
  inline void set_canUseSameAccessorFn(int value);

  inline int minGallop() const;
  inline void set_minGallop(int value);

  inline int pendingRunsSize() const;
  inline void set_pendingRunsSize(int value);

  inline FixedArray pendingRuns() const;
  inline FixedArray pendingRuns(const Isolate* isolates) const;
  inline void set_pendingRuns(FixedArray value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline FixedArray workArray() const;
  inline FixedArray workArray(const Isolate* isolates) const;
  inline void set_workArray(FixedArray value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline FixedArray tempArray() const;
  inline FixedArray tempArray(const Isolate* isolates) const;
  inline void set_tempArray(FixedArray value, WriteBarrierMode mode = UPDATE_WRITE_BARRIER);

  inline int sortLength() const;
  inline void set_sortLength(int value);

  inline int numberOfUndefined() const;
  inline void set_numberOfUndefined(int value);

 public:
  V8_INLINE static D cast(Object object) {
    return D(object.ptr());
  }
  V8_INLINE static D unchecked_cast(Object object) {
    return bit_cast<D>(object);
  }

  DECL_PRINTER(SortState)
#ifdef VERIFY_HEAP
  V8_EXPORT_PRIVATE void SortStateVerify(Isolate* isolate);
#endif  // VERIFY_HEAP

  static constexpr int kStartOfStrongFieldsOffset = P::kHeaderSize;
  static constexpr int kReceiverOffset = P::kHeaderSize;
  static constexpr int kReceiverOffsetEnd = kReceiverOffset + kTaggedSize - 1;
  static constexpr int kInitialReceiverMapOffset = kReceiverOffsetEnd + 1;
  static constexpr int kInitialReceiverMapOffsetEnd = kInitialReceiverMapOffset + kTaggedSize - 1;
  static constexpr int kInitialReceiverLengthOffset = kInitialReceiverMapOffsetEnd + 1;
  static constexpr int kInitialReceiverLengthOffsetEnd = kInitialReceiverLengthOffset + kTaggedSize - 1;
  static constexpr int kUserCmpFnOffset = kInitialReceiverLengthOffsetEnd + 1;
  static constexpr int kUserCmpFnOffsetEnd = kUserCmpFnOffset + kTaggedSize - 1;
  static constexpr int kSortComparePtrOffset = kUserCmpFnOffsetEnd + 1;
  static constexpr int kSortComparePtrOffsetEnd = kSortComparePtrOffset + kTaggedSize - 1;
  static constexpr int kLoadFnOffset = kSortComparePtrOffsetEnd + 1;
  static constexpr int kLoadFnOffsetEnd = kLoadFnOffset + kTaggedSize - 1;
  static constexpr int kStoreFnOffset = kLoadFnOffsetEnd + 1;
  static constexpr int kStoreFnOffsetEnd = kStoreFnOffset + kTaggedSize - 1;
  static constexpr int kDeleteFnOffset = kStoreFnOffsetEnd + 1;
  static constexpr int kDeleteFnOffsetEnd = kDeleteFnOffset + kTaggedSize - 1;
  static constexpr int kCanUseSameAccessorFnOffset = kDeleteFnOffsetEnd + 1;
  static constexpr int kCanUseSameAccessorFnOffsetEnd = kCanUseSameAccessorFnOffset + kTaggedSize - 1;
  static constexpr int kMinGallopOffset = kCanUseSameAccessorFnOffsetEnd + 1;
  static constexpr int kMinGallopOffsetEnd = kMinGallopOffset + kTaggedSize - 1;
  static constexpr int kPendingRunsSizeOffset = kMinGallopOffsetEnd + 1;
  static constexpr int kPendingRunsSizeOffsetEnd = kPendingRunsSizeOffset + kTaggedSize - 1;
  static constexpr int kPendingRunsOffset = kPendingRunsSizeOffsetEnd + 1;
  static constexpr int kPendingRunsOffsetEnd = kPendingRunsOffset + kTaggedSize - 1;
  static constexpr int kWorkArrayOffset = kPendingRunsOffsetEnd + 1;
  static constexpr int kWorkArrayOffsetEnd = kWorkArrayOffset + kTaggedSize - 1;
  static constexpr int kTempArrayOffset = kWorkArrayOffsetEnd + 1;
  static constexpr int kTempArrayOffsetEnd = kTempArrayOffset + kTaggedSize - 1;
  static constexpr int kSortLengthOffset = kTempArrayOffsetEnd + 1;
  static constexpr int kSortLengthOffsetEnd = kSortLengthOffset + kTaggedSize - 1;
  static constexpr int kNumberOfUndefinedOffset = kSortLengthOffsetEnd + 1;
  static constexpr int kNumberOfUndefinedOffsetEnd = kNumberOfUndefinedOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kNumberOfUndefinedOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kNumberOfUndefinedOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kNumberOfUndefinedOffsetEnd + 1;
  static constexpr int kHeaderSize = kNumberOfUndefinedOffsetEnd + 1;
  static constexpr int kSize = kNumberOfUndefinedOffsetEnd + 1;

  V8_INLINE static constexpr int32_t SizeFor() {
    DCHECK(kHeaderSize == kSize && kHeaderSize == 68);
    int32_t size = kHeaderSize;
    return size;
  }

  V8_INLINE int32_t AllocatedSize() {
    return SizeFor();
  }

  friend class Factory;

 public:
  template <class DAlias = D>
  constexpr TorqueGeneratedSortState() : P() {
    static_assert(std::is_base_of<TorqueGeneratedSortState, 
      DAlias>::value,
      "class TorqueGeneratedSortState should be used as direct base for SortState.");
  }
protected:
  inline explicit TorqueGeneratedSortState(Address ptr);
  // Special-purpose constructor for subclasses that have fast paths where
  // their ptr() is a Smi.
  inline explicit TorqueGeneratedSortState(Address ptr, HeapObject::AllowInlineSmiStorage allow_smi);
};

class SortState : public TorqueGeneratedSortState<SortState, HeapObject> {
 public:
  class BodyDescriptor;
  TQ_OBJECT_CONSTRUCTORS(SortState)
};

}  // namespace internal
}  // namespace v8

#include "src/objects/object-macros-undef.h"
#endif  // V8_GEN_TORQUE_GENERATED_INTERNAL_CLASS_DEFINITIONS_TQ_H_
