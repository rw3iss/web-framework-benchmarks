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

TNode<Object> LoadWithHoleCheck_FixedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_index, compiler::CodeAssemblerLabel* label_IfHole) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
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
    ca_.Branch(tmp9, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<HeapObject> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Object> tmp15;
  TNode<Oddball> tmp16;
  TNode<BoolT> tmp17;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp11 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp10});
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_Object_0(state_, TNode<HeapObject>{tmp0}, TNode<IntPtrT>{tmp12}).Flatten();
    tmp15 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp13, tmp14});
    tmp16 = TheHole_0(state_);
    tmp17 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp15}, TNode<HeapObject>{tmp16});
    ca_.Branch(tmp17, &block10, std::vector<Node*>{}, &block11, std::vector<Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(label_IfHole);
  }

  TNode<Object> tmp18;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp18 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp15});
    ca_.Goto(&block12);
  }

    ca_.Bind(&block12);
  return TNode<Object>{tmp18};
}

TNode<Object> LoadWithHoleCheck_FixedDoubleArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArrayBase> p_elements, TNode<Smi> p_index, compiler::CodeAssemblerLabel* label_IfHole) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
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
    ca_.Branch(tmp9, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<HeapObject> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<BoolT> tmp15;
  TNode<Float64T> tmp16;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, kDoubleSize);
    tmp11 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp10});
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_float64_or_hole_0(state_, TNode<HeapObject>{tmp0}, TNode<IntPtrT>{tmp12}).Flatten();
    std::tie(tmp15, tmp16) = LoadFloat64OrHole_0(state_, TorqueStructReference_float64_or_hole_0{TNode<HeapObject>{tmp13}, TNode<IntPtrT>{tmp14}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Branch(tmp15, &block11, std::vector<Node*>{}, &block12, std::vector<Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).Unreachable();
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(label_IfHole);
  }

  TNode<HeapNumber> tmp17;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp17 = CodeStubAssembler(state_).AllocateHeapNumberWithValue(TNode<Float64T>{tmp16});
    ca_.Goto(&block13);
  }

    ca_.Bind(&block13);
  return TNode<Object>{tmp17};
}

TNode<Number> GetFromIndex_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Number> p_length, TorqueStructArguments p_arguments) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 2);
    tmp1 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{p_arguments.length}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  TNode<Number> tmp2;
  TNode<Number> tmp3;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp3 = CodeStubAssembler(state_).NumberSub(TNode<Number>{p_length}, TNode<Number>{tmp2});
    ca_.Goto(&block4, tmp3);
  }

  TNode<IntPtrT> tmp4;
  TNode<Object> tmp5;
  TNode<Number> tmp6;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp5 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{p_arguments.frame}, TNode<RawPtrT>{p_arguments.base}, TNode<IntPtrT>{p_arguments.length}}, TNode<IntPtrT>{tmp4});
    tmp6 = ToInteger_Inline_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp5});
    ca_.Goto(&block4, tmp6);
  }

  TNode<Number> phi_bb4_5;
  TNode<Smi> tmp7;
  TNode<Number> tmp8;
  TNode<BoolT> tmp9;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_5);
    tmp7 = CodeStubAssembler(state_).SmiConstant(0);
    tmp8 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp9 = NumberIsGreaterThanOrEqual_0(state_, TNode<Number>{phi_bb4_5}, TNode<Number>{tmp8});
    ca_.Branch(tmp9, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  TNode<Number> tmp10;
  TNode<Number> tmp11;
  TNode<Number> tmp12;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp11 = CodeStubAssembler(state_).NumberSub(TNode<Number>{p_length}, TNode<Number>{tmp10});
    tmp12 = Min_0(state_, TNode<Number>{phi_bb4_5}, TNode<Number>{tmp11});
    ca_.Goto(&block8, tmp12);
  }

  TNode<Number> tmp13;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp13 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{p_length}, TNode<Number>{phi_bb4_5});
    ca_.Goto(&block8, tmp13);
  }

  TNode<Number> phi_bb8_6;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_6);
    ca_.Goto(&block9);
  }

    ca_.Bind(&block9);
  return TNode<Number>{phi_bb8_6};
}

