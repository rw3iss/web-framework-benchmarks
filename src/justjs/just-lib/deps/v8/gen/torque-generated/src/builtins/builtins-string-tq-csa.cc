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

TNode<String> ToStringImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object, Object> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object, Object> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object, Object> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block4, p_o);
  }

  TNode<Object> phi_bb4_2;
  TNode<BoolT> tmp0;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_2);
    tmp0 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp0, &block2, std::vector<Node*>{phi_bb4_2}, &block3, std::vector<Node*>{phi_bb4_2});
  }

  TNode<Object> phi_bb2_2;
  TNode<Number> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_2);
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp1 = Cast_Number_0(state_, TNode<Object>{phi_bb2_2}, &label2);
    ca_.Goto(&block7, phi_bb2_2, phi_bb2_2, phi_bb2_2);
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block8, phi_bb2_2, phi_bb2_2, phi_bb2_2);
    }
  }

  TNode<Object> phi_bb8_2;
  TNode<Object> phi_bb8_3;
  TNode<Object> phi_bb8_4;
  TNode<String> tmp3;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_2, &phi_bb8_3, &phi_bb8_4);
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = Cast_String_0(state_, TNode<HeapObject>{ca_.UncheckedCast<HeapObject>(phi_bb8_3)}, &label4);
    ca_.Goto(&block11, phi_bb8_2, phi_bb8_3);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block12, phi_bb8_2, phi_bb8_3);
    }
  }

  TNode<Object> phi_bb7_2;
  TNode<Object> phi_bb7_3;
  TNode<Object> phi_bb7_4;
  TNode<String> tmp5;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_2, &phi_bb7_3, &phi_bb7_4);
    tmp5 = CodeStubAssembler(state_).NumberToString(TNode<Number>{tmp1});
    ca_.Goto(&block1, tmp5);
  }

  TNode<Object> phi_bb12_2;
  TNode<Object> phi_bb12_3;
  TNode<Oddball> tmp6;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_2, &phi_bb12_3);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_Oddball_0(state_, TNode<HeapObject>{ca_.UncheckedCast<HeapObject>(phi_bb12_3)}, &label7);
    ca_.Goto(&block15, phi_bb12_2, phi_bb12_3);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block16, phi_bb12_2, phi_bb12_3);
    }
  }

  TNode<Object> phi_bb11_2;
  TNode<Object> phi_bb11_3;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_2, &phi_bb11_3);
    ca_.Goto(&block1, tmp3);
  }

  TNode<Object> phi_bb16_2;
  TNode<Object> phi_bb16_3;
  TNode<JSReceiver> tmp8;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_2, &phi_bb16_3);
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_JSReceiver_0(state_, TNode<HeapObject>{ca_.UncheckedCast<HeapObject>(phi_bb16_3)}, &label9);
    ca_.Goto(&block19, phi_bb16_2, phi_bb16_3);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block20, phi_bb16_2, phi_bb16_3);
    }
  }

  TNode<Object> phi_bb15_2;
  TNode<Object> phi_bb15_3;
  TNode<IntPtrT> tmp10;
  TNode<String> tmp11;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_2, &phi_bb15_3);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp11 = CodeStubAssembler(state_).LoadReference<String>(CodeStubAssembler::Reference{tmp6, tmp10});
    ca_.Goto(&block1, tmp11);
  }

  TNode<Object> phi_bb20_2;
  TNode<Object> phi_bb20_3;
  TNode<Symbol> tmp12;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_2, &phi_bb20_3);
    compiler::CodeAssemblerLabel label13(&ca_);
    tmp12 = Cast_Symbol_0(state_, TNode<HeapObject>{ca_.UncheckedCast<PrimitiveHeapObject>(phi_bb20_3)}, &label13);
    ca_.Goto(&block23, phi_bb20_2, phi_bb20_3);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block24, phi_bb20_2, phi_bb20_3);
    }
  }

  TNode<Object> phi_bb19_2;
  TNode<Object> phi_bb19_3;
  TNode<Object> tmp14;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_2, &phi_bb19_3);
    tmp14 = CodeStubAssembler(state_).CallBuiltin(Builtins::kNonPrimitiveToPrimitive_String, p_context, phi_bb19_2);
    ca_.Goto(&block4, tmp14);
  }

  TNode<Object> phi_bb24_2;
  TNode<Object> phi_bb24_3;
  TNode<String> tmp15;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_2, &phi_bb24_3);
    tmp15 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kToStringRT, p_context, p_o)); 
    ca_.Goto(&block1, tmp15);
  }

  TNode<Object> phi_bb23_2;
  TNode<Object> phi_bb23_3;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_2, &phi_bb23_3);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, MessageTemplate::kSymbolToString);
  }

  TNode<Object> phi_bb3_2;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_2);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block25);
  }

    ca_.Bind(&block25);
  return TNode<String>{phi_bb1_2};
}

