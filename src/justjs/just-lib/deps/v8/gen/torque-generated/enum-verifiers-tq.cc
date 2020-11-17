#include "src/compiler/code-assembler.h"
#include "src/ast/ast.h"
#include "src/builtins/builtins-array-gen.h"
#include "src/builtins/builtins-bigint-gen.h"
#include "src/builtins/builtins-collections-gen.h"
#include "src/builtins/builtins-constructor-gen.h"
#include "src/builtins/builtins-data-view-gen.h"
#include "src/builtins/builtins-iterator-gen.h"
#include "src/builtins/builtins-promise-gen.h"
#include "src/builtins/builtins-promise.h"
#include "src/builtins/builtins-proxy-gen.h"
#include "src/builtins/builtins-regexp-gen.h"
#include "src/builtins/builtins-string-gen.h"
#include "src/builtins/builtins-typed-array-gen.h"
#include "src/builtins/builtins-utils-gen.h"
#include "src/builtins/builtins-wasm-gen.h"
#include "src/builtins/builtins.h"
#include "src/codegen/code-factory.h"
#include "src/heap/factory-inl.h"
#include "src/ic/binary-op-assembler.h"
#include "src/objects/arguments.h"
#include "src/objects/bigint.h"
#include "src/objects/elements-kind.h"
#include "src/objects/free-space.h"
#include "src/objects/js-function.h"
#include "src/objects/js-generator.h"
#include "src/objects/js-objects.h"
#include "src/objects/js-promise.h"
#include "src/objects/js-regexp-string-iterator.h"
#include "src/objects/js-weak-refs.h"
#include "src/objects/objects.h"
#include "src/objects/ordered-hash-table.h"
#include "src/objects/property-array.h"
#include "src/objects/property-descriptor-object.h"
#include "src/objects/source-text-module.h"
#include "src/objects/stack-frame-info.h"
#include "src/objects/synthetic-module.h"
#include "src/objects/template-objects.h"
#include "src/torque/runtime-support.h"

namespace v8 {
namespace internal {
namespace  {
class EnumVerifier {
  // UnicodeEncoding (src/builtins/base.tq:190:1)
  void VerifyEnum_UnicodeEncoding(UnicodeEncoding x) {
    switch(x) {
      case UnicodeEncoding::UTF16: break;
      case UnicodeEncoding::UTF32: break;
    }
  }

  // PromiseState (src/builtins/base.tq:193:1)
  void VerifyEnum_PromiseState(Promise::PromiseState x) {
    switch(x) {
      case Promise::PromiseState::kPending: break;
      case Promise::PromiseState::kFulfilled: break;
      case Promise::PromiseState::kRejected: break;
    }
  }

  // ElementsKind (src/builtins/base.tq:211:1)
  void VerifyEnum_ElementsKind(ElementsKind x) {
    switch(x) {
      case ElementsKind::NO_ELEMENTS: break;
      case ElementsKind::PACKED_SMI_ELEMENTS: break;
      case ElementsKind::HOLEY_SMI_ELEMENTS: break;
      case ElementsKind::PACKED_ELEMENTS: break;
      case ElementsKind::HOLEY_ELEMENTS: break;
      case ElementsKind::PACKED_DOUBLE_ELEMENTS: break;
      case ElementsKind::HOLEY_DOUBLE_ELEMENTS: break;
      case ElementsKind::LAST_ANY_NONEXTENSIBLE_ELEMENTS_KIND: break;
      case ElementsKind::DICTIONARY_ELEMENTS: break;
      case ElementsKind::UINT8_ELEMENTS: break;
      case ElementsKind::INT8_ELEMENTS: break;
      case ElementsKind::UINT16_ELEMENTS: break;
      case ElementsKind::INT16_ELEMENTS: break;
      case ElementsKind::UINT32_ELEMENTS: break;
      case ElementsKind::INT32_ELEMENTS: break;
      case ElementsKind::FLOAT32_ELEMENTS: break;
      case ElementsKind::FLOAT64_ELEMENTS: break;
      case ElementsKind::UINT8_CLAMPED_ELEMENTS: break;
      case ElementsKind::BIGUINT64_ELEMENTS: break;
      case ElementsKind::BIGINT64_ELEMENTS: break;
      default: break;
    }
  }

  // AllocationFlag (src/builtins/base.tq:237:1)
  void VerifyEnum_AllocationFlag(CodeStubAssembler::AllocationFlag x) {
    switch(x) {
      case CodeStubAssembler::AllocationFlag::kNone: break;
      case CodeStubAssembler::AllocationFlag::kDoubleAlignment: break;
      case CodeStubAssembler::AllocationFlag::kPretenured: break;
      case CodeStubAssembler::AllocationFlag::kAllowLargeObjectAllocation: break;
    }
  }

