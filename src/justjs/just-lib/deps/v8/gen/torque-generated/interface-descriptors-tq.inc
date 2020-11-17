class ArrayEveryLoopContinuationDescriptor : public TorqueInterfaceDescriptor<8, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ArrayEveryLoopContinuationDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 8> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ArrayFilterLoopContinuationDescriptor : public TorqueInterfaceDescriptor<8, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ArrayFilterLoopContinuationDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 8> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ArrayFindLoopContinuationDescriptor : public TorqueInterfaceDescriptor<6, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ArrayFindLoopContinuationDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 6> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ArrayFindIndexLoopContinuationDescriptor : public TorqueInterfaceDescriptor<6, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ArrayFindIndexLoopContinuationDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 6> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ArrayForEachLoopContinuationDescriptor : public TorqueInterfaceDescriptor<8, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ArrayForEachLoopContinuationDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 8> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class LoadJoinElement_DictionaryElements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinElement_DictionaryElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinElement_FastSmiOrObjectElements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinElement_FastSmiOrObjectElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinElement_FastDoubleElements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinElement_FastDoubleElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class ConvertToLocaleStringDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ConvertToLocaleStringDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class JoinStackPushDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(JoinStackPushDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class JoinStackPopDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(JoinStackPopDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class ArrayMapLoopContinuationDescriptor : public TorqueInterfaceDescriptor<7, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ArrayMapLoopContinuationDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 7> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ArrayReduceRightLoopContinuationDescriptor : public TorqueInterfaceDescriptor<6, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ArrayReduceRightLoopContinuationDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 6> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ArrayReduceLoopContinuationDescriptor : public TorqueInterfaceDescriptor<6, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ArrayReduceLoopContinuationDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 6> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ArraySomeLoopContinuationDescriptor : public TorqueInterfaceDescriptor<8, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ArraySomeLoopContinuationDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 8> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ToIntegerDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ToIntegerDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class FastCreateDataPropertyDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(FastCreateDataPropertyDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class CheckNumberInRangeDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CheckNumberInRangeDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class CheckSameObjectDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CheckSameObjectDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class BigIntAddNoThrowDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(BigIntAddNoThrowDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class BigIntAddDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(BigIntAddDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class BigIntSubtractNoThrowDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(BigIntSubtractNoThrowDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class BigIntSubtractDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(BigIntSubtractDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class BigIntUnaryMinusDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(BigIntUnaryMinusDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class ToStringDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ToStringDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class StringToListDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StringToListDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class StringAddConvertLeftDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StringAddConvertLeftDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::TaggedPointer()};
  }
};

class StringAddConvertRightDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StringAddConvertRightDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class StringCharAtDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StringCharAtDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class FastNewFunctionContextEvalDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(FastNewFunctionContextEvalDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<Uint32T>::value};
  }
};

class FastNewFunctionContextFunctionDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(FastNewFunctionContextFunctionDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<Uint32T>::value};
  }
};

class CreateRegExpLiteralDescriptor : public TorqueInterfaceDescriptor<4, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CreateRegExpLiteralDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 4> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::TaggedSigned()};
  }
};

class CreateShallowArrayLiteralDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CreateShallowArrayLiteralDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedPointer()};
  }
};

class CreateEmptyArrayLiteralDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CreateEmptyArrayLiteralDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class CreateShallowObjectLiteralDescriptor : public TorqueInterfaceDescriptor<4, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CreateShallowObjectLiteralDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 4> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class CreateEmptyLiteralObjectDescriptor : public TorqueInterfaceDescriptor<0, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CreateEmptyLiteralObjectDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class StringToNumberDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StringToNumberDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class NonNumberToNumberDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(NonNumberToNumberDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class NonNumberToNumericDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(NonNumberToNumericDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class ToNumericDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ToNumericDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class NumberToStringDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(NumberToStringDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class ToBooleanDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ToBooleanDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class ToLengthDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ToLengthDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class ToNameDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ToNameDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class ToObjectDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ToObjectDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class NonPrimitiveToPrimitive_DefaultDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(NonPrimitiveToPrimitive_DefaultDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class NonPrimitiveToPrimitive_NumberDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(NonPrimitiveToPrimitive_NumberDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class NonPrimitiveToPrimitive_StringDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(NonPrimitiveToPrimitive_StringDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class OrdinaryToPrimitive_NumberDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(OrdinaryToPrimitive_NumberDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class OrdinaryToPrimitive_StringDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(OrdinaryToPrimitive_StringDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class IncBlockCounterDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(IncBlockCounterDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class GetTemplateObjectDescriptor : public TorqueInterfaceDescriptor<4, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(GetTemplateObjectDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 4> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::TaggedPointer()};
  }
};

class BytecodeBudgetInterruptFromCodeDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(BytecodeBudgetInterruptFromCodeDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class GetIteratorWithFeedbackDescriptor : public TorqueInterfaceDescriptor<4, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(GetIteratorWithFeedbackDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 4> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::TaggedPointer()};
  }
};

class CallIteratorWithFeedbackDescriptor : public TorqueInterfaceDescriptor<4, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CallIteratorWithFeedbackDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 4> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::TaggedSigned(), MachineType::TaggedPointer()};
  }
};

class ParseIntDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ParseIntDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class AddDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(AddDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class SubtractDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(SubtractDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class MultiplyDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(MultiplyDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class DivideDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(DivideDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ModulusDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ModulusDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ExponentiateDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ExponentiateDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class NegateDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(NegateDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class BitwiseNotDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(BitwiseNotDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class DecrementDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(DecrementDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class IncrementDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(IncrementDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class ShiftLeftDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ShiftLeftDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ShiftRightDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ShiftRightDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ShiftRightLogicalDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ShiftRightLogicalDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class BitwiseAndDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(BitwiseAndDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class BitwiseOrDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(BitwiseOrDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class BitwiseXorDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(BitwiseXorDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class LessThanDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LessThanDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class LessThanOrEqualDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LessThanOrEqualDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class GreaterThanDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(GreaterThanDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class GreaterThanOrEqualDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(GreaterThanOrEqualDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class EqualDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(EqualDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class StrictEqualDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StrictEqualDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class CreateObjectWithoutPropertiesDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CreateObjectWithoutPropertiesDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class FulfillPromiseDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(FulfillPromiseDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class RejectPromiseDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(RejectPromiseDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedPointer()};
  }
};

class NewPromiseCapabilityDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(NewPromiseCapabilityDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::TaggedPointer()};
  }
};

class PerformPromiseThenDescriptor : public TorqueInterfaceDescriptor<4, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(PerformPromiseThenDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 4> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class PromiseFulfillReactionJobDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(PromiseFulfillReactionJobDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class PromiseRejectReactionJobDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(PromiseRejectReactionJobDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class PromiseResolveDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(PromiseResolveDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class ResolvePromiseDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ResolvePromiseDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class PromiseResolveThenableJobDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(PromiseResolveThenableJobDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class ProxyDeletePropertyDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ProxyDeletePropertyDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class ProxyGetPropertyDescriptor : public TorqueInterfaceDescriptor<4, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ProxyGetPropertyDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 4> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedSigned()};
  }
};

class ProxyGetPrototypeOfDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ProxyGetPrototypeOfDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class ProxyHasPropertyDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ProxyHasPropertyDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class ProxyIsExtensibleDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ProxyIsExtensibleDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class ProxyPreventExtensionsDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ProxyPreventExtensionsDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class ProxySetPropertyDescriptor : public TorqueInterfaceDescriptor<4, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ProxySetPropertyDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 4> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class ProxySetPrototypeOfDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ProxySetPrototypeOfDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class RegExpPrototypeExecSlowDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(RegExpPrototypeExecSlowDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class RegExpMatchFastDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(RegExpMatchFastDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class RegExpReplaceDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(RegExpReplaceDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class RegExpSearchFastDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(RegExpSearchFastDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class RegExpSplitDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(RegExpSplitDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class RegExpPrototypeTestFastDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(RegExpPrototypeTestFastDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class CreateHTMLDescriptor : public TorqueInterfaceDescriptor<5, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CreateHTMLDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 5> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class StringRepeatDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StringRepeatDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class CreateTypedArrayDescriptor : public TorqueInterfaceDescriptor<5, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CreateTypedArrayDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 5> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class TypedArrayMergeSortDescriptor : public TorqueInterfaceDescriptor<6, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(TypedArrayMergeSortDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 6> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineTypeOf<UintPtrT>::value, MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class WasmInt32ToHeapNumberDescriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmInt32ToHeapNumberDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineTypeOf<Int32T>::value};
  }
};

class WasmTaggedNonSmiToInt32Descriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTaggedNonSmiToInt32Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineTypeOf<Int32T>::value;
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class WasmTaggedToFloat64Descriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTaggedToFloat64Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineTypeOf<Float64T>::value;
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class WasmMemoryGrowDescriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmMemoryGrowDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineTypeOf<Int32T>::value;
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineTypeOf<Int32T>::value};
  }
};

class WasmTableInitDescriptor : public TorqueInterfaceDescriptor<5, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTableInitDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 5> ParameterTypes() override {
    return {MachineTypeOf<Uint32T>::value, MachineTypeOf<Uint32T>::value, MachineTypeOf<Uint32T>::value, MachineType::TaggedSigned(), MachineType::TaggedSigned()};
  }
};

class WasmTableCopyDescriptor : public TorqueInterfaceDescriptor<5, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTableCopyDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 5> ParameterTypes() override {
    return {MachineTypeOf<Uint32T>::value, MachineTypeOf<Uint32T>::value, MachineTypeOf<Uint32T>::value, MachineType::TaggedSigned(), MachineType::TaggedSigned()};
  }
};

class WasmTableGetDescriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTableGetDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineTypeOf<IntPtrT>::value, MachineTypeOf<Int32T>::value};
  }
};

class WasmTableSetDescriptor : public TorqueInterfaceDescriptor<3, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTableSetDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineTypeOf<IntPtrT>::value, MachineTypeOf<Int32T>::value, MachineType::AnyTagged()};
  }
};

class WasmRefFuncDescriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmRefFuncDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineTypeOf<Uint32T>::value};
  }
};

class WasmThrowDescriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmThrowDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class WasmRethrowDescriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmRethrowDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class WasmTriggerTierUpDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTriggerTierUpDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class WasmStackGuardDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmStackGuardDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class WasmStackOverflowDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmStackOverflowDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class WasmTraceMemoryDescriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTraceMemoryDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedSigned()};
  }
};

class WasmTraceEnterDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTraceEnterDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class WasmTraceExitDescriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTraceExitDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedSigned()};
  }
};

class WasmAllocateJSArrayDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmAllocateJSArrayDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedSigned()};
  }
};

class WasmAllocateRttDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmAllocateRttDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedSigned(), MachineType::TaggedPointer()};
  }
};

class WasmAllocateStructWithRttDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmAllocateStructWithRttDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class WasmIsRttSubtypeDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmIsRttSubtypeDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer()};
  }
};

class WasmAllocateObjectWrapperDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmAllocateObjectWrapperDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class WasmInt32ToNumberDescriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmInt32ToNumberDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineTypeOf<Int32T>::value};
  }
};

class WasmUint32ToNumberDescriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmUint32ToNumberDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineTypeOf<Uint32T>::value};
  }
};

class WasmAtomicNotifyDescriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmAtomicNotifyDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineTypeOf<Uint32T>::value;
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineTypeOf<Uint32T>::value, MachineTypeOf<Uint32T>::value};
  }
};

class WasmI32AtomicWait64Descriptor : public TorqueInterfaceDescriptor<3, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmI32AtomicWait64Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineTypeOf<Uint32T>::value;
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineTypeOf<Uint32T>::value, MachineTypeOf<Int32T>::value, MachineTypeOf<IntPtrT>::value};
  }
};

class WasmI64AtomicWait64Descriptor : public TorqueInterfaceDescriptor<3, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmI64AtomicWait64Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineTypeOf<Uint32T>::value;
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineTypeOf<Uint32T>::value, MachineTypeOf<IntPtrT>::value, MachineTypeOf<IntPtrT>::value};
  }
};

class WasmGetOwnPropertyDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmGetOwnPropertyDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::TaggedPointer()};
  }
};

class WasmTrapDescriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(WasmTrapDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedSigned()};
  }
};

class ThrowWasmTrapUnreachableDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapUnreachableDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapMemOutOfBoundsDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapMemOutOfBoundsDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapUnalignedAccessDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapUnalignedAccessDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapDivByZeroDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapDivByZeroDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapDivUnrepresentableDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapDivUnrepresentableDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapRemByZeroDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapRemByZeroDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapFloatUnrepresentableDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapFloatUnrepresentableDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapFuncInvalidDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapFuncInvalidDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapFuncSigMismatchDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapFuncSigMismatchDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapDataSegmentDroppedDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapDataSegmentDroppedDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapElemSegmentDroppedDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapElemSegmentDroppedDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapTableOutOfBoundsDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapTableOutOfBoundsDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapBrOnExnNullDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapBrOnExnNullDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapRethrowNullDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapRethrowNullDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapNullDereferenceDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapNullDereferenceDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapIllegalCastDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapIllegalCastDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class ThrowWasmTrapArrayOutOfBoundsDescriptor : public TorqueInterfaceDescriptor<0, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(ThrowWasmTrapArrayOutOfBoundsDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 0> ParameterTypes() override {
    return {};
  }
};

class NewSloppyArgumentsElementsDescriptor : public TorqueInterfaceDescriptor<3, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(NewSloppyArgumentsElementsDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineTypeOf<RawPtrT>::value, MachineTypeOf<IntPtrT>::value, MachineType::TaggedSigned()};
  }
};

class NewStrictArgumentsElementsDescriptor : public TorqueInterfaceDescriptor<3, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(NewStrictArgumentsElementsDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineTypeOf<RawPtrT>::value, MachineTypeOf<IntPtrT>::value, MachineType::TaggedSigned()};
  }
};

class NewRestArgumentsElementsDescriptor : public TorqueInterfaceDescriptor<3, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(NewRestArgumentsElementsDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineTypeOf<RawPtrT>::value, MachineTypeOf<IntPtrT>::value, MachineType::TaggedSigned()};
  }
};

class GenericBuiltinTest_JSAny_0Descriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(GenericBuiltinTest_JSAny_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::AnyTagged()};
  }
};

class TestHelperPlus1Descriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(TestHelperPlus1Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedSigned()};
  }
};

class TestHelperPlus2Descriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(TestHelperPlus2Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedSigned()};
  }
};

class NewSmiBoxDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(NewSmiBoxDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedSigned()};
  }
};

class Load_FastSmiElements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Load_FastSmiElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class Load_FastObjectElements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Load_FastObjectElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class Load_FastDoubleElements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Load_FastDoubleElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class Store_FastSmiElements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Store_FastSmiElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned(), MachineType::AnyTagged()};
  }
};

class Store_FastObjectElements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Store_FastObjectElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned(), MachineType::AnyTagged()};
  }
};

class Store_FastDoubleElements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Store_FastDoubleElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned(), MachineType::AnyTagged()};
  }
};

class Delete_FastSmiElements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Delete_FastSmiElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class Delete_FastObjectElements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Delete_FastObjectElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class Delete_FastDoubleElements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Delete_FastDoubleElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class SortCompareDefaultDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(SortCompareDefaultDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class SortCompareUserFnDescriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(SortCompareUserFnDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::AnyTagged(), MachineType::AnyTagged(), MachineType::AnyTagged()};
  }
};

class CanUseSameAccessor_GenericElementsAccessor_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CanUseSameAccessor_GenericElementsAccessor_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class CopyDescriptor : public TorqueInterfaceDescriptor<5, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CopyDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 5> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned(), MachineType::TaggedPointer(), MachineType::TaggedSigned(), MachineType::TaggedSigned()};
  }
};

class MergeAtDescriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(MergeAtDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class GallopLeftDescriptor : public TorqueInterfaceDescriptor<6, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(GallopLeftDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 6> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedSigned(), MachineType::TaggedSigned(), MachineType::TaggedSigned()};
  }
};

