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

TNode<SortState> Cast_SortState_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<SortState> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = DownCastForTorqueClass_SortState_0(state_, TNode<HeapObject>{p_obj}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(label_CastError);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
  return TNode<SortState>{tmp0};
}

TNode<IntPtrT> CalculateWorkArrayLength_0(compiler::CodeAssemblerState* state_, TNode<JSReceiver> p_receiver, TNode<Number> p_initialReceiverLength) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, IntPtrT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, IntPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<UintPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = ChangeSafeIntegerNumberToUintPtr_0(state_, TNode<Number>{p_initialReceiverLength}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<UintPtrT> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, kSmiMaxValue);
    ca_.Goto(&block2, tmp2);
  }

  TNode<UintPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, kSmiMaxValue);
    tmp4 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp0}, TNode<UintPtrT>{tmp3});
    ca_.Branch(tmp4, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{tmp0});
  }

  TNode<UintPtrT> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp5 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, kSmiMaxValue);
    ca_.Goto(&block7, tmp5);
  }

  TNode<UintPtrT> phi_bb7_2;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_2);
    ca_.Goto(&block2, phi_bb7_2);
  }

  TNode<UintPtrT> phi_bb2_2;
  TNode<IntPtrT> tmp6;
  TNode<JSObject> tmp7;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_2);
    tmp6 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb2_2});
    compiler::CodeAssemblerLabel label8(&ca_);
    tmp7 = Cast_JSObject_0(state_, TNode<HeapObject>{p_receiver}, &label8);
    ca_.Goto(&block10, phi_bb2_2);
    if (label8.is_used()) {
      ca_.Bind(&label8);
      ca_.Goto(&block11, phi_bb2_2);
    }
  }

  TNode<UintPtrT> phi_bb11_2;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_2);
    ca_.Goto(&block8, phi_bb11_2, tmp6);
  }

  TNode<UintPtrT> phi_bb10_2;
  TNode<IntPtrT> tmp9;
  TNode<FixedArrayBase> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Smi> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_2);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp10 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp7, tmp9});
    tmp11 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp12 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp10, tmp11});
    tmp13 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp12});
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp15 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp14});
    ca_.Branch(tmp15, &block12, std::vector<Node*>{phi_bb10_2}, &block13, std::vector<Node*>{phi_bb10_2, tmp6});
  }

  TNode<UintPtrT> phi_bb12_2;
  TNode<IntPtrT> tmp16;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_2);
    tmp16 = CodeStubAssembler(state_).IntPtrMin(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp13});
    ca_.Goto(&block13, phi_bb12_2, tmp16);
  }

  TNode<UintPtrT> phi_bb13_2;
  TNode<IntPtrT> phi_bb13_3;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_2, &phi_bb13_3);
    ca_.Goto(&block8, phi_bb13_2, phi_bb13_3);
  }

  TNode<UintPtrT> phi_bb8_2;
  TNode<IntPtrT> phi_bb8_3;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_2, &phi_bb8_3);
    ca_.Goto(&block14, phi_bb8_3);
  }

  TNode<IntPtrT> phi_bb14_2;
    ca_.Bind(&block14, &phi_bb14_2);
  return TNode<IntPtrT>{phi_bb14_2};
}

TNode<SortState> NewSortState_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver, TNode<HeapObject> p_comparefn, TNode<Number> p_initialReceiverLength) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, BuiltinPtr, BuiltinPtr, BuiltinPtr> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, BuiltinPtr, BuiltinPtr, BuiltinPtr> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, BuiltinPtr, BuiltinPtr, BuiltinPtr> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Oddball> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Undefined_0(state_);
    tmp1 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{p_comparefn}, TNode<HeapObject>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ca_.Goto(&block4, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kSortCompareUserFn)));
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block4, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kSortCompareDefault)));
  }

  TNode<BuiltinPtr> phi_bb4_4;
  TNode<IntPtrT> tmp2;
  TNode<Map> tmp3;
  TNode<JSArray> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_4);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp3 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_receiver, tmp2});
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{p_receiver}, &label5);
    ca_.Goto(&block8);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block9);
    }
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block6, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoad_GenericElementsAccessor_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStore_GenericElementsAccessor_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kDelete_GenericElementsAccessor_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kCanUseSameAccessor_GenericElementsAccessor_0)));
  }

  TNode<Int32T> tmp6;
  TNode<BoolT> tmp7;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    EnsureWriteableFastElements_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp4});
    tmp6 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp3});
    tmp7 = CodeStubAssembler(state_).IsDoubleElementsKind(TNode<Int32T>{tmp6});
    ca_.Branch(tmp7, &block10, std::vector<Node*>{}, &block11, std::vector<Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block12, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoad_FastDoubleElements_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStore_FastDoubleElements_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kDelete_FastDoubleElements_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kCanUseSameAccessor_FastDoubleElements_0)));
  }

  TNode<BoolT> tmp8;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp8 = CodeStubAssembler(state_).IsFastSmiElementsKind(TNode<Int32T>{tmp6});
    ca_.Branch(tmp8, &block13, std::vector<Node*>{}, &block14, std::vector<Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block15, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoad_FastSmiElements_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStore_FastSmiElements_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kDelete_FastSmiElements_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kCanUseSameAccessor_FastSmiElements_0)));
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block15, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoad_FastObjectElements_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStore_FastObjectElements_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kDelete_FastObjectElements_0)), ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kCanUseSameAccessor_FastObjectElements_0)));
  }

  TNode<BuiltinPtr> phi_bb15_6;
  TNode<BuiltinPtr> phi_bb15_7;
  TNode<BuiltinPtr> phi_bb15_8;
  TNode<BuiltinPtr> phi_bb15_9;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_6, &phi_bb15_7, &phi_bb15_8, &phi_bb15_9);
    ca_.Goto(&block12, phi_bb15_6, phi_bb15_7, phi_bb15_8, phi_bb15_9);
  }

  TNode<BuiltinPtr> phi_bb12_6;
  TNode<BuiltinPtr> phi_bb12_7;
  TNode<BuiltinPtr> phi_bb12_8;
  TNode<BuiltinPtr> phi_bb12_9;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_6, &phi_bb12_7, &phi_bb12_8, &phi_bb12_9);
    ca_.Goto(&block6, phi_bb12_6, phi_bb12_7, phi_bb12_8, phi_bb12_9);
  }

  TNode<BuiltinPtr> phi_bb6_6;
  TNode<BuiltinPtr> phi_bb6_7;
  TNode<BuiltinPtr> phi_bb6_8;
  TNode<BuiltinPtr> phi_bb6_9;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<FixedArray> tmp11;
  TNode<FixedArray> tmp12;
  TNode<FixedArray> tmp13;
  TNode<Map> tmp14;
  TNode<BoolT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<HeapObject> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Smi> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<Smi> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<Smi> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<Smi> tmp38;
  TNode<SortState> tmp39;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_6, &phi_bb6_7, &phi_bb6_8, &phi_bb6_9);
    tmp9 = CalculateWorkArrayLength_0(state_, TNode<JSReceiver>{p_receiver}, TNode<Number>{p_initialReceiverLength});
    tmp10 = Convert_intptr_constexpr_int31_0(state_, kMaxMergePending_0(state_));
    tmp11 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp10});
    tmp12 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp9});
    tmp13 = kEmptyFixedArray_0(state_);
    tmp14 = CodeStubAssembler(state_).GetInstanceTypeMap(SORT_STATE_TYPE);
    tmp15 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 68);
    tmp17 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp16}, TNode<Map>{tmp14}, TNode<BoolT>{tmp15});
    tmp18 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp17, tmp18}, tmp14);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{tmp17, tmp19}, p_receiver);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp17, tmp20}, tmp3);
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{tmp17, tmp21}, p_initialReceiverLength);
    tmp22 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<HeapObject>(CodeStubAssembler::Reference{tmp17, tmp22}, p_comparefn);
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{tmp17, tmp23}, phi_bb4_4);
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{tmp17, tmp24}, phi_bb6_6);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{tmp17, tmp25}, phi_bb6_7);
    tmp26 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{tmp17, tmp26}, phi_bb6_8);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{tmp17, tmp27}, phi_bb6_9);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp29 = FromConstexpr_Smi_constexpr_int31_0(state_, kMinGallopWins_0(state_));
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp17, tmp28}, tmp29);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    tmp31 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp17, tmp30}, tmp31);
    tmp32 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp17, tmp32}, tmp11);
    tmp33 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp17, tmp33}, tmp12);
    tmp34 = FromConstexpr_intptr_constexpr_int31_0(state_, 56);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp17, tmp34}, tmp13);
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, 60);
    tmp36 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp17, tmp35}, tmp36);
    tmp37 = FromConstexpr_intptr_constexpr_int31_0(state_, 64);
    tmp38 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp17, tmp37}, tmp38);
    tmp39 = TORQUE_CAST(TNode<HeapObject>{tmp17});
    ca_.Goto(&block16);
  }

    ca_.Bind(&block16);
  return TNode<SortState>{tmp39};
}

TNode<Smi> kSuccess_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<Smi> tmp0;
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
  return TNode<Smi>{tmp0};
}

int31_t kMaxMergePending_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return 85;
}

int31_t kMinGallopWins_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return 7;
}

TNode<Smi> kSortStateTempSize_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<Smi> tmp0;
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 32);
  return TNode<Smi>{tmp0};
}

TF_BUILTIN(Load_FastSmiElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Smi> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp12 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp14 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp12}, TNode<UintPtrT>{tmp13});
    ca_.Branch(tmp14, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<HeapObject> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Object> tmp20;
  TNode<Object> tmp21;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp16 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp15});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_Object_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp18, tmp19});
    tmp21 = UnsafeCast_JSReceiver_OR_Undefined_OR_Null_OR_False_OR_True_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_Smi_OR_TheHole_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp20});
    CodeStubAssembler(state_).Return(tmp21);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(Load_FastObjectElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Smi> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp12 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp14 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp12}, TNode<UintPtrT>{tmp13});
    ca_.Branch(tmp14, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<HeapObject> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Object> tmp20;
  TNode<Object> tmp21;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp16 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp15});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_Object_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp18, tmp19});
    tmp21 = UnsafeCast_JSReceiver_OR_Undefined_OR_Null_OR_False_OR_True_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_Smi_OR_TheHole_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp20});
    CodeStubAssembler(state_).Return(tmp21);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(Load_FastDoubleElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedDoubleArray> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Smi> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp12 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp14 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp12}, TNode<UintPtrT>{tmp13});
    ca_.Branch(tmp14, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<HeapObject> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<BoolT> tmp20;
  TNode<Float64T> tmp21;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, kDoubleSize);
    tmp16 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp15});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_float64_or_hole_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp17}).Flatten();
    std::tie(tmp20, tmp21) = LoadFloat64OrHole_0(state_, TorqueStructReference_float64_or_hole_0{TNode<HeapObject>{tmp18}, TNode<IntPtrT>{tmp19}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Branch(tmp20, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Oddball> tmp22;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp22 = TheHole_0(state_);
    CodeStubAssembler(state_).Return(tmp22);
  }

  TNode<HeapNumber> tmp23;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp23 = CodeStubAssembler(state_).AllocateHeapNumberWithValue(TNode<Float64T>{tmp21});
    CodeStubAssembler(state_).Return(tmp23);
  }
}

TF_BUILTIN(Store_FastSmiElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    CodeStubAssembler(state_).StoreFixedArrayElement(TNode<FixedArray>{tmp5}, TNode<Smi>{parameter2}, TNode<Smi>{tmp6}, SKIP_WRITE_BARRIER);
    tmp7 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp7);
  }
}

TF_BUILTIN(Store_FastObjectElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Smi> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp12 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp14 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp12}, TNode<UintPtrT>{tmp13});
    ca_.Branch(tmp14, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<HeapObject> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Smi> tmp20;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp16 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp15});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_Object_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp17}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp18, tmp19}, parameter3);
    tmp20 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp20);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(Store_FastDoubleElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedDoubleArray> tmp5;
  TNode<HeapNumber> tmp6;
  TNode<Float64T> tmp7;
  TNode<Smi> tmp8;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = UnsafeCast_HeapNumber_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    tmp7 = Convert_float64_HeapNumber_0(state_, TNode<HeapNumber>{tmp6});
    CodeStubAssembler(state_).StoreFixedDoubleArrayElementSmi(TNode<FixedDoubleArray>{tmp5}, TNode<Smi>{parameter2}, TNode<Float64T>{tmp7});
    tmp8 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp8);
  }
}

TF_BUILTIN(Delete_FastSmiElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Smi> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp12 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp14 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp12}, TNode<UintPtrT>{tmp13});
    ca_.Branch(tmp14, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<HeapObject> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Oddball> tmp20;
  TNode<Smi> tmp21;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp16 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp15});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_Object_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp18, tmp19}, tmp20);
    tmp21 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp21);
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(Delete_FastObjectElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Smi> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp12 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp14 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp12}, TNode<UintPtrT>{tmp13});
    ca_.Branch(tmp14, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<HeapObject> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Oddball> tmp20;
  TNode<Smi> tmp21;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp16 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp15});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_Object_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp18, tmp19}, tmp20);
    tmp21 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp21);
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(Delete_FastDoubleElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedDoubleArray> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Smi> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp12 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp14 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp12}, TNode<UintPtrT>{tmp13});
    ca_.Branch(tmp14, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<HeapObject> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<BoolT> tmp20;
  TNode<Float64T> tmp21;
  TNode<Smi> tmp22;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, kDoubleSize);
    tmp16 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp15});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_float64_or_hole_0(state_, TNode<HeapObject>{tmp5}, TNode<IntPtrT>{tmp17}).Flatten();
    std::tie(tmp20, tmp21) = kDoubleHole_0(state_).Flatten();
    StoreFloat64OrHole_0(state_, TorqueStructReference_float64_or_hole_0{TNode<HeapObject>{tmp18}, TNode<IntPtrT>{tmp19}, TorqueStructUnsafe_0{}}, TorqueStructfloat64_or_hole_0{TNode<BoolT>{tmp20}, TNode<Float64T>{tmp21}});
    tmp22 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp22);
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(SortCompareDefault, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{parameter2});
    ca_.Branch(tmp0, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<BoolT> tmp1;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp1 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{parameter3});
    ca_.Goto(&block9, tmp1);
  }

  TNode<BoolT> tmp2;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block9, tmp2);
  }

  TNode<BoolT> phi_bb9_5;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_5);
    ca_.Branch(phi_bb9_5, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  TNode<Smi> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp3 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2});
    tmp4 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    tmp5 = CodeStubAssembler(state_).SmiLexicographicCompare(TNode<Smi>{tmp3}, TNode<Smi>{tmp4});
    CodeStubAssembler(state_).Return(tmp5);
  }

  TNode<String> tmp6;
  TNode<String> tmp7;
  TNode<Oddball> tmp8;
  TNode<Oddball> tmp9;
  TNode<BoolT> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp6 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter2});
    tmp7 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter3});
    tmp8 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kStringLessThan, parameter0, tmp6, tmp7));
    tmp9 = True_0(state_);
    tmp10 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp8}, TNode<HeapObject>{tmp9});
    ca_.Branch(tmp10, &block10, std::vector<Node*>{}, &block11, std::vector<Node*>{});
  }

  TNode<Number> tmp11;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp11 = FromConstexpr_Number_constexpr_int31_0(state_, -1);
    CodeStubAssembler(state_).Return(tmp11);
  }

  TNode<Oddball> tmp12;
  TNode<Oddball> tmp13;
  TNode<BoolT> tmp14;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp12 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kStringLessThan, parameter0, tmp7, tmp6));
    tmp13 = True_0(state_);
    tmp14 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp12}, TNode<HeapObject>{tmp13});
    ca_.Branch(tmp14, &block12, std::vector<Node*>{}, &block13, std::vector<Node*>{});
  }

  TNode<Number> tmp15;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp15 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    CodeStubAssembler(state_).Return(tmp15);
  }

  TNode<Number> tmp16;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp16 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).Return(tmp16);
  }
}

TF_BUILTIN(SortCompareUserFn, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<Oddball> tmp1;
  TNode<Object> tmp2;
  TNode<Number> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_Callable_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Undefined_0(state_);
    tmp2 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<Object>{tmp0}, TNode<Object>{tmp1}, TNode<Object>{parameter2}, TNode<Object>{parameter3});
    tmp3 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{tmp2});
    tmp4 = NumberIsNaN_0(state_, TNode<Number>{tmp3});
    ca_.Branch(tmp4, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  TNode<Number> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp5 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).Return(tmp5);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(CanUseSameAccessor_GenericElementsAccessor_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Map> parameter2 = UncheckedCast<Map>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Number> parameter3 = UncheckedCast<Number>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Oddball> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = True_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TNode<Smi> GetPendingRunsSize_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp0});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<Smi>{tmp1};
}

TNode<Smi> GetPendingRunBase_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<BoolT> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_pendingRuns, tmp2});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{p_run}, 1);
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp5});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp9 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp7}, TNode<UintPtrT>{tmp8});
    ca_.Branch(tmp9, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<HeapObject> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Object> tmp15;
  TNode<Smi> tmp16;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp11 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp10});
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_Object_0(state_, TNode<HeapObject>{p_pendingRuns}, TNode<IntPtrT>{tmp12}).Flatten();
    tmp15 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp13, tmp14});
    tmp16 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp15});
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
  return TNode<Smi>{tmp16};
}

void SetPendingRunBase_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run, TNode<Smi> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<BoolT> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_pendingRuns, tmp2});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{p_run}, 1);
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp5});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp9 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp7}, TNode<UintPtrT>{tmp8});
    ca_.Branch(tmp9, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<HeapObject> tmp13;
  TNode<IntPtrT> tmp14;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp11 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp10});
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_Object_0(state_, TNode<HeapObject>{p_pendingRuns}, TNode<IntPtrT>{tmp12}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp13, tmp14}, p_value);
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
}

TNode<Smi> GetPendingRunLength_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<BoolT> tmp11;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_pendingRuns, tmp2});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{p_run}, 1);
    tmp6 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp7 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp5}, TNode<Smi>{tmp6});
    tmp8 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp7});
    tmp9 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp11 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp9}, TNode<UintPtrT>{tmp10});
    ca_.Branch(tmp11, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<HeapObject> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<Object> tmp17;
  TNode<Smi> tmp18;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp13 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp12});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp13});
    std::tie(tmp15, tmp16) = NewReference_Object_0(state_, TNode<HeapObject>{p_pendingRuns}, TNode<IntPtrT>{tmp14}).Flatten();
    tmp17 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp15, tmp16});
    tmp18 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp17});
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
  return TNode<Smi>{tmp18};
}

void SetPendingRunLength_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run, TNode<Smi> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<BoolT> tmp11;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_pendingRuns, tmp2});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{p_run}, 1);
    tmp6 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp7 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp5}, TNode<Smi>{tmp6});
    tmp8 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp7});
    tmp9 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp11 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp9}, TNode<UintPtrT>{tmp10});
    ca_.Branch(tmp11, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<HeapObject> tmp15;
  TNode<IntPtrT> tmp16;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp13 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp12});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp13});
    std::tie(tmp15, tmp16) = NewReference_Object_0(state_, TNode<HeapObject>{p_pendingRuns}, TNode<IntPtrT>{tmp14}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp15, tmp16}, p_value);
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
}

void PushRun_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_base, TNode<Smi> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<FixedArray> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<Smi> tmp4;
  TNode<Smi> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetPendingRunsSize_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp2 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp1});
    SetPendingRunBase_0(state_, TNode<FixedArray>{tmp2}, TNode<Smi>{tmp0}, TNode<Smi>{p_base});
    SetPendingRunLength_0(state_, TNode<FixedArray>{tmp2}, TNode<Smi>{tmp0}, TNode<Smi>{p_length});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    tmp4 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp5 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp0}, TNode<Smi>{tmp4});
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp3}, tmp5);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
}

TNode<FixedArray> GetTempArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_requestedSize) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<FixedArray> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Smi> tmp5;
  TNode<BoolT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = kSortStateTempSize_0(state_);
    tmp1 = CodeStubAssembler(state_).SmiMax(TNode<Smi>{tmp0}, TNode<Smi>{p_requestedSize});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 56);
    tmp3 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp2});
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp5 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp3, tmp4});
    tmp6 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp5}, TNode<Smi>{tmp1});
    ca_.Branch(tmp6, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp7;
  TNode<FixedArray> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 56);
    tmp8 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp7});
    ca_.Goto(&block1, tmp8);
  }

  TNode<IntPtrT> tmp9;
  TNode<FixedArray> tmp10;
  TNode<IntPtrT> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp9 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp1});
    tmp10 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp9});
    tmp11 = FromConstexpr_intptr_constexpr_int31_0(state_, 56);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp11}, tmp10);
    ca_.Goto(&block1, tmp10);
  }

  TNode<FixedArray> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<FixedArray>{phi_bb1_3};
}

TF_BUILTIN(Copy, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<FixedArray> parameter1 = UncheckedCast<FixedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<FixedArray> parameter3 = UncheckedCast<FixedArray>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  TNode<Smi> parameter4 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<3>()));
  USE(parameter4);
  TNode<Smi> parameter5 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<4>()));
  USE(parameter5);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{parameter2}, TNode<Smi>{parameter4});
    ca_.Branch(tmp0, &block17, std::vector<Node*>{}, &block18, std::vector<Node*>{});
  }

  TNode<Smi> tmp1;
  TNode<Smi> tmp2;
  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp1 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{parameter5});
    tmp2 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp3 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp1}, TNode<Smi>{tmp2});
    tmp4 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter5});
    tmp5 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp6 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp4}, TNode<Smi>{tmp5});
    ca_.Goto(&block22, tmp3, tmp6);
  }

  TNode<Smi> phi_bb22_6;
  TNode<Smi> phi_bb22_7;
  TNode<BoolT> tmp7;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_6, &phi_bb22_7);
    tmp7 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb22_6}, TNode<Smi>{parameter2});
    ca_.Branch(tmp7, &block20, std::vector<Node*>{phi_bb22_6, phi_bb22_7}, &block21, std::vector<Node*>{phi_bb22_6, phi_bb22_7});
  }

  TNode<Smi> phi_bb20_6;
  TNode<Smi> phi_bb20_7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Smi> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Smi> tmp13;
  TNode<Smi> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<UintPtrT> tmp16;
  TNode<UintPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_6, &phi_bb20_7);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp11 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter3, tmp10});
    tmp12 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp11});
    tmp13 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp14 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb20_7}, TNode<Smi>{tmp13});
    tmp15 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb20_7});
    tmp16 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp15});
    tmp17 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp12});
    tmp18 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp16}, TNode<UintPtrT>{tmp17});
    ca_.Branch(tmp18, &block27, std::vector<Node*>{phi_bb20_6, phi_bb20_7, phi_bb20_7}, &block28, std::vector<Node*>{phi_bb20_6, phi_bb20_7, phi_bb20_7});
  }

  TNode<Smi> phi_bb27_6;
  TNode<Smi> phi_bb27_12;
  TNode<Smi> phi_bb27_13;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<HeapObject> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<Smi> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Smi> tmp29;
  TNode<Smi> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<BoolT> tmp34;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_6, &phi_bb27_12, &phi_bb27_13);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp20 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp15}, TNode<IntPtrT>{tmp19});
    tmp21 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp20});
    std::tie(tmp22, tmp23) = NewReference_Object_0(state_, TNode<HeapObject>{parameter3}, TNode<IntPtrT>{tmp21}).Flatten();
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp26 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp27 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp26});
    tmp28 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp27});
    tmp29 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp30 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb27_6}, TNode<Smi>{tmp29});
    tmp31 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb27_6});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp28});
    tmp34 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp32}, TNode<UintPtrT>{tmp33});
    ca_.Branch(tmp34, &block34, std::vector<Node*>{phi_bb27_12, phi_bb27_13, phi_bb27_6, phi_bb27_6}, &block35, std::vector<Node*>{phi_bb27_12, phi_bb27_13, phi_bb27_6, phi_bb27_6});
  }

  TNode<Smi> phi_bb28_6;
  TNode<Smi> phi_bb28_12;
  TNode<Smi> phi_bb28_13;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_6, &phi_bb28_12, &phi_bb28_13);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb34_12;
  TNode<Smi> phi_bb34_13;
  TNode<Smi> phi_bb34_20;
  TNode<Smi> phi_bb34_21;
  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<HeapObject> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<Object> tmp40;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_12, &phi_bb34_13, &phi_bb34_20, &phi_bb34_21);
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp36 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp31}, TNode<IntPtrT>{tmp35});
    tmp37 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp24}, TNode<IntPtrT>{tmp36});
    std::tie(tmp38, tmp39) = NewReference_Object_0(state_, TNode<HeapObject>{parameter1}, TNode<IntPtrT>{tmp37}).Flatten();
    tmp40 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp38, tmp39});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp22, tmp23}, tmp40);
    ca_.Goto(&block22, tmp30, tmp14);
  }

  TNode<Smi> phi_bb35_12;
  TNode<Smi> phi_bb35_13;
  TNode<Smi> phi_bb35_20;
  TNode<Smi> phi_bb35_21;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_12, &phi_bb35_13, &phi_bb35_20, &phi_bb35_21);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb21_6;
  TNode<Smi> phi_bb21_7;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_6, &phi_bb21_7);
    ca_.Goto(&block19);
  }

  TNode<Smi> tmp41;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp41 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{parameter5});
    ca_.Goto(&block39, parameter2, parameter4);
  }

  TNode<Smi> phi_bb39_6;
  TNode<Smi> phi_bb39_7;
  TNode<BoolT> tmp42;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_6, &phi_bb39_7);
    tmp42 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb39_6}, TNode<Smi>{tmp41});
    ca_.Branch(tmp42, &block37, std::vector<Node*>{phi_bb39_6, phi_bb39_7}, &block38, std::vector<Node*>{phi_bb39_6, phi_bb39_7});
  }

  TNode<Smi> phi_bb37_6;
  TNode<Smi> phi_bb37_7;
  TNode<IntPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<Smi> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<Smi> tmp48;
  TNode<Smi> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<UintPtrT> tmp51;
  TNode<UintPtrT> tmp52;
  TNode<BoolT> tmp53;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_6, &phi_bb37_7);
    tmp43 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp44 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp46 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter3, tmp45});
    tmp47 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp46});
    tmp48 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp49 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb37_7}, TNode<Smi>{tmp48});
    tmp50 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb37_7});
    tmp51 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp50});
    tmp52 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp47});
    tmp53 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp51}, TNode<UintPtrT>{tmp52});
    ca_.Branch(tmp53, &block44, std::vector<Node*>{phi_bb37_6, phi_bb37_7, phi_bb37_7}, &block45, std::vector<Node*>{phi_bb37_6, phi_bb37_7, phi_bb37_7});
  }

  TNode<Smi> phi_bb44_6;
  TNode<Smi> phi_bb44_13;
  TNode<Smi> phi_bb44_14;
  TNode<IntPtrT> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<IntPtrT> tmp56;
  TNode<HeapObject> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<IntPtrT> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<Smi> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<Smi> tmp64;
  TNode<Smi> tmp65;
  TNode<IntPtrT> tmp66;
  TNode<UintPtrT> tmp67;
  TNode<UintPtrT> tmp68;
  TNode<BoolT> tmp69;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_6, &phi_bb44_13, &phi_bb44_14);
    tmp54 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp55 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp50}, TNode<IntPtrT>{tmp54});
    tmp56 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp43}, TNode<IntPtrT>{tmp55});
    std::tie(tmp57, tmp58) = NewReference_Object_0(state_, TNode<HeapObject>{parameter3}, TNode<IntPtrT>{tmp56}).Flatten();
    tmp59 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp60 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp61 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp62 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp61});
    tmp63 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp62});
    tmp64 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp65 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb44_6}, TNode<Smi>{tmp64});
    tmp66 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb44_6});
    tmp67 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp66});
    tmp68 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp63});
    tmp69 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp67}, TNode<UintPtrT>{tmp68});
    ca_.Branch(tmp69, &block51, std::vector<Node*>{phi_bb44_13, phi_bb44_14, phi_bb44_6, phi_bb44_6}, &block52, std::vector<Node*>{phi_bb44_13, phi_bb44_14, phi_bb44_6, phi_bb44_6});
  }

  TNode<Smi> phi_bb45_6;
  TNode<Smi> phi_bb45_13;
  TNode<Smi> phi_bb45_14;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_6, &phi_bb45_13, &phi_bb45_14);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb51_13;
  TNode<Smi> phi_bb51_14;
  TNode<Smi> phi_bb51_21;
  TNode<Smi> phi_bb51_22;
  TNode<IntPtrT> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<HeapObject> tmp73;
  TNode<IntPtrT> tmp74;
  TNode<Object> tmp75;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_13, &phi_bb51_14, &phi_bb51_21, &phi_bb51_22);
    tmp70 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp71 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp66}, TNode<IntPtrT>{tmp70});
    tmp72 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp59}, TNode<IntPtrT>{tmp71});
    std::tie(tmp73, tmp74) = NewReference_Object_0(state_, TNode<HeapObject>{parameter1}, TNode<IntPtrT>{tmp72}).Flatten();
    tmp75 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp73, tmp74});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp57, tmp58}, tmp75);
    ca_.Goto(&block39, tmp65, tmp49);
  }

  TNode<Smi> phi_bb52_13;
  TNode<Smi> phi_bb52_14;
  TNode<Smi> phi_bb52_21;
  TNode<Smi> phi_bb52_22;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_13, &phi_bb52_14, &phi_bb52_21, &phi_bb52_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb38_6;
  TNode<Smi> phi_bb38_7;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_6, &phi_bb38_7);
    ca_.Goto(&block19);
  }

  TNode<Smi> tmp76;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp76 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp76);
  }
}

void BinaryInsertionSort_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_low, TNode<Smi> p_startArg, TNode<Smi> p_high) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block70(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{p_low}, TNode<Smi>{p_startArg});
    ca_.Branch(tmp2, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp3 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp4 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_startArg}, TNode<Smi>{tmp3});
    ca_.Goto(&block11, tmp4);
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block11, p_startArg);
  }

  TNode<Smi> phi_bb11_6;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_6);
    ca_.Goto(&block15, phi_bb11_6);
  }

  TNode<Smi> phi_bb15_6;
  TNode<BoolT> tmp5;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_6);
    tmp5 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb15_6}, TNode<Smi>{p_high});
    ca_.Branch(tmp5, &block13, std::vector<Node*>{phi_bb15_6}, &block14, std::vector<Node*>{phi_bb15_6});
  }

  TNode<Smi> phi_bb13_6;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Smi> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb13_6});
    tmp12 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp14 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp12}, TNode<UintPtrT>{tmp13});
    ca_.Branch(tmp14, &block21, std::vector<Node*>{phi_bb13_6, phi_bb13_6, phi_bb13_6, phi_bb13_6}, &block22, std::vector<Node*>{phi_bb13_6, phi_bb13_6, phi_bb13_6, phi_bb13_6});
  }

  TNode<Smi> phi_bb21_6;
  TNode<Smi> phi_bb21_8;
  TNode<Smi> phi_bb21_13;
  TNode<Smi> phi_bb21_14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<HeapObject> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Object> tmp20;
  TNode<Object> tmp21;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_6, &phi_bb21_8, &phi_bb21_13, &phi_bb21_14);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp16 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp15});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp18, tmp19});
    tmp21 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp20});
    ca_.Goto(&block30, phi_bb21_6, p_low, phi_bb21_8);
  }

  TNode<Smi> phi_bb22_6;
  TNode<Smi> phi_bb22_8;
  TNode<Smi> phi_bb22_13;
  TNode<Smi> phi_bb22_14;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_6, &phi_bb22_8, &phi_bb22_13, &phi_bb22_14);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb30_6;
  TNode<Smi> phi_bb30_7;
  TNode<Smi> phi_bb30_8;
  TNode<BoolT> tmp22;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_6, &phi_bb30_7, &phi_bb30_8);
    tmp22 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb30_7}, TNode<Smi>{phi_bb30_8});
    ca_.Branch(tmp22, &block28, std::vector<Node*>{phi_bb30_6, phi_bb30_7, phi_bb30_8}, &block29, std::vector<Node*>{phi_bb30_6, phi_bb30_7, phi_bb30_8});
  }

  TNode<Smi> phi_bb28_6;
  TNode<Smi> phi_bb28_7;
  TNode<Smi> phi_bb28_8;
  TNode<Smi> tmp23;
  TNode<Smi> tmp24;
  TNode<Smi> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Smi> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<BoolT> tmp34;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_6, &phi_bb28_7, &phi_bb28_8);
    tmp23 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb28_8}, TNode<Smi>{phi_bb28_7});
    tmp24 = CodeStubAssembler(state_).SmiSar(TNode<Smi>{tmp23}, 1);
    tmp25 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb28_7}, TNode<Smi>{tmp24});
    tmp26 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp29 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp28});
    tmp30 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp29});
    tmp31 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp25});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp30});
    tmp34 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp32}, TNode<UintPtrT>{tmp33});
    ca_.Branch(tmp34, &block35, std::vector<Node*>{phi_bb28_6, phi_bb28_7, phi_bb28_8}, &block36, std::vector<Node*>{phi_bb28_6, phi_bb28_7, phi_bb28_8});
  }

  TNode<Smi> phi_bb35_6;
  TNode<Smi> phi_bb35_7;
  TNode<Smi> phi_bb35_8;
  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<HeapObject> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<Object> tmp40;
  TNode<Object> tmp41;
  TNode<Number> tmp42;
  TNode<Number> tmp43;
  TNode<BoolT> tmp44;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_6, &phi_bb35_7, &phi_bb35_8);
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp36 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp31}, TNode<IntPtrT>{tmp35});
    tmp37 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp26}, TNode<IntPtrT>{tmp36});
    std::tie(tmp38, tmp39) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp37}).Flatten();
    tmp40 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp38, tmp39});
    tmp41 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp40});
    tmp42 = Method_SortState_Compare_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Object>{tmp21}, TNode<Object>{tmp41});
    tmp43 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp44 = NumberIsLessThan_0(state_, TNode<Number>{tmp42}, TNode<Number>{tmp43});
    ca_.Branch(tmp44, &block38, std::vector<Node*>{phi_bb35_6, phi_bb35_7, phi_bb35_8}, &block39, std::vector<Node*>{phi_bb35_6, phi_bb35_7, phi_bb35_8});
  }

  TNode<Smi> phi_bb36_6;
  TNode<Smi> phi_bb36_7;
  TNode<Smi> phi_bb36_8;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_6, &phi_bb36_7, &phi_bb36_8);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb38_6;
  TNode<Smi> phi_bb38_7;
  TNode<Smi> phi_bb38_8;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_6, &phi_bb38_7, &phi_bb38_8);
    ca_.Goto(&block40, phi_bb38_6, phi_bb38_7, tmp25);
  }

  TNode<Smi> phi_bb39_6;
  TNode<Smi> phi_bb39_7;
  TNode<Smi> phi_bb39_8;
  TNode<Smi> tmp45;
  TNode<Smi> tmp46;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_6, &phi_bb39_7, &phi_bb39_8);
    tmp45 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp46 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp25}, TNode<Smi>{tmp45});
    ca_.Goto(&block40, phi_bb39_6, tmp46, phi_bb39_8);
  }

  TNode<Smi> phi_bb40_6;
  TNode<Smi> phi_bb40_7;
  TNode<Smi> phi_bb40_8;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_6, &phi_bb40_7, &phi_bb40_8);
    ca_.Goto(&block30, phi_bb40_6, phi_bb40_7, phi_bb40_8);
  }

  TNode<Smi> phi_bb29_6;
  TNode<Smi> phi_bb29_7;
  TNode<Smi> phi_bb29_8;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_6, &phi_bb29_7, &phi_bb29_8);
    ca_.Goto(&block47, phi_bb29_6, phi_bb29_7, phi_bb29_8, phi_bb29_6);
  }

  TNode<Smi> phi_bb47_6;
  TNode<Smi> phi_bb47_7;
  TNode<Smi> phi_bb47_8;
  TNode<Smi> phi_bb47_10;
  TNode<BoolT> tmp47;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_6, &phi_bb47_7, &phi_bb47_8, &phi_bb47_10);
    tmp47 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb47_10}, TNode<Smi>{phi_bb47_7});
    ca_.Branch(tmp47, &block45, std::vector<Node*>{phi_bb47_6, phi_bb47_7, phi_bb47_8, phi_bb47_10}, &block46, std::vector<Node*>{phi_bb47_6, phi_bb47_7, phi_bb47_8, phi_bb47_10});
  }

  TNode<Smi> phi_bb45_6;
  TNode<Smi> phi_bb45_7;
  TNode<Smi> phi_bb45_8;
  TNode<Smi> phi_bb45_10;
  TNode<IntPtrT> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<Smi> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<UintPtrT> tmp54;
  TNode<UintPtrT> tmp55;
  TNode<BoolT> tmp56;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_6, &phi_bb45_7, &phi_bb45_8, &phi_bb45_10);
    tmp48 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp49 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp50 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp51 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp50});
    tmp52 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp51});
    tmp53 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb45_10});
    tmp54 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp53});
    tmp55 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp52});
    tmp56 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp54}, TNode<UintPtrT>{tmp55});
    ca_.Branch(tmp56, &block53, std::vector<Node*>{phi_bb45_6, phi_bb45_7, phi_bb45_8, phi_bb45_10, phi_bb45_10, phi_bb45_10}, &block54, std::vector<Node*>{phi_bb45_6, phi_bb45_7, phi_bb45_8, phi_bb45_10, phi_bb45_10, phi_bb45_10});
  }

  TNode<Smi> phi_bb53_6;
  TNode<Smi> phi_bb53_7;
  TNode<Smi> phi_bb53_8;
  TNode<Smi> phi_bb53_10;
  TNode<Smi> phi_bb53_15;
  TNode<Smi> phi_bb53_16;
  TNode<IntPtrT> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<IntPtrT> tmp59;
  TNode<HeapObject> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<Smi> tmp65;
  TNode<IntPtrT> tmp66;
  TNode<Smi> tmp67;
  TNode<Smi> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<UintPtrT> tmp70;
  TNode<UintPtrT> tmp71;
  TNode<BoolT> tmp72;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_6, &phi_bb53_7, &phi_bb53_8, &phi_bb53_10, &phi_bb53_15, &phi_bb53_16);
    tmp57 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp58 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp53}, TNode<IntPtrT>{tmp57});
    tmp59 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp48}, TNode<IntPtrT>{tmp58});
    std::tie(tmp60, tmp61) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp59}).Flatten();
    tmp62 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp63 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp64 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp65 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp64});
    tmp66 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp65});
    tmp67 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp68 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb53_10}, TNode<Smi>{tmp67});
    tmp69 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp68});
    tmp70 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp69});
    tmp71 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp66});
    tmp72 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp70}, TNode<UintPtrT>{tmp71});
    ca_.Branch(tmp72, &block60, std::vector<Node*>{phi_bb53_6, phi_bb53_7, phi_bb53_8, phi_bb53_10, phi_bb53_15, phi_bb53_16}, &block61, std::vector<Node*>{phi_bb53_6, phi_bb53_7, phi_bb53_8, phi_bb53_10, phi_bb53_15, phi_bb53_16});
  }

  TNode<Smi> phi_bb54_6;
  TNode<Smi> phi_bb54_7;
  TNode<Smi> phi_bb54_8;
  TNode<Smi> phi_bb54_10;
  TNode<Smi> phi_bb54_15;
  TNode<Smi> phi_bb54_16;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_6, &phi_bb54_7, &phi_bb54_8, &phi_bb54_10, &phi_bb54_15, &phi_bb54_16);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb60_6;
  TNode<Smi> phi_bb60_7;
  TNode<Smi> phi_bb60_8;
  TNode<Smi> phi_bb60_10;
  TNode<Smi> phi_bb60_15;
  TNode<Smi> phi_bb60_16;
  TNode<IntPtrT> tmp73;
  TNode<IntPtrT> tmp74;
  TNode<IntPtrT> tmp75;
  TNode<HeapObject> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<Object> tmp78;
  TNode<Smi> tmp79;
  TNode<Smi> tmp80;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_6, &phi_bb60_7, &phi_bb60_8, &phi_bb60_10, &phi_bb60_15, &phi_bb60_16);
    tmp73 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp74 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp69}, TNode<IntPtrT>{tmp73});
    tmp75 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp62}, TNode<IntPtrT>{tmp74});
    std::tie(tmp76, tmp77) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp75}).Flatten();
    tmp78 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp76, tmp77});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp60, tmp61}, tmp78);
    tmp79 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp80 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb60_10}, TNode<Smi>{tmp79});
    ca_.Goto(&block47, phi_bb60_6, phi_bb60_7, phi_bb60_8, tmp80);
  }

  TNode<Smi> phi_bb61_6;
  TNode<Smi> phi_bb61_7;
  TNode<Smi> phi_bb61_8;
  TNode<Smi> phi_bb61_10;
  TNode<Smi> phi_bb61_15;
  TNode<Smi> phi_bb61_16;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_6, &phi_bb61_7, &phi_bb61_8, &phi_bb61_10, &phi_bb61_15, &phi_bb61_16);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb46_6;
  TNode<Smi> phi_bb46_7;
  TNode<Smi> phi_bb46_8;
  TNode<Smi> phi_bb46_10;
  TNode<IntPtrT> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<IntPtrT> tmp83;
  TNode<Smi> tmp84;
  TNode<IntPtrT> tmp85;
  TNode<IntPtrT> tmp86;
  TNode<UintPtrT> tmp87;
  TNode<UintPtrT> tmp88;
  TNode<BoolT> tmp89;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_6, &phi_bb46_7, &phi_bb46_8, &phi_bb46_10);
    tmp81 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp82 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp83 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp84 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp83});
    tmp85 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp84});
    tmp86 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb46_7});
    tmp87 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp86});
    tmp88 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp85});
    tmp89 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp87}, TNode<UintPtrT>{tmp88});
    ca_.Branch(tmp89, &block67, std::vector<Node*>{phi_bb46_6, phi_bb46_7, phi_bb46_8, phi_bb46_7, phi_bb46_7}, &block68, std::vector<Node*>{phi_bb46_6, phi_bb46_7, phi_bb46_8, phi_bb46_7, phi_bb46_7});
  }

  TNode<Smi> phi_bb67_6;
  TNode<Smi> phi_bb67_7;
  TNode<Smi> phi_bb67_8;
  TNode<Smi> phi_bb67_14;
  TNode<Smi> phi_bb67_15;
  TNode<IntPtrT> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<IntPtrT> tmp92;
  TNode<HeapObject> tmp93;
  TNode<IntPtrT> tmp94;
  TNode<Smi> tmp95;
  TNode<Smi> tmp96;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_6, &phi_bb67_7, &phi_bb67_8, &phi_bb67_14, &phi_bb67_15);
    tmp90 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp91 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp86}, TNode<IntPtrT>{tmp90});
    tmp92 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp81}, TNode<IntPtrT>{tmp91});
    std::tie(tmp93, tmp94) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp92}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp93, tmp94}, tmp21);
    tmp95 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp96 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb67_6}, TNode<Smi>{tmp95});
    ca_.Goto(&block15, tmp96);
  }

  TNode<Smi> phi_bb68_6;
  TNode<Smi> phi_bb68_7;
  TNode<Smi> phi_bb68_8;
  TNode<Smi> phi_bb68_14;
  TNode<Smi> phi_bb68_15;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_6, &phi_bb68_7, &phi_bb68_8, &phi_bb68_14, &phi_bb68_15);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb14_6;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_6);
    ca_.Goto(&block70);
  }

    ca_.Bind(&block70);
}