TNode<Object> TryFastArrayLastIndexOf_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver, TNode<Object> p_searchElement, TNode<Number> p_from, compiler::CodeAssemblerLabel* label_Slow) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{p_receiver}, &label1);
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
  TNode<Smi> tmp3;
  TNode<BoolT> tmp4;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp0});
    tmp3 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp4 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp2}, TNode<Smi>{tmp3});
    ca_.Branch(tmp4, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  TNode<Smi> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp5 = CodeStubAssembler(state_).SmiConstant(-1);
    ca_.Goto(&block2, tmp5);
  }

  TNode<Smi> tmp6;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_Smi_0(state_, TNode<Object>{p_from}, &label7);
    ca_.Goto(&block7);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp8;
  TNode<Map> tmp9;
  TNode<Int32T> tmp10;
  TNode<BoolT> tmp11;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp9 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp0, tmp8});
    tmp10 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp9});
    tmp11 = CodeStubAssembler(state_).IsFastSmiOrTaggedElementsKind(TNode<Int32T>{tmp10});
    ca_.Branch(tmp11, &block9, std::vector<Node*>{}, &block10, std::vector<Node*>{});
  }

  TNode<Smi> tmp12;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp12 = FastArrayLastIndexOf_FixedArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp0}, TNode<Smi>{tmp6}, TNode<Object>{p_searchElement});
    ca_.Goto(&block2, tmp12);
  }

  TNode<Smi> tmp13;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp13 = FastArrayLastIndexOf_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp0}, TNode<Smi>{tmp6}, TNode<Object>{p_searchElement});
    ca_.Goto(&block2, tmp13);
  }

  TNode<Object> phi_bb2_4;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4);
    ca_.Goto(&block15, phi_bb2_4);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Slow);
  }

  TNode<Object> phi_bb15_4;
    ca_.Bind(&block15, &phi_bb15_4);
  return TNode<Object>{phi_bb15_4};
}

TNode<Object> GenericArrayLastIndexOf_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_object, TNode<Object> p_searchElement, TNode<Number> p_from) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block4, p_from);
  }

  TNode<Number> phi_bb4_4;
  TNode<Number> tmp0;
  TNode<BoolT> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_4);
    tmp0 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp1 = NumberIsGreaterThanOrEqual_0(state_, TNode<Number>{phi_bb4_4}, TNode<Number>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<Node*>{phi_bb4_4}, &block3, std::vector<Node*>{phi_bb4_4});
  }

  TNode<Number> phi_bb2_4;
  TNode<Oddball> tmp2;
  TNode<Oddball> tmp3;
  TNode<BoolT> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4);
    tmp2 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kHasProperty, p_context, p_object, phi_bb2_4));
    tmp3 = True_0(state_);
    tmp4 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp2}, TNode<HeapObject>{tmp3});
    ca_.Branch(tmp4, &block5, std::vector<Node*>{phi_bb2_4}, &block6, std::vector<Node*>{phi_bb2_4});
  }

  TNode<Number> phi_bb5_4;
  TNode<Object> tmp5;
  TNode<Oddball> tmp6;
  TNode<Oddball> tmp7;
  TNode<BoolT> tmp8;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_4);
    tmp5 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<Object>{p_object}, TNode<Object>{phi_bb5_4});
    tmp6 = CodeStubAssembler(state_).StrictEqual(TNode<Object>{p_searchElement}, TNode<Object>{tmp5});
    tmp7 = True_0(state_);
    tmp8 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp6}, TNode<HeapObject>{tmp7});
    ca_.Branch(tmp8, &block7, std::vector<Node*>{phi_bb5_4}, &block8, std::vector<Node*>{phi_bb5_4});
  }

  TNode<Number> phi_bb7_4;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_4);
    ca_.Goto(&block1, phi_bb7_4);
  }

  TNode<Number> phi_bb8_4;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_4);
    ca_.Goto(&block6, phi_bb8_4);
  }

  TNode<Number> phi_bb6_4;
  TNode<Number> tmp9;
  TNode<Number> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_4);
    tmp9 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp10 = CodeStubAssembler(state_).NumberSub(TNode<Number>{phi_bb6_4}, TNode<Number>{tmp9});
    ca_.Goto(&block4, tmp10);
  }

  TNode<Number> phi_bb3_4;
  TNode<Smi> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_4);
    tmp11 = CodeStubAssembler(state_).SmiConstant(-1);
    ca_.Goto(&block1, tmp11);
  }

  TNode<Object> phi_bb1_4;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4);
    ca_.Goto(&block9, phi_bb1_4);
  }

  TNode<Object> phi_bb9_4;
    ca_.Bind(&block9, &phi_bb9_4);
  return TNode<Object>{phi_bb9_4};
}

