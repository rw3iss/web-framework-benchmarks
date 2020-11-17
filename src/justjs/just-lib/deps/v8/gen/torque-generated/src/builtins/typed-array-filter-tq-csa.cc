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
#include "torque-generated/src/builtins/aggregate-error-tq-csa.h"
#include "torque-generated/src/builtins/array-copywithin-tq-csa.h"
#include "torque-generated/src/builtins/array-every-tq-csa.h"
#include "torque-generated/src/builtins/array-filter-tq-csa.h"
#include "torque-generated/src/builtins/array-find-tq-csa.h"
#include "torque-generated/src/builtins/array-findindex-tq-csa.h"
#include "torque-generated/src/builtins/array-foreach-tq-csa.h"
#include "torque-generated/src/builtins/array-from-tq-csa.h"
#include "torque-generated/src/builtins/array-isarray-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/array-lastindexof-tq-csa.h"
#include "torque-generated/src/builtins/array-map-tq-csa.h"
#include "torque-generated/src/builtins/array-of-tq-csa.h"
#include "torque-generated/src/builtins/array-reduce-right-tq-csa.h"
#include "torque-generated/src/builtins/array-reduce-tq-csa.h"
#include "torque-generated/src/builtins/array-reverse-tq-csa.h"
#include "torque-generated/src/builtins/array-shift-tq-csa.h"
#include "torque-generated/src/builtins/array-slice-tq-csa.h"
#include "torque-generated/src/builtins/array-some-tq-csa.h"
#include "torque-generated/src/builtins/array-splice-tq-csa.h"
#include "torque-generated/src/builtins/array-unshift-tq-csa.h"
#include "torque-generated/src/builtins/array-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/bigint-tq-csa.h"
#include "torque-generated/src/builtins/boolean-tq-csa.h"
#include "torque-generated/src/builtins/builtins-string-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/collections-tq-csa.h"
#include "torque-generated/src/builtins/constructor-tq-csa.h"
#include "torque-generated/src/builtins/conversion-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/console-tq-csa.h"
#include "torque-generated/src/builtins/data-view-tq-csa.h"
#include "torque-generated/src/builtins/finalization-registry-tq-csa.h"
#include "torque-generated/src/builtins/frames-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/function-tq-csa.h"
#include "torque-generated/src/builtins/growable-fixed-array-tq-csa.h"
#include "torque-generated/src/builtins/ic-callable-tq-csa.h"
#include "torque-generated/src/builtins/ic-tq-csa.h"
#include "torque-generated/src/builtins/internal-coverage-tq-csa.h"
#include "torque-generated/src/builtins/internal-tq-csa.h"
#include "torque-generated/src/builtins/iterator-tq-csa.h"
#include "torque-generated/src/builtins/math-tq-csa.h"
#include "torque-generated/src/builtins/number-tq-csa.h"
#include "torque-generated/src/builtins/object-fromentries-tq-csa.h"
#include "torque-generated/src/builtins/object-tq-csa.h"
#include "torque-generated/src/builtins/promise-abstract-operations-tq-csa.h"
#include "torque-generated/src/builtins/promise-all-tq-csa.h"
#include "torque-generated/src/builtins/promise-all-element-closure-tq-csa.h"
#include "torque-generated/src/builtins/promise-any-tq-csa.h"
#include "torque-generated/src/builtins/promise-constructor-tq-csa.h"
#include "torque-generated/src/builtins/promise-finally-tq-csa.h"
#include "torque-generated/src/builtins/promise-misc-tq-csa.h"
#include "torque-generated/src/builtins/promise-race-tq-csa.h"
#include "torque-generated/src/builtins/promise-reaction-job-tq-csa.h"
#include "torque-generated/src/builtins/promise-resolve-tq-csa.h"
#include "torque-generated/src/builtins/promise-then-tq-csa.h"
#include "torque-generated/src/builtins/promise-jobs-tq-csa.h"
#include "torque-generated/src/builtins/proxy-constructor-tq-csa.h"
#include "torque-generated/src/builtins/proxy-delete-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-get-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-get-prototype-of-tq-csa.h"
#include "torque-generated/src/builtins/proxy-has-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-is-extensible-tq-csa.h"
#include "torque-generated/src/builtins/proxy-prevent-extensions-tq-csa.h"
#include "torque-generated/src/builtins/proxy-revocable-tq-csa.h"
#include "torque-generated/src/builtins/proxy-revoke-tq-csa.h"
#include "torque-generated/src/builtins/proxy-set-property-tq-csa.h"
#include "torque-generated/src/builtins/proxy-set-prototype-of-tq-csa.h"
#include "torque-generated/src/builtins/proxy-tq-csa.h"
#include "torque-generated/src/builtins/reflect-tq-csa.h"
#include "torque-generated/src/builtins/regexp-exec-tq-csa.h"
#include "torque-generated/src/builtins/regexp-match-all-tq-csa.h"
#include "torque-generated/src/builtins/regexp-match-tq-csa.h"
#include "torque-generated/src/builtins/regexp-replace-tq-csa.h"
#include "torque-generated/src/builtins/regexp-search-tq-csa.h"
#include "torque-generated/src/builtins/regexp-source-tq-csa.h"
#include "torque-generated/src/builtins/regexp-split-tq-csa.h"
#include "torque-generated/src/builtins/regexp-test-tq-csa.h"
#include "torque-generated/src/builtins/regexp-tq-csa.h"
#include "torque-generated/src/builtins/string-endswith-tq-csa.h"
#include "torque-generated/src/builtins/string-html-tq-csa.h"
#include "torque-generated/src/builtins/string-iterator-tq-csa.h"
#include "torque-generated/src/builtins/string-pad-tq-csa.h"
#include "torque-generated/src/builtins/string-repeat-tq-csa.h"
#include "torque-generated/src/builtins/string-replaceall-tq-csa.h"
#include "torque-generated/src/builtins/string-slice-tq-csa.h"
#include "torque-generated/src/builtins/string-startswith-tq-csa.h"
#include "torque-generated/src/builtins/string-substring-tq-csa.h"
#include "torque-generated/src/builtins/string-substr-tq-csa.h"
#include "torque-generated/src/builtins/symbol-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-createtypedarray-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-every-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-entries-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-filter-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-find-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-findindex-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-foreach-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-from-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-keys-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-of-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-reduce-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-reduceright-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-set-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-slice-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-some-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-sort-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-subarray-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-values-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-tq-csa.h"
#include "torque-generated/src/builtins/wasm-tq-csa.h"
#include "torque-generated/src/builtins/weak-ref-tq-csa.h"
#include "torque-generated/src/ic/handler-configuration-tq-csa.h"
#include "torque-generated/src/objects/allocation-site-tq-csa.h"
#include "torque-generated/src/objects/api-callbacks-tq-csa.h"
#include "torque-generated/src/objects/arguments-tq-csa.h"
#include "torque-generated/src/objects/cell-tq-csa.h"
#include "torque-generated/src/objects/code-tq-csa.h"
#include "torque-generated/src/objects/contexts-tq-csa.h"
#include "torque-generated/src/objects/data-handler-tq-csa.h"
#include "torque-generated/src/objects/debug-objects-tq-csa.h"
#include "torque-generated/src/objects/descriptor-array-tq-csa.h"
#include "torque-generated/src/objects/embedder-data-array-tq-csa.h"
#include "torque-generated/src/objects/feedback-cell-tq-csa.h"
#include "torque-generated/src/objects/feedback-vector-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/foreign-tq-csa.h"
#include "torque-generated/src/objects/free-space-tq-csa.h"
#include "torque-generated/src/objects/heap-number-tq-csa.h"
#include "torque-generated/src/objects/heap-object-tq-csa.h"
#include "torque-generated/src/objects/js-array-buffer-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"
#include "torque-generated/src/objects/js-collection-iterator-tq-csa.h"
#include "torque-generated/src/objects/js-collection-tq-csa.h"
#include "torque-generated/src/objects/js-generator-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"
#include "torque-generated/src/objects/js-promise-tq-csa.h"
#include "torque-generated/src/objects/js-proxy-tq-csa.h"
#include "torque-generated/src/objects/js-regexp-string-iterator-tq-csa.h"
#include "torque-generated/src/objects/js-regexp-tq-csa.h"
#include "torque-generated/src/objects/js-weak-refs-tq-csa.h"
#include "torque-generated/src/objects/literal-objects-tq-csa.h"
#include "torque-generated/src/objects/map-tq-csa.h"
#include "torque-generated/src/objects/microtask-tq-csa.h"
#include "torque-generated/src/objects/module-tq-csa.h"
#include "torque-generated/src/objects/name-tq-csa.h"
#include "torque-generated/src/objects/oddball-tq-csa.h"
#include "torque-generated/src/objects/ordered-hash-table-tq-csa.h"
#include "torque-generated/src/objects/primitive-heap-object-tq-csa.h"
#include "torque-generated/src/objects/promise-tq-csa.h"
#include "torque-generated/src/objects/property-array-tq-csa.h"
#include "torque-generated/src/objects/property-cell-tq-csa.h"
#include "torque-generated/src/objects/property-descriptor-object-tq-csa.h"
#include "torque-generated/src/objects/prototype-info-tq-csa.h"
#include "torque-generated/src/objects/regexp-match-info-tq-csa.h"
#include "torque-generated/src/objects/scope-info-tq-csa.h"
#include "torque-generated/src/objects/script-tq-csa.h"
#include "torque-generated/src/objects/shared-function-info-tq-csa.h"
#include "torque-generated/src/objects/source-text-module-tq-csa.h"
#include "torque-generated/src/objects/stack-frame-info-tq-csa.h"
#include "torque-generated/src/objects/string-tq-csa.h"
#include "torque-generated/src/objects/struct-tq-csa.h"
#include "torque-generated/src/objects/synthetic-module-tq-csa.h"
#include "torque-generated/src/objects/template-objects-tq-csa.h"
#include "torque-generated/src/objects/template-tq-csa.h"
#include "torque-generated/src/wasm/wasm-objects-tq-csa.h"
#include "torque-generated/test/torque/test-torque-tq-csa.h"
#include "torque-generated/third_party/v8/builtins/array-sort-tq-csa.h"

