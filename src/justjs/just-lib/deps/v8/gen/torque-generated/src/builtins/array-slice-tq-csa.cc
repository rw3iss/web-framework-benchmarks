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

TNode<JSArray> HandleSimpleArgumentsSlice_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<JSArgumentsObject> p_args, TNode<Smi> p_start, TNode<Smi> p_count, compiler::CodeAssemblerLabel* label_Bailout) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, FixedArray::kMaxRegularLength);
    tmp1 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{p_count}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block1);
  }

  TNode<Smi> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_start}, TNode<Smi>{p_count});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{p_args, tmp3});
    compiler::CodeAssemblerLabel label6(&ca_);
    tmp5 = Cast_FixedArray_0(state_, TNode<HeapObject>{tmp4}, &label6);
    ca_.Goto(&block5);
    if (label6.is_used()) {
      ca_.Bind(&label6);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp7;
  TNode<Smi> tmp8;
  TNode<BoolT> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp8 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp5, tmp7});
    tmp9 = CodeStubAssembler(state_).SmiAbove(TNode<Smi>{tmp2}, TNode<Smi>{tmp8});
    ca_.Branch(tmp9, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block1);
  }

  TNode<Map> tmp10;
  TNode<JSArray> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<FixedArrayBase> tmp13;
  TNode<FixedArray> tmp14;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp10 = CodeStubAssembler(state_).LoadJSArrayElementsMap(ElementsKind::HOLEY_ELEMENTS, TNode<NativeContext>{p_context});
    tmp11 = CodeStubAssembler(state_).AllocateJSArray(ElementsKind::HOLEY_ELEMENTS, TNode<Map>{tmp10}, TNode<Smi>{p_count}, TNode<Smi>{p_count});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp13 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp11, tmp12});
    compiler::CodeAssemblerLabel label15(&ca_);
    tmp14 = Cast_FixedArray_0(state_, TNode<HeapObject>{tmp13}, &label15);
    ca_.Goto(&block9);
    if (label15.is_used()) {
      ca_.Bind(&label15);
      ca_.Goto(&block10);
    }
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp16 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_start});
    tmp17 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_count});
    tmp18 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).CopyElements(ElementsKind::PACKED_ELEMENTS, TNode<FixedArrayBase>{tmp14}, TNode<IntPtrT>{tmp18}, TNode<FixedArrayBase>{tmp5}, TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp17});
    ca_.Goto(&block11);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Bailout);
  }

    ca_.Bind(&block11);
  return TNode<JSArray>{tmp11};
}