TF_BUILTIN(ArrayPrototypeLastIndexOf, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<Number> tmp1;
  TNode<Smi> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp0});
    tmp2 = CodeStubAssembler(state_).SmiConstant(0);
    tmp3 = IsNumberEqual_0(state_, TNode<Number>{tmp1}, TNode<Number>{tmp2});
    ca_.Branch(tmp3, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  TNode<Smi> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp4 = CodeStubAssembler(state_).SmiConstant(-1);
    arguments.PopAndReturn(tmp4);
  }

  TNode<Number> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Object> tmp7;
  TNode<Object> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = GetFromIndex_0(state_, TNode<Context>{parameter0}, TNode<Number>{tmp1}, TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp7 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp6});
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = TryFastArrayLastIndexOf_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}, TNode<Object>{tmp7}, TNode<Number>{tmp5}, &label9);
    ca_.Goto(&block5);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block6);
    }
  }

  TNode<Object> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = GenericArrayLastIndexOf_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp0}, TNode<Object>{tmp7}, TNode<Number>{tmp5});
    arguments.PopAndReturn(tmp10);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    arguments.PopAndReturn(tmp8);
  }
}

TNode<Smi> FastArrayLastIndexOf_FixedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSArray> p_array, TNode<Smi> p_from, TNode<Object> p_searchElement) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArrayBase> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{p_array, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{p_from}, TNode<Smi>{tmp3});
    ca_.Branch(tmp4, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{p_from});
  }

  TNode<IntPtrT> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp6 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp5});
    tmp7 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp8 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp6}, TNode<Smi>{tmp7});
    ca_.Goto(&block3, tmp8);
  }

  TNode<Smi> phi_bb3_5;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_5);
    ca_.Goto(&block6, phi_bb3_5);
  }

  TNode<Smi> phi_bb6_5;
  TNode<Smi> tmp9;
  TNode<BoolT> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_5);
    tmp9 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp10 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb6_5}, TNode<Smi>{tmp9});
    ca_.Branch(tmp10, &block4, std::vector<Node*>{phi_bb6_5}, &block5, std::vector<Node*>{phi_bb6_5});
  }

  TNode<Smi> phi_bb4_5;
  TNode<Object> tmp11;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_5);
    compiler::CodeAssemblerLabel label12(&ca_);
    tmp11 = LoadWithHoleCheck_FixedArray_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{tmp1}, TNode<Smi>{phi_bb4_5}, &label12);
    ca_.Goto(&block9, phi_bb4_5, phi_bb4_5);
    if (label12.is_used()) {
      ca_.Bind(&label12);
      ca_.Goto(&block10, phi_bb4_5, phi_bb4_5);
    }
  }

  TNode<Smi> phi_bb10_5;
  TNode<Smi> phi_bb10_7;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_5, &phi_bb10_7);
    ca_.Goto(&block7, phi_bb10_5);
  }

  TNode<Smi> phi_bb9_5;
  TNode<Smi> phi_bb9_7;
  TNode<Oddball> tmp13;
  TNode<Oddball> tmp14;
  TNode<BoolT> tmp15;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_5, &phi_bb9_7);
    tmp13 = CodeStubAssembler(state_).StrictEqual(TNode<Object>{p_searchElement}, TNode<Object>{tmp11});
    tmp14 = True_0(state_);
    tmp15 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp13}, TNode<HeapObject>{tmp14});
    ca_.Branch(tmp15, &block11, std::vector<Node*>{phi_bb9_5}, &block12, std::vector<Node*>{phi_bb9_5});
  }

  TNode<Smi> phi_bb11_5;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_5);
    ca_.Goto(&block1, phi_bb11_5);
  }

  TNode<Smi> phi_bb12_5;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_5);
    ca_.Goto(&block7, phi_bb12_5);
  }

  TNode<Smi> phi_bb7_5;
  TNode<Smi> tmp16;
  TNode<Smi> tmp17;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_5);
    tmp16 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp17 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb7_5}, TNode<Smi>{tmp16});
    ca_.Goto(&block6, tmp17);
  }

  TNode<Smi> phi_bb5_5;
  TNode<Smi> tmp18;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_5);
    tmp18 = FromConstexpr_Smi_constexpr_int31_0(state_, -1);
    ca_.Goto(&block1, tmp18);
  }

  TNode<Smi> phi_bb1_4;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4);
    ca_.Goto(&block21, phi_bb1_4);
  }

  TNode<Smi> phi_bb21_4;
    ca_.Bind(&block21, &phi_bb21_4);
  return TNode<Smi>{phi_bb21_4};
}

