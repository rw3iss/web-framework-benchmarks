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

TNode<Smi> LoadElement_FastPackedSmiElements_Smi_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FixedArray> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<Smi> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<BoolT> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{p_elements});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp4 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp3});
    tmp5 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp4});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_index});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp5});
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
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_Object_0(state_, TNode<HeapObject>{tmp0}, TNode<IntPtrT>{tmp12}).Flatten();
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

TNode<Object> LoadElement_FastPackedObjectElements_JSAny_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FixedArray> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<Smi> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<BoolT> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{p_elements});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp4 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp3});
    tmp5 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp4});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_index});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp5});
    tmp9 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp7}, TNode<UintPtrT>{tmp8});
    ca_.Branch(tmp9, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<HeapObject> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Object> tmp15;
  TNode<Object> tmp16;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp11 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp10});
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_Object_0(state_, TNode<HeapObject>{tmp0}, TNode<IntPtrT>{tmp12}).Flatten();
    tmp15 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp13, tmp14});
    tmp16 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp15});
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
  return TNode<Object>{tmp16};
}

TNode<Float64T> LoadElement_FastPackedDoubleElements_float64_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FixedDoubleArray> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<Smi> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<BoolT> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<Object>{p_elements});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp4 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp3});
    tmp5 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp4});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_index});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp5});
    tmp9 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp7}, TNode<UintPtrT>{tmp8});
    ca_.Branch(tmp9, &block8, std::vector<Node*>{}, &block9, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<HeapObject> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<BoolT> tmp15;
  TNode<Float64T> tmp16;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, kDoubleSize);
    tmp11 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp10});
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_float64_or_hole_0(state_, TNode<HeapObject>{tmp0}, TNode<IntPtrT>{tmp12}).Flatten();
    std::tie(tmp15, tmp16) = LoadFloat64OrHole_0(state_, TorqueStructReference_float64_or_hole_0{TNode<HeapObject>{tmp13}, TNode<IntPtrT>{tmp14}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Branch(tmp15, &block12, std::vector<Node*>{}, &block13, std::vector<Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block14);
  }

    ca_.Bind(&block14);
  return TNode<Float64T>{tmp16};
}

void StoreElement_FastPackedSmiElements_Smi_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_index, TNode<Smi> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FixedArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{p_elements});
    CodeStubAssembler(state_).StoreFixedArrayElement(TNode<FixedArray>{tmp0}, TNode<Smi>{p_index}, TNode<Smi>{p_value}, SKIP_WRITE_BARRIER);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

void StoreElement_FastPackedObjectElements_JSAny_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_index, TNode<Object> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FixedArray> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<Smi> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<BoolT> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{p_elements});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp4 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp0, tmp3});
    tmp5 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp4});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_index});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp5});
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
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_Object_0(state_, TNode<HeapObject>{tmp0}, TNode<IntPtrT>{tmp12}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp13, tmp14}, p_value);
    ca_.Goto(&block9);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block9);
}