TNode<Smi> CountAndMakeRun_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_lowArg, TNode<Smi> p_high) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, Object, Smi> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, Object, Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, Object, Smi, Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, Object, Smi, Smi, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Object, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Object, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Object, Smi> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Object, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Object, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Object, Smi> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Object, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, Object, Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, Object> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, Object> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  TNode<Smi> tmp2;
  TNode<Smi> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp3 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_lowArg}, TNode<Smi>{tmp2});
    tmp4 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp3}, TNode<Smi>{p_high});
    ca_.Branch(tmp4, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<Smi> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp5 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    ca_.Goto(&block1, tmp5);
  }

  TNode<Smi> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<Smi> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<UintPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp6 = FromConstexpr_Smi_constexpr_int31_0(state_, 2);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp10 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp9});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp10});
    tmp12 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp12});
    tmp14 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp15 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp13}, TNode<UintPtrT>{tmp14});
    ca_.Branch(tmp15, &block12, std::vector<Node*>{}, &block13, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<HeapObject> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Object> tmp21;
  TNode<Object> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<Smi> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<Smi> tmp28;
  TNode<Smi> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<UintPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<BoolT> tmp33;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp17 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp12}, TNode<IntPtrT>{tmp16});
    tmp18 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp7}, TNode<IntPtrT>{tmp17});
    std::tie(tmp19, tmp20) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp18}).Flatten();
    tmp21 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp19, tmp20});
    tmp22 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp21});
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp26 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp25});
    tmp27 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp26});
    tmp28 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp29 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp3}, TNode<Smi>{tmp28});
    tmp30 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp29});
    tmp31 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp30});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp27});
    tmp33 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp31}, TNode<UintPtrT>{tmp32});
    ca_.Branch(tmp33, &block19, std::vector<Node*>{}, &block20, std::vector<Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<HeapObject> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<Object> tmp39;
  TNode<Object> tmp40;
  TNode<Number> tmp41;
  TNode<Number> tmp42;
  TNode<BoolT> tmp43;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp34 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp35 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp30}, TNode<IntPtrT>{tmp34});
    tmp36 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp23}, TNode<IntPtrT>{tmp35});
    std::tie(tmp37, tmp38) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp36}).Flatten();
    tmp39 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp37, tmp38});
    tmp40 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp39});
    tmp41 = Method_SortState_Compare_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Object>{tmp22}, TNode<Object>{tmp40});
    tmp42 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp43 = NumberIsLessThan_0(state_, TNode<Number>{tmp41}, TNode<Number>{tmp42});
    ca_.Branch(tmp43, &block22, std::vector<Node*>{}, &block23, std::vector<Node*>{});
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> tmp44;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp44 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block24, tmp44);
  }

  TNode<BoolT> tmp45;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp45 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block24, tmp45);
  }

  TNode<BoolT> phi_bb24_10;
  TNode<Smi> tmp46;
  TNode<Smi> tmp47;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_10);
    tmp46 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp47 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp3}, TNode<Smi>{tmp46});
    ca_.Goto(&block28, tmp6, tmp41, tmp22, tmp47);
  }

  TNode<Smi> phi_bb28_6;
  TNode<Number> phi_bb28_9;
  TNode<Object> phi_bb28_11;
  TNode<Smi> phi_bb28_12;
  TNode<BoolT> tmp48;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_6, &phi_bb28_9, &phi_bb28_11, &phi_bb28_12);
    tmp48 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb28_12}, TNode<Smi>{p_high});
    ca_.Branch(tmp48, &block26, std::vector<Node*>{phi_bb28_6, phi_bb28_9, phi_bb28_11, phi_bb28_12}, &block27, std::vector<Node*>{phi_bb28_6, phi_bb28_9, phi_bb28_11, phi_bb28_12});
  }

  TNode<Smi> phi_bb26_6;
  TNode<Number> phi_bb26_9;
  TNode<Object> phi_bb26_11;
  TNode<Smi> phi_bb26_12;
  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<IntPtrT> tmp51;
  TNode<Smi> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<UintPtrT> tmp55;
  TNode<UintPtrT> tmp56;
  TNode<BoolT> tmp57;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_6, &phi_bb26_9, &phi_bb26_11, &phi_bb26_12);
    tmp49 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp50 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp51 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp52 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp51});
    tmp53 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp52});
    tmp54 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb26_12});
    tmp55 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp54});
    tmp56 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp53});
    tmp57 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp55}, TNode<UintPtrT>{tmp56});
    ca_.Branch(tmp57, &block34, std::vector<Node*>{phi_bb26_6, phi_bb26_9, phi_bb26_11, phi_bb26_12, phi_bb26_12, phi_bb26_12}, &block35, std::vector<Node*>{phi_bb26_6, phi_bb26_9, phi_bb26_11, phi_bb26_12, phi_bb26_12, phi_bb26_12});
  }

  TNode<Smi> phi_bb34_6;
  TNode<Number> phi_bb34_9;
  TNode<Object> phi_bb34_11;
  TNode<Smi> phi_bb34_12;
  TNode<Smi> phi_bb34_17;
  TNode<Smi> phi_bb34_18;
  TNode<IntPtrT> tmp58;
  TNode<IntPtrT> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<HeapObject> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<Object> tmp63;
  TNode<Object> tmp64;
  TNode<Number> tmp65;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_6, &phi_bb34_9, &phi_bb34_11, &phi_bb34_12, &phi_bb34_17, &phi_bb34_18);
    tmp58 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp59 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp54}, TNode<IntPtrT>{tmp58});
    tmp60 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp49}, TNode<IntPtrT>{tmp59});
    std::tie(tmp61, tmp62) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp60}).Flatten();
    tmp63 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp61, tmp62});
    tmp64 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp63});
    tmp65 = Method_SortState_Compare_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Object>{tmp64}, TNode<Object>{phi_bb34_11});
    ca_.Branch(phi_bb24_10, &block37, std::vector<Node*>{phi_bb34_6, phi_bb34_11, phi_bb34_12}, &block38, std::vector<Node*>{phi_bb34_6, phi_bb34_11, phi_bb34_12});
  }

  TNode<Smi> phi_bb35_6;
  TNode<Number> phi_bb35_9;
  TNode<Object> phi_bb35_11;
  TNode<Smi> phi_bb35_12;
  TNode<Smi> phi_bb35_17;
  TNode<Smi> phi_bb35_18;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_6, &phi_bb35_9, &phi_bb35_11, &phi_bb35_12, &phi_bb35_17, &phi_bb35_18);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb37_6;
  TNode<Object> phi_bb37_11;
  TNode<Smi> phi_bb37_12;
  TNode<Number> tmp66;
  TNode<BoolT> tmp67;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_6, &phi_bb37_11, &phi_bb37_12);
    tmp66 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp67 = NumberIsGreaterThanOrEqual_0(state_, TNode<Number>{tmp65}, TNode<Number>{tmp66});
    ca_.Branch(tmp67, &block40, std::vector<Node*>{phi_bb37_6, phi_bb37_11, phi_bb37_12}, &block41, std::vector<Node*>{phi_bb37_6, phi_bb37_11, phi_bb37_12});
  }

  TNode<Smi> phi_bb40_6;
  TNode<Object> phi_bb40_11;
  TNode<Smi> phi_bb40_12;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_6, &phi_bb40_11, &phi_bb40_12);
    ca_.Goto(&block27, phi_bb40_6, tmp65, phi_bb40_11, phi_bb40_12);
  }

  TNode<Smi> phi_bb41_6;
  TNode<Object> phi_bb41_11;
  TNode<Smi> phi_bb41_12;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_6, &phi_bb41_11, &phi_bb41_12);
    ca_.Goto(&block39, phi_bb41_6, phi_bb41_11, phi_bb41_12);
  }

  TNode<Smi> phi_bb38_6;
  TNode<Object> phi_bb38_11;
  TNode<Smi> phi_bb38_12;
  TNode<Number> tmp68;
  TNode<BoolT> tmp69;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_6, &phi_bb38_11, &phi_bb38_12);
    tmp68 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp69 = NumberIsLessThan_0(state_, TNode<Number>{tmp65}, TNode<Number>{tmp68});
    ca_.Branch(tmp69, &block42, std::vector<Node*>{phi_bb38_6, phi_bb38_11, phi_bb38_12}, &block43, std::vector<Node*>{phi_bb38_6, phi_bb38_11, phi_bb38_12});
  }

  TNode<Smi> phi_bb42_6;
  TNode<Object> phi_bb42_11;
  TNode<Smi> phi_bb42_12;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_6, &phi_bb42_11, &phi_bb42_12);
    ca_.Goto(&block27, phi_bb42_6, tmp65, phi_bb42_11, phi_bb42_12);
  }

  TNode<Smi> phi_bb43_6;
  TNode<Object> phi_bb43_11;
  TNode<Smi> phi_bb43_12;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_6, &phi_bb43_11, &phi_bb43_12);
    ca_.Goto(&block39, phi_bb43_6, phi_bb43_11, phi_bb43_12);
  }

  TNode<Smi> phi_bb39_6;
  TNode<Object> phi_bb39_11;
  TNode<Smi> phi_bb39_12;
  TNode<Smi> tmp70;
  TNode<Smi> tmp71;
  TNode<Smi> tmp72;
  TNode<Smi> tmp73;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_6, &phi_bb39_11, &phi_bb39_12);
    tmp70 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp71 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb39_6}, TNode<Smi>{tmp70});
    tmp72 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp73 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb39_12}, TNode<Smi>{tmp72});
    ca_.Goto(&block28, tmp71, tmp65, tmp64, tmp73);
  }

  TNode<Smi> phi_bb27_6;
  TNode<Number> phi_bb27_9;
  TNode<Object> phi_bb27_11;
  TNode<Smi> phi_bb27_12;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_6, &phi_bb27_9, &phi_bb27_11, &phi_bb27_12);
    ca_.Branch(phi_bb24_10, &block44, std::vector<Node*>{phi_bb27_6, phi_bb27_9, phi_bb27_11}, &block45, std::vector<Node*>{phi_bb27_6, phi_bb27_9, phi_bb27_11});
  }

  TNode<Smi> phi_bb44_6;
  TNode<Number> phi_bb44_9;
  TNode<Object> phi_bb44_11;
  TNode<Smi> tmp74;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_6, &phi_bb44_9, &phi_bb44_11);
    tmp74 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_lowArg}, TNode<Smi>{phi_bb44_6});
    ReverseRange_0(state_, TNode<FixedArray>{tmp1}, TNode<Smi>{p_lowArg}, TNode<Smi>{tmp74});
    ca_.Goto(&block45, phi_bb44_6, phi_bb44_9, phi_bb44_11);
  }

  TNode<Smi> phi_bb45_6;
  TNode<Number> phi_bb45_9;
  TNode<Object> phi_bb45_11;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_6, &phi_bb45_9, &phi_bb45_11);
    ca_.Goto(&block1, phi_bb45_6);
  }

  TNode<Smi> phi_bb1_4;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4);
    ca_.Goto(&block46, phi_bb1_4);
  }

  TNode<Smi> phi_bb46_4;
    ca_.Bind(&block46, &phi_bb46_4);
  return TNode<Smi>{phi_bb46_4};
}

void ReverseRange_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_array, TNode<Smi> p_from, TNode<Smi> p_to) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp1 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_to}, TNode<Smi>{tmp0});
    ca_.Goto(&block4, p_from, tmp1);
  }

  TNode<Smi> phi_bb4_3;
  TNode<Smi> phi_bb4_4;
  TNode<BoolT> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_3, &phi_bb4_4);
    tmp2 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb4_3}, TNode<Smi>{phi_bb4_4});
    ca_.Branch(tmp2, &block2, std::vector<Node*>{phi_bb4_3, phi_bb4_4}, &block3, std::vector<Node*>{phi_bb4_3, phi_bb4_4});
  }

  TNode<Smi> phi_bb2_3;
  TNode<Smi> phi_bb2_4;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<Smi> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<BoolT> tmp11;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3, &phi_bb2_4);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp6 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_array, tmp5});
    tmp7 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp6});
    tmp8 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb2_3});
    tmp9 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp7});
    tmp11 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp9}, TNode<UintPtrT>{tmp10});
    ca_.Branch(tmp11, &block9, std::vector<Node*>{phi_bb2_3, phi_bb2_4, phi_bb2_3, phi_bb2_3}, &block10, std::vector<Node*>{phi_bb2_3, phi_bb2_4, phi_bb2_3, phi_bb2_3});
  }

  TNode<Smi> phi_bb9_3;
  TNode<Smi> phi_bb9_4;
  TNode<Smi> phi_bb9_9;
  TNode<Smi> phi_bb9_10;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<HeapObject> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<Object> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Smi> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<UintPtrT> tmp24;
  TNode<UintPtrT> tmp25;
  TNode<BoolT> tmp26;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_3, &phi_bb9_4, &phi_bb9_9, &phi_bb9_10);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp13 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp12});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp13});
    std::tie(tmp15, tmp16) = NewReference_Object_0(state_, TNode<HeapObject>{p_array}, TNode<IntPtrT>{tmp14}).Flatten();
    tmp17 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp15, tmp16});
    tmp18 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp21 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_array, tmp20});
    tmp22 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp21});
    tmp23 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb9_4});
    tmp24 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp23});
    tmp25 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp22});
    tmp26 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp24}, TNode<UintPtrT>{tmp25});
    ca_.Branch(tmp26, &block16, std::vector<Node*>{phi_bb9_3, phi_bb9_4, phi_bb9_4, phi_bb9_4}, &block17, std::vector<Node*>{phi_bb9_3, phi_bb9_4, phi_bb9_4, phi_bb9_4});
  }

  TNode<Smi> phi_bb10_3;
  TNode<Smi> phi_bb10_4;
  TNode<Smi> phi_bb10_9;
  TNode<Smi> phi_bb10_10;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_3, &phi_bb10_4, &phi_bb10_9, &phi_bb10_10);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb16_3;
  TNode<Smi> phi_bb16_4;
  TNode<Smi> phi_bb16_10;
  TNode<Smi> phi_bb16_11;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<HeapObject> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<Object> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<Smi> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<Smi> tmp38;
  TNode<Smi> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<UintPtrT> tmp41;
  TNode<UintPtrT> tmp42;
  TNode<BoolT> tmp43;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_3, &phi_bb16_4, &phi_bb16_10, &phi_bb16_11);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp28 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp23}, TNode<IntPtrT>{tmp27});
    tmp29 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp18}, TNode<IntPtrT>{tmp28});
    std::tie(tmp30, tmp31) = NewReference_Object_0(state_, TNode<HeapObject>{p_array}, TNode<IntPtrT>{tmp29}).Flatten();
    tmp32 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp30, tmp31});
    tmp33 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp34 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp36 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_array, tmp35});
    tmp37 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp36});
    tmp38 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp39 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb16_3}, TNode<Smi>{tmp38});
    tmp40 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb16_3});
    tmp41 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp40});
    tmp42 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp37});
    tmp43 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp41}, TNode<UintPtrT>{tmp42});
    ca_.Branch(tmp43, &block23, std::vector<Node*>{phi_bb16_4, phi_bb16_3, phi_bb16_3}, &block24, std::vector<Node*>{phi_bb16_4, phi_bb16_3, phi_bb16_3});
  }

  TNode<Smi> phi_bb17_3;
  TNode<Smi> phi_bb17_4;
  TNode<Smi> phi_bb17_10;
  TNode<Smi> phi_bb17_11;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_3, &phi_bb17_4, &phi_bb17_10, &phi_bb17_11);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb23_4;
  TNode<Smi> phi_bb23_11;
  TNode<Smi> phi_bb23_12;
  TNode<IntPtrT> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<IntPtrT> tmp46;
  TNode<HeapObject> tmp47;
  TNode<IntPtrT> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<IntPtrT> tmp51;
  TNode<Smi> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<Smi> tmp54;
  TNode<Smi> tmp55;
  TNode<IntPtrT> tmp56;
  TNode<UintPtrT> tmp57;
  TNode<UintPtrT> tmp58;
  TNode<BoolT> tmp59;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_4, &phi_bb23_11, &phi_bb23_12);
    tmp44 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp45 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp40}, TNode<IntPtrT>{tmp44});
    tmp46 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp33}, TNode<IntPtrT>{tmp45});
    std::tie(tmp47, tmp48) = NewReference_Object_0(state_, TNode<HeapObject>{p_array}, TNode<IntPtrT>{tmp46}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp47, tmp48}, tmp32);
    tmp49 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp50 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp51 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp52 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_array, tmp51});
    tmp53 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp52});
    tmp54 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp55 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb23_4}, TNode<Smi>{tmp54});
    tmp56 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb23_4});
    tmp57 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp56});
    tmp58 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp53});
    tmp59 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp57}, TNode<UintPtrT>{tmp58});
    ca_.Branch(tmp59, &block30, std::vector<Node*>{phi_bb23_4, phi_bb23_4}, &block31, std::vector<Node*>{phi_bb23_4, phi_bb23_4});
  }

  TNode<Smi> phi_bb24_4;
  TNode<Smi> phi_bb24_11;
  TNode<Smi> phi_bb24_12;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_4, &phi_bb24_11, &phi_bb24_12);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb30_11;
  TNode<Smi> phi_bb30_12;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<HeapObject> tmp63;
  TNode<IntPtrT> tmp64;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_11, &phi_bb30_12);
    tmp60 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp61 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp56}, TNode<IntPtrT>{tmp60});
    tmp62 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp49}, TNode<IntPtrT>{tmp61});
    std::tie(tmp63, tmp64) = NewReference_Object_0(state_, TNode<HeapObject>{p_array}, TNode<IntPtrT>{tmp62}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp63, tmp64}, tmp17);
    ca_.Goto(&block4, tmp39, tmp55);
  }

  TNode<Smi> phi_bb31_11;
  TNode<Smi> phi_bb31_12;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_11, &phi_bb31_12);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb3_3;
  TNode<Smi> phi_bb3_4;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_3, &phi_bb3_4);
    ca_.Goto(&block33);
  }

    ca_.Bind(&block33);
}

TF_BUILTIN(MergeAt, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<FixedArray> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArray> tmp4;
  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<Smi> tmp9;
  TNode<Smi> tmp10;
  TNode<Smi> tmp11;
  TNode<Smi> tmp12;
  TNode<Smi> tmp13;
  TNode<Smi> tmp14;
  TNode<Smi> tmp15;
  TNode<BoolT> tmp16;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetPendingRunsSize_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp2 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{parameter1, tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{parameter1, tmp3});
    tmp5 = GetPendingRunBase_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp4}, TNode<Smi>{parameter2});
    tmp6 = GetPendingRunLength_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp4}, TNode<Smi>{parameter2});
    tmp7 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp8 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp7});
    tmp9 = GetPendingRunBase_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp4}, TNode<Smi>{tmp8});
    tmp10 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp11 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp10});
    tmp12 = GetPendingRunLength_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp4}, TNode<Smi>{tmp11});
    tmp13 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp6}, TNode<Smi>{tmp12});
    SetPendingRunLength_0(state_, TNode<FixedArray>{tmp4}, TNode<Smi>{parameter2}, TNode<Smi>{tmp13});
    tmp14 = FromConstexpr_Smi_constexpr_int31_0(state_, 3);
    tmp15 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp0}, TNode<Smi>{tmp14});
    tmp16 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{parameter2}, TNode<Smi>{tmp15});
    ca_.Branch(tmp16, &block27, std::vector<Node*>{}, &block28, std::vector<Node*>{});
  }

  TNode<Smi> tmp17;
  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  TNode<Smi> tmp20;
  TNode<Smi> tmp21;
  TNode<Smi> tmp22;
  TNode<Smi> tmp23;
  TNode<Smi> tmp24;
  TNode<Smi> tmp25;
  TNode<Smi> tmp26;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    tmp17 = FromConstexpr_Smi_constexpr_int31_0(state_, 2);
    tmp18 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp17});
    tmp19 = GetPendingRunBase_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp4}, TNode<Smi>{tmp18});
    tmp20 = FromConstexpr_Smi_constexpr_int31_0(state_, 2);
    tmp21 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp20});
    tmp22 = GetPendingRunLength_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp4}, TNode<Smi>{tmp21});
    tmp23 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp24 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp23});
    SetPendingRunBase_0(state_, TNode<FixedArray>{tmp4}, TNode<Smi>{tmp24}, TNode<Smi>{tmp19});
    tmp25 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp26 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp25});
    SetPendingRunLength_0(state_, TNode<FixedArray>{tmp4}, TNode<Smi>{tmp26}, TNode<Smi>{tmp22});
    ca_.Goto(&block28);
  }

  TNode<IntPtrT> tmp27;
  TNode<Smi> tmp28;
  TNode<Smi> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<Smi> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<UintPtrT> tmp36;
  TNode<UintPtrT> tmp37;
  TNode<BoolT> tmp38;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    tmp28 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp29 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp0}, TNode<Smi>{tmp28});
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp27}, tmp29);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp32 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp33 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp32});
    tmp34 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp33});
    tmp35 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp36 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp35});
    tmp37 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp34});
    tmp38 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp36}, TNode<UintPtrT>{tmp37});
    ca_.Branch(tmp38, &block33, std::vector<Node*>{}, &block34, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<HeapObject> tmp42;
  TNode<IntPtrT> tmp43;
  TNode<Object> tmp44;
  TNode<Object> tmp45;
  TNode<Smi> tmp46;
  TNode<Smi> tmp47;
  TNode<Smi> tmp48;
  TNode<Smi> tmp49;
  TNode<Smi> tmp50;
  TNode<BoolT> tmp51;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp39 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp40 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp35}, TNode<IntPtrT>{tmp39});
    tmp41 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp30}, TNode<IntPtrT>{tmp40});
    std::tie(tmp42, tmp43) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp41}).Flatten();
    tmp44 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp42, tmp43});
    tmp45 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp44});
    tmp46 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp47 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kGallopRight, parameter0, parameter1, tmp2, tmp45, tmp5, tmp6, tmp46));
    tmp48 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp5}, TNode<Smi>{tmp47});
    tmp49 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp6}, TNode<Smi>{tmp47});
    tmp50 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp51 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp49}, TNode<Smi>{tmp50});
    ca_.Branch(tmp51, &block40, std::vector<Node*>{}, &block41, std::vector<Node*>{});
  }

  if (block34.is_used()) {
    ca_.Bind(&block34);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> tmp52;
  if (block40.is_used()) {
    ca_.Bind(&block40);
    tmp52 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp52);
  }

  TNode<IntPtrT> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<Smi> tmp56;
  TNode<IntPtrT> tmp57;
  TNode<Smi> tmp58;
  TNode<Smi> tmp59;
  TNode<Smi> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<UintPtrT> tmp62;
  TNode<UintPtrT> tmp63;
  TNode<BoolT> tmp64;
  if (block41.is_used()) {
    ca_.Bind(&block41);
    tmp53 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp54 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp55 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp56 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp55});
    tmp57 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp56});
    tmp58 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp48}, TNode<Smi>{tmp49});
    tmp59 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp60 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp58}, TNode<Smi>{tmp59});
    tmp61 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp60});
    tmp62 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp61});
    tmp63 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp57});
    tmp64 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp62}, TNode<UintPtrT>{tmp63});
    ca_.Branch(tmp64, &block50, std::vector<Node*>{}, &block51, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp65;
  TNode<IntPtrT> tmp66;
  TNode<IntPtrT> tmp67;
  TNode<HeapObject> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<Object> tmp70;
  TNode<Object> tmp71;
  TNode<Smi> tmp72;
  TNode<Smi> tmp73;
  TNode<Smi> tmp74;
  TNode<Smi> tmp75;
  TNode<BoolT> tmp76;
  if (block50.is_used()) {
    ca_.Bind(&block50);
    tmp65 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp66 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp61}, TNode<IntPtrT>{tmp65});
    tmp67 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp53}, TNode<IntPtrT>{tmp66});
    std::tie(tmp68, tmp69) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp67}).Flatten();
    tmp70 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp68, tmp69});
    tmp71 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp70});
    tmp72 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp73 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp12}, TNode<Smi>{tmp72});
    tmp74 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kGallopLeft, parameter0, parameter1, tmp2, tmp71, tmp9, tmp12, tmp73));
    tmp75 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp76 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp74}, TNode<Smi>{tmp75});
    ca_.Branch(tmp76, &block57, std::vector<Node*>{}, &block58, std::vector<Node*>{});
  }

  if (block51.is_used()) {
    ca_.Bind(&block51);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> tmp77;
  if (block57.is_used()) {
    ca_.Bind(&block57);
    tmp77 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp77);
  }

  TNode<BoolT> tmp78;
  if (block58.is_used()) {
    ca_.Bind(&block58);
    tmp78 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp49}, TNode<Smi>{tmp74});
    ca_.Branch(tmp78, &block59, std::vector<Node*>{}, &block60, std::vector<Node*>{});
  }

  if (block59.is_used()) {
    ca_.Bind(&block59);
    MergeLow_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp48}, TNode<Smi>{tmp49}, TNode<Smi>{tmp9}, TNode<Smi>{tmp74});
    ca_.Goto(&block61);
  }

  if (block60.is_used()) {
    ca_.Bind(&block60);
    MergeHigh_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp48}, TNode<Smi>{tmp49}, TNode<Smi>{tmp9}, TNode<Smi>{tmp74});
    ca_.Goto(&block61);
  }

  TNode<Smi> tmp79;
  if (block61.is_used()) {
    ca_.Bind(&block61);
    tmp79 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp79);
  }
}

