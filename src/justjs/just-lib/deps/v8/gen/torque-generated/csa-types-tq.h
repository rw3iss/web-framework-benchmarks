#ifndef V8_GEN_TORQUE_GENERATED_CSA_TYPES_TQ_H_
#define V8_GEN_TORQUE_GENERATED_CSA_TYPES_TQ_H_

#include "src/compiler/code-assembler.h"

namespace v8 {
namespace internal {
struct TorqueStructBuffer_0 {
  TNode<FixedArray> fixedArray;
  TNode<IntPtrT> index;
  TNode<IntPtrT> totalStringLength;
  TNode<BoolT> isOneByte;

  std::tuple<TNode<FixedArray>, TNode<IntPtrT>, TNode<IntPtrT>, TNode<BoolT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(fixedArray), std::make_tuple(index), std::make_tuple(totalStringLength), std::make_tuple(isOneByte));
  }
};
struct TorqueStructVector_0 {
  TNode<FixedArray> fixedArray;
  TNode<BoolT> onlySmis;
  TNode<BoolT> onlyNumbers;
  TNode<BoolT> skippedElements;

  std::tuple<TNode<FixedArray>, TNode<BoolT>, TNode<BoolT>, TNode<BoolT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(fixedArray), std::make_tuple(onlySmis), std::make_tuple(onlyNumbers), std::make_tuple(skippedElements));
  }
};
struct TorqueStructfloat64_or_hole_0 {
  TNode<BoolT> is_hole;
  TNode<Float64T> value;

  std::tuple<TNode<BoolT>, TNode<Float64T>> Flatten() const {
    return std::tuple_cat(std::make_tuple(is_hole), std::make_tuple(value));
  }
};
struct TorqueStructKeyValuePair {
  TNode<Object> key;
  TNode<Object> value;

  std::tuple<TNode<Object>, TNode<Object>> Flatten() const {
    return std::tuple_cat(std::make_tuple(key), std::make_tuple(value));
  }
};
struct TorqueStructArguments {
  TNode<RawPtrT> frame;
  TNode<RawPtrT> base;
  TNode<IntPtrT> length;

  std::tuple<TNode<RawPtrT>, TNode<RawPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(frame), std::make_tuple(base), std::make_tuple(length));
  }
};
struct TorqueStructArgumentsIterator_0 {
  TorqueStructArguments arguments;
  TNode<IntPtrT> current;

  std::tuple<TNode<RawPtrT>, TNode<RawPtrT>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(arguments.Flatten(), std::make_tuple(current));
  }
};
struct TorqueStructFrameWithArgumentsInfo_0 {
  TNode<RawPtrT> frame;
  TNode<BInt> argument_count;
  TNode<BInt> formal_parameter_count;

  std::tuple<TNode<RawPtrT>, TNode<BInt>, TNode<BInt>> Flatten() const {
    return std::tuple_cat(std::make_tuple(frame), std::make_tuple(argument_count), std::make_tuple(formal_parameter_count));
  }
};
struct TorqueStructGrowableFixedArray_0 {
  TNode<FixedArray> array;
  TNode<IntPtrT> capacity;
  TNode<IntPtrT> length;

  std::tuple<TNode<FixedArray>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(array), std::make_tuple(capacity), std::make_tuple(length));
  }
};
struct TorqueStructIteratorRecord {
  TNode<JSReceiver> object;
  TNode<Object> next;

  std::tuple<TNode<JSReceiver>, TNode<Object>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(next));
  }
};
struct TorqueStructPromiseResolvingFunctions {
  TNode<JSFunction> resolve;
  TNode<JSFunction> reject;

  std::tuple<TNode<JSFunction>, TNode<JSFunction>> Flatten() const {
    return std::tuple_cat(std::make_tuple(resolve), std::make_tuple(reject));
  }
};
struct TorqueStructPromiseAllResolveElementFunctor_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructPromiseAllRejectElementFunctor_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructPromiseAllSettledResolveElementFunctor_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructPromiseAllSettledRejectElementFunctor_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructPromiseAllWrapResultAsFulfilledFunctor_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructPromiseAllSettledWrapResultAsFulfilledFunctor_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructPromiseAllSettledWrapResultAsRejectedFunctor_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructPromiseFinallyFunctions_0 {
  TNode<JSFunction> then_finally;
  TNode<JSFunction> catch_finally;