void StoreElement_FastPackedDoubleElements_float64_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_index, TNode<Float64T> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FixedDoubleArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<Object>{p_elements});
    CodeStubAssembler(state_).StoreFixedDoubleArrayElementSmi(TNode<FixedDoubleArray>{tmp0}, TNode<Smi>{p_index}, TNode<Float64T>{p_value});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TNode<Object> GenericArrayReverse_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_receiver) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, Object> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, Object> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, BoolT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, BoolT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number, BoolT> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<Number> tmp1;
  TNode<Number> tmp2;
  TNode<Number> tmp3;
  TNode<Number> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{p_context}, TNode<Object>{p_receiver});
    tmp1 = GetLengthProperty_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp0});
    tmp2 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp3 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp4 = CodeStubAssembler(state_).NumberSub(TNode<Number>{tmp1}, TNode<Number>{tmp3});
    ca_.Goto(&block4, tmp2, tmp4);
  }

  TNode<Number> phi_bb4_4;
  TNode<Number> phi_bb4_5;
  TNode<BoolT> tmp5;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_4, &phi_bb4_5);
    tmp5 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb4_4}, TNode<Number>{phi_bb4_5});
    ca_.Branch(tmp5, &block2, std::vector<Node*>{phi_bb4_4, phi_bb4_5}, &block3, std::vector<Node*>{phi_bb4_4, phi_bb4_5});
  }

  TNode<Number> phi_bb2_4;
  TNode<Number> phi_bb2_5;
  TNode<Oddball> tmp6;
  TNode<Oddball> tmp7;
  TNode<Oddball> tmp8;
  TNode<Oddball> tmp9;
  TNode<BoolT> tmp10;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4, &phi_bb2_5);
    tmp6 = Undefined_0(state_);
    tmp7 = Undefined_0(state_);
    tmp8 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kHasProperty, p_context, tmp0, phi_bb2_4));
    tmp9 = True_0(state_);
    tmp10 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp8}, TNode<HeapObject>{tmp9});
    ca_.Branch(tmp10, &block5, std::vector<Node*>{phi_bb2_4, phi_bb2_5}, &block6, std::vector<Node*>{phi_bb2_4, phi_bb2_5, tmp6});
  }

  TNode<Number> phi_bb5_4;
  TNode<Number> phi_bb5_5;
  TNode<Object> tmp11;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_4, &phi_bb5_5);
    tmp11 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<Object>{tmp0}, TNode<Object>{phi_bb5_4});
    ca_.Goto(&block6, phi_bb5_4, phi_bb5_5, tmp11);
  }

  TNode<Number> phi_bb6_4;
  TNode<Number> phi_bb6_5;
  TNode<Object> phi_bb6_6;
  TNode<Oddball> tmp12;
  TNode<Oddball> tmp13;
  TNode<BoolT> tmp14;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_4, &phi_bb6_5, &phi_bb6_6);
    tmp12 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kHasProperty, p_context, tmp0, phi_bb6_5));
    tmp13 = True_0(state_);
    tmp14 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp12}, TNode<HeapObject>{tmp13});
    ca_.Branch(tmp14, &block7, std::vector<Node*>{phi_bb6_4, phi_bb6_5}, &block8, std::vector<Node*>{phi_bb6_4, phi_bb6_5, tmp7});
  }

  TNode<Number> phi_bb7_4;
  TNode<Number> phi_bb7_5;
  TNode<Object> tmp15;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_4, &phi_bb7_5);
    tmp15 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<Object>{tmp0}, TNode<Object>{phi_bb7_5});
    ca_.Goto(&block8, phi_bb7_4, phi_bb7_5, tmp15);
  }

  TNode<Number> phi_bb8_4;
  TNode<Number> phi_bb8_5;
  TNode<Object> phi_bb8_7;
  TNode<Oddball> tmp16;
  TNode<BoolT> tmp17;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_4, &phi_bb8_5, &phi_bb8_7);
    tmp16 = True_0(state_);
    tmp17 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp8}, TNode<HeapObject>{tmp16});
    ca_.Branch(tmp17, &block11, std::vector<Node*>{phi_bb8_4, phi_bb8_5}, &block12, std::vector<Node*>{phi_bb8_4, phi_bb8_5});
  }

  TNode<Number> phi_bb11_4;
  TNode<Number> phi_bb11_5;
  TNode<Oddball> tmp18;
  TNode<BoolT> tmp19;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_4, &phi_bb11_5);
    tmp18 = True_0(state_);
    tmp19 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp12}, TNode<HeapObject>{tmp18});
    ca_.Goto(&block13, phi_bb11_4, phi_bb11_5, tmp19);
  }

  TNode<Number> phi_bb12_4;
  TNode<Number> phi_bb12_5;
  TNode<BoolT> tmp20;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_4, &phi_bb12_5);
    tmp20 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block13, phi_bb12_4, phi_bb12_5, tmp20);
  }

  TNode<Number> phi_bb13_4;
  TNode<Number> phi_bb13_5;
  TNode<BoolT> phi_bb13_11;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_4, &phi_bb13_5, &phi_bb13_11);
    ca_.Branch(phi_bb13_11, &block9, std::vector<Node*>{phi_bb13_4, phi_bb13_5}, &block10, std::vector<Node*>{phi_bb13_4, phi_bb13_5});
  }

  TNode<Number> phi_bb9_4;
  TNode<Number> phi_bb9_5;
  TNode<Object> tmp21;
  TNode<Object> tmp22;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_4, &phi_bb9_5);
    tmp21 = CodeStubAssembler(state_).CallBuiltin(Builtins::kSetProperty, p_context, tmp0, phi_bb9_4, phi_bb8_7);
    tmp22 = CodeStubAssembler(state_).CallBuiltin(Builtins::kSetProperty, p_context, tmp0, phi_bb9_5, phi_bb6_6);
    ca_.Goto(&block14, phi_bb9_4, phi_bb9_5);
  }

  TNode<Number> phi_bb10_4;
  TNode<Number> phi_bb10_5;
  TNode<Oddball> tmp23;
  TNode<BoolT> tmp24;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_4, &phi_bb10_5);
    tmp23 = False_0(state_);
    tmp24 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp8}, TNode<HeapObject>{tmp23});
    ca_.Branch(tmp24, &block17, std::vector<Node*>{phi_bb10_4, phi_bb10_5}, &block18, std::vector<Node*>{phi_bb10_4, phi_bb10_5});
  }

  TNode<Number> phi_bb17_4;
  TNode<Number> phi_bb17_5;
  TNode<Oddball> tmp25;
  TNode<BoolT> tmp26;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_4, &phi_bb17_5);
    tmp25 = True_0(state_);
    tmp26 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp12}, TNode<HeapObject>{tmp25});
    ca_.Goto(&block19, phi_bb17_4, phi_bb17_5, tmp26);
  }

  TNode<Number> phi_bb18_4;
  TNode<Number> phi_bb18_5;
  TNode<BoolT> tmp27;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_4, &phi_bb18_5);
    tmp27 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block19, phi_bb18_4, phi_bb18_5, tmp27);
  }

  TNode<Number> phi_bb19_4;
  TNode<Number> phi_bb19_5;
  TNode<BoolT> phi_bb19_11;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_4, &phi_bb19_5, &phi_bb19_11);
    ca_.Branch(phi_bb19_11, &block15, std::vector<Node*>{phi_bb19_4, phi_bb19_5}, &block16, std::vector<Node*>{phi_bb19_4, phi_bb19_5});
  }

  TNode<Number> phi_bb15_4;
  TNode<Number> phi_bb15_5;
  TNode<Object> tmp28;
  TNode<Smi> tmp29;
  TNode<Oddball> tmp30;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_4, &phi_bb15_5);
    tmp28 = CodeStubAssembler(state_).CallBuiltin(Builtins::kSetProperty, p_context, tmp0, phi_bb15_4, phi_bb8_7);
    tmp29 = FromConstexpr_LanguageModeSmi_constexpr_LanguageMode_0(state_, LanguageMode::kStrict);
    tmp30 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kDeleteProperty, p_context, tmp0, phi_bb15_5, tmp29));
    ca_.Goto(&block20, phi_bb15_4, phi_bb15_5);
  }

  TNode<Number> phi_bb16_4;
  TNode<Number> phi_bb16_5;
  TNode<Oddball> tmp31;
  TNode<BoolT> tmp32;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_4, &phi_bb16_5);
    tmp31 = True_0(state_);
    tmp32 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp8}, TNode<HeapObject>{tmp31});
    ca_.Branch(tmp32, &block23, std::vector<Node*>{phi_bb16_4, phi_bb16_5}, &block24, std::vector<Node*>{phi_bb16_4, phi_bb16_5});
  }

  TNode<Number> phi_bb23_4;
  TNode<Number> phi_bb23_5;
  TNode<Oddball> tmp33;
  TNode<BoolT> tmp34;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_4, &phi_bb23_5);
    tmp33 = False_0(state_);
    tmp34 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp12}, TNode<HeapObject>{tmp33});
    ca_.Goto(&block25, phi_bb23_4, phi_bb23_5, tmp34);
  }

  TNode<Number> phi_bb24_4;
  TNode<Number> phi_bb24_5;
  TNode<BoolT> tmp35;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_4, &phi_bb24_5);
    tmp35 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block25, phi_bb24_4, phi_bb24_5, tmp35);
  }

  TNode<Number> phi_bb25_4;
  TNode<Number> phi_bb25_5;
  TNode<BoolT> phi_bb25_11;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_4, &phi_bb25_5, &phi_bb25_11);
    ca_.Branch(phi_bb25_11, &block21, std::vector<Node*>{phi_bb25_4, phi_bb25_5}, &block22, std::vector<Node*>{phi_bb25_4, phi_bb25_5});
  }

  TNode<Number> phi_bb21_4;
  TNode<Number> phi_bb21_5;
  TNode<Smi> tmp36;
  TNode<Oddball> tmp37;
  TNode<Object> tmp38;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_4, &phi_bb21_5);
    tmp36 = FromConstexpr_LanguageModeSmi_constexpr_LanguageMode_0(state_, LanguageMode::kStrict);
    tmp37 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kDeleteProperty, p_context, tmp0, phi_bb21_4, tmp36));
    tmp38 = CodeStubAssembler(state_).CallBuiltin(Builtins::kSetProperty, p_context, tmp0, phi_bb21_5, phi_bb6_6);
    ca_.Goto(&block22, phi_bb21_4, phi_bb21_5);
  }

  TNode<Number> phi_bb22_4;
  TNode<Number> phi_bb22_5;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_4, &phi_bb22_5);
    ca_.Goto(&block20, phi_bb22_4, phi_bb22_5);
  }

  TNode<Number> phi_bb20_4;
  TNode<Number> phi_bb20_5;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_4, &phi_bb20_5);
    ca_.Goto(&block14, phi_bb20_4, phi_bb20_5);
  }

  TNode<Number> phi_bb14_4;
  TNode<Number> phi_bb14_5;
  TNode<Number> tmp39;
  TNode<Number> tmp40;
  TNode<Number> tmp41;
  TNode<Number> tmp42;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_4, &phi_bb14_5);
    tmp39 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp40 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb14_4}, TNode<Number>{tmp39});
    tmp41 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp42 = CodeStubAssembler(state_).NumberSub(TNode<Number>{phi_bb14_5}, TNode<Number>{tmp41});
    ca_.Goto(&block4, tmp40, tmp42);
  }

  TNode<Number> phi_bb3_4;
  TNode<Number> phi_bb3_5;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_4, &phi_bb3_5);
    ca_.Goto(&block26);
  }

    ca_.Bind(&block26);
  return TNode<Object>{tmp0};
}