TNode<Smi> FastArrayLastIndexOf_FixedDoubleArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSArray> p_array, TNode<Smi> p_from, TNode<Object> p_searchElement) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArrayBase> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{p_array, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp3 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{p_from}, TNode<Smi>{tmp3});
    ca_.Branch(tmp4, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{p_from});
  }

  TNode<IntPtrT> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp6 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp1, tmp5});
    tmp7 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp8 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp6}, TNode<Smi>{tmp7});
    ca_.Goto(&block3, tmp8);
  }

  TNode<Smi> phi_bb3_5;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_5);
    ca_.Goto(&block6, phi_bb3_5);
  }

  TNode<Smi> phi_bb6_5;
  TNode<Smi> tmp9;
  TNode<BoolT> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_5);
    tmp9 = FromConstexpr_Smi_constexpr_int31_0(state_, 0);
    tmp10 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb6_5}, TNode<Smi>{tmp9});
    ca_.Branch(tmp10, &block4, std::vector<Node*>{phi_bb6_5}, &block5, std::vector<Node*>{phi_bb6_5});
  }

  TNode<Smi> phi_bb4_5;
  TNode<Object> tmp11;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_5);
    compiler::CodeAssemblerLabel label12(&ca_);
    tmp11 = LoadWithHoleCheck_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<FixedArrayBase>{tmp1}, TNode<Smi>{phi_bb4_5}, &label12);
    ca_.Goto(&block9, phi_bb4_5, phi_bb4_5);
    if (label12.is_used()) {
      ca_.Bind(&label12);
      ca_.Goto(&block10, phi_bb4_5, phi_bb4_5);
    }
  }

  TNode<Smi> phi_bb10_5;
  TNode<Smi> phi_bb10_7;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_5, &phi_bb10_7);
    ca_.Goto(&block7, phi_bb10_5);
  }

  TNode<Smi> phi_bb9_5;
  TNode<Smi> phi_bb9_7;
  TNode<Oddball> tmp13;
  TNode<Oddball> tmp14;
  TNode<BoolT> tmp15;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_5, &phi_bb9_7);
    tmp13 = CodeStubAssembler(state_).StrictEqual(TNode<Object>{p_searchElement}, TNode<Object>{tmp11});
    tmp14 = True_0(state_);
    tmp15 = CodeStubAssembler(state_).TaggedEqual(TNode<HeapObject>{tmp13}, TNode<HeapObject>{tmp14});
    ca_.Branch(tmp15, &block11, std::vector<Node*>{phi_bb9_5}, &block12, std::vector<Node*>{phi_bb9_5});
  }

  TNode<Smi> phi_bb11_5;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_5);
    ca_.Goto(&block1, phi_bb11_5);
  }

  TNode<Smi> phi_bb12_5;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_5);
    ca_.Goto(&block7, phi_bb12_5);
  }

  TNode<Smi> phi_bb7_5;
  TNode<Smi> tmp16;
  TNode<Smi> tmp17;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_5);
    tmp16 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp17 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb7_5}, TNode<Smi>{tmp16});
    ca_.Goto(&block6, tmp17);
  }

  TNode<Smi> phi_bb5_5;
  TNode<Smi> tmp18;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_5);
    tmp18 = FromConstexpr_Smi_constexpr_int31_0(state_, -1);
    ca_.Goto(&block1, tmp18);
  }

  TNode<Smi> phi_bb1_4;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4);
    ca_.Goto(&block21, phi_bb1_4);
  }

  TNode<Smi> phi_bb21_4;
    ca_.Bind(&block21, &phi_bb21_4);
  return TNode<Smi>{phi_bb21_4};
}

TNode<BoolT> Is_FastJSArray_JSArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSArray> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{p_o}, &label1);
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

}  // namespace internal
}  // namespace v8