TF_BUILTIN(ToString, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<String> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ToStringImpl_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StringPrototypeToString, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToThisValue(TNode<Context>{parameter0}, TNode<Object>{parameter1}, PrimitiveType::kString, "String.prototype.toString");
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StringPrototypeValueOf, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToThisValue(TNode<Context>{parameter0}, TNode<Object>{parameter1}, PrimitiveType::kString, "String.prototype.valueOf");
    CodeStubAssembler(state_).Return(tmp0);
  }
}

TF_BUILTIN(StringToList, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<String> parameter1 = UncheckedCast<String>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, IntPtrT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, IntPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<NativeContext> tmp1;
  TNode<Map> tmp2;
  TNode<Smi> tmp3;
  TNode<JSArray> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<FixedArrayBase> tmp6;
  TNode<FixedArray> tmp7;
  TNode<Smi> tmp8;
  TNode<IntPtrT> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadStringLengthAsWord(TNode<String>{parameter1});
    tmp1 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{parameter0});
    tmp2 = CodeStubAssembler(state_).LoadJSArrayElementsMap(ElementsKind::PACKED_ELEMENTS, TNode<NativeContext>{tmp1});
    tmp3 = CodeStubAssembler(state_).SmiTag(TNode<IntPtrT>{tmp0});
    tmp4 = CodeStubAssembler(state_).AllocateJSArray(ElementsKind::PACKED_ELEMENTS, TNode<Map>{tmp2}, TNode<IntPtrT>{tmp0}, TNode<Smi>{tmp3}, CodeStubAssembler::AllocationFlag::kAllowLargeObjectAllocation);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp6 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp4, tmp5});
    tmp7 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp6});
    tmp8 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block3, tmp8, tmp9);
  }

  TNode<Smi> phi_bb3_7;
  TNode<IntPtrT> phi_bb3_8;
  TNode<BoolT> tmp10;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_7, &phi_bb3_8);
    tmp10 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb3_8}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp10, &block1, std::vector<Node*>{phi_bb3_7, phi_bb3_8}, &block2, std::vector<Node*>{phi_bb3_7, phi_bb3_8});
  }

  TNode<Smi> phi_bb1_7;
  TNode<IntPtrT> phi_bb1_8;
  TNode<Int32T> tmp11;
  TNode<String> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Smi> tmp15;
  TNode<Smi> tmp16;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_7, &phi_bb1_8);
    tmp11 = StringBuiltinsAssembler(state_).LoadSurrogatePairAt(TNode<String>{parameter1}, TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{phi_bb1_8}, UnicodeEncoding::UTF16);
    tmp12 = StringBuiltinsAssembler(state_).StringFromSingleUTF16EncodedCodePoint(TNode<Int32T>{tmp11});
    StoreFixedArrayDirect_0(state_, TNode<FixedArray>{tmp7}, TNode<Smi>{phi_bb1_7}, TNode<Object>{tmp12});
    tmp13 = CodeStubAssembler(state_).LoadStringLengthAsWord(TNode<String>{tmp12});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb1_8}, TNode<IntPtrT>{tmp13});
    tmp15 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp16 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb1_7}, TNode<Smi>{tmp15});
    ca_.Goto(&block3, tmp16, tmp14);
  }

  TNode<Smi> phi_bb2_7;
  TNode<IntPtrT> phi_bb2_8;
  TNode<IntPtrT> tmp17;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_7, &phi_bb2_8);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{tmp4, tmp17}, phi_bb2_7);
    CodeStubAssembler(state_).Return(tmp4);
  }
}

