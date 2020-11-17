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

void ReduceToSmiOrFloat64_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_x, compiler::CodeAssemblerLabel* label_SmiResult, compiler::TypedCodeAssemblerVariable<Smi>* label_SmiResult_parameter_0, compiler::CodeAssemblerLabel* label_Float64Result, compiler::TypedCodeAssemblerVariable<Float64T>* label_Float64Result_parameter_0) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object, Object> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object, Object> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block5, p_x);
  }

  TNode<Object> phi_bb5_2;
  TNode<BoolT> tmp0;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_2);
    tmp0 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp0, &block3, std::vector<Node*>{phi_bb5_2}, &block4, std::vector<Node*>{phi_bb5_2});
  }

  TNode<Object> phi_bb3_2;
  TNode<Smi> tmp1;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_2);
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp1 = Cast_Smi_0(state_, TNode<Object>{phi_bb3_2}, &label2);
    ca_.Goto(&block8, phi_bb3_2, phi_bb3_2, phi_bb3_2);
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block9, phi_bb3_2, phi_bb3_2, phi_bb3_2);
    }
  }

  TNode<Object> phi_bb9_2;
  TNode<Object> phi_bb9_3;
  TNode<Object> phi_bb9_4;
  TNode<HeapNumber> tmp3;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_2, &phi_bb9_3, &phi_bb9_4);
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = Cast_HeapNumber_0(state_, TNode<HeapObject>{ca_.UncheckedCast<HeapObject>(phi_bb9_3)}, &label4);
    ca_.Goto(&block12, phi_bb9_2, phi_bb9_3);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block13, phi_bb9_2, phi_bb9_3);
    }
  }

  TNode<Object> phi_bb8_2;
  TNode<Object> phi_bb8_3;
  TNode<Object> phi_bb8_4;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_2, &phi_bb8_3, &phi_bb8_4);
    *label_SmiResult_parameter_0 = tmp1;
    ca_.Goto(label_SmiResult);
  }

  TNode<Object> phi_bb13_2;
  TNode<Object> phi_bb13_3;
  TNode<Number> tmp5;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_2, &phi_bb13_3);
    tmp5 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kNonNumberToNumber, p_context, ca_.UncheckedCast<HeapObject>(phi_bb13_3)));
    ca_.Goto(&block5, tmp5);
  }

  TNode<Object> phi_bb12_2;
  TNode<Object> phi_bb12_3;
  TNode<Float64T> tmp6;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_2, &phi_bb12_3);
    tmp6 = Convert_float64_HeapNumber_0(state_, TNode<HeapNumber>{tmp3});
    *label_Float64Result_parameter_0 = tmp6;
    ca_.Goto(label_Float64Result);
  }

  TNode<Object> phi_bb4_2;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_2);
    VerifiedUnreachable_0(state_);
  }
}

TF_BUILTIN(MathAbs, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    compiler::TypedCodeAssemblerVariable<Smi> tmp1(&ca_);
    compiler::TypedCodeAssemblerVariable<Float64T> tmp3(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    compiler::CodeAssemblerLabel label2(&ca_);
    ReduceToSmiOrFloat64_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label0, &tmp1, &label2, &tmp3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block5);
    }
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block6);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    if (((CodeStubAssembler(state_).IsIntPtrAbsWithOverflowSupported()))) {
      ca_.Goto(&block9);
    } else {
      ca_.Goto(&block10);
    }
  }

  TNode<Float64T> tmp4;
  TNode<Number> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp4 = CodeStubAssembler(state_).Float64Abs(TNode<Float64T>{tmp3.value()});
    tmp5 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp4});
    CodeStubAssembler(state_).Return(tmp5);
  }

  TNode<Smi> tmp6;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = CodeStubAssembler(state_).TrySmiAbs(TNode<Smi>{tmp1.value()}, &label7);
    ca_.Goto(&block12);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block13);
    }
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block8);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    CodeStubAssembler(state_).Return(tmp6);
  }

  TNode<Smi> tmp8;
  TNode<BoolT> tmp9;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp8 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp9 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp8}, TNode<Smi>{tmp1.value()});
    ca_.Branch(tmp9, &block14, std::vector<Node*>{}, &block15, std::vector<Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    CodeStubAssembler(state_).Return(tmp1.value());
  }

  TNode<Smi> tmp10;
  TNode<Smi> tmp11;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp10 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    compiler::CodeAssemblerLabel label12(&ca_);
    tmp11 = CodeStubAssembler(state_).TrySmiSub(TNode<Smi>{tmp10}, TNode<Smi>{tmp1.value()}, &label12);
    ca_.Goto(&block17);
    if (label12.is_used()) {
      ca_.Bind(&label12);
      ca_.Goto(&block18);
    }
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    ca_.Goto(&block8);
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    CodeStubAssembler(state_).Return(tmp11);
  }

  TNode<Number> tmp13;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp13 = CodeStubAssembler(state_).NumberConstant(0.0 - kSmiMinValue);
    CodeStubAssembler(state_).Return(tmp13);
  }
}