class GallopRightDescriptor : public TorqueInterfaceDescriptor<6, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(GallopRightDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 6> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged(), MachineType::TaggedSigned(), MachineType::TaggedSigned(), MachineType::TaggedSigned()};
  }
};

class ArrayTimSortDescriptor : public TorqueInterfaceDescriptor<1, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(ArrayTimSortDescriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedPointer()};
  }
};

class LoadJoinElement_GenericElementsAccessor_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinElement_GenericElementsAccessor_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_Int32Elements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_Int32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_Float32Elements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_Float32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_Float64Elements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_Float64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_Uint8ClampedElements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_Uint8ClampedElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_BigUint64Elements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_BigUint64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_BigInt64Elements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_BigInt64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_Uint8Elements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_Uint8Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_Int8Elements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_Int8Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_Uint16Elements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_Uint16Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_Int16Elements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_Int16Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class LoadJoinTypedElement_Uint32Elements_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadJoinTypedElement_Uint32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class GenericBuiltinTest_Smi_0Descriptor : public TorqueInterfaceDescriptor<1, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(GenericBuiltinTest_Smi_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 1> ParameterTypes() override {
    return {MachineType::TaggedSigned()};
  }
};

class CanUseSameAccessor_FastDoubleElements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CanUseSameAccessor_FastDoubleElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class CanUseSameAccessor_FastSmiElements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CanUseSameAccessor_FastSmiElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class CanUseSameAccessor_FastObjectElements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(CanUseSameAccessor_FastObjectElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedPointer();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedPointer(), MachineType::AnyTagged()};
  }
};

class Load_GenericElementsAccessor_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Load_GenericElementsAccessor_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class Store_GenericElementsAccessor_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Store_GenericElementsAccessor_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned(), MachineType::AnyTagged()};
  }
};

class Delete_GenericElementsAccessor_0Descriptor : public TorqueInterfaceDescriptor<2, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(Delete_GenericElementsAccessor_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineType::TaggedSigned()};
  }
};

class LoadTypedElement_Int32Elements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_Int32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_Int32Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_Int32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_Int32Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_Int32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class LoadTypedElement_Float32Elements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_Float32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_Float32Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_Float32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_Float32Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_Float32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class LoadTypedElement_Float64Elements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_Float64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_Float64Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_Float64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_Float64Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_Float64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class LoadTypedElement_Uint8ClampedElements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_Uint8ClampedElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_Uint8ClampedElements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_Uint8ClampedElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_Uint8ClampedElements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_Uint8ClampedElements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class LoadTypedElement_BigUint64Elements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_BigUint64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_BigUint64Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_BigUint64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_BigUint64Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_BigUint64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class LoadTypedElement_BigInt64Elements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_BigInt64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_BigInt64Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_BigInt64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_BigInt64Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_BigInt64Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class LoadTypedElement_Uint8Elements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_Uint8Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_Uint8Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_Uint8Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_Uint8Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_Uint8Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class LoadTypedElement_Int8Elements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_Int8Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_Int8Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_Int8Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_Int8Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_Int8Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class LoadTypedElement_Uint16Elements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_Uint16Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_Uint16Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_Uint16Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_Uint16Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_Uint16Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class LoadTypedElement_Int16Elements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_Int16Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_Int16Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_Int16Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_Int16Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_Int16Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class LoadTypedElement_Uint32Elements_0Descriptor : public TorqueInterfaceDescriptor<2, false> {
  DECLARE_DESCRIPTOR_WITH_BASE(LoadTypedElement_Uint32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::AnyTagged();
  }
  std::array<MachineType, 2> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value};
  }
};

class StoreTypedElementNumeric_Uint32Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementNumeric_Uint32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

class StoreTypedElementJSAny_Uint32Elements_0Descriptor : public TorqueInterfaceDescriptor<3, true> {
  DECLARE_DESCRIPTOR_WITH_BASE(StoreTypedElementJSAny_Uint32Elements_0Descriptor, TorqueInterfaceDescriptor)
  MachineType ReturnType() override {
    return MachineType::TaggedSigned();
  }
  std::array<MachineType, 3> ParameterTypes() override {
    return {MachineType::TaggedPointer(), MachineTypeOf<UintPtrT>::value, MachineType::AnyTagged()};
  }
};