TNode<JSArray> HandleFastAliasedSloppyArgumentsSlice_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<JSArgumentsObject> p_args, TNode<Smi> p_start, TNode<Smi> p_count, compiler::CodeAssemblerLabel* label_Bailout) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Object> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, FixedArray::kMaxRegularLength);
    tmp1 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{p_count}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp2;
  TNode<FixedArrayBase> tmp3;
  TNode<SloppyArgumentsElements> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp3 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{p_args, tmp2});
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_SloppyArgumentsElements_0(state_, TNode<HeapObject>{tmp3}, &label5);
    ca_.Goto(&block5);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<FixedArray> tmp10;
  TNode<FixedArray> tmp11;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp7 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp4, tmp6});
    tmp8 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_start}, TNode<Smi>{p_count});
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp10 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{tmp4, tmp9});
    compiler::CodeAssemblerLabel label12(&ca_);
    tmp11 = Cast_FixedArray_0(state_, TNode<HeapObject>{tmp10}, &label12);
    ca_.Goto(&block7);
    if (label12.is_used()) {
      ca_.Bind(&label12);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp13;
  TNode<Smi> tmp14;
  TNode<BoolT> tmp15;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp14 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp13});
    tmp15 = CodeStubAssembler(state_).SmiAbove(TNode<Smi>{tmp8}, TNode<Smi>{tmp14});
    ca_.Branch(tmp15, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp16;
  TNode<Context> tmp17;
  TNode<Map> tmp18;
  TNode<JSArray> tmp19;
  TNode<Smi> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<FixedArrayBase> tmp22;
  TNode<FixedArray> tmp23;
  TNode<Smi> tmp24;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp17 = CodeStubAssembler(state_).LoadReference<Context>(CodeStubAssembler::Reference{tmp4, tmp16});
    tmp18 = CodeStubAssembler(state_).LoadJSArrayElementsMap(ElementsKind::HOLEY_ELEMENTS, TNode<NativeContext>{p_context});
    tmp19 = CodeStubAssembler(state_).AllocateJSArray(ElementsKind::HOLEY_ELEMENTS, TNode<Map>{tmp18}, TNode<Smi>{p_count}, TNode<Smi>{p_count});
    tmp20 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp22 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp19, tmp21});
    tmp23 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp22});
    tmp24 = CodeStubAssembler(state_).SmiMin(TNode<Smi>{tmp7}, TNode<Smi>{tmp8});
    ca_.Goto(&block13, tmp20, p_start);
  }

  TNode<Smi> phi_bb13_12;
  TNode<Smi> phi_bb13_15;
  TNode<BoolT> tmp25;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_12, &phi_bb13_15);
    tmp25 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb13_15}, TNode<Smi>{tmp24});
    ca_.Branch(tmp25, &block11, std::vector<Node*>{phi_bb13_12, phi_bb13_15}, &block12, std::vector<Node*>{phi_bb13_12, phi_bb13_15});
  }

  TNode<Smi> phi_bb11_12;
  TNode<Smi> phi_bb11_15;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Smi> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<BoolT> tmp34;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_12, &phi_bb11_15);
    tmp26 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp29 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp4, tmp28});
    tmp30 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp29});
    tmp31 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb11_15});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp30});
    tmp34 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp32}, TNode<UintPtrT>{tmp33});
    ca_.Branch(tmp34, &block19, std::vector<Node*>{phi_bb11_12, phi_bb11_15, phi_bb11_15, phi_bb11_15}, &block20, std::vector<Node*>{phi_bb11_12, phi_bb11_15, phi_bb11_15, phi_bb11_15});
  }

  TNode<Smi> phi_bb19_12;
  TNode<Smi> phi_bb19_15;
  TNode<Smi> phi_bb19_20;
  TNode<Smi> phi_bb19_21;
  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<HeapObject> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<Object> tmp40;
  TNode<Oddball> tmp41;
  TNode<BoolT> tmp42;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_12, &phi_bb19_15, &phi_bb19_20, &phi_bb19_21);
    tmp35 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp36 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp31}, TNode<IntPtrT>{tmp35});
    tmp37 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp26}, TNode<IntPtrT>{tmp36});
    std::tie(tmp38, tmp39) = NewReference_Smi_OR_TheHole_0(state_, TNode<HeapObject>{tmp4}, TNode<IntPtrT>{tmp37}).Flatten();
    tmp40 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp38, tmp39});
    tmp41 = TheHole_0(state_);
    tmp42 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp40}, TNode<HeapObject>{tmp41});
    ca_.Branch(tmp42, &block22, std::vector<Node*>{phi_bb19_12, phi_bb19_15}, &block23, std::vector<Node*>{phi_bb19_12, phi_bb19_15});
  }

  TNode<Smi> phi_bb20_12;
  TNode<Smi> phi_bb20_15;
  TNode<Smi> phi_bb20_20;
  TNode<Smi> phi_bb20_21;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_12, &phi_bb20_15, &phi_bb20_20, &phi_bb20_21);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb22_12;
  TNode<Smi> phi_bb22_15;
  TNode<IntPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<Smi> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<Smi> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<UintPtrT> tmp50;
  TNode<UintPtrT> tmp51;
  TNode<BoolT> tmp52;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_12, &phi_bb22_15);
    tmp43 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp44 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp46 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp17, tmp45});
    tmp47 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp46});
    tmp48 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp40});
    tmp49 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp48});
    tmp50 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp49});
    tmp51 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp47});
    tmp52 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp50}, TNode<UintPtrT>{tmp51});
    ca_.Branch(tmp52, &block30, std::vector<Node*>{phi_bb22_12, phi_bb22_15}, &block31, std::vector<Node*>{phi_bb22_12, phi_bb22_15});
  }

  TNode<Smi> phi_bb30_12;
  TNode<Smi> phi_bb30_15;
  TNode<IntPtrT> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<HeapObject> tmp56;
  TNode<IntPtrT> tmp57;
  TNode<Object> tmp58;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_12, &phi_bb30_15);
    tmp53 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp54 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp49}, TNode<IntPtrT>{tmp53});
    tmp55 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp43}, TNode<IntPtrT>{tmp54});
    std::tie(tmp56, tmp57) = NewReference_Object_0(state_, TNode<HeapObject>{tmp17}, TNode<IntPtrT>{tmp55}).Flatten();
    tmp58 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp56, tmp57});
    ca_.Goto(&block24, phi_bb30_12, phi_bb30_15, tmp58);
  }

  TNode<Smi> phi_bb31_12;
  TNode<Smi> phi_bb31_15;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_12, &phi_bb31_15);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb23_12;
  TNode<Smi> phi_bb23_15;
  TNode<IntPtrT> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<Smi> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<UintPtrT> tmp65;
  TNode<UintPtrT> tmp66;
  TNode<BoolT> tmp67;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_12, &phi_bb23_15);
    tmp59 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp60 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp61 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp62 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp61});
    tmp63 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp62});
    tmp64 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb23_15});
    tmp65 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp64});
    tmp66 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp63});
    tmp67 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp65}, TNode<UintPtrT>{tmp66});
    ca_.Branch(tmp67, &block37, std::vector<Node*>{phi_bb23_12, phi_bb23_15, phi_bb23_15, phi_bb23_15}, &block38, std::vector<Node*>{phi_bb23_12, phi_bb23_15, phi_bb23_15, phi_bb23_15});
  }

  TNode<Smi> phi_bb37_12;
  TNode<Smi> phi_bb37_15;
  TNode<Smi> phi_bb37_21;
  TNode<Smi> phi_bb37_22;
  TNode<IntPtrT> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<HeapObject> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<Object> tmp73;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_12, &phi_bb37_15, &phi_bb37_21, &phi_bb37_22);
    tmp68 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp69 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp64}, TNode<IntPtrT>{tmp68});
    tmp70 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp59}, TNode<IntPtrT>{tmp69});
    std::tie(tmp71, tmp72) = NewReference_Object_0(state_, TNode<HeapObject>{tmp11}, TNode<IntPtrT>{tmp70}).Flatten();
    tmp73 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp71, tmp72});
    ca_.Goto(&block24, phi_bb37_12, phi_bb37_15, tmp73);
  }

  TNode<Smi> phi_bb38_12;
  TNode<Smi> phi_bb38_15;
  TNode<Smi> phi_bb38_21;
  TNode<Smi> phi_bb38_22;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_12, &phi_bb38_15, &phi_bb38_21, &phi_bb38_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb24_12;
  TNode<Smi> phi_bb24_15;
  TNode<Object> phi_bb24_17;
  TNode<Object> tmp74;
  TNode<Smi> tmp75;
  TNode<Smi> tmp76;
  TNode<Smi> tmp77;
  TNode<Smi> tmp78;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_12, &phi_bb24_15, &phi_bb24_17);
    tmp74 = UnsafeCast_JSReceiver_OR_Undefined_OR_Null_OR_False_OR_True_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_Smi_OR_TheHole_0(state_, TNode<Context>{p_context}, TNode<Object>{phi_bb24_17});
    tmp75 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp76 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb24_12}, TNode<Smi>{tmp75});
    CodeStubAssembler(state_).StoreFixedArrayElement(TNode<FixedArray>{tmp23}, TNode<Smi>{phi_bb24_12}, TNode<Object>{tmp74}, UNSAFE_SKIP_WRITE_BARRIER);
    tmp77 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp78 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb24_15}, TNode<Smi>{tmp77});
    ca_.Goto(&block13, tmp76, tmp78);
  }

  TNode<Smi> phi_bb12_12;
  TNode<Smi> phi_bb12_15;
  TNode<Smi> tmp79;
  TNode<Smi> tmp80;
  TNode<Smi> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<IntPtrT> tmp83;
  TNode<IntPtrT> tmp84;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_12, &phi_bb12_15);
    tmp79 = CodeStubAssembler(state_).SmiMax(TNode<Smi>{tmp7}, TNode<Smi>{p_start});
    tmp80 = CodeStubAssembler(state_).SmiMin(TNode<Smi>{tmp79}, TNode<Smi>{tmp8});
    tmp81 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp8}, TNode<Smi>{tmp80});
    tmp82 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb12_12});
    tmp83 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp80});
    tmp84 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp81});
    CodeStubAssembler(state_).CopyElements(ElementsKind::PACKED_ELEMENTS, TNode<FixedArrayBase>{tmp23}, TNode<IntPtrT>{tmp82}, TNode<FixedArrayBase>{tmp11}, TNode<IntPtrT>{tmp83}, TNode<IntPtrT>{tmp84});
    ca_.Goto(&block40);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Bailout);
  }

    ca_.Bind(&block40);
  return TNode<JSArray>{tmp19};
}