TF_BUILTIN(MathCeil, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    compiler::TypedCodeAssemblerVariable<Smi> tmp1(&ca_);
    compiler::TypedCodeAssemblerVariable<Float64T> tmp3(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    compiler::CodeAssemblerLabel label2(&ca_);
    ReduceToSmiOrFloat64_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label0, &tmp1, &label2, &tmp3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block5);
    }
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block6);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).Return(tmp1.value());
  }

  TNode<Float64T> tmp4;
  TNode<Number> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp4 = CodeStubAssembler(state_).Float64Ceil(TNode<Float64T>{tmp3.value()});
    tmp5 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp4});
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TF_BUILTIN(MathFloor, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    compiler::TypedCodeAssemblerVariable<Smi> tmp1(&ca_);
    compiler::TypedCodeAssemblerVariable<Float64T> tmp3(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    compiler::CodeAssemblerLabel label2(&ca_);
    ReduceToSmiOrFloat64_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label0, &tmp1, &label2, &tmp3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block5);
    }
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block6);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).Return(tmp1.value());
  }

  TNode<Float64T> tmp4;
  TNode<Number> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp4 = CodeStubAssembler(state_).Float64Floor(TNode<Float64T>{tmp3.value()});
    tmp5 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp4});
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TF_BUILTIN(MathRound, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    compiler::TypedCodeAssemblerVariable<Smi> tmp1(&ca_);
    compiler::TypedCodeAssemblerVariable<Float64T> tmp3(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    compiler::CodeAssemblerLabel label2(&ca_);
    ReduceToSmiOrFloat64_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label0, &tmp1, &label2, &tmp3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block5);
    }
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block6);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).Return(tmp1.value());
  }

  TNode<Float64T> tmp4;
  TNode<Number> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp4 = CodeStubAssembler(state_).Float64Round(TNode<Float64T>{tmp3.value()});
    tmp5 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp4});
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TF_BUILTIN(MathTrunc, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    compiler::TypedCodeAssemblerVariable<Smi> tmp1(&ca_);
    compiler::TypedCodeAssemblerVariable<Float64T> tmp3(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    compiler::CodeAssemblerLabel label2(&ca_);
    ReduceToSmiOrFloat64_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label0, &tmp1, &label2, &tmp3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block5);
    }
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block6);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).Return(tmp1.value());
  }

  TNode<Float64T> tmp4;
  TNode<Number> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp4 = CodeStubAssembler(state_).Float64Trunc(TNode<Float64T>{tmp3.value()});
    tmp5 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp4});
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TNode<Number> MathPowImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_base, TNode<Object> p_exponent) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Float64T> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).TruncateTaggedToFloat64(TNode<Context>{p_context}, TNode<Object>{p_base});
    tmp1 = CodeStubAssembler(state_).TruncateTaggedToFloat64(TNode<Context>{p_context}, TNode<Object>{p_exponent});
    tmp2 = CodeStubAssembler(state_).Float64Pow(TNode<Float64T>{tmp0}, TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Number>{tmp3};
}