namespace v8 {
namespace internal {

const char* kBuiltinNameFilter_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return "%TypedArray%.prototype.filter";
}

TF_BUILTIN(TypedArrayPrototypeFilter, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  Node* argc = Parameter(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = arguments.GetReceiver();
USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSTypedArray, UintPtrT> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSTypedArray, UintPtrT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSTypedArray, UintPtrT> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSTypedArray, UintPtrT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, UintPtrT> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, UintPtrT> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, UintPtrT> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, UintPtrT> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, JSTypedArray, UintPtrT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSTypedArray_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kNotTypedArray, kBuiltinNameFilter_0(state_));
  }

  TNode<JSTypedArray> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = EnsureAttached_0(state_, TNode<JSTypedArray>{tmp0}, &label3);
    ca_.Goto(&block7);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block2);
  }

  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Object> tmp7;
  TNode<JSReceiver> tmp8;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp5 = CodeStubAssembler(state_).LoadReference<UintPtrT>(CodeStubAssembler::Reference{tmp2, tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp7 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp6});
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7}, &label9);
    ca_.Goto(&block11);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block12);
    }
  }

  TNode<IntPtrT> tmp10;
  TNode<Object> tmp11;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp11 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp10});
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kCalledNonCallable, TNode<Object>{tmp11});
  }

  TNode<IntPtrT> tmp12;
  TNode<Object> tmp13;
  TNode<FixedArray> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<JSTypedArray> tmp17;
  TNode<JSTypedArray> tmp18;
  TNode<BuiltinPtr> tmp19;
  TNode<UintPtrT> tmp20;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp13 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp12});
    std::tie(tmp14, tmp15, tmp16) = NewGrowableFixedArray_0(state_).Flatten();
    std::tie(tmp17, tmp18, tmp19) = NewAttachedJSTypedArrayWitness_0(state_, TNode<JSTypedArray>{tmp2}).Flatten();
    tmp20 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block15, tmp14, tmp15, tmp16, tmp18, tmp20);
  }

  TNode<FixedArray> phi_bb15_10;
  TNode<IntPtrT> phi_bb15_11;
  TNode<IntPtrT> phi_bb15_12;
  TNode<JSTypedArray> phi_bb15_14;
  TNode<UintPtrT> phi_bb15_16;
  TNode<BoolT> tmp21;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_10, &phi_bb15_11, &phi_bb15_12, &phi_bb15_14, &phi_bb15_16);
    tmp21 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb15_16}, TNode<UintPtrT>{tmp5});
    ca_.Branch(tmp21, &block13, std::vector<Node*>{phi_bb15_10, phi_bb15_11, phi_bb15_12, phi_bb15_14, phi_bb15_16}, &block14, std::vector<Node*>{phi_bb15_10, phi_bb15_11, phi_bb15_12, phi_bb15_14, phi_bb15_16});
  }

  TNode<FixedArray> phi_bb13_10;
  TNode<IntPtrT> phi_bb13_11;
  TNode<IntPtrT> phi_bb13_12;
  TNode<JSTypedArray> phi_bb13_14;
  TNode<UintPtrT> phi_bb13_16;
  TNode<IntPtrT> tmp22;
  TNode<JSArrayBuffer> tmp23;
  TNode<BoolT> tmp24;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_10, &phi_bb13_11, &phi_bb13_12, &phi_bb13_14, &phi_bb13_16);
    tmp22 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp23 = CodeStubAssembler(state_).LoadReference<JSArrayBuffer>(CodeStubAssembler::Reference{tmp17, tmp22});
    tmp24 = IsDetachedBuffer_0(state_, TNode<JSArrayBuffer>{tmp23});
    ca_.Branch(tmp24, &block18, std::vector<Node*>{phi_bb13_10, phi_bb13_11, phi_bb13_12, phi_bb13_14, phi_bb13_16}, &block19, std::vector<Node*>{phi_bb13_10, phi_bb13_11, phi_bb13_12, phi_bb13_14, phi_bb13_16});
  }

  TNode<FixedArray> phi_bb18_10;
  TNode<IntPtrT> phi_bb18_11;
  TNode<IntPtrT> phi_bb18_12;
  TNode<JSTypedArray> phi_bb18_14;
  TNode<UintPtrT> phi_bb18_16;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_10, &phi_bb18_11, &phi_bb18_12, &phi_bb18_14, &phi_bb18_16);
    ca_.Goto(&block2);
  }

  TNode<FixedArray> phi_bb19_10;
  TNode<IntPtrT> phi_bb19_11;
  TNode<IntPtrT> phi_bb19_12;
  TNode<JSTypedArray> phi_bb19_14;
  TNode<UintPtrT> phi_bb19_16;
  TNode<JSTypedArray> tmp25;
  TNode<Numeric> tmp26;
  TNode<Number> tmp27;
  TNode<Object> tmp28;
  TNode<BoolT> tmp29;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_10, &phi_bb19_11, &phi_bb19_12, &phi_bb19_14, &phi_bb19_16);
    tmp25 = (TNode<JSTypedArray>{tmp17});