  // SlackTrackingMode (src/builtins/base.tq:245:1)
  void VerifyEnum_SlackTrackingMode(CodeStubAssembler::SlackTrackingMode x) {
    switch(x) {
      case CodeStubAssembler::SlackTrackingMode::kWithSlackTracking: break;
      case CodeStubAssembler::SlackTrackingMode::kNoSlackTracking: break;
    }
  }

  // ExtractFixedArrayFlag (src/builtins/base.tq:251:1)
  void VerifyEnum_ExtractFixedArrayFlag(CodeStubAssembler::ExtractFixedArrayFlag x) {
    switch(x) {
      case CodeStubAssembler::ExtractFixedArrayFlag::kFixedDoubleArrays: break;
      case CodeStubAssembler::ExtractFixedArrayFlag::kAllFixedArrays: break;
      case CodeStubAssembler::ExtractFixedArrayFlag::kFixedArrays: break;
      default: break;
    }
  }

  // MessageTemplate (src/builtins/base.tq:261:1)
  void VerifyEnum_MessageTemplate(MessageTemplate x) {
    switch(x) {
      case MessageTemplate::kAllPromisesRejected: break;
      case MessageTemplate::kInvalidArrayBufferLength: break;
      case MessageTemplate::kInvalidArrayLength: break;
      case MessageTemplate::kInvalidIndex: break;
      case MessageTemplate::kNotConstructor: break;
      case MessageTemplate::kNotGeneric: break;
      case MessageTemplate::kCalledNonCallable: break;
      case MessageTemplate::kCalledOnNullOrUndefined: break;
      case MessageTemplate::kCannotConvertToPrimitive: break;
      case MessageTemplate::kProtoObjectOrNull: break;
      case MessageTemplate::kInvalidOffset: break;
      case MessageTemplate::kInvalidTypedArrayLength: break;
      case MessageTemplate::kIteratorSymbolNonCallable: break;
      case MessageTemplate::kIteratorValueNotAnObject: break;
      case MessageTemplate::kNotIterable: break;
      case MessageTemplate::kReduceNoInitial: break;
      case MessageTemplate::kFirstArgumentNotRegExp: break;
      case MessageTemplate::kBigIntMixedTypes: break;
      case MessageTemplate::kTypedArrayTooShort: break;
      case MessageTemplate::kInvalidCountValue: break;
      case MessageTemplate::kConstructorNotFunction: break;
      case MessageTemplate::kSymbolToString: break;
      case MessageTemplate::kPropertyNotFunction: break;
      case MessageTemplate::kBigIntTooBig: break;
      case MessageTemplate::kNotTypedArray: break;
      case MessageTemplate::kDetachedOperation: break;
      case MessageTemplate::kBadSortComparisonFunction: break;
      case MessageTemplate::kIncompatibleMethodReceiver: break;
      case MessageTemplate::kInvalidDataViewAccessorOffset: break;
      case MessageTemplate::kTypedArraySetOffsetOutOfBounds: break;
      case MessageTemplate::kInvalidArgument: break;
      case MessageTemplate::kInvalidRegExpExecResult: break;
      case MessageTemplate::kRegExpNonRegExp: break;
      case MessageTemplate::kRegExpNonObject: break;
      case MessageTemplate::kPromiseNonCallable: break;
      case MessageTemplate::kNotAPromise: break;
      case MessageTemplate::kResolverNotAFunction: break;
      case MessageTemplate::kTooManyElementsInPromiseCombinator: break;
      case MessageTemplate::kToRadixFormatRange: break;
      case MessageTemplate::kCalledOnNonObject: break;
      case MessageTemplate::kRegExpGlobalInvokedOnNonGlobal: break;
      case MessageTemplate::kProxyNonObject: break;
      case MessageTemplate::kProxyRevoked: break;
      case MessageTemplate::kProxyTrapReturnedFalsishFor: break;
      case MessageTemplate::kProxyPrivate: break;
      case MessageTemplate::kProxyIsExtensibleInconsistent: break;
      case MessageTemplate::kProxyPreventExtensionsExtensible: break;
      case MessageTemplate::kProxyTrapReturnedFalsish: break;
      case MessageTemplate::kProxyGetPrototypeOfInvalid: break;
      case MessageTemplate::kProxyGetPrototypeOfNonExtensible: break;
      case MessageTemplate::kProxySetPrototypeOfNonExtensible: break;
      case MessageTemplate::kProxyDeletePropertyNonExtensible: break;
      case MessageTemplate::kUndefinedOrNullToObject: break;
      case MessageTemplate::kWeakRefsCleanupMustBeCallable: break;
      case MessageTemplate::kWasmTrapUnreachable: break;
      case MessageTemplate::kWasmTrapMemOutOfBounds: break;
      case MessageTemplate::kWasmTrapUnalignedAccess: break;
      case MessageTemplate::kWasmTrapDivByZero: break;
      case MessageTemplate::kWasmTrapDivUnrepresentable: break;
      case MessageTemplate::kWasmTrapRemByZero: break;
      case MessageTemplate::kWasmTrapFloatUnrepresentable: break;
      case MessageTemplate::kWasmTrapFuncInvalid: break;
      case MessageTemplate::kWasmTrapFuncSigMismatch: break;
      case MessageTemplate::kWasmTrapDataSegmentDropped: break;
      case MessageTemplate::kWasmTrapElemSegmentDropped: break;
      case MessageTemplate::kWasmTrapTableOutOfBounds: break;
      case MessageTemplate::kWasmTrapBrOnExnNull: break;
      case MessageTemplate::kWasmTrapRethrowNull: break;
      case MessageTemplate::kWasmTrapNullDereference: break;
      case MessageTemplate::kWasmTrapIllegalCast: break;
      case MessageTemplate::kWasmTrapArrayOutOfBounds: break;
      case MessageTemplate::kWeakRefsRegisterTargetAndHoldingsMustNotBeSame: break;
      case MessageTemplate::kWeakRefsRegisterTargetMustBeObject: break;
      case MessageTemplate::kWeakRefsUnregisterTokenMustBeObject: break;
      case MessageTemplate::kWeakRefsWeakRefConstructorTargetMustBeObject: break;
      default: break;
    }
  }