  std::tuple<TNode<JSFunction>, TNode<JSFunction>> Flatten() const {
    return std::tuple_cat(std::make_tuple(then_finally), std::make_tuple(catch_finally));
  }
};
struct TorqueStructInvokeThenOneArgFunctor_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructInvokeThenTwoArgFunctor_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructUnsafe_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructUninitializedIterator_0 {

  std::tuple<> Flatten() const {
    return std::tuple_cat();
  }
};
struct TorqueStructTypedArrayElementsInfo {
  TNode<UintPtrT> sizeLog2;
  TNode<Int32T> kind;

  std::tuple<TNode<UintPtrT>, TNode<Int32T>> Flatten() const {
    return std::tuple_cat(std::make_tuple(sizeLog2), std::make_tuple(kind));
  }
};
struct TorqueStructTypedArrayAccessor_0 {
  TNode<BuiltinPtr> loadNumericFn;
  TNode<BuiltinPtr> storeNumericFn;
  TNode<BuiltinPtr> storeJSAnyFn;

  std::tuple<TNode<BuiltinPtr>, TNode<BuiltinPtr>, TNode<BuiltinPtr>> Flatten() const {
    return std::tuple_cat(std::make_tuple(loadNumericFn), std::make_tuple(storeNumericFn), std::make_tuple(storeJSAnyFn));
  }
};
struct TorqueStructAttachedJSTypedArrayWitness_0 {
  TNode<JSTypedArray> stable;
  TNode<JSTypedArray> unstable;
  TNode<BuiltinPtr> loadfn;

  std::tuple<TNode<JSTypedArray>, TNode<JSTypedArray>, TNode<BuiltinPtr>> Flatten() const {
    return std::tuple_cat(std::make_tuple(stable), std::make_tuple(unstable), std::make_tuple(loadfn));
  }
};
struct TorqueStructParameterMapIterator_0 {
  TNode<IntPtrT> currentIndex;
  TNode<IntPtrT> endInterationIndex;

  std::tuple<TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(currentIndex), std::make_tuple(endInterationIndex));
  }
};
struct TorqueStructParameterValueIterator_0 {
  TNode<IntPtrT> mapped_count;
  TorqueStructArguments arguments;
  TNode<IntPtrT> current;

  std::tuple<TNode<IntPtrT>, TNode<RawPtrT>, TNode<RawPtrT>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(mapped_count), arguments.Flatten(), std::make_tuple(current));
  }
};
struct TorqueStructCoverageInfoSlot {
  TNode<Int32T> start_source_position;
  TNode<Int32T> end_source_position;
  TNode<Int32T> block_count;
  TNode<Int32T> padding;

  std::tuple<TNode<Int32T>, TNode<Int32T>, TNode<Int32T>, TNode<Int32T>> Flatten() const {
    return std::tuple_cat(std::make_tuple(start_source_position), std::make_tuple(end_source_position), std::make_tuple(block_count), std::make_tuple(padding));
  }
};
struct TorqueStructDescriptorEntry {
  TNode<PrimitiveHeapObject> key;
  TNode<Object> details;
  TNode<MaybeObject> value;

  std::tuple<TNode<PrimitiveHeapObject>, TNode<Object>, TNode<MaybeObject>> Flatten() const {
    return std::tuple_cat(std::make_tuple(key), std::make_tuple(details), std::make_tuple(value));
  }
};
struct TorqueStructFastJSArrayWitness_0 {
  TNode<JSArray> stable;
  TNode<JSArray> unstable;
  TNode<Map> map;
  TNode<BoolT> hasDoubles;
  TNode<BoolT> hasSmis;
  TNode<BoolT> arrayIsPushable;

  std::tuple<TNode<JSArray>, TNode<JSArray>, TNode<Map>, TNode<BoolT>, TNode<BoolT>, TNode<BoolT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(stable), std::make_tuple(unstable), std::make_tuple(map), std::make_tuple(hasDoubles), std::make_tuple(hasSmis), std::make_tuple(arrayIsPushable));
  }
};
struct TorqueStructFastJSArrayForReadWitness_0 {
  TNode<JSArray> stable;
  TNode<JSArray> unstable;
  TNode<Map> map;
  TNode<BoolT> hasDoubles;

  std::tuple<TNode<JSArray>, TNode<JSArray>, TNode<Map>, TNode<BoolT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(stable), std::make_tuple(unstable), std::make_tuple(map), std::make_tuple(hasDoubles));
  }
};
struct TorqueStructHashMapEntry_0 {
  TNode<Object> key;
  TNode<Object> value;