tmp26 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallableFor(ca_.isolate(),ExampleBuiltinForTorqueFunctionPointerType(1)).descriptor(), tmp19, TNode<Object>(), tmp25, phi_bb19_16));
    tmp27 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{phi_bb19_16});
    tmp28 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<Object>{tmp8}, TNode<Object>{tmp13}, TNode<Object>{tmp26}, TNode<Object>{tmp27}, TNode<Object>{tmp17});
    tmp29 = ToBoolean_0(state_, TNode<Object>{tmp28});
    ca_.Branch(tmp29, &block22, std::vector<Node*>{phi_bb19_10, phi_bb19_11, phi_bb19_12, phi_bb19_16}, &block23, std::vector<Node*>{phi_bb19_10, phi_bb19_11, phi_bb19_12, phi_bb19_16});
  }

  TNode<FixedArray> phi_bb22_10;
  TNode<IntPtrT> phi_bb22_11;
  TNode<IntPtrT> phi_bb22_12;
  TNode<UintPtrT> phi_bb22_16;
  TNode<BoolT> tmp30;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_10, &phi_bb22_11, &phi_bb22_12, &phi_bb22_16);
    tmp30 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb22_11}, TNode<IntPtrT>{phi_bb22_12});
    ca_.Branch(tmp30, &block30, std::vector<Node*>{phi_bb22_10, phi_bb22_11, phi_bb22_12, phi_bb22_16}, &block31, std::vector<Node*>{phi_bb22_10, phi_bb22_11, phi_bb22_12, phi_bb22_16});
  }

  TNode<FixedArray> phi_bb30_10;
  TNode<IntPtrT> phi_bb30_11;
  TNode<IntPtrT> phi_bb30_12;
  TNode<UintPtrT> phi_bb30_16;
  TNode<IntPtrT> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<FixedArray> tmp37;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_10, &phi_bb30_11, &phi_bb30_12, &phi_bb30_16);
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp32 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb30_11}, TNode<IntPtrT>{tmp31});
    tmp33 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb30_11}, TNode<IntPtrT>{tmp32});
    tmp34 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp35 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp33}, TNode<IntPtrT>{tmp34});
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp37 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb30_10}, TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{phi_bb30_12}, TNode<IntPtrT>{tmp35});
    ca_.Goto(&block31, tmp37, tmp35, phi_bb30_12, phi_bb30_16);
  }

  TNode<FixedArray> phi_bb31_10;
  TNode<IntPtrT> phi_bb31_11;
  TNode<IntPtrT> phi_bb31_12;
  TNode<UintPtrT> phi_bb31_16;
  TNode<IntPtrT> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<Smi> tmp41;
  TNode<IntPtrT> tmp42;
  TNode<IntPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<UintPtrT> tmp45;
  TNode<UintPtrT> tmp46;
  TNode<BoolT> tmp47;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_10, &phi_bb31_11, &phi_bb31_12, &phi_bb31_16);
    tmp38 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp39 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp40 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp41 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{phi_bb31_10, tmp40});
    tmp42 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp41});
    tmp43 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp44 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb31_12}, TNode<IntPtrT>{tmp43});
    tmp45 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb31_12});
    tmp46 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp42});
    tmp47 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp45}, TNode<UintPtrT>{tmp46});
    ca_.Branch(tmp47, &block49, std::vector<Node*>{phi_bb31_16, phi_bb31_12, phi_bb31_12, phi_bb31_12, phi_bb31_12}, &block50, std::vector<Node*>{phi_bb31_16, phi_bb31_12, phi_bb31_12, phi_bb31_12, phi_bb31_12});
  }

  TNode<UintPtrT> phi_bb49_16;
  TNode<IntPtrT> phi_bb49_25;
  TNode<IntPtrT> phi_bb49_26;
  TNode<IntPtrT> phi_bb49_30;
  TNode<IntPtrT> phi_bb49_31;
  TNode<IntPtrT> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<HeapObject> tmp51;
  TNode<IntPtrT> tmp52;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_16, &phi_bb49_25, &phi_bb49_26, &phi_bb49_30, &phi_bb49_31);
    tmp48 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp49 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{phi_bb49_31}, TNode<IntPtrT>{tmp48});
    tmp50 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp38}, TNode<IntPtrT>{tmp49});
    std::tie(tmp51, tmp52) = NewReference_Object_0(state_, TNode<HeapObject>{phi_bb31_10}, TNode<IntPtrT>{tmp50}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp51, tmp52}, tmp26);
    ca_.Goto(&block23, phi_bb31_10, phi_bb31_11, tmp44, phi_bb49_16);
  }

  TNode<UintPtrT> phi_bb50_16;
  TNode<IntPtrT> phi_bb50_25;
  TNode<IntPtrT> phi_bb50_26;
  TNode<IntPtrT> phi_bb50_30;
  TNode<IntPtrT> phi_bb50_31;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_16, &phi_bb50_25, &phi_bb50_26, &phi_bb50_30, &phi_bb50_31);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb23_10;
  TNode<IntPtrT> phi_bb23_11;
  TNode<IntPtrT> phi_bb23_12;
  TNode<UintPtrT> phi_bb23_16;
  TNode<UintPtrT> tmp53;
  TNode<UintPtrT> tmp54;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_10, &phi_bb23_11, &phi_bb23_12, &phi_bb23_16);
    tmp53 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp54 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb23_16}, TNode<UintPtrT>{tmp53});
    ca_.Goto(&block15, phi_bb23_10, phi_bb23_11, phi_bb23_12, tmp25, tmp54);
  }

  TNode<FixedArray> phi_bb14_10;
  TNode<IntPtrT> phi_bb14_11;
  TNode<IntPtrT> phi_bb14_12;
  TNode<JSTypedArray> phi_bb14_14;
  TNode<UintPtrT> phi_bb14_16;
  TNode<UintPtrT> tmp55;
  TNode<JSTypedArray> tmp56;
  TNode<UintPtrT> tmp57;
  TNode<Number> tmp58;
  TNode<NativeContext> tmp59;
  TNode<Map> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<FixedArray> tmp62;
  TNode<Smi> tmp63;
  TNode<JSArray> tmp64;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_10, &phi_bb14_11, &phi_bb14_12, &phi_bb14_14, &phi_bb14_16);
    tmp55 = CodeStubAssembler(state_).Unsigned(TNode<IntPtrT>{phi_bb14_12});
    tmp56 = TypedArraySpeciesCreateByLength_0(state_, TNode<Context>{parameter0}, kBuiltinNameFilter_0(state_), TNode<JSTypedArray>{tmp0}, TNode<UintPtrT>{tmp55});
    tmp57 = CodeStubAssembler(state_).Unsigned(TNode<IntPtrT>{phi_bb14_12});
    tmp58 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{tmp57});
    tmp59 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{parameter0});
    tmp60 = CodeStubAssembler(state_).LoadJSArrayElementsMap(ElementsKind::PACKED_ELEMENTS, TNode<NativeContext>{tmp59});
    tmp61 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp62 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb14_10}, TNode<IntPtrT>{tmp61}, TNode<IntPtrT>{phi_bb14_12}, TNode<IntPtrT>{phi_bb14_12});
    tmp63 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb14_12});
    tmp64 = CodeStubAssembler(state_).AllocateJSArray(TNode<Map>{tmp60}, TNode<FixedArrayBase>{tmp62}, TNode<Smi>{tmp63});
    CodeStubAssembler(state_).CallRuntime(Runtime::kTypedArrayCopyElements, parameter0, tmp56, tmp64, tmp58);
    arguments.PopAndReturn(tmp56);
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kDetachedOperation, kBuiltinNameFilter_0(state_));
  }
}

}  // namespace internal
}  // namespace v8

