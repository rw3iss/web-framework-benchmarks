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

TNode<BoolT> IsMonomorphic_0(compiler::CodeAssemblerState* state_, TNode<MaybeObject> p_feedback, TNode<Object> p_target) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).IsWeakReferenceToObject(TNode<MaybeObject>{p_feedback}, TNode<Object>{p_target});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BoolT>{tmp0};
}

TNode<BoolT> InSameNativeContext_0(compiler::CodeAssemblerState* state_, TNode<Context> p_lhs, TNode<Context> p_rhs) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<NativeContext> tmp0;
  TNode<NativeContext> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_lhs});
    tmp1 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_rhs});
    tmp2 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp0}, TNode<HeapObject>{tmp1});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<BoolT>{tmp2};
}

TNode<HeapObject> MaybeObjectToStrong_0(compiler::CodeAssemblerState* state_, TNode<MaybeObject> p_maybeObject, compiler::CodeAssemblerLabel* label_IfCleared) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<MaybeObject> tmp0;
  TNode<HeapObject> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<MaybeObject>{p_maybeObject});
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp1 = WeakToStrong_HeapObject_0(state_, TNode<MaybeObject>{tmp0}, &label2);
    ca_.Goto(&block7);
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(label_IfCleared);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block9);
  }

    ca_.Bind(&block9);
  return TNode<HeapObject>{tmp1};
}

void TryInitializeAsMonomorphic_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_maybeTarget, TNode<FeedbackVector> p_feedbackVector, TNode<UintPtrT> p_slotId, compiler::CodeAssemblerLabel* label_TransitionToMegamorphic) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<HeapObject> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<HeapObject> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<HeapObject> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<HeapObject, HeapObject> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<HeapObject, HeapObject> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<HeapObject> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<HeapObject> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapObject> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_HeapObject_1(state_, TNode<Context>{p_context}, TNode<Object>{p_maybeTarget}, &label1);
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

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block7, tmp0);
  }

  TNode<HeapObject> phi_bb7_5;
  TNode<BoolT> tmp2;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_5);
    tmp2 = Is_JSBoundFunction_HeapObject_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{phi_bb7_5});
    ca_.Branch(tmp2, &block5, std::vector<Node*>{phi_bb7_5}, &block6, std::vector<Node*>{phi_bb7_5});
  }

  TNode<HeapObject> phi_bb5_5;
  TNode<JSBoundFunction> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<JSReceiver> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_5);
    tmp3 = UnsafeCast_JSBoundFunction_0(state_, TNode<Context>{p_context}, TNode<Object>{phi_bb5_5});
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp5 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{tmp3, tmp4});
    ca_.Goto(&block7, tmp5);
  }

  TNode<HeapObject> phi_bb6_5;
  TNode<JSFunction> tmp6;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_5);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_JSFunction_0(state_, TNode<HeapObject>{phi_bb6_5}, &label7);
    ca_.Goto(&block8, phi_bb6_5, phi_bb6_5);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block9, phi_bb6_5, phi_bb6_5);
    }
  }

  TNode<HeapObject> phi_bb9_5;
  TNode<HeapObject> phi_bb9_6;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_5, &phi_bb9_6);
    ca_.Goto(&block1);
  }

  TNode<HeapObject> phi_bb8_5;
  TNode<HeapObject> phi_bb8_6;
  TNode<IntPtrT> tmp8;
  TNode<Context> tmp9;
  TNode<BoolT> tmp10;
  TNode<BoolT> tmp11;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_5, &phi_bb8_6);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp9 = CodeStubAssembler(state_).LoadReference<Context>(CodeStubAssembler::Reference{tmp6, tmp8});
    tmp10 = InSameNativeContext_0(state_, TNode<Context>{tmp9}, TNode<Context>{p_context});
    tmp11 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp10});
    ca_.Branch(tmp11, &block10, std::vector<Node*>{phi_bb8_5}, &block11, std::vector<Node*>{phi_bb8_5});
  }

  TNode<HeapObject> phi_bb10_5;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_5);
    ca_.Goto(&block1);
  }

  TNode<HeapObject> phi_bb11_5;
  TNode<MaybeObject> tmp12;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_5);
    tmp12 = CodeStubAssembler(state_).StoreWeakReferenceInFeedbackVector(TNode<FeedbackVector>{p_feedbackVector}, TNode<UintPtrT>{p_slotId}, TNode<HeapObject>{tmp0});
    CodeStubAssembler(state_).ReportFeedbackUpdate(TNode<FeedbackVector>{p_feedbackVector}, TNode<UintPtrT>{p_slotId}, "Call:Initialize");
    ca_.Goto(&block12);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_TransitionToMegamorphic);
  }

    ca_.Bind(&block12);
}

