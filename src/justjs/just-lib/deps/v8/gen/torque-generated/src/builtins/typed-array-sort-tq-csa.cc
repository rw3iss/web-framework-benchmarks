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

const char* kBuiltinNameSort_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return "%TypedArray%.prototype.sort";
}

TNode<Number> CallCompare_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSTypedArray> p_array, TNode<JSReceiver> p_comparefn, TNode<Object> p_a, TNode<Object> p_b) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Oddball> tmp0;
  TNode<Object> tmp1;
  TNode<Number> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<JSArrayBuffer> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Undefined_0(state_);
    tmp1 = CodeStubAssembler(state_).Call(TNode<Context>{p_context}, TNode<Object>{p_comparefn}, TNode<Object>{tmp0}, TNode<Object>{p_a}, TNode<Object>{p_b});
    tmp2 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{p_context}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp4 = CodeStubAssembler(state_).LoadReference<JSArrayBuffer>(CodeStubAssembler::Reference{p_array, tmp3});
    tmp5 = IsDetachedBuffer_0(state_, TNode<JSArrayBuffer>{tmp4});
    ca_.Branch(tmp5, &block2, std::vector<Node*>{}, &block3, std::vector<Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, MessageTemplate::kDetachedOperation, kBuiltinNameSort_0(state_));
  }

  TNode<BoolT> tmp6;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp6 = NumberIsNaN_0(state_, TNode<Number>{tmp2});
    ca_.Branch(tmp6, &block4, std::vector<Node*>{}, &block5, std::vector<Node*>{});
  }

  TNode<Number> tmp7;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp7 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    ca_.Goto(&block1, tmp7);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block1, tmp2);
  }

  TNode<Number> phi_bb1_5;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_5);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<Number>{phi_bb1_5};
}