  std::tuple<TNode<Object>, TNode<Object>> Flatten() const {
    return std::tuple_cat(std::make_tuple(key), std::make_tuple(value));
  }
};
struct TorqueStructNameDictionaryEntry_0 {
  TNode<Object> key;
  TNode<Object> value;
  TNode<Object> property_details;

  std::tuple<TNode<Object>, TNode<Object>, TNode<Object>> Flatten() const {
    return std::tuple_cat(std::make_tuple(key), std::make_tuple(value), std::make_tuple(property_details));
  }
};
struct TorqueStructTestStructA_0 {
  TNode<FixedArray> indexes;
  TNode<Smi> i;
  TNode<Number> k;

  std::tuple<TNode<FixedArray>, TNode<Smi>, TNode<Number>> Flatten() const {
    return std::tuple_cat(std::make_tuple(indexes), std::make_tuple(i), std::make_tuple(k));
  }
};
struct TorqueStructTestStructB_0 {
  TorqueStructTestStructA_0 x;
  TNode<Smi> y;

  std::tuple<TNode<FixedArray>, TNode<Smi>, TNode<Number>, TNode<Smi>> Flatten() const {
    return std::tuple_cat(x.Flatten(), std::make_tuple(y));
  }
};
struct TorqueStructTestStructC_0 {
  TorqueStructTestStructA_0 x;
  TorqueStructTestStructA_0 y;

  std::tuple<TNode<FixedArray>, TNode<Smi>, TNode<Number>, TNode<FixedArray>, TNode<Smi>, TNode<Number>> Flatten() const {
    return std::tuple_cat(x.Flatten(), y.Flatten());
  }
};
struct TorqueStructTestInner_0 {
  TNode<Int32T> x;
  TNode<Int32T> y;

  std::tuple<TNode<Int32T>, TNode<Int32T>> Flatten() const {
    return std::tuple_cat(std::make_tuple(x), std::make_tuple(y));
  }
};
struct TorqueStructTestOuter_0 {
  TNode<Int32T> a;
  TorqueStructTestInner_0 b;
  TNode<Int32T> c;

  std::tuple<TNode<Int32T>, TNode<Int32T>, TNode<Int32T>, TNode<Int32T>> Flatten() const {
    return std::tuple_cat(std::make_tuple(a), b.Flatten(), std::make_tuple(c));
  }
};
struct TorqueStructStructWithConst_0 {
  TNode<Object> a;
  TNode<Int32T> b;

  std::tuple<TNode<Object>, TNode<Int32T>> Flatten() const {
    return std::tuple_cat(std::make_tuple(a), std::make_tuple(b));
  }
};
struct TorqueStructTestIterator_0 {
  TNode<Smi> count;

  std::tuple<TNode<Smi>> Flatten() const {
    return std::tuple_cat(std::make_tuple(count));
  }
};
struct TorqueStructInternalClassStructElement_0 {
  TNode<Smi> a;
  TNode<Smi> b;

  std::tuple<TNode<Smi>, TNode<Smi>> Flatten() const {
    return std::tuple_cat(std::make_tuple(a), std::make_tuple(b));
  }
};
struct TorqueStructSmiGeneratorIterator_0 {
  TNode<Smi> value;

  std::tuple<TNode<Smi>> Flatten() const {
    return std::tuple_cat(std::make_tuple(value));
  }
};
struct TorqueStructInternalClassStructElementGeneratorIterator_0 {
  TNode<Smi> value;

  std::tuple<TNode<Smi>> Flatten() const {
    return std::tuple_cat(std::make_tuple(value));
  }
};
struct TorqueStructSlice_char8_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructSlice_char16_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_float64_or_hole_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructTestTuple_intptr_Smi_0 {
  TNode<IntPtrT> fst;
  TNode<Smi> snd;

  std::tuple<TNode<IntPtrT>, TNode<Smi>> Flatten() const {
    return std::tuple_cat(std::make_tuple(fst), std::make_tuple(snd));
  }
};
struct TorqueStructTestTuple_Smi_intptr_0 {
  TNode<Smi> fst;
  TNode<IntPtrT> snd;

  std::tuple<TNode<Smi>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(fst), std::make_tuple(snd));
  }
};
struct TorqueStructTestTuple_TestTuple_intptr_Smi_TestTuple_Smi_intptr_0 {
  TorqueStructTestTuple_intptr_Smi_0 fst;
  TorqueStructTestTuple_Smi_intptr_0 snd;