TF_BUILTIN(GallopLeft, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<FixedArray> parameter2 = UncheckedCast<FixedArray>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  TNode<Smi> parameter4 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<3>()));
  USE(parameter4);
  TNode<Smi> parameter5 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<4>()));
  USE(parameter5);
  TNode<Smi> parameter6 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<5>()));
  USE(parameter6);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block78(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block79(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block82(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Smi> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<BoolT> tmp11;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp1 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp5 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter2, tmp4});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp5});
    tmp7 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp8 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp7});
    tmp9 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp11 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp9}, TNode<UintPtrT>{tmp10});
    ca_.Branch(tmp11, &block19, std::vector<Node*>{}, &block20, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<HeapObject> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<Object> tmp17;
  TNode<Object> tmp18;
  TNode<Number> tmp19;
  TNode<Number> tmp20;
  TNode<BoolT> tmp21;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp13 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp12});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp2}, TNode<IntPtrT>{tmp13});
    std::tie(tmp15, tmp16) = NewReference_Object_0(state_, TNode<HeapObject>{parameter2}, TNode<IntPtrT>{tmp14}).Flatten();
    tmp17 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp15, tmp16});
    tmp18 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp17});
    tmp19 = Method_SortState_Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Object>{tmp18}, TNode<Object>{parameter3});
    tmp20 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp21 = NumberIsLessThan_0(state_, TNode<Number>{tmp19}, TNode<Number>{tmp20});
    ca_.Branch(tmp21, &block22, std::vector<Node*>{}, &block23, std::vector<Node*>{});
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> tmp22;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp22 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter5}, TNode<Smi>{parameter6});
    ca_.Goto(&block27, tmp0, tmp1, tmp19);
  }

  TNode<Smi> phi_bb27_7;
  TNode<Smi> phi_bb27_8;
  TNode<Number> phi_bb27_10;
  TNode<BoolT> tmp23;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_7, &phi_bb27_8, &phi_bb27_10);
    tmp23 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb27_8}, TNode<Smi>{tmp22});
    ca_.Branch(tmp23, &block25, std::vector<Node*>{phi_bb27_7, phi_bb27_8, phi_bb27_10}, &block26, std::vector<Node*>{phi_bb27_7, phi_bb27_8, phi_bb27_10});
  }

  TNode<Smi> phi_bb25_7;
  TNode<Smi> phi_bb25_8;
  TNode<Number> phi_bb25_10;
  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<Smi> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Smi> tmp29;
  TNode<Smi> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<BoolT> tmp34;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_7, &phi_bb25_8, &phi_bb25_10);
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp26 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp27 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter2, tmp26});
    tmp28 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp27});
    tmp29 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp30 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp29}, TNode<Smi>{phi_bb25_8});
    tmp31 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp30});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp28});
    tmp34 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp32}, TNode<UintPtrT>{tmp33});
    ca_.Branch(tmp34, &block32, std::vector<Node*>{phi_bb25_7, phi_bb25_8, phi_bb25_10}, &block33, std::vector<Node*>{phi_bb25_7, phi_bb25_8, phi_bb25_10});
  }

  TNode<Smi> phi_bb32_7;
  TNode<Smi> phi_bb32_8;
  TNode<Number> phi_bb32_10;
  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<HeapObject> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<Object> tmp40;
  TNode<Object> tmp41;
  TNode<Number> tmp42;
  TNode<Number> tmp43;
  TNode<BoolT> tmp44;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_7, &phi_bb32_8, &phi_bb32_10);
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp36 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp31}, TNode<IntPtrT>{tmp35});
    tmp37 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp24}, TNode<IntPtrT>{tmp36});
    std::tie(tmp38, tmp39) = NewReference_Object_0(state_, TNode<HeapObject>{parameter2}, TNode<IntPtrT>{tmp37}).Flatten();
    tmp40 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp38, tmp39});
    tmp41 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp40});
    tmp42 = Method_SortState_Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Object>{tmp41}, TNode<Object>{parameter3});
    tmp43 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp44 = NumberIsGreaterThanOrEqual_0(state_, TNode<Number>{tmp42}, TNode<Number>{tmp43});
    ca_.Branch(tmp44, &block35, std::vector<Node*>{phi_bb32_7, phi_bb32_8}, &block36, std::vector<Node*>{phi_bb32_7, phi_bb32_8});
  }

  TNode<Smi> phi_bb33_7;
  TNode<Smi> phi_bb33_8;
  TNode<Number> phi_bb33_10;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_7, &phi_bb33_8, &phi_bb33_10);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb35_7;
  TNode<Smi> phi_bb35_8;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_7, &phi_bb35_8);
    ca_.Goto(&block26, phi_bb35_7, phi_bb35_8, tmp42);
  }

  TNode<Smi> phi_bb36_7;
  TNode<Smi> phi_bb36_8;
  TNode<Smi> tmp45;
  TNode<Smi> tmp46;
  TNode<Smi> tmp47;
  TNode<Smi> tmp48;
  TNode<BoolT> tmp49;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_7, &phi_bb36_8);
    tmp45 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{phi_bb36_8}, 1);
    tmp46 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp47 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp45}, TNode<Smi>{tmp46});
    tmp48 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp49 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp47}, TNode<Smi>{tmp48});
    ca_.Branch(tmp49, &block37, std::vector<Node*>{phi_bb36_8}, &block38, std::vector<Node*>{phi_bb36_8, tmp47});
  }

  TNode<Smi> phi_bb37_7;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_7);
    ca_.Goto(&block38, phi_bb37_7, tmp22);
  }

  TNode<Smi> phi_bb38_7;
  TNode<Smi> phi_bb38_8;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_7, &phi_bb38_8);
    ca_.Goto(&block27, phi_bb38_7, phi_bb38_8, tmp42);
  }

  TNode<Smi> phi_bb26_7;
  TNode<Smi> phi_bb26_8;
  TNode<Number> phi_bb26_10;
  TNode<BoolT> tmp50;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_7, &phi_bb26_8, &phi_bb26_10);
    tmp50 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb26_8}, TNode<Smi>{tmp22});
    ca_.Branch(tmp50, &block39, std::vector<Node*>{phi_bb26_7, phi_bb26_8, phi_bb26_10}, &block40, std::vector<Node*>{phi_bb26_7, phi_bb26_8, phi_bb26_10});
  }

  TNode<Smi> phi_bb39_7;
  TNode<Smi> phi_bb39_8;
  TNode<Number> phi_bb39_10;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_7, &phi_bb39_8, &phi_bb39_10);
    ca_.Goto(&block40, phi_bb39_7, tmp22, phi_bb39_10);
  }

  TNode<Smi> phi_bb40_7;
  TNode<Smi> phi_bb40_8;
  TNode<Number> phi_bb40_10;
  TNode<Smi> tmp51;
  TNode<Smi> tmp52;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_7, &phi_bb40_8, &phi_bb40_10);
    tmp51 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb40_7}, TNode<Smi>{parameter6});
    tmp52 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb40_8}, TNode<Smi>{parameter6});
    ca_.Goto(&block24, tmp51, tmp52, phi_bb40_10);
  }

  TNode<Smi> tmp53;
  TNode<Smi> tmp54;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp53 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp54 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter6}, TNode<Smi>{tmp53});
    ca_.Goto(&block47, tmp0, tmp1, tmp19);
  }

  TNode<Smi> phi_bb47_7;
  TNode<Smi> phi_bb47_8;
  TNode<Number> phi_bb47_10;
  TNode<BoolT> tmp55;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_7, &phi_bb47_8, &phi_bb47_10);
    tmp55 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb47_8}, TNode<Smi>{tmp54});
    ca_.Branch(tmp55, &block45, std::vector<Node*>{phi_bb47_7, phi_bb47_8, phi_bb47_10}, &block46, std::vector<Node*>{phi_bb47_7, phi_bb47_8, phi_bb47_10});
  }

  TNode<Smi> phi_bb45_7;
  TNode<Smi> phi_bb45_8;
  TNode<Number> phi_bb45_10;
  TNode<IntPtrT> tmp56;
  TNode<IntPtrT> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<Smi> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<Smi> tmp61;
  TNode<Smi> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<UintPtrT> tmp64;
  TNode<UintPtrT> tmp65;
  TNode<BoolT> tmp66;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_7, &phi_bb45_8, &phi_bb45_10);
    tmp56 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp57 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp58 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp59 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter2, tmp58});
    tmp60 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp59});
    tmp61 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp62 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp61}, TNode<Smi>{phi_bb45_8});
    tmp63 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp62});
    tmp64 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp63});
    tmp65 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp60});
    tmp66 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp64}, TNode<UintPtrT>{tmp65});
    ca_.Branch(tmp66, &block52, std::vector<Node*>{phi_bb45_7, phi_bb45_8, phi_bb45_10}, &block53, std::vector<Node*>{phi_bb45_7, phi_bb45_8, phi_bb45_10});
  }

  TNode<Smi> phi_bb52_7;
  TNode<Smi> phi_bb52_8;
  TNode<Number> phi_bb52_10;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<HeapObject> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<Object> tmp72;
  TNode<Object> tmp73;
  TNode<Number> tmp74;
  TNode<Number> tmp75;
  TNode<BoolT> tmp76;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_7, &phi_bb52_8, &phi_bb52_10);
    tmp67 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp68 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp63}, TNode<IntPtrT>{tmp67});
    tmp69 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp56}, TNode<IntPtrT>{tmp68});
    std::tie(tmp70, tmp71) = NewReference_Object_0(state_, TNode<HeapObject>{parameter2}, TNode<IntPtrT>{tmp69}).Flatten();
    tmp72 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp70, tmp71});
    tmp73 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp72});
    tmp74 = Method_SortState_Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Object>{tmp73}, TNode<Object>{parameter3});
    tmp75 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp76 = NumberIsLessThan_0(state_, TNode<Number>{tmp74}, TNode<Number>{tmp75});
    ca_.Branch(tmp76, &block55, std::vector<Node*>{phi_bb52_7, phi_bb52_8}, &block56, std::vector<Node*>{phi_bb52_7, phi_bb52_8});
  }

  TNode<Smi> phi_bb53_7;
  TNode<Smi> phi_bb53_8;
  TNode<Number> phi_bb53_10;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_7, &phi_bb53_8, &phi_bb53_10);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb55_7;
  TNode<Smi> phi_bb55_8;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_7, &phi_bb55_8);
    ca_.Goto(&block46, phi_bb55_7, phi_bb55_8, tmp74);
  }

  TNode<Smi> phi_bb56_7;
  TNode<Smi> phi_bb56_8;
  TNode<Smi> tmp77;
  TNode<Smi> tmp78;
  TNode<Smi> tmp79;
  TNode<Smi> tmp80;
  TNode<BoolT> tmp81;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_7, &phi_bb56_8);
    tmp77 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{phi_bb56_8}, 1);
    tmp78 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp79 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp77}, TNode<Smi>{tmp78});
    tmp80 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp81 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp79}, TNode<Smi>{tmp80});
    ca_.Branch(tmp81, &block57, std::vector<Node*>{phi_bb56_8}, &block58, std::vector<Node*>{phi_bb56_8, tmp79});
  }

  TNode<Smi> phi_bb57_7;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_7);
    ca_.Goto(&block58, phi_bb57_7, tmp54);
  }

  TNode<Smi> phi_bb58_7;
  TNode<Smi> phi_bb58_8;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_7, &phi_bb58_8);
    ca_.Goto(&block47, phi_bb58_7, phi_bb58_8, tmp74);
  }

  TNode<Smi> phi_bb46_7;
  TNode<Smi> phi_bb46_8;
  TNode<Number> phi_bb46_10;
  TNode<BoolT> tmp82;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_7, &phi_bb46_8, &phi_bb46_10);
    tmp82 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb46_8}, TNode<Smi>{tmp54});
    ca_.Branch(tmp82, &block59, std::vector<Node*>{phi_bb46_7, phi_bb46_8, phi_bb46_10}, &block60, std::vector<Node*>{phi_bb46_7, phi_bb46_8, phi_bb46_10});
  }

  TNode<Smi> phi_bb59_7;
  TNode<Smi> phi_bb59_8;
  TNode<Number> phi_bb59_10;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_7, &phi_bb59_8, &phi_bb59_10);
    ca_.Goto(&block60, phi_bb59_7, tmp54, phi_bb59_10);
  }

  TNode<Smi> phi_bb60_7;
  TNode<Smi> phi_bb60_8;
  TNode<Number> phi_bb60_10;
  TNode<Smi> tmp83;
  TNode<Smi> tmp84;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_7, &phi_bb60_8, &phi_bb60_10);
    tmp83 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter6}, TNode<Smi>{phi_bb60_8});
    tmp84 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter6}, TNode<Smi>{phi_bb60_7});
    ca_.Goto(&block24, tmp83, tmp84, phi_bb60_10);
  }

  TNode<Smi> phi_bb24_7;
  TNode<Smi> phi_bb24_8;
  TNode<Number> phi_bb24_10;
  TNode<Smi> tmp85;
  TNode<Smi> tmp86;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_7, &phi_bb24_8, &phi_bb24_10);
    tmp85 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp86 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb24_7}, TNode<Smi>{tmp85});
    ca_.Goto(&block73, tmp86, phi_bb24_8, phi_bb24_10);
  }

  TNode<Smi> phi_bb73_7;
  TNode<Smi> phi_bb73_8;
  TNode<Number> phi_bb73_10;
  TNode<BoolT> tmp87;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_7, &phi_bb73_8, &phi_bb73_10);
    tmp87 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb73_7}, TNode<Smi>{phi_bb73_8});
    ca_.Branch(tmp87, &block71, std::vector<Node*>{phi_bb73_7, phi_bb73_8, phi_bb73_10}, &block72, std::vector<Node*>{phi_bb73_7, phi_bb73_8, phi_bb73_10});
  }

  TNode<Smi> phi_bb71_7;
  TNode<Smi> phi_bb71_8;
  TNode<Number> phi_bb71_10;
  TNode<Smi> tmp88;
  TNode<Smi> tmp89;
  TNode<Smi> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<IntPtrT> tmp92;
  TNode<IntPtrT> tmp93;
  TNode<Smi> tmp94;
  TNode<IntPtrT> tmp95;
  TNode<Smi> tmp96;
  TNode<IntPtrT> tmp97;
  TNode<UintPtrT> tmp98;
  TNode<UintPtrT> tmp99;
  TNode<BoolT> tmp100;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_7, &phi_bb71_8, &phi_bb71_10);
    tmp88 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb71_8}, TNode<Smi>{phi_bb71_7});
    tmp89 = CodeStubAssembler(state_).SmiSar(TNode<Smi>{tmp88}, 1);
    tmp90 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb71_7}, TNode<Smi>{tmp89});
    tmp91 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp92 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp93 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp94 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter2, tmp93});
    tmp95 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp94});
    tmp96 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{tmp90});
    tmp97 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp96});
    tmp98 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp97});
    tmp99 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp95});
    tmp100 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp98}, TNode<UintPtrT>{tmp99});
    ca_.Branch(tmp100, &block78, std::vector<Node*>{phi_bb71_7, phi_bb71_8, phi_bb71_10}, &block79, std::vector<Node*>{phi_bb71_7, phi_bb71_8, phi_bb71_10});
  }

  TNode<Smi> phi_bb78_7;
  TNode<Smi> phi_bb78_8;
  TNode<Number> phi_bb78_10;
  TNode<IntPtrT> tmp101;
  TNode<IntPtrT> tmp102;
  TNode<IntPtrT> tmp103;
  TNode<HeapObject> tmp104;
  TNode<IntPtrT> tmp105;
  TNode<Object> tmp106;
  TNode<Object> tmp107;
  TNode<Number> tmp108;
  TNode<Number> tmp109;
  TNode<BoolT> tmp110;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_7, &phi_bb78_8, &phi_bb78_10);
    tmp101 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp102 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp97}, TNode<IntPtrT>{tmp101});
    tmp103 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp91}, TNode<IntPtrT>{tmp102});
    std::tie(tmp104, tmp105) = NewReference_Object_0(state_, TNode<HeapObject>{parameter2}, TNode<IntPtrT>{tmp103}).Flatten();
    tmp106 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp104, tmp105});
    tmp107 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp106});
    tmp108 = Method_SortState_Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Object>{tmp107}, TNode<Object>{parameter3});
    tmp109 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp110 = NumberIsLessThan_0(state_, TNode<Number>{tmp108}, TNode<Number>{tmp109});
    ca_.Branch(tmp110, &block81, std::vector<Node*>{phi_bb78_7, phi_bb78_8}, &block82, std::vector<Node*>{phi_bb78_7, phi_bb78_8});
  }

  TNode<Smi> phi_bb79_7;
  TNode<Smi> phi_bb79_8;
  TNode<Number> phi_bb79_10;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_7, &phi_bb79_8, &phi_bb79_10);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb81_7;
  TNode<Smi> phi_bb81_8;
  TNode<Smi> tmp111;
  TNode<Smi> tmp112;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_7, &phi_bb81_8);
    tmp111 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp112 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp90}, TNode<Smi>{tmp111});
    ca_.Goto(&block83, tmp112, phi_bb81_8);
  }

  TNode<Smi> phi_bb82_7;
  TNode<Smi> phi_bb82_8;
  if (block82.is_used()) {
    ca_.Bind(&block82, &phi_bb82_7, &phi_bb82_8);
    ca_.Goto(&block83, phi_bb82_7, tmp90);
  }

  TNode<Smi> phi_bb83_7;
  TNode<Smi> phi_bb83_8;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_7, &phi_bb83_8);
    ca_.Goto(&block73, phi_bb83_7, phi_bb83_8, tmp108);
  }

  TNode<Smi> phi_bb72_7;
  TNode<Smi> phi_bb72_8;
  TNode<Number> phi_bb72_10;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_7, &phi_bb72_8, &phi_bb72_10);
    CodeStubAssembler(state_).Return(phi_bb72_8);
  }
}

TF_BUILTIN(GallopRight, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<FixedArray> parameter2 = UncheckedCast<FixedArray>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  TNode<Smi> parameter4 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<3>()));
  USE(parameter4);
  TNode<Smi> parameter5 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<4>()));
  USE(parameter5);
  TNode<Smi> parameter6 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<5>()));
  USE(parameter6);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block78(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block79(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Smi> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<BoolT> tmp11;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp1 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp5 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter2, tmp4});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp5});
    tmp7 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp8 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp7});
    tmp9 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp11 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp9}, TNode<UintPtrT>{tmp10});
    ca_.Branch(tmp11, &block19, std::vector<Node*>{}, &block20, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<HeapObject> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<Object> tmp17;
  TNode<Object> tmp18;
  TNode<Number> tmp19;
  TNode<Number> tmp20;
  TNode<BoolT> tmp21;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp13 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp12});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp2}, TNode<IntPtrT>{tmp13});
    std::tie(tmp15, tmp16) = NewReference_Object_0(state_, TNode<HeapObject>{parameter2}, TNode<IntPtrT>{tmp14}).Flatten();
    tmp17 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp15, tmp16});
    tmp18 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp17});
    tmp19 = Method_SortState_Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Object>{parameter3}, TNode<Object>{tmp18});
    tmp20 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp21 = NumberIsLessThan_0(state_, TNode<Number>{tmp19}, TNode<Number>{tmp20});
    ca_.Branch(tmp21, &block22, std::vector<Node*>{}, &block23, std::vector<Node*>{});
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> tmp22;
  TNode<Smi> tmp23;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp22 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp23 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter6}, TNode<Smi>{tmp22});
    ca_.Goto(&block27, tmp0, tmp1, tmp19);
  }

  TNode<Smi> phi_bb27_7;
  TNode<Smi> phi_bb27_8;
  TNode<Number> phi_bb27_10;
  TNode<BoolT> tmp24;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_7, &phi_bb27_8, &phi_bb27_10);
    tmp24 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb27_8}, TNode<Smi>{tmp23});
    ca_.Branch(tmp24, &block25, std::vector<Node*>{phi_bb27_7, phi_bb27_8, phi_bb27_10}, &block26, std::vector<Node*>{phi_bb27_7, phi_bb27_8, phi_bb27_10});
  }

  TNode<Smi> phi_bb25_7;
  TNode<Smi> phi_bb25_8;
  TNode<Number> phi_bb25_10;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<Smi> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Smi> tmp30;
  TNode<Smi> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<UintPtrT> tmp34;
  TNode<BoolT> tmp35;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_7, &phi_bb25_8, &phi_bb25_10);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp26 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp28 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter2, tmp27});
    tmp29 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp28});
    tmp30 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp31 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp30}, TNode<Smi>{phi_bb25_8});
    tmp32 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp32});
    tmp34 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp29});
    tmp35 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp33}, TNode<UintPtrT>{tmp34});
    ca_.Branch(tmp35, &block32, std::vector<Node*>{phi_bb25_7, phi_bb25_8, phi_bb25_10}, &block33, std::vector<Node*>{phi_bb25_7, phi_bb25_8, phi_bb25_10});
  }

  TNode<Smi> phi_bb32_7;
  TNode<Smi> phi_bb32_8;
  TNode<Number> phi_bb32_10;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<HeapObject> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<Object> tmp41;
  TNode<Object> tmp42;
  TNode<Number> tmp43;
  TNode<Number> tmp44;
  TNode<BoolT> tmp45;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_7, &phi_bb32_8, &phi_bb32_10);
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp37 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp32}, TNode<IntPtrT>{tmp36});
    tmp38 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp25}, TNode<IntPtrT>{tmp37});
    std::tie(tmp39, tmp40) = NewReference_Object_0(state_, TNode<HeapObject>{parameter2}, TNode<IntPtrT>{tmp38}).Flatten();
    tmp41 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp39, tmp40});
    tmp42 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp41});
    tmp43 = Method_SortState_Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Object>{parameter3}, TNode<Object>{tmp42});
    tmp44 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp45 = NumberIsGreaterThanOrEqual_0(state_, TNode<Number>{tmp43}, TNode<Number>{tmp44});
    ca_.Branch(tmp45, &block35, std::vector<Node*>{phi_bb32_7, phi_bb32_8}, &block36, std::vector<Node*>{phi_bb32_7, phi_bb32_8});
  }

  TNode<Smi> phi_bb33_7;
  TNode<Smi> phi_bb33_8;
  TNode<Number> phi_bb33_10;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_7, &phi_bb33_8, &phi_bb33_10);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb35_7;
  TNode<Smi> phi_bb35_8;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_7, &phi_bb35_8);
    ca_.Goto(&block26, phi_bb35_7, phi_bb35_8, tmp43);
  }

  TNode<Smi> phi_bb36_7;
  TNode<Smi> phi_bb36_8;
  TNode<Smi> tmp46;
  TNode<Smi> tmp47;
  TNode<Smi> tmp48;
  TNode<Smi> tmp49;
  TNode<BoolT> tmp50;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_7, &phi_bb36_8);
    tmp46 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{phi_bb36_8}, 1);
    tmp47 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp48 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp46}, TNode<Smi>{tmp47});
    tmp49 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp50 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp48}, TNode<Smi>{tmp49});
    ca_.Branch(tmp50, &block37, std::vector<Node*>{phi_bb36_8}, &block38, std::vector<Node*>{phi_bb36_8, tmp48});
  }

  TNode<Smi> phi_bb37_7;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_7);
    ca_.Goto(&block38, phi_bb37_7, tmp23);
  }

  TNode<Smi> phi_bb38_7;
  TNode<Smi> phi_bb38_8;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_7, &phi_bb38_8);
    ca_.Goto(&block27, phi_bb38_7, phi_bb38_8, tmp43);
  }

  TNode<Smi> phi_bb26_7;
  TNode<Smi> phi_bb26_8;
  TNode<Number> phi_bb26_10;
  TNode<BoolT> tmp51;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_7, &phi_bb26_8, &phi_bb26_10);
    tmp51 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb26_8}, TNode<Smi>{tmp23});
    ca_.Branch(tmp51, &block39, std::vector<Node*>{phi_bb26_7, phi_bb26_8, phi_bb26_10}, &block40, std::vector<Node*>{phi_bb26_7, phi_bb26_8, phi_bb26_10});
  }

  TNode<Smi> phi_bb39_7;
  TNode<Smi> phi_bb39_8;
  TNode<Number> phi_bb39_10;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_7, &phi_bb39_8, &phi_bb39_10);
    ca_.Goto(&block40, phi_bb39_7, tmp23, phi_bb39_10);
  }

  TNode<Smi> phi_bb40_7;
  TNode<Smi> phi_bb40_8;
  TNode<Number> phi_bb40_10;
  TNode<Smi> tmp52;
  TNode<Smi> tmp53;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_7, &phi_bb40_8, &phi_bb40_10);
    tmp52 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter6}, TNode<Smi>{phi_bb40_8});
    tmp53 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter6}, TNode<Smi>{phi_bb40_7});
    ca_.Goto(&block24, tmp52, tmp53, phi_bb40_10);
  }

  TNode<Smi> tmp54;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp54 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter5}, TNode<Smi>{parameter6});
    ca_.Goto(&block43, tmp0, tmp1, tmp19);
  }

  TNode<Smi> phi_bb43_7;
  TNode<Smi> phi_bb43_8;
  TNode<Number> phi_bb43_10;
  TNode<BoolT> tmp55;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_7, &phi_bb43_8, &phi_bb43_10);
    tmp55 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb43_8}, TNode<Smi>{tmp54});
    ca_.Branch(tmp55, &block41, std::vector<Node*>{phi_bb43_7, phi_bb43_8, phi_bb43_10}, &block42, std::vector<Node*>{phi_bb43_7, phi_bb43_8, phi_bb43_10});
  }

  TNode<Smi> phi_bb41_7;
  TNode<Smi> phi_bb41_8;
  TNode<Number> phi_bb41_10;
  TNode<IntPtrT> tmp56;
  TNode<IntPtrT> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<Smi> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<Smi> tmp61;
  TNode<Smi> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<UintPtrT> tmp64;
  TNode<UintPtrT> tmp65;
  TNode<BoolT> tmp66;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_7, &phi_bb41_8, &phi_bb41_10);
    tmp56 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp57 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp58 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp59 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter2, tmp58});
    tmp60 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp59});
    tmp61 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp62 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp61}, TNode<Smi>{phi_bb41_8});
    tmp63 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp62});
    tmp64 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp63});
    tmp65 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp60});
    tmp66 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp64}, TNode<UintPtrT>{tmp65});
    ca_.Branch(tmp66, &block48, std::vector<Node*>{phi_bb41_7, phi_bb41_8, phi_bb41_10}, &block49, std::vector<Node*>{phi_bb41_7, phi_bb41_8, phi_bb41_10});
  }

  TNode<Smi> phi_bb48_7;
  TNode<Smi> phi_bb48_8;
  TNode<Number> phi_bb48_10;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<HeapObject> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<Object> tmp72;
  TNode<Object> tmp73;
  TNode<Number> tmp74;
  TNode<Number> tmp75;
  TNode<BoolT> tmp76;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_7, &phi_bb48_8, &phi_bb48_10);
    tmp67 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp68 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp63}, TNode<IntPtrT>{tmp67});
    tmp69 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp56}, TNode<IntPtrT>{tmp68});
    std::tie(tmp70, tmp71) = NewReference_Object_0(state_, TNode<HeapObject>{parameter2}, TNode<IntPtrT>{tmp69}).Flatten();
    tmp72 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp70, tmp71});
    tmp73 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp72});
    tmp74 = Method_SortState_Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Object>{parameter3}, TNode<Object>{tmp73});
    tmp75 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp76 = NumberIsLessThan_0(state_, TNode<Number>{tmp74}, TNode<Number>{tmp75});
    ca_.Branch(tmp76, &block51, std::vector<Node*>{phi_bb48_7, phi_bb48_8}, &block52, std::vector<Node*>{phi_bb48_7, phi_bb48_8});
  }

  TNode<Smi> phi_bb49_7;
  TNode<Smi> phi_bb49_8;
  TNode<Number> phi_bb49_10;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_7, &phi_bb49_8, &phi_bb49_10);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb51_7;
  TNode<Smi> phi_bb51_8;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_7, &phi_bb51_8);
    ca_.Goto(&block42, phi_bb51_7, phi_bb51_8, tmp74);
  }

  TNode<Smi> phi_bb52_7;
  TNode<Smi> phi_bb52_8;
  TNode<Smi> tmp77;
  TNode<Smi> tmp78;
  TNode<Smi> tmp79;
  TNode<Smi> tmp80;
  TNode<BoolT> tmp81;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_7, &phi_bb52_8);
    tmp77 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{phi_bb52_8}, 1);
    tmp78 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp79 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp77}, TNode<Smi>{tmp78});
    tmp80 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp81 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp79}, TNode<Smi>{tmp80});
    ca_.Branch(tmp81, &block53, std::vector<Node*>{phi_bb52_8}, &block54, std::vector<Node*>{phi_bb52_8, tmp79});
  }

  TNode<Smi> phi_bb53_7;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_7);
    ca_.Goto(&block54, phi_bb53_7, tmp54);
  }

  TNode<Smi> phi_bb54_7;
  TNode<Smi> phi_bb54_8;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_7, &phi_bb54_8);
    ca_.Goto(&block43, phi_bb54_7, phi_bb54_8, tmp74);
  }

  TNode<Smi> phi_bb42_7;
  TNode<Smi> phi_bb42_8;
  TNode<Number> phi_bb42_10;
  TNode<BoolT> tmp82;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_7, &phi_bb42_8, &phi_bb42_10);
    tmp82 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb42_8}, TNode<Smi>{tmp54});
    ca_.Branch(tmp82, &block55, std::vector<Node*>{phi_bb42_7, phi_bb42_8, phi_bb42_10}, &block56, std::vector<Node*>{phi_bb42_7, phi_bb42_8, phi_bb42_10});
  }

  TNode<Smi> phi_bb55_7;
  TNode<Smi> phi_bb55_8;
  TNode<Number> phi_bb55_10;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_7, &phi_bb55_8, &phi_bb55_10);
    ca_.Goto(&block56, phi_bb55_7, tmp54, phi_bb55_10);
  }

  TNode<Smi> phi_bb56_7;
  TNode<Smi> phi_bb56_8;
  TNode<Number> phi_bb56_10;
  TNode<Smi> tmp83;
  TNode<Smi> tmp84;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_7, &phi_bb56_8, &phi_bb56_10);
    tmp83 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb56_7}, TNode<Smi>{parameter6});
    tmp84 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb56_8}, TNode<Smi>{parameter6});
    ca_.Goto(&block24, tmp83, tmp84, phi_bb56_10);
  }

  TNode<Smi> phi_bb24_7;
  TNode<Smi> phi_bb24_8;
  TNode<Number> phi_bb24_10;
  TNode<Smi> tmp85;
  TNode<Smi> tmp86;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_7, &phi_bb24_8, &phi_bb24_10);
    tmp85 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp86 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb24_7}, TNode<Smi>{tmp85});
    ca_.Goto(&block69, tmp86, phi_bb24_8, phi_bb24_10);
  }

  TNode<Smi> phi_bb69_7;
  TNode<Smi> phi_bb69_8;
  TNode<Number> phi_bb69_10;
  TNode<BoolT> tmp87;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_7, &phi_bb69_8, &phi_bb69_10);
    tmp87 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb69_7}, TNode<Smi>{phi_bb69_8});
    ca_.Branch(tmp87, &block67, std::vector<Node*>{phi_bb69_7, phi_bb69_8, phi_bb69_10}, &block68, std::vector<Node*>{phi_bb69_7, phi_bb69_8, phi_bb69_10});
  }

  TNode<Smi> phi_bb67_7;
  TNode<Smi> phi_bb67_8;
  TNode<Number> phi_bb67_10;
  TNode<Smi> tmp88;
  TNode<Smi> tmp89;
  TNode<Smi> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<IntPtrT> tmp92;
  TNode<IntPtrT> tmp93;
  TNode<Smi> tmp94;
  TNode<IntPtrT> tmp95;
  TNode<Smi> tmp96;
  TNode<IntPtrT> tmp97;
  TNode<UintPtrT> tmp98;
  TNode<UintPtrT> tmp99;
  TNode<BoolT> tmp100;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_7, &phi_bb67_8, &phi_bb67_10);
    tmp88 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb67_8}, TNode<Smi>{phi_bb67_7});
    tmp89 = CodeStubAssembler(state_).SmiSar(TNode<Smi>{tmp88}, 1);
    tmp90 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb67_7}, TNode<Smi>{tmp89});
    tmp91 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp92 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp93 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp94 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{parameter2, tmp93});
    tmp95 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp94});
    tmp96 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{tmp90});
    tmp97 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp96});
    tmp98 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp97});
    tmp99 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp95});
    tmp100 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp98}, TNode<UintPtrT>{tmp99});
    ca_.Branch(tmp100, &block74, std::vector<Node*>{phi_bb67_7, phi_bb67_8, phi_bb67_10}, &block75, std::vector<Node*>{phi_bb67_7, phi_bb67_8, phi_bb67_10});
  }

  TNode<Smi> phi_bb74_7;
  TNode<Smi> phi_bb74_8;
  TNode<Number> phi_bb74_10;
  TNode<IntPtrT> tmp101;
  TNode<IntPtrT> tmp102;
  TNode<IntPtrT> tmp103;
  TNode<HeapObject> tmp104;
  TNode<IntPtrT> tmp105;
  TNode<Object> tmp106;
  TNode<Object> tmp107;
  TNode<Number> tmp108;
  TNode<Number> tmp109;
  TNode<BoolT> tmp110;
  if (block74.is_used()) {
    ca_.Bind(&block74, &phi_bb74_7, &phi_bb74_8, &phi_bb74_10);
    tmp101 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp102 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp97}, TNode<IntPtrT>{tmp101});
    tmp103 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp91}, TNode<IntPtrT>{tmp102});
    std::tie(tmp104, tmp105) = NewReference_Object_0(state_, TNode<HeapObject>{parameter2}, TNode<IntPtrT>{tmp103}).Flatten();
    tmp106 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp104, tmp105});
    tmp107 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp106});
    tmp108 = Method_SortState_Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Object>{parameter3}, TNode<Object>{tmp107});
    tmp109 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp110 = NumberIsLessThan_0(state_, TNode<Number>{tmp108}, TNode<Number>{tmp109});
    ca_.Branch(tmp110, &block77, std::vector<Node*>{phi_bb74_7, phi_bb74_8}, &block78, std::vector<Node*>{phi_bb74_7, phi_bb74_8});
  }

  TNode<Smi> phi_bb75_7;
  TNode<Smi> phi_bb75_8;
  TNode<Number> phi_bb75_10;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_7, &phi_bb75_8, &phi_bb75_10);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb77_7;
  TNode<Smi> phi_bb77_8;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_7, &phi_bb77_8);
    ca_.Goto(&block79, phi_bb77_7, tmp90);
  }

  TNode<Smi> phi_bb78_7;
  TNode<Smi> phi_bb78_8;
  TNode<Smi> tmp111;
  TNode<Smi> tmp112;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_7, &phi_bb78_8);
    tmp111 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp112 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp90}, TNode<Smi>{tmp111});
    ca_.Goto(&block79, tmp112, phi_bb78_8);
  }

  TNode<Smi> phi_bb79_7;
  TNode<Smi> phi_bb79_8;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_7, &phi_bb79_8);
    ca_.Goto(&block69, phi_bb79_7, phi_bb79_8, tmp108);
  }

  TNode<Smi> phi_bb68_7;
  TNode<Smi> phi_bb68_8;
  TNode<Number> phi_bb68_10;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_7, &phi_bb68_8, &phi_bb68_10);
    CodeStubAssembler(state_).Return(phi_bb68_8);
  }
}