TNode<JSArray> HandleFastSlice_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<Object> p_o, TNode<Number> p_startNumber, TNode<Number> p_countNumber, compiler::CodeAssemblerLabel* label_Bailout) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSArgumentsObject> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSArgumentsObject, JSArgumentsObject> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSArgumentsObject, JSArgumentsObject> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSArray> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSArray> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_Smi_0(state_, TNode<Object>{p_startNumber}, &label1);
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

  TNode<Smi> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Smi_0(state_, TNode<Object>{p_countNumber}, &label3);
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

  TNode<JSArray> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_FastJSArrayForCopy_1(state_, TNode<Context>{p_context}, TNode<Object>{p_o}, &label5);
    ca_.Goto(&block15);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block16);
    }
  }

  TNode<JSArgumentsObject> tmp6;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_JSStrictArgumentsObject_1(state_, TNode<Context>{p_context}, TNode<Object>{ca_.UncheckedCast<Object>(p_o)}, &label7);
    ca_.Goto(&block21);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block22);
    }
  }

  TNode<Smi> tmp8;
  TNode<Smi> tmp9;
  TNode<BoolT> tmp10;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp8 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp0}, TNode<Smi>{tmp2});
    tmp9 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp4});
    tmp10 = CodeStubAssembler(state_).SmiAbove(TNode<Smi>{tmp8}, TNode<Smi>{tmp9});
    ca_.Branch(tmp10, &block17, std::vector<Node*>{}, &block18, std::vector<Node*>{});
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block1);
  }

  TNode<JSArray> tmp11;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp11 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kExtractFastJSArray, p_context, tmp4, tmp0, tmp2));
    ca_.Goto(&block2, tmp11);
  }

  TNode<JSArgumentsObject> tmp12;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    compiler::CodeAssemblerLabel label13(&ca_);
    tmp12 = Cast_JSSloppyArgumentsObject_1(state_, TNode<Context>{p_context}, TNode<Object>{ca_.UncheckedCast<Object>(p_o)}, &label13);
    ca_.Goto(&block25);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block26);
    }
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    ca_.Goto(&block12, tmp6);
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp14;
  TNode<Map> tmp15;
  TNode<BoolT> tmp16;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp15 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp12, tmp14});
    tmp16 = CodeStubAssembler(state_).IsFastAliasedArgumentsMap(TNode<Context>{p_context}, TNode<Map>{tmp15});
    ca_.Branch(tmp16, &block27, std::vector<Node*>{}, &block28, std::vector<Node*>{});
  }

  TNode<JSArray> tmp17;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    compiler::CodeAssemblerLabel label18(&ca_);
    tmp17 = HandleFastAliasedSloppyArgumentsSlice_0(state_, TNode<NativeContext>{p_context}, TNode<JSArgumentsObject>{tmp12}, TNode<Smi>{tmp0}, TNode<Smi>{tmp2}, &label18);
    ca_.Goto(&block30);
    if (label18.is_used()) {
      ca_.Bind(&label18);
      ca_.Goto(&block31);
    }
  }

  if (block31.is_used()) {
    ca_.Bind(&block31);
    ca_.Goto(&block1);
  }

  if (block30.is_used()) {
    ca_.Bind(&block30);
    ca_.Goto(&block2, tmp17);
  }

  TNode<BoolT> tmp19;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    tmp19 = CodeStubAssembler(state_).IsSloppyArgumentsMap(TNode<Context>{p_context}, TNode<Map>{tmp15});
    ca_.Branch(tmp19, &block32, std::vector<Node*>{}, &block33, std::vector<Node*>{});
  }

  if (block32.is_used()) {
    ca_.Bind(&block32);
    ca_.Goto(&block12, tmp12);
  }

  if (block33.is_used()) {
    ca_.Bind(&block33);
    ca_.Goto(&block1);
  }

  TNode<JSArgumentsObject> phi_bb12_6;
  TNode<JSArray> tmp20;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_6);
    compiler::CodeAssemblerLabel label21(&ca_);
    tmp20 = HandleSimpleArgumentsSlice_0(state_, TNode<NativeContext>{p_context}, TNode<JSArgumentsObject>{phi_bb12_6}, TNode<Smi>{tmp0}, TNode<Smi>{tmp2}, &label21);
    ca_.Goto(&block34, phi_bb12_6, phi_bb12_6);
    if (label21.is_used()) {
      ca_.Bind(&label21);
      ca_.Goto(&block35, phi_bb12_6, phi_bb12_6);
    }
  }

  TNode<JSArgumentsObject> phi_bb35_6;
  TNode<JSArgumentsObject> phi_bb35_8;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_6, &phi_bb35_8);
    ca_.Goto(&block1);
  }

  TNode<JSArgumentsObject> phi_bb34_6;
  TNode<JSArgumentsObject> phi_bb34_8;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_6, &phi_bb34_8);
    ca_.Goto(&block2, tmp20);
  }

  TNode<JSArray> phi_bb2_4;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4);
    ca_.Goto(&block36, phi_bb2_4);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Bailout);
  }

  TNode<JSArray> phi_bb36_4;
    ca_.Bind(&block36, &phi_bb36_4);
  return TNode<JSArray>{phi_bb36_4};
}