void GenerateStringAt_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_receiver, TNode<Object> p_position, const char* p_methodName, compiler::CodeAssemblerLabel* label_IfInBounds, compiler::TypedCodeAssemblerVariable<String>* label_IfInBounds_parameter_0, compiler::TypedCodeAssemblerVariable<UintPtrT>* label_IfInBounds_parameter_1, compiler::TypedCodeAssemblerVariable<UintPtrT>* label_IfInBounds_parameter_2, compiler::CodeAssemblerLabel* label_IfOutOfBounds) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<String> tmp0;
  TNode<String> tmp1;
  TNode<Number> tmp2;
  TNode<Smi> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_String_constexpr_string_0(state_, p_methodName);
    tmp1 = CodeStubAssembler(state_).ToThisString(TNode<Context>{p_context}, TNode<Object>{p_receiver}, TNode<String>{tmp0});
    tmp2 = ToInteger_Inline_0(state_, TNode<Context>{p_context}, TNode<Object>{p_position});
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = Cast_Smi_0(state_, TNode<Object>{tmp2}, &label4);
    ca_.Goto(&block5);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block2);
  }

  TNode<UintPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<BoolT> tmp8;
  TNode<BoolT> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp5 = LoadStringLengthAsUintPtr_0(state_, TNode<String>{tmp1});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp7 = CodeStubAssembler(state_).Unsigned(TNode<IntPtrT>{tmp6});
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprUintPtrLessThan(String::kMaxLength, kSmiMaxValue)));
    CodeStubAssembler(state_).StaticAssert(TNode<BoolT>{tmp8}, "static_assert(kMaxStringLengthFitsSmi) at src/builtins/builtins-string.tq:120:7");
    tmp9 = CodeStubAssembler(state_).UintPtrGreaterThanOrEqual(TNode<UintPtrT>{tmp7}, TNode<UintPtrT>{tmp5});
    ca_.Branch(tmp9, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block2);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    *label_IfInBounds_parameter_2 = tmp5;
    *label_IfInBounds_parameter_1 = tmp7;
    *label_IfInBounds_parameter_0 = tmp1;
    ca_.Goto(label_IfInBounds);
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ca_.Goto(label_IfOutOfBounds);
  }
}

TF_BUILTIN(StringPrototypeCharAt, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kPosition));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    compiler::TypedCodeAssemblerVariable<String> tmp1(&ca_);
    compiler::TypedCodeAssemblerVariable<UintPtrT> tmp2(&ca_);
    compiler::TypedCodeAssemblerVariable<UintPtrT> tmp3(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    compiler::CodeAssemblerLabel label4(&ca_);
    GenerateStringAt_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, TNode<Object>{parameter2}, "String.prototype.charAt", &label0, &tmp1, &tmp2, &tmp3, &label4);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block5);
    }
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block6);
    }
  }

  TNode<Int32T> tmp5;
  TNode<String> tmp6;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp5 = CodeStubAssembler(state_).StringCharCodeAt(TNode<String>{tmp1.value()}, TNode<UintPtrT>{tmp2.value()});
    tmp6 = CodeStubAssembler(state_).StringFromSingleCharCode(TNode<Int32T>{tmp5});
    CodeStubAssembler(state_).Return(tmp6);
  }

  TNode<String> tmp7;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp7 = kEmptyString_0(state_);
    CodeStubAssembler(state_).Return(tmp7);
  }
}