void MergeLow_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_baseA, TNode<Smi> p_lengthAArg, TNode<Smi> p_baseB, TNode<Smi> p_lengthBArg) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block86(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block87(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block88(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block89(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block70(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block94(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block95(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block101(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block102(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block104(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block105(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT, BoolT> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT, BoolT> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block128(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block129(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block135(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block137(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block138(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block139(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block140(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block136(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block145(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block146(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block152(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block153(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block155(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block156(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block161(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block162(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block168(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block170(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block171(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block169(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block176(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block177(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block183(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block184(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block186(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block187(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block109(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block188(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block189(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block201(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block202(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block208(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block209(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block211(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  TNode<FixedArray> tmp2;
  TNode<Smi> tmp3;
  TNode<Object> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Smi> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Smi> tmp11;
  TNode<Smi> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<UintPtrT> tmp14;
  TNode<UintPtrT> tmp15;
  TNode<BoolT> tmp16;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = GetTempArray_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{p_lengthAArg});
    tmp3 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp4 = CodeStubAssembler(state_).CallBuiltin(Builtins::kCopy, p_context, tmp1, p_baseA, tmp2, tmp3, p_lengthAArg);
    tmp5 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp11 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp12 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_baseA}, TNode<Smi>{tmp11});
    tmp13 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_baseA});
    tmp14 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp13});
    tmp15 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp16 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp14}, TNode<UintPtrT>{tmp15});
    ca_.Branch(tmp16, &block24, std::vector<Node*>{}, &block25, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<HeapObject> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<Smi> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<Smi> tmp27;
  TNode<Smi> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<UintPtrT> tmp30;
  TNode<UintPtrT> tmp31;
  TNode<BoolT> tmp32;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp18 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp17});
    tmp19 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp18});
    std::tie(tmp20, tmp21) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp19}).Flatten();
    tmp22 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp25 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp24});
    tmp26 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp25});
    tmp27 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp28 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_baseB}, TNode<Smi>{tmp27});
    tmp29 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_baseB});
    tmp30 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp29});
    tmp31 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp26});
    tmp32 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp30}, TNode<UintPtrT>{tmp31});
    ca_.Branch(tmp32, &block31, std::vector<Node*>{}, &block32, std::vector<Node*>{});
  }

  if (block25.is_used()) {
    ca_.Bind(&block25);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<HeapObject> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<Object> tmp38;
  TNode<Smi> tmp39;
  TNode<Smi> tmp40;
  TNode<Smi> tmp41;
  TNode<BoolT> tmp42;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp33 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp34 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp29}, TNode<IntPtrT>{tmp33});
    tmp35 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp34});
    std::tie(tmp36, tmp37) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp35}).Flatten();
    tmp38 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp36, tmp37});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp20, tmp21}, tmp38);
    tmp39 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp40 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_lengthBArg}, TNode<Smi>{tmp39});
    tmp41 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp42 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp40}, TNode<Smi>{tmp41});
    ca_.Branch(tmp42, &block38, std::vector<Node*>{}, &block39, std::vector<Node*>{});
  }

  if (block32.is_used()) {
    ca_.Bind(&block32);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block38.is_used()) {
    ca_.Bind(&block38);
    ca_.Goto(&block37, p_lengthAArg, tmp40, tmp12, tmp5, tmp28);
  }

  TNode<Smi> tmp43;
  TNode<BoolT> tmp44;
  if (block39.is_used()) {
    ca_.Bind(&block39);
    tmp43 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp44 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{p_lengthAArg}, TNode<Smi>{tmp43});
    ca_.Branch(tmp44, &block40, std::vector<Node*>{}, &block41, std::vector<Node*>{});
  }

  if (block40.is_used()) {
    ca_.Bind(&block40);
    ca_.Goto(&block35, p_lengthAArg, tmp40, tmp12, tmp5, tmp28);
  }

  TNode<IntPtrT> tmp45;
  TNode<Smi> tmp46;
  if (block41.is_used()) {
    ca_.Bind(&block41);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp46 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp45});
    ca_.Goto(&block44, p_lengthAArg, tmp40, tmp12, tmp5, tmp28, tmp46);
  }

  TNode<Smi> phi_bb44_6;
  TNode<Smi> phi_bb44_7;
  TNode<Smi> phi_bb44_10;
  TNode<Smi> phi_bb44_11;
  TNode<Smi> phi_bb44_12;
  TNode<Smi> phi_bb44_13;
  TNode<BoolT> tmp47;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_6, &phi_bb44_7, &phi_bb44_10, &phi_bb44_11, &phi_bb44_12, &phi_bb44_13);
    tmp47 = CodeStubAssembler(state_).Int32TrueConstant();
    ca_.Branch(tmp47, &block42, std::vector<Node*>{phi_bb44_6, phi_bb44_7, phi_bb44_10, phi_bb44_11, phi_bb44_12, phi_bb44_13}, &block43, std::vector<Node*>{phi_bb44_6, phi_bb44_7, phi_bb44_10, phi_bb44_11, phi_bb44_12, phi_bb44_13});
  }

  TNode<Smi> phi_bb42_6;
  TNode<Smi> phi_bb42_7;
  TNode<Smi> phi_bb42_10;
  TNode<Smi> phi_bb42_11;
  TNode<Smi> phi_bb42_12;
  TNode<Smi> phi_bb42_13;
  TNode<Smi> tmp48;
  TNode<Smi> tmp49;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_6, &phi_bb42_7, &phi_bb42_10, &phi_bb42_11, &phi_bb42_12, &phi_bb42_13);
    tmp48 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp49 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    ca_.Goto(&block47, phi_bb42_6, phi_bb42_7, phi_bb42_10, phi_bb42_11, phi_bb42_12, phi_bb42_13, tmp48, tmp49);
  }

  TNode<Smi> phi_bb47_6;
  TNode<Smi> phi_bb47_7;
  TNode<Smi> phi_bb47_10;
  TNode<Smi> phi_bb47_11;
  TNode<Smi> phi_bb47_12;
  TNode<Smi> phi_bb47_13;
  TNode<Smi> phi_bb47_14;
  TNode<Smi> phi_bb47_15;
  TNode<BoolT> tmp50;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_6, &phi_bb47_7, &phi_bb47_10, &phi_bb47_11, &phi_bb47_12, &phi_bb47_13, &phi_bb47_14, &phi_bb47_15);
    tmp50 = CodeStubAssembler(state_).Int32TrueConstant();
    ca_.Branch(tmp50, &block45, std::vector<Node*>{phi_bb47_6, phi_bb47_7, phi_bb47_10, phi_bb47_11, phi_bb47_12, phi_bb47_13, phi_bb47_14, phi_bb47_15}, &block46, std::vector<Node*>{phi_bb47_6, phi_bb47_7, phi_bb47_10, phi_bb47_11, phi_bb47_12, phi_bb47_13, phi_bb47_14, phi_bb47_15});
  }

  TNode<Smi> phi_bb45_6;
  TNode<Smi> phi_bb45_7;
  TNode<Smi> phi_bb45_10;
  TNode<Smi> phi_bb45_11;
  TNode<Smi> phi_bb45_12;
  TNode<Smi> phi_bb45_13;
  TNode<Smi> phi_bb45_14;
  TNode<Smi> phi_bb45_15;
  TNode<IntPtrT> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<Smi> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<IntPtrT> tmp56;
  TNode<UintPtrT> tmp57;
  TNode<UintPtrT> tmp58;
  TNode<BoolT> tmp59;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_6, &phi_bb45_7, &phi_bb45_10, &phi_bb45_11, &phi_bb45_12, &phi_bb45_13, &phi_bb45_14, &phi_bb45_15);
    tmp51 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp52 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp53 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp54 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp53});
    tmp55 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp54});
    tmp56 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb45_12});
    tmp57 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp56});
    tmp58 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp55});
    tmp59 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp57}, TNode<UintPtrT>{tmp58});
    ca_.Branch(tmp59, &block59, std::vector<Node*>{phi_bb45_6, phi_bb45_7, phi_bb45_10, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_14, phi_bb45_15, phi_bb45_12, phi_bb45_12}, &block60, std::vector<Node*>{phi_bb45_6, phi_bb45_7, phi_bb45_10, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_14, phi_bb45_15, phi_bb45_12, phi_bb45_12});
  }

  TNode<Smi> phi_bb59_6;
  TNode<Smi> phi_bb59_7;
  TNode<Smi> phi_bb59_10;
  TNode<Smi> phi_bb59_11;
  TNode<Smi> phi_bb59_12;
  TNode<Smi> phi_bb59_13;
  TNode<Smi> phi_bb59_14;
  TNode<Smi> phi_bb59_15;
  TNode<Smi> phi_bb59_21;
  TNode<Smi> phi_bb59_22;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<HeapObject> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<Object> tmp65;
  TNode<Object> tmp66;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<Smi> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<UintPtrT> tmp73;
  TNode<UintPtrT> tmp74;
  TNode<BoolT> tmp75;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_6, &phi_bb59_7, &phi_bb59_10, &phi_bb59_11, &phi_bb59_12, &phi_bb59_13, &phi_bb59_14, &phi_bb59_15, &phi_bb59_21, &phi_bb59_22);
    tmp60 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp61 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp56}, TNode<IntPtrT>{tmp60});
    tmp62 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp51}, TNode<IntPtrT>{tmp61});
    std::tie(tmp63, tmp64) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp62}).Flatten();
    tmp65 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp63, tmp64});
    tmp66 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp65});
    tmp67 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp68 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp69 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp70 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp69});
    tmp71 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp70});
    tmp72 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb59_11});
    tmp73 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp72});
    tmp74 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp71});
    tmp75 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp73}, TNode<UintPtrT>{tmp74});
    ca_.Branch(tmp75, &block66, std::vector<Node*>{phi_bb59_6, phi_bb59_7, phi_bb59_10, phi_bb59_11, phi_bb59_12, phi_bb59_13, phi_bb59_14, phi_bb59_15, phi_bb59_11, phi_bb59_11}, &block67, std::vector<Node*>{phi_bb59_6, phi_bb59_7, phi_bb59_10, phi_bb59_11, phi_bb59_12, phi_bb59_13, phi_bb59_14, phi_bb59_15, phi_bb59_11, phi_bb59_11});
  }

  TNode<Smi> phi_bb60_6;
  TNode<Smi> phi_bb60_7;
  TNode<Smi> phi_bb60_10;
  TNode<Smi> phi_bb60_11;
  TNode<Smi> phi_bb60_12;
  TNode<Smi> phi_bb60_13;
  TNode<Smi> phi_bb60_14;
  TNode<Smi> phi_bb60_15;
  TNode<Smi> phi_bb60_21;
  TNode<Smi> phi_bb60_22;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_6, &phi_bb60_7, &phi_bb60_10, &phi_bb60_11, &phi_bb60_12, &phi_bb60_13, &phi_bb60_14, &phi_bb60_15, &phi_bb60_21, &phi_bb60_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb66_6;
  TNode<Smi> phi_bb66_7;
  TNode<Smi> phi_bb66_10;
  TNode<Smi> phi_bb66_11;
  TNode<Smi> phi_bb66_12;
  TNode<Smi> phi_bb66_13;
  TNode<Smi> phi_bb66_14;
  TNode<Smi> phi_bb66_15;
  TNode<Smi> phi_bb66_22;
  TNode<Smi> phi_bb66_23;
  TNode<IntPtrT> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<IntPtrT> tmp78;
  TNode<HeapObject> tmp79;
  TNode<IntPtrT> tmp80;
  TNode<Object> tmp81;
  TNode<Object> tmp82;
  TNode<Number> tmp83;
  TNode<Number> tmp84;
  TNode<BoolT> tmp85;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_6, &phi_bb66_7, &phi_bb66_10, &phi_bb66_11, &phi_bb66_12, &phi_bb66_13, &phi_bb66_14, &phi_bb66_15, &phi_bb66_22, &phi_bb66_23);
    tmp76 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp77 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp72}, TNode<IntPtrT>{tmp76});
    tmp78 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp67}, TNode<IntPtrT>{tmp77});
    std::tie(tmp79, tmp80) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp78}).Flatten();
    tmp81 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp79, tmp80});
    tmp82 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp81});
    tmp83 = Method_SortState_Compare_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Object>{tmp66}, TNode<Object>{tmp82});
    tmp84 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp85 = NumberIsLessThan_0(state_, TNode<Number>{tmp83}, TNode<Number>{tmp84});
    ca_.Branch(tmp85, &block69, std::vector<Node*>{phi_bb66_6, phi_bb66_7, phi_bb66_10, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_15}, &block70, std::vector<Node*>{phi_bb66_6, phi_bb66_7, phi_bb66_10, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_15});
  }

  TNode<Smi> phi_bb67_6;
  TNode<Smi> phi_bb67_7;
  TNode<Smi> phi_bb67_10;
  TNode<Smi> phi_bb67_11;
  TNode<Smi> phi_bb67_12;
  TNode<Smi> phi_bb67_13;
  TNode<Smi> phi_bb67_14;
  TNode<Smi> phi_bb67_15;
  TNode<Smi> phi_bb67_22;
  TNode<Smi> phi_bb67_23;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_6, &phi_bb67_7, &phi_bb67_10, &phi_bb67_11, &phi_bb67_12, &phi_bb67_13, &phi_bb67_14, &phi_bb67_15, &phi_bb67_22, &phi_bb67_23);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb69_6;
  TNode<Smi> phi_bb69_7;
  TNode<Smi> phi_bb69_10;
  TNode<Smi> phi_bb69_11;
  TNode<Smi> phi_bb69_12;
  TNode<Smi> phi_bb69_13;
  TNode<Smi> phi_bb69_14;
  TNode<Smi> phi_bb69_15;
  TNode<IntPtrT> tmp86;
  TNode<IntPtrT> tmp87;
  TNode<IntPtrT> tmp88;
  TNode<Smi> tmp89;
  TNode<IntPtrT> tmp90;
  TNode<Smi> tmp91;
  TNode<Smi> tmp92;
  TNode<IntPtrT> tmp93;
  TNode<UintPtrT> tmp94;
  TNode<UintPtrT> tmp95;
  TNode<BoolT> tmp96;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_6, &phi_bb69_7, &phi_bb69_10, &phi_bb69_11, &phi_bb69_12, &phi_bb69_13, &phi_bb69_14, &phi_bb69_15);
    tmp86 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp87 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp88 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp89 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp88});
    tmp90 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp89});
    tmp91 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp92 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb69_10}, TNode<Smi>{tmp91});
    tmp93 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb69_10});
    tmp94 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp93});
    tmp95 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp90});
    tmp96 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp94}, TNode<UintPtrT>{tmp95});
    ca_.Branch(tmp96, &block76, std::vector<Node*>{phi_bb69_6, phi_bb69_7, phi_bb69_11, phi_bb69_12, phi_bb69_13, phi_bb69_14, phi_bb69_15, phi_bb69_10, phi_bb69_10}, &block77, std::vector<Node*>{phi_bb69_6, phi_bb69_7, phi_bb69_11, phi_bb69_12, phi_bb69_13, phi_bb69_14, phi_bb69_15, phi_bb69_10, phi_bb69_10});
  }

  TNode<Smi> phi_bb76_6;
  TNode<Smi> phi_bb76_7;
  TNode<Smi> phi_bb76_11;
  TNode<Smi> phi_bb76_12;
  TNode<Smi> phi_bb76_13;
  TNode<Smi> phi_bb76_14;
  TNode<Smi> phi_bb76_15;
  TNode<Smi> phi_bb76_21;
  TNode<Smi> phi_bb76_22;
  TNode<IntPtrT> tmp97;
  TNode<IntPtrT> tmp98;
  TNode<IntPtrT> tmp99;
  TNode<HeapObject> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<IntPtrT> tmp102;
  TNode<IntPtrT> tmp103;
  TNode<IntPtrT> tmp104;
  TNode<Smi> tmp105;
  TNode<IntPtrT> tmp106;
  TNode<Smi> tmp107;
  TNode<Smi> tmp108;
  TNode<IntPtrT> tmp109;
  TNode<UintPtrT> tmp110;
  TNode<UintPtrT> tmp111;
  TNode<BoolT> tmp112;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_6, &phi_bb76_7, &phi_bb76_11, &phi_bb76_12, &phi_bb76_13, &phi_bb76_14, &phi_bb76_15, &phi_bb76_21, &phi_bb76_22);
    tmp97 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp98 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp93}, TNode<IntPtrT>{tmp97});
    tmp99 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp86}, TNode<IntPtrT>{tmp98});
    std::tie(tmp100, tmp101) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp99}).Flatten();
    tmp102 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp103 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp104 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp105 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp104});
    tmp106 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp105});
    tmp107 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp108 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb76_12}, TNode<Smi>{tmp107});
    tmp109 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb76_12});
    tmp110 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp109});
    tmp111 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp106});
    tmp112 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp110}, TNode<UintPtrT>{tmp111});
    ca_.Branch(tmp112, &block83, std::vector<Node*>{phi_bb76_6, phi_bb76_7, phi_bb76_11, phi_bb76_13, phi_bb76_14, phi_bb76_15, phi_bb76_21, phi_bb76_22, phi_bb76_12, phi_bb76_12}, &block84, std::vector<Node*>{phi_bb76_6, phi_bb76_7, phi_bb76_11, phi_bb76_13, phi_bb76_14, phi_bb76_15, phi_bb76_21, phi_bb76_22, phi_bb76_12, phi_bb76_12});
  }

  TNode<Smi> phi_bb77_6;
  TNode<Smi> phi_bb77_7;
  TNode<Smi> phi_bb77_11;
  TNode<Smi> phi_bb77_12;
  TNode<Smi> phi_bb77_13;
  TNode<Smi> phi_bb77_14;
  TNode<Smi> phi_bb77_15;
  TNode<Smi> phi_bb77_21;
  TNode<Smi> phi_bb77_22;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_6, &phi_bb77_7, &phi_bb77_11, &phi_bb77_12, &phi_bb77_13, &phi_bb77_14, &phi_bb77_15, &phi_bb77_21, &phi_bb77_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb83_6;
  TNode<Smi> phi_bb83_7;
  TNode<Smi> phi_bb83_11;
  TNode<Smi> phi_bb83_13;
  TNode<Smi> phi_bb83_14;
  TNode<Smi> phi_bb83_15;
  TNode<Smi> phi_bb83_21;
  TNode<Smi> phi_bb83_22;
  TNode<Smi> phi_bb83_29;
  TNode<Smi> phi_bb83_30;
  TNode<IntPtrT> tmp113;
  TNode<IntPtrT> tmp114;
  TNode<IntPtrT> tmp115;
  TNode<HeapObject> tmp116;
  TNode<IntPtrT> tmp117;
  TNode<Object> tmp118;
  TNode<Smi> tmp119;
  TNode<Smi> tmp120;
  TNode<Smi> tmp121;
  TNode<Smi> tmp122;
  TNode<Smi> tmp123;
  TNode<Smi> tmp124;
  TNode<BoolT> tmp125;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_6, &phi_bb83_7, &phi_bb83_11, &phi_bb83_13, &phi_bb83_14, &phi_bb83_15, &phi_bb83_21, &phi_bb83_22, &phi_bb83_29, &phi_bb83_30);
    tmp113 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp114 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp109}, TNode<IntPtrT>{tmp113});
    tmp115 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp102}, TNode<IntPtrT>{tmp114});
    std::tie(tmp116, tmp117) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp115}).Flatten();
    tmp118 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp116, tmp117});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp100, tmp101}, tmp118);
    tmp119 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp120 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb83_15}, TNode<Smi>{tmp119});
    tmp121 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp122 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb83_7}, TNode<Smi>{tmp121});
    tmp123 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp124 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp125 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp122}, TNode<Smi>{tmp124});
    ca_.Branch(tmp125, &block86, std::vector<Node*>{phi_bb83_6, phi_bb83_11, phi_bb83_13}, &block87, std::vector<Node*>{phi_bb83_6, phi_bb83_11, phi_bb83_13});
  }

  TNode<Smi> phi_bb84_6;
  TNode<Smi> phi_bb84_7;
  TNode<Smi> phi_bb84_11;
  TNode<Smi> phi_bb84_13;
  TNode<Smi> phi_bb84_14;
  TNode<Smi> phi_bb84_15;
  TNode<Smi> phi_bb84_21;
  TNode<Smi> phi_bb84_22;
  TNode<Smi> phi_bb84_29;
  TNode<Smi> phi_bb84_30;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_6, &phi_bb84_7, &phi_bb84_11, &phi_bb84_13, &phi_bb84_14, &phi_bb84_15, &phi_bb84_21, &phi_bb84_22, &phi_bb84_29, &phi_bb84_30);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb86_6;
  TNode<Smi> phi_bb86_11;
  TNode<Smi> phi_bb86_13;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_6, &phi_bb86_11, &phi_bb86_13);
    ca_.Goto(&block37, phi_bb86_6, tmp122, tmp92, phi_bb86_11, tmp108);
  }

  TNode<Smi> phi_bb87_6;
  TNode<Smi> phi_bb87_11;
  TNode<Smi> phi_bb87_13;
  TNode<BoolT> tmp126;
  if (block87.is_used()) {
    ca_.Bind(&block87, &phi_bb87_6, &phi_bb87_11, &phi_bb87_13);
    tmp126 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp120}, TNode<Smi>{phi_bb87_13});
    ca_.Branch(tmp126, &block88, std::vector<Node*>{phi_bb87_6, phi_bb87_11, phi_bb87_13}, &block89, std::vector<Node*>{phi_bb87_6, phi_bb87_11, phi_bb87_13});
  }

  TNode<Smi> phi_bb88_6;
  TNode<Smi> phi_bb88_11;
  TNode<Smi> phi_bb88_13;
  if (block88.is_used()) {
    ca_.Bind(&block88, &phi_bb88_6, &phi_bb88_11, &phi_bb88_13);
    ca_.Goto(&block46, phi_bb88_6, tmp122, tmp92, phi_bb88_11, tmp108, phi_bb88_13, tmp123, tmp120);
  }

  TNode<Smi> phi_bb89_6;
  TNode<Smi> phi_bb89_11;
  TNode<Smi> phi_bb89_13;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_6, &phi_bb89_11, &phi_bb89_13);
    ca_.Goto(&block71, phi_bb89_6, tmp122, tmp92, phi_bb89_11, tmp108, phi_bb89_13, tmp123, tmp120);
  }

  TNode<Smi> phi_bb70_6;
  TNode<Smi> phi_bb70_7;
  TNode<Smi> phi_bb70_10;
  TNode<Smi> phi_bb70_11;
  TNode<Smi> phi_bb70_12;
  TNode<Smi> phi_bb70_13;
  TNode<Smi> phi_bb70_14;
  TNode<Smi> phi_bb70_15;
  TNode<IntPtrT> tmp127;
  TNode<IntPtrT> tmp128;
  TNode<IntPtrT> tmp129;
  TNode<Smi> tmp130;
  TNode<IntPtrT> tmp131;
  TNode<Smi> tmp132;
  TNode<Smi> tmp133;
  TNode<IntPtrT> tmp134;
  TNode<UintPtrT> tmp135;
  TNode<UintPtrT> tmp136;
  TNode<BoolT> tmp137;
  if (block70.is_used()) {
    ca_.Bind(&block70, &phi_bb70_6, &phi_bb70_7, &phi_bb70_10, &phi_bb70_11, &phi_bb70_12, &phi_bb70_13, &phi_bb70_14, &phi_bb70_15);
    tmp127 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp128 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp129 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp130 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp129});
    tmp131 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp130});
    tmp132 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp133 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb70_10}, TNode<Smi>{tmp132});
    tmp134 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb70_10});
    tmp135 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp134});
    tmp136 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp131});
    tmp137 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp135}, TNode<UintPtrT>{tmp136});
    ca_.Branch(tmp137, &block94, std::vector<Node*>{phi_bb70_6, phi_bb70_7, phi_bb70_11, phi_bb70_12, phi_bb70_13, phi_bb70_14, phi_bb70_15, phi_bb70_10, phi_bb70_10}, &block95, std::vector<Node*>{phi_bb70_6, phi_bb70_7, phi_bb70_11, phi_bb70_12, phi_bb70_13, phi_bb70_14, phi_bb70_15, phi_bb70_10, phi_bb70_10});
  }

  TNode<Smi> phi_bb94_6;
  TNode<Smi> phi_bb94_7;
  TNode<Smi> phi_bb94_11;
  TNode<Smi> phi_bb94_12;
  TNode<Smi> phi_bb94_13;
  TNode<Smi> phi_bb94_14;
  TNode<Smi> phi_bb94_15;
  TNode<Smi> phi_bb94_21;
  TNode<Smi> phi_bb94_22;
  TNode<IntPtrT> tmp138;
  TNode<IntPtrT> tmp139;
  TNode<IntPtrT> tmp140;
  TNode<HeapObject> tmp141;
  TNode<IntPtrT> tmp142;
  TNode<IntPtrT> tmp143;
  TNode<IntPtrT> tmp144;
  TNode<IntPtrT> tmp145;
  TNode<Smi> tmp146;
  TNode<IntPtrT> tmp147;
  TNode<Smi> tmp148;
  TNode<Smi> tmp149;
  TNode<IntPtrT> tmp150;
  TNode<UintPtrT> tmp151;
  TNode<UintPtrT> tmp152;
  TNode<BoolT> tmp153;
  if (block94.is_used()) {
    ca_.Bind(&block94, &phi_bb94_6, &phi_bb94_7, &phi_bb94_11, &phi_bb94_12, &phi_bb94_13, &phi_bb94_14, &phi_bb94_15, &phi_bb94_21, &phi_bb94_22);
    tmp138 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp139 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp134}, TNode<IntPtrT>{tmp138});
    tmp140 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp127}, TNode<IntPtrT>{tmp139});
    std::tie(tmp141, tmp142) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp140}).Flatten();
    tmp143 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp144 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp145 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp146 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp145});
    tmp147 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp146});
    tmp148 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp149 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb94_11}, TNode<Smi>{tmp148});
    tmp150 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb94_11});
    tmp151 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp150});
    tmp152 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp147});
    tmp153 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp151}, TNode<UintPtrT>{tmp152});
    ca_.Branch(tmp153, &block101, std::vector<Node*>{phi_bb94_6, phi_bb94_7, phi_bb94_12, phi_bb94_13, phi_bb94_14, phi_bb94_15, phi_bb94_21, phi_bb94_22, phi_bb94_11, phi_bb94_11}, &block102, std::vector<Node*>{phi_bb94_6, phi_bb94_7, phi_bb94_12, phi_bb94_13, phi_bb94_14, phi_bb94_15, phi_bb94_21, phi_bb94_22, phi_bb94_11, phi_bb94_11});
  }

  TNode<Smi> phi_bb95_6;
  TNode<Smi> phi_bb95_7;
  TNode<Smi> phi_bb95_11;
  TNode<Smi> phi_bb95_12;
  TNode<Smi> phi_bb95_13;
  TNode<Smi> phi_bb95_14;
  TNode<Smi> phi_bb95_15;
  TNode<Smi> phi_bb95_21;
  TNode<Smi> phi_bb95_22;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_6, &phi_bb95_7, &phi_bb95_11, &phi_bb95_12, &phi_bb95_13, &phi_bb95_14, &phi_bb95_15, &phi_bb95_21, &phi_bb95_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb101_6;
  TNode<Smi> phi_bb101_7;
  TNode<Smi> phi_bb101_12;
  TNode<Smi> phi_bb101_13;
  TNode<Smi> phi_bb101_14;
  TNode<Smi> phi_bb101_15;
  TNode<Smi> phi_bb101_21;
  TNode<Smi> phi_bb101_22;
  TNode<Smi> phi_bb101_29;
  TNode<Smi> phi_bb101_30;
  TNode<IntPtrT> tmp154;
  TNode<IntPtrT> tmp155;
  TNode<IntPtrT> tmp156;
  TNode<HeapObject> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<Object> tmp159;
  TNode<Smi> tmp160;
  TNode<Smi> tmp161;
  TNode<Smi> tmp162;
  TNode<Smi> tmp163;
  TNode<Smi> tmp164;
  TNode<Smi> tmp165;
  TNode<BoolT> tmp166;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_6, &phi_bb101_7, &phi_bb101_12, &phi_bb101_13, &phi_bb101_14, &phi_bb101_15, &phi_bb101_21, &phi_bb101_22, &phi_bb101_29, &phi_bb101_30);
    tmp154 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp155 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp150}, TNode<IntPtrT>{tmp154});
    tmp156 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp143}, TNode<IntPtrT>{tmp155});
    std::tie(tmp157, tmp158) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp156}).Flatten();
    tmp159 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp157, tmp158});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp141, tmp142}, tmp159);
    tmp160 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp161 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb101_14}, TNode<Smi>{tmp160});
    tmp162 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp163 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb101_6}, TNode<Smi>{tmp162});
    tmp164 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp165 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp166 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp163}, TNode<Smi>{tmp165});
    ca_.Branch(tmp166, &block104, std::vector<Node*>{phi_bb101_7, phi_bb101_12, phi_bb101_13}, &block105, std::vector<Node*>{phi_bb101_7, phi_bb101_12, phi_bb101_13});
  }

  TNode<Smi> phi_bb102_6;
  TNode<Smi> phi_bb102_7;
  TNode<Smi> phi_bb102_12;
  TNode<Smi> phi_bb102_13;
  TNode<Smi> phi_bb102_14;
  TNode<Smi> phi_bb102_15;
  TNode<Smi> phi_bb102_21;
  TNode<Smi> phi_bb102_22;
  TNode<Smi> phi_bb102_29;
  TNode<Smi> phi_bb102_30;
  if (block102.is_used()) {
    ca_.Bind(&block102, &phi_bb102_6, &phi_bb102_7, &phi_bb102_12, &phi_bb102_13, &phi_bb102_14, &phi_bb102_15, &phi_bb102_21, &phi_bb102_22, &phi_bb102_29, &phi_bb102_30);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb104_7;
  TNode<Smi> phi_bb104_12;
  TNode<Smi> phi_bb104_13;
  if (block104.is_used()) {
    ca_.Bind(&block104, &phi_bb104_7, &phi_bb104_12, &phi_bb104_13);
    ca_.Goto(&block35, tmp163, phi_bb104_7, tmp133, tmp149, phi_bb104_12);
  }

  TNode<Smi> phi_bb105_7;
  TNode<Smi> phi_bb105_12;
  TNode<Smi> phi_bb105_13;
  TNode<BoolT> tmp167;
  if (block105.is_used()) {
    ca_.Bind(&block105, &phi_bb105_7, &phi_bb105_12, &phi_bb105_13);
    tmp167 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp161}, TNode<Smi>{phi_bb105_13});
    ca_.Branch(tmp167, &block106, std::vector<Node*>{phi_bb105_7, phi_bb105_12, phi_bb105_13}, &block107, std::vector<Node*>{phi_bb105_7, phi_bb105_12, phi_bb105_13});
  }

  TNode<Smi> phi_bb106_7;
  TNode<Smi> phi_bb106_12;
  TNode<Smi> phi_bb106_13;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_7, &phi_bb106_12, &phi_bb106_13);
    ca_.Goto(&block46, tmp163, phi_bb106_7, tmp133, tmp149, phi_bb106_12, phi_bb106_13, tmp161, tmp164);
  }

  TNode<Smi> phi_bb107_7;
  TNode<Smi> phi_bb107_12;
  TNode<Smi> phi_bb107_13;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_7, &phi_bb107_12, &phi_bb107_13);
    ca_.Goto(&block71, tmp163, phi_bb107_7, tmp133, tmp149, phi_bb107_12, phi_bb107_13, tmp161, tmp164);
  }

  TNode<Smi> phi_bb71_6;
  TNode<Smi> phi_bb71_7;
  TNode<Smi> phi_bb71_10;
  TNode<Smi> phi_bb71_11;
  TNode<Smi> phi_bb71_12;
  TNode<Smi> phi_bb71_13;
  TNode<Smi> phi_bb71_14;
  TNode<Smi> phi_bb71_15;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_6, &phi_bb71_7, &phi_bb71_10, &phi_bb71_11, &phi_bb71_12, &phi_bb71_13, &phi_bb71_14, &phi_bb71_15);
    ca_.Goto(&block47, phi_bb71_6, phi_bb71_7, phi_bb71_10, phi_bb71_11, phi_bb71_12, phi_bb71_13, phi_bb71_14, phi_bb71_15);
  }

  TNode<Smi> phi_bb46_6;
  TNode<Smi> phi_bb46_7;
  TNode<Smi> phi_bb46_10;
  TNode<Smi> phi_bb46_11;
  TNode<Smi> phi_bb46_12;
  TNode<Smi> phi_bb46_13;
  TNode<Smi> phi_bb46_14;
  TNode<Smi> phi_bb46_15;
  TNode<Smi> tmp168;
  TNode<Smi> tmp169;
  TNode<BoolT> tmp170;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_6, &phi_bb46_7, &phi_bb46_10, &phi_bb46_11, &phi_bb46_12, &phi_bb46_13, &phi_bb46_14, &phi_bb46_15);
    tmp168 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp169 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb46_13}, TNode<Smi>{tmp168});
    tmp170 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block110, phi_bb46_6, phi_bb46_7, phi_bb46_10, phi_bb46_11, phi_bb46_12, tmp169, phi_bb46_14, phi_bb46_15, tmp170);
  }

  TNode<Smi> phi_bb110_6;
  TNode<Smi> phi_bb110_7;
  TNode<Smi> phi_bb110_10;
  TNode<Smi> phi_bb110_11;
  TNode<Smi> phi_bb110_12;
  TNode<Smi> phi_bb110_13;
  TNode<Smi> phi_bb110_14;
  TNode<Smi> phi_bb110_15;
  TNode<BoolT> phi_bb110_16;
  TNode<Smi> tmp171;
  TNode<BoolT> tmp172;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_6, &phi_bb110_7, &phi_bb110_10, &phi_bb110_11, &phi_bb110_12, &phi_bb110_13, &phi_bb110_14, &phi_bb110_15, &phi_bb110_16);
    tmp171 = FromConstexpr_Smi_constexpr_int31_0(state_, kMinGallopWins_0(state_));
    tmp172 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb110_14}, TNode<Smi>{tmp171});
    ca_.Branch(tmp172, &block111, std::vector<Node*>{phi_bb110_6, phi_bb110_7, phi_bb110_10, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_14, phi_bb110_15, phi_bb110_16}, &block112, std::vector<Node*>{phi_bb110_6, phi_bb110_7, phi_bb110_10, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_14, phi_bb110_15, phi_bb110_16});
  }

  TNode<Smi> phi_bb111_6;
  TNode<Smi> phi_bb111_7;
  TNode<Smi> phi_bb111_10;
  TNode<Smi> phi_bb111_11;
  TNode<Smi> phi_bb111_12;
  TNode<Smi> phi_bb111_13;
  TNode<Smi> phi_bb111_14;
  TNode<Smi> phi_bb111_15;
  TNode<BoolT> phi_bb111_16;
  TNode<BoolT> tmp173;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_6, &phi_bb111_7, &phi_bb111_10, &phi_bb111_11, &phi_bb111_12, &phi_bb111_13, &phi_bb111_14, &phi_bb111_15, &phi_bb111_16);
    tmp173 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block113, phi_bb111_6, phi_bb111_7, phi_bb111_10, phi_bb111_11, phi_bb111_12, phi_bb111_13, phi_bb111_14, phi_bb111_15, phi_bb111_16, tmp173);
  }

  TNode<Smi> phi_bb112_6;
  TNode<Smi> phi_bb112_7;
  TNode<Smi> phi_bb112_10;
  TNode<Smi> phi_bb112_11;
  TNode<Smi> phi_bb112_12;
  TNode<Smi> phi_bb112_13;
  TNode<Smi> phi_bb112_14;
  TNode<Smi> phi_bb112_15;
  TNode<BoolT> phi_bb112_16;
  TNode<Smi> tmp174;
  TNode<BoolT> tmp175;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_6, &phi_bb112_7, &phi_bb112_10, &phi_bb112_11, &phi_bb112_12, &phi_bb112_13, &phi_bb112_14, &phi_bb112_15, &phi_bb112_16);
    tmp174 = FromConstexpr_Smi_constexpr_int31_0(state_, kMinGallopWins_0(state_));
    tmp175 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb112_15}, TNode<Smi>{tmp174});
    ca_.Goto(&block113, phi_bb112_6, phi_bb112_7, phi_bb112_10, phi_bb112_11, phi_bb112_12, phi_bb112_13, phi_bb112_14, phi_bb112_15, phi_bb112_16, tmp175);
  }

  TNode<Smi> phi_bb113_6;
  TNode<Smi> phi_bb113_7;
  TNode<Smi> phi_bb113_10;
  TNode<Smi> phi_bb113_11;
  TNode<Smi> phi_bb113_12;
  TNode<Smi> phi_bb113_13;
  TNode<Smi> phi_bb113_14;
  TNode<Smi> phi_bb113_15;
  TNode<BoolT> phi_bb113_16;
  TNode<BoolT> phi_bb113_18;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_6, &phi_bb113_7, &phi_bb113_10, &phi_bb113_11, &phi_bb113_12, &phi_bb113_13, &phi_bb113_14, &phi_bb113_15, &phi_bb113_16, &phi_bb113_18);
    ca_.Branch(phi_bb113_18, &block114, std::vector<Node*>{phi_bb113_6, phi_bb113_7, phi_bb113_10, phi_bb113_11, phi_bb113_12, phi_bb113_13, phi_bb113_14, phi_bb113_15, phi_bb113_16}, &block115, std::vector<Node*>{phi_bb113_6, phi_bb113_7, phi_bb113_10, phi_bb113_11, phi_bb113_12, phi_bb113_13, phi_bb113_14, phi_bb113_15, phi_bb113_16});
  }

  TNode<Smi> phi_bb114_6;
  TNode<Smi> phi_bb114_7;
  TNode<Smi> phi_bb114_10;
  TNode<Smi> phi_bb114_11;
  TNode<Smi> phi_bb114_12;
  TNode<Smi> phi_bb114_13;
  TNode<Smi> phi_bb114_14;
  TNode<Smi> phi_bb114_15;
  TNode<BoolT> phi_bb114_16;
  TNode<BoolT> tmp176;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_6, &phi_bb114_7, &phi_bb114_10, &phi_bb114_11, &phi_bb114_12, &phi_bb114_13, &phi_bb114_14, &phi_bb114_15, &phi_bb114_16);
    tmp176 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block116, phi_bb114_6, phi_bb114_7, phi_bb114_10, phi_bb114_11, phi_bb114_12, phi_bb114_13, phi_bb114_14, phi_bb114_15, phi_bb114_16, tmp176);
  }

  TNode<Smi> phi_bb115_6;
  TNode<Smi> phi_bb115_7;
  TNode<Smi> phi_bb115_10;
  TNode<Smi> phi_bb115_11;
  TNode<Smi> phi_bb115_12;
  TNode<Smi> phi_bb115_13;
  TNode<Smi> phi_bb115_14;
  TNode<Smi> phi_bb115_15;
  TNode<BoolT> phi_bb115_16;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_6, &phi_bb115_7, &phi_bb115_10, &phi_bb115_11, &phi_bb115_12, &phi_bb115_13, &phi_bb115_14, &phi_bb115_15, &phi_bb115_16);
    ca_.Goto(&block116, phi_bb115_6, phi_bb115_7, phi_bb115_10, phi_bb115_11, phi_bb115_12, phi_bb115_13, phi_bb115_14, phi_bb115_15, phi_bb115_16, phi_bb115_16);
  }

  TNode<Smi> phi_bb116_6;
  TNode<Smi> phi_bb116_7;
  TNode<Smi> phi_bb116_10;
  TNode<Smi> phi_bb116_11;
  TNode<Smi> phi_bb116_12;
  TNode<Smi> phi_bb116_13;
  TNode<Smi> phi_bb116_14;
  TNode<Smi> phi_bb116_15;
  TNode<BoolT> phi_bb116_16;
  TNode<BoolT> phi_bb116_18;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_6, &phi_bb116_7, &phi_bb116_10, &phi_bb116_11, &phi_bb116_12, &phi_bb116_13, &phi_bb116_14, &phi_bb116_15, &phi_bb116_16, &phi_bb116_18);
    ca_.Branch(phi_bb116_18, &block108, std::vector<Node*>{phi_bb116_6, phi_bb116_7, phi_bb116_10, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_14, phi_bb116_15, phi_bb116_16}, &block109, std::vector<Node*>{phi_bb116_6, phi_bb116_7, phi_bb116_10, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_14, phi_bb116_15, phi_bb116_16});
  }

  TNode<Smi> phi_bb108_6;
  TNode<Smi> phi_bb108_7;
  TNode<Smi> phi_bb108_10;
  TNode<Smi> phi_bb108_11;
  TNode<Smi> phi_bb108_12;
  TNode<Smi> phi_bb108_13;
  TNode<Smi> phi_bb108_14;
  TNode<Smi> phi_bb108_15;
  TNode<BoolT> phi_bb108_16;
  TNode<BoolT> tmp177;
  TNode<Smi> tmp178;
  TNode<Smi> tmp179;
  TNode<Smi> tmp180;
  TNode<Smi> tmp181;
  TNode<IntPtrT> tmp182;
  TNode<IntPtrT> tmp183;
  TNode<IntPtrT> tmp184;
  TNode<IntPtrT> tmp185;
  TNode<Smi> tmp186;
  TNode<IntPtrT> tmp187;
  TNode<IntPtrT> tmp188;
  TNode<UintPtrT> tmp189;
  TNode<UintPtrT> tmp190;
  TNode<BoolT> tmp191;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_6, &phi_bb108_7, &phi_bb108_10, &phi_bb108_11, &phi_bb108_12, &phi_bb108_13, &phi_bb108_14, &phi_bb108_15, &phi_bb108_16);
    tmp177 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp178 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp179 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb108_13}, TNode<Smi>{tmp178});
    tmp180 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp181 = CodeStubAssembler(state_).SmiMax(TNode<Smi>{tmp180}, TNode<Smi>{tmp179});
    tmp182 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp182}, tmp181);
    tmp183 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp184 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp185 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp186 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp185});
    tmp187 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp186});
    tmp188 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb108_12});
    tmp189 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp188});
    tmp190 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp187});
    tmp191 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp189}, TNode<UintPtrT>{tmp190});
    ca_.Branch(tmp191, &block128, std::vector<Node*>{phi_bb108_6, phi_bb108_7, phi_bb108_10, phi_bb108_11, phi_bb108_12, phi_bb108_14, phi_bb108_15, phi_bb108_12, phi_bb108_12}, &block129, std::vector<Node*>{phi_bb108_6, phi_bb108_7, phi_bb108_10, phi_bb108_11, phi_bb108_12, phi_bb108_14, phi_bb108_15, phi_bb108_12, phi_bb108_12});
  }

  TNode<Smi> phi_bb128_6;
  TNode<Smi> phi_bb128_7;
  TNode<Smi> phi_bb128_10;
  TNode<Smi> phi_bb128_11;
  TNode<Smi> phi_bb128_12;
  TNode<Smi> phi_bb128_14;
  TNode<Smi> phi_bb128_15;
  TNode<Smi> phi_bb128_22;
  TNode<Smi> phi_bb128_23;
  TNode<IntPtrT> tmp192;
  TNode<IntPtrT> tmp193;
  TNode<IntPtrT> tmp194;
  TNode<HeapObject> tmp195;
  TNode<IntPtrT> tmp196;
  TNode<Object> tmp197;
  TNode<Object> tmp198;
  TNode<Smi> tmp199;
  TNode<Smi> tmp200;
  TNode<Smi> tmp201;
  TNode<BoolT> tmp202;
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_6, &phi_bb128_7, &phi_bb128_10, &phi_bb128_11, &phi_bb128_12, &phi_bb128_14, &phi_bb128_15, &phi_bb128_22, &phi_bb128_23);
    tmp192 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp193 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp188}, TNode<IntPtrT>{tmp192});
    tmp194 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp183}, TNode<IntPtrT>{tmp193});
    std::tie(tmp195, tmp196) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp194}).Flatten();
    tmp197 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp195, tmp196});
    tmp198 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp197});
    tmp199 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp200 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kGallopRight, p_context, p_sortState, tmp2, tmp198, phi_bb128_11, phi_bb128_6, tmp199));
    tmp201 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp202 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp200}, TNode<Smi>{tmp201});
    ca_.Branch(tmp202, &block135, std::vector<Node*>{phi_bb128_6, phi_bb128_7, phi_bb128_10, phi_bb128_11, phi_bb128_12, phi_bb128_15}, &block136, std::vector<Node*>{phi_bb128_6, phi_bb128_7, phi_bb128_10, phi_bb128_11, phi_bb128_12, phi_bb128_15});
  }

  TNode<Smi> phi_bb129_6;
  TNode<Smi> phi_bb129_7;
  TNode<Smi> phi_bb129_10;
  TNode<Smi> phi_bb129_11;
  TNode<Smi> phi_bb129_12;
  TNode<Smi> phi_bb129_14;
  TNode<Smi> phi_bb129_15;
  TNode<Smi> phi_bb129_22;
  TNode<Smi> phi_bb129_23;
  if (block129.is_used()) {
    ca_.Bind(&block129, &phi_bb129_6, &phi_bb129_7, &phi_bb129_10, &phi_bb129_11, &phi_bb129_12, &phi_bb129_14, &phi_bb129_15, &phi_bb129_22, &phi_bb129_23);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb135_6;
  TNode<Smi> phi_bb135_7;
  TNode<Smi> phi_bb135_10;
  TNode<Smi> phi_bb135_11;
  TNode<Smi> phi_bb135_12;
  TNode<Smi> phi_bb135_15;
  TNode<Object> tmp203;
  TNode<Smi> tmp204;
  TNode<Smi> tmp205;
  TNode<Smi> tmp206;
  TNode<Smi> tmp207;
  TNode<BoolT> tmp208;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_6, &phi_bb135_7, &phi_bb135_10, &phi_bb135_11, &phi_bb135_12, &phi_bb135_15);
    tmp203 = CodeStubAssembler(state_).CallBuiltin(Builtins::kCopy, p_context, tmp2, phi_bb135_11, tmp1, phi_bb135_10, tmp200);
    tmp204 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb135_10}, TNode<Smi>{tmp200});
    tmp205 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb135_11}, TNode<Smi>{tmp200});
    tmp206 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb135_6}, TNode<Smi>{tmp200});
    tmp207 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp208 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp206}, TNode<Smi>{tmp207});
    ca_.Branch(tmp208, &block137, std::vector<Node*>{phi_bb135_7, phi_bb135_12, phi_bb135_15}, &block138, std::vector<Node*>{phi_bb135_7, phi_bb135_12, phi_bb135_15});
  }

  TNode<Smi> phi_bb137_7;
  TNode<Smi> phi_bb137_12;
  TNode<Smi> phi_bb137_15;
  if (block137.is_used()) {
    ca_.Bind(&block137, &phi_bb137_7, &phi_bb137_12, &phi_bb137_15);
    ca_.Goto(&block35, tmp206, phi_bb137_7, tmp204, tmp205, phi_bb137_12);
  }

  TNode<Smi> phi_bb138_7;
  TNode<Smi> phi_bb138_12;
  TNode<Smi> phi_bb138_15;
  TNode<Smi> tmp209;
  TNode<BoolT> tmp210;
  if (block138.is_used()) {
    ca_.Bind(&block138, &phi_bb138_7, &phi_bb138_12, &phi_bb138_15);
    tmp209 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp210 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp206}, TNode<Smi>{tmp209});
    ca_.Branch(tmp210, &block139, std::vector<Node*>{phi_bb138_7, phi_bb138_12, phi_bb138_15}, &block140, std::vector<Node*>{phi_bb138_7, phi_bb138_12, phi_bb138_15});
  }

  TNode<Smi> phi_bb139_7;
  TNode<Smi> phi_bb139_12;
  TNode<Smi> phi_bb139_15;
  if (block139.is_used()) {
    ca_.Bind(&block139, &phi_bb139_7, &phi_bb139_12, &phi_bb139_15);
    ca_.Goto(&block37, tmp206, phi_bb139_7, tmp204, tmp205, phi_bb139_12);
  }

  TNode<Smi> phi_bb140_7;
  TNode<Smi> phi_bb140_12;
  TNode<Smi> phi_bb140_15;
  if (block140.is_used()) {
    ca_.Bind(&block140, &phi_bb140_7, &phi_bb140_12, &phi_bb140_15);
    ca_.Goto(&block136, tmp206, phi_bb140_7, tmp204, tmp205, phi_bb140_12, phi_bb140_15);
  }

  TNode<Smi> phi_bb136_6;
  TNode<Smi> phi_bb136_7;
  TNode<Smi> phi_bb136_10;
  TNode<Smi> phi_bb136_11;
  TNode<Smi> phi_bb136_12;
  TNode<Smi> phi_bb136_15;
  TNode<IntPtrT> tmp211;
  TNode<IntPtrT> tmp212;
  TNode<IntPtrT> tmp213;
  TNode<Smi> tmp214;
  TNode<IntPtrT> tmp215;
  TNode<Smi> tmp216;
  TNode<Smi> tmp217;
  TNode<IntPtrT> tmp218;
  TNode<UintPtrT> tmp219;
  TNode<UintPtrT> tmp220;
  TNode<BoolT> tmp221;
  if (block136.is_used()) {
    ca_.Bind(&block136, &phi_bb136_6, &phi_bb136_7, &phi_bb136_10, &phi_bb136_11, &phi_bb136_12, &phi_bb136_15);
    tmp211 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp212 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp213 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp214 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp213});
    tmp215 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp214});
    tmp216 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp217 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb136_10}, TNode<Smi>{tmp216});
    tmp218 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb136_10});
    tmp219 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp218});
    tmp220 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp215});
    tmp221 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp219}, TNode<UintPtrT>{tmp220});
    ca_.Branch(tmp221, &block145, std::vector<Node*>{phi_bb136_6, phi_bb136_7, phi_bb136_11, phi_bb136_12, phi_bb136_15, phi_bb136_10, phi_bb136_10}, &block146, std::vector<Node*>{phi_bb136_6, phi_bb136_7, phi_bb136_11, phi_bb136_12, phi_bb136_15, phi_bb136_10, phi_bb136_10});
  }

  TNode<Smi> phi_bb145_6;
  TNode<Smi> phi_bb145_7;
  TNode<Smi> phi_bb145_11;
  TNode<Smi> phi_bb145_12;
  TNode<Smi> phi_bb145_15;
  TNode<Smi> phi_bb145_21;
  TNode<Smi> phi_bb145_22;
  TNode<IntPtrT> tmp222;
  TNode<IntPtrT> tmp223;
  TNode<IntPtrT> tmp224;
  TNode<HeapObject> tmp225;
  TNode<IntPtrT> tmp226;
  TNode<IntPtrT> tmp227;
  TNode<IntPtrT> tmp228;
  TNode<IntPtrT> tmp229;
  TNode<Smi> tmp230;
  TNode<IntPtrT> tmp231;
  TNode<Smi> tmp232;
  TNode<Smi> tmp233;
  TNode<IntPtrT> tmp234;
  TNode<UintPtrT> tmp235;
  TNode<UintPtrT> tmp236;
  TNode<BoolT> tmp237;
  if (block145.is_used()) {
    ca_.Bind(&block145, &phi_bb145_6, &phi_bb145_7, &phi_bb145_11, &phi_bb145_12, &phi_bb145_15, &phi_bb145_21, &phi_bb145_22);
    tmp222 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp223 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp218}, TNode<IntPtrT>{tmp222});
    tmp224 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp211}, TNode<IntPtrT>{tmp223});
    std::tie(tmp225, tmp226) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp224}).Flatten();
    tmp227 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp228 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp229 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp230 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp229});
    tmp231 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp230});
    tmp232 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp233 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb145_12}, TNode<Smi>{tmp232});
    tmp234 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb145_12});
    tmp235 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp234});
    tmp236 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp231});
    tmp237 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp235}, TNode<UintPtrT>{tmp236});
    ca_.Branch(tmp237, &block152, std::vector<Node*>{phi_bb145_6, phi_bb145_7, phi_bb145_11, phi_bb145_15, phi_bb145_21, phi_bb145_22, phi_bb145_12, phi_bb145_12}, &block153, std::vector<Node*>{phi_bb145_6, phi_bb145_7, phi_bb145_11, phi_bb145_15, phi_bb145_21, phi_bb145_22, phi_bb145_12, phi_bb145_12});
  }

  TNode<Smi> phi_bb146_6;
  TNode<Smi> phi_bb146_7;
  TNode<Smi> phi_bb146_11;
  TNode<Smi> phi_bb146_12;
  TNode<Smi> phi_bb146_15;
  TNode<Smi> phi_bb146_21;
  TNode<Smi> phi_bb146_22;
  if (block146.is_used()) {
    ca_.Bind(&block146, &phi_bb146_6, &phi_bb146_7, &phi_bb146_11, &phi_bb146_12, &phi_bb146_15, &phi_bb146_21, &phi_bb146_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb152_6;
  TNode<Smi> phi_bb152_7;
  TNode<Smi> phi_bb152_11;
  TNode<Smi> phi_bb152_15;
  TNode<Smi> phi_bb152_21;
  TNode<Smi> phi_bb152_22;
  TNode<Smi> phi_bb152_29;
  TNode<Smi> phi_bb152_30;
  TNode<IntPtrT> tmp238;
  TNode<IntPtrT> tmp239;
  TNode<IntPtrT> tmp240;
  TNode<HeapObject> tmp241;
  TNode<IntPtrT> tmp242;
  TNode<Object> tmp243;
  TNode<Smi> tmp244;
  TNode<Smi> tmp245;
  TNode<Smi> tmp246;
  TNode<BoolT> tmp247;
  if (block152.is_used()) {
    ca_.Bind(&block152, &phi_bb152_6, &phi_bb152_7, &phi_bb152_11, &phi_bb152_15, &phi_bb152_21, &phi_bb152_22, &phi_bb152_29, &phi_bb152_30);
    tmp238 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp239 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp234}, TNode<IntPtrT>{tmp238});
    tmp240 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp227}, TNode<IntPtrT>{tmp239});
    std::tie(tmp241, tmp242) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp240}).Flatten();
    tmp243 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp241, tmp242});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp225, tmp226}, tmp243);
    tmp244 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp245 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb152_7}, TNode<Smi>{tmp244});
    tmp246 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp247 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp245}, TNode<Smi>{tmp246});
    ca_.Branch(tmp247, &block155, std::vector<Node*>{phi_bb152_6, phi_bb152_11, phi_bb152_15}, &block156, std::vector<Node*>{phi_bb152_6, phi_bb152_11, phi_bb152_15});
  }

  TNode<Smi> phi_bb153_6;
  TNode<Smi> phi_bb153_7;
  TNode<Smi> phi_bb153_11;
  TNode<Smi> phi_bb153_15;
  TNode<Smi> phi_bb153_21;
  TNode<Smi> phi_bb153_22;
  TNode<Smi> phi_bb153_29;
  TNode<Smi> phi_bb153_30;
  if (block153.is_used()) {
    ca_.Bind(&block153, &phi_bb153_6, &phi_bb153_7, &phi_bb153_11, &phi_bb153_15, &phi_bb153_21, &phi_bb153_22, &phi_bb153_29, &phi_bb153_30);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb155_6;
  TNode<Smi> phi_bb155_11;
  TNode<Smi> phi_bb155_15;
  if (block155.is_used()) {
    ca_.Bind(&block155, &phi_bb155_6, &phi_bb155_11, &phi_bb155_15);
    ca_.Goto(&block37, phi_bb155_6, tmp245, tmp217, phi_bb155_11, tmp233);
  }

  TNode<Smi> phi_bb156_6;
  TNode<Smi> phi_bb156_11;
  TNode<Smi> phi_bb156_15;
  TNode<IntPtrT> tmp248;
  TNode<IntPtrT> tmp249;
  TNode<IntPtrT> tmp250;
  TNode<Smi> tmp251;
  TNode<IntPtrT> tmp252;
  TNode<IntPtrT> tmp253;
  TNode<UintPtrT> tmp254;
  TNode<UintPtrT> tmp255;
  TNode<BoolT> tmp256;
  if (block156.is_used()) {
    ca_.Bind(&block156, &phi_bb156_6, &phi_bb156_11, &phi_bb156_15);
    tmp248 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp249 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp250 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp251 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp250});
    tmp252 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp251});
    tmp253 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb156_11});
    tmp254 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp253});
    tmp255 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp252});
    tmp256 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp254}, TNode<UintPtrT>{tmp255});
    ca_.Branch(tmp256, &block161, std::vector<Node*>{phi_bb156_6, phi_bb156_11, phi_bb156_15, phi_bb156_11, phi_bb156_11}, &block162, std::vector<Node*>{phi_bb156_6, phi_bb156_11, phi_bb156_15, phi_bb156_11, phi_bb156_11});
  }

  TNode<Smi> phi_bb161_6;
  TNode<Smi> phi_bb161_11;
  TNode<Smi> phi_bb161_15;
  TNode<Smi> phi_bb161_22;
  TNode<Smi> phi_bb161_23;
  TNode<IntPtrT> tmp257;
  TNode<IntPtrT> tmp258;
  TNode<IntPtrT> tmp259;
  TNode<HeapObject> tmp260;
  TNode<IntPtrT> tmp261;
  TNode<Object> tmp262;
  TNode<Object> tmp263;
  TNode<Smi> tmp264;
  TNode<Smi> tmp265;
  TNode<Smi> tmp266;
  TNode<BoolT> tmp267;
  if (block161.is_used()) {
    ca_.Bind(&block161, &phi_bb161_6, &phi_bb161_11, &phi_bb161_15, &phi_bb161_22, &phi_bb161_23);
    tmp257 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp258 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp253}, TNode<IntPtrT>{tmp257});
    tmp259 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp248}, TNode<IntPtrT>{tmp258});
    std::tie(tmp260, tmp261) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp259}).Flatten();
    tmp262 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp260, tmp261});
    tmp263 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp262});
    tmp264 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp265 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kGallopLeft, p_context, p_sortState, tmp1, tmp263, tmp233, tmp245, tmp264));
    tmp266 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp267 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp265}, TNode<Smi>{tmp266});
    ca_.Branch(tmp267, &block168, std::vector<Node*>{phi_bb161_6, phi_bb161_11}, &block169, std::vector<Node*>{phi_bb161_6, tmp245, tmp217, phi_bb161_11, tmp233});
  }

  TNode<Smi> phi_bb162_6;
  TNode<Smi> phi_bb162_11;
  TNode<Smi> phi_bb162_15;
  TNode<Smi> phi_bb162_22;
  TNode<Smi> phi_bb162_23;
  if (block162.is_used()) {
    ca_.Bind(&block162, &phi_bb162_6, &phi_bb162_11, &phi_bb162_15, &phi_bb162_22, &phi_bb162_23);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb168_6;
  TNode<Smi> phi_bb168_11;
  TNode<Object> tmp268;
  TNode<Smi> tmp269;
  TNode<Smi> tmp270;
  TNode<Smi> tmp271;
  TNode<Smi> tmp272;
  TNode<BoolT> tmp273;
  if (block168.is_used()) {
    ca_.Bind(&block168, &phi_bb168_6, &phi_bb168_11);
    tmp268 = CodeStubAssembler(state_).CallBuiltin(Builtins::kCopy, p_context, tmp1, tmp233, tmp1, tmp217, tmp265);
    tmp269 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp217}, TNode<Smi>{tmp265});
    tmp270 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp233}, TNode<Smi>{tmp265});
    tmp271 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp245}, TNode<Smi>{tmp265});
    tmp272 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp273 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp271}, TNode<Smi>{tmp272});
    ca_.Branch(tmp273, &block170, std::vector<Node*>{phi_bb168_6, phi_bb168_11}, &block171, std::vector<Node*>{phi_bb168_6, phi_bb168_11});
  }

  TNode<Smi> phi_bb170_6;
  TNode<Smi> phi_bb170_11;
  if (block170.is_used()) {
    ca_.Bind(&block170, &phi_bb170_6, &phi_bb170_11);
    ca_.Goto(&block37, phi_bb170_6, tmp271, tmp269, phi_bb170_11, tmp270);
  }

  TNode<Smi> phi_bb171_6;
  TNode<Smi> phi_bb171_11;
  if (block171.is_used()) {
    ca_.Bind(&block171, &phi_bb171_6, &phi_bb171_11);
    ca_.Goto(&block169, phi_bb171_6, tmp271, tmp269, phi_bb171_11, tmp270);
  }

  TNode<Smi> phi_bb169_6;
  TNode<Smi> phi_bb169_7;
  TNode<Smi> phi_bb169_10;
  TNode<Smi> phi_bb169_11;
  TNode<Smi> phi_bb169_12;
  TNode<IntPtrT> tmp274;
  TNode<IntPtrT> tmp275;
  TNode<IntPtrT> tmp276;
  TNode<Smi> tmp277;
  TNode<IntPtrT> tmp278;
  TNode<Smi> tmp279;
  TNode<Smi> tmp280;
  TNode<IntPtrT> tmp281;
  TNode<UintPtrT> tmp282;
  TNode<UintPtrT> tmp283;
  TNode<BoolT> tmp284;
  if (block169.is_used()) {
    ca_.Bind(&block169, &phi_bb169_6, &phi_bb169_7, &phi_bb169_10, &phi_bb169_11, &phi_bb169_12);
    tmp274 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp275 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp276 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp277 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp276});
    tmp278 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp277});
    tmp279 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp280 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb169_10}, TNode<Smi>{tmp279});
    tmp281 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb169_10});
    tmp282 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp281});
    tmp283 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp278});
    tmp284 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp282}, TNode<UintPtrT>{tmp283});
    ca_.Branch(tmp284, &block176, std::vector<Node*>{phi_bb169_6, phi_bb169_7, phi_bb169_11, phi_bb169_12, phi_bb169_10, phi_bb169_10}, &block177, std::vector<Node*>{phi_bb169_6, phi_bb169_7, phi_bb169_11, phi_bb169_12, phi_bb169_10, phi_bb169_10});
  }

  TNode<Smi> phi_bb176_6;
  TNode<Smi> phi_bb176_7;
  TNode<Smi> phi_bb176_11;
  TNode<Smi> phi_bb176_12;
  TNode<Smi> phi_bb176_21;
  TNode<Smi> phi_bb176_22;
  TNode<IntPtrT> tmp285;
  TNode<IntPtrT> tmp286;
  TNode<IntPtrT> tmp287;
  TNode<HeapObject> tmp288;
  TNode<IntPtrT> tmp289;
  TNode<IntPtrT> tmp290;
  TNode<IntPtrT> tmp291;
  TNode<IntPtrT> tmp292;
  TNode<Smi> tmp293;
  TNode<IntPtrT> tmp294;
  TNode<Smi> tmp295;
  TNode<Smi> tmp296;
  TNode<IntPtrT> tmp297;
  TNode<UintPtrT> tmp298;
  TNode<UintPtrT> tmp299;
  TNode<BoolT> tmp300;
  if (block176.is_used()) {
    ca_.Bind(&block176, &phi_bb176_6, &phi_bb176_7, &phi_bb176_11, &phi_bb176_12, &phi_bb176_21, &phi_bb176_22);
    tmp285 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp286 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp281}, TNode<IntPtrT>{tmp285});
    tmp287 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp274}, TNode<IntPtrT>{tmp286});
    std::tie(tmp288, tmp289) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp287}).Flatten();
    tmp290 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp291 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp292 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp293 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp292});
    tmp294 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp293});
    tmp295 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp296 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb176_11}, TNode<Smi>{tmp295});
    tmp297 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb176_11});
    tmp298 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp297});
    tmp299 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp294});
    tmp300 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp298}, TNode<UintPtrT>{tmp299});
    ca_.Branch(tmp300, &block183, std::vector<Node*>{phi_bb176_6, phi_bb176_7, phi_bb176_12, phi_bb176_21, phi_bb176_22, phi_bb176_11, phi_bb176_11}, &block184, std::vector<Node*>{phi_bb176_6, phi_bb176_7, phi_bb176_12, phi_bb176_21, phi_bb176_22, phi_bb176_11, phi_bb176_11});
  }

  TNode<Smi> phi_bb177_6;
  TNode<Smi> phi_bb177_7;
  TNode<Smi> phi_bb177_11;
  TNode<Smi> phi_bb177_12;
  TNode<Smi> phi_bb177_21;
  TNode<Smi> phi_bb177_22;
  if (block177.is_used()) {
    ca_.Bind(&block177, &phi_bb177_6, &phi_bb177_7, &phi_bb177_11, &phi_bb177_12, &phi_bb177_21, &phi_bb177_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb183_6;
  TNode<Smi> phi_bb183_7;
  TNode<Smi> phi_bb183_12;
  TNode<Smi> phi_bb183_21;
  TNode<Smi> phi_bb183_22;
  TNode<Smi> phi_bb183_29;
  TNode<Smi> phi_bb183_30;
  TNode<IntPtrT> tmp301;
  TNode<IntPtrT> tmp302;
  TNode<IntPtrT> tmp303;
  TNode<HeapObject> tmp304;
  TNode<IntPtrT> tmp305;
  TNode<Object> tmp306;
  TNode<Smi> tmp307;
  TNode<Smi> tmp308;
  TNode<Smi> tmp309;
  TNode<BoolT> tmp310;
  if (block183.is_used()) {
    ca_.Bind(&block183, &phi_bb183_6, &phi_bb183_7, &phi_bb183_12, &phi_bb183_21, &phi_bb183_22, &phi_bb183_29, &phi_bb183_30);
    tmp301 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp302 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp297}, TNode<IntPtrT>{tmp301});
    tmp303 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp290}, TNode<IntPtrT>{tmp302});
    std::tie(tmp304, tmp305) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp303}).Flatten();
    tmp306 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp304, tmp305});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp288, tmp289}, tmp306);
    tmp307 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp308 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb183_6}, TNode<Smi>{tmp307});
    tmp309 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp310 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp308}, TNode<Smi>{tmp309});
    ca_.Branch(tmp310, &block186, std::vector<Node*>{phi_bb183_7, phi_bb183_12}, &block187, std::vector<Node*>{phi_bb183_7, phi_bb183_12});
  }

  TNode<Smi> phi_bb184_6;
  TNode<Smi> phi_bb184_7;
  TNode<Smi> phi_bb184_12;
  TNode<Smi> phi_bb184_21;
  TNode<Smi> phi_bb184_22;
  TNode<Smi> phi_bb184_29;
  TNode<Smi> phi_bb184_30;
  if (block184.is_used()) {
    ca_.Bind(&block184, &phi_bb184_6, &phi_bb184_7, &phi_bb184_12, &phi_bb184_21, &phi_bb184_22, &phi_bb184_29, &phi_bb184_30);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb186_7;
  TNode<Smi> phi_bb186_12;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_7, &phi_bb186_12);
    ca_.Goto(&block35, tmp308, phi_bb186_7, tmp280, tmp296, phi_bb186_12);
  }

  TNode<Smi> phi_bb187_7;
  TNode<Smi> phi_bb187_12;
  if (block187.is_used()) {
    ca_.Bind(&block187, &phi_bb187_7, &phi_bb187_12);
    ca_.Goto(&block110, tmp308, phi_bb187_7, tmp280, tmp296, phi_bb187_12, tmp181, tmp200, tmp265, tmp177);
  }

  TNode<Smi> phi_bb109_6;
  TNode<Smi> phi_bb109_7;
  TNode<Smi> phi_bb109_10;
  TNode<Smi> phi_bb109_11;
  TNode<Smi> phi_bb109_12;
  TNode<Smi> phi_bb109_13;
  TNode<Smi> phi_bb109_14;
  TNode<Smi> phi_bb109_15;
  TNode<BoolT> phi_bb109_16;
  TNode<Smi> tmp311;
  TNode<Smi> tmp312;
  TNode<IntPtrT> tmp313;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_6, &phi_bb109_7, &phi_bb109_10, &phi_bb109_11, &phi_bb109_12, &phi_bb109_13, &phi_bb109_14, &phi_bb109_15, &phi_bb109_16);
    tmp311 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp312 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb109_13}, TNode<Smi>{tmp311});
    tmp313 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp313}, tmp312);
    ca_.Goto(&block44, phi_bb109_6, phi_bb109_7, phi_bb109_10, phi_bb109_11, phi_bb109_12, tmp312);
  }

  TNode<Smi> phi_bb43_6;
  TNode<Smi> phi_bb43_7;
  TNode<Smi> phi_bb43_10;
  TNode<Smi> phi_bb43_11;
  TNode<Smi> phi_bb43_12;
  TNode<Smi> phi_bb43_13;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_6, &phi_bb43_7, &phi_bb43_10, &phi_bb43_11, &phi_bb43_12, &phi_bb43_13);
    ca_.Goto(&block36, phi_bb43_6, phi_bb43_7, phi_bb43_10, phi_bb43_11, phi_bb43_12);
  }

  TNode<Smi> phi_bb37_6;
  TNode<Smi> phi_bb37_7;
  TNode<Smi> phi_bb37_10;
  TNode<Smi> phi_bb37_11;
  TNode<Smi> phi_bb37_12;
  TNode<Smi> tmp314;
  TNode<BoolT> tmp315;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_6, &phi_bb37_7, &phi_bb37_10, &phi_bb37_11, &phi_bb37_12);
    tmp314 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp315 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb37_6}, TNode<Smi>{tmp314});
    ca_.Branch(tmp315, &block188, std::vector<Node*>{phi_bb37_6, phi_bb37_7, phi_bb37_10, phi_bb37_11, phi_bb37_12}, &block189, std::vector<Node*>{phi_bb37_6, phi_bb37_7, phi_bb37_10, phi_bb37_11, phi_bb37_12});
  }

  TNode<Smi> phi_bb188_6;
  TNode<Smi> phi_bb188_7;
  TNode<Smi> phi_bb188_10;
  TNode<Smi> phi_bb188_11;
  TNode<Smi> phi_bb188_12;
  TNode<Object> tmp316;
  if (block188.is_used()) {
    ca_.Bind(&block188, &phi_bb188_6, &phi_bb188_7, &phi_bb188_10, &phi_bb188_11, &phi_bb188_12);
    tmp316 = CodeStubAssembler(state_).CallBuiltin(Builtins::kCopy, p_context, tmp2, phi_bb188_11, tmp1, phi_bb188_10, phi_bb188_6);
    ca_.Goto(&block189, phi_bb188_6, phi_bb188_7, phi_bb188_10, phi_bb188_11, phi_bb188_12);
  }

  TNode<Smi> phi_bb189_6;
  TNode<Smi> phi_bb189_7;
  TNode<Smi> phi_bb189_10;
  TNode<Smi> phi_bb189_11;
  TNode<Smi> phi_bb189_12;
  if (block189.is_used()) {
    ca_.Bind(&block189, &phi_bb189_6, &phi_bb189_7, &phi_bb189_10, &phi_bb189_11, &phi_bb189_12);
    ca_.Goto(&block36, phi_bb189_6, phi_bb189_7, phi_bb189_10, phi_bb189_11, phi_bb189_12);
  }

  TNode<Smi> phi_bb36_6;
  TNode<Smi> phi_bb36_7;
  TNode<Smi> phi_bb36_10;
  TNode<Smi> phi_bb36_11;
  TNode<Smi> phi_bb36_12;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_6, &phi_bb36_7, &phi_bb36_10, &phi_bb36_11, &phi_bb36_12);
    ca_.Goto(&block34, phi_bb36_6, phi_bb36_7, phi_bb36_10, phi_bb36_11, phi_bb36_12);
  }

  TNode<Smi> phi_bb35_6;
  TNode<Smi> phi_bb35_7;
  TNode<Smi> phi_bb35_10;
  TNode<Smi> phi_bb35_11;
  TNode<Smi> phi_bb35_12;
  TNode<Object> tmp317;
  TNode<IntPtrT> tmp318;
  TNode<IntPtrT> tmp319;
  TNode<IntPtrT> tmp320;
  TNode<Smi> tmp321;
  TNode<IntPtrT> tmp322;
  TNode<Smi> tmp323;
  TNode<IntPtrT> tmp324;
  TNode<UintPtrT> tmp325;
  TNode<UintPtrT> tmp326;
  TNode<BoolT> tmp327;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_6, &phi_bb35_7, &phi_bb35_10, &phi_bb35_11, &phi_bb35_12);
    tmp317 = CodeStubAssembler(state_).CallBuiltin(Builtins::kCopy, p_context, tmp1, phi_bb35_12, tmp1, phi_bb35_10, phi_bb35_7);
    tmp318 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp319 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp320 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp321 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp320});
    tmp322 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp321});
    tmp323 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb35_10}, TNode<Smi>{phi_bb35_7});
    tmp324 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp323});
    tmp325 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp324});
    tmp326 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp322});
    tmp327 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp325}, TNode<UintPtrT>{tmp326});
    ca_.Branch(tmp327, &block201, std::vector<Node*>{phi_bb35_6, phi_bb35_7, phi_bb35_10, phi_bb35_11, phi_bb35_12}, &block202, std::vector<Node*>{phi_bb35_6, phi_bb35_7, phi_bb35_10, phi_bb35_11, phi_bb35_12});
  }

  TNode<Smi> phi_bb201_6;
  TNode<Smi> phi_bb201_7;
  TNode<Smi> phi_bb201_10;
  TNode<Smi> phi_bb201_11;
  TNode<Smi> phi_bb201_12;
  TNode<IntPtrT> tmp328;
  TNode<IntPtrT> tmp329;
  TNode<IntPtrT> tmp330;
  TNode<HeapObject> tmp331;
  TNode<IntPtrT> tmp332;
  TNode<IntPtrT> tmp333;
  TNode<IntPtrT> tmp334;
  TNode<IntPtrT> tmp335;
  TNode<Smi> tmp336;
  TNode<IntPtrT> tmp337;
  TNode<IntPtrT> tmp338;
  TNode<UintPtrT> tmp339;
  TNode<UintPtrT> tmp340;
  TNode<BoolT> tmp341;
  if (block201.is_used()) {
    ca_.Bind(&block201, &phi_bb201_6, &phi_bb201_7, &phi_bb201_10, &phi_bb201_11, &phi_bb201_12);
    tmp328 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp329 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp324}, TNode<IntPtrT>{tmp328});
    tmp330 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp318}, TNode<IntPtrT>{tmp329});
    std::tie(tmp331, tmp332) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp330}).Flatten();
    tmp333 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp334 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp335 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp336 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp335});
    tmp337 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp336});
    tmp338 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb201_11});
    tmp339 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp338});
    tmp340 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp337});
    tmp341 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp339}, TNode<UintPtrT>{tmp340});
    ca_.Branch(tmp341, &block208, std::vector<Node*>{phi_bb201_6, phi_bb201_7, phi_bb201_10, phi_bb201_11, phi_bb201_12, phi_bb201_11, phi_bb201_11}, &block209, std::vector<Node*>{phi_bb201_6, phi_bb201_7, phi_bb201_10, phi_bb201_11, phi_bb201_12, phi_bb201_11, phi_bb201_11});
  }

  TNode<Smi> phi_bb202_6;
  TNode<Smi> phi_bb202_7;
  TNode<Smi> phi_bb202_10;
  TNode<Smi> phi_bb202_11;
  TNode<Smi> phi_bb202_12;
  if (block202.is_used()) {
    ca_.Bind(&block202, &phi_bb202_6, &phi_bb202_7, &phi_bb202_10, &phi_bb202_11, &phi_bb202_12);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb208_6;
  TNode<Smi> phi_bb208_7;
  TNode<Smi> phi_bb208_10;
  TNode<Smi> phi_bb208_11;
  TNode<Smi> phi_bb208_12;
  TNode<Smi> phi_bb208_25;
  TNode<Smi> phi_bb208_26;
  TNode<IntPtrT> tmp342;
  TNode<IntPtrT> tmp343;
  TNode<IntPtrT> tmp344;
  TNode<HeapObject> tmp345;
  TNode<IntPtrT> tmp346;
  TNode<Object> tmp347;
  if (block208.is_used()) {
    ca_.Bind(&block208, &phi_bb208_6, &phi_bb208_7, &phi_bb208_10, &phi_bb208_11, &phi_bb208_12, &phi_bb208_25, &phi_bb208_26);
    tmp342 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp343 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp338}, TNode<IntPtrT>{tmp342});
    tmp344 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp333}, TNode<IntPtrT>{tmp343});
    std::tie(tmp345, tmp346) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp344}).Flatten();
    tmp347 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp345, tmp346});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp331, tmp332}, tmp347);
    ca_.Goto(&block34, phi_bb208_6, phi_bb208_7, phi_bb208_10, phi_bb208_11, phi_bb208_12);
  }

  TNode<Smi> phi_bb209_6;
  TNode<Smi> phi_bb209_7;
  TNode<Smi> phi_bb209_10;
  TNode<Smi> phi_bb209_11;
  TNode<Smi> phi_bb209_12;
  TNode<Smi> phi_bb209_25;
  TNode<Smi> phi_bb209_26;
  if (block209.is_used()) {
    ca_.Bind(&block209, &phi_bb209_6, &phi_bb209_7, &phi_bb209_10, &phi_bb209_11, &phi_bb209_12, &phi_bb209_25, &phi_bb209_26);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb34_6;
  TNode<Smi> phi_bb34_7;
  TNode<Smi> phi_bb34_10;
  TNode<Smi> phi_bb34_11;
  TNode<Smi> phi_bb34_12;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_6, &phi_bb34_7, &phi_bb34_10, &phi_bb34_11, &phi_bb34_12);
    ca_.Goto(&block211);
  }

    ca_.Bind(&block211);
}