  std::tuple<TNode<IntPtrT>, TNode<Smi>, TNode<Smi>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(fst.Flatten(), snd.Flatten());
  }
};
struct TorqueStructReference_Smi_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_char8_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_char8_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_char16_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_char16_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Map_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_FixedArrayBase_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSlice_Object_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Object_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_Object_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructSlice_float64_or_hole_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_float64_or_hole_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Number_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSArrayBuffer_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_FixedArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_uintptr_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_FixedArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Context_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSlice_Smi_OR_TheHole_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Smi_OR_TheHole_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_Smi_OR_TheHole_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_DescriptorArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_DescriptorEntry_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_uint16_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSlice_DescriptorEntry_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_DescriptorEntry_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Name_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Smi_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSFunction_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Constructor_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Callable_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_RegExpMatchInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSAny_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_String_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SymbolFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_uint8_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSReceiver_OR_Map_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_WeakCell_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_NativeContext_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_FinalizationRegistryFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_JSFinalizationRegistry_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSReceiver_OR_Undefined_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SharedFunctionInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSReceiver_OR_Undefined_OR_Null_OR_False_OR_True_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_Smi_OR_AccessorInfo_OR_ClassPositions_OR_AccessorPair_OR_Weak_Map_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_MapBitFields3_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSReceiver_OR_Null_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Smi_OR_FixedArrayBase_OR_PropertyArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSReceiver_OR_Undefined_OR_Null_OR_False_OR_True_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_Smi_OR_SourceTextModule_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_FeedbackCell_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_DebugInfo_OR_Script_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_DebugInfoFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_CoverageInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_int32_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSlice_CoverageInfoSlot_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_CoverageInfoSlot_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_CoverageInfoSlot_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_FixedDoubleArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_NameHash_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Weak_Map_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_CallableApiObject_OR_CallableJSProxy_OR_JSBoundFunction_OR_JSFunction_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Zero_OR_PromiseReaction_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSReceiver_OR_Undefined_OR_Null_OR_False_OR_True_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_Smi_OR_PromiseReaction_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSPromise_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Boolean_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_PromiseCapability_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSObject_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_JSPromiseFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_HeapObject_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_JSPromise_OR_PromiseCapability_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSReceiver_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Null_OR_JSProxy_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_String_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_JSRegExpStringIteratorFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_SmiTagged_JSRegExpFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_float64_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructConstantIterator_Smi_0 {
  TNode<Smi> value;

  std::tuple<TNode<Smi>> Flatten() const {
    return std::tuple_cat(std::make_tuple(value));
  }
};
struct TorqueStructConstantIterator_TheHole_0 {
  TNode<Oddball> value;

  std::tuple<TNode<Oddball>> Flatten() const {
    return std::tuple_cat(std::make_tuple(value));
  }
};
struct TorqueStructIteratorSequence_Object_SliceIterator_Object_ConstantIterator_TheHole_0 {
  TorqueStructSliceIterator_Object_0 first;
  TorqueStructConstantIterator_TheHole_0 second;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>, TNode<Oddball>> Flatten() const {
    return std::tuple_cat(first.Flatten(), second.Flatten());
  }
};
struct TorqueStructConstantIterator_float64_or_hole_0 {
  TorqueStructfloat64_or_hole_0 value;

  std::tuple<TNode<BoolT>, TNode<Float64T>> Flatten() const {
    return std::tuple_cat(value.Flatten());
  }
};
struct TorqueStructIteratorSequence_float64_or_hole_SliceIterator_float64_or_hole_ConstantIterator_float64_or_hole_0 {
  TorqueStructSliceIterator_float64_or_hole_0 first;
  TorqueStructConstantIterator_float64_or_hole_0 second;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>, TNode<BoolT>, TNode<Float64T>> Flatten() const {
    return std::tuple_cat(first.Flatten(), second.Flatten());
  }
};
struct TorqueStructReference_JSArrayBufferFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_IterationKind_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_InstanceType_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_MapBitFields1_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructConstantIterator_uint8_0 {
  TNode<Uint8T> value;

  std::tuple<TNode<Uint8T>> Flatten() const {
    return std::tuple_cat(std::make_tuple(value));
  }
};
struct TorqueStructSlice_uint8_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_uint8_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructSlice_JSReceiver_OR_Undefined_OR_Null_OR_False_OR_True_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_Smi_OR_TheHole_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSReceiver_OR_Undefined_OR_Null_OR_False_OR_True_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_Smi_OR_TheHole_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_JSReceiver_OR_Undefined_OR_Null_OR_False_OR_True_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_Smi_OR_TheHole_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructConstantIterator_HashMapEntry_0 {
  TorqueStructHashMapEntry_0 value;