void TryFastPackedArrayReverse_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_receiver, compiler::CodeAssemblerLabel* label_Slow) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FastJSArray_1(state_, TNode<Context>{p_context}, TNode<Object>{p_receiver}, &label1);
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

  TNode<IntPtrT> tmp2;
  TNode<Map> tmp3;
  TNode<Int32T> tmp4;
  TNode<Int32T> tmp5;
  TNode<BoolT> tmp6;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp3 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp0, tmp2});
    tmp4 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp3});
    tmp5 = FromConstexpr_ElementsKind_constexpr_PACKED_SMI_ELEMENTS_0(state_, ElementsKind::PACKED_SMI_ELEMENTS);
    tmp6 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp4}, TNode<Int32T>{tmp5});
    ca_.Branch(tmp6, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp7;
  TNode<FixedArrayBase> tmp8;
  TNode<Smi> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    EnsureWriteableFastElements_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp0});
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp8 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp0, tmp7});
    tmp9 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp0});
    FastPackedArrayReverse_FastPackedSmiElements_Smi_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{tmp8}, TNode<Smi>{tmp9});
    ca_.Goto(&block7);
  }

  TNode<Int32T> tmp10;
  TNode<BoolT> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = FromConstexpr_ElementsKind_constexpr_PACKED_ELEMENTS_0(state_, ElementsKind::PACKED_ELEMENTS);
    tmp11 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp4}, TNode<Int32T>{tmp10});
    ca_.Branch(tmp11, &block8, std::vector<Node*>{}, &block9, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp12;
  TNode<FixedArrayBase> tmp13;
  TNode<Smi> tmp14;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    EnsureWriteableFastElements_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp0});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp13 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp0, tmp12});
    tmp14 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp0});
    FastPackedArrayReverse_FastPackedObjectElements_JSAny_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{tmp13}, TNode<Smi>{tmp14});
    ca_.Goto(&block10);
  }

  TNode<Int32T> tmp15;
  TNode<BoolT> tmp16;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp15 = FromConstexpr_ElementsKind_constexpr_PACKED_DOUBLE_ELEMENTS_0(state_, ElementsKind::PACKED_DOUBLE_ELEMENTS);
    tmp16 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp4}, TNode<Int32T>{tmp15});
    ca_.Branch(tmp16, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp17;
  TNode<FixedArrayBase> tmp18;
  TNode<Smi> tmp19;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp18 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp0, tmp17});
    tmp19 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp0});
    FastPackedArrayReverse_FastPackedDoubleElements_float64_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{tmp18}, TNode<Smi>{tmp19});
    ca_.Goto(&block10);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block1);
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block7);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block14);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Slow);
  }

    ca_.Bind(&block14);
}