void MergeHigh_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_baseA, TNode<Smi> p_lengthAArg, TNode<Smi> p_baseB, TNode<Smi> p_lengthBArg) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block86(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block87(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block88(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block89(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block70(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block94(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block95(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block101(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block102(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block104(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block105(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT, BoolT> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT, BoolT> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block128(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block129(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block135(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block137(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block138(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block136(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block143(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block144(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block150(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block151(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block153(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block154(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block159(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block160(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block166(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block168(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block169(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block170(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block171(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block167(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block176(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block177(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block183(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block184(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block186(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block187(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block109(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block188(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block189(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block205(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block206(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block212(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block213(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block215(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  TNode<FixedArray> tmp2;
  TNode<Smi> tmp3;
  TNode<Object> tmp4;
  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<Smi> tmp9;
  TNode<Smi> tmp10;
  TNode<Smi> tmp11;
  TNode<Smi> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<Smi> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<UintPtrT> tmp21;
  TNode<UintPtrT> tmp22;
  TNode<BoolT> tmp23;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = GetTempArray_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{p_lengthBArg});
    tmp3 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp4 = CodeStubAssembler(state_).CallBuiltin(Builtins::kCopy, p_context, tmp1, p_baseB, tmp2, tmp3, p_lengthBArg);
    tmp5 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_baseB}, TNode<Smi>{p_lengthBArg});
    tmp6 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp7 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp5}, TNode<Smi>{tmp6});
    tmp8 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp9 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_lengthBArg}, TNode<Smi>{tmp8});
    tmp10 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_baseA}, TNode<Smi>{p_lengthAArg});
    tmp11 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp12 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp10}, TNode<Smi>{tmp11});
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp16 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp15});
    tmp17 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp16});
    tmp18 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp19 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp7}, TNode<Smi>{tmp18});
    tmp20 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp7});
    tmp21 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp20});
    tmp22 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp17});
    tmp23 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp21}, TNode<UintPtrT>{tmp22});
    ca_.Branch(tmp23, &block24, std::vector<Node*>{}, &block25, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<HeapObject> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<Smi> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<Smi> tmp34;
  TNode<Smi> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<UintPtrT> tmp37;
  TNode<UintPtrT> tmp38;
  TNode<BoolT> tmp39;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp24 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp25 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp20}, TNode<IntPtrT>{tmp24});
    tmp26 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp25});
    std::tie(tmp27, tmp28) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp26}).Flatten();
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp32 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp31});
    tmp33 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp32});
    tmp34 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp35 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp12}, TNode<Smi>{tmp34});
    tmp36 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp12});
    tmp37 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp36});
    tmp38 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp33});
    tmp39 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp37}, TNode<UintPtrT>{tmp38});
    ca_.Branch(tmp39, &block31, std::vector<Node*>{}, &block32, std::vector<Node*>{});
  }

  if (block25.is_used()) {
    ca_.Bind(&block25);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<IntPtrT> tmp42;
  TNode<HeapObject> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<Object> tmp45;
  TNode<Smi> tmp46;
  TNode<Smi> tmp47;
  TNode<Smi> tmp48;
  TNode<BoolT> tmp49;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp40 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp41 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp40});
    tmp42 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp29}, TNode<IntPtrT>{tmp41});
    std::tie(tmp43, tmp44) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp42}).Flatten();
    tmp45 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp43, tmp44});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp27, tmp28}, tmp45);
    tmp46 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp47 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_lengthAArg}, TNode<Smi>{tmp46});
    tmp48 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp49 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp47}, TNode<Smi>{tmp48});
    ca_.Branch(tmp49, &block38, std::vector<Node*>{}, &block39, std::vector<Node*>{});
  }

  if (block32.is_used()) {
    ca_.Bind(&block32);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block38.is_used()) {
    ca_.Bind(&block38);
    ca_.Goto(&block37, tmp47, p_lengthBArg, tmp19, tmp9, tmp35);
  }

  TNode<Smi> tmp50;
  TNode<BoolT> tmp51;
  if (block39.is_used()) {
    ca_.Bind(&block39);
    tmp50 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp51 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{p_lengthBArg}, TNode<Smi>{tmp50});
    ca_.Branch(tmp51, &block40, std::vector<Node*>{}, &block41, std::vector<Node*>{});
  }

  if (block40.is_used()) {
    ca_.Bind(&block40);
    ca_.Goto(&block35, tmp47, p_lengthBArg, tmp19, tmp9, tmp35);
  }

  TNode<IntPtrT> tmp52;
  TNode<Smi> tmp53;
  if (block41.is_used()) {
    ca_.Bind(&block41);
    tmp52 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp53 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp52});
    ca_.Goto(&block44, tmp47, p_lengthBArg, tmp19, tmp9, tmp35, tmp53);
  }

  TNode<Smi> phi_bb44_6;
  TNode<Smi> phi_bb44_7;
  TNode<Smi> phi_bb44_10;
  TNode<Smi> phi_bb44_11;
  TNode<Smi> phi_bb44_12;
  TNode<Smi> phi_bb44_13;
  TNode<BoolT> tmp54;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_6, &phi_bb44_7, &phi_bb44_10, &phi_bb44_11, &phi_bb44_12, &phi_bb44_13);
    tmp54 = CodeStubAssembler(state_).Int32TrueConstant();
    ca_.Branch(tmp54, &block42, std::vector<Node*>{phi_bb44_6, phi_bb44_7, phi_bb44_10, phi_bb44_11, phi_bb44_12, phi_bb44_13}, &block43, std::vector<Node*>{phi_bb44_6, phi_bb44_7, phi_bb44_10, phi_bb44_11, phi_bb44_12, phi_bb44_13});
  }

  TNode<Smi> phi_bb42_6;
  TNode<Smi> phi_bb42_7;
  TNode<Smi> phi_bb42_10;
  TNode<Smi> phi_bb42_11;
  TNode<Smi> phi_bb42_12;
  TNode<Smi> phi_bb42_13;
  TNode<Smi> tmp55;
  TNode<Smi> tmp56;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_6, &phi_bb42_7, &phi_bb42_10, &phi_bb42_11, &phi_bb42_12, &phi_bb42_13);
    tmp55 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp56 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    ca_.Goto(&block47, phi_bb42_6, phi_bb42_7, phi_bb42_10, phi_bb42_11, phi_bb42_12, phi_bb42_13, tmp55, tmp56);
  }

  TNode<Smi> phi_bb47_6;
  TNode<Smi> phi_bb47_7;
  TNode<Smi> phi_bb47_10;
  TNode<Smi> phi_bb47_11;
  TNode<Smi> phi_bb47_12;
  TNode<Smi> phi_bb47_13;
  TNode<Smi> phi_bb47_14;
  TNode<Smi> phi_bb47_15;
  TNode<BoolT> tmp57;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_6, &phi_bb47_7, &phi_bb47_10, &phi_bb47_11, &phi_bb47_12, &phi_bb47_13, &phi_bb47_14, &phi_bb47_15);
    tmp57 = CodeStubAssembler(state_).Int32TrueConstant();
    ca_.Branch(tmp57, &block45, std::vector<Node*>{phi_bb47_6, phi_bb47_7, phi_bb47_10, phi_bb47_11, phi_bb47_12, phi_bb47_13, phi_bb47_14, phi_bb47_15}, &block46, std::vector<Node*>{phi_bb47_6, phi_bb47_7, phi_bb47_10, phi_bb47_11, phi_bb47_12, phi_bb47_13, phi_bb47_14, phi_bb47_15});
  }

  TNode<Smi> phi_bb45_6;
  TNode<Smi> phi_bb45_7;
  TNode<Smi> phi_bb45_10;
  TNode<Smi> phi_bb45_11;
  TNode<Smi> phi_bb45_12;
  TNode<Smi> phi_bb45_13;
  TNode<Smi> phi_bb45_14;
  TNode<Smi> phi_bb45_15;
  TNode<IntPtrT> tmp58;
  TNode<IntPtrT> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<Smi> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<UintPtrT> tmp64;
  TNode<UintPtrT> tmp65;
  TNode<BoolT> tmp66;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_6, &phi_bb45_7, &phi_bb45_10, &phi_bb45_11, &phi_bb45_12, &phi_bb45_13, &phi_bb45_14, &phi_bb45_15);
    tmp58 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp59 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp60 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp61 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp60});
    tmp62 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp61});
    tmp63 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb45_11});
    tmp64 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp63});
    tmp65 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp62});
    tmp66 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp64}, TNode<UintPtrT>{tmp65});
    ca_.Branch(tmp66, &block59, std::vector<Node*>{phi_bb45_6, phi_bb45_7, phi_bb45_10, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_14, phi_bb45_15, phi_bb45_11, phi_bb45_11}, &block60, std::vector<Node*>{phi_bb45_6, phi_bb45_7, phi_bb45_10, phi_bb45_11, phi_bb45_12, phi_bb45_13, phi_bb45_14, phi_bb45_15, phi_bb45_11, phi_bb45_11});
  }

  TNode<Smi> phi_bb59_6;
  TNode<Smi> phi_bb59_7;
  TNode<Smi> phi_bb59_10;
  TNode<Smi> phi_bb59_11;
  TNode<Smi> phi_bb59_12;
  TNode<Smi> phi_bb59_13;
  TNode<Smi> phi_bb59_14;
  TNode<Smi> phi_bb59_15;
  TNode<Smi> phi_bb59_21;
  TNode<Smi> phi_bb59_22;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<HeapObject> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<Object> tmp72;
  TNode<Object> tmp73;
  TNode<IntPtrT> tmp74;
  TNode<IntPtrT> tmp75;
  TNode<IntPtrT> tmp76;
  TNode<Smi> tmp77;
  TNode<IntPtrT> tmp78;
  TNode<IntPtrT> tmp79;
  TNode<UintPtrT> tmp80;
  TNode<UintPtrT> tmp81;
  TNode<BoolT> tmp82;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_6, &phi_bb59_7, &phi_bb59_10, &phi_bb59_11, &phi_bb59_12, &phi_bb59_13, &phi_bb59_14, &phi_bb59_15, &phi_bb59_21, &phi_bb59_22);
    tmp67 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp68 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp63}, TNode<IntPtrT>{tmp67});
    tmp69 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp58}, TNode<IntPtrT>{tmp68});
    std::tie(tmp70, tmp71) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp69}).Flatten();
    tmp72 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp70, tmp71});
    tmp73 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp72});
    tmp74 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp75 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp76 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp77 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp76});
    tmp78 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp77});
    tmp79 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb59_12});
    tmp80 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp79});
    tmp81 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp78});
    tmp82 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp80}, TNode<UintPtrT>{tmp81});
    ca_.Branch(tmp82, &block66, std::vector<Node*>{phi_bb59_6, phi_bb59_7, phi_bb59_10, phi_bb59_11, phi_bb59_12, phi_bb59_13, phi_bb59_14, phi_bb59_15, phi_bb59_12, phi_bb59_12}, &block67, std::vector<Node*>{phi_bb59_6, phi_bb59_7, phi_bb59_10, phi_bb59_11, phi_bb59_12, phi_bb59_13, phi_bb59_14, phi_bb59_15, phi_bb59_12, phi_bb59_12});
  }

  TNode<Smi> phi_bb60_6;
  TNode<Smi> phi_bb60_7;
  TNode<Smi> phi_bb60_10;
  TNode<Smi> phi_bb60_11;
  TNode<Smi> phi_bb60_12;
  TNode<Smi> phi_bb60_13;
  TNode<Smi> phi_bb60_14;
  TNode<Smi> phi_bb60_15;
  TNode<Smi> phi_bb60_21;
  TNode<Smi> phi_bb60_22;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_6, &phi_bb60_7, &phi_bb60_10, &phi_bb60_11, &phi_bb60_12, &phi_bb60_13, &phi_bb60_14, &phi_bb60_15, &phi_bb60_21, &phi_bb60_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb66_6;
  TNode<Smi> phi_bb66_7;
  TNode<Smi> phi_bb66_10;
  TNode<Smi> phi_bb66_11;
  TNode<Smi> phi_bb66_12;
  TNode<Smi> phi_bb66_13;
  TNode<Smi> phi_bb66_14;
  TNode<Smi> phi_bb66_15;
  TNode<Smi> phi_bb66_22;
  TNode<Smi> phi_bb66_23;
  TNode<IntPtrT> tmp83;
  TNode<IntPtrT> tmp84;
  TNode<IntPtrT> tmp85;
  TNode<HeapObject> tmp86;
  TNode<IntPtrT> tmp87;
  TNode<Object> tmp88;
  TNode<Object> tmp89;
  TNode<Number> tmp90;
  TNode<Number> tmp91;
  TNode<BoolT> tmp92;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_6, &phi_bb66_7, &phi_bb66_10, &phi_bb66_11, &phi_bb66_12, &phi_bb66_13, &phi_bb66_14, &phi_bb66_15, &phi_bb66_22, &phi_bb66_23);
    tmp83 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp84 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp79}, TNode<IntPtrT>{tmp83});
    tmp85 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp74}, TNode<IntPtrT>{tmp84});
    std::tie(tmp86, tmp87) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp85}).Flatten();
    tmp88 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp86, tmp87});
    tmp89 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp88});
    tmp90 = Method_SortState_Compare_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Object>{tmp73}, TNode<Object>{tmp89});
    tmp91 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp92 = NumberIsLessThan_0(state_, TNode<Number>{tmp90}, TNode<Number>{tmp91});
    ca_.Branch(tmp92, &block69, std::vector<Node*>{phi_bb66_6, phi_bb66_7, phi_bb66_10, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_15}, &block70, std::vector<Node*>{phi_bb66_6, phi_bb66_7, phi_bb66_10, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_15});
  }

  TNode<Smi> phi_bb67_6;
  TNode<Smi> phi_bb67_7;
  TNode<Smi> phi_bb67_10;
  TNode<Smi> phi_bb67_11;
  TNode<Smi> phi_bb67_12;
  TNode<Smi> phi_bb67_13;
  TNode<Smi> phi_bb67_14;
  TNode<Smi> phi_bb67_15;
  TNode<Smi> phi_bb67_22;
  TNode<Smi> phi_bb67_23;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_6, &phi_bb67_7, &phi_bb67_10, &phi_bb67_11, &phi_bb67_12, &phi_bb67_13, &phi_bb67_14, &phi_bb67_15, &phi_bb67_22, &phi_bb67_23);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb69_6;
  TNode<Smi> phi_bb69_7;
  TNode<Smi> phi_bb69_10;
  TNode<Smi> phi_bb69_11;
  TNode<Smi> phi_bb69_12;
  TNode<Smi> phi_bb69_13;
  TNode<Smi> phi_bb69_14;
  TNode<Smi> phi_bb69_15;
  TNode<IntPtrT> tmp93;
  TNode<IntPtrT> tmp94;
  TNode<IntPtrT> tmp95;
  TNode<Smi> tmp96;
  TNode<IntPtrT> tmp97;
  TNode<Smi> tmp98;
  TNode<Smi> tmp99;
  TNode<IntPtrT> tmp100;
  TNode<UintPtrT> tmp101;
  TNode<UintPtrT> tmp102;
  TNode<BoolT> tmp103;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_6, &phi_bb69_7, &phi_bb69_10, &phi_bb69_11, &phi_bb69_12, &phi_bb69_13, &phi_bb69_14, &phi_bb69_15);
    tmp93 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp94 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp95 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp96 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp95});
    tmp97 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp96});
    tmp98 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp99 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb69_10}, TNode<Smi>{tmp98});
    tmp100 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb69_10});
    tmp101 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp100});
    tmp102 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp97});
    tmp103 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp101}, TNode<UintPtrT>{tmp102});
    ca_.Branch(tmp103, &block76, std::vector<Node*>{phi_bb69_6, phi_bb69_7, phi_bb69_11, phi_bb69_12, phi_bb69_13, phi_bb69_14, phi_bb69_15, phi_bb69_10, phi_bb69_10}, &block77, std::vector<Node*>{phi_bb69_6, phi_bb69_7, phi_bb69_11, phi_bb69_12, phi_bb69_13, phi_bb69_14, phi_bb69_15, phi_bb69_10, phi_bb69_10});
  }

  TNode<Smi> phi_bb76_6;
  TNode<Smi> phi_bb76_7;
  TNode<Smi> phi_bb76_11;
  TNode<Smi> phi_bb76_12;
  TNode<Smi> phi_bb76_13;
  TNode<Smi> phi_bb76_14;
  TNode<Smi> phi_bb76_15;
  TNode<Smi> phi_bb76_21;
  TNode<Smi> phi_bb76_22;
  TNode<IntPtrT> tmp104;
  TNode<IntPtrT> tmp105;
  TNode<IntPtrT> tmp106;
  TNode<HeapObject> tmp107;
  TNode<IntPtrT> tmp108;
  TNode<IntPtrT> tmp109;
  TNode<IntPtrT> tmp110;
  TNode<IntPtrT> tmp111;
  TNode<Smi> tmp112;
  TNode<IntPtrT> tmp113;
  TNode<Smi> tmp114;
  TNode<Smi> tmp115;
  TNode<IntPtrT> tmp116;
  TNode<UintPtrT> tmp117;
  TNode<UintPtrT> tmp118;
  TNode<BoolT> tmp119;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_6, &phi_bb76_7, &phi_bb76_11, &phi_bb76_12, &phi_bb76_13, &phi_bb76_14, &phi_bb76_15, &phi_bb76_21, &phi_bb76_22);
    tmp104 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp105 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp100}, TNode<IntPtrT>{tmp104});
    tmp106 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp93}, TNode<IntPtrT>{tmp105});
    std::tie(tmp107, tmp108) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp106}).Flatten();
    tmp109 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp110 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp111 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp112 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp111});
    tmp113 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp112});
    tmp114 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp115 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb76_12}, TNode<Smi>{tmp114});
    tmp116 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb76_12});
    tmp117 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp116});
    tmp118 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp113});
    tmp119 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp117}, TNode<UintPtrT>{tmp118});
    ca_.Branch(tmp119, &block83, std::vector<Node*>{phi_bb76_6, phi_bb76_7, phi_bb76_11, phi_bb76_13, phi_bb76_14, phi_bb76_15, phi_bb76_21, phi_bb76_22, phi_bb76_12, phi_bb76_12}, &block84, std::vector<Node*>{phi_bb76_6, phi_bb76_7, phi_bb76_11, phi_bb76_13, phi_bb76_14, phi_bb76_15, phi_bb76_21, phi_bb76_22, phi_bb76_12, phi_bb76_12});
  }

  TNode<Smi> phi_bb77_6;
  TNode<Smi> phi_bb77_7;
  TNode<Smi> phi_bb77_11;
  TNode<Smi> phi_bb77_12;
  TNode<Smi> phi_bb77_13;
  TNode<Smi> phi_bb77_14;
  TNode<Smi> phi_bb77_15;
  TNode<Smi> phi_bb77_21;
  TNode<Smi> phi_bb77_22;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_6, &phi_bb77_7, &phi_bb77_11, &phi_bb77_12, &phi_bb77_13, &phi_bb77_14, &phi_bb77_15, &phi_bb77_21, &phi_bb77_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb83_6;
  TNode<Smi> phi_bb83_7;
  TNode<Smi> phi_bb83_11;
  TNode<Smi> phi_bb83_13;
  TNode<Smi> phi_bb83_14;
  TNode<Smi> phi_bb83_15;
  TNode<Smi> phi_bb83_21;
  TNode<Smi> phi_bb83_22;
  TNode<Smi> phi_bb83_29;
  TNode<Smi> phi_bb83_30;
  TNode<IntPtrT> tmp120;
  TNode<IntPtrT> tmp121;
  TNode<IntPtrT> tmp122;
  TNode<HeapObject> tmp123;
  TNode<IntPtrT> tmp124;
  TNode<Object> tmp125;
  TNode<Smi> tmp126;
  TNode<Smi> tmp127;
  TNode<Smi> tmp128;
  TNode<Smi> tmp129;
  TNode<Smi> tmp130;
  TNode<Smi> tmp131;
  TNode<BoolT> tmp132;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_6, &phi_bb83_7, &phi_bb83_11, &phi_bb83_13, &phi_bb83_14, &phi_bb83_15, &phi_bb83_21, &phi_bb83_22, &phi_bb83_29, &phi_bb83_30);
    tmp120 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp121 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp116}, TNode<IntPtrT>{tmp120});
    tmp122 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp109}, TNode<IntPtrT>{tmp121});
    std::tie(tmp123, tmp124) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp122}).Flatten();
    tmp125 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp123, tmp124});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp107, tmp108}, tmp125);
    tmp126 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp127 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb83_14}, TNode<Smi>{tmp126});
    tmp128 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp129 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb83_6}, TNode<Smi>{tmp128});
    tmp130 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp131 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp132 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp129}, TNode<Smi>{tmp131});
    ca_.Branch(tmp132, &block86, std::vector<Node*>{phi_bb83_7, phi_bb83_11, phi_bb83_13}, &block87, std::vector<Node*>{phi_bb83_7, phi_bb83_11, phi_bb83_13});
  }

  TNode<Smi> phi_bb84_6;
  TNode<Smi> phi_bb84_7;
  TNode<Smi> phi_bb84_11;
  TNode<Smi> phi_bb84_13;
  TNode<Smi> phi_bb84_14;
  TNode<Smi> phi_bb84_15;
  TNode<Smi> phi_bb84_21;
  TNode<Smi> phi_bb84_22;
  TNode<Smi> phi_bb84_29;
  TNode<Smi> phi_bb84_30;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_6, &phi_bb84_7, &phi_bb84_11, &phi_bb84_13, &phi_bb84_14, &phi_bb84_15, &phi_bb84_21, &phi_bb84_22, &phi_bb84_29, &phi_bb84_30);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb86_7;
  TNode<Smi> phi_bb86_11;
  TNode<Smi> phi_bb86_13;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_7, &phi_bb86_11, &phi_bb86_13);
    ca_.Goto(&block37, tmp129, phi_bb86_7, tmp99, phi_bb86_11, tmp115);
  }

  TNode<Smi> phi_bb87_7;
  TNode<Smi> phi_bb87_11;
  TNode<Smi> phi_bb87_13;
  TNode<BoolT> tmp133;
  if (block87.is_used()) {
    ca_.Bind(&block87, &phi_bb87_7, &phi_bb87_11, &phi_bb87_13);
    tmp133 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp127}, TNode<Smi>{phi_bb87_13});
    ca_.Branch(tmp133, &block88, std::vector<Node*>{phi_bb87_7, phi_bb87_11, phi_bb87_13}, &block89, std::vector<Node*>{phi_bb87_7, phi_bb87_11, phi_bb87_13});
  }

  TNode<Smi> phi_bb88_7;
  TNode<Smi> phi_bb88_11;
  TNode<Smi> phi_bb88_13;
  if (block88.is_used()) {
    ca_.Bind(&block88, &phi_bb88_7, &phi_bb88_11, &phi_bb88_13);
    ca_.Goto(&block46, tmp129, phi_bb88_7, tmp99, phi_bb88_11, tmp115, phi_bb88_13, tmp127, tmp130);
  }

  TNode<Smi> phi_bb89_7;
  TNode<Smi> phi_bb89_11;
  TNode<Smi> phi_bb89_13;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_7, &phi_bb89_11, &phi_bb89_13);
    ca_.Goto(&block71, tmp129, phi_bb89_7, tmp99, phi_bb89_11, tmp115, phi_bb89_13, tmp127, tmp130);
  }

  TNode<Smi> phi_bb70_6;
  TNode<Smi> phi_bb70_7;
  TNode<Smi> phi_bb70_10;
  TNode<Smi> phi_bb70_11;
  TNode<Smi> phi_bb70_12;
  TNode<Smi> phi_bb70_13;
  TNode<Smi> phi_bb70_14;
  TNode<Smi> phi_bb70_15;
  TNode<IntPtrT> tmp134;
  TNode<IntPtrT> tmp135;
  TNode<IntPtrT> tmp136;
  TNode<Smi> tmp137;
  TNode<IntPtrT> tmp138;
  TNode<Smi> tmp139;
  TNode<Smi> tmp140;
  TNode<IntPtrT> tmp141;
  TNode<UintPtrT> tmp142;
  TNode<UintPtrT> tmp143;
  TNode<BoolT> tmp144;
  if (block70.is_used()) {
    ca_.Bind(&block70, &phi_bb70_6, &phi_bb70_7, &phi_bb70_10, &phi_bb70_11, &phi_bb70_12, &phi_bb70_13, &phi_bb70_14, &phi_bb70_15);
    tmp134 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp135 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp136 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp137 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp136});
    tmp138 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp137});
    tmp139 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp140 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb70_10}, TNode<Smi>{tmp139});
    tmp141 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb70_10});
    tmp142 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp141});
    tmp143 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp138});
    tmp144 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp142}, TNode<UintPtrT>{tmp143});
    ca_.Branch(tmp144, &block94, std::vector<Node*>{phi_bb70_6, phi_bb70_7, phi_bb70_11, phi_bb70_12, phi_bb70_13, phi_bb70_14, phi_bb70_15, phi_bb70_10, phi_bb70_10}, &block95, std::vector<Node*>{phi_bb70_6, phi_bb70_7, phi_bb70_11, phi_bb70_12, phi_bb70_13, phi_bb70_14, phi_bb70_15, phi_bb70_10, phi_bb70_10});
  }

  TNode<Smi> phi_bb94_6;
  TNode<Smi> phi_bb94_7;
  TNode<Smi> phi_bb94_11;
  TNode<Smi> phi_bb94_12;
  TNode<Smi> phi_bb94_13;
  TNode<Smi> phi_bb94_14;
  TNode<Smi> phi_bb94_15;
  TNode<Smi> phi_bb94_21;
  TNode<Smi> phi_bb94_22;
  TNode<IntPtrT> tmp145;
  TNode<IntPtrT> tmp146;
  TNode<IntPtrT> tmp147;
  TNode<HeapObject> tmp148;
  TNode<IntPtrT> tmp149;
  TNode<IntPtrT> tmp150;
  TNode<IntPtrT> tmp151;
  TNode<IntPtrT> tmp152;
  TNode<Smi> tmp153;
  TNode<IntPtrT> tmp154;
  TNode<Smi> tmp155;
  TNode<Smi> tmp156;
  TNode<IntPtrT> tmp157;
  TNode<UintPtrT> tmp158;
  TNode<UintPtrT> tmp159;
  TNode<BoolT> tmp160;
  if (block94.is_used()) {
    ca_.Bind(&block94, &phi_bb94_6, &phi_bb94_7, &phi_bb94_11, &phi_bb94_12, &phi_bb94_13, &phi_bb94_14, &phi_bb94_15, &phi_bb94_21, &phi_bb94_22);
    tmp145 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp146 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp141}, TNode<IntPtrT>{tmp145});
    tmp147 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp134}, TNode<IntPtrT>{tmp146});
    std::tie(tmp148, tmp149) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp147}).Flatten();
    tmp150 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp151 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp152 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp153 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp152});
    tmp154 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp153});
    tmp155 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp156 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb94_11}, TNode<Smi>{tmp155});
    tmp157 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb94_11});
    tmp158 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp157});
    tmp159 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp154});
    tmp160 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp158}, TNode<UintPtrT>{tmp159});
    ca_.Branch(tmp160, &block101, std::vector<Node*>{phi_bb94_6, phi_bb94_7, phi_bb94_12, phi_bb94_13, phi_bb94_14, phi_bb94_15, phi_bb94_21, phi_bb94_22, phi_bb94_11, phi_bb94_11}, &block102, std::vector<Node*>{phi_bb94_6, phi_bb94_7, phi_bb94_12, phi_bb94_13, phi_bb94_14, phi_bb94_15, phi_bb94_21, phi_bb94_22, phi_bb94_11, phi_bb94_11});
  }

  TNode<Smi> phi_bb95_6;
  TNode<Smi> phi_bb95_7;
  TNode<Smi> phi_bb95_11;
  TNode<Smi> phi_bb95_12;
  TNode<Smi> phi_bb95_13;
  TNode<Smi> phi_bb95_14;
  TNode<Smi> phi_bb95_15;
  TNode<Smi> phi_bb95_21;
  TNode<Smi> phi_bb95_22;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_6, &phi_bb95_7, &phi_bb95_11, &phi_bb95_12, &phi_bb95_13, &phi_bb95_14, &phi_bb95_15, &phi_bb95_21, &phi_bb95_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb101_6;
  TNode<Smi> phi_bb101_7;
  TNode<Smi> phi_bb101_12;
  TNode<Smi> phi_bb101_13;
  TNode<Smi> phi_bb101_14;
  TNode<Smi> phi_bb101_15;
  TNode<Smi> phi_bb101_21;
  TNode<Smi> phi_bb101_22;
  TNode<Smi> phi_bb101_29;
  TNode<Smi> phi_bb101_30;
  TNode<IntPtrT> tmp161;
  TNode<IntPtrT> tmp162;
  TNode<IntPtrT> tmp163;
  TNode<HeapObject> tmp164;
  TNode<IntPtrT> tmp165;
  TNode<Object> tmp166;
  TNode<Smi> tmp167;
  TNode<Smi> tmp168;
  TNode<Smi> tmp169;
  TNode<Smi> tmp170;
  TNode<Smi> tmp171;
  TNode<Smi> tmp172;
  TNode<BoolT> tmp173;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_6, &phi_bb101_7, &phi_bb101_12, &phi_bb101_13, &phi_bb101_14, &phi_bb101_15, &phi_bb101_21, &phi_bb101_22, &phi_bb101_29, &phi_bb101_30);
    tmp161 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp162 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp157}, TNode<IntPtrT>{tmp161});
    tmp163 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp150}, TNode<IntPtrT>{tmp162});
    std::tie(tmp164, tmp165) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp163}).Flatten();
    tmp166 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp164, tmp165});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp148, tmp149}, tmp166);
    tmp167 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp168 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb101_15}, TNode<Smi>{tmp167});
    tmp169 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp170 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb101_7}, TNode<Smi>{tmp169});
    tmp171 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp172 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp173 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp170}, TNode<Smi>{tmp172});
    ca_.Branch(tmp173, &block104, std::vector<Node*>{phi_bb101_6, phi_bb101_12, phi_bb101_13}, &block105, std::vector<Node*>{phi_bb101_6, phi_bb101_12, phi_bb101_13});
  }

  TNode<Smi> phi_bb102_6;
  TNode<Smi> phi_bb102_7;
  TNode<Smi> phi_bb102_12;
  TNode<Smi> phi_bb102_13;
  TNode<Smi> phi_bb102_14;
  TNode<Smi> phi_bb102_15;
  TNode<Smi> phi_bb102_21;
  TNode<Smi> phi_bb102_22;
  TNode<Smi> phi_bb102_29;
  TNode<Smi> phi_bb102_30;
  if (block102.is_used()) {
    ca_.Bind(&block102, &phi_bb102_6, &phi_bb102_7, &phi_bb102_12, &phi_bb102_13, &phi_bb102_14, &phi_bb102_15, &phi_bb102_21, &phi_bb102_22, &phi_bb102_29, &phi_bb102_30);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb104_6;
  TNode<Smi> phi_bb104_12;
  TNode<Smi> phi_bb104_13;
  if (block104.is_used()) {
    ca_.Bind(&block104, &phi_bb104_6, &phi_bb104_12, &phi_bb104_13);
    ca_.Goto(&block35, phi_bb104_6, tmp170, tmp140, tmp156, phi_bb104_12);
  }

  TNode<Smi> phi_bb105_6;
  TNode<Smi> phi_bb105_12;
  TNode<Smi> phi_bb105_13;
  TNode<BoolT> tmp174;
  if (block105.is_used()) {
    ca_.Bind(&block105, &phi_bb105_6, &phi_bb105_12, &phi_bb105_13);
    tmp174 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp168}, TNode<Smi>{phi_bb105_13});
    ca_.Branch(tmp174, &block106, std::vector<Node*>{phi_bb105_6, phi_bb105_12, phi_bb105_13}, &block107, std::vector<Node*>{phi_bb105_6, phi_bb105_12, phi_bb105_13});
  }

  TNode<Smi> phi_bb106_6;
  TNode<Smi> phi_bb106_12;
  TNode<Smi> phi_bb106_13;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_6, &phi_bb106_12, &phi_bb106_13);
    ca_.Goto(&block46, phi_bb106_6, tmp170, tmp140, tmp156, phi_bb106_12, phi_bb106_13, tmp171, tmp168);
  }

  TNode<Smi> phi_bb107_6;
  TNode<Smi> phi_bb107_12;
  TNode<Smi> phi_bb107_13;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_6, &phi_bb107_12, &phi_bb107_13);
    ca_.Goto(&block71, phi_bb107_6, tmp170, tmp140, tmp156, phi_bb107_12, phi_bb107_13, tmp171, tmp168);
  }

  TNode<Smi> phi_bb71_6;
  TNode<Smi> phi_bb71_7;
  TNode<Smi> phi_bb71_10;
  TNode<Smi> phi_bb71_11;
  TNode<Smi> phi_bb71_12;
  TNode<Smi> phi_bb71_13;
  TNode<Smi> phi_bb71_14;
  TNode<Smi> phi_bb71_15;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_6, &phi_bb71_7, &phi_bb71_10, &phi_bb71_11, &phi_bb71_12, &phi_bb71_13, &phi_bb71_14, &phi_bb71_15);
    ca_.Goto(&block47, phi_bb71_6, phi_bb71_7, phi_bb71_10, phi_bb71_11, phi_bb71_12, phi_bb71_13, phi_bb71_14, phi_bb71_15);
  }

  TNode<Smi> phi_bb46_6;
  TNode<Smi> phi_bb46_7;
  TNode<Smi> phi_bb46_10;
  TNode<Smi> phi_bb46_11;
  TNode<Smi> phi_bb46_12;
  TNode<Smi> phi_bb46_13;
  TNode<Smi> phi_bb46_14;
  TNode<Smi> phi_bb46_15;
  TNode<Smi> tmp175;
  TNode<Smi> tmp176;
  TNode<BoolT> tmp177;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_6, &phi_bb46_7, &phi_bb46_10, &phi_bb46_11, &phi_bb46_12, &phi_bb46_13, &phi_bb46_14, &phi_bb46_15);
    tmp175 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp176 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb46_13}, TNode<Smi>{tmp175});
    tmp177 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block110, phi_bb46_6, phi_bb46_7, phi_bb46_10, phi_bb46_11, phi_bb46_12, tmp176, phi_bb46_14, phi_bb46_15, tmp177);
  }

  TNode<Smi> phi_bb110_6;
  TNode<Smi> phi_bb110_7;
  TNode<Smi> phi_bb110_10;
  TNode<Smi> phi_bb110_11;
  TNode<Smi> phi_bb110_12;
  TNode<Smi> phi_bb110_13;
  TNode<Smi> phi_bb110_14;
  TNode<Smi> phi_bb110_15;
  TNode<BoolT> phi_bb110_16;
  TNode<Smi> tmp178;
  TNode<BoolT> tmp179;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_6, &phi_bb110_7, &phi_bb110_10, &phi_bb110_11, &phi_bb110_12, &phi_bb110_13, &phi_bb110_14, &phi_bb110_15, &phi_bb110_16);
    tmp178 = FromConstexpr_Smi_constexpr_int31_0(state_, kMinGallopWins_0(state_));
    tmp179 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb110_14}, TNode<Smi>{tmp178});
    ca_.Branch(tmp179, &block111, std::vector<Node*>{phi_bb110_6, phi_bb110_7, phi_bb110_10, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_14, phi_bb110_15, phi_bb110_16}, &block112, std::vector<Node*>{phi_bb110_6, phi_bb110_7, phi_bb110_10, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_14, phi_bb110_15, phi_bb110_16});
  }

  TNode<Smi> phi_bb111_6;
  TNode<Smi> phi_bb111_7;
  TNode<Smi> phi_bb111_10;
  TNode<Smi> phi_bb111_11;
  TNode<Smi> phi_bb111_12;
  TNode<Smi> phi_bb111_13;
  TNode<Smi> phi_bb111_14;
  TNode<Smi> phi_bb111_15;
  TNode<BoolT> phi_bb111_16;
  TNode<BoolT> tmp180;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_6, &phi_bb111_7, &phi_bb111_10, &phi_bb111_11, &phi_bb111_12, &phi_bb111_13, &phi_bb111_14, &phi_bb111_15, &phi_bb111_16);
    tmp180 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block113, phi_bb111_6, phi_bb111_7, phi_bb111_10, phi_bb111_11, phi_bb111_12, phi_bb111_13, phi_bb111_14, phi_bb111_15, phi_bb111_16, tmp180);
  }

  TNode<Smi> phi_bb112_6;
  TNode<Smi> phi_bb112_7;
  TNode<Smi> phi_bb112_10;
  TNode<Smi> phi_bb112_11;
  TNode<Smi> phi_bb112_12;
  TNode<Smi> phi_bb112_13;
  TNode<Smi> phi_bb112_14;
  TNode<Smi> phi_bb112_15;
  TNode<BoolT> phi_bb112_16;
  TNode<Smi> tmp181;
  TNode<BoolT> tmp182;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_6, &phi_bb112_7, &phi_bb112_10, &phi_bb112_11, &phi_bb112_12, &phi_bb112_13, &phi_bb112_14, &phi_bb112_15, &phi_bb112_16);
    tmp181 = FromConstexpr_Smi_constexpr_int31_0(state_, kMinGallopWins_0(state_));
    tmp182 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb112_15}, TNode<Smi>{tmp181});
    ca_.Goto(&block113, phi_bb112_6, phi_bb112_7, phi_bb112_10, phi_bb112_11, phi_bb112_12, phi_bb112_13, phi_bb112_14, phi_bb112_15, phi_bb112_16, tmp182);
  }

  TNode<Smi> phi_bb113_6;
  TNode<Smi> phi_bb113_7;
  TNode<Smi> phi_bb113_10;
  TNode<Smi> phi_bb113_11;
  TNode<Smi> phi_bb113_12;
  TNode<Smi> phi_bb113_13;
  TNode<Smi> phi_bb113_14;
  TNode<Smi> phi_bb113_15;
  TNode<BoolT> phi_bb113_16;
  TNode<BoolT> phi_bb113_18;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_6, &phi_bb113_7, &phi_bb113_10, &phi_bb113_11, &phi_bb113_12, &phi_bb113_13, &phi_bb113_14, &phi_bb113_15, &phi_bb113_16, &phi_bb113_18);
    ca_.Branch(phi_bb113_18, &block114, std::vector<Node*>{phi_bb113_6, phi_bb113_7, phi_bb113_10, phi_bb113_11, phi_bb113_12, phi_bb113_13, phi_bb113_14, phi_bb113_15, phi_bb113_16}, &block115, std::vector<Node*>{phi_bb113_6, phi_bb113_7, phi_bb113_10, phi_bb113_11, phi_bb113_12, phi_bb113_13, phi_bb113_14, phi_bb113_15, phi_bb113_16});
  }

  TNode<Smi> phi_bb114_6;
  TNode<Smi> phi_bb114_7;
  TNode<Smi> phi_bb114_10;
  TNode<Smi> phi_bb114_11;
  TNode<Smi> phi_bb114_12;
  TNode<Smi> phi_bb114_13;
  TNode<Smi> phi_bb114_14;
  TNode<Smi> phi_bb114_15;
  TNode<BoolT> phi_bb114_16;
  TNode<BoolT> tmp183;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_6, &phi_bb114_7, &phi_bb114_10, &phi_bb114_11, &phi_bb114_12, &phi_bb114_13, &phi_bb114_14, &phi_bb114_15, &phi_bb114_16);
    tmp183 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block116, phi_bb114_6, phi_bb114_7, phi_bb114_10, phi_bb114_11, phi_bb114_12, phi_bb114_13, phi_bb114_14, phi_bb114_15, phi_bb114_16, tmp183);
  }

  TNode<Smi> phi_bb115_6;
  TNode<Smi> phi_bb115_7;
  TNode<Smi> phi_bb115_10;
  TNode<Smi> phi_bb115_11;
  TNode<Smi> phi_bb115_12;
  TNode<Smi> phi_bb115_13;
  TNode<Smi> phi_bb115_14;
  TNode<Smi> phi_bb115_15;
  TNode<BoolT> phi_bb115_16;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_6, &phi_bb115_7, &phi_bb115_10, &phi_bb115_11, &phi_bb115_12, &phi_bb115_13, &phi_bb115_14, &phi_bb115_15, &phi_bb115_16);
    ca_.Goto(&block116, phi_bb115_6, phi_bb115_7, phi_bb115_10, phi_bb115_11, phi_bb115_12, phi_bb115_13, phi_bb115_14, phi_bb115_15, phi_bb115_16, phi_bb115_16);
  }

  TNode<Smi> phi_bb116_6;
  TNode<Smi> phi_bb116_7;
  TNode<Smi> phi_bb116_10;
  TNode<Smi> phi_bb116_11;
  TNode<Smi> phi_bb116_12;
  TNode<Smi> phi_bb116_13;
  TNode<Smi> phi_bb116_14;
  TNode<Smi> phi_bb116_15;
  TNode<BoolT> phi_bb116_16;
  TNode<BoolT> phi_bb116_18;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_6, &phi_bb116_7, &phi_bb116_10, &phi_bb116_11, &phi_bb116_12, &phi_bb116_13, &phi_bb116_14, &phi_bb116_15, &phi_bb116_16, &phi_bb116_18);
    ca_.Branch(phi_bb116_18, &block108, std::vector<Node*>{phi_bb116_6, phi_bb116_7, phi_bb116_10, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_14, phi_bb116_15, phi_bb116_16}, &block109, std::vector<Node*>{phi_bb116_6, phi_bb116_7, phi_bb116_10, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_14, phi_bb116_15, phi_bb116_16});
  }

  TNode<Smi> phi_bb108_6;
  TNode<Smi> phi_bb108_7;
  TNode<Smi> phi_bb108_10;
  TNode<Smi> phi_bb108_11;
  TNode<Smi> phi_bb108_12;
  TNode<Smi> phi_bb108_13;
  TNode<Smi> phi_bb108_14;
  TNode<Smi> phi_bb108_15;
  TNode<BoolT> phi_bb108_16;
  TNode<BoolT> tmp184;
  TNode<Smi> tmp185;
  TNode<Smi> tmp186;
  TNode<Smi> tmp187;
  TNode<Smi> tmp188;
  TNode<IntPtrT> tmp189;
  TNode<IntPtrT> tmp190;
  TNode<IntPtrT> tmp191;
  TNode<IntPtrT> tmp192;
  TNode<Smi> tmp193;
  TNode<IntPtrT> tmp194;
  TNode<IntPtrT> tmp195;
  TNode<UintPtrT> tmp196;
  TNode<UintPtrT> tmp197;
  TNode<BoolT> tmp198;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_6, &phi_bb108_7, &phi_bb108_10, &phi_bb108_11, &phi_bb108_12, &phi_bb108_13, &phi_bb108_14, &phi_bb108_15, &phi_bb108_16);
    tmp184 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp185 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp186 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb108_13}, TNode<Smi>{tmp185});
    tmp187 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp188 = CodeStubAssembler(state_).SmiMax(TNode<Smi>{tmp187}, TNode<Smi>{tmp186});
    tmp189 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp189}, tmp188);
    tmp190 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp191 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp192 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp193 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp192});
    tmp194 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp193});
    tmp195 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb108_11});
    tmp196 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp195});
    tmp197 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp194});
    tmp198 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp196}, TNode<UintPtrT>{tmp197});
    ca_.Branch(tmp198, &block128, std::vector<Node*>{phi_bb108_6, phi_bb108_7, phi_bb108_10, phi_bb108_11, phi_bb108_12, phi_bb108_14, phi_bb108_15, phi_bb108_11, phi_bb108_11}, &block129, std::vector<Node*>{phi_bb108_6, phi_bb108_7, phi_bb108_10, phi_bb108_11, phi_bb108_12, phi_bb108_14, phi_bb108_15, phi_bb108_11, phi_bb108_11});
  }

  TNode<Smi> phi_bb128_6;
  TNode<Smi> phi_bb128_7;
  TNode<Smi> phi_bb128_10;
  TNode<Smi> phi_bb128_11;
  TNode<Smi> phi_bb128_12;
  TNode<Smi> phi_bb128_14;
  TNode<Smi> phi_bb128_15;
  TNode<Smi> phi_bb128_22;
  TNode<Smi> phi_bb128_23;
  TNode<IntPtrT> tmp199;
  TNode<IntPtrT> tmp200;
  TNode<IntPtrT> tmp201;
  TNode<HeapObject> tmp202;
  TNode<IntPtrT> tmp203;
  TNode<Object> tmp204;
  TNode<Object> tmp205;
  TNode<Smi> tmp206;
  TNode<Smi> tmp207;
  TNode<Smi> tmp208;
  TNode<Smi> tmp209;
  TNode<Smi> tmp210;
  TNode<BoolT> tmp211;
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_6, &phi_bb128_7, &phi_bb128_10, &phi_bb128_11, &phi_bb128_12, &phi_bb128_14, &phi_bb128_15, &phi_bb128_22, &phi_bb128_23);
    tmp199 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp200 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp195}, TNode<IntPtrT>{tmp199});
    tmp201 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp190}, TNode<IntPtrT>{tmp200});
    std::tie(tmp202, tmp203) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp201}).Flatten();
    tmp204 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp202, tmp203});
    tmp205 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp204});
    tmp206 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp207 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb128_6}, TNode<Smi>{tmp206});
    tmp208 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kGallopRight, p_context, p_sortState, tmp1, tmp205, p_baseA, phi_bb128_6, tmp207));
    tmp209 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb128_6}, TNode<Smi>{tmp208});
    tmp210 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp211 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp209}, TNode<Smi>{tmp210});
    ca_.Branch(tmp211, &block135, std::vector<Node*>{phi_bb128_6, phi_bb128_7, phi_bb128_10, phi_bb128_11, phi_bb128_12, phi_bb128_15}, &block136, std::vector<Node*>{phi_bb128_6, phi_bb128_7, phi_bb128_10, phi_bb128_11, phi_bb128_12, phi_bb128_15});
  }

  TNode<Smi> phi_bb129_6;
  TNode<Smi> phi_bb129_7;
  TNode<Smi> phi_bb129_10;
  TNode<Smi> phi_bb129_11;
  TNode<Smi> phi_bb129_12;
  TNode<Smi> phi_bb129_14;
  TNode<Smi> phi_bb129_15;
  TNode<Smi> phi_bb129_22;
  TNode<Smi> phi_bb129_23;
  if (block129.is_used()) {
    ca_.Bind(&block129, &phi_bb129_6, &phi_bb129_7, &phi_bb129_10, &phi_bb129_11, &phi_bb129_12, &phi_bb129_14, &phi_bb129_15, &phi_bb129_22, &phi_bb129_23);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb135_6;
  TNode<Smi> phi_bb135_7;
  TNode<Smi> phi_bb135_10;
  TNode<Smi> phi_bb135_11;
  TNode<Smi> phi_bb135_12;
  TNode<Smi> phi_bb135_15;
  TNode<Smi> tmp212;
  TNode<Smi> tmp213;
  TNode<Smi> tmp214;
  TNode<Smi> tmp215;
  TNode<Smi> tmp216;
  TNode<Smi> tmp217;
  TNode<Object> tmp218;
  TNode<Smi> tmp219;
  TNode<Smi> tmp220;
  TNode<BoolT> tmp221;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_6, &phi_bb135_7, &phi_bb135_10, &phi_bb135_11, &phi_bb135_12, &phi_bb135_15);
    tmp212 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb135_10}, TNode<Smi>{tmp209});
    tmp213 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb135_12}, TNode<Smi>{tmp209});
    tmp214 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp215 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp213}, TNode<Smi>{tmp214});
    tmp216 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp217 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp212}, TNode<Smi>{tmp216});
    tmp218 = CodeStubAssembler(state_).CallBuiltin(Builtins::kCopy, p_context, tmp1, tmp215, tmp1, tmp217, tmp209);
    tmp219 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb135_6}, TNode<Smi>{tmp209});
    tmp220 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp221 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp219}, TNode<Smi>{tmp220});
    ca_.Branch(tmp221, &block137, std::vector<Node*>{phi_bb135_7, phi_bb135_11, phi_bb135_15}, &block138, std::vector<Node*>{phi_bb135_7, phi_bb135_11, phi_bb135_15});
  }

  TNode<Smi> phi_bb137_7;
  TNode<Smi> phi_bb137_11;
  TNode<Smi> phi_bb137_15;
  if (block137.is_used()) {
    ca_.Bind(&block137, &phi_bb137_7, &phi_bb137_11, &phi_bb137_15);
    ca_.Goto(&block37, tmp219, phi_bb137_7, tmp212, phi_bb137_11, tmp213);
  }

  TNode<Smi> phi_bb138_7;
  TNode<Smi> phi_bb138_11;
  TNode<Smi> phi_bb138_15;
  if (block138.is_used()) {
    ca_.Bind(&block138, &phi_bb138_7, &phi_bb138_11, &phi_bb138_15);
    ca_.Goto(&block136, tmp219, phi_bb138_7, tmp212, phi_bb138_11, tmp213, phi_bb138_15);
  }

  TNode<Smi> phi_bb136_6;
  TNode<Smi> phi_bb136_7;
  TNode<Smi> phi_bb136_10;
  TNode<Smi> phi_bb136_11;
  TNode<Smi> phi_bb136_12;
  TNode<Smi> phi_bb136_15;
  TNode<IntPtrT> tmp222;
  TNode<IntPtrT> tmp223;
  TNode<IntPtrT> tmp224;
  TNode<Smi> tmp225;
  TNode<IntPtrT> tmp226;
  TNode<Smi> tmp227;
  TNode<Smi> tmp228;
  TNode<IntPtrT> tmp229;
  TNode<UintPtrT> tmp230;
  TNode<UintPtrT> tmp231;
  TNode<BoolT> tmp232;
  if (block136.is_used()) {
    ca_.Bind(&block136, &phi_bb136_6, &phi_bb136_7, &phi_bb136_10, &phi_bb136_11, &phi_bb136_12, &phi_bb136_15);
    tmp222 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp223 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp224 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp225 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp224});
    tmp226 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp225});
    tmp227 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp228 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb136_10}, TNode<Smi>{tmp227});
    tmp229 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb136_10});
    tmp230 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp229});
    tmp231 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp226});
    tmp232 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp230}, TNode<UintPtrT>{tmp231});
    ca_.Branch(tmp232, &block143, std::vector<Node*>{phi_bb136_6, phi_bb136_7, phi_bb136_11, phi_bb136_12, phi_bb136_15, phi_bb136_10, phi_bb136_10}, &block144, std::vector<Node*>{phi_bb136_6, phi_bb136_7, phi_bb136_11, phi_bb136_12, phi_bb136_15, phi_bb136_10, phi_bb136_10});
  }

  TNode<Smi> phi_bb143_6;
  TNode<Smi> phi_bb143_7;
  TNode<Smi> phi_bb143_11;
  TNode<Smi> phi_bb143_12;
  TNode<Smi> phi_bb143_15;
  TNode<Smi> phi_bb143_22;
  TNode<Smi> phi_bb143_23;
  TNode<IntPtrT> tmp233;
  TNode<IntPtrT> tmp234;
  TNode<IntPtrT> tmp235;
  TNode<HeapObject> tmp236;
  TNode<IntPtrT> tmp237;
  TNode<IntPtrT> tmp238;
  TNode<IntPtrT> tmp239;
  TNode<IntPtrT> tmp240;
  TNode<Smi> tmp241;
  TNode<IntPtrT> tmp242;
  TNode<Smi> tmp243;
  TNode<Smi> tmp244;
  TNode<IntPtrT> tmp245;
  TNode<UintPtrT> tmp246;
  TNode<UintPtrT> tmp247;
  TNode<BoolT> tmp248;
  if (block143.is_used()) {
    ca_.Bind(&block143, &phi_bb143_6, &phi_bb143_7, &phi_bb143_11, &phi_bb143_12, &phi_bb143_15, &phi_bb143_22, &phi_bb143_23);
    tmp233 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp234 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp229}, TNode<IntPtrT>{tmp233});
    tmp235 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp222}, TNode<IntPtrT>{tmp234});
    std::tie(tmp236, tmp237) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp235}).Flatten();
    tmp238 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp239 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp240 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp241 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp240});
    tmp242 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp241});
    tmp243 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp244 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb143_11}, TNode<Smi>{tmp243});
    tmp245 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb143_11});
    tmp246 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp245});
    tmp247 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp242});
    tmp248 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp246}, TNode<UintPtrT>{tmp247});
    ca_.Branch(tmp248, &block150, std::vector<Node*>{phi_bb143_6, phi_bb143_7, phi_bb143_12, phi_bb143_15, phi_bb143_22, phi_bb143_23, phi_bb143_11, phi_bb143_11}, &block151, std::vector<Node*>{phi_bb143_6, phi_bb143_7, phi_bb143_12, phi_bb143_15, phi_bb143_22, phi_bb143_23, phi_bb143_11, phi_bb143_11});
  }

  TNode<Smi> phi_bb144_6;
  TNode<Smi> phi_bb144_7;
  TNode<Smi> phi_bb144_11;
  TNode<Smi> phi_bb144_12;
  TNode<Smi> phi_bb144_15;
  TNode<Smi> phi_bb144_22;
  TNode<Smi> phi_bb144_23;
  if (block144.is_used()) {
    ca_.Bind(&block144, &phi_bb144_6, &phi_bb144_7, &phi_bb144_11, &phi_bb144_12, &phi_bb144_15, &phi_bb144_22, &phi_bb144_23);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb150_6;
  TNode<Smi> phi_bb150_7;
  TNode<Smi> phi_bb150_12;
  TNode<Smi> phi_bb150_15;
  TNode<Smi> phi_bb150_22;
  TNode<Smi> phi_bb150_23;
  TNode<Smi> phi_bb150_30;
  TNode<Smi> phi_bb150_31;
  TNode<IntPtrT> tmp249;
  TNode<IntPtrT> tmp250;
  TNode<IntPtrT> tmp251;
  TNode<HeapObject> tmp252;
  TNode<IntPtrT> tmp253;
  TNode<Object> tmp254;
  TNode<Smi> tmp255;
  TNode<Smi> tmp256;
  TNode<Smi> tmp257;
  TNode<BoolT> tmp258;
  if (block150.is_used()) {
    ca_.Bind(&block150, &phi_bb150_6, &phi_bb150_7, &phi_bb150_12, &phi_bb150_15, &phi_bb150_22, &phi_bb150_23, &phi_bb150_30, &phi_bb150_31);
    tmp249 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp250 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp245}, TNode<IntPtrT>{tmp249});
    tmp251 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp238}, TNode<IntPtrT>{tmp250});
    std::tie(tmp252, tmp253) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp251}).Flatten();
    tmp254 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp252, tmp253});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp236, tmp237}, tmp254);
    tmp255 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp256 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb150_7}, TNode<Smi>{tmp255});
    tmp257 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp258 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp256}, TNode<Smi>{tmp257});
    ca_.Branch(tmp258, &block153, std::vector<Node*>{phi_bb150_6, phi_bb150_12, phi_bb150_15}, &block154, std::vector<Node*>{phi_bb150_6, phi_bb150_12, phi_bb150_15});
  }

  TNode<Smi> phi_bb151_6;
  TNode<Smi> phi_bb151_7;
  TNode<Smi> phi_bb151_12;
  TNode<Smi> phi_bb151_15;
  TNode<Smi> phi_bb151_22;
  TNode<Smi> phi_bb151_23;
  TNode<Smi> phi_bb151_30;
  TNode<Smi> phi_bb151_31;
  if (block151.is_used()) {
    ca_.Bind(&block151, &phi_bb151_6, &phi_bb151_7, &phi_bb151_12, &phi_bb151_15, &phi_bb151_22, &phi_bb151_23, &phi_bb151_30, &phi_bb151_31);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb153_6;
  TNode<Smi> phi_bb153_12;
  TNode<Smi> phi_bb153_15;
  if (block153.is_used()) {
    ca_.Bind(&block153, &phi_bb153_6, &phi_bb153_12, &phi_bb153_15);
    ca_.Goto(&block35, phi_bb153_6, tmp256, tmp228, tmp244, phi_bb153_12);
  }

  TNode<Smi> phi_bb154_6;
  TNode<Smi> phi_bb154_12;
  TNode<Smi> phi_bb154_15;
  TNode<IntPtrT> tmp259;
  TNode<IntPtrT> tmp260;
  TNode<IntPtrT> tmp261;
  TNode<Smi> tmp262;
  TNode<IntPtrT> tmp263;
  TNode<IntPtrT> tmp264;
  TNode<UintPtrT> tmp265;
  TNode<UintPtrT> tmp266;
  TNode<BoolT> tmp267;
  if (block154.is_used()) {
    ca_.Bind(&block154, &phi_bb154_6, &phi_bb154_12, &phi_bb154_15);
    tmp259 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp260 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp261 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp262 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp261});
    tmp263 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp262});
    tmp264 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb154_12});
    tmp265 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp264});
    tmp266 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp263});
    tmp267 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp265}, TNode<UintPtrT>{tmp266});
    ca_.Branch(tmp267, &block159, std::vector<Node*>{phi_bb154_6, phi_bb154_12, phi_bb154_15, phi_bb154_12, phi_bb154_12}, &block160, std::vector<Node*>{phi_bb154_6, phi_bb154_12, phi_bb154_15, phi_bb154_12, phi_bb154_12});
  }

  TNode<Smi> phi_bb159_6;
  TNode<Smi> phi_bb159_12;
  TNode<Smi> phi_bb159_15;
  TNode<Smi> phi_bb159_23;
  TNode<Smi> phi_bb159_24;
  TNode<IntPtrT> tmp268;
  TNode<IntPtrT> tmp269;
  TNode<IntPtrT> tmp270;
  TNode<HeapObject> tmp271;
  TNode<IntPtrT> tmp272;
  TNode<Object> tmp273;
  TNode<Object> tmp274;
  TNode<Smi> tmp275;
  TNode<Smi> tmp276;
  TNode<Smi> tmp277;
  TNode<Smi> tmp278;
  TNode<Smi> tmp279;
  TNode<Smi> tmp280;
  TNode<BoolT> tmp281;
  if (block159.is_used()) {
    ca_.Bind(&block159, &phi_bb159_6, &phi_bb159_12, &phi_bb159_15, &phi_bb159_23, &phi_bb159_24);
    tmp268 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp269 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp264}, TNode<IntPtrT>{tmp268});
    tmp270 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp259}, TNode<IntPtrT>{tmp269});
    std::tie(tmp271, tmp272) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp270}).Flatten();
    tmp273 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp271, tmp272});
    tmp274 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp273});
    tmp275 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp276 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp256}, TNode<Smi>{tmp275});
    tmp277 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp278 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kGallopLeft, p_context, p_sortState, tmp2, tmp274, tmp277, tmp256, tmp276));
    tmp279 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp256}, TNode<Smi>{tmp278});
    tmp280 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp281 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp279}, TNode<Smi>{tmp280});
    ca_.Branch(tmp281, &block166, std::vector<Node*>{phi_bb159_6, phi_bb159_12}, &block167, std::vector<Node*>{phi_bb159_6, tmp256, tmp228, tmp244, phi_bb159_12});
  }

  TNode<Smi> phi_bb160_6;
  TNode<Smi> phi_bb160_12;
  TNode<Smi> phi_bb160_15;
  TNode<Smi> phi_bb160_23;
  TNode<Smi> phi_bb160_24;
  if (block160.is_used()) {
    ca_.Bind(&block160, &phi_bb160_6, &phi_bb160_12, &phi_bb160_15, &phi_bb160_23, &phi_bb160_24);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb166_6;
  TNode<Smi> phi_bb166_12;
  TNode<Smi> tmp282;
  TNode<Smi> tmp283;
  TNode<Smi> tmp284;
  TNode<Smi> tmp285;
  TNode<Smi> tmp286;
  TNode<Smi> tmp287;
  TNode<Object> tmp288;
  TNode<Smi> tmp289;
  TNode<Smi> tmp290;
  TNode<BoolT> tmp291;
  if (block166.is_used()) {
    ca_.Bind(&block166, &phi_bb166_6, &phi_bb166_12);
    tmp282 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp228}, TNode<Smi>{tmp279});
    tmp283 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp244}, TNode<Smi>{tmp279});
    tmp284 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp285 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp283}, TNode<Smi>{tmp284});
    tmp286 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp287 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp282}, TNode<Smi>{tmp286});
    tmp288 = CodeStubAssembler(state_).CallBuiltin(Builtins::kCopy, p_context, tmp2, tmp285, tmp1, tmp287, tmp279);
    tmp289 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp256}, TNode<Smi>{tmp279});
    tmp290 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp291 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp289}, TNode<Smi>{tmp290});
    ca_.Branch(tmp291, &block168, std::vector<Node*>{phi_bb166_6, phi_bb166_12}, &block169, std::vector<Node*>{phi_bb166_6, phi_bb166_12});
  }

  TNode<Smi> phi_bb168_6;
  TNode<Smi> phi_bb168_12;
  if (block168.is_used()) {
    ca_.Bind(&block168, &phi_bb168_6, &phi_bb168_12);
    ca_.Goto(&block35, phi_bb168_6, tmp289, tmp282, tmp283, phi_bb168_12);
  }

  TNode<Smi> phi_bb169_6;
  TNode<Smi> phi_bb169_12;
  TNode<Smi> tmp292;
  TNode<BoolT> tmp293;
  if (block169.is_used()) {
    ca_.Bind(&block169, &phi_bb169_6, &phi_bb169_12);
    tmp292 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp293 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp289}, TNode<Smi>{tmp292});
    ca_.Branch(tmp293, &block170, std::vector<Node*>{phi_bb169_6, phi_bb169_12}, &block171, std::vector<Node*>{phi_bb169_6, phi_bb169_12});
  }

  TNode<Smi> phi_bb170_6;
  TNode<Smi> phi_bb170_12;
  if (block170.is_used()) {
    ca_.Bind(&block170, &phi_bb170_6, &phi_bb170_12);
    ca_.Goto(&block37, phi_bb170_6, tmp289, tmp282, tmp283, phi_bb170_12);
  }

  TNode<Smi> phi_bb171_6;
  TNode<Smi> phi_bb171_12;
  if (block171.is_used()) {
    ca_.Bind(&block171, &phi_bb171_6, &phi_bb171_12);
    ca_.Goto(&block167, phi_bb171_6, tmp289, tmp282, tmp283, phi_bb171_12);
  }

  TNode<Smi> phi_bb167_6;
  TNode<Smi> phi_bb167_7;
  TNode<Smi> phi_bb167_10;
  TNode<Smi> phi_bb167_11;
  TNode<Smi> phi_bb167_12;
  TNode<IntPtrT> tmp294;
  TNode<IntPtrT> tmp295;
  TNode<IntPtrT> tmp296;
  TNode<Smi> tmp297;
  TNode<IntPtrT> tmp298;
  TNode<Smi> tmp299;
  TNode<Smi> tmp300;
  TNode<IntPtrT> tmp301;
  TNode<UintPtrT> tmp302;
  TNode<UintPtrT> tmp303;
  TNode<BoolT> tmp304;
  if (block167.is_used()) {
    ca_.Bind(&block167, &phi_bb167_6, &phi_bb167_7, &phi_bb167_10, &phi_bb167_11, &phi_bb167_12);
    tmp294 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp295 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp296 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp297 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp296});
    tmp298 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp297});
    tmp299 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp300 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb167_10}, TNode<Smi>{tmp299});
    tmp301 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb167_10});
    tmp302 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp301});
    tmp303 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp298});
    tmp304 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp302}, TNode<UintPtrT>{tmp303});
    ca_.Branch(tmp304, &block176, std::vector<Node*>{phi_bb167_6, phi_bb167_7, phi_bb167_11, phi_bb167_12, phi_bb167_10, phi_bb167_10}, &block177, std::vector<Node*>{phi_bb167_6, phi_bb167_7, phi_bb167_11, phi_bb167_12, phi_bb167_10, phi_bb167_10});
  }

  TNode<Smi> phi_bb176_6;
  TNode<Smi> phi_bb176_7;
  TNode<Smi> phi_bb176_11;
  TNode<Smi> phi_bb176_12;
  TNode<Smi> phi_bb176_22;
  TNode<Smi> phi_bb176_23;
  TNode<IntPtrT> tmp305;
  TNode<IntPtrT> tmp306;
  TNode<IntPtrT> tmp307;
  TNode<HeapObject> tmp308;
  TNode<IntPtrT> tmp309;
  TNode<IntPtrT> tmp310;
  TNode<IntPtrT> tmp311;
  TNode<IntPtrT> tmp312;
  TNode<Smi> tmp313;
  TNode<IntPtrT> tmp314;
  TNode<Smi> tmp315;
  TNode<Smi> tmp316;
  TNode<IntPtrT> tmp317;
  TNode<UintPtrT> tmp318;
  TNode<UintPtrT> tmp319;
  TNode<BoolT> tmp320;
  if (block176.is_used()) {
    ca_.Bind(&block176, &phi_bb176_6, &phi_bb176_7, &phi_bb176_11, &phi_bb176_12, &phi_bb176_22, &phi_bb176_23);
    tmp305 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp306 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp301}, TNode<IntPtrT>{tmp305});
    tmp307 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp294}, TNode<IntPtrT>{tmp306});
    std::tie(tmp308, tmp309) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp307}).Flatten();
    tmp310 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp311 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp312 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp313 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp312});
    tmp314 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp313});
    tmp315 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp316 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb176_12}, TNode<Smi>{tmp315});
    tmp317 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb176_12});
    tmp318 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp317});
    tmp319 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp314});
    tmp320 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp318}, TNode<UintPtrT>{tmp319});
    ca_.Branch(tmp320, &block183, std::vector<Node*>{phi_bb176_6, phi_bb176_7, phi_bb176_11, phi_bb176_22, phi_bb176_23, phi_bb176_12, phi_bb176_12}, &block184, std::vector<Node*>{phi_bb176_6, phi_bb176_7, phi_bb176_11, phi_bb176_22, phi_bb176_23, phi_bb176_12, phi_bb176_12});
  }

  TNode<Smi> phi_bb177_6;
  TNode<Smi> phi_bb177_7;
  TNode<Smi> phi_bb177_11;
  TNode<Smi> phi_bb177_12;
  TNode<Smi> phi_bb177_22;
  TNode<Smi> phi_bb177_23;
  if (block177.is_used()) {
    ca_.Bind(&block177, &phi_bb177_6, &phi_bb177_7, &phi_bb177_11, &phi_bb177_12, &phi_bb177_22, &phi_bb177_23);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb183_6;
  TNode<Smi> phi_bb183_7;
  TNode<Smi> phi_bb183_11;
  TNode<Smi> phi_bb183_22;
  TNode<Smi> phi_bb183_23;
  TNode<Smi> phi_bb183_30;
  TNode<Smi> phi_bb183_31;
  TNode<IntPtrT> tmp321;
  TNode<IntPtrT> tmp322;
  TNode<IntPtrT> tmp323;
  TNode<HeapObject> tmp324;
  TNode<IntPtrT> tmp325;
  TNode<Object> tmp326;
  TNode<Smi> tmp327;
  TNode<Smi> tmp328;
  TNode<Smi> tmp329;
  TNode<BoolT> tmp330;
  if (block183.is_used()) {
    ca_.Bind(&block183, &phi_bb183_6, &phi_bb183_7, &phi_bb183_11, &phi_bb183_22, &phi_bb183_23, &phi_bb183_30, &phi_bb183_31);
    tmp321 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp322 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp317}, TNode<IntPtrT>{tmp321});
    tmp323 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp310}, TNode<IntPtrT>{tmp322});
    std::tie(tmp324, tmp325) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp323}).Flatten();
    tmp326 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp324, tmp325});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp308, tmp309}, tmp326);
    tmp327 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp328 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb183_6}, TNode<Smi>{tmp327});
    tmp329 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp330 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp328}, TNode<Smi>{tmp329});
    ca_.Branch(tmp330, &block186, std::vector<Node*>{phi_bb183_7, phi_bb183_11}, &block187, std::vector<Node*>{phi_bb183_7, phi_bb183_11});
  }

  TNode<Smi> phi_bb184_6;
  TNode<Smi> phi_bb184_7;
  TNode<Smi> phi_bb184_11;
  TNode<Smi> phi_bb184_22;
  TNode<Smi> phi_bb184_23;
  TNode<Smi> phi_bb184_30;
  TNode<Smi> phi_bb184_31;
  if (block184.is_used()) {
    ca_.Bind(&block184, &phi_bb184_6, &phi_bb184_7, &phi_bb184_11, &phi_bb184_22, &phi_bb184_23, &phi_bb184_30, &phi_bb184_31);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb186_7;
  TNode<Smi> phi_bb186_11;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_7, &phi_bb186_11);
    ca_.Goto(&block37, tmp328, phi_bb186_7, tmp300, phi_bb186_11, tmp316);
  }

  TNode<Smi> phi_bb187_7;
  TNode<Smi> phi_bb187_11;
  if (block187.is_used()) {
    ca_.Bind(&block187, &phi_bb187_7, &phi_bb187_11);
    ca_.Goto(&block110, tmp328, phi_bb187_7, tmp300, phi_bb187_11, tmp316, tmp188, tmp209, tmp279, tmp184);
  }

  TNode<Smi> phi_bb109_6;
  TNode<Smi> phi_bb109_7;
  TNode<Smi> phi_bb109_10;
  TNode<Smi> phi_bb109_11;
  TNode<Smi> phi_bb109_12;
  TNode<Smi> phi_bb109_13;
  TNode<Smi> phi_bb109_14;
  TNode<Smi> phi_bb109_15;
  TNode<BoolT> phi_bb109_16;
  TNode<Smi> tmp331;
  TNode<Smi> tmp332;
  TNode<IntPtrT> tmp333;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_6, &phi_bb109_7, &phi_bb109_10, &phi_bb109_11, &phi_bb109_12, &phi_bb109_13, &phi_bb109_14, &phi_bb109_15, &phi_bb109_16);
    tmp331 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp332 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb109_13}, TNode<Smi>{tmp331});
    tmp333 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp333}, tmp332);
    ca_.Goto(&block44, phi_bb109_6, phi_bb109_7, phi_bb109_10, phi_bb109_11, phi_bb109_12, tmp332);
  }

  TNode<Smi> phi_bb43_6;
  TNode<Smi> phi_bb43_7;
  TNode<Smi> phi_bb43_10;
  TNode<Smi> phi_bb43_11;
  TNode<Smi> phi_bb43_12;
  TNode<Smi> phi_bb43_13;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_6, &phi_bb43_7, &phi_bb43_10, &phi_bb43_11, &phi_bb43_12, &phi_bb43_13);
    ca_.Goto(&block36, phi_bb43_6, phi_bb43_7, phi_bb43_10, phi_bb43_11, phi_bb43_12);
  }

  TNode<Smi> phi_bb37_6;
  TNode<Smi> phi_bb37_7;
  TNode<Smi> phi_bb37_10;
  TNode<Smi> phi_bb37_11;
  TNode<Smi> phi_bb37_12;
  TNode<Smi> tmp334;
  TNode<BoolT> tmp335;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_6, &phi_bb37_7, &phi_bb37_10, &phi_bb37_11, &phi_bb37_12);
    tmp334 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp335 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb37_7}, TNode<Smi>{tmp334});
    ca_.Branch(tmp335, &block188, std::vector<Node*>{phi_bb37_6, phi_bb37_7, phi_bb37_10, phi_bb37_11, phi_bb37_12}, &block189, std::vector<Node*>{phi_bb37_6, phi_bb37_7, phi_bb37_10, phi_bb37_11, phi_bb37_12});
  }

  TNode<Smi> phi_bb188_6;
  TNode<Smi> phi_bb188_7;
  TNode<Smi> phi_bb188_10;
  TNode<Smi> phi_bb188_11;
  TNode<Smi> phi_bb188_12;
  TNode<Smi> tmp336;
  TNode<Smi> tmp337;
  TNode<Smi> tmp338;
  TNode<Smi> tmp339;
  TNode<Object> tmp340;
  if (block188.is_used()) {
    ca_.Bind(&block188, &phi_bb188_6, &phi_bb188_7, &phi_bb188_10, &phi_bb188_11, &phi_bb188_12);
    tmp336 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp337 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb188_7}, TNode<Smi>{tmp336});
    tmp338 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb188_10}, TNode<Smi>{tmp337});
    tmp339 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp340 = CodeStubAssembler(state_).CallBuiltin(Builtins::kCopy, p_context, tmp2, tmp339, tmp1, tmp338, phi_bb188_7);
    ca_.Goto(&block189, phi_bb188_6, phi_bb188_7, phi_bb188_10, phi_bb188_11, phi_bb188_12);
  }

  TNode<Smi> phi_bb189_6;
  TNode<Smi> phi_bb189_7;
  TNode<Smi> phi_bb189_10;
  TNode<Smi> phi_bb189_11;
  TNode<Smi> phi_bb189_12;
  if (block189.is_used()) {
    ca_.Bind(&block189, &phi_bb189_6, &phi_bb189_7, &phi_bb189_10, &phi_bb189_11, &phi_bb189_12);
    ca_.Goto(&block36, phi_bb189_6, phi_bb189_7, phi_bb189_10, phi_bb189_11, phi_bb189_12);
  }

  TNode<Smi> phi_bb36_6;
  TNode<Smi> phi_bb36_7;
  TNode<Smi> phi_bb36_10;
  TNode<Smi> phi_bb36_11;
  TNode<Smi> phi_bb36_12;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_6, &phi_bb36_7, &phi_bb36_10, &phi_bb36_11, &phi_bb36_12);
    ca_.Goto(&block34, phi_bb36_6, phi_bb36_7, phi_bb36_10, phi_bb36_11, phi_bb36_12);
  }

  TNode<Smi> phi_bb35_6;
  TNode<Smi> phi_bb35_7;
  TNode<Smi> phi_bb35_10;
  TNode<Smi> phi_bb35_11;
  TNode<Smi> phi_bb35_12;
  TNode<Smi> tmp341;
  TNode<Smi> tmp342;
  TNode<Smi> tmp343;
  TNode<Smi> tmp344;
  TNode<Smi> tmp345;
  TNode<Smi> tmp346;
  TNode<Object> tmp347;
  TNode<IntPtrT> tmp348;
  TNode<IntPtrT> tmp349;
  TNode<IntPtrT> tmp350;
  TNode<Smi> tmp351;
  TNode<IntPtrT> tmp352;
  TNode<IntPtrT> tmp353;
  TNode<UintPtrT> tmp354;
  TNode<UintPtrT> tmp355;
  TNode<BoolT> tmp356;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_6, &phi_bb35_7, &phi_bb35_10, &phi_bb35_11, &phi_bb35_12);
    tmp341 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb35_10}, TNode<Smi>{phi_bb35_6});
    tmp342 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb35_12}, TNode<Smi>{phi_bb35_6});
    tmp343 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp344 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp342}, TNode<Smi>{tmp343});
    tmp345 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp346 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp341}, TNode<Smi>{tmp345});
    tmp347 = CodeStubAssembler(state_).CallBuiltin(Builtins::kCopy, p_context, tmp1, tmp344, tmp1, tmp346, phi_bb35_6);
    tmp348 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp349 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp350 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp351 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp350});
    tmp352 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp351});
    tmp353 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp341});
    tmp354 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp353});
    tmp355 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp352});
    tmp356 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp354}, TNode<UintPtrT>{tmp355});
    ca_.Branch(tmp356, &block205, std::vector<Node*>{phi_bb35_6, phi_bb35_7, phi_bb35_11}, &block206, std::vector<Node*>{phi_bb35_6, phi_bb35_7, phi_bb35_11});
  }

  TNode<Smi> phi_bb205_6;
  TNode<Smi> phi_bb205_7;
  TNode<Smi> phi_bb205_11;
  TNode<IntPtrT> tmp357;
  TNode<IntPtrT> tmp358;
  TNode<IntPtrT> tmp359;
  TNode<HeapObject> tmp360;
  TNode<IntPtrT> tmp361;
  TNode<IntPtrT> tmp362;
  TNode<IntPtrT> tmp363;
  TNode<IntPtrT> tmp364;
  TNode<Smi> tmp365;
  TNode<IntPtrT> tmp366;
  TNode<IntPtrT> tmp367;
  TNode<UintPtrT> tmp368;
  TNode<UintPtrT> tmp369;
  TNode<BoolT> tmp370;
  if (block205.is_used()) {
    ca_.Bind(&block205, &phi_bb205_6, &phi_bb205_7, &phi_bb205_11);
    tmp357 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp358 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp353}, TNode<IntPtrT>{tmp357});
    tmp359 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp348}, TNode<IntPtrT>{tmp358});
    std::tie(tmp360, tmp361) = NewReference_Object_0(state_, TNode<HeapObject>{tmp1}, TNode<IntPtrT>{tmp359}).Flatten();
    tmp362 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp363 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp364 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp365 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp2, tmp364});
    tmp366 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp365});
    tmp367 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb205_11});
    tmp368 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp367});
    tmp369 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp366});
    tmp370 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp368}, TNode<UintPtrT>{tmp369});
    ca_.Branch(tmp370, &block212, std::vector<Node*>{phi_bb205_6, phi_bb205_7, phi_bb205_11, phi_bb205_11, phi_bb205_11}, &block213, std::vector<Node*>{phi_bb205_6, phi_bb205_7, phi_bb205_11, phi_bb205_11, phi_bb205_11});
  }

  TNode<Smi> phi_bb206_6;
  TNode<Smi> phi_bb206_7;
  TNode<Smi> phi_bb206_11;
  if (block206.is_used()) {
    ca_.Bind(&block206, &phi_bb206_6, &phi_bb206_7, &phi_bb206_11);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb212_6;
  TNode<Smi> phi_bb212_7;
  TNode<Smi> phi_bb212_11;
  TNode<Smi> phi_bb212_25;
  TNode<Smi> phi_bb212_26;
  TNode<IntPtrT> tmp371;
  TNode<IntPtrT> tmp372;
  TNode<IntPtrT> tmp373;
  TNode<HeapObject> tmp374;
  TNode<IntPtrT> tmp375;
  TNode<Object> tmp376;
  if (block212.is_used()) {
    ca_.Bind(&block212, &phi_bb212_6, &phi_bb212_7, &phi_bb212_11, &phi_bb212_25, &phi_bb212_26);
    tmp371 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp372 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp367}, TNode<IntPtrT>{tmp371});
    tmp373 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp362}, TNode<IntPtrT>{tmp372});
    std::tie(tmp374, tmp375) = NewReference_Object_0(state_, TNode<HeapObject>{tmp2}, TNode<IntPtrT>{tmp373}).Flatten();
    tmp376 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp374, tmp375});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp360, tmp361}, tmp376);
    ca_.Goto(&block34, phi_bb212_6, phi_bb212_7, tmp341, phi_bb212_11, tmp342);
  }

  TNode<Smi> phi_bb213_6;
  TNode<Smi> phi_bb213_7;
  TNode<Smi> phi_bb213_11;
  TNode<Smi> phi_bb213_25;
  TNode<Smi> phi_bb213_26;
  if (block213.is_used()) {
    ca_.Bind(&block213, &phi_bb213_6, &phi_bb213_7, &phi_bb213_11, &phi_bb213_25, &phi_bb213_26);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb34_6;
  TNode<Smi> phi_bb34_7;
  TNode<Smi> phi_bb34_10;
  TNode<Smi> phi_bb34_11;
  TNode<Smi> phi_bb34_12;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_6, &phi_bb34_7, &phi_bb34_10, &phi_bb34_11, &phi_bb34_12);
    ca_.Goto(&block215);
  }

    ca_.Bind(&block215);
}