void TransitionToMegamorphic_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FeedbackVector> p_feedbackVector, TNode<UintPtrT> p_slotId) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Symbol> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = kMegamorphicSymbol_0(state_);
    CodeStubAssembler(state_).StoreFeedbackVectorSlot(TNode<FeedbackVector>{p_feedbackVector}, TNode<UintPtrT>{p_slotId}, TNode<MaybeObject>{tmp0});
    CodeStubAssembler(state_).ReportFeedbackUpdate(TNode<FeedbackVector>{p_feedbackVector}, TNode<UintPtrT>{p_slotId}, "Call:TransitionMegamorphic");
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

void CollectCallFeedback_0(compiler::CodeAssemblerState* state_, TNode<Object> p_maybeTarget, TNode<Context> p_context, TNode<HeapObject> p_maybeFeedbackVector, TNode<UintPtrT> p_slotId) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FeedbackVector> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FeedbackVector_0(state_, TNode<HeapObject>{p_maybeFeedbackVector}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block1);
  }

  TNode<MaybeObject> tmp2;
  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).IncrementCallCount(TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId});
    tmp2 = CodeStubAssembler(state_).LoadFeedbackVectorSlot(TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId});
    tmp3 = IsMonomorphic_0(state_, TNode<MaybeObject>{tmp2}, TNode<Object>{p_maybeTarget});
    ca_.Branch(tmp3, &block10, std::vector<Node*>{}, &block11, std::vector<Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block1);
  }

  TNode<BoolT> tmp4;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp4 = IsMegamorphic_0(state_, TNode<MaybeObject>{tmp2});
    ca_.Branch(tmp4, &block12, std::vector<Node*>{}, &block13, std::vector<Node*>{});
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block1);
  }

  TNode<BoolT> tmp5;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp5 = IsUninitialized_0(state_, TNode<MaybeObject>{tmp2});
    ca_.Branch(tmp5, &block14, std::vector<Node*>{}, &block15, std::vector<Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block9);
  }

  TNode<HeapObject> tmp6;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = MaybeObjectToStrong_0(state_, TNode<MaybeObject>{tmp2}, &label7);
    ca_.Goto(&block16);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block17);
    }
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block9);
  }

  TNode<JSFunction> tmp8;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_JSFunction_1(state_, TNode<Context>{p_context}, TNode<Object>{p_maybeTarget}, &label9);
    ca_.Goto(&block18);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block19);
    }
  }

  if (block19.is_used()) {
    ca_.Bind(&block19);
    ca_.Goto(&block7);
  }

  TNode<IntPtrT> tmp10;
  TNode<FeedbackCell> tmp11;
  TNode<BoolT> tmp12;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp11 = CodeStubAssembler(state_).LoadReference<FeedbackCell>(CodeStubAssembler::Reference{tmp8, tmp10});
    tmp12 = CodeStubAssembler(state_).TaggedEqual(TNode<MaybeObject>{tmp6}, TNode<MaybeObject>{tmp11});
    ca_.Branch(tmp12, &block20, std::vector<Node*>{}, &block21, std::vector<Node*>{});
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    ca_.Goto(&block1);
  }

  TNode<JSFunction> tmp13;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    compiler::CodeAssemblerLabel label14(&ca_);
    tmp13 = Cast_JSFunction_0(state_, TNode<HeapObject>{tmp6}, &label14);
    ca_.Goto(&block22);
    if (label14.is_used()) {
      ca_.Bind(&label14);
      ca_.Goto(&block23);
    }
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    ca_.Goto(&block7);
  }

  TNode<IntPtrT> tmp15;
  TNode<FeedbackCell> tmp16;
  TNode<BoolT> tmp17;
  TNode<BoolT> tmp18;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp16 = CodeStubAssembler(state_).LoadReference<FeedbackCell>(CodeStubAssembler::Reference{tmp13, tmp15});
    tmp17 = CodeStubAssembler(state_).TaggedEqual(TNode<MaybeObject>{tmp16}, TNode<MaybeObject>{tmp11});
    tmp18 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp17});
    ca_.Branch(tmp18, &block24, std::vector<Node*>{}, &block25, std::vector<Node*>{});
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    ca_.Goto(&block7);
  }

  TNode<MaybeObject> tmp19;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp19 = CodeStubAssembler(state_).StoreWeakReferenceInFeedbackVector(TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId}, TNode<HeapObject>{tmp16});
    CodeStubAssembler(state_).ReportFeedbackUpdate(TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId}, "Call:FeedbackVectorCell");
    ca_.Goto(&block8);
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    compiler::CodeAssemblerLabel label20(&ca_);
    TryInitializeAsMonomorphic_0(state_, TNode<Context>{p_context}, TNode<Object>{p_maybeTarget}, TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId}, &label20);
    ca_.Goto(&block26);
    if (label20.is_used()) {
      ca_.Bind(&label20);
      ca_.Goto(&block27);
    }
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    ca_.Goto(&block7);
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    ca_.Goto(&block8);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block6);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    TransitionToMegamorphic_0(state_, TNode<Context>{p_context}, TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId});
    ca_.Goto(&block6);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(&block28);
  }

    ca_.Bind(&block28);
}