TF_BUILTIN(ArrayPrototypeSlice, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, Number> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, Number> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp1, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<JSArray> tmp2;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_FastJSArrayForCopy_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label3);
    ca_.Goto(&block5);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block2);
  }

  TNode<JSArray> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kCloneFastJSArray, parameter0, tmp2));
    arguments.PopAndReturn(tmp4);
  }

  TNode<JSReceiver> tmp5;
  TNode<Number> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<Object> tmp8;
  TNode<Number> tmp9;
  TNode<Number> tmp10;
  TNode<BoolT> tmp11;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp6 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp5});
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp8 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp7});
    tmp9 = ToInteger_Inline_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp8});
    tmp10 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp11 = NumberIsLessThan_0(state_, TNode<Number>{tmp9}, TNode<Number>{tmp10});
    ca_.Branch(tmp11, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<Number> tmp12;
  TNode<Number> tmp13;
  TNode<Number> tmp14;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp12 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{tmp6}, TNode<Number>{tmp9});
    tmp13 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp14 = Max_0(state_, TNode<Number>{tmp12}, TNode<Number>{tmp13});
    ca_.Goto(&block9, tmp14);
  }

  TNode<Number> tmp15;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp15 = Min_0(state_, TNode<Number>{tmp9}, TNode<Number>{tmp6});
    ca_.Goto(&block9, tmp15);
  }

  TNode<Number> phi_bb9_9;
  TNode<IntPtrT> tmp16;
  TNode<Object> tmp17;
  TNode<Oddball> tmp18;
  TNode<BoolT> tmp19;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_9);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp17 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp16});
    tmp18 = Undefined_0(state_);
    tmp19 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp17}, TNode<HeapObject>{tmp18});
    ca_.Branch(tmp19, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block13, tmp6);
  }

  TNode<Number> tmp20;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp20 = ToInteger_Inline_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp17});
    ca_.Goto(&block13, tmp20);
  }

  TNode<Number> phi_bb13_11;
  TNode<Number> tmp21;
  TNode<BoolT> tmp22;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_11);
    tmp21 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp22 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb13_11}, TNode<Number>{tmp21});
    ca_.Branch(tmp22, &block15, std::vector<Node*>{}, &block16, std::vector<Node*>{});
  }

  TNode<Number> tmp23;
  TNode<Number> tmp24;
  TNode<Number> tmp25;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp23 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{tmp6}, TNode<Number>{phi_bb13_11});
    tmp24 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp25 = Max_0(state_, TNode<Number>{tmp23}, TNode<Number>{tmp24});
    ca_.Goto(&block17, tmp25);
  }

  TNode<Number> tmp26;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp26 = Min_0(state_, TNode<Number>{phi_bb13_11}, TNode<Number>{tmp6});
    ca_.Goto(&block17, tmp26);
  }

  TNode<Number> phi_bb17_12;
  TNode<Number> tmp27;
  TNode<Number> tmp28;
  TNode<Number> tmp29;
  TNode<JSArray> tmp30;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_12);
    tmp27 = CodeStubAssembler(state_).NumberSub(TNode<Number>{phi_bb17_12}, TNode<Number>{phi_bb9_9});
    tmp28 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp29 = Max_0(state_, TNode<Number>{tmp27}, TNode<Number>{tmp28});
    compiler::CodeAssemblerLabel label31(&ca_);
    tmp30 = HandleFastSlice_0(state_, TNode<NativeContext>{parameter0}, TNode<Object>{tmp5}, TNode<Number>{phi_bb9_9}, TNode<Number>{tmp29}, &label31);
    ca_.Goto(&block45);
    if (label31.is_used()) {
      ca_.Bind(&label31);
      ca_.Goto(&block46);
    }
  }

  TNode<JSReceiver> tmp32;
  TNode<Number> tmp33;
  if (block46.is_used()) {
    ca_.Bind(&block46);
    tmp32 = CodeStubAssembler(state_).ArraySpeciesCreate(TNode<Context>{parameter0}, TNode<Object>{tmp5}, TNode<Number>{tmp29});
    tmp33 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    ca_.Goto(&block49, phi_bb9_9, tmp33);
  }

  if (block45.is_used()) {
    ca_.Bind(&block45);
    arguments.PopAndReturn(tmp30);
  }

  TNode<Number> phi_bb49_9;
  TNode<Number> phi_bb49_15;
  TNode<BoolT> tmp34;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_9, &phi_bb49_15);
    tmp34 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb49_9}, TNode<Number>{phi_bb17_12});
    ca_.Branch(tmp34, &block47, std::vector<Node*>{phi_bb49_9, phi_bb49_15}, &block48, std::vector<Node*>{phi_bb49_9, phi_bb49_15});
  }

  TNode<Number> phi_bb47_9;
  TNode<Number> phi_bb47_15;
  TNode<Oddball> tmp35;
  TNode<Oddball> tmp36;
  TNode<BoolT> tmp37;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_9, &phi_bb47_15);
    tmp35 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kHasProperty, parameter0, tmp5, phi_bb47_9));
    tmp36 = True_0(state_);
    tmp37 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp35}, TNode<HeapObject>{tmp36});
    ca_.Branch(tmp37, &block50, std::vector<Node*>{phi_bb47_9, phi_bb47_15, phi_bb47_9}, &block51, std::vector<Node*>{phi_bb47_9, phi_bb47_15, phi_bb47_9});
  }

  TNode<Number> phi_bb50_9;
  TNode<Number> phi_bb50_15;
  TNode<Number> phi_bb50_16;
  TNode<Object> tmp38;
  TNode<Object> tmp39;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_9, &phi_bb50_15, &phi_bb50_16);
    tmp38 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<Object>{tmp5}, TNode<Object>{phi_bb50_16});
    tmp39 = CodeStubAssembler(state_).CallBuiltin(Builtins::kFastCreateDataProperty, parameter0, tmp32, phi_bb50_15, tmp38);
    ca_.Goto(&block51, phi_bb50_9, phi_bb50_15, phi_bb50_16);
  }

  TNode<Number> phi_bb51_9;
  TNode<Number> phi_bb51_15;
  TNode<Number> phi_bb51_16;
  TNode<Number> tmp40;
  TNode<Number> tmp41;
  TNode<Number> tmp42;
  TNode<Number> tmp43;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_9, &phi_bb51_15, &phi_bb51_16);
    tmp40 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp41 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb51_9}, TNode<Number>{tmp40});
    tmp42 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp43 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb51_15}, TNode<Number>{tmp42});
    ca_.Goto(&block49, tmp41, tmp43);
  }

  TNode<Number> phi_bb48_9;
  TNode<Number> phi_bb48_15;
  TNode<String> tmp44;
  TNode<Object> tmp45;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_9, &phi_bb48_15);
    tmp44 = kLengthString_0(state_);
    tmp45 = CodeStubAssembler(state_).CallBuiltin(Builtins::kSetProperty, parameter0, tmp32, tmp44, phi_bb48_15);
    arguments.PopAndReturn(tmp32);
  }
}

TNode<Object> UnsafeCast_JSReceiver_OR_Undefined_OR_Null_OR_False_OR_True_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_Smi_OR_TheHole_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Object> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Object>{p_o});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<Object>{tmp0};
}

TNode<JSArray> Cast_FastJSArrayForCopy_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<JSArray> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_FastJSArrayForCopy_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<JSArray>{tmp2};
}

TNode<JSArgumentsObject> Cast_JSStrictArgumentsObject_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<JSArgumentsObject> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_JSStrictArgumentsObject_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<JSArgumentsObject>{tmp2};
}

TNode<JSArgumentsObject> Cast_JSSloppyArgumentsObject_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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

  TNode<JSArgumentsObject> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_JSSloppyArgumentsObject_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{tmp0}, &label3);
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
  return TNode<JSArgumentsObject>{tmp2};
}

}  // namespace internal
}  // namespace v8