TF_BUILTIN(MathPow, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kBase));
  USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kExponent));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = MathPowImpl_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, TNode<Object>{parameter2});
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(MathMax, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  Node* argc = Parameter(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Float64T, IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Float64T, IntPtrT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Float64T, IntPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Float64T> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_float64_constexpr_float64_0(state_, -V8_INFINITY);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block3, tmp0, tmp1);
  }

  TNode<Float64T> phi_bb3_4;
  TNode<IntPtrT> phi_bb3_6;
  TNode<BoolT> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_4, &phi_bb3_6);
    tmp2 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb3_6}, TNode<IntPtrT>{torque_arguments.length});
    ca_.Branch(tmp2, &block1, std::vector<Node*>{phi_bb3_4, phi_bb3_6}, &block2, std::vector<Node*>{phi_bb3_4, phi_bb3_6});
  }

  TNode<Float64T> phi_bb1_4;
  TNode<IntPtrT> phi_bb1_6;
  TNode<Object> tmp3;
  TNode<Float64T> tmp4;
  TNode<Float64T> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4, &phi_bb1_6);
    tmp3 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{phi_bb1_6});
    tmp4 = CodeStubAssembler(state_).TruncateTaggedToFloat64(TNode<Context>{parameter0}, TNode<Object>{tmp3});
    tmp5 = CodeStubAssembler(state_).Float64Max(TNode<Float64T>{phi_bb1_4}, TNode<Float64T>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp7 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb1_6}, TNode<IntPtrT>{tmp6});
    ca_.Goto(&block3, tmp5, tmp7);
  }

  TNode<Float64T> phi_bb2_4;
  TNode<IntPtrT> phi_bb2_6;
  TNode<Number> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4, &phi_bb2_6);
    tmp8 = Convert_Number_float64_0(state_, TNode<Float64T>{phi_bb2_4});
    arguments.PopAndReturn(tmp8);
  }
}

TF_BUILTIN(MathMin, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  Node* argc = Parameter(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Float64T, IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Float64T, IntPtrT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Float64T, IntPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Float64T> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_float64_constexpr_float64_0(state_, V8_INFINITY);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block3, tmp0, tmp1);
  }

  TNode<Float64T> phi_bb3_4;
  TNode<IntPtrT> phi_bb3_6;
  TNode<BoolT> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_4, &phi_bb3_6);
    tmp2 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb3_6}, TNode<IntPtrT>{torque_arguments.length});
    ca_.Branch(tmp2, &block1, std::vector<Node*>{phi_bb3_4, phi_bb3_6}, &block2, std::vector<Node*>{phi_bb3_4, phi_bb3_6});
  }

  TNode<Float64T> phi_bb1_4;
  TNode<IntPtrT> phi_bb1_6;
  TNode<Object> tmp3;
  TNode<Float64T> tmp4;
  TNode<Float64T> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4, &phi_bb1_6);
    tmp3 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{phi_bb1_6});
    tmp4 = CodeStubAssembler(state_).TruncateTaggedToFloat64(TNode<Context>{parameter0}, TNode<Object>{tmp3});
    tmp5 = CodeStubAssembler(state_).Float64Min(TNode<Float64T>{phi_bb1_4}, TNode<Float64T>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp7 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb1_6}, TNode<IntPtrT>{tmp6});
    ca_.Goto(&block3, tmp5, tmp7);
  }

  TNode<Float64T> phi_bb2_4;
  TNode<IntPtrT> phi_bb2_6;
  TNode<Number> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4, &phi_bb2_6);
    tmp8 = Convert_Number_float64_0(state_, TNode<Float64T>{phi_bb2_4});
    arguments.PopAndReturn(tmp8);
  }
}