TNode<Smi> ComputeMinRunLength_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_nArg) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    ca_.Goto(&block8, p_nArg, tmp0);
  }

  TNode<Smi> phi_bb8_1;
  TNode<Smi> phi_bb8_2;
  TNode<Smi> tmp1;
  TNode<BoolT> tmp2;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_1, &phi_bb8_2);
    tmp1 = FromConstexpr_Smi_constexpr_int31_0(state_, 64);
    tmp2 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb8_1}, TNode<Smi>{tmp1});
    ca_.Branch(tmp2, &block6, std::vector<Node*>{phi_bb8_1, phi_bb8_2}, &block7, std::vector<Node*>{phi_bb8_1, phi_bb8_2});
  }

  TNode<Smi> phi_bb6_1;
  TNode<Smi> phi_bb6_2;
  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_1, &phi_bb6_2);
    tmp3 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp4 = CodeStubAssembler(state_).SmiAnd(TNode<Smi>{phi_bb6_1}, TNode<Smi>{tmp3});
    tmp5 = CodeStubAssembler(state_).SmiOr(TNode<Smi>{phi_bb6_2}, TNode<Smi>{tmp4});
    tmp6 = CodeStubAssembler(state_).SmiSar(TNode<Smi>{phi_bb6_1}, 1);
    ca_.Goto(&block8, tmp6, tmp5);
  }

  TNode<Smi> phi_bb7_1;
  TNode<Smi> phi_bb7_2;
  TNode<Smi> tmp7;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_1, &phi_bb7_2);
    tmp7 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb7_1}, TNode<Smi>{phi_bb7_2});
    ca_.Goto(&block19);
  }

    ca_.Bind(&block19);
  return TNode<Smi>{tmp7};
}