  // PropertyAttributes (src/builtins/base.tq:340:1)
  void VerifyEnum_PropertyAttributes(PropertyAttributes x) {
    switch(x) {
      case PropertyAttributes::NONE: break;
      case PropertyAttributes::READ_ONLY: break;
      case PropertyAttributes::DONT_ENUM: break;
      case PropertyAttributes::DONT_DELETE: break;
      case PropertyAttributes::ALL_ATTRIBUTES_MASK: break;
      case PropertyAttributes::FROZEN: break;
      default: break;
    }
  }

  // PrimitiveType (src/builtins/base.tq:387:1)
  void VerifyEnum_PrimitiveType(PrimitiveType x) {
    switch(x) {
      case PrimitiveType::kString: break;
      case PrimitiveType::kBoolean: break;
      case PrimitiveType::kSymbol: break;
      case PrimitiveType::kNumber: break;
    }
  }

  // LanguageMode (src/builtins/base.tq:443:1)
  void VerifyEnum_LanguageMode(LanguageMode x) {
    switch(x) {
      case LanguageMode::kStrict: break;
      case LanguageMode::kSloppy: break;
    }
  }

  // BigIntHandling (src/builtins/base.tq:526:1)
  void VerifyEnum_BigIntHandling(CodeStubAssembler::BigIntHandling x) {
    switch(x) {
      case CodeStubAssembler::BigIntHandling::kConvertToNumber: break;
      case CodeStubAssembler::BigIntHandling::kThrow: break;
    }
  }

  // AllocationSiteMode (src/builtins/constructor.tq:20:1)
  void VerifyEnum_AllocationSiteMode(AllocationSiteMode x) {
    switch(x) {
      case AllocationSiteMode::DONT_TRACK_ALLOCATION_SITE: break;
      case AllocationSiteMode::TRACK_ALLOCATION_SITE: break;
    }
  }

  // OrdinaryToPrimitiveHint (src/builtins/conversion.tq:9:1)
  void VerifyEnum_OrdinaryToPrimitiveHint(OrdinaryToPrimitiveHint x) {
    switch(x) {
      case OrdinaryToPrimitiveHint::kString: break;
      case OrdinaryToPrimitiveHint::kNumber: break;
    }
  }