TF_BUILTIN(MathAcos, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Acos(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathAcosh, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Acosh(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathAsin, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Asin(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathAsinh, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Asinh(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathAtan, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Atan(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathAtan2, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kY));
  USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Number> tmp2;
  TNode<Float64T> tmp3;
  TNode<Float64T> tmp4;
  TNode<Number> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter2});
    tmp3 = Convert_float64_Number_0(state_, TNode<Number>{tmp2});
    tmp4 = CodeStubAssembler(state_).Float64Atan2(TNode<Float64T>{tmp1}, TNode<Float64T>{tmp3});
    tmp5 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp4});
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TF_BUILTIN(MathAtanh, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Atanh(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathCbrt, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Cbrt(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathClz32, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Int32T> tmp1;
  TNode<Int32T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_int32_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32Clz(TNode<Int32T>{tmp1});
    tmp3 = Convert_Number_int32_0(state_, TNode<Int32T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathCos, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Cos(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathCosh, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Cosh(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathExp, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Exp(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathExpm1, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Expm1(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathFround, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float32T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float32_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = Convert_float64_float32_0(state_, TNode<Float32T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathImul, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kY));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Int32T> tmp1;
  TNode<Number> tmp2;
  TNode<Int32T> tmp3;
  TNode<Int32T> tmp4;
  TNode<Number> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_int32_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter2});
    tmp3 = Convert_int32_Number_0(state_, TNode<Number>{tmp2});
    tmp4 = CodeStubAssembler(state_).Int32Mul(TNode<Int32T>{tmp1}, TNode<Int32T>{tmp3});
    tmp5 = Convert_Number_int32_0(state_, TNode<Int32T>{tmp4});
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TF_BUILTIN(MathLog, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Log(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathLog1p, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Log1p(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathLog10, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Log10(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathLog2, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Log2(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathSin, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Sin(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathSign, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = FromConstexpr_float64_constexpr_int31_0(state_, 0);
    tmp3 = CodeStubAssembler(state_).Float64LessThan(TNode<Float64T>{tmp1}, TNode<Float64T>{tmp2});
    ca_.Branch(tmp3, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<Number> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp4 = FromConstexpr_Number_constexpr_int31_0(state_, -1);
    CodeStubAssembler(state_).Return(tmp4);
  }

  TNode<Float64T> tmp5;
  TNode<BoolT> tmp6;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = FromConstexpr_float64_constexpr_int31_0(state_, 0);
    tmp6 = CodeStubAssembler(state_).Float64GreaterThan(TNode<Float64T>{tmp1}, TNode<Float64T>{tmp5});
    ca_.Branch(tmp6, &block4, std::vector<Node*>{}, &block5, std::vector<Node*>{});
  }

  TNode<Number> tmp7;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp7 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    CodeStubAssembler(state_).Return(tmp7);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(MathSinh, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Sinh(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathSqrt, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Sqrt(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathTan, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Tan(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathTanh, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kX));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<Float64T> tmp1;
  TNode<Float64T> tmp2;
  TNode<Number> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = Convert_float64_Number_0(state_, TNode<Number>{tmp0});
    tmp2 = CodeStubAssembler(state_).Float64Tanh(TNode<Float64T>{tmp1});
    tmp3 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp2});
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(MathHypot, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, IntPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, IntPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, IntPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, IntPtrT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, IntPtrT> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, IntPtrT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, IntPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, Float64T, Float64T, IntPtrT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, Float64T, Float64T, IntPtrT> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, Float64T, Float64T, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, Float64T, Float64T, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Float64T, Float64T, Float64T, IntPtrT> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp1, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<Number> tmp2;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp2 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    arguments.PopAndReturn(tmp2);
  }

  TNode<FixedDoubleArray> tmp3;
  TNode<BoolT> tmp4;
  TNode<Float64T> tmp5;
  TNode<IntPtrT> tmp6;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp3 = CodeStubAssembler(state_).AllocateZeroedFixedDoubleArray(TNode<IntPtrT>{torque_arguments.length});
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp5 = FromConstexpr_float64_constexpr_int31_0(state_, 0);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block5, tmp4, tmp5, tmp6);
  }

  TNode<BoolT> phi_bb5_7;
  TNode<Float64T> phi_bb5_8;
  TNode<IntPtrT> phi_bb5_9;
  TNode<BoolT> tmp7;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_7, &phi_bb5_8, &phi_bb5_9);
    tmp7 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb5_9}, TNode<IntPtrT>{torque_arguments.length});
    ca_.Branch(tmp7, &block3, std::vector<Node*>{phi_bb5_7, phi_bb5_8, phi_bb5_9}, &block4, std::vector<Node*>{phi_bb5_7, phi_bb5_8, phi_bb5_9});
  }

  TNode<BoolT> phi_bb3_7;
  TNode<Float64T> phi_bb3_8;
  TNode<IntPtrT> phi_bb3_9;
  TNode<Object> tmp8;
  TNode<Number> tmp9;
  TNode<Float64T> tmp10;
  TNode<BoolT> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_7, &phi_bb3_8, &phi_bb3_9);
    tmp8 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{phi_bb3_9});
    tmp9 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<Object>{tmp8});
    tmp10 = Convert_float64_Number_0(state_, TNode<Number>{tmp9});
    tmp11 = Float64IsNaN_0(state_, TNode<Float64T>{tmp10});
    ca_.Branch(tmp11, &block7, std::vector<Node*>{phi_bb3_7, phi_bb3_8, phi_bb3_9}, &block8, std::vector<Node*>{phi_bb3_7, phi_bb3_8, phi_bb3_9});
  }

  TNode<BoolT> phi_bb7_7;
  TNode<Float64T> phi_bb7_8;
  TNode<IntPtrT> phi_bb7_9;
  TNode<BoolT> tmp12;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_7, &phi_bb7_8, &phi_bb7_9);
    tmp12 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block9, tmp12, phi_bb7_8, phi_bb7_9);
  }

  TNode<BoolT> phi_bb8_7;
  TNode<Float64T> phi_bb8_8;
  TNode<IntPtrT> phi_bb8_9;
  TNode<Float64T> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<Smi> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<UintPtrT> tmp19;
  TNode<UintPtrT> tmp20;
  TNode<BoolT> tmp21;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_7, &phi_bb8_8, &phi_bb8_9);
    tmp13 = CodeStubAssembler(state_).Float64Abs(TNode<Float64T>{tmp10});
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp17 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp3, tmp16});
    tmp18 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp17});
    tmp19 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb8_9});
    tmp20 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp18});
    tmp21 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp19}, TNode<UintPtrT>{tmp20});
    ca_.Branch(tmp21, &block14, std::vector<Node*>{phi_bb8_7, phi_bb8_8, phi_bb8_9, phi_bb8_9, phi_bb8_9, phi_bb8_9, phi_bb8_9}, &block15, std::vector<Node*>{phi_bb8_7, phi_bb8_8, phi_bb8_9, phi_bb8_9, phi_bb8_9, phi_bb8_9, phi_bb8_9});
  }

  TNode<BoolT> phi_bb14_7;
  TNode<Float64T> phi_bb14_8;
  TNode<IntPtrT> phi_bb14_9;
  TNode<IntPtrT> phi_bb14_16;
  TNode<IntPtrT> phi_bb14_17;
  TNode<IntPtrT> phi_bb14_21;
  TNode<IntPtrT> phi_bb14_22;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<HeapObject> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<BoolT> tmp27;
  TNode<Float64T> tmp28;
  TNode<BoolT> tmp29;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_7, &phi_bb14_8, &phi_bb14_9, &phi_bb14_16, &phi_bb14_17, &phi_bb14_21, &phi_bb14_22);
    tmp22 = FromConstexpr_intptr_constexpr_int31_0(state_, kDoubleSize);
    tmp23 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{phi_bb14_22}, TNode<IntPtrT>{tmp22});
    tmp24 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp14}, TNode<IntPtrT>{tmp23});
    std::tie(tmp25, tmp26) = NewReference_float64_or_hole_0(state_, TNode<HeapObject>{tmp3}, TNode<IntPtrT>{tmp24}).Flatten();
    std::tie(tmp27, tmp28) = Convert_float64_or_hole_float64_0(state_, TNode<Float64T>{tmp13}).Flatten();
    StoreFloat64OrHole_0(state_, TorqueStructReference_float64_or_hole_0{TNode<HeapObject>{tmp25}, TNode<IntPtrT>{tmp26}, TorqueStructUnsafe_0{}}, TorqueStructfloat64_or_hole_0{TNode<BoolT>{tmp27}, TNode<Float64T>{tmp28}});
    tmp29 = CodeStubAssembler(state_).Float64GreaterThan(TNode<Float64T>{tmp13}, TNode<Float64T>{phi_bb14_8});
    ca_.Branch(tmp29, &block17, std::vector<Node*>{phi_bb14_7, phi_bb14_8, phi_bb14_9}, &block18, std::vector<Node*>{phi_bb14_7, phi_bb14_8, phi_bb14_9});
  }

  TNode<BoolT> phi_bb15_7;
  TNode<Float64T> phi_bb15_8;
  TNode<IntPtrT> phi_bb15_9;
  TNode<IntPtrT> phi_bb15_16;
  TNode<IntPtrT> phi_bb15_17;
  TNode<IntPtrT> phi_bb15_21;
  TNode<IntPtrT> phi_bb15_22;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_7, &phi_bb15_8, &phi_bb15_9, &phi_bb15_16, &phi_bb15_17, &phi_bb15_21, &phi_bb15_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb17_7;
  TNode<Float64T> phi_bb17_8;
  TNode<IntPtrT> phi_bb17_9;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_7, &phi_bb17_8, &phi_bb17_9);
    ca_.Goto(&block18, phi_bb17_7, tmp13, phi_bb17_9);
  }

  TNode<BoolT> phi_bb18_7;
  TNode<Float64T> phi_bb18_8;
  TNode<IntPtrT> phi_bb18_9;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_7, &phi_bb18_8, &phi_bb18_9);
    ca_.Goto(&block9, phi_bb18_7, phi_bb18_8, phi_bb18_9);
  }

  TNode<BoolT> phi_bb9_7;
  TNode<Float64T> phi_bb9_8;
  TNode<IntPtrT> phi_bb9_9;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_7, &phi_bb9_8, &phi_bb9_9);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp31 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb9_9}, TNode<IntPtrT>{tmp30});
    ca_.Goto(&block5, phi_bb9_7, phi_bb9_8, tmp31);
  }

  TNode<BoolT> phi_bb4_7;
  TNode<Float64T> phi_bb4_8;
  TNode<IntPtrT> phi_bb4_9;
  TNode<Float64T> tmp32;
  TNode<BoolT> tmp33;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_7, &phi_bb4_8, &phi_bb4_9);
    tmp32 = FromConstexpr_float64_constexpr_float64_0(state_, V8_INFINITY);
    tmp33 = CodeStubAssembler(state_).Float64Equal(TNode<Float64T>{phi_bb4_8}, TNode<Float64T>{tmp32});
    ca_.Branch(tmp33, &block19, std::vector<Node*>{phi_bb4_7, phi_bb4_8}, &block20, std::vector<Node*>{phi_bb4_7, phi_bb4_8});
  }

  TNode<BoolT> phi_bb19_7;
  TNode<Float64T> phi_bb19_8;
  TNode<Number> tmp34;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_7, &phi_bb19_8);
    tmp34 = FromConstexpr_Number_constexpr_float64_0(state_, V8_INFINITY);
    arguments.PopAndReturn(tmp34);
  }

  TNode<BoolT> phi_bb20_7;
  TNode<Float64T> phi_bb20_8;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_7, &phi_bb20_8);
    ca_.Branch(phi_bb20_7, &block22, std::vector<Node*>{phi_bb20_7, phi_bb20_8}, &block23, std::vector<Node*>{phi_bb20_7, phi_bb20_8});
  }

  TNode<BoolT> phi_bb22_7;
  TNode<Float64T> phi_bb22_8;
  TNode<HeapNumber> tmp35;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_7, &phi_bb22_8);
    tmp35 = kNaN_0(state_);
    arguments.PopAndReturn(tmp35);
  }

  TNode<BoolT> phi_bb23_7;
  TNode<Float64T> phi_bb23_8;
  TNode<Float64T> tmp36;
  TNode<BoolT> tmp37;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_7, &phi_bb23_8);
    tmp36 = FromConstexpr_float64_constexpr_int31_0(state_, 0);
    tmp37 = CodeStubAssembler(state_).Float64Equal(TNode<Float64T>{phi_bb23_8}, TNode<Float64T>{tmp36});
    ca_.Branch(tmp37, &block25, std::vector<Node*>{phi_bb23_7, phi_bb23_8}, &block26, std::vector<Node*>{phi_bb23_7, phi_bb23_8});
  }

  TNode<BoolT> phi_bb25_7;
  TNode<Float64T> phi_bb25_8;
  TNode<Number> tmp38;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_7, &phi_bb25_8);
    tmp38 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    arguments.PopAndReturn(tmp38);
  }

  TNode<BoolT> phi_bb26_7;
  TNode<Float64T> phi_bb26_8;
  TNode<Float64T> tmp39;
  TNode<Float64T> tmp40;
  TNode<IntPtrT> tmp41;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_7, &phi_bb26_8);
    tmp39 = FromConstexpr_float64_constexpr_int31_0(state_, 0);
    tmp40 = FromConstexpr_float64_constexpr_int31_0(state_, 0);
    tmp41 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block33, phi_bb26_7, phi_bb26_8, tmp39, tmp40, tmp41);
  }

  TNode<BoolT> phi_bb33_7;
  TNode<Float64T> phi_bb33_8;
  TNode<Float64T> phi_bb33_9;
  TNode<Float64T> phi_bb33_10;
  TNode<IntPtrT> phi_bb33_11;
  TNode<BoolT> tmp42;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_7, &phi_bb33_8, &phi_bb33_9, &phi_bb33_10, &phi_bb33_11);
    tmp42 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb33_11}, TNode<IntPtrT>{torque_arguments.length});
    ca_.Branch(tmp42, &block31, std::vector<Node*>{phi_bb33_7, phi_bb33_8, phi_bb33_9, phi_bb33_10, phi_bb33_11}, &block32, std::vector<Node*>{phi_bb33_7, phi_bb33_8, phi_bb33_9, phi_bb33_10, phi_bb33_11});
  }

  TNode<BoolT> phi_bb31_7;
  TNode<Float64T> phi_bb31_8;
  TNode<Float64T> phi_bb31_9;
  TNode<Float64T> phi_bb31_10;
  TNode<IntPtrT> phi_bb31_11;
  TNode<IntPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<Smi> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<UintPtrT> tmp48;
  TNode<UintPtrT> tmp49;
  TNode<BoolT> tmp50;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_7, &phi_bb31_8, &phi_bb31_9, &phi_bb31_10, &phi_bb31_11);
    tmp43 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp44 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp46 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp3, tmp45});
    tmp47 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp46});
    tmp48 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb31_11});
    tmp49 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp47});
    tmp50 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp48}, TNode<UintPtrT>{tmp49});
    ca_.Branch(tmp50, &block39, std::vector<Node*>{phi_bb31_7, phi_bb31_8, phi_bb31_9, phi_bb31_10, phi_bb31_11, phi_bb31_11, phi_bb31_11, phi_bb31_11, phi_bb31_11}, &block40, std::vector<Node*>{phi_bb31_7, phi_bb31_8, phi_bb31_9, phi_bb31_10, phi_bb31_11, phi_bb31_11, phi_bb31_11, phi_bb31_11, phi_bb31_11});
  }

  TNode<BoolT> phi_bb39_7;
  TNode<Float64T> phi_bb39_8;
  TNode<Float64T> phi_bb39_9;
  TNode<Float64T> phi_bb39_10;
  TNode<IntPtrT> phi_bb39_11;
  TNode<IntPtrT> phi_bb39_16;
  TNode<IntPtrT> phi_bb39_17;
  TNode<IntPtrT> phi_bb39_21;
  TNode<IntPtrT> phi_bb39_22;
  TNode<IntPtrT> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<HeapObject> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<BoolT> tmp56;
  TNode<Float64T> tmp57;
  TNode<Float64T> tmp58;
  TNode<Float64T> tmp59;
  TNode<Float64T> tmp60;
  TNode<Float64T> tmp61;
  TNode<Float64T> tmp62;
  TNode<Float64T> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<IntPtrT> tmp65;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_7, &phi_bb39_8, &phi_bb39_9, &phi_bb39_10, &phi_bb39_11, &phi_bb39_16, &phi_bb39_17, &phi_bb39_21, &phi_bb39_22);
    tmp51 = FromConstexpr_intptr_constexpr_int31_0(state_, kDoubleSize);
    tmp52 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{phi_bb39_22}, TNode<IntPtrT>{tmp51});
    tmp53 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp43}, TNode<IntPtrT>{tmp52});
    std::tie(tmp54, tmp55) = NewReference_float64_or_hole_0(state_, TNode<HeapObject>{tmp3}, TNode<IntPtrT>{tmp53}).Flatten();
    std::tie(tmp56, tmp57) = LoadFloat64OrHole_0(state_, TorqueStructReference_float64_or_hole_0{TNode<HeapObject>{tmp54}, TNode<IntPtrT>{tmp55}, TorqueStructUnsafe_0{}}).Flatten();
    tmp58 = CodeStubAssembler(state_).Float64Div(TNode<Float64T>{tmp57}, TNode<Float64T>{phi_bb39_8});
    tmp59 = CodeStubAssembler(state_).Float64Mul(TNode<Float64T>{tmp58}, TNode<Float64T>{tmp58});
    tmp60 = CodeStubAssembler(state_).Float64Sub(TNode<Float64T>{tmp59}, TNode<Float64T>{phi_bb39_10});
    tmp61 = CodeStubAssembler(state_).Float64Add(TNode<Float64T>{phi_bb39_9}, TNode<Float64T>{tmp60});
    tmp62 = CodeStubAssembler(state_).Float64Sub(TNode<Float64T>{tmp61}, TNode<Float64T>{phi_bb39_9});
    tmp63 = CodeStubAssembler(state_).Float64Sub(TNode<Float64T>{tmp62}, TNode<Float64T>{tmp60});
    tmp64 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp65 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb39_11}, TNode<IntPtrT>{tmp64});
    ca_.Goto(&block33, phi_bb39_7, phi_bb39_8, tmp61, tmp63, tmp65);
  }

  TNode<BoolT> phi_bb40_7;
  TNode<Float64T> phi_bb40_8;
  TNode<Float64T> phi_bb40_9;
  TNode<Float64T> phi_bb40_10;
  TNode<IntPtrT> phi_bb40_11;
  TNode<IntPtrT> phi_bb40_16;
  TNode<IntPtrT> phi_bb40_17;
  TNode<IntPtrT> phi_bb40_21;
  TNode<IntPtrT> phi_bb40_22;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_7, &phi_bb40_8, &phi_bb40_9, &phi_bb40_10, &phi_bb40_11, &phi_bb40_16, &phi_bb40_17, &phi_bb40_21, &phi_bb40_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb32_7;
  TNode<Float64T> phi_bb32_8;
  TNode<Float64T> phi_bb32_9;
  TNode<Float64T> phi_bb32_10;
  TNode<IntPtrT> phi_bb32_11;
  TNode<Float64T> tmp66;
  TNode<Float64T> tmp67;
  TNode<Number> tmp68;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_7, &phi_bb32_8, &phi_bb32_9, &phi_bb32_10, &phi_bb32_11);
    tmp66 = CodeStubAssembler(state_).Float64Sqrt(TNode<Float64T>{phi_bb32_9});
    tmp67 = CodeStubAssembler(state_).Float64Mul(TNode<Float64T>{tmp66}, TNode<Float64T>{phi_bb32_8});
    tmp68 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp67});
    arguments.PopAndReturn(tmp68);
  }
}