TF_BUILTIN(StringPrototypeCharCodeAt, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kPosition));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    compiler::TypedCodeAssemblerVariable<String> tmp1(&ca_);
    compiler::TypedCodeAssemblerVariable<UintPtrT> tmp2(&ca_);
    compiler::TypedCodeAssemblerVariable<UintPtrT> tmp3(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    compiler::CodeAssemblerLabel label4(&ca_);
    GenerateStringAt_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, TNode<Object>{parameter2}, "String.prototype.charCodeAt", &label0, &tmp1, &tmp2, &tmp3, &label4);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block5);
    }
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block6);
    }
  }

  TNode<Int32T> tmp5;
  TNode<Smi> tmp6;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp5 = CodeStubAssembler(state_).StringCharCodeAt(TNode<String>{tmp1.value()}, TNode<UintPtrT>{tmp2.value()});
    tmp6 = Convert_Smi_int32_0(state_, TNode<Int32T>{tmp5});
    CodeStubAssembler(state_).Return(tmp6);
  }

  TNode<HeapNumber> tmp7;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp7 = kNaN_0(state_);
    CodeStubAssembler(state_).Return(tmp7);
  }
}

TF_BUILTIN(StringPrototypeCodePointAt, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedCast<NativeContext>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::kReceiver));
USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kPosition));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    compiler::TypedCodeAssemblerVariable<String> tmp1(&ca_);
    compiler::TypedCodeAssemblerVariable<UintPtrT> tmp2(&ca_);
    compiler::TypedCodeAssemblerVariable<UintPtrT> tmp3(&ca_);
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    compiler::CodeAssemblerLabel label4(&ca_);
    GenerateStringAt_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, TNode<Object>{parameter2}, "String.prototype.codePointAt", &label0, &tmp1, &tmp2, &tmp3, &label4);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block5);
    }
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block6);
    }
  }

  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Int32T> tmp7;
  TNode<Smi> tmp8;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp5 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp3.value()});
    tmp6 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp2.value()});
    tmp7 = StringBuiltinsAssembler(state_).LoadSurrogatePairAt(TNode<String>{tmp1.value()}, TNode<IntPtrT>{tmp5}, TNode<IntPtrT>{tmp6}, UnicodeEncoding::UTF32);
    tmp8 = Convert_Smi_int32_0(state_, TNode<Int32T>{tmp7});
    CodeStubAssembler(state_).Return(tmp8);
  }

  TNode<Oddball> tmp9;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp9 = Undefined_0(state_);
    CodeStubAssembler(state_).Return(tmp9);
  }
}

TF_BUILTIN(StringPrototypeConcat, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<String> tmp0;
  TNode<String> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_String_constexpr_string_0(state_, "String.prototype.concat");
    tmp1 = CodeStubAssembler(state_).ToThisString(TNode<Context>{parameter0}, TNode<Object>{parameter1}, TNode<String>{tmp0});
    tmp2 = Convert_intptr_intptr_0(state_, TNode<IntPtrT>{torque_arguments.length});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block3, tmp1, tmp3);
  }

  TNode<String> phi_bb3_5;
  TNode<IntPtrT> phi_bb3_7;
  TNode<BoolT> tmp4;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_5, &phi_bb3_7);
    tmp4 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb3_7}, TNode<IntPtrT>{tmp2});
    ca_.Branch(tmp4, &block1, std::vector<Node*>{phi_bb3_5, phi_bb3_7}, &block2, std::vector<Node*>{phi_bb3_5, phi_bb3_7});
  }

  TNode<String> phi_bb1_5;
  TNode<IntPtrT> phi_bb1_7;
  TNode<Object> tmp5;
  TNode<String> tmp6;
  TNode<String> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_5, &phi_bb1_7);
    tmp5 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{phi_bb1_7});
    tmp6 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<Object>{tmp5});
    tmp7 = StringAdd_0(state_, TNode<Context>{parameter0}, TNode<String>{phi_bb1_5}, TNode<String>{tmp6});
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp9 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb1_7}, TNode<IntPtrT>{tmp8});
    ca_.Goto(&block3, tmp7, tmp9);
  }

  TNode<String> phi_bb2_5;
  TNode<IntPtrT> phi_bb2_7;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_5, &phi_bb2_7);
    arguments.PopAndReturn(phi_bb2_5);
  }
}

TF_BUILTIN(StringConstructor, CodeStubAssembler) {
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
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::kJSNewTarget));
USE(parameter2);
  TNode<JSFunction> parameter3 = UncheckedCast<JSFunction>(Parameter(Descriptor::kJSTarget));
USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Convert_intptr_intptr_0(state_, TNode<IntPtrT>{torque_arguments.length});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp2 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<String> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).EmptyStringConstant();
    ca_.Goto(&block3, tmp3);
  }

  TNode<Oddball> tmp4;
  TNode<BoolT> tmp5;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = Undefined_0(state_);
    tmp5 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{parameter2}, TNode<HeapObject>{tmp4});
    ca_.Branch(tmp5, &block4, std::vector<Node*>{}, &block5, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp6;
  TNode<Object> tmp7;
  TNode<Symbol> tmp8;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp7 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp6});
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_Symbol_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7}, &label9);
    ca_.Goto(&block8);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block9);
    }
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block5);
  }

  TNode<String> tmp10;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp10 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kSymbolDescriptiveString, parameter0, tmp8)); 
    arguments.PopAndReturn(tmp10);
  }

  TNode<IntPtrT> tmp11;
  TNode<Object> tmp12;
  TNode<String> tmp13;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp11 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp12 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp11});
    tmp13 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<Object>{tmp12});
    ca_.Goto(&block3, tmp13);
  }

  TNode<String> phi_bb3_8;
  TNode<Oddball> tmp14;
  TNode<BoolT> tmp15;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_8);
    tmp14 = Undefined_0(state_);
    tmp15 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{parameter2}, TNode<HeapObject>{tmp14});
    ca_.Branch(tmp15, &block10, std::vector<Node*>{phi_bb3_8}, &block11, std::vector<Node*>{phi_bb3_8});
  }

  TNode<String> phi_bb10_8;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_8);
    arguments.PopAndReturn(phi_bb10_8);
  }

  TNode<String> phi_bb11_8;
  TNode<JSReceiver> tmp16;
  TNode<Map> tmp17;
  TNode<JSObject> tmp18;
  TNode<JSPrimitiveWrapper> tmp19;
  TNode<IntPtrT> tmp20;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_8);
    tmp16 = UnsafeCast_JSReceiver_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2});
    tmp17 = GetDerivedMap_0(state_, TNode<Context>{parameter0}, TNode<JSFunction>{parameter3}, TNode<JSReceiver>{tmp16});
    tmp18 = AllocateFastOrSlowJSObjectFromMap_0(state_, TNode<Context>{parameter0}, TNode<Map>{tmp17});
    tmp19 = UnsafeCast_JSPrimitiveWrapper_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp18});
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp19, tmp20}, phi_bb11_8);
    arguments.PopAndReturn(tmp19);
  }
}

TF_BUILTIN(StringAddConvertLeft, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<Object> parameter1 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<String> parameter2 = UncheckedCast<String>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  TNode<String> tmp1;
  TNode<String> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ToPrimitiveDefault_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = ToStringImpl_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp0});
    tmp2 = StringAdd_0(state_, TNode<Context>{parameter0}, TNode<String>{tmp1}, TNode<String>{parameter2});
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(StringAddConvertRight, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<String> parameter1 = UncheckedCast<String>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<Object> parameter2 = UncheckedCast<Object>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  TNode<String> tmp1;
  TNode<String> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ToPrimitiveDefault_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2});
    tmp1 = ToStringImpl_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp0});
    tmp2 = StringAdd_0(state_, TNode<Context>{parameter0}, TNode<String>{parameter1}, TNode<String>{tmp1});
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(StringCharAt, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<String> parameter1 = UncheckedCast<String>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Int32T> tmp0;
  TNode<String> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).StringCharCodeAt(TNode<String>{parameter1}, TNode<UintPtrT>{parameter2});
    tmp1 = CodeStubAssembler(state_).StringFromSingleCharCode(TNode<Int32T>{tmp0});
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TNode<IntPtrT> Convert_intptr_intptr_0(compiler::CodeAssemblerState* state_, TNode<IntPtrT> p_i) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<IntPtrT>{p_i};
}

TNode<Symbol> Cast_Symbol_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<Symbol> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Symbol_0(state_, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<Symbol>{tmp2};
}

}  // namespace internal
}  // namespace v8