void CollectInstanceOfFeedback_0(compiler::CodeAssemblerState* state_, TNode<Object> p_maybeTarget, TNode<Context> p_context, TNode<HeapObject> p_maybeFeedbackVector, TNode<UintPtrT> p_slotId) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FeedbackVector> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FeedbackVector_0(state_, TNode<HeapObject>{p_maybeFeedbackVector}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block1);
  }

  TNode<MaybeObject> tmp2;
  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = CodeStubAssembler(state_).LoadFeedbackVectorSlot(TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId});
    tmp3 = IsMonomorphic_0(state_, TNode<MaybeObject>{tmp2}, TNode<Object>{p_maybeTarget});
    ca_.Branch(tmp3, &block10, std::vector<Node*>{}, &block11, std::vector<Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block1);
  }

  TNode<BoolT> tmp4;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp4 = IsMegamorphic_0(state_, TNode<MaybeObject>{tmp2});
    ca_.Branch(tmp4, &block12, std::vector<Node*>{}, &block13, std::vector<Node*>{});
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block1);
  }

  TNode<BoolT> tmp5;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp5 = IsUninitialized_0(state_, TNode<MaybeObject>{tmp2});
    ca_.Branch(tmp5, &block14, std::vector<Node*>{}, &block15, std::vector<Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block9);
  }

  TNode<HeapObject> tmp6;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = MaybeObjectToStrong_0(state_, TNode<MaybeObject>{tmp2}, &label7);
    ca_.Goto(&block16);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block17);
    }
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block9);
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    ca_.Goto(&block7);
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    compiler::CodeAssemblerLabel label8(&ca_);
    TryInitializeAsMonomorphic_0(state_, TNode<Context>{p_context}, TNode<Object>{p_maybeTarget}, TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId}, &label8);
    ca_.Goto(&block18);
    if (label8.is_used()) {
      ca_.Bind(&label8);
      ca_.Goto(&block19);
    }
  }

  if (block19.is_used()) {
    ca_.Bind(&block19);
    ca_.Goto(&block7);
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    ca_.Goto(&block6);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    TransitionToMegamorphic_0(state_, TNode<Context>{p_context}, TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId});
    ca_.Goto(&block6);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(&block20);
  }

    ca_.Bind(&block20);
}

TNode<BoolT> BothTaggedEqualArrayFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_first, TNode<Object> p_second) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).TaggedEqual(TNode<MaybeObject>{p_first}, TNode<MaybeObject>{p_second});
    ca_.Branch(tmp0, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<JSFunction> tmp1;
  TNode<BoolT> tmp2;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = GetArrayFunction_0(state_, TNode<Context>{p_context});
    tmp2 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{p_second}, TNode<HeapObject>{tmp1});
    ca_.Goto(&block4, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block4, tmp3);
  }

  TNode<BoolT> phi_bb4_4;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_4);
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
  return TNode<BoolT>{phi_bb4_4};
}