void TypedArrayMerge_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSTypedArray> p_array, TNode<JSReceiver> p_comparefn, TNode<FixedArray> p_source, TNode<UintPtrT> p_from, TNode<UintPtrT> p_middle, TNode<UintPtrT> p_to, TNode<FixedArray> p_target) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT, UintPtrT> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block78(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block4, p_from, p_middle, p_from);
  }

  TNode<UintPtrT> phi_bb4_8;
  TNode<UintPtrT> phi_bb4_9;
  TNode<UintPtrT> phi_bb4_10;
  TNode<BoolT> tmp0;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_8, &phi_bb4_9, &phi_bb4_10);
    tmp0 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb4_10}, TNode<UintPtrT>{p_to});
    ca_.Branch(tmp0, &block2, std::vector<Node*>{phi_bb4_8, phi_bb4_9, phi_bb4_10}, &block3, std::vector<Node*>{phi_bb4_8, phi_bb4_9, phi_bb4_10});
  }

  TNode<UintPtrT> phi_bb2_8;
  TNode<UintPtrT> phi_bb2_9;
  TNode<UintPtrT> phi_bb2_10;
  TNode<BoolT> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_8, &phi_bb2_9, &phi_bb2_10);
    tmp1 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb2_8}, TNode<UintPtrT>{p_middle});
    ca_.Branch(tmp1, &block8, std::vector<Node*>{phi_bb2_8, phi_bb2_9, phi_bb2_10}, &block9, std::vector<Node*>{phi_bb2_8, phi_bb2_9, phi_bb2_10});
  }

  TNode<UintPtrT> phi_bb8_8;
  TNode<UintPtrT> phi_bb8_9;
  TNode<UintPtrT> phi_bb8_10;
  TNode<BoolT> tmp2;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_8, &phi_bb8_9, &phi_bb8_10);
    tmp2 = CodeStubAssembler(state_).UintPtrGreaterThanOrEqual(TNode<UintPtrT>{phi_bb8_9}, TNode<UintPtrT>{p_to});
    ca_.Goto(&block10, phi_bb8_8, phi_bb8_9, phi_bb8_10, tmp2);
  }

  TNode<UintPtrT> phi_bb9_8;
  TNode<UintPtrT> phi_bb9_9;
  TNode<UintPtrT> phi_bb9_10;
  TNode<BoolT> tmp3;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_8, &phi_bb9_9, &phi_bb9_10);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block10, phi_bb9_8, phi_bb9_9, phi_bb9_10, tmp3);
  }

  TNode<UintPtrT> phi_bb10_8;
  TNode<UintPtrT> phi_bb10_9;
  TNode<UintPtrT> phi_bb10_10;
  TNode<BoolT> phi_bb10_12;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_8, &phi_bb10_9, &phi_bb10_10, &phi_bb10_12);
    ca_.Branch(phi_bb10_12, &block6, std::vector<Node*>{phi_bb10_8, phi_bb10_9, phi_bb10_10}, &block7, std::vector<Node*>{phi_bb10_8, phi_bb10_9, phi_bb10_10});
  }

  TNode<UintPtrT> phi_bb6_8;
  TNode<UintPtrT> phi_bb6_9;
  TNode<UintPtrT> phi_bb6_10;
  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Smi> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<UintPtrT> tmp11;
  TNode<BoolT> tmp12;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_8, &phi_bb6_9, &phi_bb6_10);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp7 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_target, tmp6});
    tmp8 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp7});
    tmp9 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb6_10});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp11 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp12 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp10}, TNode<UintPtrT>{tmp11});
    ca_.Branch(tmp12, &block16, std::vector<Node*>{phi_bb6_8, phi_bb6_9, phi_bb6_10, phi_bb6_10, phi_bb6_10}, &block17, std::vector<Node*>{phi_bb6_8, phi_bb6_9, phi_bb6_10, phi_bb6_10, phi_bb6_10});
  }

  TNode<UintPtrT> phi_bb16_8;
  TNode<UintPtrT> phi_bb16_9;
  TNode<UintPtrT> phi_bb16_10;
  TNode<UintPtrT> phi_bb16_15;
  TNode<UintPtrT> phi_bb16_16;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<HeapObject> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Smi> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<UintPtrT> tmp23;
  TNode<UintPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<UintPtrT> tmp26;
  TNode<UintPtrT> tmp27;
  TNode<BoolT> tmp28;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_8, &phi_bb16_9, &phi_bb16_10, &phi_bb16_15, &phi_bb16_16);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp14 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp9}, TNode<IntPtrT>{tmp13});
    tmp15 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{tmp14});
    std::tie(tmp16, tmp17) = NewReference_Object_0(state_, TNode<HeapObject>{p_target}, TNode<IntPtrT>{tmp15}).Flatten();
    tmp18 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp21 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_source, tmp20});
    tmp22 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp21});
    tmp23 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp24 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb16_8}, TNode<UintPtrT>{tmp23});
    tmp25 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb16_8});
    tmp26 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp25});
    tmp27 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp22});
    tmp28 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp26}, TNode<UintPtrT>{tmp27});
    ca_.Branch(tmp28, &block23, std::vector<Node*>{phi_bb16_9, phi_bb16_10, phi_bb16_15, phi_bb16_16, phi_bb16_8, phi_bb16_8}, &block24, std::vector<Node*>{phi_bb16_9, phi_bb16_10, phi_bb16_15, phi_bb16_16, phi_bb16_8, phi_bb16_8});
  }

  TNode<UintPtrT> phi_bb17_8;
  TNode<UintPtrT> phi_bb17_9;
  TNode<UintPtrT> phi_bb17_10;
  TNode<UintPtrT> phi_bb17_15;
  TNode<UintPtrT> phi_bb17_16;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_8, &phi_bb17_9, &phi_bb17_10, &phi_bb17_15, &phi_bb17_16);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb23_9;
  TNode<UintPtrT> phi_bb23_10;
  TNode<UintPtrT> phi_bb23_15;
  TNode<UintPtrT> phi_bb23_16;
  TNode<UintPtrT> phi_bb23_23;
  TNode<UintPtrT> phi_bb23_24;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<HeapObject> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<Object> tmp34;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_9, &phi_bb23_10, &phi_bb23_15, &phi_bb23_16, &phi_bb23_23, &phi_bb23_24);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp30 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp25}, TNode<IntPtrT>{tmp29});
    tmp31 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp18}, TNode<IntPtrT>{tmp30});
    std::tie(tmp32, tmp33) = NewReference_Object_0(state_, TNode<HeapObject>{p_source}, TNode<IntPtrT>{tmp31}).Flatten();
    tmp34 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp32, tmp33});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp16, tmp17}, tmp34);
    ca_.Goto(&block11, tmp24, phi_bb23_9, phi_bb23_10);
  }

  TNode<UintPtrT> phi_bb24_9;
  TNode<UintPtrT> phi_bb24_10;
  TNode<UintPtrT> phi_bb24_15;
  TNode<UintPtrT> phi_bb24_16;
  TNode<UintPtrT> phi_bb24_23;
  TNode<UintPtrT> phi_bb24_24;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_9, &phi_bb24_10, &phi_bb24_15, &phi_bb24_16, &phi_bb24_23, &phi_bb24_24);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb7_8;
  TNode<UintPtrT> phi_bb7_9;
  TNode<UintPtrT> phi_bb7_10;
  TNode<BoolT> tmp35;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_8, &phi_bb7_9, &phi_bb7_10);
    tmp35 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb7_8}, TNode<UintPtrT>{p_middle});
    ca_.Branch(tmp35, &block26, std::vector<Node*>{phi_bb7_8, phi_bb7_9, phi_bb7_10}, &block27, std::vector<Node*>{phi_bb7_8, phi_bb7_9, phi_bb7_10});
  }

  TNode<UintPtrT> phi_bb26_8;
  TNode<UintPtrT> phi_bb26_9;
  TNode<UintPtrT> phi_bb26_10;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<Smi> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<UintPtrT> tmp42;
  TNode<UintPtrT> tmp43;
  TNode<BoolT> tmp44;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_8, &phi_bb26_9, &phi_bb26_10);
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp37 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp38 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp39 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_source, tmp38});
    tmp40 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp39});
    tmp41 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb26_8});
    tmp42 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp41});
    tmp43 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp40});
    tmp44 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp42}, TNode<UintPtrT>{tmp43});
    ca_.Branch(tmp44, &block33, std::vector<Node*>{phi_bb26_8, phi_bb26_9, phi_bb26_10, phi_bb26_8, phi_bb26_8}, &block34, std::vector<Node*>{phi_bb26_8, phi_bb26_9, phi_bb26_10, phi_bb26_8, phi_bb26_8});
  }

  TNode<UintPtrT> phi_bb33_8;
  TNode<UintPtrT> phi_bb33_9;
  TNode<UintPtrT> phi_bb33_10;
  TNode<UintPtrT> phi_bb33_15;
  TNode<UintPtrT> phi_bb33_16;
  TNode<IntPtrT> tmp45;
  TNode<IntPtrT> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<HeapObject> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<Object> tmp50;
  TNode<Object> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<Smi> tmp55;
  TNode<IntPtrT> tmp56;
  TNode<IntPtrT> tmp57;
  TNode<UintPtrT> tmp58;
  TNode<UintPtrT> tmp59;
  TNode<BoolT> tmp60;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_8, &phi_bb33_9, &phi_bb33_10, &phi_bb33_15, &phi_bb33_16);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp46 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp41}, TNode<IntPtrT>{tmp45});
    tmp47 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp46});
    std::tie(tmp48, tmp49) = NewReference_Object_0(state_, TNode<HeapObject>{p_source}, TNode<IntPtrT>{tmp47}).Flatten();
    tmp50 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp48, tmp49});
    tmp51 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp50});
    tmp52 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp53 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp54 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp55 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_source, tmp54});
    tmp56 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp55});
    tmp57 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb33_9});
    tmp58 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp57});
    tmp59 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp56});
    tmp60 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp58}, TNode<UintPtrT>{tmp59});
    ca_.Branch(tmp60, &block40, std::vector<Node*>{phi_bb33_8, phi_bb33_9, phi_bb33_10, phi_bb33_9, phi_bb33_9}, &block41, std::vector<Node*>{phi_bb33_8, phi_bb33_9, phi_bb33_10, phi_bb33_9, phi_bb33_9});
  }

  TNode<UintPtrT> phi_bb34_8;
  TNode<UintPtrT> phi_bb34_9;
  TNode<UintPtrT> phi_bb34_10;
  TNode<UintPtrT> phi_bb34_15;
  TNode<UintPtrT> phi_bb34_16;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_8, &phi_bb34_9, &phi_bb34_10, &phi_bb34_15, &phi_bb34_16);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb40_8;
  TNode<UintPtrT> phi_bb40_9;
  TNode<UintPtrT> phi_bb40_10;
  TNode<UintPtrT> phi_bb40_16;
  TNode<UintPtrT> phi_bb40_17;
  TNode<IntPtrT> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<HeapObject> tmp64;
  TNode<IntPtrT> tmp65;
  TNode<Object> tmp66;
  TNode<Object> tmp67;
  TNode<Number> tmp68;
  TNode<Number> tmp69;
  TNode<BoolT> tmp70;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_8, &phi_bb40_9, &phi_bb40_10, &phi_bb40_16, &phi_bb40_17);
    tmp61 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp62 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp57}, TNode<IntPtrT>{tmp61});
    tmp63 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp52}, TNode<IntPtrT>{tmp62});
    std::tie(tmp64, tmp65) = NewReference_Object_0(state_, TNode<HeapObject>{p_source}, TNode<IntPtrT>{tmp63}).Flatten();
    tmp66 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp64, tmp65});
    tmp67 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp66});
    tmp68 = CallCompare_0(state_, TNode<Context>{p_context}, TNode<JSTypedArray>{p_array}, TNode<JSReceiver>{p_comparefn}, TNode<Object>{tmp51}, TNode<Object>{tmp67});
    tmp69 = FromConstexpr_Number_constexpr_int31_0(state_, 0);
    tmp70 = NumberIsLessThanOrEqual_0(state_, TNode<Number>{tmp68}, TNode<Number>{tmp69});
    ca_.Branch(tmp70, &block43, std::vector<Node*>{phi_bb40_8, phi_bb40_9, phi_bb40_10}, &block44, std::vector<Node*>{phi_bb40_8, phi_bb40_9, phi_bb40_10});
  }

  TNode<UintPtrT> phi_bb41_8;
  TNode<UintPtrT> phi_bb41_9;
  TNode<UintPtrT> phi_bb41_10;
  TNode<UintPtrT> phi_bb41_16;
  TNode<UintPtrT> phi_bb41_17;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_8, &phi_bb41_9, &phi_bb41_10, &phi_bb41_16, &phi_bb41_17);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb43_8;
  TNode<UintPtrT> phi_bb43_9;
  TNode<UintPtrT> phi_bb43_10;
  TNode<IntPtrT> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<IntPtrT> tmp73;
  TNode<Smi> tmp74;
  TNode<IntPtrT> tmp75;
  TNode<IntPtrT> tmp76;
  TNode<UintPtrT> tmp77;
  TNode<UintPtrT> tmp78;
  TNode<BoolT> tmp79;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_8, &phi_bb43_9, &phi_bb43_10);
    tmp71 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp72 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp73 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp74 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_target, tmp73});
    tmp75 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp74});
    tmp76 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb43_10});
    tmp77 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp76});
    tmp78 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp75});
    tmp79 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp77}, TNode<UintPtrT>{tmp78});
    ca_.Branch(tmp79, &block50, std::vector<Node*>{phi_bb43_8, phi_bb43_9, phi_bb43_10, phi_bb43_10, phi_bb43_10}, &block51, std::vector<Node*>{phi_bb43_8, phi_bb43_9, phi_bb43_10, phi_bb43_10, phi_bb43_10});
  }

  TNode<UintPtrT> phi_bb50_8;
  TNode<UintPtrT> phi_bb50_9;
  TNode<UintPtrT> phi_bb50_10;
  TNode<UintPtrT> phi_bb50_17;
  TNode<UintPtrT> phi_bb50_18;
  TNode<IntPtrT> tmp80;
  TNode<IntPtrT> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<HeapObject> tmp83;
  TNode<IntPtrT> tmp84;
  TNode<UintPtrT> tmp85;
  TNode<UintPtrT> tmp86;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_8, &phi_bb50_9, &phi_bb50_10, &phi_bb50_17, &phi_bb50_18);
    tmp80 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp81 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp76}, TNode<IntPtrT>{tmp80});
    tmp82 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp71}, TNode<IntPtrT>{tmp81});
    std::tie(tmp83, tmp84) = NewReference_Object_0(state_, TNode<HeapObject>{p_target}, TNode<IntPtrT>{tmp82}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp83, tmp84}, tmp51);
    tmp85 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp86 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb50_8}, TNode<UintPtrT>{tmp85});
    ca_.Goto(&block45, tmp86, phi_bb50_9, phi_bb50_10);
  }

  TNode<UintPtrT> phi_bb51_8;
  TNode<UintPtrT> phi_bb51_9;
  TNode<UintPtrT> phi_bb51_10;
  TNode<UintPtrT> phi_bb51_17;
  TNode<UintPtrT> phi_bb51_18;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_8, &phi_bb51_9, &phi_bb51_10, &phi_bb51_17, &phi_bb51_18);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb44_8;
  TNode<UintPtrT> phi_bb44_9;
  TNode<UintPtrT> phi_bb44_10;
  TNode<IntPtrT> tmp87;
  TNode<IntPtrT> tmp88;
  TNode<IntPtrT> tmp89;
  TNode<Smi> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<IntPtrT> tmp92;
  TNode<UintPtrT> tmp93;
  TNode<UintPtrT> tmp94;
  TNode<BoolT> tmp95;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_8, &phi_bb44_9, &phi_bb44_10);
    tmp87 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp88 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp89 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp90 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_target, tmp89});
    tmp91 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp90});
    tmp92 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb44_10});
    tmp93 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp92});
    tmp94 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp91});
    tmp95 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp93}, TNode<UintPtrT>{tmp94});
    ca_.Branch(tmp95, &block57, std::vector<Node*>{phi_bb44_8, phi_bb44_9, phi_bb44_10, phi_bb44_10, phi_bb44_10}, &block58, std::vector<Node*>{phi_bb44_8, phi_bb44_9, phi_bb44_10, phi_bb44_10, phi_bb44_10});
  }

  TNode<UintPtrT> phi_bb57_8;
  TNode<UintPtrT> phi_bb57_9;
  TNode<UintPtrT> phi_bb57_10;
  TNode<UintPtrT> phi_bb57_17;
  TNode<UintPtrT> phi_bb57_18;
  TNode<IntPtrT> tmp96;
  TNode<IntPtrT> tmp97;
  TNode<IntPtrT> tmp98;
  TNode<HeapObject> tmp99;
  TNode<IntPtrT> tmp100;
  TNode<UintPtrT> tmp101;
  TNode<UintPtrT> tmp102;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_8, &phi_bb57_9, &phi_bb57_10, &phi_bb57_17, &phi_bb57_18);
    tmp96 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp97 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp92}, TNode<IntPtrT>{tmp96});
    tmp98 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp87}, TNode<IntPtrT>{tmp97});
    std::tie(tmp99, tmp100) = NewReference_Object_0(state_, TNode<HeapObject>{p_target}, TNode<IntPtrT>{tmp98}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp99, tmp100}, tmp67);
    tmp101 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp102 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb57_9}, TNode<UintPtrT>{tmp101});
    ca_.Goto(&block45, phi_bb57_8, tmp102, phi_bb57_10);
  }

  TNode<UintPtrT> phi_bb58_8;
  TNode<UintPtrT> phi_bb58_9;
  TNode<UintPtrT> phi_bb58_10;
  TNode<UintPtrT> phi_bb58_17;
  TNode<UintPtrT> phi_bb58_18;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_8, &phi_bb58_9, &phi_bb58_10, &phi_bb58_17, &phi_bb58_18);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb45_8;
  TNode<UintPtrT> phi_bb45_9;
  TNode<UintPtrT> phi_bb45_10;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_8, &phi_bb45_9, &phi_bb45_10);
    ca_.Goto(&block28, phi_bb45_8, phi_bb45_9, phi_bb45_10);
  }

  TNode<UintPtrT> phi_bb27_8;
  TNode<UintPtrT> phi_bb27_9;
  TNode<UintPtrT> phi_bb27_10;
  TNode<IntPtrT> tmp103;
  TNode<IntPtrT> tmp104;
  TNode<IntPtrT> tmp105;
  TNode<Smi> tmp106;
  TNode<IntPtrT> tmp107;
  TNode<IntPtrT> tmp108;
  TNode<UintPtrT> tmp109;
  TNode<UintPtrT> tmp110;
  TNode<BoolT> tmp111;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_8, &phi_bb27_9, &phi_bb27_10);
    tmp103 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp104 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp105 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp106 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_target, tmp105});
    tmp107 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp106});
    tmp108 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb27_10});
    tmp109 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp108});
    tmp110 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp107});
    tmp111 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp109}, TNode<UintPtrT>{tmp110});
    ca_.Branch(tmp111, &block68, std::vector<Node*>{phi_bb27_8, phi_bb27_9, phi_bb27_10, phi_bb27_10, phi_bb27_10}, &block69, std::vector<Node*>{phi_bb27_8, phi_bb27_9, phi_bb27_10, phi_bb27_10, phi_bb27_10});
  }

  TNode<UintPtrT> phi_bb68_8;
  TNode<UintPtrT> phi_bb68_9;
  TNode<UintPtrT> phi_bb68_10;
  TNode<UintPtrT> phi_bb68_15;
  TNode<UintPtrT> phi_bb68_16;
  TNode<IntPtrT> tmp112;
  TNode<IntPtrT> tmp113;
  TNode<IntPtrT> tmp114;
  TNode<HeapObject> tmp115;
  TNode<IntPtrT> tmp116;
  TNode<IntPtrT> tmp117;
  TNode<IntPtrT> tmp118;
  TNode<IntPtrT> tmp119;
  TNode<Smi> tmp120;
  TNode<IntPtrT> tmp121;
  TNode<UintPtrT> tmp122;
  TNode<UintPtrT> tmp123;
  TNode<IntPtrT> tmp124;
  TNode<UintPtrT> tmp125;
  TNode<UintPtrT> tmp126;
  TNode<BoolT> tmp127;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_8, &phi_bb68_9, &phi_bb68_10, &phi_bb68_15, &phi_bb68_16);
    tmp112 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp113 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp108}, TNode<IntPtrT>{tmp112});
    tmp114 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp103}, TNode<IntPtrT>{tmp113});
    std::tie(tmp115, tmp116) = NewReference_Object_0(state_, TNode<HeapObject>{p_target}, TNode<IntPtrT>{tmp114}).Flatten();
    tmp117 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp118 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp119 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp120 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_source, tmp119});
    tmp121 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp120});
    tmp122 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp123 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb68_9}, TNode<UintPtrT>{tmp122});
    tmp124 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb68_9});
    tmp125 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp124});
    tmp126 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp121});
    tmp127 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp125}, TNode<UintPtrT>{tmp126});
    ca_.Branch(tmp127, &block75, std::vector<Node*>{phi_bb68_8, phi_bb68_10, phi_bb68_15, phi_bb68_16, phi_bb68_9, phi_bb68_9}, &block76, std::vector<Node*>{phi_bb68_8, phi_bb68_10, phi_bb68_15, phi_bb68_16, phi_bb68_9, phi_bb68_9});
  }

  TNode<UintPtrT> phi_bb69_8;
  TNode<UintPtrT> phi_bb69_9;
  TNode<UintPtrT> phi_bb69_10;
  TNode<UintPtrT> phi_bb69_15;
  TNode<UintPtrT> phi_bb69_16;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_8, &phi_bb69_9, &phi_bb69_10, &phi_bb69_15, &phi_bb69_16);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb75_8;
  TNode<UintPtrT> phi_bb75_10;
  TNode<UintPtrT> phi_bb75_15;
  TNode<UintPtrT> phi_bb75_16;
  TNode<UintPtrT> phi_bb75_23;
  TNode<UintPtrT> phi_bb75_24;
  TNode<IntPtrT> tmp128;
  TNode<IntPtrT> tmp129;
  TNode<IntPtrT> tmp130;
  TNode<HeapObject> tmp131;
  TNode<IntPtrT> tmp132;
  TNode<Object> tmp133;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_8, &phi_bb75_10, &phi_bb75_15, &phi_bb75_16, &phi_bb75_23, &phi_bb75_24);
    tmp128 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp129 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp124}, TNode<IntPtrT>{tmp128});
    tmp130 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp117}, TNode<IntPtrT>{tmp129});
    std::tie(tmp131, tmp132) = NewReference_Object_0(state_, TNode<HeapObject>{p_source}, TNode<IntPtrT>{tmp130}).Flatten();
    tmp133 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp131, tmp132});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp115, tmp116}, tmp133);
    ca_.Goto(&block28, phi_bb75_8, tmp123, phi_bb75_10);
  }

  TNode<UintPtrT> phi_bb76_8;
  TNode<UintPtrT> phi_bb76_10;
  TNode<UintPtrT> phi_bb76_15;
  TNode<UintPtrT> phi_bb76_16;
  TNode<UintPtrT> phi_bb76_23;
  TNode<UintPtrT> phi_bb76_24;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_8, &phi_bb76_10, &phi_bb76_15, &phi_bb76_16, &phi_bb76_23, &phi_bb76_24);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb28_8;
  TNode<UintPtrT> phi_bb28_9;
  TNode<UintPtrT> phi_bb28_10;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_8, &phi_bb28_9, &phi_bb28_10);
    ca_.Goto(&block11, phi_bb28_8, phi_bb28_9, phi_bb28_10);
  }

  TNode<UintPtrT> phi_bb11_8;
  TNode<UintPtrT> phi_bb11_9;
  TNode<UintPtrT> phi_bb11_10;
  TNode<UintPtrT> tmp134;
  TNode<UintPtrT> tmp135;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_8, &phi_bb11_9, &phi_bb11_10);
    tmp134 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp135 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb11_10}, TNode<UintPtrT>{tmp134});
    ca_.Goto(&block4, phi_bb11_8, phi_bb11_9, tmp135);
  }

  TNode<UintPtrT> phi_bb3_8;
  TNode<UintPtrT> phi_bb3_9;
  TNode<UintPtrT> phi_bb3_10;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_8, &phi_bb3_9, &phi_bb3_10);
    ca_.Goto(&block78);
  }

    ca_.Bind(&block78);
}