TNode<BoolT> RunInvariantEstablished_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_n) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 2);
    tmp1 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{p_n}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<BoolT> tmp2;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp2);
  }

  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<Smi> tmp9;
  TNode<Smi> tmp10;
  TNode<BoolT> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp3 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{p_pendingRuns}, TNode<Smi>{p_n});
    tmp4 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp5 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_n}, TNode<Smi>{tmp4});
    tmp6 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{p_pendingRuns}, TNode<Smi>{tmp5});
    tmp7 = FromConstexpr_Smi_constexpr_int31_0(state_, 2);
    tmp8 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_n}, TNode<Smi>{tmp7});
    tmp9 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{p_pendingRuns}, TNode<Smi>{tmp8});
    tmp10 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp6}, TNode<Smi>{tmp3});
    tmp11 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp9}, TNode<Smi>{tmp10});
    ca_.Goto(&block1, tmp11);
  }

  TNode<BoolT> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<BoolT>{phi_bb1_3};
}

void MergeCollapse_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp0});
    ca_.Goto(&block4);
  }

  TNode<Smi> tmp2;
  TNode<Smi> tmp3;
  TNode<BoolT> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = GetPendingRunsSize_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState});
    tmp3 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp4 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp2}, TNode<Smi>{tmp3});
    ca_.Branch(tmp4, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<Smi> tmp9;
  TNode<BoolT> tmp10;
  TNode<BoolT> tmp11;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = GetPendingRunsSize_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState});
    tmp6 = FromConstexpr_Smi_constexpr_int31_0(state_, 2);
    tmp7 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp5}, TNode<Smi>{tmp6});
    tmp8 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp9 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp7}, TNode<Smi>{tmp8});
    tmp10 = RunInvariantEstablished_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp1}, TNode<Smi>{tmp9});
    tmp11 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp10});
    ca_.Branch(tmp11, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<BoolT> tmp12;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp12 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block9, tmp12);
  }

  TNode<BoolT> tmp13;
  TNode<BoolT> tmp14;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp13 = RunInvariantEstablished_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp1}, TNode<Smi>{tmp7});
    tmp14 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp13});
    ca_.Goto(&block9, tmp14);
  }

  TNode<BoolT> phi_bb9_5;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_5);
    ca_.Branch(phi_bb9_5, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  TNode<Smi> tmp15;
  TNode<Smi> tmp16;
  TNode<Smi> tmp17;
  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  TNode<Smi> tmp20;
  TNode<BoolT> tmp21;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp15 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp16 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp7}, TNode<Smi>{tmp15});
    tmp17 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp1}, TNode<Smi>{tmp16});
    tmp18 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp19 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp7}, TNode<Smi>{tmp18});
    tmp20 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp1}, TNode<Smi>{tmp19});
    tmp21 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp17}, TNode<Smi>{tmp20});
    ca_.Branch(tmp21, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{tmp7});
  }

  TNode<Smi> tmp22;
  TNode<Smi> tmp23;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp22 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp23 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp7}, TNode<Smi>{tmp22});
    ca_.Goto(&block12, tmp23);
  }

  TNode<Smi> phi_bb12_3;
  TNode<Smi> tmp24;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_3);
    tmp24 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kMergeAt, p_context, p_sortState, phi_bb12_3));
    ca_.Goto(&block10, phi_bb12_3);
  }

  TNode<Smi> tmp25;
  TNode<Smi> tmp26;
  TNode<Smi> tmp27;
  TNode<Smi> tmp28;
  TNode<BoolT> tmp29;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp25 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp1}, TNode<Smi>{tmp7});
    tmp26 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp27 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp7}, TNode<Smi>{tmp26});
    tmp28 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp1}, TNode<Smi>{tmp27});
    tmp29 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp25}, TNode<Smi>{tmp28});
    ca_.Branch(tmp29, &block13, std::vector<Node*>{}, &block14, std::vector<Node*>{});
  }

  TNode<Smi> tmp30;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp30 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kMergeAt, p_context, p_sortState, tmp7));
    ca_.Goto(&block10, tmp7);
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block3);
  }

  TNode<Smi> phi_bb10_3;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_3);
    ca_.Goto(&block4);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block16);
  }

    ca_.Bind(&block16);
}