  // Operation (src/builtins/number.tq:7:1)
  void VerifyEnum_Operation(Operation x) {
    switch(x) {
      case Operation::kAdd: break;
      case Operation::kSubtract: break;
      case Operation::kMultiply: break;
      case Operation::kDivide: break;
      case Operation::kModulus: break;
      case Operation::kExponentiate: break;
      case Operation::kBitwiseAnd: break;
      case Operation::kBitwiseOr: break;
      case Operation::kBitwiseXor: break;
      case Operation::kShiftLeft: break;
      case Operation::kShiftRight: break;
      case Operation::kShiftRightLogical: break;
      case Operation::kBitwiseNot: break;
      case Operation::kNegate: break;
      case Operation::kIncrement: break;
      case Operation::kDecrement: break;
      case Operation::kEqual: break;
      case Operation::kStrictEqual: break;
      case Operation::kLessThan: break;
      case Operation::kLessThanOrEqual: break;
      case Operation::kGreaterThan: break;
      case Operation::kGreaterThanOrEqual: break;
    }
  }

  // PromiseResolvingFunctionContextSlot (src/builtins/promise-abstract-operations.tq:257:1)
  void VerifyEnum_PromiseResolvingFunctionContextSlot(PromiseBuiltins::PromiseResolvingFunctionContextSlot x) {
    switch(x) {
      case PromiseBuiltins::PromiseResolvingFunctionContextSlot::kPromiseSlot: break;
      case PromiseBuiltins::PromiseResolvingFunctionContextSlot::kAlreadyResolvedSlot: break;
      case PromiseBuiltins::PromiseResolvingFunctionContextSlot::kDebugEventSlot: break;
      case PromiseBuiltins::PromiseResolvingFunctionContextSlot::kPromiseContextLength: break;
    }
  }

  // FunctionContextSlot (src/builtins/promise-abstract-operations.tq:266:1)
  void VerifyEnum_FunctionContextSlot(PromiseBuiltins::FunctionContextSlot x) {
    switch(x) {
      case PromiseBuiltins::FunctionContextSlot::kCapabilitySlot: break;
      case PromiseBuiltins::FunctionContextSlot::kCapabilitiesContextLength: break;
    }
  }

  // PromiseAllResolveElementContextSlots (src/builtins/promise-all-element-closure.tq:66:1)
  void VerifyEnum_PromiseAllResolveElementContextSlots(PromiseBuiltins::PromiseAllResolveElementContextSlots x) {
    switch(x) {
      case PromiseBuiltins::PromiseAllResolveElementContextSlots::kPromiseAllResolveElementRemainingSlot: break;
      case PromiseBuiltins::PromiseAllResolveElementContextSlots::kPromiseAllResolveElementCapabilitySlot: break;
      case PromiseBuiltins::PromiseAllResolveElementContextSlots::kPromiseAllResolveElementValuesSlot: break;
      case PromiseBuiltins::PromiseAllResolveElementContextSlots::kPromiseAllResolveElementLength: break;
    }
  }

  // PromiseAnyRejectElementContextSlots (src/builtins/promise-any.tq:9:1)
  void VerifyEnum_PromiseAnyRejectElementContextSlots(PromiseBuiltins::PromiseAnyRejectElementContextSlots x) {
    switch(x) {
      case PromiseBuiltins::PromiseAnyRejectElementContextSlots::kPromiseAnyRejectElementRemainingSlot: break;
      case PromiseBuiltins::PromiseAnyRejectElementContextSlots::kPromiseAnyRejectElementCapabilitySlot: break;
      case PromiseBuiltins::PromiseAnyRejectElementContextSlots::kPromiseAnyRejectElementErrorsSlot: break;
      case PromiseBuiltins::PromiseAnyRejectElementContextSlots::kPromiseAnyRejectElementLength: break;
    }
  }

  // PromiseValueThunkOrReasonContextSlot (src/builtins/promise-finally.tq:11:1)
  void VerifyEnum_PromiseValueThunkOrReasonContextSlot(PromiseBuiltins::PromiseValueThunkOrReasonContextSlot x) {
    switch(x) {
      case PromiseBuiltins::PromiseValueThunkOrReasonContextSlot::kValueSlot: break;
      case PromiseBuiltins::PromiseValueThunkOrReasonContextSlot::kPromiseValueThunkOrReasonContextLength: break;
    }
  }

  // PromiseFinallyContextSlot (src/builtins/promise-finally.tq:18:1)
  void VerifyEnum_PromiseFinallyContextSlot(PromiseBuiltins::PromiseFinallyContextSlot x) {
    switch(x) {
      case PromiseBuiltins::PromiseFinallyContextSlot::kOnFinallySlot: break;
      case PromiseBuiltins::PromiseFinallyContextSlot::kConstructorSlot: break;
      case PromiseBuiltins::PromiseFinallyContextSlot::kPromiseFinallyContextLength: break;
    }
  }