TF_BUILTIN(TypedArrayMergeSort, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedCast<Context>(Parameter(Descriptor::kContext));
  USE(parameter0);
  TNode<FixedArray> parameter1 = UncheckedCast<FixedArray>(Parameter(Descriptor::ParameterIndex<0>()));
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<1>()));
  USE(parameter2);
  TNode<UintPtrT> parameter3 = UncheckedCast<UintPtrT>(Parameter(Descriptor::ParameterIndex<2>()));
  USE(parameter3);
  TNode<FixedArray> parameter4 = UncheckedCast<FixedArray>(Parameter(Descriptor::ParameterIndex<3>()));
  USE(parameter4);
  TNode<JSTypedArray> parameter5 = UncheckedCast<JSTypedArray>(Parameter(Descriptor::ParameterIndex<4>()));
  USE(parameter5);
  TNode<JSReceiver> parameter6 = UncheckedCast<JSReceiver>(Parameter(Descriptor::ParameterIndex<5>()));
  USE(parameter6);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<UintPtrT> tmp0;
  TNode<UintPtrT> tmp1;
  TNode<UintPtrT> tmp2;
  TNode<UintPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).UintPtrSub(TNode<UintPtrT>{parameter3}, TNode<UintPtrT>{parameter2});
    tmp1 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp2 = CodeStubAssembler(state_).WordShr(TNode<UintPtrT>{tmp0}, TNode<UintPtrT>{tmp1});
    tmp3 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{parameter2}, TNode<UintPtrT>{tmp2});
    tmp4 = CodeStubAssembler(state_).UintPtrSub(TNode<UintPtrT>{tmp3}, TNode<UintPtrT>{parameter2});
    tmp5 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp6 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp4}, TNode<UintPtrT>{tmp5});
    ca_.Branch(tmp6, &block5, std::vector<Node*>{}, &block6, std::vector<Node*>{});
  }

  TNode<Object> tmp7;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp7 = CodeStubAssembler(state_).CallBuiltin(Builtins::kTypedArrayMergeSort, parameter0, parameter4, parameter2, tmp3, parameter1, parameter5, parameter6);
    ca_.Goto(&block6);
  }

  TNode<UintPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<BoolT> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = CodeStubAssembler(state_).UintPtrSub(TNode<UintPtrT>{parameter3}, TNode<UintPtrT>{tmp3});
    tmp9 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp10 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp8}, TNode<UintPtrT>{tmp9});
    ca_.Branch(tmp10, &block7, std::vector<Node*>{}, &block8, std::vector<Node*>{});
  }

  TNode<Object> tmp11;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp11 = CodeStubAssembler(state_).CallBuiltin(Builtins::kTypedArrayMergeSort, parameter0, parameter4, tmp3, parameter3, parameter1, parameter5, parameter6);
    ca_.Goto(&block8);
  }

  TNode<Oddball> tmp12;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    TypedArrayMerge_0(state_, TNode<Context>{parameter0}, TNode<JSTypedArray>{parameter5}, TNode<JSReceiver>{parameter6}, TNode<FixedArray>{parameter1}, TNode<UintPtrT>{parameter2}, TNode<UintPtrT>{tmp3}, TNode<UintPtrT>{parameter3}, TNode<FixedArray>{parameter4});
    tmp12 = Undefined_0(state_);
    CodeStubAssembler(state_).Return(tmp12);
  }
}