TF_BUILTIN(ArrayPrototypeReverse, CodeStubAssembler) {
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
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label0(&ca_);
    TryFastPackedArrayReverse_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label0);
    ca_.Goto(&block3);
    if (label0.is_used()) {
      ca_.Bind(&label0);
      ca_.Goto(&block4);
    }
  }

  TNode<Object> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = GenericArrayReverse_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    arguments.PopAndReturn(tmp1);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    arguments.PopAndReturn(parameter1);
  }
}

TNode<Smi> UnsafeCast_Smi_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<Smi>{tmp0};
}

TNode<JSArray> Cast_FastJSArray_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
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
    tmp2 = Cast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{tmp0}, &label3);
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

void FastPackedArrayReverse_FastPackedSmiElements_Smi_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<Smi> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp1 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp2 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_length}, TNode<Smi>{tmp1});
    ca_.Goto(&block4, tmp0, tmp2);
  }

  TNode<Smi> phi_bb4_3;
  TNode<Smi> phi_bb4_4;
  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_3, &phi_bb4_4);
    tmp3 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb4_3}, TNode<Smi>{phi_bb4_4});
    ca_.Branch(tmp3, &block2, std::vector<Node*>{phi_bb4_3, phi_bb4_4}, &block3, std::vector<Node*>{phi_bb4_3, phi_bb4_4});
  }

  TNode<Smi> phi_bb2_3;
  TNode<Smi> phi_bb2_4;
  TNode<Smi> tmp4;
  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<Smi> tmp9;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3, &phi_bb2_4);
    tmp4 = LoadElement_FastPackedSmiElements_Smi_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_3});
    tmp5 = LoadElement_FastPackedSmiElements_Smi_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_4});
    StoreElement_FastPackedSmiElements_Smi_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_3}, TNode<Smi>{tmp5});
    StoreElement_FastPackedSmiElements_Smi_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_4}, TNode<Smi>{tmp4});
    tmp6 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp7 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb2_3}, TNode<Smi>{tmp6});
    tmp8 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp9 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb2_4}, TNode<Smi>{tmp8});
    ca_.Goto(&block4, tmp7, tmp9);
  }

  TNode<Smi> phi_bb3_3;
  TNode<Smi> phi_bb3_4;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_3, &phi_bb3_4);
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
}