void MergeForceCollapse_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp0});
    ca_.Goto(&block4);
  }

  TNode<Smi> tmp2;
  TNode<Smi> tmp3;
  TNode<BoolT> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = GetPendingRunsSize_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState});
    tmp3 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp4 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp2}, TNode<Smi>{tmp3});
    ca_.Branch(tmp4, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<BoolT> tmp9;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = GetPendingRunsSize_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState});
    tmp6 = FromConstexpr_Smi_constexpr_int31_0(state_, 2);
    tmp7 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp5}, TNode<Smi>{tmp6});
    tmp8 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp9 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp7}, TNode<Smi>{tmp8});
    ca_.Branch(tmp9, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<Smi> tmp10;
  TNode<Smi> tmp11;
  TNode<Smi> tmp12;
  TNode<Smi> tmp13;
  TNode<Smi> tmp14;
  TNode<Smi> tmp15;
  TNode<BoolT> tmp16;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp10 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp11 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp7}, TNode<Smi>{tmp10});
    tmp12 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp1}, TNode<Smi>{tmp11});
    tmp13 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp14 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp7}, TNode<Smi>{tmp13});
    tmp15 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp1}, TNode<Smi>{tmp14});
    tmp16 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp12}, TNode<Smi>{tmp15});
    ca_.Goto(&block9, tmp16);
  }

  TNode<BoolT> tmp17;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp17 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block9, tmp17);
  }

  TNode<BoolT> phi_bb9_5;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_5);
    ca_.Branch(phi_bb9_5, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{tmp7});
  }

  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp18 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp19 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp7}, TNode<Smi>{tmp18});
    ca_.Goto(&block6, tmp19);
  }

  TNode<Smi> phi_bb6_3;
  TNode<Smi> tmp20;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_3);
    tmp20 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kMergeAt, p_context, p_sortState, phi_bb6_3));
    ca_.Goto(&block4);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block10);
  }

    ca_.Bind(&block10);
}

void ArrayTimSortImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 2);
    tmp1 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{p_length}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ca_.Goto(&block1);
  }

  TNode<Smi> tmp2;
  TNode<Smi> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp3 = ComputeMinRunLength_0(state_, TNode<Smi>{p_length});
    ca_.Goto(&block6, p_length, tmp2);
  }

  TNode<Smi> phi_bb6_3;
  TNode<Smi> phi_bb6_4;
  TNode<Smi> tmp4;
  TNode<BoolT> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_3, &phi_bb6_4);
    tmp4 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp5 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{phi_bb6_3}, TNode<Smi>{tmp4});
    ca_.Branch(tmp5, &block4, std::vector<Node*>{phi_bb6_3, phi_bb6_4}, &block5, std::vector<Node*>{phi_bb6_3, phi_bb6_4});
  }

  TNode<Smi> phi_bb4_3;
  TNode<Smi> phi_bb4_4;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_3, &phi_bb4_4);
    tmp6 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb4_4}, TNode<Smi>{phi_bb4_3});
    tmp7 = CountAndMakeRun_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{phi_bb4_4}, TNode<Smi>{tmp6});
    tmp8 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp7}, TNode<Smi>{tmp3});
    ca_.Branch(tmp8, &block7, std::vector<Node*>{phi_bb4_3, phi_bb4_4}, &block8, std::vector<Node*>{phi_bb4_3, phi_bb4_4, tmp7});
  }

  TNode<Smi> phi_bb7_3;
  TNode<Smi> phi_bb7_4;
  TNode<Smi> tmp9;
  TNode<Smi> tmp10;
  TNode<Smi> tmp11;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_3, &phi_bb7_4);
    tmp9 = CodeStubAssembler(state_).SmiMin(TNode<Smi>{tmp3}, TNode<Smi>{phi_bb7_3});
    tmp10 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb7_4}, TNode<Smi>{tmp7});
    tmp11 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb7_4}, TNode<Smi>{tmp9});
    BinaryInsertionSort_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{phi_bb7_4}, TNode<Smi>{tmp10}, TNode<Smi>{tmp11});
    ca_.Goto(&block8, phi_bb7_3, phi_bb7_4, tmp9);
  }

  TNode<Smi> phi_bb8_3;
  TNode<Smi> phi_bb8_4;
  TNode<Smi> phi_bb8_6;
  TNode<Smi> tmp12;
  TNode<Smi> tmp13;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_3, &phi_bb8_4, &phi_bb8_6);
    PushRun_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{phi_bb8_4}, TNode<Smi>{phi_bb8_6});
    MergeCollapse_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState});
    tmp12 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb8_4}, TNode<Smi>{phi_bb8_6});
    tmp13 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb8_3}, TNode<Smi>{phi_bb8_6});
    ca_.Goto(&block6, tmp13, tmp12);
  }

  TNode<Smi> phi_bb5_3;
  TNode<Smi> phi_bb5_4;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_3, &phi_bb5_4);
    MergeForceCollapse_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState});
    ca_.Goto(&block1);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(&block17);
  }

    ca_.Bind(&block17);
}

TNode<Smi> CompactReceiverElementsIntoWorkArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<FixedArray> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<BuiltinPtr> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Number> tmp11;
  TNode<BoolT> tmp12;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp3 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp2});
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp5 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp3, tmp4});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp5});
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp9 = CodeStubAssembler(state_).LoadReference<BuiltinPtr>(CodeStubAssembler::Reference{p_sortState, tmp8});
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp11 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_sortState, tmp10});
    tmp12 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{tmp11});
    ca_.Branch(tmp12, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<Smi> tmp13;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp13 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp11});
    ca_.Goto(&block8, tmp13);
  }

  TNode<UintPtrT> tmp14;
  TNode<Smi> tmp15;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp14 = kSmiMax_0(state_);
    compiler::CodeAssemblerLabel label16(&ca_);
    tmp15 = Convert_PositiveSmi_uintptr_0(state_, TNode<UintPtrT>{tmp14}, &label16);
    ca_.Goto(&block12);
    if (label16.is_used()) {
      ca_.Bind(&label16);
      ca_.Goto(&block13);
    }
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block8, tmp15);
  }

  TNode<Smi> phi_bb8_7;
  TNode<Smi> tmp17;
  TNode<Smi> tmp18;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_7);
    tmp17 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp18 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    ca_.Goto(&block16, tmp1, tmp6, tmp7, phi_bb8_7, tmp17, tmp18);
  }

  TNode<FixedArray> phi_bb16_2;
  TNode<IntPtrT> phi_bb16_3;
  TNode<IntPtrT> phi_bb16_4;
  TNode<Smi> phi_bb16_7;
  TNode<Smi> phi_bb16_8;
  TNode<Smi> phi_bb16_9;
  TNode<BoolT> tmp19;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_2, &phi_bb16_3, &phi_bb16_4, &phi_bb16_7, &phi_bb16_8, &phi_bb16_9);
    tmp19 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb16_9}, TNode<Number>{tmp11});
    ca_.Branch(tmp19, &block14, std::vector<Node*>{phi_bb16_2, phi_bb16_3, phi_bb16_4, phi_bb16_7, phi_bb16_8, phi_bb16_9}, &block15, std::vector<Node*>{phi_bb16_2, phi_bb16_3, phi_bb16_4, phi_bb16_7, phi_bb16_8, phi_bb16_9});
  }

  TNode<FixedArray> phi_bb14_2;
  TNode<IntPtrT> phi_bb14_3;
  TNode<IntPtrT> phi_bb14_4;
  TNode<Smi> phi_bb14_7;
  TNode<Smi> phi_bb14_8;
  TNode<Smi> phi_bb14_9;
  TNode<Object> tmp20;
  TNode<Oddball> tmp21;
  TNode<BoolT> tmp22;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_2, &phi_bb14_3, &phi_bb14_4, &phi_bb14_7, &phi_bb14_8, &phi_bb14_9);
tmp20 = CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallableFor(ca_.isolate(),ExampleBuiltinForTorqueFunctionPointerType(5)).descriptor(), tmp9, p_context, p_sortState, phi_bb14_9);
    tmp21 = TheHole_0(state_);
    tmp22 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp20}, TNode<HeapObject>{tmp21});
    ca_.Branch(tmp22, &block18, std::vector<Node*>{phi_bb14_2, phi_bb14_3, phi_bb14_4, phi_bb14_7, phi_bb14_8, phi_bb14_9}, &block19, std::vector<Node*>{phi_bb14_2, phi_bb14_3, phi_bb14_4, phi_bb14_7, phi_bb14_8, phi_bb14_9});
  }

  TNode<FixedArray> phi_bb18_2;
  TNode<IntPtrT> phi_bb18_3;
  TNode<IntPtrT> phi_bb18_4;
  TNode<Smi> phi_bb18_7;
  TNode<Smi> phi_bb18_8;
  TNode<Smi> phi_bb18_9;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_2, &phi_bb18_3, &phi_bb18_4, &phi_bb18_7, &phi_bb18_8, &phi_bb18_9);
    ca_.Goto(&block20, phi_bb18_2, phi_bb18_3, phi_bb18_4, phi_bb18_7, phi_bb18_8, phi_bb18_9);
  }

  TNode<FixedArray> phi_bb19_2;
  TNode<IntPtrT> phi_bb19_3;
  TNode<IntPtrT> phi_bb19_4;
  TNode<Smi> phi_bb19_7;
  TNode<Smi> phi_bb19_8;
  TNode<Smi> phi_bb19_9;
  TNode<Oddball> tmp23;
  TNode<BoolT> tmp24;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_2, &phi_bb19_3, &phi_bb19_4, &phi_bb19_7, &phi_bb19_8, &phi_bb19_9);
    tmp23 = Undefined_0(state_);
    tmp24 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp20}, TNode<HeapObject>{tmp23});
    ca_.Branch(tmp24, &block21, std::vector<Node*>{phi_bb19_2, phi_bb19_3, phi_bb19_4, phi_bb19_7, phi_bb19_8, phi_bb19_9}, &block22, std::vector<Node*>{phi_bb19_2, phi_bb19_3, phi_bb19_4, phi_bb19_7, phi_bb19_8, phi_bb19_9});
  }

  TNode<FixedArray> phi_bb21_2;
  TNode<IntPtrT> phi_bb21_3;
  TNode<IntPtrT> phi_bb21_4;
  TNode<Smi> phi_bb21_7;
  TNode<Smi> phi_bb21_8;
  TNode<Smi> phi_bb21_9;
  TNode<Smi> tmp25;
  TNode<Smi> tmp26;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_2, &phi_bb21_3, &phi_bb21_4, &phi_bb21_7, &phi_bb21_8, &phi_bb21_9);
    tmp25 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp26 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb21_8}, TNode<Smi>{tmp25});
    ca_.Goto(&block23, phi_bb21_2, phi_bb21_3, phi_bb21_4, phi_bb21_7, tmp26, phi_bb21_9);
  }

  TNode<FixedArray> phi_bb22_2;
  TNode<IntPtrT> phi_bb22_3;
  TNode<IntPtrT> phi_bb22_4;
  TNode<Smi> phi_bb22_7;
  TNode<Smi> phi_bb22_8;
  TNode<Smi> phi_bb22_9;
  TNode<BoolT> tmp27;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_2, &phi_bb22_3, &phi_bb22_4, &phi_bb22_7, &phi_bb22_8, &phi_bb22_9);
    tmp27 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb22_3}, TNode<IntPtrT>{phi_bb22_4});
    ca_.Branch(tmp27, &block30, std::vector<Node*>{phi_bb22_2, phi_bb22_3, phi_bb22_4, phi_bb22_7, phi_bb22_8, phi_bb22_9}, &block31, std::vector<Node*>{phi_bb22_2, phi_bb22_3, phi_bb22_4, phi_bb22_7, phi_bb22_8, phi_bb22_9});
  }

  TNode<FixedArray> phi_bb30_2;
  TNode<IntPtrT> phi_bb30_3;
  TNode<IntPtrT> phi_bb30_4;
  TNode<Smi> phi_bb30_7;
  TNode<Smi> phi_bb30_8;
  TNode<Smi> phi_bb30_9;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<FixedArray> tmp34;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_2, &phi_bb30_3, &phi_bb30_4, &phi_bb30_7, &phi_bb30_8, &phi_bb30_9);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp29 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb30_3}, TNode<IntPtrT>{tmp28});
    tmp30 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb30_3}, TNode<IntPtrT>{tmp29});
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp32 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp30}, TNode<IntPtrT>{tmp31});
    tmp33 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp34 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb30_2}, TNode<IntPtrT>{tmp33}, TNode<IntPtrT>{phi_bb30_4}, TNode<IntPtrT>{tmp32});
    ca_.Goto(&block31, tmp34, tmp32, phi_bb30_4, phi_bb30_7, phi_bb30_8, phi_bb30_9);
  }

  TNode<FixedArray> phi_bb31_2;
  TNode<IntPtrT> phi_bb31_3;
  TNode<IntPtrT> phi_bb31_4;
  TNode<Smi> phi_bb31_7;
  TNode<Smi> phi_bb31_8;
  TNode<Smi> phi_bb31_9;
  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<Smi> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<UintPtrT> tmp42;
  TNode<UintPtrT> tmp43;
  TNode<BoolT> tmp44;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_2, &phi_bb31_3, &phi_bb31_4, &phi_bb31_7, &phi_bb31_8, &phi_bb31_9);
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp37 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp38 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{phi_bb31_2, tmp37});
    tmp39 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp38});
    tmp40 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp41 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb31_4}, TNode<IntPtrT>{tmp40});
    tmp42 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb31_4});
    tmp43 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp39});
    tmp44 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp42}, TNode<UintPtrT>{tmp43});
    ca_.Branch(tmp44, &block49, std::vector<Node*>{phi_bb31_7, phi_bb31_8, phi_bb31_9, phi_bb31_4, phi_bb31_4, phi_bb31_4, phi_bb31_4}, &block50, std::vector<Node*>{phi_bb31_7, phi_bb31_8, phi_bb31_9, phi_bb31_4, phi_bb31_4, phi_bb31_4, phi_bb31_4});
  }

  TNode<Smi> phi_bb49_7;
  TNode<Smi> phi_bb49_8;
  TNode<Smi> phi_bb49_9;
  TNode<IntPtrT> phi_bb49_17;
  TNode<IntPtrT> phi_bb49_18;
  TNode<IntPtrT> phi_bb49_22;
  TNode<IntPtrT> phi_bb49_23;
  TNode<IntPtrT> tmp45;
  TNode<IntPtrT> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<HeapObject> tmp48;
  TNode<IntPtrT> tmp49;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_7, &phi_bb49_8, &phi_bb49_9, &phi_bb49_17, &phi_bb49_18, &phi_bb49_22, &phi_bb49_23);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp46 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{phi_bb49_23}, TNode<IntPtrT>{tmp45});
    tmp47 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp35}, TNode<IntPtrT>{tmp46});
    std::tie(tmp48, tmp49) = NewReference_Object_0(state_, TNode<HeapObject>{phi_bb31_2}, TNode<IntPtrT>{tmp47}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp48, tmp49}, tmp20);
    ca_.Goto(&block23, phi_bb31_2, phi_bb31_3, tmp41, phi_bb49_7, phi_bb49_8, phi_bb49_9);
  }

  TNode<Smi> phi_bb50_7;
  TNode<Smi> phi_bb50_8;
  TNode<Smi> phi_bb50_9;
  TNode<IntPtrT> phi_bb50_17;
  TNode<IntPtrT> phi_bb50_18;
  TNode<IntPtrT> phi_bb50_22;
  TNode<IntPtrT> phi_bb50_23;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_7, &phi_bb50_8, &phi_bb50_9, &phi_bb50_17, &phi_bb50_18, &phi_bb50_22, &phi_bb50_23);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb23_2;
  TNode<IntPtrT> phi_bb23_3;
  TNode<IntPtrT> phi_bb23_4;
  TNode<Smi> phi_bb23_7;
  TNode<Smi> phi_bb23_8;
  TNode<Smi> phi_bb23_9;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_2, &phi_bb23_3, &phi_bb23_4, &phi_bb23_7, &phi_bb23_8, &phi_bb23_9);
    ca_.Goto(&block20, phi_bb23_2, phi_bb23_3, phi_bb23_4, phi_bb23_7, phi_bb23_8, phi_bb23_9);
  }

  TNode<FixedArray> phi_bb20_2;
  TNode<IntPtrT> phi_bb20_3;
  TNode<IntPtrT> phi_bb20_4;
  TNode<Smi> phi_bb20_7;
  TNode<Smi> phi_bb20_8;
  TNode<Smi> phi_bb20_9;
  TNode<Smi> tmp50;
  TNode<Smi> tmp51;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_2, &phi_bb20_3, &phi_bb20_4, &phi_bb20_7, &phi_bb20_8, &phi_bb20_9);
    tmp50 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp51 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb20_9}, TNode<Smi>{tmp50});
    ca_.Goto(&block16, phi_bb20_2, phi_bb20_3, phi_bb20_4, phi_bb20_7, phi_bb20_8, tmp51);
  }

  TNode<FixedArray> phi_bb15_2;
  TNode<IntPtrT> phi_bb15_3;
  TNode<IntPtrT> phi_bb15_4;
  TNode<Smi> phi_bb15_7;
  TNode<Smi> phi_bb15_8;
  TNode<Smi> phi_bb15_9;
  TNode<IntPtrT> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<Smi> tmp55;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_2, &phi_bb15_3, &phi_bb15_4, &phi_bb15_7, &phi_bb15_8, &phi_bb15_9);
    tmp52 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp52}, phi_bb15_2);
    tmp53 = FromConstexpr_intptr_constexpr_int31_0(state_, 60);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp53}, phi_bb15_7);
    tmp54 = FromConstexpr_intptr_constexpr_int31_0(state_, 64);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp54}, phi_bb15_8);
    tmp55 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb15_4});
    ca_.Goto(&block52);
  }

    ca_.Bind(&block52);
  return TNode<Smi>{tmp55};
}

void CopyWorkArrayToReceiver_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_numberOfNonUndefined) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BuiltinPtr> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<FixedArray> tmp3;
  TNode<Smi> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp1 = CodeStubAssembler(state_).LoadReference<BuiltinPtr>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp3 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp2});
    tmp4 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    ca_.Goto(&block12, tmp4);
  }

  TNode<Smi> phi_bb12_5;
  TNode<BoolT> tmp5;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_5);
    tmp5 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb12_5}, TNode<Smi>{p_numberOfNonUndefined});
    ca_.Branch(tmp5, &block10, std::vector<Node*>{phi_bb12_5}, &block11, std::vector<Node*>{phi_bb12_5});
  }

  TNode<Smi> phi_bb10_5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Smi> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_5);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp3, tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp9});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb10_5});
    tmp12 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp14 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp12}, TNode<UintPtrT>{tmp13});
    ca_.Branch(tmp14, &block18, std::vector<Node*>{phi_bb10_5, phi_bb10_5, phi_bb10_5, phi_bb10_5}, &block19, std::vector<Node*>{phi_bb10_5, phi_bb10_5, phi_bb10_5, phi_bb10_5});
  }

  TNode<Smi> phi_bb18_5;
  TNode<Smi> phi_bb18_8;
  TNode<Smi> phi_bb18_13;
  TNode<Smi> phi_bb18_14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<HeapObject> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Object> tmp20;
  TNode<Object> tmp21;
  TNode<Smi> tmp22;
  TNode<Smi> tmp23;
  TNode<Smi> tmp24;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_5, &phi_bb18_8, &phi_bb18_13, &phi_bb18_14);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp16 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp15});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_Object_0(state_, TNode<HeapObject>{tmp3}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp18, tmp19});
    tmp21 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp20});
tmp22 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallableFor(ca_.isolate(),ExampleBuiltinForTorqueFunctionPointerType(6)).descriptor(), tmp1, p_context, p_sortState, phi_bb18_8, tmp21));
    tmp23 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp24 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb18_5}, TNode<Smi>{tmp23});
    ca_.Goto(&block12, tmp24);
  }

  TNode<Smi> phi_bb19_5;
  TNode<Smi> phi_bb19_8;
  TNode<Smi> phi_bb19_13;
  TNode<Smi> phi_bb19_14;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_5, &phi_bb19_8, &phi_bb19_13, &phi_bb19_14);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb11_5;
  TNode<IntPtrT> tmp25;
  TNode<Smi> tmp26;
  TNode<Smi> tmp27;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_5);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 64);
    tmp26 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp25});
    tmp27 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp26}, TNode<Smi>{p_numberOfNonUndefined});
    ca_.Goto(&block23, phi_bb11_5);
  }

  TNode<Smi> phi_bb23_5;
  TNode<BoolT> tmp28;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_5);
    tmp28 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb23_5}, TNode<Smi>{tmp27});
    ca_.Branch(tmp28, &block21, std::vector<Node*>{phi_bb23_5}, &block22, std::vector<Node*>{phi_bb23_5});
  }

  TNode<Smi> phi_bb21_5;
  TNode<Oddball> tmp29;
  TNode<Smi> tmp30;
  TNode<Smi> tmp31;
  TNode<Smi> tmp32;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_5);
    tmp29 = Undefined_0(state_);
tmp30 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallableFor(ca_.isolate(),ExampleBuiltinForTorqueFunctionPointerType(6)).descriptor(), tmp1, p_context, p_sortState, phi_bb21_5, tmp29));
    tmp31 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp32 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb21_5}, TNode<Smi>{tmp31});
    ca_.Goto(&block23, tmp32);
  }

  TNode<Smi> phi_bb22_5;
  TNode<IntPtrT> tmp33;
  TNode<Smi> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<BuiltinPtr> tmp36;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_5);
    tmp33 = FromConstexpr_intptr_constexpr_int31_0(state_, 60);
    tmp34 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp33});
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp36 = CodeStubAssembler(state_).LoadReference<BuiltinPtr>(CodeStubAssembler::Reference{p_sortState, tmp35});
    ca_.Goto(&block27, phi_bb22_5);
  }

  TNode<Smi> phi_bb27_5;
  TNode<BoolT> tmp37;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_5);
    tmp37 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb27_5}, TNode<Smi>{tmp34});
    ca_.Branch(tmp37, &block25, std::vector<Node*>{phi_bb27_5}, &block26, std::vector<Node*>{phi_bb27_5});
  }

  TNode<Smi> phi_bb25_5;
  TNode<Smi> tmp38;
  TNode<Smi> tmp39;
  TNode<Smi> tmp40;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_5);
tmp38 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallableFor(ca_.isolate(),ExampleBuiltinForTorqueFunctionPointerType(7)).descriptor(), tmp36, p_context, p_sortState, phi_bb25_5));
    tmp39 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp40 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb25_5}, TNode<Smi>{tmp39});
    ca_.Goto(&block27, tmp40);
  }

  TNode<Smi> phi_bb26_5;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_5);
    ca_.Goto(&block29);
  }

    ca_.Bind(&block29);
}

TF_BUILTIN(ArrayTimSort, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CompactReceiverElementsIntoWorkArray_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1});
    ArrayTimSortImpl_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp0});
    compiler::CodeAssemblerLabel label1(&ca_);
    Method_SortState_CheckAccessor_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    Method_SortState_ResetToGenericAccessor_0(state_, TNode<SortState>{parameter1});
    ca_.Goto(&block1);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block1);
  }

  TNode<Smi> tmp2;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    CopyWorkArrayToReceiver_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp0});
    tmp2 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(ArrayPrototypeSort, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Object> tmp1;
  TNode<HeapObject> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp0});
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Undefined_OR_CallableApiObject_OR_CallableJSProxy_OR_JSBoundFunction_OR_JSFunction_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1}, &label3);
    ca_.Goto(&block3);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kBadSortComparisonFunction, TNode<Object>{tmp1});
  }

  TNode<JSReceiver> tmp4;
  TNode<Number> tmp5;
  TNode<Number> tmp6;
  TNode<BoolT> tmp7;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp4 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kToObject, parameter0, parameter1));
    tmp5 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = FromConstexpr_Number_constexpr_int31_0(state_, 2);
    tmp7 = NumberIsLessThan_0(state_, TNode<Number>{tmp5}, TNode<Number>{tmp6});
    ca_.Branch(tmp7, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    arguments.PopAndReturn(parameter1);
  }

  TNode<SortState> tmp8;
  TNode<Object> tmp9;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = NewSortState_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp4}, TNode<HeapObject>{tmp2}, TNode<Number>{tmp5});
    tmp9 = CodeStubAssembler(state_).CallBuiltin(Builtins::kArrayTimSort, parameter0, tmp8);
    arguments.PopAndReturn(parameter1);
  }
}

TNode<JSReceiver> LoadSortStateReceiver_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSReceiver>{tmp1};
}

void StoreSortStateReceiver_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<JSReceiver> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<Map> LoadSortStateInitialReceiverMap_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Map>{tmp1};
}

void StoreSortStateInitialReceiverMap_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Map> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<Number> LoadSortStateInitialReceiverLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Number> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp1 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Number>{tmp1};
}

void StoreSortStateInitialReceiverLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Number> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<HeapObject> LoadSortStateUserCmpFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<HeapObject> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp1 = CodeStubAssembler(state_).LoadReference<HeapObject>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<HeapObject>{tmp1};
}

void StoreSortStateUserCmpFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<HeapObject> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<HeapObject>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<BuiltinPtr> LoadSortStateSortComparePtr_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BuiltinPtr> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp1 = CodeStubAssembler(state_).LoadReference<BuiltinPtr>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BuiltinPtr>{tmp1};
}

void StoreSortStateSortComparePtr_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<BuiltinPtr> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<BuiltinPtr> LoadSortStateLoadFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BuiltinPtr> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp1 = CodeStubAssembler(state_).LoadReference<BuiltinPtr>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BuiltinPtr>{tmp1};
}

void StoreSortStateLoadFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<BuiltinPtr> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<BuiltinPtr> LoadSortStateStoreFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BuiltinPtr> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp1 = CodeStubAssembler(state_).LoadReference<BuiltinPtr>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BuiltinPtr>{tmp1};
}

void StoreSortStateStoreFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<BuiltinPtr> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<BuiltinPtr> LoadSortStateDeleteFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BuiltinPtr> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp1 = CodeStubAssembler(state_).LoadReference<BuiltinPtr>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BuiltinPtr>{tmp1};
}

void StoreSortStateDeleteFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<BuiltinPtr> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<BuiltinPtr> LoadSortStateCanUseSameAccessorFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BuiltinPtr> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    tmp1 = CodeStubAssembler(state_).LoadReference<BuiltinPtr>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BuiltinPtr>{tmp1};
}

void StoreSortStateCanUseSameAccessorFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<BuiltinPtr> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<Smi> LoadSortStateMinGallop_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp1};
}

void StoreSortStateMinGallop_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<Smi> LoadSortStatePendingRunsSize_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp1};
}

void StoreSortStatePendingRunsSize_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<FixedArray> LoadSortStatePendingRuns_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<FixedArray>{tmp1};
}

void StoreSortStatePendingRuns_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<FixedArray> LoadSortStateWorkArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<FixedArray>{tmp1};
}

void StoreSortStateWorkArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<FixedArray> LoadSortStateTempArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 56);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<FixedArray>{tmp1};
}

void StoreSortStateTempArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 56);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<Smi> LoadSortStateSortLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 60);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp1};
}

void StoreSortStateSortLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 60);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<Smi> LoadSortStateNumberOfUndefined_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 64);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp1};
}

void StoreSortStateNumberOfUndefined_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 64);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<Number> Method_SortState_Compare_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_this, TNode<Object> p_x, TNode<Object> p_y) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BuiltinPtr> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<HeapObject> tmp3;
  TNode<Number> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp1 = CodeStubAssembler(state_).LoadReference<BuiltinPtr>(CodeStubAssembler::Reference{p_this, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp3 = CodeStubAssembler(state_).LoadReference<HeapObject>(CodeStubAssembler::Reference{p_this, tmp2});
tmp4 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallableFor(ca_.isolate(),ExampleBuiltinForTorqueFunctionPointerType(9)).descriptor(), tmp1, p_context, tmp3, p_x, p_y));
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Number>{tmp4};
}

void Method_SortState_CheckAccessor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_this, compiler::CodeAssemblerLabel* label_Bailout) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<BoolT> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_this, tmp0});
    tmp2 = IsFastJSArray_0(state_, TNode<Object>{tmp1}, TNode<Context>{p_context});
    tmp3 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp2});
    ca_.Branch(tmp3, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp4;
  TNode<BuiltinPtr> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<JSReceiver> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Map> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Number> tmp11;
  TNode<Oddball> tmp12;
  TNode<BoolT> tmp13;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    tmp5 = CodeStubAssembler(state_).LoadReference<BuiltinPtr>(CodeStubAssembler::Reference{p_this, tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp7 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_this, tmp6});
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp9 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_this, tmp8});
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp11 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_this, tmp10});
tmp12 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallableFor(ca_.isolate(),ExampleBuiltinForTorqueFunctionPointerType(8)).descriptor(), tmp5, p_context, tmp7, tmp9, tmp11));
    tmp13 = CodeStubAssembler(state_).IsFalse(TNode<Oddball>{tmp12});
    ca_.Branch(tmp13, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block1);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block7);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Bailout);
  }

    ca_.Bind(&block7);
}

void Method_SortState_ResetToGenericAccessor_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_this) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{p_this, tmp0}, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kLoad_GenericElementsAccessor_0)));
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{p_this, tmp1}, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kStore_GenericElementsAccessor_0)));
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    CodeStubAssembler(state_).StoreReference<BuiltinPtr>(CodeStubAssembler::Reference{p_this, tmp2}, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtins::kDelete_GenericElementsAccessor_0)));
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<SortState> DownCastForTorqueClass_SortState_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_o, tmp0});
    if (((CodeStubAssembler(state_).ConstexprInt31Equal(static_cast<InstanceType>(178), static_cast<InstanceType>(178))))) {
      ca_.Goto(&block3);
    } else {
      ca_.Goto(&block4);
    }
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    if ((CodeStubAssembler(state_).ClassHasMapConstant<SortState>())) {
      ca_.Goto(&block6);
    } else {
      ca_.Goto(&block7);
    }
  }

  TNode<Map> tmp2;
  TNode<BoolT> tmp3;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp2 = CodeStubAssembler(state_).GetClassMapConstant<SortState>();
    tmp3 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{tmp1}, TNode<HeapObject>{tmp2});
    ca_.Branch(tmp3, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block1);
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block8);
  }

  TNode<IntPtrT> tmp4;
  TNode<Uint16T> tmp5;
  TNode<Uint32T> tmp6;
  TNode<BoolT> tmp7;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp5 = CodeStubAssembler(state_).LoadReference<Uint16T>(CodeStubAssembler::Reference{tmp1, tmp4});
    tmp6 = FromConstexpr_uint32_constexpr_uint32_0(state_, static_cast<InstanceType>(178));
    tmp7 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp5}, TNode<Uint32T>{tmp6});
    ca_.Branch(tmp7, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block1);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block8);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block5);
  }

  TNode<Int32T> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<Uint16T> tmp10;
  TNode<Uint16T> tmp11;
  TNode<Int32T> tmp12;
  TNode<Uint16T> tmp13;
  TNode<Uint16T> tmp14;
  TNode<Int32T> tmp15;
  TNode<Int32T> tmp16;
  TNode<Uint32T> tmp17;
  TNode<Uint32T> tmp18;
  TNode<BoolT> tmp19;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp8 = FromConstexpr_int32_constexpr_int32_0(state_, (CodeStubAssembler(state_).ConstexprUint32Sub(static_cast<InstanceType>(178), static_cast<InstanceType>(178))));
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp10 = CodeStubAssembler(state_).LoadReference<Uint16T>(CodeStubAssembler::Reference{tmp1, tmp9});
    tmp11 = Convert_uint16_InstanceType_0(state_, TNode<Uint16T>{tmp10});
    tmp12 = Convert_int32_uint16_0(state_, TNode<Uint16T>{tmp11});
    tmp13 = FromConstexpr_InstanceType_constexpr_InstanceType_0(state_, static_cast<InstanceType>(178));
    tmp14 = Convert_uint16_InstanceType_0(state_, TNode<Uint16T>{tmp13});
    tmp15 = Convert_int32_uint16_0(state_, TNode<Uint16T>{tmp14});
    tmp16 = CodeStubAssembler(state_).Int32Sub(TNode<Int32T>{tmp12}, TNode<Int32T>{tmp15});
    tmp17 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp16});
    tmp18 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp8});
    tmp19 = CodeStubAssembler(state_).Uint32GreaterThan(TNode<Uint32T>{tmp17}, TNode<Uint32T>{tmp18});
    ca_.Branch(tmp19, &block13, std::vector<Node*>{}, &block14, std::vector<Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block1);
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block5);
  }

  TNode<SortState> tmp20;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp20 = TORQUE_CAST(TNode<HeapObject>{p_o});
    ca_.Goto(&block15);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_CastError);
  }

    ca_.Bind(&block15);
  return TNode<SortState>{tmp20};
}

TF_BUILTIN(CanUseSameAccessor_FastDoubleElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Map> parameter2 = UncheckedCast<Map>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Number> parameter3 = UncheckedCast<Number>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{tmp1}, TNode<HeapObject>{parameter2});
    ca_.Branch(tmp2, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<Oddball> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp3);
  }

  TNode<JSArray> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Number> tmp7;
  TNode<Smi> tmp8;
  TNode<BoolT> tmp9;
  TNode<Oddball> tmp10;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = UnsafeCast_JSArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp5 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp7 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp4, tmp6});
    tmp8 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7});
    tmp9 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp8}, TNode<Smi>{tmp5});
    tmp10 = CodeStubAssembler(state_).SelectBooleanConstant(TNode<BoolT>{tmp9});
    CodeStubAssembler(state_).Return(tmp10);
  }
}

TF_BUILTIN(CanUseSameAccessor_FastSmiElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Map> parameter2 = UncheckedCast<Map>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Number> parameter3 = UncheckedCast<Number>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{tmp1}, TNode<HeapObject>{parameter2});
    ca_.Branch(tmp2, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<Oddball> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp3);
  }

  TNode<JSArray> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Number> tmp7;
  TNode<Smi> tmp8;
  TNode<BoolT> tmp9;
  TNode<Oddball> tmp10;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = UnsafeCast_JSArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp5 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp7 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp4, tmp6});
    tmp8 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7});
    tmp9 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp8}, TNode<Smi>{tmp5});
    tmp10 = CodeStubAssembler(state_).SelectBooleanConstant(TNode<BoolT>{tmp9});
    CodeStubAssembler(state_).Return(tmp10);
  }
}

TF_BUILTIN(CanUseSameAccessor_FastObjectElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Map> parameter2 = UncheckedCast<Map>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Number> parameter3 = UncheckedCast<Number>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = CodeStubAssembler(state_).TaggedNotEqual(TNode<HeapObject>{tmp1}, TNode<HeapObject>{parameter2});
    ca_.Branch(tmp2, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<Oddball> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp3);
  }

  TNode<JSArray> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Number> tmp7;
  TNode<Smi> tmp8;
  TNode<BoolT> tmp9;
  TNode<Oddball> tmp10;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = UnsafeCast_JSArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp5 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp7 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp4, tmp6});
    tmp8 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7});
    tmp9 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp8}, TNode<Smi>{tmp5});
    tmp10 = CodeStubAssembler(state_).SelectBooleanConstant(TNode<BoolT>{tmp9});
    CodeStubAssembler(state_).Return(tmp10);
  }
}

TF_BUILTIN(Load_GenericElementsAccessor_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<Oddball> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = CodeStubAssembler(state_).HasProperty_Inline(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp1}, TNode<Object>{parameter2});
    tmp3 = CodeStubAssembler(state_).IsFalse(TNode<Oddball>{tmp2});
    ca_.Branch(tmp3, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<Oddball> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp4 = TheHole_0(state_);
    CodeStubAssembler(state_).Return(tmp4);
  }

  TNode<Object> tmp5;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<Object>{tmp1}, TNode<Object>{parameter2});
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TF_BUILTIN(Store_GenericElementsAccessor_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<Object> parameter3 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<Object> tmp2;
  TNode<Smi> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = CodeStubAssembler(state_).CallBuiltin(Builtins::kSetProperty, parameter0, tmp1, parameter2, parameter3);
    tmp3 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(Delete_GenericElementsAccessor_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedCast<SortState>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedCast<Smi>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<Smi> tmp2;
  TNode<Oddball> tmp3;
  TNode<Smi> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = FromConstexpr_LanguageModeSmi_constexpr_LanguageMode_0(state_, LanguageMode::kStrict);
    tmp3 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kDeleteProperty, parameter0, tmp1, parameter2, tmp2));
    tmp4 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TNode<JSObject> UnsafeCast_JSObject_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSObject> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<JSObject>{tmp0};
}

TNode<HeapNumber> UnsafeCast_HeapNumber_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapNumber> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<HeapNumber>{tmp0};
}

TNode<HeapObject> Cast_Undefined_OR_CallableApiObject_OR_CallableJSProxy_OR_JSBoundFunction_OR_JSFunction_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapObject> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = CodeStubAssembler(state_).TaggedToHeapObject(TNode<Object>{p_o}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block1);
  }

  TNode<HeapObject> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Undefined_OR_CallableApiObject_OR_CallableJSProxy_OR_JSBoundFunction_OR_JSFunction_0(state_, TNode<HeapObject>{tmp0}, &label3);
    ca_.Goto(&block5);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block7);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_CastError);
  }

    ca_.Bind(&block7);
  return TNode<HeapObject>{tmp2};
}

}  // namespace internal
}  // namespace v8