TF_BUILTIN(TypedArrayPrototypeSort, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, UintPtrT, UintPtrT, UintPtrT> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Object> tmp1;
  TNode<Oddball> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}}, TNode<IntPtrT>{tmp0});
    tmp2 = Undefined_0(state_);
    tmp3 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp1}, TNode<HeapObject>{tmp2});
    ca_.Branch(tmp3, &block3, std::vector<Node*>{}, &block4, std::vector<Node*>{});
  }

  TNode<BoolT> tmp4;
  TNode<BoolT> tmp5;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp4 = Is_Callable_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp5 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp4});
    ca_.Goto(&block5, tmp5);
  }

  TNode<BoolT> tmp6;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp6 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block5, tmp6);
  }

  TNode<BoolT> phi_bb5_7;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_7);
    ca_.Branch(phi_bb5_7, &block1, std::vector<Node*>{}, &block2, std::vector<Node*>{});
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, MessageTemplate::kBadSortComparisonFunction, TNode<Object>{tmp1});
  }

  TNode<JSTypedArray> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<BoolT> tmp11;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp7 = TypedArrayBuiltinsAssembler(state_).ValidateTypedArray(TNode<Context>{parameter0}, TNode<Object>{parameter1}, kBuiltinNameSort_0(state_));
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp9 = CodeStubAssembler(state_).LoadReference<UintPtrT>(CodeStubAssembler::Reference{tmp7, tmp8});
    tmp10 = FromConstexpr_uintptr_constexpr_int31_0(state_, 2);
    tmp11 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp9}, TNode<UintPtrT>{tmp10});
    ca_.Branch(tmp11, &block6, std::vector<Node*>{}, &block7, std::vector<Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    arguments.PopAndReturn(tmp7);
  }

  TNode<Oddball> tmp12;
  TNode<BoolT> tmp13;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp12 = Undefined_0(state_);
    tmp13 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp1}, TNode<HeapObject>{tmp12});
    ca_.Branch(tmp13, &block8, std::vector<Node*>{}, &block9, std::vector<Node*>{});
  }

  TNode<JSTypedArray> tmp14;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp14 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kTypedArraySortFast, parameter0, parameter1)); 
    arguments.PopAndReturn(tmp14);
  }

  TNode<JSReceiver> tmp15;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    compiler::CodeAssemblerLabel label16(&ca_);
    tmp15 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1}, &label16);
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

  TNode<Int32T> tmp17;
  TNode<BuiltinPtr> tmp18;
  TNode<BuiltinPtr> tmp19;
  TNode<BuiltinPtr> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<FixedArray> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<FixedArray> tmp24;
  TNode<UintPtrT> tmp25;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp17 = CodeStubAssembler(state_).LoadElementsKind(TNode<JSTypedArray>{tmp7});
    std::tie(tmp18, tmp19, tmp20) = GetTypedArrayAccessor_0(state_, TNode<Int32T>{tmp17}).Flatten();
    tmp21 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp9});
    tmp22 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp21});
    tmp23 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp9});
    tmp24 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp23});
    tmp25 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block16, tmp25);
  }

  TNode<UintPtrT> phi_bb16_15;
  TNode<BoolT> tmp26;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_15);
    tmp26 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb16_15}, TNode<UintPtrT>{tmp9});
    ca_.Branch(tmp26, &block14, std::vector<Node*>{phi_bb16_15}, &block15, std::vector<Node*>{phi_bb16_15});
  }

  TNode<UintPtrT> phi_bb14_15;
  TNode<Numeric> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<Smi> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<UintPtrT> tmp34;
  TNode<UintPtrT> tmp35;
  TNode<BoolT> tmp36;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_15);
