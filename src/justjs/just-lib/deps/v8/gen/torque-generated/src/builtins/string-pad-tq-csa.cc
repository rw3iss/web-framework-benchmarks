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

int31_t kStringPadStart_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return 0;
}

int31_t kStringPadEnd_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return 1;
}

TNode<String> StringPad_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_receiver, TorqueStructArguments p_arguments, const char* p_methodName, int31_t p_variant) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String, IntPtrT, String> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<String> tmp0;
  TNode<String> tmp1;
  TNode<Smi> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_String_constexpr_string_0(state_, p_methodName);
    tmp1 = CodeStubAssembler(state_).ToThisString(TNode<Context>{p_context}, TNode<Object>{p_receiver}, TNode<String>{tmp0});
    tmp2 = CodeStubAssembler(state_).LoadStringLengthAsSmi(TNode<String>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp4 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{p_arguments.length}, TNode<IntPtrT>{tmp3});
    ca_.Branch(tmp4, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ca_.Goto(&block1, tmp1);
  }

  TNode<IntPtrT> tmp5;
  TNode<Object> tmp6;
  TNode<Number> tmp7;
  TNode<Smi> tmp8;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp6 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{p_arguments.frame}, TNode<RawPtrT>{p_arguments.base}, TNode<IntPtrT>{p_arguments.length}}, TNode<IntPtrT>{tmp5});
    tmp7 = CodeStubAssembler(state_).ToLength_Inline(TNode<Context>{p_context}, TNode<Object>{tmp6});
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_Smi_0(state_, TNode<Object>{tmp7}, &label9);
    ca_.Goto(&block10);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block11);
    }
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block8);
  }

  TNode<BoolT> tmp10;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp10 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp8}, TNode<Smi>{tmp2});
    ca_.Branch(tmp10, &block12, std::vector<Node*>{}, &block13, std::vector<Node*>{});
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block1, tmp1);
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block8);
  }

  TNode<String> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp11 = FromConstexpr_String_constexpr_string_0(state_, " ");
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp14 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{p_arguments.length}, TNode<IntPtrT>{tmp13});
    ca_.Branch(tmp14, &block14, std::vector<Node*>{}, &block15, std::vector<Node*>{tmp11, tmp12});
  }

  TNode<IntPtrT> tmp15;
  TNode<Object> tmp16;
  TNode<Oddball> tmp17;
  TNode<BoolT> tmp18;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp16 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{p_arguments.frame}, TNode<RawPtrT>{p_arguments.base}, TNode<IntPtrT>{p_arguments.length}}, TNode<IntPtrT>{tmp15});
    tmp17 = Undefined_0(state_);
    tmp18 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp16}, TNode<HeapObject>{tmp17});
    ca_.Branch(tmp18, &block16, std::vector<Node*>{}, &block17, std::vector<Node*>{tmp11, tmp12});
  }

  TNode<String> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<BoolT> tmp22;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp19 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{p_context}, TNode<Object>{tmp16});
    tmp20 = CodeStubAssembler(state_).LoadStringLengthAsWord(TNode<String>{tmp19});
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp22 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp20}, TNode<IntPtrT>{tmp21});
    ca_.Branch(tmp22, &block18, std::vector<Node*>{}, &block19, std::vector<Node*>{});
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    ca_.Goto(&block1, tmp1);
  }

  if (block19.is_used()) {
    ca_.Bind(&block19);
    ca_.Goto(&block17, tmp19, tmp20);
  }

  TNode<String> phi_bb17_8;
  TNode<IntPtrT> phi_bb17_9;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_8, &phi_bb17_9);
    ca_.Goto(&block15, phi_bb17_8, phi_bb17_9);
  }

  TNode<String> phi_bb15_8;
  TNode<IntPtrT> phi_bb15_9;
  TNode<BoolT> tmp23;
  TNode<BoolT> tmp24;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_8, &phi_bb15_9);
    tmp23 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{tmp7});
    tmp24 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp23});
    ca_.Branch(tmp24, &block24, std::vector<Node*>{phi_bb15_8, phi_bb15_9}, &block25, std::vector<Node*>{phi_bb15_8, phi_bb15_9});
  }

  TNode<String> phi_bb24_8;
  TNode<IntPtrT> phi_bb24_9;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_8, &phi_bb24_9);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> phi_bb25_8;
  TNode<IntPtrT> phi_bb25_9;
  TNode<Smi> tmp25;
  TNode<Smi> tmp26;
  TNode<BoolT> tmp27;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_8, &phi_bb25_9);
    tmp25 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp7});
    tmp26 = CodeStubAssembler(state_).SmiConstant(String::kMaxLength);
    tmp27 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp25}, TNode<Smi>{tmp26});
    ca_.Branch(tmp27, &block26, std::vector<Node*>{phi_bb25_8, phi_bb25_9}, &block27, std::vector<Node*>{phi_bb25_8, phi_bb25_9});
  }

  TNode<String> phi_bb26_8;
  TNode<IntPtrT> phi_bb26_9;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_8, &phi_bb26_9);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> phi_bb27_8;
  TNode<IntPtrT> phi_bb27_9;
  TNode<Smi> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<BoolT> tmp30;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_8, &phi_bb27_9);
    tmp28 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp25}, TNode<Smi>{tmp2});
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp30 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb27_9}, TNode<IntPtrT>{tmp29});
    ca_.Branch(tmp30, &block32, std::vector<Node*>{phi_bb27_8, phi_bb27_9}, &block33, std::vector<Node*>{phi_bb27_8, phi_bb27_9});
  }

  TNode<String> phi_bb32_8;
  TNode<IntPtrT> phi_bb32_9;
  TNode<String> tmp31;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_8, &phi_bb32_9);
    tmp31 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kStringRepeat, p_context, phi_bb32_8, tmp28));
    ca_.Goto(&block34, phi_bb32_8, phi_bb32_9, tmp31);
  }

  TNode<String> phi_bb33_8;
  TNode<IntPtrT> phi_bb33_9;
  TNode<Int32T> tmp32;
  TNode<Int32T> tmp33;
  TNode<Int32T> tmp34;
  TNode<Int32T> tmp35;
  TNode<Smi> tmp36;
  TNode<String> tmp37;
  TNode<Int32T> tmp38;
  TNode<BoolT> tmp39;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_8, &phi_bb33_9);
    tmp32 = CodeStubAssembler(state_).TruncateIntPtrToInt32(TNode<IntPtrT>{phi_bb33_9});
    tmp33 = Convert_int32_Smi_0(state_, TNode<Smi>{tmp28});
    tmp34 = CodeStubAssembler(state_).Int32Div(TNode<Int32T>{tmp33}, TNode<Int32T>{tmp32});
    tmp35 = CodeStubAssembler(state_).Int32Mod(TNode<Int32T>{tmp33}, TNode<Int32T>{tmp32});
    tmp36 = Convert_Smi_int32_0(state_, TNode<Int32T>{tmp34});
    tmp37 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kStringRepeat, p_context, phi_bb33_8, tmp36));
    tmp38 = FromConstexpr_int32_constexpr_int31_0(state_, 0);
    tmp39 = CodeStubAssembler(state_).Word32NotEqual(TNode<Int32T>{tmp35}, TNode<Int32T>{tmp38});
    ca_.Branch(tmp39, &block35, std::vector<Node*>{phi_bb33_8, phi_bb33_9}, &block36, std::vector<Node*>{phi_bb33_8, phi_bb33_9, tmp37});
  }

  TNode<String> phi_bb35_8;
  TNode<IntPtrT> phi_bb35_9;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<String> tmp42;
  TNode<String> tmp43;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_8, &phi_bb35_9);
    tmp40 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp35});
    tmp41 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp42 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltin(Builtins::kStringSubstring, p_context, phi_bb35_8, tmp41, tmp40));
    tmp43 = StringAdd_0(state_, TNode<Context>{p_context}, TNode<String>{tmp37}, TNode<String>{tmp42});
    ca_.Goto(&block36, phi_bb35_8, phi_bb35_9, tmp43);
  }

  TNode<String> phi_bb36_8;
  TNode<IntPtrT> phi_bb36_9;
  TNode<String> phi_bb36_12;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_8, &phi_bb36_9, &phi_bb36_12);
    ca_.Goto(&block34, phi_bb36_8, phi_bb36_9, phi_bb36_12);
  }

  TNode<String> phi_bb34_8;
  TNode<IntPtrT> phi_bb34_9;
  TNode<String> phi_bb34_12;
  TNode<BoolT> tmp44;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_8, &phi_bb34_9, &phi_bb34_12);
    tmp44 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprInt31Equal(p_variant, kStringPadStart_0(state_))));
    ca_.Branch(tmp44, &block41, std::vector<Node*>{phi_bb34_8, phi_bb34_9, phi_bb34_12}, &block42, std::vector<Node*>{phi_bb34_8, phi_bb34_9, phi_bb34_12});
  }

  TNode<String> phi_bb41_8;
  TNode<IntPtrT> phi_bb41_9;
  TNode<String> phi_bb41_12;
  TNode<String> tmp45;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_8, &phi_bb41_9, &phi_bb41_12);
    tmp45 = StringAdd_0(state_, TNode<Context>{p_context}, TNode<String>{phi_bb41_12}, TNode<String>{tmp1});
    ca_.Goto(&block1, tmp45);
  }

  TNode<String> phi_bb42_8;
  TNode<IntPtrT> phi_bb42_9;
  TNode<String> phi_bb42_12;
  TNode<String> tmp46;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_8, &phi_bb42_9, &phi_bb42_12);
    tmp46 = StringAdd_0(state_, TNode<Context>{p_context}, TNode<String>{tmp1}, TNode<String>{phi_bb42_12});
    ca_.Goto(&block1, tmp46);
  }

  TNode<String> phi_bb1_5;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_5);
    ca_.Goto(&block47, phi_bb1_5);
  }

  TNode<String> phi_bb47_5;
    ca_.Bind(&block47, &phi_bb47_5);
  return TNode<String>{phi_bb47_5};
}

TF_BUILTIN(StringPrototypePadStart, CodeStubAssembler) {
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
    ca_.Goto(&block0);

  TNode<String> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = StringPad_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, "String.prototype.padStart", kStringPadStart_0(state_));
    arguments.PopAndReturn(tmp0);
  }
}

TF_BUILTIN(StringPrototypePadEnd, CodeStubAssembler) {
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
    ca_.Goto(&block0);

  TNode<String> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = StringPad_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, "String.prototype.padEnd", kStringPadEnd_0(state_));
    arguments.PopAndReturn(tmp0);
  }
}

}  // namespace internal
}  // namespace v8