TF_BUILTIN(MathRandom, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<HeapObject> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = MATH_RANDOM_INDEX_INDEX_0(state_);
    std::tie(tmp1, tmp2) = NativeContextSlot_NativeContext_Smi_0(state_, TNode<NativeContext>{parameter0}, TNode<IntPtrT>{tmp0}).Flatten();
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp5 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp3}, TNode<Smi>{tmp4});
    ca_.Branch(tmp5, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{tmp3});
  }

  TNode<Smi> tmp6;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp6 = CodeStubAssembler(state_).RefillMathRandom(TNode<NativeContext>{parameter0});
    ca_.Goto(&block2, tmp6);
  }

  TNode<Smi> phi_bb2_2;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<HeapObject> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<HeapObject> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<FixedDoubleArray> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<Smi> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<UintPtrT> tmp22;
  TNode<UintPtrT> tmp23;
  TNode<BoolT> tmp24;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_2);
    tmp7 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp8 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb2_2}, TNode<Smi>{tmp7});
    tmp9 = MATH_RANDOM_INDEX_INDEX_0(state_);
    std::tie(tmp10, tmp11) = NativeContextSlot_NativeContext_Smi_0(state_, TNode<NativeContext>{parameter0}, TNode<IntPtrT>{tmp9}).Flatten();
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp10, tmp11}, tmp8);
    tmp12 = MATH_RANDOM_CACHE_INDEX_0(state_);
    std::tie(tmp13, tmp14) = NativeContextSlot_NativeContext_FixedDoubleArray_0(state_, TNode<NativeContext>{parameter0}, TNode<IntPtrT>{tmp12}).Flatten();
    tmp15 = CodeStubAssembler(state_).LoadReference<FixedDoubleArray>(CodeStubAssembler::Reference{tmp13, tmp14});
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp18 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp19 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp15, tmp18});
    tmp20 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp19});
    tmp21 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp8});
    tmp22 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp21});
    tmp23 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp20});
    tmp24 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp22}, TNode<UintPtrT>{tmp23});
    ca_.Branch(tmp24, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<HeapObject> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<BoolT> tmp30;
  TNode<Float64T> tmp31;
  TNode<HeapNumber> tmp32;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, kDoubleSize);
    tmp26 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp21}, TNode<IntPtrT>{tmp25});
    tmp27 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp26});
    std::tie(tmp28, tmp29) = NewReference_float64_or_hole_0(state_, TNode<HeapObject>{tmp15}, TNode<IntPtrT>{tmp27}).Flatten();
    std::tie(tmp30, tmp31) = LoadFloat64OrHole_0(state_, TorqueStructReference_float64_or_hole_0{TNode<HeapObject>{tmp28}, TNode<IntPtrT>{tmp29}, TorqueStructUnsafe_0{}}).Flatten();
    tmp32 = CodeStubAssembler(state_).AllocateHeapNumberWithValue(TNode<Float64T>{tmp31});
    CodeStubAssembler(state_).Return(tmp32);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).Unreachable();
  }
}

TorqueStructReference_Smi_0 NativeContextSlot_NativeContext_Smi_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<IntPtrT> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapObject> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = NativeContextSlot_Smi_0(state_, TNode<NativeContext>{p_context}, TNode<IntPtrT>{p_index}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_Smi_0{TNode<HeapObject>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

TorqueStructReference_FixedDoubleArray_0 NativeContextSlot_NativeContext_FixedDoubleArray_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<IntPtrT> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapObject> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = NativeContextSlot_FixedDoubleArray_0(state_, TNode<NativeContext>{p_context}, TNode<IntPtrT>{p_index}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_FixedDoubleArray_0{TNode<HeapObject>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

}  // namespace internal
}  // namespace v8