  // ProxyRevokeFunctionContextSlot (src/builtins/proxy.tq:28:1)
  void VerifyEnum_ProxyRevokeFunctionContextSlot(ProxiesCodeStubAssembler::ProxyRevokeFunctionContextSlot x) {
    switch(x) {
      case ProxiesCodeStubAssembler::ProxyRevokeFunctionContextSlot::kProxySlot: break;
      case ProxiesCodeStubAssembler::ProxyRevokeFunctionContextSlot::kProxyContextLength: break;
    }
  }

  // Flag (src/builtins/regexp.tq:180:1)
  void VerifyEnum_Flag(JSRegExp::Flag x) {
    switch(x) {
      case JSRegExp::Flag::kNone: break;
      case JSRegExp::Flag::kGlobal: break;
      case JSRegExp::Flag::kIgnoreCase: break;
      case JSRegExp::Flag::kMultiline: break;
      case JSRegExp::Flag::kSticky: break;
      case JSRegExp::Flag::kUnicode: break;
      case JSRegExp::Flag::kDotAll: break;
    }
  }

  // ContextSlot (src/objects/contexts.tq:86:1)
  void VerifyEnum_ContextSlot(Context::Field x) {
    switch(x) {
      case Context::Field::SCOPE_INFO_INDEX: break;
      case Context::Field::PREVIOUS_INDEX: break;
      case Context::Field::AGGREGATE_ERROR_FUNCTION_INDEX: break;
      case Context::Field::ARRAY_BUFFER_FUN_INDEX: break;
      case Context::Field::ARRAY_BUFFER_NOINIT_FUN_INDEX: break;
      case Context::Field::ARRAY_BUFFER_MAP_INDEX: break;
      case Context::Field::ARRAY_FUNCTION_INDEX: break;
      case Context::Field::ARRAY_JOIN_STACK_INDEX: break;
      case Context::Field::OBJECT_FUNCTION_INDEX: break;
      case Context::Field::ITERATOR_RESULT_MAP_INDEX: break;
      case Context::Field::JS_ARRAY_PACKED_ELEMENTS_MAP_INDEX: break;
      case Context::Field::JS_ARRAY_PACKED_SMI_ELEMENTS_MAP_INDEX: break;
      case Context::Field::MATH_RANDOM_CACHE_INDEX: break;
      case Context::Field::MATH_RANDOM_INDEX_INDEX: break;
      case Context::Field::NUMBER_FUNCTION_INDEX: break;
      case Context::Field::PROXY_REVOCABLE_RESULT_MAP_INDEX: break;
      case Context::Field::REFLECT_APPLY_INDEX: break;
      case Context::Field::REGEXP_FUNCTION_INDEX: break;
      case Context::Field::REGEXP_LAST_MATCH_INFO_INDEX: break;
      case Context::Field::INITIAL_STRING_ITERATOR_MAP_INDEX: break;
      case Context::Field::INITIAL_ARRAY_ITERATOR_MAP_INDEX: break;
      case Context::Field::SLOW_OBJECT_WITH_NULL_PROTOTYPE_MAP: break;
      case Context::Field::STRICT_ARGUMENTS_MAP_INDEX: break;
      case Context::Field::SLOPPY_ARGUMENTS_MAP_INDEX: break;
      case Context::Field::FAST_ALIASED_ARGUMENTS_MAP_INDEX: break;
      case Context::Field::FUNCTION_CONTEXT_MAP_INDEX: break;
      case Context::Field::PROMISE_FUNCTION_INDEX: break;
      case Context::Field::PROMISE_THEN_INDEX: break;
      case Context::Field::PROMISE_PROTOTYPE_INDEX: break;
      case Context::Field::STRICT_FUNCTION_WITHOUT_PROTOTYPE_MAP_INDEX: break;
      case Context::Field::CONTINUATION_PRESERVED_EMBEDDER_DATA_INDEX: break;
      case Context::Field::BOUND_FUNCTION_WITH_CONSTRUCTOR_MAP_INDEX: break;
      case Context::Field::BOUND_FUNCTION_WITHOUT_CONSTRUCTOR_MAP_INDEX: break;
      case Context::Field::MIN_CONTEXT_SLOTS: break;
      default: break;
    }
  }

  // IterationKind (src/objects/js-array.tq:5:1)
  void VerifyEnum_IterationKind(IterationKind x) {
    switch(x) {
      case IterationKind::kKeys: break;
      case IterationKind::kValues: break;
      case IterationKind::kEntries: break;
    }
  }

};
}  // namespace 
}  // namespace internal
}  // namespace v8