  std::tuple<TNode<Object>, TNode<Object>> Flatten() const {
    return std::tuple_cat(value.Flatten());
  }
};
struct TorqueStructSlice_HashMapEntry_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_HashMapEntry_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_HashMapEntry_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructSBox_intptr_0 {
  TNode<IntPtrT> value;

  std::tuple<TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(value));
  }
};
struct TorqueStructSBox_SBox_intptr_0 {
  TorqueStructSBox_intptr_0 value;

  std::tuple<TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(value.Flatten());
  }
};
struct TorqueStructReference_Oddball_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSlice_Smi_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_Smi_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructSlice_InternalClassStructElement_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_InternalClassStructElement_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_InternalClassStructElement_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_CompareBuiltinFn_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_LoadFn_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_StoreFn_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_DeleteFn_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_CanUseSameAccessorFn_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_ScopeInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSlice_MaybeObject_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TNode<IntPtrT> length;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), std::make_tuple(length), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_MaybeObject_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructSliceIterator_MaybeObject_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> start;
  TNode<IntPtrT> end;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(start), std::make_tuple(end), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_ExternalPointer_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Code_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_MapBitFields2_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_DependentCode_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Smi_OR_Cell_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Smi_OR_TransitionArray_OR_Map_OR_Weak_Map_OR_PrototypeInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Smi_OR_ByteArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Smi_OR_Code_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_AllocationSite_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Zero_OR_NonNullForeign_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_InterceptorInfoFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Zero_OR_Foreign_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Zero_OR_InterceptorInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Name_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_AccessorInfoFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Zero_OR_NonNullForeign_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_ByteArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_ByteArray_OR_Exception_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_int8_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_FixedArray_OR_BreakPoint_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_DebuggerHints_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Script_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_BytecodeArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_WasmValueType_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_EnumCache_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_FixedArray_OR_FeedbackVector_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Smi_OR_Weak_Code_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_uint32_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Uninitialized_OR_FreeSpace_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_RawPtr_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_AsyncGeneratorRequest_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSGlobalProxy_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Script_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_SharedFunctionInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_NumberOrUndefined_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Smi_OR_NaN_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSRegExp_OR_JSRegExpResultIndices_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Foreign_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_ObjectHashTable_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_JSModuleNamespace_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Module_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_AnyName_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_PropertyDescriptorObjectFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Zero_OR_WeakArrayList_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_FixedArray_OR_Zero_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_PrototypeInfoFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Symbol_OR_Smi_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_FixedArray_OR_SharedFunctionInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Smi_OR_Foreign_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_WeakFixedArray_OR_WeakArrayList_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_ScriptFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_BytecodeArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_String_OR_NoSharedNameSentinel_OR_ScopeInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_int16_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SharedFunctionInfoFlags2_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SharedFunctionInfoFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_PreparseData_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSFunction_OR_JSGeneratorObject_OR_SharedFunctionInfo_OR_SourceTextModuleInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSObject_OR_TheHole_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_ArrayList_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_JSPromise_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_SourceTextModuleFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Null_OR_String_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Null_OR_WasmInstanceObject_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_StackFrameInfoFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_FrameArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_StackFrameInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_JSArray_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_TheHole_OR_CachedTemplateObject_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_TemplateList_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_ObjectTemplateInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_FunctionTemplateInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_InterceptorInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_CallHandlerInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_AccessCheckInfo_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Zero_OR_Foreign_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_FunctionTemplateRareData_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_FunctionTemplateInfoFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_SmiTagged_ObjectTemplateInfoFlags_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_WasmInstanceObject_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_Foreign_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_WeakArrayList_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_Undefined_OR_JSArrayBuffer_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
struct TorqueStructReference_HeapNumber_0 {
  TNode<HeapObject> object;
  TNode<IntPtrT> offset;
  TorqueStructUnsafe_0 unsafeMarker;

  std::tuple<TNode<HeapObject>, TNode<IntPtrT>> Flatten() const {
    return std::tuple_cat(std::make_tuple(object), std::make_tuple(offset), unsafeMarker.Flatten());
  }
};
}  // namespace internal
}  // namespace v8
#endif  // V8_GEN_TORQUE_GENERATED_CSA_TYPES_TQ_H_