void FastPackedArrayReverse_FastPackedObjectElements_JSAny_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<Smi> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp1 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp2 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_length}, TNode<Smi>{tmp1});
    ca_.Goto(&block4, tmp0, tmp2);
  }

  TNode<Smi> phi_bb4_3;
  TNode<Smi> phi_bb4_4;
  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_3, &phi_bb4_4);
    tmp3 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb4_3}, TNode<Smi>{phi_bb4_4});
    ca_.Branch(tmp3, &block2, std::vector<Node*>{phi_bb4_3, phi_bb4_4}, &block3, std::vector<Node*>{phi_bb4_3, phi_bb4_4});
  }

  TNode<Smi> phi_bb2_3;
  TNode<Smi> phi_bb2_4;
  TNode<Object> tmp4;
  TNode<Object> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<Smi> tmp9;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3, &phi_bb2_4);
    tmp4 = LoadElement_FastPackedObjectElements_JSAny_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_3});
    tmp5 = LoadElement_FastPackedObjectElements_JSAny_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_4});
    StoreElement_FastPackedObjectElements_JSAny_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_3}, TNode<Object>{tmp5});
    StoreElement_FastPackedObjectElements_JSAny_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_4}, TNode<Object>{tmp4});
    tmp6 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp7 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb2_3}, TNode<Smi>{tmp6});
    tmp8 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp9 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb2_4}, TNode<Smi>{tmp8});
    ca_.Goto(&block4, tmp7, tmp9);
  }

  TNode<Smi> phi_bb3_3;
  TNode<Smi> phi_bb3_4;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_3, &phi_bb3_4);
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
}