void CollectConstructFeedback_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_target, TNode<Object> p_newTarget, TNode<HeapObject> p_maybeFeedbackVector, TNode<UintPtrT> p_slotId, compiler::CodeAssemblerLabel* label_ConstructGeneric, compiler::CodeAssemblerLabel* label_ConstructArray, compiler::TypedCodeAssemblerVariable<AllocationSite>* label_ConstructArray_parameter_0) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<AllocationSite> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FeedbackVector> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FeedbackVector_0(state_, TNode<HeapObject>{p_maybeFeedbackVector}, &label1);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  TNode<MaybeObject> tmp2;
  TNode<BoolT> tmp3;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).IncrementCallCount(TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId});
    tmp2 = CodeStubAssembler(state_).LoadFeedbackVectorSlot(TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId});
    tmp3 = IsMonomorphic_0(state_, TNode<MaybeObject>{tmp2}, TNode<Object>{p_newTarget});
    ca_.Branch(tmp3, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block1);
  }

  TNode<BoolT> tmp4;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp4 = IsMegamorphic_0(state_, TNode<MaybeObject>{tmp2});
    ca_.Branch(tmp4, &block13, std::vector<Node*>{}, &block14, std::vector<Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block1);
  }

  TNode<BoolT> tmp5;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp5 = IsUninitialized_0(state_, TNode<MaybeObject>{tmp2});
    ca_.Branch(tmp5, &block15, std::vector<Node*>{}, &block16, std::vector<Node*>{});
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    ca_.Goto(&block10);
  }

  TNode<BoolT> tmp6;
  TNode<BoolT> tmp7;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp6 = CodeStubAssembler(state_).IsWeakOrCleared(TNode<MaybeObject>{tmp2});
    tmp7 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp6});
    ca_.Branch(tmp7, &block17, std::vector<Node*>{}, &block18, std::vector<Node*>{});
  }

  TNode<Object> tmp8;
  TNode<BoolT> tmp9;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp8 = TORQUE_CAST(TNode<MaybeObject>{tmp2});
    tmp9 = Is_AllocationSite_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp8});
    ca_.Branch(tmp9, &block19, std::vector<Node*>{}, &block20, std::vector<Node*>{});
  }

  TNode<BoolT> tmp10;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp10 = BothTaggedEqualArrayFunction_0(state_, TNode<Context>{p_context}, TNode<Object>{p_target}, TNode<Object>{p_newTarget});
    ca_.Branch(tmp10, &block21, std::vector<Node*>{}, &block22, std::vector<Node*>{});
  }

  TNode<AllocationSite> tmp11;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp11 = UnsafeCast_AllocationSite_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp8});
    ca_.Goto(&block2, tmp11);
  }

  if (block22.is_used()) {
    ca_.Bind(&block22);
    ca_.Goto(&block8);
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    ca_.Goto(&block18);
  }

  TNode<HeapObject> tmp12;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    compiler::CodeAssemblerLabel label13(&ca_);
    tmp12 = MaybeObjectToStrong_0(state_, TNode<MaybeObject>{tmp2}, &label13);
    ca_.Goto(&block23);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block24);
    }
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    ca_.Goto(&block10);
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    ca_.Goto(&block8);
  }

  TNode<BoolT> tmp14;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp14 = BothTaggedEqualArrayFunction_0(state_, TNode<Context>{p_context}, TNode<Object>{p_target}, TNode<Object>{p_newTarget});
    ca_.Branch(tmp14, &block25, std::vector<Node*>{}, &block26, std::vector<Node*>{});
  }

  TNode<AllocationSite> tmp15;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp15 = CodeStubAssembler(state_).CreateAllocationSiteInFeedbackVector(TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId});
    CodeStubAssembler(state_).ReportFeedbackUpdate(TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId}, "Construct:CreateAllocationSite");
    ca_.Goto(&block2, tmp15);
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    compiler::CodeAssemblerLabel label16(&ca_);
    TryInitializeAsMonomorphic_0(state_, TNode<Context>{p_context}, TNode<Object>{p_newTarget}, TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId}, &label16);
    ca_.Goto(&block27);
    if (label16.is_used()) {
      ca_.Bind(&label16);
      ca_.Goto(&block28);
    }
  }

  if (block28.is_used()) {
    ca_.Bind(&block28);
    ca_.Goto(&block8);
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    ca_.Goto(&block7);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    TransitionToMegamorphic_0(state_, TNode<Context>{p_context}, TNode<FeedbackVector>{tmp0}, TNode<UintPtrT>{p_slotId});
    ca_.Goto(&block7);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block1);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_ConstructGeneric);
  }

  TNode<AllocationSite> phi_bb2_0;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_0);
    *label_ConstructArray_parameter_0 = phi_bb2_0;
    ca_.Goto(label_ConstructArray);
  }
}

TNode<HeapObject> WeakToStrong_HeapObject_0(compiler::CodeAssemblerState* state_, TNode<MaybeObject> p_x, compiler::CodeAssemblerLabel* label_ClearedWeakPointer) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapObject> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = CodeStubAssembler(state_).GetHeapObjectAssumeWeak(TNode<MaybeObject>{p_x}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(label_ClearedWeakPointer);
  }

  TNode<HeapObject> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = (TNode<HeapObject>{tmp0});
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
  return TNode<HeapObject>{tmp2};
}

TNode<BoolT> Is_JSBoundFunction_HeapObject_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<HeapObject> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSBoundFunction> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSBoundFunction_0(state_, TNode<HeapObject>{p_o}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<BoolT> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp3);
  }

  TNode<BoolT> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<BoolT>{phi_bb1_2};
}

TNode<JSBoundFunction> UnsafeCast_JSBoundFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSBoundFunction> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<JSBoundFunction>{tmp0};
}

TNode<BoolT> Is_AllocationSite_Object_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<AllocationSite> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_AllocationSite_1(state_, TNode<Context>{p_context}, TNode<Object>{p_o}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<BoolT> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp3);
  }

  TNode<BoolT> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<BoolT>{phi_bb1_2};
}

TNode<AllocationSite> UnsafeCast_AllocationSite_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<AllocationSite> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<AllocationSite>{tmp0};
}

}  // namespace internal
}  // namespace v8