tmp27 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallableFor(ca_.isolate(),ExampleBuiltinForTorqueFunctionPointerType(1)).descriptor(), tmp18, TNode<Object>(), tmp7, phi_bb14_15));
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp30 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp31 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp22, tmp30});
    tmp32 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp31});
    tmp33 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb14_15});
    tmp34 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp33});
    tmp35 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp32});
    tmp36 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp34}, TNode<UintPtrT>{tmp35});
    ca_.Branch(tmp36, &block23, std::vector<Node*>{phi_bb14_15, phi_bb14_15, phi_bb14_15}, &block24, std::vector<Node*>{phi_bb14_15, phi_bb14_15, phi_bb14_15});
  }

  TNode<UintPtrT> phi_bb23_15;
  TNode<UintPtrT> phi_bb23_21;
  TNode<UintPtrT> phi_bb23_22;
  TNode<IntPtrT> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<HeapObject> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<IntPtrT> tmp42;
  TNode<IntPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<Smi> tmp45;
  TNode<IntPtrT> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<UintPtrT> tmp48;
  TNode<UintPtrT> tmp49;
  TNode<BoolT> tmp50;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_15, &phi_bb23_21, &phi_bb23_22);
    tmp37 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp38 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp33}, TNode<IntPtrT>{tmp37});
    tmp39 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp28}, TNode<IntPtrT>{tmp38});
    std::tie(tmp40, tmp41) = NewReference_Object_0(state_, TNode<HeapObject>{tmp22}, TNode<IntPtrT>{tmp39}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp40, tmp41}, tmp27);
    tmp42 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp43 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp44 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp45 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp24, tmp44});
    tmp46 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp45});
    tmp47 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb23_15});
    tmp48 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp47});
    tmp49 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp46});
    tmp50 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp48}, TNode<UintPtrT>{tmp49});
    ca_.Branch(tmp50, &block30, std::vector<Node*>{phi_bb23_15, phi_bb23_15, phi_bb23_15}, &block31, std::vector<Node*>{phi_bb23_15, phi_bb23_15, phi_bb23_15});
  }

  TNode<UintPtrT> phi_bb24_15;
  TNode<UintPtrT> phi_bb24_21;
  TNode<UintPtrT> phi_bb24_22;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_15, &phi_bb24_21, &phi_bb24_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb30_15;
  TNode<UintPtrT> phi_bb30_21;
  TNode<UintPtrT> phi_bb30_22;
  TNode<IntPtrT> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<HeapObject> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<UintPtrT> tmp56;
  TNode<UintPtrT> tmp57;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_15, &phi_bb30_21, &phi_bb30_22);
    tmp51 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp52 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp47}, TNode<IntPtrT>{tmp51});
    tmp53 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp42}, TNode<IntPtrT>{tmp52});
    std::tie(tmp54, tmp55) = NewReference_Object_0(state_, TNode<HeapObject>{tmp24}, TNode<IntPtrT>{tmp53}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp54, tmp55}, tmp27);
    tmp56 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp57 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb30_15}, TNode<UintPtrT>{tmp56});
    ca_.Goto(&block16, tmp57);
  }

  TNode<UintPtrT> phi_bb31_15;
  TNode<UintPtrT> phi_bb31_21;
  TNode<UintPtrT> phi_bb31_22;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_15, &phi_bb31_21, &phi_bb31_22);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb15_15;
  TNode<UintPtrT> tmp58;
  TNode<Object> tmp59;
  TNode<UintPtrT> tmp60;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_15);
    tmp58 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    tmp59 = CodeStubAssembler(state_).CallBuiltin(Builtins::kTypedArrayMergeSort, parameter0, tmp24, tmp58, tmp9, tmp22, tmp7, tmp15);
    tmp60 = FromConstexpr_uintptr_constexpr_int31_0(state_, 0);
    ca_.Goto(&block35, tmp60);
  }

  TNode<UintPtrT> phi_bb35_15;
  TNode<BoolT> tmp61;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_15);
    tmp61 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb35_15}, TNode<UintPtrT>{tmp9});
    ca_.Branch(tmp61, &block33, std::vector<Node*>{phi_bb35_15}, &block34, std::vector<Node*>{phi_bb35_15});
  }

  TNode<UintPtrT> phi_bb33_15;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<Smi> tmp65;
  TNode<IntPtrT> tmp66;
  TNode<IntPtrT> tmp67;
  TNode<UintPtrT> tmp68;
  TNode<UintPtrT> tmp69;
  TNode<BoolT> tmp70;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_15);
    tmp62 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp63 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp64 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp65 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp22, tmp64});
    tmp66 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp65});
    tmp67 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb33_15});
    tmp68 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp67});
    tmp69 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp66});
    tmp70 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp68}, TNode<UintPtrT>{tmp69});
    ca_.Branch(tmp70, &block41, std::vector<Node*>{phi_bb33_15, phi_bb33_15, phi_bb33_15, phi_bb33_15}, &block42, std::vector<Node*>{phi_bb33_15, phi_bb33_15, phi_bb33_15, phi_bb33_15});
  }

  TNode<UintPtrT> phi_bb41_15;
  TNode<UintPtrT> phi_bb41_21;
  TNode<UintPtrT> phi_bb41_26;
  TNode<UintPtrT> phi_bb41_27;
  TNode<IntPtrT> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<IntPtrT> tmp73;
  TNode<HeapObject> tmp74;
  TNode<IntPtrT> tmp75;
  TNode<Object> tmp76;
  TNode<Numeric> tmp77;
  TNode<Smi> tmp78;
  TNode<UintPtrT> tmp79;
  TNode<UintPtrT> tmp80;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_15, &phi_bb41_21, &phi_bb41_26, &phi_bb41_27);
    tmp71 = FromConstexpr_intptr_constexpr_int31_0(state_, kTaggedSize);
    tmp72 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp67}, TNode<IntPtrT>{tmp71});
    tmp73 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp62}, TNode<IntPtrT>{tmp72});
    std::tie(tmp74, tmp75) = NewReference_Object_0(state_, TNode<HeapObject>{tmp22}, TNode<IntPtrT>{tmp73}).Flatten();
    tmp76 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp74, tmp75});
    tmp77 = UnsafeCast_Numeric_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp76});
tmp78 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallableFor(ca_.isolate(),ExampleBuiltinForTorqueFunctionPointerType(2)).descriptor(), tmp19, parameter0, tmp7, phi_bb41_21, tmp77));
    tmp79 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp80 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb41_15}, TNode<UintPtrT>{tmp79});
    ca_.Goto(&block35, tmp80);
  }

  TNode<UintPtrT> phi_bb42_15;
  TNode<UintPtrT> phi_bb42_21;
  TNode<UintPtrT> phi_bb42_26;
  TNode<UintPtrT> phi_bb42_27;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_15, &phi_bb42_21, &phi_bb42_26, &phi_bb42_27);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> phi_bb34_15;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_15);
    arguments.PopAndReturn(tmp7);
  }
}

TNode<Numeric> UnsafeCast_Numeric_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Numeric> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<Numeric>{tmp0};
}

}  // namespace internal
}  // namespace v8