void FastPackedArrayReverse_FastPackedDoubleElements_float64_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<Smi> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp1 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp2 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_length}, TNode<Smi>{tmp1});
    ca_.Goto(&block4, tmp0, tmp2);
  }

  TNode<Smi> phi_bb4_3;
  TNode<Smi> phi_bb4_4;
  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_3, &phi_bb4_4);
    tmp3 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb4_3}, TNode<Smi>{phi_bb4_4});
    ca_.Branch(tmp3, &block2, std::vector<Node*>{phi_bb4_3, phi_bb4_4}, &block3, std::vector<Node*>{phi_bb4_3, phi_bb4_4});
  }

  TNode<Smi> phi_bb2_3;
  TNode<Smi> phi_bb2_4;
  TNode<Float64T> tmp4;
  TNode<Float64T> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<Smi> tmp9;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3, &phi_bb2_4);
    tmp4 = LoadElement_FastPackedDoubleElements_float64_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_3});
    tmp5 = LoadElement_FastPackedDoubleElements_float64_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_4});
    StoreElement_FastPackedDoubleElements_float64_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_3}, TNode<Float64T>{tmp5});
    StoreElement_FastPackedDoubleElements_float64_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{p_elements}, TNode<Smi>{phi_bb2_4}, TNode<Float64T>{tmp4});
    tmp6 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp7 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb2_3}, TNode<Smi>{tmp6});
    tmp8 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp9 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb2_4}, TNode<Smi>{tmp8});
    ca_.Goto(&block4, tmp7, tmp9);
  }

  TNode<Smi> phi_bb3_3;
  TNode<Smi> phi_bb3_4;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_3, &phi_bb3_4);
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
}

}  // namespace internal
}  // namespace v8

